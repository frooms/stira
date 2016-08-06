
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

#include "GretagMacbethColorChecker.h"
#include "../../imagedata/color/TransformColorSpace.h"
namespace stira {
namespace image {

using namespace std;

//----------------------------------------------------------

GretagMacbethColorChecker::GretagMacbethColorChecker()
{
}

//----------------------------------------------------------

GretagMacbethColorChecker::~GretagMacbethColorChecker()
{}

//----------------------------------------------------------

std::vector<ColorValue> GretagMacbethColorChecker::GenerateVector()
{
   std::vector<ColorValue> colorVector;

   colorVector.push_back( ColorCheckerDarkSkin );
   colorVector.push_back( ColorCheckerLightSkin );
   colorVector.push_back( ColorCheckerBlueSky );
   colorVector.push_back( ColorCheckerFoliage );
   colorVector.push_back( ColorCheckerBlueFlower );
   colorVector.push_back( ColorCheckerBluishGreen );
   colorVector.push_back( ColorCheckerOrange );
   colorVector.push_back( ColorCheckerPurpilishBlue );
   colorVector.push_back( ColorCheckerModerateRed );
   colorVector.push_back( ColorCheckerPurple );
   colorVector.push_back( ColorCheckerYellowGreen );
   colorVector.push_back( ColorCheckerOrangeYellow );
   colorVector.push_back( ColorCheckerBlue );
   colorVector.push_back( ColorCheckerGreen );
   colorVector.push_back( ColorCheckerRed );
   colorVector.push_back( ColorCheckerYellow );
   colorVector.push_back( ColorCheckerMagenta );
   colorVector.push_back( ColorCheckerCyan );
   colorVector.push_back( ColorCheckerWhite );
   colorVector.push_back( ColorCheckerNeutral80 );
   colorVector.push_back( ColorCheckerNeutral65 );
   colorVector.push_back( ColorCheckerNeutral50 );
   colorVector.push_back( ColorCheckerNeutral35 );
   colorVector.push_back( ColorCheckerBlack );
   return colorVector;
}

//----------------------------------------------------------

Image* GretagMacbethColorChecker::Generate( int borderWidth, int squareSize )
{
   std::vector<ColorValue> colorVector = GenerateVector();
   int width  = 6 * squareSize + 7 * borderWidth;
   int height = 4 * squareSize + 5 * borderWidth;
   TransformColorSpace tcsp;
   Image* pColorChecker = new Image( width, height, 3 );
   
   assert( tcsp.GetReferenceWhite( ) == ColorConstants::sD65_XYZ );
   
   for ( int verticalCount = 0; verticalCount < 4; verticalCount++ )
   {
      for ( int horizontalCount = 0; horizontalCount < 6; horizontalCount++ )
      {
         int offsetY = (  verticalCount + 1) * borderWidth +   verticalCount * squareSize;
         int offsetX = (horizontalCount + 1) * borderWidth + horizontalCount * squareSize;
         
         int colorID = 6 * verticalCount + horizontalCount;
         
         DrawSquare( pColorChecker, offsetX, offsetY, squareSize, tcsp.LabtosRGB( colorVector[colorID] ) );
      }
   }

   return pColorChecker;
}

//----------------------------------------------------------

void GretagMacbethColorChecker::DrawSquare( Image* pColorChecker, int offsetX, int offsetY, int squareSize, ColorValue cv )
{
   for (int y = offsetY; y < offsetY + squareSize; y++ )
   {
       for (int x = offsetX; x < offsetX + squareSize; x++ )
       {
          pColorChecker->SetColor( x, y, cv );
       }
   }
}

//----------------------------------------------------------

}
}
