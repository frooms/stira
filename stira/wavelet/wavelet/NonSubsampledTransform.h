
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
 
#ifndef STIRA_WAVELET_NONSUBSAMPLEDTRANSFORM_H
#define STIRA_WAVELET_NONSUBSAMPLEDTRANSFORM_H

#include "../../imagedata/datastructures/ArrayGrid.h"
#include "Wavelet.h"
#include "WaveletTapGenerator.h"

namespace stira {
namespace wavelet {

using namespace stira::imagedata;


/** \brief Computes orthogonal redundant (i.e., non-subsampled) wavelet decomposition / reconstruction 
  * This class implements the a-trous algorithm of Mallat */
class NonSubsampledTransform : public Wavelet
{
public:
   /** \brief constructor
     * \param type type of wavelet to use (see enum in waveletTabs.h) */
   NonSubsampledTransform( WaveletType type=DAUBECHIES_2 );
   
   /** \brief destructor */
   ~NonSubsampledTransform();
   
   /** \brief decomposition
     * \param pSourceGrid grid to be deomposed
     * \param nrScales nr of scales in the decomposition
     * \return true if all went well*/
   virtual bool Decompose( ArrayGrid<double>* pSourceGrid, int nrScales );
   
   /** \brief reconstructs the decomposed image
     * \param threshold hard threshold for bandpass images, just for demo purposes*/
   virtual bool Reconstruct(double threshold = 0.0);

private:
   /** \brief performs single level of the decomposition
     * \param pInputGrid data as input to be decomposed to next level
     * \param myScale number of current decomposition scale (0 = first scale; 1 = second scale and so on)*/
   void DecomposeSingleScale( ArrayGrid<double> * pInputGrid, int myScale );
      
   /** \brief performs single level of the reconstruction
     * \param pReconstructedGrid data as output from reconstructing this level
     * \param myScale number of current decomposition scale (0 = first scale; 1 = second scale and so on)
     * \param threshold threshold for detail coefficients as test for reconstruction*/
   void ReconstructSingleScale( ArrayGrid<double> * pReconstructedGrid, int myScale, double threshold );

   /** \brief specialized version of Transform1D, where is known that filter is lowpass and data are row per row
     * \param pInputData data before filtering
     * \param pFilteredData data after filtering
     * \param isForward true if forward transform; false if inverse transform */
   void LowpassRowTransform1D( double * pInputData, double * pFilteredData, bool isForward );
   
   /** \brief specialized version of Transform1D, where is known that filter is lowpass and data are column per column
     * \param pInputData data before filtering
     * \param pFilteredData data after filtering
     * \param isForward true if forward transform; false if inverse transform */
   void LowpassColumnTransform1D( double * pInputData, double * pFilteredData, bool isForward );

   /** \brief specialized version of Transform1D, where is known that filter is highpass and data are row per row
     * \param pInputData data before filtering
     * \param pFilteredData data after filtering
     * \param isForward true if forward transform; false if inverse transform */
   void DetailRowTransform1D( double * pInputData, double * pFilteredData, bool isForward );
   
   /** \brief specialized version of Transform1D, where is known that filter is highpass and data are column per column
     * \param pInputData data before filtering
     * \param pFilteredData data after filtering
     * \param isForward true if forward transform; false if inverse transform */
   void DetailColumnTransform1D( double * pInputData, double * pFilteredData, bool isForward );

   /** \brief Creates the extended data structures and upsamples the needed filters
     * This action is just performed once for the whole scale instead of each time per row and per column
     * \param width width of non-extended source data
     * \param height height of non-extended source data
     * \param pLowpassFilter the non-upsampled lowpass filter taps
     * \param pDetailFilter the non-upsampled highpass filter taps
     * \param nrTaps the number of filter taps (=length of the filter)
     * \param scale scale at which we are currently (0 = finest, then going up recursively)
     * \return true if all went well */
   bool CreateExtendedDataStructures(int width, int height, double* pLowpassFilter, double* pDetailFilter, int nrTaps, int scale);
   
   /** \brief Clears the extended data structures and upsamples the needed filters
     * just needed once at end of each scale*/
   bool ClearExtendedDataStructures();
   
   /** \brief filters a single column
     *
     * \param pOutputData output: the filtered data
     * \param pFilterTaps  input: the filter taps
     * \param pInputData input: the array containing the input data */
   void FilterColumn( double * pOutputData, double* pFilterTaps, double * pInputData);

  /** \brief filters a single row
    *
    * \param pOutputData output: the filtered data
    * \param pFilterTaps  input: the filter taps
    * \param pInputData input: the array containing the input data */
   void FilterRow( double * pOutputData, double * pFilterTaps, double * pInputData);
   
   int mWidth;  ///< length of non-extended row
   int mHeight; ///< length of non-extended column
   int mExtendedFilterLength;  ///< length of upsampled filter
   int mExtendedFilterHalfLength;
   int mUpscaleFactor; ///< upsampling factor
   double* mpExtendedLowpassFilter; ///< extended lowpass filter with 2^p-1 zeros between the coefficients
   double* mpExtendedDetailFilter; ///< extended highpass filter with 2^p-1 zeros between the coefficients
   
   double* mpRowIn;
   double* mpRowOut;
   double* mpColumnIn;
   double* mpColumnOut;
   
   double* mpExtendedRowInputData;     ///< array containing extended input row
   double* mpExtendedColumnInputData;  ///< array containing extended input column
   double* mpExtendedRowOutputData;    ///< array containing extended row after filtering
   double* mpExtendedColumnOutputData; ///< array containing extended column after filtering
   
   int mExtendedInputWidth;   ///< length of extended input row
   int mExtendedInputHeight;  ///< length of extended input column
   
   int mExtendedOutputWidth;  ///< length of extended output row
   int mExtendedOutputHeight;  ///< length of extended output column
   
   double* mpExtraExtendedRowData;    ///< array containing extended row 
   double* mpExtraExtendedColumnData; ///< array containing extended column 
   int mExtraExtendedWidth;  ///< length of extended output row
   int mExtraExtendedHeight;  ///< length of extended output column
};

}
}

#endif
