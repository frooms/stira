
/***************************************************************************************
 *   Copyright (C) 2009 by Filip Rooms                                                 *
 *                                                                                     *
 *  Terms and conditions for using this software in any form are provided in the       *
 *  file COPYING, which can be found in the root directory of this project.            *
 *                                                                                     *
 *   Contact data: filip.rooms@gmail.com                                               *
 *                 http://www.filiprooms.be/                                           *
 *                                                                                     *
 ***************************************************************************************/

#include "DrawFigures.h"
#include "MathUtils.h"

#include <iostream>
#include <cmath>

using namespace std;

namespace stira {
namespace common{

DrawFigures::DrawFigures()
{
}

//==========================================================================================

DrawFigures::~DrawFigures()
{}

//==========================================================================================

std::vector< Point<int> > DrawFigures::BresenhamDrawLine(int x0, int y0, int x1, int y1)
{
   std::vector< Point<int> > pointsOnLine;
   int Dx = x1 - x0;
   int Dy = y1 - y0;
   int steep = (abs((double)(Dy)) >= abs((double)(Dx)));
   if (steep)
   {
      MathUtils::SwitchValues(x0, y0);
      MathUtils::SwitchValues(x1, y1);
      // recompute Dx, Dy after swap
      Dx = x1 - x0;
      Dy = y1 - y0;
   }
   int xstep = 1;
   if (Dx < 0)
   {
      xstep = -1;
      Dx = -Dx;
   }
   int ystep = 1;
   if (Dy < 0)
   {
      ystep = -1;
      Dy = -Dy;
   }
   int TwoDy = 2*Dy;
   int TwoDyTwoDx = TwoDy - 2*Dx; // 2*Dy - 2*Dx
   int E = TwoDy - Dx; //2*Dy - Dx
   int y = y0;
   int xDraw, yDraw;
   for (int x = x0; x != x1; x += xstep)
   {
      if (steep)
      {
         xDraw = y;
         yDraw = x;
      }
      else
      {
         xDraw = x;
         yDraw = y;
      }
      // plot
      pointsOnLine.push_back( Point<int>(xDraw, yDraw) );
      // next
      if (E > 0)
      {
         E += TwoDyTwoDx; //E += 2*Dy - 2*Dx;
         y = y + ystep;
      }
      else
      {
         E += TwoDy; //E += 2*Dy;
      }
   }
   return pointsOnLine;
}

//----------------------------------------------------------------------------------------------------------

std::vector< Point<int> > DrawFigures::BresenhamDrawLine( Point<int> startPoint, Point<int> endPoint )
{
   return BresenhamDrawLine( startPoint.GetX(), startPoint.GetY(), endPoint.GetX(), endPoint.GetY() );
}

//----------------------------------------------------------------------------------------------------------

std::vector< Point<int> > DrawFigures::DrawRectangle(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY)
{
   std::vector< Point<int> > vPointsROI;

   for ( int y = topLeftY; y <= bottomRightY; y++ )
   {
      vPointsROI.push_back( Point<int>( topLeftX, y) );
      vPointsROI.push_back( Point<int>( bottomRightX, y) );
   }

   for ( int x = topLeftX+1; x < bottomRightX; x++ )
   {
      vPointsROI.push_back( Point<int>(x, topLeftY) );
      vPointsROI.push_back( Point<int>(x, bottomRightY) );
   }
   return vPointsROI;
}

//----------------------------------------------------------------------------------------------------------

// http://stackoverflow.com/questions/7946187/point-and-ellipse-rotated-position-test-algorithm
bool DrawFigures::IsInsideEllipse( double xTest, double yTest, double xCenter, double yCenter, double majorAxis, double minorAxis, double angleRadians )
{
    double xm = ( ( xTest - xCenter ) * cos( angleRadians ) + ( yTest - yCenter ) * sin( angleRadians ) ) / majorAxis;
    double ym = ( ( xTest - xCenter ) * sin( angleRadians ) - ( yTest - yCenter ) * cos( angleRadians ) ) / minorAxis;

    double tmpValue = ( xm * xm ) + ( ym * ym );
    if (tmpValue <= 1.0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//----------------------------------------------------------------------------------------------------------

std::vector< Point<int> > DrawFigures::DrawRectangle( RectangularROI<int> rroi )
{
   return DrawRectangle( rroi.GetTopLeftCorner().GetX(),     rroi.GetTopLeftCorner().GetY(),
                         rroi.GetBottomRightCorner().GetX(), rroi.GetBottomRightCorner().GetY() );
}

//----------------------------------------------------------------------------------------------------------

std::vector< Point<int> > DrawFigures::DrawRectangle( Point<int> topLeftCorner, Point<int> bottomRightCorner )
{
   return DrawRectangle( topLeftCorner.GetX(),     topLeftCorner.GetY(),
                         bottomRightCorner.GetX(), bottomRightCorner.GetY() );
}

//----------------------------------------------------------------------------------------------------------

std::vector< Point<int> > DrawFigures::DrawCircle( Point<int> center, int radius )
{
   int x0 = center.GetX();
   int y0 = center.GetY();
   std::vector< Point<int> > vPointsROI;
   int f = 1 - radius;
   int ddF_x = 1;
   int ddF_y = -2 * radius;
   int x = 0;
   int y = radius;

   vPointsROI.push_back( Point<int>( x0, y0 + radius) );
   vPointsROI.push_back( Point<int>( x0, y0 - radius) );
   vPointsROI.push_back( Point<int>( x0 + radius, y0) );
   vPointsROI.push_back( Point<int>( x0 - radius, y0) );

   while(x < y)
   {
      // ddF_x == 2 * x + 1;
      // ddF_y == -2 * y;
      // f == x*x + y*y - radius*radius + 2*x - y + 1;
      if(f >= 0)
      {
         y--;
         ddF_y += 2;
         f += ddF_y;
      }
      x++;
      ddF_x += 2;
      f += ddF_x;
      vPointsROI.push_back( Point<int>( x0 + x, y0 + y) );
      vPointsROI.push_back( Point<int>( x0 - x, y0 + y) );
      vPointsROI.push_back( Point<int>( x0 + x, y0 - y) );
      vPointsROI.push_back( Point<int>( x0 - x, y0 - y) );
      vPointsROI.push_back( Point<int>( x0 + y, y0 + x) );
      vPointsROI.push_back( Point<int>( x0 - y, y0 + x) );
      vPointsROI.push_back( Point<int>( x0 + y, y0 - x) );
      vPointsROI.push_back( Point<int>( x0 - y, y0 - x) );
   }
   return vPointsROI;
}

//----------------------------------------------------------------------------------------------------------

std::vector< Point<int> > DrawFigures::DrawPolygon( std::vector< Point<int> > vVertices )
{
   std::vector< Point<int> > vPointsROI;

   int nrVertices = vVertices.size();

   for( int i = 0; i < nrVertices-1; i++)
   {
      Point<int> startPoint = vVertices[i];
      Point<int> stopPoint = vVertices[i+1];
      std::vector< Point<int> > vLinePoints = BresenhamDrawLine( startPoint.GetX(), startPoint.GetY(),
                                                                 stopPoint.GetX(), stopPoint.GetY() );
      int nrPointsInLine = vLinePoints.size();
      for ( int j = 0; j < nrPointsInLine; j++)
      {
         vPointsROI.push_back( vLinePoints[j] );
      }
   }

   Point<int> startPoint = vVertices[nrVertices-1];
   Point<int> stopPoint = vVertices[0];
   std::vector< Point<int> > vLinePoints = BresenhamDrawLine( startPoint.GetX(), startPoint.GetY(),
                                                              stopPoint.GetX(), stopPoint.GetY() );
   int nrPointsInLine = vLinePoints.size();
   for ( int j = 0; j < nrPointsInLine; j++)
   {
      vPointsROI.push_back( vLinePoints[j] );
   }
   return vPointsROI;
}

//----------------------------------------------------------------------------------------------------------

bool DrawFigures::IsPointInPolygon( std::vector< Point<int> > vVertices, Point<int> testPoint )
{
   int nvert = vVertices.size();
   int i, j;
   bool c = false;
   for (i = 0, j = nvert-1; i < nvert; j = i++)
   {
      if (    ( ( vVertices[i].GetY() > testPoint.GetY() ) != ( vVertices[j].GetY() > testPoint.GetY() ) )
           && (  testPoint.GetX() < (   ( vVertices[j].GetX() - vVertices[i].GetX() )
                                      * ( testPoint.GetY()  - vVertices[i].GetY()  )
                                      / ( vVertices[j].GetY()  - vVertices[i].GetY()  )
                                      + vVertices[i].GetX()
                                    )
              )
         )
      {
         c = !c;
      }
  }
  return c;
}

//----------------------------------------------------------------------------------------------------------

double DrawFigures::GetPolygonArea( std::vector< Point<int> > vVertices )
{
   double area = 0;
   int N = vVertices.size();
   //We will triangulate the polygon
   //into triangles with points vertex 0, vertex i and vertex i+1

   for(int i = 1; i+1<N; i++)
   {
       double x1 = vVertices[i].GetX() - vVertices[0].GetX();
       double y1 = vVertices[i].GetY() - vVertices[0].GetY();
       double x2 = vVertices[i+1].GetX() - vVertices[0].GetX();
       double y2 = vVertices[i+1].GetY() - vVertices[0].GetY();
       double cross = x1*y2 - x2*y1;
       area += cross;
   }
   return abs(area/2.0);
}

//----------------------------------------------------------------------------------------------------------

}
}
