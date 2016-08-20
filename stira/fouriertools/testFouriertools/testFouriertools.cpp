
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

#include "testFouriertools.h"
#include "../fouriertools/TransferFunctionGenerator.h"
#include "../../imagetools/tools/ImageIO.h"
#include "../../imagetools/imagegenerator/GridGenerator.h"
#include "../../imagedata/simpletools/GridStatistics.h"

using namespace std;
using namespace stira;
using namespace stira::fouriertools;
using namespace stira::imagedata;
using namespace stira::imagetools;

//======================================================================================

bool FFTHighPassTest( ArrayGrid<double>* pSourceGrid )
{
   FFTBand* pFFTDataBand = new FFTBand( pSourceGrid );

   assert(pFFTDataBand != 0);
   assert(pFFTDataBand->GetWidth() == pSourceGrid->GetWidth());
   assert(pFFTDataBand->GetHeight() == pSourceGrid->GetHeight());

   pFFTDataBand->ApplyForwardTransform();

   ArrayGrid<double>* pHPTransferFunction = TransferFunctionGenerator::GenerateHighPassTransferFunction( pSourceGrid->GetWidth(), pSourceGrid->GetHeight(), 32, 64);
   ImageIO::WritePGM( pHPTransferFunction, "HPTransferFunctionTest.ppm", ImageIO::GRADIENT_OUT );
   FFTBand* pFFTFilteredBand = FFT::ApplyTransferFunction( pFFTDataBand, pHPTransferFunction );

   delete pFFTDataBand;
   delete pHPTransferFunction;

   ArrayGrid<double>* pHPFilteredGrid = pFFTFilteredBand->ConvertToRealGrid();
   delete pFFTFilteredBand;

   ImageIO::WritePGM( pHPFilteredGrid, "HPFilteeredImageTest.ppm", ImageIO::NORMAL_OUT);

   delete pHPFilteredGrid;
   return true;
}

//======================================================================================================

bool FFTLowPassTest( ArrayGrid<double>* pSourceGrid )
{
   FFTBand* pFFTDataBand = new FFTBand( pSourceGrid );
   pFFTDataBand->ApplyForwardTransform();

   ArrayGrid<double>* pLPTransferFunction = TransferFunctionGenerator::GenerateLowPassTransferFunction( pSourceGrid->GetWidth(), pSourceGrid->GetHeight(), 32, 64 );
   ImageIO::WritePGM( pLPTransferFunction, string("FFT-LPtransfertest.txt"));
   FFTBand* pFFTFilteredBand = FFT::ApplyTransferFunction( pFFTDataBand, pLPTransferFunction );
   delete pFFTDataBand;
   delete pLPTransferFunction;

   ArrayGrid<double>* pLPFilteredGrid = pFFTFilteredBand->ConvertToRealGrid();
   delete pFFTFilteredBand;

   ImageIO::WritePGM( pLPFilteredGrid, string("LPTest.ppm"), ImageIO::NORMAL_OUT);

   delete pLPFilteredGrid;
   return true;
}

//======================================================================================================

bool FFTAxialTest( ArrayGrid<double>* pSourceGrid )
{
   FFTBand* pFFTDataBand = new FFTBand( pSourceGrid );
   pFFTDataBand->ApplyForwardTransform();

   int width  = pSourceGrid->GetWidth();
   int height = pSourceGrid->GetHeight();
   int axisWidth = 1;
   double innerRadius = 15;
   double outerRadius = width / 2 - 1;

   ArrayGrid<double>* pLPTransferFunction = TransferFunctionGenerator::GenerateAxisSuppressTransferFunction( width, height, axisWidth, innerRadius, outerRadius );
   ImageIO::WritePGM( pLPTransferFunction, string("AxialTest.pgm"));
   FFTBand* pFFTFilteredBand = FFT::ApplyTransferFunction( pFFTDataBand, pLPTransferFunction );
   delete pFFTDataBand;
   delete pLPTransferFunction;

   ArrayGrid<double>* pLPFilteredGrid = pFFTFilteredBand->ConvertToRealGrid();
   delete pFFTFilteredBand;

   ImageIO::WritePGM( pLPFilteredGrid, string("AxialTest.ppm"), ImageIO::NORMAL_OUT);

   delete pLPFilteredGrid;
   return true;
}

//======================================================================================================

bool FFTAxialExtractTest( ArrayGrid<double>* pSourceGrid )
{
   FFTBand* pFFTDataBand = new FFTBand( pSourceGrid );
   pFFTDataBand->ApplyForwardTransform();

   int width  = pSourceGrid->GetWidth();
   int height = pSourceGrid->GetHeight();
   int axisWidth = 4;

   ArrayGrid<double>* pLPTransferFunction = TransferFunctionGenerator::GenerateAxisExtractTransferFunction( width, height, axisWidth );
   ImageIO::WritePGM( pLPTransferFunction, string("AxialTransferFunctionY.pgm"));
   FFTBand* pFFTFilteredBand = FFT::ApplyTransferFunction( pFFTDataBand, pLPTransferFunction );
   delete pFFTDataBand;
   delete pLPTransferFunction;

   ArrayGrid<double>* pLPFilteredGrid = pFFTFilteredBand->ConvertToRealGrid();
   delete pFFTFilteredBand;

   ImageIO::WritePGM( pLPFilteredGrid, string("AxialExtractResultY.ppm"), ImageIO::NORMAL_OUT);

   delete pLPFilteredGrid;
   return true;
}

