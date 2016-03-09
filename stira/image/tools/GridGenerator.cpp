
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

#include <algorithm>
#include "GridGenerator.h"
#include "../../common/common/Point.h"
#include "../../common/common/Random.h"
#include "../../common/common/MathUtils.h"
#include "../../common/common/DrawFigures.h"
#include "../../common/common/StiraMacros.h"
#include "ImageIO.h"

#define PRINT_DIAGNOSTICS

namespace stira {
namespace image {

using namespace std;
using namespace common;

//--------------------------------------------------------------------------

GridGenerator::GridGenerator()
{
}

//--------------------------------------------------------------------------

GridGenerator::~GridGenerator()
{
}

//--------------------------------------------------------------------------

ArrayGrid<double>* GridGenerator::GenerateEmpty(int width, int height, double intensity)
{
   bool needsInitialization = true;
   return new ArrayGrid<double>(width, height, needsInitialization, intensity );
}

//--------------------------------------------------------------------------

ArrayGrid<double>* GridGenerator::GenerateEmptyPlusGaussianNoise(int width, int height, double intensity, double sigma)
{
   ArrayGrid<double>* pGrid = new ArrayGrid<double>( width, height );
   Random rn;

   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         pGrid->SetValue(x, y, (intensity + rn.normal( 0.0, sigma )) );
      }
   }
   return pGrid;
}

//--------------------------------------------------------------------------

ArrayGrid<double>* GridGenerator::GenerateHorizontalGradient(int width, int height)
{
   ArrayGrid<double>* pGrid = new ArrayGrid<double>(width, height );
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         double tmpValue = (double)(x) /(double)( width ) * 256.0;
         pGrid->SetValue(x, y, tmpValue);
      }
   }
   return pGrid;
}

//--------------------------------------------------------------------------

ArrayGrid<double>* GridGenerator::GenerateVerticalGradient(int width, int height)
{
   ArrayGrid<double>* pGrid = new ArrayGrid<double>(width, height );
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         double tmpValue = (double)(y) /(double)( height ) * 256.0;
         pGrid->SetValue(x, y, tmpValue);
      }
   }
   return pGrid;
}

//--------------------------------------------------------------------------

ArrayGrid<double>* GridGenerator::GenerateHorizontalSineWave(int width, int height, double frequency)
{
   ArrayGrid<double>* pGrid = new ArrayGrid<double>(width, height );
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         double tmpValue = 127.0 + 127.0 * sin( (double)(x) / frequency);
         pGrid->SetValue(x, y, tmpValue);
      }
   }
   return pGrid;
}

//--------------------------------------------------------------------------

ArrayGrid<double>* GridGenerator::GenerateVerticalSineWave(int width, int height, double frequency)
{
   ArrayGrid<double>* pGrid = new ArrayGrid<double>(width, height );
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         double tmpValue = 127.0 + 127.0 * sin( (double)(y) / frequency);
         pGrid->SetValue(x, y, tmpValue);
      }
   }
   return pGrid;
}

//--------------------------------------------------------------------------

ArrayGrid<double>* GridGenerator::GenerateEuclideanSpots(int width, int height, double frequency)
{
   ArrayGrid<double>* pGrid = new ArrayGrid<double>(width, height );
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         double tmpValue = 127.0 + 127.0 * (cos( 2.0*M_PI*( (double)(x) / frequency)) + cos( 2.0*M_PI*( (double)(y) / frequency)));
         pGrid->SetValue(x, y, tmpValue);
      }
   }
   return pGrid;
}

//--------------------------------------------------------------------------

ArrayGrid<double>* GridGenerator::GenerateStarChart(int sideSize, int nrPeriods )
{
   double halfSize = (static_cast<double>(sideSize) / 2.0);
   assert (nrPeriods > 0);

   ArrayGrid<double>* pGrid = new ArrayGrid<double>(sideSize, sideSize );
   for (int y = 0; y < sideSize; y++)
   {
      for (int x = 0; x < sideSize; x++)
      {
         double tmpValue;
         double xx = static_cast<double>(x) - halfSize;
         double yy = static_cast<double>(y) - halfSize;
         double theta = atan2(yy, xx);
         double radius = sqrt( xx * xx + yy * yy );
         if (radius==0.0)
         {
            tmpValue = 127.0;
         }
         else
         {
            tmpValue = 127.0 + 127.0 * sin( nrPeriods * theta );
         }
         pGrid->SetValue(x, y, tmpValue);
      }
   }
   return pGrid;
}

