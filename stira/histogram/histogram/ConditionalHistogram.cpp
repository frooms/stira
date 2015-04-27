
/***********************************************************************************
 *   Copyright (C) 2008 by Filip Rooms                                             *
 *                                                                                 *
 *  Terms and conditions for using this software in any form are provided in the   *
 *  file COPYING, which can be found in the root directory of this project.        *
 *                                                                                 *
 *   Contact data: filip.rooms@gmail.com                                           *
 *                 http://www.filiprooms.be/                                       *
 *                                                                                 *
 ***********************************************************************************/
#include <string>
#include "ConditionalHistogram.h"
#include "../../image/tools/ImageIO.h"
#include "../../image/tools/NumberGridTools.h"

using namespace std;

namespace stira {
namespace histogram {

using namespace image;

ConditionalHistogram::ConditionalHistogram( double horizontalBinSize, double verticalBinSize, double horizontalMin, double horizontalMax, double verticalMin, double verticalMax, int nrBands )
{
   mNrBands = nrBands;
   mHorizontalBinSize = horizontalBinSize;
   mVerticalBinSize = verticalBinSize;
   mHorizontalMin = horizontalMin;
   mHorizontalMax = horizontalMax;
   mVerticalMin = verticalMin;
   mVerticalMax = verticalMax;

   int width  = (int)( fabs(horizontalMax - horizontalMin) + 1.5 );
   int height = (int)( fabs(verticalMax - verticalMin) + 1.5 );

   for (int i = 0; i < mNrBands; i++)
   {
      bool needInitialisation = true;
      int initialIntValue = 0;
      ArrayGrid<int>* pGrid = new ArrayGrid<int>( width, height, needInitialisation, initialIntValue );
      mvpData.push_back( pGrid );
   }
}

//----------------------------------------------------------------

ConditionalHistogram::ConditionalHistogram( Image* pImage1, Image* pImage2, bool useAbsoluteValues )
{
   assert( pImage1->GetWidth() == pImage2->GetWidth() );
   assert( pImage1->GetHeight() == pImage2->GetHeight() );
   assert( pImage1->GetNumberOfBands() == pImage2->GetNumberOfBands() );
   mNrBands = pImage1->GetNumberOfBands();

   mHorizontalMin = 0.0;
   mHorizontalMax = pImage1->GetAbsMax( );
   mVerticalMin = 0.0;
   mVerticalMax = pImage2->GetAbsMax( );

   for (int bandNr = 0; bandNr < mNrBands; bandNr++ )
   {
      BuildConditionalHistogram( pImage1->GetBands()[bandNr], pImage2->GetBands()[bandNr], useAbsoluteValues );
   }

   VisualizeAsImage(std::string("MyConditionalHistogram.ppm"));
}

//----------------------------------------------------------------

ConditionalHistogram::ConditionalHistogram( image::ArrayGrid<double>* pGrid1, image::ArrayGrid<double>* pGrid2, bool useAbsoluteValues )
{
   assert( pGrid1->GetWidth()  == pGrid2->GetWidth() );
   assert( pGrid1->GetHeight() == pGrid2->GetHeight() );

   mHorizontalMin = 0.0;
   mHorizontalMax = NumberGridTools<double>::GetAbsMax( pGrid1 );
   mVerticalMin   = 0.0;
   mVerticalMax   = NumberGridTools<double>::GetAbsMax( pGrid2 );

   BuildConditionalHistogram( pGrid1, pGrid2, useAbsoluteValues );

   VisualizeAsImage(std::string("MyConditionalHistogram.pgm"));
}

//----------------------------------------------------------------

ConditionalHistogram::~ConditionalHistogram()
{
   for (int i = 0; i < mNrBands; i++)
   {
      delete mvpData[i];
   }
}

//----------------------------------------------------------------

bool ConditionalHistogram::Write( std::string fileName )
{
   if (mNrBands > 0)
   {
      ofstream ofp;
      ofp.open(const_cast<char*>(fileName.c_str()), ios::out);

      if (!ofp)
      {
         cerr << "Can't open file: " << fileName << endl;
         return false;
      }
      int width = mvpData[0]->GetWidth();
      int height = mvpData[0]->GetHeight();
      for (int bandID = 0; bandID < mNrBands; bandID++)
      {
         ofp << endl << endl << "Writing band " << bandID << endl << flush;
         ofp << "========================" << endl << flush;
         for (int y = 0; y < height; y++)
         {
            for (int x = 0; x < width; x++)
            {
               ofp << mvpData[bandID]->GetValue(x, y) << "\t" << flush;
            }
            ofp << endl << flush;
         }
      }
      ofp.close();
   }
   return true;
}

//----------------------------------------------------------------

void ConditionalHistogram::BuildConditionalHistogram( image::ArrayGrid<double>* pGrid1, image::ArrayGrid<double>* pGrid2, bool absoluteValue )
{
   assert( pGrid1->GetWidth()  == pGrid2->GetWidth() );
   assert( pGrid1->GetHeight() == pGrid2->GetHeight() );
   bool needInitialisation = true;
   int initialIntValue = 0;
   ArrayGrid<int>* pHistogramGrid = new ArrayGrid<int>( (int)(mHorizontalMax+1), (int)(mVerticalMax+1), needInitialisation, initialIntValue );
   mvpData.push_back( pHistogramGrid );

   int width = pGrid1->GetWidth();
   int height = pGrid1->GetHeight();

   if (absoluteValue)
   {
      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x++)
         {
            AddOne( pHistogramGrid, (int)( fabs( pGrid1->GetValue(x, y) ) ),
                                    (int)( fabs( pGrid2->GetValue(x, y) ) ) );
         }
      }
   }
   else
   {
      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x++)
         {
            AddOne( pHistogramGrid, (int)( pGrid1->GetValue(x, y) - mHorizontalMin ),
                                    (int)( pGrid2->GetValue(x, y) - mVerticalMin ) );
         }
      }
   }
}

