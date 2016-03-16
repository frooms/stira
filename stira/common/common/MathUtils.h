
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

#ifndef STIRA_COMMON_MATHUTILS_H
#define STIRA_COMMON_MATHUTILS_H

#include <stdint.h>
#include <complex>
#include <vector>

#include "Point.h"

namespace stira {

namespace common {

/** \brief A class with some handy mathematical functions.
  * <OL><LI> SWITCH TWO VALUES
  *     <LI> ORDER / COMPARE STUFF / CLIP RANGE / CHECK IF IS RANGE
  *     <LI> STUFF RELATED TO ANGLES
  *     <LI> SOLVE LINEAR / QUADRATIC EQUATIONS
  *     <LI> COMPUTE MATHEMATICAL FUNCTION VALUE
  *     <LI> COMPUTE VALUES OF GAUSSIAN FUNCTION / DERIVATIVES
  *     <LI> COMPUTE STATISTICS
  * </OL> */
class MathUtils{
public:

   /** \brief Constructor.*/
   MathUtils();

   /** \brief Destructor. */
   ~MathUtils();

   // 1. SWITCH TWO VALUES
   ///////////////////////

   /** \brief switches the values for the variables a and b
     * \param a the first value; gets the value of b after switch
     * \param b the second value; gets the value of a after switch*/
   static void SwitchValues(double& a, double& b);

   /** \brief switches the values for the variables a and b
     * \param a the first value; gets the value of b after switch
     * \param b the second value; gets the value of a after switch*/
   static void SwitchValues(int& a, int& b);

   // 2. ORDER / COMPARE STUFF / CLIP RANGE / CHECK IF IS RANGE
   ////////////////////////////////////////////////////////////

   /** \brief returns the smallest of both input values
     * \param value1 first input value
     * \param value2 second input value*/
   static double GetMin(double value1, double value2);

   /** \brief returns the largest of both input values
     * \param value1 first input value
     * \param value2 second input value*/
   static double GetMax(double value1, double value2);

   /** \brief compare method for two doubles, as needed by qsort
     * \param a first number to compare
     * \param b second number to compare
     * \return -1 if the first number is the smallest, 1 if it is bigger and 0 if both numbers are equal*/
   static int CompareDoubles(const void *a, const void *b);

   /** \brief compare method for two floats, as needed by qsort
     * \param a first number to compare
     * \param b second number to compare
     * \return -1 if the first number is the smallest, 1 if it is bigger and 0 if both numbers are equal*/
   static int CompareFloats(const void *a, const void *b);

   /** \brief compare method for two doubles, as needed by qsort
     * \param a first number to compare
     * \param b second number to compare
     * \return -1 if the first number is the smallest, 1 if it is bigger and 0 if both numbers are equal*/
   static int CompareIntegers(const void *a, const void *b);

   /** \brief Clips value to be in the range [min, max]
     * if the user by accident switches the maximum and minimum values, this method corrects this
     * \param min the minimum value allowed value after clipping
     * \param value the value to be clipped
     * \param max the maximum value allowed after clipping*/
   static int ClipValue( int value, int min=0, int max=255 );

   /** \brief Clips value to be in the range [min, max]
     * if the user by accident switches the maximum and minimum values, this method corrects this
     * \param min the minimum value allowed value after clipping
     * \param value the value to be clipped
     * \param max the maximum value allowed after clipping*/
   static double ClipValue(double value, double min=0.0 , double max=255.0);

   /** \brief Checks if a value is between a lower and an upper value
        * \param testValue the value to be checked
        * \param underLimit the lower limit for the value
        * \param upperLimit the upper limit for the value */
   static bool IsBetween(double testValue, double underLimit, double upperLimit);

   /** \brief applies modulo to number
     * While number is larger than number, subtract modulo; While number is smaller than 0, add modulo
     * \param input input number
     * \param modulo modulo*/
   static double ApplyModulo( double input, double modulo );

   /** \brief prints to stdout the bits in a 32bit unsigned integer
     * \param i input unigned integer */
   static void PrintBitsInInt(unsigned int i);

   /** \brief prints to stdout the bits in an unsigned char
     * \param c input unigned char */
   static void PrintBitsInChar(unsigned char c);

