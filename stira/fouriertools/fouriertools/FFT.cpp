
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

#include "FFT.h"
#include "FFTBand.h"
#include "TransferFunctionGenerator.h"
#include "../../imagetools/tools/ImageIO.h"
#include "../../imagetools/tools/ImageTools.h"
#include "../../imagetools/imagegenerator/GridGenerator.h"
#include "../../imagedata/simpletools/GridStatistics.h"
#include "../../imagedata/simpletools/GridExtender.h"
#include "../../common/common/MathUtils.h"

#include <iostream>
#include <fstream>

namespace stira {
namespace fouriertools {

using namespace image;

// These class' methods are divided in the following categories 
//    1) GENERAL METHODS
//    2) GENERAL OPERATIONS
//    3) APPLY TRANSFER FUNCTION VARIANTS      (output spatial and complex-valued )
//    4) APPLY TRANSFER FUNCTION FFT VARIANTS  (output fourier )
//    5) APPLY TRANSFER FUNCTION FFT VARIANTS  (output spatial and real-valued )
///////////////////////////////////////////////////////////////////////////////////////

//---------------------------------------------------------------------------------------

FFT::FFT()
{
}

//---------------------------------------------------------------------------------------

FFT::~FFT()
{
}

//---------------------------------------------------------------------------------------

/////////////////////////
//                     //
// 1) GENERAL METHODS  //
//                     //
/////////////////////////

ArrayGrid<complex <double> >* FFT::CreateComplexGridFromRealGrid( ArrayGrid<double>* pGridIn)
{
   int width  = pGridIn->GetWidth();
   int height = pGridIn->GetHeight();
   bool needInitialisation = true;
   complex<double> initialComplexValue( 0.0, 0.0);
   ArrayGrid< complex<double> >* pComplexGrid = new ArrayGrid< complex<double> >( width, height, needInitialisation, initialComplexValue );
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         complex<double> cv(pGridIn->GetValue(x, y), 0.0);
         pComplexGrid->SetValue(x, y, cv);
      }
   }
   return pComplexGrid;
}

//---------------------------------------------------------------------------------------

ArrayGrid<double>* FFT::CreateRealGridFromComplexGrid( ArrayGrid<complex <double> >* pGridIn)
{
   int width  = pGridIn->GetWidth();
   int height = pGridIn->GetHeight();
   bool needInitialisation = true;
   double initialRealValue = 0.0;
   ArrayGrid<double>* pRealGrid = new ArrayGrid<double>( width, height, needInitialisation, initialRealValue );
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         pRealGrid->SetValue(x, y, (pGridIn->GetValue(x, y)).real());
      }
   }
   return pRealGrid;
}

//---------------------------------------------------------------------------------------

void FFT::RescaleGrid( ArrayGrid<double>* pGrid, double newMin, double newMax)
{
   double oldMin =  10000000000000000000000.0;
   double oldMax = -10000000000000000000000.0;
   
   int width = pGrid->GetWidth();
   int height = pGrid->GetHeight();
   
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         if (pGrid->GetValue(x, y) < oldMin) {oldMin = pGrid->GetValue(x, y);}
         if (pGrid->GetValue(x, y) > oldMax) {oldMax = pGrid->GetValue(x, y);}
      }
   }
   
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         // first normalize between 0 and 1
         double ttmp1 = (pGrid->GetValue(x, y) - oldMin) / (oldMax - oldMin);
         
         double ttmp2 = (newMax - newMin) * ttmp1 + newMin;
         pGrid->SetValue(x, y, ttmp2);
      }
   }
}

//---------------------------------------------------------------------------------------

