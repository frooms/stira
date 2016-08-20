
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

#include <iostream>
#include <cstdlib>
#include <cassert>
#include "../geometrictransform/Translation.h"
#include "../geometrictransform/RigidTransform.h"
#include "../geometrictransform/AffineTransform.h"
#include "../geometrictransform/FisheyeCorrector.h"
#include "../tools/ImageIO.h"
#include "../interpolation/BilinearInterpolator.h"

using namespace std;
using namespace stira::imagedata;
using namespace stira::imagetools;
using namespace stira::common;

//========================================================================================

bool TranslationTest( Image* pInImage )
{
   Translation tran;
   tran.SetDeltaX( 5.1 );
   tran.SetDeltaY( 3.7 );

   Image* pImageOut = tran.Apply( pInImage );
   assert( pImageOut != 0 );

   assert ( ImageIO::Write( pImageOut, string("TranslateTest.ppm") ) == true);
   delete pImageOut;

   return true;
}

//========================================================================================

bool RigidTest( Image* pInImage )
{
   RigidTransform rig;
   rig.SetInterpolatorType(INTERPOLATE_BICUBIC);
   rig.SetTheta( 0.3 );
   rig.SetDeltaX( 5.1 );
   rig.SetDeltaY( 3.7 );

   Image* pImageOut = rig.Apply( pInImage );
   assert( pImageOut != 0 );
   assert ( ImageIO::Write( pImageOut, string("RigidTest.ppm") ) == true);
   delete pImageOut;

   Image* pImageRotated = rig.RotateAroundCenter( pInImage, 0.1 );
   assert( pImageRotated != 0 );
   assert ( ImageIO::Write( pImageRotated, string("RotateTest.ppm") ) == true);
   delete pImageRotated;

   return true;
}

//========================================================================================

bool AffineTest( Image* pInImage )
{
   AffineTransform aftran;
   aftran.SetA11( 1.3 );
   aftran.SetA12( 0.4 );
   aftran.SetA21( 0.4 );
   aftran.SetA22( 0.5 );
   aftran.SetDeltaX( 1.7 );
   aftran.SetDeltaY( 3.9 );

   // default bilinear
   Image* pImageOut = aftran.Apply( pInImage );
   assert ( ImageIO::Write( pImageOut, string("AffineTestBilinear.ppm") ) == true);
   delete pImageOut;

   aftran.SetInterpolatorType( INTERPOLATE_NEAREST_NEIGHBOR );
   pImageOut = aftran.Apply( pInImage );
   assert ( ImageIO::Write( pImageOut, string("AffineTestNearestNeighbor.ppm") ) == true);
   delete pImageOut;

   aftran.SetInterpolatorType( INTERPOLATE_BICUBIC );
   pImageOut = aftran.Apply( pInImage );
   assert ( ImageIO::Write( pImageOut, string("AffineTestBicubic.ppm") ) == true);

   Image* pImageOut2 = aftran.ApplyInverse( pImageOut );
   assert ( ImageIO::Write( pImageOut2, string("AffineTestInverse.ppm") ) == true);
   delete pImageOut;
   delete pImageOut2;

   return true;
}

//========================================================================================

bool AffineForwardInverseTest( )
{
   AffineTransform aftran;
   aftran.SetA11( 1.3 );
   aftran.SetA12( 2.4 );
   aftran.SetA21( 3.4 );
   aftran.SetA22( 4.5 );
   aftran.SetDeltaX( 1.7 );
   aftran.SetDeltaY( 3.9 );

   Point<double> p1(3.5, 8.7);

   Point<double> p1Forward = aftran.GetTransformedPoint( p1.x, p1.y );

   Point<double> p1ForwardInverse = aftran.GetInverseTransformedPoint( p1Forward.x, p1Forward.y );

   cout << "Original point " << p1 << ", after forward transform " << p1Forward << " and after forward+inverse transform  " << p1ForwardInverse << endl << flush;

   if ( p1 == p1ForwardInverse )
   {
      return true;
   }
   else
   {
      return false;
   }
}

//========================================================================================

bool InterpolationTest( )
{
   double x1 = 14;
   double x2 = 15;
   double y1 = 20;
   double y2 = 21;

   double I11 =  91;
   double I12 = 162;
   double I21 = 210;
   double I22 =  95;

   double x = 14.5;
   double y = 20.2;

   double interpolatedValue = BilinearInterpolator:: Run( x1, x2, y1, y2, I11, I12, I21, I22, x, y );

   assert ( fabs( interpolatedValue - 146.1 ) < 0.0001 );

   return true;
}

//========================================================================================

bool FisheyeTest( )
{
   Image* pInImage = ImageIO::Read( "../../../../stira/stira/testdata/Fisheye_photo.ppm" );
   FisheyeCorrector fc;

   Image* pImageCorrected = fc.ApplyCorrect( pInImage, 14, 3 );
   assert( pImageCorrected != 0 );
   assert ( ImageIO::Write( pImageCorrected, string("FisheyeTest.ppm") ) == true);
   delete pImageCorrected;

   return true;
}

//========================================================================================

int main(int argc, char *argv[])
{
   int testsRun = 0;
   int testsSuccess = 0;
   const char* fileName;
   if (argc == 2)
   {
      fileName = argv[1];
   }
   else
   {
      fileName = "../../../../stira/stira/testdata/colorsquares.ppm";
   }

   Image* pInImage = ImageIO::Read( fileName );

   testsRun++;
   if ( AffineForwardInverseTest( ) != true)
   {
      cerr << "AffineForwardInverseTest went wrong..." << endl << flush;
   }
   else
   {
       testsSuccess ++;
   }

   // 0) Generate synthetic test images test
   ///////////////////////////////
   testsRun++;
   if ( TranslationTest( pInImage ) != true)
   {
      cerr << "TranslationTest on image went wrong..." << endl << flush;
   }
   else
   {
       testsSuccess ++;
   }

   testsRun++;
   if ( RigidTest( pInImage ) != true)
   {
      cerr << "RigidTest on image went wrong..." << endl << flush;
   }
   else
   {
       testsSuccess ++;
   }

   testsRun++;
   if ( AffineTest( pInImage ) != true)
   {
      cerr << "AffineTest on image went wrong..." << endl << flush;
   }
   else
   {
       testsSuccess ++;
   }

   testsRun++;
   if ( InterpolationTest( ) != true)
   {
      cerr << "InterpolationTest went wrong..." << endl << flush;
   }
   else
   {
       testsSuccess ++;
   }

   testsRun++;
   if ( FisheyeTest( ) != true)
   {
      cerr << "InterpolationTest went wrong..." << endl << flush;
   }
   else
   {
       testsSuccess ++;
   }

   cout << "Tests run = " << testsRun << ", of which succeeded " << testsSuccess << endl << flush;
   delete pInImage;
   return EXIT_SUCCESS;
}
