
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

#include "PyramidTools.h"

namespace stira {
namespace image {

using namespace std;

PyramidTools::PyramidTools()
{
}

//===================================================================================================

PyramidTools::~PyramidTools()
{
}

//===================================================================================================

int PyramidTools::DetermineWidth( Pyramid< double >* pPyramid )
{
   int border = 10;
   int sourceWidth;
   if ( pPyramid->IsFinestScaleSubsampled() )
   {
      sourceWidth = pPyramid->GetSourceDataWidth() / 2 + 1;
   }
   else
   {
      sourceWidth = pPyramid->GetSourceDataWidth();
   }
   return ( border + pPyramid->GetNumberOfOrientations() * (sourceWidth + border) );
}

//===================================================================================================

int PyramidTools::DetermineHeight( Pyramid< double >* pPyramid )
{
   int border = 10;
   
   int nrScales = pPyramid->GetNumberOfScales();
   int totalHeight = border;
   
   for (int i = 0; i < nrScales; i++)
   {
      totalHeight += ( pPyramid->GetRecursiveScale(i)->GetOrientedBand(0)->GetHeight() + border);
   }
   if ( pPyramid->HasResidualScale() )
   {
      totalHeight += ( pPyramid->GetResidualScale()->GetOrientedBand(0)->GetHeight() + border);
   }
   totalHeight += ( pPyramid->GetLowpassResidual()->GetHeight() + border );
   return totalHeight;
}

//===================================================================================================

Image* PyramidTools::VisualizeRealPyramid( Pyramid< double >* pPyramid )
{
   int border = 10;
   int totalWidth  = DetermineWidth( pPyramid );
   int totalHeight = DetermineHeight( pPyramid );
   Image* pImage = new Image( totalWidth, totalHeight, 1 );
   
   int nrScales = pPyramid->GetNumberOfScales();
   int nrOrientations = pPyramid->GetNumberOfOrientations();
   
   int xTop = border;
   int yTop = border;
   if ( pPyramid->HasResidualScale() )
   {
      for (int i = 0; i < nrOrientations; i++)
      {
         pImage->InsertSubGrid( pPyramid->GetResidualScale()->GetOrientedBand(i), xTop, yTop );
         xTop += (border + pPyramid->GetResidualScale()->GetOrientedBand(i)->GetWidth());
      }
      xTop = border;
      yTop += (pPyramid->GetResidualScale()->GetOrientedBand(0)->GetHeight() + border);
   }
   
   for (int scaleNr = 0; scaleNr < nrScales; scaleNr++ )
   {
      xTop = border;
      for (int orientationNr = 0; orientationNr < nrOrientations; orientationNr++)
      {
         pImage->InsertSubGrid( pPyramid->GetRecursiveScale(scaleNr)->GetOrientedBand(orientationNr), xTop, yTop );
         xTop += (border + pPyramid->GetRecursiveScale(scaleNr)->GetOrientedBand(orientationNr)->GetWidth() );
      }
      yTop += (pPyramid->GetRecursiveScale(scaleNr)->GetOrientedBand(0)->GetHeight() + border);
   }
   
   xTop = border;
   pImage->InsertSubGrid( pPyramid->GetLowpassResidual(), xTop, yTop );
   return pImage;
}

//===================================================================================================

}
}
