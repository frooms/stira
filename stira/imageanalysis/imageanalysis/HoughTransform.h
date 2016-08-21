
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

using namespace imagedata;

/** \brief Hough transform
 * References: http://www.keymolen.com/2013/05/hough-transformation-c-implementation.html
 *             https://github.com/marcbowes/Hough-Circle-Detector/blob/master/src/hcd.cpp
  */
class HoughTransform
{
public:
    /** \brief constructor */
    HoughTransform();

    /** \brief destructor */
    ~HoughTransform();

    /** \brief gets lines as detected by the Hough transform
      * \param pEdges edge image (typically output liike from Canny edge detector)
      * \param threshold  threshold how many hits a line must have with the edge image to be counted as actual line
      * \return vector of line segments  */
    std::vector< common::LineSegment<int> > GetLines( ArrayGrid<bool>* pEdges, int threshold );

    /** \brief gets circles as detected by the Hough transform (just one single radius)
      * \param pEdges edge image (typically output liike from Canny edge detector)
      * \param radius radius of circles to look for in the image
      * \param threshold  threshold how many hits a line must have with the edge image to be counted as actual line
      * \return vector of line segments  */
    std::vector< common::Point<int> > GetCirclesRadius( ArrayGrid<bool>* pEdges, int radius, int threshold );

    /** \brief visualizes the accumulator as an image
      * \param fileName name of file to write accumulator image to */
    void VisualizeAcculumulator( std::string fileName );

private:
    /** \brief builds the accumulator in case of line Hough transform
      * \param pEdges edge image */
    int BuildAccumulatorLines( ArrayGrid<bool>* pEdges );

    /** \brief builds the accumulator in case of circle Hough transform
      * \param pEdges edge image
      * \param radius radius of circles to look for in the image */
    int BuildAccumulatorCircles( ArrayGrid<bool>* pEdgeGrid, int radius );

    ArrayGrid<int>* mpAccu;  ///< accumulator array
    int mImageWidth;         ///< width of the input image
    int mImageHeight;        ///< height of the input image

    int mAccuWidth;    ///< width of the accumulator array
    int mAccuHeight;   ///< height of the accumulator array
};

}
}

#endif // HOUGHTRANSFORM_H
