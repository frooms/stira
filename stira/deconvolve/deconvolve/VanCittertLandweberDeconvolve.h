
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

#ifndef STIRA_DECONVOLVE_VANCITTERTLANDWEBERDECONVOLVE_H
#define STIRA_DECONVOLVE_VANCITTERTLANDWEBERDECONVOLVE_H

#include "../../imagedata/datastructures/Image.h"
#include "IterativeDeconvolve.h"

namespace stira{
namespace deconvolve{

/** \brief enum value to specify deconvolution method*/
enum deconvolutionType 
{
   DECONVOLVE_VANCITTERT, ///< van cittert deconvolution
   DECONVOLVE_LANDWEBER, ///< landweber deconvolution
};

/** \brief child class for computing Van Cittert or Landweber deconvolution
  *
  * These two types of deconvolution are so closely related that we take them together
  *
  * Course study report http://www.bmi2.bmt.tue.nl/image-analysis/Education/OGO/ 
  * 2003-2004 3.2b Deblurring,  S.H.M. Allon, M.G. Debertrand, B.T.H.M. Sleutjes Report (500 KB) 
  */
class VanCittertLandweberDeconvolve: public IterativeDeconvolve
{
public:
   /** \brief constructor without setting PSF, so is still to be determined or estimated before run
     * \param pDegradedImage the input image to be restored
     * \param maxNrOfIterations maximum number of iterations */
   VanCittertLandweberDeconvolve( image::Image* pDegradedImage, int maxNrOfIterations=20 );
   
   /** \brief constructor with setting the PSF
     * \param pDegradedImage the input image to be restored
     * \param pPSF the input PSF (needs same width and height as pDegradedImage)
     * \param maxNrOfIterations maximum number of iterations */
   VanCittertLandweberDeconvolve( image::Image* pDegradedImage, image::Image* pPSF, int maxNrOfIterations=20 );
   
   /** \brief destructor*/
   ~VanCittertLandweberDeconvolve();
   
   /** \brief sets the flag if positivity should be enforced after every iteration
     * If true, all negative values in the image are set to zero after every iteration*/
   void SetEnforcePositivity(bool flag);
   
   /** \brief gets the flag if positivity should be enforced after every iteration*/
   bool GetEnforcePositivity();
   
   /** \brief sets deconvolution type*/
   deconvolutionType GetDeconvolutionType();
   
   /** \brief gets deconvolution type*/
   void SetDeconvolutionType( deconvolutionType myType );
   
   /** \brief starts the deconvolution if all inputs are available
     * After completion, get the result with GetRestoredImage() from the parent class*/
   bool Run();
   
   /** \brief prints for diagnostic purposes parameters to standard output*/
   void PrintParameters();

private:
   /** \brief checks if all inputs are available*/
   bool IsReadyToRun();

   /** \brief runs one iteration of the deconvolution on a single band of the image*/
   bool RunSingleIterationSingleBand( );
   
   /** \brief applies enforcing the positivity constraint
     * \param pGrid single band of image on which to apply the constraint*/
   bool ApplyPositivityConstraint( image::ArrayGrid<double>* pGrid );

   deconvolutionType mDeconvolutionType; ///< Regularization method 
   bool mFlagEnforcePositivity;  ///< flag if positivity should be enforced after every iteration
};

}
}

#endif
