
/***********************************************************************************
 *   Code from: http://infohost.nmt.edu/~imcgarve/perlin_noise/                    *
 *                                                                                 *
 *  Adaptations to integrate in stira framework Copyright (C) 2009 by Filip Rooms  *
 *                                                                                 *
 *  Terms and conditions for using this software in any form are provided in the   *
 *  file COPYING, which can be found in the root directory of this project.        *
 *                                                                                 *
 *   Contact data: filip.rooms@gmail.com                                           *
 *                 http://www.filiprooms.be/                                       *
 *                                                                                 *
 ***********************************************************************************/

#ifndef STIRA_IMAGE_TOOLS_PERLINNOISE_H
#define STIRA_IMAGE_TOOLS_PERLINNOISE_H

#include "../../imagedata/datastructures/Image.h"

namespace stira {
namespace image {

/** \brief class to generate clouds of Perlin noise
  *  code slightly adapted from code of Isaac McGarvey: 
  *            http://infohost.nmt.edu/~imcgarve/perlin_noise/
  *
  *  to check for other textures: http://lodev.org/cgtutor/randomnoise.html
  */
class PerlinNoise
{
public:
   /** \brief constructor */
   PerlinNoise();
   
   /** \brief destructor */
   ~PerlinNoise();
   
   /** \brief Generates an Image containing Perlin clouds
     * Values are allowed to overfloat; afterwards, they are put back in the range with a modulus operation
     * \param persistence factor with which the noise per octave is multiplied
     * \param octaves nr of octaves ("different frequencies") used in generating the Perlin noise
     * \param width   width of image to generate
     * \param height  height of image to generate
     * \param red   relative fraction of red in general background color
     * \param green relative fraction of green in general background color
     * \param blue  relative fraction of blue in general background color
     * \param seed seed to initialize random generator
     * \param zoom zoom factor */
   Image* Generate( float persistence, int octaves, unsigned int width, unsigned int height, float red, float green, float blue, int seed, float zoom);
   
   /** \brief Generates an Image containing normalized Perlin clouds
     * Values are scaled in the right range with linear range rescaling
     * \param persistence factor with which the noise per octave is multiplied
     * \param octaves nr of octaves ("different frequencies") used in generating the Perlin noise
     * \param width   width of image to generate
     * \param height  height of image to generate
     * \param red   relative fraction of red in general background color
     * \param green relative fraction of green in general background color
     * \param blue  relative fraction of blue in general background color
     * \param seed seed to initialize random generator
     * \param zoom zoom factor */
   Image* GenerateNormalized( float persistence, int octaves, unsigned int width, unsigned int height, float red, float green, float blue, int seed, float zoom);
private:
   /** \brief Actual pseudo-random generator to generate single noise sample associated with a pixel position*/
   float Noise(int x, int y);
   
   /** \brief Generates smoothened noise pixel based on generating noise neighbors in 3x3 neighborhood*/
   float SmoothNoise(int x, int y);
   float Interpolate(float a, float b, float x);
   float InterpolatedNoise(float x, float y);

   int mSeed;  ///< seed for the random generator
};

}
}

#endif
