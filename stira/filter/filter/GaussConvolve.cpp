
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

#include <cassert>

#include "GaussConvolve.h"
#include "../../common/common/MathUtils.h"
#include "../../fouriertools/fouriertools/FFT.h"
#include "../../imagetools/tools/ImageIO.h"
#include "../../imagetools/tools/ImageTools.h"
#include "../../imagetools/imagegenerator/GridGenerator.h"
#include "../../imagedata/simpletools/GridExtender.h"

//#define KERNEL_VISUALIZE

namespace stira{
namespace filter{

using namespace common;
using namespace fouriertools;
using namespace image;

GaussConvolve::GaussConvolve()
{
}

//--------------------------------------------------------------------------

GaussConvolve::~GaussConvolve()
{
}

//-------------------------------------------------------------------

ArrayGrid<double>* GaussConvolve::CreateBlurredBars( int width, int height, int barWidth, double sigmaBlurMax )
{
   ArrayGrid<double>* pBars = GridGenerator::GenerateBars( width, height, barWidth );
   double sigmaTmp = 0.0;
   double* pKernel = 0;
   double deltaSigma = sigmaBlurMax / ((double)(width));

   int kernelSize = 0;
   int newCandidateKernelSize = 0;
   double *pColumnIn  = new double[ height ];
   double *pColumnOut = new double[ height ];

   for (int x = 0; x < width; x++)
   {
      double* pNewCandidateKernel = Generate1DGaussianKernel( sigmaTmp, newCandidateKernelSize, 0 );

      if ( newCandidateKernelSize % 2 == 1)
      {
         if (pKernel != 0)
         {
            delete []pKernel;
         }
         pKernel = pNewCandidateKernel;
         kernelSize = newCandidateKernelSize;

         // filter all columns
         for (int y = 0; y < height; y++)
         {
            pColumnIn[y] = pBars->GetValue(x, y);
         }
         SeparableFilter::BasicFilter1D (&(*pColumnIn), &(*pKernel), &(*pColumnOut), height, kernelSize, image::GridExtender<double>::EXTEND_MIRROR );

         for (int y = 0; y < height; y++)
         {
            pBars->SetValue(x, y, pColumnOut[y] );
         }
      }
      sigmaTmp += deltaSigma;
   }
   delete []pColumnIn;
   delete []pColumnOut;
   if (pKernel != 0)
   {
      delete []pKernel;
   }

   return pBars;
}

//--------------------------------------------------------------------------

double* GaussConvolve::Generate1DGaussianKernel(double sigma, int& size, int order)
{
   if ( sigma < 0.5 )
   {
      size = 0;
      return 0;
   }
   else
   {
      size = 2 * (int)( 6.0 * sigma + 0.5 ) / 2 + 1;
      if (size % 2 == 0) {size++;}
      int halfSize = ( size / 2 );
      double* pKernel = new double[ size ];
      #ifdef KERNEL_VISUALIZE
      cout << endl << endl << "======================================================" << endl << flush;
      #endif

      switch( order )
      {
         case 0:
         {
            pKernel[halfSize]= MathUtils::Gaussian( 0.0, 0.0, sigma );
            #ifdef KERNEL_VISUALIZE
            cout << endl << endl << "0\t" << pKernel[halfSize] << endl << flush;
            #endif
            if (size != 1)
            {
               for (int i = 1; i <= halfSize; i++)
               {
                  double g = MathUtils::Gaussian( (double)(i), 0.0, sigma );
                  pKernel[halfSize+i]= g;
                  pKernel[halfSize-i]= g;
                  #ifdef KERNEL_VISUALIZE
                  cout << i << "\t" << g << endl << flush;
                  #endif
               }
            }
            double ssum = 0.0;
            for (int i = 0; i < size; i++)
            {
               ssum += pKernel[i];
            }
            #ifdef KERNEL_VISUALIZE
            cout << "\t ssum = " << ssum;
            #endif
            for (int i = 0; i < size; i++)
            {
               pKernel[i] /= ssum;
               #ifdef KERNEL_VISUALIZE
               cout << " \t " << pKernel[i] << endl << flush;
               #endif
            }

            break;
         }
         case 1:
         {
            pKernel[halfSize]= MathUtils::GaussianFirstDerivativeX1D( 0.0, 0.0, sigma );
            for (int i = 1; i <= halfSize; i++)
            {
               double g = MathUtils::GaussianFirstDerivativeX1D( (double)(i), 0.0, sigma );
               pKernel[halfSize+i]= g;
               pKernel[halfSize-i]= -g;
               #ifdef KERNEL_VISUALIZE
               cout << g << " \t " << endl << flush;
               #endif
            }
            break;
         }
         case 2:
         {
            pKernel[halfSize]= MathUtils::GaussianSecondDerivateX1D( 0.0, 0.0, sigma );
            for (int i = 1; i <= halfSize; i++)
            {
               double g = MathUtils::GaussianSecondDerivateX1D( (double)(i), 0.0, sigma );
               pKernel[halfSize+i]= g;
               pKernel[halfSize-i]= g;
               #ifdef KERNEL_VISUALIZE
               cout << g << " \t " << endl << flush;
               #endif
            }
            break;
         }
         default:
         {
            cerr << "Cannot generate 1D gaussian derivative filter kernel of order " << order << endl << flush;
            break;
         }
      }
      return pKernel;
   }
}

//--------------------------------------------------------------------------

Image* GaussConvolve::Convolve(Image* pImage, double sigma, FilterType myType)
{
   switch (myType)
   {
      case FFT_BASED:
      {
         return FFTConvolve( pImage, sigma);
      }
      case RECURSIVE_BASED:
      {
         return RecursiveConvolve( pImage, sigma);
      }
      default:
      {
         cerr << "Unsupported convolution type" << endl << flush;
         return 0;
      }
   }
}

//--------------------------------------------------------------------------

image::ArrayGrid<double>* GaussConvolve::Convolve(image::ArrayGrid<double>* pGrid, double sigma, FilterType myType )
{
   switch (myType)
   {
      case FFT_BASED:
      {
         return FFTConvolve( pGrid, sigma);
      }
      case RECURSIVE_BASED:
      {
         return RecursiveConvolve( pGrid, sigma);
      }
      default:
      {
         cerr << "Unsupported convolution type" << endl << flush;
         return 0;
      }
   }
}

//--------------------------------------------------------------------------

ArrayGrid<double>* GaussConvolve::DerivativeConvolveFFT(image::ArrayGrid<double>* pGridIn, double sigmaX, double sigmaY, DerivativeType myType)
{
   ArrayGrid<double>* pFilterKernel = 0;

   ArrayGrid<double>* pInputExtendedGrid = pGridIn->Clone();

   int width = pInputExtendedGrid->GetWidth();
   int height = pInputExtendedGrid->GetHeight();
   switch (myType)
   {
      case DERIVATIVE_NONE:
      {
         pFilterKernel = GridGenerator::GenerateGaussian( width, height, sigmaX, sigmaY );
         #ifdef KERNEL_VISUALIZE
         ImageIO::WritePGM( pFilterKernel, std::string("FilterKernelGauss.pgm"), ImageIO::NORMAL_OUT );
         #endif
         break;
      }
      case DERIVATIVE_X:
      {
         pFilterKernel = GridGenerator::GenerateGaussianFirstDerivativeX( width, height, sigmaX, sigmaY );
         #ifdef KERNEL_VISUALIZE
         ImageIO::WritePGM( pFilterKernel, std::string("FilterKernelGauss_FirstDerivative_X.pgm"), ImageIO::NORMAL_OUT );
         #endif
         break;
      }
      case DERIVATIVE_Y:
      {
         pFilterKernel = GridGenerator::GenerateGaussianFirstDerivativeY( width, height, sigmaX, sigmaY );
         #ifdef KERNEL_VISUALIZE
         ImageIO::WritePGM( pFilterKernel, std::string("FilterKernelGauss_FirstDerivative_Y.pgm"), ImageIO::NORMAL_OUT );
         #endif
         break;
      }
      case DERIVATIVE_XX:
      {
         pFilterKernel = GridGenerator::GenerateGaussianSecondDerivativeX( width, height, sigmaX, sigmaY );
         #ifdef KERNEL_VISUALIZE
         ImageIO::WritePGM( pFilterKernel, std::string("FilterKernelGauss_SecondDerivative_XX.pgm"), ImageIO::NORMAL_OUT );
         #endif
         break;
      }
      case DERIVATIVE_YY:
      {
         pFilterKernel = GridGenerator::GenerateGaussianSecondDerivativeY( width, height, sigmaX, sigmaY );
         #ifdef KERNEL_VISUALIZE
         ImageIO::WritePGM( pFilterKernel, std::string("FilterKernelGauss_SecondDerivative_YY.pgm"), ImageIO::NORMAL_OUT );
         #endif
         break;
      }
      case DERIVATIVE_XY:
      {
         pFilterKernel = GridGenerator::GenerateGaussianMixedDerivativesXY( width, height, sigmaX, sigmaY );
         #ifdef KERNEL_VISUALIZE
         ImageIO::WritePGM( pFilterKernel, std::string("FilterKernelGauss_SecondDerivative_XY.pgm"), ImageIO::NORMAL_OUT );
         #endif
         break;
      }
      default:
      {
         cerr << "Unsupported convolution type" << endl << flush;
         return 0;
      }
   }

   ArrayGrid<double>* pConvolvedGrid = FFT::Convolve( pInputExtendedGrid, pFilterKernel);

   delete pInputExtendedGrid;
   delete pFilterKernel;

   //ArrayGrid<double>* pCroppedGrid = GridExtender<double>::CropBorder( pConvolvedGrid, borderWidth, borderWidth);
   ArrayGrid<double>* pCroppedGrid = pConvolvedGrid->Clone();

   delete pConvolvedGrid;
   return pCroppedGrid;
}

//--------------------------------------------------------------------------

ArrayGrid<double>* GaussConvolve::DerivativeConvolveSeparable(image::ArrayGrid<double>* pGridIn, double sigma, DerivativeType myType, image::GridExtender<double>::ExtensionType myExtensionType)
{
   double* pFilter1DX = 0;
   double* pFilter1DY = 0;
   int kernelSizeX;
   int kernelSizeY;
   int orderX;
   int orderY;
   switch (myType)
   {
      case DERIVATIVE_NONE:
      {
         orderX = orderY = 0;
         break;
      }
      case DERIVATIVE_X:
      {
         orderX = 1; orderY = 0;
         break;
      }
      case DERIVATIVE_Y:
      {
         orderX = 0; orderY = 1;
         break;
      }
      case DERIVATIVE_XX:
      {
         orderX = 2; orderY = 0;
         break;
      }
      case DERIVATIVE_YY:
      {
         orderX = 0; orderY = 2;
         break;
      }
      case DERIVATIVE_XY:
      {
         orderX = 1; orderY = 1;
         break;
      }
      default:
      {
         cerr << "Unsupported convolution type" << endl << flush;
         return 0;
      }
   }
   pFilter1DX = Generate1DGaussianKernel( sigma, kernelSizeX, orderX );
   pFilter1DY = Generate1DGaussianKernel( sigma, kernelSizeY, orderY );
   SeparableFilter sf;
   ArrayGrid<double>* pConvolvedGrid = sf.RunRowColumn( pGridIn, pFilter1DX, pFilter1DY, kernelSizeX, kernelSizeY, myExtensionType );
   delete []pFilter1DX;
   delete []pFilter1DY;
   return pConvolvedGrid;
}

//--------------------------------------------------------------------------

ArrayGrid<double>* GaussConvolve::ConvolveSeparable(image::ArrayGrid<double>* pGridIn, double sigma)
{
   return DerivativeConvolveSeparable( pGridIn, sigma, DERIVATIVE_NONE, image::GridExtender<double>::EXTEND_TILED);
}

//--------------------------------------------------------------------------

image::Image* GaussConvolve::DerivativeConvolveFFT(image::Image* pImage, double sigma, DerivativeType myType, image::GridExtender<double>::ExtensionType myExtensionType)
{
   int borderWidth = 50;
   int borderHeight = 50;
   image::Image* pImageIn = 0;

   switch (myExtensionType)
   {
      case image::GridExtender<double>::EXTEND_MIRROR:
      {
         pImageIn = ImageTools::MirrorBorder( pImage, borderWidth, borderHeight);
         break;
      }
      case image::GridExtender<double>::EXTEND_ZERO:
      {
         pImageIn = ImageTools::PaddBorder( pImage, borderWidth, borderHeight, 0.0 );
         break;
      }
      case image::GridExtender<double>::EXTEND_TILED:
      default:
      {
         pImageIn = pImage;
         break;
      }
   }

   int nrBands = pImageIn->GetNumberOfBands();
   int width = pImageIn->GetWidth();
   int height = pImageIn->GetHeight();

   Image* pImageOut = new Image(width, height);

   for (int i = 0; i < nrBands; i++)
   {
      ArrayGrid<double>* pGridOut = DerivativeConvolveFFT( pImageIn->GetBands()[i], sigma, sigma, myType );
      pImageOut->AddBand( pGridOut );
   }
   std::string outName = pImageIn->GetImageName() + std::string("-Gauss");

   Image* pImageFinal = 0;
   switch (myExtensionType)
   {
      case image::GridExtender<double>::EXTEND_MIRROR:
      case image::GridExtender<double>::EXTEND_ZERO:
      {
         pImageFinal = ImageTools::CropBorder( pImageOut, borderWidth, borderHeight);
         delete pImageOut;
         delete pImageIn;
         break;
      }
      case image::GridExtender<double>::EXTEND_TILED:
      default:
      {
         pImageFinal = pImageOut;
         break;
      }
   }
   pImageFinal->SetImageName( outName );
   return pImageFinal;
}

//--------------------------------------------------------------------------

image::Image* GaussConvolve::DerivativeConvolveSeparable(image::Image* pImageIn, double sigma, DerivativeType myType, image::GridExtender<double>::ExtensionType myExtensionType)
{
   int nrBands = pImageIn->GetNumberOfBands();
   int width = pImageIn->GetWidth();
   int height = pImageIn->GetHeight();

   Image* pImageOut = new Image(width, height);

   for (int i = 0; i < nrBands; i++)
   {
      ArrayGrid<double>* pGridOut = DerivativeConvolveSeparable( pImageIn->GetBands()[i], sigma, myType, myExtensionType );
      pImageOut->AddBand( pGridOut );
   }
   std::string outName = pImageIn->GetImageName() + std::string("-Gauss");
   pImageOut->SetImageName(outName);
   return pImageOut;
}

//--------------------------------------------------------------------------

image::Image* GaussConvolve::ConvolveSeparable(image::Image* pImageIn, double sigma )
{
   return DerivativeConvolveSeparable( pImageIn, sigma, DERIVATIVE_NONE, image::GridExtender<double>::EXTEND_TILED);
}

//--------------------------------------------------------------------------

image::ArrayGrid<double>* GaussConvolve::UpsampleGaussianInterpolated( image::ArrayGrid<double>* pGridIn, int upscalefactor )
{
   double alpha = 1.4;
   double sigmaGauss = alpha * (double)(upscalefactor * upscalefactor);
   bool needInitialisation = true;
   double initialRealValue = 0.0;

   int sourceWidth  = pGridIn->GetWidth();
   int sourceHeight = pGridIn->GetHeight();

   int upscaledWidth  = sourceWidth  * upscalefactor;
   int upscaledHeight = sourceHeight * upscalefactor;

   int halfWidth = upscalefactor / 2;

   image::ArrayGrid<double>* pUpscaledGrid = new ArrayGrid<double>( upscaledWidth, upscaledHeight, needInitialisation, initialRealValue );

   for (int y = 0; y < sourceHeight; y++)
   {
      for (int x = 0; x < sourceWidth; x++)
      {
         int xx = x * upscalefactor + halfWidth;
         int yy = y * upscalefactor + halfWidth;
         assert (xx < upscaledWidth);
         assert (yy < upscaledHeight);
         pUpscaledGrid->SetValue(xx, yy, pGridIn->GetValue(x, y) );
      }
   }
   ArrayGrid<double>* pInterpolatedGrid = DerivativeConvolveSeparable(pUpscaledGrid, sigmaGauss, DERIVATIVE_NONE);
   pInterpolatedGrid->MultiplyWith( upscalefactor );
   delete pUpscaledGrid;
   return pInterpolatedGrid;
}

//--------------------------------------------------------------------------

double GaussConvolve::GetQ(double sigma)
{
   double q = 0.0;
   if (sigma < 0.5)
   {
      cerr << "GaussConvolve: Value of sigma (" << sigma << ") not valid!!" << endl << flush;
      return 0;
   }

   if (sigma <= 2.5)
   {
      q = 3.97156 - 4.14554 * sqrt(1.0 - 0.26891 * sigma);
      return q;
   }

   q = 0.98711 * sigma - 0.96330;
   return q;
}

//--------------------------------------------------------------------------

ArrayGrid<double>* GaussConvolve::RecursiveConvolve( ArrayGrid<double>* pGridIn, double sigma)
{
   int borderWidth  = (int)(5 * sigma);
   int borderHeight = (int)(5 * sigma);
   ArrayGrid<double>* pGridExpanded = GridExtender<double>::MirrorBorder( pGridIn, borderWidth, borderHeight );

   int height = pGridExpanded->GetHeight();
   int width  = pGridExpanded->GetHeight();

   double q = GetQ( sigma );

   double b0 = 1.57825 + 2.44413 * q + 1.42810 * q * q + 0.422205 * q * q * q;
   double b1 =           2.44413 * q + 2.85619 * q * q + 1.266610 * q * q * q;
   double b2 =                       - 1.42810 * q * q - 1.266610 * q * q * q;
   double b3 =                                           0.422205 * q * q * q;
   double B  = 1.0 - ((b1 + b2 + b3) / b0);

   std::cout << "filtering coefficients: q = " << q << std::endl << std::flush;

   std::cout << "\t b0 = " << b0 << std::endl << std::flush;
   std::cout << "\t b1 = " << b1 << std::endl << std::flush;
   std::cout << "\t b2 = " << b2 << std::endl << std::flush;
   std::cout << "\t b3 = " << b3 << std::endl << std::flush;
   std::cout << "\t B  = " << B << std::endl << std::flush;

   // filter rows
   for (int y = 0; y < height; y++)
   {
      //forward filter
      for (int x = 3; x < width; x++)
      {
         double ttmp = B * pGridExpanded->GetValue(x, y) + ( (   b1 * pGridExpanded->GetValue(x-1, y)
                                                               + b2 * pGridExpanded->GetValue(x-2, y)
                                                               + b3 * pGridExpanded->GetValue(x-3, y)
                                                             ) / b0
                                                           );
         pGridExpanded->SetValue(x, y, ttmp);
      }
      //backward filter
      for (int x = width-4; x >= 0; x--)
      {
         double ttmp = B * pGridExpanded->GetValue(x, y) + ( (   b1 * pGridExpanded->GetValue(x+1, y)
                                                               + b2 * pGridExpanded->GetValue(x+2, y)
                                                               + b3 * pGridExpanded->GetValue(x+3, y)
                                                             ) / b0
                                                           );
         pGridExpanded->SetValue(x, y, ttmp);
      }
   }

   // filter columns
   for (int x = 0; x < width; x++)
   {
      //forward filter
      for (int y = 3; y < height; y++)
      {
         double ttmp = B * pGridExpanded->GetValue(x, y) + ( (   b1 * pGridExpanded->GetValue(x, y-1)
                                                               + b2 * pGridExpanded->GetValue(x, y-2)
                                                               + b3 * pGridExpanded->GetValue(x, y-3)
                                                             ) / b0
                                                           );
         pGridExpanded->SetValue(x, y, ttmp);
      }
      //backward filter
      for (int y = height-4; y >= 0; y--)
      {
         double ttmp = B * pGridExpanded->GetValue(x, y) + ( (   b1 * pGridExpanded->GetValue(x, y+1)
                                                               + b2 * pGridExpanded->GetValue(x, y+2)
                                                               + b3 * pGridExpanded->GetValue(x, y+3)
                                                             )/ b0
                                                           );
         pGridExpanded->SetValue(x, y, ttmp);
      }
   }

//    ArrayGrid<double>* pGridOut = pGridExpanded->CropBorder( borderWidth, borderHeight );
//    delete pGridExpanded;
//    return pGridOut;

   return pGridExpanded;
}

//--------------------------------------------------------------------------

Image* GaussConvolve::FFTConvolve(Image* pInputImage, double sigma)
{
   return FFT::GaussConvolve( pInputImage, sigma );
}

//--------------------------------------------------------------------------

ArrayGrid<double>* GaussConvolve::FFTConvolve(ArrayGrid<double>* pInputGrid, double sigma)
{
   return FFT::GaussConvolve( pInputGrid, sigma );
}

//--------------------------------------------------------------------------

Image* GaussConvolve::RecursiveConvolve(Image* pInputImage, double sigma)
{
   int nrOfBands = pInputImage->GetNumberOfBands();
   int width     = pInputImage->GetWidth();
   int height    = pInputImage->GetHeight();

   Image* pConvolvedImage = new Image( width, height);

   for (int bandNr = 0; bandNr < nrOfBands; bandNr++)
   {
      ArrayGrid<double>* pConvolvedGrid = RecursiveConvolve(pInputImage->GetBands()[bandNr], sigma);
      pConvolvedImage->AddBand( pConvolvedGrid );
   }
   std::string outName = pInputImage->GetImageName() + std::string("-Gauss");
   pConvolvedImage->SetImageName(outName);
   return pConvolvedImage;
}
//--------------------------------------------------------------------------


}
}