//--------------------------------------------------------------------------

ArrayGrid<double>* GridGenerator::GenerateBars(int width, int height, int barWidth )
{
   bool needInitialisation = true;
   double initialRealValue = 0.0;
   ArrayGrid<double>* pGrid = new ArrayGrid<double>( width, height, needInitialisation, initialRealValue );
   int threshold = 2*barWidth;
   for ( int y = 0; y < height; y++)
   {
      for ( int x = 0; x < width; x++)
      {
         if (y % threshold < barWidth)
         {
            pGrid->SetValue(x, y, 255.0);
         }
      }
   }
   for ( int y = 0; y < height; y++)
   {
      for ( int x = 0; x < width; x++)
      {
         if (y % threshold < barWidth)
         {
            pGrid->SetValue(x, y, 255.0);
         }
      }
   }

   return pGrid;
}

//--------------------------------------------------------------------------

// 1) PSF generation
////////////////////

ArrayGrid<double>* GridGenerator::GenerateLine(int width, int height, double length, double angle )
{
   double sum = 0.0;
   double halfLength = length / 2.0;

   int x0 = (int)(halfLength * cos( angle ) + 0.5);
   int y0 = (int)(halfLength * sin( angle ) + 0.5);
   int x1 = -x0;
   int y1 = -y0;

   std::vector< Point<int> > pointVector = DrawFigures::BresenhamDrawLine( x0, y0, x1, y1 );

   ArrayGrid<double>* pPSFGrid = new ArrayGrid<double>(width, height);

   int nrPoints = pointVector.size();
   double psfValue = 1.0 / (double)(nrPoints);

   for( std::vector< Point<int> >::iterator it = pointVector.begin();
       it != pointVector.end();
       ++it
      )
   {
      double xx = static_cast<double>( (*it).x) + (static_cast<double>(width) / 2.0);
      double yy = static_cast<double>( (*it).y) + (static_cast<double>(height) / 2.0);
      pPSFGrid->SetValue( xx, yy, psfValue );
   }

   #ifdef PRINT_DIAGNOSTICS
   sum = 0.0;
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         sum += pPSFGrid->GetValue(x, y);
      }
   }
   cout << "Line PSF: sum = " << sum << endl << flush;
   #endif

   return pPSFGrid;
}

//--------------------------------------------------------------------------

ArrayGrid<double>* GridGenerator::GenerateSquare(int width, int height, double squareWidth)
{
   double sum = 0.0;
   double halfWidth = squareWidth / 2.0;

   ArrayGrid<double>* pPSFGrid = new ArrayGrid<double>(width, height);  // NOT initialized at construction
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         double tmpValue;
         double xx = static_cast<double>(x) - (static_cast<double>(width) / 2.0);
         double yy = static_cast<double>(y) - (static_cast<double>(height) / 2.0);

         if ( ( fabs( xx ) <= halfWidth ) && ( fabs( yy ) <= halfWidth ) )
         {
            tmpValue = 1.0;
            sum ++;
         }
         else
         {
            tmpValue = 0.0;
         }
         pPSFGrid->SetValue(x, y, tmpValue);
      }
   }
   pPSFGrid->DivideBy( sum );

   #ifdef PRINT_DIAGNOSTICS
   sum = 0.0;
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         sum += pPSFGrid->GetValue(x, y);
      }
   }
   cout << "Square PSF: sum = " << sum << endl << flush;
   #endif

   return pPSFGrid;
}

//--------------------------------------------------------------------------

