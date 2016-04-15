
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

/** \brief class for adaptive histogram equalization like in https://en.wikipedia.org/wiki/Adaptive_histogram_equalization
  *    Warning: this implementation is still in progress!!
  */

class AdaptiveHistogramEqualizer
{
public:
    /** \brief constructor */
    AdaptiveHistogramEqualizer( image::Image* pSourceImage );

    ~AdaptiveHistogramEqualizer( );

    bool Initialize( int blockWidth, int blockHeight);

    /** \brief overloaded Run method per image
      * \param pSourceImage the input image
      * \return a newly created image as result of contrast enhancement, becomes responsability of the caller*/
    image::Image* Run();

private:

    void BuildNormHistogramSingleBlock( image::ArrayGrid<double>* pInGrid, int xi, int yi );

    double GetEqualizedValueSingleBlock( image::ArrayGrid<double>* pInGrid, int x, int y, int xi, int yi );

    double InterpolateEqualizedValue( image::ArrayGrid<double>* pInGrid, int x, int y );

    image::ArrayGrid< std::pair< common::Point<double>, histogram::FloatHistogram*> >* mpHistogramPerBlock;

    image::Image* mpSourceImage;
    int mWidth;
    int mHeight;
    int mBlockWidth;
    int mBlockHeight;

    int mNrBlocksX;
    int mNrBlocksY;

    int mDesiredMax;
    int mDesiredMin;\

};

}
}

#endif // ADAPTIVEHISTOGRAMEQUALIZER_H
