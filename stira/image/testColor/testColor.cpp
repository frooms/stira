
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
#include <iomanip>
#include <sstream>
#include <string>

#include <cstdlib>
#include <cassert>
#include "../tools/ImageIO.h"
#include "../color/ColorValue.h"
#include "../color/TransformColorSpace.h"
#include "../tools/NumberGridTools.h"
#include "../tools/GridGenerator.h"
#include "../tools/ImageTools.h"
#include "../color/GretagMacbethColorChecker.h"
#include "../color/ColorBalancer.h"
#include "../color/ChromaticAdaptation.h"
#include "../color/DistinctColorGenerator.h"

#define COLOR_TOLERANCE_THRESHOLD 0.0005

//#define FULL_DIAGNOSE_TEST

using namespace std;
using namespace stira::image;

bool ColorTest()
{
   int width = 30;
   int height = 360;
   Image* pColorTestChart = new Image(width, height, 3);
   TransformColorSpace tcsp;
   for (int theta = 0; theta < 360; theta++)
   {
      ColorValue hsvValue, rgbValue;
      hsvValue.c[0] = (double)(theta);
      hsvValue.c[1] = 1.0;
      hsvValue.c[2] = 1.0;
      hsvValue.type = TYPE_HSV;
      rgbValue = tcsp.HSVtoRGB( hsvValue );
      for (int i = 0; i < width; i++)
      {
         for (int j = 0; j < 3; j++)
         {
            pColorTestChart->GetBands()[j]->SetValue(i, theta, rgbValue.c[j]);
         }
      }
   }
   ImageIO::Write( pColorTestChart, std::string("ColorChart.ppm") );
   delete pColorTestChart;
   return true;
}

//========================================================================================

bool ColorOperatorsTest()
{
   double myValue = 3.1289;

   double c0 =  37;
   double c1 = 123;
   double c2 = 209;

   ColorValue cv1 = ColorValue( c0, c1, c2, TYPE_RGB );
   ColorValue cv2 = cv1;

   assert (cv1 == cv2);

   cv2 = cv1 * myValue;
   for (int i = 0; i < 3; i++)
   {
      assert ( cv2.c[i] == myValue * cv1.c[i] );
   }

   cv2 = cv1 / myValue;
   for (int i = 0; i < 3; i++)
   {
      assert ( cv2.c[i] == cv1.c[i] / myValue );
   }

   cv2 = cv1 + myValue;
   for (int i = 0; i < 3; i++)
   {
      assert ( cv2.c[i] == cv1.c[i] + myValue);
   }

   cv2 = cv1 - myValue;
   for (int i = 0; i < 3; i++)
   {
      assert ( cv2.c[i] == cv1.c[i] - myValue );
   }

   ColorValue cv3 = cv1 * cv2;
   for (int i = 0; i < 3; i++)
   {
      assert ( cv3.c[i] == cv1.c[i] * cv2.c[i] );
   }

   cv3 = cv1 + cv2;
   for (int i = 0; i < 3; i++)
   {
      assert ( cv3.c[i] == cv1.c[i] + cv2.c[i] );
   }

   cv3 = cv1 - cv2;
   for (int i = 0; i < 3; i++)
   {
      assert ( cv3.c[i] == cv1.c[i] - cv2.c[i] );
   }

   cv3 = cv1 / cv2;
   for (int i = 0; i < 3; i++)
   {
      assert ( cv3.c[i] == cv1.c[i] / cv2.c[i] );
   }
   return true;
}

//========================================================================================

bool GenerateDistinctColorsTest()
{
   DistinctColorGenerator dcg;
   for (int i = 0; i < 100; i++)
   {
      cout << "New color " << i << " is " << dcg.GenerateNewColor() << endl;
   }
   return true;
}

//========================================================================================

bool ChromaticAdaptationTest1()
{
   ChromaticAdaptationType adaptationType = CHROMATICADAPTATION_BRADFORD;
   double c0 =  37.0;
   double c1 = 123.0;
   double c2 = 209.0;
   TransformColorSpace tcsp;

   ColorValue cv1 = ColorValue( c0, c1, c2, TYPE_RGB );

   cout << "Normalized color " << (cv1 / 255.0) << endl << flush;

   // verified with Bruce Lindbloom CIE Color Calculator;
   //     * RGB values first normalized to [0, 1];
   //     * reference illuminant D50
   //     * Adaptation: "None"
   ColorValue cv1XYZ = tcsp.sRGBtoXYZ( cv1 );

   cout << "XYZ color in (D50) = " << cv1XYZ << endl << flush;

   ChromaticAdaptation ca1( ColorConstants::sD50_XYZ, ColorConstants::sD65_XYZ, adaptationType );
   ColorValue cvAdapted1 = ca1.AdaptXYZColor( cv1XYZ );


   // values verfied with Bruce Lindbloom Chromatic Adaptation Calculator
   assert ( fabs(cvAdapted1.c[0] - 0.220299 ) < COLOR_TOLERANCE_THRESHOLD );
   assert ( fabs(cvAdapted1.c[1] - 0.201274 ) < COLOR_TOLERANCE_THRESHOLD );
   assert ( fabs(cvAdapted1.c[2] - 0.836253 ) < COLOR_TOLERANCE_THRESHOLD );

   cout << "XYZ color adapted (D65, Bradford) = " << cvAdapted1 << endl << flush;

   adaptationType = CHROMATICADAPTATION_VONKRIES;

   ChromaticAdaptation ca2( ColorConstants::sD50_XYZ, ColorConstants::sD65_XYZ, adaptationType );
   ColorValue cvAdapted2 = ca2.AdaptXYZColor( cv1XYZ );

   // values verfied with Bruce Lindbloom Chromatic Adaptation Calculator
   assert ( fabs(cvAdapted2.c[0] - 0.222661 ) < COLOR_TOLERANCE_THRESHOLD );
   assert ( fabs(cvAdapted2.c[1] - 0.192128 ) < COLOR_TOLERANCE_THRESHOLD );
   assert ( fabs(cvAdapted2.c[2] - 0.831211 ) < COLOR_TOLERANCE_THRESHOLD );

   cout << "XYZ color adapted (D65, Von Kries) = " << cvAdapted2 << endl << flush;

   adaptationType = CHROMATICADAPTATION_XYZSCALING;

   ChromaticAdaptation ca3( ColorConstants::sD50_XYZ, ColorConstants::sD65_XYZ, adaptationType );
   ColorValue cvAdapted3 = ca3.AdaptXYZColor( cv1XYZ );

   // values verfied with Bruce Lindbloom Chromatic Adaptation Calculator
   assert ( fabs(cvAdapted3.c[0] - 0.190759 ) < COLOR_TOLERANCE_THRESHOLD );
   assert ( fabs(cvAdapted3.c[1] - 0.191610 ) < COLOR_TOLERANCE_THRESHOLD );
   assert ( fabs(cvAdapted3.c[2] - 0.831214 ) < COLOR_TOLERANCE_THRESHOLD );

   cout << "XYZ color adapted (D65, XYZ scaling) = " << cvAdapted3 << endl << flush;
   return true;
}

