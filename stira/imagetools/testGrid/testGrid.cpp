
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
#include "../../common/common/DrawFigures.h"
#include "../../common/common/ClusteringLearning.h"
#include "../../common/common/FitCurve.h"
#include "../../imagedata/simpletools/ArrayGridTools.h"
#include "../../imagedata/simpletools/GridExtender.h"
#include "../imagegenerator/GridGenerator.h"
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
   Image* pImage = ImageIO::Read( std::string("../../../../stira/stira/testdata/lena256.pgm") );
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
   Image* pImage = ImageIO::Read( std::string("../../../../stira/stira/testdata/mandril.pgm") );

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
   Image* pImage = ImageIO::Read( std::string("../../../../stira/stira/testdata/mandril.pgm") );
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
   GridStatistics<double>::GetMinMax( &grid, mmin, mmax, xMin, yMin, xMax, yMax );

   assert ( mmin == -122.0 );
   assert ( mmax ==   96.0 );
   assert ( mmin == grid(  0, 122 ) );
   assert ( mmax == grid( 96, 0   ) );

   grid.MultiplyWith( -3.0 );
   GridStatistics<double>::GetMin( &grid, mmin, xMin, yMin );

   assert ( mmin == -288.0 );
   assert ( mmin == grid(96, 0) );

   GridStatistics<double>::GetMax( &grid, mmax, xMax, yMax );

   assert ( mmax == 366.0 );
   assert ( mmax == grid( 0, 122 ) );

   grid.MultiplyWith( -2.0 );
   GridStatistics<double>::GetMin( &grid, mmin, xMin, yMin );

   assert ( mmin == -732.0 );
   assert ( mmin == grid( 0, 122 ) );

   GridStatistics<double>::GetMax( &grid, mmax, xMax, yMax );

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

   double localMean0 = GridStatistics<double>::ComputeLocalMean( &grid, xTopLeft, yTopLeft, xBottomRight, yBottomRight );

   assert ( fabs( localMean0 - 115.0 ) < 0.01 );

   x = 90;
   y = 117;
   xTopLeft = x - localHalfWidth;
   yTopLeft = y - localHalfHeight;
   xBottomRight = x + localHalfWidth;
   yBottomRight = y + localHalfHeight;

   double localMin = GridStatistics<double>::GetLocalMinimum( &grid, x, y, localWidth, localHeight );
   double localMax = GridStatistics<double>::GetLocalMaximum( &grid, x, y, localWidth, localHeight );
   double localAbsMax = GridStatistics<double>::GetLocalAbsMaximum( &grid, x, y, localWidth, localHeight );

   double localMean1 = GridStatistics<double>::ComputeLocalMean( &grid, xTopLeft, yTopLeft, xBottomRight, yBottomRight );

   assert ( fabs( localMean1  - 207.0 ) < 0.01 );
   assert ( fabs( localMin    - 204.0 ) < 0.01 );
   assert ( fabs( localMax    - 210.0 ) < 0.01 );
   assert ( fabs( localAbsMax - 210.0 ) < 0.01 );

   double localAbsMean = GridStatistics<double>::ComputeLocalAbsoluteMean( &grid, xTopLeft, yTopLeft, xBottomRight, yBottomRight );

   assert ( fabs( localAbsMean - 207.0 ) < 0.01 );

   double localVariance1 = GridStatistics<double>::ComputeLocalVariance( &grid, xTopLeft, yTopLeft, xBottomRight, yBottomRight, localMean1 );
   double localVariance2 = GridStatistics<double>::ComputeLocalVariance( &grid, xTopLeft, yTopLeft, xBottomRight, yBottomRight );

   assert ( fabs( localVariance1 - localVariance2 ) < 0.01 );

   return true;
}

//--------------------------------------------------------------------

