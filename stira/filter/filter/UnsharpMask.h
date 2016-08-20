
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

#ifndef STIRA_FILTER_UNSHARPMASK_H
#define STIRA_FILTER_UNSHARPMASK_H

#include <stdint.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "../../imagedata/datastructures/Image.h"

namespace stira {
namespace filter {

using namespace imagedata;

/** \brief Enhances image sharpness by unsharp masking */
class UnsharpMask
{
public:
   /** \brief constructor */
   UnsharpMask();
   
   /** \brief destructor */
   ~UnsharpMask();

   static Image* Run( Image* pImageIn, double sigma=1.0, double factor=0.5 );
};

}
}

#endif
