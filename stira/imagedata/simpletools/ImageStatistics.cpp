#include "ImageStatistics.h"
#include "GridStatistics.h"
#include <iostream>

namespace stira {
namespace image {

ImageStatistics::ImageStatistics()
{

}

// 3. IMAGE RESCALE
///////////////////

void ImageStatistics::Rescale( Image* pImage, double newMin, double newMax )
{
   if (pImage->GetNumberOfBands() > 0)
   {
      double mmin, mmax;
      GetMinMax( pImage, mmin, mmax );
      int height = pImage->GetHeight();
      int width = pImage->GetWidth();

      for (int bandNr = 0; bandNr < pImage->GetNumberOfBands(); bandNr ++)
      {
         ArrayGrid<double>* pGrid = pImage->GetBands()[bandNr];

         double gridMin, gridMax;
         GridStatistics<double>::GetMinMax( pGrid, gridMin, gridMax );
         if (pGrid != 0)
         {
            if ((mmax - mmin) < 0.0001)
            {
               for (int y = 0; y < height; y++)
               {
                  for (int x = 0; x < width; x++)
                  {
                     pGrid->SetValue(x, y, mmax);
                  }
               }
            }
            else
            {
               for (int y = 0; y < height; y++)
               {
                  for (int x = 0; x < width; x++)
                  {
                     pGrid->SetValue(x, y, ( ((pGrid->GetValue(x, y) - mmin) / (mmax - mmin) ) * (newMax - newMin)) + newMin );
                  }
               }
            }
         }
         else
         {
            std::cerr << "Image band << " << bandNr << " is NULL!!!" << std::endl << std::flush;
            return;
         }
      }
   }
   else
   {
      std::cerr << "Image::GetMinMax::ERROR: Image contains no valid bands!!!" << std::endl << std::flush;
      return;
   }
}

//===================================================================================================

void ImageStatistics::GetMinMax( Image* pImage, double& mmin, double& mmax, int& minBandNr, int& maxBandNr)
{
   double tmpMin, tmpMax;
   mmin =  100000000000000000000000000.0;
   mmax = -100000000000000000000000000.0;

   if ( pImage->GetNumberOfBands() > 0)
   {
      for (int bandNr = 0; bandNr < pImage->GetNumberOfBands(); bandNr ++)
      {
         ArrayGrid<double>* pGrid = pImage->GetBands()[bandNr];
         if (pGrid != 0)
         {
            GridStatistics<double>::GetMinMax( pGrid, tmpMin, tmpMax );
            if (tmpMin < mmin) {mmin = tmpMin; minBandNr = bandNr;}
            if (tmpMax > mmax) {mmax = tmpMax; maxBandNr = bandNr;}
         }
         else
         {
            std::cerr << "Image::GetMinMax::ERROR: Image band " << bandNr << " is 0!!!" << std::endl << std::flush;
         }
      }
   }
   else
   {
      std::cerr << "Image::GetMinMax::ERROR: Image contains no valid bands!!!" << std::endl << std::flush;
   }
}

//===================================================================================================

void ImageStatistics::GetMinMax( Image* pImage, double& mmin, double& mmax )
{
   int i, j;
   ImageStatistics::GetMinMax( pImage, mmin, mmax, i, j );
}

//===================================================================================================

double ImageStatistics::GetAbsMax( Image* pImage )
{
   double tmpMax;
   double mmax = 0.0;

   if (pImage->GetNumberOfBands() > 0)
   {
      for (int bandNr = 0; bandNr < pImage->GetNumberOfBands(); bandNr ++)
      {
         ArrayGrid<double>* pGrid = pImage->GetBands()[bandNr];
         if (pGrid != 0)
         {
            tmpMax = GridStatistics<double>::GetAbsMax( pGrid );
            if (tmpMax > mmax) {mmax = tmpMax;}
         }
         else
         {
            std::cerr << "Image::GetMinMax::ERROR: Image band " << bandNr << " is 0!!!" << std::endl << std::flush;
         }
      }
   }
   else
   {
      std::cerr << "Image::GetMinMax::ERROR: Image contains no valid bands!!!" << std::endl << std::flush;
   }
   return mmax;
}

}
}
