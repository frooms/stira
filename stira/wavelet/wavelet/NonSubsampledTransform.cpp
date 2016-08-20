
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
#include <iostream>

#include "../../common/common/MathUtils.h"
#include "NonSubsampledTransform.h"

//#define VIEW_FILTER_TAPS

namespace stira {
namespace wavelet {

using namespace std;
using namespace common;
using namespace imagedata;
using namespace imagetools;

NonSubsampledTransform::NonSubsampledTransform( WaveletType type ) : Wavelet()
{
   mpExtendedLowpassFilter = 0;
   mpExtendedDetailFilter = 0;
   mpExtendedRowInputData = 0;
   mpExtendedColumnInputData = 0;
   mpExtendedRowOutputData = 0;
   mpExtendedColumnOutputData = 0;
   
   WaveletTapGenerator wtg;
   mSet = wtg.Generate( type );
   mNrOrientations = 3;
   
   #ifdef VIEW_FILTER_TAPS
      cout.setf(ios::fixed,ios::floatfield);
      cout.precision(10);

      cout << "Lowpass forw. \t Lowpass inv. \t Highpass forw. \t Highpass inv. " << endl << flush;
      for (int i = 0; i < mSet.length; i++)
      {
         cout << mSet.pLowpassForward[i] << "\t" << mSet.pLowpassInvers[i] << "\t" << mSet.pHighpassForward[i] << "\t" << mSet.pHighpassInvers[i] << endl << flush;
      }
   #endif
}

//------------------------------------------------------------------------------

NonSubsampledTransform::~NonSubsampledTransform()
{
   delete [](mSet.pLowpassInvers);
   delete [](mSet.pLowpassForward);
   delete [](mSet.pHighpassInvers);
   delete [](mSet.pHighpassForward);
}

//------------------------------------------------------------------------------

bool NonSubsampledTransform::Decompose( ArrayGrid<double>* pSourceGrid, int nrScales )
{
   mNrScales = nrScales;
   bool createBands=true;
   bool isSubsampled=false;
   bool isLowestScaleSubsampled=false;
   this->Initialize( pSourceGrid, mNrScales, mNrOrientations, createBands, isSubsampled, isLowestScaleSubsampled );
   
   ArrayGrid<double>* pReinputGrid = pSourceGrid;
   
   for (int scale = 0; scale < this->GetNumberOfScales(); scale++)
   {
      DecomposeSingleScale( pReinputGrid, scale );
      pReinputGrid = mpPyramid->GetLowpassResidual( );
   }
      
   return true;
}

//------------------------------------------------------------------------------

bool NonSubsampledTransform::Reconstruct(double threshold )
{
   for (int scale =  this->GetNumberOfScales()-1; scale >= 0; scale--)
   {
      ArrayGrid<double>* pReinputGrid = mpPyramid->GetLowpassResidual( )->Clone();
      ReconstructSingleScale( pReinputGrid, scale, threshold );

      mpPyramid->SetLowpassResidual( pReinputGrid );
   }
   
   mpDecomposeReconstructGrid = mpPyramid->GetLowpassResidual()->Clone();
   
   return true;
}

//------------------------------------------------------------------------------

bool NonSubsampledTransform::CreateExtendedDataStructures(int width, int height, double* pLowpassFilter, double* pDetailFilter, int nrTaps, int scale)
{
   mWidth = width;
   mHeight = height;
   // upsampling factor
   int upsamplefactor = common::MathUtils::ComputeIntegerPower( 2, scale );
   
   // extended filter length
   mExtendedFilterLength = ( nrTaps - 1 ) * upsamplefactor + 1;
   
   mExtendedFilterHalfLength = mExtendedFilterLength / 2;

   mpExtendedLowpassFilter = new double[ mExtendedFilterLength ]; // extended filter: putting 2^p-1 zeros between the coefficients
   mpExtendedDetailFilter  = new double[ mExtendedFilterLength ]; // extended filter: putting 2^p-1 zeros between the coefficients
   
   mExtendedInputWidth   = width  + mExtendedFilterLength - 1;
   mExtendedInputHeight  = height + mExtendedFilterLength - 1;;
   
   mExtendedOutputWidth  = width  + 2 * mExtendedFilterLength - 2;
   mExtendedOutputHeight = height + 2 * mExtendedFilterLength - 2;
   
   mpExtendedRowInputData     = new double [ mExtendedInputWidth  ];
   mpExtendedColumnInputData  = new double [ mExtendedInputHeight ];
   
   mpExtendedRowOutputData    = new double [ mExtendedOutputWidth  ];
   mpExtendedColumnOutputData = new double [ mExtendedOutputHeight ];
   
   mExtraExtendedWidth  = mExtendedInputWidth  + 2 * mExtendedFilterLength - 2; 
   mExtraExtendedHeight = mExtendedInputHeight + 2 * mExtendedFilterLength - 2;
   
   mpExtraExtendedRowData    = new double [ mExtraExtendedWidth ];
   mpExtraExtendedColumnData = new double [ mExtraExtendedHeight ];
   
   for (int i = 0; i < mExtendedFilterLength; i++)
   {
      mpExtendedLowpassFilter[i] = 0;     // putting zeros between
      mpExtendedDetailFilter[i]  = 0;
   }
   for (int i = 0; i < nrTaps; i++)
   {
      mpExtendedLowpassFilter[ i * upsamplefactor ] = pLowpassFilter[ i ]; // upsampling of the filter
      mpExtendedDetailFilter[  i * upsamplefactor ] = pDetailFilter[ i ];
   }
   return true;
}

//------------------------------------------------------------------------------
bool NonSubsampledTransform::ClearExtendedDataStructures()
{
   delete []mpExtendedLowpassFilter;     mpExtendedLowpassFilter = 0;
   delete []mpExtendedDetailFilter;      mpExtendedDetailFilter = 0;
   delete []mpExtendedRowInputData;      mpExtendedRowInputData = 0;
   delete []mpExtendedColumnInputData;   mpExtendedColumnInputData = 0;
   
   delete []mpExtendedRowOutputData;     mpExtendedRowOutputData = 0;
   delete []mpExtendedColumnOutputData;  mpExtendedColumnOutputData = 0;
   delete []mpExtraExtendedRowData;      mpExtraExtendedRowData = 0;
   delete []mpExtraExtendedColumnData;   mpExtraExtendedColumnData = 0;
   return true;
}

//------------------------------------------------------------------------------

void NonSubsampledTransform::DecomposeSingleScale ( ArrayGrid<double> * pInputGrid, int Scale )
{
   int width = mpPyramid->GetLowpassResidual( )->GetWidth();
   int height = mpPyramid->GetLowpassResidual( )->GetHeight();
   
   // local storage for row and column to filter
   mpRowIn     = new double [ width ];
   mpRowOut    = new double [ width ];
   mpColumnIn  = new double [ height ];
   mpColumnOut = new double [ height ];
   
   //CreateExtendedDataStructures( width, height, Lowpass_Filt, Detail_Filt, FILTERLENGTH, Scale );
   CreateExtendedDataStructures( width, height, mSet.pLowpassForward, mSet.pHighpassForward, mSet.length, Scale );
   
   // horizontal filtering
   for ( int j = 0; j < height; j++ )
   {
      // input row
      for ( int i = 0; i < width; i++ )
      {
         mpRowIn[ i ] = pInputGrid->GetValue( i, j );
      }
   
      // highpass filtering
      DetailRowTransform1D( mpRowIn, mpRowOut, true );
      
      // store in result wavelet band
      for (int i = 0; i < width; i++)
      {
         mpPyramid->GetRecursiveScale( Scale )->GetOrientedBand( 1 )->SetValue( i, j, mpRowOut[ i ] );
         mpPyramid->GetRecursiveScale( Scale )->GetOrientedBand( 2 )->SetValue( i, j, mpRowOut[ i ] );
      }
   
      // lowpass filtering
      LowpassRowTransform1D( mpRowIn, mpRowOut, true );
      
      // store in result wavelet band
      for (int i=0; i<width; i++)
      {
         mpPyramid->GetRecursiveScale( Scale )->GetOrientedBand( 0 )->SetValue( i, j, mpRowOut[ i ] );
         mpPyramid->GetLowpassResidual( )->SetValue( i, j, mpRowOut[ i ] );
      }
   }
   
   // vertical filtering
   for ( int i = 0; i < width; i++ )
   {
      // get input column; filter column; store in resulting wavelet band
      for ( int j = 0; j < height; j++ ) { mpColumnIn[ j ] = mpPyramid->GetLowpassResidual( )->GetValue( i, j ); }
      LowpassColumnTransform1D( mpColumnIn, mpColumnOut, true );
      for ( int j = 0; j < height; j++ ) { mpPyramid->GetLowpassResidual( )->SetValue( i, j, mpColumnOut[ j ] ); }
         
      for ( int j = 0; j < height; j++ ) { mpColumnIn[ j ] = mpPyramid->GetRecursiveScale( Scale )->GetOrientedBand( 0 )->GetValue( i, j ); }
      DetailColumnTransform1D( mpColumnIn, mpColumnOut, true );
      for ( int j = 0; j < height; j++ ) { mpPyramid->GetRecursiveScale( Scale )->GetOrientedBand( 0 )->SetValue( i, j, mpColumnOut[ j ] ); }
   
      for ( int j = 0; j < height; j++) { mpColumnIn[ j ] = mpPyramid->GetRecursiveScale( Scale )->GetOrientedBand( 1 )->GetValue( i, j ); }
      LowpassColumnTransform1D( mpColumnIn, mpColumnOut, true );
      for ( int j = 0; j < height; j++) { mpPyramid->GetRecursiveScale( Scale )->GetOrientedBand( 1 )->SetValue( i, j, mpColumnOut[ j ] ); }
      
      for ( int j = 0; j < height; j++ ) { mpColumnIn[ j ] = mpPyramid->GetRecursiveScale( Scale )->GetOrientedBand( 2 )->GetValue( i, j ); }
      DetailColumnTransform1D( mpColumnIn, mpColumnOut, true );
      for ( int j = 0; j < height; j++ ) { mpPyramid->GetRecursiveScale( Scale )->GetOrientedBand( 2 )->SetValue( i, j, mpColumnOut[ j ] ); }
   } 
   ClearExtendedDataStructures();
   
   // clean-up local storage
   delete []mpRowIn;
   delete []mpRowOut;
   delete []mpColumnIn;
   delete []mpColumnOut;
}

//------------------------------------------------------------------------------

void NonSubsampledTransform::ReconstructSingleScale( ArrayGrid<double> * pReconstructedGrid, int Scale, double threshold )
{
   int width = mpPyramid->GetLowpassResidual( )->GetWidth();
   int height = mpPyramid->GetLowpassResidual( )->GetHeight();
   // local storage for row and column to filter
   mpRowIn     = new double [ width ];
   mpRowOut    = new double [ width ];
   mpColumnIn  = new double [ height ];
   mpColumnOut = new double [ height ];
   
   //CreateExtendedDataStructures( width, height, iLowPass_Filt, iDetail_Filt, FILTERLENGTH, Scale );
   CreateExtendedDataStructures( width, height, mSet.pLowpassInvers, mSet.pHighpassInvers, mSet.length, Scale );
   
   // horizontal filtering
   for ( int x = 0; x < width; x++)
   {
      for ( int y = 0; y < height; y++ ) { mpColumnIn[ y ] = mpPyramid->GetLowpassResidual( )->GetValue( x, y ); }
      LowpassColumnTransform1D( mpColumnIn, mpColumnOut, false );
      for ( int y = 0; y < height; y++ ) { mpPyramid->GetLowpassResidual( )->SetValue( x, y, mpColumnOut[ y ] ); }
       
      for ( int y = 0; y < height; y++ ) { mpColumnIn[ y ] = mpPyramid->GetRecursiveScale( Scale )->GetOrientedBand( 0 )->GetValue( x, y ); }
      DetailColumnTransform1D( mpColumnIn, mpColumnOut, false );
      for ( int y = 0; y < height; y++ ) { mpPyramid->GetRecursiveScale( Scale )->GetOrientedBand( 0 )->SetValue( x, y, mpColumnOut[ y ] ); }
   
      for ( int y = 0; y < height; y++ ) { mpColumnIn[ y ] = mpPyramid->GetRecursiveScale( Scale )->GetOrientedBand( 1 )->GetValue( x, y ); }
      LowpassColumnTransform1D( mpColumnIn, mpColumnOut, false );
      for ( int y = 0; y < height; y++ ) { mpPyramid->GetRecursiveScale( Scale )->GetOrientedBand( 1 )->SetValue( x, y, mpColumnOut[ y ] ); }
   
      for ( int y = 0; y < height; y++ ) { mpColumnIn[ y ] = mpPyramid->GetRecursiveScale( Scale )->GetOrientedBand( 2 )->GetValue( x, y ); }
      DetailColumnTransform1D( mpColumnIn, mpColumnOut, false );
      for ( int y = 0; y < height; y++ ) { mpPyramid->GetRecursiveScale( Scale )->GetOrientedBand( 2 )->SetValue( x, y, mpColumnOut[ y ] ); }
   }

   // vertical filtering
   for ( int y = 0; y < height; y++ )
   {
      for ( int x = 0; x < width; x++ )  { mpRowIn[ x ] = mpPyramid->GetLowpassResidual( )->GetValue( x, y ); }
      LowpassRowTransform1D( mpRowIn, mpRowOut, false );
      for ( int x = 0; x < width; x++ )  { mpPyramid->GetLowpassResidual( )->SetValue( x, y, mpRowOut[ x ] ); }
   
      for ( int x = 0; x < width; x++ )  { mpRowIn[ x ] = mpPyramid->GetRecursiveScale( Scale )->GetOrientedBand( 0 )->GetValue( x, y ); }
      LowpassRowTransform1D( mpRowIn, mpRowOut, false );
      for ( int x = 0; x < width; x++ )  { mpPyramid->GetRecursiveScale( Scale )->GetOrientedBand( 0 )->SetValue( x, y, mpRowOut[ x ] ); }
   
      for ( int x = 0; x < width; x++ )  { mpRowIn[x] = mpPyramid->GetRecursiveScale( Scale )->GetOrientedBand( 1 )->GetValue( x, y ); }
      DetailRowTransform1D( mpRowIn, mpRowOut, false );
      for ( int x = 0; x < width; x++ )  { mpPyramid->GetRecursiveScale( Scale )->GetOrientedBand( 1 )->SetValue( x, y, mpRowOut[ x ] ); }
   
      for ( int x = 0; x < width; x++ )  { mpRowIn[x] = mpPyramid->GetRecursiveScale( Scale )->GetOrientedBand( 2 )->GetValue( x, y ); }
      DetailRowTransform1D( mpRowIn, mpRowOut, false );
      for ( int x = 0; x < width; x++ )  { mpPyramid->GetRecursiveScale( Scale )->GetOrientedBand( 2 )->SetValue( x, y, mpRowOut[ x ] ); }
   }
   
   if ( threshold > 0.0 )
   {
      for ( int j = 0; j < height; j++ )
      {
         for ( int i = 0; i < width; i++ )
         {
            if ( fabs( mpPyramid->GetRecursiveScale( Scale )->GetOrientedBand( 2 )->GetValue( i, j ) ) < threshold ) 
            {
               mpPyramid->GetRecursiveScale( Scale )->GetOrientedBand( 2 )->SetValue( i, j, 0.0 );
            }
            if ( fabs( mpPyramid->GetRecursiveScale( Scale )->GetOrientedBand( 1 )->GetValue( i, j ) ) < threshold ) 
            {
               mpPyramid->GetRecursiveScale( Scale )->GetOrientedBand( 1 )->SetValue( i, j, 0.0 );
            }
            if ( fabs( mpPyramid->GetRecursiveScale( Scale )->GetOrientedBand( 0 )->GetValue( i, j ) ) < threshold ) 
            {
               mpPyramid->GetRecursiveScale( Scale )->GetOrientedBand( 0 )->SetValue( i, j, 0.0 );
            }
            
            // store mean of the 4 filtered values
            pReconstructedGrid->SetValue( i, j, ( ( mpPyramid->GetRecursiveScale( Scale )->GetOrientedBand( 2 )->GetValue( i, j ) +
                                                    mpPyramid->GetRecursiveScale( Scale )->GetOrientedBand( 1 )->GetValue( i, j ) +
                                                    mpPyramid->GetRecursiveScale( Scale )->GetOrientedBand( 0 )->GetValue( i, j ) +
                                                    mpPyramid->GetLowpassResidual( )->GetValue( i, j ) ) / 4.0 ));
         }
      }
   }
   else
   {
      for (int j=0; j<height; j++)
      {
         for (int i=0; i<width; i++)
         {
            // store mean of the 4 filtered values
            pReconstructedGrid->SetValue( i, j, ( ( mpPyramid->GetRecursiveScale( Scale )->GetOrientedBand( 2 )->GetValue( i, j ) +
                                                    mpPyramid->GetRecursiveScale( Scale )->GetOrientedBand( 1 )->GetValue( i, j ) +
                                                    mpPyramid->GetRecursiveScale( Scale )->GetOrientedBand( 0 )->GetValue( i, j ) +
                                                    mpPyramid->GetLowpassResidual( )->GetValue( i, j ) ) / 4.0 ));
         }
      }
   }

   ClearExtendedDataStructures();
   
   // clean-up local storage
   delete []mpRowIn;
   delete []mpRowOut;
   delete []mpColumnIn;
   delete []mpColumnOut;
}

//------------------------------------------------------------------------------

void NonSubsampledTransform::LowpassRowTransform1D( double * pInputData, double * pFilteredData, bool isForward )
{
   if (isForward)
   {
      for (int i = 0; i < mWidth; i++ )                    { mpExtendedRowInputData[ i          ] = pInputData[i];     }
      for (int i = 0; i < mExtendedFilterLength - 1; i++ ) { mpExtendedRowInputData[ mWidth + i ] = mpExtendedRowInputData[i]; }
   }
   else
   {
      for (int i = 0; i < mWidth;  i++)                    { mpExtendedRowInputData[ i + mExtendedFilterLength - 1 ] = pInputData[ i ]; }
      for (int i = 0; i < mExtendedFilterLength - 1 ; i++) { mpExtendedRowInputData[i] = mpExtendedRowInputData[ i + mWidth ]; }
   }
   
   FilterRow( mpExtendedRowOutputData, mpExtendedLowpassFilter, mpExtendedRowInputData );
   // take relevant part (cut endings)
   for (int i = 0; i < mWidth; i++) { pFilteredData[ i ] = mpExtendedRowOutputData[ i + mExtendedFilterLength - 1 ]; }
}

//------------------------------------------------------------------------------

void NonSubsampledTransform::LowpassColumnTransform1D( double * pInputData, double * pFilteredData, bool isForward )
{
   if (isForward)
   {
      for (int i = 0; i < mHeight; i++ )                   { mpExtendedColumnInputData[ i           ] = pInputData[i];     }
      for (int i = 0; i < mExtendedFilterLength - 1; i++ ) { mpExtendedColumnInputData[ mHeight + i ] = mpExtendedColumnInputData[i]; }
   }
   else
   {
      for (int i = 0; i < mHeight;  i++)                   { mpExtendedColumnInputData[ i + mExtendedFilterLength - 1 ] = pInputData[ i ]; }
      for (int i = 0; i < mExtendedFilterLength - 1 ; i++) { mpExtendedColumnInputData[i] = mpExtendedColumnInputData[ i + mHeight ]; }
   }
   
   FilterColumn( mpExtendedColumnOutputData, mpExtendedLowpassFilter, mpExtendedColumnInputData );
   // take relevant part (cut endings)
   for (int i = 0; i < mHeight; i++) { pFilteredData[ i ] = mpExtendedColumnOutputData[ i + mExtendedFilterLength - 1 ]; }
}

//------------------------------------------------------------------------------

void NonSubsampledTransform::DetailRowTransform1D( double * pInputData, double * pFilteredData, bool isForward )
{
   if (isForward)
   {
      for (int i = 0; i < mWidth; i++ )                    { mpExtendedRowInputData[ i          ] = pInputData[i]; }
      for (int i = 0; i < mExtendedFilterLength - 1; i++ ) { mpExtendedRowInputData[ mWidth + i ] = mpExtendedRowInputData[i]; }
   }
   else
   {
      for (int i = 0; i < mWidth;  i++)                    { mpExtendedRowInputData[ i + mExtendedFilterLength - 1 ] = pInputData[ i ]; }
      for (int i = 0; i < mExtendedFilterLength - 1 ; i++) { mpExtendedRowInputData[i] = mpExtendedRowInputData[ i + mWidth ]; }
   }
   
   FilterRow( mpExtendedRowOutputData, mpExtendedDetailFilter, mpExtendedRowInputData );
   // take relevant part (cut endings)
   for (int i = 0; i < mWidth; i++) { pFilteredData[ i ] = mpExtendedRowOutputData[ i + mExtendedFilterLength - 1 ]; }
}

//------------------------------------------------------------------------------

void NonSubsampledTransform::DetailColumnTransform1D( double * pInputData, double * pFilteredData, bool isForward )
{
   if (isForward)
   {
      for (int i = 0; i < mHeight; i++ )                   { mpExtendedColumnInputData[ i           ] = pInputData[i];     }
      for (int i = 0; i < mExtendedFilterLength - 1; i++ ) { mpExtendedColumnInputData[ mHeight + i ] = mpExtendedColumnInputData[i]; }
   }
   else
   {
      for (int i = 0; i < mHeight;  i++)                   { mpExtendedColumnInputData[ i + mExtendedFilterLength - 1 ] = pInputData[ i ];       }
      for (int i = 0; i < mExtendedFilterLength - 1 ; i++) { mpExtendedColumnInputData[i]                               = mpExtendedColumnInputData[ i + mHeight ]; }
   }
   
   FilterColumn( mpExtendedColumnOutputData, mpExtendedDetailFilter, mpExtendedColumnInputData );
   // take relevant part (cut endings)
   for (int i = 0; i < mHeight; i++) { pFilteredData[ i ] = mpExtendedColumnOutputData[ i + mExtendedFilterLength - 1 ]; }
}

//------------------------------------------------------------------------------

void NonSubsampledTransform::FilterRow( double * pOutputData, double * pFilterTaps, double * pInputData)
{
   for (int i = 0; i < mExtraExtendedWidth; i++)
   {
      mpExtraExtendedRowData[i]     = 0;
   }
   for (int i = 0; i < mExtendedInputWidth; i++)
   {
      mpExtraExtendedRowData[ i + mExtendedFilterLength - 1 ] = pInputData[ i ];
   }
   
   // convolution kernel
   for (int i = 0; i< mExtendedFilterLength + mExtendedInputWidth - 1; i++)
   {
      double c = 0; // result value 
      for (int j=0; j<mExtendedFilterLength; j++) 
      { 
         c += pFilterTaps[ mExtendedFilterLength - j - 1 ] * mpExtraExtendedRowData[ i + j ];
      }
      pOutputData[i] = c;
   }
}

//------------------------------------------------------------------------------

void NonSubsampledTransform::FilterColumn( double * pOutputData, double * pFilterTaps, double * pInputData)
{
   for (int i = 0; i < mExtraExtendedHeight; i++)
   {
      mpExtraExtendedColumnData[ i ] = 0;
   }
   for (int i = 0; i<mExtendedInputHeight; i++)
   {
      mpExtraExtendedColumnData[ i + mExtendedFilterLength - 1 ] = pInputData[ i ];
   }
   
   // convolution kernel
   for (int i = 0; i < mExtendedFilterLength + mExtendedInputHeight - 1; i++)
   {
      double c = 0; // result value 
      for (int j = 0; j < mExtendedFilterLength; j++)
      {
         c += pFilterTaps[ mExtendedFilterLength - j - 1 ] * mpExtraExtendedColumnData[ i + j ];
      }
      pOutputData[ i ] = c;
   }
}

//------------------------------------------------------------------------------

}
}
