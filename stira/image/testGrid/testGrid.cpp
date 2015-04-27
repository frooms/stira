
/***********************************************************************************
 *   Copyright (C) 2008, 2009 by Filip Rooms                                       *
 *                                                                                 *
 *  Terms and conditions for using this software in any form are provided in the   *
 *  file COPYING, which can be found in the root directory of this project.        *
 *                                                                                 *
 *   Contact data: filip.rooms@gmail.com                                           *
 *                 http://www.filiprooms.be/                                       *
 *                                                                                 *
 ***********************************************************************************/

#include "testGrid.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../../common/common/Point.h"
#include "../tools/GridExtender.h"
#include "../tools/GridGenerator.h"
#include "../tools/DrawImageTools.h"

using namespace stira;
using namespace stira::common;

//-----------------------------------------------------------------------------------------

bool TestGridData()
{
   ArrayGrid<double>* pZonePlate = GridGenerator::GenerateZonePlate();

   double* pArray = pZonePlate->GetDataCopy();
   int width  = pZonePlate->GetWidth();
   int height = pZonePlate->GetHeight();

   delete pZonePlate;

   ArrayGrid<double>* pNewGrid = new ArrayGrid<double>( width, height, pArray );

   ImageIO::WritePGM( pNewGrid, std::string("CopyGridZonePlate.pgm") );
   delete pNewGrid;

   return true;
}

//-----------------------------------------------------------------------------------------

bool TestGridExtender()
{
   Image* pImage = ImageIO::Read( std::string("../../testdata/lena256.pgm") );
   int borderWidth = 15;
   int borderHeight = 25;
   double myValue = 0;
   ArrayGrid<double>* pGrid = pImage->GetBands()[0];

   ArrayGrid<double>* pNullPaddedGrid = GridExtender<double>::PaddBorder( pGrid, borderWidth, borderHeight, myValue );
   ImageIO::WritePGM( pNullPaddedGrid, std::string("NullPaddedGrid.pgm") );
   delete pNullPaddedGrid;

   ArrayGrid<double>* pMirrorBorderGrid = GridExtender<double>::MirrorBorder( pGrid, borderWidth, borderHeight );
   ImageIO::WritePGM( pMirrorBorderGrid, std::string("MirrorBorderGrid.pgm") );
   delete pMirrorBorderGrid;

   delete pImage;

   return true;
}

//-----------------------------------------------------------------------------------------

bool GridTestBracketsOperator()
{
   int width = 150;
   int height = 100;
   ArrayGrid<double> grid(width, height);

   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         grid(x, y) = (double)(x-y);
      }
   }

   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         assert ( grid(x, y) == (double)(x-y) );
      }
   }
   ImageIO::WritePGM(&grid, string("GridTest.pgm"), ImageIO::NORMAL_OUT);
   return true;
}

//--------------------------------------------------------------------

bool GridRotateTest()
{
   int width = 150;
   int height = 100;
   ArrayGrid<double> grid(width, height);

   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         grid(x, y) = (double)(x-y);
      }
   }

   ArrayGrid<double>* pGrid000 = NumberGridTools<double>::Rotate90DegreesClockwise( &grid );
   ImageIO::WritePGM( pGrid000, string("GridNull.pgm"), ImageIO::NORMAL_OUT);
   delete pGrid000;

   ArrayGrid<double>* pGridPlus90 = NumberGridTools<double>::Rotate90DegreesClockwise( &grid );
   ImageIO::WritePGM( pGridPlus90, string("GridPlus90.pgm"), ImageIO::NORMAL_OUT);
   delete pGridPlus90;

   ArrayGrid<double>* pGridMin90 = NumberGridTools<double>::Rotate90DegreesCounterClockwise( &grid );
   ImageIO::WritePGM( pGridMin90, string("GridMin90.pgm"), ImageIO::NORMAL_OUT);
   delete pGridMin90;

   ArrayGrid<double>* pGrid180 = NumberGridTools<double>::Rotate180Degrees( &grid );
   ImageIO::WritePGM( pGrid180, string("Grid180.pgm"), ImageIO::NORMAL_OUT);
   delete pGrid180;

   cout << "Grid test succeeded!!" << endl << flush;
   return true;
}

//--------------------------------------------------------------------

