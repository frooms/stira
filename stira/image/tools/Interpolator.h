
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

#ifndef STIRA_IMAGE_TOOLS_INTERPOLATOR_H
#define STIRA_IMAGE_TOOLS_INTERPOLATOR_H

#include "../datastructures/ArrayGrid.h"

namespace stira {
namespace image {

/** \brief identifier of interpolation type*/
enum InterpolatorType { INTERPOLATE_NEAREST_NEIGHBOR, INTERPOLATE_BILINEAR, INTERPOLATE_BICUBIC };

/** \brief A class for interpolation
  */
class Interpolator
{
public:
   /** \brief constructor */
   Interpolator();

   /** \brief destructor */
  virtual ~Interpolator();

   /** \brief Runs interpolation
     * \param pGrid grid in which to interpolate
     * \param x x coordinate of point to be interpolated
     * \param y y coordinate of point to be interpolated */
   virtual double Run( ArrayGrid<double>* pGrid, double x, double y ) = 0;
};

}
}

#endif
