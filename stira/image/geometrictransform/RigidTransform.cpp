
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
#include "RigidTransform.h"

namespace stira {
namespace image {

using namespace common;
using namespace std;

//===================================================================================================

RigidTransform::RigidTransform( )
{
   mTheta = 0.0;

   mDeltaX = 0.0;
   mDeltaY = 0.0;
}

//===================================================================================================

RigidTransform::~RigidTransform( )
{
}

//===================================================================================================

void RigidTransform::SetTheta( double theta )
{
   mTheta = theta;
}

//===================================================================================================

void RigidTransform::SetDeltaX( double dx )
{
   mDeltaX = dx;
}

//===================================================================================================

void RigidTransform::SetDeltaY( double dy )
{
   mDeltaY = dy;
}

//===================================================================================================

Point<double> RigidTransform::GetTransformedPoint( double x, double y )
{
   return Point<double>( cos( mTheta ) * x - sin( mTheta ) * y + mDeltaX,
                         sin( mTheta ) * x + cos( mTheta ) * y + mDeltaY );
}

//===================================================================================================

Point<double> RigidTransform::GetInverseTransformedPoint( double x, double y )
{
   double x1 = x - mDeltaX;
   double y1 = y - mDeltaY;
   return Point<double>( cos( mTheta ) * x1 + sin( mTheta ) * y1, -sin( mTheta ) * x1 + cos( mTheta ) * y1 );
}

//===================================================================================================

Image* RigidTransform::RotateAroundCenter( Image* pImageIn, double theta )
{
   int nrbands = pImageIn->GetNumberOfBands();

   Image* pImageOut = new Image( pImageIn->GetWidth(), pImageIn->GetHeight() );

   for(int bandID = 0; bandID < nrbands; bandID++)
   {
      ArrayGrid< double >* pGridIn = pImageIn->GetBands()[bandID];

      ArrayGrid<double>* pTransformedGrid = RotateAroundCenter( pGridIn, theta );
      pImageOut->AddBand( pTransformedGrid );
   }

   return pImageOut;
}

//===================================================================================================

ArrayGrid<double>* RigidTransform::RotateAroundCenter( ArrayGrid<double>* pGridIn, double theta )
{
   int width  = pGridIn->GetWidth();
   int height = pGridIn->GetHeight();

   double w2 = (double)(width)  / 2.0;
   double h2 = (double)(height) / 2.0;

   mTheta = theta;

   mDeltaX = 0.0;
   mDeltaY = 0.0;

   ArrayGrid<double>* pGridOut = new ArrayGrid<double>( width, height );

   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         common::Point<double> myPoint = GetTransformedPoint( (double)x - w2, (double)y - h2 );
         pGridOut->SetValue( x, y, mpInterpolator->Run( pGridIn, myPoint.x + w2, myPoint.y + h2 ) );
      }
   }

   return pGridOut;
}

//===================================================================================================

}
}