   /** \brief combine 4 unsigned in one 32 bit unsigned integer
     *   [ 1 1 1 1 1 1 1 1 ] [ 1 1 1 1 1 1 1 1 ] [ 1 1 1 1 1 1 1 1 ] [ 1 1 1 1 1 1 1 1 ]
     *     unsigned char c0    unsigned char c1    unsigned char c2    unsigned char c3
     *
     * \param c0 first  input unsigned char, will be placed at the most significant bits of the integer
     * \param c1 second input unsigned char, will be placed at the next 8 less significant bits of the integer
     * \param c2 third  input unsigned char, will be placed at the next 8 less significant bits of the integer
     * \param c3 fourth input unsigned char, will be placed at the least significant bits of the integer
     */
   static unsigned int CombineCharsInInt(unsigned char i0, unsigned char i1, unsigned char i2, unsigned char i3);

   /** \brief splits a 32bit unsigned integer in a vector of 4 unsigned chars
     * \param value input unsigned integer */
   static std::vector<unsigned char> SplitIntInChars( int value );

   // 3. STUFF RELATED TO ANGLES
   /////////////////////////////

   /** \brief computes the angle of the line from the origin to the point (x,y)
     * \param x x coordinate
     * \param y y coordinate */
   static double ComputeArgument(double x, double y);

   /** \brief converts degrees to radians
     * \param degrees value in degrees to convert to radians*/
   static double ToRadians( double degrees );

   /** \brief converts radians to degrees
     * \param radians value in radians to convert to degrees*/
   static double ToDegrees( double radians );

   // 4. SOLVE LINEAR / QUADRATIC EQUATIONS
   ////////////////////////////////////////

   /** \brief solves a linear equation ax + b = 0
     * \param a slope coefficient
     * \param b offset
     * \param solution the solution of the equation
     * \return false if there is no solution (a==0); true otherwise*/
   static bool SolveLinearEquation (double a, double b, double& solution);

   /** \brief solves a quadratic equation a * x * x + b * x + c = 0 (real-valued case)
     * \param a quadratic coefficient
     * \param b linear coefficient
     * \param c constant
     * \param outSolution1 the first solution of the equation
     * \param outSolution2 the second solution of the equation
     * \return true if solutions are real-valued; false otherwise*/
   bool SolveQuadraticEquation( double a, double b, double c, double& outSolution1, double& outSolution2);

   /** \brief solves a quadratic equation a * x * x + b * x + c = 0 (complex-valued case)
     * \param a quadratic coefficient
     * \param b linear coefficient
     * \param c constant
     * \param outSolution1 the first solution of the equation
     * \param outSolution2 the second solution of the equation
     * \return true if solutions are real-valued; false otherwise*/
   static bool SolveQuadraticEquation ( std::complex<double> a, std::complex<double> b, std::complex<double> c,
                                        std::complex<double>& outSolution1, std::complex<double>& outSolution2);

   // 5. COMPUTE MATHEMATICAL FUNCTION VALUE
   /////////////////////////////////////////

   /** \brief Computes PSNR (Peak Signal to Noise Ratio) given the MSE (Mean Square Error)
     * Ref: http://en.wikipedia.org/wiki/PSNR
     * \param MSE the MSE (Mean Square Error)
     * \param peakValue maximum possible value of the data range */
   static double ComputePSNR( double MSE, double peakValue=255.0 );

   /** \brief applies gamma correction to input value
     * Data is for gamma correction first normalized between 0 and 1
     * \param inValue incoming value
     * \param gamma value of gamma
     * \param rangeMin minimum of data range of incoming value
     * \param rangeMax maximum of data range of incoming value*/
   static double GammaCorrect( double inValue, double gamma, double rangeMin=0.0, double rangeMax=255.0);

