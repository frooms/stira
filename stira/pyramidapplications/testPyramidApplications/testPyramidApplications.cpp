
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

#include "../../image/tools/ImageIO.h"
#include "../../image/tools/GridGenerator.h"
#include "../../image/tools/ImageTools.h"
#include "../../image/datastructures/CWTPyramid.h"
#include "../../steerable/pyramid/PyramidReal.h"
#include "../../steerable/pyramid/PyramidComplex.h"

#include "../../steerable/freemanadelson/ComputeSteerableFilteredImages.h"
#include "../../steerable/orientationestimation/ComputeOrientation.h"

#include "../pyramidapplications/PyramidDenoiser.h"
#include "../pyramidapplications/PyramidContrastEnhancer.h"
#include "../pyramidapplications/PyramidKeyPointDetector.h"

using namespace std;
using namespace stira::image;
using namespace stira::fouriertools;
using namespace stira::steerable;
using namespace stira::pyramidapplications;

//========================================================================================

bool AverageConeRatioTest(Image* pImage, int nrScales, int nrOrientations)
{
   int nrBands = pImage->GetNumberOfBands();
   int width = pImage->GetWidth();
   int height = pImage->GetHeight();
   int border = 8;
   bool needsInitialisation = true;
   double initialValue = 0.0;
   ArrayGrid<double>* pACRGrid = new ArrayGrid<double>( width, height, needsInitialisation, initialValue );

   for (int k = 0; k < nrBands; k++)
   {
      PyramidReal np( pImage->GetBands()[k], nrScales, nrOrientations );
      np.Decompose();

      //np.GetPyramid()->ExportBandsToPGM();
      Pyramid<double>* pPyr = np.GetPyramid();

      for (int orientationNr = 0; orientationNr < nrOrientations; orientationNr++)
      {
         //cout << "Processing orientation " << orientationNr << endl << flush;
         for (int y = border; y < height-border; y++)
         {
            for (int x = border; x < width-border; x++)
            {
               pACRGrid->SetValue( x, y, pPyr->GetAverageConeRatioSubSampled( x, y, orientationNr, 0, nrScales ) - 1.0 );
            }
         }
         //NumberGridTools<double>::DiagnoseReal( pACRGrid );
         std::stringstream ss;
         ss << std::string("ACR_Image_") << k << std::string("_") << orientationNr << ".pgm";
         std::string fileName = ss.str();
         ImageIO::WritePGM( pACRGrid, fileName, ImageIO::NORMAL_OUT );
         //ss << std::string("ACR_Image_") << k << std::string("_") << orientationNr << ".txt";
         //std::string fileName = ss.str();
         //ImageIO::WriteTXT( pACRGrid, fileName );
      }
   }

   delete pACRGrid;
   return true;
}

//========================================================================================

bool PyramidRealDenoiseTest(Image* pImage, int nrScales, int nrOrientations)
{
   double sigmaNoise = 10.0;
   bool isColored = true;
   int paddedBorderWidth = 64;
   int nrBands = pImage->GetNumberOfBands();
   Image* pImageNoise = ImageTools::MirrorBorder( pImage, paddedBorderWidth, paddedBorderWidth );

   Image* pFilteredImage = new Image( pImageNoise->GetWidth(), pImageNoise->GetHeight() );
   pImageNoise->AddGaussianNoise( sigmaNoise, isColored );

   ImageIO::Write( pImageNoise, std::string("NoisyInput-Real.ppm"), ImageIO::NULL_OUT );

   //ImageIO::Write( pImageNoise, "SteerableNoise.ppm", ImageIO::NULL_OUT);

   cout << "Input denoising: width = " << pImageNoise->GetWidth() << " height = " << pImageNoise->GetHeight() << endl;

   for (int k = 0; k < nrBands; k++)
   {
      PyramidReal np( pImageNoise->GetBands()[k], nrScales, nrOrientations);
      //PyramidComplex np(pInImage->GetBands()[k], nrScales, nrOrientations);
      np.Decompose();

      //np.GetPyramid()->ExportBandsToPGM();

      PyramidDenoiser pd( np.GetPyramid(), BIVARIATE, 3.5);  // doesn't work yet with the complex pyramid!!!
      pd.Run();

      np.Reconstruct();
      pFilteredImage->AddBand( np.GetCopyOfReconstructedGrid() );
      cout << "Added reconstructed band " << k  << " width = " << pFilteredImage->GetBands()[k]->GetWidth()
                                               << " height = " << pFilteredImage->GetBands()[k]->GetHeight() << endl;
   }

   cout << "Before cropping, width = " << pFilteredImage->GetWidth()
                                            << " height = " << pFilteredImage->GetHeight() << endl;
   Image* pImageOut = ImageTools::CropBorder( pFilteredImage, paddedBorderWidth, paddedBorderWidth );

   cout << "After cropping, width = " << pImageOut->GetWidth()
                                            << " height = " << pFilteredImage->GetHeight() << endl;

   ImageIO::Write( pImageOut, "SteerableRealDenoised.ppm", ImageIO::NULL_OUT);
   cout << "\t PyramidDenoiseTest PSNR = "<< ImageTools::ComputePSNR( pImage, pImageOut ) << endl << flush;

   delete pImageNoise;
   delete pImageOut;
   delete pFilteredImage;
   return true;
}

