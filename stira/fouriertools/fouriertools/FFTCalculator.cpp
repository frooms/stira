
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

#include "FFTCalculator.h"

using namespace std;

namespace stira {
namespace fouriertools {

//============================================================================================

FFTCalculator::FFTCalculator()
{
   mWidth        = 0;
   mHeight       = 0;
   mpComplexGrid = 0;
}

//============================================================================================

FFTCalculator::FFTCalculator( ArrayGrid< std::complex<double> >* pComplexGrid)
{
   mWidth        = pComplexGrid->GetWidth();
   mHeight       = pComplexGrid->GetHeight();
   mpComplexGrid = pComplexGrid;
}

//============================================================================================

FFTCalculator::~FFTCalculator()
{
}

//============================================================================================

void FFTCalculator::SwitchQuadrants( ArrayGrid< std::complex<double> > *pGridIn)
{
   // regroup four quadrants of image so that the origin is in the center of the image

   ArrayGrid< complex<double> >* pTmpFFTGridBeforeSwitch = new ArrayGrid< complex<double> >( *pGridIn );

   int halfWidthFirst  = (int)(ceil((double)(mWidth) / 2.0));
   int halfHeightFirst = (int)(ceil((double)(mHeight) / 2.0));
   
   int halfWidthLast  = (int)(floor((double)(mWidth) / 2.0));
   int halfHeightLast = (int)(floor((double)(mHeight) / 2.0));

   for (int y = 0; y < mHeight; y++)
   {
      for (int x = 0; x < mWidth; x ++)
      {
         int xn, yn;

         if (x < halfWidthFirst)  {xn = x + halfWidthLast;}  else {xn = x - halfWidthFirst;}
         if (y < halfHeightFirst) {yn = y + halfHeightLast;} else {yn = y - halfHeightFirst;}

         complex<double> complexValue = pTmpFFTGridBeforeSwitch->GetValue(x, y);
         pGridIn->SetValue(xn, yn, complexValue);
      }
   }
   delete pTmpFFTGridBeforeSwitch;
}

//============================================================================================

void FFTCalculator::SwitchQuadrants()
{
   // regroup four quadrants of image so that the origin is in the center of the image

   ArrayGrid< complex<double> >* pTmpFFTGridBeforeSwitch = new ArrayGrid< complex<double> >( *mpComplexGrid );

   int halfWidthFirst  = (int)(ceil((double)(mWidth) / 2.0));
   int halfHeightFirst = (int)(ceil((double)(mHeight) / 2.0));
   
   int halfWidthLast  = (int)(floor((double)(mWidth) / 2.0));
   int halfHeightLast = (int)(floor((double)(mHeight) / 2.0));

   for (int y = 0; y < mHeight; y++)
   {
      for (int x = 0; x < mWidth; x ++)
      {
         int xn, yn;

         if (x < halfWidthFirst)  {xn = x + halfWidthLast;}  else {xn = x - halfWidthFirst;}
         if (y < halfHeightFirst) {yn = y + halfHeightLast;} else {yn = y - halfHeightFirst;}

         complex<double> complexValue = pTmpFFTGridBeforeSwitch->GetValue(x, y);
         mpComplexGrid->SetValue(xn, yn, complexValue);
      }
   }
   delete pTmpFFTGridBeforeSwitch;
}

//============================================================================================
}
}

