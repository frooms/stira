
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
#include "../../deconvolve/deconvolve/WienerDeconvolve.h"
#include "../../deconvolve/deconvolve/VanCittertLandweberDeconvolve.h"

using namespace std;
using namespace stira::imagedata;
using namespace stira::imagetools;
using namespace stira::deconvolve;
using namespace stira::filter;

bool TestWiener( Image* pTestImage, Image* pImagePSF, double sigmaNoise )
{
   WienerDeconvolve wd(pTestImage, pImagePSF);
   wd.SetSigmaNoise( sigmaNoise );
   wd.Run();
   Image* pFilteredImage = wd.GetRestoredImage();
   
   ImageIO::Write(pFilteredImage, string("WienerRestored.ppm"), ImageIO::NULL_OUT );
   delete pFilteredImage;
   return true;
}

//========================================================================================

bool TestLandweber( Image* pTestImage, Image* pImagePSF, double sigmaNoise )
{
   int maxNrIterations = 25;
   VanCittertLandweberDeconvolve decLandweber( pTestImage, pImagePSF, maxNrIterations);
   decLandweber.SetDeconvolutionType( DECONVOLVE_LANDWEBER );
   decLandweber.SetSigmaNoise( sigmaNoise );
   decLandweber.Run();
   Image* pFilteredImage = decLandweber.GetRestoredImage();
   
   ImageIO::Write(pFilteredImage, string("LandweberRestored.ppm"), ImageIO::NULL_OUT );
   delete pFilteredImage;
   return true;
}

//========================================================================================

bool TestVanCittert( Image* pTestImage, Image* pImagePSF, double sigmaNoise )
{
   int maxNrIterations = 25;
   VanCittertLandweberDeconvolve decVanCittert( pTestImage, pImagePSF, maxNrIterations);
   decVanCittert.SetDeconvolutionType( DECONVOLVE_VANCITTERT );
   decVanCittert.SetSigmaNoise( sigmaNoise );
   decVanCittert.Run();
   Image* pFilteredImage = decVanCittert.GetRestoredImage();
   
   ImageIO::Write(pFilteredImage, string("VanCittertRestored.ppm"), ImageIO::NULL_OUT );
   delete pFilteredImage;
   return true;
}

//========================================================================================

int main(int argc, char *argv[])
{
   Image* pInImage = 0;
   
   if (argc == 2)
   {
      pInImage = ImageIO::Read( argv[1] );
   }
   else
   {
      pInImage = ImageIO::Read( "../../../../stira/stira/testdata/circles.pgm" );
   }
   
   double sigmaBlur = 1.5;
   double sigmaNoise = 5.0;
   
   //////////////////////////////////////////////////////
   // WIENERTESTS
   //////////////////////////////////////////////////////
   Image* pTestImage = GaussConvolve::Convolve( pInImage, sigmaBlur, GaussConvolve::FFT_BASED);

   pTestImage->AddGaussianNoise( sigmaNoise );
   
   ArrayGrid<double>* pPSF = GridGenerator::GenerateGaussian( pInImage->GetWidth(), pInImage->GetHeight(), sigmaBlur, sigmaBlur);
   Image* pImagePSF = new Image( pPSF );
   
   cout << "PSF has " << pImagePSF->GetNumberOfBands() << " bands." << endl << flush;
   
   ImageIO::Write(pTestImage, string("DegradedImage.ppm"), ImageIO::NULL_OUT );
   
   if ( TestWiener( pTestImage, pImagePSF, sigmaNoise ) )
   {
      cout << "TestWiener OK" << endl << flush;
   }
   else
   {
      cout << "TestWiener failed" << endl << flush;
   }

   if ( TestLandweber( pTestImage, pImagePSF, sigmaNoise ) )
   {
      cout << "TestLandweber OK" << endl << flush;
   }
   else
   {
      cout << "TestLandweber failed" << endl << flush;
   }
   
   if ( TestVanCittert( pTestImage, pImagePSF, sigmaNoise ) )
   {
      cout << "TestLandweber OK" << endl << flush;
   }
   else
   {
      cout << "TestLandweber failed" << endl << flush;
   }
   delete pTestImage;
   delete pInImage;
   delete pPSF;
}