// from http://docs.opencv.org/3.1.0/d1/dee/tutorial_introduction_to_pca.html
bool TestOrientationPCA()
{
    vector< stira::common::Point<double> > pts;
    /* initialize random seed: */
    srand (time(NULL));

    int nrPointsCurrent = 0;
    int nrPointsMax = 500;

    //image to visualize result
    Image* pImageVisualizePCA = new Image(512, 512, 3);

    while (nrPointsCurrent < nrPointsMax)
    {
          double x = 512 * (double)(rand()) / ((double)RAND_MAX);
          double y = 512 * (double)(rand()) / ((double)RAND_MAX);

          if ( DrawFigures::IsInsideEllipse(x, y, 256, 256, 200, 50, M_PI / 4) )
          {
              pts.push_back( Point<double>( x, y ) );
              DrawImageTools::DrawCircle(pImageVisualizePCA, Point<int>(x,y), 1, ColorValue(255,255,255));
              nrPointsCurrent++;
          }
    }

    ClusteringLearning cl( pts );
    PcaResult pcaRes = cl.ComputePCA();

    cout << "PCA center = ( " << pcaRes.center.x << ", " << pcaRes.center.y << " )" << endl;
    cout << "       eigen vector 1 = (" <<  pcaRes.vector[0].x  << ", " <<  pcaRes.vector[0].y << ")  value = " << pcaRes.eigenValue[0] << endl;
    cout << "       eigen vector 2 = (" <<  pcaRes.vector[1].x  << ", " <<  pcaRes.vector[1].y << ")  value = " << pcaRes.eigenValue[1] << endl;

    // Draw the principal components
    DrawImageTools::DrawDisk(pImageVisualizePCA, Point<int>(pcaRes.center.x, pcaRes.center.y ), 3, ColorValue(255,0,255));

    Point<int> pp1 = ( pcaRes.center + 0.02 * pcaRes.vector[0] * pcaRes.eigenValue[0] ).ToInt();
    Point<int> pp2 = ( pcaRes.center - 0.02 * pcaRes.vector[1] * pcaRes.eigenValue[1] ).ToInt();

    DrawImageTools::DrawArrow(pImageVisualizePCA, pcaRes.center.ToInt(), pp1, ColorValue(0, 255, 0), 1);
    DrawImageTools::DrawArrow(pImageVisualizePCA, pcaRes.center.ToInt(), pp2, ColorValue(255, 0, 0), 5);

    double angle = atan2( pcaRes.vector[0].y,  pcaRes.vector[0].x); // orientation in radians
    cout << "       angle = " << angle << endl;
    ImageIO::Write(pImageVisualizePCA, "VisualizePCA.png");
    return true;
}

//--------------------------------------------------------------------

void TestLocalAutoCorrelation()
{
    double gridMin, gridMax;
    int xMin, yMin, xMax, yMax;
    int xCenter, yCenter;
    int localHalfWidth = 7;
    Image* pImageIn = ImageIO::ReadImageOpenCV("../../../../stira/stira/testdata/lena512.pgm");

    // Line
    xCenter = 428;
    yCenter = 92;

    ArrayGrid<double>* pACGridLine = NumberGridTools<double>::ComputeLocalAutoCorrelation(pImageIn->GetBands()[0], xCenter, yCenter, localHalfWidth );
    ImageIO::WriteOpenCV( pACGridLine, std::string("AutoCorrLineGrid.pgm"), ImageIO::NORMAL_OUT );
    GridStatistics<double>::GetMinMax( pACGridLine, gridMin, gridMax, xMin, yMin, xMax, yMax );
    cout << "Line: AC min = " << gridMin << ", max = " << gridMax << endl;
    delete pACGridLine;

    // Eye
    xCenter = 265;
    yCenter = 265;

    ArrayGrid<double>* pACGridTexture = NumberGridTools<double>::ComputeLocalAutoCorrelation(pImageIn->GetBands()[0], xCenter, yCenter, localHalfWidth );
    ImageIO::WriteOpenCV( pACGridTexture, std::string("AutoCorrEyeGrid.pgm"), ImageIO::NORMAL_OUT );
    GridStatistics<double>::GetMinMax( pACGridTexture, gridMin, gridMax, xMin, yMin, xMax, yMax );
    cout << "Eye: AC min = " << gridMin << ", max = " << gridMax << endl;
    delete pACGridTexture;

    // Smooth
    xCenter = 320;
    yCenter = 460;

    ArrayGrid<double>* pACGridSmooth = NumberGridTools<double>::ComputeLocalAutoCorrelation(pImageIn->GetBands()[0], xCenter, yCenter, localHalfWidth );
    ImageIO::WriteOpenCV( pACGridSmooth, std::string("AutoCorrSmoothGrid.pgm"), ImageIO::NORMAL_OUT );
    GridStatistics<double>::GetMinMax( pACGridSmooth, gridMin, gridMax, xMin, yMin, xMax, yMax );
    cout << "Smooth: AC min = " << gridMin << ", max = " << gridMax << endl;
    delete pACGridSmooth;
}

