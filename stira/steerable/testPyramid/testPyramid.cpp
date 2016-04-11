
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

#include "../../common/common/ExecutionTimer.h"

#include "../../image/tools/ImageIO.h"
#include "../../image/tools/PyramidTools.h"

#include "../../filter/filter/SeparableFilter.h"
#include "../../filter/filter/GaussConvolve.h"

#include "../pyramid/PyramidReal.h"
#include "../pyramid/PyramidComplex.h"
#include "../pyramid/PyramidBurtAdelson.h"

#include "../freemanadelson/ComputeSteerableFilteredImages.h"
#include "../orientationestimation/ComputeOrientation.h"

#define DIAGNOSE

using namespace std;
using namespace stira::common;
using namespace stira::image;
using namespace stira::fouriertools;
using namespace stira::filter;
using namespace stira::steerable;

//========================================================================================

bool SteerableFreemanAdelsonTest( Image* pImage )
{
   assert(pImage != 0);

   ComputeSteerableFilteredImages csf( pImage->GetBands()[0] );
   assert( csf.Run() == 1);
   return true;
}

//========================================================================================

bool TestPyramidBurtAdelson( Image* pImage )
{
   assert(pImage != 0);

   int nrScales = 4;

   PyramidBurtAdelson pba;

   pba.Decompose( pImage, nrScales );

   for (int i = 0; i < nrScales; i++)
   {
       ArrayGrid<double>* pTemp = pba.GetPyramid()->GetRecursiveScale( i )->GetOrientedBand(0);
       stringstream ss;
       ss << "PyrLevel" << i << ".pgm";
       ImageIO::WritePGM( pTemp, ss.str(), ImageIO::GRADIENT_OUT );
   }
   ArrayGrid<double>* pRec = pba.Reconstruct();
   ImageIO::WritePGM( pRec, "Reconstructed.pgm", ImageIO::NULL_OUT );

   delete pRec;

   return true;
}

//========================================================================================


bool PyramidRealDecomposeReconstructTest(Image* pImage, int nrScales, int nrOrientations)
{
   ArrayGrid<double>* pGridIn = pImage->GetBands()[0];

   ExecutionTimer et;
   et.StartTimer();

   PyramidReal np( pGridIn, nrScales, nrOrientations );

   np.Decompose();

   #ifdef DIAGNOSE
      Pyramid<double>* pPyramid = np.GetPyramid();
      Image* pVisualizePyramid = PyramidTools::VisualizeRealPyramid( pPyramid );
      ImageIO::Write( pVisualizePyramid, std::string("VisualizePyramid.pgm"), ImageIO::NULL_OUT );
      delete pVisualizePyramid;

      pPyramid->ExportBandsToPGM();
      np.Diagnose();
   #else
     cout << "\t Uncomment \"#define DIAGNOSE\" for diagnostics of subbands..." << endl << flush;
   #endif

   np.Reconstruct();

   et.StopTimer();
   et.PrintTimeAsUserAndSystemTimes();

   ArrayGrid<double>* pGridOut = np.GetCopyOfReconstructedGrid();
   #ifdef DIAGNOSE
     std::string fileName = string("PyramidRealReconstruction.pgm");
     ImageIO::WritePGM( pGridOut, fileName, ImageIO::NULL_OUT );

     ArrayGrid<double>* pDifferenceGrid = NumberGridTools<double>::CreateSquaredErrorGrid(  pImage->GetBands()[0], pGridOut );
     std::string fileName2 = string("PyramidRealReconstructionDifferenceGrid.pgm");
     ImageIO::WritePGM( pDifferenceGrid, fileName2, ImageIO::NORMAL_OUT );
     delete pDifferenceGrid;
   #endif
   cout << "\t PSNR after reconstruction PyramidReal is " << NumberGridTools<double>::ComputePSNR( pGridIn, pGridOut ) << endl << flush;

   delete pGridOut;

   return true;
}

//========================================================================================

