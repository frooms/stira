
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

#include "WatershedToboggan.h"
#include <algorithm>
#include <string>
#include <iostream>
#include "../../common/common/Point.h"
#include "../../image/tools/ImageIO.h"
#include "../../image/datastructures/OrientationGrid.h"
#include "../../filter/filter/NonSeparableFilter.h"

#include "Thinning.h"

#define USE_GRADIENT

using namespace std;

namespace stira {
namespace imageanalysis {

using namespace image;
using namespace filter;

//----------------------------------------------------------------

bool MyPixelSortPredicate(const PixelElement<int>& lhs, const PixelElement<int>& rhs)
{
  return lhs.value < rhs.value;
}

//----------------------------------------------------------------

WatershedToboggan::WatershedToboggan()
{
   mpLabelGrid = 0;
   mpDistanceGrid = 0;
   mpWatershedGrid = 0;
}

//----------------------------------------------------------------

WatershedToboggan::~WatershedToboggan()
{
   if ( mpLabelGrid     != 0 ) { delete mpLabelGrid;}
   if ( mpDistanceGrid  != 0 ) { delete mpDistanceGrid;}
   if ( mpWatershedGrid != 0 ) { delete mpWatershedGrid; }
}

//----------------------------------------------------------------

int WatershedToboggan::GetSourceIntensity( int x, int y )
{
   return (int)(mpSourceGrid->GetValue( x, y ) + 0.5);
}

//----------------------------------------------------------------

int WatershedToboggan::GetLabel( int x, int y )
{
   return mpLabelGrid->GetValue( x, y );
}

//----------------------------------------------------------------

void WatershedToboggan::SetLabel( int x, int y, int label )
{
   mpLabelGrid->SetValue( x, y, label );
}

//----------------------------------------------------------------

int WatershedToboggan::GetDistance( int x, int y )
{
   return mpDistanceGrid->GetValue( x, y );
}

//----------------------------------------------------------------

void WatershedToboggan::SetDistance( int x, int y, int distance )
{
   mpDistanceGrid->SetValue( x, y, distance );
}

//----------------------------------------------------------------

void WatershedToboggan::CreateSortedPixelList( )
{
   int width  = mpSourceGrid->GetWidth();
   int height = mpSourceGrid->GetHeight();
   
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         mvSortedPixelElementVector.push_back( CreatePixelElement( x, y) );
      }
   }
   
   std::sort( mvSortedPixelElementVector.begin(), mvSortedPixelElementVector.end(), MyPixelSortPredicate);
}

//----------------------------------------------------------------

void WatershedToboggan::PrintPixelElementVector( )
{
   for ( std::vector< PixelElement<int> >::iterator it = mvSortedPixelElementVector.begin(); it != mvSortedPixelElementVector.end(); ++it)
   {
      cout << "At (" << (*it).x << ", " << (*it).y << "), we have " << (*it).value << endl << flush;
   }
}

//----------------------------------------------------------------

void WatershedToboggan::InspectNeighboursOfNewMinima( int x, int y )
{
   if ( GetLabel( x, y ) == LABEL_MASK)
   {
      SetLabel( x, y, mCurrentLabel );
      mpFifoQueue.push( CreatePixelElement( x, y) );
   }
}

//----------------------------------------------------------------

std::vector< PixelElement<int> > WatershedToboggan::MaskInitialCandidates( int currentIndex )
{
   std::vector< PixelElement<int> > maskedPixelVector;
   int i = currentIndex;
   
   while (    ( i < (int)( mvSortedPixelElementVector.size() ) )
           && ( mvSortedPixelElementVector[i].value <= mCurrentLevel )
         )
   {
      int x = mvSortedPixelElementVector[i].x;
      int y = mvSortedPixelElementVector[i].y;
      //if (GetLabel( x, y) == LABEL_INITIAL)
      //{
         SetLabel( x, y, LABEL_MASK );
         SetDistance( x, y, 1 );
         maskedPixelVector.push_back( mvSortedPixelElementVector[i] );
      //}
      i++;
   }
   mCurrentDistance = 1;
   return maskedPixelVector;
}

//----------------------------------------------------------------

