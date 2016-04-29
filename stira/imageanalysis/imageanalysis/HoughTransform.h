
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

#ifndef STIRA_IMAGEANALYSIS_HOUGHTRANSFORM_H
#define STIRA_IMAGEANALYSIS_HOUGHTRANSFORM_H

#include <iostream>
#include <cstdlib>
#include <cmath>
#include "../../common/common/Point.h"
#include "../../common/common/LineSegment.h"
#include "../../image/datastructures/Image.h"

namespace stira {
namespace imageanalysis {

/** \brief Canny edge detector
  */
class HoughTransform
{
public:
    HoughTransform();
    int BuildAccumulator( image::ArrayGrid<bool>* pEdges );
    std::vector< common::LineSegment<int> > GetLines( int threshold );

    void VisualizeAcculumulator( std::string fileName );

private:
    image::ArrayGrid<int>* mpAccu;
    int mImageWidth;
    int mImageHeight;

    int mAccuWidth;
    int mAccuHeight;
};
}
}
#endif // HOUGHTRANSFORM_H
