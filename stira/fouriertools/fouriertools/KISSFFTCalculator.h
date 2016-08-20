
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

#ifndef STIRA_FFT_KISSFFTCALCULATOR_H
#define STIRA_FFT_KISSFFTCALCULATOR_H

#include "FFTCalculator.h"

#include "kiss_fft.h"
#include "kiss_fftnd.h"

namespace stira {
namespace fouriertools {

using namespace imagedata;

/** \brief A class to compute the Fourier transforms based on the KISS FFT library by Mark Borgerding
  * Mark Borgerding wrote all the *kiss_fft* files
  * Source: http://sourceforge.net/projects/kissfft/  */
class KISSFFTCalculator : public FFTCalculator
{

public:
   /** \brief construct an FFT calculator initialized with and FFTBand 
     * \param pComplexGrid pointer to an ArrayGrid of complex values*/
   KISSFFTCalculator( ArrayGrid< std::complex<double> >* pComplexGrid);
   
   KISSFFTCalculator();

   /** \brief destructor */
   ~KISSFFTCalculator();

   /** \brief Computes the forward FFT*/
   void ApplyForwardTransform();

   /** \brief Computes the inverse FFT */
   void ApplyInverseTransform();
   
   /** \brief Computes the inverse FFT 
     * \param pGridIn the input grid for the forward transform
     * \return a complex-valued grid containing the transformed data; the caller becomes responsible to delete it.*/
   ArrayGrid< std::complex<double> >* ApplyInverseTransform( ArrayGrid< std::complex<double> >* pGridIn);

private:
   /** \brief help method to create the intermediate data structures for the KISS FFT library */
   bool CreateLibData( ArrayGrid< std::complex<double> >* pGridin );

   /** \brief help method to clean the intermediate input data structures for the KISS FFT library */
   bool CleanLibData();

   /** \brief Converts the KISS data structure with the result back to an FFTBand */
   void WriteResultInFFTBand();

   kiss_fft_cpx* mpInKISSData;   ///< intermediate data structure for the KISS library
   kiss_fft_cpx* mpOutKISSData;  ///< intermediate data structure for the KISS library
};

}
}

#endif

