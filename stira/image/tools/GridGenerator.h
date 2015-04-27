
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

#ifndef STIRA_IMAGE_TOOLS_GRIDGENERATOR_H
#define STIRA_IMAGE_TOOLS_GRIDGENERATOR_H

#include "../../common/common/Random.h"
#include "../datastructures/ArrayGrid.h"

namespace stira {
namespace image {

/**  \brief Generates different predefined grids
  */
class GridGenerator
{
public:
   /** \brief constructor*/
   GridGenerator();
   
   /** \brief destructor*/
   ~GridGenerator();
   
   /** \brief generates a flat image of given dimensions and given constant intensity
     * \param width width of grid to generate
     * \param heigh height of grid to generate
     * \param intensity constant intensity for all grid pixels*/
   static ArrayGrid<double>* GenerateEmpty(int width=256, int height=256, double intensity=127.0);

   /** \brief generates a flat image of given dimensions and given constant intensity contaminated with gaussian noise with given sigma
     * \warning grid values are *NOT* clipped to some range
     * \param width width of grid to generate
     * \param heigh height of grid to generate
     * \param intensity constant intensity for all grid pixels
     * \param sigma sigma of the Gaussian noise (mu = 0)*/
   static ArrayGrid<double>* GenerateEmptyPlusGaussianNoise(int width=256, int height=256, double intensity=127.0, double sigma=10.0);
   
   /** \brief generates a simple grid with horizontal intensity gradient
     * \param width width of grid to generate
     * \param height height of grid to generate*/
   static ArrayGrid<double>* GenerateHorizontalGradient(int width=256, int height=256);
   
   /** \brief generates a simple grid with horizontal intensity gradient
     * \param width width of grid to generate
     * \param height height of grid to generate*/
   static ArrayGrid<double>* GenerateVerticalGradient(int width=256, int height=256);
   
   /** \brief generates a simple grid with a horizontal frequency sine wave
     * \param width width of grid to generate
     * \param height height of grid to generate
     * \param frequency frequency of the sine wave*/
   static ArrayGrid<double>* GenerateHorizontalSineWave(int width, int height, double frequency);

   /** \brief generates a simple grid with vertical frequency sine wave
     * \param width width of grid to generate
     * \param height height of grid to generate
     * \param frequency frequency of the sine wave*/
   static ArrayGrid<double>* GenerateVerticalSineWave(int width, int height, double frequency);
   
   /** \brief generates a simple grid with Euclidean spot intensities
     * Used in AM halftoning; see PhD Stefaan Lippens, Ghent University, 2008-2009: 
     *                                  "Advanced Techniques for Digital Halftoning", p 194 eq 7.4
     * \param width width of grid to generate
     * \param height height of grid to generate
     * \param frequency frequency of the spots*/
   static ArrayGrid<double>* GenerateEuclideanSpots(int width, int height, double frequency);

   /** \brief generates a square with a star-shaped structure
     * In fact a sine that goes in polar coordinates nrPeriods times over the angular polar 
     * coordinate, while kept constant along the radial polar coordinate
     * \param sideSize size of single side of the square
     * \param nrPeriods number of periods of the sine wave along the angular coordinate*/
   static ArrayGrid<double>* GenerateStarChart(int sideSize, int nrPeriods );
   
   /** \brief generates a grid of alternating horizontal black and white bars
     * A version of this pattern where the bars become gradually blurred more and more 
     * is placed under filter::GaussConvolve for dependancy reasons (depends on gaussian filtering)
     * \param width width of the test pattern
     * \param height height of the test pattern
     * \param barWidth width of a bar in the image*/
   static ArrayGrid<double>* GenerateBars(int width, int height, int barWidth=50 );

// 1) PSF's / filter kernels
////////////////////////////
   
public:

   static ArrayGrid<double>* GenerateLine(int width, int height, double length, double angle );

   static ArrayGrid<double>* GenerateSquare(int width, int height, double suqareWidth);

   static ArrayGrid<double>* GenerateDisk(int width, int height, double diskWidth);

   /** \brief generates an Airy filter kernel 
    * more details, see http://en.wikipedia.org/wiki/Airy_disc 
    *
    * \warning uses j1(x) Bessel function from X/Open System Interfaces Extensions to math.h. 
    *          These are not present in any ANSI or ISO C standard.
    *          see http://en.wikipedia.org/wiki/Math.h
    * 
    * \param width width of the grid 
    * \param height height of the grid 
    * \param airyWidth width of the PSF
    * \return grid with the generated Airy filter kernel */
   static ArrayGrid<double>* GenerateAiry(int width, int height, double airyWidth);

   /** \brief generates a circular symmetric Gaussian filter kernel 
    * 
    * \param width width of the grid 
    * \param height height of the grid 
    * \param sigma sigma of the PSF
    * \return grid with the generated Gaussian filter kernel */
   static ArrayGrid<double>* GenerateGaussian (int width, int height, double sigma );

   /** \brief generates a Gaussian filter kernel 
    * 
    * \param width width of the grid 
    * \param height height of the grid 
    * \param sigmaX sigma in x direction for the PSF
    * \param sigmaY sigma in y direction for the PSF
    * \return grid with the generated Gaussian filter kernel */
   static ArrayGrid<double>* GenerateGaussian (int width, int height, double sigmaX, double sigmaY);


