
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

#ifndef STIRA_FILTER_GAUSSCONVOLVE_H
#define STIRA_FILTER_GAUSSCONVOLVE_H

#include "../../imagedata/datastructures/Image.h"

#include "SeparableFilter.h"

namespace stira{
namespace filter{

/** \brief Convolves image with Gaussian PSF
  *
  * Recursive implementation based on:
  *
  *  article{ young95recursive,
  *            author = {Young, I. T. and {van~Vliet}, L. J.},
  *            title  = {Recursive implementation of the Gaussian filter},
  *            volume = {44},
  *            number = {2},
  *            pages  = {139-151},
  *            year   = {1995},
  *            url    = {http://citeseer.ist.psu.edu/young95recursive.html}
  *          }
*/
class GaussConvolve
{

/////////////////////////////////////
//                                 //
// 1) enum descriptors             //
//                                 //
/////////////////////////////////////

public:
   /** \brief identifier which type of gausssian filter this is*/
   enum FilterType{ FFT_BASED, RECURSIVE_BASED };

   /** \brief identifier which type of gausssian filter this is*/
   enum DerivativeType{ DERIVATIVE_NONE, DERIVATIVE_X, DERIVATIVE_Y, DERIVATIVE_XX, DERIVATIVE_YY, DERIVATIVE_XY };

/////////////////////////////////////
//                                 //
// 2) constructor / destructor     //
//                                 //
/////////////////////////////////////

public:
   /** \brief constructor*/
   GaussConvolve();

   /** \brief destructor*/
   ~GaussConvolve();

   /** \brief generate test pattern of horizontal bars that become gradually more and more blurred
     * \param width width of the test pattern
     * \param height height of the test pattern
     * \param barWidth width of a bar in the image
     * \param sigmaBlurMax the maximal blur applied to the bars (at the right of the image)*/
   static ArrayGrid<double>* CreateBlurredBars( int width, int height, int barWidth, double sigmaBlurMax );

//////////////////////////////////////
//                                  //
// 3) generic gaussian filtering    //
//                                  //
//////////////////////////////////////

public:
   /** \brief Applies Gaussian filter to grid
     * Generates new grid, which the caller is responsible for
     * \param pImage input grid
     * \param sigma sigma for the gaussian filter
     * \param myType how to compute the filtering: recursively or in Fourier domain*/
   static ArrayGrid<double>* Convolve( ArrayGrid<double>* pImage, double sigma, FilterType myType=FFT_BASED);

   /** \brief Applies Gaussian filter to image
     * Generates new image, which the caller is responsible for
     * \param pImage input image
     * \param sigma sigma for the gaussian filter
     * \param myType how to compute the filtering: recursively or in Fourier domain*/
   static Image* Convolve( Image* pImage, double sigma, FilterType myType=FFT_BASED);

////////////////////////////////////////////////////////////
//                                                        //
// 4) methods to filter with gaussian derivative kernels  //
//                                                        //
////////////////////////////////////////////////////////////

public:
   /** \brief Applies Gaussian filter or its derivatives (applied in Fourier domain) to a grid
     * Generates new grid with filter response, which the caller is responsible for
     * \param pGridIn input grid
     * \param sigma sigma for the gaussian filter
     * \param myType which derivative kernel to use for the filtering */
   static ArrayGrid<double>* DerivativeConvolveFFT( ArrayGrid< double >* pGridIn, double sigmaX, double sigmaY, DerivativeType myType );

   /** \brief Applies Gaussian filter or its derivatives (applied in spatial domain by a separable filter in x and y) to grid
     * Generates new grid with filter response, which the caller is responsible for
     * \param pGridIn input grid
     * \param sigma sigma for the gaussian filter
     * \param myType which derivative kernel to use for the filtering
     * \param myExtensionType identifies how borders should be extended (mirror, tiled periodically, zero's) */
   static ArrayGrid<double>* DerivativeConvolveSeparable( ArrayGrid<double>* pGridIn, double sigma, DerivativeType myType, GridExtender<double>::ExtensionType myExtensionType = GridExtender<double>::EXTEND_MIRROR );

   /** \brief Simple interface to straightforward Gaussian filter (applied in spatial domain by a separable filter in x and y) to grid
     * Generates new grid with filter response, which the caller is responsible for
     * \param pGridIn input grid
     * \param sigma sigma for the gaussian filter*/
   static ArrayGrid<double>* ConvolveSeparable( ArrayGrid< double >* pGridIn, double sigma );

