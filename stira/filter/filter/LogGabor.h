
#ifndef STIRA_FILTER_LOGGABOR_H
#define STIRA_FILTER_LOGGABOR_H

/***********************************************************************************
 *   Copyright (C) 2010 by Filip Rooms                                             *
 *                                                                                 *
 *  Terms and conditions for using this software in any form are provided in the   *
 *  file COPYING, which can be found in the root directory of this project.        *
 *                                                                                 *
 *   Contact data: filip.rooms@gmail.com                                           *
 *                 http://www.filiprooms.be/                                       *
 *                                                                                 *
 ***********************************************************************************/

#include <stdint.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "../../image/datastructures/Image.h"

namespace stira{
namespace filter{

/** \brief Generates Log Gabor filtered image
  * Fourier domain transfer function is implemented in fouriertools/TransferFunctionGenerator
  * Reference: Peter Kovesi:
  *    http://www.csse.uwa.edu.au/~pk/Research/MatlabFns/PhaseCongruency/Docs/convexpl.html*/
class LogGabor
{
public:
   /** \brief constructor
     * \param pImage input image on which to apply the filter */
   LogGabor( image::Image *pImage );

   /** \brief destructor */
   ~LogGabor( );

   /** \brief Gets the frequency radius of the middle of the frequency band to filter*/
   double GetCenterFrequency();

   /** \brief Sets the radius of the middle of the frequency band to filter
     * \param centerFrequency radius of the middle of the frequency band to filter*/
   void SetCenterFrequency( double centerFrequency );

   /** \brief Gets the width in the radial direction of the frequency band to filter */
   double GetRadialWidth();

   /** \brief Sets the width in the radial direction of the frequency band to filter
     * \param radialWidth width of the frequency band to filter*/
   void SetRadialWidth( double radialWidth );

   /** \brief Gets the central angle of the frequency band to filter */
   double GetCenterAngle();

   /** \brief Sets the central angle of the frequency band to filter
     * \param centerAngle central angle of the frequency band to filter */
   void SetCenterAngle( double centerAngle );

   /** \brief Gets the width in the angular direction of the frequency band to filter */
   double GetAngleSpread();

   /** \brief Sets the width in the angular direction of the frequency band to filter
     * \param angleSpread the width in the angular direction of the frequency band to filter */
   void SetAngleSpread( double angleSpread );

   /** \brief Creates an output image with the real component of the response of the filter
     * \param rescaleVisualize flag whether or not the output needs to be rescaled between 0 and 255 */
   image::Image* GetRealResponse( bool rescaleVisualize=true );

   /** \brief Creates an output image with the imaginary component of the response of the filter
     * \param rescaleVisualize flag whether or not the output needs to be rescaled between 0 and 255 */
   image::Image* GetImagResponse( bool rescaleVisualize=true );

   /** \brief Creates an output image with the transfer function corresponding with the filter
     * \param rescaleVisualize flag whether or not the output needs to be rescaled between 0 and 255 */
   image::Image* GetTransferFunction( bool rescaleVisualize=true );

   /** \brief Creates an output image with the magnitude of the complex response of the filter
     * \param rescaleVisualize flag whether or not the output needs to be rescaled between 0 and 255 */
   image::Image* GetMagnitude( bool rescaleVisualize=true );

   /** \brief prints the parameter for the log-Gabor filter on the command line */
   void PrintParameters();

   /** \brief run method of this class */
   void Run();

private:
   image::Image *mpImage;  ///< input image
   double mCenterFrequency; ///< the central angle of the frequency band to filter
   double mRadialWidth; ///< the width in the radial direction of the frequency band to filter
   double mCenterAngle; ///< the central angle of the frequency band to filter
   double mAngleSpread; ///< the width in the angular direction of the frequency band to filter

   image::Image *mpImageReal;  ///< image with the real component of the response of the filter
   image::Image *mpImageImag;  ///< image with the imaginary component of the response of the filter
   image::Image *mpImageTransfer;  ///< image with the transfer function corresponding with the filter

};

}
}
#endif // LOGGABOR_H
