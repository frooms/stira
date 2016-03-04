
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

#ifndef STIRA_COMMON_DRAWFIGURES_H
#define STIRA_COMMON_DRAWFIGURES_H

#include <vector>
#include "Point.h"
#include "RectangularROI.h"

namespace stira {
namespace common {

/** \brief A class to draw some simple parametric figure contours.
  *
  * In fact, this class generates a vector with the pixels that belong to the contour of the figure.
  *
  * The corresponding tests are located in subproject image/testDrawing */
class DrawFigures{
public:

   /** \brief Constructor.*/
   DrawFigures();

   /** \brief Destructor. */
   ~DrawFigures();

   /** \brief Generates vector with points on line to be drawn
     * Algoritm used is Bresenham, see
     * <A HREF="http://en.wikipedia.org/wiki/Bresenham's_line_algorithm">
                http://en.wikipedia.org/wiki/Bresenham's_line_algorithm</A>
     * \param startX x coordinate of start point
     * \param startY y coordinate of start point
     * \param endX x coordinate of end point
     * \param endY y coordinate of end point*/
   static std::vector< Point<int> > BresenhamDrawLine( int startX, int startY, int endX, int endY );

   /** \brief Generates vector with points on line to be drawn
     * Overloaded method with points as inputs instead of all coordinates separately
     * \param startPoint start point of the line
     * \param endPoint   end point of the line */
   static std::vector< Point<int> > BresenhamDrawLine( Point<int> startPoint, Point<int> endPoint );

   /** \brief Generates vector with points on rectangle to be drawn, edges parallel with the axes
     *
     * \param topLeftX x coordinate of top left corner
     * \param topLeftY y coordinate of top left corner
     * \param bottomRightX x coordinate of bottom right corner
     * \param bottomRightY y coordinate of bottom right corner */
   static std::vector< Point<int> > DrawRectangle(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY);

   /** \brief Tests if a point is inside an ellipse
     *
     * \param xTest x coordinate of point to test
     * \param yTest y coordinate of point to test
     * \param xCenter x coordinate of ellipse center
     * \param yCenter y coordinate of ellipse center
     * \param majorAxis ellipse major axis
     * \param minorAxis ellipse minor axis
     * \param angleRadians rotation angle of the ellipse */
   static bool IsInsideEllipse( double xTest, double yTest, double xCenter, double yCenter, double majorAxis, double minorAxis, double angleRadians );

   /** \brief Generates vector with points on rectangle to be drawn, edges parallel with the axes
     * Overloaded method with points as inputs instead of all coordinates separately
     * \param topLeftCorner top left corner of the rectangle
     * \param bottomRightCorner bottom right corner of the rectangle */
   static std::vector< Point<int> > DrawRectangle( Point<int> topLeftCorner, Point<int> bottomRightCorner );

   /** \brief Generates vector with points on rectangle to be drawn, edges parallel with the axes
     *
     * \param rroi rectangle to be drawn */
   static std::vector< Point<int> > DrawRectangle( RectangularROI<int> rroi );

   /** \brief Generates vector with points on circle to be drawn
     *  Implementation from <A HREF="http://en.wikipedia.org/wiki/Midpoint_circle_algorithm">
     *                               http://en.wikipedia.org/wiki/Midpoint_circle_algorithm</A>
     * \param center center of circle to be drawn
     * \param radius radius of circle to be drawn */
   static std::vector< Point<int> > DrawCircle( Point<int> center, int radius );

   /** \brief Draws a polygon
     *   We give a vector with sequentially the corner points.
     *   These are then connected by lines with the BresenhamDrawLine method .
     * \param vVertices vector containing the vertices (=corners) of the polgon */
   static std::vector< Point<int> > DrawPolygon( std::vector< Point<int> > vVertices );

   /** \brief Checks if a point is inside a polygon
     * Source <A HREF="http://www.ecse.rpi.edu/Homepages/wrf/Research/Short_Notes/pnpoly.html">
     *                 http://www.ecse.rpi.edu/Homepages/wrf/Research/Short_Notes/pnpoly.html</A>
     *
     * \param vVertices vector containing the vertices (=corners) of the polgon
     * \param testPoint point to be tested if it is inside the polygon */
   static bool IsPointInPolygon( std::vector< Point<int> > vVertices, Point<int> testPoint );

   /** \brief Computes area of a polygon
     * Source <A HREF="">
     *                 http://www.topcoder.com/tc?d1=tutorials&d2=geometry1&module=Static</A>
     *
     * \param vVertices vector containing the vertices (=corners) of the polgon */
   static double GetPolygonArea( std::vector< Point<int> > vVertices );

};
}
}
#endif
