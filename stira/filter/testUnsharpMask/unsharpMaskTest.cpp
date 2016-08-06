
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
#include "../../imagedata/datastructures/Image.h"
#include "../../imagetools/tools/ImageIO.h"
#include "../../imagetools/imagegenerator/GridGenerator.h"

#include "../../fouriertools/fouriertools/FFT.h"
#include "../filter/GaussConvolve.h"
#include "../filter/UnsharpMask.h"

using namespace std;
using namespace stira;
using namespace stira::filter;
using namespace stira::fouriertools;
using namespace stira::image;

//======================================================================================================

int main(int argc, char *argv[])
{
   string fileNamePGM;
   if (argc != 2)
   {
      fileNamePGM = string("../../../../stira/stira/testdata/lena256.pgm");
   }
   else
   {
      fileNamePGM = string(argv[1]);
   }
   
   cout << "Proceeding with tests with " << fileNamePGM << " as input image." << endl << flush;
   
   Image* pImage = ImageIO::Read( fileNamePGM );

   double sigmaBlur = 1.5;
   double sigmaNoise = 0.5;
   Image* pImageBlurred = GaussConvolve::Convolve( pImage, sigmaBlur, GaussConvolve::FFT_BASED );

   pImageBlurred->AddGaussianNoise( sigmaNoise );
   ImageIO::Write( pImageBlurred, string("DegradedInput.ppm"), ImageIO::NULL_OUT);
   
   double sigma = 1.5;
   double factor = 1.5;
   image::Image* pOutImage = UnsharpMask::Run( pImageBlurred, sigma, factor );

   ImageIO::Write( pOutImage, string("UnsharpMaskResult.ppm"), ImageIO::NULL_OUT);

   delete pImage;
   delete pOutImage;
}
