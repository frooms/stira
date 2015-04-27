
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

#include "CriticallySubsampledTransform.h"
//#define DEBUG

namespace stira {
namespace wavelet {

using namespace filter;
using namespace image;
using namespace std;

CriticallySubsampledTransform::CriticallySubsampledTransform() : Wavelet()
{
}

//------------------------------------------------------------------------------------------

CriticallySubsampledTransform::~CriticallySubsampledTransform()
{
}

//------------------------------------------------------------------------------------------

bool CriticallySubsampledTransform::Decompose( image::ArrayGrid<double>* pSourceGrid, int nrScales )
{
   Initialize( pSourceGrid, nrScales );
   
   ArrayGrid<double>* pRecursiveInput = pSourceGrid;

   for ( mCurrentScale = 0; mCurrentScale < mNrScales; mCurrentScale++)
   {
      int width  = pRecursiveInput->GetWidth();
      int height = pRecursiveInput->GetHeight();
      int downScaledWidth  = width / 2;
      int downScaledHeight = height / 2;
      bool needsInitialisation = true;
      double initialValue = 0.0;
      ArrayGrid<double>* pLLGrid = new ArrayGrid<double>( downScaledWidth, downScaledHeight, needsInitialisation, initialValue );
      ArrayGrid<double>* pLHGrid = new ArrayGrid<double>( downScaledWidth, downScaledHeight, needsInitialisation, initialValue );
      ArrayGrid<double>* pHLGrid = new ArrayGrid<double>( downScaledWidth, downScaledHeight, needsInitialisation, initialValue );
      ArrayGrid<double>* pHHGrid = new ArrayGrid<double>( downScaledWidth, downScaledHeight, needsInitialisation, initialValue );
            
      // to be sure that (x+1) and (y+1) won't exceed width and height
      int limitWidth  = (width  / 2 ) * 2;
      int limitHeight = (height / 2 ) * 2;
      
      #ifdef DEBUG
      cout << "Width = " << width << ", height = " << height << endl << flush;
      cout << "limitWidth = " << limitWidth << ", limitHeight = " << limitHeight << endl << flush;
      #endif
      
      for (int y = 0; y < limitHeight; y+=2)
      {
         for (int x = 0; x < limitWidth; x+=2)
         {
            int halfX = x/2;
            int halfY = y/2;
            
            #ifdef DEBUG
            //cout << "Width = " << width << ", height = " << height << endl << flush;
            if ((x+1) > width)  {cout <<  (x+1) << " goes out of bounds." << endl << flush;}
            if ((y+1) > height) {cout <<  (y+1) << " goes out of bounds." << endl << flush;}
            assert ((x+1) < width);
            assert ((y+1) < height);
            #endif
            
            double x00 = pRecursiveInput->GetValue( x,   y   );
            double x01 = pRecursiveInput->GetValue( x,   y+1 );
            double x10 = pRecursiveInput->GetValue( x+1, y   );
            double x11 = pRecursiveInput->GetValue( x+1, y+1 );
            
            pLLGrid->SetValue( halfX, halfY, ( (x00 + x01 + x10 + x11) / 2.0) );
            pLHGrid->SetValue( halfX, halfY, ( (x00 + x01 - x10 - x11) / 2.0) );
            pHLGrid->SetValue( halfX, halfY, ( (x00 - x01 + x10 - x11) / 2.0) );
            pHHGrid->SetValue( halfX, halfY, ( (x00 - x01 - x10 + x11) / 2.0) );
         }
      }
      mpPyramid->GetRecursiveScale( mCurrentScale )->AddOrientedBand( pLHGrid );   // in on index 0
      mpPyramid->GetRecursiveScale( mCurrentScale )->AddOrientedBand( pHLGrid );   // in on index 1
      mpPyramid->GetRecursiveScale( mCurrentScale )->AddOrientedBand( pHHGrid );   // in on index 2

      mpPyramid->SetLowpassResidual( pLLGrid );
      
      pRecursiveInput = mpPyramid->GetLowpassResidual( );
   }
   return true;
}

//------------------------------------------------------------------------------------------

bool CriticallySubsampledTransform::Reconstruct( double threshold )
{
   ArrayGrid<double>* pRecursiveInput = mpPyramid->GetLowpassResidual( );
   for ( mCurrentScale = mNrScales-1; mCurrentScale >= 0; mCurrentScale-- )
   {
      int width  = pRecursiveInput->GetWidth();
      int height = pRecursiveInput->GetHeight();
      int upScaledWidth  =  width * 2;
      int upScaledHeight = height * 2;
      bool needsInitialisation = true;
      double initialValue = 0.0;

      ArrayGrid<double>* pLLGrid = new ArrayGrid<double>( upScaledWidth, upScaledHeight, needsInitialisation, initialValue );
      for (int y = 0; y < upScaledHeight; y+=2)
      {
         for (int x = 0; x < upScaledWidth; x+=2)
         {
            int halfX = x/2;
            int halfY = y/2;

            double x00 = pRecursiveInput->GetValue( halfX, halfY );
            
            double x01 = mpPyramid->GetRecursiveScale( mCurrentScale )->GetOrientedBand( 0 )->GetValue( halfX, halfY );
            double x10 = mpPyramid->GetRecursiveScale( mCurrentScale )->GetOrientedBand( 1 )->GetValue( halfX, halfY );
            double x11 = mpPyramid->GetRecursiveScale( mCurrentScale )->GetOrientedBand( 2 )->GetValue( halfX, halfY );
            
            pLLGrid->SetValue( x  , y  , (x00 + x01 + x10 + x11) / 2.0 );
            pLLGrid->SetValue( x  , y+1, (x00 + x01 - x10 - x11) / 2.0 );
            pLLGrid->SetValue( x+1, y  , (x00 - x01 + x10 - x11) / 2.0 );
            pLLGrid->SetValue( x+1, y+1, (x00 - x01 - x10 + x11) / 2.0 );
         }
      }
      pRecursiveInput = pLLGrid->Clone(); delete pLLGrid;
   }
   mpDecomposeReconstructGrid = pRecursiveInput;
   return true;
}

}
}

