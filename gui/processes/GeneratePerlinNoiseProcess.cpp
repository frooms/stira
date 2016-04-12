
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

#include "GeneratePerlinNoiseProcess.h"
#include "../../stira/image/tools/NumberGridTools.h"
#include "../../stira/image/tools/PerlinNoise.h"
#include "../../stira/filter/filter/GaussConvolve.h"

using namespace std;
using namespace stira::image;

GeneratePerlinNoiseProcess::GeneratePerlinNoiseProcess( ) : Process( )
{
   mProcessName = QString("Perlin Clouds");
}

//--------------------------------------------------------

GeneratePerlinNoiseProcess::~GeneratePerlinNoiseProcess()
{
}

//--------------------------------------------------------

int GeneratePerlinNoiseProcess::GetWidth()
{
   return mWidth;
}

//--------------------------------------------------------

void GeneratePerlinNoiseProcess::SetWidth( int width )
{
   mWidth = width;
}

//--------------------------------------------------------

int GeneratePerlinNoiseProcess::GetHeight()
{
   return mHeight;
}

//--------------------------------------------------------

void GeneratePerlinNoiseProcess::SetHeight( int height )
{
   mHeight = height;
}

//--------------------------------------------------------
    
double GeneratePerlinNoiseProcess::GetPersistence()
{
   return mPersistence;
}

//--------------------------------------------------------

void GeneratePerlinNoiseProcess::SetPersistence( double p )
{
   mPersistence = p;
}

//--------------------------------------------------------

int GeneratePerlinNoiseProcess::GetNumberOfOctaves()
{
   return mNrOctaves;
}

//--------------------------------------------------------

void GeneratePerlinNoiseProcess::SetNumberOfOctaves( int nrOctaves )
{
   mNrOctaves = nrOctaves;
}

//--------------------------------------------------------

double GeneratePerlinNoiseProcess::GetRedFactor()
{
   return mRed;
}

//--------------------------------------------------------
    
void GeneratePerlinNoiseProcess::SetRedFactor( double factor )
{
   mRed = factor;
}

//--------------------------------------------------------
    
double GeneratePerlinNoiseProcess::GetGreenFactor()
{
   return mGreen;
}

//--------------------------------------------------------
    
void GeneratePerlinNoiseProcess::SetGreenFactor( double factor )
{
   mGreen = factor;
}
    
double GeneratePerlinNoiseProcess::GetBlueFactor()
{
   return mBlue;
}

//--------------------------------------------------------
    
void GeneratePerlinNoiseProcess::SetBlueFactor( double factor )
{
   mBlue = factor;
}

//--------------------------------------------------------

int GeneratePerlinNoiseProcess::GetSeed()
{
   return mSeed;
}

//--------------------------------------------------------

void GeneratePerlinNoiseProcess::SetSeed( int seed )
{
   mSeed = seed;
}

//--------------------------------------------------------

double GeneratePerlinNoiseProcess::GetZoom()
{
   return mZoom;
}

//--------------------------------------------------------

void GeneratePerlinNoiseProcess::SetZoom( double zoom )
{
   mZoom = zoom;
}
   
bool GeneratePerlinNoiseProcess::GetUseNormalization()
{
   return mUseNormalization;
}

void GeneratePerlinNoiseProcess::SetUseNormalization( bool useNormalize )
{
   mUseNormalization = useNormalize;
}

//--------------------------------------------------------

void GeneratePerlinNoiseProcess::run()
{
   PerlinNoise pn;
   Image* pOutImage = 0;
   if ( mUseNormalization )
   {
      pOutImage = pn.GenerateNormalized( mPersistence, mNrOctaves, mWidth, mHeight, mRed, mGreen, mBlue, mSeed, mZoom );
   }
   else
   {
      pOutImage = pn.Generate( mPersistence, mNrOctaves, mWidth, mHeight, mRed, mGreen, mBlue, mSeed, mZoom );
   }
   std::string imageName = std::string("PerlinClouds");
   pOutImage->SetImageName( imageName );
   AddResult( pOutImage );
   // ownership of this image is transfered through GetImage() to ImageDataList
}
