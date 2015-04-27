
/***************************************************************************************
 *   Copyright (C) 2010 by Filip Rooms                                                 *
 *                                                                                     *
 *  Terms and conditions for using this software in any form are provided in the       *
 *  file COPYING, which can be found in the root directory of this project.            *
 *                                                                                     *
 *   Contact data: filip.rooms@gmail.com                                               *
 *                 http://www.filiprooms.be/                                           *
 *                                                                                     *
 ***************************************************************************************/

#ifndef STIRA_COMMON_FITCURVE_H
#define STIRA_COMMON_FITCURVE_H

#include <vector>
#include "Point.h"


namespace stira {
namespace common {

enum FitType{ FIT_LINEAR, FIT_QUADRATIC, FIT_POLYNOMIAL, FIT_EXPONENTIAL, FIT_GAUSSIAN };

/** \brief class to fit a parametric function to a set of data points
  * For the moment, only linear, quadratic and exponential fit are available */
class FitCurve
{
public:
    /** \brief constructor
      * \param inputPoints the points to which the data model has to be fitted */
    FitCurve( std::vector< Point<int> > inputPoints );

    /** \brief constructor
      * \param inputPoints the points to which the data model has to be fitted */
    FitCurve( std::vector< Point<double> > inputPoints );

    /** \brief sets the input data points (coordinates in double precision float format )
      * \param inputPoints the input data points */
    void SetPoints( std::vector< Point<double> > inputPoints );

    /** \brief sets the input data points (coordinates in integer format )
      * \param inputPoints the input data points  */
    void SetPoints( std::vector< Point<int> > inputPoints );

    /** \brief fits a straight line to a set of 2D points (x, y = a * x + b)
      * Source: <A HREF="http://mathworld.wolfram.com/LeastSquaresFitting.html">
      *                  http://mathworld.wolfram.com/LeastSquaresFitting.html</A>
      * \return vector with output parameters ( a, b ) */
    std::vector<double> FitLinear( );

    /** \brief fits a straight line to a set of 2D points (x, y = a * x^2 + b * x + c)
      * Source: <A HREF="http://mathforum.org/library/drmath/view/72047.html">
      *                  http://mathforum.org/library/drmath/view/72047.html</A>
      * \return vector with output parameters ( a, b, c ) */
    std::vector<double> FitQuadratic( );

    /** \brief fits an exponential to a set of 2D points ( x, y = a * exp( b * x ) )
      * Source <A HREF="http://mathworld.wolfram.com/LeastSquaresFittingExponential.html">
      *                 http://mathworld.wolfram.com/LeastSquaresFittingExponential.html</A>
      * \return vector with output parameters ( a, b ) */
    std::vector<double> FitExponential( );

    /** \brief Gets a vector with all errors (in absolute value between the data points and the modeled points */
    std::vector<double> GetAllAbsoluteErrors();

    /** \brief Gets a vector with the average absolute error */
    double GetMeanAbsoluteError();

    /** \brief Fitting of a general polynomial of a given degree n to a set of 2D points (x, y = a * x^n + b * x^(n-1) + ... )
      *   Math of the least square fitting: http://mathworld.wolfram.com/LeastSquaresFittingPolynomial.html
      *   Documentation of the used cv::Mat object: see http://opencv.willowgarage.com/documentation/cpp/basic_structures.html
      * \param polynomialDegree the degree of the polynomial
      * \return vector with output parameters ( a, b, ... ) */
    std::vector<double> PolynomialFit( int polynomialDegree );

    /** \brief Fitting of a guassian profile to a set of 2D points (x, y = G(x) )
      * Reference: http://terpconnect.umd.edu/~toh/spectrum/CurveFitting.html
      * \return vector with in the following order ( peakHeight, peakPosition, sigma) */
    std::vector<double> GaussianFitLeastSquares( );

    /** \brief writes source data points and points from the fitted model to disk
      * \param fileName name of file to write to */
    bool WriteToDisk( std::string fileName );
private:
    /** \brief Gets a vector with all errors (in absolute value between the data points and the modeled points */
    void ComputeFittingErrors( );

    /** \brief Creates the points according to the model */
    void CreateModelPoints();

    int mNumberOfIterations;

    std::vector< Point<double> > mvDataPoints;  ///< the input data points

    std::vector< Point<double> > mvTransformedDataPoints;  ///< the transformed input data points. e.g., to fit a Gaussian
    std::vector< Point<double> > mvModelPoints;  ///< the points according to the fitted model
    std::vector<double> mvOutParameters;        ///< the model parameters
    FitType mFitType;   ///< fitting type (linear, quadratic, exponential)
    std::vector<double> mvFitAbsoluteErrors;  ///< the errors in y in absolute value between the model en the data

    bool mIsFitReady;   ///< flag if fitting of the model is ready
    bool mIsModelDataReady;  ///< flag if the model data points are ready
    bool mIsErrorVectorReady;  ///< flag if the model data points are ready
    int mPolynomialDegree;  ///< the degree of the polynomial, in case a polynomial is fitted to the data points
};

}
}

#endif // FITCURVE_H
