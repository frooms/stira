
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
#include "../../image/tools/ImageIO.h"
#include "../../avi/avi/avi.h"
#include "../../avi/avi/riff.h"
#include "../../avi/avi/frame.h"

#include "../../contrastenhance/contrastenhance/HistogramTools.h"
#include "../../contrastenhance/contrastenhance/Retinex.h"

#include "../../image/datastructures/CWTPyramid.h"
#include "../../steerable/pyramid/PyramidReal.h"
#include "../../wavelet/wavelet/CriticallySubsampledTransform.h"
#include "../../wavelet/wavelet/NonSubsampledTransform.h"
#include "../../pyramidapplications/pyramidapplications/PyramidDenoiser.h"
#include "../../pyramidapplications/pyramidapplications/PyramidContrastEnhancer.h"
//#define WRITE_PPM_FRAMES

using namespace std;
using namespace stira;
using namespace stira::image;
using namespace stira::contrastenhance;
using namespace stira::steerable;
using namespace stira::wavelet;
using namespace stira::pyramidapplications;


//======================================================================================

bool AviTest( )
{
   const char * aviFileName   = "../../testdata/gsale10.avi";
   tAVI_RGB  aviSequenceIn, aviSequenceOut;
   //tFrame* pMovieframe = 0;

   int contrastEnhancemethod = 0;

   aviSequenceIn.Read ( aviFileName  ); // reading sequence into buffer
   int width = aviSequenceIn.GetWidth();
   int height = aviSequenceIn.GetHeight();
   int nrFrames = aviSequenceIn.GetNumberOfFrames();
   int nrScales = 3;
   int nrOrientations = 4;

   cout << "nr frames = " << nrFrames << "  w = " << width << "  h = " << height << endl << flush;
   if ( contrastEnhancemethod == 0)
   {
      cout << "\t Combined video denoising and contrast enhancement." << endl << flush;
   }
   else
   {
      cout << "\t Pure video denoising." << endl << flush;
   }
   nrFrames = 40;

   aviSequenceOut.Write ("ProcessedSequence.avi", nrFrames, width, height);

   tFrame* pInputFrame    = new tFrame( width, height );
   tFrame* pFilteredFrame = new tFrame( width, height );

   for (int frameNR = 0; frameNR < nrFrames; frameNR++)
   {
      cout << "Processing frame " << frameNR << endl << flush;

      stira::image::Image* pImage = aviSequenceIn.GetFrameAsImage( frameNR, pInputFrame );

      #ifdef WRITE_PPM_FRAMES
      stringstream ss;
      ss << "Frame-" << frameNR << ".ppm";
      string fileName = ss.str();

      ImageIO::Write(pImage, fileName);
      #endif

      Image* pFilteredImage = new Image( pImage->GetWidth(), pImage->GetHeight() );

      //PyramidReal transf( pImage->GetBands()[0], nrScales, nrOrientations);
      //transf.Decompose();

      //CriticallySubsampledTransform transf;   nrOrientations = 3;

      NonSubsampledTransform transf;   nrOrientations = 3;

      transf.Decompose( pImage->GetBands()[0], nrScales );

      Pyramid<double>* pPyramid = transf.GetPyramid();

      PyramidDenoiser pd( pPyramid, BIVARIATE, 10.0);    pd.Run();

      if (contrastEnhancemethod == 0)
      {
         PyramidContrastEnhancer pce( 0.3 );
         pce.RunPyramid( pPyramid );
      }

      transf.Reconstruct( );
      ArrayGrid<double>* pGrid = transf.GetCopyOfReconstructedGrid();

      pFilteredImage->AddBand( pGrid );

      if (contrastEnhancemethod == 1)
      {
         HistogramTools heq;
         heq.HistogramEqualizeSingleBand( pGrid );
      }

      if (contrastEnhancemethod == 2)
      {
         Retinex ret;
         double lfrac = 0.03; // 0.03 emperically seemed a good value for turtle test image
         double ufrac = 0.99; //0.995 emperically seemed a good value for turtle test image

         ArrayGrid<double>* pGrid2 = Retinex::RunMSR( pGrid, lfrac, ufrac );
         pFilteredImage->RemoveBand( pGrid );
         pFilteredImage->AddBand( pGrid2 );
      }

      //int nrFrames = aviSequenceOut.GetNumberOfFrames();
      aviSequenceOut.WriteImageToFrame( frameNR, pFilteredFrame, pFilteredImage );
      delete pFilteredImage;
   }
   return true;
}



//======================================================================================

int main( int argc, char *argv[])
{
   AviTest();
   return 1;
}
