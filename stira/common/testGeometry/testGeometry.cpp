
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

#include "../common/Point.h"
#include "../common/RectangularROI.h"
#include "../common/DrawFigures.h"
#include "../common/LineSegment.h"
#include "../common/Curve.h"
#include <iostream>
#include <cassert>
#include <cstdlib>

#define TOLERANCE 0.000001

using namespace std;
using namespace stira::common;

bool TestRectangularROI()
{
   double topLeftX = 12.3;
   double topLeftY = 15.7;
   double bottomRightX = 56.1;
   double bottomRightY = 83.4;
   Point<double> topLeftCorner( topLeftX, topLeftY );
   Point<double> bottomRightCorner( bottomRightX, bottomRightY );

   RectangularROI<double> rroi( topLeftCorner, bottomRightCorner );

   Point<double> pInside( 17.1, 39.5 );
   Point<double> pOutside( 1.1, 3.8 );

   assert( rroi.IsInROI( pInside ) );       cout << "Test point inside ROI OK!" << endl << flush;
   assert( rroi.IsInROI( pOutside ) == false );      cout << "Test point outside ROI OK!" << endl << flush;
   assert( fabs( rroi.GetWidth() - ( bottomRightX - topLeftX ) ) < TOLERANCE );
   cout << "ROI width = " << rroi.GetWidth() << " and reference " << ( bottomRightX - topLeftX ) << " -> OK! " << endl << flush;
   cout << "ROI height = " << rroi.GetHeight() << " and reference " << ( bottomRightY - topLeftY ) << " -> OK! " << endl << flush;
   assert( fabs( rroi.GetHeight() - ( bottomRightY - topLeftY ) ) < TOLERANCE );
   return true;
}

//-------------------------------------------------------

void TestPointOperators()
{
   Point<double> p1( 17.1, 39.5 );
   Point<double> p2( 1.1, 3.8 );

   Point<double> p3 = p1 + p2;
   Point<double> p4 = p1 - p2;
   cout << p1 << " + " << p2 << " = " << p3 << endl << flush;
   cout << p1 << " - " << p2 << " = " << p4 << endl << flush;

   cout << p1 << " == " << p1 << "? -> " << ( p1 == p1 ) << endl << flush;
   cout << p1 << " == " << p2 << "? -> " << ( p1 == p2 ) << endl << flush;

   cout << p1 << " * " << p2 << " = " << (p1 * p2) << endl << flush;
   cout << p1 << " ^ " << p2 << " = " << (p1 ^ p2) << endl << flush;

   Point<double> p5 = p1;
   cout << "p1 = " << p1 << " and after assignment, p5 = " << p5 << endl << flush;
}

//-------------------------------------------------------

void TestConnectCurves()
{
   int startX1 = 15;
   int startY1 =  7;
   int endX1   = 29;
   int endY1   = 10;
   std::vector< Point<int> > pointsOnLine1 = DrawFigures::BresenhamDrawLine( startX1, startY1, endX1, endY1 );
   Curve myCurve1( pointsOnLine1 );
   myCurve1.WritePointsToStdOut();

   cout << "Start point is " << myCurve1.GetStartPoint() << endl << flush;
   cout << "End point is " << myCurve1.GetEndPoint() << endl << flush;

   int startX2 = 32;
   int startY2 = 12;
   int endX2   = 45;
   int endY2   = 15;
   std::vector< Point<int> > pointsOnLine2 = DrawFigures::BresenhamDrawLine( startX2, startY2, endX2, endY2 );
   Curve myCurve2( pointsOnLine2 );
   myCurve2.WritePointsToStdOut();

   cout << "New merged curve " << endl << endl << flush;
   myCurve1.ConnectToCurve( myCurve2 );
   myCurve1.WritePointsToStdOut();
}

//-------------------------------------------------------

void TestEllipse()
{
   /* initialize random seed: */
   srand (time(NULL));


   ofstream myfile;
   myfile.open ("example.txt");


   for (int i = 0; i < 500; i++)
   {
         double x = 512 * (double)(rand()) / ((double)RAND_MAX);
         double y = 512 * (double)(rand()) / ((double)RAND_MAX);

         if ( DrawFigures::IsInsideEllipse(x, y, 256, 256, 200, 100, M_PI / 4) )
         {
             myfile << x << ", " << y << endl;
         }
   }
   myfile.close();
}

//-------------------------------------------------------

void TestLineSegment()
{
   Point<double> p( 17.2, 39.5 );
   Point<double> p1( 34.1, 3.8 );
   Point<double> p2( 87.1, 3.8 );

   LineSegment<double> ls( p1, p2 );

   double length = ls.GetLength();
   double distance = ls.GetDistanceToLine( p );

   cout << "length of " << p1 << " - " << p2 << " = " << length << endl << flush;
   cout << "distance of " << p << " to this line = " << distance << endl << flush;
}

//-------------------------------------------------------

void TestSmoothCurve()
{
   Point<double> p( 17.2, 39.5 );
   Point<double> p1( 34.1, 3.8 );
   Point<double> p2( 87.1, 3.8 );

   LineSegment<double> ls( p1, p2 );

   double length = ls.GetLength();
   double distance = ls.GetDistanceToLine( p );

   cout << "length of " << p1 << " - " << p2 << " = " << length << endl << flush;
   cout << "distance of " << p << " to this line = " << distance << endl << flush;
}

//-------------------------------------------------------

int main()
{
   TestRectangularROI();
   TestPointOperators();
   TestLineSegment();
   TestConnectCurves();
   TestEllipse();
   return 1;
}

