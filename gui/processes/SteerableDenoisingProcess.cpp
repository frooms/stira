
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

#include "SteerableDenoisingProcess.h"
#include "../../stira/imagetools/tools/ImageTools.h"
#include "../../stira/steerable/pyramid/PyramidReal.h"
#include "../../stira/pyramidapplications/pyramidapplications/PyramidDenoiser.h"

using namespace stira::pyramidapplications;
using namespace stira::steerable;
using namespace stira::imagetools;
using namespace stira::imagedata;


SteerableDenoisingProcess::SteerableDenoisingProcess( Image* pImage ) : Process( pImage )
{
   mProcessName = QString("Steerable Pyramid Denoised Result");
}

//--------------------------------------------------------

SteerableDenoisingProcess::~SteerableDenoisingProcess()
{
}

//--------------------------------------------------------

int SteerableDenoisingProcess::GetNrScales()
{
   return mNrScales;
}

//--------------------------------------------------------

void SteerableDenoisingProcess::SetNrScales(int nr)
{
   mNrScales = nr;
}

//--------------------------------------------------------

int SteerableDenoisingProcess::GetNrOrientations()
{
   return mNrOrientations;
}

//--------------------------------------------------------

void SteerableDenoisingProcess::SetNrOrientations(int nr)
{
   mNrOrientations = nr;
}

//--------------------------------------------------------

double SteerableDenoisingProcess::GetNoiseLevel()
{
   return mNoiseLevel;
}

//--------------------------------------------------------

void SteerableDenoisingProcess::SetNoiseLevel(double nl)
{
   mNoiseLevel = nl;
}

//--------------------------------------------------------

void SteerableDenoisingProcess::run()
{
   int width = mpImage->GetWidth();
   int height = mpImage->GetHeight();
   int nrBands = mpImage->GetNumberOfBands();
   
   int borderWidth  = ( width  / 2 );  if ( borderWidth  > 256) { borderWidth  = 256; }
   int borderHeight = ( height / 2 );  if ( borderHeight > 256) { borderHeight = 256; }

   Image* pExtendedImage = ImageTools::MirrorBorder( mpImage, borderWidth, borderHeight );

   Image* pFilteredImage = new Image( pExtendedImage->GetWidth(), pExtendedImage->GetHeight() );
   for (int k =0; k < nrBands; k++)
   {
      PyramidReal np( pExtendedImage->GetBands()[k], mNrScales, mNrOrientations);
      np.Decompose();
      
      PyramidDenoiser pd( np.GetPyramid(), BIVARIATE, mNoiseLevel);  // doesn't work yet with the complex pyramid!!!
      pd.Run();
      
      np.Reconstruct();
      pFilteredImage->AddBand( np.GetCopyOfReconstructedGrid() );
   }
   delete pExtendedImage;
   Image* pOutImage = ImageTools::CropBorder( pFilteredImage, borderWidth, borderHeight );
   delete pFilteredImage;
   std::string outName = mpImage->GetImageName() + std::string("-SteerableDenoise");
   pOutImage->SetImageName(outName);
   AddResult( pOutImage );
   // ownership of this image is transfered through GetImage() to ImageDataList
}

//--------------------------------------------------------
