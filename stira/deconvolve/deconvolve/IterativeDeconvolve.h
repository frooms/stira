
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

#ifndef STIRA_DECONVOLVE_ITERATIVEDECONVOLVE_H
#define STIRA_DECONVOLVE_ITERATIVEDECONVOLVE_H

#include "../../imagedata/datastructures/Image.h"
#include "../../fouriertools/fouriertools/FFTBand.h"
#include "DeconvolveMaster.h"

namespace stira{
namespace deconvolve{


/** \brief enum value to specify regularization method*/
enum regularizationType 
{
   REGULARIZE_NONE, ///< no regularization
   REGULARIZE_TIKHONOV_MILLER,  ///< Tikhonov-Miller regularization
   REGULARIZE_CONCHELLO, ///< Conchello regularization
   REGULARIZE_MAXIMUM_ENTROPY, ///< Maximum Entropy regularization
   REGULARIZE_TOTAL_VARIATION///< Total Variation regularization
};


/** \brief parent class for computing iterative deconvolution schemes */
class IterativeDeconvolve: public DeconvolveMaster
{
public:
   /** \brief sets regularization parameter lambda*/
   void SetLambda(double lambda);
   
   /** \brief gets regularization parameter lambda*/
   double GetLambda();
   
   /** \brief sets step size*/
   void SetStepSize(double stepSize);
   
   /** \brief gets step size*/
   double GetStepSize();

   /** \brief gets the maximum number of iterations */
   int GetMaximumNrOfIterations();

   /** \brief sets the maximum number of iterations 
     * \param nrIter the maximum number of iterations */
   void SetMaximumNrOfIterations( int nrIter);

protected:
   /** \brief constructor 
     * Protected constructor; should be called by a child class
     * \param pDegradedImage the degraded input image for restoration
     * \param maxNrOfIterations the maximum number of iterations*/
   IterativeDeconvolve( image::Image* pDegradedImage, int maxNrOfIterations=20 );
   
   /** \brief constructor
     * Protected constructor; should be called by a child class
     * \param pDegradedImage the degraded input image for restoration
     * \param pPSF the Point Spread Function
     * \param maxNrOfIterations the maximum number of iterations*/
   IterativeDeconvolve( image::Image* pDegradedImage, image::Image* pPSF, int maxNrOfIterations=20 );
   
   /** \brief destructor*/
   ~IterativeDeconvolve();
   
   /** \brief initializes all data structures for deconvolution*/
   void Initialize( int maxNrOfIterations );

   /** \brief Prepares grid for restoration
     * Restoration goes per colour band per iteration, so for each step, 
     * the pointers mpDegradedGrid, mpLastGrid, mpNewGrid, mpPSFGrid are set here*/
   bool PrepareCurrentGrids( );

   /** \brief Runs a single iteration on a single colour band of the image 
     * Implemented in the child classes*/
   virtual bool RunSingleIterationSingleBand( )=0;

   image::Image* mpLastEstimate; ///< pointer to the restored image from previous iteration
   image::Image* mpNewEstimate; ///< pointer to the restored image from current iteration
   
   double mLambda;  ///< Regularization parameter
   double mStepSize;  ///< Step size
   int mCurrentIterationNr; ///< number of the current iteration
   int mCurrentBandNr; ///< number of the current band being retsored
   int mMaximumNrOfIterations;  ///< maximum number of iterations

   // intermediate pointers, not to be deleted
   image::ArrayGrid<double>* mpDegradedGrid;   ///< pointer to a band of the degraded image
   image::ArrayGrid<double>* mpLastGrid;   ///< pointer to a band of the restored image from previous iteration
   image::ArrayGrid<double>* mpNewGrid;   ///< pointer to a band of the restored image from current iteration
   image::ArrayGrid<double>* mpPSFGrid;   ///< pointer to a band of the Point Spread Function
};

}
}
#endif
