
/***********************************************************************************
 *   Code from: http://lodev.org/cgtutor/randomnoise.html                          *
 *                                                                                 *
 *  Adaptations to integrate in stira framework Copyright (C) 2016 by Filip Rooms  *
 *                                                                                 *
 *  Terms and conditions for using this software in any form are provided in the   *
 *  file COPYING, which can be found in the root directory of this project.        *
 *                                                                                 *
 *   Contact data: filip.rooms@gmail.com                                           *
 *                 http://www.filiprooms.be/                                       *
 *                                                                                 *
 ***********************************************************************************/

#ifndef STIRA_IMAGE_TOOLS_TEXTUREGENERATOR_H
#define STIRA_IMAGE_TOOLS_TEXTUREGENERATOR_H

#include "../../imagedata/datastructures/Image.h"
namespace stira {
namespace imagetools {

using namespace imagedata;

/** \brief class to generate different kinds of textures
  *  code slightly adapted from  http://lodev.org/cgtutor/randomnoise.html
  */
class TextureGenerator
{
public:
    enum TextureType { TEXTURE_PERLIN, TEXTURE_WOOD, TEXTURE_MARBLE };

   /** \brief constructor */
   TextureGenerator( int width, int height, TextureType myTextureType );

   /** \brief destructor */
   ~TextureGenerator();

   Image* GenerateClouds();

   /** \brief Generates marble like texture
     * \param xPeriod defines repetition of marble lines in x direction
     * \param yPeriod defines repetition of marble lines in y direction
     * \param turbPower makes twists
     * \param turbSize initial size of the turbulence */
   Image* GenerateMarble( double xPeriod, double yPeriod, double turbPower, double turbSize );

   /** Generate wood-like texture
    *  \param xyPeriod number of rings
    *  \param turbPower makes twists
    *  \param turbSize initial size of the turbulence */
   Image* GenerateWood( double xyPeriod, double turbPower, double turbSize );

private:
   void GenerateNoise();

   double SmoothNoise(double x, double y);

   double Turbulence(double x, double y, double size);

   int mWidth;
   int mHeight;
   TextureType mTextureType;
   ArrayGrid<double>* mpNoise;
   TransformColorSpace* mTransformColorSpace;
};

}
}
#endif // TEXTUREGENERATOR_H
