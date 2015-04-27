
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

#include "LaplacianOfGaussianFilter.h"
#include "../../image/tools/ImageTools.h"

namespace stira{
namespace filter{

using namespace image;

LaplacianOfGaussianFilter::LaplacianOfGaussianFilter()
{
}

//--------------------------------------------------------------------------

LaplacianOfGaussianFilter::~LaplacianOfGaussianFilter()
{
}

//--------------------------------------------------------------------------

double LaplacianOfGaussianFilter::GetC(int x, int y, double sigma, int halfSize)
{
   double tmpValue = 0.0;
   double sigmaSquared = sigma * sigma;
   double sigmaToTheFourth = sigmaSquared * sigmaSquared;
   
   double size = (double)((2.0 * halfSize + 1.0) * (2.0 * halfSize + 1.0)); 
   
   for (int n = y - halfSize; n <= y + halfSize; n++)
   {
      for (int m = x - halfSize; m <= x + halfSize; m++)
      {
         int mSquared = m * m;
         int nSquared = n * n;
         double r = ((double)(mSquared + nSquared) / (2.0 * sigmaSquared));
         tmpValue += ( (1.0 - r) * exp(-r) ) / (-M_PI * sigmaToTheFourth);
      }
   }
   return (tmpValue / size);
}

//--------------------------------------------------------------------------

double* LaplacianOfGaussianFilter::GenerateLoGKernel(int halfSize, double sigma)
{
   int kernelSize = 2 * halfSize + 1;
   double* pKernel = new double[kernelSize * kernelSize];
   
   double sigmaSquared = sigma * sigma;
   double sigmaToTheFourth = sigmaSquared * sigmaSquared;
   for (int y = 0; y < kernelSize; y++)
   {
      for (int x = 0; x < kernelSize; x++)
      {
         int xx = x - halfSize;
         int yy = y - halfSize;
         double C = GetC(xx, yy, sigma, halfSize);
         int xSquared = xx * xx;
         int ySquared = yy * yy;
         double r = ((double)(xSquared + ySquared) / (2.0 * sigmaSquared));
         pKernel[x + y * kernelSize] = ( (1.0 - r) * exp(-r) ) / (-M_PI * sigmaToTheFourth) - C;
      }
   }
   return pKernel;
}

//--------------------------------------------------------------------------

image::Image* LaplacianOfGaussianFilter::Run(image::Image* pImage, double scaleFactor)
{
   int halfSize = 4;
   double sigma = 1.5;
   int kernelSize = 2 * halfSize + 1;
   
   Image* pOutImage = ImageTools::MirrorBorder( pImage, halfSize, halfSize );
   
   int width  = pOutImage->GetWidth();
   int height = pOutImage->GetHeight();
   int nrBands = pOutImage->GetNumberOfBands();
   
   double* pKernel = GenerateLoGKernel( halfSize, sigma);
   for (int bandNr = 0; bandNr < nrBands; bandNr++)
   {
      ArrayGrid<double>* pGrid = pOutImage->GetBands()[bandNr];
      
      for (int y = halfSize; y < (height - halfSize); y++)
      {
         for (int x = halfSize; x < (width - halfSize); x++)
         {
            double tmpValue = 0.0;
            
            for (int dy = -halfSize; dy <= halfSize; dy++)
            {
               for (int dx = -halfSize; dx <= halfSize; dx++)
               {
                  tmpValue += pGrid->GetValue(x+dx, y+dy) * pKernel[(dx+halfSize) + kernelSize * (dy+halfSize)];
               }
            }
            pOutImage->GetBands()[bandNr]->SetValue(x, y, scaleFactor * tmpValue);
         }
      }
   }
   
   delete []pKernel;
   Image* pOutCropImage = ImageTools::CropBorder( pOutImage, halfSize, halfSize );
   delete pOutImage;
   std::string outName = pImage->GetImageName() + std::string("-LaplacianOfGaussian");
   pOutCropImage->SetImageName(outName);
   return pOutCropImage;
}

//--------------------------------------------------------------------------

}
}
