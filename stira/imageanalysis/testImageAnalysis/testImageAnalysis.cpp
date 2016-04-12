
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

#include "../../common/common/StringUtils.h"
#include "../../image/tools/ImageIO.h"
#include "../../image/tools/NumberGridTools.h"
#include "../../image/tools/GridConverter.h"
#include "../../image/tools/DrawImageTools.h"
#include "../../image/tools/ImageTools.h"
#include "../../histogram/histogram/IntHistogram.h"
#include "../../histogram/histogram/FloatHistogram.h"
#include "../../histogram/histogram/RunLengthHistogram.h"
#include "../../filter/filter/NonSeparableFilter.h"
#include "../imageanalysis/CannyEdgeDetector.h"
#include "../imageanalysis/DistanceTransform.h"
#include "../imageanalysis/WatershedToboggan.h"
#include "../imageanalysis/WatershedMeyer.h"
#include "../imageanalysis/StegerLineDetector.h"
#include "../imageanalysis/FloodFill.h"
#include "../imageanalysis/ContourTracing.h"
#include "../imageanalysis/Thinning.h"
#include "../imageanalysis/SLIC.h"
#include "../imageanalysis/HOG.h"
#include "../imageanalysis/FunctionsOpenCV.h"
#include "../imageanalysis/CompareCurvesInImage.h"
#include "../imageanalysis/FindMaximalIncludedRectangles.h"


using namespace std;
using namespace stira;
using namespace stira::common;
using namespace stira::image;
using namespace stira::histogram;
using namespace stira::imageanalysis;

void TestWSMeyer( Image *pImage )
{
   ArrayGrid<int>* pGridIn = NumberGridTools<double>::CreateIntGrid( pImage->GetBands()[0] );
   // Create the watershed transformation
   WatershedMeyer< int > wm;

   // Execute the transformation
   wm.Run( pGridIn, true );

   // Test some of the getters
   cout << "\t << NLabels " << (int)(wm.GetNumberOfLabels()) << endl << flush;
   cout << "\t << Watershed Pixels " << (int)(wm.GetNumberOfWatershedPixels()) << endl << flush;

   ArrayGrid<bool>* pWatershedGrid = wm.GetWatershedGrid(); // creates boolean grid fro vector of watershed pixel elements
   ImageIO::WritePGM( pWatershedGrid, std::string("WatershedMeyerRidges.ppm") );
   delete pWatershedGrid;

   ArrayGrid<int>* pLabelImage = (wm.GetLabelImage())->Clone();
   ImageIO::WritePGM( pLabelImage, std::string("WatershedMeyerLabels.ppm") );
   delete pLabelImage;

   Image* pSegmented = wm.CreateLabelsRidgeImage();
   ImageIO::Write( pSegmented, std::string("WatershedMeyerLabelsRidges.ppm") );
   delete pSegmented;

   pSegmented = wm.CreateLabelsIntensitiesImage();
   ImageIO::Write( pSegmented, std::string("WatershedMeyerRidgesImage.ppm") );
   delete pSegmented;
   delete pGridIn;
}

//-----------------------------------------------------------------------------------

void TestDistanceTransform()
{
    std::string filename = string("../../testdata/contours2.png");
    Image *pImage = ImageIO::Read(filename);
    DistanceTransform* pDT = new DistanceTransform();
    ArrayGrid<double>* pResult = pDT->Run( pImage->GetBands()[0] );

    ImageIO::WritePGM( pResult, "DistanceTransform.pgm", ImageIO::NORMAL_OUT );
}

//-----------------------------------------------------------------------------------

void TestHOG( Image *pImage )
{
    int nrBins = 9;
    int cellWidth = 8;
    int cellHeight = 8;
    double viz_factor = 3;
    double scaleFactor = 1.0;

    std::vector<double> descriptorValues;
    ofstream myfile;
    myfile.open ("HogSelf.txt");

    common::RectangularROI<int> myRoi;
    HOG myHOG( pImage, myRoi, cellWidth, cellHeight, nrBins);

    myHOG.ComputeHogDescriptor( descriptorValues );

    for (unsigned int i = 0; i < descriptorValues.size(); i++)
    {
        myfile << descriptorValues[i] << std::endl;
    }
    myfile.close();

    std::cout << "After computation of descriptor, " << descriptorValues.size() << std::endl;

    image::Image* pVisual = myHOG.VisualizeHogDescriptor( descriptorValues,
                                                          pImage->GetWidth(), pImage->GetHeight(),
                                                          scaleFactor, viz_factor);

    ImageIO::Write(pVisual, "HogOut.ppm");
}

//-----------------------------------------------------------------------------------

