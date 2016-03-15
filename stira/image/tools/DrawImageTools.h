
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

#ifndef STIRA_IMAGE_TOOLS_DRAWIMAGETOOLS_H
#define STIRA_IMAGE_TOOLS_DRAWIMAGETOOLS_H

#include "../../common/common/StiraMacros.h"
#include "../../common/common/Point.h"
#include "NumberGridTools.h"
#include "../datastructures/Image.h"
#include "../color/ColorValue.h"

namespace stira {
namespace image {

/** \brief Class with operations on image objects;
  * This class draws within an existing image without creating a new image object */
class DrawImageTools
{
public:
   /** \brief constructor */
   DrawImageTools();

   /** \brief destructor */
   ~DrawImageTools();

   /** Draws a square of given color in an image
     * \param pImageInOut image to draw on
     * \param myCenterPoint central point of square to draw
     * \param halfLength half of side of square to draw
     * \param newColor color of square */
   static void DrawSquare( Image* pImageInOut, common::Point<int> myCenterPoint, int halfLength, ColorValue newColor );

   /** Draws a rectangle of given intensity on grid
     * \param pGridInOut grid to draw on
     * \param myTopLeftPoint top left point of rectangle to draw
     * \param myBottomRightPoint bottom right point of rectangle to draw
     * \param newValue value to set inside the rectangle
     * \param fillSurface flag whether or not the rectangle should be filled; if false, only the circumference is drawn */
   static void DrawRectangle( ArrayGrid<double>* pGridInOut, common::Point<int> myTopLeftPoint, common::Point<int> myBottomRightPoint, double newValue, bool fillSurface );

   /** Draws a rectangle of given intensity on grid
     * \param pGridInOut grid to draw on
     * \param rroi rectangle ROI to draw
     * \param newValue value to set inside the rectangle
     * \param fillSurface flag whether or not the rectangle should be filled; if false, only the circumference is drawn */
   static void DrawRectangle( ArrayGrid<double>* pGridInOut, common::RectangularROI<int> rroi, double newValue, bool fillSurface );

   /** Draws a rectangle of given color (all bands same value) on an image
     * \param pGridInOut grid to draw on
     * \param myTopLeftPoint top left point of rectangle to draw
     * \param myBottomRightPoint bottom right point of rectangle to draw
     * \param newValue value to set inside the rectangle
     * \param fillSurface flag whether or not the rectangle should be filled; if false, only the circumference is drawn */
   static void DrawRectangle( Image* pImageInOut, common::Point<int> myTopLeftPoint, common::Point<int> myBottomRightPoint, double newValue, bool fillSurface );

   /** Draws a rectangle of given color (all bands same value) on an image
     * \param pImageInOut image to draw on
     * \param rroi rectangle ROI to draw
     * \param newValue value to set inside the rectangle
     * \param fillSurface flag whether or not the rectangle should be filled; if false, only the circumference is drawn */
   static void DrawRectangle( Image* pImageInOut, common::RectangularROI<int> rroi, double newValue, bool fillSurface );

   /** Draws a rectangle of given color on an image
     * \param pImageInOut image to draw on
     * \param myTopLeftPoint top left point of rectangle to draw
     * \param myBottomRightPoint bottom right point of rectangle to draw
     * \param newColorValue color to set inside the rectangle
     * \param fillSurface flag whether or not the rectangle should be filled; if false, only the circumference is drawn */
   static void DrawRectangle( Image* pImageInOut, common::Point<int> myTopLeftPoint, common::Point<int> myBottomRightPoint, ColorValue newColorValue, bool fillSurface );

   /** Draws a rectangle of given color on an image
     * \param pImageInOut image to draw on
     * \param rroi rectangle ROI to draw
     * \param newColorValue color to set inside the rectangle
     * \param fillSurface flag whether or not the rectangle should be filled; if false, only the circumference is drawn */
   static void DrawRectangle( Image* pImageInOut, common::RectangularROI<int> rroi, ColorValue newColorValue, bool fillSurface );

   /** Draws a filled disk of given color in an image
     * \param pImageInOut image to draw on
     * \param myCenterPoint central point of circle to draw
     * \param radius radius of circle to draw
     * \param newColor color of circle */
   static void DrawDisk( Image* pImageInOut, common::Point<int> myCenterPoint, double radius, ColorValue newColor=ColorValue( 255, 0, 0, TYPE_RGB ));

   static void Plot8CirclePoints( Image* pImage, int xCenter, int yCenter, int x, int y, ColorValue cv );

   /** Draws a circle contour of given color in an image
     * \param pImageInOut image to draw on
     * \param myCenterPoint central point of circle to draw
     * \param radius radius of circle to draw
     * \param newColor color of circle */
   static void DrawCircle( Image* pImageInOut, common::Point<int> myCenterPoint, double radius, ColorValue newColor=ColorValue( 255, 0, 0, TYPE_RGB ));

   /** Draws a line of given color in an image
     * \param pImageInOut image to draw on
     * \param xStart x coordinate of start point on line to draw
     * \param xStop  x coordinate of stop point on line to draw
     * \param yStart y coordinate of start point on line to draw
     * \param yStop  y coordinate of stop point on line to draw
     * \param newColor color of line */
   static std::vector< common::Point<int> > DrawLine( Image* pImageInOut, int xStart, int xStop, int yStart, int yStop, ColorValue newColor=ColorValue( 255, 0, 0, TYPE_RGB ));

   /** Draws a line of given color in an image
     * \param pImageInOut image to draw on
     * \param startPoint start point of line to draw
     * \param stopPoint  stop point of line to draw
     * \param newColor color of line */
   static std::vector< common::Point<int> > DrawLine( Image* pImageInOut, common::Point<int> startPoint, common::Point<int> stopPoint, ColorValue newColor=ColorValue( 255, 0, 0, TYPE_RGB ));

   static void DrawArrow(Image* pImage, common::Point<int> p, common::Point<int> q, ColorValue cv, const float scale = 0.2);

   /** Draws a point of given color in an image
     * \param pImageInOut image to draw on
     * \param x x coordinate of point
     * \param y y coordinate of point
     * \param newColor color of square */
   static void DrawPoint( Image* pImageInOut, int x, int y, ColorValue newColor);

   /** Draws a point of given color in an image
     * \param pImageInOut image to draw on
     * \param myPoint point to draw
     * \param newColor color of square */
   static void DrawPoint( Image* pImageInOut, common::Point<int> myPoint, ColorValue newColor);

   /** Draws a vector of points of given color in an image
     * \param pGridInOut grid to draw on
     * \param vPoints vector of points to draw
     * \param newValue new value to set for the selected points */
   static void DrawPoints( ArrayGrid<double>* pGridInOut, std::vector< common::Point<int> > vPoints, double newValue );

   /** Draws a vector of points of given color in an image
     * \param pImageInOut image to draw on
     * \param vPoints vector of points to draw
     * \param newColor color of square */
   static void DrawPoints( Image* pImageInOut, std::vector< common::Point<int> > vPoints, ColorValue newColor);

   /** Creates a greyscale image with color points where pGridBool has value true
     * \param pGrid input grid on which the greyscale image will be based
     * \param pGridBool the boolean mask of points to draw in the specified color
     * \param cv the color value to use to draw the points with value "true" in the pGridBool */
   static Image* DrawBoolOnInput( ArrayGrid<double>* pGrid, ArrayGrid<bool>* pGridBool, ColorValue cv=ColorValue( 255, 0, 0, TYPE_RGB ) );
};

}
}

#endif