   /** \brief generates a Gaussian filter kernel 
    * 
    * \param width width of the grid 
    * \param height height of the grid 
    * \param sigma1 sigma1 for the PSF
    * \param sigma2 sigma2 for the PSF
    * \param rho rho for the PSF ( must be in ] -1, 1 [ or we divide by 0 )
    * \return grid with the generated Gaussian filter kernel */
   static ArrayGrid<double>* GenerateGaussian (int width, int height, double sigma1, double sigma2, double rho);
   
   /** \brief generates a first derivative in x of Gaussian filter kernel 
    * 
    * \param width width of the grid 
    * \param height height of the grid 
    * \param sigma sigma for the filter kernel
    * \return grid with the generated first derivative in x of Gaussian filter kernel */
   static ArrayGrid<double>* GenerateGaussianFirstDerivativeX(int width, int height, double sigmaX, double sigmaY );
   
   /** \brief generates a first derivative in y of Gaussian filter kernel 
    * 
    * \param width width of the grid 
    * \param height height of the grid 
    * \param sigma sigma for the filter kernel
    * \return grid with the generated first derivative in y of Gaussian filter kernel */
   static ArrayGrid<double>* GenerateGaussianFirstDerivativeY(int width, int height, double sigmaX, double sigmaY );

   /** \brief generates a second derivative in x of Gaussian filter kernel 
    * 
    * \param width width of the grid 
    * \param height height of the grid 
    * \param sigma sigma for the filter kernel
    * \return grid with the generated PSF */
   static ArrayGrid<double>* GenerateGaussianSecondDerivativeX (int width, int height, double sigmaX, double sigmaY );

   /** \brief generates a second derivative in y of Gaussian filter kernel 
    * 
    * \param width width of the grid 
    * \param height height of the grid 
    * \param sigma sigma for the filter kernel
    * \return grid with the generated PSF */
   static ArrayGrid<double>* GenerateGaussianSecondDerivativeY (int width, int height, double sigmaX, double sigmaY );

   /** \brief generates mixed first derivatives in x and y of Gaussian filter kernel 
    * 
    * \param width width of the grid 
    * \param height height of the grid 
    * \param sigma sigma for the filter kernel
    * \return grid with the generated PSF */
   static ArrayGrid<double>* GenerateGaussianMixedDerivativesXY (int width, int height, double sigmaX, double sigmaY );
   
   /** \brief generates delta peak
    * 
    * \param width width of the grid 
    * \param height height of the grid 
    * \param x x coordinate of delta peak
    * \param y y coordinate of delta peak
    * \param intensity intensity of delta peak
    * Well, normally, we would have an infinite peak at a mathematical point, but a pixel is not 
    * a mathematical point, so we allow extra scaling how high this peak is
    * \return grid with the generated delta peak */
   static ArrayGrid<double>* GenerateDeltaPeak(int width, int height, int x, int y, double intensity );


// 2) Zone plate
////////////////
   
public:
   /** \brief generates the inverse zoneplate test image 512x512 pixels*/
   static ArrayGrid<double>* GenerateInverseZonePlate ( );
   
   /** \brief generates the classical zoneplate test image 512x512 pixels*/
   static ArrayGrid<double>* GenerateZonePlate ( );
   
   /** \brief generates Log Frequency-Contrast test image
     * as shown on http://www.imatest.com/docs/log_f_Cont.html
     * Change in frequency here is exponential of sqrt of x (empirical)
     * Change in contrast is inverse square of y (like in doc imatest)*/
   static ArrayGrid<double>* GenerateLogFrequencyContrastChart( );

// 3) Shepp-Logan
/////////////////
   
public:
   /** \brief generates the classical Shepp-Logan phantom for CT 512x512 pixels
     * Based on http://server.oersted.dtu.dk/ftp/jaj/31655/ct_programs/ (no longer available)
     * Hugh Murrell, Computer Aided Tomography, The Mathematica Journal, 1996, Vol 6, No. 2, pp.60-65
     * similar to java code of Thevenaz found on http://bigwww.epfl.ch/thevenaz/shepplogan/
     * \param factor factor with which to multiply the intensities inside the small inner ellipses to modify the contrast*/
   static ArrayGrid<double>* GenerateSheppLogan( double factor=1.0 );
   
private:
   /** \brief Helper function for Shepp-Logan phantom generator: adds single ellipse
     * \param pGrid grid in which to add ellipse
     * \param xCenter normalized x coordinate of ellipse center
     * \param yCenter normalized y coordinate of ellipse center
     * \param majorAxis normalized major axis of ellipse
     * \param minorAxis normalized minor axis of ellipse
     * \param angle rotation angle of ellipse, in degrees
     * \param value value to add to image when inside the ellipse*/
   static void AddEllipse( ArrayGrid<double>* pGrid, double xCenter, double yCenter, double majorAxis, double minorAxis, double angle, double value);
      
// 4) ISING-process generated texture
//     see ~/develop/c/metropolis/metropolis.c for original program
//     TODO finish: doesn't work properly yet: coherence is lost at bottom of image
///////////////////////////////////////////////////////////////////////////////////
   
public:
   /** \brief generates a random field texture using Ising model and simulated annealing*/
   static ArrayGrid<int>* GenerateIsingTexture( );
   
private:
   
   static void UpdateIsingState( ArrayGrid<int>* pGrid, double T, double beta, Random* pRandom);
   static void InitializeIsingState( ArrayGrid<int>* pGrid, Random* pRandom);
   static void WriteCurrentIsingState( ArrayGrid<int>* pGrid, int iterationNr);


};
}
}

#endif
