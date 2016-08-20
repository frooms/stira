
/***********************************************************************************
 *   Copyright (C) 2016 by Filip Rooms                                             *
 *                                                                                 *
 *  Terms and conditions for using this software in any form are provided in the   *
 *  file COPYING, which can be found in the root directory of this project.        *
 *                                                                                 *
 *   Contact data: filip.rooms@gmail.com                                           *
 *                 http://www.filiprooms.be/                                       *
 *                                                                                 *
 ***********************************************************************************/

#ifndef STIRA_IMAGE_TOOLS_BICUBICINTERPOLATOR_H
#define STIRA_IMAGE_TOOLS_BICUBICINTERPOLATOR_H

#include "Interpolator.h"

namespace stira {
namespace imagetools {

/** \brief child class for bicubic interpolation
  * Source: http://www.paulinternet.nl/?page=bicubic
  */
class BicubicInterpolator: public Interpolator
{
public:
    /** \brief constructor */
    BicubicInterpolator();

    /** \brief destructor */
    virtual ~BicubicInterpolator();

    /** \brief Bicubic interpolation
      * \param pGrid grid in which to interpolate
      * \param x x coordinate of point to be interpolated
      * \param y y coordinate of point to be interpolated */
    virtual double Run( ArrayGrid<double>* pGrid, double x, double y );

private:

    /** \brief 1D cubic interpolation
     * \param array of function values at positions { xf - 1, xf, xc, xc + 1 }
     * \param x value to interpolate for (xc = ceil(x) and xf = floor(x))*/
    double cubicInterpolate (double p[4], double x);

    /** \brief Bicubic interpolation
     * \param array of function values at positions around point to be interpolated
     * \param x value to interpolate for
     * \param y value to interpolate for */
    double bicubicInterpolate (double p[4][4], double x, double y);
};


}
}

#endif // BICUBICINTERPOLATOR_H
