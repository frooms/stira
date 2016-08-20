
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

#include "RichardsonLucyDeconvolve.h"
#include "../../fouriertools/fouriertools/FFT.h"
#include "../../common/common/MathUtils.h"
#include "../../common/common/StiraMacros.h"
#include "../../imagetools/tools/NumberGridTools.h"

#define RL_THRESHOLD 0.00000001

using namespace std;

namespace stira{
namespace deconvolve{

using namespace imagedata;
using namespace imagetools;
using namespace fouriertools;
using namespace common;


RichardsonLucyDeconvolve::RichardsonLucyDeconvolve( Image* pDegradedImage, regularizationType myRegularizationType, int maxNrOfIterations )
                           : IterativeDeconvolve( pDegradedImage, maxNrOfIterations )
{
   mRegularizationType = myRegularizationType;
   mEnforceIntensityRange = true;
}

//--------------------------------------------------------------------------

RichardsonLucyDeconvolve::RichardsonLucyDeconvolve( Image* pDegradedImage, Image* pPSF, regularizationType myRegularizationType, int maxNrOfIterations )
                           : IterativeDeconvolve( pDegradedImage, pPSF, maxNrOfIterations )
{
   mRegularizationType = myRegularizationType;
   mEnforceIntensityRange = true;
}

//--------------------------------------------------------------------------

RichardsonLucyDeconvolve::~RichardsonLucyDeconvolve( )
{
   delete mpLastEstimate;
   delete mpNewEstimate;
}

//--------------------------------------------------------------------------

void RichardsonLucyDeconvolve::SetEnforceIntensityRange( bool flag )
{
   mEnforceIntensityRange = flag;
}

//--------------------------------------------------------------------------

bool RichardsonLucyDeconvolve::GetEnforceIntensityRange()
{
   return mEnforceIntensityRange;
}

//--------------------------------------------------------------------------


//--------------------------------------------------------------------------

void RichardsonLucyDeconvolve::PrintParameters()
{
   cout << "\t Current iteration nr = " << mCurrentIterationNr << endl << flush;
   cout << "\t Maximum nr of iterations =  " << mMaximumNrOfIterations << endl << flush;
   cout << "\t mpLastEstimate = " << mpLastEstimate << endl << flush;
   cout << "\t mpNewEstimate  = " << mpNewEstimate << endl << flush;
   cout << "\t mpCurrentBandNr = " << mCurrentBandNr << endl << flush;
   cout << "\t mLambda = " << mLambda << endl << flush;
   cout << "\t mRegularizationType = " ;
   switch (mRegularizationType)
   {
      case REGULARIZE_NONE:
      {
         cout << " REGULARIZE_NONE " << endl << flush;
         break;
      }
      case REGULARIZE_TIKHONOV_MILLER:
      {
         cout << " REGULARIZE_TIKHONOV_MILLER" << endl << flush;
         break;
      }
      case REGULARIZE_CONCHELLO:
      {
         cout << " REGULARIZE_CONCHELLO" << endl << flush;
         break;
      }
      case REGULARIZE_MAXIMUM_ENTROPY:
      {
         cout << " REGULARIZE_MAXIMUM_ENTROPY" << endl << flush;
         break;
      }
      case REGULARIZE_TOTAL_VARIATION:
      {
         cout << " REGULARIZE_TOTAL_VARIATION" << endl << flush;
         break;
      }
   }
}

//--------------------------------------------------------------------------

regularizationType RichardsonLucyDeconvolve::GetRegularizationType()
{
   return mRegularizationType;
}

//--------------------------------------------------------------------------

void RichardsonLucyDeconvolve::SetRegularizationType( regularizationType myType )
{
   mRegularizationType = myType;
}

//--------------------------------------------------------------------------

std::string RichardsonLucyDeconvolve::ComposeOutputName()
{
   std::string outName = mpDegradedImage->GetImageName() + std::string("-RichardsonLucy");
   switch (mRegularizationType)
   {
      case REGULARIZE_NONE:
      {
         outName += std::string("-raw");
         break;
      }
      case REGULARIZE_TIKHONOV_MILLER:
      {
         outName += std::string("-TikhonovMiller");
         break;
      }
      case REGULARIZE_CONCHELLO:
      {
         outName += std::string("-Conchello");
         break;
      }
      case REGULARIZE_MAXIMUM_ENTROPY:
      {
         outName += std::string("-MaximumEntropy");
         break;
      }
      case REGULARIZE_TOTAL_VARIATION:
      {
         outName += std::string("-TotalVariation");
         break;
      }
   }
   return outName;
}

//--------------------------------------------------------------------------

bool RichardsonLucyDeconvolve::Run( )
{
   if (IsReadyToRun() == true)
   {  
      PrintParameters();
      int nrBands = mpDegradedImage->GetNumberOfBands();
      for (mCurrentIterationNr = 0; mCurrentIterationNr < mMaximumNrOfIterations; mCurrentIterationNr++)
      {
         cout << "\t iteration " << mCurrentIterationNr << endl << flush;
         for ( mCurrentBandNr = 0; mCurrentBandNr < nrBands; mCurrentBandNr++)
         {
            RunSingleIterationSingleBand( );
         }
         
         mpLastEstimate->CopyImageValues( mpNewEstimate );
      }
      mpRestoredImage = mpNewEstimate->Clone();
      mpRestoredImage->SetImageName( ComposeOutputName() );
      return true;
   }
   else
   {
      cerr << "Unable to start RL iterations; return 0 and abort..." << endl << flush;
      return false;
   }
}

//--------------------------------------------------------------------------

bool RichardsonLucyDeconvolve::IsReadyToRun()
{
   return AreParentConditionsOK();
}

//--------------------------------------------------------------------------

bool RichardsonLucyDeconvolve::RunSingleIterationSingleBand( )
{
   PrepareCurrentGrids( );
   
   // raw RL iteration step
   ////////////////////////
   
   ArrayGrid<double>* pConvolved = FFT::Convolve( mpLastGrid, mpPSFGrid );
   ArrayGrid<double>* pTmpGrid = mpDegradedGrid->Clone();
   pTmpGrid->DivideBy( pConvolved ); delete pConvolved;
   pConvolved = FFT::Convolve( pTmpGrid, mpPSFGrid );  delete pTmpGrid;
   mpNewGrid->MultiplyWith( pConvolved ); delete pConvolved;
   
   // Regularization step
   ////////////////////////
   
   RegularizeIteration( );
   return true;
}

//--------------------------------------------------------------------------

void RichardsonLucyDeconvolve::RegularizeIteration( )
{
   switch(mRegularizationType)
   {
      case REGULARIZE_NONE:
      {
         break;
      }
      case REGULARIZE_TIKHONOV_MILLER:
      {
         RegularizeTikhonovMiller( );
         break;
      }
      case REGULARIZE_CONCHELLO:
      {
         RegularizeConchello( );
         break;
      }
      case REGULARIZE_MAXIMUM_ENTROPY:
      {
         RegularizeMaximumEntropy( );
         break;
      }
      
      case REGULARIZE_TOTAL_VARIATION:
      {
         RegularizeTotalVariation( );
         break;
      }
   }
   
   if ( mEnforceIntensityRange )
   {
      ClipIntensities( );
   }

}

//--------------------------------------------------------------------------

double RichardsonLucyDeconvolve::MFunction(double a, double b)
{
   double signA, signB;
   
   if (a != 0.0)
   {
      signA = a / fabs(a);
   }
   else
   {
      signA = 1.0;
   }
   
   if (b != 0.0)
   {
      signB = b / fabs(b);
   }
   else
   {
      signB = 1.0;
   }
   
   return (((signA + signB) / 2.0) * common::MathUtils::GetMin( fabs(a), fabs(b) ));
}

//--------------------------------------------------------------------------

double RichardsonLucyDeconvolve::GetXContribution(ArrayGrid<double>* pGrid, int x, int y)
{
   double dPlus = pGrid->GetValue( x+1, y  ) - pGrid->GetValue( x,   y  );
   double dMin  = pGrid->GetValue( x,   y  ) - pGrid->GetValue( x-1, y  );
   
   double ttmp = MFunction( dPlus, dMin );
         
   return (dPlus / sqrt( POWER2( dPlus ) + POWER2( ttmp ) + RL_THRESHOLD));
}

//--------------------------------------------------------------------------

double RichardsonLucyDeconvolve::GetYContribution(ArrayGrid<double>* pGrid, int x, int y)
{
   double dPlus = pGrid->GetValue( x, y+1) - pGrid->GetValue( x, y  ); 
   double dMin  = pGrid->GetValue( x, y  ) - pGrid->GetValue( x, y-1);

   double ttmp = MFunction( dPlus, dMin );

   return (dPlus / sqrt( POWER2( dPlus ) + POWER2( ttmp ) + RL_THRESHOLD));
}

//--------------------------------------------------------------------------

void RichardsonLucyDeconvolve::RegularizeTotalVariation( )
{
   ArrayGrid<double>* pLastGrid = mpLastEstimate->GetBands()[ mCurrentBandNr ];
   ArrayGrid<double>* pNewGrid = mpNewEstimate->GetBands()[ mCurrentBandNr ];
   
   int width = pNewGrid->GetWidth();
   int height = pNewGrid->GetHeight();
   
   for (int y = 2; y < height-1; y++)
   {
      for (int x = 2; x < width-1; x++)
      {
         double dx1 = GetXContribution( pLastGrid, x,   y );
         double dx0 = GetXContribution( pLastGrid, x-1, y );
         double dy1 = GetYContribution( pLastGrid, x,   y );
         double dy0 = GetYContribution( pLastGrid, x,   y-1 );
         double localDivergence = dx1 - dx0 + dy1 - dy0;

         pNewGrid->SetValue( x, y, pNewGrid->GetValue( x, y ) *  (1.0 / ((1.0 - mLambda * localDivergence ) ) ) );
      }
   }
}

//--------------------------------------------------------------------------

void RichardsonLucyDeconvolve::RegularizeTikhonovMiller( )
{
   ArrayGrid<double>* pLastGrid = mpLastEstimate->GetBands()[ mCurrentBandNr ];
   ArrayGrid<double>* pNewGrid = mpNewEstimate->GetBands()[ mCurrentBandNr ];
   
   int width = pLastGrid->GetWidth();
   int height = pLastGrid->GetHeight();
   
   for (int y = 1; y < height-1; y++)
   {
      for (int x = 1; x < width-1; x++)
      {
         double dxx = NumberGridTools<double>::GetSecondDerivativeXX( pLastGrid, x, y );
         double dyy = NumberGridTools<double>::GetSecondDerivativeYY( pLastGrid, x, y );

         pNewGrid->SetValue( x, y, pNewGrid->GetValue( x, y ) *  (1.0 / ((1.0 + 2.0 * mLambda * (dxx + dyy ) ) ) ) );
      }
   }
}

//--------------------------------------------------------------------------

void RichardsonLucyDeconvolve::RegularizeMaximumEntropy( )
{
   ArrayGrid<double>* pLastGrid = mpLastEstimate->GetBands()[ mCurrentBandNr ];
   ArrayGrid<double>* pNewGrid = mpNewEstimate->GetBands()[ mCurrentBandNr ];
   
   int width = pLastGrid->GetWidth();
   int height = pLastGrid->GetHeight();

   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         pNewGrid->SetValue( x, y, pNewGrid->GetValue( x, y ) * (1.0 -  mLambda *  pLastGrid->GetValue(x, y) * log( pLastGrid->GetValue(x, y) + RL_THRESHOLD ) ));
      }
   }
}

//--------------------------------------------------------------------------

void RichardsonLucyDeconvolve::RegularizeConchello( )
{
   ArrayGrid<double>* pNewGrid = mpNewEstimate->GetBands()[ mCurrentBandNr ];
   
   int width = pNewGrid->GetWidth();
   int height = pNewGrid->GetHeight();
   
   // initialize to avoid border artifacts
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         pNewGrid->SetValue(x, y, ((-1.0 + sqrt( 1.0 + 2.0 * mLambda * pNewGrid->GetValue(x, y))) / mLambda));
      }
   }
}
//--------------------------------------------------------------------------

void RichardsonLucyDeconvolve::ClipIntensities( )
{
   ArrayGrid<double>* pNewGrid = mpNewEstimate->GetBands()[ mCurrentBandNr ];
   
   int width  = pNewGrid->GetWidth();
   int height = pNewGrid->GetHeight();
   
   double min = 0.0;
   double max = 255.0;
   // initialize to avoid border artifacts
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         pNewGrid->SetValue(x, y, MathUtils::ClipValue( pNewGrid->GetValue(x, y), min, max ) );
      }
   }
}


//--------------------------------------------------------------------------


}
}
