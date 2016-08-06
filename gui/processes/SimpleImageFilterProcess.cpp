
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

#include "SimpleImageFilterProcess.h"
#include "../../stira/imagedata/simpletools/ImageStatistics.h"
#include "../../stira/imagetools/imagegenerator/GridGenerator.h"
#include "../../stira/fouriertools/fouriertools/FFT.h"
#include "../../stira/filter/filter/SeparableFilter.h"
#include "../../stira/filter/filter/NonSeparableFilter.h"
#include "../../stira/filter/filter/MedianFilter.h"
#include "../../stira/filter/filter/GaussConvolve.h"
#include "../../stira/filter/filter/UnsharpMask.h"
#include "../../stira/filter/filter/AdaptiveBilateralFilter.h"
#include "../../stira/filter/filter/KuwaharaFilter.h"
#include "../../stira/filter/filter/LaplacianOfGaussianFilter.h"
#include "../../stira/filter/filter/NonLocalMeansFilter.h"
using namespace stira::filter;
using namespace stira::image;
using namespace stira::fouriertools;
using namespace std;

SimpleImageFilterProcess::SimpleImageFilterProcess( Image* pImage ) : Process( pImage )
{
   mProcessName = QString("Simple Filter Result");
}

//--------------------------------------------------------

SimpleImageFilterProcess::~SimpleImageFilterProcess()
{
}

//--------------------------------------------------------

void SimpleImageFilterProcess::SetFilterType( StiraDefinitions::SimpleFilterType myType )
{
   mType = myType;
}

//--------------------------------------------------------

StiraDefinitions::SimpleFilterType SimpleImageFilterProcess::GetFilterType()
{
   return mType;
}

//--------------------------------------------------------

void SimpleImageFilterProcess::SetFilterWidth(int width)
{
   mFilterWidth = width;
}

//--------------------------------------------------------

int SimpleImageFilterProcess::GetFilterWidth()
{
   return mFilterWidth;
}

//--------------------------------------------------------

void SimpleImageFilterProcess::SetSigma( double sigma )
{
   mSigma = sigma;
}

//--------------------------------------------------------

double SimpleImageFilterProcess::GetSigma()
{
   return mSigma;
}

//--------------------------------------------------------
   
void SimpleImageFilterProcess::SetAngle( double angle )
{
   mAngle = angle;
}

//--------------------------------------------------------

double SimpleImageFilterProcess::GetAngle()
{
   return mAngle;
}

//--------------------------------------------------------

void SimpleImageFilterProcess::SetExtensionType( stira::image::GridExtender<double>::ExtensionType myType )
{
   mExtensionType = myType;
}

//--------------------------------------------------------

stira::image::GridExtender<double>::ExtensionType SimpleImageFilterProcess::GetExtensionType()
{
   return mExtensionType;
}

//--------------------------------------------------------

void SimpleImageFilterProcess::run()
{
   Image* pOutImage = 0;
   
   switch( GetFilterType() )
   {
      case StiraDefinitions::FILTER_LOCALMEAN:
      {
         double *pFilter = new double[mFilterWidth];
         for (int i = 0; i < mFilterWidth; i++)
         {
            pFilter[i] = (double)(1.0) / (double)(mFilterWidth);
         }
         SeparableFilter sf;
         pOutImage = sf.RunRowColumn( mpImage, pFilter, pFilter, mFilterWidth, mFilterWidth, mExtensionType );
         std::string outName = mpImage->GetImageName() + std::string("-LocalMean");
         pOutImage->SetImageName(outName);
         break;
      }
      case StiraDefinitions::FILTER_NONLOCALMEAN:
      {
         NonLocalMeansFilter nlm;
         nlm.SetSigma( mSigma );
         pOutImage = nlm.Run( mpImage );
         break;
      }
      case StiraDefinitions::FILTER_NORMALMEDIAN:
      {
         int filterWidth = (int)(mFilterWidth/2);
         pOutImage = MedianFilter::RunMedian( mpImage, filterWidth );
         break;
      }
      case StiraDefinitions::FILTER_HYBRIDMEDIAN:
      {
         int filterWidth = (int)(mFilterWidth/2);
         pOutImage = MedianFilter::RunHybridMedian( mpImage, filterWidth );
         break;
      }
      case StiraDefinitions::FILTER_GAUSSIAN:
      {
         pOutImage = GaussConvolve::DerivativeConvolveFFT( mpImage, mSigma, GaussConvolve::DERIVATIVE_NONE, mExtensionType);
         break;
      }
      case StiraDefinitions::FILTER_ADAPTIVEBILATERAL:
      {
         pOutImage = AdaptiveBilateralFilter::Run( mpImage );
         break;
      }
      case StiraDefinitions::FILTER_LAPLACIANOFGAUSSIAN:
      {
         pOutImage = LaplacianOfGaussianFilter::Run( mpImage );
         ImageStatistics::Rescale( pOutImage, 0.0, 255.0);
         break;
      }
      case StiraDefinitions::FILTER_KUWAHARA:
      {
         pOutImage = KuwaharaFilter::Run( mpImage, mFilterWidth );
         break;
      }
      case StiraDefinitions::FILTER_UNSHARPMASK:
      {
         pOutImage = UnsharpMask::Run( mpImage, mSigma, 2.0 );
         break;
      }
      case StiraDefinitions::FILTER_SOBELX:
      {
         pOutImage = NonSeparableFilter::RunSobelX( mpImage );
         std::string outName = mpImage->GetImageName() + std::string("-SobelX");
         pOutImage->SetImageName(outName);
         break;
      }
      case StiraDefinitions::FILTER_SOBELY:
      {
         pOutImage = NonSeparableFilter::RunSobelY( mpImage );
         std::string outName = mpImage->GetImageName() + std::string("-SobelY");
         pOutImage->SetImageName(outName);
         break;
      }
      case StiraDefinitions::FILTER_MOTIONBLUR:
      {
         ArrayGrid<double>* pPSF = GridGenerator::GenerateLine( mpImage->GetWidth(), mpImage->GetHeight(), 
                                                                this->GetFilterWidth(), this->GetAngle() 
                                                              );
         pOutImage = FFT::Convolve( mpImage, pPSF );
         delete pPSF;
         std::string outName = mpImage->GetImageName() + std::string("-MotionBlur");
         pOutImage->SetImageName(outName);
         break;
      }
   }
   
   AddResult( pOutImage );
   // ownership of this image is transfered through GetImage() to ImageDataList
}

//--------------------------------------------------------
