
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

#include <algorithm>
#include "NoiseEstimator.h"
#include "../../common/common/MathUtils.h"
#include "../../imagetools/tools/ImageIO.h"
#include "../../imagetools/tools/PyramidTools.h"
#include "../wavelet/CriticallySubsampledTransform.h"

namespace stira {
namespace wavelet {

using namespace common;

//----------------------------------------------------------------

bool MySortPredicate(const double& lhs, const double& rhs)
{
  return lhs < rhs;
}

//----------------------------------------------------------------

NoiseEstimator::NoiseEstimator()
{
}

//----------------------------------------------------------------

NoiseEstimator::~NoiseEstimator()
{
}

//----------------------------------------------------------------

double NoiseEstimator::GetMedianValue( image::ArrayGrid<double>* pGrid )
{
   double medianValue;
   int width  = pGrid->GetWidth();
   int height = pGrid->GetHeight();

   std::vector<double> vIntensitiesVector;

   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         vIntensitiesVector.push_back( fabs( pGrid->GetValue( x, y) ) );
      }
   }

   sort( vIntensitiesVector.begin(), vIntensitiesVector.end(), MySortPredicate );

   medianValue = vIntensitiesVector[width*height/2];

   return medianValue;
}

//----------------------------------------------------------------

double NoiseEstimator::Run( image::ArrayGrid<double>* pGrid )
{
   double noiseLevel;
   CriticallySubsampledTransform wdr;

   wdr.Decompose( pGrid, 1);

   // visualize all bands together in single image
   /*image::Image* pCritical = image::PyramidTools::VisualizeRealPyramid( wdr.GetPyramid() );
   image::ImageIO::Write( pCritical, std::string("HaarDecomposeBands.pgm"), image::ImageIO::NULL_OUT );
   delete pCritical;

   wdr.GetPyramid();*/

   noiseLevel = GetMedianValue( wdr.GetPyramid()->GetRecursiveScale(0)->GetOrientedBand(2) ) / 0.6745;

   return noiseLevel;
}

//----------------------------------------------------------------

}
}
