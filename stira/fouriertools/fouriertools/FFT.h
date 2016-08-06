
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

#ifndef STIRA_FFT_FFT_H
#define STIRA_FFT_FFT_H
#include <iostream>
#include <cstdlib>

#include "kiss_fft.h"
#include "kiss_fftnd.h"

#include "../../imagedata/datastructures/Image.h"
#include "../../common/common/Definitions.h"

#include "FFTBand.h"

namespace stira {
namespace fouriertools {

/** \brief A class to hold spectral bands of an image  */
// These class' methods are divided in the following categories 
//    1) GENERAL METHODS
//    2) GENERAL OPERATIONS
//    3) APPLY TRANSFER FUNCTION VARIANTS      (output spatial and complex-valued )
//    4) APPLY TRANSFER FUNCTION FFT VARIANTS  (output fourier )
//    5) APPLY TRANSFER FUNCTION FFT VARIANTS  (output spatial and real-valued )
///////////////////////////////////////////////////////////////////////////////////////

class FFT{
public:

   /** \brief Constructor.*/
   FFT();

   /** \brief Destructor. */
   ~FFT();
   
// 1) GENERAL METHODS
//////////////////////
public:
   
   /** \brief creates a grid of complex values from a real-valued grid in which the imaginary components are 0
     * \param pGridIn real-valued input grid */
   static image::ArrayGrid< std::complex <double> >* CreateComplexGridFromRealGrid( image::ArrayGrid<double>* pGridIn);
   
   /** \brief creates a grid of real values from a complex-valued grid; we just take the real component of each complex number
     * \param pGridIn complex-valued input grid */
   static image::ArrayGrid<double>* CreateRealGridFromComplexGrid( image::ArrayGrid< std::complex <double> >* pGridIn);

protected:
   
   /** \brief rescales the intensities in pGrid
     * \param pGrid Grid to rescale intensites of
     * \param newMin minimum after rescaling
     * \param newMax maximum after rescaling*/
   static void RescaleGrid( image::ArrayGrid<double>* pGrid, double newMin, double newMax);
   
   /** \brief Writes for diagnostic purposes the real or imaginary part of FFTData to disk 
     * \param pFFTData data to write to disk
     * \param myDataType enum if the real or imaginary part is to be written to disk
     * \param pFileName   name of the file to write to
     * \param factor rescaling factor with which all intensities are multiplied before they are written to disk*/
   static void WriteFFTDataToPPM( FFTBand* pFFTData, FFTDataType myDataType, char* pFileName, double factor);

// 2) GENERAL OPERATIONS
/////////////////////////
public:

   /** \brief Computes power spectrum, and returns it as a grid.
     * \param pInputGrid input grid to compute the power spectrum for*/
   static image::ArrayGrid<double>* ComputePowerSpectrum( image::ArrayGrid<double>* pInputGrid );

   /** \brief Computes logarithm of the power spectrum, and returns it as a grid.
     * Logarithm is used for compression of dynamic range of values, for visualization
     * \param pInputGrid input grid to compute the power spectrum for*/
   static image::ArrayGrid<double>* ComputeLogPowerSpectrum( image::ArrayGrid<double>* pInputGrid );

   /** \brief Computes radially averaged power spectrum, and returns it rescaled logaritmically as a 1D vector of doubles.   
     *
     * Ref: R. Ulichney, "Dithering with Blue Noise", Proc. of the IEEE, vol. 76, no. 1, pp. 56-79, 1988.
     *      http://www.hpl.hp.com/personal/Robert_Ulichney/publications.html
     * \param pInputImage input grid to compute the power spectrum for
     * \param thetaSteps number of steps to take along a circle with given radius to average the spectrum*/
   static std::vector<double> ComputeRadiallyAveragedSpectrum( image::ArrayGrid<double>* pInputImage, int thetaSteps=500 );

   /** \brief Computes the convolution of a single grid with the filterKernel in the argument
     * \param pInputGrid grid to be convolved
     * \param pFilterKernel the PSF to convolve the band with
     * \return result of convolution as a new grid. */
   static image::ArrayGrid<double>* Convolve( image::ArrayGrid<double>* pInputGrid, image::ArrayGrid<double>* pFilterKernel);
   
   /** \brief Overloaded method to computes the convolution of an image with the filterKernel
     * \param pInputImage image to be convolved (band by band)
     * \param pFilterKernel the PSF to convolve the bands with
     * \return result of convolution as a new image. */
   static image::Image* Convolve( image::Image* pInputImage, image::ArrayGrid<double>* pFilterKernel);

   /** \brief Computes the convolution of an image with a Gaussian PSF with given sigma
     * \param pInputImage image to be convolved
     * \param sigma the sigma for the Gaussian PSF 
     * \return result of convolution as an image. */
   static image::Image* GaussConvolve(image::Image* pInputImage, double sigma);
   
