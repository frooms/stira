
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

#ifndef STIRA_PYRAMIDAPPLICATIONS_PYRAMIDCONTRASTENHANCER_H
#define STIRA_PYRAMIDAPPLICATIONS_PYRAMIDCONTRASTENHANCER_H

#include <vector>

#include "../../imagedata/datastructures/Pyramid.h"

namespace stira {
namespace pyramidapplications {
   
/** \brief A class to demonstrate simple contrast enhancement
  * The original reference used curvelets, we replaced these by a steerable pyramid
  * Original reference: 
  *
  * "Gray and color image contrast enhancement by the curvelet transform"
  * Murtagh, Fionn and Starck, J.L. and Candes, E.J. and Donoho, D.L. (2003) 
  * IEEE  Transactions on Image Processing, 12 (6). pp. 706-717.
  */
class PyramidContrastEnhancer
{
public:
   /** \brief constructor
     * \param pPyramid pyramid with input data
     * \param sigma noise level, in order to avoid to amplify noise */
   PyramidContrastEnhancer( double sigma );
   
   /** \brief destructor*/
   ~PyramidContrastEnhancer();
   
   /** \brief run method
     * Processes al color bands in the image independantly
     * \param pImage input image to be enhanced
     * \param nrScales number of scales to use in the decomposition
     * \param nrOrientations number of orientations to use per scale in the decomposition
     * \param applyWavelet true: apply old wavelet-based enhancement; false: use new approach of Murtagh et al*/
   image::Image* Run( image::Image* pImage, int nrScales, int nrOrientations, bool applyWavelet=false );
   
   /** \brief runs contrast enhancement on a already decomposed pyramid 
     * Corresponds to single color band
     * \param pPyramid input pyramid
     * \param applyWavelet true: apply old wavelet-based enhancement; false: use new approach of Murtagh et al*/
   void RunPyramid( image::Pyramid<double>* pPyramid, bool applyWavelet=false );
   
   /** \brief color version of contrast enhancement
     * Color version has the following steps
     *   1) 3 band image is transformed to Luv
     *   2) Each band is decomposed in a pyramid
     *   3) The enhancement factor is computed based on the L2 norm of the Luv vector of pyramid coefficients
     *   4) The three components are multiplied with the enhancement factor
     *   5) The pyramids are reconstructed
     *   6) Result is transformed back to RGB
     *   7) 3 band image is transformed to Luv
     * \param pImage input image to be enhanced
     * \param nrScales number of scales to use in the decomposition
     * \param nrOrientations number of orientations to use per scale in the decomposition
     * \param applyWavelet true: apply old wavelet-based enhancement; false: use new approach of Murtagh et al*/
   image::Image* Run3Colors( image::Image* pImage, int nrScales, int nrOrientations, bool applyWavelet=false );
   
   /** \brief gets the sigma of the noise*/
   double GetSigmaNoise();
   
   /** \brief sets the sigma of the noise
     * \param sigma the sigma of the noise*/
   void SetSigmaNoise( double sigma );
   
   /** \brief gets the noise threshold factor
     * This is the factor with which sigma is multiplied to determine a minimum threshold for amplification; 
     * smaller coefficients are considered to be noise and are thus not amplified*/
   double GetNoiseThresholdFactor();
   
   /** \brief sets the noise threshold factor
     * \param factor the noise threshold factor */
   void SetNoiseThresholdFactor( double factor );
   
   /** \brief gets the noise threshold 
     * Is in fact (sigmaNoise x noiseThresholdFactor) */
   double GetNoiseThreshold();
   
   /** \brief sets the noise threshold 
     * \param threshold the noise threshold  */
   void SetNoiseThreshold( double threshold );
   
   /** \brief gets the non-linearity degree*/
   double GetNonLinearityDegree();
   
   /** \brief sets the non-linearity degree
     * \param degree the non-linearity degree */
   void SetNonLinearityDegree( double degree );
   
