
/***********************************************************************************
 *   Copyright (C) 2008 by Filip Rooms                                             *
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

#include "../../imagedata/datastructures/Image.h"
#include "../fouriertools/FFT.h"
namespace stira {

bool HighPassTest( image::ArrayGrid<double>* pSourceGrid );

bool LowPassTest( image::ArrayGrid<double>* pSourceGrid );

bool ApplySetOfTransferFunctionsTest( image::ArrayGrid<double>* pSourceGrid );

bool ForwardInverseTest(image::ArrayGrid<double>* pSourceGrid);

void FFTtest(image::Image* pSourceImage);

int main();

}
