
/***************************************************************************************
 *   Copyright (C) 2008 by Filip Rooms                                                 *
 *                                                                                     *
 *  Terms and conditions for using this software in any form are provided in the       *
 *  file COPYING, which can be found in the root directory of this project.            *
 *                                                                                     *
 *   Contact data: filip.rooms@gmail.com                                               *
 *                 http://www.filiprooms.be/                                           *
 *                                                                                     *
 ***************************************************************************************/

#include "HistogramTools.h"
#include "../../common/common/MathUtils.h"
#include "../../filter/filter/GaussConvolve.h"
#include "../../histogram/histogram/IntHistogram.h"
#include "../../histogram/histogram/FloatHistogram.h"
#include "../../image/tools/NumberGridTools.h"

#define DEBUG

namespace stira {
namespace contrastenhance {

using namespace std;
using namespace image;
using namespace common;
using namespace filter;
using namespace histogram;

//////////////////////////
//                      //
// 0) GENERAL STUFF     //
//                      //
//////////////////////////

HistogramTools::HistogramTools()
{
}

//----------------------------------------------------------------------------------------

HistogramTools::~HistogramTools()
{
}

//----------------------------------------------------------------------------------------


/////////////////////////////
//                         //
// 1) HISTOGRAM REMAPPING  //
//                         //
/////////////////////////////

double HistogramTools::MatchHistogramValue( double inValue,
                                            IntHistogram* fhIncomingCumulativeHistogram,
                                            FloatHistogram* fhReferenceCumulativeHistogram
                                          )
{
   double inCumulativeValue = fhIncomingCumulativeHistogram->GetBinValue( 0, int(inValue) );
   int histogramSize = fhReferenceCumulativeHistogram->GetNrOfBins();

   if ( inCumulativeValue > fhReferenceCumulativeHistogram->GetBinValue( 0, histogramSize-1 ) )
   {
      return 255;
   }

   for (int i = 0; i < histogramSize; i++)
   {
      //double refValue = fhReferenceCumulativeHistogram->GetBinValue( 0, i );
      if ( fhReferenceCumulativeHistogram->GetBinValue( 0, i ) >= (inCumulativeValue-0.5) )
      {
         return MathUtils::ClipValue(i, 0, 255);
      }
   }
   return -1;
}

//----------------------------------------------------------------------------------------

void HistogramTools::RemapHistogramInROI( image::ArrayGrid<double>* pInGrid,
                                          RectangularROI<int> rroi,
                                          IntHistogram* fhCumulativeInput,
                                          FloatHistogram* fhCumulativeReference )
{
   int xMin = MathUtils::ClipValue(rroi.GetTopLeftCorner().x, 0, pInGrid->GetWidth() );
   int yMin = MathUtils::ClipValue(rroi.GetTopLeftCorner().y, 0, pInGrid->GetHeight() );
   int xMax = MathUtils::ClipValue(rroi.GetBottomRightCorner().x, 0, pInGrid->GetWidth() );
   int yMax = MathUtils::ClipValue(rroi.GetBottomRightCorner().y, 0, pInGrid->GetHeight() );

   for (int y = yMin; y < yMax; y++)
   {
      for (int x = xMin; x < xMax; x++)
      {
         pInGrid->SetValue( x, y, MatchHistogramValue( pInGrid->GetValue( x, y ), fhCumulativeInput, fhCumulativeReference ) );
      }
   }
}

//----------------------------------------------------------------------------------------

////////////////////////////////////////
//                                    //
// 2) HISTOGRAM EQUALIZATION METHODS  //
//                                    //
////////////////////////////////////////

Image* HistogramTools::RobustLinearRescale( image::Image* pSourceImage, double lowerFraction, double upperFraction )
{
   Image* pOutImage = pSourceImage->Clone();

   if ( RobustLinearRescaleNoNew( pOutImage, lowerFraction, upperFraction ) )
   {
      return pOutImage;
   }
   else
   {
      return 0;
   }
}

//----------------------------------------------------------------------------------------

bool HistogramTools::RobustLinearRescaleNoNew( image::Image* pSourceImage, double lowerFraction, double upperFraction )
{
   double imageMin, imageMax;
   int bandMin, bandMax;

   if ( ( lowerFraction < 0.001 ) && ( upperFraction > 0.999 ) )
   {
      for (int bandNr = 0; bandNr < pSourceImage->GetNumberOfBands(); bandNr++ )
      {
         pSourceImage->GetMinMax(imageMin, imageMax, bandMin, bandMax );

         int width  = pSourceImage->GetWidth();
         int height = pSourceImage->GetHeight();
         ArrayGrid<double>* pGrid = pSourceImage->GetBands()[bandNr];
         for (int y = 0; y < height; y++)
         {
            for (int x = 0; x < width; x++)
            {
               pGrid->SetValue( x, y, 255.0 * ( ( pGrid->GetValue( x, y ) - imageMin ) / (imageMax - imageMin) ) );
            }
         }
      }
   }
   else
   {
      bool useDataMinMax = true;
      IntHistogram stdHistogram( pSourceImage, useDataMinMax, lowerFraction, upperFraction );
      pSourceImage->GetMinMax(imageMin, imageMax, bandMin, bandMax );

      double robustMax = stdHistogram.GetUpperBound( bandMax );
      double robustMin = stdHistogram.GetLowerBound( bandMin );

      int width  = pSourceImage->GetWidth();
      int height = pSourceImage->GetHeight();
      for (int bandNr = 0; bandNr < pSourceImage->GetNumberOfBands(); bandNr++ )
      {
         ArrayGrid<double>* pGrid = pSourceImage->GetBands()[bandNr];
         for (int y = 0; y < height; y++)
         {
            for (int x = 0; x < width; x++)
            {
               pGrid->SetValue( x, y, MathUtils::ClipValue( pGrid->GetValue( x, y ), robustMin, robustMax ) );
            }
         }
         double clippedMin, clippedMax;
         NumberGridTools<double>::GetMinMax( pGrid, clippedMin, clippedMax );
         for (int y = 0; y < height; y++)
         {
            for (int x = 0; x < width; x++)
            {
               pGrid->SetValue( x, y, 255.0 * ( ( pGrid->GetValue( x, y ) - clippedMin ) / (clippedMax - clippedMin) ) );
            }
         }
      }
   }
   return true;
}



//----------------------------------------------------------------------------------------

void HistogramTools::HistogramEqualizeSingleBand( image::ArrayGrid<double>* pInGrid )
{
   int desiredMax, desiredMin;
   double dataMin, dataMax;
   int nrBands = 1;

   NumberGridTools<double>::GetMinMax( pInGrid, dataMin, dataMax );
   bool useDataMinMax = false;
   IntHistogram* pStdHistogram       = new IntHistogram( pInGrid, useDataMinMax );
   IntHistogram* pCumulHistogram     = new IntHistogram( pInGrid, useDataMinMax );
   FloatHistogram *pNormCumulHistogram = new FloatHistogram( pStdHistogram->GetNrOfBins(), nrBands );

   pCumulHistogram->ConvertInCumulativeHistogram();

   pNormCumulHistogram->InitializeWithNormalizedCumulativeHistogram( pStdHistogram, pCumulHistogram);

   desiredMax = (int)(dataMax);
   desiredMin = 0;

   for (int y = 0; y < pInGrid->GetHeight(); y++)
   {
      for (int x = 0; x < pInGrid->GetWidth(); x++)
      {
         int binNr = pInGrid->GetValue(x, y) - dataMin;

         double myEqualizedValue = desiredMax * ( pNormCumulHistogram->GetBinValue( 0, binNr ) / ((double)(pNormCumulHistogram->GetNrOfBins())));

         if (myEqualizedValue > static_cast<double>(desiredMax)) {myEqualizedValue = static_cast<double>(desiredMax);}
         if (myEqualizedValue < static_cast<double>(desiredMin)) {myEqualizedValue = static_cast<double>(desiredMin);}

         pInGrid->SetValue(x, y, myEqualizedValue);
      }
   }

   //NumberGridTools<double>::GetMinMax( pInGrid, dataMin, dataMax );

   delete pStdHistogram;
   delete pCumulHistogram;
   delete pNormCumulHistogram;
}

//----------------------------------------------------------------------------------------

Image* HistogramTools::HistogramEqualizePerBand( image::Image* pSourceImage )
{
   if ( pSourceImage != 0 )
   {
      int nrBands = pSourceImage->GetNumberOfBands();

      image::Image* pResultImage = pSourceImage->Clone();

      for (int bandNr = 0; bandNr < nrBands; bandNr++)
      {
         HistogramEqualizeSingleBand( pResultImage->GetBands()[bandNr] );
      }
      std::string outName = pSourceImage->GetImageName() + std::string("-EqualizePerBand");
      pResultImage->SetImageName(outName);
      return pResultImage;
   }
   else
   {
      cerr << "No valid source data" << endl << flush;
      return 0;
   }
}

//----------------------------------------------------------------------------------------

Image* HistogramTools::HistogramEqualizeHSI( image::Image* pSourceImage )
{
   if ( ( pSourceImage != 0 ) && (pSourceImage->GetNumberOfBands() == 3) )
   {
      double dataMin = 0.0;
      double dataMax = 255.0;

      image::Image* pResultImage = pSourceImage->Clone();
      pResultImage->RGBToHSI();

      ArrayGrid<double>* pValueGrid = pResultImage->GetBands()[2];  // pValueGrid refers directly to the I values

      NumberGridTools<double>::RescaleGrid( pValueGrid, dataMin, dataMax );
      HistogramEqualizeSingleBand( pValueGrid );

      NumberGridTools<double>::RescaleGrid( pValueGrid, 0.0, 1.0 );
      pResultImage->HSIToRGB();

      std::string outName = pSourceImage->GetImageName() + std::string("-EqualizeHSI");
      pResultImage->SetImageName(outName);
      return pResultImage;
   }
   else
   {
      if (pSourceImage == 0 )
      {
         cerr << "No valid source data: was NULL pointer" << endl << flush;
         return 0;
      }
      if (pSourceImage->GetNumberOfBands() != 3)
      {
         cerr << "HSV-based histogram equalization only possible if there are three spectral bands, and the given image has "
              << pSourceImage->GetNumberOfBands() << " bands " << endl << flush;
         return 0;
      }
   }
   // if this point is reached, there is something very wrong!!
   return 0;
}

//----------------------------------------------------------------------------------------

Image* HistogramTools::ColorHistogramEqualize( image::Image* pSourceImage )
{
   if ( ( pSourceImage != 0 ) && (pSourceImage->GetNumberOfBands() == 3) )
   {
      double dataMin = 0.0;
      double dataMax = 255.0;

      image::Image* pResultImage = pSourceImage->Clone();
      pResultImage->sRGBToLab();

      ArrayGrid<double>* pValueGrid = pResultImage->GetBands()[0];  // pValueGrid refers directly to the L values
      NumberGridTools<double>::RescaleGrid( pValueGrid, dataMin, dataMax );

      HistogramEqualizeSingleBand( pValueGrid );

      NumberGridTools<double>::RescaleGrid( pResultImage->GetBands()[0], 0.0, 99.0 );

      pResultImage->LabTosRGB();
      pResultImage->ClipImageValues( 0.0, 255.0 );
      std::string outName = pSourceImage->GetImageName() + std::string("-EqualizedLab");
      pResultImage->SetImageName(outName);
      return pResultImage;
   }
   else
   {
      if (pSourceImage == 0 )
      {
         cerr << "No valid source data: was NULL pointer" << endl << flush;
         return 0;
      }
      if (pSourceImage->GetNumberOfBands() != 3)
      {
         cerr << "HSV-based histogram equalization only possible if there are three spectral bands, and the given image has "
              << pSourceImage->GetNumberOfBands() << " bands " << endl << flush;
         return 0;
      }
   }
   // if this point is reached, there is something very wrong!!
   return 0;
}

//----------------------------------------------------------------------------------------

}
}
