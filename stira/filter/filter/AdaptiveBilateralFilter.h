
/***********************************************************************************
 *   Copyright (C) 2008 by Filip Rooms                                             *
 *                                                                                 *
 *  Terms and conditions for using this software in any form are provided in the   *
 *  file COPYING, which can be found in the root directory of this project.        *
 *                                                                                 *
 *   Contact data: filip.rooms@gmail.com                                           *
 *                 http://www.filiprooms.be/                                       *
 *                                                                                 *
 ***********************************************************************************/

#ifndef STIRA_FILTER_ADAPTIVEBILINEARFILTER_H
#define STIRA_FILTER_ADAPTIVEBILINEARFILTER_H

#include "../../imagedata/datastructures/Image.h"

namespace stira{
namespace filter{

/** \brief computes adaptive bilateral filter as described in reference
  * Bibtex reference:
  *     article{ zhang08adaptive,
  *                author  = {Zhang, B. and Allebach, J. P.},
  *                title   = {Adaptive Bilateral Filter for Sharpness Enhancement and Noise Removal},
  *                journal = {IEEE Trans. Image Processing},
  *                volume  = {17},
  *                number  = {5},
  *                pages   = {664--678}
  *                year    = {2008}
  *            }
  */
class AdaptiveBilateralFilter
{
public:
   /** \brief constructor*/
   AdaptiveBilateralFilter();
   
   /** \brief destructor*/
   ~AdaptiveBilateralFilter();
   
   /** \brief run method*/
   static image::Image* Run(image::Image* pImage);
private:
   /** \brief Converts LoG to adaptive parameter zeta
     *
     * For adaptivity, LaplacianOfGaussian (LoG) of the image is computed. In contrast with 
     * The reference paper, we approximate the relation between LoG and zeta with a parametric 
     * model instead of a LUT from a training set.
     *
     * \param logClass clipped intensity of the LoG output*/
   static double LoGClassToZeta(double logClass);

   /** \brief Converts LoG to adaptive parameter sigma_R
     *
     * For adaptivity, LaplacianOfGaussian (LoG) of the image is computed. In contrast with 
     * The reference paper, we approximate the relation between LoG and sigma_R with a parametric 
     * model instead of a LUT from a training set.
     *
     * \param logClass clipped intensity of the LoG output*/
   static double LoGClassToSigmaR(double logClass);

   static const int mWindowSize;  ///< size of window to consider per pixel being filtered
};

}
}

#endif
