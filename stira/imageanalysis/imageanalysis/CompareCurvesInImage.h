
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

#ifndef STIRA_IMAGEANALYSIS_COMPARECURVESINIMAGE_H
#define STIRA_IMAGEANALYSIS_COMPARECURVESINIMAGE_H

#include "../../imagedata/datastructures/Image.h"
#include "../../imagedata/color/ColorValue.h"

namespace stira {
namespace imageanalysis {

/** \brief compares two gray value images in which mono-colored curves are drawn */
class CompareCurvesInImage
{
public:
   CompareCurvesInImage( image::Image* pImage1, image::Image* pImage2, image::ColorValue cv );

   int GetDifference();

private:
   image::Image* mpImage1;
   image::Image* mpImage2;
   image::ColorValue mColorValue;
   std::vector<int> mvCurveY1;
   std::vector<int> mvCurveY2;
   std::vector<int> mvCurveDelta;
};

}
}

#endif // COMPARECURVESINIMAGE_H