//========================================================================================

bool ChromaticAdaptationTest2()
{
   ChromaticAdaptationType adaptationType = CHROMATICADAPTATION_BRADFORD;
   double c0 = 253.0;
   double c1 =  58.0;
   double c2 = 149.0;

   TransformColorSpace tcsp;

   ColorValue cv1 = ColorValue( c0, c1, c2, TYPE_RGB );

   cout << "Normalized color " << (cv1 / 255.0) << endl << flush;

   // verified with Bruce Lindbloom CIE Color Calculator;
   //     * RGB values first normalized to [0, 1];
   //     * reference illuminant D50
   //     * Adaptation: "None"
   ColorValue cv1XYZ = tcsp.sRGBtoXYZ( cv1 );

   cout << "XYZ color in (D50) = " << cv1XYZ << endl << flush;

   ChromaticAdaptation ca1( ColorConstants::sD50_XYZ, ColorConstants::sF7_XYZ, adaptationType );
   ColorValue cvAdapted1 = ca1.AdaptXYZColor( cv1XYZ );

   // values verfied with Bruce Lindbloom Chromatic Adaptation Calculator
   assert ( fabs(cvAdapted1.c[0] - 0.46696 ) < COLOR_TOLERANCE_THRESHOLD );
   assert ( fabs(cvAdapted1.c[1] - 0.25648 ) < COLOR_TOLERANCE_THRESHOLD );
   assert ( fabs(cvAdapted1.c[2] - 0.41184 ) < COLOR_TOLERANCE_THRESHOLD );

   cout << "XYZ color adapted (F7, Bradford) = " << cvAdapted1 << endl << flush;

   adaptationType = CHROMATICADAPTATION_VONKRIES;

   ChromaticAdaptation ca2( ColorConstants::sD50_XYZ, ColorConstants::sA_XYZ, adaptationType );
   ColorValue cvAdapted2 = ca2.AdaptXYZColor( cv1XYZ );

   // values verfied with Bruce Lindbloom Chromatic Adaptation Calculator
   assert ( fabs(cvAdapted2.c[0] - 0.50948 ) < COLOR_TOLERANCE_THRESHOLD );
   assert ( fabs(cvAdapted2.c[1] - 0.26498 ) < COLOR_TOLERANCE_THRESHOLD );
   assert ( fabs(cvAdapted2.c[2] - 0.13355 ) < COLOR_TOLERANCE_THRESHOLD );

   cout << "XYZ color adapted (A, Von Kries) = " << cvAdapted2 << endl << flush;

   adaptationType = CHROMATICADAPTATION_XYZSCALING;

   ChromaticAdaptation ca3( ColorConstants::sD50_XYZ, ColorConstants::sE_XYZ, adaptationType );
   ColorValue cvAdapted3 = ca3.AdaptXYZColor( cv1XYZ );

   // values verfied with Bruce Lindbloom Chromatic Adaptation Calculator
   assert ( fabs(cvAdapted3.c[0] - 0.49211 ) < COLOR_TOLERANCE_THRESHOLD );
   assert ( fabs(cvAdapted3.c[1] - 0.26080 ) < COLOR_TOLERANCE_THRESHOLD );
   assert ( fabs(cvAdapted3.c[2] - 0.37530 ) < COLOR_TOLERANCE_THRESHOLD );

   cout << "XYZ color adapted (E, XYZ scaling) = " << cvAdapted3 << endl << flush;
   return true;
}

//========================================================================================


bool ChromaticAdaptationTest3( )
{
   Image* pInImage = ImageIO::Read( std::string("../../testdata/chouffe.ppm") );

   ChromaticAdaptationType adaptationType = CHROMATICADAPTATION_BRADFORD;

   pInImage->ChromaticAdapt( ColorConstants::sD93_XYZ, ColorConstants::sD50_XYZ, adaptationType );
   ImageIO::Write( pInImage, std::string("ChromaticD93-D50.ppm") );
   delete pInImage;

   pInImage = ImageIO::Read( std::string("../../testdata/chouffe.ppm") );
   pInImage->ChromaticAdapt( ColorConstants::sD50_XYZ, ColorConstants::sD75_XYZ, adaptationType );
   ImageIO::Write( pInImage, std::string("ChromaticD50-D93.ppm") );

   delete pInImage;
   return true;
}

//========================================================================================

bool ColorBalanceTest()
{
   Image* pInImage = ImageIO::Read( std::string("../../testdata/Lenna.ppm") );
   //Image* pInImage = ImageIO::Read( std::string("../../testdata/StanfordTowerOrigin.ppm") );
   //Image* pInImage = ImageIO::Read( std::string("../../testdata/chouffe.ppm") );
   //Image* pInImage = ImageIO::Read( std::string("../../testdata/HulstColorRaw.ppm") );

   Image* pOutImage = ColorBalancer::RunGrayWorld( pInImage );
   ImageIO::Write( pOutImage, std::string("GrayWorldBalance.ppm") );
   delete pOutImage;

   pOutImage = ColorBalancer::RunPerfectReflector( pInImage );
   ImageIO::Write( pOutImage, std::string("PerfectReflectorBalance.ppm") );
   delete pOutImage;

   pOutImage = ColorBalancer::RunGrayColorPoint( pInImage );
   ImageIO::Write( pOutImage, std::string("GrayColorPointBalance.ppm") );
   delete pOutImage;

   pOutImage = ColorBalancer::RunBalance( pInImage );
   ImageIO::Write( pOutImage, std::string("Balance.ppm") );
   delete pOutImage;
   return true;
}