//--------------------------------------------------------------------

bool TestCircularShiftGrid()
{
    Image* pImageIn = ImageIO::ReadImageOpenCV("../../../../stira/stira/testdata/lena512.pgm");

    ArrayGrid<double>* pGrid = pImageIn->GetBands()[0];

    ArrayGrid<double>* pGridShift = ArrayGridTools<double>::CircularShiftGrid(pGrid, 120, 50);
    ImageIO::WriteOpenCV( pGridShift, std::string("GridShift.pgm"), ImageIO::NORMAL_OUT );
    delete pImageIn;
    delete pGridShift;
    return true;
}

//--------------------------------------------------------------------

bool TestDistanceCriteria()
{
    Image* pImage1 = ImageIO::ReadImageOpenCV("../../../../stira/stira/testdata/test1.png");
    Image* pImage2 = ImageIO::ReadImageOpenCV("../../../../stira/stira/testdata/test1.pgm");
    Image* pImage3 = ImageIO::ReadImageOpenCV("../../../../stira/stira/testdata/test1stretch.pgm");
    Image* pImage4 = ImageIO::ReadImageOpenCV("../../../../stira/stira/testdata/test2.png");

    ArrayGrid<double>* pGrid1 = pImage1->GetBands()[0];   // reference image
    ArrayGrid<double>* pGrid2 = pImage2->GetBands()[0];   // reference image, intensities scaled linearly, should match well in NCC
    ArrayGrid<double>* pGrid3 = pImage3->GetBands()[0];   // shape in reference image stretched, should be bad match
    ArrayGrid<double>* pGrid4 = pImage4->GetBands()[0];   // reference image in which areas are colored differently, should still match well with MI

    double ssd12 = NumberGridTools<double>::ComputeLocalSquaredDifference( pGrid1, 0, 0, 511, 511, pGrid2, 0, 0, 511, 511 );
    double ssd13 = NumberGridTools<double>::ComputeLocalSquaredDifference( pGrid1, 0, 0, 511, 511, pGrid3, 0, 0, 511, 511 );
    double ssd14 = NumberGridTools<double>::ComputeLocalSquaredDifference( pGrid1, 0, 0, 511, 511, pGrid4, 0, 0, 511, 511 );
    double ssd23 = NumberGridTools<double>::ComputeLocalSquaredDifference( pGrid2, 0, 0, 511, 511, pGrid3, 0, 0, 511, 511 );
    double ssd24 = NumberGridTools<double>::ComputeLocalSquaredDifference( pGrid2, 0, 0, 511, 511, pGrid4, 0, 0, 511, 511 );
    double ssd34 = NumberGridTools<double>::ComputeLocalSquaredDifference( pGrid3, 0, 0, 511, 511, pGrid4, 0, 0, 511, 511 );

    std::cout << "ssd12 = " << ssd12 <<std:: endl;
    std::cout << "ssd13 = " << ssd13 <<std:: endl;
    std::cout << "ssd14 = " << ssd14 <<std:: endl;
    std::cout << "ssd23 = " << ssd23 <<std:: endl;
    std::cout << "ssd24 = " << ssd24 <<std:: endl;
    std::cout << "ssd34 = " << ssd34 <<std:: endl;


    double ncc12 = NumberGridTools<double>::ComputeLocalCrossCorrelation( pGrid1, 0, 0, 511, 511, pGrid2, 0, 0, 511, 511 );
    double ncc13 = NumberGridTools<double>::ComputeLocalCrossCorrelation( pGrid1, 0, 0, 511, 511, pGrid3, 0, 0, 511, 511 );
    double ncc14 = NumberGridTools<double>::ComputeLocalCrossCorrelation( pGrid1, 0, 0, 511, 511, pGrid4, 0, 0, 511, 511 );
    double ncc23 = NumberGridTools<double>::ComputeLocalCrossCorrelation( pGrid2, 0, 0, 511, 511, pGrid3, 0, 0, 511, 511 );
    double ncc24 = NumberGridTools<double>::ComputeLocalCrossCorrelation( pGrid2, 0, 0, 511, 511, pGrid4, 0, 0, 511, 511 );
    double ncc34 = NumberGridTools<double>::ComputeLocalCrossCorrelation( pGrid3, 0, 0, 511, 511, pGrid4, 0, 0, 511, 511 );

    std::cout << "ncc12 = " << ncc12 <<std:: endl;
    std::cout << "ncc13 = " << ncc13 <<std:: endl;
    std::cout << "ncc14 = " << ncc14 <<std:: endl;
    std::cout << "ncc23 = " << ncc23 <<std:: endl;
    std::cout << "ncc24 = " << ncc24 <<std:: endl;
    std::cout << "ncc34 = " << ncc34 <<std:: endl;

    double mi12 = NumberGridTools<double>::ComputeLocalMutualInformation( pGrid1, 0, 0, 511, 511, pGrid2, 0, 0, 511, 511 );
    double mi13 = NumberGridTools<double>::ComputeLocalMutualInformation( pGrid1, 0, 0, 511, 511, pGrid3, 0, 0, 511, 511 );
    double mi14 = NumberGridTools<double>::ComputeLocalMutualInformation( pGrid1, 0, 0, 511, 511, pGrid4, 0, 0, 511, 511 );
    double mi23 = NumberGridTools<double>::ComputeLocalMutualInformation( pGrid2, 0, 0, 511, 511, pGrid3, 0, 0, 511, 511 );
    double mi24 = NumberGridTools<double>::ComputeLocalMutualInformation( pGrid2, 0, 0, 511, 511, pGrid4, 0, 0, 511, 511 );
    double mi34 = NumberGridTools<double>::ComputeLocalMutualInformation( pGrid3, 0, 0, 511, 511, pGrid4, 0, 0, 511, 511 );

    std::cout << "mi12 = " << mi12 <<std:: endl;
    std::cout << "mi13 = " << mi13 <<std:: endl;
    std::cout << "mi14 = " << mi14 <<std:: endl;
    std::cout << "mi23 = " << mi23 <<std:: endl;
    std::cout << "mi24 = " << mi24 <<std:: endl;
    std::cout << "mi34 = " << mi34 <<std:: endl;

    delete pImage1;
    delete pImage2;
    delete pImage3;
    delete pImage4;
    return true;
}

//--------------------------------------------------------------------

int main( )
{
   TestLocalAutoCorrelation();
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
   if ( TestDistanceCriteria() != true )
   {
      cerr << "TestDistanceCriteria failed" << endl << flush;
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

   if (TestOrientationPCA() != true )
   {
      cerr << "TestOrientationPCA failed" << endl << flush;
   }

   if (TestCircularShiftGrid() != true )
   {
      cerr << "TestShiftGrid failed" << endl << flush;
   }
   return 0;
}
