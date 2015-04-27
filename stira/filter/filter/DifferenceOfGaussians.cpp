/***********************************************************************************
 *   Copyright (C) 2011 by Filip Rooms                                             *
 *                                                                                 *
 *  Terms and conditions for using this software in any form are provided in the   *
 *  file COPYING, which can be found in the root directory of this project.        *
 *                                                                                 *
 *   Contact data: filip.rooms@gmail.com                                           *
 *                 http://www.filiprooms.be/                                       *
 *                                                                                 *
 ***********************************************************************************/

#include "DifferenceOfGaussians.h"
#include "GaussConvolve.h"
#include "../../common/common/MathUtils.h"
#include "../../fouriertools/fouriertools/FFT.h"
#include "../../image/tools/GridExtender.h"
#include "../../image/tools/GridGenerator.h"
#include "../../image/tools/ImageIO.h"

//#define VISUALIZE_FILTERKERNEL

namespace stira{
namespace filter{

using namespace common;
using namespace fouriertools;
using namespace image;

//--------------------------------------------------------------------------

DifferenceOfGaussians::DifferenceOfGaussians( )
{
}

//--------------------------------------------------------------------------


DifferenceOfGaussians::~DifferenceOfGaussians( )
{
}

//--------------------------------------------------------------------------

ArrayGrid<double>* DifferenceOfGaussians::Run( ArrayGrid<double>* pGridIn, double sigmaX1, double sigmaY1, double sigmaX2, double sigmaY2 )
{
   int borderWidth = 20;
   int borderHeight = 20;
   ArrayGrid<double>* pGaussFilterKernel1 = 0;
   ArrayGrid<double>* pGaussFilterKernel2 = 0;

   ArrayGrid<double>* pInputExtendedGrid = GridExtender<double>::MirrorBorder( pGridIn, borderWidth, borderHeight);

   int width = pInputExtendedGrid->GetWidth();
   int height = pInputExtendedGrid->GetHeight();

   pGaussFilterKernel1 = GridGenerator::GenerateGaussian( width, height, sigmaX1, sigmaY1 );
   pGaussFilterKernel2 = GridGenerator::GenerateGaussian( width, height, sigmaX2, sigmaY2 );

   pGaussFilterKernel1->SubtractGrid( pGaussFilterKernel2 );

#ifdef VISUALIZE_FILTERKERNEL
   ImageIO::WritePGM( pGaussFilterKernel1, string("DoG-kernel.pgm"), ImageIO::GRADIENT_OUT);
#endif

   ArrayGrid<double>* pConvolvedGrid = FFT::Convolve( pInputExtendedGrid, pGaussFilterKernel1);

   delete pInputExtendedGrid;
   delete pGaussFilterKernel1;
   delete pGaussFilterKernel2;

   ArrayGrid<double>* pCroppedGrid = GridExtender<double>::CropBorder( pConvolvedGrid, borderWidth, borderWidth);

   delete pConvolvedGrid;
   return pCroppedGrid;
}

//--------------------------------------------------------------------------

image::ArrayGrid<double>* DifferenceOfGaussians::Run( image::ArrayGrid<double>* pGridIn, double sigmaX1, double sigmaX2, double sigmaY )
{
   return Run( pGridIn, sigmaX1, sigmaY, sigmaX2, sigmaY );
}

//--------------------------------------------------------------------------

image::Image* DifferenceOfGaussians::Run( image::Image* pImageIn, double sigmaX1, double sigmaY1, double sigmaX2, double sigmaY2 )
{
   Image* pImageOut = new Image( pImageIn->GetWidth(), pImageIn->GetHeight() );

   int nrBands = pImageIn->GetNumberOfBands();
   for ( int bandID = 0; bandID < nrBands; bandID++ )
   {
      ArrayGrid<double>* pFilteredBand = Run( pImageIn->GetBands()[bandID], sigmaX1, sigmaY1, sigmaX2, sigmaY2 );
      pImageOut->AddBand(pFilteredBand);
   }

   return pImageOut;
}

//--------------------------------------------------------------------------

image::Image* DifferenceOfGaussians::Run( image::Image* pImageIn, double sigmaX1, double sigmaX2, double sigmaY )
{
   return Run( pImageIn, sigmaX1, sigmaY, sigmaX2, sigmaY );
}

//--------------------------------------------------------------------------

}
}
