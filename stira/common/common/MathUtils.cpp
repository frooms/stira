
/***************************************************************************************
 *   Copyright (C) 2008 by Filip Rooms                                                 *
 *                                                                                     *
 *  Terms and conditions for using this software in any form are provided in the       *
 *  file COPYING, which can be found in the root directory of this project.            *
 *                                                                                     *
 *   Contact data: filip.rooms@gmail.com                                               *
 *                 http://www.filiprooms.be/                                           *
 *                                                                                     *
 ***************************************************************************************/

#include "MathUtils.h"
#include "StiraMacros.h"

#include <iostream>
#include <cmath>
#include <cassert>
#include <bitset>

using namespace std;

namespace stira {
namespace common{

MathUtils::MathUtils()
{
}

//----------------------------------------------------------------------------------------------------

MathUtils::~MathUtils()
{}

//----------------------------------------------------------------------------------------------------

// 1. SWITCH TWO VALUES
///////////////////////

void MathUtils::SwitchValues(double& a, double& b)
{
   double ttmp = b;
   b = a;
   a = ttmp;
}

//----------------------------------------------------------------------------------------------------

void MathUtils::SwitchValues(int& a, int& b)
{
   int ttmp = b;
   b = a;
   a = ttmp;
}

//======================================================================================================

// 2. ORDER / COMPARE STUFF / CLIP RANGE / CHECK IF IS RANGE
////////////////////////////////////////////////////////////

double MathUtils::GetMin(double a, double b)
{
   if (a < b)
   {
      return a;
   }
   else
   {
      return b;
   }
}

//----------------------------------------------------------------------------------------------------

double MathUtils::GetMax(double a, double b)
{
   if (a > b)
   {
      return a;
   }
   else
   {
      return b;
   }
}

//----------------------------------------------------------------------------------------------------

int MathUtils::CompareDoubles(const void *a, const void *b)
{
   double d1 = *((double*)a);
   double d2 = *((double*)b);

   if (d1 < d2)
   {
      return -1;
   }
   else if (d1 == d2)
   {
     return 0;
   }
   else
   {
      return 1;
   }
}

//----------------------------------------------------------------------------------------------------

int MathUtils::CompareFloats(const void *a, const void *b)
{
   float f1 = *((float*)a);
   float f2 = *((float*)b);

   if (f1 < f2)
   {
      return -1;
   }
   else if (f1 == f2)
   {
     return 0;
   }
   else
   {
      return 1;
   }
}

//----------------------------------------------------------------------------------------------------

int MathUtils::CompareIntegers(const void *a, const void *b)
{
   int i1 = *((int*)a);
   int i2 = *((int*)b);

   if (i1 < i2)
   {
      return -1;
   }
   else if (i1 == i2)
   {
     return 0;
   }
   else
   {
      return 1;
   }
}

//----------------------------------------------------------------------------------------------------

double MathUtils::ClipValue(double value, double min, double max)
{
   if (max < min)
   {
      SwitchValues( min, max);
   }
   if (value < min) {return min;}
   if (value > max) {return max;}
   return value;
}

//----------------------------------------------------------------------------------------------------

int MathUtils::ClipValue( int value, int min, int max )
{
   if (max < min)
   {
      SwitchValues( min, max);
   }
   if (value < min) {return min;}
   if (value > max) {return max;}
   return value;
}

//----------------------------------------------------------------------------------------------------

bool MathUtils::IsBetween(double testValue, double underLimit, double upperLimit)
{
   if ( ( testValue >= underLimit ) && (testValue <= upperLimit ) )
   {
      return true;
   }
   else
   {
      return false;
   }
}

//----------------------------------------------------------------------------------------------------

double MathUtils::ApplyModulo( double input, double modulo )
{
   while ( input > modulo )
   {
      input -= modulo;
   }
   while ( input < 0.0 )
   {
      input += modulo;
   }
   return input;
}

//----------------------------------------------------------------------------------------------------

void MathUtils::PrintBitsInInt(unsigned int i)
{
    std::cout << std::bitset<32>(i) << std::flush;
}

//----------------------------------------------------------------------------------------------------

void MathUtils::PrintBitsInChar(unsigned char c)
{
    for (int i = 0; i < 8; i++)
    {
       std::cout << !!((c << i) & 0x80) << std::flush;
    }
    //std::cout << std::bitset<8>(c) << std::endl << std::flush;
}

//----------------------------------------------------------------------------------------------------

unsigned int MathUtils::CombineCharsInInt(unsigned char i0, unsigned char i1, unsigned char i2, unsigned char i3)
{
    unsigned int combined = (unsigned int)((i0 << 24) | (i1 << 16) | (i2 << 8) | (i3 << 0));
    return combined;
}

//----------------------------------------------------------------------------------------------------

std::vector<unsigned char> MathUtils::SplitIntInChars( int value )
{
    vector<unsigned char> arrayOfByte(4);
    for (int i = 0; i < 4; i++)
    {
       arrayOfByte[3 - i] = (value >> (i * 8));
    }
    return arrayOfByte;
}

//======================================================================================================

// 3. STUFF RELATED TO ANGLES
/////////////////////////////

double MathUtils::ComputeArgument(double x, double y)
{
   if (y >= 0.0)
   {
      return atan2(y, x);
   }
   else
   {
      return ( 2.0 * M_PI + atan2(y, x) );
   }
}

//----------------------------------------------------------------------------------------------------

double MathUtils::ToRadians( double degrees )
{
   return ( M_PI * (degrees / 180.0 ) );
}

//----------------------------------------------------------------------------------------------------

double MathUtils::ToDegrees( double radians )
{
   return ( 180.0 * ( radians / M_PI ) );
}

//======================================================================================================

// 4. SOLVE LINEAR / QUADRATIC EQUATIONS
////////////////////////////////////////

bool MathUtils::SolveLinearEquation (double a, double b, double& solution)
{
   if (a == 0.0)
   {
      return false;
   }
   else
   {
      solution = -b / a;
      return true;
   }
}

//----------------------------------------------------------------------------------------------------

bool MathUtils::SolveQuadraticEquation( std::complex<double> a, std::complex<double> b, std::complex<double> c,
                                        std::complex<double>& outSolution1, std::complex<double>& outSolution2)
{
   complex<double> discriminant = b * b - 4.0 * a * c;
   outSolution1 = -b + sqrt( discriminant ) / (2.0 * a);
   outSolution2 = -b - sqrt( discriminant ) / (2.0 * a);
   if ( (discriminant.real() > 0.0) && (discriminant.imag() == 0.0) )
   {
      return true;
   }
   else
   {
      return false;
   }
}

//----------------------------------------------------------------------------------------------------

bool MathUtils::SolveQuadraticEquation( double a, double b, double c, double& outSolution1, double& outSolution2)
{
   double discriminant = b * b - 4.0 * a * c;

   if (discriminant >= 0.0)
   {
      outSolution1 = -b + sqrt( discriminant ) / (2.0 * a);
      outSolution2 = -b - sqrt( discriminant ) / (2.0 * a);
      return true;
   }
   else
   {
      outSolution1 = 0.0;
      outSolution2 = 0.0;
      cerr << "Discriminant is negative, use complex expression to solve equation!!" << endl << flush;
      return false;
   }
}

//======================================================================================================

// 5. COMPUTE MATHEMATICAL FUNCTION VALUE
/////////////////////////////////////////

double MathUtils::ComputePSNR( double MSE, double peakValue )
{
   return ( 10.0 * log10( peakValue * peakValue / MSE ) );
}

//----------------------------------------------------------------------------------------------------

double MathUtils::GammaCorrect( double inValue, double gamma, double rangeMin, double rangeMax )
{
   double range = ( rangeMax - rangeMin );
   double tmpValue = ( inValue - rangeMin ) / range;
   tmpValue = pow( tmpValue, (1.0 / gamma) );
   return ( tmpValue * range + rangeMin );
}

//----------------------------------------------------------------------------------------------------

double MathUtils::GetSteerableInterPolationCoefficient(int i, int K, double theta)
{
   //return sin( M_PI * (m - n) - theta * K) / (K * sin ((M_PI) * (m - n) - theta) );
   return sin( M_PI * (i - 1) - theta * K) / (K * sin ((M_PI) * (i - 1) - theta) );
}

//----------------------------------------------------------------------------------------------------

int MathUtils::ComputeIntegerPower(int myNumber, int myExponent)
{
   int myCounter = myExponent;
   int myResult = 1;
   while (myCounter >= 1)
   {
      myResult *= myNumber;
      myCounter --;
   }
   return myResult;
}

//----------------------------------------------------------------------------------------------------

double MathUtils::Factorial(const double& inputNumber)
{
   double tmpResult = 1.0;
   double copyInput = inputNumber;

   while (copyInput > 1.0)
   {
      tmpResult *= copyInput;
      copyInput --;
   }
   return tmpResult;
}

//======================================================================================================

// 6. COMPUTE VALUES OF GAUSSIAN FUNCTION / DERIVATIVES
///////////////////////////////////////////////////////

std::vector<double> MathUtils::GenerateGaussianSamples( double sigma )
{
   int halfSampleSize = (2*sigma+0.5);

   int size = 2 * halfSampleSize + 1;

   int centerIndex = halfSampleSize; // halfSampleSize samples left of the peak; the peak at (halfSampleSize + 1) and then halfSampleSize samples right of the peak

   std::vector<double> gaussianSamples;

   for (int i = 0; i < size; i++)
   {
      gaussianSamples.push_back( Gaussian( i, centerIndex, sigma ) );
   }

   double totalValue = 0;
   for (int i = 0; i < size; i++)
   {
      totalValue += gaussianSamples[i];
   }
   cout << "Total Value before normalisation is " << totalValue << endl;
   for (int i = 0; i < size; i++)
   {
      gaussianSamples[i] /= totalValue;
   }

   return gaussianSamples;
}

//----------------------------------------------------------------------------------------------------

std::vector< Point<double> > MathUtils::GenerateGaussianPoints( int gaussCenterX, double sigma, bool scaleAmplitude, double amplitude )
{
   int halfSampleSize = (2*sigma+0.5);

   int size = 2 * halfSampleSize + 1;

   int centerIndex = halfSampleSize; // halfSampleSize samples left of the peak; the peak at (halfSampleSize + 1) and then halfSampleSize samples right of the peak

   double peakValue = Gaussian( 0, 0, sigma );
   std::vector< Point<double> > gaussianPoints;

   cout << " generating " << size << " model points now " << endl;
   if (scaleAmplitude)
   {
      for (int i = 0; i < size; i++)
      {
         cout << "Fitting point model " << Point<double>( gaussCenterX-centerIndex+i, amplitude * Gaussian( i, centerIndex, sigma ) / peakValue ) << endl;
         gaussianPoints.push_back( Point<double>( gaussCenterX-centerIndex+i, amplitude * Gaussian( i, centerIndex, sigma ) / peakValue ) );
      }
   }
   else
   {
      for (int i = 0; i < size; i++)
      {
         cout << "Fitting point model " << Point<double>( gaussCenterX-centerIndex+i, Gaussian( i, centerIndex, sigma ) ) << endl;
         gaussianPoints.push_back( Point<double>( gaussCenterX-centerIndex+i, Gaussian( i, centerIndex, sigma ) ) );
      }
   }

   return gaussianPoints;
}

//----------------------------------------------------------------------------------------------------

std::vector< Point<double> > MathUtils::GenerateGaussianPoints( std::vector< Point<double> > inPoints, int gaussCenterX, double sigma, bool scaleAmplitude, double amplitude )
{
   std::vector< Point<double> > gaussianPoints;

   int size = inPoints.size();
   cout << " generating " << size << " model points now " << endl;
   if (scaleAmplitude)
   {
      for (int i = 0; i < size; i++)
      {
         double peakValue = Gaussian( 0, 0, sigma );
         double x = inPoints[i].GetX();
         Point<double> pt( x, amplitude * Gaussian( x, gaussCenterX, sigma ) / peakValue );
         gaussianPoints.push_back( pt );
      }
   }
   else
   {
      for (int i = 0; i < size; i++)
      {
         double x = inPoints[i].GetX();
         Point<double> pt( x, Gaussian( x, gaussCenterX, sigma ) );
         gaussianPoints.push_back( pt );
      }
   }

   return gaussianPoints;
}

//----------------------------------------------------------------------------------------------------

double MathUtils::Gaussian( double x, double mu, double sigma )
{
   assert( sigma > 0.0 );

   double xMinMuDividedBySigma = (x - mu) / sigma;

   double value =  exp ( -0.5 * ( xMinMuDividedBySigma * xMinMuDividedBySigma ) )
                 / ( sqrt( 2.0 * M_PI ) * sigma );

   return value;
}

//----------------------------------------------------------------------------------------------------

double MathUtils::Gaussian( double x, double y, double muX, double muY, double sigmaX, double sigmaY )
{
   assert( sigmaX > 0.0 );
   assert( sigmaY > 0.0 );

   return (   Gaussian( x, muX, sigmaX )
            * Gaussian( y, muY, sigmaY )
          );
}

//----------------------------------------------------------------------------------------------------

double MathUtils::GaussianFirstDerivativeX1D( double x, double mu, double sigma )
{
   assert( sigma > 0.0 );

   return (        ( - ( x - mu ) / ( sqrt( 2.0 * M_PI ) * POWER3( sigma ) ) )
             * exp ( -0.5 * ( POWER2( ( ( x - mu ) / sigma) ) ) )
          );
}

//----------------------------------------------------------------------------------------------------

double MathUtils::GaussianSecondDerivateX1D( double x, double mu, double sigma )
{
   assert( sigma > 0.0 );

   return (       ( ( x - mu + sigma ) * ( x - mu - sigma ) / ( sqrt(2.0 * M_PI) * POWER5( sigma ) ) )
            * exp (-0.5 * ( POWER2( ( ( x - mu ) / sigma) ) )  )
          );
}

//----------------------------------------------------------------------------------------------------

double MathUtils::GaussianDx( double x, double y, double muX, double muY, double sigmaX, double sigmaY )
{
   assert( sigmaX > 0.0 );
   assert( sigmaY > 0.0 );

   return (   GaussianFirstDerivativeX1D( x, muX, sigmaX )
            *                   Gaussian( y, muY, sigmaY )
          );
}

//----------------------------------------------------------------------------------------------------

double MathUtils::GaussianDy( double x, double y, double muX, double muY, double sigmaX, double sigmaY )
{
   assert( sigmaX > 0.0 );
   assert( sigmaY > 0.0 );

   return (                       Gaussian( x, muX, sigmaX )
              * GaussianFirstDerivativeX1D( y, muY, sigmaY )
          );
}

//----------------------------------------------------------------------------------------------------

double MathUtils::GaussianSecondDerivateX1D( double x, double y, double muX, double muY, double sigmaX, double sigmaY )
{
   assert( sigmaX > 0.0 );
   assert( sigmaY > 0.0 );

   return (   GaussianSecondDerivateX1D( x, muX, sigmaX )
            *    Gaussian( y, muY, sigmaY )
          );
}

//----------------------------------------------------------------------------------------------------

double MathUtils::GaussianD2y( double x, double y, double muX, double muY, double sigmaX, double sigmaY )
{
   assert( sigmaX > 0.0 );
   assert( sigmaY > 0.0 );

   return (                    Gaussian( x, muX, sigmaX )
            * GaussianSecondDerivateX1D( y, muY, sigmaY )
          );
}

//----------------------------------------------------------------------------------------------------

double MathUtils::GaussianDxDy( double x, double y, double muX, double muY, double sigmaX, double sigmaY )
{
   assert( sigmaX > 0.0 );
   assert( sigmaY > 0.0 );

   return (   GaussianFirstDerivativeX1D( x, muX, sigmaX )
            * GaussianFirstDerivativeX1D( y, muY, sigmaY )
          );
}

//======================================================================================================

// 7. COMPUTE STATISTICS
////////////////////////

double* MathUtils::ComputeCrossCorrelation( double* x, double* y, int nrSamples, int maxDelay )
{
   double* pCrossCorrelation = new double[ 2 * maxDelay ];

   // Calculate the mean of the two series x[], y[]
   double meanX = 0;
   double meanY = 0;
   for (int i = 0; i < nrSamples; i++ )
   {
      meanX += x[i];
      meanY += y[i];
   }
   meanX /= nrSamples;
   meanY /= nrSamples;

   // Calculate the denominator
   double sx = 0;
   double sy = 0;
   for ( int i = 0; i < nrSamples; i++ )
   {
      sx += (x[i] - meanX) * (x[i] - meanX);
      sy += (y[i] - meanY) * (y[i] - meanY);
   }
   double denom = sqrt( sx * sy );

   // Calculate the correlation series
   for (int delay = -maxDelay; delay < maxDelay; delay++ )
   {
      double sxy = 0;
      for ( int i = 0; i < nrSamples; i++ )
      {
         int j = i + delay;
         if (j < 0 || j >= nrSamples)
            continue;
         else
            sxy += (x[i] - meanX) * (y[j] - meanY);
         /* Or should it be (?)
         if (j < 0 || j >= n)
             sxy += (x[i] - mx) * (-my);
          else
             sxy += (x[i] - mx) * (y[j] - my);
          */
      }
      pCrossCorrelation[delay + maxDelay] = sxy / denom;    // the correlation coefficient at "delay"
   }
   return pCrossCorrelation;
}

//======================================================================================================

}
}
