
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

#include <iostream>
#include "CannyEdgeDetector.h"
#include "../../common/common/MathUtils.h"
#include "../../imagetools/tools/ImageIO.h"
#include "../../histogram/histogram/IntHistogram.h"
#include "../../filter/filter/NonSeparableFilter.h"
#include "../../fouriertools/fouriertools/FFT.h"

//#define VERBOSE_OUT

namespace stira {
namespace imageanalysis {

using namespace std;
using namespace common;
using namespace imagedata;
using namespace imagetools;
using namespace histogram;
using namespace filter;
using namespace fouriertools;

CannyEdgeDetector::CannyEdgeDetector()
{
}

//----------------------------------------------------------------

CannyEdgeDetector::~CannyEdgeDetector()
{
}

//----------------------------------------------------------------

bool CannyEdgeDetector::IsCandidateLocalMaximum( int x, int y, int quantized, OrientationGrid* pOrientationGrid )
{
   switch (quantized)
   {
      // horizontal edge " -- "
      case 0:
      {
         if (    ( pOrientationGrid->GetMagnitude(x, y) >=  ( pOrientationGrid->GetMagnitude(x, y+1) ) )
              && ( pOrientationGrid->GetMagnitude(x, y) >=  ( pOrientationGrid->GetMagnitude(x, y-1) ) )
            )
         {
            return true;
         }
         else
         {
            return false;
         }
      }
      // edge " / "
      case 1:
      {
         if (    ( pOrientationGrid->GetMagnitude(x, y) >=  ( pOrientationGrid->GetMagnitude(x-1, y+1) ) )
              && ( pOrientationGrid->GetMagnitude(x, y) >=  ( pOrientationGrid->GetMagnitude(x+1, y-1) ) )
            )
         {
            return true;
         }
         else
         {
            return false;
         }
      }
      // vertical edge " | "
      case 2:
      {
         if (    ( pOrientationGrid->GetMagnitude(x, y) >=  ( pOrientationGrid->GetMagnitude(x-1, y) ) )
              && ( pOrientationGrid->GetMagnitude(x, y) >=  ( pOrientationGrid->GetMagnitude(x+1, y) ) )
            )
         {
            return true;
         }
         else
         {
            return false;
         }
      }
      // edge " \ "
      case 3:
      {
         if (    ( pOrientationGrid->GetMagnitude(x, y) >=  ( pOrientationGrid->GetMagnitude(x+1, y+1) ) )
              && ( pOrientationGrid->GetMagnitude(x, y) >=  ( pOrientationGrid->GetMagnitude(x-1, y-1) ) )
            )
         {
            return true;
         }
         else
         {
            return false;
         }
      }
      default:
      {
         return false;
      }
   }
}

//----------------------------------------------------------------

ArrayGrid<bool>* CannyEdgeDetector::CreateNonMaximaSuppressedMap( OrientationGrid* pOrientationGrid )
{
   int width  = pOrientationGrid->GetWidth();
   int height = pOrientationGrid->GetHeight();

   ArrayGrid<bool>* pCandidateEdgeMap = new ArrayGrid<bool>(width, height);  // NOT initialized at construction; values are set below

   for (int y = 1; y < height-1; y++)
   {
      for (int x = 1; x < width-1; x++)
      {
         int quantizedAngle = (int)( ( pOrientationGrid->GetAngle(x, y)) / (M_PI / 4) );
         if (quantizedAngle > 3) {quantizedAngle = 0;}
         pCandidateEdgeMap->SetValue(x, y, IsCandidateLocalMaximum( x, y, quantizedAngle, pOrientationGrid ) );
      }
   }

   // deal with special cases at image borders
   for (int y = 0; y < height; y++)
   {
      pCandidateEdgeMap->SetValue(0, y, false );
      pCandidateEdgeMap->SetValue(1, y, false );
   }
   for (int y = 0; y < height; y++)
   {
      pCandidateEdgeMap->SetValue(width-1, y, false );
      pCandidateEdgeMap->SetValue(width-2, y, false );
   }
   for (int x = 0; x < width; x++)
   {
      pCandidateEdgeMap->SetValue(x, 0, false );
      pCandidateEdgeMap->SetValue(x, 1, false );
   }
   for (int x = 0; x < width; x++)
   {
      pCandidateEdgeMap->SetValue(x, height-1, false );
      pCandidateEdgeMap->SetValue(x, height-2, false );
   }
   ImageIO::WritePGM( pCandidateEdgeMap, std::string("MaximaMap.pgm") );
   return pCandidateEdgeMap;
}

//----------------------------------------------------------------

ArrayGrid<edgeLabel>* CannyEdgeDetector::CreateCandidateLabelGrid( OrientationGrid* pOrientationGrid, ArrayGrid<bool>* pCandidateGrid, double loThreshold)
{
   int width  = pCandidateGrid->GetWidth();
   int height = pCandidateGrid->GetHeight();

   int nrCandidates = 0;
   bool isInitialized = true;
   ArrayGrid<edgeLabel>* pLabelGrid = new ArrayGrid<edgeLabel>( width, height, isInitialized, IS_CANDIDATE_EDGE );

   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         if ( (pCandidateGrid->GetValue( x, y ) == true) && (pOrientationGrid->GetMagnitude( x, y ) > loThreshold) )
         {
            #ifdef VERBOSE_OUT
            cout << "CreateCandidateLabelGrid: candidate edge initialized at (" << x << ", " << y << ")" << endl << flush;
            #endif
            pLabelGrid->SetValue( x, y, IS_CANDIDATE_EDGE );
            nrCandidates++;
         }
         else
         {
            pLabelGrid->SetValue( x, y, IS_NO_EDGE );
         }
      }
   }
   #ifdef VERBOSE_OUT
   cout << "At end, number of edge candidates is " << nrCandidates << endl << flush;
   #endif
   return pLabelGrid;
}