//========================================================================================

bool ColorCheckerTest()
{
   int borderWidth = 4;
   int squareSize = 50;

   Image* pColorTestChart = GretagMacbethColorChecker::Generate( borderWidth, squareSize );

   ImageIO::Write( pColorTestChart, std::string("GretagMacbethColorChecker.ppm") );
   delete pColorTestChart;
   return true;
}

//========================================================================================

bool RGB2HSV2RGBTest(Image* pInImage )
{
   cout << " RGB -> HSV -> RGB test" << endl << flush;
   Image* pOut = pInImage->Clone();

   pOut->RGBToHSV();
   #ifdef FULL_DIAGNOSE_TEST
   ImageIO::Write( pOut, string("HSVImage.ppm"), ImageIO::NORMAL_OUT );
   #endif
   pOut->HSVToRGB();
   Image* pDiff = ImageTools::CreateImageSSD( pInImage, pOut );

   ImageIO::Write( pDiff, string("DiffHSVImage.ppm"), ImageIO::NORMAL_OUT );

   double absMax = pDiff->GetAbsMax( );

   ImageIO::Write( pOut, string("RGB2HSV2RGBImage.ppm"), ImageIO::NULL_OUT );
   delete pDiff;
   delete pOut;

   if (absMax < 0.00000001)
   {
      return true;
   }
   else
   {
      return false;
   }
}

//========================================================================================

bool RGB2XYZ2RGBTest(Image* pInImage )
{
   cout << " RGB -> XYZ -> RGB test" << endl << flush;
   Image* pOut = pInImage->Clone();

   pOut->sRGBToXYZ();
   #ifdef FULL_DIAGNOSE_TEST
   ImageIO::Write( pOut, string("XYZImage.ppm"), ImageIO::NORMAL_OUT );
   #endif
   pOut->XYZTosRGB();
   Image* pDiff = ImageTools::CreateImageSSD( pInImage, pOut );

   #ifdef FULL_DIAGNOSE_TEST
   ImageIO::Write( pOut, string("RGB2XYZ2RGBImage.ppm"), ImageIO::NULL_OUT );
   ImageIO::Write( pOut, string("DiffXYZImage.ppm"), ImageIO::NULL_OUT );
   #endif
   delete pDiff;
   delete pOut;
   return true;
}

//========================================================================================

bool RGB2Luv2RGBTest(Image* pInImage )
{
   cout << " RGB -> Luv -> RGB test" << endl << flush;
   Image* pOut = pInImage->Clone();

   pOut->sRGBToLuv();
   #ifdef FULL_DIAGNOSE_TEST
   ImageIO::Write( pOut, string("LuvImage.ppm"), ImageIO::NORMAL_OUT );
   #endif
   cout << " In Luv space" << endl << flush;
   #ifdef FULL_DIAGNOSE_TEST
   pOut->Diagnose(string("LUV"));
   #endif
   pOut->LuvTosRGB();
   Image* pDiff = ImageTools::CreateImageSSD( pInImage, pOut );

   #ifdef FULL_DIAGNOSE_TEST
   ImageIO::Write( pOut, string("RGB2Luv2RGBImage.ppm"), ImageIO::NULL_OUT );
   ImageIO::Write( pDiff, string("DiffLuvImage.ppm"), ImageIO::NULL_OUT );
   #endif
   delete pDiff;
   delete pOut;
   return true;
}


//========================================================================================

bool RGB2Lab2RGBTest(Image* pInImage )
{
   cout << " RGB -> Lab -> RGB test" << endl << flush;
   Image* pOut = pInImage->Clone();

   pOut->sRGBToLab();
   #ifdef FULL_DIAGNOSE_TEST
   ImageIO::Write( pOut, string("LabImage.ppm"), ImageIO::NORMAL_OUT );
   #endif
   cout << " In Lab space" << endl << flush;
   #ifdef FULL_DIAGNOSE_TEST
   pOut->Diagnose(string("Lab"));
   #endif
   pOut->LabTosRGB();
   Image* pDiff = ImageTools::CreateImageSSD( pInImage, pOut );

   #ifdef FULL_DIAGNOSE_TEST
   ImageIO::Write( pOut, string("RGB2Lab2RGBImage.ppm"), ImageIO::NULL_OUT );
   ImageIO::Write( pDiff, string("DiffLabImage.ppm"), ImageIO::NULL_OUT );
   #endif
   delete pDiff;
   delete pOut;
   return true;
}

//========================================================================================

bool RGB2HSI2RGBTest(Image* pInImage )
{
   cout << " RGB -> HSI -> RGB test" << endl << flush;
   Image* pOut = pInImage->Clone();

   pOut->RGBToHSI();
   #ifdef FULL_DIAGNOSE_TEST
   ImageIO::Write( pOut, string("HSIImage.ppm"), ImageIO::NORMAL_OUT );
   #endif
   pOut->HSIToRGB();
   Image* pDiff = ImageTools::CreateImageSSD( pInImage, pOut );

   #ifdef FULL_DIAGNOSE_TEST
   ImageIO::Write( pDiff, string("DiffHSIImage-2.ppm"), ImageIO::NORMAL_OUT );
   ImageIO::Write( pOut, string("RGB2HSI2RGBImage.ppm"), ImageIO::NULL_OUT );
   #endif
   delete pDiff;
   delete pOut;
   return true;
}

//========================================================================================

bool AdobeRGB2XYZ2AdobeRGBTest(Image* pInImage )
{
   cout << " AdobeRGB -> XYZ -> AdobeRGB test" << endl << flush;
   Image* pOut = pInImage->Clone();

   pOut->AdobeRGBToXYZ();
   #ifdef FULL_DIAGNOSE_TEST
   ImageIO::Write( pOut, string("AdobeXYZImage.ppm"), ImageIO::NORMAL_OUT );
   pOut->Diagnose();
   #endif

   pOut->XYZToAdobeRGB();
   Image* pDiff = ImageTools::CreateImageSSD( pInImage, pOut );

   #ifdef FULL_DIAGNOSE_TEST
   ImageIO::Write( pDiff, string("AdobeDiffXYZHSIImage-2.ppm"), ImageIO::NORMAL_OUT );
   ImageIO::Write( pOut, string("AdobeRGB2XYZ2AdobeRGBImage.ppm"), ImageIO::NULL_OUT );
   #endif
   delete pDiff;
   delete pOut;
   return true;
}

