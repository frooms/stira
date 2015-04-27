
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
   Point(T x, T y, coordinateMode mode=COORDINATES_CARTESIAN, pointType myType=TYPE_DEFAULT);

   /** \brief destructor.*/
   ~Point();

   /** \brief gets x coordinate of point*/
   T GetX() const;

   /** \brief gets y coordinate of point*/
   T GetY() const;

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
     * \param x new x coordinate to set
     * \param y new y coordinate to set */
   void SetXAndY(T x, T y);

   /** \brief sets new first coordinate for point
     * \param x new first coordinate to set */
   void SetX( T x );

   /** \brief sets new second coordinate for point
     * \param y new second coordinate to set */
   void SetY( T y );

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

private:
   T mX;  ///< x coordinate of the point
   T mY; ///< y coordinate of the point
   coordinateMode mMode;  ///< keeps track if coordinate mode is cartesian or polar
   pointType mPointType;  ///< keeps track in case point is in a curve if it is the start or stop point in a curve
};

template <class T>
std::ostream& operator << ( std::ostream& output, const Point<T>& p );

//================================================================================================

template <class T>
Point<T> Point<T>::operator - ( Point<T> otherPoint )
{
   return Point<T>( ( this->mX - otherPoint.mX ), ( this->mY - otherPoint.mY ) );
}

//------------------------------------------------------------------

template <class T>
Point<T> Point<T>::operator + ( Point<T> otherPoint )
{
   return Point<T>( ( this->mX + otherPoint.mX ), ( this->mY + otherPoint.mY ) );
}

//------------------------------------------------------------------

template <class T>
T Point<T>::operator * ( Point<T> otherPoint )
{
   return ( ( this->mX * otherPoint.mX ) + ( this->mY * otherPoint.mY ) );
}

//------------------------------------------------------------------

template <class T>
T Point<T>::operator ^ ( Point<T> otherPoint )
{
   return ( ( this->mX * otherPoint.mY ) - ( this->mY * otherPoint.mX ) );
}

//------------------------------------------------------------------

template <class T>
std::ostream& operator << ( std::ostream& output, const Point<T>& p )
{
   output << " ( " <<  p.GetX() << ", " << p.GetY() << " ) ";
   return output;  // for multiple << operators.
}

//------------------------------------------------------------------

template <class T>
bool Point<T>::operator== ( Point<T> otherPoint )
{
   if (    ( (double)(fabs( (double)(this->mX) - (double)(otherPoint.mX) )) < 0.0000001)
        && ( (double)(fabs( (double)(this->mY) - (double)(otherPoint.mY) )) < 0.0000001)
        && ( this->mMode == otherPoint.mMode )
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
   mX = (T)(0);
   mY = (T)(0);
   mMode = COORDINATES_CARTESIAN;
   mPointType = TYPE_DEFAULT;
}

//------------------------------------------------------------------

template <class T>
Point<T>::Point(T x, T y, coordinateMode mode, pointType myType )
{
   mX = x;
   mY = y;
   mMode = mode;
   mPointType = myType;
}

//------------------------------------------------------------------

template <class T>
Point<T>::~Point()
{
}

//------------------------------------------------------------------

template <class T>
T Point<T>::GetX() const
{
   return mX;
}

//------------------------------------------------------------------

template <class T>
T Point<T>::GetY() const
{
   return mY;
}

//------------------------------------------------------------------

template <class T>
T Point<T>::GetRadius() const
{
   return mX;
}

//------------------------------------------------------------------

template <class T>
T Point<T>::GetTheta() const
{
   return mY;
}

//------------------------------------------------------------------

template <class T>
coordinateMode Point<T>::GetMode() const
{
   return mMode;
}

//------------------------------------------------------------------

template <class T>
pointType Point<T>::GetType() const
{
   return mPointType;
}

//------------------------------------------------------------------

template <class T>
void Point<T>::SetType( pointType type )
{
   mPointType = type;
}

//------------------------------------------------------------------

template <class T>
void Point<T>::SetXAndY(T x, T y)
{
   mX = x;
   mY = y;
   mMode = COORDINATES_CARTESIAN;
}



//------------------------------------------------------------------

template <class T>
void Point<T>::SetX( T x )
{
   mX = x;
}

//------------------------------------------------------------------

template <class T>
void Point<T>::SetY( T y )
{
   mY = y;
}

//------------------------------------------------------------------

template <class T>
void Point<T>::SetRadiusAndTheta( T radius, T theta )
{
   mX = radius;
   mY = theta;
   mMode = COORDINATES_POLAR;
}

//------------------------------------------------------------------

template <class T>
double Point<T>::GetDistance(Point other)
{
   if ( mMode == COORDINATES_CARTESIAN )
   {
      double dx = (double)(mX) - (double)(other.GetX());
      double dy = (double)(mY) - (double)(other.GetY());
      return (sqrt(dx*dx + dy*dy));
   }
   else // http://en.wikipedia.org/wiki/Radial_distance_(geometry)
   {
      double r1     = (double)(mX);
      double theta1 = (double)(mY);
      double r2     = (double)(other.GetX());
      double theta2 = (double)(other.GetY());
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
   if (mMode != COORDINATES_POLAR)
   {
      T xx = ( mX - xCenter );
      T yy = ( mY - yCenter );
      T radius = sqrt( xx * xx + yy * yy );
      T theta = atan2( yy, xx );
      mX = radius;
      mY = theta;
      mMode = COORDINATES_POLAR;
   }
}

//------------------------------------------------------------------

template <class T>
void Point<T>::ToCartesian( )
{
   if (mMode != COORDINATES_CARTESIAN)
   {
      T x = mX * cos( mY );
      T y = mX * sin( mY );
      mX = x;
      mY = y;
      mMode = COORDINATES_CARTESIAN;
   }
}

//------------------------------------------------------------------

template <class T>
void Point<T>::MirrorOrigin( )
{
   if (mMode == COORDINATES_CARTESIAN)
   {
      mX *= -1;
      mY *= -1;
   }
   else // polar
   {
      if (mY > 0)
      {
         mY -= M_PI;
      }
      else
      {
         mY += M_PI;
      }
   }
}

//------------------------------------------------------------------

template <class T>
void Point<T>::MirrorXaxis( )
{
   mY *= -1;
}

//------------------------------------------------------------------

template <class T>
void Point<T>::MirrorYaxis( )
{
   mX *= -1;
}

//------------------------------------------------------------------

}
}
#endif
