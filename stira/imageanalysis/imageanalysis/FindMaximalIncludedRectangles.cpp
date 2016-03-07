#include "FindMaximalIncludedRectangles.h"

namespace stira {
namespace imageanalysis {

using namespace stira::common;
using namespace stira::image;

FindMaximalIncludedRectangles::FindMaximalIncludedRectangles()
{
}

//----------------------------------------------------------------------------------------------------

std::vector< RectangularROI<int> > FindMaximalIncludedRectangles::Run( ArrayGrid<bool>* pObjectGrid )
{
   std::vector< RectangularROI<int> > foundIncludedRectangles;
   int gridWidth = pObjectGrid->GetWidth();
   int gridHeight = pObjectGrid->GetHeight();

   int distanceToImageTopArray [ gridWidth ] [ gridHeight ];
   int distanceToImageBottomArray [ gridWidth ][ gridHeight ];

   for ( int x = 0 ; x < gridWidth ; ++ x )
   {
      distanceToImageTopArray [ x ][ 0 ] = pObjectGrid->GetValue( x, 0 ) ? 0 : -1;
   }
   for ( int y = 1 ; y < gridHeight ; ++ y )
   {
      for ( int x = 0 ; x < gridWidth ; ++ x )
      {
         if ( !pObjectGrid->GetValue( x, y ) )
         {
            distanceToImageTopArray[ x ][ y ] = -1;
         }
         else distanceToImageTopArray [ x ][ y ] = distanceToImageTopArray [ x ] [ y - 1 ] + 1;
      }
   }

   for ( int x = 0 ; x < gridWidth ; ++ x )
   {
      distanceToImageBottomArray [ x ][ gridHeight - 1 ] = pObjectGrid->GetValue( x, gridHeight - 1 ) ? 0 : -1;
   }

   for ( int y = gridHeight - 2 ; y >= 0 ; -- y )
   {
      for ( int x = 0 ; x < gridWidth ; ++ x )
      {
         if ( ! pObjectGrid->GetValue( x, y ) )
         {
            distanceToImageBottomArray [ x ][ y ] = -1;
         }
         else
         {
            distanceToImageBottomArray [ x ][ y ] = distanceToImageBottomArray [ x ][ y + 1 ] + 1;
         }
      }
   }

   for ( int x = gridWidth - 1 ; x >= 0 ; --x )
   {
      int maxDistanceToImageBottom = gridHeight ;
      for ( int y = gridHeight - 1 ; y >= 0 ; --y )
      {
         ++ maxDistanceToImageBottom ;
         if ( pObjectGrid->GetValue( x, y ) && ( x == 0 || ! pObjectGrid->GetValue( x - 1,  y ) ) )
         {
            int currentDistanceToImageTop = distanceToImageTopArray [ x ][ y ];
            int currentDistanceToImageBottom = distanceToImageBottomArray [ x ][ y ];
            int rectangleWidth = 1 ;
            while ( ( x + rectangleWidth < gridWidth ) && ( pObjectGrid->GetValue( x + rectangleWidth, y ) ) )
            {
               int nextDistanceToImageTop = distanceToImageTopArray [ x + rectangleWidth ][ y ];
               int nextDistanceToImageBottom = distanceToImageBottomArray [ x + rectangleWidth ][ y ];
               if ( ( nextDistanceToImageTop < currentDistanceToImageTop ) || ( nextDistanceToImageBottom < currentDistanceToImageBottom ) )
               {
                  if ( currentDistanceToImageBottom < maxDistanceToImageBottom ) foundIncludedRectangles.push_back( RectangularROI<int>( x , y - currentDistanceToImageTop , x+rectangleWidth , y+ currentDistanceToImageBottom + 1 ) );
                  if ( nextDistanceToImageTop < currentDistanceToImageTop ) currentDistanceToImageTop = nextDistanceToImageTop;
                  if ( nextDistanceToImageBottom < currentDistanceToImageBottom ) currentDistanceToImageBottom = nextDistanceToImageBottom;
               }
               ++ rectangleWidth ;
            }
            if ( currentDistanceToImageBottom < maxDistanceToImageBottom ) foundIncludedRectangles.push_back( RectangularROI<int>( x , y - currentDistanceToImageTop , x + rectangleWidth , y + currentDistanceToImageBottom + 1 ) );
            maxDistanceToImageBottom = 0 ;
         }
      }
   }
   return foundIncludedRectangles;
}

//----------------------------------------------------------------------------------------------------

histogram::IntHistogram FindMaximalIncludedRectangles::CreateRectangleHistogram( std::vector< common::RectangularROI<int> > vRectangle, rectangleMeasure myMeasureType, bool isCumulative )
{
   int nrRectangles = vRectangle.size();

   int maxMeasure = 0;

   switch (myMeasureType)
   {
      case MEASURE_WIDTH:
      {
         for (int i = 0; i < nrRectangles; i++)
         {
            double myMeasureValue = vRectangle[i].GetWidth();
            if (myMeasureValue > maxMeasure) {maxMeasure = myMeasureValue;}
         }
         break;
      }
      case MEASURE_HEIGHT:
      {
         for (int i = 0; i < nrRectangles; i++)
         {
            double myMeasureValue = vRectangle[i].GetHeight();
            if (myMeasureValue > maxMeasure) {maxMeasure = myMeasureValue;}
         }
         break;
      }
      case MEASURE_DIAGONALLENGTH:
      {
         for (int i = 0; i < nrRectangles; i++)
         {
            double myMeasureValue = vRectangle[i].GetDiagonalLength();
            if (myMeasureValue > maxMeasure) {maxMeasure = myMeasureValue;}
         }
         break;

      }
      case MEASURE_AREA:
      default:
      {
         for (int i = 0; i < nrRectangles; i++)
         {
            double myMeasureValue = vRectangle[i].GetArea();
            if (myMeasureValue > maxMeasure) {maxMeasure = myMeasureValue;}
         }
         break;
      }
   }

   double binSize = 20.0;
   int nrOfBands = 1;
   int minValue = 0;
   int maxValue = (int)( maxMeasure + 1.5 );
   histogram::IntHistogram ih( binSize, nrOfBands, minValue, maxValue );

   switch (myMeasureType)
   {
      case MEASURE_WIDTH:
      {
         for (int i = 0; i < nrRectangles; i++)
         {
            ih.AddDataPoint( (int)( vRectangle[i].GetWidth() + 0.5 ) );
         }
         break;
      }
      case MEASURE_HEIGHT:
      {
         for (int i = 0; i < nrRectangles; i++)
         {
            ih.AddDataPoint( (int)( vRectangle[i].GetHeight() + 0.5 ) );
         }
         break;
      }
      case MEASURE_DIAGONALLENGTH:
      {
         for (int i = 0; i < nrRectangles; i++)
         {
            ih.AddDataPoint( (int)( vRectangle[i].GetDiagonalLength() + 0.5 ) );
         }
         break;

      }
      case MEASURE_AREA:
      default:
      {
         for (int i = 0; i < nrRectangles; i++)
         {
            ih.AddDataPoint( (int)(vRectangle[i].GetArea() + 0.5 ) );
         }
         break;
      }
   }


   if (isCumulative)
   {
      ih.ConvertInCumulativeHistogram();
   }
   return ih;
}

}
}
