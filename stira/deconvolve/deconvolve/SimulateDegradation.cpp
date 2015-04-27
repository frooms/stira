
/***********************************************************************************
 *   Copyright (C) 2011 by Filip Rooms                                             *
 *                                                                                 *
 *  Terms and conditions for using this software in any form are provided in the   *
 *  file COPYING, which can be found in the root directory of this project.        *
 *                                                                                 *
 *   Contact data: filip.rooms@gmail.com                                           *
 *                 http://www.filiprooms.be/                                       *
 *                                                                                 *
 ***********************************************************************************/

#include "SimulateDegradation.h"

#include "../../image/tools/GridGenerator.h"
#include "../../fouriertools/fouriertools/FFT.h"

#include "../../common/common/MathUtils.h"

namespace stira{
namespace deconvolve{

using namespace stira::image;
using namespace stira::fouriertools;
using namespace stira::common;

SimulateDegradation::SimulateDegradation()
{
}

//----------------------------------------------------------------------------------------------

SimulateDegradation::~SimulateDegradation()
{
}

//----------------------------------------------------------------------------------------------

image::ArrayGrid<double>* SimulateDegradation::GeneratePSF( int width, int height, BlurType myBlurType, std::vector<double> vBlurParameters )
{
   ArrayGrid<double>* pBlurKernel = 0;
   switch( myBlurType )
   {
      case BLURTYPE_AIRY:
      {
         pBlurKernel = GridGenerator::GenerateAiry( width, height, vBlurParameters[0]);
         break;
      }
      case BLURTYPE_BOX:
      {
         pBlurKernel = GridGenerator::GenerateSquare( width, height, vBlurParameters[0]);
         break;
      }
      case BLURTYPE_DISC:
      {
         pBlurKernel = GridGenerator::GenerateDisk( width, height, vBlurParameters[0]);
         break;
      }
      case BLURTYPE_LINE:
      {
         pBlurKernel = GridGenerator::GenerateLine( width, height, vBlurParameters[0], vBlurParameters[1] );
         break;
      }
      case BLURTYPE_GAUSSIAN:
      default:
      {
         if (vBlurParameters.size() == 3)
         {
            pBlurKernel =  GridGenerator::GenerateGaussian( width, height, vBlurParameters[0], vBlurParameters[1], vBlurParameters[2] );
         }
         else if (vBlurParameters.size() == 2)
         {
            pBlurKernel =  GridGenerator::GenerateGaussian( width, height, vBlurParameters[0], vBlurParameters[1] );
         }
         else
         {
            pBlurKernel =  GridGenerator::GenerateGaussian( width, height, vBlurParameters[0] );
         }
         break;
      }
   }
   return pBlurKernel;
}

//----------------------------------------------------------------------------------------------

bool SimulateDegradation::SimulateNoise( image::ArrayGrid<double>* pGridIn, NoiseType myNoiseType, double noiseLevel )
{
   int width  = pGridIn->GetWidth();
   int height = pGridIn->GetHeight();

   Random rn;
   double mmin = 0.0;
   double mmax = 255.0;

   switch( myNoiseType )
   {
      case NOISETYPE_POISSON:
      {
         for (int y = 0; y < height; y++)
         {
            for (int x = 0; x < width; x++)
            {
               pGridIn->SetValue(x, y, MathUtils::ClipValue( noiseLevel * ( (rn.poisson( (pGridIn->GetValue(x, y)  / noiseLevel) + 0.5) ) ), mmin, mmax ) );
            }
         }
         break;
      }
      case NOISETYPE_SALTANDPEPPER:
      {
         for (int y = 0; y < height; y++)
         {
            for (int x = 0; x < width; x++)
            {
               double value1 = rn.uniform( );
               double value2 = rn.uniform( );
               if (value1 < noiseLevel)
               {
                  if (value2 < 0.5)
                  {
                     pGridIn->SetValue(x, y, mmin);
                  }
                  else
                  {
                     pGridIn->SetValue(x, y, mmax);
                  }
               }
            }
         }
         break;
      }
      case NOISETYPE_GAUSSIAN:
      default:
      {
         for (int y = 0; y < height; y++)
         {
            for (int x = 0; x < width; x++)
            {
               pGridIn->SetValue(x, y, MathUtils::ClipValue( (pGridIn->GetValue(x, y) + rn.normal( 0.0, noiseLevel ) ), mmin, mmax) );
            }
         }
         break;
      }
   }
   return true;
}

//----------------------------------------------------------------------------------------------

image::ArrayGrid<double>* SimulateDegradation::Run( image::ArrayGrid<double>* pGridIn, NoiseType myNoiseType, double noiseLevel, BlurType myBlurType, std::vector<double> vBlurParameters )
{
   image::ArrayGrid<double>* pBlurKernel = GeneratePSF( pGridIn->GetWidth(), pGridIn->GetHeight(), myBlurType, vBlurParameters );

   image::ArrayGrid<double>* pGridOut = FFT::Convolve( pGridIn, pBlurKernel );
   delete pBlurKernel;
   SimulateNoise(  pGridOut, myNoiseType, noiseLevel );
   return pGridOut;
}

//----------------------------------------------------------------------------------------------

image::Image* SimulateDegradation::Run( image::Image* pImageIn, NoiseType myNoiseType, double noiseLevel, BlurType myBlurType, std::vector<double> vBlurParameters )
{
   image::ArrayGrid<double>* pBlurKernel = GeneratePSF( pImageIn->GetWidth(), pImageIn->GetHeight(), myBlurType, vBlurParameters );

   image::Image* pImageOut = FFT::Convolve( pImageIn, pBlurKernel );
   delete pBlurKernel;

   for (int bandID = 0; bandID < pImageIn->GetNumberOfBands(); bandID++)
   {
      SimulateNoise( pImageOut->GetBands()[bandID], myNoiseType, noiseLevel );
   }

   return pImageOut;
}

//----------------------------------------------------------------------------------------------

}
}
