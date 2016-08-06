
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

#include <cmath>
#include <iostream>
#include "../../common/common/MathUtils.h"
#include "PerlinNoise.h"

using namespace std;

namespace stira {
namespace image {

using namespace common;

//--------------------------------------------------------------------------

PerlinNoise::PerlinNoise()
{
}

//--------------------------------------------------------------------------

PerlinNoise::~PerlinNoise()
{
}

//--------------------------------------------------------------------------

float PerlinNoise::Noise(int x, int y)
{
   int n = x + y * 57 + mSeed;
   n = (n << 13) ^ n;
   return (float) (1.0 - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
   //return value is always in range [-1.0, 1.0]
}

//--------------------------------------------------------------------------

float PerlinNoise::SmoothNoise(int x, int y)
{
   float corners = (Noise(x-1, y-1) + Noise(x+1, y-1) + Noise(x-1, y+1) + Noise(x+1, y+1)) / 16;
   float sides   = (Noise(x-1, y) + Noise(x+1, y) + Noise(x, y-1) + Noise(x, y+1)) / 8;
   float center  =  Noise(x, y ) / 4;
   return corners + sides + center;
}

//--------------------------------------------------------------------------

float PerlinNoise::Interpolate(float a, float b, float x)
{
   float ft = x * 3.1415927f;
   float f = (1.0 - std::cos(ft)) * .5f;

   return  a*(1.0-f) + b*f;
}

//--------------------------------------------------------------------------

float PerlinNoise::InterpolatedNoise(float x, float y)
{
   int wholePartX = (int) x;
   float fractionPartX = x - wholePartX;

   int wholePartY = (int) y;
   float fractionPartY = y - wholePartY;

   float v1 = SmoothNoise( wholePartX    , wholePartY     );
   float v2 = SmoothNoise( wholePartX + 1, wholePartY     );
   float v3 = SmoothNoise( wholePartX    , wholePartY + 1 );
   float v4 = SmoothNoise( wholePartX + 1, wholePartY + 1 );

   // first interpolate in x between (x, y), (x+1, y) and between (x, y+1), (x+1, y+1)
   float i1 = Interpolate( v1, v2, fractionPartX );
   float i2 = Interpolate( v3, v4, fractionPartX );

   // then interpolate in y
   return Interpolate( i1, i2, fractionPartY );
}

//--------------------------------------------------------------------------

Image* PerlinNoise::Generate( float persistence, int octaves, unsigned int width, unsigned int height, float red, float green, float blue, int seed, float zoom)
{
   mSeed = seed;
   Image* pData = new Image( width, height, 3 );
   for (unsigned int y = 0; y < height; ++y)
   {
      for (unsigned int x = 0; x < width; ++x)
      {
         float total = 0;
         float frequency = 1;
         float amplitude = 1;

         for (int i = 0; i < octaves; ++i)
         {
            total = total + InterpolatedNoise(x * frequency / zoom, y * frequency / zoom) * amplitude;
            frequency *= 2;
            amplitude *= persistence;
         }

         // simulate overflow out of range by applying modulo 255 to result
         ColorValue cv = ColorValue( MathUtils::ApplyModulo( (red   * (total + 1) * 127.5), 255.0 ),
                                     MathUtils::ApplyModulo( (green * (total + 1) * 127.5), 255.0 ),
                                     MathUtils::ApplyModulo( (blue  * (total + 1) * 127.5), 255.0 ),
                                     TYPE_RGB
                                   );

         // set resulting color at pixel location
         pData->SetColor(x, y, cv);
      }
   }
   return pData;
}

//--------------------------------------------------------------------------

Image* PerlinNoise::GenerateNormalized( float persistence, int octaves, unsigned int width, unsigned int height, float red, float green, float blue, int seed, float zoom)
{
   Image* pData = new Image( width, height, 3 );
   mSeed = seed;

   float min = 0;
   float max = 0;
   float maxColorMultiplier;
   float * pDataFloat = new float[width * height];

   //Generate raw float data
   for (unsigned int y = 0; y < height; ++y)
   {
      for (unsigned int x = 0; x < width; ++x)
      {
         float total = 0;
         float frequency = 1;
         float amplitude = 1;

         for (int i = 0; i < octaves; ++i)
         {
            total = total + InterpolatedNoise(x * frequency / zoom, y * frequency / zoom) * amplitude;
            frequency *= 2;
            amplitude *= persistence;
         }

         pDataFloat[y * width + x] = total;

         min = total < min ? total : min;
         max = total > max ? total : max;
      }
   }

   //Normalize color multipliers
   maxColorMultiplier = red > green ? red : green;
   maxColorMultiplier = blue > maxColorMultiplier ? blue : maxColorMultiplier;
   red   /= maxColorMultiplier;
   green /= maxColorMultiplier;
   blue  /= maxColorMultiplier;
   
   for (unsigned int y = 0; y < height; ++y)
   {
      for (unsigned int x = 0; x < width; ++x)
      {
         int index = x + y * width;
         ColorValue cv = ColorValue( ( red   * ((pDataFloat[index] - min) / (max - min)) * 255.0 ),
                                     ( green * ((pDataFloat[index] - min) / (max - min)) * 255.0 ),
                                     ( blue  * ((pDataFloat[index] - min) / (max - min)) * 255.0 ),
                                     TYPE_RGB
                                   );
         pData->SetColor(x, y, cv);
      }
   }

   delete []pDataFloat;
   return pData;
}

//--------------------------------------------------------------------------

}
}
