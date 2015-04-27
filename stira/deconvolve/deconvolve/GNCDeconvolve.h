
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

#ifndef STIRA_DECONVOLVE_GNCDECONVOLVE_H
#define STIRA_DECONVOLVE_GNCDECONVOLVE_H

#include "../../common/common/Point.h"

#include "../../image/datastructures/Pyramid.h"
#include "IterativeDeconvolve.h"
#include "../../steerable/pyramid/PyramidReal.h"

namespace stira{
namespace deconvolve{

/** \brief child class for computing GNC-based image deconvolution
  * GNC stands for Graduated Non Convexity, related stuff to markov 
  * random fields
  *
  * See my own PhD thesis
  * WORK IN PROGRESS: re-implementing code from ~/bin/fft/fftw215/gnc2
  *
  * Inspired on PhD thesis Sanja page 62
  *
  */
class GNCDeconvolve: public IterativeDeconvolve
{
public:
   /** \brief constructor without setting PSF, so is still to be determined before run
     * \param pDegradedImage the input image to be restored
     * \param maxNrOfIterations maximum number of iterations */
   GNCDeconvolve( image::Image* pDegradedImage, int maxNrOfIterations=20 );
   
   /** \brief constructor with PSF
     * \param pDegradedImage the input image to be restored
     * \param pPSF the input PSF (needs same width and height as pDegradedImage)
     * \param maxNrOfIterations maximum number of iterations */
   GNCDeconvolve( image::Image* pDegradedImage, image::Image* pPSF, int maxNrOfIterations=20 );
   
   /** \brief destructor*/
   ~GNCDeconvolve();
   
   /** \brief starts the deconvolution if all inputs are available
     * After completion, get the result with GetRestoredImage() from the parent class*/
   bool Run();
   
   /** \brief prints for diagnostic purposes parameters to standard output*/
   void PrintParameters();
   
   /** \brief prints for diagnostic purposes parameters to standard output*/
   void InitializeParameters();
   
   /** \brief gets the number of scales in the multiscale restoration*/
   int GetNumberOfScales();
   
   /** \brief sets the number of scales in the multiscale restoration
     * \param nrScales the number of scales */
   void SetNumberOfScales(int nrScales);
   
   /** \brief gets the number of orientations per scale in the multiscale restoration*/
   int GetNumberOfOrientations();
   
   /** \brief sets the number of orientations per scale in the multiscale restoration
     * \param nrOrientations the number of orientations per scale */
   void SetNumberOfOrientations(int nrOrientations);
   
   /** \brief gets mu (scaling factor for data fitting) */
   double GetMu();
   
   /** \brief sets mu (scaling factor for data fitting)
     * \param newMu new value for mu to set*/
   void SetMu(double newMu);
   
   /** \brief gets lambda (scaling factor for regularization)*/
   double GetLambda();
   
   /** \brief sets lambda (scaling factor for regularization)
     * \param newLambda new value for lambda to set*/
   void SetLambda(double newLambda);
   
   /** \brief Gets value for gamma
     * This parameter controls the amount of convexity of the cost function and is updated when iterations converge*/
   double GetGamma();
   
   /** \brief Sets value for gamma
     * \param newGamma new value for gamma to set*/
   void SetGamma(double newGamma );
   
   /** \brief Gets value for final value of gamma*/
   double GetGammaFinal();
   
   /** \brief Sets value for final value of gamma
     * \param newGammaFinal new value for final gamma to set*/
   void SetGammaFinal(double newGammaFinal);
   
   /** \brief Gets the update factor 
     * Parameter gamma controls the amount of convexity; when the iterations converge 
     * for a given gamma, gamma is multiplied with this factor and the computations are resumed.*/
   double GetUpdateFactor();
   
   /** \brief Gets the update factor 
     * Parameter gamma controls the amount of convexity; when the iterations converge 
     * for a given gamma, gamma is multiplied with this factor and the computations are resumed.
     * \param newFactor new value for the update factor*/
   void SetUpdateFactor(double newFactor);
   
   /** \brief sets threshold for MSE (Mean Square error) under which the iterations are stopped. 
     * \param myThreshold new value of the threshold to set */
   void SetMSEDifferenceThreshold( double myThreshold );
   
