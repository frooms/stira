
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

#include "StereoMatchDepth.h"
#include "../../imagetools/tools/NumberGridTools.h"
#include <string>

namespace stira {
namespace imageanalysis {

using namespace std;
using namespace imagedata;
using namespace imagetools;
using namespace common;

//----------------------------------------------------------------

StereoMatchDepth::StereoMatchDepth() { }

//----------------------------------------------------------------

ArrayGrid<double>* StereoMatchDepth::MatchStereo( ArrayGrid<double>* pGrid1,
                                                  ArrayGrid<double>* pGrid2,
                                                  int windowHalfWidth,
                                                  common::MatchCriterion myMatchCriterion,
                                                  int maxDisparity
                                                )
{
    switch(myMatchCriterion)
    {
        case common::MATCH_MI:
        {
            return MatchStereoMI( pGrid1, pGrid2, windowHalfWidth, maxDisparity );
        }
        case common::MATCH_NCC:
        {
            return MatchStereoNCC( pGrid1, pGrid2, windowHalfWidth, maxDisparity );
        }
        default:
        case common::MATCH_SSD:
        {
            return MatchStereoSSD( pGrid1, pGrid2, windowHalfWidth, maxDisparity );
        }
    }
}

//----------------------------------------------------------------

ArrayGrid<double>* StereoMatchDepth::MatchStereoSSD( ArrayGrid<double>* pGrid1,
                                                     ArrayGrid<double>* pGrid2,
                                                     int windowHalfWidth,
                                                     int maxDisparity
                                                   )
{
    int width  = pGrid1->GetWidth();
    int height = pGrid1->GetHeight();
    ArrayGrid<double>* pGridResult = new ArrayGrid<double>( width, height );

    for ( int y = windowHalfWidth; y < height - windowHalfWidth; y++ )
    {
        std::cout << "Processing line " << y << std::endl;
        for ( int x = windowHalfWidth; x < width - windowHalfWidth; x++ )
        {
            double bestLocalSSD = 1000000000000000000000.0;
            int bestX = 0;
            int xTop1 = x - windowHalfWidth;
            int yTop1 = y - windowHalfWidth;
            int xBottom1 = x + windowHalfWidth;
            int yBottom1 = y + windowHalfWidth;

            for ( int dx = 1; dx < maxDisparity; dx++ )
            {
                int xTop2, yTop2, xBottom2, yBottom2;
                double currentSSD;
                xBottom2 = x + dx + windowHalfWidth;
                if (xBottom2 < width)
                {
                    xTop2 = x + dx - windowHalfWidth;
                    yTop2 = yTop1;
                    yBottom2 = yBottom1;

                    currentSSD = NumberGridTools<double>::ComputeLocalSquaredDifference( pGrid1, xTop1, yTop1, xBottom1, yBottom1,
                                                                                         pGrid2, xTop2, yTop2, xBottom2, yBottom2 );
                    if ( currentSSD < bestLocalSSD - 5 )
                    {
                        bestLocalSSD = currentSSD;
                        bestX = x + dx;
                    }
                }
                xTop2 = x - dx - windowHalfWidth;

                if (xTop2 > 0)
                {
                    yTop2 = yTop1;
                    xBottom2 = x - dx + windowHalfWidth;
                    yBottom2 = yBottom1;

                    currentSSD = NumberGridTools<double>::ComputeLocalSquaredDifference( pGrid1, xTop1, yTop1, xBottom1, yBottom1,
                                                                                         pGrid2, xTop2, yTop2, xBottom2, yBottom2 );
                    if ( currentSSD < bestLocalSSD - 5 )
                    {
                        bestLocalSSD = currentSSD;
                        bestX = x + dx;
                    }
                }
            }

            double disparity = abs(x-bestX);
            if (disparity < maxDisparity)
            {
                pGridResult->SetValue( x, y, disparity);
            }
            else
            {
                pGridResult->SetValue( x, y, 0 );
            }
        }
    }
    return pGridResult;
}

//----------------------------------------------------------------

ArrayGrid<double>* StereoMatchDepth::MatchStereoNCC( ArrayGrid<double>* pGrid1,
                                                     ArrayGrid<double>* pGrid2,
                                                     int windowHalfWidth,
                                                     int maxDisparity
                                                   )
{
    int width  = pGrid1->GetWidth();
    int height = pGrid1->GetHeight();
    ArrayGrid<double>* pGridResult = new ArrayGrid<double>( width, height );

    for ( int y = windowHalfWidth; y < height - windowHalfWidth; y++ )
    {
        std::cout << "Processing line " << y << std::endl;
        for ( int x = windowHalfWidth; x < width - windowHalfWidth; x++ )
        {
            double bestLocalNCC = 0;
            int bestX = 0;
            int xTop1 = x - windowHalfWidth;
            int yTop1 = y - windowHalfWidth;
            int xBottom1 = x + windowHalfWidth;
            int yBottom1 = y + windowHalfWidth;

            for ( int dx = 1; dx < maxDisparity; dx++ )
            {
                int xTop2, yTop2, xBottom2, yBottom2;
                double currentNCC;
                xBottom2 = x + dx + windowHalfWidth;
                if (xBottom2 < width)
                {
                    xTop2 = x + dx - windowHalfWidth;
                    yTop2 = yTop1;
                    yBottom2 = yBottom1;

                    currentNCC = NumberGridTools<double>::ComputeLocalCrossCorrelation( pGrid1, xTop1, yTop1, xBottom1, yBottom1,
                                                                                        pGrid2, xTop2, yTop2, xBottom2, yBottom2 );
                    if ( currentNCC > bestLocalNCC + 0.05 )
                    {
                        bestLocalNCC = currentNCC;
                        bestX = x + dx;
                    }
                }
                xTop2 = x - dx - windowHalfWidth;

                if (xTop2 > 0)
                {
                    yTop2 = yTop1;
                    xBottom2 = x - dx + windowHalfWidth;
                    yBottom2 = yBottom1;

                    currentNCC = NumberGridTools<double>::ComputeLocalCrossCorrelation( pGrid1, xTop1, yTop1, xBottom1, yBottom1,
                                                                                        pGrid2, xTop2, yTop2, xBottom2, yBottom2 );

                    if ( currentNCC > bestLocalNCC + 0.05 )
                    {
                        bestLocalNCC = currentNCC;
                        bestX = x + dx;
                    }
                }
            }

            double disparity = abs(x-bestX);
            if (disparity < maxDisparity)
            {
                pGridResult->SetValue( x, y, disparity);
            }
            else
            {
                pGridResult->SetValue( x, y, 0 );
            }
        }
    }
    return pGridResult;
}

//----------------------------------------------------------------

ArrayGrid<double>* StereoMatchDepth::MatchStereoMI( ArrayGrid<double>* pGrid1,
                                                    ArrayGrid<double>* pGrid2,
                                                    int windowHalfWidth,
                                                    int maxDisparity
                                                  )
{
    int width  = pGrid1->GetWidth();
    int height = pGrid1->GetHeight();
    ArrayGrid<double>* pGridResult = new ArrayGrid<double>( width, height );

    for ( int y = windowHalfWidth; y < height - windowHalfWidth; y++ )
    {
        std::cout << "Processing line " << y << std::endl;
        for ( int x = windowHalfWidth; x < width - windowHalfWidth; x++ )
        {
            double bestLocalMI = 0;
            int bestX = 0;
            int xTop1 = x - windowHalfWidth;
            int yTop1 = y - windowHalfWidth;
            int xBottom1 = x + windowHalfWidth;
            int yBottom1 = y + windowHalfWidth;

            for ( int dx = 1; dx < maxDisparity; dx++ )
            {
                int xTop2, yTop2, xBottom2, yBottom2;
                double currentMI;
                xBottom2 = x + dx + windowHalfWidth;
                if (xBottom2 < width)
                {
                    xTop2 = x + dx - windowHalfWidth;
                    yTop2 = yTop1;
                    yBottom2 = yBottom1;

                    currentMI = NumberGridTools<double>::ComputeLocalMutualInformation( pGrid1, xTop1, yTop1, xBottom1, yBottom1,
                                                                                         pGrid2, xTop2, yTop2, xBottom2, yBottom2 );
                    if ( currentMI > bestLocalMI + 100 )
                    {
                        bestLocalMI = currentMI;
                        bestX = x + dx;
                    }
                }
                xTop2 = x - dx - windowHalfWidth;

                if (xTop2 > 0)
                {
                    yTop2 = yTop1;
                    xBottom2 = x - dx + windowHalfWidth;
                    yBottom2 = yBottom1;

                    currentMI = NumberGridTools<double>::ComputeLocalMutualInformation( pGrid1, xTop1, yTop1, xBottom1, yBottom1,
                                                                                        pGrid2, xTop2, yTop2, xBottom2, yBottom2 );
                    if ( currentMI > bestLocalMI + 100 )
                    {
                        bestLocalMI = currentMI;
                        bestX = x + dx;
                    }
                }
            }

            double disparity = abs(x-bestX);
            if (disparity < maxDisparity)
            {
                pGridResult->SetValue( x, y, disparity);
            }
            else
            {
                pGridResult->SetValue( x, y, 0 );
            }
        }
    }
    return pGridResult;
}

}
}