//----------------------------------------------------------------

bool HasEdgeNeighbor(ArrayGrid<edgeLabel>* pLabelGrid, Point<int> lastSeed, OrientationGrid* pOrientationGrid, double loThreshold)
{
   Point<int> pos(-1, -1);
   for (int dy = -1; dy <= 1; dy++)
   {
      for (int dx = -1; dx <= 1; dx++)
      {
         if ( !( (dx == 0) && (dy == 0) ) )
         {
            int checkX = lastSeed.x + dx;
            int checkY = lastSeed.y + dy;
            if (  (checkX >= 0) && (checkX < pOrientationGrid->GetWidth()) && (checkY >= 0) && (checkY < pOrientationGrid->GetHeight()) )
            {
               if ( (pLabelGrid->GetValue(checkX, checkY) == IS_EDGE) && (pOrientationGrid->GetMagnitude(checkX, checkY) > loThreshold))
               {
                  #ifdef VERBOSE_OUT
                  cout << "Has edge neighbor at (" << checkX << ", " << checkY << ")" << endl << flush;
                  #endif
                  pLabelGrid->SetValue( checkX, checkY, IS_EDGE );
                  return true;
               }
            }
         }
      }
   }
   #ifdef VERBOSE_OUT
   cout << "Has no edge neighbor" << endl << flush;
   #endif
   return false;
}

//----------------------------------------------------------------

