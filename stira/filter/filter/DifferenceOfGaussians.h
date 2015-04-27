/***********************************************************************************
 *   Copyright (C) 2011 by Filip Rooms                                             *
 *                                                                                 *
 *  Terms and conditions for using this software in any form are provided in the   *
 *  file COPYING, which can be found in the root directory of this project.        *
 *                                                                                 *
 *   Contact data: filip.rooms@gmail.com                                           *
 *                 http://www.filiprooms.be/                                       *
 *                                                                                 *
 ***********************************************************************************/

#ifndef STIRA_FILTER_DIFFERENCEOFGAUSSIANS_H
#define STIRA_FILTER_DIFFERENCEOFGAUSSIANS_H

#include "../../image/datastructures/Image.h"

namespace stira{
namespace filter{

/** \brief Creates a Difference of Gaussians filtered image
  *  http://en.wikipedia.org/wiki/Difference_of_Gaussians
  */
class DifferenceOfGaussians
{
public:
   /** \brief constructor */
   DifferenceOfGaussians( );

   /** \brief destructor */
   ~DifferenceOfGaussians( );

   /** \brief Filters a grid with a Difference of Gaussians filterkernel
     * \param pGridIn input grid to be filtered
     * \param sigmaX1 sigma in X direction for the narrowest gaussian
     * \param sigmaY1 sigma in Y direction for the narrowest gaussian
     * \param sigmaX2 sigma in X direction for the broadest gaussian
     * \param sigmaY2 sigma in Y direction for the broadest gaussian
     * \return the resulting filtered grid */
   static image::ArrayGrid<double>* Run( image::ArrayGrid<double>* pGridIn, double sigmaX1, double sigmaY1, double sigmaX2, double sigmaY2 );

   /** \brief Filters a grid with a Difference of Gaussians filterkernel
     * \param pGridIn input grid to be filtered
     * \param sigmaX1 sigma in X direction for the narrowest gaussian
     * \param sigmaX2 sigma in X direction for the broadest gaussian
     * \param sigmaY sigma in Y direction
     * \return the resulting filtered grid */
   static image::ArrayGrid<double>* Run( image::ArrayGrid<double>* pGridIn, double sigmaX1, double sigmaX2, double sigmaY );

   /** \brief Filters an image with a Difference of Gaussians filterkernel
     * \param pImageIn input image to be filtered
     * \param sigmaX1 sigma in X direction for the narrowest gaussian
     * \param sigmaY1 sigma in Y direction for the narrowest gaussian
     * \param sigmaX2 sigma in X direction for the broadest gaussian
     * \param sigmaY2 sigma in Y direction for the broadest gaussian
     * \return the resulting filtered image */
   static image::Image* Run( image::Image* pImageIn, double sigmaX1, double sigmaY1, double sigmaX2, double sigmaY2 );

   /** \brief Filters an image with a Difference of Gaussians filterkernel
     * \param pImageIn input image to be filtered
     * \param sigmaX1 sigma in X direction for the narrowest gaussian
     * \param sigmaX2 sigma in X direction for the broadest gaussian
     * \param sigmaY sigma in Y direction
     * \return the resulting filtered image */
   static image::Image* Run( image::Image* pImageIn, double sigmaX1, double sigmaX2, double sigmaY );
};

}
}

#endif // DIFFERENCEOFGAUSSIANS_H
