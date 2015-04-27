
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

#ifndef STIRA_FFT_TRANSFERFUNCTIONGENERATOR_H
#define STIRA_FFT_TRANSFERFUNCTIONGENERATOR_H
#include <iostream>
#include <cstdlib>

#include "../../image/datastructures/Image.h"
#include "../../common/common/Definitions.h"

#include "FFTBand.h"

namespace stira {
namespace fouriertools {

/** \brief Generate transfer functions to be applied in the fourier domain */
class TransferFunctionGenerator{
public:

   /** \brief Constructor.*/
   TransferFunctionGenerator();

   /** \brief Destructor.*/
   ~TransferFunctionGenerator();

   /** \brief gets factors for scaling coordinates in Fourier domain
     * \param width   in:  width of the grid
     * \param height  in:  height of the grid
     * \param xFactor out: scaling factor in x direction
     * \param yFactor out: scaling factor in y direction*/
   static int GetScaleFactors(int width, int height, double& xFactor, double& yFactor);

   /** \brief Generates a highpass transfer function as an ArrayGrid object
     *
     * \param width width of grid to be generated
     * \param height height of grid to be generated
     * \param x1 lowpass frequency (from here to DC, all frequencies are 0)
     * \param x2 highpass frequency (from here to the edges, all frequencies are 1)
     * \return grid with transfer function */
   static image::ArrayGrid<double>* GenerateHighPassTransferFunction(int width, int height, double x1, double x2);

   /** \brief Generates a lowpass transfer function as an ArrayGrid object
     *
     * \param width width of grid to be generated
     * \param height height of grid to be generated
     * \param x1 lowpass frequency (from here to DC, all frequencies are 1)
     * \param x2 highpass frequency (from here to the edges, all frequencies are 0)
     * \return grid with transfer function */
   static image::ArrayGrid<double>* GenerateLowPassTransferFunction(int width, int height, double x1, double x2);

   /** \brief Generates a oriented transfer function as an ArrayGrid object
     *
     * \param width width of grid to be generated
     * \param height height of grid to be generated
     * \param orientationIndex number of the orientation to consider now
     * \param maxNrOfOrientations maximum number of orientations in this decomposition
     * \param isForward flag whether this transform is forward transform (if false; is backward transform)
     * \param mode enum whether the transfer function needs to produce a real or complex valued response
     * \return grid with transfer function */
   static FFTBand* GenerateOrientedTransferFunction(int width, int height, int orientationIndex, int maxNrOfOrientations, bool isForward, common::NumberMode mode=common::MODE_REAL);

   /** \brief Trick to distribute highest frequencies over set of bands
     * \param inoutGrid transfer function to be masked (is input as well as output)
     * \param nrBands nr of bands over wich to distribute the energy of this frequencies
     * \return grid with transfer function  */
   static void HighFrequencyCrossMask(FFTBand* inoutGrid, int nrBands);

   /** \brief Generates a LogGaussian axially symmetric transfer function
     * Help function for GenerateLogGaborBandTransferFunction
     *
     * \param width width of the grid with the transfer function
     * \param height height of the grid with the transfer function
     * \param centerFrequency distance from DC at which the maximum transfer occurs
     * \param bandWidth width of the transfer band
     * \return grid with transfer function */
   static image::ArrayGrid<double>* GenerateLogRadiusBand(int width, int height, double centerFrequency, double bandWidth);

   /** \brief Generates a angular Gaussian transfer function
     * Help function for GenerateLogGaborBandTransferFunction
     *
     * \param width width of the grid with the transfer function
     * \param height height of the grid with the transfer function
     * \param centerAngle angle on which the maximum transfer occurs
     * \param angleSpread angular width of the transfer band
     * \return grid with transfer function */
   static image::ArrayGrid<double>* GenerateGaussianAngularBand(int width, int height, double centerAngle, double angleSpread);

   /** \brief Generates a LogGabor transfer function
     * Source: Peter Kovesi:
     *    http://www.csse.uwa.edu.au/~pk/Research/MatlabFns/PhaseCongruency/Docs/convexpl.html
     * \param width width of the grid with the transfer function
     * \param height height of the grid with the transfer function
     * \param centerFrequency distance from DC at which the maximum transfer occurs
     * \param radialWidth radial width of the transfer band
     * \param centerAngle angle on which the maximum transfer occurs
     * \param angleSpread angular width of the transfer band
     * \return grid with transfer function */
   static image::ArrayGrid<double>* GenerateLogGaborBandTransferFunction(int width, int height, double centerFrequency, double radialWidth, double centerAngle, double angleSpread);

   /** \brief Generates a transfer function to suppress frequencies on the axes
     *
     * \param width width of the grid with the transfer function
     * \param height height of the grid with the transfer function
     * \param axisWidth width around the axis to suppress
     * \param x1 distance from DC up to which the axis frequencies are not suppressed
     * \param x2 distance from DC beyond which all frequencies are suppressed
     * \return grid with transfer function */
   static image::ArrayGrid<double>* GenerateAxisSuppressTransferFunction(int width, int height, int axisWidth, double x1, double x2);

   static image::ArrayGrid<double>* GenerateAxisExtractTransferFunction(int width, int height, int axisWidth );

   /** \brief Converts a Fourier domain transfer function to a filter kernel
     * \warning  the inverse Fourier Transform is applied to pTransferFunction, so take that into account when using this data after
     *           applying this function
     * \param pTransferFunction the transfer function to be converted
     * \param mode tells if the real or the imaginary values are taken after the Inverse Fourier Transform is applied to the transfer function*/
   static image::ArrayGrid<double>* ConvertTransferFunctionToFilterKernel( FFTBand* pTransferFunction, common::NumberMode mode = common::MODE_REAL );

   /** \brief Converts a Fourier domain transfer function to a filter kernel
     * \param pTransferFunction the transfer function to be converted
     * \param mode tells if the real or the imaginary values are taken after the Inverse Fourier Transform is applied to the transfer function*/
   static image::ArrayGrid<double>* ConvertTransferFunctionToFilterKernel( image::ArrayGrid<double>* pTransferFunction, common::NumberMode mode = common::MODE_REAL );

private:
   /** \brief Help function to deal with non-square images
     * \param inWidth width of grid to be generated
     * \param inHeight height of grid to be generated
     * \param outXFactor scale factor for x-coordinate
     * \param outYFactor scale factor for y-coordinate
     * \param inoutX1 smallest distance to DC of transition zone in the transfer function
     * \param inoutX2 largest distance to DC of transition zone in the transfer function */
   static void InitializeRatios(int inWidth, int inHeight, double& outXFactor, double& outYFactor, double& inoutX1, double& inoutX2);

   /** \brief Computes new x-coordinate when assuming that center of image is origin
     * \param x original x-coordinate in pixel coordinates
     * \param width width of grid to be generated
     * \param halfWidth half of the width of grid to be generated
     * \param xFactor scale factor for x-coordinate*/
   static double GetXn(double x, double width, double halfWidth, double xFactor);

   /** \brief Computes new y-coordinate when assuming that center of image is origin
     * \param y original y-coordinate in pixel coordinates
     * \param height height of grid to be generated
     * \param halfHeight half of the height of grid to be generated
     * \param yFactor scale factor for y-coordinate*/
   static double GetYn(double y, double height, double halfHeight, double yFactor);
};

}
}

#endif

