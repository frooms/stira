
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

#ifndef STIRA_DEGRADATIONESTIMATION_COMPARESMOOTHSHARPDIJK_H
#define STIRA_DEGRADATIONESTIMATION_COMPARESMOOTHSHARPDIJK_H

#include <iostream>
#include <cmath>
#include "../../image/datastructures/Image.h"

namespace stira {
namespace degradationestimation {

/** \brief class to compare effects of sharpening and filtering using joint histograms of gradients
  *  Reference: "A new measure for the effect of sharpening and smoothing filters on images",
  *             J. Dijk, D. de Ridder, P.W. Verbeek, J. Walraven, I.T. Young, and L.J. van Vliet
  *              in: B.K. Ersboll, P. Johansen (eds.), SCIA'99, Proc. 11th Scandinavian Conference on Image Analysis
  *                  (Kangerlussuaq, Greenland, June 7-11),
  *                  Pattern Recognition Society of Denmark, Lyngby, 1999, 213-220.
  * WORK IN PROGRESS */
class CompareSmoothSharpDijk
{
public:
   /** \brief constructor
     * \param pImage1 first image to compare
     * \param pImage2 second image to compare
     * \param name identifier for identifier of comparison */
   CompareSmoothSharpDijk( image::Image* pImage1, image::Image* pImage2, std::string name );

   /** \brief destructor */
   ~CompareSmoothSharpDijk();

   /** \brief run method */
   bool Run();

private:
   image::Image* mpImage1;     ///< pointer to first image to compare
   image::Image* mpImage2;     ///< pointer to second image to compare
   
   int mWidth;          ///< width of images to compare
   int mHeight;         ///< width of images to compare
   std::string mName;   ///< name identifier for identifier of comparison
};

}
}

#endif
