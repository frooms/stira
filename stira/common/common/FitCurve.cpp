
/***************************************************************************************
 *   Copyright (C) 2011 by Filip Rooms                                                 *
 *                                                                                     *
 *  Terms and conditions for using this software in any form are provided in the       *
 *  file COPYING, which can be found in the root directory of this project.            *
 *                                                                                     *
 *   Contact data: filip.rooms@gmail.com                                               *
 *                 http://www.filiprooms.be/                                           *
 *                                                                                     *
 ***************************************************************************************/

#include "FitCurve.h"
#include "StiraMacros.h"
#include "MathUtils.h"
#include <cassert>
#include <algorithm>
#include <opencv2/opencv.hpp>


#define FIT_EPSILON 0.001
#define FIT_NOISE_MU 0.0
#define FIT_NOISE_SIGMA 3.0

using namespace std;

namespace stira {
namespace common {

//---------------------------------------------------------------------------------

FitCurve::FitCurve( vector< Point<int> > inputPoints )
{
   //cout << " -> got " << inputPoints.size() << " input points " << endl;
   SetPoints( inputPoints );
   mIsFitReady = false;
   mIsModelDataReady = false;
   mIsErrorVectorReady = false;
   mNumberOfIterations = 0;
}

//---------------------------------------------------------------------------------

FitCurve::FitCurve( vector< Point<double> > inputPoints )
{
   SetPoints( inputPoints );
   mIsFitReady = false;
   mIsModelDataReady = false;
   mIsErrorVectorReady = false;
   mNumberOfIterations = 0;
}

//---------------------------------------------------------------------------------

void FitCurve::SetPoints( std::vector< Point<double> > inputPoints )
{
   mvDataPoints.clear();
   int nrPoints = inputPoints.size();
   for (int i = 0; i < nrPoints; i++)
   {
      mvDataPoints.push_back( inputPoints[i] );
   }
}

//---------------------------------------------------------------------------------

void FitCurve::SetPoints( std::vector< Point<int> > inputPoints )
{
   mvDataPoints.clear();
   int nrPoints = inputPoints.size();
   for (int i = 0; i < nrPoints; i++)
   {
      Point<double> myPoint( (double)(inputPoints[i].GetX()), (double)(inputPoints[i].GetY() ) );
      mvDataPoints.push_back( myPoint );
   }
}

//---------------------------------------------------------------------------------

vector<double> FitCurve::FitLinear( )
{
   mIsFitReady = false;
   mIsModelDataReady = false;
   mIsErrorVectorReady = false;
   mvOutParameters.clear();
   mFitType = FIT_LINEAR;
   double meanX = 0.0;
   double meanY = 0.0;
   int nrPoints = 0;
   for( std::vector< common::Point<double> >::iterator it = mvDataPoints.begin();
        it != mvDataPoints.end();
        ++it
      )
   {
      meanX += (double)( (*it).GetX() );
      meanY += (double)( (*it).GetY() );
      nrPoints++;
   }
   meanX /= nrPoints;
   meanY /= nrPoints;

   double Sxx = 0.0;
   double Syy = 0.0;
   double Sxy = 0.0;

   for( std::vector< common::Point<double> >::iterator it = mvDataPoints.begin();
        it != mvDataPoints.end();
        ++it
      )
   {
      double tmpX = (double)( (*it).GetX() ) - meanX;
      double tmpY = (double)( (*it).GetY() ) - meanY;

      Sxx += POWER2( tmpX );
      Syy += POWER2( tmpY );
      Sxy += ( tmpX * tmpY );
   }

   mvOutParameters.push_back( Sxy / ( Sxx + FIT_EPSILON ) );
   mvOutParameters.push_back( meanY - ( mvOutParameters[0] * meanX) );
   mIsFitReady = true;

   return mvOutParameters;
}

//---------------------------------------------------------------------------------

vector<double> FitCurve::FitQuadratic( )
{
   mIsFitReady = false;
   mIsModelDataReady = false;
   mIsErrorVectorReady = false;
   mvOutParameters.clear();
   mFitType = FIT_QUADRATIC;

   double S40 = 0.0;
   double S30 = 0.0;
   double S20 = 0.0;
   double S10 = 0.0;
   double S00 = 0.0;

   double S21 = 0.0;
   double S11 = 0.0;
   double S01 = 0.0;

   for( std::vector< common::Point<double> >::iterator it = mvDataPoints.begin();
        it != mvDataPoints.end();
        ++it
      )
   {
      double tmpX = (*it).GetX();
      double tmpY = (*it).GetY();
      S40 += POWER4( tmpX );
      S30 += POWER3( tmpX );
      S20 += POWER2( tmpX );
      S10 += tmpX;
      S00 ++;

      S21 += ( POWER2( tmpX ) * tmpY );
      S11 += ( tmpX * tmpY );
      S01 += tmpY;
   }
   double denominator = (S00*S20*S40 -  POWER2( S10 )*S40 - S00* POWER2( S30 ) + 2*S10*S20*S30 - POWER3( S20 ) ) + FIT_EPSILON;

   double a = (S01*S10*S30 - S11*S00*S30 - S01* POWER2( S20 )
           + S11*S10*S20 + S21*S00*S20 - S21* POWER2( S10 ) )
        / denominator;

   double b = (S11*S00*S40 - S01*S10*S40 + S01*S20*S30
        - S21*S00*S30 - S11* POWER2( S20 ) + S21*S10*S20)
         / denominator;

   double c = (S01*S20*S40 - S11*S10*S40 - S01* POWER2( S30 )
        + S11*S20*S30 + S21*S10*S30 - S21* POWER2( S20 ) )
              / denominator;

   mvOutParameters.push_back( a );
   mvOutParameters.push_back( b );
   mvOutParameters.push_back( c );
   mIsFitReady = true;
   return mvOutParameters;
}

//---------------------------------------------------------------------------------

vector<double> FitCurve::FitExponential( )
{
   mIsFitReady = false;
   mIsModelDataReady = false;
   mIsErrorVectorReady = false;
   mvOutParameters.clear();
   mFitType = FIT_EXPONENTIAL;
   double X2Y   = 0.0;
   double XY    = 0.0;
   double  Y    = 0.0;
   double XYlnY = 0.0;
   double YlnY  = 0.0;

   for( std::vector< common::Point<double> >::iterator it = mvDataPoints.begin();
        it != mvDataPoints.end();
        ++it
      )
   {
      {
         double tmpX = (*it).GetX();
         double tmpY = (*it).GetY();
         X2Y   += POWER2( tmpX ) * tmpY;
         XY    += tmpX * tmpY;
         Y     += tmpY;
         YlnY  += tmpY * log ( tmpY );
         XYlnY += tmpX * tmpY * log ( tmpY );
      }
   }
   double denominator = Y * X2Y - POWER2( XY ) + FIT_EPSILON;

   mvOutParameters.push_back( exp( ( (X2Y * YlnY) - (XY * XYlnY) ) / denominator ) );
   mvOutParameters.push_back( ( (Y * XYlnY) - (XY * YlnY) ) / denominator );
   mIsFitReady = true;
   return mvOutParameters;
}

//---------------------------------------------------------------------------------
// to visualize with gnuplot: remove first line and type then
//    gnuplot> set style data lines
//    gnuplot> plot './FineName.txt' using 1:2, './FileName.txt' using 1:3
void FitCurve::CreateModelPoints()
{
   mvModelPoints.clear();
   mIsModelDataReady = false;
   int nrPoints = mvDataPoints.size();
   switch (mFitType)
   {
      case FIT_QUADRATIC:
      {
      cout << "Fitting quadratic model evaluation" << endl;
         double a = mvOutParameters[0];
         double b = mvOutParameters[1];
         double c = mvOutParameters[2];
         for (int i = 0; i < nrPoints; i++)
         {
            double x = mvDataPoints[i].GetX();
            double y = a * x * x + b * x + c;
            mvModelPoints.push_back( Point<double>( x, y ) );
         }
         break;
      }
      case FIT_EXPONENTIAL:
      {
      cout << "Fitting exponential model evaluation" << endl;
         double a = mvOutParameters[0];
         double b = mvOutParameters[1];
         for (int i = 0; i < nrPoints; i++)
         {
            double x = mvDataPoints[i].GetX();
            double y = a * exp( x * b);
            mvModelPoints.push_back( Point<double>( x, y ) );
         }
         break;
      }
      case FIT_LINEAR:
      {
      cout << "Fitting linear model evaluation" << endl;
         double a = mvOutParameters[0];
         double b = mvOutParameters[1];
         for (int i = 0; i < nrPoints; i++)
         {
            double x = mvDataPoints[i].GetX();
            double y = a * x + b;
            mvModelPoints.push_back( Point<double>( x, y ) );
         }
         break;
      }
   case FIT_GAUSSIAN:
   {
      cout << "Fitting gaussian model evaluation" << endl;
      mvModelPoints = MathUtils::GenerateGaussianPoints( mvDataPoints, mvOutParameters[1], mvOutParameters[2], true, mvOutParameters[0] );
      break;
   }
   default:
   case FIT_POLYNOMIAL:
   {
      cout << "Fitting polynomial model evaluation" << endl;
      for (int i = 0; i < nrPoints; i++)
      {
         double x = mvDataPoints[i].GetX();
         double y = 0.0;
         for (int j = 0; j <= mPolynomialDegree; j++ )
         {
            y += mvOutParameters[j] * pow( x, (double)(mPolynomialDegree-j) );
         }
         mvModelPoints.push_back( Point<double>( x, y ) );
      }
      break;
   }
   }
   mIsModelDataReady = true;
   assert( mvDataPoints.size() == mvModelPoints.size() );
}

//---------------------------------------------------------------------------------

std::vector<double> FitCurve::GetAllAbsoluteErrors()
{
   if ( !mIsErrorVectorReady )
   {
      ComputeFittingErrors( );
      assert( mvDataPoints.size() == mvFitAbsoluteErrors.size() );
   }
   return mvFitAbsoluteErrors;
}

//---------------------------------------------------------------------------------

void FitCurve::ComputeFittingErrors( )
{
   cout << "Computing the fitting errors comparing data with created model" << endl << flush;
   mIsErrorVectorReady = false;
   mvModelPoints.clear();
   CreateModelPoints();
   mvFitAbsoluteErrors.clear();
   int nrPoints = mvDataPoints.size();
   cout << "Computing " << nrPoints << " fitting errors " << endl;
   for (int i = 0; i < nrPoints; i++)
   {
      mvFitAbsoluteErrors.push_back( fabs( mvDataPoints[i].GetY() - mvModelPoints[i].GetY() ) );
   }
   //std::sort( mvFitAbsoluteErrors.begin(), mvFitAbsoluteErrors.end(), std::greater<double>() );

   mIsErrorVectorReady = true;
}

//---------------------------------------------------------------------------------

double FitCurve::GetMeanAbsoluteError()
{
   GetAllAbsoluteErrors();
   double avgError = 0.0;
   int nrPoints = mvFitAbsoluteErrors.size();
   for (int i = 0; i < nrPoints; i++)
   {
      avgError += mvFitAbsoluteErrors[i];
   }
   return ( avgError / nrPoints );
}

//---------------------------------------------------------------------------------

// http://mathworld.wolfram.com/LeastSquaresFittingPolynomial.html
vector<double> FitCurve::PolynomialFit( int polynomialDegree )
{
   mIsFitReady = false;
   mIsModelDataReady = false;
   mIsErrorVectorReady = false;
   mPolynomialDegree = polynomialDegree;
   mvOutParameters.clear();
   mFitType = FIT_POLYNOMIAL;
   int nrPoints = mvDataPoints.size();
   cv::Mat myX = cv::Mat( nrPoints, polynomialDegree + 1, CV_64F ); // Mat m = Mat(rows, cols, type);
   cv::Mat myY = cv::Mat( nrPoints, 1, CV_64F );
   cv::Mat myA = cv::Mat( polynomialDegree + 1, 1, CV_64F );

   for (int i = 0; i < nrPoints; i++)
   {
      double currentPointX = mvDataPoints[i].GetX();
      for (int j = 0; j < polynomialDegree+1; j++)
      {
         myX.at<double>( i, j ) = pow( currentPointX, (double)(j) );
      }
      myY.at<double>(i,0) = mvDataPoints[i].GetY();
   }
   // http://en.wikipedia.org/wiki/Polynomial_regression
   myA = ( myX.t() * myX ).inv() * myX.t() * myY;

   for (int i = 0; i < polynomialDegree+1; i++)
   {
      mvOutParameters.push_back( myA.at<double>(polynomialDegree-i,0) );
   }
   mIsFitReady = true;
   return mvOutParameters;
}

//---------------------------------------------------------------------------------

//http://en.wikipedia.org/wiki/Least_squares#Weighted_least_squares
// check also PhD Hiep p 88-89 and 194

// http://terpconnect.umd.edu/~toh/spectrum/CurveFitting.html
// An interesting example of the use of transformation to convert a non-linear relationship into a form
// that is amenable to polynomial curve fitting is the use of the natural log (ln) transformation to
// convert a Gaussian peak, which has the fundamental functional form exp(-x2), into a parabola of the
// form -x2, which can be fit with a second order polynomial (quadratic) function (y = a + bx + cx2).
// The equation for a Gaussian peak is y = height*exp(-((x-position)./(0.6005615*width)) ^2), where height
// is the peak height, position is the x-axis location of the peak maximum, and width is the width of the
// peak at half-maximum. A little algebra will show that all three parameters of the peak (height, maximum
// position, and width) can be calculated from the three quadratic coefficients a, b, and c;
//   - the peak height is given by exp(a-c*(b/(2*c))^2)
//   - the peak position by -b/(2*c)
//   - the peak half-width by 2.35482/(sqrt(2)*sqrt(-c)).
vector<double> FitCurve::GaussianFitLeastSquares( )
{
   //cout << mvDataPoints.size() << " input data points for fitting " << endl << flush;
   int polynomialDegree = 2;
   mIsFitReady = false;
   mIsModelDataReady = false;
   mIsErrorVectorReady = false;
   mPolynomialDegree = polynomialDegree;
   mvOutParameters.clear();
   int nrPoints = mvDataPoints.size();

   //cout << mvDataPoints.size() << " before transform input data points for fitting " << endl << flush;

   for (int i = 0; i < nrPoints; i++)
   {
      double currentPointX = mvDataPoints[i].GetX();
      double currentPointY = mvDataPoints[i].GetY();
      if ( currentPointY > 0 )
      {
         mvTransformedDataPoints.push_back( Point<double>( currentPointX, log( currentPointY ) ) );
      }
   }

   double peakHeight;
   double peakPosition;
   double sigma;

   if ( mvTransformedDataPoints.size() > 3)
   {
      std::vector< Point<double> > mvDataPointsCopy = mvDataPoints;
      mvDataPoints = mvTransformedDataPoints;

      vector<double> modelParameters = FitCurve::PolynomialFit( polynomialDegree );

      // notation as above y = a + bx + cx2
      double c = modelParameters[0];
      double b = modelParameters[1];
      double a = modelParameters[2];

      peakHeight  = exp( a - c * pow(( b / ( 2.0 * c ) ), 2.0 ) );
      peakPosition = -b / ( 2.0 * c );
      //double peakHalfWidth = 2.35482/(sqrt(2)*sqrt(-c));   // 2.35482 = 2*sqrt(2 ln 2)

      sigma = 1.0 / ( sqrt( 2.0 ) * sqrt( -c ) );   // FWHM = 2.35482 * sigma
      mvDataPoints = mvDataPointsCopy;
   }
   else
   {
      peakHeight = 0.0;
      peakPosition = mvDataPoints[nrPoints/2+1].GetX();
      sigma = 0.0;
   }

   mvOutParameters.clear(); // contains polynomial parameters
   mvOutParameters.push_back(peakHeight);
   mvOutParameters.push_back(peakPosition);
   mvOutParameters.push_back(sigma);
   mFitType = FIT_GAUSSIAN;
   mIsFitReady = true;
   return mvOutParameters;
}

//---------------------------------------------------------------------------------

bool FitCurve::WriteToDisk( std::string fileName )
{
   if (!mIsModelDataReady)
   {
      CreateModelPoints();
   }
   cerr << "Model Points ready..." << endl;

   ofstream ofp;
   ofp.open(const_cast<char*>(fileName.c_str()), ios::out);

   if (!ofp)
   {
      cerr << "Can't open file: " << fileName << endl;
      return false;
   }

   int nrPoints = mvDataPoints.size();
   ofp << "x \t y_data \t y_fit " << endl;
   for(int i = 0; i < nrPoints; i++)
   {
      ofp << mvDataPoints[i].GetX() << std::string("\t") << mvDataPoints[i].GetY() << std::string("\t") << mvModelPoints[i].GetY() << endl;
   }

   ofp.close();
   return true;
}

//---------------------------------------------------------------------------------

}
}
