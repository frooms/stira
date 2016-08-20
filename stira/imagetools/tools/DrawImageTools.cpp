
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

#include "DrawImageTools.h"
#include <stdint.h>
#include <iostream>
#include <vector>
#include "../../common/common/Point.h"
#include "../../common/common/DrawFigures.h"
#include "../../imagedata/color/ColorValue.h"

namespace stira {
namespace imagetools {

using namespace common;

DrawImageTools::DrawImageTools()
{
}

//--------------------------------------------------------------------------------------

DrawImageTools::~DrawImageTools()
{
}

//--------------------------------------------------------------------------------------

std::vector< Point<int> > DrawImageTools::DrawLine( Image* pImageInOut, int xStart, int xStop, int yStart, int yStop, ColorValue newColor )
{
   std::vector< Point<int> > pointVector = DrawFigures::BresenhamDrawLine( xStart, yStart, xStop, yStop );

   for( std::vector< Point<int> >::iterator it = pointVector.begin();
       it != pointVector.end();
       ++it
      )
   {
      DrawPoint( pImageInOut, (*it).x, (*it).y, newColor );
   }
   return pointVector;
}

//--------------------------------------------------------------------------------------

std::vector< Point<int> > DrawImageTools::DrawLine( Image* pImageInOut, Point<int> startPoint, Point<int> stopPoint, ColorValue newColor)
{
   return DrawLine( pImageInOut, startPoint.x, stopPoint.x, startPoint.y, stopPoint.y, newColor );
}

//--------------------------------------------------------------------------------------

std::vector< common::Point<int> > DrawImageTools::DrawLine( ArrayGrid<double>* pGridInOut, common::Point<int> startPoint, common::Point<int> stopPoint, double newValue )
{
    std::vector< Point<int> > pointVector = DrawFigures::BresenhamDrawLine( startPoint.x, startPoint.y, stopPoint.x, stopPoint.y );

    for( std::vector< Point<int> >::iterator it = pointVector.begin();
        it != pointVector.end();
        ++it
       )
    {
       DrawPoint( pGridInOut, (*it), newValue );
    }
    return pointVector;
}

//--------------------------------------------------------------------------------------

void  DrawImageTools::DrawArrow(Image* pImg, Point<int> p, Point<int> q, ColorValue colour, const float scale)
{
    double angle = atan2( (double) p.y - q.y, (double) p.x - q.x ); // angle in radians
    double hypotenuse = sqrt( (double) (p.y - q.y) * (p.y - q.y) + (p.x - q.x) * (p.x - q.x));

    // Here we lengthen the arrow by a factor of scale
    q.x = (int) (p.x - scale * hypotenuse * cos(angle));
    q.y = (int) (p.y - scale * hypotenuse * sin(angle));
    DrawImageTools::DrawLine(pImg, p, q, colour);

    // create the arrow hooks
    p.x = (int) (q.x + 9 * cos(angle + M_PI / 4));
    p.y = (int) (q.y + 9 * sin(angle + M_PI / 4));
    DrawImageTools::DrawLine(pImg, p, q, colour);

    p.x = (int) (q.x + 9 * cos(angle - M_PI / 4));
    p.y = (int) (q.y + 9 * sin(angle - M_PI / 4));
    DrawImageTools::DrawLine(pImg, p, q, colour);
}

//--------------------------------------------------------------------------------------

void DrawImageTools::DrawPoint( Image* pImageInOut, int x, int y, ColorValue newColor )
{
   if (    ( x >= 0 )
        && ( x < pImageInOut->GetWidth() )
        && ( y >= 0 )
        && ( y < pImageInOut->GetHeight() )
      )
   {
      pImageInOut->SetColor( x, y, newColor );
   }
}

//--------------------------------------------------------------------------------------

void DrawImageTools::DrawPoint( Image* pImageInOut, Point<int> myPoint, ColorValue newColor)
{
   DrawPoint( pImageInOut, myPoint.x, myPoint.y, newColor );
}

//--------------------------------------------------------------------------------------

void DrawImageTools::DrawPoint( ArrayGrid<double>* pGridInOut, common::Point<int> myPoint, double newValue )
{
   pGridInOut->SetValue( myPoint, newValue );
}

//--------------------------------------------------------------------------------------

void DrawImageTools::DrawPoint( ArrayGrid<double>* pGridInOut, int x, int y, double newValue )
{
   pGridInOut->SetValue( x, y, newValue );
}

//--------------------------------------------------------------------------------------

void DrawImageTools::DrawPoints( ArrayGrid<double>* pGridInOut, std::vector< common::Point<int> > vPoints, double newValue )
{
   int length = vPoints.size();
   for (int i = 0; i < length; i++)
   {
      pGridInOut->SetValue( vPoints[i], newValue );
   }
}

//--------------------------------------------------------------------------------------

void DrawImageTools::DrawPoints( Image* pImageInOut, std::vector< Point<int> > vPoints, ColorValue newColor)
{
   int length = vPoints.size();
   for (int i = 0; i < length; i++)
   {
      DrawPoint( pImageInOut, vPoints[i], newColor );
   }
}

//--------------------------------------------------------------------------------------

void DrawImageTools::DrawSquare( Image* pImageInOut, Point<int> myCenterPoint, int halfLength, ColorValue newColor)
{
   for (int dy = -halfLength; dy <= halfLength; dy++)
   {
      for (int dx = -halfLength; dx <= halfLength; dx++)
      {
         DrawPoint( pImageInOut, myCenterPoint.x + dx, myCenterPoint.y + dy, newColor );
      }
   }
}

//--------------------------------------------------------------------------------------

void DrawImageTools::DrawRectangle( ArrayGrid<double>* pGridInOut, common::Point<int> myTopLeftPoint, common::Point<int> myBottomRightPoint, double newValue, bool fillSurface )
{
   if ( fillSurface )
   {
      for (int yy = myTopLeftPoint.y; yy <= myBottomRightPoint.y; yy++)
      {
         for (int xx = myTopLeftPoint.x; xx <= myBottomRightPoint.x; xx++)
         {
            if ( ( xx >= 0 ) && ( xx < pGridInOut->GetWidth() ) && ( yy >= 0 ) && ( yy < pGridInOut->GetHeight() ) )
            {
               pGridInOut->SetValue( xx, yy, newValue );
            }
         }
      }
   }
   else
   {
      for (int yy = myTopLeftPoint.y; yy <= myBottomRightPoint.y; yy++)
      {
         for (int xx = myTopLeftPoint.x; xx <= myBottomRightPoint.x; xx++)
         {
            if (    ( xx == myTopLeftPoint.x )
                 || ( xx == myBottomRightPoint.x )
                 || ( yy == myTopLeftPoint.y )
                 || ( yy == myBottomRightPoint.y )
               )
            {
               if ( xx >= 0 && xx < pGridInOut->GetWidth() && yy >= 0 && yy < pGridInOut->GetHeight() )
               {
                  pGridInOut->SetValue( xx, yy, newValue );
               }
            }
         }
      }
   }
}

//--------------------------------------------------------------------------------------

void DrawImageTools::DrawRectangle( ArrayGrid<double>* pGridInOut, common::RectangularROI<int> rroi, double newValue, bool fillSurface )
{
   DrawRectangle( pGridInOut, rroi.GetTopLeftCorner(), rroi.GetBottomRightCorner(), newValue, fillSurface );
}

//--------------------------------------------------------------------------------------

void DrawImageTools::DrawRectangle( Image* pImageInOut, common::Point<int> myTopLeftPoint, common::Point<int> myBottomRightPoint, double newValue, bool fillSurface )
{
   int nrBands = pImageInOut->GetNumberOfBands();
   for (int i = 0; i < nrBands; i++)
   {
      DrawRectangle( pImageInOut->GetBands()[i], myTopLeftPoint, myBottomRightPoint, newValue, fillSurface );
   }
}

//--------------------------------------------------------------------------------------

void DrawImageTools::DrawRectangle( Image* pImageInOut, common::RectangularROI<int> rroi, double newValue, bool fillSurface )
{
   int nrBands = pImageInOut->GetNumberOfBands();
   for (int i = 0; i < nrBands; i++)
   {
      DrawRectangle( pImageInOut->GetBands()[i], rroi, newValue, fillSurface );
   }
}

//--------------------------------------------------------------------------------------

void DrawImageTools::DrawRectangle( Image* pImageInOut, common::Point<int> myTopLeftPoint, common::Point<int> myBottomRightPoint, ColorValue newColorValue, bool fillSurface )
{
   int nrBands = pImageInOut->GetNumberOfBands();
   for (int i = 0; i < nrBands; i++)
   {
      double newValue = 255;
      if ( i < 3 )
      {
         newValue = newColorValue.c[i];
      }
      DrawRectangle( pImageInOut->GetBands()[i], myTopLeftPoint, myBottomRightPoint, newValue, fillSurface );
   }
}

//--------------------------------------------------------------------------------------

void DrawImageTools::DrawRectangle( Image* pImageInOut, common::RectangularROI<int> rroi, ColorValue newColorValue, bool fillSurface )
{
   int nrBands = pImageInOut->GetNumberOfBands();
   for (int i = 0; i < nrBands; i++)
   {
      double newValue = 255;
      if ( i < 3 )
      {
         newValue = newColorValue.c[i];
      }
      DrawRectangle( pImageInOut->GetBands()[i], rroi, newValue, fillSurface );
   }
}

//--------------------------------------------------------------------------------------

void DrawImageTools::DrawDisk( Image* pImageInOut, Point<int> myCenterPoint, double radius, ColorValue newColor)
{
   for (int dy = -radius; dy <= radius; dy++)
   {
      for (int dx = -radius; dx <= radius; dx++)
      {
         double tmpRadius = sqrt( (double)(dx)*(double)(dx) + (double)(dy)*(double)(dy) );
         if (tmpRadius <= radius)
         {
            DrawPoint( pImageInOut, myCenterPoint.x + dx, myCenterPoint.y + dy, newColor );
         }
      }
   }
}

//--------------------------------------------------------------------------------------

void DrawImageTools::DrawDisk( ArrayGrid<double>* pGridInOut, Point<int> myCenterPoint, double radius, double newValue )
{
   for (int dy = -radius; dy <= radius; dy++)
   {
      for (int dx = -radius; dx <= radius; dx++)
      {
         double tmpRadius = sqrt( (double)(dx)*(double)(dx) + (double)(dy)*(double)(dy) );
         if (tmpRadius <= radius)
         {
            DrawPoint( pGridInOut, myCenterPoint.x + dx, myCenterPoint.y + dy, newValue );
         }
      }
   }
}

//--------------------------------------------------------------------------------------

void DrawImageTools::Plot8CirclePoints( Image* pImage, int xCenter, int yCenter, int x, int y, ColorValue cv )
{
    pImage->SetColor( xCenter+x, yCenter+y, cv ); //point in octant 1
    pImage->SetColor( xCenter-x, yCenter+y, cv ); //point in octant 4
    pImage->SetColor( xCenter-x, yCenter-y, cv ); //point in octant 5
    pImage->SetColor( xCenter+x, yCenter-y, cv ); //point in octant 8
    pImage->SetColor( xCenter+y, yCenter+x, cv ); //point in octant 2
    pImage->SetColor( xCenter-y, yCenter+x, cv ); //point in octant 3
    pImage->SetColor( xCenter-y, yCenter-x, cv ); //point in octant 6
    pImage->SetColor( xCenter+y, yCenter-x, cv ); //point in octant 7
}

//--------------------------------------------------------------------------------------

void DrawImageTools::DrawCircle( Image* pImageInOut, common::Point<int> myCenterPoint, double radius, ColorValue cv )
{
    int x, y;
    int xChange, yChange;
    int radiusError;

    x = radius;
    y = 0;

    xChange = 1 - 2 * radius;
    yChange = 1;
    radiusError = 0;
    while ( x >= y )
    {
        Plot8CirclePoints( pImageInOut, myCenterPoint.x, myCenterPoint.y, x, y, cv );
        y++;
        radiusError += yChange;
        yChange += 2;
        if ( 2*radiusError + xChange > 0 )
        {
            x--;
            radiusError += xChange;
            xChange += 2;
        }
    }
}

//--------------------------------------------------------------------------------------

void DrawImageTools::DrawPolygon( Image* pImageInOut, common::Polygon myPolygon, ColorValue newColor )
{
    int nrVertices = myPolygon.GetNumberOfVertices();

    for (int i = 0; i < nrVertices-1; i++)
    {
        Point<double> pStart = myPolygon.GetVertex( i );
        Point<double> pStop  = myPolygon.GetVertex( i+1 );
        DrawLine( pImageInOut, pStart.x, pStop.x, pStart.y, pStop.y, newColor );
    }
    Point<double> pStart = myPolygon.GetVertex( nrVertices-1 );
    Point<double> pStop  = myPolygon.GetVertex( 0 );
    DrawLine( pImageInOut, pStart.x, pStop.x, pStart.y, pStop.y, newColor );
}

void DrawImageTools::DrawPolygon( ArrayGrid<double>* pGridInOut, common::Polygon myPolygon, double newValue )
{
    int nrVertices = myPolygon.GetNumberOfVertices();

    for (int i = 0; i < nrVertices-1; i++)
    {
        Point<int> pStart = myPolygon.GetVertexInt( i );
        Point<int> pStop  = myPolygon.GetVertexInt( i+1 );
        DrawLine( pGridInOut, pStart, pStop, newValue );
    }
    Point<int> pStart = myPolygon.GetVertexInt( nrVertices-1 );
    Point<int> pStop  = myPolygon.GetVertexInt( 0 );
    DrawLine( pGridInOut, pStart, pStop, newValue );
}

//--------------------------------------------------------------------------------------

Image* DrawImageTools::DrawBoolOnInput( ArrayGrid<double>* pGrid, ArrayGrid<bool>* pGridBool, ColorValue cv )
{
   Image* pImage = new Image( pGrid->GetWidth(), pGrid->GetHeight() );
   for (int i = 0; i < 3; i++)
   {
      ArrayGrid<double>* pGridClone = pGrid->Clone();
      pImage->AddBand( pGridClone );
   }

   for( int y = 0; y < pGrid->GetHeight(); y++ )
   {
      for( int x = 0; x < pGrid->GetWidth(); x++ )
      {
         if ( pGridBool->GetValue( x, y ) == false )
         {
            pImage->SetColor( x, y, cv );
         }
      }
   }
   return pImage;
}

//--------------------------------------------------------------------------------------

}
}
