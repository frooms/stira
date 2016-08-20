

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

#include "ColorValue.h"
#include <cmath>
#include <iostream>
#include "../../common/common/MathUtils.h"
#define ONETHIRD  (1.0 / 3.0)

//----------------------------------------------------------

namespace stira {
namespace imagedata {

ColorValue::ColorValue()
{
   for(int i = 0; i < 3; i++)
   {
      this->c[i] = 0;
   }
   this->type = TYPE_RGB;
}

//----------------------------------------------------------

ColorValue::ColorValue(double r, double g, double b, ColorType myType)
{
   this->c[0] = r;
   this->c[1] = g;
   this->c[2] = b;

   this->type = myType;
}

//----------------------------------------------------------

void ColorValue::SetColorValue( double r, double g, double b, ColorType myType )
{
   this->c[0] = r;
   this->c[1] = g;
   this->c[2] = b;

   this->type = myType;
}

//----------------------------------------------------------

double ColorValue::GetMax( )
{
   double myMax = c[0];
   if ( c[1] > myMax) {myMax = c[1];}
   if ( c[2] > myMax) {myMax = c[2];}
   return myMax;
}

//----------------------------------------------------------

double ColorValue::GetAverage( )
{
   return ( (double)( c[0] + c[1] +  c[2] ) / 3.0 );
}

//----------------------------------------------------------

double ColorValue::GetMin( )
{
   double myMin = c[0];
   if ( c[1] < myMin) {myMin = c[1];}
   if ( c[2] < myMin) {myMin = c[2];}
   return myMin;
}

//----------------------------------------------------------

ColorValue& ColorValue::operator=( const ColorValue& r )
{
   for(int i = 0; i < 3; i++)
   {
      this->c[i] = r.c[i];
   }
   this->type = r.type;

   return *this;
}

//----------------------------------------------------------

std::ostream& operator << ( std::ostream& out, const ColorValue& cv)
{
   out.precision(4);

   out << " ( " << std::dec << cv.c[0] << "\t" << cv.c[1] << "\t" << cv.c[2] << " ) ";

   /*out << "(" << std::dec << cv.c[0] << ", " << cv.c[1] << ", " << cv.c[2] << ") of type ";
   switch(cv.type)
   {
      case TYPE_RGB:
      {
         out << "RGB";
         break;
      }
      case TYPE_XYZ:
      {
         out << "XYZ";
         break;
      }
      case TYPE_CMY:
      {
         out << "CMY";
         break;
      }
      case TYPE_YUV:
      {
         out << "YUV";
         break;
      }
      case TYPE_HSV:
      {
         out << "HSV";
         break;
      }
      case TYPE_HSI:
      {
         out << "HSI";
         break;
      }
      case TYPE_LUV:
      {
         out << "Luv";
         break;
      }
      case TYPE_LAB:
      {
         out << "Lab";
         break;
      }
      case TYPE_UNKNOWN:
      default:
      {
         out << "unknown";
         break;
      }
   }*/
   return out;
}

//----------------------------------------------------------

bool operator== (ColorValue leftval, ColorValue rightval)
{
   if (    ( fabs( leftval.c[0] - rightval.c[0] ) < 0.01)
        && ( fabs( leftval.c[1] - rightval.c[1] ) < 0.01)
        && ( fabs( leftval.c[2] - rightval.c[2] ) < 0.01)
        && ( leftval.type == rightval.type )
      )
   {
      return true;
   }
   else
   {
      return false;
   }
}

//----------------------------------------------------------

bool operator!= (ColorValue leftval, ColorValue rightval)
{
   if (    ( fabs( leftval.c[0] - rightval.c[0] ) > 0.01)
        || ( fabs( leftval.c[1] - rightval.c[1] ) > 0.01)
        || ( fabs( leftval.c[2] - rightval.c[2] ) > 0.01)
        || ( leftval.type != rightval.type )
      )
   {
      return true;
   }
   else
   {
      return false;
   }
}

//----------------------------------------------------------

ColorValue  operator+ (ColorValue leftval, ColorValue rightval)
{
   return ColorValue( (leftval.c[0] + rightval.c[0] ), (leftval.c[1] + rightval.c[1] ), (leftval.c[2] + rightval.c[2] ), leftval.type );
}

//----------------------------------------------------------

ColorValue  operator- (ColorValue leftval, ColorValue rightval)
{
   return ColorValue( (leftval.c[0] - rightval.c[0] ), (leftval.c[1] - rightval.c[1] ), (leftval.c[2] - rightval.c[2] ), leftval.type );
}

//----------------------------------------------------------

ColorValue  operator* (ColorValue leftval, ColorValue rightval)
{
   return ColorValue( (leftval.c[0] * rightval.c[0] ), (leftval.c[1] * rightval.c[1] ), (leftval.c[2] * rightval.c[2] ), leftval.type );
}

//----------------------------------------------------------

ColorValue  operator/ (ColorValue leftval, ColorValue rightval)
{
   return ColorValue( (leftval.c[0] / rightval.c[0] ), (leftval.c[1] / rightval.c[1] ), (leftval.c[2] / rightval.c[2] ), leftval.type );
}

//----------------------------------------------------------

ColorValue  operator+ (ColorValue leftval, double value )
{
   return ColorValue( (leftval.c[0] + value ), (leftval.c[1] + value ), (leftval.c[2] + value ), leftval.type );
}

//----------------------------------------------------------

ColorValue  operator- (ColorValue leftval, double value )
{
   return ColorValue( (leftval.c[0] - value ), (leftval.c[1] - value ), (leftval.c[2] - value ), leftval.type );
}

//----------------------------------------------------------

ColorValue  operator* (ColorValue leftval, double value )
{
   return ColorValue( (leftval.c[0] * value ), (leftval.c[1] * value ), (leftval.c[2] * value ), leftval.type );
}

//----------------------------------------------------------

ColorValue  operator/ (ColorValue leftval, double value )
{
   return ColorValue( (leftval.c[0] / value ), (leftval.c[1] / value ), (leftval.c[2] / value ), leftval.type );
}

//----------------------------------------------------------

}
}
