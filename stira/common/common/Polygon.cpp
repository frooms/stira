
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

#include <algorithm>
#include <cassert>
#include "Polygon.h"
#include "Curve.h"
#include "DrawFigures.h"

namespace stira {
namespace common {

Polygon::Polygon() {}

//------------------------------------------------------------

void Polygon::AddVertex( Point<double> newVertex )
{
    mvVertices.push_back( newVertex );
}

//------------------------------------------------------------

unsigned int Polygon::GetNumberOfVertices( )
{
    return mvVertices.size();
}

//------------------------------------------------------------

Point<double> Polygon::GetVertex( int nr )
{
    return mvVertices[nr];
}

//------------------------------------------------------------

Point<int> Polygon::GetVertexInt( int nr )
{
    return Point<int>(mvVertices[nr].x + 0.5, mvVertices[nr].y + 0.5);
}

//------------------------------------------------------------

void Polygon::ChangeVertex( int nr, double x, double y )
{
    mvVertices[nr].x = x;
    mvVertices[nr].y = y;
}

//----------------------------------------------------------------------------------------------------------

bool Polygon::IsPointInPolygon( Point<int> testPoint )
{
   int nrVertices = mvVertices.size();
   int i, j;
   bool c = false;
   for (i = 0, j = nrVertices-1; i < nrVertices; j = i++)
   {
      if (    ( ( mvVertices[i].y > testPoint.y ) != ( mvVertices[j].y > testPoint.y ) )
           && (  testPoint.x < (        ( mvVertices[j].x - mvVertices[i].x )
                                      * ( testPoint.y  - mvVertices[i].y  )
                                      / ( mvVertices[j].y  - mvVertices[i].y  )
                                      + mvVertices[i].x
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

double Polygon::GetPolygonArea( )
{
   int numPoints = mvVertices.size();
   double area = 0;         // Accumulates area in the loop
   int j = numPoints-1;  // The last vertex is the 'previous' one to the first

   for (int i=0; i<numPoints; i++)
   {
      area = area +  (mvVertices[j].x + mvVertices[i].x) * (mvVertices[j].y - mvVertices[i].y);
      j = i;  //j is previous vertex to i
   }
   return abs(area/2);
}

//------------------------------------------------------------

}
}
