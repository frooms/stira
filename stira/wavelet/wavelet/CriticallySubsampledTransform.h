
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
 
#ifndef STIRA_WAVELET_CRITICALLYSUBSAMPLEDTRANSFORM_H
#define STIRA_WAVELET_CRITICALLYSUBSAMPLEDTRANSFORM_H

#include "Wavelet.h"

namespace stira {
namespace wavelet {

using namespace stira::imagedata;

/** \brief parent class to compute redundant, non-subsampled wavelet decomposition / reconstruction */
class CriticallySubsampledTransform : public Wavelet
{
public:
   /** \brief constructor */
   CriticallySubsampledTransform();
   
   /** \brief destructor */
   ~CriticallySubsampledTransform();
   
   /** \brief decomposition
     * 
     * \param pSourceGrid grid to be deomposed
     * \param nrScales nr of scales in the decomposition
     * \return true if all went well*/
   virtual bool Decompose( ArrayGrid<double>* pSourceGrid, int nrScales );
   
   /** \brief reconstructs the decomposed image
     * \param threshold hard threshold for bandpass images, just for demo purposes*/
   virtual bool Reconstruct( double threshold=0 );
   
private:

};

}
}

#endif
