
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

#ifndef STIRA_STEERABLE_PYRAMID_PYRAMIDREAL_H
#define STIRA_STEERABLE_PYRAMID_PYRAMIDREAL_H

#include "PyramidMaster.h"

namespace stira {
namespace steerable {

/** \brief child class to compute FFT based real-valued steerable pyramid decomposition/reconstruction
  * Bibtex reference for formulae used here:
  * Formulae used from appendix; main paper is about texture denoising
  *     article{ portilla03image,
  *                author  = {Portilla, J. and Strela, V. and Wainwright, M. and Simoncelli, E.},
  *                title   = {Image denoising using scale mixtures of Gaussians in the wavelet domain},
  *                journal = {IEEE Trans. Image Processing},
  *                volume  = {12},
  *                number  = {11}, 
  *                pages   = {1338--1351}
  *                year    = {2003},
  *                url     = {http://citeseer.ist.psu.edu/article/portilla03image.html}
  *            }
  */
class PyramidReal : public PyramidMaster< double >
{
public:
   /** \brief constructor
     * \param pGridIn source input grid data
     * \param myNrScales nr of scales in which to decompose the image
     * \param myNrOrientations nr of orientations in which to decompose the image*/
   PyramidReal( ArrayGrid<double>* pGridIn, int myNrScales, int myNrOrientations);
   
   /** \brief destructor*/
   ~PyramidReal();
   
    /** \brief decomposes the source image in an steerable pyramid*/
   bool Decompose();
   
   /** \brief reconstructs the steerable pyramid back to an image */
   bool Reconstruct();
   
   /** \brief diagnoses the current steerable pyramid */
   bool Diagnose();
   
   /** \brief writes pFftSubband to a PGM file for diagnostics
     * \param pFftSubband band to export for visualization
     * \param bandType band type, to be used for rescaling and in file name
     * \param scaleNr number of current scale, to be used for rescaling and in file name
     * \param orientationNr number of current orientation, to be used for rescaling and in file name*/
   bool VisualizeReconstructedBandpass( fouriertools::FFTBand* pFftSubband, std::string bandType, int scaleNr, int orientationNr );

private:

};
}
}

#endif
