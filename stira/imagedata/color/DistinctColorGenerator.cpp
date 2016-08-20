
/***********************************************************************************
 *   Copyright (C) 2010 by Filip Rooms                                             *
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
#include "DistinctColorGenerator.h"

using namespace std;

namespace stira {
namespace imagedata {

using namespace common;


DistinctColorGenerator::DistinctColorGenerator()
{
   mFactor = 255;
   mColorsGenerated = 0;
   mpColorCycle = new ColorValue[6];
   mpColorCycle[0].SetColorValue( 1.0, 0.0, 0.0, TYPE_RGB);
   mpColorCycle[1].SetColorValue( 0.0, 1.0, 0.0, TYPE_RGB);
   mpColorCycle[2].SetColorValue( 0.0, 0.0, 1.0, TYPE_RGB);
   mpColorCycle[3].SetColorValue( 1.0, 1.0, 0.0, TYPE_RGB);
   mpColorCycle[4].SetColorValue( 1.0, 0.0, 1.0, TYPE_RGB);
   mpColorCycle[5].SetColorValue( 0.0, 1.0, 1.0, TYPE_RGB);
}

//----------------------------------------------------------

DistinctColorGenerator::~DistinctColorGenerator()
{
   delete []mpColorCycle;
}

//----------------------------------------------------------

ColorValue DistinctColorGenerator::GenerateNewColor()
{
   int innerCycleNr = mColorsGenerated % 6;
   int outerCycleNr = mColorsGenerated / 6;
   int cyclesize = MathUtils::ComputeIntegerPower( 2, (int)(log((double)(outerCycleNr)) / log( 2.0 ) ) );
   int insideCyclecounter = outerCycleNr % cyclesize;

   if ( outerCycleNr == 0)
   {
      mFactor = 255;
   }
   else
   {
      mFactor = 256 / (2*cyclesize) + insideCyclecounter * (256/cyclesize);
   }

   ColorValue newColor = mpColorCycle[innerCycleNr] * mFactor;
   /*cout << "\tmColorsGenerated: " << mColorsGenerated << " cyclesize: " << cyclesize
                                                      << ", innerCycleNr: " << innerCycleNr
                                                      << ", outerCycleNr: " << outerCycleNr
                                                      << ", mFactor: " << mFactor
                                                      << ", insideCyclecounter: " << insideCyclecounter
                                                      << " -> generated = " << newColor << endl << flush;*/
   mColorsGenerated++;
   return newColor;
}

//----------------------------------------------------------

}
}
