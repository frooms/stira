
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

#include "RichardsonLucyDeconvolveProcess.h"

#include "../../stira/fouriertools/fouriertools/FFT.h"
#include "../../stira/imagetools/imagegenerator/GridGenerator.h"

using namespace stira::image;
using namespace stira::fouriertools;
using namespace stira::deconvolve;

RichardsonLucyDeconvolveProcess::RichardsonLucyDeconvolveProcess( Image* pImage ) : Process( pImage )
{
   mRegularizationType = StiraDefinitions::RLREGULARIZE_NONE;
   mPSFType = StiraDefinitions::PSF_GAUSS;
   mProcessName = QString("Richardson-Lucy Deconvolved Result");
}

//------------------------------------------------------------------

RichardsonLucyDeconvolveProcess::~RichardsonLucyDeconvolveProcess()
{
}

//------------------------------------------------------------------

void RichardsonLucyDeconvolveProcess::SetLambda( double lambda )
{
   mLambda = lambda;
}

//------------------------------------------------------------------

double RichardsonLucyDeconvolveProcess::GetLambda()
{
   return mLambda;
}

//------------------------------------------------------------------

void RichardsonLucyDeconvolveProcess::SetBlurLevel( double blurLevel )
{
   mBlurLevel = blurLevel;
}

//------------------------------------------------------------------

double RichardsonLucyDeconvolveProcess::GetBlurLevel()
{
   return mBlurLevel;
}

//------------------------------------------------------------------

StiraDefinitions::RLRegularizationType RichardsonLucyDeconvolveProcess::GetRegularizationType()
{
   return mRegularizationType;
}

//------------------------------------------------------------------

void RichardsonLucyDeconvolveProcess::SetRegularizationType( StiraDefinitions::RLRegularizationType myType )
{
   mRegularizationType = myType;
}

//------------------------------------------------------------------

StiraDefinitions::PSFType RichardsonLucyDeconvolveProcess::GetPSFType()
{
   return mPSFType;
}

//------------------------------------------------------------------

void RichardsonLucyDeconvolveProcess::SetPSFType( StiraDefinitions::PSFType myType )
{
   mPSFType = myType;
}

//------------------------------------------------------------------

int RichardsonLucyDeconvolveProcess::GetNrOfIterations()
{
   return mNrOfIterations;
}

//------------------------------------------------------------------

void RichardsonLucyDeconvolveProcess::SetNrOfIterations( int nrIterations )
{
   mNrOfIterations = nrIterations;
}

//------------------------------------------------------------------

ArrayGrid<double>* RichardsonLucyDeconvolveProcess::GeneratePSF()
{
   int width  = mpImage->GetWidth();
   int height = mpImage->GetHeight();
   double blurLevel = this->GetBlurLevel();
   
   switch ( mPSFType )
   {
      case StiraDefinitions::PSF_DISK:
      {
         return stira::image::GridGenerator::GenerateDisk( width, height, blurLevel );
      }
      case StiraDefinitions::PSF_SQUARE:
      {
         return stira::image::GridGenerator::GenerateSquare( width, height, blurLevel );
      }
      case StiraDefinitions::PSF_AIRY:
      {
         return stira::image::GridGenerator::GenerateAiry( width, height, blurLevel );
      }
      case StiraDefinitions::PSF_GAUSS: 
      default:
      {
         return stira::image::GridGenerator::GenerateGaussian ( width, height, blurLevel );
      }
   }
}

//------------------------------------------------------------------

stira::deconvolve::regularizationType RichardsonLucyDeconvolveProcess::ConvertRegularizationType( )
{
   switch( mRegularizationType )
   {
      case StiraDefinitions::RLREGULARIZE_TIKHONOV_MILLER:
      {
         return stira::deconvolve::REGULARIZE_TIKHONOV_MILLER;
      }
      case StiraDefinitions::RLREGULARIZE_CONCHELLO:
      {
         return stira::deconvolve::REGULARIZE_CONCHELLO;
      }
      case StiraDefinitions::RLREGULARIZE_MAXIMUM_ENTROPY:
      {
         return stira::deconvolve::REGULARIZE_MAXIMUM_ENTROPY;
      }
      case StiraDefinitions::RLREGULARIZE_TOTAL_VARIATION:
      {
         return stira::deconvolve::REGULARIZE_TOTAL_VARIATION;
      }
      case StiraDefinitions::RLREGULARIZE_NONE:
      default:
      {
         return stira::deconvolve::REGULARIZE_NONE;
      }
   }
}

//------------------------------------------------------------------

void RichardsonLucyDeconvolveProcess::run()
{
   stira::deconvolve::regularizationType myRegularizationType = ConvertRegularizationType( );
   Image* pPSFImage = new Image ( GeneratePSF() );
   
   stira::deconvolve::RichardsonLucyDeconvolve rld ( mpImage, pPSFImage, myRegularizationType, mNrOfIterations );
   rld.SetSigmaNoise( 1.0 );
   rld.SetLambda( mLambda );
   rld.Run();
   
   Image* pOutImage = rld.GetRestoredImage();

   delete pPSFImage;
   AddResult( pOutImage );
   // ownership of this image is transfered through GetImage() to ImageDataList
}

//------------------------------------------------------------------