ArrayGrid<double>* GridGenerator::GenerateDisk(int width, int height, double diskWidth)
{
   double sum = 0.0;
   double halfWidth = diskWidth / 2.0;

   ArrayGrid<double>* pPSFGrid = new ArrayGrid<double>(width, height);  // NOT initialized at construction
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         double tmpValue;
         double xx = static_cast<double>(x) - (static_cast<double>(width) / 2.0);
         double yy = static_cast<double>(y) - (static_cast<double>(height) / 2.0);
         double radius = L2NORM( xx, yy );
         if (radius <= halfWidth)
         {
            tmpValue = 1.0;
            sum ++;
         }
         else
         {
            tmpValue = 0.0;
         }
         pPSFGrid->SetValue(x, y, tmpValue);
      }
   }
   pPSFGrid->DivideBy( sum );

   #ifdef PRINT_DIAGNOSTICS
   sum = 0.0;
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         sum += pPSFGrid->GetValue(x, y);
      }
   }
   cout << "Disk PSF: sum = " << sum << endl << flush;
   #endif

   return pPSFGrid;
}

//--------------------------------------------------------------------------

ArrayGrid<double>* GridGenerator::GenerateAiry(int width, int height, double airyWidth)
{
   double sum = 0.0;
   double max = 0.0;

   ArrayGrid<double>* pPSFGrid = new ArrayGrid<double>(width, height);  // NOT initialized at construction
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         double tmpValue;
         double xx = static_cast<double>(x) - (static_cast<double>(width) / 2.0);
         double yy = static_cast<double>(y) - (static_cast<double>(height) / 2.0);
         double radius = L2NORM( xx, yy );
         if (radius==0.0)
         {
            tmpValue = 1.0;
         }
         else
         {
            double u = radius / airyWidth;
            tmpValue = POWER2( (2.0 * j1(u) / u) );
         }
         pPSFGrid->SetValue(x, y, tmpValue);
         sum += tmpValue;
      }
   }
   pPSFGrid->DivideBy( sum );

   #ifdef PRINT_DIAGNOSTICS
   sum = 0.0;
   max = 0.0;
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         sum += pPSFGrid->GetValue(x, y);
         if (pPSFGrid->GetValue(x, y) > max) {max = pPSFGrid->GetValue(x, y);}
      }
   }
   cout << "Airy PSF: sum = " << sum << " and max = " << max << endl << flush;
   #endif
   return pPSFGrid;
}

//--------------------------------------------------------------------------

ArrayGrid<double>* GridGenerator::GenerateGaussian (int width, int height, double sigma )
{
   return GenerateGaussian ( width, height, sigma, sigma );
}

//--------------------------------------------------------------------------

ArrayGrid<double>* GridGenerator::GenerateGaussian (int width, int height, double sigmaX, double sigmaY )
{
   #ifdef PRINT_DIAGNOSTICS
   double ssum = 0.0;
   #endif

   ArrayGrid<double>* pPSFGrid = new ArrayGrid<double>( width, height );  // NOT initialized at construction

   double halfWidth  = ( (double)(width)  / 2.0 );
   double halfHeight = ( (double)(height) / 2.0 );
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x ++)
      {
         pPSFGrid->SetValue( x, y, MathUtils::Gaussian( x, y, halfWidth, halfHeight, sigmaX, sigmaY ) );

         #ifdef PRINT_DIAGNOSTICS
         ssum += pPSFGrid->GetValue(x, y);
         #endif
      }
   }
   pPSFGrid->DivideBy( ssum );

   return pPSFGrid;
}

//--------------------------------------------------------------------------

ArrayGrid<double>* GridGenerator::GenerateGaussianFirstDerivativeX(int width, int height, double sigmaX, double sigmaY )
{
   #ifdef PRINT_DIAGNOSTICS
   double ssum = 0.0;
   #endif

   ArrayGrid<double>* pPSFGrid = new ArrayGrid<double>( width, height );  // NOT initialized at construction

   double halfWidth  = ( (double)(width)  / 2.0 );
   double halfHeight = ( (double)(height) / 2.0 );
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x ++)
      {
         pPSFGrid->SetValue(x, y, MathUtils::GaussianDx( x, y, halfWidth, halfHeight, sigmaX, sigmaY ) );

         #ifdef PRINT_DIAGNOSTICS
         ssum += pPSFGrid->GetValue(x, y);
         #endif
      }
   }

   return pPSFGrid;
}