   /** \brief computes steerable interpolation coefficient for angle theta
     * Suppose B_theta(x,y) = k1(theta) * B1(x,y)) + k2(theta) * B2(x,y)) + k3(theta) * B1(x,y),
     *    with B_theta the interpolated band, ki(theta) the interpolation coefficients (i=1,2,3)
     *    and Bi(x,y) the basis bands (i=1,2,3).
     * then this function computes ki(theta)
     * This formulation is a generalization of the expression of Freeman and Adelson by Bart Goossens
     * for an arbitrary number of orientations
     * \param i the number of the band with which the interpolation coefficient corresponds (see above)
     * \param K the total number of oriented bands (in our example above, K=3)
     * \param theta the angle under which to interpolate*/
   static double GetSteerableInterPolationCoefficient(int i, int K, double theta);

   /** \brief help function to have an exact factorial in case the input number is a casted integer
     * \param inputNumber number of which to compute the factorial*/
   static double Factorial(const double& inputNumber);

   /** \brief computes myNumber to the power myExponent, to prevent all that messy casting that pow() otherwise requires
     * \param myNumber the number to be raised to the power myExponent
     * \param myExponent the exponent to be used*/
   static int ComputeIntegerPower(int myNumber, int myExponent);

   // 6. COMPUTE VALUES OF GAUSSIAN FUNCTION / DERIVATIVES
   ///////////////////////////////////////////////////////

   /** \brief computes a set of points sampled regularly from the Gauss function (NOT random variables with Gaussian distribution!!)
     * \param sigma sigma of the function */
   static std::vector<double> GenerateGaussianSamples( double sigma );

   /** \brief computes a set of Gaussian sample points
     * The Gaussian has the peak at gaussCenterX, unity sample distance and half width 2 times sigma
     * \param gaussCenterX x coordinate cooresponding with the center (i.e., the peak)
     * \param sigma sigma of the gaussian profile
     * \param scaleAmplitude flag whether or not the values are rescaled so the peak has a predefined value
     * \param amplitude predefined value for the peak */
   static std::vector< Point<double> > GenerateGaussianPoints( int gaussCenterX, double sigma, bool scaleAmplitude=false, double amplitude=1 );

   /** \brief computes a set of Gaussian sample points
     * It uses the x coordinates of inPoints to compute the function value with the peak at gaussCenterX
     * \param gaussCenterX x coordinate cooresponding with the center (i.e., the peak)
     * \param sigma sigma of the gaussian profile
     * \param scaleAmplitude flag whether or not the values are rescaled so the peak has a predefined value
     * \param amplitude predefined value for the peak */
   static std::vector< Point<double> > GenerateGaussianPoints( std::vector< Point<double> > inPoints, int gaussCenterX, double sigma, bool scaleAmplitude, double amplitude );

   /** \brief computes for a value x the value G(x) with G the Gaussian function (as used in probabilities)
     * Reference: http://mathworld.wolfram.com/GaussianFunction.html
     * G(x) = 1/sqrt(2*sigma*pi) * exp( (x - mu) / 2 sigma^2 )
     * \param x value for which to compute the function value
     * \param mu mu of the function (related to the position of the peak of the function )
     * \param sigma sigma of the function (related to the width)*/
   static double Gaussian( double x, double mu, double sigma );

   /** \brief computes for a point (x,y) the value G(x,y) with G the 2D Gaussian function (as used in probabilities)
     * Reference: http://mathworld.wolfram.com/GaussianFunction.html
     * G(x) = 1/(2*pi*sigmaX*sigmaY) * exp( (x - muX) / (2 sigmaX^2) + (y - muY) / (2 sigmaY^2) )
     * \param x x coordinate of point for which to compute the function value
     * \param y y coordinate of point for which to compute the function value
     * \param muX muX of the function (related to the x coordinate of the position of the peak of the function )
     * \param muY muY of the function (related to the y coordinate of the position of the peak of the function )
     * \param sigmaX sigmaX of the function (related to the width in the x-direction)
     * \param sigmaY sigmaY of the function (related to the width in the y-direction)*/
   static double Gaussian( double x, double y, double muX, double muY, double sigmaX, double sigmaY );

   /** \brief computes for a value x the value G'(x) with G' the first derivative of the Gaussian function
     * \param x value for which to compute the function value
     * \param mu mu of the function
     * \param sigma sigma of the function */
   static double GaussianFirstDerivativeX1D( double x, double mu, double sigma );

