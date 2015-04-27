
/***********************************************************************************
 *   Copyright (C) 2009 by Filip Rooms                                             *
 *                                                                                 *
 *  Terms and conditions for using this software in any form are provided in the   *
 *  file COPYING, which can be found in the root directory of this project.        *
 *                                                                                 *
 *   Contact data: filip.rooms@gmail.com                                           *
 *                 http://www.filiprooms.be/                                       *
 *                                                                                 *
 ***********************************************************************************/

// Test if we generate a grid with given mean intensity and additive white Gaussian noise,
// we indeed obtain a grid with the required statistics

#include <iostream>
#include <cstdlib>
#include "../tools/NumberGridTools.h"
#include "../../common/common/Random.h"

using namespace std;
using namespace stira::image;
using namespace stira::common;

bool TestEmptyPlusGaussianNoise( int width, int height, double intensity, double sigma )
{
   ArrayGrid<double>* pGrid = new ArrayGrid<double>( width, height );
   Random rn;

   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         pGrid->SetValue(x, y, (intensity + rn.normal( 0.0, sigma )) );
      }
   }

   double testMean     = NumberGridTools<double>::GetGridMean( pGrid );
   double testVariance = NumberGridTools<double>::GetGridVariance( pGrid, testMean );
   double testKurtosis = NumberGridTools<double>::GetGridKurtosis( pGrid, testMean, testVariance );

   if ( fabs( sqrt( testVariance ) - sigma ) > 0.1 )
   {
      cout << "mean intensity: theoretically = " << intensity << "\t estimated = " << testMean << " too different!!" << endl << flush;
      delete pGrid;
      return false;
   }

   if ( fabs( intensity - testMean ) > 0.1 )
   {
      cout << "variance: theoretically = " << sigma * sigma << " \t estimated = " << testVariance << " too different!!" << endl << flush;
      delete pGrid;
      return false;
   }

   if ( fabs( testKurtosis ) > 0.1 )
   {
      cout << "Kurtosis  " << testKurtosis << " too large (should be close to 0 for Gaussian noise)!!" << endl << flush;
      delete pGrid;
      return false;
   }

   cout << "Mean     : theoretically = " << intensity     << " \t estimated = " << testMean     << " \t -> OK!" << endl << flush;
   cout << "variance : theoretically = " << sigma * sigma << " \t estimated = " << testVariance << " \t -> OK!" << endl << flush;
   cout << "Kurtosis : " << testKurtosis << ", is close to 0 \t\t\t -> OK!" << endl << flush;

   delete pGrid;
   return true;
}

//========================================================================================

int main( )
{
   int width  = 512;
   int height = 512;
   double intensity = 25.0;
   double sigma = 7.0;

   if (TestEmptyPlusGaussianNoise( width, height, intensity, sigma ) )
   {
      cout << "Test noise statistics OK!" << endl << flush;
   }
   else
   {
      cout << "Test noise statistics FAILED!" << endl << flush;
   }
   return EXIT_SUCCESS;
}
