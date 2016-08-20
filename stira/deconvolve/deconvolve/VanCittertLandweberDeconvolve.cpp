
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

#include "VanCittertLandweberDeconvolve.h"
#include "../../fouriertools/fouriertools/FFT.h"
#include "../../fouriertools/fouriertools/FFTBand.h"

namespace stira{
namespace deconvolve{

using namespace fouriertools;
using namespace std;

VanCittertLandweberDeconvolve::VanCittertLandweberDeconvolve( Image* pDegradedImage, int maxNrOfIterations )
                           : IterativeDeconvolve( pDegradedImage, maxNrOfIterations )
{
   mDeconvolutionType = DECONVOLVE_LANDWEBER;
   mFlagEnforcePositivity = true;
}

//--------------------------------------------------------------------------

VanCittertLandweberDeconvolve::VanCittertLandweberDeconvolve( Image* pDegradedImage, Image* pPSF, int maxNrOfIterations )
                           : IterativeDeconvolve( pDegradedImage, pPSF, maxNrOfIterations )
{
   mDeconvolutionType = DECONVOLVE_LANDWEBER;
   mFlagEnforcePositivity = true;
}

//--------------------------------------------------------------------------

VanCittertLandweberDeconvolve::~VanCittertLandweberDeconvolve( )
{
}

//--------------------------------------------------------------------------

void VanCittertLandweberDeconvolve::PrintParameters()
{
   cout << "\t Current iteration nr = " << mCurrentIterationNr << endl << flush;
   cout << "\t Maximum nr of iterations =  " << mMaximumNrOfIterations << endl << flush;
   cout << "\t mpNewEstimate  = " << mpNewEstimate << endl << flush;
   cout << "\t mpCurrentBandNr = " << mCurrentBandNr << endl << flush;
   cout << "\t mLambda = " << mLambda << endl << flush;
   cout << "\t mFlagEnforcePositivity = " << mFlagEnforcePositivity << endl << flush;
   cout << "\t mStepSize = " << mStepSize << endl << flush;
   cout << "\t mDeconvolutionType = " ;
   switch (mDeconvolutionType)
   {
      case DECONVOLVE_VANCITTERT:
      {
         cout << " DECONVOLVE_VANCITTERT " << endl << flush;
         break;
      }
      case DECONVOLVE_LANDWEBER:
      {
         cout << " DECONVOLVE_LANDWEBER" << endl << flush;
         break;
      }
   }
}

//--------------------------------------------------------------------------

void VanCittertLandweberDeconvolve::SetEnforcePositivity(bool flag)
{
   mFlagEnforcePositivity = flag;
}

//--------------------------------------------------------------------------

bool VanCittertLandweberDeconvolve::GetEnforcePositivity()
{
   return mFlagEnforcePositivity;
}

//--------------------------------------------------------------------------;

deconvolutionType VanCittertLandweberDeconvolve::GetDeconvolutionType()
{
   return mDeconvolutionType;
}

//--------------------------------------------------------------------------;

void VanCittertLandweberDeconvolve::SetDeconvolutionType( deconvolutionType myType )
{
   mDeconvolutionType = myType;
}

//--------------------------------------------------------------------------

bool VanCittertLandweberDeconvolve::Run()
{
   std::string outName;
   if (IsReadyToRun() == true)
   {
      PrintParameters();
      for (mCurrentIterationNr = 0; mCurrentIterationNr < mMaximumNrOfIterations; mCurrentIterationNr++)
      {
         cout << "\t iteration " << mCurrentIterationNr << endl << flush;
         for (int mpCurrentBandNr = 0; mpCurrentBandNr < mpDegradedImage->GetNumberOfBands(); mpCurrentBandNr++)
         {
            RunSingleIterationSingleBand( );
         }
      }
      mpRestoredImage = mpNewEstimate->Clone();
      if ( mDeconvolutionType == DECONVOLVE_LANDWEBER )
      {
         outName = mpDegradedImage->GetImageName() + std::string("-Landweber");
      }
      else
      {
         outName = mpDegradedImage->GetImageName() + std::string("-VanCittert");
      }
      mpRestoredImage->SetImageName(outName);
   }
   else
   {
      cerr << "Unable to start RL iterations; return 0 and abort..." << endl << flush;
   }
   return true;
}

//--------------------------------------------------------------------------

bool VanCittertLandweberDeconvolve::ApplyPositivityConstraint( ArrayGrid<double>* pGrid )
{
   int width = pGrid->GetWidth();
   int height = pGrid->GetHeight();
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         if ( pGrid->GetValue( x, y ) < 0.0 ) { pGrid->SetValue( x, y, 0.0); }
      }
   }
   return true;
}

//--------------------------------------------------------------------------;

bool VanCittertLandweberDeconvolve::IsReadyToRun()
{
   return AreParentConditionsOK();
}

//--------------------------------------------------------------------------;

// Van Cittert -> next = previous + lambda x   ( degrad - ( previous * psf) )
// Landweber   -> next = previous + lambda x ( ( degrad - ( previous * psf) ) * psf )
// with "x" for point-by-point multiplication and "*" for convolution
bool VanCittertLandweberDeconvolve::RunSingleIterationSingleBand( )
{
   PrepareCurrentGrids( );

   ArrayGrid<double>* pConvolved = FFT::Convolve( mpNewGrid, mpPSFGrid );
   ArrayGrid<double>* pTmpGrid = mpDegradedGrid->Clone();
   pTmpGrid->SubtractGrid( pConvolved ); delete pConvolved;

   if ( mDeconvolutionType == DECONVOLVE_LANDWEBER )
   {
      pConvolved = FFT::Convolve( pTmpGrid, mpPSFGrid );    delete pTmpGrid;
      pConvolved->MultiplyWith( mStepSize );
   }
   else
   {
      pConvolved = pTmpGrid;
      pConvolved->MultiplyWith( mStepSize / 24.0 );
   }

   mpNewGrid->AddGrid( pConvolved );   delete pConvolved;
   if (mFlagEnforcePositivity == true)
   {
      ApplyPositivityConstraint( mpNewGrid );
   }

   return true;
}

//--------------------------------------------------------------------------;


}
}