Point<int> CannyEdgeDetector::GetStartSeed( OrientationGrid* pOrientationGrid, ArrayGrid<edgeLabel>* pLabelGrid, Point<int> lastSeed, double hiThreshold, double lowThreshold)
{
   int width  = pOrientationGrid->GetWidth();
   int height = pOrientationGrid->GetHeight();
   Point<int> pos(-1, -1);


   int y = lastSeed.y;
   for (int x = lastSeed.x; x < width; x++)
   {
      #ifdef VERBOSE_OUT
      cout << "Checking candidate new seed (" << x << ", " << y << ")" << flush;
      #endif
      if (pLabelGrid->GetValue( x, y ) == IS_CANDIDATE_EDGE )
      {
         #ifdef VERBOSE_OUT
         cout << "\t is candidate edge: check if " << pOrientationGrid->GetMagnitude( x, y ) << " > " << hiThreshold << endl << flush;
         #endif
         if (pOrientationGrid->GetMagnitude( x, y ) > hiThreshold)
         {
            pos.SetXAndY( x, y );
            pLabelGrid->SetValue( x, y, IS_EDGE );
            #ifdef VERBOSE_OUT
            cout << "Start seed generated: " << pos << flush;
            #endif
            return pos;
         }
         #ifdef VERBOSE_OUT
         cout << "\t failed; check if " << pOrientationGrid->GetMagnitude( x, y ) << " > " << lowThreshold << " and has edge neighbor" << endl << flush;
         #endif
         Point<int> thisSeed(x, y);
         if ( (HasEdgeNeighbor( pLabelGrid, thisSeed, pOrientationGrid, lowThreshold) ) && (pOrientationGrid->GetMagnitude( x, y ) > lowThreshold) )
         {
            pos.SetXAndY( x, y );
            pLabelGrid->SetValue( x, y, IS_EDGE );
            #ifdef VERBOSE_OUT
            cout << "Start seed generated: " << pos << flush;
            #endif
            return pos;
         }
      }
      else
      {
         #ifdef VERBOSE_OUT
         cout << "\t is no edge candidate " << endl << flush;
         #endif
      }
   }

   for (int y = lastSeed.y+1; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         #ifdef VERBOSE_OUT
         cout << "Checking candidate new seed (" << x << ", " << y << ")" << flush;
         #endif
         if (pLabelGrid->GetValue( x, y ) == IS_CANDIDATE_EDGE )
         {
            #ifdef VERBOSE_OUT
            cout << "\t is candidate edge: check if " << pOrientationGrid->GetMagnitude( x, y ) << " > " << hiThreshold << endl << flush;
            #endif
            if (pOrientationGrid->GetMagnitude( x, y ) > hiThreshold)
            {
               pos.SetXAndY( x, y );
               pLabelGrid->SetValue( x, y, IS_EDGE );
               #ifdef VERBOSE_OUT
               cout << "Start seed generated: " << pos << flush;
               #endif
               return pos;
            }
            #ifdef VERBOSE_OUT
            cout << "\t failed; check if > hiThreshold and has edge neighbor" << endl << flush;
            #endif
            Point<int> thisSeed(x, y);
            if ( (HasEdgeNeighbor( pLabelGrid, thisSeed, pOrientationGrid, lowThreshold) ) && (pOrientationGrid->GetMagnitude( x, y ) > lowThreshold) )
            {
               pos.SetXAndY( x, y );
               #ifdef VERBOSE_OUT
               cout << "Start seed generated: " << pos << flush;
               #endif
               return pos;
            }
         }
         else
         {
            #ifdef VERBOSE_OUT
            cout << "\t is no edge candidate " << endl << flush;
            #endif
         }
      }
   }
   #ifdef VERBOSE_OUT
   cout << "No more valid seeds left " << flush;
   #endif
   // none found; return (-1, -1)
   return pos;
}

//----------------------------------------------------------------