   /** \brief gets the upper limit for amplification factor (between 0 and 1)
     * Is in fact the factor with which the maximum coefficient is multiplied to 
     * determine the threshold above which no amplification is applied*/
   double GetUpperLimitAmplificationFactor();
   
   /** \brief sets the upper limit for amplification factor
     * \param limit the upper limit for amplification factor */
   void SetUpperLimitAmplificationFactor( double limit );
   
   /** \brief gets the factor that determines the compression of the dynamic range*/
   double GetDynamicRangeCompressionFactor();
   
   /** \brief sets the factor that determines the compression of the dynamic range
     * \param limit the upper limit for amplification factor */
   void SetDynamicRangeCompressionFactor( double factor );
   
   /** \brief gets the upper limit for amplification
     * Coefficients with an absolute value bigger than this value are not amplified
     * Can also be determined by finding the coefficient with maximum absolute value 
     * multiplied with UpperLimitAmplificationFactor*/
   double GetUpperLimitAmplification();
   
   /** \brief gets the upper limit for amplification
     * \param limit the upper limit for amplification*/
   void SetUpperLimitAmplification( double limit );
   
   /** \brief creates a file to inspect the values of the amplification factors over a range of coefficients
     * \param fileName name of file to write factors to
     * \param myMin minimum of the range of coefficients to inspect
     * \param myMax maximum of the range of coefficients to inspect
     * \param stepSize step size to walk through the range*/
   bool TestAmplificationfactor( std::string fileName, double myMin, double myMax, double stepSize );
   
   /** \brief prints the parameters of the algorithm to standard output */
   void PrintParameters();

private:
   
   /** \brief enhances contrast in a single band
     * \param pBand band in which to enhance contrast
     * \param applyWavelet true: apply old wavelet-based enhancement; false: use new approach of Murtagh et al*/
   bool ContrastEnhanceSingleBand( image::ArrayGrid<double>* pBand, bool applyWavelet );
   
   /** \brief enhances contrast in a single band that is part of 3 color bands
     * \param pBand1 color band 1 in which to enhance contrast
     * \param pBand2 color band 2 in which to enhance contrast
     * \param pBand3 color band 3 in which to enhance contrast
     * \param applyWavelet true: apply old wavelet-based enhancement; false: use new approach of Murtagh et al*/
   bool ContrastEnhanceSingleBand3Colors( image::ArrayGrid<double>* pBandColor1,
                                          image::ArrayGrid<double>* pBandColor2, 
                                          image::ArrayGrid<double>* pBandColor3, bool applyWavelet  );
   
   /** \brief computes for a given coefficient the contrast enhancement multiplier 
     * Here, the multiplier is determined according to the Curvelet-based method 
     * described in the reference mentioned above
     * \param x coefficient to enhance*/
   double GetCoefficientMultiplierCurvelet( double x );
   
   /** \brief computes for a given coefficient the contrast enhancement multiplier 
     * Here, the multiplier is determined  according to the older Wavelet-based method also 
     * described in the reference mentioned above
     * \param x coefficient to enhance*/
   double GetCoefficientMultiplierWavelet(double x );

   double mSigmaNoise;  ///< noise sigma
   
   double mNoiseThresholdFactor;  ///< noise factor
   
   double mNoiseThreshold; ///< noise level threshold to avoid noise amplification; is (mSigma x mC) with mC > 3
   
   double mNonLinearityDegree;  ///< degree of non-linearity
   
   double mUpperLimitAmplificationFactor;  ///< determines up to which magnitude edges are amplified 
                                           ///< (edges with gradient up to 
                                           ///<           (max abs value coeff * mUpperLimitAmplificationFactor) 
                                           ///< are amplified)
                                           
   double mDynamicRangeCompressionFactor;  ///< coefficient for dynamic range compression if not 0 
                                           ///< -> softens strongest edges and amplifies faintest edges
                                           
   double mUpperLimitAmplification;     ///< maximum value for which a coefficient is amplified; 
                                        ///< is ((max of a band) x mUpperLimitAmplificationFactor) with mUpperLimitAmplificationFactor < 1
   
};

}
}
#endif
