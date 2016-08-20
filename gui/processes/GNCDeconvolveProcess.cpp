
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
 
#include "GNCDeconvolveProcess.h"

#include "../../stira/deconvolve/deconvolve/GNCDeconvolve.h"
#include "../../stira/fouriertools/fouriertools/FFT.h"
#include "../../stira/imagetools/imagegenerator/GridGenerator.h"

using namespace stira::imagetools;
using namespace stira::imagedata;
using namespace stira::fouriertools;
using namespace stira::deconvolve;

GNCDeconvolveProcess::GNCDeconvolveProcess( Image* pImage ) : Process( pImage )
{
   mProcessName = QString("GNC Deconvolved Result");
}

//------------------------------------------------------------------

GNCDeconvolveProcess::~GNCDeconvolveProcess()
{
}

//------------------------------------------------------------------

double GNCDeconvolveProcess::GetBlurLevel()
{
   return mBlurLevel;
}

//------------------------------------------------------------------

void GNCDeconvolveProcess::SetBlurLevel( double blurLevel )
{
   mBlurLevel = blurLevel;
}

//------------------------------------------------------------------

int GNCDeconvolveProcess::GetNrOfScales()
{
   return mNrOfScales;
}

//------------------------------------------------------------------

void GNCDeconvolveProcess::SetNrOfScales( int nrOfScales )
{
   mNrOfScales = nrOfScales;
}

//------------------------------------------------------------------

int GNCDeconvolveProcess::GetNrOfOrientations( )
{
   return mNrOfOrientations;
}

//------------------------------------------------------------------

void GNCDeconvolveProcess::SetNrOfOrientations( int nrOfOrientations )
{
   mNrOfOrientations = nrOfOrientations;
}

//------------------------------------------------------------------

double GNCDeconvolveProcess::GetLambda()
{
   return mLambda;
}

//------------------------------------------------------------------

void GNCDeconvolveProcess::SetLambda( double lambda )
{
   mLambda = lambda;
}

//------------------------------------------------------------------

double GNCDeconvolveProcess::GetMu()
{
   return mMu;
}

//------------------------------------------------------------------

void GNCDeconvolveProcess::SetMu( double mu )
{
   mMu = mu;
}

//------------------------------------------------------------------

double GNCDeconvolveProcess::GetGammaInitial()
{
   return mGammaInitial;
}

//------------------------------------------------------------------
;
void GNCDeconvolveProcess::SetGammaInitial( double gammaInitial )
{
   mGammaInitial = gammaInitial;
}

//------------------------------------------------------------------
;

double GNCDeconvolveProcess::GetGammaFinal()
{
   return mGammaFinal;
}

//------------------------------------------------------------------

void GNCDeconvolveProcess::SetGammaFinal( double gammaFinal )
{
   mGammaFinal = gammaFinal;
}

//------------------------------------------------------------------

double GNCDeconvolveProcess::GetUpdateFactor()
{
   return mUpdateFactor;
}

//------------------------------------------------------------------

void GNCDeconvolveProcess::SetUpdateFactor( double updateFactor )
{
   mUpdateFactor = updateFactor;
}

//------------------------------------------------------------------

int GNCDeconvolveProcess::GetNrOfIterations()
{
   return mNrOfIterations;
}

//------------------------------------------------------------------

void GNCDeconvolveProcess::SetNrOfIterations( int nrIterations )
{
   mNrOfIterations = nrIterations;
}

//------------------------------------------------------------------

void GNCDeconvolveProcess::run()
{
   int width  = mpImage->GetWidth();
   int height = mpImage->GetHeight();
   double sigmaBlur = this->GetBlurLevel();
   
   ArrayGrid<double>* pPSF = GridGenerator::GenerateGaussian ( width, height, sigmaBlur, sigmaBlur );
   Image* pPSFImage = new Image ( pPSF );
   
   stira::deconvolve::GNCDeconvolve gncd( mpImage, pPSFImage, mNrOfIterations );

   gncd.SetNumberOfScales( mNrOfScales );
   gncd.SetNumberOfOrientations( mNrOfOrientations );
   gncd.SetMu( mMu );
   gncd.SetLambda( mLambda );
   gncd.SetUpdateFactor( mUpdateFactor );
   gncd.SetGamma( mGammaInitial );
   gncd.SetGammaFinal( mGammaFinal );
   gncd.Run();
   
   AddResult( gncd.GetRestoredImage() );

   delete pPSFImage;
   // ownership of this image is transfered through GetImage() to ImageDataList
}

//------------------------------------------------------------------
