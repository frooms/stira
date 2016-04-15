
/***************************************************************************************
 *   Copyright (C) 2016 by Filip Rooms                                                 *
 *                                                                                     *
 *  Terms and conditions for using this software in any form are provided in the       *
 *  file COPYING, which can be found in the root directory of this project.            *
 *                                                                                     *
 *   Contact data: filip.rooms@gmail.com                                               *
 *                 http://www.filiprooms.be/                                           *
 *                                                                                     *
 ***************************************************************************************/

#ifndef STIRA_CONTRASTENHANCE_ADAPTIVEHISTOGRAMEQUALIZER_H
#define STIRA_CONTRASTENHANCE_ADAPTIVEHISTOGRAMEQUALIZER_H

#include "../../common/common/RectangularROI.h"
#include "../../image/datastructures/Image.h"
#include "../../histogram/histogram/FloatHistogram.h"

namespace stira {
namespace contrastenhance {

/** \brief class for adaptive histogram equalization like in https://en.wikipedia.org/wiki/Adaptive_histogram_equalization */
class AdaptiveHistogramEqualizer
{
public:
    /** \brief constructor
      * \param pSourceImage the input image
      * \param blockWidth width of block to divide image in
      * \param blockHeight height of block to divide image in */
    AdaptiveHistogramEqualizer( image::Image* pSourceImage, int blockWidth, int blockHeight );

    /** \brief destructor */
    ~AdaptiveHistogramEqualizer( );

    /** \brief Initializes block sizes and corresponding data structures
      * Needs to be called  */
    bool Initialize( );

    /** \brief Run method
      * \return a newly created image as result of contrast enhancement, becomes responsability of the caller*/
    image::Image* Run();

private:

    /** \brief Builds normalized cumulative histogram for single block */
    void BuildNormHistogramSingleBlock( image::ArrayGrid<double>* pInGrid, int xi, int yi );

    /** \brief gets equalized image intensity according to single block */
    double GetEqualizedValueSingleBlock( image::ArrayGrid<double>* pInGrid, int x, int y, int xi, int yi );

    /** \brief gets equalized image intensity interpolated from four neighboring blocks */
    double InterpolateEqualizedValue( image::ArrayGrid<double>* pInGrid, int x, int y );

    image::ArrayGrid< histogram::FloatHistogram*>* mpHistogramPerBlock;   ///< grid of histograms per block

    image::Image* mpSourceImage;  ///< grid of histograms per block

    int mWidth;            ///< width of input image
    int mHeight;           ///< height of input image
    int mBlockWidth;       ///< width of single block
    int mBlockHeight;      ///< height of single block

    int mNrBlocksX;        ///< number of blocks in x direction
    int mNrBlocksY;        ///< number of blocks in y direction

    int mDesiredMax;       ///< desired maximum intensity after equalization
    int mDesiredMin;       ///< desired minimum intensity after equalization
};

}
}

#endif // ADAPTIVEHISTOGRAMEQUALIZER_H
