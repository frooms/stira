
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
#include "../tools/GridGenerator.h"
#include "../tools/ImageIO.h"
#include "../color/ColorValue.h"
#include "../color/TransformColorSpace.h"
#include "../tools/NumberGridTools.h"
#include "../tools/ImageTools.h"
#include "../tools/GenerateFractal.h"
#include "../tools/PerlinNoise.h"

using namespace std;
using namespace stira::image;
using namespace stira::common;

void TestVersionOpenCV()
{
   cout << "Open CV version " << CV_MAJOR_VERSION << "." << CV_MINOR_VERSION << endl << flush;
}
//-----------------------------------------------------------------

bool GenerateSyntheticImagesTest()
{
   bool allSuccess = true;

   int width = 256;
   int height = 256;
   double sigma1 = 3.0;
   double sigma2 = 15.0;
   double rho = -0.9;
   double sigma = 7.0;

   ArrayGrid<double>* pGrid = GridGenerator::GenerateHorizontalGradient(512, 128);
   ImageIO::WritePGM(pGrid, string("HorizontalGradient.pgm"), ImageIO::NULL_OUT);
   delete pGrid;

   ArrayGrid<double>* pInvZone = GridGenerator::GenerateInverseZonePlate ( );
   ImageIO::WritePGM(pInvZone, string("InvZonePlate.pgm"), ImageIO::NULL_OUT );
   delete pInvZone;

   ArrayGrid<double>* pZone = GridGenerator::GenerateZonePlate ( );
   ImageIO::WritePGM(pZone, string("ZonePlate.pgm"), ImageIO::NULL_OUT );
   delete pZone;

   ArrayGrid<double>* pSheppLogan = GridGenerator::GenerateSheppLogan ( );
   ImageIO::WritePGM(pSheppLogan, string("SheppLogan.pgm"), ImageIO::NORMAL_OUT );
   delete pSheppLogan;

   ArrayGrid<double>* pLogFrequencyContrast = GridGenerator::GenerateLogFrequencyContrastChart( );
   ImageIO::WritePGM( pLogFrequencyContrast, string("LogFrequencyContrast.pgm"), ImageIO::NORMAL_OUT );
   delete pLogFrequencyContrast;

   int nrPeriods = 85;
   ArrayGrid<double>* pStarChart = GridGenerator::GenerateStarChart( width, nrPeriods );
   ImageIO::WritePGM( pStarChart, string("StarChart.pgm"), ImageIO::NORMAL_OUT );
   delete pStarChart;

   double length = 13.0;
   double angle = 0.4;
   ArrayGrid<double>* pLine = GridGenerator::GenerateLine( width, height, length, angle );
   ImageIO::WritePGM( pLine, string("PSFLine.pgm"), ImageIO::NORMAL_OUT );
   delete pLine;

   ArrayGrid<double>* pSquare = GridGenerator::GenerateSquare( width, height, sigma);
   ImageIO::WritePGM(pSquare, string("PSFSquare.pgm"), ImageIO::NORMAL_OUT );
   delete pSquare;

   ArrayGrid<double>* pDisk = GridGenerator::GenerateDisk( width, height, sigma);
   ImageIO::WritePGM(pDisk, string("PSFDisk.pgm"), ImageIO::NORMAL_OUT );
   delete pDisk;

   ArrayGrid<double>* pAiry = GridGenerator::GenerateAiry( width, height, sigma);
   ImageIO::WritePGM(pAiry, string("Airy.pgm"), ImageIO::NORMAL_OUT );
   delete pAiry;

   ArrayGrid<double>* pGauss =  GridGenerator::GenerateGaussian( width, height, sigma1, sigma2, rho);
   ImageIO::WritePGM( pGauss, string("Gauss.pgm"), ImageIO::NORMAL_OUT );
   delete pGauss;

   ArrayGrid<double>* pGx = GridGenerator::GenerateGaussianFirstDerivativeX( width, height, sigma1, sigma2 );
   ImageIO::WritePGM( pGx, string("Gx.pgm"), ImageIO::GRADIENT_OUT );
   ImageIO::WriteTXT( pGx, string("Gx.txt") );
   delete pGx;

   ArrayGrid<double>* pGy = GridGenerator::GenerateGaussianFirstDerivativeY( width, height, sigma1, sigma2 );
   ImageIO::WritePGM( pGy, string("Gy.pgm"), ImageIO::GRADIENT_OUT );
   ImageIO::WriteTXT( pGy, string("Gy.txt") );
   delete pGy;

   ArrayGrid<double>* pGxx = GridGenerator::GenerateGaussianSecondDerivativeX ( width, height, sigma1, sigma2 );
   ImageIO::WritePGM( pGxx, string("Gxx.pgm"), ImageIO::NORMAL_OUT );
   ImageIO::WriteTXT( pGxx, string("Gxx.txt") );
   delete pGxx;

   ArrayGrid<double>* pGyy = GridGenerator::GenerateGaussianSecondDerivativeY ( width, height, sigma1, sigma2 );
   ImageIO::WritePGM( pGyy, string("Gyy.pgm"), ImageIO::NORMAL_OUT );
   ImageIO::WriteTXT( pGyy, string("Gyy.txt") );
   delete pGyy;

   ArrayGrid<double>* pGxy = GridGenerator::GenerateGaussianMixedDerivativesXY ( width, height, sigma1, sigma2 );
   ImageIO::WritePGM(pGxy, string("Gxy.pgm"), ImageIO::NORMAL_OUT );
   delete pGxy;

   ArrayGrid<double>* pBars = GridGenerator::GenerateBars( width, height, 20 );
   ImageIO::WritePGM( pBars, string("Bars.pgm"), ImageIO::NORMAL_OUT );
   delete pBars;

   float persistence = 0.8;
   int octaves = 7;
   float red   = 1.5;
   float green = 1.0;
   float blue  = 2.0;
   int seed = 0;
   float zoom = 75;
   PerlinNoise pn;
   Image* pData = pn.Generate( persistence, octaves, width, height, red, green, blue, seed, zoom );
   ImageIO::Write( pData, std::string("PerlinColor.ppm") );
   delete pData;

   //ArrayGrid<int>* pIsing = GridGenerator::GenerateIsingTexture( );
   //ImageIO::WritePGM(pGx, string("Ising.pgm"), ImageIO::GRADIENT_OUT );
   //delete pIsing;

   return allSuccess;
}

