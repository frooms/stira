
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

#include "../../common/common/LineSegment.h"
#include "../../imagedata/datastructures/Image.h"
#include "../../imagedata/datastructures/OrientationGrid.h"

namespace stira {
namespace imageanalysis {

/** \brief Canny edge detector
  */
class HoughTransform
{
public:
    HoughTransform();
    ~HoughTransform();

    //http://www.keymolen.com/2013/05/hough-transformation-c-implementation.html
    std::vector< common::LineSegment<int> >                GetLines(   image::ArrayGrid<bool>* pEdges,      int threshold );

    //https://github.com/marcbowes/Hough-Circle-Detector/blob/master/src/hcd.cpp
    std::vector< std::pair< common::Point<int>, double > > GetCirclesRadius( image::OrientationGrid* pOrientGrid, int radius, int threshold );

    void VisualizeAcculumulator( std::string fileName );

private:
    int BuildAccumulatorLines( image::ArrayGrid<bool>* pEdges );
    int BuildAccumulatorCircles( image::OrientationGrid* pOrientGrid );

    image::ArrayGrid<int>* mpAccu;
    int mImageWidth;
    int mImageHeight;

    int mAccuWidth;
    int mAccuHeight;
};
}
}
#endif // HOUGHTRANSFORM_H
