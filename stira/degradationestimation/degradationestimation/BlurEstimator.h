
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

#ifndef STIRA_DEGRADATIONESTIMATION_BLURESTIMATOR_H
#define STIRA_DEGRADATIONESTIMATION_BLURESTIMATOR_H

#include <iostream>
#include <cmath>
#include "../../imagedata/datastructures/Image.h"

namespace stira {
namespace degradationestimation {

/** \brief A class to estimate blur by searching a range of blur values and selecting the one with the best gradient kurtosis
  * References: - "Blur Identification based on Kurtosis Minimization". D. Li, R. Mersereau and S. Simsk in IEEE ICIP2005.
  *             - "Parametric PSF estimation via sparseness maximization in the wavelet domain", F. Rooms, W. Philips and J. Portilla, 
  *                SPIE "Wavelet Applications in Industrial Processing II" 2004, Philadelphia, pp. 26--33
  */
class BlurEstimator{

public:

   /** \brief Constructor. */
   BlurEstimator();

   /** \brief Destructor. */
   ~BlurEstimator();

   /** \brief gets the sigma of the blur for the given grid 
     * \param pGrid the grid for which to determine the blur */
   double Run( image::ArrayGrid<double>* pGrid );

   /** \brief Gets the underlimit of the search range in which to search the blur*/
   double GetBlurUnderLimit();
   
   /** \brief Sets the underlimit of the search range in which to search the blur
     * \param underLimit the underlimit of the search range */
   void SetBlurUnderLimit( double underLimit );

   /** \brief Gets the upperlimit of the search range in which to search the blur*/
   double GetBlurUpperLimit();
   
   /** \brief Sets the upperlimit of the search range in which to search the blur
     * \param upperLimit the upperlimit of the search range */
   void SetBlurUpperLimit( double upperLimit );

   /** \brief gets the step size with which to search the search range*/
   double GetStepSize();
   
   /** \brief sets the step size with which to search the search range
     * \param stepSize the step size */
   void SetStepSize( double stepSize );
   
   /** \brief gets the level of noise in the input grid 
     * In our case, we assume this is the sigma of white Gaussian noise*/
   double GetNoiseLevel();
   
   /** \brief Sets the level of noise in the input grid 
     * In our case, we assume this is the sigma of white Gaussian noise
     * \param noiseLevel the level of noise in the input grid*/
   void SetNoiseLevel( double noiseLevel );

private:

   double mBlurUnderLimit; ///< the underlimit of the search range in which to search the blur
   double mBlurUpperLimit; ///< the upperlimit of the search range in which to search the blur
   double mActualBlur; ///< will hold the actually found image blur 
   double mStepSize; ///< the step size
   double mNoiseLevel; ///<the level of noise in the input grid

};
}
}

#endif