//========================================================================================

bool ImageIOTest()
{
   //PGM test
   //////////
   Image* pImg = 0;
   std::string pgmName = string("../../../../stira/stira/testdata/lena256.pgm");
   pImg = ImageIO::Read( pgmName );

   if( pImg == 0 )                      { return false;}
   if( pImg->GetNumberOfBands() != 1 )  { delete pImg; return false;}
   if( pImg->GetWidth() != 256 )        { delete pImg; return false;}
   if( pImg->GetHeight() != 256 )       { delete pImg; return false;}

   if( ImageIO::Write( pImg, string("PGMWriteTest.pgm") ) != true )   {delete pImg; return false;}
   delete pImg;
   cout << "IomageIO PGM IO OK!!" << endl << flush;

   //PPM test
   //////////
   pImg = 0;
   std::string ppmName = string("../../../../stira/stira/testdata/Lenna.ppm");
   pImg = ImageIO::Read( ppmName );

   if( pImg == 0 )                        { return false;}
   if( pImg->GetNumberOfBands() != 3 )    { delete pImg; return false;}
   if( pImg->GetWidth() != 512 )          { delete pImg; return false;}
   if( pImg->GetHeight() != 512 )         { delete pImg; return false;}

   if(ImageIO::Write( pImg, string("PPMWriteTest.pgm") ) != true)   {delete pImg; return false;}
   delete pImg;
   cout << "IomageIO PPM IO OK!!" << endl << flush;

   //OpenCV test
   /////////////
   pImg = 0;
   int expectedWidth  = 956;
   int expectedHeight = 307;
   std::string openCvName = string("../../../../stira/stira/testdata/stitch.tif");
   pImg = ImageIO::ReadImageOpenCV( openCvName );

   if( pImg == 0 )                       { return false;}
   cout << "pImg->GetNumberOfBands()  = " << pImg->GetNumberOfBands() << endl << flush;
   cout << "pImg->GetWidth() = " << pImg->GetWidth() << endl << flush;
   cout << "pImg->GetHeight() = " << pImg->GetHeight() << endl << flush;

   if( pImg->GetWidth() != expectedWidth )
   {
      delete pImg;
      cerr << "ERROR: Image width is " << pImg->GetWidth() << ", while we expected " << expectedWidth << " !!" << endl << flush;
      return false;
   }
   if( pImg->GetHeight() != expectedHeight )
   {
      delete pImg;
      cerr << "ERROR: Image height is " << pImg->GetHeight() << ", while we expected " << expectedHeight << " !!" << endl << flush;
      return false;
   }

   if( ImageIO::Write( pImg, string("OpenCvWriteTest.ppm") ) != true)
   {
      delete pImg;
      cerr << "ERROR: writing image as PPM using native function failed!!" << endl << flush;
      return false;
   }

   if( ImageIO::WriteOpenCV( pImg, string("OpenCvWriteTest.jpg") ) != true)
   {
      delete pImg;
      cerr << "ERROR: writing image as JPG using OpenCV failed!!" << endl << flush;
      return false;
   }

   if( ImageIO::WriteOpenCV( pImg, string("OpenCvWriteTest.png") ) != true)
   {
      delete pImg;
      cerr << "ERROR: writing image as PNG using OpenCV failed!!" << endl << flush;
      return false;
   }
   else
   {
      delete pImg;
      cout << "OpenCv IO success!!" << endl << flush;
      return true;
   }
}

