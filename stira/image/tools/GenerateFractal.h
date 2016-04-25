
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
#include "../../common/common/MonotonicCubicSplineInterpolator.h"

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

   /** \brief sets the maximum number of iterations to test if a point can escape
     * \param maxNr the maximal number of iterations */
   void SetMaxNumberOfIterations( int maxNr );

   /** \brief sets the escape radius if a point has escaped after a certain number of iterations
     * \param radius the escape radius */
   void SetEscapeRadius( double radius );

   /** \brief sets the render dimensions
     * \param width the number of pixels in x direction of the final image
     * \param height the number of pixels in y direction of the final image */
   void SetRenderDimensions( int width, int height );

   /** \brief Gets the number of pixels per mathematical unit length in the x direction */
   double GetResolutionX();

   /** \brief Gets the number of pixels per mathematical unit length in the y direction */
   double GetResolutionY();

   /** \brief Gets the mathematical center of the generated fractal */
   common::Point<double> GetMathCenterPoint();

   /** \brief Gets the mathematical width of the generated image */
   double GetMathWidth();

   /** \brief Gets the number of pixels in x direction of the final image */
   double GetPixelWidth();

   /** \brief gets the number of pixels in x direction of the final image */
   double GetPixelHeight();
   
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

   /** \brief Tests whether a point is inside the cardioid or in the period-2 bulb to reduce computations */
   bool TestIsInMandelbrotMainBody( double x, double y );

   int GiveLastIteration( double xx, double yy, double x0, double y0, double& lastModulus );

   ColorValue InterpolateColorUltraFractal( double smoothColor );

   /** \brief assigns a color according to the number of iterations in a continuous way */
   ColorValue AssignColorContinuous( int iterationNumber, double& lastModulus );

   /** \brief assigns a color according to the number of iterations according to the UlraFractal way
     * \remark still uses linear interpolation instead of Monocubic interpolation for the time being */
   ColorValue AssignColorUltraFractal( double smoothColor, double& lastModulus );

   int mMaxNumberOfIterations;   ///< max. nr. of iterations to test if a point can escape

   double mEscapeRadius;  ///< radius in complex plane outside which the point is considered
                          ///< to have "escaped" from the set after some number of iterations
   double mEscapeRadiusSquared;   ///< squared of the escape radius

   double mPixelWidth;     ///< the number of pixels in x direction of the final image
   double mPixelHeight;     ///< the number of pixels in x direction of the final image
   double mWidthHeightRatio;
   double mResolutionX;     ///< the number of pixels per mathematical unit in x direction
   double mResolutionY;     ///< the number of pixels per mathematical unit in y direction

   double mMathCenterX;  ///< x coordinate of the mathematical center of the generated fractal image
   double mMathCenterY;  ///< y coordinate of the mathematical center of the generated fractal image
   double mMathWidth;  ///< the mathematical width of the generated fractal image

   TransformColorSpace* mpColorTransformer;  ///< color space transform object

   common::MonotonicCubicSplineInterpolator* mpInterpolateRed;
   common::MonotonicCubicSplineInterpolator* mpInterpolateGreen;
   common::MonotonicCubicSplineInterpolator* mpInterpolateBlue;
};

}
}

#endif
