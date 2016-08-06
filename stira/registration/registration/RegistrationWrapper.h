
/***********************************************************************************
 *   Copyright (C) 2008 by Filip Rooms                                             *
 *                                                                                 *
 *  Terms and conditions for using this software in any form are provided in the   *
 *  file COPYING, which can be found in the root directory of this project.        *
 *                                                                                 *
 *  C++ Wrapper for Intramodal registration software from Philippe Thévenaz        *
 *           http://bigwww.epfl.ch/thevenaz/registration/                          *
 *                                                                                 *
 *    It is an automatic sub-pixel registration algorithm that minimizes the       *
 *    mean square difference of intensities between a reference and a test data    *
 *    set, which can be either tri-dimensional (3-D) volumes or bi-dimensional     *
 *    (2-D) images. It uses spline processing, is based on a coarse-to-fine        *
 *    strategy (pyramid approach), and performs minimization according to a new    *
 *    variation of the iterative Marquardt-Levenberg algorithm for non-linear      *
 *    least-square optimization (MLA).                                             *
 *                                                                                 *
 *   Contact data: filip.rooms@gmail.com                                           *
 *                 http://www.filiprooms.be/                                       *
 *                                                                                 *
 ***********************************************************************************/

#ifndef STIRA_REGISTRATION_REGISTRATIONWRAPPER_H
#define STIRA_REGISTRATION_REGISTRATIONWRAPPER_H

#include "../../imagedata/datastructures/ArrayGrid.h"
#include "../../imagetools/geometrictransform/AffineTransform.h"
#include "register.h"

namespace stira {
namespace registration {

/** \brief C++ Wrapper for Intramodal registration software from Philippe Thévenaz
  * http://bigwww.epfl.ch/thevenaz/registration/ */
class RegistrationWrapper
{
public:
   /** \brief constructor
     * \param pMasterGrid the reference grid that stays fixed
     * \param pSlaveGrid the grid to be registered, is transformed */
   RegistrationWrapper( image::ArrayGrid<double>* pMasterGrid, image::ArrayGrid<double>* pSlaveGrid );

   /** \brief destructor */
   ~RegistrationWrapper();

   /** \brief Runs the actual image registration */
   bool Run();

   /** \brief gets pointer to the registered slave grid */
   image::ArrayGrid<double>* GetRegisteredGrid();

   /** \brief gets the transform as computed by the registration process */
   image::AffineTransform* GetResultingTransform( );

   /** \brief Prints the parameters of the found transform in a console on standard output*/
   void PrintTransform( );

private:
   bool mIsReadyToRun;  ///< flag if all parameters are set to be able to run

   image::AffineTransform* mpResultingTransform;  ///< object to store the final transform

   /** \brief helper method to create an ArrayGrid from an array of floats
     * \param pArray array of floats to create grid from
     * \param width width of the grid to create
     * \param height height of the grid to create*/
   image::ArrayGrid<double>* CreateGridFromArray( float* pArray, int width, int height );

   /** \brief helper method to create an array of floats from an ArrayGrid
     * \param pArray grid to create array of floats from*/
   float* CreateArrayFromGrid( image::ArrayGrid<double>* pGridIn );

   /** \brief sets all initial parameters before registration
     * \param width width of the grid to create
     * \param height height of the grid to create
     * \param pMasterArray array of floats that serves as master data (not to be transformed)
     * \param pSlaveArray array of floats that serves as slaver data (to be transformed to fit with master data) */
   void Initialize2D( int width, int height, float* pMasterArray, float* pSlaveArray );

   rParam mRegistrationParameters;  ///< struct containing all initial parameter settings before registration can start
};

}
}

#endif