//========================================================================================

bool RGB2CMY2RGBTest(Image* pInImage )
{
   cout << " RGB -> CMY -> RGB test" << endl << flush;
   Image* pOut = pInImage->Clone();

   pOut->RGBToCMY();
   #ifdef FULL_DIAGNOSE_TEST
   ImageIO::Write( pOut, string("CMYImage.ppm"), ImageIO::NORMAL_OUT );
   pOut->Diagnose();
   #endif
   pOut->CMYToRGB();
   Image* pDiff = ImageTools::CreateImageSSD( pInImage, pOut );

   #ifdef FULL_DIAGNOSE_TEST
   ImageIO::Write( pDiff, string("Diff-RGB-CMY-RGB.ppm"), ImageIO::NORMAL_OUT );
   ImageIO::Write( pOut, string("RGB-CMY-RGBImage.ppm"), ImageIO::NULL_OUT );
   #endif
   delete pDiff;
   delete pOut;
   return true;
}

//========================================================================================

bool RGB2YUV2RGBTest(Image* pInImage )
{
   cout << " RGB -> YUV -> RGB test" << endl << flush;
   Image* pOut = pInImage->Clone();

   pOut->RGBToYUV();
   #ifdef FULL_DIAGNOSE_TEST
   ImageIO::Write( pOut, string("YUVImage.ppm"), ImageIO::NORMAL_OUT );
   pOut->Diagnose();
   #endif

   pOut->YUVToRGB();

   double psnr = ImageTools::ComputePSNR( pInImage, pOut );

   cout << "\t psnr = " << psnr << endl << flush;

   #ifdef FULL_DIAGNOSE_TEST
   Image* pDiff = ImageTools::CompareImagesSSD( pInImage, pOut );

   ImageIO::Write( pDiff, string("Diff-RGB-YUV-RGB.ppm"), ImageIO::NORMAL_OUT );
   ImageIO::Write( pOut, string("RGB-YUV-RGBImage.ppm"), ImageIO::NULL_OUT );
   delete pDiff;
   #endif
   delete pOut;
   return true;
}

//========================================================================================

bool ColorMapTest()
{
   ArrayGrid<double>* pGrid = (ArrayGrid<double>*)(GridGenerator::GenerateHorizontalGradient());
   #ifdef FULL_DIAGNOSE_TEST
   ImageIO::WritePGM(pGrid, string("Gradient.pgm"), ImageIO::NULL_OUT);
   #endif

   Image* pJet = new Image(pGrid);
   Image* pImg = ImageTools::ApplyJetColorMap( pJet );
   #ifdef FULL_DIAGNOSE_TEST
   ImageIO::Write( pImg, std::string("ImageJet.ppm") );
   #endif
   delete pJet;
   delete pImg;
   return true;
}

//========================================================================================

bool labVisualizeTest()
{
   int halfSize = 128;
   int width = 2 * halfSize + 1;
   int height = 2 * halfSize + 1;
   int startPos = -halfSize;
   int endPos = halfSize;
   double l, a, b;
   Image* pImg = new Image( width, height, 3 );
   TransformColorSpace tcsp;

   int nrNonRepresentable = 0;
   int nrRepresentable = 0;

   for (l = 0; l <= 100; l+=10)
   {
      for (b = startPos; b <= endPos; b++ )
      {
         for (a = startPos; a <= endPos; a++ )
         {
            ColorValue cv1 = ColorValue( l, a, b, TYPE_LAB );
            ColorValue cv2 = tcsp.LabtosRGB( cv1 );
            double color2Min = cv2.GetMin();
            double color2Max = cv2.GetMax();

            // with these restrictions, we are able to reproduce the figures for http://en.wikipedia.org/wiki/Lab_color_space
            //  "The CIE 1976 (L*, a*, b*) color space (CIELAB), showing only colors that fit within the sRGB gamut"
            // more specific, see http://en.wikipedia.org/wiki/File:Lab_color_space.png
            if ( ( color2Min < 0.0) || (color2Min > 255.0) || ( color2Max < 0.0) || (color2Max > 255.0) )
            {
               for (int j = 0; j < 3; j++)
               {
                  cv2.c[j] = 0;
               }
               nrNonRepresentable++;
            }
            else
            {
               nrRepresentable++;
            }

            pImg->SetColor( (int)(a+halfSize), (int)(b+halfSize), cv2 );

         }
      }
      stringstream ss;
      ss << "ImageLab-" << setfill('0') << setw(3) << l << ".ppm";
      std::string fileName = ss.str();
      ImageIO::Write( pImg, fileName );
   }
   cout << "nrNonRepresentable = " << nrNonRepresentable << " and nrRepresentable = " << nrRepresentable << endl << flush;

   delete pImg;
   return true;
}

//========================================================================================


bool yuvVisualizeTest()
{
   int halfSize = 128;
   int width = 2 * halfSize + 1;
   int height = 2 * halfSize + 1;
   int startPos = -halfSize;
   int endPos = halfSize;

   Image* pImg = new Image( width, height, 3 );
   TransformColorSpace tcsp;

   int nrNonRepresentable = 0;
   int nrRepresentable = 0;

   for (double y = 0; y <= 1.0; y+=0.1)
   {
      for (double v = startPos; v <= endPos; v++ )
      {
         for (double u = startPos; u <= endPos; u++ )
         {
            double tmpU = u / 320;
            double tmpV = v / 320;
            ColorValue cv1 = ColorValue( y, tmpU, tmpV, TYPE_YUV );
            ColorValue cv2 = tcsp.YUVtoRGB( cv1 );
            cv2.c[0] *= 255.0;
            cv2.c[1] *= 255.0;
            cv2.c[2] *= 255.0;
            double color2Min = cv2.GetMin();
            double color2Max = cv2.GetMax();

            // with these restrictions, we are able to reproduce the figure for http://en.wikipedia.org/wiki/YUV
            // but in our case the vertical axis is pointing the other way (negative at top to positive at bottom,
            //   while in wikipedia it goes from positive at top to negative at the bottom)
            // more specific, see http://en.wikipedia.org/wiki/File:YUV_UV_plane.svg
            if ( ( color2Min < 0.0) || (color2Min > 255.0) || ( color2Max < 0.0) || (color2Max > 255.0) )
            {
               for (int j = 0; j < 3; j++)
               {
                  cv2.c[j] = 0;
               }
               nrNonRepresentable++;
            }
            else
            {
               nrRepresentable++;
            }

            pImg->SetColor( (int)(u+halfSize), (int)(v+halfSize), cv2 );

         }
      }
      stringstream ss;
      ss << "ImageYUV-" << setfill('0') << setw(3) << y << ".ppm";
      std::string fileName = ss.str();
      ImageIO::Write( pImg, fileName );
   }
   cout << "nrNonRepresentable = " << nrNonRepresentable << " and nrRepresentable = " << nrRepresentable << endl << flush;

   delete pImg;
   return true;
}