   /** \brief gets threshold for MSE (Mean Square error) under which the iterations are stopped. */
   double GetMSEDifferenceThreshold();
   
private:
   /** \brief checks if another iteration is needed
     * for this, we check if the difference in MSE in last and previous iteration is still above a threshold, and 
     * if the max nr of iterations hasn't been reached yet
     * \param previousMSE MSE in previous iteration
     * \param currentMSE MSE in last iteration
     * \param currentIteration nr of the last iteration*/
   bool NeedsAnotherIteration( double previousMSE, double currentMSE, int currentIteration );
   
   /** \brief runs a single iteration on a single color band of the image*/
   virtual bool RunSingleIterationSingleBand( );
   
   /** \brief prepares data for the first iteration*/
   void PrepareDataForInitialIteration();
   
   /** \brief prepares data for recursive iterations */
   void PrepareDataForRecursiveIteration();

   /** \brief runs a single iteration on a single color band of the image*/
   void PrepareCurrentSubbandsForIteration();
   
   /** \brief computes the function value for the adaptive interaction function (called h)
     * \param x the function argument */
   double ComputeInteractionFunction( double x );
   
   /** \brief gets an indicator of the local spatial activity in this band and position
     * We compute the factor for bivariate shrinkage according to Sendur and Selesnick; if it is 
     * close to 1, we have significant image structures to preserve and we will give more weight to 
     * the data fitting term; if it is close to zero, it is more likely to be due to noise and we give 
     * more weight to the regularization */
   double ComputeActivityIndicator( int x, int y );
   
   /** \brief gets the potential contribution in a given band
     * The contribution is between a coefficient at a given position (x, y) and a neighbour that is delta away from it
     * \param x x coordinate of reference coefficient
     * \param y y coordinate of reference coefficient
     * \param delta difference in coordinates for neighbour (delta.GetX() and delta.GetY() are typically -1,0,1 */
   double GetPotential(int x, int y, common::Point<int> delta);

   /** \brief checks if all inputs are available*/
   bool IsReadyToRun();

   /** \brief processes for a single scale a single oriented subband */
   void GNCStep( );
   
   double GetNeighborhoodPotential( int x, int y );
   
   double GetUpdatedCoefficient( int x, int y, double activityIndex, double totalPotential );
   
   image::ArrayGrid<double>* mpNewSolutionGrid;  ///< current oriented band of the degraded source data
   
   double mMu;
   double mLambda;
   double mUpdateFactor;
   double mMSEDifferenceThreshold;   ///< minimum difference in MSE between two iterations to continue
   
   double mGamma;   ///< Current value of gamma; decreases to mGammaFinal
   double mGammaFinal;  ///< Final and also minimal of gamma
   
   int mNumberOfScales; ///< the number of scales
   int mNumberOfOrientations; ///< the number of orientations per scale
   int mSubsampleFactor; ///< Factor to compute position of parent coefficient for next scale
   
   int mCurrentScaleNr; ///< number of the scale currently being processed
   int mCurrentOrientationNr;  ///< number of the orientation currently being processed
   
   image::ArrayGrid<double>* mpBlurredLastEstimateGrid;  ///< blurred version of
   
   steerable::PyramidReal* mpDegradedPyramid;  ///< pyramid of the original degraded source data
   steerable::PyramidReal* mpLastEstimatePyramid;  ///< pyramid of the restored result from last iteration
   steerable::PyramidReal* mpBlurredLastEstimatePyramid; ///< pyramid of the blurred restored result from last iteration
   steerable::PyramidReal* mpNewEstimatePyramid;   ///< pyramid of the restored result from the current iteration
   
   image::ArrayGrid<double>* mpDegradedCurrentBand;  ///< current oriented band of the degraded source data
   image::ArrayGrid<double>* mpLastEstimateCurrentBand;  ///< current oriented band of the restored result from last iteration
   image::ArrayGrid<double>* mpLastEstimateCurrentParentBand; ///< parent band of current oriented band of the restored result from last iteration
   image::ArrayGrid<double>* mpBlurredLastEstimateCurrentBand; ///< current oriented band of the blurred restored result from last iteration
   image::ArrayGrid<double>* mpNewEstimateCurrentBand; ///<  current oriented band of the restored result from the current iteration
   
};

}
}

#endif
