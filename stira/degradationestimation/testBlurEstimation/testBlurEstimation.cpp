
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
#include "../../common/common/MathUtils.h"
#include "../../imagetools/tools/ImageIO.h"
#include "../../imagetools/imagegenerator/GridGenerator.h"
#include "../../wavelet/wavelet/NoiseEstimator.h"
#include "../../filter/filter/GaussConvolve.h"
#include "../degradationestimation/BlurEstimator.h"
#include "../degradationestimation/BlurEstimatorHu.h"

using namespace std;
using namespace stira::common;
using namespace stira::imagedata;
using namespace stira::imagetools;
using namespace stira::filter;
using namespace stira::degradationestimation;
using namespace stira::wavelet;

//-------------------------------------------------------------------

void TestBlurestimate( Image* pImage, double sigmaBlur, double sigmaNoise )
{
   Image* pImage2 = GaussConvolve::ConvolveSeparable( pImage, sigmaBlur );
   //pImage2->AddGaussianNoise( sigmaNoise );

   ImageIO::Write( pImage2, std::string("TestBlurEstimateInput.pgm") );
   BlurEstimator myBE;
   myBE.SetNoiseLevel( sigmaNoise );
   double estimatedBlur = myBE.Run( pImage2->GetBands()[0] );
   cout << "In TestBlurestimate: input blur is " << sigmaBlur << " and estimated blur is " << estimatedBlur << endl << flush;
   delete pImage2;
}

//-------------------------------------------------------------------

void TestBlurEstimateHu( Image* pImage, double sigmaBlur )
{
   Image* pImage2 = GaussConvolve::ConvolveSeparable( pImage, sigmaBlur );
   ImageIO::Write( pImage2, std::string("TestBlurEstimateInputHu.pgm") );
   //pImage2->AddGaussianNoise( sigmaNoise );

   BlurEstimatorHu myBE;
   myBE.Run( pImage2->GetBands()[0] );

   delete pImage2;
}

//-------------------------------------------------------------------

int main(int argc, char *argv[])
{
   Image* pImage = 0;
   double sigmaBlur;

   const char* inputname;
   if (argc == 3)
   {
      inputname =  argv[1];
      sigmaBlur = atof( argv[2] );
   }
   else if (argc == 2)
   {
      inputname = argv[1];
      sigmaBlur   = 2.0;
   }
   else
   {
      inputname = "../../../../stira/stira/testdata/lena512.pgm";
      sigmaBlur   = 2.0;
   }

   pImage = ImageIO::Read( inputname );

   //TestBlurestimate(   pImage, sigmaBlur, sigmaNoise );
   TestBlurEstimateHu( pImage, sigmaBlur );
   delete pImage;
}