//========================================================================================

bool rgbVisualizeTest()
{
   double r, g, b, rStep, gStep, bStep;

   rStep = gStep = bStep = 1.0;
   int maxL = 110;
   int maxA = 256;
   int maxB = 256;
   ColorValue*** pLABCube;//[ maxL ][ maxA ][ maxB ];  // cube of color values

   pLABCube = new ColorValue**[110];
   {
      for( int l = 0; l < maxL; l++)
      {
         pLABCube[ l ] = new ColorValue*[256];
         for( int a = 0; a < maxA; a++)
         {
            pLABCube[ l ][ a ] = new ColorValue[256];
         }
      }
   }

   ColorValue cv0 = ColorValue( 0, 0, 0, TYPE_LAB );

   for (int l=0; l < maxL; l++)
   {
      for (int a=0; a < maxA; a++)
      {
         for (int b=0; b < maxB; b++)
         {
            pLABCube[ l ][ a ][ b ] = cv0;
         }
      }
   }
   TransformColorSpace tcsp;

   for (r = 0.0; r <= 255.0; r += rStep)
   {
      for (g = 0.0; g <= 255.0; g += gStep )
      {
         for (b = 0.0; b <= 255.0; b += bStep )
         {
            ColorValue cv1 = ColorValue( r, g, b, TYPE_RGB );
            ColorValue cv2 = tcsp.sRGBtoLab( cv1 );
            if (    ( cv2.c[0] >    0 )
                 && ( cv2.c[0] < maxL )
                 && ( cv2.c[1] > -127 )
                 && ( cv2.c[1] <  128 )
                 && ( cv2.c[2] > -127 )
                 && ( cv2.c[2] <  128 )
               )
            {
               ColorValue cvRGB = ColorValue( r, g, b, TYPE_RGB );
               pLABCube[ (int)(cv2.c[0]) ]
                      [ (int)(cv2.c[1]+127) ]
                      [ (int)(cv2.c[2]+127) ] = cvRGB;
            }
         }
      }
   }

   // This visualization allows us to reproduce the visualization of the sRGB space in L*a*b* coordinate space;
   //   consistent with the slicer output from ColorThink software of Chromix
   for (int l = 0; l < maxL; l+=2)
   {
      Image* pImg = new Image( maxA, maxB, 3 );
      for (int a=0; a < maxA; a++)
      {
         for (int b=0; b < maxB; b++)
         {
            pImg->SetColor( a, b, pLABCube[ l ][ a ][ b ] );
         }
      }
      stringstream ss;
      ss << "ImageRGB-" << setfill('0') << setw(3) << l << ".ppm";
      std::string fileName = ss.str();
      ImageIO::Write( pImg, fileName );
      delete pImg;
   }

   for (int l=0; l < maxL; l++)
   {
      for( int a = 0; a < maxA; a++)
      {
         delete []pLABCube[ l ][ a ];
      }
      delete []pLABCube[ l ];
   }
   delete []pLABCube;

   return true;
}

//========================================================================================

bool RGB2LabTest()
{
   TransformColorSpace col;
   col.SetReferenceWhite( ColorConstants::sD50_XYZ );

   /*ColorValue RGB1 = {   0,   0,   0, TYPE_RGB};
   ColorValue RGB2 = {   0,   0, 255, TYPE_RGB};
   ColorValue RGB3 = {   0, 255,   0, TYPE_RGB};
   ColorValue RGB4 = { 255,   0,   0, TYPE_RGB};
   ColorValue RGB5 = {   0, 255, 255, TYPE_RGB};
   ColorValue RGB6 = { 255, 255,   0, TYPE_RGB};
   ColorValue RGB7 = { 255,   0, 255, TYPE_RGB};
   ColorValue RGB8 = { 255, 255, 255, TYPE_RGB};*/


   /* obtained values are consistent with Bruce Lindbloom's CIE Color Calculator
      http://www.brucelindbloom.com/index.html?ColorCalculator.html
      with settings: "scale RGB" set to "true"; and "Adaptation" to "None"*/
   ColorValue RGB1 = ColorValue(  12,   8,  98, TYPE_RGB );
   ColorValue RGB2 = ColorValue( 124,  32, 178, TYPE_RGB );
   ColorValue RGB3 = ColorValue( 213, 201,  78, TYPE_RGB );
   ColorValue RGB4 = ColorValue(  26,  65,  15, TYPE_RGB );
   ColorValue RGB5 = ColorValue(  78, 155,  55, TYPE_RGB );
   ColorValue RGB6 = ColorValue( 164, 125,  32, TYPE_RGB );
   ColorValue RGB7 = ColorValue( 149,  37, 195, TYPE_RGB );
   ColorValue RGB8 = ColorValue( 220,  25, 255, TYPE_RGB );

   cout << " With reference white D50" << endl << flush;
   cout << RGB1 << " -> " << col.sRGBtoLab( RGB1 ) << endl << flush;
   cout << RGB2 << " -> " << col.sRGBtoLab( RGB2 ) << endl << flush;
   cout << RGB3 << " -> " << col.sRGBtoLab( RGB3 ) << endl << flush;
   cout << RGB4 << " -> " << col.sRGBtoLab( RGB4 ) << endl << flush;
   cout << RGB5 << " -> " << col.sRGBtoLab( RGB5 ) << endl << flush;
   cout << RGB6 << " -> " << col.sRGBtoLab( RGB6 ) << endl << flush;
   cout << RGB7 << " -> " << col.sRGBtoLab( RGB7 ) << endl << flush;
   cout << RGB8 << " -> " << col.sRGBtoLab( RGB8 ) << endl << flush;

   col.SetReferenceWhite( ColorConstants::sD65_XYZ );

   cout << " With reference white D65" << endl << flush;
   cout << RGB1 << " -> " << col.sRGBtoLab( RGB1 ) << endl << flush;
   cout << RGB2 << " -> " << col.sRGBtoLab( RGB2 ) << endl << flush;
   cout << RGB3 << " -> " << col.sRGBtoLab( RGB3 ) << endl << flush;
   cout << RGB4 << " -> " << col.sRGBtoLab( RGB4 ) << endl << flush;
   cout << RGB5 << " -> " << col.sRGBtoLab( RGB5 ) << endl << flush;
   cout << RGB6 << " -> " << col.sRGBtoLab( RGB6 ) << endl << flush;
   cout << RGB7 << " -> " << col.sRGBtoLab( RGB7 ) << endl << flush;
   cout << RGB8 << " -> " << col.sRGBtoLab( RGB8 ) << endl << flush;

   return true;
}


