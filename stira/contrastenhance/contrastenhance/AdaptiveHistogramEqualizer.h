
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

/** \brief class with tools for image intensity remapping using histograms, like histogram matching and histogram equalization
  */

class AdaptiveHistogramEqualizer
{
public:
    AdaptiveHistogramEqualizer();

    void HistogramEqualizeSingleBlock( image::ArrayGrid<double>* pInGrid, int xi, int yi );


    /** \brief overloaded Run method per image
      * \param pSourceImage the input image
      * \return a newly created image as result of contrast enhancement, becomes responsability of the caller*/
    image::Image* Run( image::Image* pSourceImage );


    /** \brief sets the size of the local window around a central pixel
      * \param size size of the local window around a central pixel
      * usually between 5 and 11 */
    void SetBlockSize( int size );

private:
    image::ArrayGrid<histogram::FloatHistogram*>* pHistogramPerBlock;

};

}
}

#endif // ADAPTIVEHISTOGRAMEQUALIZER_H
