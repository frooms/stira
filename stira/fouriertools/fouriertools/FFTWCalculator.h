
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

#ifndef STIRA_FFT_FFTWCALCULATOR_H
#define STIRA_FFT_FFTWCALCULATOR_H

#include "FFTCalculator.h"
#include <fftw3.h>

namespace stira {
namespace fouriertools {

using namespace imagedata;

/** \brief A class to compute the Fourier transforms based on the FFTW library  */
class FFTWCalculator : public FFTCalculator
{

public:
   /** \brief construct an FFT calculator initialized with data from an FFTBand 
     * \param pComplexGrid pointer to an ArrayGrid of complex values*/
   FFTWCalculator( ArrayGrid< std::complex<double> >* pComplexGrid);
   
   /** \brief construct an empty FFT calculator*/
   FFTWCalculator();

   /** \brief destructor */
   virtual ~FFTWCalculator();

   /** \brief Computes the forward FFT */
   virtual void ApplyForwardTransform();

   /** \brief Computes the inverse FFT */
   virtual void ApplyInverseTransform();

private:
   /** \brief help method to create the intermediate data structures for the FFTW library */
   bool CreateLibData( ArrayGrid< std::complex<double> >* pGridin );

   /** \brief help method to clean the intermediate input data structures for the FFTW library */
   bool CleanLibData();

   /** \brief Converts the FFTW data structure with the result back to an FFTBand */
   void WriteResultInFFTBand();

   fftw_complex* mpInFFTWData;   ///< intermediate data structure for the FFTW library
   fftw_complex* mpOutFFTWData;  ///< intermediate data structure for the FFTW library
};

}
}

#endif

