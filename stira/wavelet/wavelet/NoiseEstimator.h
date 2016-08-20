
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

#ifndef STIRA_WAVELET_NOISEESTIMATOR_H
#define STIRA_WAVELET_NOISEESTIMATOR_H

#include <iostream>
#include <cmath>
#include "../../imagedata/datastructures/Image.h"

namespace stira {
namespace wavelet {

using namespace imagedata;

/** \brief A class to estimate sigma for white noise with the Mean Absolute Deviation method of Donoho 
  * References: - "Ideal spatial adaptation by wavelet shrinkage", D. Donoho and I. Johnstone, Biometrika,
  *                1994, vol. 81, pp. 425--455 (relevant section is on 17th page of the paper, just above section 4.3)
  *             - "Image Denoising Using Wavelets and Spatial Context Modeling", A. Pizurica, 
  *                Ph.D. thesis, Ghent University 2002 (relevant section on page 27) 
  */
class NoiseEstimator{

public:

   /** \brief Constructor. */
   NoiseEstimator();

   /** \brief Destructor. */
   ~NoiseEstimator();

   /** \brief gets the sigma of the noise for the given grid 
     * \param pGrid the grid for which to determine the noise */
   static double Run( ArrayGrid<double>* pGrid );

private:
   /** \brief gets the median value for the given grid 
     * In this noise estimation, this grid is the HH band of the finest scale of the (Haar) wavelet 
     * decomposition of the grid that was passed to the run method of this class
     * \param pGrid the grid for which to determine the noise */
   static double GetMedianValue( ArrayGrid<double>* pGrid );
};
}
}

#endif
