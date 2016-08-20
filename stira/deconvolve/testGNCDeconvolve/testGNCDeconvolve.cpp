
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

#include "../../imagetools/tools/ImageIO.h"
#include "../../imagetools/imagegenerator/GridGenerator.h"
#include "../../filter/filter/GaussConvolve.h"
#include "../../deconvolve/deconvolve/GNCDeconvolve.h"

#define CASE_SIMULATED_DEGRADATION

using namespace std;
using namespace stira::imagedata;
using namespace stira::imagetools;
using namespace stira::filter;
using namespace stira::deconvolve;

//========================================================================================

int main(int argc, char *argv[])
{
   Image* pInImage = 0;

   const char* inputname;
   if (argc == 2)
   {
      inputname = argv[1];
   }
   else
   {
      inputname = "../../../../stira/stira/testdata/circles.pgm";
   }
   
   pInImage = ImageIO::Read( inputname );
   Image* pImageSolution = 0;
   bool allSuccess = true;
   
   // PSF generation
   ////////////////////
   double sigmaBlur = 0.7;
   
   ArrayGrid<double>* pPSF = GridGenerator::GenerateGaussian( pInImage->GetWidth(), pInImage->GetHeight(), sigmaBlur, sigmaBlur);
   Image* pImagePSF = new Image( pPSF );
   ImageIO::Write(pImagePSF, string("GNC-PSFImage.ppm"), ImageIO::NORMAL_OUT );
   
   int nrbands = pImagePSF->GetNumberOfBands();
   if (nrbands > 1)
   {
      cout << "PSF has " << nrbands << " bands." << endl << flush;
   }
   else
   {
      cout << "PSF has " << nrbands << " band." << endl << flush;
   }
   
   //////////////////////////////////////////////////////
   // Simulate degraded image
   //////////////////////////////////////////////////////
   #ifdef CASE_SIMULATED_DEGRADATION
   double sigmaNoise = 5.0;
   Image* pTestImage = GaussConvolve::Convolve( pInImage, sigmaBlur, GaussConvolve::FFT_BASED);

   pTestImage->AddGaussianNoise( sigmaNoise );
   
   ImageIO::Write(pTestImage, string("GNC-DegradedImage.ppm"), ImageIO::NULL_OUT );
   #endif
   //////////////////////////////////////////////////////
   // GNC Deconvolve TESTS
   //////////////////////////////////////////////////////
   int nrIterations = 10;
   
   cout << "Running test with input image " << inputname << " using " << nrIterations << " iterations." << endl << flush;
   
   #ifdef CASE_SIMULATED_DEGRADATION
      GNCDeconvolve gncd(pTestImage, pImagePSF, nrIterations);
   #else
   // if INPUT IS ALREADY DEGRADED 
      pTestImage2 = pInImage;
      GNCDeconvolve gncd(pTestImage2, pImagePSF, nrIterations);
   #endif
      
      
   ImageIO::WritePGM( pTestImage->GetBands()[0], string("GNC-DegradedImageGray.pgm"), ImageIO::NULL_OUT);
      
   /*
   // Good values for circle image
   gncd.SetNumberOfScales( 4 );
   gncd.SetNumberOfOrientations( 8 );
   gncd.SetMu( 1.3 );
   gncd.SetLambda( 0.66 );
   gncd.SetUpdateFactor( 0.7 );
   gncd.SetGamma( 5.0 );
   gncd.SetGammaFinal( 2.5 );*/

   // 18/12/2008: good up to now
   /*gncd.SetNumberOfScales( 4 );
   gncd.SetNumberOfOrientations( 8 );
   gncd.SetMu( 1.4 );
   gncd.SetLambda( 0.66 );
   gncd.SetUpdateFactor( 0.7 );
   gncd.SetGamma( 6.0 );
   gncd.SetGammaFinal( 2.0 );*/
   
   // 18/12/2008: good up to now
   gncd.SetNumberOfScales( 4 );
   gncd.SetNumberOfOrientations( 8 );
   gncd.SetMu( 0.8 );
   gncd.SetLambda( 0.8 );
   gncd.SetUpdateFactor( 0.7 );
   gncd.SetGamma( 4.0 );
   gncd.SetGammaFinal( 2.0 );
   
   
   gncd.Run();
   pImageSolution = gncd.GetRestoredImage();
   
   //////////////////////////////////////////////////////
   // write output
   //////////////////////////////////////////////////////
   ImageIO::Write( pImageSolution, string("GNC-Solution.ppm"), ImageIO::NULL_OUT ); delete pImageSolution;
   
   if (allSuccess == true)
   {
      cout << "end: all tests ended successfully" << endl << flush;
   }
   else
   {
      cout << "end: *NOT* all tests ended successfully" << endl << flush;
   }

   delete pInImage;
   #ifdef CASE_SIMULATED_DEGRADATION
   delete pTestImage;
   #endif
   delete pImagePSF;
   //delete pImageSolution;
   return EXIT_SUCCESS;
}
