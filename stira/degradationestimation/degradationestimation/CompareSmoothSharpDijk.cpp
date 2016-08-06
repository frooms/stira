
/***********************************************************************************
 *   Copyright (C) 2008 by Filip Rooms                                             *
 *                                                                                 *
 *  Terms and conditions for using this software in any form are provided in the   *
 *  file COPYING, which can be found in the root directory of this project.        *
 *                                                                                 *
 *   Contact data: filip.rooms@gmail.com                                           *
 *                 http://www.filiprooms.be/                                       *
 *                                                                                 *
 ***********************************************************************************/

#include <cassert>
#include "CompareSmoothSharpDijk.h"
#include "../../filter/filter/NonSeparableFilter.h"
#include "../../imagedata/datastructures/OrientationGrid.h"
#include "../../imagetools/tools/NumberGridTools.h"
#include "../../imagedata/datastructures/Image.h"
#include "../../histogram/histogram/JointHistogram.h"

namespace stira {
namespace degradationestimation {

using namespace std;
using namespace image;
using namespace histogram;
using namespace filter;

CompareSmoothSharpDijk::CompareSmoothSharpDijk(image::Image* pImage1, image::Image* pImage2, string name)
{
   assert (pImage1 != 0);
   assert (pImage2 != 0);
   
   assert (pImage1->GetWidth() == pImage2->GetWidth() );
   assert (pImage1->GetHeight() == pImage2->GetHeight() );
   mName = name;
   mpImage1 = pImage1;
   mpImage2 = pImage2;
   
   mWidth = mpImage1->GetWidth();
   mHeight = mpImage1->GetHeight();
}

//----------------------------------------------------------------
   
CompareSmoothSharpDijk::~CompareSmoothSharpDijk()
{
}

//----------------------------------------------------------------

bool CompareSmoothSharpDijk::Run()
{
   OrientationGrid* pOrientationGrid1 = NonSeparableFilter::DetermineLocalMagnitudeAndOrientation( mpImage1->GetBands()[0] );
   OrientationGrid* pOrientationGrid2 = NonSeparableFilter::DetermineLocalMagnitudeAndOrientation( mpImage2->GetBands()[0] );
   
   ArrayGrid<double>* pMagnitudeGrid1 = pOrientationGrid1->ExtractMagnitudeGrid();
   ArrayGrid<double>* pMagnitudeGrid2 = pOrientationGrid2->ExtractMagnitudeGrid();
   
   Image* pMagnitudeImage1 = new Image( pMagnitudeGrid1 );
   Image* pMagnitudeImage2 = new Image( pMagnitudeGrid2 );
   JointHistogram ch( pMagnitudeImage1, pMagnitudeImage2, true );
   
   ch.VisualizeAsImage(std::string("ConditionalHistogram_" + mName + ".pgm"));
   return true;
}

//----------------------------------------------------------------

}
}

