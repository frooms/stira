
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
#include "../../stira/image/tools/GridGenerator.h"
#include "../../stira/image/tools/NumberGridTools.h"
#include "../../stira/filter/filter/GaussConvolve.h"
#include "../../stira/image/color/GretagMacbethColorChecker.h"

using namespace std;
using namespace stira::image;

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
         pGrid = stira::image::GridGenerator::GenerateEmpty( width, height );
         imageName = std::string("EmptyImage");
         break;
      }
      case StiraDefinitions::SYNTHETIC_EMPTYPLUSNOISE:
      {
         pGrid = stira::image::GridGenerator::GenerateEmptyPlusGaussianNoise( width, height );
         imageName = std::string("EmptyNoisyImage");
         break;
      }
      case StiraDefinitions::SYNTHETIC_HORIZONTALGRADIENT:
      {
         pGrid = stira::image::GridGenerator::GenerateHorizontalGradient( width, height );
         imageName = std::string("HorizontalGradient");
         break;
      }
      case StiraDefinitions::SYNTHETIC_VERTICALGRADIENT:
      {
         pGrid = stira::image::GridGenerator::GenerateVerticalGradient( width, height );
         imageName = std::string("VerticalGradient");
         break;
      }
      case StiraDefinitions::SYNTHETIC_HORIZONTALSINE:
      {
         pGrid = stira::image::GridGenerator::GenerateHorizontalSineWave( width, height, frequency );
         imageName = std::string("HorizontalSine");
         break;
      }
      case StiraDefinitions::SYNTHETIC_VERTICALSINE:
      {
         pGrid = stira::image::GridGenerator::GenerateVerticalSineWave( width, height, frequency );
         imageName = std::string("VerticalSine");
         break;
      }
      case StiraDefinitions::SYNTHETIC_EUCLIDEANSPOTS:
      {
         pGrid = stira::image::GridGenerator::GenerateEuclideanSpots( width, height, frequency );
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
         pGrid = stira::image::GridGenerator::GenerateStarChart( width, (int)(frequency) );
         imageName = std::string("StarChart");
         break;
      }
      case StiraDefinitions::SYNTHETIC_LOGFREQUENCYCONTRAST:
      {
         pGrid = stira::image::GridGenerator::GenerateLogFrequencyContrastChart( );
         imageName = std::string("LogFrequencyContrastChart");
         break;
      }
      case StiraDefinitions::SYNTHETIC_INVERSEZONEPLATE:
      {
         pGrid = stira::image::GridGenerator::GenerateInverseZonePlate ( );
         imageName = std::string("InverseZonePlate");
         break;
      }
      case StiraDefinitions::SYNTHETIC_SHEPPLOGAN:
      {
         double mmin, mmax;
         pGrid = stira::image::GridGenerator::GenerateSheppLogan( 15.0 );
         
         stira::image::NumberGridTools<double>::GetMinMax( pGrid, mmin, mmax );
         double factor = 255.0 / mmax;
         pGrid->MultiplyWith( factor );
         imageName = std::string("SheppLogan");
         break;
      }
      case StiraDefinitions::SYNTHETIC_GRETAGMACBETH:
      {
         pOutImage = stira::image::GretagMacbethColorChecker::Generate( 4, 60 );
         imageName = std::string("GretagMacbeth");
         break;
      }
      case StiraDefinitions::SYNTHETIC_ISING:
      {
         double mmin, mmax;
         ArrayGrid<int>* pGridTmp = stira::image::GridGenerator::GenerateIsingTexture( );
         pGrid = stira::image::NumberGridTools<int>::CreateDoubleGrid( pGridTmp );
         stira::image::NumberGridTools<double>::GetMinMax( pGrid, mmin, mmax );
         double factor = 255.0 / mmax;
         pGrid->MultiplyWith( factor );
         imageName = std::string("IsingTexture");
         delete pGridTmp;
         break;
      }
      case StiraDefinitions::SYNTHETIC_ZONEPLATE:
      default:
      {
         pGrid = stira::image::GridGenerator::GenerateZonePlate ( );
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
