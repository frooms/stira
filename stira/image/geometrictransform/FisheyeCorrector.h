
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
#include "../tools/BicubicInterpolator.h"

namespace stira {
namespace image {

/** \brief simple class to correct Fisheye distortion
  *  Reference: http://www.tannerhelland.com/4743/simple-algorithm-correcting-lens-distortion/ */
class FisheyeCorrector
{
public:

   /** \brief constructor */
   FisheyeCorrector( );

   /** \brief destructor */
   ~FisheyeCorrector( );

   /** \brief Generates new image by computing inverse fisheye warp
     * \param pImageIn input image to inverse warp
     * \param strength of the warping
     * \param zoom zoom to apply */
   Image* ApplyCorrect( Image* pImageIn, double strength, double zoom );

   /** \brief Inverse fisheye warps input grid
     * \param pGridIn input grid to inverse warp
     * \param pGridOut result grid in which result of inverse warp is written
     * \param strength of the warping
     * \param zoom zoom to apply */
   void ApplyCorrect( ArrayGrid<double>* pGridIn, ArrayGrid<double>* pGridOut, double strength, double zoom );

private:
   Interpolator* mpInterpolator;  ///< image intensity interpolator object

   /** \brief transform the pixel coordinate from distorted to corrected position
     * \brief x x coordinate in distorted grid for which to compute corrected position
     * \brief y y coordinate in distorted grid for which to compute corrected position, double
     * \brief halfWidth
     * \brief halfHeight
     * \brief correctionRadius
     * \brief zoom */
   common::Point<double> TransformPixel(int x, int y, double halfWidth, double halfHeight, double correctionRadius, double zoom );
};
}
}

#endif // FISHEYECORRECTOR_H
