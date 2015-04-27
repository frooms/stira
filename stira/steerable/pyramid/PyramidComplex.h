
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

#ifndef STIRA_STEERABLE_PYRAMID_PYRAMIDCOMPLEX_H
#define STIRA_STEERABLE_PYRAMID_PYRAMIDCOMPLEX_H

#include "PyramidMaster.h"

namespace stira {
namespace steerable {

/** \brief child class to compute FFT based complex-valued steerable pyramid decomposition/reconstruction
  * Formulae used from appendix; main paper is about texture modeling
  *
  *    @article{ portilla00parametric,
  *                author  = {Portilla, J. and Simoncelli, E.},
  *                title   = {A Parametric Texture Model based on Joint Statistics of Complex Wavelet Coefficients},
  *                journal = {Int. Journal of Computer Vision},
  *                volume  = {40},
  *                number  = {1}, 
  *                pages   = {49--71}
  *                year    = {2000},
  *                url     = {http://citeseer.ist.psu.edu/portilla00parametric.html}
  *            }
  */
class PyramidComplex : public PyramidMaster< std::complex<double> >
{
public:
   /** \brief constructor
     * \param pGridIn source input grid data
     * \param myNrScales nr of scales in which to decompose the image
     * \param myNrOrientations nr of orientations in which to decompose the image*/
   PyramidComplex( image::ArrayGrid<double>* pGridIn, int myNrScales, int myNrOrientations);
   
   /** \brief destructor*/
   ~PyramidComplex();
   
    /** \brief decomposes the source image in an steerable pyramid*/
   bool Decompose();
   
   /** \brief reconstructs the steerable pyramid back to an image */
   bool Reconstruct();
   
   /** \brief diagnoses the current steerable pyramid */
   bool Diagnose();
   
   /** \brief Diagnostic method to visualize a complex-valued bandpass grid
     * \param pGrid bandpass grid to visualize
     * \param bandType type of subband (for generation of file name to write to)
     * \param scaleNr nr of scale of current subband
     * \param orientationNr nr of orientation of current subband*/
   bool VisualizeComplexBandpass( image::ArrayGrid< std::complex<double> >* pGrid, std::string bandType, int scaleNr, int orientationNr );

   /** \brief Diagnostic method to visualize a complex-valued reconstructed subband
     * \param pFftBandIn subband to visualize
     * \param bandType type of subband (for generation of file name to write to)
     * \param scaleNr nr of scale of current subband
     * \param orientationNr nr of orientation of current subband*/
   bool VisualizeReconstructedBandpass( fouriertools::FFTBand* pFftBandIn, std::string bandType, int scaleNr, int orientationNr );

private:

};
}
}

#endif
