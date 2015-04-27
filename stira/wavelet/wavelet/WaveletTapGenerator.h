
/***********************************************************************************
 *   Copyright (C) 2009 by Filip Rooms                                             *
 *                                                                                 *
 *  Terms and conditions for using this software in any form are provided in the   *
 *  file COPYING, which can be found in the root directory of this project.        *
 *                                                                                 *
 *   Contact data: filip.rooms@gmail.com                                           *
 *                 http://www.filiprooms.be/                                       *
 *                                                                                 *
 ***********************************************************************************/

#ifndef STIRA_WAVELET_WAVELETTAPGENERATOR_H
#define STIRA_WAVELET_WAVELETTAPGENERATOR_H

#include "WaveletTapGenerator.h"
#include "WaveletTaps.h"

namespace stira {
namespace wavelet {

//=========================================================================================================

/** \brief struct containing filter taps needed for analysis and reconstruction */
struct WaveletFilterSet
{
   double* pLowpassForward;   ///< array containing the decomposition lowpass taps
   double* pLowpassInvers;    ///< array containing the reconstruction lowpass taps
   double* pHighpassForward;  ///< array containing the decomposition highpass taps
   double* pHighpassInvers;   ///< array containing the reconstruction highpass taps
   int length;                ///< length of the arrays (orthogonal: all arrays have the same length)
   WaveletType type;          ///< identifier for wavelet type
};

//=========================================================================================================

/** \brief wavelet tap set factory 
  * Generates a set of decomposition/reconstruction filter taps for the type of wavelet specified */
class WaveletTapGenerator
{
public:
   /** \brief constructor */
   WaveletTapGenerator();
   
   /** \brief destructor */
   ~WaveletTapGenerator();
   
   /** \brief generates the set of filter taps 
     * \param type which type of wavelet taps to generate */
   WaveletFilterSet Generate( WaveletType type );

private:
   WaveletFilterSet mSet; ///< set of filter taps
   void Initialize( WaveletType type ); ///< allocates memory for the filter taps
   void FillInFirstFilterTaps( ); ///< fills in the values of the first set of filter taps
   void FillInOtherTaps( ); ///< fills in the values of the other sets of filter taps
};
}
}

#endif