void TestSLIC( Image *pImage )
{
    unsigned int* img = 0; //Each 32 bit unsigned int encodes the combination of ARGB values for a single pixel.
    int nrSiperPixels = 200;
    double superPixelSize = 10.0;

    int width = pImage->GetWidth();
    int height = pImage->GetHeight();

    img = ImageTools::CreateIntArrayFromColorImage( pImage );

    int imgSize = width*height;
    //---------------------------------------------------------
    if(nrSiperPixels < 20 || nrSiperPixels > imgSize/4) nrSiperPixels = imgSize/200;//i.e the default size of the superpixel is 200 pixels
    if(superPixelSize < 1.0 || superPixelSize > 80.0) superPixelSize = 20.0;
    //---------------------------------------------------------
    int* labels = new int[imgSize];
    int numlabels(0);

    SLIC slic;
    //slic.DoSuperpixelSegmentation_ForGivenNumberOfSuperpixels( img, width, height, labels, numlabels, m_spcount, m_compactness);
    slic.DoSuperpixelSegmentation_ForGivenSuperpixelSize(img, width, height, labels, numlabels, 100, superPixelSize);//demo
    slic.DrawContoursAroundSegments(img, labels, width, height, 0);
    if(labels) delete [] labels;

    Image* pImageOut = ImageTools::CreateColorImageFromIntArray( img, width, height );
    ImageIO::Write( pImageOut, "SlicTest.pgm");

    if(img) delete [] img;
    delete pImageOut;
}

//-----------------------------------------------------------------------------------

void TestContourTrace( )
{
   std::string filename = string("../../testdata/testLines.ppm");

   Image *pImage = ImageIO::Read( filename );

   double alphaStraight = 0.975;
   double alphaNotStraight = 0.5;

   ContourTracing* pCtSum = new ContourTracing( alphaStraight, alphaNotStraight, std::string("./") );
   std::pair< ArrayGrid<double>*, ArrayGrid<double>* > gridPair = pCtSum->Run( pImage->GetBands()[0] );

   Image* pOutImage = new Image( gridPair.first->GetWidth(), gridPair.first->GetHeight() );
   ArrayGrid<double>* pGridNull = new ArrayGrid<double>( gridPair.first->GetWidth(), gridPair.first->GetHeight() );
   pOutImage->AddBand( gridPair.first );
   pOutImage->AddBand( gridPair.second );
   pOutImage->AddBand( pGridNull );

   ImageIO::Write( pOutImage, std::string("ContourTracingSumTest.ppm"), ImageIO::NORMAL_OUT );

   // CLEAN

   delete pCtSum;
   delete pImage;
}

//-----------------------------------------------------------------------------------

void TestThinning( )
{
   std::string filename = string("../../testdata/thinningTestPattern.png");
   Image *pImage = ImageIO::Read( filename );

   int width  = pImage->GetBands()[0]->GetWidth();
   int height = pImage->GetBands()[0]->GetHeight();

   int minX = 10;
   int minY = 15;
   int maxX = width - 15;
   int maxY = height - 1;
   RectangularROI<int> rroi( minX, minY, maxX, maxY );

   Thinning<double> t;
   ArrayGrid<double>* pThinnedGrid = t.RunThinning( pImage->GetBands()[0], rroi, 255.0 );
   ImageIO::WritePGM( pThinnedGrid, std::string("ThinnedGrid.pgm"), ImageIO::NORMAL_OUT );

   delete pImage;
   delete pThinnedGrid;
}

//-----------------------------------------------------------------------------------

void TestFindMaximalIncludedRectangles( )
{
   std::string filename1 = string("../../testdata/Spatial3.png");
   Image *pImage = ImageIO::Read( filename1 );

   double thresholdHigh = 200;

   ArrayGrid<bool>* pBoolGridHigh = NumberGridTools<double>::BinaryThreshold( pImage->GetBands()[0], thresholdHigh );

   std::vector< common::RectangularROI<int> > listOfRectangles1 = FindMaximalIncludedRectangles::Run( pBoolGridHigh );
   int listLength1 = listOfRectangles1.size();
   delete pBoolGridHigh;
   cout << " In Spatial3 threshold 200" << endl << flush;
   cout << " =========================" << endl << flush;
   for (int i = 0; i < listLength1; i++)
   {
      cout << " Rectangle " << i << " from " << listOfRectangles1[i].GetTopLeftCorner()
                                   << " to " << listOfRectangles1[i].GetBottomRightCorner()
           << " has width " << listOfRectangles1[i].GetWidth() << " and height " <<  listOfRectangles1[i].GetHeight()
           << ", so area "  << listOfRectangles1[i].GetWidth() *  listOfRectangles1[i].GetHeight() << endl;
   }
   IntHistogram ih1 = FindMaximalIncludedRectangles::CreateRectangleHistogram( listOfRectangles1 );
   ih1.Write( std::string("ThresholdHighCumulativeHistogram.txt") );

   //---------------------------------------------------------------------------------

   double thresholdLow = 100;
   ArrayGrid<bool>* pBoolGridLow = NumberGridTools<double>::BinaryThreshold( pImage->GetBands()[0], thresholdLow );

   std::vector< common::RectangularROI<int> > listOfRectangles2 = FindMaximalIncludedRectangles::Run( pBoolGridLow );
   int listLength2 = listOfRectangles2.size();
   delete pBoolGridLow;
   cout << " In Spatial3 threshold 100" << endl << flush;
   cout << " =========================" << endl << flush;
   for (int i = 0; i < listLength2; i++)
   {
      cout << " Rectangle " << i << " from " << listOfRectangles2[i].GetTopLeftCorner()
                                   << " to " << listOfRectangles2[i].GetBottomRightCorner()
           << " has width " << listOfRectangles2[i].GetWidth() << " and height " <<  listOfRectangles2[i].GetHeight()
           << ", so area " << listOfRectangles2[i].GetWidth() *  listOfRectangles2[i].GetHeight() << endl;
   }
   IntHistogram ih2 = FindMaximalIncludedRectangles::CreateRectangleHistogram( listOfRectangles2 );
   ih2.Write( std::string("ThresholdHighCumulativeHistogram.txt") );
}

