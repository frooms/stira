#include "SubsampledTransform.h"

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include "../../imagedata/simpletools/ArrayGridTools.h"
#include "../../imagetools/tools/NumberGridTools.h"
#include "../../imagetools/tools/PyramidTools.h"

//#define VIEW_FILTER_TAPS
namespace stira {
namespace wavelet {

using namespace image;
using namespace std;
using namespace common;

SubsampledTransform::SubsampledTransform( WaveletType type )
{
   WaveletTapGenerator wtg;
   mSet = wtg.Generate( type );
   mpBuffer = 0;
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

//-------------------------------------------------------------------------------

SubsampledTransform::~SubsampledTransform()
{
   delete [](mSet.pLowpassInvers);
   delete [](mSet.pLowpassForward);
   delete [](mSet.pHighpassInvers);
   delete [](mSet.pHighpassForward);
}

//-------------------------------------------------------------------------------

void SubsampledTransform::Decompose1D( double* pArray )
{
   int filterLength = mSet.length;
   for (int i = 0; i < mBufferLength - (filterLength-1); i += 2)
   {
      mpBuffer[i]   = 0.0;
      mpBuffer[i+1] = 0.0;
      for (int k = 0; k < filterLength; k++)
      {
         mpBuffer[i]   += ( mSet.pLowpassForward[ k ]  * pArray[ i + k ] );
         mpBuffer[i+1] -= ( mSet.pHighpassForward[ k ] * pArray[ i + k ] );
      }
   }

   int startLength = filterLength - 2;
   
   for (int tmpLength = startLength; tmpLength > 0; tmpLength-=2)
   {
      int lengthDifference = filterLength - tmpLength;
      mpBuffer[ mBufferLength - tmpLength     ] = 0.0;
      mpBuffer[ mBufferLength - tmpLength + 1 ] = 0.0;

      int ii = 0;
      for (int i1 = tmpLength; i1 > 0; i1--)
      {
         mpBuffer[ mBufferLength - tmpLength     ] += (  mSet.pLowpassForward[ ii ] * pArray[ mBufferLength - i1 ] );
         mpBuffer[ mBufferLength - tmpLength + 1 ] -= ( mSet.pHighpassForward[ ii ] * pArray[ mBufferLength - i1 ] );
         ii++;
      }
      for (int i1 = 0; i1 < lengthDifference; i1++)
      {
         mpBuffer[ mBufferLength - tmpLength   ] += (  mSet.pLowpassForward[ ii ] * pArray[ i1 ] );
         mpBuffer[ mBufferLength - tmpLength+1 ] -= ( mSet.pHighpassForward[ ii ] * pArray[ i1 ] );
         ii++;
      }
   }
   
   CopyArray( mpBuffer, pArray );
}

//-------------------------------------------------------------------------------

void SubsampledTransform::Reconstruct1D(double* pArray )
{
   int filterLength = mSet.length;
   
   int startLength = filterLength - 2;
   for ( int i = startLength; i < mBufferLength; i += 2 )
   {
      mpBuffer[i]   = 0.0;
      mpBuffer[i+1] = 0.0;
      
      for ( int j = 0; j <= startLength; j += 2 )
      {
         mpBuffer[ i   ] += (  mSet.pLowpassInvers[ j      ] * pArray[ i - j + 1] );
         mpBuffer[ i   ] += (  mSet.pLowpassInvers[ j + 1  ] * pArray[ i - startLength + j     ] );
         
         mpBuffer[ i+1 ] -= (  mSet.pHighpassInvers[ j     ] * pArray[ i - startLength + j + 1 ] );
         mpBuffer[ i+1 ] -= (  mSet.pHighpassInvers[ j + 1 ] * pArray[ i - j] );
      }
   }
   
   for ( int tmpLength = 0; tmpLength < startLength; tmpLength += 2 )
   {
      mpBuffer[ tmpLength     ] = 0.0;
      mpBuffer[ tmpLength + 1 ] = 0.0;
      for ( int i1 = 0; i1 < startLength - tmpLength; i1 += 2 )
      {
         mpBuffer[ tmpLength  ] += (  mSet.pLowpassInvers[ i1+1 ]             * pArray[ mBufferLength - (startLength - tmpLength - i1)     ] );
         mpBuffer[ tmpLength  ] += (  mSet.pLowpassInvers[ startLength - i1 ] * pArray[ mBufferLength - (startLength - tmpLength - i1 - 1) ] );
         
         mpBuffer[ tmpLength + 1 ] -= (  mSet.pHighpassInvers[ i1 ]                   * pArray[ mBufferLength - (startLength - tmpLength - i1 - 1) ] );
         mpBuffer[ tmpLength + 1 ] -= (  mSet.pHighpassInvers[ startLength - i1 + 1 ] * pArray[ mBufferLength - (startLength - tmpLength - i1 )    ] );
      }
      for ( int i1 = 0; i1 <= tmpLength; i1 += 2 )
      {
         mpBuffer[ tmpLength  ] += (  mSet.pLowpassInvers[ filterLength-i1-1 ] * pArray[ tmpLength - i1     ] );
         mpBuffer[ tmpLength  ] += (  mSet.pLowpassInvers[ i1 ]                * pArray[ tmpLength - i1 + 1 ] );
         
         mpBuffer[ tmpLength + 1 ] -= (  mSet.pHighpassInvers[ filterLength-i1-2 ] * pArray[ tmpLength - i1 + 1 ] );
         mpBuffer[ tmpLength + 1 ] -= (  mSet.pHighpassInvers[ i1+1 ]              * pArray[ tmpLength - i1     ] );
      }
   }

   CopyArray( mpBuffer, pArray );
}

//-------------------------------------------------------------------------------

void SubsampledTransform::Permute( double *pArray )
{
   int templength = mBufferLength / 2;
   for (int i = 0; i < templength; i ++)
   {
      mpBuffer[ i              ] = pArray[ 2 * i     ];
      mpBuffer[ i + templength ] = pArray[ 2 * i + 1 ];
   }

   CopyArray( mpBuffer, pArray );
}

//-------------------------------------------------------------------------------

void SubsampledTransform::InversePermute( double *pArray )
{
   int templength = mBufferLength / 2;
   for (int i = 0; i < templength; i ++)
   {
      mpBuffer[2 * i]     = pArray[i];
      mpBuffer[2 * i + 1] = pArray[i + templength];
   }
   
   CopyArray( mpBuffer, pArray );
}

//-------------------------------------------------------------------------------

void SubsampledTransform::MultiscaleDecompose( )
{
   for ( mCurrentScale = 0; mCurrentScale < mNrScales; mCurrentScale++ )
   {
      mBufferLength = (int) ( mpDecomposeReconstructGrid->GetWidth() / pow( (double)(2.0), mCurrentScale ) );
      double *pRow    = new double[ mBufferLength ];
      double *pColumn = new double[ mBufferLength ];
      mpBuffer        = new double[ mBufferLength ];
      
      for (int j = 0; j < mBufferLength; j++)
      {
         CopyGridRowToArray( mpDecomposeReconstructGrid, pRow, j );
         Decompose1D( pRow );
         Permute( pRow );
         CopyArrayRowToGrid( pRow, mpDecomposeReconstructGrid, j );
      }
      
      for (int i = 0; i < mBufferLength; i++)
      {
         CopyGridColumnToArray( mpDecomposeReconstructGrid, pColumn, i );
         Decompose1D( pColumn );
         Permute( pColumn );
         CopyArrayColumnToGrid( pColumn, mpDecomposeReconstructGrid, i );
      }
   
      delete []pRow;
      delete []pColumn;
      delete []mpBuffer;
      mpBuffer = 0;
   }
}

//-------------------------------------------------------------------------------

void SubsampledTransform::CopyArrayRowToGrid( double* pRow, ArrayGrid<double>* pGrid, int rowNr )
{
   for (int i = 0; i < mBufferLength; i++)
   {
      pGrid->SetValue( i, rowNr, pRow[ i ] );
   }
}

//-------------------------------------------------------------------------------

void SubsampledTransform::CopyArrayColumnToGrid( double* pColumn, ArrayGrid<double>* pGrid, int columnNr )
{
   for (int j = 0; j < mBufferLength; j++)
   {
      pGrid->SetValue( columnNr, j, pColumn[ j ] );
   }
}

//-------------------------------------------------------------------------------

void SubsampledTransform::CopyGridRowToArray( ArrayGrid<double>* pGrid, double* pRow, int rowNr )
{
   for (int i = 0; i < mBufferLength; i++)
   {
      pRow[i] = pGrid->GetValue( i, rowNr );
   }
}

//-------------------------------------------------------------------------------

void SubsampledTransform::CopyGridColumnToArray( ArrayGrid<double>* pGrid, double* pColumn, int columnNr )
{
   for (int j = 0; j < mBufferLength; j++)
   {
      pColumn[j] = pGrid->GetValue( columnNr, j );
   }
}

//-------------------------------------------------------------------------------

void SubsampledTransform::CopyArray( double* pArrayIn, double* pArrayOut )
{
   for (int i = 0; i < mBufferLength; i++)
   {
      pArrayOut[i] = pArrayIn[i];
   }
}

//-------------------------------------------------------------------------------

void SubsampledTransform::MultiscaleReconstruct( )
{
   for ( mCurrentScale = mNrScales - 1; mCurrentScale > -1; mCurrentScale --)
   {
      mBufferLength = (int) ( mpDecomposeReconstructGrid->GetWidth() / pow( (double)(2.0), mCurrentScale));

      double *pRow    = new double[ mBufferLength ];
      double *pColumn = new double[ mBufferLength ];
      mpBuffer        = new double[ mBufferLength ];
      for (int j = 0; j < mBufferLength; j++)
      {
         CopyGridRowToArray( mpDecomposeReconstructGrid, pRow, j );
         InversePermute( pRow );
         Reconstruct1D( pRow );
         CopyArrayRowToGrid( pRow, mpDecomposeReconstructGrid, j );
      }

      for (int i = 0; i < mBufferLength; i++)
      {
         CopyGridColumnToArray( mpDecomposeReconstructGrid, pColumn, i );
         InversePermute( pColumn );
         Reconstruct1D( pColumn );
         CopyArrayColumnToGrid( pColumn, mpDecomposeReconstructGrid, i );
      }
      delete []pRow;
      delete []pColumn;
      delete []mpBuffer;
      mpBuffer = 0;
   }
}

//-------------------------------------------------------------------------------

bool SubsampledTransform::Decompose( image::ArrayGrid<double>* pSourceGrid, int nrScales )
{
   int width  = pSourceGrid->GetWidth();
   int height = pSourceGrid->GetHeight();
   
   assert ( width == height );
   
   mNrScales = nrScales;
   mpSourceGrid = pSourceGrid;
   mpDecomposeReconstructGrid = pSourceGrid->Clone();
   
   Initialize( mpDecomposeReconstructGrid, mNrScales );
   
   MultiscaleDecompose( );
   
   CreatePyramidFromGrid( );
   return true;
}

//-------------------------------------------------------------------------------

void SubsampledTransform::CreatePyramidFromGrid( )
{
   int sourceWidth  = mpDecomposeReconstructGrid->GetWidth();
   int sourceHeight = mpDecomposeReconstructGrid->GetWidth();
   for ( mCurrentScale = 0; mCurrentScale < mNrScales; mCurrentScale++ )
   {
      int scaleWidth  = sourceWidth  / pow( (double)(2.0), mCurrentScale+1 );
      int scaleHeight = sourceHeight / pow( (double)(2.0), mCurrentScale+1 );
      
      ArrayGrid<double>* pLHGrid = ArrayGridTools<double>::ExtractSubGrid( mpDecomposeReconstructGrid, 0,          scaleHeight,   scaleWidth, 2*scaleHeight );
      ArrayGrid<double>* pHLGrid = ArrayGridTools<double>::ExtractSubGrid( mpDecomposeReconstructGrid, scaleWidth,           0, 2*scaleWidth,   scaleHeight );
      ArrayGrid<double>* pHHGrid = ArrayGridTools<double>::ExtractSubGrid( mpDecomposeReconstructGrid, scaleWidth, scaleHeight, 2*scaleWidth, 2*scaleHeight );
      
      mpPyramid->GetRecursiveScale( mCurrentScale )->AddOrientedBand( pLHGrid );   // in on index 0
      mpPyramid->GetRecursiveScale( mCurrentScale )->AddOrientedBand( pHLGrid );   // in on index 1
      mpPyramid->GetRecursiveScale( mCurrentScale )->AddOrientedBand( pHHGrid );   // in on index 2
   }
   
   mCurrentScale = mNrScales;
   int scaleWidth  = sourceWidth  / pow( (double)(2.0), mCurrentScale );
   int scaleHeight = sourceHeight / pow( (double)(2.0), mCurrentScale );
      
   ArrayGrid<double>* pLLGrid = ArrayGridTools<double>::ExtractSubGrid( mpDecomposeReconstructGrid, 0, 0, scaleWidth, scaleHeight );
   mpPyramid->SetLowpassResidual( pLLGrid );
}

//-------------------------------------------------------------------------------

void SubsampledTransform::CreateGridFromPyramid( double threshold  )
{
   int sourceWidth  = mpDecomposeReconstructGrid->GetWidth();
   int sourceHeight = mpDecomposeReconstructGrid->GetWidth();
   
   mCurrentScale = mNrScales;
   int scaleWidth  = sourceWidth  / pow( (double)(2.0), mCurrentScale );
   int scaleHeight = sourceHeight / pow( (double)(2.0), mCurrentScale );
      
   ArrayGridTools<double>::InsertSubGrid( mpDecomposeReconstructGrid, mpPyramid->GetLowpassResidual(), 0, 0, scaleWidth, scaleHeight );
   
   for ( mCurrentScale = 0; mCurrentScale < mNrScales; mCurrentScale++ )
   {
      int scaleWidth  = sourceWidth  / pow( (double)(2.0), mCurrentScale+1 );
      int scaleHeight = sourceHeight / pow( (double)(2.0), mCurrentScale+1 );
      
      if ( threshold > 0.0 )
      {
         for (int orientationNr = 0; orientationNr < 3; orientationNr++)
         {
            NumberGridTools<double>::HardThreshold( mpPyramid->GetRecursiveScale(mCurrentScale)->GetOrientedBand( orientationNr ), threshold );
         }
      }
      
      ArrayGridTools<double>::InsertSubGrid( mpDecomposeReconstructGrid, mpPyramid->GetRecursiveScale(mCurrentScale)->GetOrientedBand(0), 0,          scaleHeight,   scaleWidth, 2*scaleHeight );
      ArrayGridTools<double>::InsertSubGrid( mpDecomposeReconstructGrid, mpPyramid->GetRecursiveScale(mCurrentScale)->GetOrientedBand(1), scaleWidth,           0, 2*scaleWidth,   scaleHeight );
      ArrayGridTools<double>::InsertSubGrid( mpDecomposeReconstructGrid, mpPyramid->GetRecursiveScale(mCurrentScale)->GetOrientedBand(2), scaleWidth, scaleHeight, 2*scaleWidth, 2*scaleHeight );
   }
}

//-------------------------------------------------------------------------------

bool SubsampledTransform::Reconstruct( double threshold )
{
   CreateGridFromPyramid( threshold );
   
   MultiscaleReconstruct( );
   return true;
}

//-------------------------------------------------------------------------------

}
}