void FFT::WriteFFTDataToPPM(FFTBand* pFFTData, FFTDataType myDataType, char* pFileName, double factor)
{
   ofstream file_out;
   file_out.open ( pFileName, ios::binary );

   file_out << "P5" << " " << pFFTData->GetWidth() << " " << pFFTData->GetHeight() << " " << 255 << "\n";

   if (myDataType == RE)
   {
      for (int y = 0; y < pFFTData->GetHeight(); y++ )
      {
         for (int x = 0; x < pFFTData->GetWidth(); x++ )
         {
            file_out << (unsigned char)(factor * (pFFTData->GetValue(x, y).real()));
         }
      }
   }
   else
   {
      for (int y = 0; y < pFFTData->GetHeight(); y++ )
      {
         for (int x = 0; x < pFFTData->GetWidth(); x++ )
         {
            file_out << (unsigned char)(factor * (pFFTData->GetValue(x, y).imag()));
         }
      }
   }
   file_out.close ();
}

//======================================================================================================

/////////////////////////////////////
//                                 //
// 2) GENERAL OPERATIONS           //
//                                 //
/////////////////////////////////////

ArrayGrid<double>* FFT::ComputePowerSpectrum( ArrayGrid<double>* pSourceGrid )
{
   FFTBand* pFFTDataBand = new FFTBand( pSourceGrid );
   pFFTDataBand->ApplyForwardTransform();

   int width  = pFFTDataBand->GetWidth();
   int height = pFFTDataBand->GetHeight();
   bool needInitialisation = true;
   double initialRealValue = 0.0;
   
   ArrayGrid<double>* pSpectrumGrid = new ArrayGrid<double>( width, height, needInitialisation, initialRealValue );
   
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         complex< double > ttmpValue = pFFTDataBand->GetValue( x, y );
         pSpectrumGrid->SetValue( x, y, (ttmpValue * conj(ttmpValue)).real() );
      }
   }
   
   delete pFFTDataBand;
   
   pSpectrumGrid->SwitchQuadrants();
   
   return pSpectrumGrid;
}

//---------------------------------------------------------------------------------------

image::ArrayGrid<double>* FFT::ComputeLogPowerSpectrum( image::ArrayGrid<double>* pSourceGrid )
{
   ArrayGrid<double>* pSpectrumGrid = ComputePowerSpectrum( pSourceGrid );
   
   int width  = pSpectrumGrid->GetWidth();
   int height = pSpectrumGrid->GetHeight();

   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         double ttmpValue = log10( pSpectrumGrid->GetValue(x, y) + 1.0);

         pSpectrumGrid->SetValue( x, y, ttmpValue );
      }
   }
   
   double mmin, mmax;
   GridStatistics<double>::GetMinMax( pSpectrumGrid, mmin, mmax );

   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         double ttmpValue = pSpectrumGrid->GetValue( x, y);

         pSpectrumGrid->SetValue( x, y, (255.0 * (ttmpValue - mmin) / (mmax - mmin)));
      }
   }
   
   return pSpectrumGrid;
}

//---------------------------------------------------------------------------------------

