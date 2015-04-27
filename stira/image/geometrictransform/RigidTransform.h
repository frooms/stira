
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

#ifndef STIRA_IMAGE_GEOMETRICTRANSFORM_RIGIDTRANSFORM_H
#define STIRA_IMAGE_GEOMETRICTRANSFORM_RIGIDTRANSFORM_H

#include "GeometricTransform.h"

namespace stira {
namespace image {

/** \brief class to apply rigid transform to an image
  * x' = cos(t) * x - sin(t) * y + dx
  * y' = sin(t) * x + cos(t) * y + dy */
class RigidTransform : public GeometricTransform
{
public:

   /** \brief constructor */
   RigidTransform( );

   /** \brief destructor */
   ~RigidTransform( );

   /** \brief sets the rotation angle
     * \param theta the rotation angle*/
   void SetTheta( double theta );

   /** \brief sets the dx parameter of the affine transform
     * \param dx the new value for the dx parameter*/
   void SetDeltaX( double dx );

   /** \brief sets the dy parameter of the affine transform
     * \param dy the new value for the dy parameter*/
   void SetDeltaY( double dy );

   /** \brief Generates new image by rotating pImageIn around its center over an angle theta
     * \param pImageIn input image to rotate
     * \param theta angle over which to rotate the image */
   Image* RotateAroundCenter( Image* pImageIn, double theta );

   /** \brief Generates new grid by rotating pGridIn around its center over an angle theta
     * \param pGridIn input grid to rotate
     * \param theta angle over which to rotate the grid */
   ArrayGrid<double>* RotateAroundCenter( ArrayGrid<double>* pGridIn, double theta );

private:

   /** \brief computes coordinates of point after applying forward transform
     * \param x x coordinate of point to transform
     * \param y y coordinate of point to transform*/
   virtual common::Point<double> GetTransformedPoint( double  x, double y );

   /** \brief computes coordinates of point after applying inverse transform
     * \param x x coordinate of point to transform
     * \param y y coordinate of point to transform*/
   virtual common::Point<double> GetInverseTransformedPoint( double x, double y );

   double mTheta;  ///< the rotation angle

   double mDeltaX;  ///< the dx parameter, i.e., the distance to translate in x direction
   double mDeltaY;  ///< the dy parameter, i.e., the distance to translate in y direction

   double mDeterminant;  ///< the determinant of the matrix of the affine transform
};
}
}

#endif

