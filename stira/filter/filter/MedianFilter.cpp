

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

#include "MedianFilter.h"
#include "../../common/common/MathUtils.h"
#include "../../imagetools/tools/ImageTools.h"

namespace stira{
namespace filter{

using namespace common;
using namespace std;
using namespace imagedata;
using namespace imagetools;

// NOTE: according to http://theory.stanford.edu/~amitp/rants/c++-vs-c/
//  sorting with sort() from STL is many times quicker than qsort; however, does
//  the usage of an STL container not ruin this speedup??? Or can sort() also work
//  on normal arrays?

MedianFilter::MedianFilter() {}

//-------------------------------------------------------------------

MedianFilter::~MedianFilter() {}

//-------------------------------------------------------------------

ArrayGrid<int>* MedianFilter::RunMedian( ArrayGrid<int>* pGridIn, int mySize)
{
   int windowWidth = 2 * mySize + 1;
   int windowArea  = windowWidth * windowWidth;
   int medianPosition = (int)(windowArea / 2);

   int width  = pGridIn->GetWidth();
   int height = pGridIn->GetHeight();

   int *pR = new int [windowArea];

   ArrayGrid<int>* pGridOut = pGridIn->Clone();

   for (int y = mySize; y < height - mySize; y++)
   {
      for (int x = mySize; x < width - mySize; x ++)
      {
         int myIndex=0;
         for (int s = -mySize; s <= mySize; s++)
         {
            for (int t = -mySize; t <= mySize; t++)
            {
               pR[myIndex] = pGridIn->GetValue( x+s, y+t );
               myIndex++;
            }
         }
         qsort( pR, windowArea, sizeof(int), MathUtils::CompareIntegers );
         pGridOut->SetValue( x, y, pR[ medianPosition ] );
      }
   }

   delete [] pR;
   return pGridOut;
}

//-------------------------------------------------------------------

ArrayGrid<double>* MedianFilter::RunMedian( ArrayGrid<double>* pGridIn, int size)
{
   int windowWidth = 2 * size + 1;
   int windowArea  = windowWidth * windowWidth;
   int medianPosition = (int)(windowArea / 2);

   int width = pGridIn->GetWidth();
   int height = pGridIn->GetHeight();

   double* pR = new double[windowArea];

   ArrayGrid<double>* pGridOut = pGridIn->Clone();
   //cout << "Input grid has width " << pGridIn->GetWidth() << " and height " << pGridIn->GetHeight() << endl;

   for (int y = size; y < height-size; y++)
   {
      for (int x = size; x < width - size; x ++)
      {
         int index=0;
         for (int s = -size; s <= size; s++)
         {
            for (int t = -size; t <= size; t++)
            {
               pR[index] = pGridIn->GetValue( x+s, y+t );
               index++;
            }
         }
         qsort( pR, windowArea, sizeof(double), MathUtils::CompareDoubles );
         pGridOut->SetValue( x, y, pR[medianPosition] );
      }
   }

   delete [] pR;
   cout << "Output grid has width " << pGridOut->GetWidth() << " and height " << pGridOut-> GetHeight() << endl;
   return pGridOut;
}

//-------------------------------------------------------------------

Image* MedianFilter::RunMedian( Image* pImageIn, int size)
{
   Image* pImageInExtended = ImageTools::MirrorBorder( pImageIn, size, size );

   // create an empty image without data bands
   Image* pImageOutExtended = new Image( pImageInExtended->GetWidth(), pImageInExtended->GetHeight() );

   int nrBands = pImageInExtended->GetNumberOfBands();
   for (int bandNr = 0; bandNr < nrBands; bandNr++)
   {
      ArrayGrid<double>* pGridOut = RunMedian( pImageInExtended->GetBands()[bandNr], size);
      pImageOutExtended->AddBand( pGridOut );
   }

   Image* pImageOut = ImageTools::CropBorder( pImageOutExtended, size, size );
   delete pImageInExtended;
   delete pImageOutExtended;
   std::string outName = pImageIn->GetImageName() + std::string("-Median");
   pImageOut->SetImageName(outName);
   return pImageOut;
}

//-------------------------------------------------------------------

// for size = 2, kernelSize = 9
// "X" shaped filter mask X; Plus shaped filter mask P and central pixel
//
// X    *    P    *    X
// *    X    P    X    *
// P    P   PCX   P    P
// *    X    P    X    *
// X    *    P    *    X

ArrayGrid<double>* MedianFilter::RunHybridMedian( ArrayGrid<double>* pGridIn, int size)
{
   int kernelSize = 4 * size + 1;
   int medianPosition = (int)(kernelSize / 2);

   int width = pGridIn->GetWidth();
   int height = pGridIn->GetHeight();

   double *pPlusShaped = new double [kernelSize];
   double *pXShaped = new double [kernelSize];
   double medianOfMedians[3], centralPixelValue;

   ArrayGrid<double>* pGridOut = pGridIn->Clone();

   for (int y = size; y < height - size; y++)
   {
      for (int x = size; x < width - size; x ++)
      {
         centralPixelValue = pGridIn->GetValue( x, y );
         int index = 0;
         for (int s = -size; s <= size; s++)
         {
            if (s != 0)
            {
               pPlusShaped[index] = pGridIn->GetValue( x + s, y );
               index++;
            }
         }
         for (int s = -size; s <= size; s++)
         {
            if (s != 0)
            {
               pPlusShaped[ index ] = pGridIn->GetValue( x, y + s );
               index++;
            }
         }
         pPlusShaped[ index ] = centralPixelValue ;

         index = 0;
         for (int s = -size; s <= size; s++)
         {
            if (s != 0)
            {
               pXShaped[ index ] = pGridIn->GetValue( x + s, y + s );
               index++;
            }
         }
         for (int s = -size; s <= size; s++)
         {
            if (s != 0)
            {
               pXShaped[ index ] = pGridIn->GetValue( x + s, y - s );
               index ++;
            }
         }
         pXShaped[ index ] = centralPixelValue;

         qsort( pPlusShaped, kernelSize, sizeof(double), MathUtils::CompareDoubles );
         qsort( pXShaped,    kernelSize, sizeof(double), MathUtils::CompareDoubles );

         medianOfMedians[ 0 ] = pPlusShaped[ medianPosition ];
         medianOfMedians[ 1 ] = pXShaped[ medianPosition ];
         medianOfMedians[ 2 ] = centralPixelValue;

         qsort( medianOfMedians, 3, sizeof(double), MathUtils::CompareDoubles );

         pGridOut->SetValue( x, y, medianOfMedians[1] );
      }
   }
   delete []pPlusShaped;
   delete []pXShaped;
   return pGridOut;
}

//-------------------------------------------------------------------

// for size = 2, kernelSize = 9
// "X" shaped filter mask X; Plus shaped filter mask P and central pixel
//
// X    *    P    *    X
// *    X    P    X    *
// P    P   PCX   P    P
// *    X    P    X    *
// X    *    P    *    X

Image* MedianFilter::RunHybridMedian( Image* pImageIn, int size)
{
   Image* pImageInExtended = ImageTools::MirrorBorder( pImageIn, size, size );

   int nrBands = pImageInExtended->GetNumberOfBands();

   Image* pImageOutExtended = new Image( pImageInExtended->GetWidth(), pImageInExtended->GetHeight() );

   for (int bandNr = 0; bandNr < nrBands; bandNr++)
   {
      ArrayGrid<double>* pGridOut = RunHybridMedian( pImageInExtended->GetBands()[ bandNr ], size );
      pImageOutExtended->AddBand( pGridOut );
   }

   Image* pImageOut = ImageTools::CropBorder( pImageOutExtended, size, size );
   delete pImageInExtended;
   delete pImageOutExtended;
   std::string outName = pImageIn->GetImageName() + std::string("-HybridMedian");
   pImageOut->SetImageName(outName);
   return pImageOut;
}

//-------------------------------------------------------------------

}
}

