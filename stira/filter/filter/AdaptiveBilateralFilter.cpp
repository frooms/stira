
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

#include "AdaptiveBilateralFilter.h"
#include "LaplacianOfGaussianFilter.h"
#include "../../image/tools/ImageTools.h"
#include "../../image/datastructures/Image.h"

namespace stira{
namespace filter{

using namespace image;
   
const int AdaptiveBilateralFilter::mWindowSize = 7;

//--------------------------------------------------------------------------

AdaptiveBilateralFilter::AdaptiveBilateralFilter()
{
}

//--------------------------------------------------------------------------

AdaptiveBilateralFilter::~AdaptiveBilateralFilter()
{
}

//--------------------------------------------------------------------------

double AdaptiveBilateralFilter::LoGClassToZeta(double logClass)
{
   if (logClass < -60.0) {logClass = -60.0;}
   if (logClass >  60.0) {logClass =  60.0;}
   return (logClass / 2.0);
}

//--------------------------------------------------------------------------

double AdaptiveBilateralFilter::LoGClassToSigmaR(double logClass)
{
   double x = fabs(logClass);
   double sigmaR;   // no three return's in order to be able to check final result in single cout if necessary
   
   if (x <= 15.0)
   {
      sigmaR = (0.6667 * x + 7.0); 
   }
   else if (x <= 30.0)
   {
      sigmaR = (-0.8 * x + 29.0);
   }
   else
   {
      sigmaR = 5.0;
   }
   
   return sigmaR;
}

//--------------------------------------------------------------------------

Image* AdaptiveBilateralFilter::Run(Image* pImage)
{
   int halfSize = (int)(floor(mWindowSize / 2));
   int borderSize = 2 * halfSize;
   Image*   pFilteredImage =  ImageTools::MirrorBorder( pImage, borderSize, borderSize );
   Image* pInputCloneImage =  ImageTools::MirrorBorder( pImage, borderSize, borderSize );

   int width   = pFilteredImage->GetWidth();
   int height  = pFilteredImage->GetHeight();
   int nrBands = pFilteredImage->GetNumberOfBands();
   
   double sigmaD =  4.0;    // 2.0 is default value
   double sigmaR = 20.0;    // 20.0 default value; this value is adjusted adaptively in the loop
   
   Image* pLogImage = LaplacianOfGaussianFilter::Run( pFilteredImage, 3.5);
   
   for (int bandNr = 0; bandNr < nrBands; bandNr++)
   {
      ArrayGrid<double>* pInputGrid    = pInputCloneImage->GetBands()[bandNr];
      ArrayGrid<double>* pFilteredGrid =   pFilteredImage->GetBands()[bandNr];
      ArrayGrid<double>* pLogGrid      =        pLogImage->GetBands()[bandNr];
      
      for (int y0 = halfSize; y0 < height-halfSize; y0++)
      {
         for (int x0 = halfSize; x0 < width-halfSize; x0++)
         {
            double I0 = pInputGrid->GetValue(x0, y0);
            double R0 = 0.0;
            double tmpValue = 0.0;
                  
            double zetaLocal = LoGClassToZeta( pLogGrid->GetValue( x0, y0 ) );
            sigmaR =  LoGClassToSigmaR( pLogGrid->GetValue( x0, y0 ));
            
            for (int dy = -halfSize; dy <= halfSize; dy++)
            {
               for (int dx = -halfSize; dx <= halfSize; dx++)
               {
                  double I1 = pInputGrid->GetValue((x0 + dx), (y0 + dy));
                  double dI = I0 - I1 -  zetaLocal;
                  
                  double E1 = exp( -(((dx*dx) + (dy*dy)) / (2.0 * sigmaD * sigmaD )));
                  double E2 = exp( -((dI*dI) / (2.0 * sigmaR * sigmaR )));
                  
                  tmpValue += (E1 * E2 * pInputGrid->GetValue((x0 + dx), (y0 + dy)));
                  R0 += (E1 * E2);
               }
            }
            pFilteredGrid->SetValue(x0, y0, (tmpValue / R0));
         }
      }
   }
   delete pLogImage;
   delete pInputCloneImage;
   Image* pOutImage = ImageTools::CropBorder( pFilteredImage, borderSize, borderSize );
   std::string outName = pImage->GetImageName() + std::string("-AdaptiveBilateral");
   pOutImage->SetImageName(outName);
   delete pFilteredImage;
   return pOutImage;
}

//--------------------------------------------------------------------------

}
}
