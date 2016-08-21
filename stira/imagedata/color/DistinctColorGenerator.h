
/***********************************************************************************
 *   Copyright (C) 2010 by Filip Rooms                                             *
 *                                                                                 *
 *  Terms and conditions for using this software in any form are provided in the   *
 *  file COPYING, which can be found in the root directory of this project.        *
 *                                                                                 *
 *   Contact data: filip.rooms@gmail.com                                           *
 *                 http://www.filiprooms.be/                                       *
 *                                                                                 *
 ***********************************************************************************/

#ifndef STIRA_IMAGEDATA_COLOR_DISTINCTCOLORGENERATOR_H
#define STIRA_IMAGEDATA_COLOR_DISTINCTCOLORGENERATOR_H

#include <stdint.h>
#include <iostream>
#include <vector>
#include <cmath>
#include "ColorValue.h"

namespace stira {
namespace imagedata {

/** \brief generate distinct colors for visualization
  * Based on  http://stackoverflow.com/questions/309149/generate-distinctly-different-rgb-colors-in-graphs
  * Generates (I, 0, 0), (0, I, 0), (0, 0, I), (I, I, 0), (I, 0, I), (0, I, I)
  *   with I 255, 128, 64+0x128=64, 64+1x128=192, 32+0x64=32, 32+1x64=96, 32+2x64=160, 32+3x64=224, ...*/
class DistinctColorGenerator
{
public:
    /** \brief constructor */
    DistinctColorGenerator();

    /** \brief destructor */
    ~DistinctColorGenerator();

    /** \brief generates a new color */
    ColorValue GenerateNewColor();
private:
    int mColorsGenerated;  ///< Number of colors already generated
    ColorValue* mpColorCycle;  ///< vector with six base vectors
    double mFactor; ///< factor to multiply base vectors with to obtain color
};

}
}

#endif // DISTINCTCOLORGENERATOR_H