   /** \brief computes for a value x the value G''(x) with G'' the second derivative of the Gaussian function
     * \param x value for which to compute the function value
     * \param mu mu of the function
     * \param sigma sigma of the function*/
   static double GaussianSecondDerivateX1D( double x, double mu, double sigma );

   /** \brief computes for a point (x,y) the value of the first derivative to x of the 2D Gaussian function
     * \param x x coordinate of point for which to compute the function value
     * \param y y coordinate of point for which to compute the function value
     * \param muX muX of the function (related to the x coordinate of the position of the peak of the function )
     * \param muY muY of the function (related to the y coordinate of the position of the peak of the function )
     * \param sigmaX sigmaX of the function (related to the width in the x-direction)
     * \param sigmaY sigmaY of the function (related to the width in the y-direction)*/
   static double GaussianDx( double x, double y, double muX, double muY, double sigmaX, double sigmaY );

   /** \brief computes for a point (x,y) the value of the first derivative to y of the 2D Gaussian function
     * \param x x coordinate of point for which to compute the function value
     * \param y y coordinate of point for which to compute the function value
     * \param muX muX of the function (related to the x coordinate of the position of the peak of the function )
     * \param muY muY of the function (related to the y coordinate of the position of the peak of the function )
     * \param sigmaX sigmaX of the function (related to the width in the x-direction)
     * \param sigmaY sigmaY of the function (related to the width in the y-direction)*/
   static double GaussianDy( double x, double y, double muX, double muY, double sigmaX, double sigmaY );

   /** \brief computes for a point (x,y) the value of the second derivative to x of the 2D Gaussian function
     * \param x x coordinate of point for which to compute the function value
     * \param y y coordinate of point for which to compute the function value
     * \param muX muX of the function (related to the x coordinate of the position of the peak of the function )
     * \param muY muY of the function (related to the y coordinate of the position of the peak of the function )
     * \param sigmaX sigmaX of the function (related to the width in the x-direction)
     * \param sigmaY sigmaY of the function (related to the width in the y-direction)*/
   static double GaussianSecondDerivateX1D( double x, double y, double muX, double muY, double sigmaX, double sigmaY );

   /** \brief computes for a point (x,y) the value of the second derivative to y of the 2D Gaussian function
     * \param x x coordinate of point for which to compute the function value
     * \param y y coordinate of point for which to compute the function value
     * \param muX muX of the function (related to the x coordinate of the position of the peak of the function )
     * \param muY muY of the function (related to the y coordinate of the position of the peak of the function )
     * \param sigmaX sigmaX of the function (related to the width in the x-direction)
     * \param sigmaY sigmaY of the function (related to the width in the y-direction)*/
   static double GaussianD2y( double x, double y, double muX, double muY, double sigmaX, double sigmaY );

   /** \brief computes for a point (x,y) the value of the mixed first derivatives to x and y of the 2D Gaussian function
     * \param x x coordinate of point for which to compute the function value
     * \param y y coordinate of point for which to compute the function value
     * \param muX muX of the function (related to the x coordinate of the position of the peak of the function )
     * \param muY muY of the function (related to the y coordinate of the position of the peak of the function )
     * \param sigmaX sigmaX of the function (related to the width in the x-direction)
     * \param sigmaY sigmaY of the function (related to the width in the y-direction)*/
   static double GaussianDxDy( double x, double y, double muX, double muY, double sigmaX, double sigmaY );

   // 7. COMPUTE STATISTICS
   ////////////////////////

   /** \brief Computes cross-correlation between two signals x and y
     * Reference: code + explanation: http://local.wasp.uwa.edu.au/~pbourke/miscellaneous/correlate/
     *            general:            http://en.wikipedia.org/wiki/Cross-correlation
     * \param x array of values of first function
     * \param y array of values of second function
     * \param nrSamples number of elements in x and y
     * \param maxDelay maximum delay to compute cross-correlation for
     * \return array of (2*maxDelay) cross-correlation values */
   static double* ComputeCrossCorrelation( double* x, double* y, int nrSamples, int maxDelay );

   /** \brief normalizes all elements of the vector passed as argument, overwriting the original values
     * \param inVector vector to normalize  */
   static void NormalizeVector( std::vector<double>& inVector );

};
}
}

#endif
