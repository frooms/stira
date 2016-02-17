
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

#include "../common/MathUtils.h"
#include "../common/QuantileNormalDistribution.h"
#include "../common/Random.h"
#include "../common/FitCurve.h"
#include "../common/Statistics.h"
#include <iostream>
#include <iomanip>
#include <cassert>

#define FIT_NOISE_MIN -1.0
#define FIT_NOISE_MAX  1.0

using namespace std;
using namespace stira::common;

std::vector<double> MakeVector( double* pData, int nrElements )
{
   std::vector<double> vVector;
   for (int i = 0; i < nrElements; i++)
   {
      vVector.push_back( pData[i] );
   }
   return vVector;
}

//-----------------------------------------------------------------

void TestApplyModulo()
{
   double base = 360.0;
   double factor = 3.0;
   double remainder = 10.0 * M_PI * M_E;
   double a = base * factor + remainder;

   assert ( fabs( MathUtils::ApplyModulo( a, base ) - remainder ) < 0.0001);
   cout << "Modulo test success!!" << endl << flush;
}

//-----------------------------------------------------------------

void TestArgument()
{
   for (double theta = 0.0; theta < 2.0 * M_PI; theta += 0.05)
   {
      double x = cos(theta);
      double y = sin(theta);

      assert( fabs( theta - MathUtils::ComputeArgument( x, y ) ) < 0.001 );
   }
   cout << "Argument test success!!" << endl << flush;
}

//-----------------------------------------------------------------

void TestBitshiftCharInt()
{
    unsigned char c0 = 126;     std::cout << "Input value 0 = " << (int)(c0) << "\t";  MathUtils::PrintBitsInChar(c0);  std::cout << std::endl << std::flush;
    unsigned char c1 =  55;     std::cout << "Input value 1 = " << (int)(c1) << "\t";  MathUtils::PrintBitsInChar(c1);  std::cout << std::endl << std::flush;
    unsigned char c2 = 147;     std::cout << "Input value 2 = " << (int)(c2) << "\t";  MathUtils::PrintBitsInChar(c2);  std::cout << std::endl << std::flush;
    unsigned char c3 =  37;     std::cout << "Input value 3 = " << (int)(c3) << "\t";  MathUtils::PrintBitsInChar(c3);  std::cout << std::endl << std::flush;

    std::cout << "Concat chars : " << std::flush;
    MathUtils::PrintBitsInChar(c0);
    MathUtils::PrintBitsInChar(c1);
    MathUtils::PrintBitsInChar(c2);
    MathUtils::PrintBitsInChar(c3);  std::cout << std::endl << std::flush;

    int intCombined = MathUtils::CombineCharsInInt(c0, c1, c2, c3);
    std::cout << "Combin chars : " << std::flush;  MathUtils::PrintBitsInInt(intCombined);  std::cout << std::endl << std::flush;

    std::cout << "Split into chars" << std::endl << std::flush;
    vector<unsigned char> charVector = MathUtils::SplitIntInChars(intCombined);

    assert( charVector[0] == c0 );      std::cout << "Split value 0 = " << (int)(charVector[0]) << "\t";  MathUtils::PrintBitsInChar(charVector[0]);  std::cout << std::endl << std::flush;
    assert( charVector[1] == c1 );      std::cout << "Split value 1 = " << (int)(charVector[1]) << "\t";  MathUtils::PrintBitsInChar(charVector[1]);  std::cout << std::endl << std::flush;
    assert( charVector[2] == c2 );      std::cout << "Split value 2 = " << (int)(charVector[2]) << "\t";  MathUtils::PrintBitsInChar(charVector[2]);  std::cout << std::endl << std::flush;
    assert( charVector[3] == c3 );      std::cout << "Split value 3 = " << (int)(charVector[3]) << "\t";  MathUtils::PrintBitsInChar(charVector[3]);  std::cout << std::endl << std::flush;
}

//-----------------------------------------------------------------

void TestLineCurveFit()
{
   Random rd;
   double a = 3.0;
   double b = -15.0;
   int nrPoints = 50;
   vector< Point<double> > inPointsLine;
   for (int i = 0; i < nrPoints; i++)
   {
      double x = 0.1 * (double)(i);
      double y = a * x + b + rd.uniform( FIT_NOISE_MIN, FIT_NOISE_MAX );
      Point<double> pt( x, y );
      inPointsLine.push_back( pt );
   }
   FitCurve fc( inPointsLine );
   vector<double> fitParameters = fc.FitLinear( );

   cout << "Linear fit: " << endl
                  << "\t input a = " << a << ", estimated a = " << fitParameters[0] << endl
                  << "\t input b = " << b << ", estimated b = " << fitParameters[1] << endl
                  << "\t average absolute error = " << fc.GetMeanAbsoluteError() << endl << flush;

   assert ( fabs( a - fitParameters[0] ) < ( FIT_NOISE_MAX - FIT_NOISE_MIN ) );
   assert ( fabs( b - fitParameters[1] ) < ( FIT_NOISE_MAX - FIT_NOISE_MIN ) );

   cout << " -> OK!!" << endl << flush;
   fc.WriteToDisk( std::string("LinearFitTest.txt") );
}

