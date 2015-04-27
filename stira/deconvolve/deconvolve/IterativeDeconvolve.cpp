
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

#include "IterativeDeconvolve.h"
#include "../../common/common/MathUtils.h"

namespace stira{
namespace deconvolve{

using namespace std;
using namespace common;
using namespace image;

//--------------------------------------------------------------------------

IterativeDeconvolve::IterativeDeconvolve( image::Image* pDegradedImage, int maxNrOfIterations )
                           : DeconvolveMaster( pDegradedImage )
{
   Initialize( maxNrOfIterations );
}

//--------------------------------------------------------------------------

IterativeDeconvolve::IterativeDeconvolve( image::Image* pDegradedImage, image::Image* pPSF, int maxNrOfIterations )
                           : DeconvolveMaster( pDegradedImage, pPSF )
{
   Initialize( maxNrOfIterations );
}

//--------------------------------------------------------------------------

void IterativeDeconvolve::Initialize( int maxNrOfIterations )
{
   mCurrentIterationNr = 0;
   mMaximumNrOfIterations = maxNrOfIterations;
   mpLastEstimate = mpDegradedImage->Clone();
   mpNewEstimate  = mpDegradedImage->Clone();
   mCurrentBandNr = 0;
   mLambda = 0.001;
   mStepSize = 1.0;

   mMaximumNrOfIterations = maxNrOfIterations;

   mpDegradedGrid=0;
   mpLastGrid=0;
   mpNewGrid=0;
   mpPSFGrid=0;
}

//--------------------------------------------------------------------------

IterativeDeconvolve::~IterativeDeconvolve()
{
}

//--------------------------------------------------------------------------

int IterativeDeconvolve::GetMaximumNrOfIterations()
{
   return mMaximumNrOfIterations;
}

//--------------------------------------------------------------------------
void IterativeDeconvolve::SetMaximumNrOfIterations( int nrIter)
{
   mMaximumNrOfIterations = nrIter;
}

//--------------------------------------------------------------------------

void IterativeDeconvolve::SetLambda(double lambda)
{
   mLambda = lambda;
}

//--------------------------------------------------------------------------

double IterativeDeconvolve::GetLambda()
{
   return mLambda;
}

//--------------------------------------------------------------------------

void IterativeDeconvolve::SetStepSize(double stepSize)
{
   mStepSize = stepSize;
}

//--------------------------------------------------------------------------

double IterativeDeconvolve::GetStepSize()
{
   return mStepSize;
}

//--------------------------------------------------------------------------

bool IterativeDeconvolve::PrepareCurrentGrids( )
{
   mpDegradedGrid = mpDegradedImage->GetBands()[ mCurrentBandNr ];
   mpLastGrid = mpLastEstimate->GetBands()[ mCurrentBandNr ];
   mpNewGrid = mpNewEstimate->GetBands()[ mCurrentBandNr ];
   
   mpPSFGrid = 0;
   if (mpPSF->GetNumberOfBands() > 1)
   {
      mpPSFGrid = mpPSF->GetBands()[ mCurrentBandNr ];
   }
   else
   {
      mpPSFGrid = mpPSF->GetBands()[0];
   }
   return true;
}


}
}
