
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
 
#include <iostream>
#include <cstdlib>
#include <cassert>
#include "../tools/ImageIO.h"
#include "../../imagedata/color/ColorValue.h"
#include "../tools/NumberGridTools.h"
#include "../imagegenerator/GridGenerator.h"

using namespace std;
using namespace stira::image;

//--------------------------------------------------------------------

/** \brief tests the brackets operator for a grid
  * the bracket operator allows us direct access to the value at a given point like grid(x, y) */
bool GridTestBracketsOperator();

/** \brief test for simple grid rotations over angles that are multiples of 90 degrees */
bool GridRotateTest();

/** \brief test to find minimum and maximum of a grid
  * This test is repeated before and after some grid operations like adding a constant to all grid values, 
  * multiplying the grid with a constant... */
bool MinMaxTest();

/** \brief main function */
int main( /*int argc, char *argv[]*/ );
