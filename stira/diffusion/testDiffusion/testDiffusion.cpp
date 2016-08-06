
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

/** \brief This file contains a few tests to verify correct functioning of some routines
  * 
  * These tests could also be used as examples on how to use the code.
  */

#include <iostream>
#include <cstdlib>
#include <cassert>
#include "../../imagedata/datastructures/Image.h"
#include "../../imagetools/tools/ImageIO.h"
#include "../../diffusion/diffusion/AnisotropicDiffusion.h"

using namespace std;
using namespace stira;
using namespace stira::diffusion;
using namespace stira::image;

//======================================================================================

bool DiffusionTest(Image* pImage)
{
   assert(pImage != 0);

   AnisotropicDiffusion ad( pImage );
   ad.SetMaxNumberOfIterations( 100 );
   ad.SetFlowFactor( 0.5 );
   Image* pDiffusedImage = 0;
   pDiffusedImage = ad.Run();
   assert( pDiffusedImage != 0 );

   assert( ImageIO::Write(pDiffusedImage, string("diffusedImage.pgm"), ImageIO::NORMAL_OUT) == true);
   delete pDiffusedImage;
   return true;
}

//======================================================================================

int main( )
{
   Image* pImage = 0;
   string fileNamePGM("../../../../stira/stira/testdata/lena512.pgm");
   pImage = ImageIO::Read( fileNamePGM );
   
   if (DiffusionTest( pImage) == true )
   {
      cout << "Diffusion test success!!" << endl << flush;
   }
   else
   {
      cout << "Diffusion test FAILED!!" << endl << flush;
   }
   if (pImage != 0) {delete pImage;}
   return 1;
}
