#ifndef STIRA_IMAGEANALYSIS_FLOODFILL_H
#define STIRA_IMAGEANALYSIS_FLOODFILL_H

#include "../../common/common/Point.h"
#include "../../common/common/RectangularROI.h"
#include "../../image/datastructures/ArrayGrid.h"
#include <vector>

namespace stira {
namespace imageanalysis {

/** \brief class that implements a simple flood fill
  * Based on recursive implementation described in http://en.wikipedia.org/wiki/Flood_fill */
class FloodFill
{
public:
    /** \brief constructor */
    FloodFill();

    /** \brief Run method of the fill
      * \param pGrid grid to be filled
      * \param nodeX x coordinate of starting seed
      * \param nodeY y coordinate of starting seed
      * \param targetValue value to be replaced
      * \param replacementValue value to replace targetValue by
      * \return the number of pixels filled by this flooding  */
    int Run( image::ArrayGrid<int>* pGrid, int nodeX, int nodeY, int targetValue, int replacementValue, bool fill8Connected=true );

    /** \brief Gets a vector with the pixels that were flooded during the Run
      * \warning call is only valid after Run was called!!!
      * \return vector with the pixels that were flooded during the Run*/
    std::vector< common::Point<int> > GetFloodedPixels();

    /** \brief Gets the center of gravity of the region that was flooded
      * if the region was empty, the point (0,0) is returned
      * \warning call is only valid after Run was called!!!
      * \return point that is center of gravity of the pixels that were flooded during the Run*/
    common::Point<double> GetCenterOfGravity();

    /** \brief Gets the bounding box of the region that was flooded
      * if the region was empty, the point (0,0) is returned
      * \warning call is only valid after Run was called!!!
      * \return point that is center of gravity of the pixels that were flooded during the Run*/
    common::RectangularROI<int> GetBoundingBox();

    /** \brief allows to prepare a help grid to deal with filling between two thresholds instead of filling a single value in a grid
      * \param pGrid input grid
      * \param lowerBound lower bound value for filling
      * \param upperBound upper bound value for filling
      * \param targetValue value that all values in the range between lowerBound and upperBound are replaced with
      * \return a new grid in which the range between lowerBound and upperBound is replaced by a single value
      * \warning the return grid becomes the responsability of the caller to delete.*/
    static image::ArrayGrid<int>* PrepareValues( image::ArrayGrid<double>* pGrid, int lowerBound, int upperBound, int targetValue );

private:

    /** \brief the actual flood fill (calls itself recursively) in case of 4-connectivity
      * For a pixel "x", the neighbors "+" considered are above, below, left and right:
      *
      *               +
      *             + x +
      *               +
      *
      * \param pGrid grid to be filled
      * \param nodeX x coordinate of starting seed
      * \param nodeY y coordinate of starting seed
      * \param targetValue value to be replaced
      * \param replacementValue value to replace targetValue by */
    void Fill4Connected( image::ArrayGrid<int>* pGrid, int nodeX, int nodeY, int targetValue, int replacementValue );

    /** \brief the actual flood fill (calls itself recursively) in case of 8-connectivity
      * For a pixel "x", the neighbors "+" considered are above, below, left and right and the diagonals:
      *
      *             + + +
      *             + x +
      *             + + +
      *
      * \param pGrid grid to be filled
      * \param nodeX x coordinate of starting seed
      * \param nodeY y coordinate of starting seed
      * \param targetValue value to be replaced
      * \param replacementValue value to replace targetValue by */
    void Fill8Connected( image::ArrayGrid<int>* pGrid, int nodeX, int nodeY, int targetValue, int replacementValue );

    int mNrPixelsFlooded; ///< the number of pixels filled by this flooding
    std::vector< common::Point<int> > mvPixelsFlooded;  ///< vector with the pixels that were flooded during the Run

};
}
}

#endif // FLOODFILL_H