//========================================================================================

bool SaturationTest()
{
   TransformColorSpace tcsp;
   ColorValue rgbBrown = ColorValue( 131, 115,  85, TYPE_RGB );
   ColorValue rgbBlue  = ColorValue(  86, 115, 128, TYPE_RGB );

   cout << rgbBrown
        << " -> " << tcsp.sRGBtoLab( rgbBrown )
        << " -> " << tcsp.RGBtoHSI( rgbBrown )
        << " -> " << tcsp.RGBtoHSV( rgbBrown ) << endl << flush;

   cout << rgbBlue
        << " -> " << tcsp.sRGBtoLab( rgbBlue )
        << " -> " << tcsp.RGBtoHSI( rgbBlue )
        << " -> " << tcsp.RGBtoHSV( rgbBlue )  << endl << flush;

   return true;
}

//========================================================================================

// reference values from spreadsheet on http://www.digitalcolour.org/understanding/Tristimulus.htm
bool SpectralToXYZTest()
{
   double threshold = 0.000001;
   double spectralValues[40]
     = { 0.11501, 0.12900, 0.28997, 0.54062, 0.64620, 0.66568, 0.68373, 0.70216, 0.71370, 0.72216,
         0.72831, 0.72719, 0.71721, 0.70794, 0.69588, 0.67721, 0.66911, 0.66766, 0.66611, 0.67797,
         0.70353, 0.73258, 0.74644, 0.74612, 0.73850, 0.72674, 0.71238, 0.69810, 0.68553, 0.67679,
         0.67354, 0.67546, 0.68141, 0.69381, 0.71073, 0.73057, 0.75012, 0.77421, 0.79512, 0.81538 };

   int wavelengthMin = 380;
   int wavelengthMax = 770;
   TransformColorSpace tcs;
   ColorValue XYZ = tcs.SpectralValuesToXYZ( spectralValues, wavelengthMin, wavelengthMax );

   assert ( fabs( XYZ.c[0] - 68.44494323 ) < threshold );
   assert ( fabs( XYZ.c[1] - 69.79940707 ) < threshold );
   assert ( fabs( XYZ.c[2] - 57.53051152 ) < threshold );

   return true;
}

//========================================================================================

bool ConvertPrimariesTest( std::string fileNameIn, std::string fileNameOut )
{
   ifstream fileData( fileNameIn.c_str() );
   if (!fileData)
   {
      cout << "ERROR: testColor ConvertPrimariesTest can't read from file " << fileNameIn << "." << endl;
      return false;
   }

   int minWavelength = 380;
   int maxWavelength = 730;

   TransformColorSpace tcs;
   tcs.SetReferenceWhite( ColorConstants::sD50_XYZ );

   ofstream ofp;
   ofp.open(const_cast<char*>( fileNameOut.c_str()), ios::out | ios::binary);

   if (!ofp)
   {
      cout << "Can't write to file " << fileNameOut << "." << endl;
      return false;
   }

   while( !fileData.eof() )
   {
      double value[ 36 ];
      for (int i = 0; i < 36; i++)
      {
         fileData >> value[i];
      }
      ofp << tcs.XYZtoLab( tcs.SpectralValuesToXYZ( value, minWavelength, maxWavelength ) / 100.0 ) << "\r\n" << flush;
   }
   fileData.close();
   ofp.close();
   return true;
}

//========================================================================================

