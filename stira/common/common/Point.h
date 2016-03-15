
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

#ifndef STIRA_COMMON_POINT_H
#define STIRA_COMMON_POINT_H

#include <cmath>
#include <iostream>
#include <fstream>

namespace stira {
namespace common {

struct IntensityPoint
{
   int x;
   int y;
   double intensity;
};

enum coordinateMode{ COORDINATES_CARTESIAN, COORDINATES_POLAR };
enum pointType{ TYPE_START, TYPE_END, TYPE_DEFAULT };


/** \brief A class to represent a 2D point. */
template <class T>
class Point{

public:

   /** \brief Constructor.*/
   Point();

   /** \brief Constructor.*/
   Point(T xNew, T yNew, coordinateMode mode=COORDINATES_CARTESIAN, pointType myType=TYPE_DEFAULT);

   /** \brief destructor.*/
   ~Point();

   /** \brief gets radial coordinate of point, in case of polar coordinates*/
   T GetRadius() const;

   /** \brief gets angular coordinate of point, in case of polar coordinates**/
   T GetTheta() const;

   /** \brief gets radial coordinate of point, in case of polar coordinates*/
   pointType GetType() const;

   /** \brief gets angular coordinate of point, in case of polar coordinates**/
   void  SetType( pointType type );

   coordinateMode GetMode() const;

   /** \brief sets new cartesian coordinates for point
     * \param xNew new x coordinate to set
     * \param yNew new y coordinate to set */
   void SetXAndY(T xNew, T yNew);

   /** \brief sets new coordinates for point*/
   void SetRadiusAndTheta( T radius, T theta );

   /** \brief gets Euclidian distance to other point
     * \param other other point to compute distance to*/
   double GetDistance(Point other=Point<T>(0,0) );

   /** \brief transforms current point coordinates to polar coordinates*/
   void ToPolar( T xCenter=0, T yCenter=0 );

   /** \brief transforms current point coordinates to cartesian coordinates*/
   void ToCartesian( );

   /** \brief mirrors current point towards the origin */
   void MirrorOrigin( );

   /** \brief mirrors current point towards X axis */
   void MirrorXaxis( );

   /** \brief mirrors current point towards Y axis */
   void MirrorYaxis( );

   Point<double> ToDouble();
   Point<int> ToInt();

   /** \brief overloaded operator to compare two Points
     * \param otherPoint other point to check equality */
   bool operator == ( Point<T> otherPoint );

   /** \brief overloaded operator to compare two Points
     * \param otherPoint other point to check inequality */
   bool operator != ( Point<T> otherPoint );

   /** \brief overloaded operator to add two Points
     * \param otherPoint other point to add */
   Point<T> operator + ( Point<T> otherPoint );

   /** \brief overloaded operator to subtract two Points
     * \param otherPoint other point to subtract */
   Point<T> operator - ( Point<T> otherPoint );

   /** \brief overloaded operator to compute the dot product of two segments (0,0)-thisPoint and (0,0)-otherPoint
     * Source <A HREF="http://www.topcoder.com/tc?d1=tutorials&d2=geometry1&module=Static">
     *                 http://www.topcoder.com/tc?d1=tutorials&d2=geometry1&module=Static</A>
     *
     * \param otherPoint other point to compute dot product with */
   T operator * ( Point<T> otherPoint );

   /** \brief overloaded operator to compute the norm of the cross product of two segments (0,0)-thisPoint and (0,0)-otherPoint
     * Remark: this just computes the NORM; the real result of an actual cross product would be a vector perpendicular to the plane
     * Source <A HREF="http://www.topcoder.com/tc?d1=tutorials&d2=geometry1&module=Static">
     *                 http://www.topcoder.com/tc?d1=tutorials&d2=geometry1&module=Static</A>
     *
     * \param otherPoint other point to compute cross product norm with */
   T operator ^ ( Point<T> otherPoint );

