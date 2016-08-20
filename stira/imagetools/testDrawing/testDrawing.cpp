

/***********************************************************************************
 *   Copyright (C) 2008 by Filip Rooms                                             *
 *                                                                                 *
 *  Terms and conditions for using this software in any form are provided in the   *
 *  file COPYING, which can be found in the root directory of this project.        *
 *                                                                                 *
 *   Contact data: filip.rooms@gmail.com                                           *
 *                 http://www.filiprooms.be/                                       *
 *                                                                                 *
 ***********************************************************************************/

#include <iostream>
#include <cstdlib>
#include <cassert>
#include "../../common/common/Point.h"
#include "../../common/common/Polygon.h"
#include "../../common/common/RectangularROI.h"
#include "../../common/common/DrawFigures.h"
#include "../tools/ImageIO.h"
#include "../tools/NumberGridTools.h"
#include "../tools/ImageTools.h"
#include "../tools/DrawImageTools.h"

using namespace std;
using namespace stira::imagedata;
using namespace stira::imagetools;
using namespace stira::common;

void TestDrawFigure()
{
   int width = 512;
   int height = 512;

   Image* pImage = new Image( width, height, 3 );

   Polygon myPolygon;
   myPolygon.AddVertex( Point<double>(  70,  50 ) );
   myPolygon.AddVertex( Point<double>( 240,  50 ) );
   myPolygon.AddVertex( Point<double>( 240, 380 ) );
   myPolygon.AddVertex( Point<double>(  70, 380 ) );

   DrawImageTools::DrawPolygon( pImage, myPolygon, ColorValue(50,100,250,TYPE_RGB) );

   Point<int> testPointOut( 60, 240 );

   DrawImageTools::DrawDisk( pImage, testPointOut, 1, ColorValue(250,0,0,TYPE_RGB) );

   bool testRes1 = myPolygon.IsPointInPolygon( testPointOut );
   cout << "Test point 1 in polygon = " << testRes1 << endl << flush;

   Point<int> testPointIn( 226, 126 );
   DrawImageTools::DrawDisk( pImage, testPointIn, 1, ColorValue(0,250,0,TYPE_RGB) );

   ImageIO::Write( pImage, std::string("Polygon1.ppm") );

   bool testRes2 = myPolygon.IsPointInPolygon( testPointIn );
   cout << "Test point 2 in polygon = " << testRes2 << endl << flush;

   double area = myPolygon.GetPolygonArea();

   assert( area == 170 * 330);
   cout << "Polygon area = " << area << endl << flush;

   myPolygon.ChangeVertex( 2, 330, 80 );
   DrawImageTools::DrawPolygon( pImage, myPolygon, ColorValue(250,200,250,TYPE_RGB) );
   ImageIO::Write( pImage, std::string("Polygon2.ppm") );
   delete pImage;
}

//========================================================================================

int main(int argc, char *argv[])
{
   const char* fileName;
   bool allSuccess = true;
   if (argc == 2)
   {
      fileName = argv[1];
   }
   else
   {
      fileName = "../../../../stira/stira/testdata/lena256.pgm";
   }
   Image* pInImage = ImageIO::Read( fileName );
   TestDrawFigure();

   delete pInImage;
   return allSuccess;
}
