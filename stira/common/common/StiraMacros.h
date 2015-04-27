
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

#ifndef STIRA_COMMON_STIRAMACROS_H
#define STIRA_COMMON_STIRAMACROS_H

#define STIRA_VERSION "Develop"

#define STIRA_INDEX_WIDTH 6

#define STIRA_EPSILON  0.00000000000001

#define POWER2(x)     ( (x) * (x) )

#define POWER3(x)     ( (x) * (x) * (x) )

#define POWER4(x)     ( (x) * (x) * (x) * (x) )

#define POWER5(x)     ( (x) * (x) * (x) * (x) * (x) )

#define POWER6(x)     ( (x) * (x) * (x) * (x) * (x) * (x) )

#define POWER7(x)     ( (x) * (x) * (x) * (x) * (x) * (x) * (x) )

#define MYDOUBLE(x)   ( (x) + (x) )

#define MYTRIPLE(x)   ( (x) + (x) + (x) )

#define L2NORM(x,y)   sqrt( (x) * (x) + (y) * (y) )

#define S_SWAP(x, y)    (x ^= y ^= x ^= y)

#endif
