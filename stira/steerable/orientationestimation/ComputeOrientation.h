
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
 
#ifndef STIRA_STEERABLE_ORIENTATIONESTIMATION_COMPUTEORIENTATION_H
#define STIRA_STEERABLE_ORIENTATIONESTIMATION_COMPUTEORIENTATION_H

#include <stdint.h>
#include <iostream>
#include <cmath>
#include "../../imagedata/color/ColorValue.h"
#include "../../imagedata/datastructures/Image.h"
#include "../../imagedata/datastructures/PyramidLevel.h"
#include "../../imagedata/datastructures/OrientationGrid.h"

namespace stira {
namespace steerable {

using namespace imagedata;

/** \brief A class to compute local orientation in an image */
class ComputeOrientation{
public:

   /** \brief Constructor. */
   ComputeOrientation();

   /** \brief Destructor. */
   ~ComputeOrientation();

   /** \brief assigns for visualization a color triplet to an angle
     * This mapping happens based on the HSV coilor space, where mapping an angle 
     * theta to color is implicit (when letting H vary and keeping S and V fixed to 1). 
     * This HSV color is then converted to an RGB triplet*/
   static ColorValue ConvertAngleToHSVMap(double angle);
   
   /** \brief assigns for visualization a color triplet to an angle
     * This mapping is a simple interpolation between the RGB primaries between 0 and pi*/
   static ColorValue ConvertAngleToRGBMap(double angle);

   /** \brief computes dominant orientation with separable steerable filters as described by from Freeman and Adelson:
     *
     * W. T. Freeman and E. H. Adelson, The design and use of steerable filters,
     * IEEE Trans. on Pattern Analysis and Machine Intelligence, vol. 13, no. 9, pp. 891 - 906, Sept. 1991.
     * also available as technical report from http://people.csail.mit.edu/billf/steerpaper.html
     *
     * Creates a new image object that becomes the responsability of the caller to delete
     * 
     * These filters form a quadrature pair: The H's are the odd filters and the G's are the even filters
     * 
     * \param pResponseH2a first odd separable steerable basis filter
     * \param pResponseH2b second odd separable steerable basis filter
     * \param pResponseH2c third odd separable steerable basis filter
     * \param pResponseH2d fourth odd separable steerable basis filter
     * \param pResponseG2a first even separable steerable basis filter
     * \param pResponseG2b second even separable steerable basis filter
     * \param pResponseG2c third even separable steerable basis filter
     * \return Grid containing local orientations and edge strengths */
   static OrientationGrid* ComputeDominantOrientationInputFreemanAdelson(
                      ArrayGrid<double>* pResponseH2a,
                      ArrayGrid<double>* pResponseH2b,
                      ArrayGrid<double>* pResponseH2c,
                      ArrayGrid<double>* pResponseH2d,
                      ArrayGrid<double>* pResponseG2a,
                      ArrayGrid<double>* pResponseG2b,
                      ArrayGrid<double>* pResponseG2c);

   /** \brief computes dominant orientation with resonse bands from a single level of the conmplex steerable pyramid
     * 
     * The relations have been computed analytically for the case of 4 orientations; other numbers of orientations 
     * are currently not available.
     * 
     * \param pPyrLevel one level of the complex steerable pyramid
     * \return Grid containing local orientations and edge strengths */
   static OrientationGrid* ComputeDominantOrientationInputComplexPyramidLevel( PyramidLevel< std::complex<double> >* pPyrLevel);
};

}
}
#endif