//--------------------------------------------------------------------------

ArrayGrid<double>* GridGenerator::GenerateGaussianFirstDerivativeY(int width, int height, double sigmaX, double sigmaY )
{
   #ifdef PRINT_DIAGNOSTICS
   double ssum = 0.0;
   #endif

   ArrayGrid<double>* pPSFGrid = new ArrayGrid<double>( width, height );  // NOT initialized at construction

   double halfWidth  = ( (double)(width)  / 2.0 );
   double halfHeight = ( (double)(height) / 2.0 );
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x ++)
      {
         pPSFGrid->SetValue(x, y, MathUtils::GaussianDy( x, y, halfWidth, halfHeight, sigmaX, sigmaY ) );

         #ifdef PRINT_DIAGNOSTICS
         ssum += pPSFGrid->GetValue(x, y);
         #endif
      }
   }

   return pPSFGrid;
}

//--------------------------------------------------------------------------

ArrayGrid<double>* GridGenerator::GenerateGaussianSecondDerivativeX (int width, int height, double sigmaX, double sigmaY )
{
   #ifdef PRINT_DIAGNOSTICS
   double ssum = 0.0;
   #endif

   ArrayGrid<double>* pPSFGrid = new ArrayGrid<double>( width, height );  // NOT initialized at construction

   double halfWidth  = static_cast<double>(width)  / 2.0;
   double halfHeight = static_cast<double>(height) / 2.0;

   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x ++)
      {
         pPSFGrid->SetValue(x, y, MathUtils::GaussianSecondDerivateX1D( x, y, halfWidth, halfHeight, sigmaX, sigmaY ) );

         #ifdef PRINT_DIAGNOSTICS
         ssum += pPSFGrid->GetValue(x, y);
         #endif
      }
   }

   return pPSFGrid;
}


//--------------------------------------------------------------------------

ArrayGrid<double>* GridGenerator::GenerateGaussianSecondDerivativeY (int width, int height, double sigmaX, double sigmaY )
{
   #ifdef PRINT_DIAGNOSTICS
   double ssum = 0.0;
   #endif

   ArrayGrid<double>* pPSFGrid = new ArrayGrid<double>( width, height );  // NOT initialized at construction

   double halfWidth  = static_cast<double>(width)  / 2.0;
   double halfHeight = static_cast<double>(height) / 2.0;

   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x ++)
      {
         double value = MathUtils::GaussianD2y( x, y, halfWidth, halfHeight, sigmaX, sigmaY );
         pPSFGrid->SetValue(x, y, value );

         #ifdef PRINT_DIAGNOSTICS
         ssum += value;
         #endif
      }
   }

   return pPSFGrid;
}

//--------------------------------------------------------------------------

ArrayGrid<double>* GridGenerator::GenerateGaussianMixedDerivativesXY (int width, int height, double sigmaX, double sigmaY )
{
   #ifdef PRINT_DIAGNOSTICS
   double ssum = 0.0;
   #endif

   ArrayGrid<double>* pPSFGrid = new ArrayGrid<double>( width, height );  // NOT initialized at construction

   double halfWidth  = static_cast<double>(width)  / 2.0;
   double halfHeight = static_cast<double>(height) / 2.0;

   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x ++)
      {
         pPSFGrid->SetValue(x, y, MathUtils::GaussianDxDy( x, y, halfWidth, halfHeight, sigmaX, sigmaY ) );

         #ifdef PRINT_DIAGNOSTICS
         ssum += fabs(pPSFGrid->GetValue(x, y));
         #endif
      }
   }
   #ifdef PRINT_DIAGNOSTICS
   cout << "GenerateGaussianMixedDerivativesXY: sum = " << ssum << endl << flush;
   #endif

   return pPSFGrid;
}

//--------------------------------------------------------------------------