Point<int> CannyEdgeDetector::GetNextNeighbor( OrientationGrid* pOrientationGrid, ArrayGrid<edgeLabel>* pLabelGrid, Point<int> lastNeighbor, double loThreshold)
{
   Point<int> pos(-1, -1);
   for (int dy = -1; dy <= 1; dy++)
   {
      for (int dx = -1; dx <= 1; dx++)
      {
         if ( !( (dx == 0) && (dy == 0) ) )
         {
            int checkX = lastNeighbor.x + dx;
            int checkY = lastNeighbor.y + dy;
            if (  (checkX >= 0) && (checkX < pOrientationGrid->GetWidth()) && (checkY >= 0) && (checkY < pOrientationGrid->GetHeight()) )
            {
               if (pLabelGrid->GetValue(checkX, checkY) == IS_CANDIDATE_EDGE)
               {
                  if (pOrientationGrid->GetMagnitude(checkX, checkY) > loThreshold)
                  {
                     pLabelGrid->SetValue(checkX, checkY, IS_EDGE);
                     pos.SetXAndY( checkX, checkY );
                     #ifdef VERBOSE_OUT
                     cout << "Found valid next neighbor: " << pos << flush;
                     #endif
                     return pos;
                  }
                  /*else
                  {
                     pLabelGrid->SetValue(checkX, checkY, IS_NO_EDGE);
                  }*/
               }
            }
         }
      }
   }
   // none found; return (-1, -1)
   #ifdef VERBOSE_OUT
   cout << "No valid neighbors: " << flush;
   #endif
   return pos;
}

//----------------------------------------------------------------

ArrayGrid<bool>* CannyEdgeDetector::CreateOutPut( ArrayGrid<edgeLabel>* pLabelGrid, bool alsoTakeCandidates )
{
   int width  = pLabelGrid->GetWidth();
   int height = pLabelGrid->GetHeight();
   ArrayGrid<bool>* pGrid = new ArrayGrid<bool>(width, height);  // NOT initialized at construction; values are set below
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         if (pLabelGrid->GetValue( x, y ) == IS_EDGE )
         {
            pGrid->SetValue( x, y, true );

         }
         else
         {
            if ((alsoTakeCandidates) && (pLabelGrid->GetValue( x, y ) == IS_CANDIDATE_EDGE ))
            {
               pGrid->SetValue( x, y, true );
            }
            else
            {
               pGrid->SetValue( x, y, false );
            }
         }
      }
   }
   return pGrid;
}

//----------------------------------------------------------------

ArrayGrid<bool>* CannyEdgeDetector::ApplyHysteresis( OrientationGrid* pOrientationGrid,
                                         ArrayGrid<bool>* pCandidateGrid, double lowThreshold, double highThreshold )
{
   ArrayGrid<double>* pMagnitudeMap = pOrientationGrid->ExtractMagnitudeGrid();

   ArrayGrid<edgeLabel>* pLabelGrid = CreateCandidateLabelGrid( pOrientationGrid, pCandidateGrid, lowThreshold);
   ArrayGrid<bool>* pResult0 = CreateOutPut( pLabelGrid, true );
   delete pResult0;
   delete pMagnitudeMap;

   cout << " loThreshold = " << lowThreshold << " and hiThreshold = " << highThreshold << endl << flush;

   // 1) search next IS_CANDIDATE_EDGE
   //      if > hiThreshold -> becomes IS_EDGE
   //      else if neighbor IS_EDGE and > loThreshold, neighbor becomes IS_EDGE
   // 2) check neighbors with IS_CANDIDATE_EDGE
   //       if > loThreshold, neighbor becomes IS_EDGE
   //       repeat 2) until no further tracking is possible

   Point<int> lastSeed(1, 1);
   Point<int> startSeed = GetStartSeed( pOrientationGrid, pLabelGrid, lastSeed, highThreshold, lowThreshold);
   int seedX = startSeed.x;
   int seedY = startSeed.y;

   while( (seedX != -1) && (seedY != -1) )
   {
      Point<int> nextSeed( seedX, seedY );
      Point<int> nextNeighbor = GetNextNeighbor( pOrientationGrid, pLabelGrid, nextSeed, lowThreshold);
      while ( (nextNeighbor.x != -1) && (nextNeighbor.y != -1) )
      {
         nextNeighbor = GetNextNeighbor( pOrientationGrid, pLabelGrid, nextSeed, lowThreshold);
      }

      lastSeed.SetXAndY( seedX, seedY );

      nextSeed = GetStartSeed( pOrientationGrid, pLabelGrid, lastSeed, highThreshold, lowThreshold);
      seedX = nextSeed.x;
      seedY = nextSeed.y;
   }
   ArrayGrid<bool>* pResult = CreateOutPut( pLabelGrid );
   delete pLabelGrid;
   return pResult;
}

