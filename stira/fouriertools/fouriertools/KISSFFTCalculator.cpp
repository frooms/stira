
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

#include "KISSFFTCalculator.h"

using namespace std;

namespace stira {
namespace fouriertools {

//============================================================================================

KISSFFTCalculator::KISSFFTCalculator() : FFTCalculator( )
{
   mpInKISSData  = 0;
   mpOutKISSData = 0;
}

//============================================================================================

KISSFFTCalculator::KISSFFTCalculator( ArrayGrid< std::complex<double> >* pComplexGrid) : FFTCalculator( pComplexGrid )
{
   mpInKISSData  = 0;
   mpOutKISSData = 0;
}

//============================================================================================

KISSFFTCalculator::~KISSFFTCalculator()
{
   CleanLibData();
}

//============================================================================================

void KISSFFTCalculator::ApplyForwardTransform()
{
   int numberOfImageDimensions = 2;
   int* pArrayWithImageDimensions;

   pArrayWithImageDimensions = new int[numberOfImageDimensions];
   CreateLibData(mpComplexGrid);
   
   pArrayWithImageDimensions[0] = mWidth;
   pArrayWithImageDimensions[1] = mHeight;
   kiss_fftnd_cfg fcfg2d = kiss_fftnd_alloc(pArrayWithImageDimensions, numberOfImageDimensions, 0, 0, 0);
   kiss_fftnd(fcfg2d, mpInKISSData, mpOutKISSData);

   WriteResultInFFTBand();

   CleanLibData();
   #ifdef DEBUG
      cout << "In FFTCalculator::ApplyForwardTransform(), free fcfg2d " << fcfg2d << endl << flush;
   #endif
   free(fcfg2d );
   kiss_fft_cleanup();
   delete []pArrayWithImageDimensions;
}

//============================================================================================

void KISSFFTCalculator::ApplyInverseTransform()
{
   int  numberOfImageDimensions = 2;
   int* pArrayWithImageDimensions;

   pArrayWithImageDimensions = new int[numberOfImageDimensions];
   CreateLibData( mpComplexGrid );
   
   pArrayWithImageDimensions[0] = mWidth;
   pArrayWithImageDimensions[1] = mHeight;
   
   kiss_fftnd_cfg icfg2d = kiss_fftnd_alloc((int*)(pArrayWithImageDimensions), (int)(numberOfImageDimensions), 1, 0, 0);
   kiss_fftnd(icfg2d, mpInKISSData, mpOutKISSData);

   WriteResultInFFTBand();

   CleanLibData();
   free(icfg2d);
   #ifdef DEBUG
      cout << "In FFTCalculator::ApplyInverseTransform(), free icfg2d " << icfg2d << endl << flush;
   #endif
   kiss_fft_cleanup();
   delete []pArrayWithImageDimensions;
}

//============================================================================================

void KISSFFTCalculator::WriteResultInFFTBand()
{
   for (int y = 0; y < mHeight; y++)
   {
      for (int x = 0; x < mWidth; x++)
      {
         complex<double> complexValue(mpOutKISSData[x + mWidth * y].r, mpOutKISSData[x + mWidth * y].i);
         mpComplexGrid->SetValue(x, y, complexValue);
      }
   }
}

//============================================================================================

bool KISSFFTCalculator::CreateLibData( ArrayGrid< std::complex<double> >* pGridIn)
{
   int myWidth  = pGridIn->GetWidth();
   int myHeight = pGridIn->GetHeight();
   
   CleanLibData();
   size_t bufferLength = size_t(sizeof(kiss_fft_cpx) * myWidth * myHeight );
   mpInKISSData  = new kiss_fft_cpx[bufferLength];
   mpOutKISSData = new kiss_fft_cpx[bufferLength];

   for (int y = 0; y < myHeight; y++)
   {
      for (int x = 0; x < myWidth; x++)
      {
         mpInKISSData[x + myWidth * y].r = (pGridIn->GetValue(x, y)).real() ;
         mpInKISSData[x + myWidth * y].i = (pGridIn->GetValue(x, y)).imag() ;
      }
   }

   for (int y = 0; y < myHeight; y++)
   {
      for (int x = 0; x < myWidth; x++)
      {
         mpOutKISSData[x + myWidth * y].r = 0.0;
         mpOutKISSData[x + myWidth * y].i = 0.0;
      }
   }
   return true;
}

//============================================================================================

bool KISSFFTCalculator::CleanLibData()
{
   if (mpInKISSData != 0)
   {
      delete []mpInKISSData;
      mpInKISSData = 0;
   }

   if (mpOutKISSData != 0)
   {
      delete []mpOutKISSData;
      mpOutKISSData = 0;
   }
   return true;
}

//============================================================================================
}
}

