
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

#ifndef STIRA_DIFFUSION_ANISOTROPICDIFFUSION_H
#define STIRA_DIFFUSION_ANISOTROPICDIFFUSION_H

#include <stdint.h>
#include <iostream>
#include <cmath>
#include "../../image/datastructures/Image.h"

namespace stira {
namespace diffusion {

/** \brief A class to compute anisotropic diffusion 
  * for more info, see http://www.cs.sfu.ca/~stella/papers/blairthesis/main/node22.html*/
class AnisotropicDiffusion{
public:

   /** \brief Constructor. 
    *  A clone is made of the source image, which is returned after processing, leaving the source data intact
    *  The returned object becomes the responsability of the caller to delete
    *  \param pSourceImage source image on which to perform the diffusion
    */
   AnisotropicDiffusion(image::Image* pSourceImage);

   /** \brief Destructor. */
   ~AnisotropicDiffusion();

   /** \brief sets the flow constant, that regulates the strength of the diffusion
     * \param fc the constant to set */
   void SetFlowFactor(double fc);

   /** \brief gets the flow constant, that regulates the strength of the diffusion */
   double GetFlowFactor();

   /** \brief sets the maximum number of iterations
     * \param maxnr the maximum number of iterations */
   void SetMaxNumberOfIterations( int maxnr);
   
   /** \brief gets the maximum number of iterations */
   int GetMaxNumberOfIterations();

   /** \brief the run method of the object */
   image::Image* Run();

private:
   
   /** \brief to control the strength of the diffusion, determine the mean gradient in the grid 
     * \param pGrid input grid for which to determine the mean gradient */
   double DetermineMeanGradient( image::ArrayGrid<double>* pGrid);
   
   image::Image* mpSourceImage;   ///< source data grid
   double mFlowFactor;               ///< diffusion flow factor
   int mMaxNumberOfIterations;    ///< the maximum number of iterations

};
}
}
#endif