// fileReference1 : spectral values as measured for default setup (needed as input)
// fileModel1     : spectral values from model for default setup (needed as input)
// fileModel2     : spectral values from model for target setup  (needed as input)
// fileReference2 : spectral values as measured for target setup (not exactly needed in model, but used as ground thruth for verification)
// fileOut        : corrected spectral values for target setup, plus model statistics
bool CorrectSpectralValues( std::string fileReference1, std::string fileModel1, std::string fileModel2, std::string fileReference2, std::string fileOut )
{
   ifstream inReferenceStream1( fileReference1.c_str() );
   if ( !inReferenceStream1 )
   {
      cout << "ERROR: testColor CorrectSpectralValues can't read from file " << fileReference1 << "." << endl;
      return false;
   }
   else
   {
      cout << "Successfully read default reference values from file " << fileReference1 << "." << endl;
   }

   ifstream inModeledStream1( fileModel1.c_str() );
   if ( !inModeledStream1 )
   {
      cout << "ERROR: testColor CorrectSpectralValues can't read from file " << fileModel1 << "." << endl;
      return false;
   }
   else
   {
      cout << "Successfully read default modeled values from file " << fileReference1 << "." << endl;
   }

   ifstream inModeledStream2( fileModel2.c_str() );
   if ( !inModeledStream2 )
   {
      cout << "ERROR: testColor CorrectSpectralValues Can't read from file " << fileModel2 << "." << endl;
      return false;
   }
   else
   {
      cout << "Successfully read target modeled values from file " << fileReference1 << "." << endl;
   }

   ifstream inReferenceStream2( fileReference2.c_str() );
   if ( !inReferenceStream2 )
   {
      cout << "ERROR: testColor CorrectSpectralValues can't read from file " << fileReference2 << "." << endl;
      return false;
   }
   else
   {
      cout << "Successfully read target reference values from file " << fileReference1 << "." << endl;
   }

   int minWavelength = 380;
   int maxWavelength = 730;

   TransformColorSpace tcs;
   tcs.SetReferenceWhite( ColorConstants::sD50_XYZ );

   ofstream outStreamLabDE;
   outStreamLabDE.open(const_cast<char*>( fileOut.c_str()), ios::out | ios::binary);

   ofstream outStreamSpectralValues;
   outStreamSpectralValues.open( "CorrectedSpectralValues.txt", ios::out | ios::binary);

   if ( !outStreamSpectralValues )
   {
      cout << "Can't write to file " << fileOut << "." << endl;
      return false;
   }
   if ( !outStreamLabDE )
   {
      cout << "Can't write to file " << fileOut << "." << endl;
      return false;
   }

   while( !inReferenceStream1.eof() )
   {
      double spectralValuesReference1[ 36 ];
      double spectralValuesModel1[ 36 ];
      double spectralValuesModel2[ 36 ];
      double spectralValuesReference2[ 36 ];
      double spectralValuesModel2Corrected[ 36 ];

      for (int i = 0; i < 36; i++)
      {
         inReferenceStream1   >> spectralValuesReference1[ i ];
         inReferenceStream2   >> spectralValuesReference2[ i ];
         inModeledStream1 >> spectralValuesModel1[ i ];
         inModeledStream2 >> spectralValuesModel2[ i ];

         double correctionTerm = spectralValuesModel1[i] - spectralValuesReference1[i];
         spectralValuesModel2Corrected[i] = spectralValuesModel2[i] - correctionTerm;
         outStreamSpectralValues << spectralValuesModel2Corrected[i] << "\t";
      }
      ColorValue labOriginal = tcs.SpectralValuesToLab( spectralValuesModel2, minWavelength, maxWavelength );
      ColorValue labCorrected = tcs.SpectralValuesToLab( spectralValuesModel2Corrected, minWavelength, maxWavelength );
      outStreamSpectralValues << "\r\n";
      outStreamLabDE  << labOriginal << "\t"
                      << tcs.DeltaE2000( spectralValuesModel2,          spectralValuesReference2, minWavelength, maxWavelength ) << "\t"
                      << labCorrected  << "\t"
                      << tcs.DeltaE2000( spectralValuesModel2Corrected, spectralValuesReference2, minWavelength, maxWavelength ) << "\r\n" << flush;
   }
   inReferenceStream1.close();
   inReferenceStream2.close();
   inModeledStream1.close();
   inModeledStream2.close();
   outStreamLabDE.close();
   outStreamSpectralValues.close();
   return true;
}

//========================================================================================

// Compare with results from Colour Engineering Toolbox (free Matlab toolbox)
// available at http://www.digitalcolour.org/toolbox.htm, used for reference results (REF)
// WARNING!!! - Lindbloom uses standard D65 with sRGB;
//            - digitalcolour reference values default uses D50.
bool DeltaE200Test1()
{
   double epsilon = 0.05;
   ColorValue RGB1 = ColorValue( 0, 100, 255, TYPE_RGB );
   ColorValue RGB2 = ColorValue( 0, 255,   0, TYPE_RGB );

   TransformColorSpace col;
   col.SetReferenceWhite( ColorConstants::sD50_XYZ );

   ColorValue XYZ1 = col.sRGBtoXYZ( RGB1 );
   ColorValue XYZ2 = col.sRGBtoXYZ( RGB2 );

   cout << RGB1 << " -> " << XYZ1 << endl << flush;
   cout << RGB2 << " -> " << XYZ2 << endl << flush;

   // (REF) XYZ1 = 22.6072   16.3343   96.5691
   // (REF) XYZ2 = 35.7600   71.5200   11.9200

   ColorValue LAB1 = col.sRGBtoLab( RGB1 );
   ColorValue LAB2 = col.sRGBtoLab( RGB2 );

   // (REF) LAB1 = 47.4101   34.9968 -101.4584
   // (REF) LAB2 = 87.7370  -87.9062   73.9055

   cout << RGB1 << " -> " << LAB1 << endl << flush;
   cout << RGB2 << " -> " << LAB2 << endl << flush;

   assert ( fabs( LAB1.c[0] - 47.4101) < epsilon );
   assert ( fabs( LAB1.c[1] - 34.9968) < epsilon );
   assert ( fabs( LAB1.c[2] + 101.4584) < epsilon );

   assert ( fabs( LAB2.c[0] - 87.7370) < epsilon );
   assert ( fabs( LAB2.c[1] + 87.9062) < epsilon );
   assert ( fabs( LAB2.c[2] - 73.9055) < epsilon );
   // (REF) DE = 74.5160
   TransformColorSpace tcsp;
   assert ( fabs( tcsp.DeltaE2000( LAB1, LAB2 ) - 74.5160) < epsilon );
   return true;
}

//========================================================================================

// Compare with results from Colour Engineering Toolbox (free Matlab toolbox)
// available at http://www.digitalcolour.org/toolbox.htm, used for reference results (REF)
// WARNING!!! Lindbloom uses standard D65 with sRGB; digitalcolour reference values default uses D50.
bool DeltaE200Test2()
{
   double epsilon = 0.05;

   TransformColorSpace col;
   col.SetReferenceWhite( ColorConstants::sD50_XYZ );

   ColorValue RGB1 = ColorValue( 0,   0,   0, TYPE_RGB );
   ColorValue RGB2 = ColorValue( 0, 255, 255, TYPE_RGB );

   ColorValue XYZ1 = col.sRGBtoXYZ( RGB1 );
   ColorValue XYZ2 = col.sRGBtoXYZ( RGB2 );

   ColorValue LAB1 = col.sRGBtoLab( RGB1 );
   ColorValue LAB2 = col.sRGBtoLab( RGB2 );

   // (REF) LAB1 = 0     0     0
   // (REF) LAB2 = 91.1165  -50.0523  -33.4136

   cout << RGB1 << " -> " << LAB1 << endl << flush;
   cout << RGB2 << " -> " << LAB2 << endl << flush;

   assert ( fabs( LAB1.c[0] - 0.0) < epsilon );
   assert ( fabs( LAB1.c[1] - 0.0) < epsilon );
   assert ( fabs( LAB1.c[2] + 0.0) < epsilon );

   assert ( fabs( LAB2.c[0] - 91.1165) < epsilon );
   assert ( fabs( LAB2.c[1] + 50.0523) < epsilon );
   assert ( fabs( LAB2.c[2] + 33.4136) < epsilon );

   // (REF) DE = 90.8271
   TransformColorSpace tcsp;
   assert ( fabs( tcsp.DeltaE2000( LAB1, LAB2 ) - 90.8271) < epsilon );
   return true;
}

