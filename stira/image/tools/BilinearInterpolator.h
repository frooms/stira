
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

#ifndef STIRA_IMAGE_TOOLS_BILINEARINTERPOLATOR_H
#define STIRA_IMAGE_TOOLS_BILINEARINTERPOLATOR_H

#include "Interpolator.h"

namespace stira {
namespace image {

/** \brief child class for bilinear interpolation
  * Source: http://en.wikipedia.org/wiki/Bilinear_interpolation
  */
class BilinearInterpolator: public Interpolator
{
public:
   /** \brief constructor */
   BilinearInterpolator();

   /** \brief destructor */
   virtual ~BilinearInterpolator();

   /** \brief Bilinear interpolation
     * \param pGrid grid in which to interpolate
     * \param x x coordinate of point to be interpolated
     * \param y y coordinate of point to be interpolated */
   virtual double Run( ArrayGrid<double>* pGrid, double x, double y );

   /** \brief Bilinear interpolation
     *
     *              x1           x                          x2
     *     +--------+------------+------------------------+----->
     *     |        |            |                        |
     *     |                     |
     *     |      (x1,y1)                               (x1,y1)
     *  y1 +-- I11  +------------+------------------------+  I21
     *     |        |            |                        |
     *     |        |            |                        |
     *  y  +---     +------------+------------------------+
     *     |        |            | (x,y)                  |
     *     |        |            |                        |
     *     |        |            |                        |
     *     |        |            |                        |
     *     |        |            |                        |
     *  y2 +--- I12 +------------+------------------------+ I22
     *     |      (x1,y2)                               (x2,y2)
     *     |
     *     V
     *
     * \param x1 x coordinate of top left corner (minimum x coordinate)
     * \param x2 x coordinate of bottom right corner (maximum x coordinate)
     * \param y1 y coordinate of top left corner (minimum y coordinate)
     * \param y2 y coordinate of bottom right corner (maximum y coordinate)
     * \param I11 (intensity) value at point (x1,y1)
     * \param I12 (intensity) value at point (x1,y2)
     * \param I21 (intensity) value at point (x2,y1)
     * \param I22 (intensity) value at point (x2,y2)
     * \param x x coordinate of point to be interpolated
     * \param y y coordinate of point to be interpolated */
   static double Run( double x1, double x2, double y1, double y2, double I11, double I12 , double I21, double I22, double x, double y );
};

}
}

#endif
