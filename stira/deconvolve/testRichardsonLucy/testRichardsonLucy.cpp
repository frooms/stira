
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
#include "../../filter/filter/GaussConvolve.h"
#include "../../deconvolve/deconvolve/RichardsonLucyDeconvolve.h"
#include "../../deconvolve/deconvolve/SimulateDegradation.h"

using namespace std;
using namespace stira::image;
using namespace stira::filter;
using namespace stira::deconvolve;


bool TestRichardSonLucySimulated( std::string fileName )
{
   Image* pInImage = 0;
   int nrIterations = 15;
   double lambda = 0.0006;

   cout << "Running test with input image " << fileName << " using " << nrIterations << " iterations." << endl << flush;

   pInImage = ImageIO::Read( fileName );
   Image* pImageSolution = 0;
   bool allSuccess = true;

   //////////////////////////////////////////////////////
   // Simulate degraded image
   //////////////////////////////////////////////////////
   vector<double> vBlurParameters;
   double sigmaBlur = 1.5; vBlurParameters.push_back(sigmaBlur);
   double sigmaNoise = 5.0;
   Image* pTestImage = SimulateDegradation::Run( pInImage, NOISETYPE_GAUSSIAN, sigmaNoise, BLURTYPE_GAUSSIAN, vBlurParameters );

   ImageIO::Write(pTestImage, string("RL-DegradedImage.ppm"), ImageIO::NULL_OUT );

   //////////////////////////////////////////////////////
   // Richardson-Lucy TESTS
   //////////////////////////////////////////////////////
   ArrayGrid<double>* pPSF = GridGenerator::GenerateGaussian( pInImage->GetWidth(), pInImage->GetHeight(), sigmaBlur, sigmaBlur);
   Image* pImagePSF = new Image( pPSF );
   cout << "PSF has " << pImagePSF->GetNumberOfBands() << " bands." << endl << flush;

   RichardsonLucyDeconvolve rld(pTestImage, pImagePSF, REGULARIZE_TOTAL_VARIATION, nrIterations);

   rld.SetLambda( lambda );
   //rld.SetRegularizationType( REGULARIZE_TIKHONOV_MILLER);     // value for lambda around 0.00062; unstable 0.0007 and higher
   //rld.SetRegularizationType( REGULARIZE_CONCHELLO ); // value for lambda around 0.000051; if larger, image is dimmed; if smaller, risk on instability
   //rld.SetRegularizationType( REGULARIZE_MAXIMUM_ENTROPY );rld.SetLambda( 0.0005 );

   lambda = 0.015;
   rld.SetLambda( lambda );
   rld.SetRegularizationType(REGULARIZE_TOTAL_VARIATION );  // value for lambda around 0.002 or higher
   rld.SetSigmaNoise( sigmaNoise );
   rld.Run();
   pImageSolution = rld.GetRestoredImage();

   //////////////////////////////////////////////////////
   // write output
   //////////////////////////////////////////////////////
   ImageIO::Write( pImageSolution, string("RL-Solution.ppm"), ImageIO::NULL_OUT ); delete pImageSolution;


   if (allSuccess == true)
   {
      cout << "end: all tests ended successfully" << endl << flush;
   }
   else
   {
      cout << "end: *NOT* all tests ended successfully" << endl << flush;
   }

   delete pInImage;
   delete pTestImage;
   delete pImagePSF;
   return true;
}

//========================================================================================

bool TestRichardSonLucyMotionBlur( std::string fileName )
{
   Image* pInImage = 0;
   int nrIterations = 30;
   double lambda = 0.03;

   cout << "Running test with input image " << fileName << " using " << nrIterations << " iterations." << endl << flush;

   pInImage = ImageIO::Read( fileName );
   Image* pImageSolution = 0;
   bool allSuccess = true;

   //////////////////////////////////////////////////////
   // Richardson-Lucy TESTS
   //////////////////////////////////////////////////////
   ArrayGrid<double>* pPSF = GridGenerator::GenerateLine( pInImage->GetWidth(), pInImage->GetHeight(), 7, 0 );
   ArrayGrid<double>* pPSF2 = GaussConvolve::Convolve( pPSF, 0.5 );
   delete pPSF;
   Image* pImagePSF = new Image( pPSF2 );
   cout << "PSF has " << pImagePSF->GetNumberOfBands() << " bands." << endl << flush;
   ImageIO::Write( pImagePSF, string("RL-PSF-MotionBlur.ppm"), ImageIO::NORMAL_OUT ); delete pImageSolution;

   RichardsonLucyDeconvolve rld( pInImage, pImagePSF, REGULARIZE_TOTAL_VARIATION, nrIterations);
   rld.SetLambda( lambda );
   rld.SetSigmaNoise( 0.01 );
   rld.SetRegularizationType(REGULARIZE_TOTAL_VARIATION );  // value for lambda around 0.002 or higher
   rld.Run();
   pImageSolution = rld.GetRestoredImage();

   //////////////////////////////////////////////////////
   // write output
   //////////////////////////////////////////////////////
   ImageIO::Write( pImageSolution, string("RL-Solution-MotionBlur.ppm"), ImageIO::NULL_OUT ); delete pImageSolution;


   if (allSuccess == true)
   {
      cout << "end: all tests ended successfully" << endl << flush;
   }
   else
   {
      cout << "end: *NOT* all tests ended successfully" << endl << flush;
   }

   delete pInImage;
   delete pImagePSF;
   return true;
}

//========================================================================================

int main(int argc, char *argv[])
{
   const char* inputname;
   if (argc == 2)
   {
      inputname = argv[1];
   }
   else
   {
      inputname = "../../../../stira/stira/testdata/circles.pgm";
   }

   cout << "Running test with input image " << inputname << endl << flush;
   TestRichardSonLucySimulated( inputname );
   TestRichardSonLucyMotionBlur( inputname );

   return EXIT_SUCCESS;
}