   /** \brief Applies Gaussian filter or its derivatives (applied in Fourier domain) to image
     * Generates new image with filter response, which the caller is responsible for
     * \param pImageIn input grid
     * \param sigma sigma for the gaussian filter
     * \param myType which derivative kernel to use for the filtering
     * \param myExtensionType identifies how borders should be extended (mirror, tiled periodically, zero's) */
   static Image* DerivativeConvolveFFT( Image* pImageIn, double sigma, DerivativeType myType, GridExtender<double>::ExtensionType myExtensionType = GridExtender<double>::EXTEND_MIRROR );

   /** \brief Applies Gaussian filter or its derivatives (applied in spatial domain by a separable filter in x and y) to image
     * Generates new image with filter response, which the caller is responsible for
     * \param pImageIn input image
     * \param sigma sigma for the gaussian filter
     * \param myType which derivative kernel to use for the filtering
     * \param myExtensionType identifies how borders should be extended (mirror, tile, black)*/
   static Image* DerivativeConvolveSeparable( Image* pImageIn, double sigma, DerivativeType myType, GridExtender<double>::ExtensionType myExtensionType = GridExtender<double>::EXTEND_MIRROR );

   /** \brief Simple interface to straightforward Gaussian filter (applied in spatial domain by a separable filter in x and y) to grid
     * Generates new image with filter response, which the caller is responsible for
     * \param pImageIn input image
     * \param sigma sigma for the gaussian filter*/
   static Image* ConvolveSeparable( Image* pImageIn, double sigma );

///////////////////////////////////////
//                                   //
// 5) generate simple gaussian PSF   //
//                                   //
///////////////////////////////////////

public:
   /** \brief Generates a Gaussian filter kernel
     * Generates new image, which the caller is responsible for
     * \param width width of image to generate
     * \param height height of image to generate
     * \param sigmaX sigma in X direction for the gaussian filter
     * \param sigmaY sigma in Y direction for the gaussian filter*/
   static ArrayGrid<double>* GenerateGaussianPSF ( int width, int height, double sigmaX, double sigmaY );

   /** \brief Generates a Gaussian filter kernel
     * Generates new image, which the caller is responsible for
     * \param width width of image to generate
     * \param height height of image to generate
     * \param sigma1 sigma of x for the gaussian filter
     * \param sigma2 sigma of y for the gaussian filter
     * \param rho    correlation coefficient, must be between -1 and 1*/
   static ArrayGrid<double>* GenerateGaussianPSF ( int width, int height, double sigma1, double sigma2, double rho );

///////////////////////////////////////////////////////////
//                                                       //
// 6) Upsample / downsample with Gaussian interpolation  //
//                                                       //
///////////////////////////////////////////////////////////

public:
   /** \brief Generates an upscaled grid, where all pixels are interpolated with a Gaussian function
     * Generates new grid with filter response, which the caller is responsible for
     * \param pGridIn input grid
     * \param upscalefactor factor with which grid needs to be upscaled*/
   static ArrayGrid<double>* UpsampleGaussianInterpolated( ArrayGrid<double>* pGridIn, int upscalefactor );

//////////////////////////////
//                          //
// 7) Private help methods  //
//                          //
//////////////////////////////

private:
   /** \brief Generates a 1D gaussian filter kernel or gaussian derivative kernel
     * \param sigma sigma of the gaussian
     * \param size output parameter with length of the kernel
     * \param order derivative order for the kernel
     * \return array with filter kernel coefficients
     */
   static double* Generate1DGaussianKernel(double sigma, int& size, int order);

   /** \brief internal conversion from sigma to internal variable q for recursive filtering (see reference)
     * \param sigma value to be converted*/
   static double GetQ(double sigma);

   /** \brief convolve grid using recursive filtering
     * \param pGridIn input grid to be filtered
     * \param sigma sigma for the gaussian filter*/
   static ArrayGrid<double>* RecursiveConvolve( ArrayGrid<double>* pGridIn, double sigma);

   /** \brief convolve image using Fourier domain filtering
     * \param pImage input image to be filtered
     * \param sigma sigma for the gaussian filter*/
   static Image* FFTConvolve( Image* pImage, double sigma);

   /** \brief convolve grid using Fourier domain filtering
     * \param pGrid input grid to be filtered
     * \param sigma sigma for the gaussian filter*/
   static ArrayGrid<double>* FFTConvolve( ArrayGrid<double>* pGrid, double sigma);

   /** \brief convolve image using recursive gaussian filtering
     * \param pImage input image to be filtered
     * \param sigma sigma for the gaussian filter*/
   static Image* RecursiveConvolve( Image* pImage, double sigma);

};

}
}

#endif
