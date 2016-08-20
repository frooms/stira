
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
 
#include "Retinex.h"
#include "../../filter/filter/GaussConvolve.h"
#include "../../histogram/histogram/IntHistogram.h"
#include "../../imagetools/tools/NumberGridTools.h"
#include "../../imagetools/tools/ImageIO.h"

namespace stira {
namespace contrastenhance {

using namespace std;
using namespace imagedata;
using namespace imagetools;
using namespace histogram;
using namespace filter;

//===========================================================

Retinex::Retinex()
{
}

//===========================================================

Retinex::~Retinex()
{
}

//===========================================================

Image* Retinex::SingleScaleRetinex(Image* pInImage, double sigma)
{
   Image* pRetinexImage = new Image( pInImage->GetWidth(), pInImage->GetHeight() );
   for (int bandNr = 0; bandNr < pInImage->GetNumberOfBands(); bandNr++)
   {
      ArrayGrid<double>* pRetinexGrid = SingleScaleRetinex( pInImage->GetBands()[bandNr], sigma);
      pRetinexImage->AddBand( pRetinexGrid );
   }
   std::string outName = pInImage->GetImageName() + std::string("-SingleScaleRetinex");
   pRetinexImage->SetImageName(outName);
   return pRetinexImage;
}

//===========================================================

ArrayGrid<double>* Retinex::SingleScaleRetinex(ArrayGrid<double>* pInGrid, double sigma)
{
   ArrayGrid<double>* pBlurredGrid = GaussConvolve::Convolve( pInGrid, sigma, GaussConvolve::FFT_BASED);
    
   int width   = pInGrid->GetWidth();
   int height  = pInGrid->GetHeight();
   
   bool needInitialisation = true;
   double initialRealValue = 0.0;
  
   ArrayGrid<double>* pRetinexGrid = new ArrayGrid<double>( width, height, needInitialisation, initialRealValue );
   
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         pRetinexGrid->SetValue(x, y, ( log10( pInGrid->GetValue(x, y) + 0.01) - log10( pBlurredGrid->GetValue(x, y) + 0.01 ) ) );
      }
   }
   
   delete pBlurredGrid;
   return pRetinexGrid;
}

//===========================================================

Image* Retinex::ColorCorrectImage( Image* pInImage )
{
   int width   = pInImage->GetWidth();
   int height  = pInImage->GetHeight();
   int nrBands = pInImage->GetNumberOfBands();
   
   double alpha = 128.0;
   double beta  =  46.0;
   
   Image* pCorrectionImage = new Image( width, height, nrBands);
   
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         double averageColor = 0.0;
         for (int bandNr = 0; bandNr < nrBands; bandNr++)
         {
            averageColor += (pInImage->GetBands()[bandNr]->GetValue(x, y) + 1.0);
         }
         averageColor /= nrBands;
         for (int bandNr = 0; bandNr < nrBands; bandNr++)
         {
            double tmpValue2;
            if (averageColor == 0.0)
            {
               tmpValue2 = 0.0;
            }
            else
            {
               tmpValue2 = beta * log10( alpha * ( pInImage->GetBands()[bandNr]->GetValue(x, y) + 1.0) ) - log10(averageColor);
            }
            pCorrectionImage->GetBands()[bandNr]->SetValue(x, y, tmpValue2);
         }
      }
   }
   std::string outName = pInImage->GetImageName() + std::string("-ColorCorrect");
   pCorrectionImage->SetImageName(outName);
   return pCorrectionImage;
}

//===========================================================

Image* Retinex::MultiScaleRetinex(Image* pInImage )
{
   Image* pRetinexImage = new Image( pInImage->GetWidth(), pInImage->GetHeight() );
   
   for (int bandNr = 0; bandNr < pInImage->GetNumberOfBands(); bandNr++)
   {
      ArrayGrid<double>* pRetinexGrid = MultiScaleRetinex( pInImage->GetBands()[bandNr] );
      pRetinexImage->AddBand( pRetinexGrid );
   }
   
   std::string outName = pInImage->GetImageName() + std::string("-MultiScaleRetinex");
   pRetinexImage->SetImageName(outName);
   return pRetinexImage;
}


//===========================================================