ArrayGrid<double>* GridGenerator::GenerateGaussian (int width, int height, double sigmaX, double sigmaY, double rho)
{
   assert( rho > -1.0 ); // if == -1 or 1, then ( 1.0 - POWER2( rho ) )  is zero, and we divide by 0!!
   assert( rho <  1.0 );

   double ssum = 0.0;
   double exponentFactor = 1.0 / (2.0 * ( 1.0 - POWER2( rho ) ) );
   double normFactor = 1.0 / (2.0 * M_PI * sigmaX * sigmaY * sqrt( 1.0 - POWER2( rho ) ) );

   ArrayGrid<double>* pPSFGrid = new ArrayGrid<double>( width, height );  // NOT initialized at construction

   double halfWidth  = static_cast<double>(width)  / 2.0;
   double halfHeight = static_cast<double>(height) / 2.0;
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x ++)
      {
         double xx = (static_cast<double>(x) - halfWidth  ) / sigmaX;
         double yy = (static_cast<double>(y) - halfHeight ) / sigmaY;

         double z = POWER2( xx ) - (2.0 * rho * xx * yy) + POWER2( yy );

         double psfValue = normFactor * exp( -z * exponentFactor );

         pPSFGrid->SetValue(x, y, psfValue );

         ssum += pPSFGrid->GetValue(x, y);
      }
   }

   pPSFGrid->DivideBy( ssum );

   return pPSFGrid;
}

//--------------------------------------------------------------------------

ArrayGrid<double>* GridGenerator::GenerateDeltaPeak(int width, int height, int x, int y, double intensity )
{
   bool needInitialisation = true;
   double initialRealValue = 0.0;
   ArrayGrid<double>* pPSFGrid = new ArrayGrid<double>( width, height, needInitialisation, initialRealValue );

   pPSFGrid->SetValue(x, y, intensity);
   return pPSFGrid;
}

//--------------------------------------------------------------------------

// 2) Zone plate
////////////////

ArrayGrid<double>* GridGenerator::GenerateInverseZonePlate ( )
{
   int width  = 512;
   int height = 512;
   ArrayGrid<double>* pZoneGrid = new ArrayGrid<double>( width, height );  // NOT initialized at construction

   cout << "Using new macro's!!" << endl << flush;
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x ++)
      {
         double xx = (double) (x - width/2);
         double yy = (double) (y - height/2);

         double radius = L2NORM( xx, yy );
         double g =  sin( (112.0 * M_PI) / (log(2.0))  * (pow(2.0, -radius / 56.0) - pow(2.0, - 256.0 / 56.0)));
         double gridValue;
         if (radius < 56.0)
         {
            gridValue = 127.0;
         }
         else if ((radius >= 56.0) && (radius < 64.0))
         {
            gridValue = 127.0 * (1.0 + g * POWER2( cos ((( M_PI * radius) / 16.0 - 4.0 * M_PI)) ) );
         }
         else if ((radius >= 64.0) && (radius < 224.0))
         {
            gridValue = 127.0 * (1.0 + g);
         }
         else if ((radius >= 224.0) && (radius < 256.0))
         {
            gridValue = 127.0 * (1.0 + g * POWER2( sin( (( M_PI * radius) / 64.0 - 4.0 * M_PI)) ) );
         }
         else // (radius >= 256.0)
         {
            gridValue = 127.0;
         }
         pZoneGrid->SetValue( x, y, gridValue );
      }
   }
   return pZoneGrid;
}

//--------------------------------------------------------------------------

ArrayGrid<double>* GridGenerator::GenerateZonePlate ( )
{
   int width  = 512;
   int height = 512;

   ArrayGrid<double>* pZoneGrid = new ArrayGrid<double>( width, height );  // NOT initialized at construction

   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x ++)
      {
         double xx = (double) (x - width/2);
         double yy = (double) (y - height/2);

         double radius = L2NORM( xx, yy );

         double gridValue = -112.0 *( cos ( M_PI / 512.0 * POWER2( radius ) ) ) + 128.0;
         pZoneGrid->SetValue( x, y, gridValue );
      }
   }
   return pZoneGrid;
}

//--------------------------------------------------------------------------