//======================================================================================================

bool FFTApplySetOfTransferFunctionsTest( ArrayGrid<double>* pSourceGrid )
{
   ImageIO io;
   FFTBand* pFFTDataBand = new FFTBand( pSourceGrid );
   pFFTDataBand->ApplyForwardTransform();
   common::NumberMode myMode = common::MODE_REAL;

   ArrayGrid<double>* pBPFilteredGrid;

   int orientationIndex = 0;
   int maxNrOfOrientations = 12;

   ArrayGrid<double>* pHPTransferFunction = TransferFunctionGenerator::GenerateHighPassTransferFunction( pSourceGrid->GetWidth(), pSourceGrid->GetHeight(), 32, 64 );

   FFTBand* pBPTransferFunction = TransferFunctionGenerator::GenerateOrientedTransferFunction( pSourceGrid->GetWidth(), pSourceGrid->GetHeight(), orientationIndex, maxNrOfOrientations, myMode);
   pBPTransferFunction->Multiply( pHPTransferFunction ); delete pHPTransferFunction;
   TransferFunctionGenerator::HighFrequencyCrossMask( pBPTransferFunction, maxNrOfOrientations );

   FFTBand* pFFTFilteredBand = FFT::ApplyTransferFunction( pFFTDataBand, pBPTransferFunction );
   if (maxNrOfOrientations % 2 == 0)
   {
      pBPFilteredGrid = pFFTFilteredBand->ConvertToImaginaryGrid();
   }
   else
   {
      pBPFilteredGrid = pFFTFilteredBand->ConvertToRealGrid();
   }

   ImageIO::WritePGM( pBPFilteredGrid, string("TransferFunctionSetTest.ppm"), ImageIO::GRADIENT_OUT);
   delete pFFTDataBand;
   delete pFFTFilteredBand;
   delete pBPFilteredGrid;
   delete pBPTransferFunction;
   return true;
}

//======================================================================================================

bool FFTForwardInverseTest( ArrayGrid<double>* pSourceGrid)
{
   int width = pSourceGrid->GetWidth();
   int height = pSourceGrid->GetHeight();
   int nrPixels = width * height;

   FFTBand* pFFTDataBand = new FFTBand( pSourceGrid );

   pFFTDataBand->ApplyForwardTransform();

   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         complex<double> complexValue = pFFTDataBand->GetValue(x, y) / (double)(nrPixels);
         pFFTDataBand->SetValue(x, y, complexValue);
      }
   }

   pFFTDataBand->ApplyInverseTransform();

   pFFTDataBand->SwitchQuadrants();

   bool needInitialisation = true;
   double initialRealValue = 0.0;
   ArrayGrid<double>* pReconstGrid = new ArrayGrid<double>( width, height, needInitialisation, initialRealValue );

   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         pReconstGrid->SetValue(x, y, (pFFTDataBand->GetValue(x, y).real() ));
      }
   }

   ImageIO::WritePGM( pReconstGrid, string("FFTDecompReconstTest.ppm"), ImageIO::NORMAL_OUT);
   delete pFFTDataBand;
   delete pReconstGrid;
   return true;
}

//======================================================================================================

bool FFTSpectrumTest( ArrayGrid<double>* pSourceGrid)
{
   ArrayGrid<double>* pSpectrum = FFT::ComputePowerSpectrum( pSourceGrid );

   assert(pSpectrum != 0);
   ImageIO::WritePGM(pSpectrum, "SpectrumTest.ppm", ImageIO::NORMAL_OUT);

   delete pSpectrum;
   return true;
}

//======================================================================================================

bool FFTNoiseSpectrumTest( int width, int height, double sigma )
{
   ArrayGrid<double>* pGridNoise = GridGenerator::GenerateEmptyPlusGaussianNoise( width, height, 0.0, sigma);
   ArrayGrid<double>* pSpectrum = FFT::ComputePowerSpectrum( pGridNoise );

   double average  = GridStatistics<double>::GetGridMean( pSpectrum );

   double fourierNoiseLevel = (width * height * sigma * sigma);

   cout << "\tThe spectrum mean = " << average << " and thearetically = " << fourierNoiseLevel
        << " so diff = " << fabs(fourierNoiseLevel - average) << endl << flush;

   delete pSpectrum;
   return true;
}

//======================================================================================================

