
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

#ifndef STIRA_IMAGE_GEOMETRICTRANSFORM_TRANSLATION_H
#define STIRA_IMAGE_GEOMETRICTRANSFORM_TRANSLATION_H

#include "GeometricTransform.h"

namespace stira {
namespace imagetools {

/** \brief class to translate an image */
class Translation : public GeometricTransform
{
public:
   /** \brief constructor */
   Translation( );

   /** \brief destructor */
   ~Translation( );
   
   /** \brief sets distance to translate in x direction
     * \param dx amount of translation in the x direction */
   void SetDeltaX( double dx );
   
   /** \brief sets distance to translate in y direction
     * \param dy amount of translation in the y direction */
   void SetDeltaY( double dy );

private:

   /** \brief computes coordinates of point after applying forward transform
     * \param x x coordinate of point to transform
     * \param y y coordinate of point to transform*/
   common::Point<double> GetTransformedPoint( double  x, double y );
   
   /** \brief computes coordinates of point after applying inverse transform
     * \param x x coordinate of point to transform
     * \param y y coordinate of point to transform*/
   common::Point<double> GetInverseTransformedPoint( double x, double y );
   
   double mDeltaX;  ///< distance to translate in x direction
   double mDeltaY;  ///< distance to translate in y direction
};
}
}

#endif

