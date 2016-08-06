
/***************************************************************************************
 *   Copyright (C) 2008 by Filip Rooms                                                 *
 *                                                                                     *
 *  Terms and conditions for using this software in any form are provided in the       *
 *  file COPYING, which can be found in the root directory of this project.            *
 *                                                                                     *
 *   Contact data: filip.rooms@gmail.com                                               *
 *                 http://www.filiprooms.be/                                           *
 *                                                                                     *
 ***************************************************************************************/

#ifndef STIRA_CONTRASTENHANCE_HISTOGRAMEQUALIZE_H
#define STIRA_CONTRASTENHANCE_HISTOGRAMEQUALIZE_H

#include "../../common/common/RectangularROI.h"
#include "../../imagedata/datastructures/Image.h"
#include "../../histogram/histogram/FloatHistogram.h"

namespace stira {
namespace contrastenhance {

/** \brief class with tools for image intensity remapping using histograms, like histogram matching and histogram equalization
  */
class HistogramTools
{

//////////////////////////
//                      //
// 0) GENERAL STUFF     //
//                      //
//////////////////////////

public:

   /** \brief constructor */
   HistogramTools();

   /** \brief destructor */
   ~HistogramTools();

/////////////////////////////
//                         //
// 1) HISTOGRAM REMAPPING  //
//                         //
/////////////////////////////

public:

   /** \brief remap intensities in an image ROI to follow a target histogram
     * References   http://en.wikipedia.org/wiki/Histogram_equalization -> Backprojection
     *              http://en.wikipedia.org/wiki/Histogram_matching
     *
     * \param pInGrid source image grid with intensity values to be remapped
     * \param rroi the rectangular region of interest within which values are to be remapped
     * \param ihCumulativeReferenceHistogram target cumulative histogram after remapping (not normalized) */
   static void RemapHistogramInROI( image::ArrayGrid<double>* pInGrid,
                                    common::RectangularROI<int> rroi,
                                    histogram::IntHistogram* fhCumulativeInput,
                                    histogram::FloatHistogram* fhCumulativeReference );

   /** \brief matches an intensity from an image with ihIncomingCumulativeHistogram to transform it to ihCumulativeReferenceHistogram
     * \param inValue incoming intensity value to be remapped
     * \param fhIncomingCumulativeHistogram incoming cumulative histogram before remapping (not normalized)
     * \param fhCumulativeReferenceHistogram target cumulative histogram after remapping (not normalized) */
   static double MatchHistogramValue( double inValue,
                                      histogram::IntHistogram* fhIncomingCumulativeHistogram,
                                      histogram::FloatHistogram* fhCumulativeReferenceHistogram );

////////////////////////////////////////
//                                    //
// 2) HISTOGRAM EQUALIZATION METHODS  //
//                                    //
////////////////////////////////////////

public:

   /** \brief Performs robust linear intensity rescaling, creating a new object as result
     * A new image is created, which becomes the responsability of the caller
     * \param pSourceImage input image
     * \param lowerFraction fraction of darkest pixels to ignore
     * \param upperFraction fraction of pixels to take into account (1-upperFraction is fraction to be discarded)*/
   static image::Image* RobustLinearRescale( image::Image* pSourceImage, double lowerFraction=0.01, double upperFraction=0.99 );

   /** \brief Performs robust linear intensity rescaling on the image itself, creating no new object
     * (No new image is created; old values are overwritten)
     * \param pSourceImage input image; contains result as well
     * \param lowerFraction fraction of darkest pixels to ignore
     * \param upperFraction fraction of pixels to take into account (1-upperFraction is fraction to be discarded)*/
   static bool RobustLinearRescaleNoNew( image::Image* pSourceImage, double lowerFraction=0.01, double upperFraction=0.99 );

   /** \brief performs histogram equalization on a single band
     * \param pInOutGrid the input grid; values are changed on source data*/
   static void HistogramEqualizeSingleBand( image::ArrayGrid<double>* pInOutGrid );

   /** \brief performs histogram equalization on an image, but for all bands independantly
     * \param pInImage the input image*/
   static image::Image* HistogramEqualizePerBand( image::Image* pInImage );

   /** \brief performs histogram equalization on an RGB image using transformation to HSI color space
     * RGB colors are transformed to HSI, and only the I component is equalized; after that, the result is
     * transformed back to RGB
     * \param pInImage the input image*/
   static image::Image* HistogramEqualizeHSI( image::Image* pInImage );

   /** \brief performs histogram equalization on an RGB image using transformation to CIE-Lab color space
     * RGB colors are transformed to  CIE-Lab, and only the L component is equalized; after that, the result is
     * transformed back to RGB (values are clipped to range 0-255)
     * \param pInImage the input image*/
   static image::Image* ColorHistogramEqualize( image::Image* pInImage );

};

}
}

#endif