//-----------------------------------------------------------------

void TestQuadraticCurveFit()
{
   Random rd;
   double a = 3.0;
   double b = -7.0;
   double c = 11.0;
   int nrPoints = 50;
   vector< Point<double> > inPointsLine;
   for (int i = 0; i < nrPoints; i++)
   {
      double x = 0.1 * (double)(i);
      double y = a * x * x + b * x + c + rd.uniform( FIT_NOISE_MIN,FIT_NOISE_MAX );
      Point<double> pt( x, y );
      inPointsLine.push_back( pt );
   }

   FitCurve fc( inPointsLine );
   vector<double> fitParameters = fc.FitQuadratic();

   cout << "Quadratic fit: " << endl
                  << "\t input a = " << a << ", estimated a = " << fitParameters[0] << endl
                  << "\t input b = " << b << ", estimated b = " << fitParameters[1] << endl
                  << "\t input c = " << c << ", estimated c = " << fitParameters[2] << endl
                  << "\t average absolute error = " << fc.GetMeanAbsoluteError() << endl << flush;

   assert ( fabs( a - fitParameters[0] ) < ( FIT_NOISE_MAX - FIT_NOISE_MIN ) );
   assert ( fabs( b - fitParameters[1] ) < ( FIT_NOISE_MAX - FIT_NOISE_MIN ) );
   assert ( fabs( c - fitParameters[2] ) < ( FIT_NOISE_MAX - FIT_NOISE_MIN ) );

   cout << " -> OK!!" << endl << flush;
   fc.WriteToDisk( std::string("QuadraticFitTest.txt") );
}

//-----------------------------------------------------------------

void TestCubicCurveFit()
{
   int polynomialDegree = 3;
   Random rd;
   double a = 3.0;
   double b = -7.0;
   double c = 11.0;
   double d = -2.0;
   int nrPoints = 50;
   vector< Point<double> > inPointsLine;
   for (int i = 0; i < nrPoints; i++)
   {
      double x = 0.1 * (double)(i);
      double y = a * x * x * x + b * x * x  + c * x + d + rd.uniform( FIT_NOISE_MIN,FIT_NOISE_MAX );
      Point<double> pt( x, y );
      inPointsLine.push_back( pt );
   }

   FitCurve fc( inPointsLine );

   vector<double> fitParameters = fc.PolynomialFit( polynomialDegree );

   cout << "Cubic fit: " << endl
                  << "\t input a = " << a << ", estimated a = " << fitParameters[0] << endl
                  << "\t input b = " << b << ", estimated b = " << fitParameters[1] << endl
                  << "\t input c = " << c << ", estimated c = " << fitParameters[2] << endl
                  << "\t input d = " << d << ", estimated d = " << fitParameters[3] << endl << flush;

   assert ( fabs( a - fitParameters[0] ) < ( FIT_NOISE_MAX - FIT_NOISE_MIN ) );
   assert ( fabs( b - fitParameters[1] ) < ( FIT_NOISE_MAX - FIT_NOISE_MIN ) );
   assert ( fabs( c - fitParameters[2] ) < ( FIT_NOISE_MAX - FIT_NOISE_MIN ) );
   assert ( fabs( d - fitParameters[3] ) < ( FIT_NOISE_MAX - FIT_NOISE_MIN ) );

   cout << " -> OK!!" << endl << flush;
   fc.WriteToDisk( std::string("PolynomialCubicFitTest.txt") );
}

//-----------------------------------------------------------------

void TestExponentialCurveFit()
{
   Random rd;
   double a = 3.0;
   double b = 5.0;
   int nrPoints = 50;
   vector< Point<double> > inPointsLine;
   for (int i = 0; i < nrPoints; i++)
   {
      double x = 0.1 * (double)(i);
      double y = a * exp( x * b) + rd.uniform( FIT_NOISE_MIN, FIT_NOISE_MAX );
      Point<double> pt( x, y );
      inPointsLine.push_back( pt );
   }

   FitCurve fc( inPointsLine );
   vector<double> fitParameters = fc.FitExponential();

   cout << "Exponential fit: " << endl
                  << "\t input a = " << a << ", estimated a = " << fitParameters[0] << endl
                  << "\t input b = " << b << ", estimated b = " << fitParameters[1] << endl
                  << "\t average absolute error = " << fc.GetMeanAbsoluteError() << endl << flush;

   assert ( fabs( a - fitParameters[0] ) < ( FIT_NOISE_MAX - FIT_NOISE_MIN ) );
   assert ( fabs( b - fitParameters[1] ) < ( FIT_NOISE_MAX - FIT_NOISE_MIN ) );

   cout << " -> OK!!" << endl << flush;
   fc.WriteToDisk( std::string("ExponentialFitTest.txt") );
}

