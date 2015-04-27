
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

#ifndef STIRA_IMAGEANALYSIS_STEGERLINEDETECTOR_H
#define STIRA_IMAGEANALYSIS_STEGERLINEDETECTOR_H

#include <iostream>
#include "../../image/datastructures/Image.h"
#include "../../common/common/Point.h"

namespace stira {
namespace imageanalysis {
   
/** \brief Steger line detector  
  * article{ steger98line,
  *       author  = {Steger, C.},
  *       title   = {An unbiased detector of curvilinear structures},
  *       journal = {IEEE Trans. Pattern Analysis and Machine Intelligence},
  *       volume  = {20},
  *       number  = {2},
  *       pages   = {113--125},
  *       month   = {February},
  *       year    = {1998}
  *     }
  *
  * Remark: performs line detection up to the point where line candidates are detected; 
  *         line linking is not implemented.
  *
  */
class StegerLineDetector
{
public:
   
   /** \brief Constructor. */
   StegerLineDetector();
   
   /** \brief Destructor. */
   ~StegerLineDetector();
   
   /** \brief run method 
     * 
     * \param pGridIn input data grid
     * \param sigmaSmooth sigma used for smoothing
     * \param lowerThreshold lower threshold for line linking hysteresis
     * \param higherThreshold higher threshold for line linking hysteresis
     * \param isModeLight true for bright lines on dark background; false for dark lines on a bright background
     * \return grid where lines have value true and background has value false
     */
   image::ArrayGrid<bool>* Run( image::ArrayGrid<double>* pGridIn, double sigmaSmooth, double lowerThreshold, double higherThreshold, bool isModeLight );

private:
   /** \brief solves eigenvalues of symmetrical matrix
     *
     * Matrix is of form [ App  Apq ]
     *                   [ Apq  Aqq ]
     *
     * Algorithm described in Numerical Recipes in C, Second Edition (1992) Chapter 11 "Eigensystems" 
     * Section 11.1 Jacobi Transformations of a Symmetric Matrix
     * \param App input matrix element
     * \param Aqq input matrix element
     * \param Apq input matrix element
     * \param outEigenValue1 output: largest eigenvalue (in absolute value)
     * \param outEigenValue2 output: smallest eigenvalue (in absolute value)
     * \param outEigenVector1 output: normalized eigenvector corresponding to outEigenValue1
     * \param outEigenVector2 output: normalized eigenvector corresponding to outEigenValue2*/
   bool EigenValueComputation( double App, double Aqq, double Apq, 
                               double& outEigenValue1, double& outEigenValue2, 
                               common::Point<double>& outEigenVector1, common::Point<double>& outEigenVector2);
};

}
}
#endif
