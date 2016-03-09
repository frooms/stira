#include "FloodFill.h"
#include <iostream>

using namespace stira::common;
using namespace std;
using namespace stira::image;

namespace stira {
namespace imageanalysis {

//------------------------------------------------------------------------------------------

FloodFill::FloodFill()
{
}

//------------------------------------------------------------------------------------------

void FloodFill::Fill4Connected( ArrayGrid<int>* pGrid, int nodeX, int nodeY, int targetValue, int replacementValue )
{
   if ( ( nodeX >= 0 ) && ( nodeX < pGrid->GetWidth() ) && ( nodeY >= 0 ) && ( nodeY < pGrid->GetHeight() ) )
   {
      if ( pGrid->GetValue( nodeX, nodeY ) == targetValue )
      {
         pGrid->SetValue( nodeX, nodeY, replacementValue );
         mNrPixelsFlooded++;
         Point<int> pt(nodeX, nodeY);
         mvPixelsFlooded.push_back( pt );
         if ( nodeX - 1 >= 0                )  { Fill4Connected( pGrid, nodeX-1, nodeY,   targetValue, replacementValue ); }
         if ( nodeX + 1 < pGrid->GetWidth() )  { Fill4Connected( pGrid, nodeX+1, nodeY,   targetValue, replacementValue ); }
         if ( nodeY - 1 >= 0 )                 { Fill4Connected( pGrid, nodeX,   nodeY-1, targetValue, replacementValue ); }
         if ( nodeY + 1 < pGrid->GetHeight() ) { Fill4Connected( pGrid, nodeX,   nodeY+1, targetValue, replacementValue ); }

         return;
      }
   }
}

//------------------------------------------------------------------------------------------

void FloodFill::Fill8Connected( ArrayGrid<int>* pGrid, int nodeX, int nodeY, int targetValue, int replacementValue )
{
   if ( ( nodeX >= 0 ) && ( nodeX < pGrid->GetWidth() ) && ( nodeY >= 0 ) && ( nodeY < pGrid->GetHeight() ) )
   {
      if ( pGrid->GetValue( nodeX, nodeY ) == targetValue )
      {
         pGrid->SetValue( nodeX, nodeY, replacementValue );
         mNrPixelsFlooded++;
         Point<int> pt(nodeX, nodeY);
         mvPixelsFlooded.push_back( pt );
         if ( nodeX - 1 >= 0                )  { Fill8Connected( pGrid, nodeX-1, nodeY,   targetValue, replacementValue ); }
         if ( nodeX + 1 < pGrid->GetWidth() )  { Fill8Connected( pGrid, nodeX+1, nodeY,   targetValue, replacementValue ); }
         if ( nodeY - 1 >= 0 )                 { Fill8Connected( pGrid, nodeX,   nodeY-1, targetValue, replacementValue ); }
         if ( nodeY + 1 < pGrid->GetHeight() ) { Fill8Connected( pGrid, nodeX,   nodeY+1, targetValue, replacementValue ); }

         if ( ( nodeX - 1 >= 0                 ) && ( nodeY - 1 >= 0) )                  { Fill8Connected( pGrid, nodeX-1, nodeY-1,   targetValue, replacementValue ); }
         if ( ( nodeX - 1 >= 0                 ) && ( nodeY +1 < pGrid->GetHeight() ) )  { Fill8Connected( pGrid, nodeX-1, nodeY+1,   targetValue, replacementValue ); }
         if ( ( nodeX + 1 < pGrid->GetWidth()  ) && ( nodeY - 1 >= 0) )                  { Fill8Connected( pGrid, nodeX+1, nodeY-1,   targetValue, replacementValue ); }
         if ( ( nodeX + 1 < pGrid->GetWidth()  ) && ( nodeY +1 < pGrid->GetHeight() ) )  { Fill8Connected( pGrid, nodeX+1, nodeY+1,   targetValue, replacementValue ); }

         return;
      }
   }
}

//------------------------------------------------------------------------------------------

int FloodFill::Run( ArrayGrid<int>* pGrid, int nodeX, int nodeY, int targetValue, int replacementValue, bool fill8Connected )
{
   mNrPixelsFlooded = 0;
   mvPixelsFlooded.clear();
   if ( fill8Connected )
   {
      Fill8Connected( pGrid, nodeX, nodeY, targetValue, replacementValue );
   }
   else
   {
      Fill4Connected( pGrid, nodeX, nodeY, targetValue, replacementValue );
   }
   return mNrPixelsFlooded;
}

//------------------------------------------------------------------------------------------

std::vector< Point<int> > FloodFill::GetFloodedPixels()
{
   return mvPixelsFlooded;
}

//------------------------------------------------------------------------------------------

common::Point<double> FloodFill::GetCenterOfGravity()
{
   double tmpX = 0.0;
   double tmpY = 0.0;
   int nrElements = 0;
   for( std::vector< common::Point<int> >::iterator it = mvPixelsFlooded.begin();
        it != mvPixelsFlooded.end();
        ++it
      )
   {
      tmpX += (double)( (*it).x );
      tmpY += (double)( (*it).y );
      nrElements++;
   }
   if (nrElements != 0)
   {
      return Point<double>( tmpX / nrElements, tmpY / nrElements );
   }
   else
   {
      return Point<double>( 0, 0 );
   }
}

//------------------------------------------------------------------------------------------

common::RectangularROI<int> FloodFill::GetBoundingBox()
{
   double minX =  1000000000.0;
   double minY =  1000000000.0;
   double maxX = -1000000000.0;
   double maxY = -1000000000.0;

   for( std::vector< common::Point<int> >::iterator it = mvPixelsFlooded.begin();
        it != mvPixelsFlooded.end();
        ++it
      )
   {
      double tmpX = (double)( (*it).x );
      double tmpY = (double)( (*it).y );
      if ( tmpX < minX ) { minX = tmpX; }
      if ( tmpX > maxX ) { maxX = tmpX; }
      if ( tmpY < minY ) { minY = tmpY; }
      if ( tmpY > maxY ) { maxY = tmpY; }
   }

   return RectangularROI<int>( Point<int>( (int)(minX + 0.5), (int)(minY + 0.5) ),
                               Point<int>( (int)(maxX + 0.5), (int)(maxY + 0.5) )
                             );
}

//------------------------------------------------------------------------------------------

ArrayGrid<int>* FloodFill::PrepareValues( ArrayGrid<double>* pGrid, int lowerBound, int upperBound, int targetValue )
{
   int width  = pGrid->GetWidth();
   int height = pGrid->GetHeight();
   ArrayGrid<int>* pPreparedGrid = new ArrayGrid<int>( width, height );

   for ( int y = 0; y < height; y++ )
   {
      for ( int x = 0; x < width; x++ )
      {
         if ( ( pGrid->GetValue(x, y) >= lowerBound ) && ( pGrid->GetValue(x, y) <= upperBound + 1 ) )
         {
            pPreparedGrid->SetValue( x, y, targetValue );
         }
      }
   }
   return pPreparedGrid;
}

//------------------------------------------------------------------------------------------

}
}