//-----------------------------------------------------------------

void TestGaussianCurveFit()
{
   int gaussCenterX = 715;
   double sigma = 5;
   bool scaleAmplitude=true;
   double amplitude=25;
   Random rn;

   std::vector< Point<double> > gaussPoints = MathUtils::GenerateGaussianPoints( gaussCenterX, sigma , scaleAmplitude, amplitude);


   for(unsigned int i = 0; i < gaussPoints.size(); i++)
   {
      double value1 = rn.uniform( );
      double value2 = rn.uniform( 0.0, 15 );
      if ( value1 > 0.7)
      {
         gaussPoints[i].SetY( gaussPoints[i].GetY() + value2 );
      }
      cout << "Point generated in " << i << gaussPoints[i] << "\t noisy point " << i << gaussPoints[i] << endl;
   }

   FitCurve fc( gaussPoints );
   vector<double> fitParameters = fc.GaussianFitLeastSquares( );

   fc.GetAllAbsoluteErrors();
   cout << "Gaussian fit: " << endl
                  << "\t input peak height = " << amplitude << ", estimated = " << fitParameters[0] << endl
                  << "\t input mu = " << gaussCenterX << ", estimated = " << fitParameters[1] << endl
                  << "\t input sigma = " << sigma << ", estimated = " << fitParameters[2] << endl
                  << "\t average absolute error = " << fc.GetMeanAbsoluteError() << endl << flush;

   std::pair< double, double > pp = Statistics<double>::ComputeFirstTwoCentralMoments( gaussPoints );
   cout << "\t 1st moment = " << pp.first
        << "\t 2nd moment = " << pp.second << endl << flush;


   cout << " -> OK!!" << endl << flush;
   //fc2.WriteToDisk( std::string("GaussianFitTest.txt") );
}

//-----------------------------------------------------------------

void TestStatistics()
{
   double realMean     =  8.0;
   double realVariance = 44.25;
   double* pData = new double[9];
   pData[0] =  2.0;
   pData[1] =  5.0;
   pData[2] = 21.0;
   pData[3] =  7.0;
   pData[4] =  4.0;
   pData[5] = 17.0;
   pData[6] =  4.0;
   pData[7] =  9.0;
   pData[8] =  3.0;

   double avg1  = Statistics<double>::GetAverage(  pData, 9 );
   double var11 = Statistics<double>::GetVariance( pData, 9 );
   double var12 = Statistics<double>::GetVariance( pData, 9, avg1 );

   assert ( fabs(  avg1 - realMean     ) < 0.00001 );
   assert ( fabs( var11 - realVariance ) < 0.00001 );
   assert ( fabs( var12 - realVariance ) < 0.00001 );

   cout << "TestStatistics() avg1 = " << avg1 << "\t var11 = " << var11 << "\t var12 = " << var12 << " -> OK!!" << endl << flush;

   std::vector<double> vVector = MakeVector( pData, 9 );

   double avg2  = Statistics<double>::GetAverage(  vVector );
   double var21 = Statistics<double>::GetVariance( vVector );
   double var22 = Statistics<double>::GetVariance( vVector, avg2 );

   assert ( fabs(  avg2 - realMean     ) < 0.00001 );
   assert ( fabs( var21 - realVariance ) < 0.00001 );
   assert ( fabs( var22 - realVariance ) < 0.00001 );

   cout << "TestStatistics() avg2 = " << avg2 << "\t var21 = " << var21 << "\t var22 = " << var22 << " -> OK!!" << endl << flush;

   delete []pData;
}

//------------------------------------------------------

