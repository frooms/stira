
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

#include "../datastructures/Image.h"
namespace stira {
namespace image {

/** \brief class to generate clouds of Perlin noise
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
   Image* GenerateMarble();
   Image* GenerateWood();

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
