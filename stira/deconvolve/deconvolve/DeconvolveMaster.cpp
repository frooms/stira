
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

#include "DeconvolveMaster.h"

namespace stira{
namespace deconvolve{

using namespace std;

//--------------------------------------------------------------------------

DeconvolveMaster::DeconvolveMaster( Image* pDegradedImage )
{
   mpDegradedImage = pDegradedImage;
   mpRestoredImage = 0;
   mpPSF = 0;
   mSigmaNoise = -1.0;
}

//--------------------------------------------------------------------------

DeconvolveMaster::DeconvolveMaster( Image* pDegradedImage, Image* pPSF )
{
   mpDegradedImage = pDegradedImage;
   mpRestoredImage = 0;
   mpPSF = pPSF;
   mSigmaNoise = -1.0;
}

//--------------------------------------------------------------------------

DeconvolveMaster::~DeconvolveMaster()
{
   if (mpRestoredImage != 0)
   {
      delete mpRestoredImage;
   }
}

//--------------------------------------------------------------------------

Image* DeconvolveMaster::GetDegradedImage()
{
   return mpDegradedImage;
}

//--------------------------------------------------------------------------

void DeconvolveMaster::SetDegradedImage( Image* pDegradedImage)
{
   mpDegradedImage = pDegradedImage;
}

//--------------------------------------------------------------------------

Image* DeconvolveMaster::GetPSF()
{
   return mpPSF;
}

//--------------------------------------------------------------------------

void DeconvolveMaster::SetPSF(Image* pPSF)
{
   if (mpPSF != 0)
   {
      delete mpPSF;
   }
   mpPSF = pPSF;
}

//--------------------------------------------------------------------------

Image* DeconvolveMaster::GetRestoredImage()
{
   return mpRestoredImage->Clone();
}

//--------------------------------------------------------------------------

void DeconvolveMaster::SetSigmaNoise(double sigma)
{
   mSigmaNoise = sigma;
}

//--------------------------------------------------------------------------

double DeconvolveMaster::GetSigmaNoise()
{
   return mSigmaNoise;
}

//--------------------------------------------------------------------------

bool DeconvolveMaster::AreParentConditionsOK()
{
   if (mpDegradedImage != 0)
   {
      int width   = mpDegradedImage->GetWidth();
      int height  = mpDegradedImage->GetHeight();
      int nrBands = mpDegradedImage->GetNumberOfBands();
      if (mpPSF != 0)
      {
         if ( (mpPSF->GetWidth() != width) && (mpPSF->GetHeight() != height) )
         {
            cerr << "Deconvolve cannot run: PSF available, but with different dimensions than the degraded source image" << endl << flush;
            return false;
         }
         if ((mpPSF->GetNumberOfBands() != 1) && (mpPSF->GetNumberOfBands() != nrBands))
         {
            cerr << "Deconvolve cannot run: PSF has an invalid nr of bands: " << mpPSF->GetNumberOfBands() << endl << flush;
            return false;
         }
         if (mSigmaNoise < 0.0)
         {
            cerr << "Deconvolve cannot run: input sigma noise is invalid" << endl << flush;
            return false;
         }
      }
      else
      {
         cerr << "Deconvolve cannot run: no PSF available" << endl << flush;
         return false;
      }
      return true;
   }
   else
   {
      cerr << "Deconvolve cannot run: no degraded input image available" << endl << flush;
      return false;
   }
}

//--------------------------------------------------------------------------

}
}