void TestStatisticsBis()
{
   double realMean     = 21.22222222;
   double realVariance = 96.69444444;
   double* pData = new double[9];
   pData[0] = 19.0;
   pData[1] = 25.0;
   pData[2] =  7.0;
   pData[3] = 34.0;
   pData[4] = 16.0;
   pData[5] = 23.0;
   pData[6] = 37.0;
   pData[7] = 11.0;
   pData[8] = 19.0;

   double avg1  = Statistics<double>::GetAverage(  pData, 9 );
   double var11 = Statistics<double>::GetVariance( pData, 9 );
   double var12 = Statistics<double>::GetVariance( pData, 9, avg1 );

   assert ( fabs(  avg1 - realMean ) < 0.00001 );
   assert ( fabs( var11 - realVariance ) < 0.00001 );
   assert ( fabs( var12 - realVariance ) < 0.00001 );

   cout << "TestStatisticsBis() avg1 = " << avg1 << "\t var11 = " << var11 << "\t var12 = " << var12 << " -> OK!!" << endl << flush;

   std::vector<double> vVector = MakeVector( pData, 9 );

   double avg2  = Statistics<double>::GetAverage(  vVector );
   double var21 = Statistics<double>::GetVariance( vVector );
   double var22 = Statistics<double>::GetVariance( vVector, avg2 );

   assert ( fabs(  avg2 - realMean ) < 0.00001 );
   assert ( fabs( var21 - realVariance ) < 0.00001 );
   assert ( fabs( var22 - realVariance ) < 0.00001 );

   cout << "TestStatisticsBis() avg2 = " << avg2 << "\t var21 = " << var21 << "\t var22 = " << var22 << " -> OK!!" << endl << flush;
   delete []pData;
}

//------------------------------------------------------

void TestGaussianity()
{
   for ( double sigma = 1.0; sigma < 10; sigma++)
   {
      cout << "For sigma = " << sigma << endl;
      std::vector<double> samples = MathUtils::GenerateGaussianSamples( sigma );
      int size = samples.size();

      int nrQuantiles = 10;
      double  dataQuantiles[nrQuantiles];
      double modelQuantiles[nrQuantiles];

      double cumulSum = 0.0;
      double fraction = 1.0 / double(nrQuantiles+1);
      for (int i = 0; i < size; i++)
      {
         cumulSum += samples[i];
         for ( int j = 0; j < nrQuantiles; j++)
         {
            if ( cumulSum < (j+1)*fraction ) { dataQuantiles[j] = i; }
         }
      }

      std::vector< Point< double> > myPoints;
      for ( int j = 0; j < nrQuantiles; j++)
      {
         modelQuantiles[j] = QuantileNormalDistribution::Run( (j+1)*fraction );
         cout << j << "\t" << dataQuantiles[j] << "\t" << modelQuantiles[j] << endl;
         Point<double> pt(dataQuantiles[j], modelQuantiles[j]);
         myPoints.push_back( pt );
      }

      FitCurve fc( myPoints );
      std::vector<double> paramsLinear = fc.FitLinear( );
      cout << "Fitted y = " << paramsLinear[0] << " * x + " << paramsLinear[1] << " to QQ-plot with rho = "
           << Statistics<double>::GetCorrelation( dataQuantiles, modelQuantiles, nrQuantiles ) << endl;
   }
}

//------------------------------------------------------

void TestCorrelation()
{
   std::vector<double> vData1, vData2;
   vData1.push_back(  1 );  vData2.push_back( -6.842946122 );
   vData1.push_back(  2 );  vData2.push_back( -1.939954214 );
   vData1.push_back(  3 );  vData2.push_back( -1.65355662  );
   vData1.push_back(  4 );  vData2.push_back(  1.50095826 );
   vData1.push_back(  5 );  vData2.push_back(  3.24282038 );
   vData1.push_back(  6 );  vData2.push_back( 11.74910711 );
   vData1.push_back(  7 );  vData2.push_back( 14.34698600 );
   vData1.push_back(  8 );  vData2.push_back( 12.35675488 );
   vData1.push_back(  9 );  vData2.push_back( 17.44428189 );
   vData1.push_back( 10 );  vData2.push_back( 19.44932646 );
   vData1.push_back( 11 );  vData2.push_back( 21.09429656 );
   vData1.push_back( 12 );  vData2.push_back( 29.10691150 );
   vData1.push_back( 13 );  vData2.push_back( 32.11850657 );
   vData1.push_back( 14 );  vData2.push_back( 31.17123954 );

   double correlation = Statistics<double>::GetCorrelation( vData1, vData2 );

   assert ( fabs( correlation - 0.987039 ) < 0.00001 );
   cout << "TestCorrelation = " << correlation << endl << flush;
}

//------------------------------------------------------

int main()
{
   //TestArgument();
   //TestApplyModulo();
   //TestLineCurveFit();
   //TestQuadraticCurveFit();
   //TestCubicCurveFit();
   //TestExponentialCurveFit();
   //TestStatistics();
   //TestStatisticsBis();
   //TestCorrelation();
   //TestGaussianCurveFit();
   TestGaussianity();
}
