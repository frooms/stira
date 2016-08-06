
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

#include "NonLocalMeansFilter.h"
#include "../../common/common/MathUtils.h"
#include "../../imagetools/tools/ImageTools.h"

namespace stira{
namespace filter{

using namespace common;
using namespace image;
using namespace std;

NonLocalMeansFilter::NonLocalMeansFilter( int size )
{
   mBlockSize = size;

   mBlockHalfSize = (int)(mBlockSize / 2);
   mSigma = (double)(mBlockHalfSize) * 20.0;
   mSearchWindowSize = mBlockSize * 1;
   mNrIterations = 1;
}

//-------------------------------------------------------------------

NonLocalMeansFilter::~NonLocalMeansFilter()
{
}

//-------------------------------------------------------------------
void NonLocalMeansFilter::SetBlockSize( int size )
{
   mBlockSize = size;
}

//-------------------------------------------------------------------

int NonLocalMeansFilter::GetBlockSize( )
{
   return mBlockSize;
}

//-------------------------------------------------------------------

void NonLocalMeansFilter::SetSigma( double sigma )
{
   mSigma = sigma;
}

//-------------------------------------------------------------------

double NonLocalMeansFilter::GetSigma( )
{
   return mSigma;
}

//-------------------------------------------------------------------

double NonLocalMeansFilter::ComputeEuclideanDistance( int xCenter1, int yCenter1, int xCenter2, int yCenter2 )
{
   double myDistance = 0.0;
   for (int dy = -mBlockHalfSize; dy <= mBlockHalfSize; dy++)
   {
      for (int dx = -mBlockHalfSize; dx <= mBlockHalfSize; dx++)
      {
         myDistance += POWER2(   mpGridIn->GetValue( xCenter1 + dx, yCenter1 + dy )
                               - mpGridIn->GetValue( xCenter2 + dx, yCenter2 + dy )
                             );
      }
   }
   return myDistance;
}

//-------------------------------------------------------------------

std::vector< blockMatch > NonLocalMeansFilter::CheckNeighboringBlocks( int xCenter, int yCenter )
{
   vector< blockMatch > myBlocks;
   for (int y = -mSearchWindowSize; y < mSearchWindowSize; y++)
   {
      for (int x = -mSearchWindowSize; x < mSearchWindowSize; x++)
      {
         blockMatch newBlock;
         newBlock.x = x + xCenter;
         newBlock.y = y + yCenter;
         newBlock.distance = ComputeEuclideanDistance( x + xCenter, y + yCenter, xCenter, yCenter );
         myBlocks.push_back( newBlock );
      }
   }
   return myBlocks;
}

//-------------------------------------------------------------------

void NonLocalMeansFilter::FilterCurrentBlock( int xCenter, int yCenter, vector< blockMatch > myBlocks )
{
   for (int y = -mBlockHalfSize; y <= mBlockHalfSize; y++)
   {
      for (int x = -mBlockHalfSize; x <= mBlockHalfSize; x++)
      {
         double tmpValue  = 0.0;
         double totalWeight = 0.0;
         for (int i = 0; i < (int)(myBlocks.size()); i++)
         {
            double tmpWeight = exp( -( myBlocks[i].distance ) / POWER2( mSigma ) );
            tmpValue += ( mpGridIn->GetValue( myBlocks[i].x + x, myBlocks[i].y + y ) * tmpWeight);
            totalWeight += tmpWeight;
         }
         mpGridOut->SetValue( xCenter + x, yCenter + y, tmpValue / totalWeight );
      }
   }
}

//-------------------------------------------------------------------

void NonLocalMeansFilter::LoopOverImage( )
{
   vector< blockMatch > myBlocks;

   int start = mSearchWindowSize + mBlockHalfSize;
   int stopX = mSourceWidth  + mSearchWindowSize + mBlockHalfSize;
   int stopY = mSourceHeight + mSearchWindowSize + mBlockHalfSize;

   for (int y = start; y < stopY; y +=mBlockSize )
   {
      for (int x = start; x < stopX; x +=mBlockSize-1 )
      {
         vector< blockMatch > myBlocks = CheckNeighboringBlocks( x, y );
         FilterCurrentBlock( x, y, myBlocks );
      }
   }
}

//-------------------------------------------------------------------

image::Image* NonLocalMeansFilter::Run( image::Image* pImageIn )
{
   int borderSize = (int)(1.5 * (double)(mSearchWindowSize));
   mSourceWidth = pImageIn->GetWidth();
   mSourceHeight = pImageIn->GetHeight();
   Image* pImageInExtended = ImageTools::MirrorBorder( pImageIn, borderSize, borderSize );
   Image* pImageTmpExtended = pImageInExtended->Clone();
   Image* pImageOutExtended = pImageInExtended->Clone();

   mExtendedWidth = pImageInExtended->GetWidth();
   mExtendedHeight = pImageInExtended->GetHeight();
   mNrBands = pImageInExtended->GetNumberOfBands();

   for (int iter = 0; iter < mNrIterations; iter++)
   {
      for (int i = 0; i < mNrBands; i++)
      {
         mpGridIn  = pImageTmpExtended->GetBands()[ i ];
         mpGridOut = pImageOutExtended->GetBands()[ i ];

         LoopOverImage( );
      }
      pImageTmpExtended->CopyImageValues( pImageOutExtended );
   }
   Image* pImageOut = ImageTools::CropBorder( pImageOutExtended, borderSize, borderSize );
   delete pImageInExtended;
   delete pImageOutExtended;
   delete pImageTmpExtended;
   std::string outName = pImageIn->GetImageName() + std::string("-NonLocalMeans");
   pImageOut->SetImageName(outName);
   return pImageOut;
}

//-------------------------------------------------------------------

}
}

