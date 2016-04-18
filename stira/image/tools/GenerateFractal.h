
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

#ifndef STIRA_IMAGE_TOOLS_GENERATEFRACTAL_H
#define STIRA_IMAGE_TOOLS_GENERATEFRACTAL_H

#include <complex>
#include "../datastructures/Image.h"
#include "../color/TransformColorSpace.h"

namespace stira {
namespace image {

/** \brief class to generate fractals
  * For now, only the Mandelbrot set is implemented */
class GenerateFractal
{
public:
   /** \brief constructor */
   GenerateFractal();
   
   /** \brief destructor */
   ~GenerateFractal();

   /** \brief Generates Mandelbrot set
     * http://en.wikipedia.org/wiki/Mandelbrot_set
     * \param centerX mathematical x coordinate of image center
     * \param centerY mathematical y coordinate of image center
     * \param width   mathematical image width */
   Image* CreateMandelbrot( double centerX, double centerY, double width );

   /** \brief Generates Julia set
     * http://www.karlsims.com/julia.html
     * \param centerX mathematical x coordinate of image center
     * \param centerY mathematical y coordinate of image center
     * \param width   mathematical image width */
   Image* CreateJulia( double centerX, double centerY, double width, double Cx, double Cy );

   /** \brief sets maximum number of iterations to test if a point can escape */
   void SetMaxNumberOfIterations( int maxNr );
   void SetEscapeRadius( double radius );

   void SetRenderDimensions( int width, int height );
   
private:

   /** \brief Generates Mandelbrot set
     * http://en.wikipedia.org/wiki/Mandelbrot_set
     * \param topX mathematical x coordinate of top right corner
     * \param topY mathematical y coordinate of top right corner
     * \param bottomX mathematical x coordinate of bottom left corner
     * \param bottomY mathematical y coordinate of bottom left corner
     * \param resolution number of pixels per mathematical distance unit */
   Image* CreateMandelbrot( double topX, double topY, double bottomX, double bottomY );

   /** \brief Generates Julia set
     * http://www.karlsims.com/julia.html
     * \param topX mathematical x coordinate of top right corner
     * \param topY mathematical y coordinate of top right corner
     * \param bottomX mathematical x coordinate of bottom left corner
     * \param bottomY mathematical y coordinate of bottom left corner
     * \param resolution number of pixels per mathematical distance unit
     * \param Cx real part of complex constant in iteration formula
     * \param Cy imag part of complex constant in iteration formula*/
   Image* CreateJulia( double topX, double topY, double bottomX, double bottomY, double Cx, double Cy );

   bool TestIsInMandelbrotMainBody( double x, double y );

   int GiveLastIteration( double xx, double yy, double x0, double y0, double& lastModulus );

   ColorValue InterpolateColorUltraFractal( double smoothColor );
   
   int mMaxNumberOfIterations;   ///< max. nr. of iterations to test if a point can escape

   double mEscapeRadius;
   double mEscapeRadiusSquared;   ///< squared radius in complex plane outside which the point is considered
                                  ///< to have "escaped" from the set after some nr of iterations
   
   /** \brief assigns a color according to the number of iterations required to escape*/
   ColorValue AssignColor( int iterationNumber );
   ColorValue AssignColorContinuous( int iterationNumber, double& lastModulus );
   ColorValue AssignColorUltraFractal( double smoothColor );

   TransformColorSpace* mpColorTransformer;  ///< color space transform object

   int mPixelWidth;
   int mPixelHeight;
   double mWidthHeightRatio;
   int mResolutionX;
   int mResolutionY;
};

}
}

#endif