bool GridAverageTest()
{
   int width = 256;
   int height = 256;

   int centerX = width / 2;
   int centerY = height / 2;
   double newValue = 240;
   bool fillSurface = true;
   int halfSize1 = 96;
   ArrayGrid<double>* pGrid1 = new ArrayGrid<double>(width, height);  DrawImageTools::DrawRectangle( pGrid1, Point<int>(centerX-halfSize1, centerY-halfSize1),
                                                                                                             Point<int>(centerX+halfSize1, centerY+halfSize1),
                                                                                                             newValue, fillSurface );
   std::vector< ArrayGrid<double>* > gridVector;
   gridVector.push_back( pGrid1 );
   ImageIO::WriteOpenCV( pGrid1, std::string("Square1.png") );

   halfSize1 = 64;
   ArrayGrid<double>* pGrid2 = new ArrayGrid<double>(width, height);  DrawImageTools::DrawRectangle( pGrid2, common::Point<int>(centerX-halfSize1, centerY-halfSize1),
                                                                                                             common::Point<int>(centerX+halfSize1, centerY+halfSize1),
                                                                                                             newValue, fillSurface );
   gridVector.push_back( pGrid2 );
   ImageIO::WriteOpenCV( pGrid2, std::string("Square2.png") );

   halfSize1 = 32;
   ArrayGrid<double>* pGrid3 = new ArrayGrid<double>(width, height);  DrawImageTools::DrawRectangle( pGrid3, common::Point<int>(centerX-halfSize1, centerY-halfSize1),
                                                                                                             common::Point<int>(centerX+halfSize1, centerY+halfSize1),
                                                                                                             newValue, fillSurface );
   gridVector.push_back( pGrid3 );
   ImageIO::WriteOpenCV( pGrid3, std::string("Square3.png") );


   ArrayGrid<double>* pAvgGrid = NumberGridTools<double>::AverageGrids( gridVector );
   ImageIO::WriteOpenCV( pAvgGrid, std::string("AvgSquare.png"), ImageIO::NULL_OUT );

   bool isSuccess = true;
   if ( (int)(pAvgGrid->GetValue( 128, 128 ) ) != 240 ) {isSuccess = false;}
   if ( (int)(pAvgGrid->GetValue(  78, 128 ) ) != 160 ) {isSuccess = false;}
   if ( (int)(pAvgGrid->GetValue(  48, 128 ) ) !=  80 ) {isSuccess = false;}

   delete pGrid1;
   delete pGrid2;
   delete pGrid3;
   delete pAvgGrid;

   if ( isSuccess )
   {
      cout << "Grid averaging test succeeded!!" << endl << flush;
   }
   return isSuccess;
}

//--------------------------------------------------------------------

bool GridPolarTransformTest()
{
   Image* pImage = ImageIO::Read( std::string("../../testdata/mandril.pgm") );

   ArrayGrid<double>* pGridPT = NumberGridTools<double>::LogPolarTransform( pImage->GetBands()[0] );
   ImageIO::WritePGM( pGridPT, string("GridLogPolarTransform.pgm"), ImageIO::NORMAL_OUT);
   delete pGridPT;

   cout << "GridPolarTransform test succeeded!!" << endl << flush;

   delete pImage;
   return true;
}

//--------------------------------------------------------------------

bool ExtractSubgridTest()
{
   Image* pImage = ImageIO::Read( std::string("../../testdata/mandril.pgm") );
   int xTop = 0;
   int yTop = 0;
   int xBottom = 128;
   int yBottom = 256;
   ArrayGrid<double>* pGridPT = ArrayGridTools<double>::ExtractSubGrid( pImage->GetBands()[0], xTop, yTop, xBottom, yBottom );
   ImageIO::WritePGM( pGridPT, string("ExtractedSubGrid.pgm"), ImageIO::NULL_OUT);
   delete pGridPT;

   cout << "ExtractSubGrid test succeeded!!" << endl << flush;

   delete pImage;
   return true;
}

//--------------------------------------------------------------------

bool MinMaxTest()
{
   int width = 97;
   int height = 123;
   ArrayGrid<double> grid(width, height);

   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         grid(x, y) = (double)(x-y);
      }
   }

   double mmin, mmax;
   int xMin, yMin, xMax, yMax;
   NumberGridTools<double>::GetMinMax( &grid, mmin, mmax, xMin, yMin, xMax, yMax );

   assert ( mmin == -122.0 );
   assert ( mmax ==   96.0 );
   assert ( mmin == grid(  0, 122 ) );
   assert ( mmax == grid( 96, 0   ) );

   grid.MultiplyWith( -3.0 );
   NumberGridTools<double>::GetMin( &grid, mmin, xMin, yMin );

   assert ( mmin == -288.0 );
   assert ( mmin == grid(96, 0) );

   NumberGridTools<double>::GetMax( &grid, mmax, xMax, yMax );

   assert ( mmax == 366.0 );
   assert ( mmax == grid( 0, 122 ) );

   grid.MultiplyWith( -2.0 );
   NumberGridTools<double>::GetMin( &grid, mmin, xMin, yMin );

   assert ( mmin == -732.0 );
   assert ( mmin == grid( 0, 122 ) );

   NumberGridTools<double>::GetMax( &grid, mmax, xMax, yMax );

   assert ( mmax == 576.0 );
   assert ( mmax == grid(96, 0) );

   ImageIO::WritePGM(&grid, string("GridTest.pgm"), ImageIO::NORMAL_OUT);
   cout << "MinMax test succeeded!!" << endl << flush;
   return true;
}

