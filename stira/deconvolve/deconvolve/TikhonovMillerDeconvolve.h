
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

#ifndef STIRA_DECONVOLVE_TIKHONOVMILLERDECONVOLVE_H
#define STIRA_DECONVOLVE_TIKHONOVMILLERDECONVOLVE_H

#include "../../imagedata/datastructures/Image.h"
#include "IterativeDeconvolve.h"

namespace stira{
namespace deconvolve{

/** \brief child class for computing Tikhonov-Miller deconvolution
  * Based on implementation of my thesis student Tim Stevens
  * \warning NOT OPERATIONAL YET*/
class TikhonovMillerDeconvolve: public IterativeDeconvolve
{
public:
   /** \brief constructor without setting PSF, so is still to be determined or estimated before run
     * \param pDegradedImage the input image to be restored
     * \param maxNrOfIterations maximum number of iterations */
   TikhonovMillerDeconvolve( image::Image* pDegradedImage, int maxNrOfIterations=20 );

   /** \brief constructor with setting the PSF
     * \param pDegradedImage the input image to be restored
     * \param pPSF the input PSF (needs same width and height as pDegradedImage)
     * \param maxNrOfIterations maximum number of iterations */
   TikhonovMillerDeconvolve( image::Image* pDegradedImage, image::Image* pPSF, int maxNrOfIterations=20 );

   /** \brief destructor*/
   ~TikhonovMillerDeconvolve();

   /** \brief sets the flag if positivity should be enforced after every iteration
     * If true, all negative values in the image are set to zero after every iteration*/
   void SetEnforcePositivity(bool flag);

   /** \brief gets the flag if positivity should be enforced after every iteration*/
   bool GetEnforcePositivity();

   /** \brief starts the deconvolution if all inputs are available
     * After completion, get the result with GetRestoredImage() from the parent class*/
   bool Run();

   /** \brief prints for diagnostic purposes parameters to standard output*/
   void PrintParameters();

   void ICTM_filter( int nrIterations, image::ArrayGrid<double> *pData, image::ArrayGrid<double> *pPsf );

private:

   //double TikhonovMillerDeconvolve::ComputeLambda( FFTBand* pLaplacianOperator, fftw_complex *G, fftw_complex *g)

   stira::fouriertools::FFTBand* GenerateLaplacian( int width, int height );
   /** \brief checks if all inputs are available*/
   bool IsReadyToRun();

   /** \brief runs one iteration of the deconvolution on a single band of the image*/
   bool RunSingleIterationSingleBand( );

   /** \brief applies enforcing the positivity constraint
     * \param pGrid single band of image on which to apply the constraint*/
   bool ApplyPositivityConstraint( image::ArrayGrid<double>* pGrid );

   bool mFlagEnforcePositivity;  ///< flag if positivity should be enforced after every iteration
};

}
}

#endif
