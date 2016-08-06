
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

#ifndef STIRA_IMAGE_DATASTRUCTURES_CWTPYRAMID_H
#define STIRA_IMAGE_DATASTRUCTURES_CWTPYRAMID_H

#include <stdint.h>
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <cassert>

#include "Pyramid.h"

namespace stira {
namespace image {

/** \brief Special child data class to contain complex-valued lowpass levels for a subsampled complex wavelet transform
  * In essence a container for objects of the class PyramidLevel that contain the actual bands */
class CWTPyramid : public Pyramid< std::complex< double > >
{

public:
   /** \brief constructor 
     * \param pSourceBand grid containing the source data to be decomposed
     * \param myNrScales number of scales in the decomposition*/
   CWTPyramid(ArrayGrid<double>* pSourceBand, int myNrScales);
   
   /** \brief destructor */
   virtual ~CWTPyramid();
   
   /** \brief Gets 1st complex-valued lowpass image */
   ArrayGrid< std::complex< double > >* GetLowPassResidual1();
   
   /** \brief Sets 1st complex-valued lowpass image 
     * \param pBand 1st lowpass image to set*/
   void SetLowPassResidual1( ArrayGrid< std::complex< double > >* pBand);
   
   /** \brief Gets 2nd complex-valued lowpass image */
   ArrayGrid< std::complex< double > >* GetLowPassResidual2();
   
   /** \brief Sets 2nd complex-valued lowpass image 
     * \param pBand 2nd lowpass image to set*/
   void SetLowPassResidual2(ArrayGrid< std::complex< double > >* pBand);
   
   //void ExportBandsToPGM();

private:
   ArrayGrid< std::complex< double > >* mpLowPassResidual1; ///< 1st complex-valued lowpass image 
   ArrayGrid< std::complex< double > >* mpLowPassResidual2; ///< 2nd complex-valued lowpass image 
};

}
}

#endif
