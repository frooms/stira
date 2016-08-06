
/***************************************************************************************
 *   Copyright (C) 2009 by Filip Rooms                                                 *
 *                                                                                     *
 *  Terms and conditions for using this software in any form are provided in the       *
 *  file COPYING, which can be found in the root directory of this project.            *
 *                                                                                     *
 *   Contact data: filip.rooms@gmail.com                                               *
 *                 http://www.filiprooms.be/                                           *
 *                                                                                     *
 ***************************************************************************************/

#include "AdaptiveEnhanceLuong.h"
#include "../../common/common/MathUtils.h"
#include "../../imagedata/simpletools/GridExtender.h"
#include "../../imagedata/simpletools/GridStatistics.h"
#include "../../imagetools/tools/ImageIO.h"
#include "../../histogram/histogram/IntHistogram.h"

#define REGULARIZED
#define ISITERATIVE

namespace stira {
namespace contrastenhance {

using namespace common;
using namespace image;
using namespace std;
using namespace histogram;

//-------------------------------------------------------------------------

AdaptiveEnhanceLuong::AdaptiveEnhanceLuong( int windowSize )
{
   mWindowSize = windowSize;
   mTmpAlphaFactor = 1.0;
   mFinalAlphaFactor = 1.0;
   mpSourceGrid = 0;
   mpMeanGrid = 0;
   mpVarianceGrid = 0;
   mpLastStepGrid = 0;
   mpNextStepGrid = 0;
}

//-------------------------------------------------------------------------

AdaptiveEnhanceLuong::~AdaptiveEnhanceLuong()
{
   if (mpMeanGrid != 0)
   {
      delete mpMeanGrid;
   }
   if (mpVarianceGrid != 0)
   {
      delete mpVarianceGrid;
   }
}

//-------------------------------------------------------------------------

void AdaptiveEnhanceLuong::SetAlphaFactor( double factor )
{
   mFinalAlphaFactor = factor;
}

//-------------------------------------------------------------------------

void AdaptiveEnhanceLuong::SetWindowSize( int size )
{
   mWindowSize = size;
}

//-------------------------------------------------------------------------

void AdaptiveEnhanceLuong::GetBlockStatistics( )
{
   for (int y = mHalfBlockSize; y < mHeight - mHalfBlockSize; y ++ )
   {
      for (int x = mHalfBlockSize; x < mWidth - mHalfBlockSize; x ++ )
      {
         int xTopLeft = x - mHalfBlockSize;
         int yTopLeft = y - mHalfBlockSize;
         int xBottomRight = x + mHalfBlockSize;
         int yBottomRight = y + mHalfBlockSize;
             mpMeanGrid->SetValue( x, y, GridStatistics<double>::ComputeLocalMean(     mpLastStepGrid, xTopLeft, yTopLeft, xBottomRight, yBottomRight ) );
         mpVarianceGrid->SetValue( x, y, GridStatistics<double>::ComputeLocalVariance( mpLastStepGrid, xTopLeft, yTopLeft, xBottomRight, yBottomRight, mpMeanGrid->GetValue( x, y ) ) );
      }
   }
   double minVariance, maxVariance;

   ArrayGrid<double>* pCroppedVarianceGrid = GridExtender<double>::CropBorder( mpVarianceGrid, mWindowSize, mWindowSize );
   GridStatistics<double>::GetMinMax( pCroppedVarianceGrid, minVariance, maxVariance );

   bool useDataMinMax = true;
   int binsize = (int)(( maxVariance - minVariance ) / 500.0);

   IntHistogram* pHistogram = new IntHistogram( pCroppedVarianceGrid, useDataMinMax, 0.1, 0.9, binsize, 0 );

   mLowerBound = pHistogram->GetLowerBound();
   mUpperBound = pHistogram->GetUpperBound();
   delete pHistogram;
   delete pCroppedVarianceGrid;
}

//-------------------------------------------------------------------------

void AdaptiveEnhanceLuong::RemapGridIntensities( )
{
   for (int y = mHalfBlockSize; y < mHeight - mHalfBlockSize; y ++ )
   {
      for (int x = mHalfBlockSize; x < mWidth - mHalfBlockSize; x ++ )
      {
         double inValue = mpLastStepGrid->GetValue(x, y) / 255.0;
         double localMinimum = GridStatistics<double>::GetLocalMinimum( mpLastStepGrid, x, y, mWindowSize, mWindowSize ) / 255.0;
         double localMaximum = GridStatistics<double>::GetLocalMaximum( mpLastStepGrid, x, y, mWindowSize, mWindowSize ) / 255.0;
         double outValue = 0.0;

         double alpha = mTmpAlphaFactor * ( localMaximum - localMinimum );
         #ifdef REGULARIZED
         double weightFactor =    (MathUtils::ClipValue( mpVarianceGrid->GetValue( x, y ), mLowerBound, mUpperBound ) - mLowerBound)
                                / (mUpperBound - mLowerBound)
                                - 0.1;
         #endif
         mpAlphaGrid->SetValue( x, y, alpha );
         if ( inValue > ( ( localMaximum + localMinimum ) / 2.0 ) )
         {
            outValue = pow( inValue, 1.0 - alpha );
         }
         else
         {
            outValue = 1.0 - pow( ( 1.0 - inValue ), 1.0 - alpha );
         }
         #ifdef REGULARIZED
         double newValue = weightFactor * 255.0 * outValue + (1.0 - weightFactor) * mpMeanGrid->GetValue( x, y );
         mpNextStepGrid->SetValue( x, y, newValue );
         #else
         mpNextStepGrid->SetValue( x, y, 255.0 * outValue );
         #endif
      }
   }
   stringstream ss;
   ss << std::string("AlphaMap-") << mTmpAlphaFactor << std::string(".pgm");
   std::string fileName = ss.str();

   ImageIO::WritePGM( mpAlphaGrid, fileName, ImageIO::NORMAL_OUT );

   mpLastStepGrid->SetGridValues( *mpNextStepGrid );
}

//-------------------------------------------------------------------------

void AdaptiveEnhanceLuong::Initialize( )
{
   mWidth  = mpSourceGrid->GetWidth();;
   mHeight = mpSourceGrid->GetHeight();
   mHalfBlockSize = mWindowSize / 2;
   mpLastStepGrid = mpSourceGrid->Clone();
   mpNextStepGrid = mpSourceGrid->Clone();
   mpMeanGrid     = new image::ArrayGrid<double>( mWidth, mHeight );
   mpVarianceGrid = new image::ArrayGrid<double>( mWidth, mHeight );
   mpAlphaGrid    = new image::ArrayGrid<double>( mWidth, mHeight );
}

void AdaptiveEnhanceLuong::Cleanup()
{
   if ( mpLastStepGrid != 0 ) { delete mpLastStepGrid;   mpLastStepGrid = 0; }
   if ( mpNextStepGrid != 0 ) { delete mpNextStepGrid;   mpNextStepGrid = 0; }
   if ( mpMeanGrid     != 0 ) { delete mpMeanGrid;       mpMeanGrid = 0;     }
   if ( mpVarianceGrid != 0 ) { delete mpVarianceGrid;   mpVarianceGrid = 0; }
   if ( mpAlphaGrid    != 0 ) { delete mpAlphaGrid;      mpAlphaGrid = 0; }
}

void AdaptiveEnhanceLuong::RunSingleGrid( )
{
   #ifdef ISITERATIVE
     mTmpAlphaFactor = 0.1;
     while ( mTmpAlphaFactor < mFinalAlphaFactor )
     {
        cout << "Processing with mTmpAlphaFactor = " << mTmpAlphaFactor << endl << flush;
        #ifdef REGULARIZED
        GetBlockStatistics( );
        #endif
        RemapGridIntensities( );
        mTmpAlphaFactor += 0.1;
        if ( mTmpAlphaFactor == 0.3 ) { mWindowSize = 5; mHalfBlockSize = mWindowSize / 2;}
        if ( mTmpAlphaFactor == 0.6 ) { mWindowSize = 3; mHalfBlockSize = mWindowSize / 2;}
     }
   #else
     mTmpAlphaFactor = mFinalAlphaFactor;

     cout << "Processing with mTmpAlphaFactor = " << mTmpAlphaFactor << endl << flush;
     #ifdef REGULARIZED
     GetBlockStatistics( );
     #endif
     RemapGridIntensities( );
   #endif

}

//-------------------------------------------------------------------------

Image* AdaptiveEnhanceLuong::Run( Image* pSourceImage )
{
   Image* pOutImage = new Image( pSourceImage->GetWidth(), pSourceImage->GetHeight() );

   int nrbands = pSourceImage->GetNumberOfBands();

   for (int bandID = 0; bandID < nrbands; bandID ++ )
   {
      mpSourceGrid = pSourceImage->GetBands()[bandID];
      Initialize( );
      RunSingleGrid( );
      pOutImage->AddBand( mpNextStepGrid->Clone() );
      Cleanup();
   }
   return pOutImage;
}

//-------------------------------------------------------------------------

}
}
