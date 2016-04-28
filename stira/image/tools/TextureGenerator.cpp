
/***********************************************************************************
 *   Code from: http://infohost.nmt.edu/~imcgarve/perlin_noise/                    *
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

#include <cmath>
#include <iostream>
#include "../../common/common/MathUtils.h"
#include "../color/ColorValue.h"
#include "../color/TransformColorSpace.h"

#include "TextureGenerator.h"

using namespace std;

namespace stira {
namespace image {

using namespace common;


TextureGenerator::TextureGenerator( int width, int height, TextureType myTextureType )
{
   mWidth = width;
   mHeight = height;
   mTextureType = myTextureType;
   mpNoise = new ArrayGrid<double>(width, height);
   mTransformColorSpace = new TransformColorSpace();
}


TextureGenerator::~TextureGenerator()
{
   delete mpNoise;
   delete mTransformColorSpace;
}

void TextureGenerator::GenerateNoise()
{
   for (int y = 0; y < mHeight; y++)
   {
      for (int x = 0; x < mWidth; x++)
      {
         mpNoise->SetValue(x, y, (rand() % 32768) / 32768.0 );
      }
   }
}

double TextureGenerator::SmoothNoise(double x, double y)
{
   //get fractional part of x and y
   double fractX = x - int(x);
   double fractY = y - int(y);

   //wrap around
   int x1 = (int(x) + mWidth) % mWidth;
   int y1 = (int(y) + mHeight) % mHeight;

   //neighbor values
   int x2 = (x1 + mWidth - 1) % mWidth;
   int y2 = (y1 + mHeight - 1) % mHeight;

   //smooth the noise with bilinear interpolation
   double value = 0.0;
   value += fractX         * fractY         * mpNoise->GetValue( x1, y1 );
   value += (1.0 - fractX) * fractY         * mpNoise->GetValue( x2, y1 );
   value += fractX         * (1.0 - fractY) * mpNoise->GetValue( x1, y2 );
   value += (1.0 - fractX) * (1.0 - fractY) * mpNoise->GetValue( x2, y2 );

   return value;
}

double TextureGenerator::Turbulence(double x, double y, double size)
{
   double value = 0.0, initialSize = size;

   while(size >= 1)
   {
      value += SmoothNoise(x / size, y / size) * size;
      size /= 2.0;
   }

   return( 128.0 * value / initialSize );
}

Image* TextureGenerator::GenerateClouds()
{
   Image* pTextureOut = new Image( mWidth, mHeight, 3);
   GenerateNoise();
   for(int y = 0; y < mHeight; y++)
   {
      for(int x = 0; x < mWidth; x++)
      {
         double L = (192.0 + (Turbulence(x, y, 64.0)) / 4.0 ) / 255.0;

         ColorValue colorHSL = ColorValue(240, 1.0, L, TYPE_HSL );
         ColorValue colorRGB = mTransformColorSpace->HSLtoRGB( colorHSL );
         pTextureOut->SetColor(x, y, colorRGB);
      }
   }
   return pTextureOut;
}

Image* TextureGenerator::GenerateMarble()
{
    Image* pTextureOut = new Image( mWidth, mHeight, 3);
    GenerateNoise();

    //xPeriod and yPeriod together define the angle of the lines
    //xPeriod and yPeriod both 0 ==> it becomes a normal clouds or turbulence pattern
    double xPeriod = 5.0; //defines repetition of marble lines in x direction
    double yPeriod = 10.0; //defines repetition of marble lines in y direction
    //turbPower = 0 ==> it becomes a normal sine pattern
    double turbPower = 5.0; //makes twists
    double turbSize = 32.0; //initial size of the turbulence

    for(int y = 0; y < mHeight; y++)
    for(int x = 0; x < mWidth; x++)
    {
      double xyValue = x * xPeriod / mWidth + y * yPeriod / mHeight + turbPower * Turbulence(x, y, turbSize) / 256.0;
      double sineValue = 256 * fabs(sin(xyValue * 3.14159));
      ColorValue cv = ColorValue( sineValue, sineValue, sineValue );
      pTextureOut->SetColor(x, y, cv );
    }
    return pTextureOut;
}

Image* TextureGenerator::GenerateWood()
{
   Image* pTextureOut = new Image( mWidth, mHeight, 3);
   GenerateNoise();

   double xyPeriod = 12.0; //number of rings
   double turbPower = 0.1; //makes twists
   double turbSize = 32.0; //initial size of the turbulence

   for(int y = 0; y < mHeight; y++)
   for(int x = 0; x < mWidth; x++)
   {
      double xValue = (x - mWidth / 2) / double(mWidth);
      double yValue = (y - mHeight / 2) / double(mHeight);
      double distValue = sqrt(xValue * xValue + yValue * yValue) + turbPower * Turbulence(x, y, turbSize) / 256.0;
      double sineValue = 128.0 * fabs(sin(2 * xyPeriod * distValue * 3.14159));
      ColorValue cv = ColorValue( 80 + sineValue, 30 + sineValue, 30 );
      pTextureOut->SetColor(x, y, cv );
   }
   return pTextureOut;
}

}
}
