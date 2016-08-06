
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

#include "../../common/common/MathUtils.h"
#include "../../imagetools/tools/ImageIO.h"
#include "PyramidKeyPointDetector.h"
#include "../../filter/filter/GaussConvolve.h"

namespace stira {
namespace pyramidapplications {

using namespace std;
using namespace common;
using namespace image;
using namespace filter;

PyramidKeyPointDetector::PyramidKeyPointDetector(  image::Pyramid< std::complex<double> >* pPyramid )
{
   mpPyramid = pPyramid;
}

//---------------------------------------------------------------

PyramidKeyPointDetector::~PyramidKeyPointDetector()
{
}

//---------------------------------------------------------------

bool PyramidKeyPointDetector::MergeOrientationsFauqueur( int scale )
{
   ArrayGrid<double>* pEnergyMap = 0;
   ArrayGrid<double>* pUpscaledEnergyMap = 0;

   PyramidLevel< std::complex< double > >* pPyrLevel = 0;

   if (scale >= 0)
   {
      pPyrLevel = mpPyramid->GetRecursiveScale( scale );
   }
   else
   {
      pPyrLevel = mpPyramid->GetResidualScale( );
   }
   int width = pPyrLevel->GetWidth();
   int height = pPyrLevel->GetHeight();
   bool needsInitialisation = true;
   double initialValue = 0.0;
   pEnergyMap = new ArrayGrid<double>( width, height, needsInitialisation, initialValue );

   int nrOrientations = mpPyramid->GetNumberOfOrientations();

   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         double tmpValue = 0.0;
         for (int i = 0; i < nrOrientations-1; i++)
         {
            for (int j = i+1; j < nrOrientations; j++)
            {
               if (  ( abs( i - j ) > 1 ) && ( abs( i - j%(nrOrientations-1) ) > 0) )
               {
                  tmpValue += (    abs( pPyrLevel->GetOrientedBand( i )->GetValue(x, y) )
                                 * abs( pPyrLevel->GetOrientedBand( j )->GetValue(x, y) )
                              );
               }
            }
         }
         pEnergyMap->SetValue( x, y, tmpValue);
      }
   }

   if (scale > 0)
   {
      pUpscaledEnergyMap = GaussConvolve::UpsampleGaussianInterpolated( pEnergyMap, MathUtils::ComputeIntegerPower(2, scale ) );
      delete pEnergyMap;
   }
   else
   {
      pUpscaledEnergyMap = pEnergyMap;
   }
   mvEnergyMaps.push_back( pUpscaledEnergyMap );

   return true;
}

//---------------------------------------------------------------

bool PyramidKeyPointDetector::MergeOrientationsVariant( int scale )
{
   ArrayGrid<double>* pEnergyMap = 0;
   ArrayGrid<double>* pUpscaledEnergyMap = 0;

   PyramidLevel< std::complex< double > >* pPyrLevel = 0;

   pPyrLevel = mpPyramid->GetRecursiveScale( scale );

   int width = pPyrLevel->GetWidth();
   int height = pPyrLevel->GetHeight();
   bool needsInitialisation = true;
   double initialValue = 0.0;
   pEnergyMap = new ArrayGrid<double>( width, height, needsInitialisation, initialValue );

   int nrOrientations = mpPyramid->GetNumberOfOrientations();

   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         double tmpValue = 1.0;
         for (int i = 0; i < nrOrientations; i++)
         {
            tmpValue *= abs( pPyrLevel->GetOrientedBand( i )->GetValue(x, y) );
         }
         pEnergyMap->SetValue( x, y, tmpValue);
      }
   }

   if (scale > 0)
   {
      pUpscaledEnergyMap = GaussConvolve::UpsampleGaussianInterpolated( pEnergyMap, MathUtils::ComputeIntegerPower(2, scale ) );
      delete pEnergyMap;
   }
   else
   {
      pUpscaledEnergyMap = pEnergyMap;
   }
   mvEnergyMaps.push_back( pUpscaledEnergyMap );

   return true;
}

//---------------------------------------------------------------

void PyramidKeyPointDetector::AccumulateScales( )
{
   int nrScalesToAccumulate = mvEnergyMaps.size();

   int width   = mvEnergyMaps[0]->GetWidth();
   int height  = mvEnergyMaps[0]->GetHeight();
   bool needsInitialisation = true;
   double initialValue = 0.0;
   ArrayGrid<double>* pAccumulate = new ArrayGrid<double>( width, height, needsInitialisation, initialValue );
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         double tmpValue = 0.0;
         for (int scale = 0; scale < nrScalesToAccumulate; scale++)
         {
            tmpValue += mvEnergyMaps[scale]->GetValue(x, y);
         }
         pAccumulate->SetValue(x, y, tmpValue);
      }
   }
   mvAccumulatedMaps.push_back( pAccumulate );

   int scaleID = nrScalesToAccumulate;
   stringstream ss;
   ss << "AccumulatedEnergy-" << scaleID << ".pgm";
   ImageIO::WritePGM( pAccumulate, ss.str(), ImageIO::NORMAL_OUT );

   ArrayGrid<bool>* pKeyPointsMap  = FindLocalMaxima( pAccumulate );
   stringstream ss1;
   ss1 << "KeyPointMap-" << scaleID << ".pgm";
   ImageIO::WritePGM( pKeyPointsMap, ss1.str() );
}

//---------------------------------------------------------------

image::ArrayGrid<bool>* PyramidKeyPointDetector::FindLocalMaxima( ArrayGrid<double>* pGrid )
{
   int size = 5;
   int width   = pGrid->GetWidth();
   int height  = pGrid->GetHeight();
   bool needsInitialisation = true;
   double initialValue = false;
   ArrayGrid<bool>* pKeyPointsMap = new ArrayGrid<bool>( width, height, needsInitialisation, initialValue );
   pKeyPointsMap->SetGridValues( false );
   for (int y = size; y < height-size; y++)
   {
      for (int x = size; x < width-size; x++)
      {
         bool isLocalMaximum = true;
         for (int dy = -size; dy <= size; dy++)
         {
            for (int dx = -size; dx <= size; dx++)
            {
               if (  (dx != 0) || (dy != 0) )
               {
                  if (pGrid->GetValue(x+dx, y+dy) >= pGrid->GetValue(x, y))
                  {
                     isLocalMaximum = false;
                  }
               }
            }
         }
         pKeyPointsMap->SetValue(x, y, isLocalMaximum);
      }
   }
   return pKeyPointsMap;
}

//---------------------------------------------------------------

void PyramidKeyPointDetector::Run()
{
   int nrScales = mpPyramid->GetNumberOfScales();

   for (int scaleID = 0; scaleID < nrScales; scaleID++)
   {
      //MergeOrientationsVariant( scaleID );
      MergeOrientationsFauqueur( scaleID );

      AccumulateScales( );
   }
}

//---------------------------------------------------------------

}
}
