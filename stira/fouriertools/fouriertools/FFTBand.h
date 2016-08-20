
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

#ifndef STIRA_FFT_FFTBAND_H
#define STIRA_FFT_FFTBAND_H

#include <complex>

#include "../../imagedata/datastructures/ArrayGrid.h"

namespace stira {
namespace fouriertools {

using namespace imagedata;

enum FFTTransformDirection {FORWARD, BACKWARD};

enum FFTDataType {RE, IM};

/** \brief data structure for FFT manipulations*/
class FFTBand
{
public:
   /** \brief Constructor: build a complex band initialized by a real-valued grid
     * \param pGrid grid to initialize this complex band with 
     * \param isreal flag if real-valued grid values should be used as the real components of the complex numbers (if false: use as imag components)
     */
   FFTBand( ArrayGrid<double>* pGrid, bool isreal = true);
   
   /** \brief Constructor: build a complex band initialized by a complex-valued grid
     * \param pGrid grid to initialize this complex band with */
   FFTBand( ArrayGrid<std::complex <double> >* pGrid );

   /** \brief Constructor: build a complex band initialized by zeros
     * \param width width of the band to construct
     * \param height height of the band to construct 
     * \param initValue optional value to initialize this band with*/
   FFTBand( int width, int height, std::complex< double > initValue = std::complex< double >( 0.0, 0.0 ) );
   
   /** \brief Copy constructor */
   FFTBand( FFTBand &otherFFTBand );

   /** \brief destructor */
   ~FFTBand();
   
   /** \brief clones the current band */
   FFTBand* Clone();
   
   /** \brief Get a value from the complex band 
     * \param x x coordinate of the value to get
     * \param y y coordinate of the value to get */
   std::complex< double > GetValue( int x, int y ) const;

   /** \brief Set a value in the complex band using a complex data type from STL
     * \param x x coordinate of the value to set
     * \param y y coordinate of the value to set
     * \param complexValue the value to set */
   void SetValue( int x, int y, std::complex<double> complexValue );
   
   /** \brief Set a value in the complex band using two double representing the real and imaginary part of the complex number
     * \param x x coordinate of the value to set
     * \param y y coordinate of the value to set
     * \param realValue real part of the complex number to set 
     * \param imagValue imaginary part of the complex number to set */
   void SetValue( int x, int y, double realValue, double imagValue );

   /** \brief Get width of data grid */
   int GetWidth() const;

   /** \brief Get height of data grid */
   int GetHeight() const;

   /** \brief Replaces the current FFTBand with a forward transformed one */
   void ApplyForwardTransform();

   /** \brief Replaces the current FFTBand with an inverse transformed one */
   void ApplyInverseTransform();
   
   /** \brief Mirrors the whole band around the center of the band
     * Changes the original data structure (not creating a new one)*/
   void PointMirrorBand();
   
   /** \brief creates a real-valued ArrayGrid with the real component of the complex values in this FFTBand*/
   ArrayGrid<double>* ConvertToRealGrid( );
   
   /** \brief creates a real-valued ArrayGrid with the imaginary component of the complex values in this FFTBand*/
   ArrayGrid<double>* ConvertToImaginaryGrid( );
   
   /** \brief creates a complex-valued ArrayGrid with the complex values in this FFTBand*/
   ArrayGrid<std::complex<double> >* ConvertToComplexGrid( );
   
   /** \brief export abs of current FFTBand to a PGM file 
     * \param fileName name of PGM to export to */
   void ExportAbsImage( std::string fileName );
   
   /** \brief switches upper left with lower right quadrant and lower left with upper right
     * Changes the original data structure (not creating a new one)*/
   void SwitchQuadrants();
   
   /** \brief changes all complex grid values in their complex conjugate values
     * Changes the original data structure (not creating a new one)*/
   void Conjugate();

   /** \brief gets maximum value of real or imaginary components in the band
     * \param type real or imaginary component*/
   double GetBandMaximum(FFTDataType type);
   
   /** \brief gets minimum value of real or imaginary components in the band
     * \param type real or imaginary component*/
   double GetBandMinimum(FFTDataType type);
   
   /** \brief multiplies this FFTBand point by point with another FFTBand
     * \param other the other FFTBand
     * \warning works directly on the band data; original data is lost*/
   void Multiply(FFTBand* other);
   
   /** \brief multiplies this FFTBand point by point with an ArrayGrid
     * \param grid the ArrayGrid
     * \warning works directly on the band data; original data is lost*/
   void Multiply(ArrayGrid<double>* grid);
   
   /** \brief multiplies this FFTBand point by point with a real-valued factor
     * \param myFactor factor to multiply every value in the grid with
     * \warning works directly on the band data; original data is lost*/
   void Multiply(std::complex<double> myFactor);

   /** \brief multiplies this FFTBand point by point with a complex-valued factor
     * \param myFactor factor to multiply every value in the grid with
     * \warning works directly on the band data; original data is lost*/
   void Multiply(double myFactor);

private:

   void InitializeFFTBandValuesFromGrid( ArrayGrid<double>* pGrid, bool isreal);

   /** \brief Initializes this FFTBand with a constant value 
     * \param initValue optional value to initialize this band with*/
   bool InitializeBandWithConstantValue( std::complex<double> initValue=std::complex<double>(0.0, 0.0) );
   
   /** \brief Initializes this FFTBand with real-valued values of the band of an image
     * The real components get the values from the grid, the imaginary components are set to zero
     * \param pGrid image band to initialize this FFTBand from */
   bool InitializeBandWithRealValues( ArrayGrid<double>* pGrid );
   
   /** \brief Initializes this FFTBand with imaginary values of the band of an image 
     * The real components are set to zero, the imaginary components get the values from the grid
     * \param pGrid image band to initialize this FFTBand from */
   bool InitializeBandWithImagValues( ArrayGrid<double>* pGrid );
   
   /** \brief Initializes this FFTBand with complex values of the band of an image 
     * \param pGrid image band to initialize this FFTBand from */
    bool InitializeBandWithComplexValues( ArrayGrid< std::complex<double> >* pGrid );
   
   ArrayGrid< std::complex<double> >* mpFFTGrid;///< Data grid containing the complex fourier data
};
}
}

#endif

