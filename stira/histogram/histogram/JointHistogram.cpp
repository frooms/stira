
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
#include "JointHistogram.h"
#include "../../image/tools/ImageIO.h"
#include "../../image/tools/NumberGridTools.h"

using namespace std;

namespace stira {
namespace histogram {

using namespace image;

JointHistogram::JointHistogram( double horizontalBinSize, double verticalBinSize, double horizontalMin, double horizontalMax, double verticalMin, double verticalMax, int nrBands )
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

JointHistogram::JointHistogram( Image* pImage1, Image* pImage2, bool useAbsoluteValues )
{
   assert( pImage1->GetWidth() == pImage2->GetWidth() );
   assert( pImage1->GetHeight() == pImage2->GetHeight() );
   assert( pImage1->GetNumberOfBands() == pImage2->GetNumberOfBands() );
   mNrBands = pImage1->GetNumberOfBands();

   mRoiTopX1 = 0;
   mRoiTopY1 = 0;
   mRoiTopX2 = 0;
   mRoiTopY2 = 0;
   mRoiBottomX1 = pImage1->GetWidth()-1;
   mRoiBottomY1 = pImage1->GetHeight()-1;
   mRoiBottomX2 = pImage1->GetWidth()-1;
   mRoiBottomY2 = pImage1->GetHeight()-1;

   if (useAbsoluteValues)
   {
       mHorizontalMin = 0.0;
       mHorizontalMax = pImage1->GetAbsMax( );
       mVerticalMin = 0.0;
       mVerticalMax = pImage2->GetAbsMax( );
   }
   else
   {
       pImage1->GetMinMax( mHorizontalMin, mHorizontalMax );
       pImage2->GetMinMax( mVerticalMin,   mVerticalMax   );
   }

   for (int bandNr = 0; bandNr < mNrBands; bandNr++ )
   {
      BuildJointHistogram( pImage1->GetBands()[bandNr], pImage2->GetBands()[bandNr], useAbsoluteValues );
   }
}

//----------------------------------------------------------------

JointHistogram::JointHistogram( image::ArrayGrid<double>* pGrid1, int xTop1, int yTop1, int xBottom1, int yBottom1,
                                image::ArrayGrid<double>* pGrid2, int xTop2, int yTop2, int xBottom2, int yBottom2,
                                bool useAbsoluteValues )
{
    mRoiTopX1 = xTop1;
    mRoiTopY1 = yTop1;
    mRoiTopX2 = xTop2;
    mRoiTopY2 = yTop2;
    mRoiBottomX1 = xBottom1;
    mRoiBottomY1 = yBottom1;
    mRoiBottomX2 = xBottom2;
    mRoiBottomY2 = yBottom2;

    assert( pGrid1->GetWidth()  == pGrid2->GetWidth() );
    assert( pGrid1->GetHeight() == pGrid2->GetHeight() );

    if (useAbsoluteValues)
    {
        mHorizontalMin = 0.0;
        mHorizontalMax = NumberGridTools<double>::GetAbsMax( pGrid1 );
        mVerticalMin   = 0.0;
        mVerticalMax   = NumberGridTools<double>::GetAbsMax( pGrid2 );
    }
    else
    {
        NumberGridTools<double>::GetMinMax( pGrid1, mHorizontalMin, mHorizontalMax );
        NumberGridTools<double>::GetMinMax( pGrid2, mVerticalMin,   mVerticalMax   );
    }

    BuildJointHistogram( pGrid1, pGrid2, useAbsoluteValues );

    VisualizeAsImage(std::string("MyConditionalHistogram.pgm"));
}

//----------------------------------------------------------------

JointHistogram::JointHistogram( image::ArrayGrid<double>* pGrid1, image::ArrayGrid<double>* pGrid2, bool useAbsoluteValues )
{
   assert( pGrid1->GetWidth()  == pGrid2->GetWidth() );
   assert( pGrid1->GetHeight() == pGrid2->GetHeight() );

   mRoiTopX1 = 0;
   mRoiTopY1 = 0;
   mRoiTopX2 = 0;
   mRoiTopY2 = 0;
   mRoiBottomX1 = pGrid1->GetWidth()-1;
   mRoiBottomY1 = pGrid1->GetHeight()-1;
   mRoiBottomX2 = pGrid1->GetWidth()-1;
   mRoiBottomY2 = pGrid1->GetHeight()-1;

   if (useAbsoluteValues)
   {
       mHorizontalMin = 0.0;
       mHorizontalMax = NumberGridTools<double>::GetAbsMax( pGrid1 );
       mVerticalMin   = 0.0;
       mVerticalMax   = NumberGridTools<double>::GetAbsMax( pGrid2 );
   }
   else
   {
       NumberGridTools<double>::GetMinMax( pGrid1, mHorizontalMin, mHorizontalMax );
       NumberGridTools<double>::GetMinMax( pGrid2, mVerticalMin,   mVerticalMax   );
   }

   BuildJointHistogram( pGrid1, pGrid2, useAbsoluteValues );

   VisualizeAsImage(std::string("MyConditionalHistogram.pgm"));
}

//----------------------------------------------------------------

JointHistogram::~JointHistogram()
{
   for (int i = 0; i < mNrBands; i++)
   {
      delete mvpData[i];
      delete mvpDataNormalized[i];
   }
}

//----------------------------------------------------------------

bool JointHistogram::Write( std::string fileName )
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

void JointHistogram::BuildJointHistogram( image::ArrayGrid<double>* pGrid1, image::ArrayGrid<double>* pGrid2, bool absoluteValue )
{
   int roiWidth  = mRoiBottomX1 - mRoiTopX1;      assert( ( mRoiBottomX2 - mRoiTopX2 ) == roiWidth );
   int roiHeight = mRoiBottomY1 - mRoiTopY1;      assert( ( mRoiBottomY2 - mRoiTopY2 ) == roiHeight );

   bool needInitialisation = true;
   int initialIntValue = 0;
   ArrayGrid<int>* pHistogramGrid = new ArrayGrid<int>( (int)(mHorizontalMax+1), (int)(mVerticalMax+1), needInitialisation, initialIntValue );

   ArrayGrid<double>* pNormalizedGrid = new ArrayGrid<double>( (int)(mHorizontalMax+1), (int)(mVerticalMax+1), needInitialisation, initialIntValue );
   if (absoluteValue)
   {
      for (int dy = 0; dy < roiHeight; dy++)
      {
         for (int dx = 0; dx < roiWidth; dx++)
         {
            AddOne( pHistogramGrid, (int)( fabs( pGrid1->GetValue( mRoiTopX1 + dx, mRoiTopY1 + dy ) ) ),
                                    (int)( fabs( pGrid2->GetValue( mRoiTopX2 + dx, mRoiTopY2 + dy ) ) ) );
         }
      }
      for (int y = 0; y < pHistogramGrid->GetHeight(); y++)
      {
         for (int x = 0; x < pHistogramGrid->GetWidth(); x++)
         {
            // each pixel in the roi increases the value of a certain bin by one, so sum over the histogram is nr of pixels
            double tmpValue = (double)(pHistogramGrid->GetValue( x, y )) / (double)( roiWidth * roiHeight );
            pNormalizedGrid->SetValue( x, y, tmpValue );
         }
      }
   }
   else
   {
      for (int dy = 0; dy < roiHeight; dy++)
      {
         for (int dx = 0; dx < roiWidth; dx++)
         {
            AddOne( pHistogramGrid, (int)( pGrid1->GetValue( mRoiTopX1 + dx, mRoiTopY1 + dy ) - mHorizontalMin ),
                                    (int)( pGrid2->GetValue( mRoiTopX2 + dx, mRoiTopY2 + dy ) - mVerticalMin ) );

            //std::cout << "Grid value = " << (int)( pGrid1->GetValue( mRoiTopX1 + dx, mRoiTopY1 + dy ) - mHorizontalMin ) << " vs " << (int)( pGrid2->GetValue( mRoiTopX2 + dx, mRoiTopY2 + dy ) - mVerticalMin ) << std:: endl;
         }
      }
      for (int y = 0; y < pHistogramGrid->GetHeight(); y++)
      {
         for (int x = 0; x < pHistogramGrid->GetWidth(); x++)
         {
            // each pixel in the roi increases the value of a certain bin by one, so sum over the histogram is nr of pixels
            double tmpValue = (double)(pHistogramGrid->GetValue( x, y )) / (double)( roiWidth * roiHeight );
            pNormalizedGrid->SetValue( x, y, tmpValue );
         }
      }
   }
   mvpData.push_back( pHistogramGrid );
   mvpDataNormalized.push_back( pNormalizedGrid );

}

//----------------------------------------------------------------

void JointHistogram::AddOne( ArrayGrid<int>* pGrid, int x, int y)
{
   assert( x >= 0);
   assert( x < pGrid->GetWidth());
   assert( y >= 0);
   assert( y < pGrid->GetHeight());

   pGrid->AddOne( x, y );
}

//----------------------------------------------------------------

int JointHistogram::GetValue(int band, int x, int y)
{
   assert(band < (int)(mvpData.size()) );
   assert( x >= 0);
   assert( x < mvpData[band]->GetWidth());
   assert( y >= 0);
   assert( y < mvpData[band]->GetHeight());

   return mvpData[band]->GetValue(x, y );
}

//----------------------------------------------------------------

int JointHistogram::GetNrOfHorizontalBins()
{
   return mvpData[0]->GetWidth();
}

//----------------------------------------------------------------

int JointHistogram::GetNrOfVerticalBins()
{
   return mvpData[0]->GetHeight();
}

//----------------------------------------------------------------

int JointHistogram::GetBinValue( int bandNr, int binX, int binY )
{
    return mvpData[bandNr]->GetValue( binX, binY );
}

//----------------------------------------------------------------

double JointHistogram::GetNormalizedBinValue( int bandNr, int binX, int binY )
{
    return mvpDataNormalized[bandNr]->GetValue( binX, binY );
}

//----------------------------------------------------------------

FloatHistogram* JointHistogram::GetMarginalPDF1()
{
   int nrBands = mvpDataNormalized.size();
   FloatHistogram* pFH = new FloatHistogram( mHorizontalMax+1, nrBands );

   for (int bandNr = 0; bandNr < mvpDataNormalized.size(); bandNr++ )
   {
      for (int x = 0; x < mvpDataNormalized[0]->GetWidth(); x++)
      {
         float tmpValue = 0;
         for (int y = 0; y < mvpDataNormalized[0]->GetHeight(); y++)
         {
            tmpValue += mvpDataNormalized[bandNr]->GetValue( x, y );
         }
         pFH->SetBinValue( bandNr, x, tmpValue );
      }
   }

   return pFH;
}

//----------------------------------------------------------------

FloatHistogram* JointHistogram::GetMarginalPDF2()
{
   int nrBands = mvpDataNormalized.size();
   FloatHistogram* pFH = new FloatHistogram( mVerticalMax+1, nrBands );

   for (int bandNr = 0; bandNr < mvpDataNormalized.size(); bandNr++ )
   {
      for (int y = 0; y < mvpDataNormalized[0]->GetHeight(); y++)
      {
         float tmpValue = 0;
         for (int x = 0; x < mvpDataNormalized[0]->GetWidth(); x++)
         {
            tmpValue += mvpDataNormalized[bandNr]->GetValue( x, y );
         }
         pFH->SetBinValue( bandNr, y, tmpValue );
      }
   }
   return pFH;
}

//----------------------------------------------------------------

void JointHistogram::VisualizeAsImage(std::string imageName)
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

void JointHistogram::ExportText(std::string fileName)
{
   ofstream ofp;

   int width  = mvpData[0]->GetWidth();
   int height = mvpData[0]->GetHeight();

   ofp.open(const_cast<char*>(fileName.c_str()), ios::out);

   for ( int y = 0; y < height; y++)
   {
       for (int x = 0; x < width; x++)
       {
           ofp << "\t" <<mvpData[0]->GetValue(x, y);
       }
       ofp << "\n";
   }
   ofp.close();
}


//----------------------------------------------------------------

}
}
