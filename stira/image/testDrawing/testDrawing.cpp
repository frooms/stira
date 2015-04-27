

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
#include "../../common/common/RectangularROI.h"
#include "../../common/common/DrawFigures.h"
#include "../tools/ImageIO.h"
#include "../tools/NumberGridTools.h"
#include "../tools/ImageTools.h"

using namespace std;
using namespace stira::image;
using namespace stira::common;

void TestDrawFigure()
{
   int width = 512;
   int height = 512;
   ArrayGrid<int>* pGrid = new ArrayGrid<int>( width, height );
   std::vector< Point<int> > vCorners;
   Point<int> p1(129, 52);   vCorners.push_back( p1 );
   Point<int> p2(234, 32);   vCorners.push_back( p2 );
   Point<int> p3(356, 51);   vCorners.push_back( p3 );
   Point<int> p4(267, 248);  vCorners.push_back( p4 );
   Point<int> p5(100, 156);  vCorners.push_back( p5 );

   pGrid->SetValue( DrawFigures::DrawPolygon( vCorners ), 250 );

   Point<int> testPointOut( 60, 240 );
   pGrid->SetValue( testPointOut.GetX(), testPointOut.GetY(), 250 );
   pGrid->SetValue( testPointOut.GetX()-1, testPointOut.GetY(), 250 );
   pGrid->SetValue( testPointOut.GetX()+1, testPointOut.GetY(), 250 );
   pGrid->SetValue( testPointOut.GetX(), testPointOut.GetY()-1, 250 );
   pGrid->SetValue( testPointOut.GetX(), testPointOut.GetY()+1, 250 );

   ImageIO::WritePGM( pGrid, std::string("Polygon.pgm"), ImageIO::NULL_OUT );

   bool testRes1 = DrawFigures::IsPointInPolygon( vCorners, testPointOut );
   cout << "Test point 1 in polygon = " << testRes1 << endl << flush;

   Point<int> testPointIn( 226, 126 );
   pGrid->SetValue( testPointIn.GetX(), testPointIn.GetY(), 250 );
   pGrid->SetValue( testPointIn.GetX()-1, testPointIn.GetY(), 250 );
   pGrid->SetValue( testPointIn.GetX()+1, testPointIn.GetY(), 250 );
   pGrid->SetValue( testPointIn.GetX(), testPointIn.GetY()-1, 250 );
   pGrid->SetValue( testPointIn.GetX(), testPointIn.GetY()+1, 250 );

   ImageIO::WritePGM( pGrid, std::string("Polygon.pgm"), ImageIO::NULL_OUT );

   bool testRes2 = DrawFigures::IsPointInPolygon( vCorners, testPointIn );
   cout << "Test point 2 in polygon = " << testRes2 << endl << flush;
   delete pGrid;
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
      fileName = "../../testdata/lena256.pgm";
   }
   Image* pInImage = ImageIO::Read( fileName );
   TestDrawFigure();

   delete pInImage;
   return allSuccess;
}
