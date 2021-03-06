
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

#include "GenerateImageProcess.h"
#include "../../stira/imagetools/imagegenerator/GridGenerator.h"
#include "../../stira/imagedata/simpletools/GridConverter.h"
#include "../../stira/imagedata/simpletools/GridStatistics.h"
#include "../../stira/filter/filter/GaussConvolve.h"
#include "../../stira/imagetools/imagegenerator/GretagMacbethColorChecker.h"

using namespace std;
using namespace stira::imagedata;
using namespace stira::imagetools;

GenerateImageProcess::GenerateImageProcess( ) : Process( )
{
   mProcessName = QString("Synthetic Image");
}

//--------------------------------------------------------

GenerateImageProcess::~GenerateImageProcess()
{
}

//--------------------------------------------------------

int GenerateImageProcess::GetWidth()
{
   return mWidth;
}

//--------------------------------------------------------

void GenerateImageProcess::SetWidth( int width )
{
   mWidth = width;
}

//--------------------------------------------------------

int GenerateImageProcess::GetHeight()
{
   return mHeight;
}

//--------------------------------------------------------

void GenerateImageProcess::SetHeight( int height )
{
   mHeight = height;
}

//--------------------------------------------------------

double GenerateImageProcess::GetFrequency()
{
   return mFrequency;
}

//--------------------------------------------------------

void GenerateImageProcess::SetFrequency( double frequency )
{
   mFrequency = frequency;
}

//--------------------------------------------------------

double GenerateImageProcess::GetMaxSigma()
{
   return mMaxSigma;
}

//--------------------------------------------------------

void GenerateImageProcess::SetMaxSigma( double maxSigma )
{
   mMaxSigma = maxSigma;
}

//--------------------------------------------------------

enum StiraDefinitions::SyntheticImageType GenerateImageProcess::GetType()
{
   return mImageType;
}

//--------------------------------------------------------

void GenerateImageProcess::SetType( enum StiraDefinitions::SyntheticImageType myType )
{
   mImageType = myType;
}

//--------------------------------------------------------

void GenerateImageProcess::run()
{
   int width = this->GetWidth();
   int height = this->GetHeight();
   double frequency = this->GetFrequency();
   double maxSigma = this->GetMaxSigma();
   ArrayGrid<double>* pGrid = 0;
   
   std::string imageName;
   Image* pOutImage = 0;
   switch( this->GetType() )
   {
      case StiraDefinitions::SYNTHETIC_EMPTY:
      {
         pGrid = stira::imagetools::GridGenerator::GenerateEmpty( width, height );
         imageName = std::string("EmptyImage");
         break;
      }
      case StiraDefinitions::SYNTHETIC_EMPTYPLUSNOISE:
      {
         pGrid = stira::imagetools::GridGenerator::GenerateEmptyPlusGaussianNoise( width, height );
         imageName = std::string("EmptyNoisyImage");
         break;
      }
      case StiraDefinitions::SYNTHETIC_HORIZONTALGRADIENT:
      {
         pGrid = stira::imagetools::GridGenerator::GenerateHorizontalGradient( width, height );
         imageName = std::string("HorizontalGradient");
         break;
      }
      case StiraDefinitions::SYNTHETIC_VERTICALGRADIENT:
      {
         pGrid = stira::imagetools::GridGenerator::GenerateVerticalGradient( width, height );
         imageName = std::string("VerticalGradient");
         break;
      }
      case StiraDefinitions::SYNTHETIC_HORIZONTALSINE:
      {
         pGrid = stira::imagetools::GridGenerator::GenerateHorizontalSineWave( width, height, frequency );
         imageName = std::string("HorizontalSine");
         break;
      }
      case StiraDefinitions::SYNTHETIC_VERTICALSINE:
      {
         pGrid = stira::imagetools::GridGenerator::GenerateVerticalSineWave( width, height, frequency );
         imageName = std::string("VerticalSine");
         break;
      }
      case StiraDefinitions::SYNTHETIC_EUCLIDEANSPOTS:
      {
         pGrid = stira::imagetools::GridGenerator::GenerateEuclideanSpots( width, height, frequency );
         imageName = std::string("EuclideanSpots");
         break;
      }
      case StiraDefinitions::SYNTHETIC_BLURREDBARS:
      {
         pGrid = stira::filter::GaussConvolve::CreateBlurredBars( width, height, frequency, maxSigma );
         imageName = std::string("BlurredBars");
         break;
      }
      case StiraDefinitions::SYNTHETIC_STARCHART:
      {
         pGrid = stira::imagetools::GridGenerator::GenerateStarChart( width, (int)(frequency) );
         imageName = std::string("StarChart");
         break;
      }
      case StiraDefinitions::SYNTHETIC_LOGFREQUENCYCONTRAST:
      {
         pGrid = stira::imagetools::GridGenerator::GenerateLogFrequencyContrastChart( );
         imageName = std::string("LogFrequencyContrastChart");
         break;
      }
      case StiraDefinitions::SYNTHETIC_INVERSEZONEPLATE:
      {
         pGrid = stira::imagetools::GridGenerator::GenerateInverseZonePlate ( );
         imageName = std::string("InverseZonePlate");
         break;
      }
      case StiraDefinitions::SYNTHETIC_SHEPPLOGAN:
      {
         double mmin, mmax;
         pGrid = stira::imagetools::GridGenerator::GenerateSheppLogan( 15.0 );
         
         stira::imagedata::GridStatistics<double>::GetMinMax( pGrid, mmin, mmax );
         double factor = 255.0 / mmax;
         pGrid->MultiplyWith( factor );
         imageName = std::string("SheppLogan");
         break;
      }
      case StiraDefinitions::SYNTHETIC_GRETAGMACBETH:
      {
         pOutImage = stira::imagetools::GretagMacbethColorChecker::Generate( 4, 60 );
         imageName = std::string("GretagMacbeth");
         break;
      }
      case StiraDefinitions::SYNTHETIC_ISING:
      {
         double mmin, mmax;
         ArrayGrid<int>* pGridTmp = stira::imagetools::GridGenerator::GenerateIsingTexture( );
         pGrid = stira::imagedata::GridConverter::ConvertToDouble( pGridTmp );
         stira::imagedata::GridStatistics<double>::GetMinMax( pGrid, mmin, mmax );
         double factor = 255.0 / mmax;
         pGrid->MultiplyWith( factor );
         imageName = std::string("IsingTexture");
         delete pGridTmp;
         break;
      }
      case StiraDefinitions::SYNTHETIC_ZONEPLATE:
      default:
      {
         pGrid = stira::imagetools::GridGenerator::GenerateZonePlate ( );
         imageName = std::string("ZonePlate");
         break;
      }
   }
   if (this->GetType() != StiraDefinitions::SYNTHETIC_GRETAGMACBETH)
   {
      pOutImage = new Image( pGrid );
   }
   pOutImage->SetImageName( imageName );
   AddResult( pOutImage );
   // ownership of this image is transfered through GetImage() to ImageDataList
}