   T x;  ///< x coordinate of the point
   T y; ///< y coordinate of the point

private:
   coordinateMode mode;  ///< keeps track if coordinate mode is cartesian or polar
   pointType type;  ///< keeps track in case point is in a curve if it is the start or stop point in a curve
};

template <class T>
std::ostream& operator << ( std::ostream& output, const Point<T>& p );

//================================================================================================

template <class T>
Point<T> Point<T>::operator - ( Point<T> otherPoint )
{
   return Point<T>( ( this->x - otherPoint.x ), ( this->y - otherPoint.y ) );
}

//------------------------------------------------------------------

template <class T>
Point<T> Point<T>::operator + ( Point<T> otherPoint )
{
   return Point<T>( ( this->x + otherPoint.x ), ( this->y + otherPoint.y ) );
}

//------------------------------------------------------------------

template <class T>
T Point<T>::operator * ( Point<T> otherPoint )
{
   return ( ( this->x * otherPoint.x ) + ( this->y * otherPoint.y ) );
}

template <class T>
Point<T> operator* (double a, const Point<T>& pt)
{
    return ( Point<T>( pt.x * a, pt.y * a, pt.GetMode(), pt.GetType() ) );
}

template <class T>
Point<T> operator* (const Point<T>& pt, double a)
{
    return ( Point<T>( pt.x * a, pt.y * a, pt.GetMode(), pt.GetType() ) );
}

//------------------------------------------------------------------

template <class T>
T Point<T>::operator ^ ( Point<T> otherPoint )
{
   return ( ( this->x * otherPoint.y ) - ( this->y * otherPoint.x ) );
}

//------------------------------------------------------------------

template <class T>
std::ostream& operator << ( std::ostream& output, const Point<T>& p )
{
   output << " ( " <<  p.x << ", " << p.y << " ) ";
   return output;  // for multiple << operators.
}

//------------------------------------------------------------------

template <class T>
bool Point<T>::operator== ( Point<T> otherPoint )
{
   if (    ( (double)(fabs( (double)(this->x) - (double)(otherPoint.x) )) < 0.0000001)
        && ( (double)(fabs( (double)(this->y) - (double)(otherPoint.y) )) < 0.0000001)
        && ( this->mode == otherPoint.mode )
      )
   {
      return true;
   }
   else
   {
      return false;
   }
}

//------------------------------------------------------------------

template <class T>
bool Point<T>::operator!= ( Point<T> otherPoint )
{
   return !( *this == otherPoint );
}

//------------------------------------------------------------------

template <class T>
Point<T>::Point()
{
   x = (T)(0);
   y = (T)(0);
   mode = COORDINATES_CARTESIAN;
   type = TYPE_DEFAULT;
}

//------------------------------------------------------------------

template <class T>
Point<T>::Point(T xNew, T yNew, coordinateMode mode, pointType myType )
{
   x = xNew;
   y = yNew;
   mode = mode;
   type = myType;
}

//------------------------------------------------------------------

template <class T>
Point<T>::~Point()
{
}

template <class T>
Point<double> Point<T>::ToDouble()
{
    return Point<double>( static_cast<double>(this->x), static_cast<double>(this->y), this->GetMode(), this->GetType() );
}

template <class T>
Point<int> Point<T>::ToInt()
{
    return Point<int>( static_cast<int>(this->x + 0.5), static_cast<int>(this->y + 0.5), this->GetMode(), this->GetType() );
}

//------------------------------------------------------------------

template <class T>
T Point<T>::GetRadius() const
{
   return x;
}

//------------------------------------------------------------------

template <class T>
T Point<T>::GetTheta() const
{
   return y;
}

//------------------------------------------------------------------

template <class T>
coordinateMode Point<T>::GetMode() const
{
   return mode;
}

//------------------------------------------------------------------

template <class T>
pointType Point<T>::GetType() const
{
   return type;
}

//------------------------------------------------------------------

template <class T>
void Point<T>::SetType( pointType newType )
{
   type = newType;
}

//------------------------------------------------------------------

template <class T>
void Point<T>::SetXAndY(T xNew, T yNew)
{
   x = xNew;
   y = yNew;
   mode = COORDINATES_CARTESIAN;
}

//------------------------------------------------------------------

template <class T>
void Point<T>::SetRadiusAndTheta( T radius, T theta )
{
   x = radius;
   y = theta;
   mode = COORDINATES_POLAR;
}

//------------------------------------------------------------------

template <class T>
double Point<T>::GetDistance(Point other)
{
   if ( mode == COORDINATES_CARTESIAN )
   {
      double dx = (double)(x) - (double)(other.x);
      double dy = (double)(y) - (double)(other.y);
      return (sqrt(dx*dx + dy*dy));
   }
   else // http://en.wikipedia.org/wiki/Radial_distance_(geometry)
   {
      double r1     = (double)(x);
      double theta1 = (double)(y);
      double r2     = (double)(other.x);
      double theta2 = (double)(other.y);
      double radialDistance = sqrt(   r1 * r1
                                    + r2 * r2
                                    - 2.0 * r1 * r2 * cos( theta1 - theta2 )
                                  );
      return radialDistance;
   }
}

//------------------------------------------------------------------

template <class T>
void Point<T>::ToPolar( T xCenter, T yCenter )
{
   if (mode != COORDINATES_POLAR)
   {
      T xx = ( x - xCenter );
      T yy = ( y - yCenter );
      T radius = sqrt( xx * xx + yy * yy );
      T theta = atan2( yy, xx );
      x = radius;
      y = theta;
      mode = COORDINATES_POLAR;
   }
}

//------------------------------------------------------------------

template <class T>
void Point<T>::ToCartesian( )
{
   if (mode != COORDINATES_CARTESIAN)
   {
      T xCart = x * cos( y );
      T yCart = x * sin( y );
      x = xCart;
      y = yCart;
      mode = COORDINATES_CARTESIAN;
   }
}

//------------------------------------------------------------------

template <class T>
void Point<T>::MirrorOrigin( )
{
   if (mode == COORDINATES_CARTESIAN)
   {
      x *= -1;
      y *= -1;
   }
   else // polar
   {
      if (y > 0)
      {
         y -= M_PI;
      }
      else
      {
         y += M_PI;
      }
   }
}

//------------------------------------------------------------------

template <class T>
void Point<T>::MirrorXaxis( )
{
   y *= -1;
}

//------------------------------------------------------------------

template <class T>
void Point<T>::MirrorYaxis( )
{
   x *= -1;
}

//------------------------------------------------------------------

}
}
#endif
