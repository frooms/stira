
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

#ifndef STIRA_FILTER__LAPLACIANOFGAUSSIANFILTER_H
#define STIRA_FILTER__LAPLACIANOFGAUSSIANFILTER_H

#include "../../image/datastructures/Image.h"

namespace stira{
namespace filter{

/** \brief Creates a Laplacian of Gaussian filtered image
  *
  * In fact second derivative (Laplacian: of a smoothened version of the image,
  * combined in a single filter operation:
  * if r^2 = x^2 + y^2
  *    z = r^2 / (2 * (sigma^2))
  * then LoG(x,y) = (1-z) * exp(-z) / (pi * sigma^4)
  * http://homepages.inf.ed.ac.uk/rbf/HIPR2/log.htm
  */
class LaplacianOfGaussianFilter
{
public:
   /** \brief constructor*/
   LaplacianOfGaussianFilter();

   /** \brief destructor*/
   ~LaplacianOfGaussianFilter();

   /** \brief Runs the LoG filtering operation
     * Creates a new image, which becomes the responsability of the caller
     * \param pImage input image
     * \param scaleFactor factor with which to scale the output intensities*/
   static image::Image* Run(image::Image* pImage, double scaleFactor=1.0);

private:
   /** \brief Computes intermediate parameter C
     *
     * \param x x coordinate for the central pixel currently being filtered
     * \param y y coordinate for the central pixel currently being filtered
     * \param sigma sigma of the gaussian prefilter
     * \param halfSize if filter kernel window size is 2N+1, halfSize is N
     * \return parameter C
     */
   static double GetC(int x, int y, double sigma, int halfSize);

   /** \brief Generates the LoG filter kernel
     *
     * \param sigma sigma of the gaussian prefilter
     * \param halfSize if filter kernel window size is 2N+1, halfSize is N
     * \return array containing filter taps for LoG kernel
     */
   static double* GenerateLoGKernel(int halfSize, double sigma);
};

}
}
#endif
