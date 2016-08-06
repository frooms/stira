
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

#include "AffineTransform.h"

namespace stira {
namespace image {

using namespace common;
using namespace std;

//===================================================================================================

AffineTransform::AffineTransform( ) : GeometricTransform()
{
   mA11 = 1.0;
   mA12 = 0.0;
   mA21 = 0.0;
   mA22 = 1.0;
   
   mDeltaX = 0.0;
   mDeltaY = 0.0;
   ComputeDeterminant( );
}

//===================================================================================================

AffineTransform::~AffineTransform( )
{
}

//===================================================================================================

void AffineTransform::SetA11( double a11 )
{
   mA11 = a11;
   ComputeDeterminant( );
}

//===================================================================================================

void AffineTransform::ComputeDeterminant( )
{
   mDeterminant = mA11 * mA22 - mA12 * mA21;
}

//===================================================================================================

double AffineTransform::GetDeterminant( )
{
   ComputeDeterminant( );
   return mDeterminant;
}

//===================================================================================================

double AffineTransform::GetA11( )
{
   return mA11;
}

//===================================================================================================

void AffineTransform::SetA12( double a12 )
{
   mA12 = a12;
   ComputeDeterminant( );
}

//===================================================================================================

double AffineTransform::GetA12( )
{
   return mA12;
}

//===================================================================================================

void AffineTransform::SetA21( double a21 )
{
   mA21 = a21;
   ComputeDeterminant( );
}

//===================================================================================================

double AffineTransform::GetA21( )
{
   return mA21;
}

//===================================================================================================

void AffineTransform::SetA22( double a22 )
{
   mA22 = a22;
   ComputeDeterminant( );
}

//===================================================================================================

double AffineTransform::GetA22( )
{
   return mA22;
}

//===================================================================================================

void AffineTransform::SetDeltaX( double dx )
{
   mDeltaX = dx;
}

//===================================================================================================

double AffineTransform::GetDeltaX( )
{
   return mDeltaX;
}

//===================================================================================================

void AffineTransform::SetDeltaY( double dy )
{
   mDeltaY = dy;
}

//===================================================================================================

double AffineTransform::GetDeltaY( )
{
   return mDeltaY;
}

//===================================================================================================

Point<double> AffineTransform::GetTransformedPoint( double x, double y )
{
   return Point<double>( mA11 * x + mA12 * y + mDeltaX, mA21 * x + mA22 * y + mDeltaY );
}

//===================================================================================================

Point<double> AffineTransform::GetInverseTransformedPoint( double x, double y )
{
   double x1 = x - mDeltaX;
   double y1 = y - mDeltaY;
   return Point<double>( ((mA22 * x1 - mA12 * y1) / mDeterminant), ((-mA21 * x1 + mA11 * y1) / mDeterminant) );
}

//===================================================================================================

}
}
