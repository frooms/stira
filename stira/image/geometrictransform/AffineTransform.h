
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

#ifndef STIRA_IMAGE_GEOMETRICTRANSFORM_AFFINETRANSFORM_H
#define STIRA_IMAGE_GEOMETRICTRANSFORM_AFFINETRANSFORM_H

#include "GeometricTransform.h"

namespace stira {
namespace image {

/** \brief class to apply affine transform to an image 
  * x' = a11 * x + a12 * y + dx 
  * y' = a21 * x + a22 * y + dy */
class AffineTransform : public GeometricTransform
{
public:

   /** \brief constructor */
   AffineTransform( );

   /** \brief destructor */
   ~AffineTransform( );
   
   /** \brief sets the a11 parameter of the affine transform 
     * \param a11 the new value for the a11 parameter*/
   void SetA11( double a11 );
   
   /** \brief gets the a_11 parameter of the affine transform */
   double GetA11( );
   
   /** \brief sets the a_12 parameter of the affine transform 
     * \param a12 the new value for the a11 parameter*/
   void SetA12( double a12 );
   
   /** \brief gets the a_12 parameter of the affine transform */
   double GetA12( );
   
   /** \brief sets the a21 parameter of the affine transform 
     * \param a21 the new value for the a11 parameter*/
   void SetA21( double a21 );
   
   /** \brief gets the a_21 parameter of the affine transform */
   double GetA21( );
   
   /** \brief sets the a22 parameter of the affine transform 
     * \param a22 the new value for the a11 parameter*/
   void SetA22( double a22 );
   
   /** \brief gets the a_22 parameter of the affine transform */
   double GetA22( );
   
   /** \brief sets the parameter of the translation in the x direction (dx)
     * \param dx the new value for the dx parameter*/
   void SetDeltaX( double dx );
   
   /** \brief gets the parameter of the translation in the x direction */
   double GetDeltaX( );
   
   /** \brief sets the parameter of the translation in the y direction (dy)
     * \param dy the new value for the dy parameter*/
   void SetDeltaY( double dy );
   
   /** \brief gets the parameter of the translation in the y direction */
   double GetDeltaY( );
   
   /** \brief gets the determinant of the affine transform matrix */
   double GetDeterminant( );

   /** \brief computes coordinates of point after applying forward transform
     * \param x x coordinate of point to transform
     * \param y y coordinate of point to transform*/
   virtual common::Point<double> GetTransformedPoint( double  x, double y );
   
   /** \brief computes coordinates of point after applying inverse transform
     * \param x x coordinate of point to transform
     * \param y y coordinate of point to transform*/
   virtual common::Point<double> GetInverseTransformedPoint( double x, double y );

private:

   /** \brief computes the determinant of the affine transform matrix */
   void ComputeDeterminant( );
   
   double mA11;  ///< the a11 parameter of the affine transform matrix
   double mA12;  ///< the a12 parameter of the affine transform matrix
   double mA21;  ///< the a21 parameter of the affine transform matrix
   double mA22;  ///< the a22 parameter of the affine transform matrix
   
   double mDeltaX;  ///< the translation distance to translate in the x direction
   double mDeltaY;  ///< the translation distance to translate in the x direction
   
   double mDeterminant;  ///< the determinant of the matrix of the affine transform
};
}
}

#endif

