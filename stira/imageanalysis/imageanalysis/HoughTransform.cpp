
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
#include "../../imagetools/tools/ImageIO.h"

namespace stira {
namespace imageanalysis {

using namespace std;
using namespace common;
using namespace image;

HoughTransform::HoughTransform()
{
    mpAccu = 0;
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

   if (mpAccu != 0) { delete mpAccu; }
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

int HoughTransform::BuildAccumulatorCircles( ArrayGrid<bool>* pEdgeGrid, int radius )
{
   mImageWidth  = pEdgeGrid->GetWidth();
   mImageHeight = pEdgeGrid->GetHeight();
   //Create the accu
   if (mpAccu != 0) { delete mpAccu; }
   mpAccu = new ArrayGrid<int>( mImageWidth, mImageHeight );
   mAccuWidth  = pEdgeGrid->GetWidth();
   mAccuHeight = pEdgeGrid->GetHeight();

   for (int y0 = radius; y0 < mImageHeight - radius; y0++)
   {
       for (int x0 = radius; x0 < mImageWidth - radius; x0++)
       {
           int f = 1 - radius;
           int ddF_x = 1;
           int ddF_y = -2 * radius;
           int xx = 0;
           int yy = radius;

           if (pEdgeGrid->GetValue( x0, y0 + radius) ) { mpAccu->AddOne( x0, y0); }
           if (pEdgeGrid->GetValue( x0, y0 - radius) ) { mpAccu->AddOne( x0, y0); }
           if (pEdgeGrid->GetValue( x0 + radius, y0) ) { mpAccu->AddOne( x0, y0); }
           if (pEdgeGrid->GetValue( x0 - radius, y0) ) { mpAccu->AddOne( x0, y0); }

           while(xx < yy)
           {
              // ddF_x == 2 * x + 1;
              // ddF_y == -2 * y;
              // f == x*x + y*y - radius*radius + 2*x - y + 1;
              if(f >= 0)
              {
                 yy--;
                 ddF_y += 2;
                 f += ddF_y;
              }
              xx++;
              ddF_x += 2;
              f += ddF_x;
              if (pEdgeGrid->GetValue( x0 + xx, y0 + yy) ) { mpAccu->AddOne( x0, y0); }
              if (pEdgeGrid->GetValue( x0 - xx, y0 + yy) ) { mpAccu->AddOne( x0, y0); }
              if (pEdgeGrid->GetValue( x0 + xx, y0 - yy) ) { mpAccu->AddOne( x0, y0); }
              if (pEdgeGrid->GetValue( x0 - xx, y0 - yy) ) { mpAccu->AddOne( x0, y0); }
              if (pEdgeGrid->GetValue( x0 + yy, y0 + xx) ) { mpAccu->AddOne( x0, y0); }
              if (pEdgeGrid->GetValue( x0 - yy, y0 + xx) ) { mpAccu->AddOne( x0, y0); }
              if (pEdgeGrid->GetValue( x0 + yy, y0 - xx) ) { mpAccu->AddOne( x0, y0); }
           }
       }
   }

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

std::vector< Point<int> > HoughTransform::GetCirclesRadius( image::ArrayGrid<bool>* pEdgeGrid, int radius, int threshold )
{
    BuildAccumulatorCircles( pEdgeGrid, radius );

    std::vector< Point<int> > circleCenters;

    if( mpAccu == 0)
       return circleCenters;

    for( int y0 = 0; y0 < mpAccu->GetHeight(); y0 ++ )
    {
       for( int x0 = 0; x0 < mpAccu->GetWidth(); x0++ )
       {
          if( mpAccu->GetValue(x0, y0) >= threshold )
          {
             //Is this point a local maxima (9x9)
             int max = mpAccu->GetValue( x0, y0 );
             for( int ly = -4; ly <= 4; ly++ )
             {
                for( int lx = -4; lx <= 4; lx++ )
                {
                   if( ( ly + y0 >= 0 && ly + y0 < mAccuHeight ) && ( lx + x0 >= 0 && lx + x0 < mAccuWidth ) )
                   {
                      if( mpAccu->GetValue( x0 + lx, y0 + ly ) > max )
                      {
                         max = mpAccu->GetValue( x0 + lx, y0 + ly );
                         ly = lx = 5;
                      }
                   }
                }
             }
             if(max > mpAccu->GetValue( x0, y0 ) )
                continue;

             circleCenters.push_back( Point<int>( x0,y0 ) );
          }
       }
    }

    return circleCenters;
}

//--------------------------------------------------------------------------------

}}

