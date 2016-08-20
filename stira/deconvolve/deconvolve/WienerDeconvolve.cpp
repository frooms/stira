
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

#include "WienerDeconvolve.h"

#include "../../common/common/StiraMacros.h"
#include "../../imagetools/tools/ImageIO.h"
#include "../../fouriertools/fouriertools/FFTBand.h"
#include "../../fouriertools/fouriertools/FFT.h"
#include "../../filter/filter/GaussConvolve.h"

namespace stira{
namespace deconvolve{

#define THRESHOLD 0.01

using namespace std;
using namespace imagedata;
using namespace imagetools;
using namespace filter;
using namespace fouriertools;

WienerDeconvolve::WienerDeconvolve( Image* pDegradedImage ) : DeconvolveMaster( pDegradedImage )
{
}

//--------------------------------------------------------------------------

WienerDeconvolve::WienerDeconvolve( Image* pDegradedImage, Image* pPSF ) : DeconvolveMaster( pDegradedImage, pPSF )
{
}

//--------------------------------------------------------------------------

WienerDeconvolve::~WienerDeconvolve( )
{
}

//--------------------------------------------------------------------------

bool WienerDeconvolve::IsReadyToRun()
{
   return AreParentConditionsOK();
}

//--------------------------------------------------------------------------

ArrayGrid<double>* WienerDeconvolve::EstimateIdealSpectrum( FFTBand* pFFTInputGrid, FFTBand* pFFTPSFGrid, double noiseLevel )
{
   int width  = pFFTInputGrid->GetWidth();
   int height = pFFTInputGrid->GetHeight();
   bool needInitialisation = true;
   double initialRealValue = 0.0;
   ArrayGrid<double>* pEstimatedIdealSpectrum = new ArrayGrid<double>( width, height, needInitialisation, initialRealValue );
   double fourierNoiseLevel = width * height * noiseLevel * noiseLevel;
   
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         double spectrumDegraded = std::norm( pFFTInputGrid->GetValue( x, y ) );  // norm is square of magnitude
         double spectrumPsf      = std::norm(   pFFTPSFGrid->GetValue( x, y ) ); // norm is square of magnitude
         double estimatedValue = THRESHOLD;
         double differenceValue = spectrumDegraded - fourierNoiseLevel;
         if (( spectrumPsf > THRESHOLD) && (differenceValue > 0.0 ))
         {
            estimatedValue = differenceValue / spectrumPsf;
         }
         pEstimatedIdealSpectrum->SetValue( x, y, estimatedValue );
      }
   }
   
   ArrayGrid<double>* pSmoothSpectrum = GaussConvolve::ConvolveSeparable(pEstimatedIdealSpectrum, 1.5);
   delete pEstimatedIdealSpectrum;
   return pSmoothSpectrum;
}

//--------------------------------------------------------------------------

ArrayGrid<double>* WienerDeconvolve::RunSingleband( ArrayGrid<double>* pInGrid, ArrayGrid<double>* pInPSF, double noiseLevel )
{
   int width  = pInGrid->GetWidth();
   int height = pInGrid->GetHeight();

   FFTBand* pFFTInputGrid = new FFTBand( pInGrid );
   FFTBand* pFFTPSFGrid   = new FFTBand( pInPSF );
   FFTBand* pWienerOut    = new FFTBand( pInGrid );
   
   pFFTInputGrid->ApplyForwardTransform();
   pFFTPSFGrid->ApplyForwardTransform();
   
   ArrayGrid<double>* pEstimatedIdealSpectrum = EstimateIdealSpectrum( pFFTInputGrid, pFFTPSFGrid, noiseLevel );
   double fourierNoiseLevel = width * height * noiseLevel * noiseLevel;
   pFFTPSFGrid->Conjugate();
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         complex<double> wienerEstimate = 
                             (   ( pFFTPSFGrid->GetValue(x, y) * pFFTInputGrid->GetValue(x, y) )
                               / (     POWER2( abs( pFFTPSFGrid->GetValue( x, y ) ) )
                                   + ( fourierNoiseLevel / pEstimatedIdealSpectrum->GetValue(x, y) )
                                 )
                             );
         wienerEstimate /= (width * height);
         pWienerOut->SetValue( x, y, wienerEstimate );
      }
   }
   pWienerOut->ApplyInverseTransform();
   
   ArrayGrid<double>* pRestoredGrid = pWienerOut->ConvertToRealGrid();

   delete pEstimatedIdealSpectrum;

   delete pFFTInputGrid;
   delete pFFTPSFGrid;
   delete pWienerOut;
   return pRestoredGrid;
}

//--------------------------------------------------------------------------

bool WienerDeconvolve::Run()
{
   if (IsReadyToRun() )
   {
      int width  = mpDegradedImage->GetWidth();
      int height = mpDegradedImage->GetHeight();
      int nrbands = mpDegradedImage->GetNumberOfBands();
      mpRestoredImage = new Image( width, height );
      std::string outName = mpDegradedImage->GetImageName() + std::string("-Wiener");
      mpRestoredImage->SetImageName(outName);
      
      if ( mpPSF->GetNumberOfBands() != nrbands )
      {
         for (int i = 0; i < nrbands; i++)
         {
            ArrayGrid<double>* pRestoredBand = RunSingleband( mpDegradedImage->GetBands()[i], mpPSF->GetBands()[0], GetSigmaNoise() );
            mpRestoredImage->AddBand( pRestoredBand );
         }
      }
      else
      {
         for (int i = 0; i < nrbands; i++)
         {
            ArrayGrid<double>* pRestoredBand = RunSingleband( mpDegradedImage->GetBands()[i], mpPSF->GetBands()[i], GetSigmaNoise() );
            mpRestoredImage->AddBand( pRestoredBand );
         }
      }
      return true;
   }
   else
   {
      cerr << "Wiener initial conditions not fulfilled to start running" << endl << flush;
      return false;
   }
}

//--------------------------------------------------------------------------

}
}
