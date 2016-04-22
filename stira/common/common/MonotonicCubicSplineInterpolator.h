
/***************************************************************************************
 *   Copyright (C) 2016 by Filip Rooms                                                 *
 *                                                                                     *
 *  Terms and conditions for using this software in any form are provided in the       *
 *  file COPYING, which can be found in the root directory of this project.            *
 *                                                                                     *
 *   Contact data: filip.rooms@gmail.com                                               *
 *                 http://www.filiprooms.be/                                           *
 *                                                                                     *
 ***************************************************************************************/
#ifndef STIRA_COMMON_MONOTONICCUBICSPLINEINTERPOLATOR_H
#define STIRA_COMMON_MONOTONICCUBICSPLINEINTERPOLATOR_H

#include <vector>

namespace stira {
namespace common {

/** \brief help struct to create data interpolation */
struct dataRow
{
    double x;    ///< x coordinate of source datapoint
    double y;    ///< x coordinate of source datapoint
    double delta;    ///< slopes of the secant lines between successive data points
    double m;        ///< tangents at every data point
    double alpha;
    double beta;
};

/** Class for monotone cubic spline interpolation
 * Ref: https://en.wikipedia.org/wiki/Monotone_cubic_interpolation
 *      http://math.stackexchange.com/questions/45218/implementation-of-monotone-cubic-interpolation */
class MonotonicCubicSplineInterpolator
{
public:
    /** \brief constructor
      * \param dataPoints input data points */
    MonotonicCubicSplineInterpolator( std::vector< std::pair<double, double> > dataPoints );

    /** \brief actually interpolate for a given value
      * \param x the value for which to interpolate */
    double Interpolate(double x);

private:
    /** \brief Hermite_00 base function
      * \param t the function argument */
    double Hermite00(double t);

    /** \brief Hermite_10 base function
      * \param t the function argument */
    double Hermite10(double t);

    /** \brief Hermite_01 base function
      * \param t the function argument */
    double Hermite01(double t);

    /** \brief Hermite_11 base function
      * \param t the function argument */
    double Hermite11(double t);

    /** \brief Create the interpolation function based on the input data points */
    void CreateInterpolant( );

    std::vector<dataRow> mData;  ///< input data points
    int mNumberOfPoints;     ///< number of input data points
};

}
}

#endif // MONOTONICCUBICSPLINEINTERPOLATOR_H
