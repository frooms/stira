
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

#include "ContrastEnhanceProcess.h"
#include "../../stira/image/tools/ImageTools.h"
#include "../../stira/diffusion/diffusion/AnisotropicDiffusion.h"
#include "../../stira/contrastenhance/contrastenhance/Retinex.h"
#include "../../stira/contrastenhance/contrastenhance/HistogramTools.h"
#include "../../stira/contrastenhance/contrastenhance/AdaptiveEnhanceLuong.h"
#include "../../stira/contrastenhance/contrastenhance/HazeRemover.h"
#include "../../stira/pyramidapplications/pyramidapplications/PyramidContrastEnhancer.h"

using namespace stira::contrastenhance;
using namespace stira::pyramidapplications;
using namespace stira::image;


ContrastEnhanceProcess::ContrastEnhanceProcess( Image* pImage ) : Process( pImage )
{
   mProcessName = QString("Contrast Enhancement Result");
}

//--------------------------------------------------------
   
ContrastEnhanceProcess::~ContrastEnhanceProcess()
{
}

//--------------------------------------------------------

void ContrastEnhanceProcess::SetGamma( double gamma )
{
   mGamma = gamma;
}

//--------------------------------------------------------

double ContrastEnhanceProcess::GetGamma( )
{
   return mGamma;
}

//--------------------------------------------------------

void ContrastEnhanceProcess::SetWindowSize( int wsize )
{
   mWindowSize = wsize;
}

//--------------------------------------------------------

int ContrastEnhanceProcess::GetWindowSize( )
{
   return mWindowSize;
}


//--------------------------------------------------------

void ContrastEnhanceProcess::SetAlphaFactor( double factor )
{
   mAlphaFactor = factor;
}

//--------------------------------------------------------

double ContrastEnhanceProcess::GetAlphaFactor( )
{
   return mAlphaFactor;
}

//--------------------------------------------------------

void ContrastEnhanceProcess::SetLowerFraction( double fraction )
{
   mLowerFraction = fraction;
}

//--------------------------------------------------------

double ContrastEnhanceProcess::GetLowerFraction( )
{
   return mLowerFraction;
}

//--------------------------------------------------------

void ContrastEnhanceProcess::SetUpperFraction( double fraction )
{
   mUpperFraction = fraction;
}

//--------------------------------------------------------
double ContrastEnhanceProcess::GetUpperFraction( )
{
   return mUpperFraction;
}

//--------------------------------------------------------

void ContrastEnhanceProcess::SetContrastEnhanceType( StiraDefinitions::ContrastEnhanceType myType )
{
   mType = myType;
}

//--------------------------------------------------------

StiraDefinitions::ContrastEnhanceType ContrastEnhanceProcess::GetContrastEnhanceType()
{
   return mType;
}

//--------------------------------------------------------

void ContrastEnhanceProcess::run()
{
   stira::image::Image* pOutImage = 0;
   
   switch ( mType )
   {
      case StiraDefinitions::CONTRAST_NEGATIVE:
      {
         pOutImage = ImageTools::Negative( mpImage );
         break;
      }
      case StiraDefinitions::CONTRAST_GAMMA:
      {
         pOutImage = ImageTools::ApplyGamma( mpImage, mGamma );
         break;
      }
      case StiraDefinitions::CONTRAST_LINEARSCALE:
      {
         pOutImage = stira::contrastenhance::HistogramTools::RobustLinearRescale( mpImage, mLowerFraction, mUpperFraction );
         break;
      }
      case StiraDefinitions::CONTRAST_DARKCHANNEL:
      {
         stira::contrastenhance::HazeRemover hr;
         pOutImage = hr.Run( mpImage );
         Image* pOutImageBis = stira::contrastenhance::HistogramTools::RobustLinearRescale( pOutImage, mLowerFraction, mUpperFraction );
         delete pOutImage;
         pOutImage = pOutImageBis;
         break;
      }
      case StiraDefinitions::CONTRAST_RETINEX:
      {
         pOutImage = stira::contrastenhance::Retinex::RunMSRCR ( mpImage, mLowerFraction, mUpperFraction, true );
         pOutImage->Rescale();
         break;
      }
      case StiraDefinitions::CONTRAST_ADAPTIVE_LUONG:
      {
         AdaptiveEnhanceLuong ael;
         ael.SetAlphaFactor( GetAlphaFactor() );
         ael.SetWindowSize( GetWindowSize() );
         pOutImage = ael.Run( mpImage );
         std::string outName = mpImage->GetImageName() + std::string("-AdaptiveLuong");
         pOutImage->SetImageName( outName );
         break;
      }
      case StiraDefinitions::CONTRAST_WAVELET:
      {
         int nrScales = 3;
         int nrOrientations = 6;
         PyramidContrastEnhancer pce( 0.5 );
         if ( mpImage->GetNumberOfBands() == 3 )
         {
            Image* pImageLuv = mpImage->Clone();
            
            pImageLuv->sRGBToLuv();
            pOutImage = pce.Run3Colors( pImageLuv, nrScales, nrOrientations, false );
            pOutImage->LuvTosRGB();
            
            delete pImageLuv;
         }
         else
         {
            Image* pTmpImage = pce.Run( mpImage, nrScales, nrOrientations, false );
            pOutImage = stira::contrastenhance::HistogramTools::RobustLinearRescale( mpImage, 0.03, 0.99 );
            delete pTmpImage;
         }
         
         std::string outName = mpImage->GetImageName() + std::string("-WaveletContrastEnhanced");
         pOutImage->SetImageName( outName );
            
         break;
      }
      case StiraDefinitions::CONTRAST_HISTOGRAM_EQUALIZE_RGB:
      {
         if ( mpImage->GetNumberOfBands() == 3 )  // equalize V in Lab space
         {
            pOutImage = stira::contrastenhance::HistogramTools::HistogramEqualizeHSI( mpImage );
            break;
         }
      }
      default: // equalize all bands independantly
      {
         pOutImage = stira::contrastenhance::HistogramTools::HistogramEqualizePerBand( mpImage );
      }
   }
   AddResult( pOutImage );
   // ownership of this image is transfered through GetImage() to ImageDataList
}

//--------------------------------------------------------

