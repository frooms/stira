
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

#include <vector>

#include "PyramidDenoiser.h"

#include "../../imagedata/simpletools/GridStatistics.h"

namespace stira {
namespace pyramidapplications {

using namespace std;

//===================================================================================================

PyramidDenoiser::PyramidDenoiser( Pyramid<double>* pPyramid, ShrinkageRule myRule, double sigma)
{
   mpPyramid = pPyramid;
   mWindowSize = 7;
   mWindowHalfSize = mWindowSize / 2;
   mSigmaNoise = sigma;
   mShrinkageRule = myRule;
   assert (pPyramid != 0);
   if (pPyramid->HasResidualScale() )
   {
      mFinestDenoisingLevel = -1;
   }
   else
   {
      mFinestDenoisingLevel = 0;
   }


   // for the steerable pyramid, variance in the residual level is 1 x sigma,
   //                                     in the first recursive level sigma / 2
   //                                     each consecutive level up, variance is further divided by 4
   mScaleFactorResidualLevel = 1.0;
   mScaleFactorResidualToRecursiveLevel = sqrt(2.0);
   mScaleFactorRecursiveLevel = 2.0;
}

//===================================================================================================

PyramidDenoiser::~PyramidDenoiser()
{
}

//===================================================================================================

double PyramidDenoiser::EstimateSigmaSignal( ArrayGrid<double>* pBand, int xCenter, int yCenter, double sigmaNoise, int windowSize)
{
   assert ( ( windowSize % 2 ) == 1 );
   int windowHalfSize = (windowSize - 1) / 2;

   if (    ( ( xCenter - windowHalfSize ) >= 0)
        && ( ( xCenter + windowHalfSize ) < pBand->GetWidth() )
        && ( ( yCenter - windowHalfSize ) >= 0)
        && ( ( yCenter + windowHalfSize) < pBand->GetHeight() )
      )
   {
      int xTopleft = xCenter - windowHalfSize;
      int yTopleft = yCenter - windowHalfSize;
      int xBottomRight = xCenter + windowHalfSize;
      int yBottomRight = yCenter + windowHalfSize;
      double tmpMean       = GridStatistics< double >::ComputeLocalMean(     pBand, xTopleft, yTopleft, xBottomRight, yBottomRight );
      double localVariance = GridStatistics< double >::ComputeLocalVariance( pBand, xTopleft, yTopleft, xBottomRight, yBottomRight, tmpMean );
      double signalVariance = localVariance - ( sigmaNoise * sigmaNoise );
      if (signalVariance > 0.0)
      {
         return sqrt( signalVariance );
      }
      else
      {
         return 0.0;
      }
   }
   else
   {
      return 0.0;
   }
}

//===================================================================================================

double PyramidDenoiser::GetSigmaNoise()
{
   return mSigmaNoise;
}

//===================================================================================================

void PyramidDenoiser::SetSigmaNoise(double sigmaNoise)
{
   mSigmaNoise = sigmaNoise;
}

//===================================================================================================

void PyramidDenoiser::Run()
{
   for (int level = mpPyramid->GetNumberOfScales() - 2; level >= mFinestDenoisingLevel; level--)
   {
      DenoiseLevel( level );
   }
}

//===================================================================================================

double PyramidDenoiser::ComputeBivariateShrinkagefactor( double w1, double w2, double localSigma, double sigmaNoise )
{
   double wTmp = sqrt( ( w1 * w1 ) + ( w2 * w2 ) );
   double w = ( wTmp - ( sqrt( 3.0 ) * sigmaNoise * sigmaNoise ) / localSigma );

   if (w < 0.0)
   {
      w = 0.0;
   }

   if (wTmp > 0.0)
   {
      w /= wTmp;
   }
   else
   {
      w = 1.0;
   }
   return w;
}

//===================================================================================================

double PyramidDenoiser::ComputeWienerShrinkagefactor( double sigmaSignal, double sigmaNoise )
{
   double sigma2 = sigmaSignal * sigmaSignal;
   double sigmaNoise2 = sigmaNoise * sigmaNoise;

   return (sigma2 / (sigma2 + sigmaNoise2));
}

//===================================================================================================

double PyramidDenoiser::ComputeLaplacianShrinkagefactor(double w1, double sigmaSignal, double sigmaNoise)
{
   double signW = w1 / fabs( w1 );
   double sigmaNoise2 = sigmaNoise * sigmaNoise;

   double tmpValue = (fabs(w1) - ((sqrt(2.0) * sigmaNoise2) / sigmaSignal));

   if (tmpValue < 0.0)
   {
      tmpValue = 0.0;
   }
   return  (signW * tmpValue);
}

//===================================================================================================

void PyramidDenoiser::DenoiseLevelWiener(int level)
{
   if ( level < (int)( mpPyramid->GetNumberOfScales() - 1 ) )
   {
      PyramidLevel<double>* pBandSet;
      if (level != -1)
      {
         pBandSet = mpPyramid->GetRecursiveScale(level);
      }
      else
      {
         pBandSet = mpPyramid->GetResidualScale();
      }

      for (int orientationIndex = 0; orientationIndex < pBandSet->GetNumberOfOrientations(); orientationIndex++)
      {
         ArrayGrid<double>* pBand = pBandSet->GetOrientedBand( orientationIndex);
         for (int y = 0; y < pBand->GetHeight(); y++)
         {
            for (int x = 0; x < pBand->GetWidth(); x++)
            {
               double sigmaSignal = EstimateSigmaSignal( pBand, x, y, mSigmaNoise, mWindowSize );
               double shrinkageFactor = ComputeWienerShrinkagefactor( sigmaSignal, mSigmaNoise );
               pBand->SetValue( x, y, shrinkageFactor * pBand->GetValue( x, y ) );
            }
         }
      }
   }
   else
   {
      std::cerr << "PyramidDenoiser::DenoiseLevelWiener: Cannot denoise level " << level << " since top level is " << mpPyramid->GetNumberOfScales() << std::endl << std::flush;
   }
}

//===================================================================================================

void PyramidDenoiser::DenoiseLevelLaplacian(int level)
{
   if (level < (int)(mpPyramid->GetNumberOfScales() - 1))
   {
      PyramidLevel<double>* pBandSet;
      if (level != -1)
      {
         pBandSet = mpPyramid->GetRecursiveScale(level);
      }
      else
      {
         pBandSet = mpPyramid->GetResidualScale();
      }

      for (int orientationIndex = 0; orientationIndex < pBandSet->GetNumberOfOrientations(); orientationIndex++)
      {
         ArrayGrid<double>* pBand = pBandSet->GetOrientedBand( orientationIndex);
         for (int y = 0; y < pBand->GetHeight(); y++)
         {
            for (int x = 0; x < pBand->GetWidth(); x++)
            {
               double sigmaSignal = EstimateSigmaSignal( pBand, x, y, mSigmaNoise, mWindowSize );
               double w1 = pBand->GetValue(x,y);
               double shrinkageFactor = ComputeLaplacianShrinkagefactor(w1, sigmaSignal, mSigmaNoise);
               mpPyramid->GetRecursiveScale( level)->GetOrientedBand( orientationIndex)->SetValue(x,y, shrinkageFactor * w1);
            }
         }
      }
   }
   else
   {
      std::cerr << "PyramidDenoiser::DenoiseLevelLaplacian: Cannot denoise level " << level << " since top level is " << mpPyramid->GetNumberOfScales() << std::endl << std::flush;
   }
}

//===================================================================================================

double PyramidDenoiser::GetScaledNoiseVarianceFactor(int level)
{
   double myFactor = mScaleFactorResidualLevel;

   if (level >= 0)
   {
      myFactor *= ( mScaleFactorResidualToRecursiveLevel * mScaleFactorResidualToRecursiveLevel);
   }
   for (int i = level; i > 0; i--)
   {
      myFactor *= ( mScaleFactorRecursiveLevel * mScaleFactorRecursiveLevel );
   }
   return myFactor;
}

//===================================================================================================

double PyramidDenoiser::GetScaledParentChildFactor(int level)
{
   if (level < 0)
   {
      return mScaleFactorResidualToRecursiveLevel;
   }
   else
   {
      return mScaleFactorRecursiveLevel;
   }
}

//===================================================================================================

void PyramidDenoiser::DenoiseLevelBivariate(int level)
{
   if (level < (int)(mpPyramid->GetNumberOfScales() - 1))
   {
      PyramidLevel<double>* pBandSetCurrent;
      PyramidLevel<double>* pBandSetParent;
      if (level != -1)
      {
         pBandSetCurrent = mpPyramid->GetRecursiveScale(level);
         pBandSetParent = mpPyramid->GetRecursiveScale(level+1);
      }
      else
      {
         pBandSetCurrent = mpPyramid->GetResidualScale();
         pBandSetParent = mpPyramid->GetRecursiveScale(0);
      }

      double avgVariance = 0.0;

      double scaleNoiseVariance = mSigmaNoise / GetScaledNoiseVarianceFactor( level );
      double scaleParentChildFactor = GetScaledParentChildFactor( level);

      for (int orientationIndex = 0; orientationIndex < pBandSetCurrent->GetNumberOfOrientations(); orientationIndex++)
      {
         ArrayGrid<double>* pBandCurrent = pBandSetCurrent->GetOrientedBand( orientationIndex);
         ArrayGrid<double>* pBandParent = pBandSetParent->GetOrientedBand( orientationIndex);

         double meanVal     = GridStatistics<double>::GetGridMean( pBandCurrent );
         double varianceVal = GridStatistics<double>::GetGridVariance( pBandCurrent, meanVal );

         #ifdef DEBUG
         cout << "Denoising level " << level << " and orientationIndex " << orientationIndex
              << ", variance is " << varianceVal << " and scaled noise variance = " << scaleNoiseVariance << endl << flush;
         #endif
         avgVariance += varianceVal;


         for (int y = 0; y < pBandCurrent->GetHeight(); y++)
         {
            for (int x = 0; x < pBandCurrent->GetWidth(); x++)
            {
               double sigmaSignal = EstimateSigmaSignal( pBandCurrent, x, y, mSigmaNoise, mWindowSize );
               double w1 = pBandCurrent->GetValue(x,y);
               double w2 = pBandParent->GetValue(x/2,y/2) / scaleParentChildFactor;
               double shrinkageFactor = ComputeBivariateShrinkagefactor(w1, w2, sigmaSignal, scaleNoiseVariance );
               pBandCurrent->SetValue(x,y, shrinkageFactor * w1);
            }
         }
      }
      #ifdef DEBUG
      cout << "Average variance at scale level = " << (avgVariance) / (double)(pBandSetCurrent->GetNumberOfOrientations())
           << endl << flush;
      #endif
   }
   else
   {
      std::cerr << "PyramidDenoiser::DenoiseLevelBivariate: Cannot denoise level " << level << " since top level is " << mpPyramid->GetNumberOfScales() << std::endl << std::flush;
   }
}

//===================================================================================================

void PyramidDenoiser::DenoiseLevel(int level)
{
   if (level < (mpPyramid->GetNumberOfScales() - 1))
   {
      //std::cerr << "Denoising level " << level << std::endl << std::flush;
      switch (mShrinkageRule)
      {
         case WIENER:
         {
            DenoiseLevelWiener( level );
            break;
         }
         case LAPLACIAN:
         {
            DenoiseLevelLaplacian( level );
            break;
         }
         case BIVARIATE:
         {
            DenoiseLevelBivariate( level );
            break;
         }
         default:
         {
            break;
         }
      }
   }
   else
   {
      std::cerr << "PyramidDenoiser::DenoiseLevel: Cannot denoise level " << level << " since top level is " << mpPyramid->GetNumberOfScales() << std::endl << std::flush;
   }
}

//===================================================================================================

}
}
