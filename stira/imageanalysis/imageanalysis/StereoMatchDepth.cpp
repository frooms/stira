
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
#include "../../image/tools/NumberGridTools.h"
#include <string>

namespace stira {
namespace imageanalysis {

using namespace std;
using namespace image;
using namespace common;

//----------------------------------------------------------------


StereoMatchDepth::StereoMatchDepth()
{

}

//----------------------------------------------------------------

image::ArrayGrid<double>* StereoMatchDepth::MatchStereo( image::ArrayGrid<double>* pGrid1,
                                                         image::ArrayGrid<double>* pGrid2,
                                                         int windowHalfWidth,
                                                         common::MatchCriterion myMatchCriterion
                                                       )
{
    switch(myMatchCriterion)
    {
        case common::MATCH_MI:
        {
            return MatchStereoMI( pGrid1, pGrid2, windowHalfWidth );
        }
        case common::MATCH_NCC:
        {
            return MatchStereoNCC( pGrid1, pGrid2, windowHalfWidth );
        }
        default:
        case common::MATCH_SSD:
        {
            return MatchStereoSSD( pGrid1, pGrid2, windowHalfWidth );
        }
    }
}

//----------------------------------------------------------------

image::ArrayGrid<double>* StereoMatchDepth::MatchStereoSSD( image::ArrayGrid<double>* pGrid1,
                                                            image::ArrayGrid<double>* pGrid2,
                                                            int windowHalfWidth
                                                          )
{
    int width  = pGrid1->GetWidth();
    int height = pGrid1->GetHeight();
    image::ArrayGrid<double>* pGridResult = new image::ArrayGrid<double>( width, height );

    for ( int y = windowHalfWidth; y < height - windowHalfWidth; y++ )
    {
        std::cout << "Processing line " << y << std::endl;
        for ( int x = windowHalfWidth; x < width - windowHalfWidth; x++ )
        {
            double bestLocalSSD = 1000000000000000000;
            int bestX = 0;
            int xTop1 = x - windowHalfWidth;
            int yTop1 = y - windowHalfWidth;
            int xBottom1 = x + windowHalfWidth;
            int yBottom1 = y + windowHalfWidth;
            for ( int xx = windowHalfWidth; xx < width - windowHalfWidth; xx++ )
            {
                int xTop2 = xx - windowHalfWidth;
                int yTop2 = yTop1;
                int xBottom2 = xx + windowHalfWidth;
                int yBottom2 = yBottom1;
                double currentSSD = NumberGridTools<double>::ComputeLocalSquaredDifference( pGrid1, xTop1, yTop1, xBottom1, yBottom1,
                                                                                            pGrid2, xTop2, yTop2, xBottom2, yBottom2 );
                if ( currentSSD < bestLocalSSD )
                {
                    bestLocalSSD = currentSSD;
                    bestX = xx;
                }
            }
            pGridResult->SetValue( x, y, abs(x-bestX));
        }
    }
    return pGridResult;
}

//----------------------------------------------------------------

image::ArrayGrid<double>* StereoMatchDepth::MatchStereoNCC( image::ArrayGrid<double>* pGrid1,
                                                            image::ArrayGrid<double>* pGrid2,
                                                            int windowHalfWidth
                                                          )
{
    int width  = pGrid1->GetWidth();
    int height = pGrid1->GetHeight();
    image::ArrayGrid<double>* pGridResult = new image::ArrayGrid<double>( width, height );

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
            for ( int xx = windowHalfWidth; xx < width - windowHalfWidth; xx++ )
            {
                int xTop2 = xx - windowHalfWidth;
                int yTop2 = yTop1;
                int xBottom2 = xx + windowHalfWidth;
                int yBottom2 = yBottom1;
                double currentNCC = NumberGridTools<double>::ComputeLocalCrossCorrelation( pGrid1, xTop1, yTop1, xBottom1, yBottom1,
                                                                                           pGrid2, xTop2, yTop2, xBottom2, yBottom2 );
                if ( currentNCC > bestLocalNCC )
                {
                    bestLocalNCC = currentNCC;
                    bestX = xx;
                }
            }
            pGridResult->SetValue( x, y, abs(x-bestX));
        }
    }
    return pGridResult;
}

//----------------------------------------------------------------

image::ArrayGrid<double>* StereoMatchDepth::MatchStereoMI( image::ArrayGrid<double>* pGrid1,
                                                           image::ArrayGrid<double>* pGrid2,
                                                           int windowHalfWidth
                                                         )
{
    int width  = pGrid1->GetWidth();
    int height = pGrid1->GetHeight();
    image::ArrayGrid<double>* pGridResult = new image::ArrayGrid<double>( width, height );

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
            for ( int xx = windowHalfWidth; xx < width - windowHalfWidth; xx++ )
            {
                int xTop2 = xx - windowHalfWidth;
                int yTop2 = yTop1;
                int xBottom2 = xx + windowHalfWidth;
                int yBottom2 = yBottom1;
                double currentMI = NumberGridTools<double>::ComputeLocalMutualInformation( pGrid1, xTop1, yTop1, xBottom1, yBottom1,
                                                                                           pGrid2, xTop2, yTop2, xBottom2, yBottom2 );
                if ( currentMI > bestLocalMI )
                {
                    bestLocalMI = currentMI;
                    bestX = xx;
                }
            }
            pGridResult->SetValue( x, y, abs(x-bestX));
        }
    }
    return pGridResult;
}

}
}

