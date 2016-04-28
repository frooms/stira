
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

#ifndef STIRA_IMAGE_COLOR_COLORVALUE_H
#define STIRA_IMAGE_COLOR_COLORVALUE_H

#include <stdint.h>
#include <iostream>
#include <vector>
#include <cmath>

namespace stira {
namespace image {

// COLOR DATA STRUCTURE
/////////////////////////

/** \brief identifier of color space representation*/
enum ColorType { TYPE_RGB, TYPE_XYZ, TYPE_CMY, TYPE_YUV, TYPE_HSV, TYPE_LAB, TYPE_LUV, TYPE_HSI, TYPE_HSL, TYPE_UNKNOWN };

/** \brief struct that represents the color value triplet and an identifier*/
class ColorValue
{
public:
   /** \brief empty constructor
     * All values are initialized to 0; type is set to RGB */
   ColorValue();

   /** \brief constructor
     * \param r first color component
     * \param g second color component
     * \param b third color component
     * \param myType type of color (colorspace); default is RGB */
   ColorValue(double r, double g, double b, ColorType myType=TYPE_RGB);

   /** \brief empty constructor
     * All values are initialized to 0; type is set to RGB */
   void SetColorValue( double r, double g, double b, ColorType myType );

   double c[3]; ///< array containing three color components

   ColorType type; ///< specifier which color space is used

   /** \brief assignment operator
     * \param r color to assign to this color */
   ColorValue& operator=( const ColorValue& r );

   /** \brief gets the largest of the three color components*/
   double GetMax( );

   /** \brief gets the average of the three color components*/
   double GetAverage( );

   /** \brief gets the smallest of the three color components*/
   double GetMin( );
};

//==================================================================================

// OVERLOADED OPERATORS FOR COLOR OBJECT
//////////////////////////////////////////

/** \brief overloaded operator to insert ColorValue in a stream*/
std::ostream& operator<<( std::ostream& out, const ColorValue& cv);

/** \brief overloaded operator to compare two ColorValue structs*/
bool operator== (ColorValue leftval, ColorValue rightval);

/** \brief overloaded operator to compare two ColorValue structs*/
bool operator!= (ColorValue leftval, ColorValue rightval);

/** \brief overloaded operator to add two ColorValue structs*/
ColorValue  operator+ (ColorValue leftval, ColorValue rightval);

/** \brief overloaded operator to subtract two ColorValue structs*/
ColorValue  operator- (ColorValue leftval, ColorValue rightval);

/** \brief overloaded operator to multiply two ColorValue structs component by component*/
ColorValue  operator* (ColorValue leftval, ColorValue rightval);

/** \brief overloaded operator to divide two ColorValue structs component by component*/
ColorValue  operator/ (ColorValue leftval, ColorValue rightval);

/** \brief overloaded operator to add a constant to all components of a ColorValue struct*/
ColorValue  operator+ (ColorValue leftval, double value );

/** \brief overloaded operator to subtract a constant from all components of a ColorValue struct*/
ColorValue  operator- (ColorValue leftval, double value );

/** \brief overloaded operator to multiply all components of a ColorValue struct with a constant*/
ColorValue  operator* (ColorValue leftval, double value );

/** \brief overloaded operator to divide all components of a ColorValue struct by a constant*/
ColorValue  operator/ (ColorValue leftval, double value );

}
}

#endif
