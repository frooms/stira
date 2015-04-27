/*
* Lower tail quantile for standard normal distribution function.
*
* This function returns an approximation of the inverse cumulative
* standard normal distribution function.  I.e., given P, it returns
* an approximation to the X satisfying P = Pr{Z <= X} where Z is a
* random variable from the standard normal distribution.
*
* The algorithm uses a minimax approximation by rational functions
* and the result has a relative error whose absolute value is less
* than 1.15e-9.
*
* Author:      Peter John Acklam
* Time-stamp:  2002-06-09 18:45:44 +0200
* E-mail:      jacklam@math.uio.no
* WWW URL:     http://www.math.uio.no/~jacklam
*
* C implementation adapted from Peter's Perl version
*
* Downloaded from http://home.online.no/~pjacklam/notes/invnorm/impl/sprouse/ltqnorm.c
*
*/

#ifndef STIRA_COMMON_QUANTILENORMALDISTRIBUTION_H
#define STIRA_COMMON_QUANTILENORMALDISTRIBUTION_H

#include <cmath>
#include <errno.h>
#include <vector>

namespace stira {
namespace common {

#define LOW  0.02425
#define HIGH 0.97575

class QuantileNormalDistribution
{
public:
   QuantileNormalDistribution();

   /** \brief returns for a probability p of a density function the corresponding quantile
     * a histogram can when normalized be considered to be a probability density function*/
   static double Run( double p );

   /** \brief analyse a normalised histogram if its quantiles follow those of a normal distribution
     * If the normalizedHistogram follows a normal distribution, the points in a Quantile-Quantile plot follow a straight line
     * \param normalizedHistogram the histogram (expected to be normalized) as input
     * \param rho the correlation coefficient of the quantiles of the input histogram and those of a standard normal dsitribution
     * \param writeQuantiles flag whether or not to write the quantiles
     * \return a vector (a, b) that describes the linear relationship y = ax+b between the normal quantiles and the histogram quantiles*/
   static std::vector<double> AnalyseNormalizedHistogram( std::vector<double> normalizedHistogram, double& rho, bool writeQuantiles=false );

private:

   /* Coefficients in rational approximations. */
   static const double a[];

   static const double b[];

   static const double c[];

   static const double d[];
};

}
}

#endif // QUANTILENORMALDISTRIBUTION_H