//----------------------------------------------------------------

void ConditionalHistogram::AddOne( ArrayGrid<int>* pGrid, int x, int y)
{
   assert( x >= 0);
   assert( x < pGrid->GetWidth());
   assert( y >= 0);
   assert( y < pGrid->GetHeight());

   pGrid->AddOne( x, y );
}

//----------------------------------------------------------------

int ConditionalHistogram::GetValue(int band, int x, int y)
{
   assert(band < (int)(mvpData.size()) );
   assert( x >= 0);
   assert( x < mvpData[band]->GetWidth());
   assert( y >= 0);
   assert( y < mvpData[band]->GetHeight());

   return mvpData[band]->GetValue(x, y );
}

//----------------------------------------------------------------

int ConditionalHistogram::GetNrOfHorizontalBins()
{
   return mvpData[0]->GetWidth();
}

//----------------------------------------------------------------

int ConditionalHistogram::GetNrOfVerticalBins()
{
   return mvpData[0]->GetHeight();
}

//----------------------------------------------------------------

void ConditionalHistogram::VisualizeAsImage(std::string imageName)
{
   if (mvpData.size() == 1)
   {
      ArrayGrid<int>* pOutGrid = mvpData[0]->Clone();
      NumberGridTools<int>::RescaleGrid(pOutGrid, 0, 255 );
      ImageIO::WritePGM( pOutGrid, imageName );
      delete pOutGrid;
   }

   if (mvpData.size() == 3)
   {
      Image* pImageOut = new Image( mvpData[0]->GetWidth(), mvpData[0]->GetHeight() );
      for (int i = 0; i < 3; i++)
      {
         ArrayGrid<double>* pOutGrid = NumberGridTools<int>::CreateDoubleGrid( mvpData[i] );
         NumberGridTools<double>::RescaleGrid( pOutGrid, 0.0, 255.0 );
         pImageOut->AddBand( pOutGrid );
      }
      ImageIO::Write( pImageOut, imageName );
      delete pImageOut;
   }
}

//----------------------------------------------------------------

}
}
