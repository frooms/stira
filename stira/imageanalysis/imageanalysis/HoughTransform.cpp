
/***********************************************************************************
 *   Copyright (C) 2016 by Filip Rooms                                             *
 *                                                                                 *
 *  Terms and conditions for using this software in any form are provided in the   *
 *  file COPYING, which can be found in the root directory of this project.        *
 *                                                                                 *
 *   Contact data: filip.rooms@gmail.com                                           *
 *                 http://www.filiprooms.be/                                       *
 *                                                                                 *
 ***********************************************************************************/

#include "HoughTransform.h"

#include <iostream>
#include <vector>
#include "../../common/common/MathUtils.h"
#include "../../image/tools/ImageIO.h"

namespace stira {
namespace imageanalysis {

using namespace std;
using namespace common;
using namespace image;

HoughTransform::HoughTransform()
{
}

//--------------------------------------------------------------------------------

HoughTransform::~HoughTransform()
{
    delete mpAccu;
}

//--------------------------------------------------------------------------------

int HoughTransform::BuildAccumulatorLines( ArrayGrid<bool>* pEdgeGrid )
{
   mImageWidth  = pEdgeGrid->GetWidth();
   mImageHeight = pEdgeGrid->GetHeight();
   //Create the accu
   double hough_h = ((sqrt(2.0) * (double)( mImageHeight > mImageWidth ? mImageHeight : mImageWidth ) ) / 2.0);
   mAccuHeight = hough_h * 2.0; // -r -> +r
   mAccuWidth  = 180;

   mpAccu = new ArrayGrid<int>( mAccuWidth, mAccuHeight );

   double center_x = mImageWidth  / 2.0;
   double center_y = mImageHeight / 2.0;

   for( int y = 0; y < mImageHeight; y++ )
   {
      for( int x = 0; x < mImageWidth; x++ )
      {
         if( pEdgeGrid->GetValue( x, y) )
         {
            for( int t = 0; t < 180; t++ )
            {
               double r =   ((double)x - center_x) * cos( MathUtils::ToRadians( (double)t ) )
                          + ((double)y - center_y) * sin( MathUtils::ToRadians( (double)t ) );
               mpAccu->AddOne( t, round(r + hough_h) );
            }
         }
      }
   }
   return 0;
}

//--------------------------------------------------------------------------------

int HoughTransform::BuildAccumulatorCircles( OrientationGrid* pOrientGrid )
{
   mImageWidth  = pOrientGrid->GetWidth();
   mImageHeight = pOrientGrid->GetHeight();
   //Create the accu
   /*double hough_h = ((sqrt(2.0) * (double)( mImageHeight > mImageWidth ? mImageHeight : mImageWidth ) ) / 2.0);
   mAccuHeight = hough_h * 2.0; // -r -> +r
   mAccuWidth  = 180;

   mpAccu = new ArrayGrid<int>( mAccuWidth, mAccuHeight );

   double center_x = mImageWidth  / 2.0;
   double center_y = mImageHeight / 2.0;

   for( int y = 0; y < mImageHeight; y++ )
   {
      for( int x = 0; x < mImageWidth; x++ )
      {
         if( pEdgeGrid->GetValue( x, y) )
         {
            for( int t = 0; t < 180; t++ )
            {
               double r =   ((double)x - center_x) * cos( MathUtils::ToRadians( (double)t ) )
                          + ((double)y - center_y) * sin( MathUtils::ToRadians( (double)t ) );
               mpAccu->AddOne( t, round(r + hough_h) );
            }
         }
      }
   }*/
   return 0;
}

//--------------------------------------------------------------------------------

void HoughTransform::VisualizeAcculumulator( std::string fileName )
{
    ImageIO::WritePGM(mpAccu, fileName, ImageIO::NORMAL_OUT);
}

//--------------------------------------------------------------------------------

std::vector< common::LineSegment<int> > HoughTransform::GetLines(  ArrayGrid<bool>* pEdgeGrid, int threshold)
{
   BuildAccumulatorLines( pEdgeGrid );
   std::vector< LineSegment<int> > lines;

   if( mpAccu == 0)
      return lines;

   for( int r = 0; r < mAccuHeight; r++ )
   {
      for( int t = 0; t < mAccuWidth; t++ )
      {
         if( mpAccu->GetValue(t, r) >= threshold )
         {
            //Is this point a local maxima (9x9)
            int max = mpAccu->GetValue( t, r );
            for( int ly = -4; ly <= 4; ly++ )
            {
               for( int lx = -4; lx <= 4; lx++ )
               {
                  if( ( ly + r >= 0 && ly + r < mAccuHeight ) && ( lx + t >= 0 && lx + t < mAccuWidth ) )
                  {
                     if( mpAccu->GetValue( t + lx, r + ly ) > max )
                     {
                        max = mpAccu->GetValue( t + lx, r + ly );
                        ly = lx = 5;
                     }
                  }
               }
            }
            if(max > mpAccu->GetValue( t, r ) )
               continue;

            double tRad =  MathUtils::ToRadians( (double)t );
            int x1, y1, x2, y2;
            x1 = y1 = x2 = y2 = 0;

            if( t >= 45 && t <= 135 )
            {
               //y = (r - x cos(t)) / sin(t)
               x1 = 0;
               y1 = ((double)( r - ( mAccuHeight / 2 ) ) - ( ( x1 - ( mImageWidth / 2 ) ) * cos( tRad ) ) ) / sin( tRad ) + ( mImageHeight / 2);
               x2 = mImageWidth - 0;
               y2 = ((double)(r-(mAccuHeight/2)) - ((x2 - (mImageWidth/2) ) * cos( tRad ))) / sin( tRad ) + (mImageHeight / 2);
            }
            else
            {
               //x = (r - y sin(t)) / cos(t);
               y1 = 0;
               x1 = ((double)(r-(mAccuHeight/2)) - ((y1 - (mImageHeight/2) ) * sin( tRad ))) / cos( tRad ) + (mImageWidth / 2);
               y2 = mImageHeight - 0;
               x2 = ((double)(r-(mAccuHeight/2)) - ((y2 - (mImageHeight/2) ) * sin( tRad ))) / cos( tRad ) + (mImageWidth / 2);
            }

            lines.push_back( LineSegment<int>( Point<int>( x1,y1 ), Point<int>(x2,y2)));
         }
      }
   }

   std::cout << "lines: " << lines.size() << " " << threshold << std::endl;
   return lines;
}

//--------------------------------------------------------------------------------

std::vector< std::pair< common::Point<int>, double > > HoughTransform::GetCirclesRadius( image::OrientationGrid* pOrientGrid, int radius, int threshold )
{
    BuildAccumulatorCircles( pOrientGrid );
    std::vector< std::pair< common::Point<int>, double > > circles;
    return circles;
}

//--------------------------------------------------------------------------------

}}

