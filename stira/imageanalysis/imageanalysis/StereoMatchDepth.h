
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

#ifndef STIRA_IMAGEANALYSIS_STEREOMATCHDEPTH_H
#define STIRA_IMAGEANALYSIS_STEREOMATCHDEPTH_H

#include <iostream>
#include "../../common/common/Definitions.h"
#include "../../common/common/Point.h"
#include "../../image/datastructures/Image.h"

namespace stira {
namespace imageanalysis {

// http://www.cse.psu.edu/~rtc12/CSE486/lecture09_6pp.pdf
// http://campar.in.tum.de/twiki/pub/Chair/TeachingWs09Cv2/3D_CV2_WS_2009_Stereo.pdf
class StereoMatchDepth
{
public:
    StereoMatchDepth();

    static image::ArrayGrid<double>* MatchStereo( image::ArrayGrid<double>* pGrid1, image::ArrayGrid<double>* pGrid2,
                                                  int windowHalfWidth, common::MatchCriterion myMatchCriterion, int maxDisparity );

private:

    static image::ArrayGrid<double>* MatchStereoSSD( image::ArrayGrid<double>* pGrid1, image::ArrayGrid<double>* pGrid2,
                                                     int windowHalfWidth, int maxDisparity );

    static image::ArrayGrid<double>* MatchStereoNCC( image::ArrayGrid<double>* pGrid1, image::ArrayGrid<double>* pGrid2,
                                                     int windowHalfWidth, int maxDisparity );

    static image::ArrayGrid<double>* MatchStereoMI( image::ArrayGrid<double>* pGrid1, image::ArrayGrid<double>* pGrid2,
                                                    int windowHalfWidth, int maxDisparity );
};

}
}

#endif // STEREOMATCHDEPTH_H
