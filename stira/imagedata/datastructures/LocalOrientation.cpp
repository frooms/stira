
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

#include "LocalOrientation.h"

namespace stira {
namespace imagedata {

LocalOrientation::LocalOrientation()
{
   mAngle     = 0.0;
   mMagnitude = 0.0;
}

LocalOrientation::~LocalOrientation()
{
}

double LocalOrientation::GetMagnitude()
{
   return mMagnitude;
}

void LocalOrientation::SetMagnitude(double myMagnitude)
{
   mMagnitude = myMagnitude;
}

double LocalOrientation::GetAngle()
{
   return mAngle;
}

void LocalOrientation::SetAngle(double myAngle)
{
   mAngle = myAngle;
}

void LocalOrientation::SetMagnitudeAndAngle( double myMagnitude, double myAngle )
{
   mAngle = myAngle;
   mMagnitude = myMagnitude;
}

}
}