   /** \brief Computes the convolution of a single grid with a Gaussian PSF with given sigma
     * \param pInputGrid grid to be convolved
     * \param sigma the sigma for the Gaussian PSF 
     * \return result of convolution as a grid. */
   static image::ArrayGrid<double>* GaussConvolve( image::ArrayGrid<double>* pInputGrid, double sigma );

// 3) APPLY TRANSFER FUNCTION VARIANTS
//       Different possible inputs; output is complex-valued but in the spatial domain!!
////////////////////////////////////////////////////////////////////////////////////////
public:

   /** \brief Applies a transfer function to a FFTBand (= Fourier-transformed input data)
     *
     * Takes the Fourier Transformed image as input and creates a complex-valued grid in the
     * spatial domain (so output is NOT in the Fourier domain anymore!!) 
     *
     * Complex-valued output is convenient though for generalization purposes: both real-valued 
     * as complex valued output can be generated, and can be postprocessed according to the specific case
     *
     * Handy when building a pyramid: needs to extract bands from same image, so: 
     *       FFT once, apply different transfer functions and IFFT for each extracted band
     *
     * \param pFFTImageData input data already fourier-transformed
     * \param transferFunction transfer functions to be applied on this FFTBand */
   static FFTBand* ApplyTransferFunction(FFTBand* pFFTImageData, image::ArrayGrid<double>* transferFunction);

   /** \brief Applies a transfer function to a FFTBand (= Fourier-transformed input data)
     * Overloaded ApplyTransferFunction to allow that the transfer function is also in complex format already
     *
     * \param pFFTImageData input data already fourier-transformed
     * \param transferFunction transfer functions to be applied on this FFTBand */
   static FFTBand* ApplyTransferFunction(FFTBand* pFFTImageData, FFTBand* transferFunction);

// 4) APPLY TRANSFER FUNCTION FFT VARIANTS
//       Different possible inputs; output is complex-valued and still in the Fourier domain
////////////////////////////////////////////////////////////////////////////////////////////
public:

   /** \brief yet another method to apply a transfer function
     * This time, it takes real input and gives output in the Fourier domain
     * Motivation: when reconstructing a pyramid, we can sum all the bands in the Fourier domain, so we only need 
     * the inverse Fourier transform once.
     *
     * \param pInputGrid the input grid to be filtered
     * \param transferFunction the transfer function to be applied on this FFTBand*/
   static FFTBand* ApplyTransferFunctionFFT( image::ArrayGrid<double>* pInputGrid, image::ArrayGrid<double>* transferFunction);
   
   /** \brief yet another method to apply a transfer function
     * Overloaded previous method to allow that the transfer function is also in complex format already
     *
     * \param pInputGrid the input grid to be filtered
     * \param transferFunction the transfer function to be applied on this FFTBand*/
   static FFTBand* ApplyTransferFunctionFFT( image::ArrayGrid<double>* pInputGrid, FFTBand* transferFunction );
   
   /** \brief yet another method to apply a transfer function
     * Overloaded previous method to allow that the transfer function is also in complex format already
     *
     * \param pInputGrid the input grid to be filtered
     * \param transferFunction the transfer function to be applied on this FFTBand*/
   static FFTBand* ApplyTransferFunctionFFT( image::ArrayGrid< std::complex<double> >* pInputGrid, FFTBand* transferFunction );

// 5) APPLY TRANSFER FUNCTION FFT VARIANTS
//       Real-valued spatial domain input -> real-valued spatial domain output
////////////////////////////////////////////////////////////////////////////////////////////
public:

   /** \brief yet another method to apply a transfer function
     *
     * \param pInputGrid the input grid to be filtered
     * \param transferFunction the transfer function to be applied on this real-valued grid
     * \param myDataType specifies if we want the real or imaginary component as output*/
   static image::ArrayGrid<double>* ApplyTransferFunctionSpatial( image::ArrayGrid<double>* pInputGrid, image::ArrayGrid<double>* transferFunction, FFTDataType myDataType=RE);
   
   /** \brief yet another method to apply a transfer function
     *
     * \param pInputGrid the input grid to be filtered
     * \param transferFunction the transfer function to be applied on this real-valued grid
     * \return a pair with as first element the real components of the complex values and as second element the imaginary components*/
   static std::pair< image::ArrayGrid<double>*, image::ArrayGrid<double>*> ApplyTransferFunctionSpatialComplex(  image::ArrayGrid<double>* pInputGrid,  image::ArrayGrid<double>* transferFunction);
   
   /** \brief supresses the outer frequencies in an image; essentially makes an image band-limited
     * \param pInputGrid grid to be convolved */ 
   static image::ArrayGrid<double>* SuppressOuterFrequencies( image::ArrayGrid<double>* pInputGrid );
   
};
}
}
#endif
