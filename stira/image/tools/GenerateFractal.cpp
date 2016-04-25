
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
#include "GenerateFractal.h"
#include <complex>

namespace stira {
namespace image {

GenerateFractal::GenerateFractal()
{
   mMaxNumberOfIterations = 1000;
   mEscapeRadius = 2.0;
   mEscapeRadiusSquared = mEscapeRadius * mEscapeRadius;
   mpColorTransformer = new TransformColorSpace;
   mPixelWidth  = 800;
   mPixelHeight = 800;
   mWidthHeightRatio = (double)(mPixelHeight) / (double)(mPixelWidth);

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

void GenerateFractal::SetRenderDimensions( int width, int height )
{
    mPixelWidth  = width;
    mPixelHeight = height;
    mWidthHeightRatio = (double)(mPixelHeight) / (double)(mPixelWidth);
}

//------------------------------------------------------------------------------

GenerateFractal::~GenerateFractal()
{
   delete mpColorTransformer;
   delete mpInterpolateRed;
   delete mpInterpolateGreen;
   delete mpInterpolateBlue;
}

//------------------------------------------------------------------------------

void GenerateFractal::SetMaxNumberOfIterations( int maxNr )
{
   mMaxNumberOfIterations = maxNr;
}

//------------------------------------------------------------------------------

void GenerateFractal::SetEscapeRadius( double radius )
{
   mEscapeRadius = radius;
   mEscapeRadiusSquared = radius * radius;
}

//------------------------------------------------------------------------------

int GenerateFractal::GetResolutionX()
{
    return mResolutionX;
}

int GenerateFractal::GetResolutionY()
{
    return mResolutionY;
}

int GenerateFractal::GetPixelWidth()
{
    return mPixelWidth;
}

int GenerateFractal::GetPixelHeight()
{
    return mPixelHeight;
}

common::Point<double> GenerateFractal::GetMathCenterPoint()
{
    return common::Point<double>( mMathCenterX, mMathCenterY );
}

double GenerateFractal::GetMathWidth()
{
    return mMathWidth;
}

//------------------------------------------------------------------------------

ColorValue GenerateFractal::AssignColorContinuous( int iterationNumber, double& lastModulus )
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
      double remainder = common::MathUtils::ApplyModulo( tmpValue, 120.0 ) + 180;

      ColorValue hsvValue;
      hsvValue.c[0] = remainder;
      hsvValue.c[1] = 0.6;
      hsvValue.c[2] = 1.0;
      hsvValue.type = TYPE_HSV;

      return mpColorTransformer->HSVtoRGB( hsvValue );
   }
}

//------------------------------------------------------------------------------

ColorValue GenerateFractal::AssignColorUltraFractal( double iterationNumber, double& lastModulus )
{
   if (iterationNumber == mMaxNumberOfIterations)
   {
      ColorValue cv = ColorValue( 0.0, 0.0, 0.0, TYPE_RGB );
      return cv;
   }
   else
   {
      double factor = 6.0;
      double tmpValue = iterationNumber + 1.0 - log(log(lastModulus)) / log ( mEscapeRadius );
      tmpValue = common::MathUtils::ApplyModulo(  (factor * tmpValue / mMaxNumberOfIterations), 1.0 );
      //double tmpValue = (double)(iterationNumber) / (double)( mMaxNumberOfIterations );
      return InterpolateColorUltraFractal( tmpValue );
   }
}

//------------------------------------------------------------------------------
// http://stackoverflow.com/questions/16500656/which-color-gradient-is-used-to-color-mandelbrot-in-wikipedia
ColorValue GenerateFractal::InterpolateColorUltraFractal( double smoothColor )
{
   ColorValue interPolated;
   interPolated.SetColorValue( mpInterpolateRed->Interpolate( smoothColor),
                               mpInterpolateGreen->Interpolate( smoothColor),
                               mpInterpolateBlue->Interpolate( smoothColor), TYPE_RGB );

   return interPolated;
}

//------------------------------------------------------------------------------

int GenerateFractal::GiveLastIteration( double x, double y, double Cx, double Cy, double& lastModulus )
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

   lastModulus = sqrt( xSquared + ySquared );

   return iterationNumber;
}

//------------------------------------------------------------------------------

Image* GenerateFractal::CreateMandelbrot( double centerX, double centerY, double width )
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

bool GenerateFractal::TestIsInMandelbrotMainBody( double x, double y )
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

Image* GenerateFractal::CreateMandelbrot( double topX, double topY, double bottomX, double bottomY )
{
   double mathematicalWidth  = bottomX - topX;
   double mathematicalHeight = bottomY - topY;

   mResolutionX = mPixelWidth / mathematicalWidth;
   mResolutionY = mPixelHeight / mathematicalHeight;
   
   std::cout << "Generating Mandelbrot of w = " << mPixelWidth << " and h = " << mPixelHeight << std::endl << std::flush;
   std::cout << "   \t mResolutionX = " << mResolutionX << " and mResolutionY = " << mResolutionY << std::endl << std::flush;
   
   Image* pFractal = new Image( mPixelWidth, mPixelHeight, 3 );
   
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

Image* GenerateFractal::CreateJulia( double centerX, double centerY, double width, double Cx, double Cy )
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

Image* GenerateFractal::CreateJulia( double topX, double topY, double bottomX, double bottomY, double Cx, double Cy )
{
   double mathematicalWidth  = bottomX - topX;
   double mathematicalHeight = bottomY - topY;

   mResolutionX = mPixelWidth / mathematicalWidth;
   mResolutionY = mPixelHeight / mathematicalHeight;
   
   std::cout << "Generating Julia of w = " << mPixelWidth << " and h = " << mPixelHeight << std::endl << std::flush;
   std::cout << "   \t mResolutionX = " << mResolutionX << " and mResolutionY = " << mResolutionY << std::endl << std::flush;
   
   Image* pFractal = new Image( mPixelWidth, mPixelHeight, 3 );

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
