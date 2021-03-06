
/***********************************************************************************
 *   Copyright (C) 2009 by Filip Rooms                                             *
 *                                                                                 *
 *  Terms and conditions for using this software in any form are provided in the   *
 *  file COPYING, which can be found in the root directory of this project.        *
 *                                                                                 *
 *   Contact data: filip.rooms@gmail.com                                           *
 *                 http://www.filiprooms.be/                                       *
 *                                                                                 *
 ***********************************************************************************/

#include "../../common/common/MathUtils.h"
#include "FractalGenerator.h"
#include <complex>

namespace stira {
namespace imagetools {

FractalGenerator::FractalGenerator()
{
   mMaxNumberOfIterations = 1000;
   mEscapeRadius = 2.0;
   mEscapeRadiusSquared = mEscapeRadius * mEscapeRadius;
   mpColorTransformer = new TransformColorSpace;
   mPixelWidth  = 800.0;
   mPixelHeight = 800.0;
   mWidthHeightRatio = mPixelHeight / mPixelWidth;

   // create color interpolants

   std::vector< std::pair<double, double> > dataRed;
   dataRed.push_back( std::pair<double, double>(  -0.1425,   0.0 ) );
   dataRed.push_back( std::pair<double, double>(   0.0000,   0.0 ) );
   dataRed.push_back( std::pair<double, double>(   0.1600,  32.0 ) );
   dataRed.push_back( std::pair<double, double>(   0.4200, 237.0 ) );
   dataRed.push_back( std::pair<double, double>(   0.6425, 255.0 ) );
   dataRed.push_back( std::pair<double, double>(   0.8575,   0.0 ) );
   dataRed.push_back( std::pair<double, double>(   1.0000,   0.0 ) );
   mpInterpolateRed = new common::MonotonicCubicSplineInterpolator( dataRed );

   std::vector< std::pair<double, double> > dataGreen;
   dataGreen.push_back( std::pair<double, double>(  -0.1425,   2.0 ) );
   dataGreen.push_back( std::pair<double, double>(   0.0000,   7.0 ) );
   dataGreen.push_back( std::pair<double, double>(   0.1600, 107.0 ) );
   dataGreen.push_back( std::pair<double, double>(   0.4200, 255.0 ) );
   dataGreen.push_back( std::pair<double, double>(   0.6425, 170.0 ) );
   dataGreen.push_back( std::pair<double, double>(   0.8575,   2.0 ) );
   dataGreen.push_back( std::pair<double, double>(   1.0000,   7.0 ) );
   mpInterpolateGreen = new common::MonotonicCubicSplineInterpolator( dataGreen );

   std::vector< std::pair<double, double> > dataBlue;
   dataBlue.push_back( std::pair<double, double>(  -0.1425,   0.0 ) );
   dataBlue.push_back( std::pair<double, double>(   0.0000, 100.0 ) );
   dataBlue.push_back( std::pair<double, double>(   0.1600, 203.0 ) );
   dataBlue.push_back( std::pair<double, double>(   0.4200, 255.0 ) );
   dataBlue.push_back( std::pair<double, double>(   0.6425,   0.0 ) );
   dataBlue.push_back( std::pair<double, double>(   0.8575,   0.0 ) );
   dataBlue.push_back( std::pair<double, double>(   1.0000, 100.0 ) );
   mpInterpolateBlue = new common::MonotonicCubicSplineInterpolator( dataBlue );
}

//------------------------------------------------------------------------------

void FractalGenerator::SetRenderDimensions( int width, int height )
{
    mPixelWidth  = width;
    mPixelHeight = height;
    mWidthHeightRatio = mPixelHeight / mPixelWidth;
}

//------------------------------------------------------------------------------

FractalGenerator::~FractalGenerator()
{
   delete mpColorTransformer;
   delete mpInterpolateRed;
   delete mpInterpolateGreen;
   delete mpInterpolateBlue;
}

//------------------------------------------------------------------------------

void FractalGenerator::SetMaxNumberOfIterations( int maxNr )
{
   mMaxNumberOfIterations = maxNr;
}

//------------------------------------------------------------------------------

void FractalGenerator::SetEscapeRadius( double radius )
{
   mEscapeRadius = radius;
   mEscapeRadiusSquared = radius * radius;
}

//------------------------------------------------------------------------------

double FractalGenerator::GetResolutionX()
{
    return mResolutionX;
}

//------------------------------------------------------------------------------

double FractalGenerator::GetResolutionY()
{
    return mResolutionY;
}

//------------------------------------------------------------------------------

double FractalGenerator::GetPixelWidth()
{
    return mPixelWidth;
}

//------------------------------------------------------------------------------

double FractalGenerator::GetPixelHeight()
{
    return mPixelHeight;
}

//------------------------------------------------------------------------------

common::Point<double> FractalGenerator::GetMathCenterPoint()
{
    return common::Point<double>( mMathCenterX, mMathCenterY );
}

//------------------------------------------------------------------------------

double FractalGenerator::GetMathWidth()
{
    return mMathWidth;
}

//------------------------------------------------------------------------------

ColorValue FractalGenerator::AssignColorContinuous( int iterationNumber, double& lastModulus )
{
   if (iterationNumber == mMaxNumberOfIterations)
   {
      ColorValue cv = ColorValue( 0.0, 0.0, 0.0, TYPE_RGB );
      return cv;
   }
   else
   {
      double tmpValue = iterationNumber + 1.0 - log(log(lastModulus)) / log ( mEscapeRadius );
      tmpValue = 0.95 + 5.0 * tmpValue;
      double remainder = common::MathUtils::ApplyModulo( tmpValue, 280.0 ) + 180;

      ColorValue hsvValue;
      hsvValue.c[0] = remainder;
      hsvValue.c[1] = 0.6;
      hsvValue.c[2] = 1.0;
      hsvValue.type = TYPE_HSV;

      return mpColorTransformer->HSVtoRGB( hsvValue );
   }
}

//------------------------------------------------------------------------------

// http://stackoverflow.com/questions/16500656/which-color-gradient-is-used-to-color-mandelbrot-in-wikipedia
ColorValue FractalGenerator::AssignColorUltraFractal( double iterationNumber, double& lastModulus )
{
   if (iterationNumber == mMaxNumberOfIterations)
   {
      ColorValue cv = ColorValue( 0.0, 0.0, 0.0, TYPE_RGB );
      return cv;
   }
   else
   {
      double log_zn = log( lastModulus ) / 2.0;
      double nu = log( log_zn / log(2.0) ) / log(2.0);
      // Rearranging the potential function.
      // Dividing log_zn by log(2) instead of log(N = 1<<8)
      // because we want the entire palette to range from the
      // center to radius 2, NOT our bailout radius.
      iterationNumber = iterationNumber + 1.0 - nu;
      double ampFactor = 10.0;
      double tmpValue = common::MathUtils::ApplyModulo(  ( ampFactor * iterationNumber / mMaxNumberOfIterations), 1.0 );
      return InterpolateColorUltraFractal( tmpValue );
   }
}

//------------------------------------------------------------------------------
ColorValue FractalGenerator::InterpolateColorUltraFractal( double smoothColor )
{
   ColorValue interPolated;
   interPolated.SetColorValue( mpInterpolateRed->Interpolate( smoothColor),
                               mpInterpolateGreen->Interpolate( smoothColor),
                               mpInterpolateBlue->Interpolate( smoothColor), TYPE_RGB );

   return interPolated;
}

//------------------------------------------------------------------------------

int FractalGenerator::GiveLastIteration( double x, double y, double Cx, double Cy, double& lastModulus )
{
   int iterationNumber = 0;

   double xSquared = x * x;
   double ySquared = y * y;

   while ( ( (xSquared + ySquared) <= mEscapeRadiusSquared ) && ( iterationNumber < mMaxNumberOfIterations ) )
   {
      double xTmp = xSquared - ySquared + Cx;
      double yTmp = 2.0 * x * y + Cy;

      x = xTmp;
      y = yTmp;

      xSquared = x * x;
      ySquared = y * y;
      iterationNumber++;
   }

   lastModulus = xSquared + ySquared;

   return iterationNumber;
}

//------------------------------------------------------------------------------

Image* FractalGenerator::CreateMandelbrot( double centerX, double centerY, double width )
{
   mMathCenterX = centerX;
   mMathCenterY = centerY;
   mMathWidth = width;
   double height = width * (double)(mPixelHeight) / (double)(mPixelWidth);
   double topX    = centerX - width / 2.0;
   double bottomX = centerX + width / 2.0;

   double topY    = centerY - height / 2.0;
   double bottomY = centerY + height / 2.0;
   return CreateMandelbrot( topX, topY, bottomX, bottomY );
}

//------------------------------------------------------------------------------

bool FractalGenerator::TestIsInMandelbrotMainBody( double x, double y )
{
    double p = sqrt( (x - 0.25) * (x - 0.25) + y * y);
    if ( x < ( p - 2*p*p + 0.25))
    {
        return true;
    }
    else if ( ((x+1.0)*(x+1.0) + y*y) < (1.0 / 16.0) )
    {
        return true;
    }
    else
    {
        return false;
    }
}

//------------------------------------------------------------------------------

Image* FractalGenerator::CreateMandelbrot( double topX, double topY, double bottomX, double bottomY )
{
   double mathematicalWidth  = bottomX - topX;
   double mathematicalHeight = bottomY - topY;

   mResolutionX = mPixelWidth / mathematicalWidth;
   mResolutionY = mPixelHeight / mathematicalHeight;

   mMaxNumberOfIterations += (50*log10(mResolutionX));
   
   std::cout << "Generating Mandelbrot of w = " << mPixelWidth << " and h = " << mPixelHeight << std::endl << std::flush;
   std::cout << "   \t mResolutionX = " << mResolutionX << " and mResolutionY = " << mResolutionY << std::endl << std::flush;
   std::cout << "   \t mMaxNumberOfIterations = " << mMaxNumberOfIterations << std::endl << std::flush;
   
   Image* pFractal = new Image( (int)(mPixelWidth), (int)(mPixelHeight), 3 );
   
   for (int y = 0; y < mPixelHeight; y++)
   {
      for (int x = 0; x < mPixelWidth; x++)
      {
         int lastIterationNumber;
         double x0 = topX + (double)(x) / mResolutionX;
         double y0 = topY + (double)(y) / mResolutionY;
         
         double xx = 0.0;
         double yy = 0.0;
         double lastModulus;

         if (TestIsInMandelbrotMainBody( x0, y0 ))
         {
             lastIterationNumber = mMaxNumberOfIterations;
         }
         else
         {
             lastIterationNumber = GiveLastIteration( xx, yy, x0, y0, lastModulus );
         }

         //pFractal->SetColor( x, y, AssignColorContinuous( lastIterationNumber, lastModulus ) );
         pFractal->SetColor( x, y, AssignColorUltraFractal( lastIterationNumber, lastModulus ) );
      }
   }
   
   return pFractal;
}

//------------------------------------------------------------------------------

Image* FractalGenerator::CreateJulia( double centerX, double centerY, double width, double Cx, double Cy )
{
   mMathCenterX = centerX;
   mMathCenterY = centerY;
   mMathWidth = width;
   double height = width * (double)(mPixelHeight) / (double)(mPixelWidth);
   double topX    = centerX - width / 2.0;
   double bottomX = centerX + width / 2.0;

   double topY    = centerY - height / 2.0;
   double bottomY = centerY + height / 2.0;
   return CreateJulia( topX, topY, bottomX, bottomY, Cx, Cy );
}

//------------------------------------------------------------------------------

Image* FractalGenerator::CreateJulia( double topX, double topY, double bottomX, double bottomY, double Cx, double Cy )
{
   double mathematicalWidth  = bottomX - topX;
   double mathematicalHeight = bottomY - topY;

   mResolutionX = mPixelWidth / mathematicalWidth;
   mResolutionY = mPixelHeight / mathematicalHeight;
   
   std::cout << "Generating Julia of w = " << mPixelWidth << " and h = " << mPixelHeight << std::endl << std::flush;
   std::cout << "   \t mResolutionX = " << mResolutionX << " and mResolutionY = " << mResolutionY << std::endl << std::flush;
   
   Image* pFractal = new Image( (int)(mPixelWidth), (int)(mPixelHeight), 3 );

   for (int y = 0; y < mPixelHeight; y++)
   {
      for (int x = 0; x < mPixelWidth; x++)
      {
         double x0 = topX + (double)(x) / mResolutionX;
         double y0 = topY + (double)(y) / mResolutionY;
         
         double lastModulus;
         int lastIterationNumber = GiveLastIteration( x0, y0, Cx, Cy, lastModulus );

         //pFractal->SetColor( x, y, AssignColorContinuous( lastIterationNumber, lastModulus ) );
         pFractal->SetColor( x, y, AssignColorUltraFractal( lastIterationNumber, lastModulus ) );
      }
   }
   
   return pFractal;
}

//------------------------------------------------------------------------------

}
}