//----------------------------------------------------------------

void CannyEdgeDetector::QuantifyOrientations( OrientationGrid* pOrientationGrid )
{
   double angle0225 = common::MathUtils::ToRadians(  22.5 );
   double angle0675 = common::MathUtils::ToRadians(  67.5 );
   double angle1125 = common::MathUtils::ToRadians( 112.5 );
   double angle1575 = common::MathUtils::ToRadians( 157.5 );

   double angle0450 = 0.25 * M_PI;
   double angle0900 = 0.50 * M_PI;
   double angle1350 = 0.75 * M_PI;

   for (int y = 0; y < pOrientationGrid->GetHeight(); y++)
   {
      for (int x = 0; x < pOrientationGrid->GetWidth(); x++)
      {
         double thisAngle = pOrientationGrid->GetAngle( x, y );

         if ( ( (thisAngle < angle0225 ) && ( thisAngle > -angle0225 ) ) ||   ( thisAngle >  angle1575 ) || ( thisAngle < -angle1575 ) )
            pOrientationGrid->SetAngle( x, y, 0.0 );
         if ( ( (thisAngle > angle0225 ) && ( thisAngle <  angle0675 ) ) || ( ( thisAngle < -angle1125 ) && ( thisAngle > -angle1575) ) )
            pOrientationGrid->SetAngle( x, y, angle0450 );
         if ( ( (thisAngle > angle0675 ) && ( thisAngle <  angle1125 ) ) || ( ( thisAngle < -angle0675 ) && ( thisAngle > -angle1125) ) )
            pOrientationGrid->SetAngle( x, y, angle0900 );
         if ( ( (thisAngle > angle1125 ) && ( thisAngle <  angle1575 ) ) || ( ( thisAngle < -angle0225 ) && ( thisAngle > -angle0675) ) )
            pOrientationGrid->SetAngle( x, y, angle1350 );

      }
   }
}



//----------------------------------------------------------------

ArrayGrid<bool>* CannyEdgeDetector::Run(ArrayGrid<double>* pGridIn, double sigmaSmooth, double lowerThreshold, double upperThreshold)
{
   ArrayGrid<double>* pSmoothGrid = 0;
   if (sigmaSmooth > 0.0)
   {
      pSmoothGrid = FFT::GaussConvolve( pGridIn, sigmaSmooth );
   }
   else
   {
      pSmoothGrid = pGridIn->Clone();
   }
   OrientationGrid* pOrientationGrid = NonSeparableFilter::DetermineLocalMagnitudeAndOrientation( pSmoothGrid );
   delete pSmoothGrid;
   QuantifyOrientations( pOrientationGrid );

#ifdef VERBOSE_OUT
   pOrientationGrid->ExportMagnitudeImage( std::string("CannyMagnitude.ppm" ) );
   pOrientationGrid->ExportOrientationImage( std::string("CannyOrientation.ppm" ) );
#endif
   ArrayGrid<bool>* pCandidateGrid = CreateNonMaximaSuppressedMap( pOrientationGrid );

#ifdef VERBOSE_OUT
   ImageIO::WritePGM( pCandidateGrid, std::string("CannyNonMaximaSuppressed.ppm") );
#endif

   ArrayGrid<bool>* pResult = ApplyHysteresis( pOrientationGrid, pCandidateGrid,
                                               lowerThreshold, upperThreshold );
#ifdef VERBOSE_OUT
   ImageIO::WritePGM( pResult, std::string("CannyAfterHysteresis.ppm" ) );
#endif

   delete pCandidateGrid;
   delete pOrientationGrid;
   return pResult;
}

//----------------------------------------------------------------

}
}
