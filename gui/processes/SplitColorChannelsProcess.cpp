
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

#include <sstream>
#include "SplitColorChannelsProcess.h"
#include "../src/ImageDataList.h"
#include "../../stira/image/tools/ImageTools.h"

using namespace stira::image;

SplitColorChannelsProcess::SplitColorChannelsProcess( Image* pImage ) : Process( pImage )
{
   mProcessName = QString("Split Color Channels Result");
   mReferenceIlluminant = ColorConstants::sD65_XYZ;
}

//--------------------------------------------------------

SplitColorChannelsProcess::~SplitColorChannelsProcess()
{
}

//--------------------------------------------------------

void SplitColorChannelsProcess::SetColorSpace( stira::image::ColorType colorSpace )
{
   mColorSpace = colorSpace;
}

//--------------------------------------------------------

stira::image::ColorType SplitColorChannelsProcess::GetColorSpace( )
{
   return mColorSpace;
}

//--------------------------------------------------------

stira::image::ColorValue SplitColorChannelsProcess::GetReferenceIlluminant()
{
   return mReferenceIlluminant;
}

//--------------------------------------------------------

void SplitColorChannelsProcess::SetReferenceIlluminant( stira::image::ColorValue referenceIlluminant )
{
   mReferenceIlluminant = referenceIlluminant;
}

//--------------------------------------------------------

void SplitColorChannelsProcess::run()
{
   stira::image::Image* pOutImage = mpImage->Clone(); // ownership of pOutImage is transfered to separate band images
   int nrbands = pOutImage->GetNumberOfBands();
   std::string bandID[3];
   
   switch ( mColorSpace )
   {
      case stira::image::TYPE_CMY:
      {
         pOutImage->RGBToCMY( );
         bandID[0] = std::string("C");
         bandID[1] = std::string("M");
         bandID[2] = std::string("Y");
         break;
      }
      case stira::image::TYPE_YUV:
      {
         pOutImage->RGBToYUV( );
         bandID[0] = std::string("Y");
         bandID[1] = std::string("U");
         bandID[2] = std::string("V");
         break;
      }
      case stira::image::TYPE_HSV:
      {
         pOutImage->RGBToHSV( );
         bandID[0] = std::string("H");
         bandID[1] = std::string("S");
         bandID[2] = std::string("V");
         break;
      }
      case stira::image::TYPE_HSI:
      {
         pOutImage->RGBToHSI( );
         bandID[0] = std::string("H");
         bandID[1] = std::string("S");
         bandID[2] = std::string("I");
         break;
      }
      case stira::image::TYPE_XYZ:
      {
         pOutImage->sRGBToXYZ( mReferenceIlluminant );
         bandID[0] = std::string("X");
         bandID[1] = std::string("Y");
         bandID[2] = std::string("Z");
         break;
      }
      case stira::image::TYPE_LAB:
      {
         pOutImage->sRGBToLab( mReferenceIlluminant );
         bandID[0] = std::string("L");
         bandID[1] = std::string("A");
         bandID[2] = std::string("B");
         break;
      }
      case stira::image::TYPE_LUV:
      {
         pOutImage->sRGBToLuv( mReferenceIlluminant );
         bandID[0] = std::string("L");
         bandID[1] = std::string("U");
         bandID[2] = std::string("V");
         break;
      }
      case stira::image::TYPE_UNKNOWN:
      case stira::image::TYPE_RGB:
      default: // equalize all bands independantly
      {
         bandID[0] = std::string("R");
         bandID[1] = std::string("G");
         bandID[2] = std::string("B");
         break;
      }
   }
   
   for ( int bandNr = 0; bandNr < nrbands; bandNr++ )
   {
      NumberGridTools<double>::RescaleGrid( pOutImage->GetBands()[bandNr], 0.0, 255.0 );
      Image* pChannelImage = new Image( pOutImage->GetBands()[bandNr] );
      std::string outName = mpImage->GetImageName() +std::string("-") + std::string( bandID[bandNr] );
      pChannelImage->SetImageName( outName );
      AddResult( pChannelImage );
   }
}

//--------------------------------------------------------