vector<double> FFT::ComputeRadiallyAveragedSpectrum( ArrayGrid<double>* pSourceGrid, int thetaSteps )
{
   ArrayGrid<double>* pSpectrum = ComputePowerSpectrum( pSourceGrid ); // already puts DC component in center!!
   //ImageIO::WritePGM( pSpectrum, string("RawSpectrumIn.pgm"), ImageIO::NORMAL_OUT);
   
   int width = pSourceGrid->GetWidth();
   int height = pSourceGrid->GetHeight();
   
   double ratioWidthHeight = (double)(width) / (double)(height);
   
   // width and height are allowed to be different from now on
   
   int halfWidth  = width  / 2;
   int halfHeight = height / 2;
   
   double thetaStepSize = (2.0 * M_PI) / (double)(thetaSteps);

   vector<double> vAveragedspectrum;
   
   // scan in polar coordinates
   ////////////////////////////
   
   if (ratioWidthHeight < 1.0)
   {
      double maxradius = (double)(width / 2);
      for (double radius = 0.0; radius < maxradius; radius ++)
      {
         double tmpValue = 0.0;
         for (double theta = 0.0; theta < (2.0 * M_PI); theta += thetaStepSize)
         {
            int x = (int)( halfWidth + radius * cos(theta) + 0.5); //nearest neighbour
            int y = (int)( halfHeight + radius * ratioWidthHeight * sin(theta) + 0.5); //nearest neighbour
            tmpValue += pSpectrum->GetValue(x, y);
         }
         tmpValue /= (double)(thetaSteps);
         vAveragedspectrum.push_back(tmpValue);
      }
   }
   else
   {
      double maxradius = (double)(width / 2) / ratioWidthHeight;
      for (double radius = 0.0; radius < maxradius; radius ++)
      {
         double tmpValue = 0.0;
         for (double theta = 0.0; theta < (2.0 * M_PI); theta += thetaStepSize)
         {
            int x = (int)( halfWidth + radius / ratioWidthHeight * cos(theta) + 0.5); //nearest neighbour
            int y = (int)( halfHeight + radius * sin(theta) + 0.5); //nearest neighbour
            tmpValue += pSpectrum->GetValue(x, y);
         }
         tmpValue /= (double)(thetaSteps);
         vAveragedspectrum.push_back(tmpValue);
      }
   }
   
   ofstream ofp;
   ofp.open("AveragedSpectrum.txt", ios::out);

   if (!ofp) 
   {
      cerr << "Can't open file: AveragedSpectrum.txt" << endl;
      return vAveragedspectrum;
   }
   
   for (int i = 0; i < (int)(vAveragedspectrum.size()); i++)
   {
      ofp << i << std::string("\t") << log10(vAveragedspectrum[i]) 
               << std::string("\t") << sqrt(vAveragedspectrum[i] / ( width * height))
               << endl << flush;
   }
   ofp.close();
   
   return vAveragedspectrum;
}

//---------------------------------------------------------------------------------------

Image* FFT::Convolve( Image* pInput, ArrayGrid<double>* pFilterKernel)
{
   int nrBands = pInput->GetNumberOfBands();
   int width = pInput->GetWidth();
   int height = pInput->GetHeight();
   Image* pOut = new Image( width, height );
   for (int i = 0; i < nrBands; i++)
   {
      image::ArrayGrid<double>* pGridOut = FFT::Convolve( pInput->GetBands()[i], pFilterKernel );
      pOut->AddBand( pGridOut );
   }
   return pOut;
}

//---------------------------------------------------------------------------------------

ArrayGrid<double>* FFT::Convolve( ArrayGrid<double>* pSourceGrid, ArrayGrid<double>* pFilterKernel)
{
   FFTBand myFFTImageData( pSourceGrid );
   myFFTImageData.ApplyForwardTransform();

   FFTBand myFFTFilterData( pFilterKernel );
   myFFTFilterData.ApplyForwardTransform();

   FFTBand myConvolvedData( pSourceGrid );
   
   int width  = pSourceGrid->GetWidth();
   int height = pSourceGrid->GetHeight();
   int nrPixels = width * height;
   
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         complex<double> ttmp;

         ttmp = (myFFTImageData.GetValue(x, y) * myFFTFilterData.GetValue(x, y));
         complex<double> ttmpNormalized = ttmp / (double)(nrPixels);

         myConvolvedData.SetValue(x, y, ttmpNormalized);
      }
   }
   myConvolvedData.ApplyInverseTransform();

   return myConvolvedData.ConvertToRealGrid();
}

//---------------------------------------------------------------------------------------

Image* FFT::GaussConvolve(Image* pInputImage, double sigma )
{
   int borderFactor = 0;
   int borderWidth = (int)(borderFactor * sigma);
   
   if (borderWidth > 0)
   {
      cout << "###WARNING### Adding border/ blurring / removing border adds extra frequencies along the x and Y axes!!!" << endl << flush;
   }
   
   if ( borderWidth > pInputImage->GetWidth() )  { borderWidth = pInputImage->GetWidth() -1;}
   if ( borderWidth > pInputImage->GetHeight() ) { borderWidth = pInputImage->GetHeight() -1;}
   
   Image* pInputCloneImage = ImageTools::MirrorBorder( pInputImage, borderWidth, borderWidth );

   int nrOfBands = pInputCloneImage->GetNumberOfBands();
   int width = pInputCloneImage->GetWidth();
   int height = pInputCloneImage->GetHeight();
   
   Image* pConvolvedImage = new Image( width, height);
   ArrayGrid<double>* pPSF = GridGenerator::GenerateGaussian ( width, height, sigma, sigma);
   
   for (int bandNr = 0; bandNr < nrOfBands; bandNr++)
   {
      ArrayGrid<double>* pConvolvedGrid = FFT::Convolve( pInputCloneImage->GetBands()[bandNr], pPSF);
      pConvolvedImage->AddBand( pConvolvedGrid );
   }

   delete pInputCloneImage;
   delete pPSF;
   
   Image* pOutImage = ImageTools::CropBorder( pConvolvedImage, borderWidth, borderWidth);
   
   delete pConvolvedImage;
   return pOutImage;
}