//========================================================================================

/*bool ReadPgmFromZipFileTest()
{
   std::string zipName = std::string("/u/frooms/research/develop/stira-env/stira/testdata/testZipFile.zip");

   std::string imageInZipName = std::string("CropOrig-2033.pgm");

   ArrayGrid<int>* pGrid = ImageIO::ReadPGMfromZip( zipName, imageInZipName );

   cout << "Image from zip: width = " << pGrid->GetWidth() << " height = " << pGrid->GetHeight() << endl << flush;

   ImageIO::WritePGM( pGrid, std::string("ImageFromZip.pgm") );
   delete pGrid;
   return true;
}*/

//========================================================================================

bool ImageOpenCvTest()
{
   Image *pImage1 = ImageIO::Read( string("../../../../stira/stira/testdata/buildings_small.jpg") );
   IplImage* pIplImage1 = ImageIO::ConvertImageToOpenCv( pImage1 );
   cvSaveImage( "StiraToOpenCvImage.jpg", pIplImage1 );

   IplImage* pIplImage2 = cvLoadImage( "../../../../stira/stira/testdata/LindbloomColorChecker.jpg" );
   Image* pImage2 = ImageIO::ConvertOpenCvToImage( pIplImage2 );

   ImageIO::Write( pImage2, string("OpenCvToStiraImage.ppm") );

   cvReleaseImage( &pIplImage2 );
   cvReleaseImage( &pIplImage2 );

   delete pImage1;
   delete pImage2;
   return true;
}

//========================================================================================

bool MirrorCropTest(Image* pInImage)
{
   int borderWidth = 20;
   int borderHeight = 80;

   // add border to image
   Image* pImExpanded = ImageTools::MirrorBorder( pInImage, borderWidth, borderHeight);

   ImageIO::Write( pImExpanded, string("ExpandedImage.ppm"), ImageIO::NORMAL_OUT );

   // crop the previously added border again from image
   Image* pImCropped = ImageTools::CropBorder( pImExpanded, borderWidth, borderHeight);
   if (pImExpanded != 0) {delete pImExpanded;}

   ImageIO::Write( pImCropped, string("CroppedImage.ppm"), ImageIO::NORMAL_OUT );

   // verify that adding border and removing it again results in identical copy of original image
   Image* pDiffImage = ImageTools::CreateImageSSD( pImCropped, pInImage );
   ImageIO::Write( pDiffImage, string("CompareImage.ppm"), ImageIO::NORMAL_OUT );

   // clean up...
   if (pDiffImage != 0) {delete pDiffImage;}
   if (pImCropped != 0) {delete pImCropped;}
   return true;
}

//========================================================================================

