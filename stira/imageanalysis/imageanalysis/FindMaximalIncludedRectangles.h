#ifndef STIRA_IMAGEANALYSIS_FINDMAXIMALINCLUDEDRECTANGLES_H
#define STIRA_IMAGEANALYSIS_FINDMAXIMALINCLUDEDRECTANGLES_H

#include <vector>
#include "../../common/common/RectangularROI.h"
#include "../../histogram/histogram/IntHistogram.h"
#include "../../image/datastructures/ArrayGrid.h"

enum rectangleMeasure{ MEASURE_WIDTH, MEASURE_HEIGHT, MEASURE_AREA, MEASURE_DIAGONALLENGTH };

namespace stira {
namespace imageanalysis {

/** \brief finds maximal rectangles contained in an object
  * Maximal means that the rectangle can not be in its whole part of a larger rectangle
  * Algorithm is from http://www.montefiore.ulg.ac.be/~pierard/rectangles/ */
class FindMaximalIncludedRectangles
{
public:
   /** \brief constructor */
   FindMaximalIncludedRectangles();

   /** \brief finds contained maximum rectangles contained in boolean object
     * \param pObjectGrid input boolean grid
     * \return vector of maximum contained rectangles */
   static std::vector< common::RectangularROI<int> > Run( image::ArrayGrid<bool>* pObjectGrid );

   static histogram::IntHistogram CreateRectangleHistogram( std::vector< common::RectangularROI<int> > vRectangle,
                                                            rectangleMeasure myMeasure=MEASURE_AREA, bool isCumulative=true );
};

}
}

#endif // STIRA_IMAGEANALYSIS_FINDMAXIMALINCLUDEDRECTANGLES_H