//========================================================================================

bool PyramidContrastEnhanceTest(Image* pImage, int nrScales, int nrOrientations)
{
   int nrBands = pImage->GetNumberOfBands();

   Image* pFilteredImage = new Image( pImage->GetWidth(), pImage->GetHeight() );
   for (int k =0; k < nrBands; k++)
   {
      PyramidReal np(pImage->GetBands()[k], nrScales, nrOrientations);
      //PyramidComplex np(pInImage->GetBands()[k], nrScales, nrOrientations);
      np.Decompose();

      PyramidContrastEnhancer pce( 0.3 );  // doesn't work yet with the complex pyramid!!!
      pce.RunPyramid( np.GetPyramid() );

      np.Reconstruct();
      pFilteredImage->AddBand( np.GetCopyOfReconstructedGrid() );
   }
   ImageIO::Write( pFilteredImage, "SteerableContrastEnhanced.ppm", ImageIO::NORMAL_OUT );

   delete pFilteredImage;
   return true;
}

//========================================================================================

bool PyramidContrastEnhanceTestColor(Image* pImage, int nrScales, int nrOrientations)
{
   PyramidContrastEnhancer pce( 0.5 );

   Image* pImageLuv = pImage->Clone();

   pImageLuv->sRGBToLuv();
   Image* pOutImage = pce.Run3Colors( pImageLuv, nrScales, nrOrientations, false );
   pOutImage->LuvTosRGB();

   ImageIO::Write( pOutImage, "SteerableContrastEnhancedColor.ppm", ImageIO::NORMAL_OUT );

   delete pOutImage;
   delete pImageLuv;
   return true;
}

//========================================================================================

bool PyramidContrastEnhanceTestFactors( )
{
   PyramidContrastEnhancer pce( 0.3 );
   std::string fileName = std::string("PyramidContrastFactors.txt");
   double myMin =   0.0;
   double myMax = 100.0;
   double stepSize = 0.5;
   pce.SetUpperLimitAmplification( 15.0 );
   //pce.PrintParameters();
   pce.TestAmplificationfactor( fileName, myMin, myMax, stepSize );

   return true;
}

//========================================================================================

bool PyramidKeyPoint( Image* pImage, int nrScales, int nrOrientations)
{
   int nrBands = pImage->GetNumberOfBands();

   for (int k =0; k < nrBands; k++)
   {
      PyramidComplex np(pImage->GetBands()[k], nrScales, nrOrientations);
      np.Decompose();

      PyramidKeyPointDetector pkpd( np.GetPyramid() );  // doesn't work with the real pyramid!!!
      pkpd.Run();
   }
   return true;
}

//========================================================================================