bool RotateTest(Image* pInImage)
{
   // rotate 90 degrees
   Image* pImage090 = ImageTools::Rotate90DegreesClockwise( pInImage );
   ImageIO::Write( pImage090, string("Image090.ppm"), ImageIO::NORMAL_OUT );
   delete pImage090;

   // rotate 180 degrees
   Image* pImage180 = ImageTools::Rotate180Degrees( pInImage );
   ImageIO::Write( pImage180, string("Image180.ppm"), ImageIO::NORMAL_OUT );
   delete pImage180;

   // rotate 270 degrees
   Image* pImage270 = ImageTools::Rotate90DegreesClockwise( pInImage );
   ImageIO::Write( pImage270, string("Image270.ppm"), ImageIO::NORMAL_OUT );
   delete pImage270;

   return true;
}

//========================================================================================

bool ExtractROITest(Image* pInImage)
{
   Point<int> topLeft( 20, 43 );
   Point<int> bottomRight( 227, 131 );

   Image* pImROI = ImageTools::ExtractSubImage( pInImage, topLeft, bottomRight);

   ImageIO::Write( pImROI, string("ExtractedROIImage.ppm"), ImageIO::NULL_OUT );

   ImageIO::WriteTXT( pImROI->GetBands()[0], string("ExtractedROIImage.txt") );
   delete pImROI;
   return true;
}

//========================================================================================

bool AddGaussianNoiseTest(Image* pInImage)
{
   double sigma = 4.0;
   Image* pCopyInputImage = pInImage->Clone();
   pInImage->AddGaussianNoise( sigma );

   ArrayGrid<double>* pSSIMGrid = NumberGridTools<double>::ComputeSSIM(pCopyInputImage->GetBands()[0],  pInImage->GetBands()[0], 9 );

   ImageIO::WritePGM( (ArrayGrid<double>*)(pSSIMGrid), string("SSIM-Grid.pgm"), ImageIO::NORMAL_OUT );

   ImageIO::Write( pInImage, string("GaussianNoise.ppm"), ImageIO::NORMAL_OUT );
   delete pSSIMGrid;
   delete pCopyInputImage;
   return true;
}

//========================================================================================

bool SepiaToneTest(Image* pInImage)
{
   int width = pInImage->GetWidth();
   int height = pInImage->GetHeight();
   int nrBands = pInImage->GetNumberOfBands();

   if (nrBands == 3)
   {
      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x++)
         {
            ColorValue rgbValue = pInImage->GetColor( x, y );
            pInImage->SetColor( x, y, TransformColorSpace::RGBToSepia( TransformColorSpace::RGBToSepia2( rgbValue ) ) );
         }
      }
   }

   // important to take NULL_OUT instead of NORMAL_OUT!! Result would become gray instead of sepia otherwise
   ImageIO::Write( pInImage, string("SepiaImage.ppm"), ImageIO::NULL_OUT );
   return true;
}

//========================================================================================

bool GenerateFractalTest()
{
   GenerateFractal gf;
   double topX = 0.8;
   double topY = 1.15;
   double bottomX = -2.1;
   double bottomY = -1.15;
   double resolution = 500.0;

   /*double topX = -1.749995;
   double topY = 0.000000001;
   double bottomX = -1.749995001;
   double bottomY = -0.000000001;
   double resolution = 500000000000.0;*/
   /*double topX = -1.74;
   double topY = 0.01;
   double bottomX = -1.75;
   double bottomY = -0.01;
   double resolution = 50000.0;*/

   Image* pFractal = 0;

   pFractal = gf.CreateMandelbrot( topX, topY, bottomX, bottomY, resolution );
   ImageIO::Write( pFractal, string("FractalMandelbrotImage.ppm"), ImageIO::NULL_OUT );
   delete pFractal;

   topX = 2.0;
   topY = 1.0;
   bottomX = -2.0;
   bottomY = -1.0;
   resolution = 500.0;
   //double Cx = -0.79;
   //double Cy = 0.15;
   double Cx = -0.162;
   double Cy = 1.04;
   pFractal = gf.CreateJulia( topX, topY, bottomX, bottomY, resolution, Cx, Cy );
   ImageIO::Write( pFractal, string("FractalJuliaImage.ppm"), ImageIO::NULL_OUT );
   delete pFractal;
   return true;
}