ArrayGrid<double>* GridGenerator::GenerateLogFrequencyContrastChart( )
{
   int width  = 495;
   int height = 256;
   ArrayGrid<double>* pZoneGrid = new ArrayGrid<double>( width, height );  // NOT initialized at construction

   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x ++)
      {
         double halfX = sqrt( (double)(x) / 13.0 );
         double yy = (double)((height + 1.0 - y) / height);
         double scaleFactor = yy * yy;
         double gridValue = -127.5 *( cos ( exp( halfX ) ) ) ;
         pZoneGrid->SetValue( x, y, gridValue * scaleFactor + 127.5 );
      }
   }
   return pZoneGrid;
}

//--------------------------------------------------------------------------

// 3) Shepp-Logan
/////////////////

// Based on http://server.oersted.dtu.dk/ftp/jaj/31655/ct_programs/
ArrayGrid<double>* GridGenerator::GenerateSheppLogan( double factor )
{
   int width  = 512;
   int height = 512;
   bool needInitialisation = true;
   double initialRealValue = 0.0;

   ArrayGrid<double>* pSLGrid = new ArrayGrid<double>( width, height, needInitialisation, initialRealValue );

   AddEllipse( pSLGrid,  0.00,  0.0000,  0.920,  0.6900,  90.0,  2.00 );
   AddEllipse( pSLGrid,  0.00, -0.0184,  0.874,  0.6624,  90.0, -0.98 );
   AddEllipse( pSLGrid,  0.22,  0.0000,  0.310,  0.1100,  72.0, -0.02 * factor );
   AddEllipse( pSLGrid, -0.22,  0.0000,  0.410,  0.1600, 108.0, -0.02 * factor );
   AddEllipse( pSLGrid,  0.00,  0.3500,  0.250,  0.2100,  90.0,  0.01 * factor );
   AddEllipse( pSLGrid,  0.00,  0.1000,  0.046,  0.0460,   0.0,  0.01 * factor );
   AddEllipse( pSLGrid,  0.00, -0.1000,  0.046,  0.0460,   0.0,  0.01 * factor );
   AddEllipse( pSLGrid, -0.08, -0.6050,  0.046,  0.0230,   0.0,  0.01 * factor );
   AddEllipse( pSLGrid,  0.00, -0.6050,  0.023,  0.0230,   0.0,  0.01 * factor );
   AddEllipse( pSLGrid,  0.06, -0.6050,  0.046,  0.0230,  90.0,  0.01 * factor );

   return pSLGrid;
}

//--------------------------------------------------------------------------

// helper method for generating shepp-logan phantom
void GridGenerator::AddEllipse(ArrayGrid<double>* pGrid, double xCenter, double yCenter, double majorAxis, double minorAxis, double angle, double value)
{
   int height = pGrid->GetHeight();
   int width  = pGrid->GetWidth();

   double angleRadians = M_PI * angle / 180.0;
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x ++)
      {
         double xx = -2.0 * ((double)(x) / (double)(width) - 0.5);
         double yy =  2.0 * ((double)(y) / (double)(height) - 0.5);

         double xm = ( ( xx + xCenter ) * cos( angleRadians ) + ( yy + yCenter ) * sin( angleRadians ) ) / majorAxis;
         double ym = (-( xx + xCenter ) * sin( angleRadians ) + ( yy + yCenter ) * cos( angleRadians ) ) / minorAxis;

         double tmpValue = POWER2( xm ) + POWER2( ym );
         if (tmpValue <= 1.0)
         {
            double gridIntensity = pGrid->GetValue(x, y) + value;
            pGrid->SetValue(x, y, gridIntensity);
         }
      }
   }
}

//--------------------------------------------------------------------------

// 4) ISING-process generated texture
//     see ~/develop/c/metropolis/metropolis.c for original program
//     TODO finish: doesn't work properly yet: coherence is lost at bottom of image
///////////////////////////////////////////////////////////////////////////////////

ArrayGrid<int>* GridGenerator::GenerateIsingTexture( )
{
   Random* pRandom = new Random();
   int width  = 256;
   int height = 256;
   double beta  = -0.9;
   double temperature =  1.0;
   int maxNrIterations = 41;

   srand (time (NULL));

   ArrayGrid<int>* pGrid = new ArrayGrid<int>( width, height );
   InitializeIsingState( pGrid, pRandom );//iterate metropolis algorithm on Ising model
  //===========================================

   for (int t = 0; t < maxNrIterations; t ++)
   {
      cout << "Iteration " << t << " temperature = " << temperature << endl << flush;
      UpdateIsingState( pGrid, temperature, beta, pRandom);

      if (t % 10 == 0)
      {
         WriteCurrentIsingState( pGrid, t );
      }

      temperature /= 1.02;
   }
   delete pRandom;
   return pGrid;
}

