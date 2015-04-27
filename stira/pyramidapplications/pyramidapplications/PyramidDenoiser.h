
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

#ifndef STIRA_PYRAMIDAPPLICATIONS_PYRAMIDDENOISER_H
#define STIRA_PYRAMIDAPPLICATIONS_PYRAMIDDENOISER_H

#include <vector>

#include "../../image/datastructures/Pyramid.h"

namespace stira {
namespace pyramidapplications {
   
enum ShrinkageRule{WIENER, LAPLACIAN, BIVARIATE};
   
/** \brief A class to demonstrate simple denoising of the bands of a steerable pyramid
  * Reference: "Bivariate Shrinkage Functions for Wavelet-based Image Denoising", Sendur, L. and Selesnick, I., 
  *             IEEE Transactions on Signal Processing, 50(11):2744-2756, November 2002.
  *
  *          - Wiener    : p2746 formula (10)
  *          - Laplacian : p2746 formula (12)
  *          - Bivariate : p2748 formula (30)
  *
  *   URL: http://taco.poly.edu/selesi/bishrink/index.html
  */
class PyramidDenoiser
{
   public:

      /** \brief Constructor
        *
        * \param pPyramid a steerable pyramid to be denoised
        * \param myRule shrinkage rule to apply to the coefficients
        * \param sigma sigma of the noise
        */
      PyramidDenoiser( image::Pyramid<double>* pPyramid, ShrinkageRule myRule, double sigma);

      /** \brief Destructor. */
      ~PyramidDenoiser();
      
      /** \brief Gets the sigma of the noise */
      double GetSigmaNoise();
      
      /** \brief Sets the sigma of the noise 
        * \param sigmaNoise sigma of the noise to set*/
      void SetSigmaNoise(double sigmaNoise);
      
      /** \brief gets scaling factor between coefficients magnitude in residual scale versus spatial domain
        * Specifically to scale noise std deviation in spatial domain and residual level*/
      double GetScaleFactorResidualLevel();
      
      /** \brief sets scaling factor between coefficients magnitude in residual scale versus spatial domain
        * \param factor factor to set */
      void SetScaleFactorResidualLevel( double factor );
      
      /** \brief gets scaling factor between coefficients magnitude in residual scale versus first recursive scale */
      double GetScaleFactorResidualToRecursiveLevel();
      
      /** \brief sets scaling factor between coefficients magnitude in residual scale versus first recursive scale
        * \param factor factor to set  */
      void SetScaleFactorResidualToRecursiveLevel( double factor );
      
      /** \brief gets scaling factor between coefficients magnitude in two successice recursive scales */
      double GetScaleFactorRecursiveLevel();
      
      /** \brief gets scaling factor between coefficients magnitude in two successice recursive scales 
        * \param factor factor to set */
      void SetScaleFactorRecursiveLevel( double factor );
      
      /** \brief Runs the denoising algorithm */
      void Run();

      /** \brief Computes the shrinkage factor for the wavelet coefficients using the bivariate rule 
        * \param w1 coefficient in current subband
        * \param w2 coefficient that corresponds with w1 in its parent scale
        * \param sigmaSignal estimated standard deviation of the local signal in a neighbourhood of w1 (only same band)
        * \param sigmaNoise noise level (is not exactly sigma of the noise in case of steerable pyramids)*/
      static double ComputeBivariateShrinkagefactor(double w1, double w2, double sigmaSignal, double sigmaNoise);

      /** \brief Computes the shrinkage factor for the wavelet coefficients using the Wiener rule 
        * \param sigmaSignal estimated standard deviation of the local signal in a neighbourhood of w1 (only same band)
        * \param sigmaNoise noise level (is not exactly sigma of the noise in case of steerable pyramids)*/
      static double ComputeWienerShrinkagefactor( double sigmaSignal, double sigmaNoise );

      /** \brief Computes the shrinkage factor for the wavelet coefficients using the Laplacian rule 
        * \param w1 coefficient in current subband
        * \param sigmaSignal estimated standard deviation of the local signal in a neighbourhood of w1 (only same band)
        * \param sigmaNoise noise level (is not exactly sigma of the noise in case of steerable pyramids)*/
      static double ComputeLaplacianShrinkagefactor(double w1, double sigmaSignal, double sigmaNoise);

      /** \brief Estimates the standard deviation of the signal in a given band around a given pixel (window size specified as a member variable) 
        * \param pBand the band in which to estimate the local variance
        * \param xCenter x coordinate of center pixel of the local window in which to estimate the local variance
        * \param yCenter y coordinate of center pixel of the local window in which to estimate the local variance
        * \param sigmaNoise sigma of the noise*/
      static double EstimateSigmaSignal( image::ArrayGrid<double>* pBand, int xCenter, int yCenter, double sigmaNoise, int windowSize);
      
   private:
      
      /** \brief gets the factor with which the noise variance is scaled at given level
        * \param level the given level*/
      double GetScaledNoiseVarianceFactor(int level);
      
      /** \brief gets the factor with which the parent needs to be scaled with respect to the child
        * \param level the given level for the child*/
      double GetScaledParentChildFactor(int level);
      
      /** \brief denoises level <code>level</code> of the pyramid (Generic)
        * \param level the number of the level to denoise */
      void DenoiseLevel(int level);
      
      /** \brief denoises level <code>level</code> of the pyramid (Wiener)
        * \param level the number of the level to denoise */
      void DenoiseLevelWiener(int level);
      
      /** \brief denoises level <code>level</code> of the pyramid (Laplacian)
        * \param level the number of the level to denoise */
       void DenoiseLevelLaplacian(int level);
      
      /** \brief denoises level <code>level</code> of the pyramid (Bivariate)
        * \param level the number of the level to denoise */
      void DenoiseLevelBivariate(int level);

      int mFinestDenoisingLevel;
      int mWindowSize;  ///< window size to determine the local variance of the wavelet coefficients in a subband 
      int mWindowHalfSize; ///< half of the window size to determine the local variance of the wavelet coefficients in a subband 
      double mSigmaNoise; ///< sigma of the noise
      
      ShrinkageRule mShrinkageRule;   ///< enum to define which shrinkage rule to apply
      
      double mScaleFactorResidualLevel;  ///< scale factor normal noise variance in spatial domain and in recursive level
      double mScaleFactorResidualToRecursiveLevel;  ///< scale factor coefficients between residual and first recursive level
      double mScaleFactorRecursiveLevel;  ///< scale factor coefficients between two successive recursive levels
      
      image::Pyramid<double>* mpPyramid;   ///< pointer to the pyramid to denoise
};
}
}
#endif
