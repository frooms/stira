
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
#include "../color/ColorValue.h"

namespace stira {
namespace image {

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
      DrawPoint( pImageInOut, (*it).GetX(), (*it).GetY(), newColor );
   }
   return pointVector;
}

//--------------------------------------------------------------------------------------

std::vector< Point<int> > DrawImageTools::DrawLine( Image* pImageInOut, Point<int> startPoint, Point<int> stopPoint, ColorValue newColor)
{
   return DrawLine( pImageInOut, startPoint.GetX(), stopPoint.GetX(), startPoint.GetY(), stopPoint.GetY(), newColor );
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
   DrawPoint( pImageInOut, myPoint.GetX(), myPoint.GetY(), newColor );
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
         DrawPoint( pImageInOut, myCenterPoint.GetX() + dx, myCenterPoint.GetY() + dy, newColor );
      }
   }
}

//--------------------------------------------------------------------------------------

void DrawImageTools::DrawRectangle( ArrayGrid<double>* pGridInOut, common::Point<int> myTopLeftPoint, common::Point<int> myBottomRightPoint, double newValue, bool fillSurface )
{
   if ( fillSurface )
   {
      for (int yy = myTopLeftPoint.GetY(); yy <= myBottomRightPoint.GetY(); yy++)
      {
         for (int xx = myTopLeftPoint.GetX(); xx <= myBottomRightPoint.GetX(); xx++)
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
      for (int yy = myTopLeftPoint.GetY(); yy <= myBottomRightPoint.GetY(); yy++)
      {
         for (int xx = myTopLeftPoint.GetX(); xx <= myBottomRightPoint.GetX(); xx++)
         {
            if (    ( xx == myTopLeftPoint.GetX() )
                 || ( xx == myBottomRightPoint.GetX() )
                 || ( yy == myTopLeftPoint.GetY() )
                 || ( yy == myBottomRightPoint.GetY() )
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

void DrawImageTools::DrawCircle( Image* pImageInOut, Point<int> myCenterPoint, double radius, ColorValue newColor)
{
   for (int dy = -radius; dy <= radius; dy++)
   {
      for (int dx = -radius; dx <= radius; dx++)
      {
         double tmpRadius = sqrt( (double)(dx)*(double)(dx) + (double)(dy)*(double)(dy) );
         if (tmpRadius <= radius)
         {
            DrawPoint( pImageInOut, myCenterPoint.GetX() + dx, myCenterPoint.GetY() + dy, newColor );
         }
      }
   }
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