bool PyramidOrientationTest(Image* pImage, int nrScales, int nrOrientations)
{
   PyramidComplex np(pImage->GetBands()[0], nrScales, nrOrientations);
   np.Decompose();

   //np.GetPyramid()->ExportBandsToPGM();

   for (int scaleNr = 0; scaleNr < nrScales; scaleNr++)
   {
      stringstream ssOri;
      ssOri << "Pyr-Orientation-" << scaleNr << ".ppm";
      stringstream ssMag;
      ssMag << "Pyr-Magnitude-" << scaleNr << ".ppm";
      OrientationGrid* pOrientationGridRec = ComputeOrientation::ComputeDominantOrientationInputComplexPyramidLevel( np.GetPyramid()->GetRecursiveScale( scaleNr ) );

      pOrientationGridRec->ExportMagnitudeImage( ssMag.str() );
      pOrientationGridRec->ExportOrientationImage( ssOri.str(), 2.0);

      delete pOrientationGridRec;
   }
   stringstream ssOri;
   ssOri << "Pyr-Orientation-res.ppm";
   stringstream ssMag;
   ssMag << "Pyr-Magnitude-res.ppm";
   OrientationGrid* pOrientationGridResid = ComputeOrientation::ComputeDominantOrientationInputComplexPyramidLevel( np.GetPyramid()->GetResidualScale() );

   pOrientationGridResid->ExportMagnitudeImage( ssMag.str() );
   pOrientationGridResid->ExportOrientationImage( ssOri.str(), 2.0);

   delete pOrientationGridResid;

   return true;
}

//========================================================================================

int main(int argc, char *argv[])
{
   Image* pImage = 0;

   int nrScales = 4;
   int nrOrientations = 4;
   const char* inputname;

   bool allTestsOK = true;
   if (argc == 4)
   {
      inputname =  argv[1];
      nrScales       = atoi( argv[2] );
      nrOrientations = atoi( argv[3] );
   }
   else if (argc == 2)
   {
      inputname =  argv[1];
   }
   else
   {
      //inputname = "../../../../stira/stira/testdata/testhaze.ppm";
      inputname = "../../../../stira/stira/testdata/Lenna.ppm";
      //inputname = "../../../../stira/stira/testdata/testKeyPoints.ppm";
      //inputname = "../../../../stira/stira/testdata/cameraman2.pgm";
   }
   cout << endl << endl << "# Running test with input image " << inputname << endl << flush;
   cout << "#\t nr scales = " << nrScales << " and nr of orientations = " << nrOrientations << endl << flush;
   cout << "##################################################################" << endl << flush;

   pImage = ImageIO::Read( inputname );

   if ( PyramidOrientationTest( pImage, nrScales, nrOrientations) == true )
   {
      cout << "  * Orientation Estimation \t OK" << endl << flush;
   }
   else
   {
      cout << "  * Orientation Estimation \t FAILED" << endl << flush;
      allTestsOK = false;
   }

   if (PyramidRealDenoiseTest( pImage, nrScales, nrOrientations) == true )
   {
      cout << "  * PyramidRealDenoiseTest \t\t OK" << endl << flush;
   }
   else
   {
      cout << "  * PyramidRealDenoiseTest \t\t FAILED" << endl << flush;
      allTestsOK = false;
   }

   if (PyramidContrastEnhanceTest( pImage, nrScales, nrOrientations) == true )
   {
      PyramidContrastEnhanceTestFactors();
      cout << "  * ContrastEnhance per band \t OK" << endl << flush;
   }
   else
   {
      cout << "  * ContrastEnhance per band \t FAILED" << endl << flush;
      allTestsOK = false;
   }

   if (PyramidContrastEnhanceTestColor( pImage, nrScales, nrOrientations) == true )
   {
      PyramidContrastEnhanceTestFactors();
      cout << "  * ContrastEnhanceColor \t OK" << endl << flush;
   }
   else
   {
      cout << "  * ContrastEnhanceColor \t FAILED" << endl << flush;
      allTestsOK = false;
   }

   if (AverageConeRatioTest( pImage, nrScales, nrOrientations) == true )
   {
      cout << "  * AverageConeRatioTest \t OK" << endl << flush;
   }
   else
   {
      cout << "  * AverageConeRatioTest \t FAILED" << endl << flush;
      allTestsOK = false;
   }

   if (PyramidKeyPoint( pImage, nrScales, nrOrientations*2) == true )
   {
      cout << "  * PyramidKeyPointTest \t OK" << endl << flush;
   }
   else
   {
      cout << "  * PyramidKeyPointTest \t FAILED" << endl << flush;
      allTestsOK = false;
   }

   if (allTestsOK)
   {
      cout << "end: all tests ended successfully!!" << endl << flush;
   }
   else
   {
      cout << "end: *NOT* all tests ended successfully..." << endl << flush;
   }

   delete pImage;

   return EXIT_SUCCESS;
}