//---------------------------------------------------------------------------------------

ArrayGrid<double>* FFT::GaussConvolve( ArrayGrid<double>* pInputGrid, double sigma )
{
   int borderFactor = 0;
   int borderWidth = (int)(borderFactor * sigma);
   
   if (borderWidth > 0)
   {
      cout << "###WARNING### Adding border/ blurring / removing border adds extra frequencies along the x and Y axes!!!" << endl << flush;
   }
   
   if (borderWidth > pInputGrid->GetWidth())  {borderWidth = pInputGrid->GetWidth() -1;}
   if (borderWidth > pInputGrid->GetHeight()) {borderWidth = pInputGrid->GetHeight() -1;}
   
   ArrayGrid<double>* pInputExtendedGrid = GridExtender<double>::MirrorBorder( pInputGrid, borderWidth, borderWidth);

   int width = pInputExtendedGrid->GetWidth();
   int height = pInputExtendedGrid->GetHeight();

   ArrayGrid<double>* pPSF = GridGenerator::GenerateGaussian ( width, height, sigma, sigma);
   
   ArrayGrid<double>* pConvolvedGrid = FFT::Convolve( pInputExtendedGrid, pPSF);

   delete pInputExtendedGrid;
   delete pPSF;
   
   ArrayGrid<double>* pCroppedGrid = GridExtender<double>::CropBorder( pConvolvedGrid, borderWidth, borderWidth);
   
   delete pConvolvedGrid;
   return pCroppedGrid;
}

//---------------------------------------------------------------------------------------

image::ArrayGrid<double>* FFT::SuppressOuterFrequencies( image::ArrayGrid<double>* pInputGrid )
{
   int width = pInputGrid->GetWidth();
   int height = pInputGrid->GetHeight();
   ArrayGrid<double>* pTransferFunctionH0 = TransferFunctionGenerator::GenerateLowPassTransferFunction( width, height, 0.15 * width, 0.45 * width );
   return FFT::ApplyTransferFunctionSpatial( pInputGrid, pTransferFunctionH0 );
}

//======================================================================================================

//////////////////////////////////////////////////////////////////
//                                                              //
// 3) APPLY TRANSFER FUNCTION VARIANTS                          //
//       Different possible inputs;                             //
//       output is complex-valued but in the spatial domain!!   //
//                                                              //
//////////////////////////////////////////////////////////////////

