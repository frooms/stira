
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

#include "FFTWCalculator.h"

using namespace std;

namespace stira {
namespace fouriertools {

//============================================================================================

FFTWCalculator::FFTWCalculator() : FFTCalculator()
{
   mpInFFTWData  = 0;
   mpOutFFTWData = 0;
}

//============================================================================================

FFTWCalculator::FFTWCalculator( ArrayGrid< std::complex<double> >* pComplexGrid) : FFTCalculator( pComplexGrid )
{
   mpInFFTWData  = 0;
   mpOutFFTWData = 0;
}

//============================================================================================

FFTWCalculator::~FFTWCalculator()
{
   CleanLibData();
}

//============================================================================================

void FFTWCalculator::ApplyForwardTransform()
{
   CreateLibData( mpComplexGrid );

   fftw_plan fftwPlan = fftw_plan_dft_2d( mHeight, mWidth, mpInFFTWData, mpOutFFTWData, FFTW_FORWARD, FFTW_ESTIMATE );
   
   fftw_execute( fftwPlan );
   fftw_destroy_plan( fftwPlan );

   WriteResultInFFTBand();
   CleanLibData();
   fftw_cleanup();
}

//============================================================================================

void FFTWCalculator::ApplyInverseTransform()
{
   CreateLibData( mpComplexGrid );

   fftw_plan fftwPlan = fftw_plan_dft_2d( mHeight, mWidth, mpInFFTWData, mpOutFFTWData, FFTW_BACKWARD, FFTW_ESTIMATE );
   fftw_execute( fftwPlan );
   fftw_destroy_plan( fftwPlan );

   WriteResultInFFTBand();
   CleanLibData();
   fftw_cleanup();
}

//============================================================================================

void FFTWCalculator::WriteResultInFFTBand()
{
   for (int y = 0; y < mHeight; y++)
   {
      for (int x = 0; x < mWidth; x++)
      {
         complex<double> complexValue(mpOutFFTWData[x + mWidth * y][0], mpOutFFTWData[x + mWidth * y][1]);
         mpComplexGrid->SetValue(x, y, complexValue);
      }
   }
}

//============================================================================================

bool FFTWCalculator::CreateLibData( ArrayGrid< std::complex<double> >* pGridIn)
{
   mWidth  = pGridIn->GetWidth();
   mHeight = pGridIn->GetHeight();
   
   CleanLibData();
   
   mpInFFTWData  = (fftw_complex *) malloc( mWidth * mHeight * sizeof(fftw_complex) );
   mpOutFFTWData = (fftw_complex *) malloc( mWidth * mHeight * sizeof(fftw_complex) );

   for (int y = 0; y < mHeight; y++)
   {
      for (int x = 0; x < mWidth; x++)
      {
         mpInFFTWData[x + mWidth * y][0] = (pGridIn->GetValue(x, y)).real() ;
         mpInFFTWData[x + mWidth * y][1] = (pGridIn->GetValue(x, y)).imag() ;
      
         mpOutFFTWData[x + mWidth * y][0] = 0.0;
         mpOutFFTWData[x + mWidth * y][1] = 0.0;
      }
   }
   return true;
}

//============================================================================================

bool FFTWCalculator::CleanLibData()
{
   if (mpInFFTWData != 0)
   {
      fftw_free( mpInFFTWData );
      mpInFFTWData = 0;
   }
   if ( mpOutFFTWData != 0)
   {
      fftw_free( mpOutFFTWData );
      mpOutFFTWData = 0;
   }
   return true;
}

//============================================================================================
}
}

