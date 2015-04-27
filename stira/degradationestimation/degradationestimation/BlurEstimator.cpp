
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

#include <sstream>
#include <string>

#include "BlurEstimator.h"
#include "../../common/common/MathUtils.h"
#include "../../image/tools/GridGenerator.h"
#include "../../image/tools/NumberGridTools.h"
#include "../../image/tools/ImageIO.h"
#include "../../deconvolve/deconvolve/WienerDeconvolve.h"

using namespace std;

namespace stira {
namespace degradationestimation {

using namespace common;
using namespace image;
using namespace deconvolve;

//----------------------------------------------------------------

BlurEstimator::BlurEstimator()
{
   mBlurUnderLimit = 0.5;
   mBlurUpperLimit = 5.0;
   
   mStepSize = 0.5;
   mNoiseLevel = 5.0;
}

//----------------------------------------------------------------

BlurEstimator::~BlurEstimator()
{
}

//----------------------------------------------------------------

double BlurEstimator::GetBlurUnderLimit()
{
   return mBlurUnderLimit;
}

//----------------------------------------------------------------

void BlurEstimator::SetBlurUnderLimit( double underLimit )
{
   mBlurUnderLimit = underLimit;
}

//----------------------------------------------------------------

double BlurEstimator::GetBlurUpperLimit()
{
   return mBlurUpperLimit;
}

//----------------------------------------------------------------

void BlurEstimator::SetBlurUpperLimit( double upperLimit )
{
   mBlurUpperLimit = upperLimit;
}

//----------------------------------------------------------------

double BlurEstimator::GetStepSize()
{
   return mStepSize;
}

//----------------------------------------------------------------

void BlurEstimator::SetStepSize( double stepSize )
{
   mStepSize = stepSize;
}

//----------------------------------------------------------------

double BlurEstimator::GetNoiseLevel()
{
   return mNoiseLevel;
}

//----------------------------------------------------------------

void BlurEstimator::SetNoiseLevel( double noiseLevel )
{
   mNoiseLevel = noiseLevel;
}

//----------------------------------------------------------------

double BlurEstimator::Run( image::ArrayGrid<double>* pGrid )
{
   double tmpKurtosis = 10000.0;
   for (double tmpBlurLevel = mBlurUnderLimit; tmpBlurLevel <= mBlurUpperLimit; tmpBlurLevel += mStepSize)
   {
      ArrayGrid<double>* pPSF = GridGenerator::GenerateGaussian( pGrid->GetWidth(), pGrid->GetHeight(), tmpBlurLevel, tmpBlurLevel);
      
      image::ArrayGrid<double>* pTmpResult = WienerDeconvolve::RunSingleband( pGrid, pPSF, mNoiseLevel );
      
      stringstream ss;
      ss << "CandidateDeblur-" << (int)(tmpBlurLevel*10) << ".pgm";
      string fileName = ss.str();
      
      ImageIO::WritePGM( pTmpResult, fileName );
      
      double myMean     = NumberGridTools<double>::GetGridMean( pTmpResult );
      double myVariance = NumberGridTools<double>::GetGridVariance( pTmpResult, myMean );
      double myKurtosis = NumberGridTools<double>::GetGridKurtosis( pTmpResult, myMean, myVariance );
      
      if (myKurtosis < tmpKurtosis)
      {
         mActualBlur = tmpBlurLevel;
         tmpKurtosis = myKurtosis;
      }

      delete pTmpResult;
   }

   cout << "Final blur level = " << mActualBlur << endl << flush;
   return mActualBlur;
}

//----------------------------------------------------------------

}
}
