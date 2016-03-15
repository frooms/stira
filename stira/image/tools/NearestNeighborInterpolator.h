
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

#ifndef STIRA_IMAGE_TOOLS_NEARESTNEIGHBORINTERPOLATOR_H
#define STIRA_IMAGE_TOOLS_NEARESTNEIGHBORINTERPOLATOR_H

#include "Interpolator.h"

namespace stira {
namespace image {

/** \brief child class for Nearest Neighbor interpolation
  */
class NearestNeighborInterpolator : public Interpolator
{
public:
   /** \brief constructor */
   NearestNeighborInterpolator();
   
   /** \brief destructor */
   virtual ~NearestNeighborInterpolator();
   
   /** \brief Runs interpolation
     * \param pGrid grid in which to interpolate
     * \param x x coordinate of point to be interpolated
     * \param y y coordinate of point to be interpolated */
   virtual double Run( ArrayGrid<double>* pGrid, double x, double y );
};

}
}

#endif
