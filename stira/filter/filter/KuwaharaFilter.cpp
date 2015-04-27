
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

#include "KuwaharaFilter.h"
#include "../../image/tools/NumberGridTools.h"
#include "../../image/tools/ImageTools.h"

namespace stira{
namespace filter{

using namespace image;

KuwaharaFilter::KuwaharaFilter()
{
}

//--------------------------------------------------------------------------

KuwaharaFilter::~KuwaharaFilter()
{
}

//--------------------------------------------------------------------------

int KuwaharaFilter::GetSmallestIndex(double* pArray, int size )
{
   double tmpValue = 100000000000000000000000000000000000000000000.0;
   int smallestIndex = 0;
   for (int i = 0; i < size; i++)
   {
      if (pArray[i] < tmpValue)
      {
         tmpValue = pArray[i];
         smallestIndex = i;
      }
   }
   return smallestIndex;
}

//--------------------------------------------------------------------------

image::Image* KuwaharaFilter::Run( image::Image* pImageIn, int windowSize )
{
   if (windowSize % 4 != 1) {windowSize = 5;}
   assert (windowSize % 4 == 1);
   assert (windowSize > 1 );
   assert (pImageIn != 0);

   int distance = windowSize / 4;
   int subwindowSize = (windowSize + 1) / 2;
   int subwindowHalfSize = subwindowSize / 2;

   Image* pExpandedImage = ImageTools::MirrorBorder( pImageIn, subwindowSize, subwindowSize );
   Image* pCloneImage = pExpandedImage->Clone();

   int widthExpanded  = pExpandedImage->GetWidth();
   int heightExpanded = pExpandedImage->GetHeight();
   int nrBands = pExpandedImage->GetNumberOfBands();

   for (int bandNr = 0; bandNr < nrBands; bandNr++)
   {
      ArrayGrid<double>* pInGrid  = pExpandedImage->GetBands()[bandNr];
      ArrayGrid<double>* pOutGrid = pCloneImage->GetBands()[bandNr];
      for (int y = subwindowSize; y < heightExpanded-subwindowSize; y++)
      {
         for (int x = subwindowSize; x < widthExpanded-subwindowSize; x++)
         {
            double mean[4];
            double variance[4];
            int x0 = x - distance;
            int y0 = y - distance;
            int x0TopLeft     = x0 - subwindowHalfSize;   int y0TopLeft     = y0 - subwindowHalfSize;
            int x0BottomRight = x0 + subwindowHalfSize;   int y0BottomRight = y0 + subwindowHalfSize;
            mean[0]     = NumberGridTools<double>::ComputeLocalMean(     pInGrid, x0TopLeft, y0TopLeft, x0BottomRight, y0BottomRight );
            variance[0] = NumberGridTools<double>::ComputeLocalVariance( pInGrid, x0TopLeft, y0TopLeft, x0BottomRight, y0BottomRight, mean[0] );

            int x1 = x + distance;
            int y1 = y - distance;
            int x1TopLeft     = x1 - subwindowHalfSize;   int y1TopLeft     = y1 - subwindowHalfSize;
            int x1BottomRight = x1 + subwindowHalfSize;   int y1BottomRight = y1 + subwindowHalfSize;
            mean[1]     = NumberGridTools<double>::ComputeLocalMean(     pInGrid, x1TopLeft, y1TopLeft, x1BottomRight, y1BottomRight );
            variance[1] = NumberGridTools<double>::ComputeLocalVariance( pInGrid, x1TopLeft, y1TopLeft, x1BottomRight, y1BottomRight, mean[1] );

            int x2 = x - distance;
            int y2 = y + distance;
            int x2TopLeft     = x2 - subwindowHalfSize;   int y2TopLeft     = y2 - subwindowHalfSize;
            int x2BottomRight = x2 + subwindowHalfSize;   int y2BottomRight = y2 + subwindowHalfSize;
            mean[2]     = NumberGridTools<double>::ComputeLocalMean(     pInGrid, x2TopLeft, y2TopLeft, x2BottomRight, y2BottomRight );
            variance[2] = NumberGridTools<double>::ComputeLocalVariance( pInGrid, x2TopLeft, y2TopLeft, x2BottomRight, y2BottomRight, mean[2] );

            int x3 = x + distance;
            int y3 = y + distance;
            int x3TopLeft     = x3 - subwindowHalfSize;   int y3TopLeft     = y3 - subwindowHalfSize;
            int x3BottomRight = x3 + subwindowHalfSize;   int y3BottomRight = y3 + subwindowHalfSize;
            mean[3]     = NumberGridTools<double>::ComputeLocalMean(     pInGrid, x3TopLeft, y3TopLeft, x3BottomRight, y3BottomRight );
            variance[3] = NumberGridTools<double>::ComputeLocalVariance( pInGrid, x3TopLeft, y3TopLeft, x3BottomRight, y3BottomRight, mean[3] );

            int smallestIndex = GetSmallestIndex( variance, 4 );

            pOutGrid->SetValue( x, y, mean[ smallestIndex ] );
         }
      }
   }
   delete pExpandedImage;
   Image* pOutImage = ImageTools::CropBorder( pCloneImage, subwindowSize, subwindowSize );
   std::string outName = pImageIn->GetImageName() + std::string("-Kuwahara");
   pOutImage->SetImageName(outName);
   delete pCloneImage;
   return pOutImage;
}

//--------------------------------------------------------------------------

}
}

