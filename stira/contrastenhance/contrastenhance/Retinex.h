
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

#ifndef STIRA_CONTRASTENHANCE_RETINEX_H
#define STIRA_CONTRASTENHANCE_RETINEX_H

#include "../../common/common/Random.h"
#include "../../imagedata/datastructures/Image.h"

namespace stira {
namespace contrastenhance {

/** \brief retinex contrast enhancement/color restoration
  *
  * http://dragon.larc.nasa.gov/background/retpubs.html
  *
  * Ref: http://dragon.larc.nasa.gov/background/retpubs.html
  *      1. D. J. Jobson, Z. Rahman, and G. A. Woodell,
  *         A Multi-Scale Retinex For Bridging the Gap Between Color Images and the Human Observation of Scenes,
  *         IEEE Transactions on Image Processing: Special Issue on Color Processing, July 1997.
  *
  *         D. J. Jobson, Z. Rahman, and G. A. Woodell,  Retinex Image Processing: Improved Fidelity for Direct
  *         Visual Observation, Proceedings of the IS&T Fourth Color Imaging Conference: Color Science, Systems,
  *         and Applications, (1996).
  */
class Retinex
{
public:

//////////////////////////
//                      //
// 1) GENERAL STUFF     //
//                      //
//////////////////////////

   /** \brief constructor */
   Retinex();

   /** \brief destructor */
   ~Retinex();

///////////////////////////////////////////////////
//                                               //
// 2) MULTISCALE RETINEX WITH COLOR RESTORATION  //
//     (Rahman, Jobson,  Woodell)                //
//                                               //
///////////////////////////////////////////////////

public:
   /** \brief run method of MultiScale Retinex with Color Restoration according to Jobson et al
     * \param pSourceImage input image
     * \param lowerFraction lower fraction of pixels to be discarded
     * \param upperFraction upper fraction of pixels to be discarded
     * \param applyColorCorrection flag if color correction needs to be applied*/
   static image::Image* RunMSRCR( image::Image* pSourceImage, double lowerFraction, double upperFraction, bool applyColorCorrection=true);

   /** \brief run method of MultiScale Retinexaccording to Jobson et al for single band
     * \param pInGrid input grid
     * \param lowerFraction lower fraction of pixels to be discarded
     * \param upperFraction upper fraction of pixels to be discarded */
   static image::ArrayGrid<double>* RunMSR( image::ArrayGrid<double>* pInGrid, double lowerFraction, double upperFraction );

private:
   /** \brief runs a single scale retinex on an image
     * \param pInImage input image
     * \param sigma sigma value specifying scale of this single scale retinex
     * \return contrast enhanced image on this scale*/
   static image::Image* SingleScaleRetinex(image::Image* pInImage, double sigma);

   /** \brief runs a single scale retinex on a single grid
     * \param pInGrid input grid
     * \param sigma sigma value specifying scale of this single scale retinex
     * \return contrast enhanced grid on this scale*/
   static image::ArrayGrid<double>* SingleScaleRetinex( image::ArrayGrid<double>* pInGrid, double sigma );

   /** \brief runs a multiscale retinex on an image
     * \param pInImage input image
     * \return multiscale contrast enhanced image*/
   static image::Image* MultiScaleRetinex( image::Image* pInImage );

   /** \brief runs a multiscale retinex on a single grid
     * \param pInGrid input grid
     * \return multiscale contrast enhanced image*/
   static image::ArrayGrid<double>* MultiScaleRetinex( image::ArrayGrid<double>* pInGrid );

   /** \brief Color correction of image
     * \param pInImage input image
     * \return color corrected image*/
   static image::Image* ColorCorrectImage( image::Image* pInImage );

   /** \brief Clips the dynamic range of an image by applying two thresholds; subsequently scales the clipped image values
     * Works directly on the image values; old values are lost
     * \param pInOutImage input image
     * \param lowerFraction lower fraction of pixels to be clipped (e.g., if 0.03, the 3% darkest pixels are clipped)
     * \param upperFraction lower fraction of pixels to be clipped (e.g., if 0.98, the 2% brightest pixels are clipped) */
   static void ClipAndScaleImage(image::Image* pInOutImage, double lowerFraction, double upperFraction);

   /** \brief Clips the dynamic range of a single grid by applying two thresholds; subsequently scales the clipped image values
     * Works directly on the image values; old values are lost
     * \param pInOutGrid input grid
     * \param lowerFraction lower fraction of pixels to be clipped (e.g., if 0.03, the 3% darkest pixels are clipped)
     * \param upperFraction lower fraction of pixels to be clipped (e.g., if 0.98, the 2% brightest pixels are clipped) */
   static void ClipAndScaleGrid(image::ArrayGrid<double>* pInOutGrid, double lowerFraction, double upperFraction);

private:
};

}
}

#endif
