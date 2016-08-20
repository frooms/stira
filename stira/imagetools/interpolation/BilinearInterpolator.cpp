
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

#include "BilinearInterpolator.h"
#include "../../common/common/StiraMacros.h"

namespace stira {
namespace imagetools {

BilinearInterpolator::BilinearInterpolator()
{
}

//----------------------------------------------------------

BilinearInterpolator::~BilinearInterpolator()
{
}

//----------------------------------------------------------

double BilinearInterpolator::Run( ArrayGrid<double>* pGrid, double x, double y )
{
   double x1 = floor( x );
   double x2 =  ceil( x );
   double y1 = floor( y );
   double y2 =  ceil( y );

   if ( ( x1 >= 0 ) && ( x2 < pGrid->GetWidth() ) && ( y1 >= 0 ) && ( y2 < pGrid->GetHeight() ) )
   {
      double I11 = pGrid->GetValue( x1, y1 );
      double I12 = pGrid->GetValue( x1, y2 );
      double I21 = pGrid->GetValue( x2, y1 );
      double I22 = pGrid->GetValue( x2, y2 );

      return Run( x1, x2, y1, y2, I11, I12, I21, I22, x, y );
   }
   else
   {
      return 0.0;
   }
}

//----------------------------------------------------------

double BilinearInterpolator::Run( double x1, double x2, double y1, double y2, double I11, double I12 , double I21, double I22, double x, double y )
{
   if (fabs(x1-x2) < STIRA_EPSILON)
   {
      if (fabs(y1-y2) < STIRA_EPSILON)
      {
         return I11;
      }
      else
      {
         double value = ( ( ( y2 - y ) * I11 + ( y - y1 ) * I12 ) / (y2 - y1) );
         return value;
      }
   }
   else
   {
      if (fabs(y1-y2) < STIRA_EPSILON)
      {
         double value = ( ( ( x2 - x ) * I11 + ( x - x1 ) * I21 ) / (x2 - x1) );
         return value;
      }
      else
      {
         double value = (   (     I11 * (x2 - x) * (y2 - y)
                                + I21 * (x - x1) * (y2 - y)
                                + I12 * (x2 - x) * (y - y1)
                                + I22 * (x - x1) * (y - y1)
                            )
                            / ( (x2 - x1) * (y2 - y1) )
                         );
         return value;
      }
   }
}

//----------------------------------------------------------

}
}
