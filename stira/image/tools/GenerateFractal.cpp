
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
   mPixelWidth  = 2000;
   mPixelHeight = 1500;
   mWidthHeightRatio = (double)(mPixelHeight) / (double)(mPixelWidth);
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

ColorValue GenerateFractal::AssignColor( int iterationNumber )
{
   if (iterationNumber == mMaxNumberOfIterations)
   {
      ColorValue cv = ColorValue( 0.0, 0.0, 0.0, TYPE_RGB );
      return cv;
   }
   else
   {
      double tmpValue = (double)((2 * iterationNumber) % 360);
      ColorValue hsvValue;
      hsvValue.c[0] = tmpValue;
      hsvValue.c[1] = 1.0;
      hsvValue.c[2] = 1.0;
      hsvValue.type = TYPE_HSV;
      return mpColorTransformer->HSVtoRGB( hsvValue );
   }
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

ColorValue GenerateFractal::AssignColorUltraFractal( double iterationNumber )
{
   if (iterationNumber == mMaxNumberOfIterations)
   {
      ColorValue cv = ColorValue( 0.0, 0.0, 0.0, TYPE_RGB );
      return cv;
   }
   else
   {
      double tmpValue = common::MathUtils::ApplyModulo( 5.0 * (double)(iterationNumber) / (double)(mMaxNumberOfIterations), 1.0);
      return InterpolateColorUltraFractal( tmpValue );
   }
}

//------------------------------------------------------------------------------
// http://stackoverflow.com/questions/16500656/which-color-gradient-is-used-to-color-mandelbrot-in-wikipedia
ColorValue GenerateFractal::InterpolateColorUltraFractal( double smoothColor )
{
   ColorValue interPolated;
   double r, g, b;
   double pos0 = 0.0;     ColorValue cv0(0,   7,   100);
   double pos1 = 0.16;    ColorValue cv1(32,  107, 203);
   double pos2 = 0.42;    ColorValue cv2(237, 255, 255);
   double pos3 = 0.6425;  ColorValue cv3(255, 170, 0);
   double pos4 = 0.8575;  ColorValue cv4(0,   2,   0);


   if (smoothColor < pos1)
   {
       r = common::MathUtils::LinearInterpolate( pos0, cv0.c[0], pos1, cv1.c[0], smoothColor );
       g = common::MathUtils::LinearInterpolate( pos0, cv0.c[1], pos1, cv1.c[1], smoothColor );
       b = common::MathUtils::LinearInterpolate( pos0, cv0.c[2], pos1, cv1.c[2], smoothColor );
   }
   else if (smoothColor < pos2)
   {
       r = common::MathUtils::LinearInterpolate( pos1, cv1.c[0], pos2, cv2.c[0], smoothColor );
       g = common::MathUtils::LinearInterpolate( pos1, cv1.c[1], pos2, cv2.c[1], smoothColor );
       b = common::MathUtils::LinearInterpolate( pos1, cv1.c[2], pos2, cv2.c[2], smoothColor );
   }
   else if (smoothColor < pos3)
   {
       r = common::MathUtils::LinearInterpolate( pos2, cv2.c[0], pos3, cv3.c[0], smoothColor );
       g = common::MathUtils::LinearInterpolate( pos2, cv2.c[1], pos3, cv3.c[1], smoothColor );
       b = common::MathUtils::LinearInterpolate( pos2, cv2.c[2], pos3, cv3.c[2], smoothColor );
   }
   else if (smoothColor < pos4)
   {
       r = common::MathUtils::LinearInterpolate( pos3, cv3.c[0], pos4, cv4.c[0], smoothColor );
       g = common::MathUtils::LinearInterpolate( pos3, cv3.c[1], pos4, cv4.c[1], smoothColor );
       b = common::MathUtils::LinearInterpolate( pos3, cv3.c[2], pos4, cv4.c[2], smoothColor );
   }
   else
   {
       r = common::MathUtils::LinearInterpolate( pos4, cv4.c[0], pos0, cv0.c[0], smoothColor );
       g = common::MathUtils::LinearInterpolate( pos4, cv4.c[1], pos0, cv0.c[1], smoothColor );
       b = common::MathUtils::LinearInterpolate( pos4, cv4.c[2], pos0, cv0.c[2], smoothColor );
   }

   interPolated.SetColorValue( r, g, b, TYPE_RGB );

   return interPolated;
}

//------------------------------------------------------------------------------

int GenerateFractal::GiveLastIteration( double x, double y, double Cx, double Cy, double& lastModulus )
{
   double xSquared = x * x;
   double ySquared = y * y;
   
   int iterationNumber = 0;
   
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
   double mathematicalWidth  = topX - bottomX;
   double mathematicalHeight = topY - bottomY;

   mResolutionX = mPixelWidth / mathematicalWidth;
   mResolutionY = mPixelHeight / mathematicalHeight;
   
   std::cout << "Generating Mandelbrot of w = " << mPixelWidth << " and h = " << mPixelHeight << std::endl << std::flush;
   
   Image* pFractal = new Image( mPixelWidth, mPixelHeight, 3 );
   
   for (int y = 0; y < mPixelHeight; y++)
   {
      for (int x = 0; x < mPixelWidth; x++)
      {
         int lastIterationNumber;
         double x0 = bottomX + (double)(x) / mResolutionX;
         double y0 = topY    - (double)(y) / mResolutionY;
         
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
         pFractal->SetColor( x, y, AssignColorUltraFractal( lastIterationNumber ) );
      }
   }
   
   return pFractal;
}

//------------------------------------------------------------------------------

Image* GenerateFractal::CreateJulia( double centerX, double centerY, double width, double Cx, double Cy )
{
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
   double mathematicalWidth  = topX - bottomX;
   double mathematicalHeight = topY - bottomY;

   mResolutionX = mPixelWidth / mathematicalWidth;
   mResolutionY = mPixelHeight / mathematicalHeight;
   
   std::cout << "Generating Julia of w = " << mPixelWidth << " and h = " << mPixelHeight << std::endl << std::flush;
   
   Image* pFractal = new Image( mPixelWidth, mPixelHeight, 3 );

   for (int y = 0; y < mPixelHeight; y++)
   {
      for (int x = 0; x < mPixelWidth; x++)
      {
         double x0 = bottomX + (double)(x) / mResolutionX;
         double y0 = topY    - (double)(y) / mResolutionY;
         
         double lastModulus;
         int lastIterationNumber = GiveLastIteration( x0, y0, Cx, Cy, lastModulus );

         //pFractal->SetColor( x, y, AssignColorContinuous( lastIterationNumber, lastModulus ) );
         pFractal->SetColor( x, y, AssignColorUltraFractal( lastIterationNumber ) );
      }
   }
   
   return pFractal;
}

//------------------------------------------------------------------------------

}
}