//========================================================================================

bool ColorMapTest()
{
   ArrayGrid<double>* pGrid = (ArrayGrid<double>*)(GridGenerator::GenerateHorizontalGradient());
   ImageIO::WritePGM(pGrid, string("Gradient.pgm"), ImageIO::NULL_OUT);

   Image* pJet = new Image(pGrid);
   Image* pImg = ImageTools::ApplyJetColorMap( pJet );
   ImageIO::Write( pImg, std::string("ImageJet.ppm") );
   delete pJet;
   delete pImg;
   return true;
}

//========================================================================================

int main(int argc, char *argv[])
{
   const char* fileName;
   int nrTestsTotal = 0;
   int nrTestsSucceeded = 0;
   if (argc == 2)
   {
      fileName = argv[1];
   }
   else
   {
      fileName = "../../../../stira/stira/testdata/lena256.pgm";
   }
   Image* pInImage = ImageIO::Read( fileName );

   // 0) Generate synthetic test images test
   /////////////////////////////////////////
   cout << "GenerateSyntheticImagesTest:";
   nrTestsTotal ++;
   if ( GenerateSyntheticImagesTest() )
   {
      nrTestsSucceeded ++;
      cout << " \t OK!" << endl << flush;
   }
   else
   {
      cout << " \t FAILED!" << endl << flush;
   }

   // 1) Image input / output test
   ///////////////////////////////
   cout << "ImageIOTest:";
   nrTestsTotal ++;
   if ( ImageIOTest() )
   {
      nrTestsSucceeded ++;
      cout << " \t OK!" << endl << flush;
   }
   else
   {
      cout << " \t FAILED!" << endl << flush;
   }

   cout << "ImageOpenCvTest:";
   nrTestsTotal ++;
   if ( ImageOpenCvTest() )
   {
      nrTestsSucceeded ++;
      cout << " \t OK!" << endl << flush;
   }
   else
   {
      cout << " \t FAILED!" << endl << flush;
   }

    // 2) Extract ROI test
   ///////////////////////
   cout << "ExtractROITest:";
   nrTestsTotal ++;
   if ( ExtractROITest( pInImage ) )
   {
      nrTestsSucceeded ++;
      cout << " \t OK!" << endl << flush;
   }
   else
   {
      cout << " \t FAILED!" << endl << flush;
   }

   // 3) add / remove extra border test
   ////////////////////////////////////
   cout << "MirrorCropTest:";
   nrTestsTotal ++;
   if ( MirrorCropTest( pInImage ) )
   {
      nrTestsSucceeded ++;
      cout << " \t OK!" << endl << flush;
   }
   else
   {
      cout << " \t FAILED!" << endl << flush;
   }

   // 4) add gaussian noise test
   /////////////////////////////
   cout << "AddGaussianNoiseTest:";
   nrTestsTotal ++;
   if ( AddGaussianNoiseTest( pInImage ) )
   {
      nrTestsSucceeded ++;
      cout << " \t OK!" << endl << flush;
   }
   else
   {
      cout << " \t FAILED!" << endl << flush;
   }

   // 5) Map image to jet color map
   ////////////////////////////////
   cout << "ColorMapTest:";
   nrTestsTotal ++;
   if ( ColorMapTest( ) )
   {
      nrTestsSucceeded ++;
      cout << " \t OK!" << endl << flush;
   }
   else
   {
      cout << " \t FAILED!" << endl << flush;
   }

   // 6) Rotate image
   //////////////////
   cout << "RotateTest:";
   nrTestsTotal ++;
   if ( RotateTest( pInImage ) )
   {
      nrTestsSucceeded ++;
      cout << " \t OK!" << endl << flush;
   }
   else
   {
      cout << " \t FAILED!" << endl << flush;
   }

   //nrTestsTotal ++;
   SepiaToneTest( pInImage );

   // EXPERIMENTAL...
   //////////////////

   //nrTestsTotal ++;
   GenerateFractalTest();

   cout << " SUMMARY: " << nrTestsSucceeded << "/" << nrTestsTotal << " succeeded." << endl;
   delete pInImage;
   return EXIT_SUCCESS;
}
