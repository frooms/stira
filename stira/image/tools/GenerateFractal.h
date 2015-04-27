
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
     * \param topX mathematical x coordinate of top right corner
     * \param topY mathematical y coordinate of top right corner
     * \param bottomX mathematical x coordinate of bottom left corner
     * \param bottomY mathematical y coordinate of bottom left corner
     * \param resolution number of pixels per mathematical distance unit */
   Image* CreateMandelbrot( double topX, double topY, double bottomX, double bottomY, double resolution );

   /** \brief Generates Mandelbrot set
     * http://en.wikibooks.org/wiki/Fractals/Iterations_in_the_complex_plane/Julia_set
     * http://eldar.mathstat.uoguelph.ca/dashlock/ftax/Julia.html
     * \warning Not functional yet!!!
     * \param topX mathematical x coordinate of top right corner
     * \param topY mathematical y coordinate of top right corner
     * \param bottomX mathematical x coordinate of bottom left corner
     * \param bottomY mathematical y coordinate of bottom left corner
     * \param resolution number of pixels per mathematical distance unit
     * \param Cx real part of complex constant in iteration formula
     * \param Cy imag part of complex constant in iteration formula*/
   Image* CreateJulia( double topX, double topY, double bottomX, double bottomY, double resolution, double Cx, double Cy );
   
   void SetMaxNumberOfIterations( int maxNr );   ///< max. nr. of iterations to test if a point can escape
   
   void SetEscapeRadiusSquared( double radiusSquared );
   
private:

   double EstimateExternalDistance( double lastZx, double lastZy,  double previousZx, double previousZy,  double previousdZx, double previousdZy);

   int GiveLastIteration( double xx, double yy, double x0, double y0, double& lastModulus );
   
   int mMaxNumberOfIterations;   ///< max. nr. of iterations to test if a point can escape
   double mEscapeRadiusSquared;   ///< sqaured radius in complex plane outside which the point is considered 
                                  ///< to have "escaped" from the set after some nr of iterations
   
   /** \brief assigns a color according to the number of iterations required to escape*/
   ColorValue AssignColor( int iterationNumber );
   ColorValue AssignColorContinuous( int iterationNumber, double& lastModulus );

   
   TransformColorSpace* mpColorTransformer;  ///< color space transform object
};

}
}

#endif
