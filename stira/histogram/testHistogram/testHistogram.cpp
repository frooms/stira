
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
#include "../../image/tools/ImageTools.h"
#include "../../image/tools/ImageIO.h"
#include "../histogram/IntHistogram.h"
#include "../histogram/FloatHistogram.h"
#include "../histogram/ConditionalHistogram.h"
#include "../histogram/Spatiogram.h"

using namespace std;
using namespace stira::image;
using namespace stira::histogram;

bool SpatiogramTest()
{
   ArrayGrid<double>* pGrid1 = ImageIO::ReadArrayOpenCVAsDouble( std::string( "../../../../stira/stira/testdata/Spatial1.png" ) );
   ArrayGrid<double>* pGrid2 = ImageIO::ReadArrayOpenCVAsDouble( std::string( "../../../../stira/stira/testdata/Spatial2.png" ) );
   ArrayGrid<double>* pGrid3 = ImageIO::ReadArrayOpenCVAsDouble( std::string( "../../../../stira/stira/testdata/Spatial3.png" ) );

   int binSize = 1;
   Spatiogram sp1( pGrid1, binSize );
   Spatiogram sp2( pGrid2, binSize );
   Spatiogram sp3( pGrid3, binSize );

   int threshold = 100;  // no bins with less than "threshold" counts are written to file
   sp1.Write( std::string("Spatiogram1.txt"), threshold );
   sp2.Write( std::string("Spatiogram2.txt"), threshold );
   sp3.Write( std::string("Spatiogram3.txt"), threshold );

   delete pGrid1;
   delete pGrid2;
   delete pGrid3;

   return true;
}

//-------------------------------------------------------------------------------------

bool HistogramTest(Image* pInImage)
{
   double lowerFraction=0.01;
   double upperFraction=0.99;
   int binsize=1;
   bool useDataMinMax = false;
   ArrayGrid<bool>* pMaskGrid=0;
   IntHistogram intHist( pInImage, useDataMinMax, lowerFraction, upperFraction, binsize, pMaskGrid );
   intHist.Write("IntHistogram.txt");

   IntHistogram stdHist( pInImage, useDataMinMax, lowerFraction, upperFraction, binsize, pMaskGrid );
   stdHist.Write("StdHistogram.txt");

   bool requiresNormalization = true;
   FloatHistogram flHist( &stdHist, requiresNormalization );

   flHist.Write("flHistogram.txt");
   return true;
}

//-------------------------------------------------------------------------------------

bool CondidtionalHistogramTest(Image* pInImage)
{
   Image* pGammaImage = ImageTools::ApplyGamma( pInImage, 0.5 );
   ConditionalHistogram ch( pInImage, pGammaImage );

   ch.VisualizeAsImage( std::string("ConditionalHistogramGamma.ppm") );
   delete pGammaImage;
   return true;
}

//-------------------------------------------------------------------------------------

bool QuantileTest(Image* pInImage)
{
   bool isCorrect = true;
   double lowerFraction=0.01;
   double upperFraction=0.99;
   int binsize=1;
   ArrayGrid<bool>* pMaskGrid=0;
   bool useDataMinMax = false;
   IntHistogram intHist( pInImage, useDataMinMax, lowerFraction, upperFraction, binsize, pMaskGrid );
   intHist.Write("QuantileTestHistogram.txt");

   double quartile1 = intHist.GetQuantile( 0, 0.25 );

   double quartile2 = intHist.GetQuantile( 0, 0.5 );

   double quartile3 = intHist.GetQuantile( 0, 0.75 );

   if ( quartile1 !=  88 ) { isCorrect = false; }

   if ( quartile2 != 127 ) { isCorrect = false; }

   if ( quartile3 != 156 ) { isCorrect = false; }

   cout << quartile1 << "\t" << quartile2 << "\t" << quartile3 << endl;

   return isCorrect;
}

//========================================================================================

int main(int argc, char *argv[])
{
   const char* fileName;
   if (argc == 2)
   {
      fileName = argv[1];
   }
   else
   {
      fileName = "../../../../stira/stira/testdata/lena256.pgm";
   }
   bool allSuccess = true;
   Image* pInImage = ImageIO::Read( fileName );


   if ( HistogramTest( pInImage ) != true )
   {
      cerr << "IntHistogramTest went wrong..." << endl << flush;
      allSuccess = false;
   }

   if ( CondidtionalHistogramTest( pInImage) != true )
   {
      cerr << "CondidtionalHistogramTest went wrong..." << endl << flush;
      allSuccess = false;
   }

   if ( SpatiogramTest() != true )
   {
      cerr << "SpatiogramTest went wrong..." << endl << flush;
      allSuccess = false;
   }

   if ( QuantileTest( pInImage ) != true )
   {
      cerr << "QuantileTest went wrong..." << endl << flush;
      allSuccess = false;
   }

   if ( allSuccess == true )
   {
      cout << "end: all tests ended successfully" << endl << flush;
   }
   else
   {
      cout << "end: *NOT* all tests ended successfully" << endl << flush;
   }

   delete pInImage;
   return EXIT_SUCCESS;
}