//========================================================================================

int main(int argc, char *argv[])
{
   const char* fileName;
   if (argc == 2)
   {
      fileName = argv[1];
   }
   else
   {
      fileName = "../../testdata/Peppers512rgb.ppm";
   }
   bool allSuccess = true;
   Image* pInImage = ImageIO::Read( fileName );

  // GENERAL TESTS
  /////////////////

   ColorCheckerTest();
   ColorBalanceTest();

   if (RGB2HSV2RGBTest( pInImage) != true)
   {
      cerr << "RGB 2 HSV 2 RGB went wrong..." << endl << flush;
      allSuccess = false;
   }
   else
   {
      cout << "RGB 2 HSV 2 RGB -> OK!" << endl << flush;
   }

   if (RGB2HSI2RGBTest( pInImage ) != true)
   {
      cerr << "RGB 2 HSI 2 RGB went wrong..." << endl << flush;
      allSuccess = false;
   }
   else
   {
      cout << "RGB 2 HSI 2 RGB -> OK!" << endl << flush;
   }

   if (RGB2XYZ2RGBTest( pInImage ) != true)
   {
      cerr << "RGB 2 XYZ 2 RGB went wrong..." << endl << flush;
      allSuccess = false;
   }
   else
   {
      cout << "RGB 2 XYZ 2 RGB -> OK!" << endl << flush;
   }

   if (RGB2Luv2RGBTest( pInImage ) != true)
   {
      cerr << "RGB 2 Luv 2 RGB went wrong..." << endl << flush;
      allSuccess = false;
   }
   else
   {
      cout << "RGB 2 Luv 2 RGB -> OK!" << endl << flush;
   }

   if (RGB2Lab2RGBTest( pInImage ) != true)
   {
      cerr << "RGB 2 Lab 2 RGB went wrong..." << endl << flush;
      allSuccess = false;
   }
   else
   {
      cout << "RGB 2 Lab 2 RGB -> OK!" << endl << flush;
   }

   if ( AdobeRGB2XYZ2AdobeRGBTest( pInImage ) != true)
   {
      cerr << "AdobeRGB 2 XYZ 2 AdobeRGB went wrong..." << endl << flush;
      allSuccess = false;
   }
   else
   {
      cout << "AdobeRGB 2 XYZ 2 AdobeRGB -> OK!" << endl << flush;
   }

   if (DeltaE200Test1() != true)
   {
      cerr << "Delta E test 1 went wrong..." << endl << flush;
      allSuccess = false;
   }
   else
   {
      cout << "Delta E test 1 -> OK!" << endl << flush;
   }

   if (DeltaE200Test2() != true)
   {
      cerr << "Delta E test 2 went wrong..." << endl << flush;
      allSuccess = false;
   }
   else
   {
      cout << "Delta E test 2 -> OK!" << endl << flush;
   }

   if (RGB2LabTest() != true)
   {
      cerr << "RGB2LabTest went wrong..." << endl << flush;
      allSuccess = false;
   }
   else
   {
      cout << "RGB2LabTest -> OK!" << endl << flush;
   }

   if (SaturationTest() != true)
   {
      cerr << "SaturationTest went wrong..." << endl << flush;
      allSuccess = false;
   }
   else
   {
      cout << "SaturationTest -> OK!" << endl << flush;
   }

   if ( RGB2CMY2RGBTest( pInImage ) != true)
   {
      cerr << "RGB 2 CMY 2 RGB went wrong..." << endl << flush;
      allSuccess = false;
   }
   else
   {
      cout << "RGB 2 CMY 2 RGB -> OK!" << endl << flush;
   }

   if ( RGB2YUV2RGBTest( pInImage ) != true)
   {
      cerr << "RGB 2 YUV 2 RGB went wrong..." << endl << flush;
      allSuccess = false;
   }
   else
   {
      cout << "RGB 2 YUV 2 RGB -> OK!" << endl << flush;
   }

   if ( labVisualizeTest() != true)
   {
      cerr << "lab Visualize Test went wrong..." << endl << flush;
      allSuccess = false;
   }
   else
   {
      cout << "lab Visualize Test -> OK!" << endl << flush;
   }

   if ( rgbVisualizeTest() != true)
   {
      cerr << "rgb Visualize Test went wrong..." << endl << flush;
      allSuccess = false;
   }
   else
   {
      cerr << "rgb Visualize Test -> OK!" << endl << flush;
   }


   if ( ColorOperatorsTest() != true)
   {
      cerr << "Color Operators Test went wrong..." << endl << flush;
      allSuccess = false;
   }
   else
   {
      cout << "Color Operators Test -> OK!" << endl << flush;
   }

   if ( ChromaticAdaptationTest1() != true)
   {
      cerr << "Chromatic Adaptation Test 1 went wrong..." << endl << flush;
      allSuccess = false;
   }
   else
   {
      cout << "Chromatic Adaptation Test 1 -> OK!" << endl << flush;
   }

   if ( ChromaticAdaptationTest2() != true)
   {
      cerr << "Chromatic Adaptation Test 2 went wrong..." << endl << flush;
      allSuccess = false;
   }
   else
   {
      cout << "Chromatic Adaptation Test 2 -> OK!" << endl << flush;
   }

   if ( ChromaticAdaptationTest3( ) != true)
   {
      cerr << "Chromatic Adaptation Test 3 went wrong..." << endl << flush;
      allSuccess = false;
   }
   else
   {
      cout << "Chromatic Adaptation Test 3 -> OK!" << endl << flush;
   }

   if ( SpectralToXYZTest( ) != true)
   {
      cerr << "Spectral To XYZ Test went wrong..." << endl << flush;
      allSuccess = false;
   }
   else
   {
      cout << "Spectral To XYZ Test -> OK!" << endl << flush;
   }

   yuvVisualizeTest();

   GenerateDistinctColorsTest();

  // FINISH ALL TESTS
  ////////////////////

   delete pInImage;

   if (allSuccess == true)
   {
      cout << "end: all tests ended successfully" << endl << flush;
   }
   else
   {
      cout << "end: *NOT* all tests ended successfully" << endl << flush;
   }
   return EXIT_SUCCESS;
}