//-----------------------------------------------------------------------------------

void TestFloodFill()
{
   std::string filename = string("../../testdata/binary.pgm");
   Image *pImage = ImageIO::Read( filename );
   int width  = pImage->GetWidth();
   int height = pImage->GetHeight();
   ArrayGrid<bool>* pGridBool = new ArrayGrid<bool>( width, height );
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         pGridBool->SetValue(x, y, (pImage->GetBands()[0]->GetValue(x, y) > 200) );
      }
   }
   ImageIO::WritePGM( pGridBool, std::string("TestOut.pgm") );
   ArrayGrid<int>* pGridInt = GridConverter::ConvertToInt( pGridBool );
   FloodFill ff;

   int pixelsFlooded = ff.Run( pGridInt, 260, 270, 255, 128 );
   cout << "Nr of connected pixels that were flooded: " << pixelsFlooded << endl << flush;

   Point<double> cg = ff.GetCenterOfGravity();
   pGridInt->SetValue(cg.x, cg.y, 0);
   cout << "Center of region that was flooded: ( " << cg.x << ", " << cg.y << " )." << endl << flush;

   ImageIO::WritePGM( pGridInt, std::string("FillTestOut.pgm") );

   delete pImage;
   delete pGridBool;
}

//-----------------------------------------------------------------------------------


int main(int argc, char *argv[])
{
   Image* pImage = 0;
   double sigmaSmooth;

   const char* inputname;

   if (argc == 2)
   {
      inputname = argv[1];
      sigmaSmooth    = 2.0;
   }
   else
   {
      inputname = "../../testdata/Lenna.ppm";
      //inputname = "../../testdata/TestSparse2.ppm";
      //inputname = "../../testdata/ZonePlate.ppm";
      sigmaSmooth    = 1.0;
   }
   cout << "Running test with input image " << inputname << " sigmaSmooth = " << sigmaSmooth << endl << flush;
   pImage = ImageIO::Read( inputname );

   /////////////////////////////////////////////////////
   // CONTOUR TRACING
   TestContourTrace( );

   /////////////////////////////////////////////////////
   // CANNY
   cout << "Canny Test " << endl << flush;
   double loThreshold = 30.0;
   double hiThreshold = 80.0;
   ArrayGrid<bool>* pEdgeGrid = CannyEdgeDetector::Run( pImage->GetBands()[0], sigmaSmooth, loThreshold, hiThreshold );
   ImageIO::WritePGM( pEdgeGrid, string("CannyOut.pgm") );
   delete pEdgeGrid;

   /////////////////////////////////////////////////////
   // SLIC
   TestSLIC( pImage );

   /////////////////////////////////////////////////////
   // HOG: Histogram of Oriented Gradients
   TestHOG( pImage );

   /////////////////////////////////////////////////////
   // WATERSHED

   cout << "Waterhed Toboggan Test " << endl << flush;
   WatershedToboggan wt;
   ArrayGrid<int>* pTobLabelGrid = wt.Run( pImage->GetBands()[0] );
   ImageIO::WritePGM( pTobLabelGrid, string("WatershedToboggan.pgm"), ImageIO::NORMAL_OUT);
   delete pTobLabelGrid;

   cout << "Waterhed Meyer Test " << endl << flush;
   TestWSMeyer( pImage );

   /////////////////////////////////////////////////////
   // STEGER
   double lowerThreshold = 0.2;
   double upperThreshold = 0.9;

   cout << "Steger Line detector Test " << endl << flush;
   StegerLineDetector sld;
   ArrayGrid<bool>* pLineGrid = sld.Run( pImage->GetBands()[0], sigmaSmooth, lowerThreshold, upperThreshold, false );
   ImageIO::WritePGM( pLineGrid, std::string("StegerLinePoints.pgm") );
   delete pLineGrid;

   /////////////////////////////////////////////////////
   // THINNING
   TestThinning( );

   TestDistanceTransform( );

   /////////////////////////////////////////////////////
   // FIND MAXIMAL INCLUDED RECTANGLES
   //TestFindMaximalIncludedRectangles( );

   /////////////////////////////////////////////////////
   // FLOODFILL

   cout << "Floodfill Test " << endl << flush;
   TestFloodFill();

   delete pImage;
}