bool LogGaborTest( ArrayGrid<double>* pSourceGrid)
{
   int width  = pSourceGrid->GetWidth();
   int height = pSourceGrid->GetHeight();

   double centerFrequency = width / 5.0;
   double radialWidth = 1.25;
   double centerAngle = 0.7;
   double angleSpread = 0.3;
   ArrayGrid<double>* pLogGaborTransferFunction = TransferFunctionGenerator::GenerateLogGaborBandTransferFunction( width, height, centerFrequency, radialWidth, centerAngle, angleSpread);
   assert( pLogGaborTransferFunction != 0 );

   std::pair< ArrayGrid<double>*, ArrayGrid<double>*> pComplexGridPair = FFT::ApplyTransferFunctionSpatialComplex( pSourceGrid, pLogGaborTransferFunction );
   assert( pComplexGridPair.first != 0);
   assert( pComplexGridPair.second != 0);
   ImageIO::WritePGM( pComplexGridPair.first, "LogGaborFiltered_RE.ppm", ImageIO::GRADIENT_OUT);
   ImageIO::WritePGM( pComplexGridPair.second, "LogGaborFiltered_IM.ppm", ImageIO::GRADIENT_OUT);

   delete pComplexGridPair.first;
   delete pComplexGridPair.second;
   pLogGaborTransferFunction->SwitchQuadrants();
   ImageIO::WritePGM( pLogGaborTransferFunction, "LogGaborTransferFunction.ppm", ImageIO::NORMAL_OUT );
   delete pLogGaborTransferFunction;
   return true;
}

//======================================================================================================

bool SuppressOuterFrequenciesTest( ArrayGrid<double>* pSourceGrid)
{
   ArrayGrid<double>* pFilteredGrid = FFT::SuppressOuterFrequencies( pSourceGrid );

   ImageIO::WritePGM( pFilteredGrid, "SuppressOuterFrequencies.pgm", ImageIO::NORMAL_OUT );
   ArrayGrid<double>* pSpectrum =  FFT::ComputeLogPowerSpectrum( pFilteredGrid );
   ImageIO::WritePGM( pSpectrum, "SuppressOuterFrequenciesSpectrum.pgm", ImageIO::NORMAL_OUT );

   delete pFilteredGrid;
   delete pSpectrum;
   return true;
}

//======================================================================================================

int main()
{
   Image* pImage = 0;
   //string fileNamePGM("../../../../stira/stira/testdata/lena256.pgm");
   string fileNamePGM("../../../../stira/stira/testdata/blackman.png");

   pImage = ImageIO::Read( fileNamePGM );

   //cout << "Tests FFT (2D)" << endl << flush;

   ArrayGrid<double>* pInputGrid = pImage->GetBands()[0];

   cout << "FFTAxialTest";
   if ( FFTAxialTest( pInputGrid ) )
   {
      cout << "\t\tOK!" << endl << flush;
   }
   else
   {
      cout << "\t\tFAILED!" << endl << flush;
   }

   cout << "FFTSpectrumTest:";
   if ( FFTSpectrumTest( pInputGrid ) )
   {
      cout << "\tOK!" << endl << flush;
   }
   else
   {
      cout << "\tFAILED!" << endl << flush;
   }

   cout << "FFTSpectrumTest:";
   if ( FFTAxialExtractTest( pInputGrid ) )
   {
      cout << "\tOK!" << endl << flush;
   }
   else
   {
      cout << "\tFAILED!" << endl << flush;
   }

   cout << "FFTForwardInverseTest:";
   if ( FFTForwardInverseTest( pInputGrid ) )
   {
      cout << "\tOK!" << endl << flush;
   }
   else
   {
      cout << "\tFAILED!" << endl << flush;
   }

   cout << "FFTHighPassTest:";
   if ( FFTHighPassTest( pInputGrid ) )
   {
      cout << "\tOK!" << endl << flush;
   }
   else
   {
      cout << "\tFAILED!" << endl << flush;
   }

   cout << "FFTLowPassTest:";
   if ( FFTLowPassTest( pInputGrid ) )
   {
      cout << "\t\tOK!" << endl << flush;
   }
   else
   {
      cout << "\t\tFAILED!" << endl << flush;
   }

   cout << "FFTApplySetOfTransferFunctionsTest:";
   if ( FFTApplySetOfTransferFunctionsTest( pInputGrid ) )
   {
      cout << "\tOK!" << endl << flush;
   }
   else
   {
      cout << "\tFAILED!" << endl << flush;
   }

   cout << "SuppressOuterFrequenciesTest:";
   if ( SuppressOuterFrequenciesTest( pInputGrid ) )
   {
      cout << "\tOK!" << endl << flush;
   }
   else
   {
      cout << "\tFAILED!" << endl << flush;
   }

   cout << "LogGaborTest:";
   if ( LogGaborTest( pInputGrid ) )
   {
      cout << "\t\tOK!" << endl << flush;
   }
   else
   {
      cout << "\t\tFAILED!" << endl << flush;
   }

   int width = 256;
   int height = 256;
   double sigma = 10.0;

   cout << "FFTNoiseSpectrumTest:";
   if ( FFTNoiseSpectrumTest( width, height, sigma ) )
   {
      cout << "\tOK!" << endl << flush;
   }
   else
   {
      cout << "\tFAILED!" << endl << flush;
   }

   delete pImage;
}
