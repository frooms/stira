
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
 
#include "WienerDeconvolveProcess.h"

#include "../../stira/deconvolve/deconvolve/WienerDeconvolve.h"
#include "../../stira/fouriertools/fouriertools/FFT.h"
#include "../../stira/imagetools/imagegenerator/GridGenerator.h"

using namespace stira::imagedata;
using namespace stira::imagetools;
using namespace stira::fouriertools;
using namespace stira::deconvolve;

WienerDeconvolveProcess::WienerDeconvolveProcess( Image* pImage ) : Process( pImage )
{
   mProcessName = QString("Wiener Deconvolved Result");
}

//------------------------------------------------------------------

WienerDeconvolveProcess::~WienerDeconvolveProcess()
{
}

//------------------------------------------------------------------

void WienerDeconvolveProcess::SetNoiseLevel( double noiseLevel )
{
   mNoiseLevel = noiseLevel;
}

//------------------------------------------------------------------

double WienerDeconvolveProcess::GetNoiseLevel()
{
   return mNoiseLevel;
}

//------------------------------------------------------------------

void WienerDeconvolveProcess::SetBlurLevel( double blurLevel )
{
   mBlurLevel = blurLevel;
}

//------------------------------------------------------------------

double WienerDeconvolveProcess::GetBlurLevel()
{
   return mBlurLevel;
}

//------------------------------------------------------------------

void WienerDeconvolveProcess::run()
{
   int width  = mpImage->GetWidth();
   int height = mpImage->GetHeight();
   double sigmaBlur = this->GetBlurLevel();
   
   ArrayGrid<double>* pPSF = GridGenerator::GenerateGaussian ( width, height, sigmaBlur, sigmaBlur );
   Image* pPSFImage = new Image ( pPSF );
   stira::deconvolve::WienerDeconvolve wd ( mpImage, pPSFImage );
   wd.SetSigmaNoise ( this->GetNoiseLevel() );
   wd.Run();
   
   AddResult( wd.GetRestoredImage() );

   delete pPSFImage;
   // ownership of this image is transfered through GetImage() to ImageDataList
}

//------------------------------------------------------------------
