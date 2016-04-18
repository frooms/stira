
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

      double remainder = common::MathUtils::ApplyModulo( tmpValue, 120.0 ) + 120;

      ColorValue hsvValue;
      hsvValue.c[0] = remainder;
      hsvValue.c[1] = 0.6;
      hsvValue.c[2] = 1.0;
      hsvValue.type = TYPE_HSV;
      return mpColorTransformer->HSVtoRGB( hsvValue );
   }
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

Image* GenerateFractal::CreateMandelbrot( double topX, double topY, double bottomX, double bottomY, double resolution )
{
   double mathematicalWidth  = topX - bottomX;
   double mathematicalHeight = topY - bottomY;
   int pixelWidth  = (int)(mathematicalWidth  * resolution + 0.5);
   int pixelHeight = (int)(mathematicalHeight * resolution + 0.5);
   
   std::cout << "Generating Mandelbrot of w = " << pixelWidth << " and h = " << pixelHeight << std::endl << std::flush;
   
   Image* pFractal = new Image( pixelWidth, pixelHeight, 3 );
   
   for (int y = 0; y < pixelHeight; y++)
   {
      for (int x = 0; x < pixelWidth; x++)
      {
         double x0 = bottomX + (double)(x) / resolution;
         double y0 = topY    - (double)(y) / resolution;
         
         double xx = 0.0;
         double yy = 0.0;
         double lastModulus;
         
         int lastIterationNumber = GiveLastIteration( xx, yy, x0, y0, lastModulus );
         
         pFractal->SetColor( x, y, AssignColorContinuous( lastIterationNumber, lastModulus ) );
      }
   }
   
   return pFractal;
}

//------------------------------------------------------------------------------


double GenerateFractal::EstimateExternalDistance( double lastZx, double lastZy,  double previousZx, double previousZy,  double previousdZx, double previousdZy)
{
   std::complex<double> Zprevious( previousZx, previousZy);
   std::complex<double> dZprevious( previousdZx, previousdZy);
   std::complex<double> Zlast( lastZx, lastZy);
   
   std::complex<double> dZlast = 2.0 * Zprevious * dZprevious + 1.0;
   return (2.0 * std::abs(Zlast) * log(std::abs(Zlast) ) / std::abs(dZlast));
}

//------------------------------------------------------------------------------

Image* GenerateFractal::CreateJulia( double topX, double topY, double bottomX, double bottomY, double resolution, double Cx, double Cy )
{
   double mathematicalWidth  = topX - bottomX;
   double mathematicalHeight = topY - bottomY;
   int pixelWidth  = (int)(mathematicalWidth  * resolution + 0.5);
   int pixelHeight = (int)(mathematicalHeight * resolution + 0.5);
   
   std::cout << "Generating Julia of w = " << pixelWidth << " and h = " << pixelHeight << std::endl << std::flush;
   
   Image* pFractal = new Image( pixelWidth, pixelHeight, 3 );


   for (int y = 0; y < pixelHeight; y++)
   {
      for (int x = 0; x < pixelWidth; x++)
      {
         double x0 = bottomX + (double)(x) / resolution;
         double y0 = topY    - (double)(y) / resolution;
         
         double lastModulus;
         int lastIterationNumber = GiveLastIteration( x0, y0, Cx, Cy, lastModulus );
         
         pFractal->SetColor( x, y,  AssignColorContinuous( lastIterationNumber, lastModulus ) );
      }
   }
   
   return pFractal;
}

//------------------------------------------------------------------------------

}
}
