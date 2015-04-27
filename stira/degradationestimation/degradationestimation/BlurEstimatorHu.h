
/***********************************************************************************
 *   Copyright (C) 2009 by Filip Rooms                                             *
 *                                                                                 *
 *  Terms and conditions for using this software in any form are provided in the   *
 *  file COPYING, which can be found in the root directory of this project.        *
 *                                                                                 *
 *   Contact data: filip.rooms@gmail.com                                           *
 *                 http://www.filiprooms.be/                                       *
 *                                                                                 *
 ***********************************************************************************/

#ifndef STIRA_DEGRADATIONESTIMATION_BLURESTIMATORHU_H
#define STIRA_DEGRADATIONESTIMATION_BLURESTIMATORHU_H

#include <iostream>
#include <cmath>
#include "../../image/datastructures/Image.h"

namespace stira {
namespace degradationestimation {

/** \brief A class to estimate blur (for now, only first method is implemented)
  * References: - "Low Cost Robust Blur estimator". H. Hu and G. De Haan in IEEE ICIP 2006,
  *               Oct. 8-11, 2006, Atlanta (GA), pp. 617-620.
  *             - "Adaptive Image Restoration Based on Local Robust Blur Estimation", H. Hu and G. de Haan,
  *               Proceedings of the 9th International Conference on Advanced Concepts for Intelligent Vision Systems,
  *               Volume LNCS 4678 , pp. 461-472, Springer, Aug. 2007
  *             - http://www.es.ele.tue.nl/~dehaan/
  *  \warning: to be checked; not completely functional yet...
  */
class BlurEstimatorHu{

public:

   /** \brief Constructor. */
   BlurEstimatorHu();

   /** \brief Destructor. */
   ~BlurEstimatorHu();

   /** \brief gets smallest reblur sigma value */
   double GetSigmaA();

   /** \brief sets smallest reblur sigma value
     * \param sigmaA smallest reblur sigma value */
   void SetSigmaA( double sigmaA );

   /** \brief gets largest reblur sigma value */
   double GetSigmaB();

   /** \brief sets largest reblur sigma value
     * \param sigmaB largest reblur sigma value */
   void SetSigmaB( double sigmaB );

   /** \brief gets the sigma of the blur for the given grid
     * \param pGrid the grid for which to determine the blur */
   double Run( image::ArrayGrid<double>* pGrid );

private:
   double mSigmaA; ///< smallest reblur sigma value
   double mSigmaB; ///< largest reblur sigma value

};
}
}

#endif
