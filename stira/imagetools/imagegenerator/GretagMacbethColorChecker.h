
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

#ifndef STIRA_IMAGE_COLOR_GRETAGMACBETHCOLORCHECKER_H
#define STIRA_IMAGE_COLOR_GRETAGMACBETHCOLORCHECKER_H

#include <stdint.h>
#include <iostream>
#include <vector>
#include <cmath>

#include "../../imagedata/datastructures/Image.h"
#include "../../imagedata/color/ColorValue.h"

namespace stira {
namespace imagetools {

using namespace imagedata;

/** \brief GretagMacbeth Color Checker Numeric Values 
  * http://www.brucelindbloom.com/ColorCheckerCalculator.html
  * Values for "D65" Reference illuminant (default is now "C"!!!), standard observer 2 degrees */

const ColorValue ColorCheckerDarkSkin      = ColorValue( 37.257016,  12.726583,   14.868860,  TYPE_LAB );
const ColorValue ColorCheckerLightSkin     = ColorValue( 65.958746,  13.499786,   17.224390,  TYPE_LAB );
const ColorValue ColorCheckerBlueSky       = ColorValue( 50.585267,  -1.608605,  -21.262644,  TYPE_LAB );
const ColorValue ColorCheckerFoliage       = ColorValue( 43.187513, -16.070296,   21.969862,  TYPE_LAB );
const ColorValue ColorCheckerBlueFlower    = ColorValue( 55.662298,  11.181362,  -25.010428,  TYPE_LAB );
const ColorValue ColorCheckerBluishGreen   = ColorValue( 71.231516, -31.860875,    1.507367,  TYPE_LAB );
const ColorValue ColorCheckerOrange        = ColorValue( 60.536299,  31.336008,   58.354847,  TYPE_LAB );
const ColorValue ColorCheckerPurpilishBlue = ColorValue( 40.523041,  15.476893,  -42.459360,  TYPE_LAB );
const ColorValue ColorCheckerModerateRed   = ColorValue( 50.358436,  45.358851,   14.448100,  TYPE_LAB );
const ColorValue ColorCheckerPurple        = ColorValue( 30.572438,  23.466944,  -22.322275,  TYPE_LAB );
const ColorValue ColorCheckerYellowGreen   = ColorValue( 71.979705, -26.868719,   58.582380,  TYPE_LAB );
const ColorValue ColorCheckerOrangeYellow  = ColorValue( 71.788905,  14.993000,   67.061189,  TYPE_LAB );
const ColorValue ColorCheckerBlue          = ColorValue( 29.593817,  26.860116,  -52.662832,  TYPE_LAB );
const ColorValue ColorCheckerGreen         = ColorValue( 55.522906, -41.058573,   34.944168,  TYPE_LAB );
const ColorValue ColorCheckerRed           = ColorValue( 40.366198,  53.354489,   26.117702,  TYPE_LAB );
const ColorValue ColorCheckerYellow        = ColorValue( 81.700048,  -1.289440,   79.417086,  TYPE_LAB );
const ColorValue ColorCheckerMagenta       = ColorValue( 50.394438,  49.649733,  -15.676535,  TYPE_LAB );
const ColorValue ColorCheckerCyan          = ColorValue( 51.084380, -23.767317,  -26.239253,  TYPE_LAB );
const ColorValue ColorCheckerWhite         = ColorValue( 95.369861,  -0.694237,    2.624089,  TYPE_LAB );
const ColorValue ColorCheckerNeutral80     = ColorValue( 80.983772,  -0.074234,    0.305438,  TYPE_LAB );
const ColorValue ColorCheckerNeutral65     = ColorValue( 66.245949,  -0.138206,    0.085954,  TYPE_LAB );
const ColorValue ColorCheckerNeutral50     = ColorValue( 51.244054,  -0.076186,    0.687046,  TYPE_LAB );
const ColorValue ColorCheckerNeutral35     = ColorValue( 35.379419,  -0.141659,   -0.124626,  TYPE_LAB );
const ColorValue ColorCheckerBlack         = ColorValue( 20.522060,   0.335571,   -0.187863,  TYPE_LAB );

/** \brief A class for generating the Gretag - Macbeth Color Checker chart
  * References: http://www.rags-int-inc.com/PhotoTechStuff/MacbethTarget/
  *             http://www.brucelindbloom.com/index.html?ColorCheckerRGB.html
  */
class GretagMacbethColorChecker
{
public:

   /** \brief constructor */
   GretagMacbethColorChecker( );
   
   /** \brief destructor */
   ~GretagMacbethColorChecker();
   
   /** \brief Puts the GretagMacbeth Color Checker Numeric Values in an STL vector for easier drawing*/
   static std::vector<ColorValue> GenerateVector();
   
   /** \brief main method to generate the Gretag Macbeth Color Checker
     * \param borderWidth width of border between color patches
     * \param squareSize size of patch side*/
   static Image* Generate( int borderWidth, int squareSize );
   
private:

   /** \brief Paints a square with upper left corner (offsetX, offsetY) and side squareSize in color cv
     * \param pColorChecker the image in which to paint the square
     * \param offsetX offset in x of the top left corner of the square wrt the top left corner of the image
     * \param offsetY offset in y of the top left corner of the square wrt the top left corner of the image
     * \param squareSize size of one side of the square to draw
     * \param cv the color to fill the square with*/
   static void DrawSquare( Image* pColorChecker, int offsetX, int offsetY, int squareSize, ColorValue cv );
};

}
}

#endif
