
/***************************************************************************************
 *   Copyright (C) 2008 by Filip Rooms                                                 *
 *                                                                                     *
 *  Terms and conditions for using this software in any form are provided in the       *
 *  file COPYING, which can be found in the root directory of this project.            *
 *                                                                                     *
 *   Contact data: filip.rooms@gmail.com                                               *
 *                 http://www.filiprooms.be/                                           *
 *                                                                                     *
 ***************************************************************************************/

#ifndef STIRA_COMMON_DEFINITIONS_H
#define STIRA_COMMON_DEFINITIONS_H

#include <string>

// in /usr/lib/gcc/x86_64-linux-gnu/4.2/include/float.h
#include <cfloat>

// defines DBL_EPSILON: difference between 1 and  least value > 1 representable in "double"

namespace stira {
namespace common {

enum NumberMode {MODE_REAL, MODE_IMAG, MODE_COMPLEX, MODE_MEAN, MODE_UNKNOWN};

enum MatchCriterion {MATCH_SSD, MATCH_NCC, MATCH_MI, MATCH_UNKNOWN};

enum DirectionMode { APPLY_FORWARD, APPLY_BACKWARD };
/** \brief A class to hold spectral bands of an image  */
class Definitions{
public:

   /** \brief Constructor.*/
   Definitions();

   /** \brief Destructor. */
   ~Definitions();

};
}
}
#endif
