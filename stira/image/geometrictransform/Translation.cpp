
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

#include "Translation.h"

namespace stira {
namespace image {

using namespace common;

//===================================================================================================

Translation::Translation( )
{
   mDeltaX = 0.0;
   mDeltaY = 0.0;
}

//===================================================================================================

Translation::~Translation( )
{
}

//===================================================================================================
   
void Translation::SetDeltaX( double dx )
{
   mDeltaX = dx;
}

//===================================================================================================

void Translation::SetDeltaY( double dy )
{
   mDeltaY = dy;
}

//===================================================================================================

Point<double> Translation::GetTransformedPoint(double  x, double y )
{
   return Point<double>( x + mDeltaX, y + mDeltaY );
}

//===================================================================================================

Point<double> Translation::GetInverseTransformedPoint( double x, double y )
{
   return Point<double>( x - mDeltaX, y - mDeltaY );
}

//===================================================================================================

}
}
