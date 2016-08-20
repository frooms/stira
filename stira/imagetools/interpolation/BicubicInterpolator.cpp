
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

#include "BicubicInterpolator.h"
#include "../../common/common/StiraMacros.h"

namespace stira {
namespace imagetools {

BicubicInterpolator::BicubicInterpolator()
{
}

//----------------------------------------------------------

BicubicInterpolator::~BicubicInterpolator()
{
}

//----------------------------------------------------------

double BicubicInterpolator::Run( ArrayGrid<double>* pGrid, double x, double y )
{
   double p[4][4];
   double x1 = floor( x );
   double x2 =  ceil( x );
   double y1 = floor( y );
   double y2 =  ceil( y );

   if (    ( x1-1 >= 0 ) && ( x1+1 < pGrid->GetWidth() )
        && ( y1-1 >= 0 ) && ( y1+1 < pGrid->GetHeight() ) )
   {
       p[0][0] = pGrid->GetValue(x1-1,y1-1);
       p[0][1] = pGrid->GetValue(x1-1,y1);
       p[0][2] = pGrid->GetValue(x1-1,y2);
       p[0][3] = pGrid->GetValue(x1-1,y2+1);

       p[1][0] = pGrid->GetValue(x1,y1-1);
       p[1][1] = pGrid->GetValue(x1,y1);
       p[1][2] = pGrid->GetValue(x1,y2);
       p[1][3] = pGrid->GetValue(x1,y2+1);

       p[2][0] = pGrid->GetValue(x2,y1-1);
       p[2][1] = pGrid->GetValue(x2,y1);
       p[2][2] = pGrid->GetValue(x2,y2);
       p[2][3] = pGrid->GetValue(x2,y2+1);

       p[3][0] = pGrid->GetValue(x2+1,y1-1);
       p[3][1] = pGrid->GetValue(x2+1,y1);
       p[3][2] = pGrid->GetValue(x2+1,y2);
       p[3][3] = pGrid->GetValue(x2+1,y2+1);

       return bicubicInterpolate ( p, x-x1, y-y1);
   }
   else
   {
       return 0.0;
   }
}


double BicubicInterpolator::cubicInterpolate (double p[4], double x)
{
    return p[1] + 0.5 * x*(p[2] - p[0] + x*(2.0*p[0] - 5.0*p[1] + 4.0*p[2] - p[3] + x*(3.0*(p[1] - p[2]) + p[3] - p[0])));
}

double BicubicInterpolator::bicubicInterpolate (double p[4][4], double x, double y)
{
    double arr[4];
    arr[0] = cubicInterpolate(p[0], y);
    arr[1] = cubicInterpolate(p[1], y);
    arr[2] = cubicInterpolate(p[2], y);
    arr[3] = cubicInterpolate(p[3], y);
    return cubicInterpolate(arr, x);
}

}
}