ArrayGrid<double>* Retinex::MultiScaleRetinex(ArrayGrid<double>* pInGrid )
{
   int width = pInGrid->GetWidth();
   int height = pInGrid->GetHeight();
   bool needInitialisation = true;
   double initialRealValue = 0.0;
   ArrayGrid<double>* pRetinexGrid = new ArrayGrid<double>( width, height, needInitialisation, initialRealValue );
   
   ArrayGrid<double>* pGrid015 = SingleScaleRetinex( pInGrid,  15);
   ArrayGrid<double>* pGrid080 = SingleScaleRetinex( pInGrid,  80);
   ArrayGrid<double>* pGrid250 = SingleScaleRetinex( pInGrid, 250);

   
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         double tmpValue = (pGrid015->GetValue(x, y) + pGrid080->GetValue(x, y) + pGrid250->GetValue(x, y)) / 3.0;
         pRetinexGrid->SetValue(x, y, tmpValue );
      }
   }
   
   delete pGrid015;
   delete pGrid080;
   delete pGrid250;
   
   return pRetinexGrid;
}

//===========================================================

void Retinex::ClipAndScaleImage(Image* pInOutImage, double lowerFraction, double upperFraction)
{
   int nrBands = pInOutImage->GetNumberOfBands();
   
   for (int bandNr = 0; bandNr < nrBands; bandNr++)
   {
      ClipAndScaleGrid( pInOutImage->GetBands()[bandNr], lowerFraction, upperFraction);
   }
}


//===========================================================

void Retinex::ClipAndScaleGrid(ArrayGrid<double>* pInOutGrid, double lowerFraction, double upperFraction)
{
   bool useDataMinMax = true;
   IntHistogram h(pInOutGrid, useDataMinMax, lowerFraction, upperFraction);
   
   h.Write( std::string( "RetinexHistogram.txt" ) );

   int width  = pInOutGrid->GetWidth();
   int height = pInOutGrid->GetHeight();
   
   double lowerBound = h.GetLowerBound( 0 );
   double upperBound = h.GetUpperBound( 0 );
   
   #ifdef DEBUG
     cout << "Clipping with lower fraction " << lowerFraction << " and upper fraction " << upperFraction 
          << endl << flush;
     h.Write( std::string( "RetinexHistogram.txt" ) );
     cout << "For grid: lowerBound = " << lowerBound << " and upperBound " << upperBound << endl << flush;
   #endif

   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         double tmpValue = pInOutGrid->GetValue(x, y);
         
         if (tmpValue < lowerBound) { pInOutGrid->SetValue(x, y, lowerBound);}
         if (tmpValue > upperBound) { pInOutGrid->SetValue(x, y, upperBound);}
      }
   }
}

//===========================================================

ArrayGrid<double>* Retinex::RunMSR( ArrayGrid<double>* pInGrid, double lowerFraction, double upperFraction )
{
   ArrayGrid<double>* pFilteredGrid = MultiScaleRetinex( pInGrid );
   
   #ifdef DEBUG
      double mmin, mmax, mmean;
      NumberGridTools<double>::GetMinMax( pFilteredImage->GetBands()[bandNr], mmin, mmax );
      mmean = NumberGridTools<double>::GetGridMean( pFilteredImage->GetBands()[bandNr] );
      cout << "After Retinex for single grid, min = " << mmin << " and max = " << mmax << " mean = " << mmean << endl << flush;
   #endif
   
   ClipAndScaleGrid( pFilteredGrid, lowerFraction, upperFraction);
   
   return pFilteredGrid;
}

//===========================================================

Image* Retinex::RunMSRCR(Image* pInImage, double lowerFraction, double upperFraction, bool applyColorCorrection)
{
   Image* pFilteredImage = MultiScaleRetinex( pInImage );
   if ( applyColorCorrection )
   {
      Image* pRetinex = ColorCorrectImage( pInImage );
   
      pFilteredImage->MultiplyWith( pRetinex );
      delete pRetinex;
   }
   
   #ifdef DEBUG
      for (int bandNr = 0; bandNr < pFilteredImage->GetNumberOfBands(); bandNr++)
      {
         double mmin, mmax, mmean;
         NumberGridTools<double>::GetMinMax( pFilteredImage->GetBands()[bandNr], mmin, mmax );
         mmean = NumberGridTools<double>::GetGridMean( pFilteredImage->GetBands()[bandNr] );
         cout << "After Retinex for band " << bandNr << " min = " << mmin << " and max = " << mmax << " mean = " << mmean << endl << flush;
      }
   #endif
   
   ClipAndScaleImage(pFilteredImage, lowerFraction, upperFraction);
   std::string outName = pInImage->GetImageName() + std::string("-MultiScaleRetinexColorCorrected");
   pFilteredImage->SetImageName(outName);
   return pFilteredImage;
}

//===========================================================

}
}