//--------------------------------------------------------------------------

void GridGenerator::InitializeIsingState( ArrayGrid<int>* pGrid, Random* pRandom)
{
   int height = pGrid->GetHeight();
   int width  = pGrid->GetWidth();
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         double sample = pRandom->uniform( 0., 1. );
         if (sample <= 0.5)
         {
            pGrid->SetValue(x, y, -1);
         }
         else
         {
            pGrid->SetValue(x, y, 1);
         }
      }
   }
}

//--------------------------------------------------------------------------

void GridGenerator::WriteCurrentIsingState( ArrayGrid<int>* pGrid, int iterationNr)
{
   int height = pGrid->GetHeight();
   int width  = pGrid->GetWidth();

   ArrayGrid<double>* pGridOut = new ArrayGrid<double>( pGrid->GetWidth(), pGrid->GetHeight() );

   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         int value = pGrid->GetValue(x, y);
         if (value < 0) {pGridOut->SetValue(x, y, 0.0);}
         else {pGridOut->SetValue(x, y, 255.0);}
      }
   }
   stringstream ss;
   ss << "Ising-" << iterationNr << ".pgm";
   string fileName = ss.str();

   ImageIO::WritePGM(pGridOut, fileName, ImageIO::NULL_OUT);
   delete pGridOut;
}

//--------------------------------------------------------------------------

void GridGenerator::UpdateIsingState( ArrayGrid<int>* pGrid, double temperature, double beta, Random* pRandom)
{
   int height = pGrid->GetHeight();
   int width  = pGrid->GetWidth();

   std::vector< Point<int> > vPointList;

   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         Point<int> p(x, y);
         vPointList.push_back(p);
      }
   }

   // Update all labels in random order. vPointList contains the coordinates of the labels
   // and a random element in vPointList is taken. The label with
   // corresponding coordinates is updated and the element is then removed from the vector,
   // and a new random value is chosen from the remaining vector
   //
   // You can play with the eight weights below to achieve anisotropical results
   //==================================================================================

   double weightLeft  = 1.0;
   double weightRight = 1.0;
   double weightUpper = 1.0;
   double weightLower = 1.0;

   while (!(vPointList.empty()))
   {
      int randomIndex = pRandom->uniformDiscrete( 0, vPointList.size() );

      int x = vPointList[randomIndex].x;
      int y = vPointList[randomIndex].y;

      int xLeft  = x - 1;     if (xLeft  < 0      ) {xLeft  = width-1;}
      int xRight = x + 1;     if (xRight > width-1) {xRight = 0;}

      int yUpper = y + 1;     if (yUpper > height-1) {yUpper  = 0;}
      int yLower = y - 1;     if (yLower < 0       ) {yLower  = height-1;}

      //energy of the random label in old state
      double oldEnergy = (    weightLeft  * pGrid->GetValue(x, y) * pGrid->GetValue(xLeft,  y)
                           +  weightRight * pGrid->GetValue(x, y) * pGrid->GetValue(xRight, y)
                           +  weightUpper * pGrid->GetValue(x, y) * pGrid->GetValue(x, yUpper)
                           +  weightLower * pGrid->GetValue(x, y) * pGrid->GetValue(x, yLower)
                         ) * beta;

      //energy of the random label in switched state
      double switchedEnergy = -oldEnergy;

      //update label
      double randomJump = (double) ( rand() ) / RAND_MAX;
      double potential = exp( -( switchedEnergy - oldEnergy ) / temperature );

      if (potential > randomJump)
      {
         pGrid->SetValue( x, y, pGrid->GetValue( x, y ) * ( -1.0 ) );
      }

      //mark coordinates label as visited
      vPointList.erase (vPointList.begin()+randomIndex);
   }

   return;
}

}
}
