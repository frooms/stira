
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

#ifndef STIRAGUI_DEFINITIONS_STIRADEFINITIONS_H
#define STIRAGUI_DEFINITIONS_STIRADEFINITIONS_H

class StiraDefinitions
{
public:

   static const int maxWidth;

   static const int maxHeight;
   
   /** \brief constructor*/
   StiraDefinitions();
   
   /** \brief destructor*/
   ~StiraDefinitions();
   
   /** \brief enum type for identifying image type when generating a synthetic image*/
   enum SyntheticImageType { SYNTHETIC_EMPTY, ///< constant intensity
                             SYNTHETIC_EMPTYPLUSNOISE, ///< constant intensity + gaussian noise
                             SYNTHETIC_HORIZONTALGRADIENT, ///< linear horizontal intensity gradient
                             SYNTHETIC_VERTICALGRADIENT, ///< linear vertical intensity gradient
                             SYNTHETIC_HORIZONTALSINE, ///< sine wave along x; constant along y 
                             SYNTHETIC_VERTICALSINE,  ///< constant along x; sine wave along y
                             SYNTHETIC_EUCLIDEANSPOTS,  ///< spots with Euclidean profile (AM halftoning spot function)
                             SYNTHETIC_BLURREDBARS,  ///< horizontal bars that gradually become more and more blurred
                             SYNTHETIC_INVERSEZONEPLATE, ///< inverse of zone plate
                             SYNTHETIC_ZONEPLATE, ///< zone plate (aka Newton rings)
                             SYNTHETIC_STARCHART, ///< polar coordinates: constant along radius, sine wave over angle
                             SYNTHETIC_LOGFREQUENCYCONTRAST, ///< log frequency sine wave; contrast decreases with (y^2)
                             SYNTHETIC_SHEPPLOGAN, ///< Shepp-Logan phantom
                             SYNTHETIC_GRETAGMACBETH, ///< Gretag-Macbeth color chart
                             SYNTHETIC_ISING  ///< Ising-model generated texture
                           };
   
   /** \brief enum type for identifying regularization type when applying Richardson-Lucy deconvolution*/
   enum RLRegularizationType { RLREGULARIZE_NONE, ///< no regularization 
                               RLREGULARIZE_TIKHONOV_MILLER, ///< Tikhonov-Miller regularization 
                               RLREGULARIZE_CONCHELLO, ///< Conchello regularization 
                               RLREGULARIZE_MAXIMUM_ENTROPY, ///< maximum entropy regularization 
                               RLREGULARIZE_TOTAL_VARIATION ///< total variation regularization 
                             };
   
   /** \brief enum type for identifying contrast enhancement procedure*/
   enum ContrastEnhanceType{
                             CONTRAST_NEGATIVE, ///< creates negative of an image
                             CONTRAST_GAMMA, ///< applies gamma correction
                             CONTRAST_LINEARSCALE, ///< linear intensity rescaling, ignoring a fraction of outliers
                             CONTRAST_DARKCHANNEL, ///< linear intensity rescaling, ignoring a fraction of outliers
                             CONTRAST_RETINEX, ///< multiscale retinex with color restoration accrding to Jobson, Rahman et al
                             CONTRAST_RETINEX_HSI, ///< experimental HSI space based multiscale retinex
                             CONTRAST_HISTOGRAM_EQUALIZE_RGB, ///< color histogram equalization (equalize L component in Lab space)
                             CONTRAST_HISTOGRAM_EQUALIZE_PERBAND, ///< histogram equalization, all bands independantly
                             CONTRAST_WAVELET, ///< contrast enhance with curvelet-based method of Starck et al (here with steerable pyr ipv curvelets)
                             CONTRAST_ADAPTIVE_LUONG ///< method from Hiep's PhD
                           };

   /** \brief enum type for identifying filter type*/
   enum SimpleFilterType {
                           FILTER_LOCALMEAN, ///< average intensity of values in local window around it
                           FILTER_NONLOCALMEAN, ///< non-local means filter (Buades) to reduce noise
                           FILTER_MOTIONBLUR, ///< linear PSF of given length and angle
                           FILTER_SOBELX, ///<  sobel filter in X direction
                           FILTER_SOBELY, ///<  sobel filter in Y direction
                           FILTER_NORMALMEDIAN,  ///<  median intensity of values in local window around it
                           FILTER_HYBRIDMEDIAN,  ///<  median intensity of values in local window around it
                           FILTER_GAUSSIAN,  ///< weighted local mean with gaussian weights window around it
                           FILTER_KUWAHARA, ///< non-linear edge preserving smoothing filter
                           FILTER_ADAPTIVEBILATERAL, ///< variant on bilateral filter
                           FILTER_LAPLACIANOFGAUSSIAN, ///< Laplacian of Gaussian; kind of derivative filter
                           FILTER_UNSHARPMASK  ///< unsharp mask sharpening
                         };
   
   /** \brief enum type for identifying noise type when simulating noise in an image*/
   enum NoiseType{ NOISE_POISSON, ///< noise has a Poisson distribution
                   NOISE_GAUSSIAN, ///< noise has a Gaussian distribution
                   NOISE_IMPULSE ///< noise is of type impulse
                 };
   
   /** \brief enum type for identifying type of parametric PSF (Point Spread Function) */
   enum PSFType{ PSF_DISK,  ///< PSF is a unform disk
                 PSF_SQUARE, ///< PSF is a uniform square
                 PSF_GAUSS,  ///< PSF is a Gaussian function
                 PSF_AIRY,  ///< PSF is an Airy disk (see optics)
                 PSF_LINE  ///< PSF is a straight line
               };
   
   /** \brief enum type for identifying type how to compare two images*/
   enum ImageCompareType{ COMPARE_SSD,  ///< Compare using Sum of Squared Differences criterion (SSD)
                          COMPARE_SSIM   ///< Compare using Structural SIMilarity criterion (SSIM)
                        };

   /** \brief enum type for identifying process type */
   enum ImageProcessType{ PROCESS_ANISOTROPIC_DIFFUSION, ///< Anisotropic diffusion image smoothing
                          PROCESS_CANNY, ///< Canny edge detection
                          PROCESS_SPLITBREGMAN_TV_DENOISE, ///< Split-Bregman Total Variation denoising
                          PROCESS_COMPARE_IMAGE, ///< Compares two images
                          PROCESS_CONTRAST_ENHANCE, ///< enhances image contrast
                          PROCESS_GENERATE_IMAGE, ///< generates synthetic image
                          PROCESS_RICHARDSON_LUCY,  ///< Richardson-Lucy deconvolution
                          PROCESS_SIMPLE_FILTER,  ///< applies a simple filter
                          PROCESS_SIMULATE_NOISE, ///< simulates noise
                          PROCESS_STEERABLE_DENOISING,  ///< bivariate gaussian based denoising as in Sendur et al
                          PROCESS_WATERSHED,  ///< flood-based watershed segmentation
                          PROCESS_WIENER  ///< Wiener deconvolution
                        };

};
   
#endif
