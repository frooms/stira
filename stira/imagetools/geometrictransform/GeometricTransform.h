
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

#ifndef STIRA_IMAGE_GEOMETRICTRANSFORM_GEOMETRICTRANSFORM_H
#define STIRA_IMAGE_GEOMETRICTRANSFORM_GEOMETRICTRANSFORM_H

#include "../interpolation/Interpolator.h"
#include "../../imagedata/datastructures/Image.h"
#include "../../common/common/Point.h"

namespace stira {
namespace imagetools {

/** \brief Geometric parametric transformation of an image */
class GeometricTransform{

public:
   /** \brief constructor */
   GeometricTransform( );

   /** \brief destructor */
   ~GeometricTransform( );
   
   /** \brief generates new forward transfored image 
     * \param pImageIn input image to transform*/
   Image* Apply( Image* pImageIn );
   
   /** \brief generates new inverse transfored image 
     * \param pImageIn input imae to transform*/
   Image* ApplyInverse( Image* pImageIn );
   
   /** \brief sets the interpolatortype to 'type'
     * \param type the interpolator type*/
   void SetInterpolatorType( InterpolatorType type );
   
   /** \brief gets the interpolatortype*/
   InterpolatorType GetInterpolatorType( );
   
   /** \brief computes coordinates of point after applying forward transform
     * \param x x coordinate of point to transform
     * \param y y coordinate of point to transform*/
   virtual common::Point<double> GetTransformedPoint( double  x, double y ) = 0;
   
   /** \brief computes coordinates of point after applying inverse transform
     * \param x x coordinate of point to transform
     * \param y y coordinate of point to transform*/
   virtual common::Point<double> GetInverseTransformedPoint( double x, double y ) = 0;
   
protected:
   InterpolatorType mInterpolatorType;    ///> type of interpolation to apply 
   Interpolator* mpInterpolator;    ///< interpolator object
   
};
}
}

#endif

