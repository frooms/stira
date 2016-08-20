
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

#ifndef STIRA_FILTER_NONSEPARABLEFILTER_H
#define STIRA_FILTER_NONSEPARABLEFILTER_H

#include <stdint.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "../../imagedata/datastructures/Image.h"
#include "../../imagedata/datastructures/OrientationGrid.h"

namespace stira {
namespace filter {

using namespace imagedata;

/** \brief Filters an image using a non-separable filter kernel */
class NonSeparableFilter
{
public:
   
   /** \brief Constructor. */
   NonSeparableFilter();
   
   /** \brief Destructor. */
   ~NonSeparableFilter();
     
   /** \brief filters single band in image with 2D non-separable filter kernel
     * \param pInput input data
     * \param filterKernel filter kernel in lexicographical order (all rows after each other)
     * \param filterWidth  width of kernel
     * \param filterHeight  height of kernel
     * \return filtered grid */
   static ArrayGrid<double>* Run( ArrayGrid<double>* pInput, double *filterKernel, int filterWidth, int filterHeight);
     
   /** \brief filters single band in image with Sobel X filter kernel
     * \param pInput input data
     * \return filtered grid */
   static ArrayGrid<double>* RunSobelX( ArrayGrid<double>* pInput);
     
   /** \brief filters single band in image with Sobel Y filter kernel
     * \param pInput input data
     * \return filtered grid */
   static ArrayGrid<double>* RunSobelY( ArrayGrid<double>* pInput);
     
   /** \brief filters single band in image with Sobel X filter kernel
     * \param pInput input data
     * \return filtered grid */
   static Image* RunSobelX( Image* pInput);
     
   /** \brief filters single band in image with Sobel Y filter kernel
     * \param pInput input data
     * \return filtered grid */
   static Image* RunSobelY( Image* pInput);
   
   /** \brief Computes a grid with the local orientation and edge strength based on the Sobel (X and Y direction) filters
     * \param pGridIn input image
     * \return grid containing local edge strengths and edge magnitudes */
   static OrientationGrid* DetermineLocalMagnitudeAndOrientation( ArrayGrid<double>* pGridIn );

   /** \brief Creates and returns a sobel filter kernel for x direction
     * \warning caller becomes responsible; clean up after usage!!*/
   static double* GetSobelXKernel();
   
   /** \brief Creates and returns a sobel filter kernel for y direction
     * \warning caller becomes responsible; clean up after usage!!*/
   static double* GetSobelYKernel();
};

}
}

#endif
