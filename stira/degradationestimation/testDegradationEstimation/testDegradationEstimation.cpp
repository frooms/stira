
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
#include "../../imagetools/tools/ImageIO.h"
#include "../../wavelet/wavelet/NoiseEstimator.h"
#include "../degradationestimation/CompareSmoothSharpDijk.h"
#include "../../steerable/pyramid/PyramidReal.h"
#include "../../pyramidapplications/pyramidapplications/PyramidDenoiser.h"
#include "../../filter/filter/GaussConvolve.h"
#include "../../filter/filter/KuwaharaFilter.h"

using namespace std;
using namespace stira::imagedata;
using namespace stira::imagetools;
using namespace stira::filter;
using namespace stira::degradationestimation;
using namespace stira::wavelet;
using namespace stira::steerable;
using namespace stira::pyramidapplications;

//-------------------------------------------------------------------

Image* PyramidDenoise(Image* pImage, int nrScales, int nrOrientations, double noiseLevel)
{
   int nrBands = pImage->GetNumberOfBands();
   
   Image* pFilteredImage = new Image( pImage->GetWidth(), pImage->GetHeight() );
   for (int k =0; k < nrBands; k++)
   {
      PyramidReal np(pImage->GetBands()[k], nrScales, nrOrientations);
      np.Decompose();
      
      PyramidDenoiser pd( np.GetPyramid(), BIVARIATE, noiseLevel);
      pd.Run();
      
      np.Reconstruct();
      pFilteredImage->AddBand( np.GetCopyOfReconstructedGrid() );
   }

   return pFilteredImage;
}

//-------------------------------------------------------------------

void TestDeNoise( Image* pImage, double sigmaNoise )
{
   Image* pImage2 = pImage->Clone();
   pImage2->AddGaussianNoise( sigmaNoise );
   
   double noiseLevel = NoiseEstimator::Run( pImage2->GetBands()[0] );
   cout << "Estimated noise level = " << noiseLevel << endl << flush;
   
   Image* pImage3 = PyramidDenoise( pImage2, 3, 8, 3.0 );
   CompareSmoothSharpDijk cssd( pImage2, pImage3, std::string("denoise") );
   cssd.Run();
   delete pImage2;
   delete pImage3;
}

//-------------------------------------------------------------------

void TestKuwahara( Image* pImage )
{
   Image* pImage2 = KuwaharaFilter::Run( pImage );

   CompareSmoothSharpDijk cssd( pImage, pImage2, std::string("kuwahara") );
   cssd.Run();
   delete pImage2;
}

//-------------------------------------------------------------------

void TestBlur( Image* pImage, double sigmaBlur )
{
   Image* pImage2 = GaussConvolve::ConvolveSeparable( pImage, sigmaBlur );
   CompareSmoothSharpDijk cssd( pImage, pImage2, std::string("blur") );
   cssd.Run();
   delete pImage2;
}

//-------------------------------------------------------------------

void TestBlurNoise( Image* pImage, double sigmaBlur, double sigmaNoise )
{
   Image* pImage2 = GaussConvolve::ConvolveSeparable( pImage, sigmaBlur );
   Image* pImage3 = pImage2->Clone();
   pImage3->AddGaussianNoise( sigmaNoise );
   CompareSmoothSharpDijk cssd( pImage2, pImage3, std::string("blurnoise") );
   cssd.Run();
   delete pImage2;
   delete pImage3;
}

//-------------------------------------------------------------------

int main(int argc, char *argv[])
{
   Image* pImage = 0;
   double sigmaNoise, sigmaBlur;

   const char* inputname;
   if (argc == 4)
   {
      inputname =  argv[1];
      sigmaNoise = atof( argv[2] );
      sigmaBlur = atof( argv[3] );
   }
   else if (argc == 2)
   {
      inputname = argv[1];
      sigmaNoise  = 10.0;
      sigmaBlur   = 2.0;
   }
   else
   {
      //inputname = "../../../../stira/stira/testdata/nematodes2.pgm";
      //inputname = "../../../../stira/stira/testdata/circles.pgm";
      //inputname = "../../../../stira/stira/testdata/cameraman2.pgm";
      inputname = "../../../../stira/stira/testdata/lena256.pgm";
      sigmaNoise    = 10.0;
      sigmaBlur   = 2.0;
   }
   
   pImage = ImageIO::Read( inputname );
   //TestNoiseEstimator( pImage, sigmaNoise );
   TestBlur( pImage, sigmaBlur );
   
   TestKuwahara( pImage );
   //TestPureNoise( pImage, sigmaNoise );
   TestBlurNoise( pImage, sigmaBlur, sigmaNoise );
}