bool WatershedToboggan::IsValidNeighbour(int x, int y, int dx, int dy)
{
   if ( (dx != 0 ) || (dy != 0) ) // otherwise, neighbour is pixel itself
   {
      int xx = x + dx;
      int yy = y + dy;
      if (     (xx >= 0) 
            && (xx < mpLabelGrid->GetWidth()) 
            && (yy >= 0) 
            && (yy < mpLabelGrid->GetHeight())
         )
      {
         return true;
      }
   }
   return false;
}

//----------------------------------------------------------------

PixelElement<int> WatershedToboggan::GetSmallestNeighbour( int x, int y )
{
   PixelElement<int> pe;
   pe.value = 100000000;
   for (int dy = -1; dy <= 1; dy++)
   {
      for (int dx = -1; dx <= 1; dx++)
      {
         if ( IsValidNeighbour( x, y, dx, dy) )
         {
            int xx = x + dx;
            int yy = y + dy;
            if ( GetSourceIntensity( xx, yy ) < pe.value )
            {
               pe = CreatePixelElement( xx, yy );
            }
         }
      }
   }
   return pe;
}

//----------------------------------------------------------------

int WatershedToboggan::GetLabelFromNeighbours( int x, int y )
{
   PixelElement<int> pe = GetSmallestNeighbour( x, y );
   int smallestIntensityLabel = GetLabel( pe.x, pe.y );

   if ( pe.value < mCurrentLevel )
   {
      bool minimumNeighboursHaveUniqueLabel = true;
      for (int dy = -1; dy <= 1; dy++)
      {
         for (int dx = -1; dx <= 1; dx++)
         {
            if ( IsValidNeighbour( x, y, dx, dy) )
            {
               int xx = x + dx;
               int yy = y + dy;
               
               // check if all neighbours with same smallest intensity have the same label = 'smallestIntensityLabel'
               if (     ( GetSourceIntensity( xx, yy ) == pe.value)
                     && ( GetLabel( xx, yy ) != smallestIntensityLabel )
                  )
               {
                  minimumNeighboursHaveUniqueLabel = false;
               }
            }
         }
      }
      
      if (minimumNeighboursHaveUniqueLabel)
      {
         SetLabel( x, y, smallestIntensityLabel );
      }
      else
      {
         //SetLabel( x, y, LABEL_WATERSHED );
         mpWatershedGrid->SetValue( x, y, true );
      }
      SetDistance( x, y, 0 );
   
      mpFifoQueue.push( CreatePixelElement( x, y) );
      return 1;

   }

   return 0;
}

//----------------------------------------------------------------

int WatershedToboggan::DetermineMaskLabelsFromLabeledNeighbours( std::vector< PixelElement<int> >& maskedPixelVector )
{
   int nrProcessedPixels = 0;
   for ( std::vector< PixelElement<int> >::iterator it  = maskedPixelVector.begin();
                                             it != maskedPixelVector.end();
                                             ++it
       )
   {
      nrProcessedPixels += GetLabelFromNeighbours( (*it).x, (*it).y );
   }

   return nrProcessedPixels;
}

//----------------------------------------------------------------

void WatershedToboggan::ProcessNeighboursOfQueueElements(int x, int y)
{
   if ( GetLabel( x, y ) > 0)
   {
      for (int dy = -1; dy <= 1; dy++)
      {
         for (int dx = -1; dx <= 1; dx++)
         {
            if ( IsValidNeighbour( x, y, dx, dy) )
            {
               int xx = x + dx;
               int yy = y + dy;
               if ( GetLabel( xx, yy ) == LABEL_MASK )
               {
                  SetLabel( xx, yy, GetLabel( x, y ) );
                  SetDistance( xx, yy, mCurrentDistance );
                  mpFifoQueue.push( CreatePixelElement( xx, yy ) );
               }
               else if (    (    GetLabel( xx, yy ) != GetLabel( x, y ) ) 
                         && ( GetDistance( xx, yy ) == mCurrentDistance-1 )
                         //&& ( GetDistance( xx, yy ) == mCurrentDistance )
                       )
               {
                  //SetLabel( xx, yy, LABEL_WATERSHED );
                  mpWatershedGrid->SetValue( x, y, true );
               }
            }
         }
      }
   }
}