bool PyramidComplexDecomposeReconstructTest(Image* pImage, int nrScales, int nrOrientations)
{
   ArrayGrid<double>* pGridIn = pImage->GetBands()[0];
   PyramidComplex np( pGridIn, nrScales, nrOrientations);

   np.Decompose();

   #ifdef DIAGNOSE
     Pyramid< std::complex<double> >* pPyramid = np.GetPyramid();
     pPyramid->ExportBandsToPGM();
     np.Diagnose();
   #else
     cout << "\t Uncomment \"#define DIAGNOSE\" for diagnostics of subbands..." << endl << flush;
   #endif
   np.Reconstruct();

   ArrayGrid<double>* pGridOut = np.GetCopyOfReconstructedGrid();
   #ifdef DIAGNOSE
      bool printOutput = true;
      std::string fileName = string("PyramidComplexReconstruction.pgm");
      ImageIO::WritePGM( pGridOut, fileName, ImageIO::NULL_OUT );

      ArrayGrid<double>* pDifferenceGrid = NumberGridTools<double>::CreateSquaredErrorGrid( pGridIn, pGridOut, printOutput );
      std::string fileName2 = string("PyramidRealReconstructionDifferenceGrid.pgm");
      ImageIO::WritePGM( pDifferenceGrid, fileName2, ImageIO::NORMAL_OUT );
      delete pDifferenceGrid;
   #endif
   cout << "\t PSNR after reconstruction PyramidReal is " << NumberGridTools<double>::ComputePSNR( pGridIn, pGridOut ) << endl << flush;

   delete pGridOut;
   return true;
}

//========================================================================================

bool PyramidThresholdTest(Image* pImage, int nrScales, int nrOrientations)
{
   PyramidReal np( pImage->GetBands()[0], nrScales, nrOrientations);
   np.Decompose();

   Pyramid<double>* pPyramid = np.GetPyramid();
   #ifdef DIAGNOSE
     pPyramid->ExportBandsToPGM();
   #else
     cout << "\t Uncomment \"#define DIAGNOSE\" for diagnostics of subbands..." << endl << flush;
   #endif

   double threshold = 4.0;

   for (int level = -1; level < nrScales; level++)
   {
      PyramidLevel<double>* pBandSet;
      if (level != -1)
      {
         pBandSet = pPyramid->GetRecursiveScale(level);
      }
      else
      {
         pBandSet = pPyramid->GetResidualScale();
      }

      for (int orientationIndex = 0; orientationIndex < pBandSet->GetNumberOfOrientations(); orientationIndex++)
      {
         ArrayGrid<double>* pBand = pBandSet->GetOrientedBand( orientationIndex );
         for (int y = 0; y < pBand->GetHeight(); y++)
         {
            for (int x = 0; x < pBand->GetWidth(); x++)
            {
               double tmpValue = fabs( pBand->GetValue(x, y) );
               if ( tmpValue < threshold )
               {
                  pBand->SetValue(x, y, 0.0);
               }
            }
         }
      }
   }
   np.Reconstruct();
   ArrayGrid<double>* pGridOut = np.GetCopyOfReconstructedGrid();
   std::string fileName = string("PyramidThresholdTest.pgm");
   ImageIO::WritePGM( pGridOut, fileName, ImageIO::NULL_OUT );

   return true;
}

//========================================================================================

