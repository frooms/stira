
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

#include "TransferFunctionGenerator.h"
#include "../../common/common/MathUtils.h"
#include "../../image/tools/NumberGridTools.h"

namespace stira {
namespace fouriertools {

using namespace image;
using namespace std;

TransferFunctionGenerator::TransferFunctionGenerator()
{
}

TransferFunctionGenerator::~TransferFunctionGenerator()
{
}

/////////////////////////////////////
//                                 //
// 2) GENERATE TRANSFER FUNCTIONS  //
//                                 //
/////////////////////////////////////

int TransferFunctionGenerator::GetScaleFactors(int width, int height, double& xFactor, double& yFactor)
{
   int isBiggest;
   if (width > height)
   {
      xFactor = 1.0;
      yFactor = ( (double)(width) / (double)(height) );
      isBiggest = 1;
   }
   else
   {
      xFactor = ( (double)(height) / (double)(width) );
      yFactor = 1.0;
      isBiggest = 2;
   }
   return isBiggest;
}

//======================================================================================================

void TransferFunctionGenerator::InitializeRatios(int inWidth, int inHeight, double& outXFactor, double& outYFactor, double& inoutX1, double& inoutX2)
{
   int isBiggest = GetScaleFactors( inWidth, inHeight, outXFactor, outYFactor);

   if (isBiggest == 2)
   {
      inoutX1 *= outXFactor;
      inoutX2 *= outXFactor;
   }
}

//======================================================================================================

double TransferFunctionGenerator::GetXn(double x, double width, double halfWidth, double xFactor)
{
   if (x < halfWidth)
   {
      return (x * xFactor);
   }
   else
   {
      return ( (x - width) * xFactor );
   }
}

//======================================================================================================

double TransferFunctionGenerator::GetYn(double y, double height, double halfHeight, double yFactor)
{
   if (y < halfHeight)
   {
      return ( y * yFactor );
   }
   else
   {
      return ( (y - height) * yFactor );
   }
}

//======================================================================================================

ArrayGrid<double>* TransferFunctionGenerator::GenerateHighPassTransferFunction(int width, int height, double x1, double x2)
{
   bool needInitialisation = true;
   double initialRealValue = 0.0;
   ArrayGrid<double>* pHighPassTransferFunction = new ArrayGrid<double>( width, height, needInitialisation, initialRealValue );

   double w2 = width / 2.0 ;
   double h2 = height / 2.0 ;

   double xFactor, yFactor;
   InitializeRatios( width, height, xFactor, yFactor, x1, x2);

   for (double y = 0; y < height; y++)
   {
      for (double x = 0; x < width; x++)
      {
         double xn = GetXn( x, width, w2, xFactor);
         double yn = GetYn( y, height, h2, yFactor);

         double radius = sqrt( xn * xn + yn * yn );
         double ttmp2;

         if (radius <= x1) { ttmp2 = 0.0; }
         else if (radius >= x2) { ttmp2 = 1.0; }
         else // if ((radius > x1) && (radius < x2))
         {
            double ttmp  = M_PI / 4.0 * (1.0 + (radius - x1) / (x2 - x1));
            ttmp2 = cos(M_PI / 2.0 * (log (ttmp * 2.0 / M_PI) / log(2.0)));
         }

         pHighPassTransferFunction->SetValue((int)(x), (int)(y), ttmp2);
      }
   }
   return pHighPassTransferFunction;
}

//======================================================================================================

ArrayGrid<double>* TransferFunctionGenerator::GenerateLowPassTransferFunction(int width, int height, double x1, double x2)
{
   bool needInitialisation = true;
   double initialRealValue = 0.0;
   ArrayGrid<double>* pLowPassTransferFunction = new ArrayGrid<double>( width, height, needInitialisation, initialRealValue );

   double xFactor, yFactor;
   InitializeRatios( width, height, xFactor, yFactor, x1, x2 );

   double w2 = width / 2.0 ;
   double h2 = height / 2.0 ;

   for (double y = 0; y < height; y++)
   {
      for (double x = 0; x < width; x++)
      {
         double xn = GetXn( x, width, w2, xFactor);
         double yn = GetYn( y, height, h2, yFactor);

         double radius = sqrt(xn * xn + yn * yn);

         if (radius < x1)
         {
            pLowPassTransferFunction->SetValue((int)(x), (int)(y), 1.0);
         }

         if (radius > x2)
         {
            pLowPassTransferFunction->SetValue((int)(x), (int)(y), 0.0);
         }

         if ((radius >= x1) && (radius <= x2))
         {
            double ttmp, ttmp2;
            ttmp = M_PI / 4.0 * (1.0 + (radius - x1) / (x2 - x1));
            ttmp2 = cos(M_PI / 2.0 * (log(ttmp * 4.0 / M_PI)/ log(2.0)));

            pLowPassTransferFunction->SetValue((int)(x), (int)(y), ttmp2);
         }
      }
   }
   return pLowPassTransferFunction;
}

//======================================================================================================

ArrayGrid<double>* TransferFunctionGenerator::GenerateAxisSuppressTransferFunction(int width, int height, int axisWidth, double x1, double x2)
{
   bool needInitialisation = true;
   double initialRealValue = 0.0;
   ArrayGrid<double>* pAxialTransferFunction = new ArrayGrid<double>( width, height, needInitialisation, initialRealValue );

   double xFactor, yFactor;
   InitializeRatios( width, height, xFactor, yFactor, x1, x2 );

   double w2 = width / 2.0 ;
   double h2 = height / 2.0 ;

   for (double y = 0; y < height; y++)
   {
      for (double x = 0; x < width; x++)
      {
         double xn = GetXn( x, width, w2, xFactor);
         double yn = GetYn( y, height, h2, yFactor);

         double radius = sqrt(xn * xn + yn * yn);

         if (radius < x1)
         {
            pAxialTransferFunction->SetValue((int)(x), (int)(y), 1.0);
         }

         if (radius >= x1)
         {
            if (radius < x2)
            {
               if ( (fabs(xn) > axisWidth) && (fabs(yn) > axisWidth))
               {
                  pAxialTransferFunction->SetValue((int)(x), (int)(y), 1.0);
               }
               else
               {
                  pAxialTransferFunction->SetValue((int)(x), (int)(y), 0.0);
               }
            }
            else
            {
               pAxialTransferFunction->SetValue((int)(x), (int)(y), 0.0);
            }
         }
      }
   }
   return pAxialTransferFunction;
}

//======================================================================================================

ArrayGrid<double>* TransferFunctionGenerator::GenerateAxisExtractTransferFunction(int width, int height, int axisWidth )
{
   bool needInitialisation = true;
   double initialRealValue = 0.0;
   ArrayGrid<double>* pAxialTransferFunction = new ArrayGrid<double>( width, height, needInitialisation, initialRealValue );

   for (double y = 0; y < height; y++)
   {
      for (double x = 0; x < width; x++)
      {
         if ( ( x < axisWidth ) || ( width - 1 - x < axisWidth ) )
         {
            pAxialTransferFunction->SetValue((int)(x), (int)(y), 1.0);
         }
         /*if ( ( y < axisWidth ) || ( height - 1 - y < axisWidth ) )
         {
            pAxialTransferFunction->SetValue((int)(x), (int)(y), 1.0);
         }*/
      }
   }
   return pAxialTransferFunction;
}

//======================================================================================================
void TransferFunctionGenerator::HighFrequencyCrossMask(FFTBand* inoutGrid, int nrBands)
{
   int width  = inoutGrid->GetWidth();
   int height = inoutGrid->GetHeight();

   complex<double> sqrtNorm = complex<double>( (1.0 / sqrt( (double)(nrBands) )), 0.0 );

   int halfwidth  = (int)(floor ( (double)(width) / 2.0 + 0.5));
   int halfheight = (int)(floor ( (double)(height) / 2.0  + 0.5));

   for (int y = 0; y < height; y++)
   {
      inoutGrid->SetValue(halfwidth, y, sqrtNorm);
   }

   for (int x = 0; x < width; x++)
   {
      inoutGrid->SetValue(x, halfheight, sqrtNorm);
   }
}

//======================================================================================================

FFTBand* TransferFunctionGenerator::GenerateOrientedTransferFunction(int width, int height, int orientationIndex, int maxNrOfOrientations, bool isForward, common::NumberMode myMode)
{
   FFTBand* pOrientedTransferFunction = new FFTBand(width, height);

   double K = (double)(maxNrOfOrientations);
   complex<double> modulationFactor;
   if (isForward)
   {
      modulationFactor = pow(complex<double>(0.0, -1.0), (double)(maxNrOfOrientations-1));
   }
   else
   {
      modulationFactor = pow(complex<double>(0.0, 1.0), (double)(maxNrOfOrientations-1));
   }

   double normfactor = common::MathUtils::Factorial(K - 1.0) / sqrt(K * common::MathUtils::Factorial(2.0 * (K - 1.0)));

   double w = (double)( width  );
   double h = (double)( height );

   double w2 = w / 2.0 ;
   double h2 = h / 2.0 ;

   double xFactor, yFactor;
   GetScaleFactors( width, height, xFactor, yFactor );

   if (myMode == common::MODE_REAL)
   {
      for (double y = 0.0; y < h; y+=1.0)
      {
         for (double x = 0.0; x < w; x+=1.0)
         {
            double xn = GetXn( x, width,  w2, xFactor );
            double yn = GetYn( y, height, h2, yFactor );

            double theta = atan2( yn, xn ) - (double)(orientationIndex) * M_PI / K;
            double ttmp = normfactor * pow( (double)( 2.0 * cos(theta)), (double)( K - 1.0 ) );

            complex<double> cvalue = modulationFactor * ttmp;
            pOrientedTransferFunction->SetValue((int)(x), (int)(y), cvalue);
         }
      }
   }
   else
   {
      for (double y = 0.0; y < h; y+=1.0)
      {
         for (double x = 0.0; x < w; x+=1.0)
         {
            double xn = GetXn( x, width, w2, xFactor);
            double yn = GetYn( y, height, h2, yFactor);
            complex<double> cvalue;

            double theta = atan2(yn, xn) - (double)(orientationIndex) * M_PI / K;
            double ttmp = normfactor * pow( (double)(2.0 * cos(theta)), (double)(K-1.0));
            if ((fabs(theta) < M_PI / 2.0) || (fabs(theta) > 3.0 * M_PI / 2.0))
            {
               cvalue = modulationFactor * ttmp;
            }
            else
            {
                cvalue = complex<double>( 0.0, 0.0 );
            }

            pOrientedTransferFunction->SetValue((int)(x), (int)(y), cvalue);
         }
      }
   }
   return pOrientedTransferFunction;
}

//======================================================================================================
// Generates log-Gabor transfer functions as described by Kovesi:
//    http://www.csse.uwa.edu.au/~pk/Research/MatlabFns/PhaseCongruency/Docs/convexpl.html
ArrayGrid<double>* TransferFunctionGenerator::GenerateLogRadiusBand(int width, int height, double centerFrequency, double radialWidth)
{
   bool needInitialisation = true;
   double initialRealValue = 0.0;
   ArrayGrid<double>* pLogRadiusBandPassTransferFunction = new ArrayGrid<double>( width, height, needInitialisation, initialRealValue );

   double xFactor, yFactor;
   GetScaleFactors( width, height, xFactor, yFactor );

   double w2 = width / 2.0 ;
   double h2 = height / 2.0 ;

   for (double y = 0; y < height; y++)
   {
      for (double x = 0; x < width; x++)
      {
         double xn = GetXn( x, width,  w2, xFactor );
         double yn = GetYn( y, height, h2, yFactor );

         double radius = sqrt(xn * xn + yn * yn);
         double l1 = log(radius/centerFrequency);
         double l2 = log(radialWidth);
         pLogRadiusBandPassTransferFunction->SetValue( (int)(x), (int)(y), ( exp(-( l1 * l1 ) / ( 2.0 * l2 * l2 ) ) ) );
      }
   }
   return pLogRadiusBandPassTransferFunction;
}

//======================================================================================================

ArrayGrid<double>* TransferFunctionGenerator::GenerateGaussianAngularBand(int width, int height, double centerAngle, double angleSpread)
{
   bool needInitialisation = true;
   double initialRealValue = 0.0;
   ArrayGrid<double>* pAngularSpreadTransferFunction = new ArrayGrid<double>( width, height, needInitialisation, initialRealValue );

   double xFactor, yFactor;
   GetScaleFactors( width, height, xFactor, yFactor );

   double w2 = width / 2.0 ;
   double h2 = height / 2.0 ;

   for (double y = 0; y < height; y++)
   {
      for (double x = 0; x < width; x++)
      {
         double xn = GetXn( x, width, w2, xFactor);
         double yn = GetYn( y, height, h2, yFactor);

         double theta = atan2(-yn, xn);              // Matrix values contain polar angle.

         double sintheta = sin(theta);
         double costheta = cos(theta);

         double ds = sintheta * cos( centerAngle ) - costheta * sin( centerAngle );
         double dc = costheta * cos( centerAngle ) + sintheta * sin( centerAngle );
         double dtheta = fabs( atan2( ds, dc ) );
         double spread = exp( ( - dtheta * dtheta ) / ( 2.0 * angleSpread * angleSpread ) );
         pAngularSpreadTransferFunction->SetValue( (int)(x), (int)(y), spread );
      }
   }
   return pAngularSpreadTransferFunction;
}

//======================================================================================================

ArrayGrid<double>* TransferFunctionGenerator::GenerateLogGaborBandTransferFunction(int width, int height, double centerFrequency, double radialWidth, double centerAngle, double angleSpread)
{
   ArrayGrid<double>* pLogGaborTransferFunction = GenerateLogRadiusBand( width, height, centerFrequency, radialWidth );
   ArrayGrid<double>* pAngularTransferFunction = GenerateGaussianAngularBand( width, height, centerAngle, angleSpread );

   pLogGaborTransferFunction->MultiplyWith( pAngularTransferFunction );

   delete pAngularTransferFunction;
   return pLogGaborTransferFunction;
}

//======================================================================================================

ArrayGrid<double>* ConvertTransferFunctionToFilterKernel( FFTBand* pTransferFunction, common::NumberMode mode )
{
   pTransferFunction->ApplyInverseTransform();
   image::ArrayGrid<double>* pGridKernel = 0;
   if (mode == common::MODE_REAL)
   {
      pGridKernel = pTransferFunction->ConvertToRealGrid();
   }
   else
   {
      pGridKernel = pTransferFunction->ConvertToImaginaryGrid();
   }
   return pGridKernel;
}

//======================================================================================================

ArrayGrid<double>* ConvertTransferFunctionToFilterKernel( image::ArrayGrid<double>* pTransferFunction, common::NumberMode mode = common::MODE_REAL )
{
   FFTBand* pTransferFunctionFFT = new FFTBand( pTransferFunction );
   ArrayGrid<double>* pGridKernel = ConvertTransferFunctionToFilterKernel( pTransferFunctionFFT, mode );
   delete pTransferFunctionFFT;
   return pGridKernel;
}

//======================================================================================================

}
}
