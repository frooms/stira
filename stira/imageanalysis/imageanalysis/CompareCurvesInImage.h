
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

using namespace imagedata;

/** \brief compares two gray value images in which mono-colored curves are drawn */
class CompareCurvesInImage
{
public:
   CompareCurvesInImage( Image* pImage1, Image* pImage2, ColorValue cv );

   int GetDifference();

private:
   Image* mpImage1;
   Image* mpImage2;
   ColorValue mColorValue;
   std::vector<int> mvCurveY1;
   std::vector<int> mvCurveY2;
   std::vector<int> mvCurveDelta;
};

}
}

#endif // COMPARECURVESINIMAGE_H
