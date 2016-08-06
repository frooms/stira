
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

#include "CompareCurvesInImage.h"
#include "../../histogram/histogram/RunLengthHistogram.h"
#include "../../imagetools/tools/ImageIO.h"

namespace stira {
namespace imageanalysis {

using namespace stira::histogram;
using namespace stira::image;

CompareCurvesInImage::CompareCurvesInImage( image::Image* pImage1, image::Image* pImage2, image::ColorValue cv )
{
   mpImage1 = pImage1;
   mpImage2 = pImage2;
   assert( mpImage1->GetWidth()  == mpImage2->GetWidth() );
   assert( mpImage1->GetHeight() == mpImage2->GetHeight() );
   mColorValue = cv;
}

//----------------------------------------------------------------

int CompareCurvesInImage::GetDifference()
{
   image::ColorValue cv1 = ColorValue(   0,   0, 255, TYPE_RGB );
   image::ColorValue cv2 = ColorValue(   0, 255,   0, TYPE_RGB );
   image::ColorValue cv3 = ColorValue(   0, 255, 255, TYPE_RGB );
   Image* pDiffImage = new Image(  mpImage1->GetWidth(), mpImage1->GetHeight(), 3 );
   int differentPixels = 0;
   for (int x = 0; x < mpImage1->GetWidth(); x++)
   {
      int y1 = 0;
      int y2 = 0;
      while ( mpImage1->GetColor( x, y1 ) != mColorValue )
      {
         y1++;
      }
      mvCurveY1.push_back( y1 );
      while ( mpImage2->GetColor( x, y2 ) != mColorValue )
      {
         y2++;
      }
      if ( y1 != y2 )
      {
         pDiffImage->SetColor(x, y1, cv1 );
         pDiffImage->SetColor(x, y2, cv2 );
      }
      else
      {
         pDiffImage->SetColor(x, y1, cv3 );
      }

      mvCurveY2.push_back( y2 );
      mvCurveDelta.push_back( abs(y1 - y2 ) );
   }

   int maxHistogramLength = 2000;
   int maxDelta = 85;
   RunLengthHistogram RLH( maxDelta, maxHistogramLength );
   RLH.Analyse( mvCurveDelta );
   RLH.WriteSegments( std::string("DifferenceCurves.txt"), 404 );
   ImageIO::WriteOpenCV(pDiffImage, std::string("DifferenceCurves.png"));
   delete pDiffImage;

   return differentPixels;
}

//----------------------------------------------------------------

}
}
