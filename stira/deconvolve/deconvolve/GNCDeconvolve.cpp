
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

#include "GNCDeconvolve.h"
#include "../../image/tools/NumberGridTools.h"
#include "../../fouriertools/fouriertools/FFT.h"
#include "../../fouriertools/fouriertools/FFTBand.h"
#include "../../wavelet/wavelet/NoiseEstimator.h"
#include "../../pyramidapplications/pyramidapplications/PyramidDenoiser.h"

#define S_BORDER 2
#define OLD_POTENTIALS true
//#define OLD_ACTIVITY_CONTRIB true

#define DIAGNOSE_GNC

namespace stira{
namespace deconvolve{

using namespace image;
using namespace fouriertools;
using namespace steerable;
using namespace std;
using namespace wavelet;
using namespace pyramidapplications;

//--------------------------------------------------------------------------

common::Point<int> pointLeft(-1, 0), pointRight(1, 0), pointTop(0, -1), pointBottom(0, 1), pointTopLeft(-1, -1), pointBottomLeft(-1, 1), pointTopRight(1, -1), pointBottomRight(1, 1);

common::Point<int> nMin2Min2( -2, -2), nMin2Min1( -2, -1), nMin2Null( -2, 0), nMin2Plus1( -2, 1), nMin2Plus2( -2, 2);
common::Point<int> nMin1Min2( -1, -2), nMin1Min1( -1, -1), nMin1Null( -1, 0), nMin1Plus1( -1, 1), nMin1Plus2( -1, 2);
common::Point<int> nNullMin2(  0, -2), nNullMin1(  0, -1), nNullNull(  0, 0), nNullPlus1(  0, 1), nNullPlus2(  0, 2);
common::Point<int> nPlus1Min2( 1, -2), nPlus1Min1( 1, -1), nPlus1Null( 1, 0), nPlus1Plus1( 1, 1), nPlus1Plus2( 1, 2);
common::Point<int> nPlus2Min2( 2, -2), nPlus2Min1( 2, -1), nPlus2Null( 2, 0), nPlus2Plus1( 2, 1), nPlus2Plus2( 2, 2);

//--------------------------------------------------------------------------

GNCDeconvolve::GNCDeconvolve( image::Image* pDegradedImage, int maxNrOfIterations )
                           : IterativeDeconvolve( pDegradedImage, maxNrOfIterations )
{
   InitializeParameters();
}

//--------------------------------------------------------------------------

GNCDeconvolve::GNCDeconvolve( image::Image* pDegradedImage, image::Image* pPSF, int maxNrOfIterations )
                           : IterativeDeconvolve( pDegradedImage, pPSF, maxNrOfIterations )
{
   InitializeParameters();
}

//--------------------------------------------------------------------------

GNCDeconvolve::~GNCDeconvolve( )
{
}

//--------------------------------------------------------------------------

void GNCDeconvolve::InitializeParameters()
{
   mpBlurredLastEstimateGrid = 0;
   
   mMu = 1.0;
   mLambda = 1.0;
   mUpdateFactor = 0.9;
   mMSEDifferenceThreshold = 0.1;
}

//--------------------------------------------------------------------------

void GNCDeconvolve::PrintParameters()
{
   cout << "Current Gamma = " << mGamma << endl << flush;
   cout << "Final Gamma   = " << mGammaFinal << endl << flush;
   
   cout << "NumberOfScales = " << mNumberOfScales << endl << flush;
   cout << "NumberOfOrientations = " << mNumberOfOrientations << endl << flush;
}

//--------------------------------------------------------------------------

int GNCDeconvolve::GetNumberOfScales()
{
   return mNumberOfScales;
}

//--------------------------------------------------------------------------

void GNCDeconvolve::SetNumberOfScales(int nrScales)
{
   mNumberOfScales = nrScales;
}

//--------------------------------------------------------------------------

int GNCDeconvolve::GetNumberOfOrientations()
{
   return mNumberOfOrientations;
}

//--------------------------------------------------------------------------

void GNCDeconvolve::SetNumberOfOrientations(int nrOrientations)
{
   mNumberOfOrientations = nrOrientations;
}

//--------------------------------------------------------------------------

double GNCDeconvolve::ComputeInteractionFunction( double x )
{
   return (1.0 / (fabs(x / mGamma)));
}

//--------------------------------------------------------------------------

double GNCDeconvolve::GetMu()
{
   return mMu;
}

//--------------------------------------------------------------------------

void GNCDeconvolve::SetMu(double newMu)
{
   mMu = newMu;
}

//--------------------------------------------------------------------------

double GNCDeconvolve::GetLambda()
{
   return mLambda;
}

//--------------------------------------------------------------------------

void GNCDeconvolve::SetLambda(double newLambda)
{
   mLambda = newLambda;
}

//--------------------------------------------------------------------------


double GNCDeconvolve::GetUpdateFactor()
{
   return mUpdateFactor;
}

//--------------------------------------------------------------------------

void GNCDeconvolve::SetUpdateFactor(double newFactor)
{
   mUpdateFactor = newFactor;
}

//--------------------------------------------------------------------------

double GNCDeconvolve::GetGamma()
{
   return mGamma;
}

//--------------------------------------------------------------------------

void GNCDeconvolve::SetGamma(double newGamma)
{
   mGamma = newGamma;
}

//--------------------------------------------------------------------------

double GNCDeconvolve::GetGammaFinal()
{
   return mGammaFinal;
}

//--------------------------------------------------------------------------

void GNCDeconvolve::SetGammaFinal(double newGammaFinal)
{
   mGammaFinal = newGammaFinal;
}

//--------------------------------------------------------------------------

void GNCDeconvolve::SetMSEDifferenceThreshold( double myThreshold )
{
   mMSEDifferenceThreshold = myThreshold;
}

//--------------------------------------------------------------------------

double GNCDeconvolve::GetMSEDifferenceThreshold()
{
   return mMSEDifferenceThreshold;
}

//--------------------------------------------------------------------------

double GNCDeconvolve::ComputeActivityIndicator( int x, int y )
{
   int windowSize = 7;
   
   double childCoefficient = mpLastEstimateCurrentBand->GetValue( x, y );
   double parentCoefficient = mpLastEstimateCurrentParentBand->GetValue( x/mSubsampleFactor, y/mSubsampleFactor );
   double sigmaSignal = PyramidDenoiser::EstimateSigmaSignal( mpLastEstimateCurrentBand, x, y, mSigmaNoise, windowSize);
   return PyramidDenoiser::ComputeBivariateShrinkagefactor( childCoefficient, parentCoefficient, sigmaSignal, mSigmaNoise);
}

//--------------------------------------------------------------------------

double GNCDeconvolve::GetPotential(int x, int y, common::Point<int> delta)
{
   double activityIndicator = 0.125;//ComputeActivityIndicator( x+delta.GetX(), y+delta.GetY() );
   double differenceValue   = mpLastEstimateCurrentBand->GetValue( x, y ) - mpLastEstimateCurrentBand->GetValue( x+delta.x, y+delta.y );
   return  ( differenceValue * ComputeInteractionFunction( differenceValue ) * activityIndicator );
}

//--------------------------------------------------------------------------

double GNCDeconvolve::GetNeighborhoodPotential( int x, int y )
{
   double totalPotential =   GetPotential( x, y, pointTopLeft )    +  GetPotential( x, y, pointTop )    + GetPotential( x, y, pointTopRight) 
                           + GetPotential( x, y, pointLeft )       +                                      GetPotential( x, y, pointRight) 
                           + GetPotential( x, y, pointBottomLeft ) +  GetPotential( x, y, pointBottom ) + GetPotential( x, y, pointBottomRight);
   return totalPotential;
}

//--------------------------------------------------------------------------

// formula (7.1) in my PhD, very similar to formula (4.51) from the MRF book of Stan Li.
double GNCDeconvolve::GetUpdatedCoefficient( int x, int y, double activityIndex, double totalPotential )
{
   double newValue =         mpLastEstimateCurrentBand->GetValue(x, y) 
                     - mMu * activityIndex * ( mpBlurredLastEstimateCurrentBand->GetValue(x, y) - mpDegradedCurrentBand->GetValue(x, y) )
                     - mLambda * (1.0 - activityIndex) * totalPotential;
   return newValue;
}

//--------------------------------------------------------------------------

void GNCDeconvolve::GNCStep( )
{
   PrepareCurrentSubbandsForIteration( );
   int width = mpLastEstimateCurrentBand->GetWidth();
   int height = mpLastEstimateCurrentBand->GetHeight();
   for (int y = S_BORDER; y < height - S_BORDER; y++)
   {
      for (int x = S_BORDER; x < width - S_BORDER; x++)
      {
         double activityIndex = ComputeActivityIndicator( x, y );
         double totalPotential = GetNeighborhoodPotential( x, y );
         double newValue = GetUpdatedCoefficient( x, y, activityIndex, totalPotential );
         
         mpNewEstimateCurrentBand->SetValue(x, y, newValue );
      }
   }
}

//--------------------------------------------------------------------------

bool GNCDeconvolve::NeedsAnotherIteration( double previousMSE, double currentMSE, int currentIteration )
{
   return ( fabs( previousMSE - currentMSE ) > mMSEDifferenceThreshold) && (currentIteration < mMaximumNrOfIterations);
}

//--------------------------------------------------------------------------

bool GNCDeconvolve::Run()
{
   mCurrentBandNr = 0;
   
   while (mGamma > mGammaFinal)
   {
      double mse     = 100000000000000.0;
      double mselast = 100000000000001.0;
      int iterationCount = 0;
      
      PrepareDataForInitialIteration(); // decomposes the grids into pyramids
      #ifdef DIAGNOSE_GNC
      cout << " mu = " << mMu << " lambda = " << mLambda << " Gamma = " << mGamma << endl << flush;
      cout << "=================================================================" << endl << flush;
      #endif
      while ( NeedsAnotherIteration( mselast, mse, iterationCount ) )
      {
         mSigmaNoise = NoiseEstimator::Run( mpLastGrid ) / 2.0;
         mselast = mse;

         for ( mCurrentScaleNr = mNumberOfScales-2; mCurrentScaleNr >= -1; mCurrentScaleNr--)
         {
            // hard-coded loop over 4 orientations!!! Needed for encoding clique configurations
            ///////////////////////////////////////////////////////////////////////////////////
            for ( mCurrentOrientationNr = 0; mCurrentOrientationNr < mNumberOfOrientations; mCurrentOrientationNr++)
            {
               GNCStep( );
            }
         }
         mpNewEstimatePyramid->Reconstruct();

         delete mpNewSolutionGrid;
         mpNewSolutionGrid = mpNewEstimatePyramid->GetCopyOfReconstructedGrid();
         mselast = mse;
         mse = NumberGridTools<double>::ComputeMSE( mpNewSolutionGrid, mpLastGrid );
         #ifdef DIAGNOSE_GNC
         cout << "Iteration = " << iterationCount << " sigma = " << mSigmaNoise << " MSE = " << mse << endl << flush;
         #endif

         iterationCount ++;

         if ( NeedsAnotherIteration( mselast, mse, iterationCount ) )
         {
            PrepareDataForRecursiveIteration();
         }
      }
      mGamma *= mUpdateFactor;
   }
   mpRestoredImage = new Image( mpNewSolutionGrid->Clone() );
   std::string outName = mpDegradedImage->GetImageName() + std::string("-GNC");
   mpRestoredImage->SetImageName(outName);

   return true;
}
//--------------------------------------------------------------------------

bool GNCDeconvolve::IsReadyToRun()
{
   return AreParentConditionsOK();
}

//--------------------------------------------------------------------------

void GNCDeconvolve::PrepareDataForInitialIteration()
{
   PrepareCurrentGrids( );
   int width = mpDegradedGrid->GetWidth();
   int height =  mpDegradedGrid->GetHeight();
   
   bool needInitialisation = true;
   double initialRealValue = 0.0;
   
   mpNewSolutionGrid = new ArrayGrid<double>( width, height, needInitialisation, initialRealValue );
   
   mpDegradedPyramid = new PyramidReal( mpDegradedGrid, mNumberOfScales, mNumberOfOrientations );
   mpDegradedPyramid->Decompose();
   
   mpLastEstimatePyramid = new PyramidReal( mpLastGrid, mNumberOfScales, mNumberOfOrientations);
   mpLastEstimatePyramid->Decompose();
   
   if (mpBlurredLastEstimateGrid != 0)
   {
      delete mpBlurredLastEstimateGrid;
   }
   mpBlurredLastEstimateGrid = FFT::Convolve( mpLastGrid, mpPSFGrid );
   mpBlurredLastEstimatePyramid = new PyramidReal( mpBlurredLastEstimateGrid, mNumberOfScales, mNumberOfOrientations);
   mpBlurredLastEstimatePyramid->Decompose();
   
   mpNewEstimatePyramid = new PyramidReal( mpDegradedGrid->Clone(), mNumberOfScales, mNumberOfOrientations);
   mpNewEstimatePyramid->Decompose();
}

//--------------------------------------------------------------------------

void GNCDeconvolve::PrepareDataForRecursiveIteration()
{
   PrepareCurrentGrids( );
   NumberGridTools<double>::CopyValues( mpNewSolutionGrid, mpLastGrid );
   
   delete mpNewEstimatePyramid;
   mpNewEstimatePyramid = new PyramidReal( mpLastGrid->Clone(), mNumberOfScales, mNumberOfOrientations);
   mpNewEstimatePyramid->Decompose();
   
   #ifdef DIAGNOSE_GNC
   stringstream ss;
   ss << std::string("GNC-Gamma-") << mGamma <<  std::string("Iteration-") <<  mCurrentIterationNr << std::string(".pgm");
   ImageIO::WritePGM( mpLastGrid, ss.str() );
   #endif
   
   delete mpBlurredLastEstimateGrid;
   mpBlurredLastEstimateGrid = FFT::Convolve( mpLastGrid, mpPSFGrid );
   
   delete mpBlurredLastEstimatePyramid;
   mpBlurredLastEstimatePyramid = new PyramidReal( mpBlurredLastEstimateGrid, mNumberOfScales, mNumberOfOrientations);
   mpBlurredLastEstimatePyramid->Decompose();
}

//--------------------------------------------------------------------------

void GNCDeconvolve::PrepareCurrentSubbandsForIteration( )
{
   //cout << "Preparing bands related with scale nr " << mCurrentScaleNr << " and orientation nr " << mCurrentOrientationNr << endl << flush;
   if (mCurrentScaleNr >= 0)
   {
      mSubsampleFactor = 2;
      mpDegradedCurrentBand = mpDegradedPyramid->GetPyramid()->GetRecursiveScale( mCurrentScaleNr )->GetOrientedBand( mCurrentOrientationNr );
      mpLastEstimateCurrentBand = mpLastEstimatePyramid->GetPyramid()->GetRecursiveScale( mCurrentScaleNr )->GetOrientedBand( mCurrentOrientationNr );
      mpLastEstimateCurrentParentBand = mpLastEstimatePyramid->GetPyramid()->GetRecursiveScale( mCurrentScaleNr+1 )->GetOrientedBand( mCurrentOrientationNr );
      mpBlurredLastEstimateCurrentBand = mpBlurredLastEstimatePyramid->GetPyramid()->GetRecursiveScale( mCurrentScaleNr )->GetOrientedBand( mCurrentOrientationNr );
      mpNewEstimateCurrentBand = mpNewEstimatePyramid->GetPyramid()->GetRecursiveScale( mCurrentScaleNr )->GetOrientedBand( mCurrentOrientationNr );
   }
   else if ( mpDegradedPyramid->GetPyramid()->HasResidualScale() )
   {
      mSubsampleFactor = 1;
      mpDegradedCurrentBand = mpDegradedPyramid->GetPyramid()->GetResidualScale( )->GetOrientedBand( mCurrentOrientationNr );
      mpLastEstimateCurrentBand = mpLastEstimatePyramid->GetPyramid()->GetResidualScale( )->GetOrientedBand( mCurrentOrientationNr );
      mpLastEstimateCurrentParentBand = mpLastEstimatePyramid->GetPyramid()->GetRecursiveScale( 0 )->GetOrientedBand( mCurrentOrientationNr );
      mpBlurredLastEstimateCurrentBand = mpBlurredLastEstimatePyramid->GetPyramid()->GetResidualScale( )->GetOrientedBand( mCurrentOrientationNr );
      mpNewEstimateCurrentBand = mpNewEstimatePyramid->GetPyramid()->GetResidualScale( )->GetOrientedBand( mCurrentOrientationNr );
   }
}

//--------------------------------------------------------------------------

bool GNCDeconvolve::RunSingleIterationSingleBand( )
{
   return true;
}

//--------------------------------------------------------------------------

}
}