bool PyramidOrientationTest(Image* pImage, int nrScales, int nrOrientations)
{
   PyramidComplex np(pImage->GetBands()[0], nrScales, nrOrientations);
   np.Decompose();

   #ifdef DIAGNOSE
     np.GetPyramid()->ExportBandsToPGM();
   #else
     cout << "\t Uncomment \"#define DIAGNOSE\" for diagnostics of subbands..." << endl << flush;
   #endif

   for (int scaleNr = 0; scaleNr < nrScales; scaleNr++)
   {
      stringstream ssOri;
      ssOri << "Pyr-Orientation-" << scaleNr << ".ppm";
      stringstream ssMag;
      ssMag << "Pyr-Magnitude-" << scaleNr << ".ppm";
      OrientationGrid* pOrientationGridRec = ComputeOrientation::ComputeDominantOrientationInputComplexPyramidLevel( np.GetPyramid()->GetRecursiveScale( scaleNr ) );

      pOrientationGridRec->ExportMagnitudeImage( ssMag.str() );
      pOrientationGridRec->ExportOrientationImage( ssOri.str(), 2.0);

      delete pOrientationGridRec;
   }
   stringstream ssOri;
   ssOri << "Pyr-Orientation-res.ppm";
   stringstream ssMag;
   ssMag << "Pyr-Magnitude-res.ppm";
   OrientationGrid* pOrientationGridResid = ComputeOrientation::ComputeDominantOrientationInputComplexPyramidLevel( np.GetPyramid()->GetResidualScale() );

   pOrientationGridResid->ExportMagnitudeImage( ssMag.str() );
   pOrientationGridResid->ExportOrientationImage( ssOri.str(), 0.1);

   delete pOrientationGridResid;

   return true;
}

//========================================================================================

int main(int argc, char *argv[])
{
   Image* pImage = 0;

   int nrScales;
   int nrOrientations;
   const char* inputname;
   if (argc == 4)
   {
      inputname =  argv[1];
      nrScales       = atoi( argv[2] );
      nrOrientations = atoi( argv[3] );
   }
   else if (argc == 2)
   {
      inputname =  argv[1];
      nrScales       = 4;
      nrOrientations = 6;
   }
   else
   {
      inputname = "../../testdata/lena512.pgm";
      //inputname = "../../testdata/testhaze.ppm";
      //inputname = "../../testdata/arab.pgm";
      //inputname = "../../testdata/blackman.pgm";
      //inputname = "../../testdata/nematodes.pgm";
      nrScales = 4;
      nrOrientations = 6;
   }
   cout << "Running test with input image " << inputname << " nr scales = " << nrScales << " and nr of orientations = " << nrOrientations << endl << flush;

   pImage = ImageIO::Read( inputname );

   cout << "* Pyramid Threshold Test:" << endl << flush;
   if ( PyramidThresholdTest( pImage, nrScales, nrOrientations) == true )
   {
      cout << "\t-> OK!!" << endl << flush;
   }
   else
   {
      cout << "\t-> FAILED!!" << endl << flush;
   }

   cout << "* Pyramid Real-valued Decompose/Reconstruct Test:" << endl << flush;
   if ( PyramidRealDecomposeReconstructTest( pImage, nrScales, nrOrientations) == true )
   {
      cout << "\t-> OK!!" << endl << flush;
   }
   else
   {
      cout << "\t-> FAILED!!" << endl << flush;
   }

   cout << "* Pyramid Complex-valued Decompose/Reconstruct Test:" << endl << flush;
   if ( PyramidComplexDecomposeReconstructTest( pImage, nrScales, nrOrientations) == true )
   {
      cout << "\t-> OK!!" << endl << flush;
   }
   else
   {
      cout << "\t-> FAILED!!" << endl << flush;
   }

   nrOrientations = 4;  // orientation computation only derived for 4 oriented bands per scale
   cout << "* Pyramid Orientation Estimation test:" << endl << flush;
   if ( PyramidOrientationTest( pImage, nrScales, nrOrientations) == true )
   {
      cout << "\t-> OK!!" << endl << flush;
   }
   else
   {
      cout << "\t-> FAILED!!" << endl << flush;
   }

   cout << "* Pyramid Burt Adelson test:" << endl << flush;
   if (TestPyramidBurtAdelson( pImage) == true )
   {
      cout << "\t-> OK!!" << endl << flush;
   }
   else
   {
      cout << "\t-> FAILED!!" << endl << flush;
   }

   cout << "* Steerable Freeman Adelson test:" << endl << flush;
   if (SteerableFreemanAdelsonTest( pImage) == true )
   {
      cout << "\t-> OK!!" << endl << flush;
   }
   else
   {
      cout << "\t-> FAILED!!" << endl << flush;
   }

   cout << "END: all tests ended..." << endl << flush;

   delete pImage;

   return EXIT_SUCCESS;
}
