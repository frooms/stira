#ifndef STIRA_FILTER_COLORLOOKUPTABLE_H
#define STIRA_FILTER_COLORLOOKUPTABLE_H

/***********************************************************************************
 *   Copyright (C) 2012 by Filip Rooms                                             *
 *                                                                                 *
 *  Terms and conditions for using this software in any form are provided in the   *
 *  file COPYING, which can be found in the root directory of this project.        *
 *                                                                                 *
 *   Contact data: filip.rooms@gmail.com                                           *
 *                 http://www.filiprooms.be/                                       *
 *                                                                                 *
 ***********************************************************************************/

#include "../../imagedata/datastructures/Image.h"
#include "../../imagetools/interpolation/BilinearInterpolator.h"

namespace stira{
namespace filter{

/** \brief colour lookup table to assign colours to the 4096 labels occuring in LBP's with a 12 point neighborhood */
class ColorLookupTable
{
public:
   ColorLookupTable();
   double mLUT_R_last[4096][3];
};

}
}

#endif // COLORLOOKUPTABLE_H