FFTBand* FFT::ApplyTransferFunction(FFTBand* pFFTImageData, FFTBand* pTransferFunction)
{
   if (    (pFFTImageData != 0)        && ( pTransferFunction != 0) 
        && (pFFTImageData->GetWidth()  == pTransferFunction->GetWidth())
        && (pFFTImageData->GetHeight() == pTransferFunction->GetHeight())
      )
   {
      int width  = pFFTImageData->GetWidth();
      int height = pFFTImageData->GetHeight();
      int nrPixels = width * height;
   
      FFTBand* pBandpassedData = new FFTBand(width, height);       // create a complex valued image to write output to
      
      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x++)
         {
            complex<double> myFactor = pTransferFunction->GetValue(x, y) / ( (double)(nrPixels) );
            complex<double> ttt = pFFTImageData->GetValue(x, y) * myFactor;

            pBandpassedData->SetValue(x, y, ttt);
         }
      }
      
      pBandpassedData->ApplyInverseTransform();
      pBandpassedData->SwitchQuadrants();
   
      return pBandpassedData;
   }
   else
   {
      if (pFFTImageData == 0)
      {
         cerr << "Input data in fourier domain 0; not able to execute ApplyTransferFunction" << endl << flush;
      }
      if (pTransferFunction == 0) 
      {
         cerr << "Input transfer function 0; not able to execute ApplyTransferFunction" << endl << flush;
      }
      if (pFFTImageData->GetWidth() != pTransferFunction->GetWidth())
      {
         cerr << "Width of input data (= " << pFFTImageData->GetWidth() 
          << ") and transfer function (= " << pTransferFunction->GetWidth() 
          << ") not equal; not able to execute ApplyTransferFunction" << endl << flush;
      }
      if (pFFTImageData->GetHeight() != pTransferFunction->GetHeight())
      {
         cerr << "Height of input data (= " << pFFTImageData->GetHeight() 
          << ") and transfer function (= " << pTransferFunction->GetHeight() 
          << ") not equal; not able to execute ApplyTransferFunction" << endl << flush;
      }
      return 0;
   }
}


//======================================================================================================

FFTBand* FFT::ApplyTransferFunction( FFTBand* pFFTImageData, ArrayGrid<double>* transferFunction )
{
   FFTBand* pFFTTransferFunction = new FFTBand( transferFunction );
   
   FFTBand* pFilteredGrid = ApplyTransferFunction( pFFTImageData, pFFTTransferFunction);
   delete pFFTTransferFunction;
   return pFilteredGrid;
}

//======================================================================================================

/////////////////////////////////////////////////////////////////////
//                                                                 //
// 4) APPLY TRANSFER FUNCTION FFT VARIANTS                         //
//       Different possible inputs;                                //
//       output is complex-valued and still in the Fourier domain  //
//                                                                 //
/////////////////////////////////////////////////////////////////////

FFTBand* FFT::ApplyTransferFunctionFFT( ArrayGrid<double>* pInputGrid, FFTBand* transferFunction )
{
   if (    ( pInputGrid != 0) && (transferFunction != 0) 
        && ( pInputGrid->GetWidth() == transferFunction->GetWidth())
        && ( pInputGrid->GetHeight() == transferFunction->GetHeight())
      )
   {
      FFTBand* pFFTImageData = new FFTBand( pInputGrid );
      pFFTImageData->ApplyForwardTransform();
      
      int width  = pInputGrid->GetWidth();
      int height = pInputGrid->GetHeight();
      
      double imSize = (double)(width) * (double)(height);
   
      FFTBand* pBandpassedData = new FFTBand(width, height);       // create a complex valued image to write output to
      
      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x++)
         {
            complex<double> tmpValue = pFFTImageData->GetValue(x, y) * transferFunction->GetValue(x, y);
            pBandpassedData->SetValue(x, y, (tmpValue / imSize ) );
         }
      }
      
      delete pFFTImageData;
   
      return pBandpassedData;
   }
   else
   {
      if ( pInputGrid == 0)
      {
         cerr << "Input data in fourier domain 0; not able to execute ApplyTransferFunction" << endl << flush;
      }
      if ( transferFunction == 0) 
      {
         cerr << "Input transfer function 0; not able to execute ApplyTransferFunction" << endl << flush;
      }
      if ( pInputGrid->GetWidth() != transferFunction->GetWidth())
      {
         cerr << "Width of input data and transfer function not equal; not able to execute ApplyTransferFunction" << endl << flush;
      }
      if ( pInputGrid->GetHeight() != transferFunction->GetHeight())
      {
         cerr << "Height of input data and transfer function not equal; not able to execute ApplyTransferFunction" << endl << flush;
      }
      return 0;
   }
}

//======================================================================================================

