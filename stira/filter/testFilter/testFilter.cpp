
/***********************************************************************************
 *  Copyright (C) 2008 by Filip Rooms                                              *
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
#include <cstdlib>
#include <cassert>
#include "../../common/common/StringUtils.h"
#include "../../imagedata/datastructures/Image.h"
#include "../../imagedata/simpletools/GridExtender.h"
#include "../../imagetools/tools/ImageTools.h"
#include "../../imagetools/tools/ImageIO.h"
#include "../../imagetools/imagegenerator/GridGenerator.h"
#include "../../imagetools/geometrictransform/RigidTransform.h"

#include "../../fouriertools/fouriertools/FFT.h"
#include "../filter/GaussConvolve.h"
#include "../filter/LaplacianOfGaussianFilter.h"
#include "../filter/DifferenceOfGaussians.h"
#include "../filter/AdaptiveBilateralFilter.h"
#include "../filter/MedianFilter.h"
#include "../filter/SeparableFilter.h"
#include "../filter/NonSeparableFilter.h"
#include "../filter/KuwaharaFilter.h"
#include "../filter/NonLocalMeansFilter.h"
#include "../filter/LocalBinaryPattern.h"
#include "../filter/ColorLookupTable.h"
#include "../filter/LogGabor.h"
#include "../filter/AnisotropicGaussian.h"

#include "../../histogram/histogram/FloatHistogram.h"

using namespace std;
using namespace stira;
using namespace stira::filter;
using namespace stira::fouriertools;
using namespace stira::histogram;
using namespace stira::imagedata;
using namespace stira::imagetools;

//======================================================================================================

bool RotateGaussianFFTConvolveTest( ArrayGrid<double>* pSourceGrid )
{
   int width  = pSourceGrid->GetWidth();
   int height = pSourceGrid->GetHeight();

   RigidTransform rt;
   ArrayGrid<double>* pPSF = GridGenerator::GenerateGaussian( width, height, 7.0, 1.0 );

   double theta = M_PI / 4.0;
   ArrayGrid<double>* pPsfRotated = rt.RotateAroundCenter( pPSF, theta );
   ArrayGrid<double>* pConvolved = FFT::Convolve( pSourceGrid, pPsfRotated );

   ImageIO::WritePGM( pPsfRotated,       string( "psfRotatedTest.ppm"),        ImageIO::NORMAL_OUT );
   ImageIO::WritePGM( pConvolved, string( "convolvedRotatedTest.ppm" ), ImageIO::NORMAL_OUT );

   assert( pPSF != 0);
   assert( pConvolved != 0 );

   delete pPSF;
   delete pPsfRotated;
   delete pConvolved;
   return true;
}

//======================================================================================================

bool FFTConvolveTest( ArrayGrid<double>* pSourceGrid )
{
   int width  = pSourceGrid->GetWidth();
   int height = pSourceGrid->GetHeight();

   ArrayGrid<double>* pPSF = GridGenerator::GenerateGaussian( width, height, 3.0, 3.0 );

   ArrayGrid<double>* pConvolved = FFT::Convolve( pSourceGrid, pPSF );

   ImageIO::WritePGM( pPSF,       string( "psftest.ppm"),        ImageIO::NORMAL_OUT );
   ImageIO::WritePGM( pConvolved, string( "convolvedtest.ppm" ), ImageIO::NORMAL_OUT );

   assert( pPSF != 0);
   assert( pConvolved != 0 );

   delete pPSF;
   delete pConvolved;
   return true;
}

//======================================================================================================

bool AnisotropicGaussianFilterTest( ArrayGrid<double>* pInputGrid )
{
   Image* pImageIn = new Image( pInputGrid );
   stira::filter::AnisotropicGaussian AG;
   double sigmaShortAxis = 1.0;
   double sigmaLongAxis  = 6.0;
   int orderShortAxis = 2;
   int orderLongAxis = 0;

   for (int i = 0; i < 180; i+= 90)
   {
      ArrayGrid<double>* pAniGaussGrid = AG.Run( pImageIn->GetBands()[0], sigmaShortAxis, sigmaLongAxis, common::MathUtils::ToRadians(double(i)), orderShortAxis, orderLongAxis);
      pAniGaussGrid->MultiplyWith( -1.0 );
      std::stringstream ss;
      ss << string("AnisotropicGaussian-") << setfill('0') << setw(4) << i << string(".png");
      std::string fileName = ss.str();
      ImageIO::WriteOpenCV( pAniGaussGrid, fileName, ImageIO::NORMAL_OUT);

      assert( pAniGaussGrid != 0 );

      delete pAniGaussGrid;
   }
   //delete pImageIn;
   return true;
}

//======================================================================================================

bool LoGTest(Image* pSourceImage)
{
   Image* pLogImage = stira::filter::LaplacianOfGaussianFilter::Run( pSourceImage );

   ImageIO::Write(pLogImage, string("LoGtest.ppm"), ImageIO::GRADIENT_OUT);

   assert( pLogImage != 0 );

   delete pLogImage;
   return true;
}

//======================================================================================================


bool DoGTest(Image* pSourceImage)
{
   double sigmaX1 = 5;
   double sigmaY1 = 3;
   double sigmaX2 = 5;
   double sigmaY2 = 9;
   Image* pDogImage = stira::filter::DifferenceOfGaussians::Run( pSourceImage, sigmaX1, sigmaY1, sigmaX2, sigmaY2 );

   ImageIO::Write( pDogImage, string("DoGtest.ppm"), ImageIO::GRADIENT_OUT);

   assert( pDogImage != 0 );

   delete pDogImage;
   return true;
}

//======================================================================================================

bool MedianFilterTest(Image* pSourceImage)
{
   Image* pABFImage = stira::filter::MedianFilter::RunHybridMedian( pSourceImage, 2 );
   //Image* pABFImage = stira::filter::MedianFilter::RunMedian( pSourceImage, 2 );

   assert( pABFImage != 0 );

   ImageIO::Write( pABFImage, string("HybridMedianFilterResult.pgm"), ImageIO::NULL_OUT);

   delete pABFImage;
   return true;
}

//======================================================================================================

bool AdaptiveBilateralFilterTest(Image* pSourceImage)
{
   Image* pABFImage = stira::filter::AdaptiveBilateralFilter::Run( pSourceImage );

   assert( pABFImage != 0 );

   ImageIO::Write(pABFImage, string("AdaptiveBilateralFilterResult.ppm"), ImageIO::NORMAL_OUT);

   delete pABFImage;
   return true;
}

//======================================================================================================

bool KuwaharaFilterTest(Image* pSourceImage)
{
   Image* pKFImage = stira::filter::KuwaharaFilter::Run( pSourceImage );

   assert( pKFImage != 0 );

   ImageIO::Write(pKFImage, string("KuwaharaFilterResult.ppm"), ImageIO::NORMAL_OUT );

   delete pKFImage;
   return true;
}

//======================================================================================================

bool SeparableFilterTest(Image* pSourceImage)
{
   int length = 3;
   double coeff = 1.0 / (double)(length);
   double pFilterX[ 3 ] = {coeff, coeff, coeff};
   double pFilterY[ 3 ] = {coeff, coeff, coeff};

   stira::filter::SeparableFilter sf;
   ArrayGrid<double>* pOutGrid = sf.SeparableFilter::RunRowColumn( pSourceImage->GetBands()[0], pFilterX, pFilterY, length, length );

   Image* pSeparableFilteredImage = new Image(pOutGrid);
   assert( pSeparableFilteredImage != 0 );

   ImageIO::Write(pSeparableFilteredImage, string("SeparableFilterResult.ppm"), ImageIO::NORMAL_OUT);

   delete pSeparableFilteredImage;
   return true;
}

//======================================================================================================

bool SeparableFilterEvenTest(Image* pSourceImage)
{
   int lengthX = 3;
   int lengthY = 3;
   double coeff = 1.0;
   double pFilterX[ 3 ] = {coeff, 0.0, -coeff};
   double pFilterY[ 3 ] = {coeff / 3.0, coeff / 3.0, coeff / 3.0};

   stira::filter::SeparableFilter sf;
   ArrayGrid<double>* pOutGridX = sf.SeparableFilter::RunRowColumn( pSourceImage->GetBands()[0], pFilterX, pFilterY, lengthX, lengthY );
   ImageIO::WritePGM( pOutGridX, string("SeparableFilterEvenResult1.ppm"), ImageIO::NORMAL_OUT );
   ImageIO::WriteTXT( pOutGridX, string("SeparableFilterEvenResult1.txt") );

   ArrayGrid<double>* pOutGridY = sf.SeparableFilter::RunRowColumn( pSourceImage->GetBands()[0], pFilterY, pFilterX, lengthY, lengthX );
   ImageIO::WritePGM( pOutGridY, string("SeparableFilterEvenResult2.ppm"), ImageIO::NORMAL_OUT );
   ImageIO::WritePGM( pOutGridY, string("SeparableFilterEvenResult2.txt") );


   ///////////////////////////////////////////////////////////////////////////////////////////////
   int width  = pSourceImage->GetWidth();
   int height = pSourceImage->GetHeight();
   ArrayGrid<bool>* pGrid = new ArrayGrid<bool>( width, height );
   pGrid->SetGridValues( false );


   double threshold1 = 2.0;
   double threshold2 = 4.0;
   double threshold3 = 4.0;
   for (int y = 1; y < height-1; y+=2)
   {
      for (int x = 1; x < width-1; x+=2)
      {
         if (
             // are we not in the background?
                 ( fabs( pOutGridX->GetValue( x,   y   ) ) > threshold1 )
              && ( fabs( pOutGridX->GetValue( x,   y+1 ) ) > threshold1 )
              && ( fabs( pOutGridX->GetValue( x+1, y   ) ) > threshold1 )
              && ( fabs( pOutGridX->GetValue( x+1, y+1 ) ) > threshold1 )
             // is pixel right under it similar enough?
              && ( fabs( pOutGridX->GetValue( x,   y   ) - pOutGridX->GetValue( x,   y+1 ) ) < threshold2 )
              && ( fabs( pOutGridX->GetValue( x+1, y+1 ) - pOutGridX->GetValue( x+1, y+1 ) ) < threshold2 )
             // are we on a step edge: is pixel at the right the negative of this pixel
              && ( fabs( pOutGridX->GetValue( x,   y   ) + pOutGridX->GetValue( x+1, y   ) ) < threshold3 )
              && ( fabs( pOutGridX->GetValue( x,   y+1 ) + pOutGridX->GetValue( x+1, y+1 ) ) < threshold3 )
            )
         {
            //pGrid->SetValue(x, y, true);
            pGrid->SetValue(x+1, y, true);
            //pGrid->SetValue(x, y+1, true);
            pGrid->SetValue(x+1, y+1, true);
         }
      }
   }

   ImageIO::WritePGM( pGrid, std::string("CandidateGridPoints.pgm" ) );
   delete pGrid;
   delete pOutGridX;
   delete pOutGridY;
   return true;
}

//======================================================================================================

bool NonSeparableFilterTest( Image* pSourceImage )
{
   double* pSobelXKernel = stira::filter::NonSeparableFilter::GetSobelXKernel();

   cout << "               [ " << pSobelXKernel[0] << "\t " <<  pSobelXKernel[1] << "\t " << pSobelXKernel[2] << " ]" << endl << flush;
   cout << "Sobel X kernel [ " << pSobelXKernel[3] << "\t " <<  pSobelXKernel[4] << "\t " << pSobelXKernel[5] << " ]" << endl << flush;
   cout << "               [ " << pSobelXKernel[6] << "\t " <<  pSobelXKernel[7] << "\t " << pSobelXKernel[8] << " ]" << endl << endl << flush;

   ArrayGrid<double>* pOutGridX = stira::filter::NonSeparableFilter::Run( pSourceImage->GetBands()[0], pSobelXKernel, 3, 3 );
   Image* pNonSeparableFilteredImageX = new Image( pOutGridX );

   assert( pNonSeparableFilteredImageX != 0 );

   ImageIO::Write( pNonSeparableFilteredImageX, string("NonSeparableFilter-SobelX-Result.ppm"), ImageIO::GRADIENT_OUT);

   delete pNonSeparableFilteredImageX;
   delete []pSobelXKernel;

   double* pSobelYKernel = stira::filter::NonSeparableFilter::GetSobelYKernel();

   cout << "               [  " << pSobelYKernel[0] << "\t  " <<  pSobelYKernel[1] << "\t  " << pSobelYKernel[2] << " ]" << endl << flush;
   cout << "Sobel Y kernel [  " << pSobelYKernel[3] << "\t  " <<  pSobelYKernel[4] << "\t  " << pSobelYKernel[5] << " ]" << endl << flush;
   cout << "               [ "  << pSobelYKernel[6] << "\t " <<   pSobelYKernel[7] << "\t "  << pSobelYKernel[8] << " ]" << endl << flush;

   ArrayGrid<double>* pOutGridY = stira::filter::NonSeparableFilter::Run( pSourceImage->GetBands()[0], pSobelYKernel, 3, 3 );
   Image* pNonSeparableFilteredImageY = new Image(pOutGridY);

   assert( pNonSeparableFilteredImageY != 0 );

   ImageIO::Write(pNonSeparableFilteredImageY, string("NonSeparableFilter-SobelY-Result.ppm"), ImageIO::GRADIENT_OUT);

   delete pNonSeparableFilteredImageY;
   delete []pSobelYKernel;
   return true;
}

//======================================================================================================

bool GaussianInterpolateTest( Image* pSourceImage )
{
   ArrayGrid<double>* pOutGrid = stira::filter::GaussConvolve::UpsampleGaussianInterpolated( pSourceImage->GetBands()[0], 4 );

   assert( pOutGrid != 0 );

   ImageIO::WritePGM( pOutGrid, string("GaussInterpolatedResult.ppm"), ImageIO::NORMAL_OUT);

   delete pOutGrid;
   return true;
}

//======================================================================================================

bool NonLocalMeansFilterTest( Image* pSourceImage )
{
   NonLocalMeansFilter nsf;

   Image* pNoisyImage = pSourceImage->Clone();
   double sigma = 10.0;  // sigma of the gaussian noise
   bool isColored = true;
   pNoisyImage->AddGaussianNoise( sigma, isColored );

   ImageIO::Write( pNoisyImage, string("ImageNoisyGauss10.pgm"), ImageIO::NORMAL_OUT);

   nsf.SetSigma( 80.0 );  // sigma of the weights of the blocks
   Image* pNLFiltered = nsf.Run( pNoisyImage );

   double psnr = ImageTools::ComputePSNR( pSourceImage, pNLFiltered );

   cout << "\t PSNR after = " << psnr << endl << flush;

   ImageIO::Write( pNLFiltered, string("Image")+pNLFiltered->GetImageName( )+string(".pgm"), ImageIO::NORMAL_OUT);
   delete pNoisyImage;
   delete pNLFiltered;
   return true;
}

//======================================================================================================

bool LogGaborFilterTest( Image* pSourceImage )
{
   LogGabor lg( pSourceImage );
   lg.Run();

   Image* pImgMag = lg.GetMagnitude( );
   ImageIO::Write( pImgMag, string("LogGabor-")+pSourceImage->GetImageName( )+string("-Magnitude.pgm"), ImageIO::NORMAL_OUT);
   delete pImgMag;  // we got a clone of the image, that we need to clean now


   Image* pImgReal = lg.GetRealResponse( );  // default rescaled between 0 and 255
   ImageIO::Write( pImgReal, string("LogGabor-")+pSourceImage->GetImageName( )+string("-Real.pgm"), ImageIO::NORMAL_OUT);
   delete pImgReal;  // we got a clone of the image, that we need to clean now

   Image* pImgImag = lg.GetImagResponse( );
   ImageIO::Write( pImgImag, string("LogGabor-")+pSourceImage->GetImageName( )+string("-Imag.pgm"), ImageIO::NORMAL_OUT);
   delete pImgImag;  // we got a clone of the image, that we need to clean now
   Image* pImgTransf = lg.GetTransferFunction();
   ImageIO::Write( pImgTransf, string("LogGabor-")+pSourceImage->GetImageName( )+string("-OTF.pgm"), ImageIO::NORMAL_OUT);
   delete pImgTransf;  // we got a clone of the image, that we need to clean now

   return true;
}

//======================================================================================================

bool GeometricTexturalPatternTest( Image* pSourceImage )
{
   int imWidth  = pSourceImage->GetWidth();
   int imHeight = pSourceImage->GetHeight();
   ArrayGrid<double>* pGrid = new ArrayGrid<double>( imWidth, imHeight );
   LocalBinaryPattern lbp;
   for (int y = 3; y < imHeight-3; y++)
   {
      for (int x = 3; x < imWidth-3; x++)
      {
         double myValue = lbp.ComputePointGLTP( pSourceImage->GetBands()[0], x, y, 5, true );
         pGrid->SetValue( x, y, myValue );
      }
   }

   ImageIO::WriteOpenCV(pGrid, std::string("GLTP.png") );
   delete pGrid;
   return true;

}

//======================================================================================================

bool LocalBinaryPatternSymmetricTest( Image* pSourceImage )
{
   int imWidth  = pSourceImage->GetWidth();
   int imHeight = pSourceImage->GetHeight();

   ColorLookupTable cLUT;

   Image* pImage = new Image( imWidth, imHeight, 3 );

   //double threshold = 5;
   double threshold = 1;

   ArrayGrid<int>* pGridLBP = new ArrayGrid<int>( imWidth, imHeight );
   ArrayGrid<double>* pGrid1 = new ArrayGrid<double>( imWidth, imHeight );
   ArrayGrid<double>* pGrid2 = new ArrayGrid<double>( imWidth, imHeight );
   ArrayGrid<double>* pGrid3 = new ArrayGrid<double>( imWidth, imHeight );
   LocalBinaryPattern lbp;
   for (int y = 3; y < imHeight-3; y++)
   {
      for (int x = 3; x < imWidth-3; x++)
      {
         int myValue = lbp.ComputePointLBPSym( pSourceImage->GetBands()[0], x, y, threshold, false );
         pGridLBP->SetValue( x, y, myValue );
         pGrid1->SetValue( x, y, cLUT.mLUT_R_last[myValue][0] );
         pGrid2->SetValue( x, y, cLUT.mLUT_R_last[myValue][1] );
         pGrid3->SetValue( x, y, cLUT.mLUT_R_last[myValue][2] );

         ColorValue cv( (double)(255) * cLUT.mLUT_R_last[myValue][2],
                        (double)(255) * cLUT.mLUT_R_last[myValue][1],
                        (double)(255) * cLUT.mLUT_R_last[myValue][0], TYPE_RGB );
         pImage->SetColor( x, y, cv);
      }
   }

   ImageIO::WriteOpenCV(pImage, std::string("LBPSym.png") );

   ImageIO::WriteOpenCV(pGrid1, std::string("LBPSym0.png") );
   ImageIO::WriteOpenCV(pGrid2, std::string("LBPSym1.png") );
   ImageIO::WriteOpenCV(pGrid3, std::string("LBPSym2.png") );

   delete pGridLBP;
   delete pGrid1;
   delete pGrid2;
   delete pGrid3;
   delete pImage;
   return true;
}

//-----------------------------------------------------------------------------------

void TestCompareYarns()
{
   Image *pImage1 = ImageIO::Read( string("../../../../stira/stira/testdata/CropOrig-2037.pgm") );
   Image *pImage2 = ImageIO::Read( string("../../../../stira/stira/testdata/CropOrig-2038.pgm") );
   Image *pImage3 = ImageIO::Read( string("../../../../stira/stira/testdata/CropOrig-2039.pgm") );

   int nrPoints = 8;
   double radius = 3.0;
   double initAngle = 0.01;

   LocalBinaryPattern lbp1( pImage1->GetBands()[0], initAngle, radius, nrPoints );
   FloatHistogram* pFH1 = lbp1.RunHistogram( );
   pFH1->Write( std::string("LBP-Norm-Histogram1.txt") );

   LocalBinaryPattern lbp2( pImage2->GetBands()[0], initAngle, radius, nrPoints );
   FloatHistogram* pFH2 = lbp2.RunHistogram( );
   pFH2->Write( std::string("LBP-Norm-Histogram2.txt") );

   LocalBinaryPattern lbp3( pImage3->GetBands()[0], initAngle, radius, nrPoints );
   FloatHistogram* pFH3 = lbp3.RunHistogram( );
   pFH3->Write( std::string("LBP-Norm-Histogram3.txt") );

   double KL12 = pFH1->ComputeSymmetricKullbackLeiblerDistance( pFH2 );
   double KL13 = pFH1->ComputeSymmetricKullbackLeiblerDistance( pFH3 );
   double KL23 = pFH2->ComputeSymmetricKullbackLeiblerDistance( pFH3 );

   double KL21 = pFH2->ComputeSymmetricKullbackLeiblerDistance( pFH1 );
   double KL31 = pFH3->ComputeSymmetricKullbackLeiblerDistance( pFH1 );
   double KL32 = pFH3->ComputeSymmetricKullbackLeiblerDistance( pFH2 );

   assert( fabs( KL12 - KL21 ) < 0.0001 );
   assert( fabs( KL13 - KL31 ) < 0.0001 );
   assert( fabs( KL23 - KL32 ) < 0.0001 );

   cout << " KL12 = " << KL12 << endl;
   cout << " KL13 = " << KL13 << endl;
   cout << " KL23 = " << KL23 << endl;

   cout << " KL21 = " << KL21 << endl;
   cout << " KL31 = " << KL31 << endl;
   cout << " KL32 = " << KL32 << endl;

   delete pImage1;
   delete pImage2;
   delete pImage3;

   delete pFH1;
   delete pFH2;
   delete pFH3;
}

//-----------------------------------------------------------------------------------

void TestLocalBinaryPattern()
{
   std::string filename = string("../../testdata/binary.pgm");
   Image *pImage = ImageIO::Read( filename );
   int width  = pImage->GetWidth();
   int height = pImage->GetHeight();
   ArrayGrid<double>* pGridOut = pImage->GetBands()[0]->Clone();

   int nrPoints = 8;
   double radius = 3.0;
   double initAngle = 0.01;

   LocalBinaryPattern lbp( pImage->GetBands()[0], initAngle, radius, nrPoints );

   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         int myValue = lbp.RunCode( x, y );
         pGridOut->SetValue( x, y, myValue );
      }
   }
   std::string fileOut("LocalBinaryPatternOut.pgm");
   ImageIO::WritePGM( pGridOut, fileOut, ImageIO::NORMAL_OUT );

   delete pImage;
   delete pGridOut;
}

//======================================================================================================

int main(int argc, char *argv[])
{
   string fileNamePGM;
   if (argc != 2)
   {
      fileNamePGM = string("../../../../stira/stira/testdata/lena512.pgm");
      //fileNamePGM = string("../../../../stira/stira/testdata/Rikki.pgm");
      //fileNamePGM = string("../../../../stira/stira/testdata/lena256-GaussianNoise.pgm");
      //fileNamePGM = string("../../../../stira/stira/testdata/bricks_zigzag_texture_6190218.PGM");
   }
   else
   {
      fileNamePGM = string(argv[1]);
   }

   cout << "Proceeding with tests with " << fileNamePGM << " as input image." << endl << flush;

   Image* pImage = 0;

   pImage = ImageIO::Read( fileNamePGM );

   cout << "Tests Filters" << endl << flush;

   ArrayGrid<double>* pInputGrid = pImage->GetBands()[0];

   // LIGHTWEIGHT FILTERS TESTS
   /////////////////////////////

   cout << "FFTConvolveTest: \t\t";
   if ( FFTConvolveTest( pInputGrid ) )
   {
      cout << "OK!" << endl << flush;
   }
   else
   {
      cout << "FAILED!" << endl << flush;
   }

   cout << "RotateGaussianFFTConvolveTest: \n";
   if ( RotateGaussianFFTConvolveTest( pInputGrid ) )
   {
      cout << "\t\t\t\tOK!" << endl << flush;
   }
   else
   {
      cout << "\t\t\t\tFAILED!" << endl << flush;
   }

   cout << "Laplacian of Gaussians Test: \t";
   if ( LoGTest( pImage ) )
   {
      cout << "OK!" << endl << flush;
   }
   else
   {
      cout << "FAILED!" << endl << flush;
   }

   cout << "Difference of Gaussians Test: \t";
   if ( DoGTest( pImage ) )
   {
      cout << "OK!" << endl << flush;
   }
   else
   {
      cout << "FAILED!" << endl << flush;
   }

   cout << "AnisotropicGaussianFilterTest: \t";
   if ( AnisotropicGaussianFilterTest( pInputGrid ) )
   {
      cout << "OK!" << endl << flush;
   }
   else
   {
      cout << "FAILED!" << endl << flush;
   }

   cout << "SeparableFilterTest: \t\t";
   if ( SeparableFilterTest( pImage ) )
   {
      cout << "OK!" << endl << flush;
   }
   else
   {
      cout << "FAILED!" << endl << flush;
   }

   cout << "NonSeparableFilterTest: \n";
   if ( NonSeparableFilterTest( pImage ) )
   {
      cout << "\t\t\t\tOK!" << endl << flush;
   }
   else
   {
      cout << "\t\t\t\tFAILED!" << endl << flush;
   }

   cout << "MedianFilterTest: \t";
   if ( MedianFilterTest( pImage ) )
   {
      cout << "OK!" << endl << flush;
   }
   else
   {
      cout << "FAILED!" << endl << flush;
   }

   cout << "SeparableFilterEvenTest: \t";
   if ( SeparableFilterEvenTest( pImage ) )
   {
      cout << "OK!" << endl << flush;
   }
   else
   {
      cout << "FAILED!" << endl << flush;
   }

   cout << "LogGaborFilterTest: \n";
   if ( LogGaborFilterTest( pImage ) )
   {
      cout << "\t\t\t\tOK!" << endl << flush;
   }
   else
   {
      cout << "\t\t\t\tFAILED!" << endl << flush;
   }

   cout << "GeometricTexturalPatternTest: \n";
   if ( GeometricTexturalPatternTest( pImage ) )
   {
      cout << "\t\t\t\tOK!" << endl << flush;
   }
   else
   {
      cout << "\t\t\t\tFAILED!" << endl << flush;
   }

   cout << "LocalBinaryPatternSymmetricTest: \n";
   if ( LocalBinaryPatternSymmetricTest( pImage ) )
   {
      cout << "\t\t\t\tOK!" << endl << flush;
   }
   else
   {
      cout << "\t\t\t\tFAILED!" << endl << flush;
   }

   // HEAVYWEIGHT FILTERS TESTS
   /////////////////////////////

   cout << "AdaptiveBilateralFilterTest: \t";
   if ( AdaptiveBilateralFilterTest( pImage ) )
   {
      cout << "OK!" << endl << flush;
   }
   else
   {
      cout << "FAILED!" << endl << flush;
   }

   cout << "NonLocalMeansFilterTest: \n";
   if ( NonLocalMeansFilterTest( pImage ) )
   {
      cout << "\t\t\t\tOK!" << endl << flush;
   }
   else
   {
      cout << "\t\t\t\tFAILED!" << endl << flush;
   }

   cout << "KuwaharaFilterTest: \t\t";
   if ( KuwaharaFilterTest( pImage ) )
   {
      cout << "OK!" << endl << flush;
   }
   else
   {
      cout << "FAILED!" << endl << flush;
   }

   cout << "GaussianInterpolateTest: \t";
   if ( GaussianInterpolateTest( pImage ) )
   {
      cout << "OK!" << endl << flush;
   }
   else
   {
      cout << "FAILED!" << endl << flush;
   }

   delete pImage;
}
