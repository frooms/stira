
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

#ifndef STIRA_DECONVOLVE_WIENERDECONVOLVE_H
#define STIRA_DECONVOLVE_WIENERDECONVOLVE_H

#include "../../imagedata/datastructures/Image.h"
#include "../../fouriertools/fouriertools/FFTBand.h"
#include "DeconvolveMaster.h"

namespace stira{
namespace deconvolve{

/** \brief child class for computing wiener deconvolution
  */
class WienerDeconvolve: public DeconvolveMaster
{
public:
   
   /** \brief constructor 
     * \param pDegradedImage the degraded input image for restoration*/
   WienerDeconvolve( image::Image* pDegradedImage );
   
   /** \brief constructor  
     * \param pDegradedImage the degraded input image for restoration
     * \param pPSF the Point Spread Function*/
   WienerDeconvolve(image::Image* pDegradedImage, image::Image* pPSF );
   
   /** \brief destructor */
   ~WienerDeconvolve( );
   
   /** \brief starts the deconvolution if all inputs are available
     * After completion, get the result with GetRestoredImage() from the parent class*/
   bool Run();
   
   /** \brief Run restoration for single spectral band 
     * assumes simplest case that bands can be processed independently
     * \param pInGrid band to be retsored
     * \param pInPSF Point Spread Function for this band
     * \param noiseLevel the noise level */
   static image::ArrayGrid<double>* RunSingleband( image::ArrayGrid<double>* pInGrid, image::ArrayGrid<double>* pInPSF, double noiseLevel );

private:
   /** \brief checks if all inputs are available*/
   bool IsReadyToRun();
   
   /** \brief quick and dirty approach to estimate spectrum; must be replaced later by more robust method\
     * \param pFFTInputGrid Fourier transformed degraded data
     * \param pFFTPSFGrid Fourier transformed PSF
     * \param noiseLevel the noise level */
   static image::ArrayGrid<double>* EstimateIdealSpectrum( fouriertools::FFTBand* pFFTInputGrid, fouriertools::FFTBand* pFFTPSFGrid, double noiseLevel );
};

}
}

#endif
