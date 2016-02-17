
/***********************************************************************************
 *   Copyright (C) 2016 by Filip Rooms                                             *
 *                                                                                 *
 *  Terms and conditions for using this software in any form are provided in the   *
 *  file COPYING, which can be found in the root directory of this project.        *
 *                                                                                 *
 *   Contact data: filip.rooms@gmail.com                                           *
 *                 http://www.filiprooms.be/                                       *
 *                                                                                 *
 ***********************************************************************************/

#ifndef STIRA_IMAGE_GEOMETRICTRANSFORM_FISHEYECORRECTOR_H
#define STIRA_IMAGE_GEOMETRICTRANSFORM_FISHEYECORRECTOR_H

#include "../datastructures/Image.h"
#include "../../common/common/Point.h"
#include "../tools/BilinearInterpolator.h"

namespace stira {
namespace image {

// http://www.tannerhelland.com/4743/simple-algorithm-correcting-lens-distortion/
class FisheyeCorrector
{
public:

   /** \brief constructor */
   FisheyeCorrector( );

   /** \brief destructor */
   ~FisheyeCorrector( );

   /** \brief Generates new image by rotating pImageIn around its center over an angle theta
     * \param pImageIn input image to rotate
     * \param theta angle over which to rotate the image */
   Image* ApplyCorrect( Image* pImageIn, double strength, double zoom );

   /** \brief Generates new grid by rotating pGridIn around its center over an angle theta
     * \param pGridIn input grid to rotate
     * \param theta angle over which to rotate the grid */
   ArrayGrid<double>* ApplyCorrect( ArrayGrid<double>* pGridIn, double strength, double zoom );

private:
   BilinearInterpolator* mpInterpolator;
   common::Point<double> TransformPixel(int x, int y, double halfWidth, double halfHeight, double correctionRadius, double zoom );
};
}
}

#endif // FISHEYECORRECTOR_H