//--------------------------------------------------------------------

bool LocalStatisticsTest()
{
   int width = 128;
   int height = 128;
   ArrayGrid<double> grid(width, height);

   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         grid(x, y) = (double)(x+y);
      }
   }
   ImageIO::WriteOpenCV( &grid, std::string("TestAverageGridIn.pgm"), ImageIO::NULL_OUT );

   int x = 31;
   int y = 84;
   int localWidth = 5;
   int localHeight = 3;

   int localHalfWidth = localWidth / 2;
   int localHalfHeight = localHeight / 2;
   int xTopLeft = x - localHalfWidth;
   int yTopLeft = y - localHalfHeight;
   int xBottomRight = x + localHalfWidth;
   int yBottomRight = y + localHalfHeight;

   double localMean0 = NumberGridTools<double>::ComputeLocalMean( &grid, xTopLeft, yTopLeft, xBottomRight, yBottomRight );

   assert ( fabs( localMean0 - 115.0 ) < 0.01 );

   x = 90;
   y = 117;
   xTopLeft = x - localHalfWidth;
   yTopLeft = y - localHalfHeight;
   xBottomRight = x + localHalfWidth;
   yBottomRight = y + localHalfHeight;

   double localMin = NumberGridTools<double>::GetLocalMinimum( &grid, x, y, localWidth, localHeight );
   double localMax = NumberGridTools<double>::GetLocalMaximum( &grid, x, y, localWidth, localHeight );
   double localAbsMax = NumberGridTools<double>::GetLocalAbsMaximum( &grid, x, y, localWidth, localHeight );

   double localMean1 = NumberGridTools<double>::ComputeLocalMean( &grid, xTopLeft, yTopLeft, xBottomRight, yBottomRight );

   assert ( fabs( localMean1  - 207.0 ) < 0.01 );
   assert ( fabs( localMin    - 204.0 ) < 0.01 );
   assert ( fabs( localMax    - 210.0 ) < 0.01 );
   assert ( fabs( localAbsMax - 210.0 ) < 0.01 );

   double localAbsMean = NumberGridTools<double>::ComputeLocalAbsoluteMean( &grid, xTopLeft, yTopLeft, xBottomRight, yBottomRight );

   assert ( fabs( localAbsMean - 207.0 ) < 0.01 );

   double localVariance1 = NumberGridTools<double>::ComputeLocalVariance( &grid, xTopLeft, yTopLeft, xBottomRight, yBottomRight, localMean1 );
   double localVariance2 = NumberGridTools<double>::ComputeLocalVariance( &grid, xTopLeft, yTopLeft, xBottomRight, yBottomRight );

   assert ( fabs( localVariance1 - localVariance2 ) < 0.01 );

   return true;

}

//--------------------------------------------------------------------

int main( /*int argc, char *argv[]*/ )
{
   if( MinMaxTest() != true )
   {
      cerr << "MinMaxTest failed" << endl << flush;
   }
   if( GridTestBracketsOperator() != true )
   {
      cerr << "Grid BracketsOperator test failed" << endl << flush;
   }
   if( GridRotateTest() != true )
   {
      cerr << "Grid Rotate test failed" << endl << flush;
   }
   if( GridPolarTransformTest() != true )
   {
      cerr << "Grid Log-Polar transform test failed" << endl << flush;
   }
   if( ExtractSubgridTest() != true )
   {
      cerr << "ExtractSubGrid test failed" << endl << flush;
   }
   if( TestGridExtender() != true )
   {
      cerr << "TestGridExtender failed" << endl << flush;
   }

   if( LocalStatisticsTest() != true )
   {
      cerr << "LocalStatisticsTest failed" << endl << flush;
   }

   if( TestGridData() != true )
   {
      cerr << "TestGridData failed" << endl << flush;
   }

   if( GridAverageTest() != true )
   {
      cerr << "TestAverageGrid failed" << endl << flush;
   }
   return 0;
}
