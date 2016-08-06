
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

#ifndef STIRA_WAVELET_WAVELET_H
#define STIRA_WAVELET_WAVELET_H

#include <stdint.h>
#include <iostream>
#include <cstdlib>
#include <cmath>

#include "../../imagedata/datastructures/ArrayGrid.h"
#include "../../imagetools/tools/ImageIO.h"
#include "../../imagedata/datastructures/Pyramid.h"
#include "../../filter/filter/SeparableFilter.h"
#include "WaveletTapGenerator.h"

namespace stira {
namespace wavelet {

/** \brief parent class to compute wavelet decomposition / reconstruction 
  * For the moment just a fast Haar wavelet is available. Fast in the sense that the downsampling 
  * and upsampling are directly integrated in the computations and that no unnecessary coefficients 
  * are computed that are removed by the subsampling*/
class Wavelet
{
public:
   /** \brief constructor */
   Wavelet();
   
   /** \brief destructor */
   virtual ~Wavelet();
   
   /** \brief decomposition
     * 
     * \param pSourceGrid grid to be deomposed
     * \param nrScales nr of scales in the decomposition
     * \return true if all went well*/
   virtual bool Decompose( image::ArrayGrid<double>* pSourceGrid, int nrScales ) = 0;
   
   /** \brief Gets the pyramid with all the subbands*/
   image::Pyramid<double>* GetPyramid();
   
   /** \brief reconstructs the decomposed image
     * \param threshold hard threshold for bandpass images, just for demo purposes*/
   virtual bool Reconstruct(double threshold = 0.0) = 0;
   
   /** \brief gets a copy of the grid after wavelket reconstruction
     * Caller gets responsability to delete it after usage*/
   image::ArrayGrid<double>* GetCopyOfReconstructedGrid();
   
   /** \brief gets the number of orientations*/
   int GetNumberOfOrientations();
   
   /** \brief gets the number of scales*/
   int GetNumberOfScales();
   
protected:
   
   /** \brief Initializes data structures and variables for decomposition
     * 
     * \param pSourceGrid input grid to be decomposed
     * \param nrScales the number of scales
     * \param nrOrientations the number of orientations
     * \param createBands flag whether we need to allocate the bands upon initialization
     * \param isSubsampled flag whether the deomposition is subsampled
     * \param isLowestScaleSubsampled flag whether the finest deomposed scale is subsampled (only used if isSubsampled is true)
     */
   void Initialize( image::ArrayGrid<double>* pSourceGrid, int nrScales, int nrOrientations=3, bool createBands=false, bool isSubsampled=true, bool isLowestScaleSubsampled=true );

   int mNrOrientations; ///< Number of orientations; default 3 with classical wavelets (LH, HL and HH)
   int mNrScales; ///< Number of scales
   image::Pyramid<double>* mpPyramid;  ///< data structure for decomposed bands with wavelet coefficients
   image::ArrayGrid<double>* mpDecomposeReconstructGrid;  ///< grid after deompose/reconstruct
   int mCurrentScale;   ///< number of the scale being computed
   WaveletFilterSet mSet;  ///< the wavelet filter taps

   image::ArrayGrid<double>* mpSourceGrid;  ///< pointer to source data before decomposition
};
}
}
#endif
