
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

#include "NearestNeighborInterpolator.h"
#include <cmath>
#include "../../common/common/MathUtils.h"

#define EPSILON 0.000001

namespace stira {
namespace image {

NearestNeighborInterpolator::NearestNeighborInterpolator()
{
}

//----------------------------------------------------------

NearestNeighborInterpolator::~NearestNeighborInterpolator()
{
}

//----------------------------------------------------------

double NearestNeighborInterpolator::Run( ArrayGrid<double>* pGrid, double x, double y )
{
   double x1 = floor( x );
   double x2 = ceil( x );
   double y1 = floor( y );
   double y2 = ceil( y );
   
   if (    (x1 >= 0) && (x1 < pGrid->GetWidth())  && (x2 >= 0) && (x2 < pGrid->GetWidth())
        && (y1 >= 0) && (y1 < pGrid->GetHeight()) && (y2 >= 0) && (y2 < pGrid->GetHeight())
      )
   {
      double dx1 = fabs(x - x1);
      double dx2 = fabs(x - x2);
      double dy1 = fabs(x - x1);
      double dy2 = fabs(x - x2);
      
      if (dx1 < dx2)
      {
         if (dy1 < dy2)
         {
            return pGrid->GetValue( x1, y1 );
         }
         else
         {
            return pGrid->GetValue( x1, y2 );
         }
      }
      else
      {
         if (dy1 < dy2)
         {
            return pGrid->GetValue( x2, y1 );
         }
         else
         {
            return pGrid->GetValue( x2, y2 );
         }
      }
   }
   else
   {
      return 0.0;
   }
}
//----------------------------------------------------------

}
}
