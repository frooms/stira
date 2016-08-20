
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
#include "../../imagedata/datastructures/Image.h"

namespace stira {
namespace imageanalysis {

using namespace imagedata;

// http://www.cse.psu.edu/~rtc12/CSE486/lecture09_6pp.pdf
// http://campar.in.tum.de/twiki/pub/Chair/TeachingWs09Cv2/3D_CV2_WS_2009_Stereo.pdf
class StereoMatchDepth
{
public:
    StereoMatchDepth();

    static ArrayGrid<double>* MatchStereo( ArrayGrid<double>* pGrid1, ArrayGrid<double>* pGrid2,
                                           int windowHalfWidth, common::MatchCriterion myMatchCriterion, int maxDisparity );

private:

    static ArrayGrid<double>* MatchStereoSSD( ArrayGrid<double>* pGrid1, ArrayGrid<double>* pGrid2,
                                              int windowHalfWidth, int maxDisparity );

    static ArrayGrid<double>* MatchStereoNCC( ArrayGrid<double>* pGrid1, ArrayGrid<double>* pGrid2,
                                              int windowHalfWidth, int maxDisparity );

    static ArrayGrid<double>* MatchStereoMI( ArrayGrid<double>* pGrid1, ArrayGrid<double>* pGrid2,
                                             int windowHalfWidth, int maxDisparity );
};

}
}

#endif // STEREOMATCHDEPTH_H
