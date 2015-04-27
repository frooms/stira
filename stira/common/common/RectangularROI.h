
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

#ifndef STIRA_COMMON_RECTANGULARROI_H
#define STIRA_COMMON_RECTANGULARROI_H

#include <cmath>
#include <iostream>
#include "Point.h"

namespace stira {
namespace common {

/** \brief A class to represent a rectangular ROI.
  * The edges of this ROI are parallel with the x and y axes.
  * Here, we consider a closed ROI, i.e., the edge points also belong to the ROI.*/
template <class T>
class RectangularROI{

public:
   /** \brief constructor */
   RectangularROI( );

   /** \brief constructor
     * \param topLeftCorner the point that is the top left corner of the rectangle
     * \param bottomRightCorner the point that is the bottom right corner of the rectangle */
   RectangularROI( Point<T> topLeftCorner, Point<T> bottomRightCorner );

   /** \brief constructor
     * \param topLeftCorner the point that is the top left corner of the rectangle
     * \param bottomRightCorner the point that is the bottom right corner of the rectangle */
   RectangularROI( T topLeftX,  T topLeftY, T bottomRightX, T bottomRightY );

   /** \brief destructor */
   ~RectangularROI();

   /** \brief Gets the top left corner point of the rectangle */
   Point<T> GetTopLeftCorner();

   /** \brief Gets the bottom right corner point of the rectangle */
   Point<T> GetBottomRightCorner();

   /** \brief Gets the center point of the rectangle */
   Point<T> GetCenter();

   /** \brief Checks if a candidate point is inside this rectangle */
   bool IsInROI( Point<T> candidatePoint );

   /** \brief Gets the width of this rectangle */
   T GetWidth();

   /** \brief Gets the height of this rectangle */
   T GetHeight();

   T GetArea();

   T GetDiagonalLength();

private:

   /** \brief Initializes the Rectangular ROI with the top left and bottom right corner points
     * \param topLeftCorner the point that is the top left corner of the rectangle
     * \param bottomRightCorner the point that is the bottom right corner of the rectangle */
   void Initialize( Point<T> topLeftCorner, Point<T> bottomRightCorner );

   Point<T> mTopLeftCorner; ///< the top left corner point of the rectangle
   Point<T> mBottomRightCorner; ///< the bottom right corner point of the rectangle
   Point<T> mCenter;   ///< center point of the rectangle
   T mWidth;   ///< width  of this rectangle
   T mHeight;  ///< height of this rectangle
};

//==================================================================

template <class T>
RectangularROI<T>::RectangularROI( )
{
   mTopLeftCorner     = Point<int>( 0, 0 );
   mBottomRightCorner = Point<int>( 0, 0 );
   mWidth  = 0;
   mHeight = 0;
   mCenter.SetXAndY( 0, 0 );
}

//----------------------------------------------------------

template <class T>
RectangularROI<T>::RectangularROI( Point<T> topLeftCorner, Point<T> bottomRightCorner )
{
   Initialize( topLeftCorner, bottomRightCorner );
}

//----------------------------------------------------------

template <class T>
RectangularROI<T>::RectangularROI( T topLeftX,  T topLeftY, T bottomRightX, T bottomRightY )
{
    Point<T> topLeftCorner( topLeftX, topLeftY);
    Point<T> bottomRightCorner( bottomRightX, bottomRightY );
    Initialize( topLeftCorner, bottomRightCorner );
}

//----------------------------------------------------------

template <class T>
RectangularROI<T>::~RectangularROI()
{
}

//----------------------------------------------------------

template <class T>
void RectangularROI<T>::Initialize( Point<T> topLeftCorner, Point<T> bottomRightCorner )
{
   if (    ( topLeftCorner.GetX() <= bottomRightCorner.GetX() )
        && ( topLeftCorner.GetY() <= bottomRightCorner.GetY() )
      )
   {
      mTopLeftCorner     = topLeftCorner;
      mBottomRightCorner = bottomRightCorner;
   }
   else
   {
      mTopLeftCorner     = bottomRightCorner;
      mBottomRightCorner = topLeftCorner;
      std::cerr << "In RectangularROI: first point entered " << topLeftCorner
                << " is no valid top point compared with "   << bottomRightCorner
                << ") !!!" << std::endl << std::flush;
   }
   mWidth  = mBottomRightCorner.GetX() - mTopLeftCorner.GetX();
   mHeight = mBottomRightCorner.GetY() - mTopLeftCorner.GetY();
   mCenter.SetXAndY( topLeftCorner.GetX() + mWidth / 2, topLeftCorner.GetY() + mHeight / 2 );
}

//----------------------------------------------------------

template <class T>
Point<T> RectangularROI<T>::GetTopLeftCorner()
{
   return  mTopLeftCorner;
}

//----------------------------------------------------------

template <class T>
Point<T> RectangularROI<T>::GetBottomRightCorner()
{
   return mBottomRightCorner;
}

//----------------------------------------------------------

template <class T>
Point<T> RectangularROI<T>::GetCenter()
{
   return mCenter;
}

//----------------------------------------------------------

template <class T>
T RectangularROI<T>::GetWidth()
{
   return mWidth;
}

//----------------------------------------------------------

template <class T>
T RectangularROI<T>::GetHeight()
{
   return mHeight;
}

//----------------------------------------------------------

template <class T>
T RectangularROI<T>::GetArea()
{
   return ( mWidth * mHeight );
}

//----------------------------------------------------------

template <class T>
T RectangularROI<T>::GetDiagonalLength()
{
   double w2 = (double)(  mWidth * mWidth  );
   double h2 = (double)( mHeight * mHeight );
   return sqrt( w2 + h2 );
}

//----------------------------------------------------------

template <class T>
bool RectangularROI<T>::IsInROI( Point<T> candidatePoint )
{
   if (    ( candidatePoint.GetX() >= mTopLeftCorner.GetX() )
        && ( candidatePoint.GetX() <= mBottomRightCorner.GetX() )
        && ( candidatePoint.GetY() >= mTopLeftCorner.GetY() )
        && ( candidatePoint.GetY() <= mBottomRightCorner.GetY() )
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

}
}
#endif