FFTBand* FFT::ApplyTransferFunctionFFT( ArrayGrid< complex<double> >* pInputGrid, FFTBand* transferFunction )
{
   if (    ( pInputGrid != 0) && (transferFunction != 0) 
        && ( pInputGrid->GetWidth() == transferFunction->GetWidth())
        && ( pInputGrid->GetHeight() == transferFunction->GetHeight())
      )
   {
      FFTBand* pFFTImageData = new FFTBand( pInputGrid );
      pFFTImageData->ApplyForwardTransform();
      
      int width  = pInputGrid->GetWidth();
      int height = pInputGrid->GetHeight();
      
      double imSize = (double)(width) * (double)(height);
   
      FFTBand* pBandpassedData = new FFTBand(width, height);       // create a complex valued image to write output to
      
      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x++)
         {
            complex<double> tmpValue = pFFTImageData->GetValue(x, y) * transferFunction->GetValue(x, y);
            pBandpassedData->SetValue(x, y, (tmpValue / imSize ) );
         }
      }
      
      delete pFFTImageData;
   
      return pBandpassedData;
   }
   else
   {
      if ( pInputGrid == 0)
      {
         cerr << "Input data in fourier domain 0; not able to execute ApplyTransferFunction" << endl << flush;
      }
      if ( transferFunction == 0) 
      {
         cerr << "Input transfer function 0; not able to execute ApplyTransferFunction" << endl << flush;
      }
      if ( pInputGrid->GetWidth() != transferFunction->GetWidth())
      {
         cerr << "Width of input data and transfer function not equal; not able to execute ApplyTransferFunction" << endl << flush;
      }
      if ( pInputGrid->GetHeight() != transferFunction->GetHeight())
      {
         cerr << "Height of input data and transfer function not equal; not able to execute ApplyTransferFunction" << endl << flush;
      }
      return 0;
   }
}

//======================================================================================================

FFTBand* FFT::ApplyTransferFunctionFFT( ArrayGrid<double>* pInputGrid, ArrayGrid<double>* transferFunction )
{
   FFTBand* pFFTTransferFunction = new FFTBand( transferFunction );
   
   FFTBand* pFilteredBand = ApplyTransferFunctionFFT( pInputGrid, pFFTTransferFunction );
   delete pFFTTransferFunction;
   return pFilteredBand;
}

//======================================================================================================

/////////////////////////////////////////////////////////////////////
//                                                                 //
// 5) APPLY TRANSFER FUNCTION FFT VARIANTS                         //
//       Real-valued spatial domain input                          //
//       output is real-valued and in the spatial domain           //
//                                                                 //
/////////////////////////////////////////////////////////////////////

ArrayGrid<double>* FFT::ApplyTransferFunctionSpatial( ArrayGrid<double>* pInputGrid, ArrayGrid<double>* transferFunction, FFTDataType dataType)
{
   FFTBand* pOutFFTBand = ApplyTransferFunctionFFT( pInputGrid, transferFunction );
   pOutFFTBand->ApplyInverseTransform();
   ArrayGrid<double>* pOutGrid = 0;
   
   switch(dataType)
   {
      case IM:
      {
         pOutGrid = pOutFFTBand->ConvertToImaginaryGrid( );
         break;
      }
      default:
      {
         pOutGrid = pOutFFTBand->ConvertToRealGrid( );
         break;
      }
   }
   delete pOutFFTBand;
   pOutGrid->SwitchQuadrants();
   return pOutGrid;
}

//======================================================================================================

std::pair<ArrayGrid<double>*, ArrayGrid<double>*> FFT::ApplyTransferFunctionSpatialComplex( ArrayGrid<double>* pInputGrid, ArrayGrid<double>* transferFunction)
{
   FFTBand* pOutFFTBand = ApplyTransferFunctionFFT( pInputGrid, transferFunction );
   pOutFFTBand->ApplyInverseTransform();
   ArrayGrid<double>* pOutGridReal = pOutFFTBand->ConvertToRealGrid( );
   ArrayGrid<double>* pOutGridImag = pOutFFTBand->ConvertToImaginaryGrid( );
   
   pOutGridReal->SwitchQuadrants();
   pOutGridImag->SwitchQuadrants();
   
   std::pair<ArrayGrid<double>*, ArrayGrid<double>*> p(pOutGridReal, pOutGridImag);
   delete pOutFFTBand;
   return p;
}

//============================================================================================

}
}
