
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

#ifndef STIRA_FFT_FFTCALCULATOR_H
#define STIRA_FFT_FFTCALCULATOR_H

#include "FFTBand.h"

#include "kiss_fft.h"
#include "kiss_fftnd.h"

namespace stira {
namespace fouriertools {

/** \brief Parent class to compute the Fourier transforms based on several libraries
  * Survey of FFT implementations: http://www.jjj.de/fft/fftpage.html
  * Child classes specifically offer interface to
  *  - FFTWCalculator : FFTW http://www.fftw.org/
  *  - KISSFFTCalculator : Kiss FFT http://sourceforge.net/projects/kissfft/ */
class FFTCalculator
{

public:
   /** \brief construct an FFT calculator initialized with and FFTBand 
     * \param pComplexGrid pointer to an ArrayGrid of complex values*/
   FFTCalculator( image::ArrayGrid< std::complex<double> >* pComplexGrid);
   
   /** \brief construct an FFT calculator; not initialized*/
   FFTCalculator();

   /** \brief destructor */
   virtual ~FFTCalculator();

   /** \brief Computes the forward FFT*/
   virtual void ApplyForwardTransform()=0;

   /** \brief Computes the inverse FFT */
   virtual void ApplyInverseTransform()=0;

   /** \brief Switches the four quadrants by mirroring them around the center of the image
     * As source image, the image given at construction time is used */
   void SwitchQuadrants();

   /** \brief Switches the four quadrants by mirroring them around the center of the image 
     * \param pGridIn the grid of which the quadrants are to be switched (object itself is altered; no new object created)*/
   void SwitchQuadrants(image::ArrayGrid<std::complex<double> > *pGridIn);

protected:
   /** \brief help method to create the intermediate data structures for the underlying library */
   virtual bool CreateLibData( image::ArrayGrid< std::complex<double> >* pGridin )=0;

   /** \brief help method to clean the intermediate input data structures for the underlying library */
   virtual bool CleanLibData()=0;

   /** \brief Converts the KISS data structure with the result back to an FFTBand */
   virtual void WriteResultInFFTBand()=0;
   
   image::ArrayGrid< std::complex<double> >* mpComplexGrid;   ///< Grid with the complex data
   
   int mWidth;  ///< width of the data
   int mHeight;  ///< height of the data
};

}
}

#endif