//----------------------------------------------------------------

PixelElement<int>  WatershedToboggan::CreatePixelElement(int x, int y )
{
   PixelElement<int> pe;
   pe.x = x;
   pe.y = y;
   pe.value = GetSourceIntensity( x, y );
   return pe;
}

//----------------------------------------------------------------

void WatershedToboggan::ProcessNewMinima( std::vector< PixelElement<int> > vCurrentLevelPixels )
{
   for ( std::vector< PixelElement<int> >::iterator it  = vCurrentLevelPixels.begin();
                                             it != vCurrentLevelPixels.end();
                                             ++it
       )
   {
      int x = (*it).x;
      int y = (*it).y;
      if ( GetLabel( x, y ) == LABEL_MASK )
      {
         mCurrentLabel++;
         SetLabel( x, y, mCurrentLabel );
         mpFifoQueue.push( (*it) );
         
         while (  !(mpFifoQueue.empty() ))
         {
            PixelElement<int> pe = mpFifoQueue.front();
            mpFifoQueue.pop();
            int x = pe.x;
            int y = pe.y;
            for (int dy = -1; dy <= 1; dy++)
            {
               for (int dx = -1; dx <= 1; dx++)
               {
                  if ( IsValidNeighbour( x, y, dx, dy ) )
                  {
                     InspectNeighboursOfNewMinima( x+dx, y+dy );
                  }
               }
            }
         }
      }
   }
}

//----------------------------------------------------------------

void WatershedToboggan::ResetQueue()
{
   while (  !(mpFifoQueue.empty() ))
   {
      mpFifoQueue.front();
      mpFifoQueue.pop();
   }
}

//----------------------------------------------------------------

ArrayGrid<int>* WatershedToboggan::Run( image::ArrayGrid<double>* pGridIn )
{
   int width  = pGridIn->GetWidth();
   int height = pGridIn->GetHeight();
   
   #ifdef USE_GRADIENT
      OrientationGrid* pOrientationGrid = NonSeparableFilter::DetermineLocalMagnitudeAndOrientation( pGridIn );
      ArrayGrid<double>* pMagnitudeGrid = pOrientationGrid->ExtractMagnitudeGrid();
      delete pOrientationGrid;
      mpSourceGrid = pMagnitudeGrid;
   #else
      mpSourceGrid = pGridIn;
   #endif
   bool needsInitialisation = true;
   
   mpLabelGrid = new ArrayGrid<int>( width, height, needsInitialisation, LABEL_INITIAL );
   mpDistanceGrid = new ArrayGrid<int>(width, height, needsInitialisation, 0);
   mpWatershedGrid = new ArrayGrid<bool>(width, height, needsInitialisation, false);
   mpWatershedGrid->SetGridValues( false );
   CreateSortedPixelList( );
   
   int hMin = mvSortedPixelElementVector[0].value;
   int hMax = mvSortedPixelElementVector[width*height-1].value;
   int pixelIndex = 0;

   mCurrentLabel = 1;
   mCurrentLevel = hMin - 1;
   while ( mCurrentLevel <= hMax + 1)
   {
      ResetQueue();
      std::vector< PixelElement<int> > vCurrentLevelMaskPixels;
      
      vCurrentLevelMaskPixels = MaskInitialCandidates( pixelIndex );
      
      DetermineMaskLabelsFromLabeledNeighbours( vCurrentLevelMaskPixels );
      
      while ( !( mpFifoQueue.empty() ) )
      {
         PixelElement<int> pe = mpFifoQueue.front();
         mpFifoQueue.pop();
         mCurrentDistance = GetDistance( pe.x, pe.y ) + 1;
         ProcessNeighboursOfQueueElements( pe.x, pe.y );
      }
      
      ProcessNewMinima( vCurrentLevelMaskPixels );
      mCurrentLevel += 20;
      pixelIndex += vCurrentLevelMaskPixels.size();
   }
   #ifdef USE_GRADIENT
   delete pMagnitudeGrid;
   #endif
   return mpLabelGrid->Clone();
}

//----------------------------------------------------------------
}
}

