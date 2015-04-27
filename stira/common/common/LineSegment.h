
/***************************************************************************************
 *   Copyright (C) 2010 by Filip Rooms                                                 *
 *                                                                                     *
 *  Terms and conditions for using this software in any form are provided in the       *
 *  file COPYING, which can be found in the root directory of this project.            *
 *                                                                                     *
 *   Contact data: filip.rooms@gmail.com                                               *
 *                 http://www.filiprooms.be/                                           *
 *                                                                                     *
 ***************************************************************************************/

#ifndef STIRA_COMMON_LINESEGMENT_H
#define STIRA_COMMON_LINESEGMENT_H

#include <cmath>
#include <iostream>
#include "Point.h"

namespace stira {
namespace common {

/** \brief A class to represent a 2D line segment by a point couple. */
template <class T>
class LineSegment
{
public:

   /** \brief Constructor.*/
   LineSegment( Point<T> point1,  Point<T> point2 );

   /** \brief destructor.*/
   ~LineSegment();

   /** \brief gets point 1 */
   Point<T> GetPoint1();

   /** \brief sets point 1 to p */
   void SetPoint1( Point<T> p );

   /** \brief gets point 2 */
   Point<T> GetPoint2();

   /** \brief sets point 2 to p */
   void SetPoint2( Point<T> p );

   /** \brief gets the length of this line segment */
   double GetLength();

   /** \brief gets distance of point p to the line
     * \param p point to get distance of
     * \param isSegment flag if we compute the distance to the line defined by the points, or just the line segment between the points
     *   if isSegment is true, we compute the distance of the point to the nearest point of the line segment (which is limited by the two points)
     *                   false we compute the distance to the (infinitely long) line that is defined by the two points.
    */
   double GetDistanceToLine( Point<T> p, bool isSegment=false );

private:
   Point<T> mPoint1;  ///< first end point
   Point<T> mPoint2;  ///< second end point

};

//==================================================================

template <class T>
LineSegment<T>::LineSegment( Point<T> point1,  Point<T> point2 )
{
   mPoint1 = point1;
   mPoint2 = point2;
}

//------------------------------------------------------------------

template <class T>
LineSegment<T>::~LineSegment()
{
}

//------------------------------------------------------------------

template <class T>
Point<T> LineSegment<T>::GetPoint1()
{
   return mPoint1;
}

//------------------------------------------------------------------

template <class T>
void LineSegment<T>::SetPoint1( Point<T> p )
{
   mPoint1 = p;
}

//------------------------------------------------------------------

template <class T>
Point<T> LineSegment<T>::GetPoint2()
{
   return mPoint2;
}

//------------------------------------------------------------------

template <class T>
void LineSegment<T>::SetPoint2( Point<T> p )
{
   mPoint2 = p;
}

//------------------------------------------------------------------

template <class T>
double LineSegment<T>::GetLength()
{
   return mPoint1.GetDistance( mPoint2 );
}

//------------------------------------------------------------------

template <class T>
double LineSegment<T>::GetDistanceToLine( Point<T> p, bool isSegment )
{
   if( isSegment )
   {
       T dot1 = ( p - mPoint2 ) * ( mPoint2 - mPoint1 );
       if( dot1 > 0)
       {
          return sqrt( ( mPoint2 - p ) * ( mPoint2 - p ) );
       }

       T dot2 = ( p - mPoint1 ) * ( mPoint1 - mPoint2 );
       if( dot2 > 0)
       {
          return sqrt( ( mPoint1 - p ) * ( mPoint1 - p ) );
       }
   }
   return fabs( ( ( mPoint2 - mPoint1 ) ^ ( p - mPoint1 ) ) / sqrt( ( mPoint2 - mPoint1 ) * ( mPoint2 - mPoint1 ) ) );
}

}
}
#endif // LINESEGMENT_H
