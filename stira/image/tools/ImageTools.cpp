
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

#include "ImageTools.h"
#include "GridExtender.h"
#include "../../common/common/MathUtils.h"
#include "../color/TransformColorSpace.h"

#include <cassert>
#include <sstream>

namespace stira {
namespace image {

using namespace common;
using namespace std;

// 0. CONSTRUCTOR / DESTRUCTOR
//////////////////////////////

ImageTools::ImageTools()
{
}

//===================================================================================================

ImageTools::~ImageTools()
{
}

//===================================================================================================

// 1. PADD / CROP IMAGE
///////////////////////

Image* ImageTools::MirrorBorder( Image* pInImage, int borderWidth, int borderHeight)
{
   assert( borderWidth >= 0);
   assert( borderHeight >= 0);

   Image* pExpandedImage = new Image( pInImage->GetWidth()  + 2 * borderWidth,
                                      pInImage->GetHeight() + 2 * borderHeight
                                    );

   for (int bandIndex = 0; bandIndex < pInImage->GetNumberOfBands(); bandIndex++)
   {
      ArrayGrid<double>* pBand = 0;
      pBand = GridExtender<double>::MirrorBorder( pInImage->GetBands()[bandIndex], borderWidth, borderHeight );
      pExpandedImage->AddBand(pBand);
   }
   return pExpandedImage;
}

//===================================================================================================

Image* ImageTools::CropBorder( Image* pInImage, int borderWidth, int borderHeight)
{
   assert( borderWidth >= 0);
   assert( borderHeight >= 0);
   int width = pInImage->GetWidth();
   int height = pInImage->GetHeight();

   if ((borderWidth >= 0) && (borderHeight >= 0))
   {
      int croppedWidth  = width  - 2 * borderWidth;
      int croppedHeight = height - 2 * borderHeight;

      if ((croppedWidth > 5) && (croppedHeight > 5))
      {
         Image* pCroppedImage = new Image( pInImage->GetWidth()  - 2 * borderWidth,
                                           pInImage->GetHeight() - 2 * borderHeight
                                         );

         for (int bandIndex = 0; bandIndex < pInImage->GetNumberOfBands(); bandIndex++)
         {
            ArrayGrid<double>* pBand = 0;
            pBand = GridExtender<double>::CropBorder( pInImage->GetBands()[bandIndex], borderWidth, borderHeight);
            pCroppedImage->AddBand(pBand);
         }
         return pCroppedImage;
      }
      else
      {
         std::cerr << "Image would be to small after cropping: sizes (" << croppedWidth << ", " << croppedHeight << ")" << std::endl << std::flush;
         return 0;
      }
   }
   else
   {
      std::cerr << "Tried to crop image with illegal border sizes (" << borderWidth << ", " << borderHeight << ")" << std::endl << std::flush;
      return 0;
   }
}

//===================================================================================================

Image* ImageTools::PaddBorder( Image* pInImage, int borderWidth, int borderHeight, double paddingValue )
{
   assert( borderWidth >= 0);
   assert( borderHeight >= 0);

   Image* pExpandedImage = new Image( pInImage->GetWidth()  + 2 * borderWidth,
                                      pInImage->GetHeight() + 2 * borderHeight
                                    );

   for (int bandIndex = 0; bandIndex < pInImage->GetNumberOfBands(); bandIndex++)
   {
      ArrayGrid<double>* pBand = 0;
      pBand = GridExtender<double>::PaddBorder( pInImage->GetBands()[bandIndex], borderWidth, borderHeight, paddingValue );
      pExpandedImage->AddBand(pBand);
   }
   return pExpandedImage;
}

//===================================================================================================

Image* ImageTools::ExtractSubImage( Image* pInImage, Point<int> topLeft, Point<int> bottomRight )
{
   assert( topLeft.GetX() >= 0);
   assert( topLeft.GetY() >= 0);
   assert( topLeft.GetX() < pInImage->GetWidth() );
   assert( topLeft.GetY() < pInImage->GetHeight() );

   assert( bottomRight.GetX() >= 0);
   assert( bottomRight.GetY() >= 0);
   assert( bottomRight.GetX() < pInImage->GetWidth() );
   assert( bottomRight.GetY() < pInImage->GetHeight() );

   assert( topLeft.GetX() < bottomRight.GetX() );
   assert( topLeft.GetY() < bottomRight.GetY() );
   int width  = bottomRight.GetX() - topLeft.GetX() + 1;
   int height = bottomRight.GetY() - topLeft.GetY() + 1;

   Image* pCroppedImage = new Image( width, height, pInImage->GetNumberOfBands() );

   for (int bandIndex = 0; bandIndex < pInImage->GetNumberOfBands(); bandIndex++)
   {
      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x++)
         {
            pCroppedImage->GetBands()[bandIndex]->SetValue(x, y, pInImage->GetBands()[bandIndex]->GetValue(x + topLeft.GetX(), y + topLeft.GetY() ) );
         }
      }
   }
   return pCroppedImage;
}
//===================================================================================================

// 2. COMPARE IMAGES
////////////////////

Image* ImageTools::CreateImageSSD( Image* pImage1, Image* pImage2, bool printOutput )
{
   int width = pImage1->GetWidth();
   int height = pImage1->GetHeight();
   int nrBands = pImage1->GetNumberOfBands();

   if ((width == pImage2->GetWidth()) && (height == pImage2->GetHeight()) && (nrBands == pImage2->GetNumberOfBands()) )
   {
      Image* pDiffImage = new Image( width, height );
      for (int bandNr = 0; bandNr < nrBands; bandNr ++)
      {
         if (printOutput)
         {
            std::cout << "\t For band nr " << bandNr << "\t" << std::flush;
         }
         ArrayGrid<double>* pDiffGrid = NumberGridTools<double>::CreateSquaredErrorGrid( pImage1->GetBands()[ bandNr ],
                                                                                         pImage2->GetBands()[ bandNr ],
                                                                                         printOutput );
         if (printOutput)
         {
            std::cout << std::flush;
         }
         pDiffImage->AddBand( pDiffGrid );
      }

      std::string outName = std::string("MSE-") + pImage1->GetImageName() + std::string("-") + pImage2->GetImageName();
      pDiffImage->SetImageName(outName);

      return pDiffImage;
   }
   else
   {
      if (width != pImage2->GetWidth())
      {
         std::cerr << "ERROR: cannot compare images for which widths are not equal: " << width << " != "<< pImage2->GetWidth() << std::endl << std::flush;
      }

      if (height != pImage2->GetHeight())
      {
         std::cerr << "ERROR: cannot compare images for which heights are not equal: " << height << " != " << pImage2->GetHeight() << std::endl << std::flush;
      }

      if (nrBands != pImage2->GetNumberOfBands())
      {
         std::cerr << "ERROR: cannot compare images for which nr of bands are not equal: " << nrBands << " != " << pImage2->GetNumberOfBands() << std::endl << std::flush;
      }
      return 0;
   }
}

//===================================================================================================

double ImageTools::ComputeMSE( Image* pImage1, Image* pImage2 )
{
   int nrBands = pImage1->GetNumberOfBands();
   if ( pImage2->GetNumberOfBands() != nrBands )
   {
      cerr << "Cannot compute MSE: images don't have same number of bands!!!!" << endl << flush;
      return -1;
   }

   double MSE = 0.0;
   for (int bandID = 0; bandID < nrBands; bandID++ )
   {
      MSE += NumberGridTools<double>::ComputeMSE( pImage1->GetBands()[bandID], pImage2->GetBands()[bandID] );
   }
   return (MSE / (double)(nrBands));
}

//===================================================================================================

double ImageTools::ComputePSNR( Image* pImage1, Image* pImage2 )
{
   double MSE = ComputeMSE( pImage1, pImage2 );
   return ( 10.0 * log10( 255.0 * 255.0 / MSE ) );
}

//===================================================================================================

Image* ImageTools::CreateImageSSIM( Image* pImage1, Image* pImage2, int localImageWidth )
{
   int width = pImage1->GetWidth();
   int height = pImage1->GetHeight();
   int nrBands = pImage1->GetNumberOfBands();

   if ((width == pImage2->GetWidth()) && (height == pImage2->GetHeight()) && (nrBands == pImage2->GetNumberOfBands()) )
   {
      Image* pDiffImage = new Image( width, height );
      for (int bandNr = 0; bandNr < nrBands; bandNr ++)
      {
         std::cout << "For band nr " << bandNr << std::endl << std::flush;
         ArrayGrid<double>* pDiffGrid = NumberGridTools<double>::ComputeSSIM( pImage1->GetBands()[ bandNr ], pImage2->GetBands()[ bandNr ], localImageWidth );
         std::cout << std::endl << std::flush;

         double mmin, mmax;
         NumberGridTools<double>::GetMinMax( pDiffGrid, mmin, mmax );

         cout << "SSIM: before rescaling band " << bandNr << " mmin = " << mmin << " and mmax = " << mmax << endl << flush;
         NumberGridTools<double>::RescaleGrid( pDiffGrid, 0.0, 255.0 );
         NumberGridTools<double>::GetMinMax( pDiffGrid, mmin, mmax );

         cout << "SSIM: after rescaling band " << bandNr << " mmin = " << mmin << " and mmax = " << mmax << endl << flush;

         pDiffImage->AddBand( pDiffGrid );
      }

      std::string outName = std::string("SSIM-") + pImage1->GetImageName() + std::string("-") + pImage2->GetImageName();
      pDiffImage->SetImageName(outName);

      return pDiffImage;
   }
   else
   {
      if (width != pImage2->GetWidth())
      {
         std::cerr << "ERROR: cannot compare images for which widths are not equal: " << width << " != "<< pImage2->GetWidth() << std::endl << std::flush;
      }

      if (height != pImage2->GetHeight())
      {
         std::cerr << "ERROR: cannot compare images for which heights are not equal: " << height << " != " << pImage2->GetHeight() << std::endl << std::flush;
      }

      if (nrBands != pImage2->GetNumberOfBands())
      {
         std::cerr << "ERROR: cannot compare images for which nr of bands are not equal: " << nrBands << " != " << pImage2->GetNumberOfBands() << std::endl << std::flush;
      }
      return 0;
   }
}

//===================================================================================================

std::vector<double> ImageTools::GetColorMappingFactors( Image* pImage1, Image* pImage2 )
{
   int width   = pImage1->GetWidth();
   int height  = pImage1->GetHeight();
   int nrBands = pImage1->GetNumberOfBands();
   std::vector<double> colorRatios;

   if ((width == pImage2->GetWidth()) && (height == pImage2->GetHeight()) && (nrBands == pImage2->GetNumberOfBands()))
   {
      for (int bandID = 0; bandID < nrBands; bandID++)
      {
         double mean1 = NumberGridTools<double>::GetGridMean( pImage1->GetBands()[bandID] );
         double mean2 = NumberGridTools<double>::GetGridMean( pImage2->GetBands()[bandID] );
         colorRatios.push_back( mean1 / mean2 );
      }
   }
   else
   {
      cerr << "Impossible to determine ColorMappingFactors when input images have different dimensions or different nr of bands" << endl << flush;
   }
   return colorRatios;
}

//===================================================================================================

void ImageTools::CompareColorCurveInImages( Image* pImage1, Image* pImage2, ColorValue compareColor, int dyTollerance, double& averageDistance, double& nrPixelsOverTolerance )
{
   assert ( pImage1 != 0 );
   assert ( pImage2 != 0 );
   assert ( pImage1->GetWidth() == pImage2->GetWidth() );
   assert ( pImage1->GetHeight() == pImage2->GetHeight() );
   assert ( pImage1->GetNumberOfBands() == 3 );
   assert ( pImage1->GetNumberOfBands() == pImage2->GetNumberOfBands() );

   int width  = pImage1->GetWidth();
   int height = pImage1->GetHeight();
   nrPixelsOverTolerance = 0;
   averageDistance = 0;
   for ( int x = 0; x < width; x++ )
   {
      int localY1 = 0;
      int localY2 = 0;
      for ( int y = 0; y < height; y++ )
      {
         if ( pImage1->GetColor(x, y) == compareColor )
         {
            localY1 = y;
            break;
         }
      }
      for (int y = 0; y < height; y++ )
      {
         if ( pImage2->GetColor(x, y) == compareColor )
         {
            localY2 = y;
            break;
         }
      }
      int deltaY = abs( localY1 - localY2 );
      if ( deltaY > dyTollerance) {nrPixelsOverTolerance++;}
      averageDistance += deltaY;
   }
   averageDistance /= (double)(width);
}

//===================================================================================================

// 3. MIX TWO IMAGES
////////////////////

Image* ImageTools::CreateCheckeredImage( Image* pImage1, Image* pImage2, int blockSize)
{
   int width = pImage1->GetWidth();
   int height = pImage1->GetHeight();
   int nrBands = pImage1->GetNumberOfBands();
   Image* pChecker = 0;
   if ((width == pImage2->GetWidth()) && (height == pImage2->GetHeight()) && (nrBands == pImage2->GetNumberOfBands()))
   {
      pChecker = pImage1->Clone();
      for (int bandNr = 0; bandNr < nrBands; bandNr++ )
      {
         ArrayGrid<double>* pGrid1 = pImage1->GetBands()[bandNr];
         ArrayGrid<double>* pGrid2 = pImage2->GetBands()[bandNr];
         ArrayGrid<double>* pOutGrid = pChecker->GetBands()[bandNr];
         for (int y = 0; y < height; y++)
         {
            for (int x = 0; x < width; x++)
            {
               int xx = x / blockSize;
               int yy = y / blockSize;

               if (((xx + yy) % 2) == 0)
               {
                  pOutGrid->SetValue(x, y, pGrid1->GetValue(x, y));
               }
               else
               {
                  pOutGrid->SetValue(x, y, pGrid2->GetValue(x, y));
               }
            }
         }
      }
      std::string outName = std::string("Checker-") + pImage1->GetImageName() + std::string("-") + pImage2->GetImageName();
      pChecker->SetImageName( outName );
   }
   else
   {
      cerr << "Impossible to create checker board image when input images have different dimensions or different nr of bands" << endl << flush;
   }
   return pChecker;
}


//===================================================================================================

Image* ImageTools::CreateTransparantlyMixedImage( Image* pImage1, Image* pImage2, double thisWeight)
{
   int width = pImage1->GetWidth();
   int height = pImage1->GetHeight();
   int nrBands = pImage1->GetNumberOfBands();
   Image* pTransparant = 0;
   double otherWeight;
   if ((width == pImage2->GetWidth()) && (height == pImage2->GetHeight()) && (nrBands == pImage2->GetNumberOfBands()))
   {
      pTransparant = pImage1->Clone();
      if ((thisWeight > 0.0) && (thisWeight < 1.0))
      {
         otherWeight = 1.0 - thisWeight;
      }
      else
      {
         thisWeight = 0.5;
         otherWeight = 0.5;
      }
      for (int bandNr = 0; bandNr < nrBands; bandNr++ )
      {
         ArrayGrid<double>* pGrid1 = pImage1->GetBands()[bandNr];
         ArrayGrid<double>* pGrid2 = pImage2->GetBands()[bandNr];
         ArrayGrid<double>* pOutGrid = pTransparant->GetBands()[bandNr];
         for (int y = 0; y < height; y++)
         {
            for (int x = 0; x < width; x++)
            {
               pOutGrid->SetValue(x, y, ( (pGrid1->GetValue(x, y) * thisWeight) + (pGrid2->GetValue(x, y) * otherWeight) ));
            }
         }
      }
      std::string outName = std::string("Transparant-") + pImage1->GetImageName() + std::string("-") + pImage2->GetImageName();
      pTransparant->SetImageName(outName);
   }
   else
   {
      cerr << "Impossible to create transparant image when input images have different dimensions or different nr of bands" << endl << flush;
   }

   return pTransparant;
}

//===================================================================================================


// 4. REMAP IMAGE INTENSITIES
/////////////////////////////

Image* ImageTools::ApplyGamma( Image* pInImage, double gamma )
{
   int width = pInImage->GetWidth();
   int height = pInImage->GetHeight();
   int nrBands = pInImage->GetNumberOfBands();

   Image* pGammaImage = pInImage->Clone();

   for (int bandNr = 0; bandNr < nrBands; bandNr ++)
   {
      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x++)
         {
            double gammaCorrected = MathUtils::GammaCorrect( pInImage->GetBands()[bandNr]->GetValue( x, y ), gamma );
            pGammaImage->GetBands()[bandNr]->SetValue( x, y, gammaCorrected );
         }
      }
   }

   stringstream ss;
   ss <<  pInImage->GetImageName() << std::string("-Gamma-") << gamma;
   pGammaImage->SetImageName( ss.str() );
   return pGammaImage;
}

//===================================================================================================

Image* ImageTools::CreateLinearRescaledImage( Image* pImage, bool bandsIndepentant )
{
   Image* pScaledImage = pImage->Clone();
   int nrBands = pImage->GetNumberOfBands();
   if ( bandsIndepentant )
   {
      for (int i = 0; i < nrBands; i++)
      {
         NumberGridTools<double>::RescaleGrid( pScaledImage->GetBands()[i], 0.0, 255.0 );
      }
   }
   else
   {
      double globalMinimum =  1000000000000000.0;
      double globalMaximum = -1000000000000000.0;

      vector< myMinMax > bandMinmaxVector;
      for (int i = 0; i < nrBands; i++)
      {
         myMinMax bandMinMax;
         NumberGridTools<double>::GetMinMax( pImage->GetBands()[i], bandMinMax.min, bandMinMax.max );
         bandMinmaxVector.push_back(bandMinMax);
         if ( bandMinMax.min < globalMinimum )
         {
            globalMinimum = bandMinMax.min;
         }
         if ( bandMinMax.max < globalMaximum )
         {
            globalMaximum = bandMinMax.max;
         }
      }
      for (int i = 0; i < nrBands; i++)
      {
         double newMin = 255.0 * (bandMinmaxVector[i].min - globalMinimum) / (globalMaximum - globalMinimum);
         double newMax = 255.0 * (bandMinmaxVector[i].max - globalMinimum) / (globalMaximum - globalMinimum);
         NumberGridTools<double>::RescaleGrid( pScaledImage->GetBands()[i], newMin, newMax );
      }
   }
   return pScaledImage;
}

//===================================================================================================

Image* ImageTools::ApplyJetColorMap( Image* pInImage )
{
   int width = pInImage->GetWidth();
   int height = pInImage->GetHeight();
   int nrBands = pInImage->GetNumberOfBands();

   if (nrBands == 1)
   {
      Image* pJet = new Image(width, height, 3);
      ArrayGrid<double>* pGrid = pInImage->GetBands()[0];
      double mmin, mmax;
      NumberGridTools<double>::GetMinMax( pGrid, mmin, mmax);

      double nrColors = 256.0;
      double slope = 4.0 / nrColors;
      double peakPoint = nrColors / 4.0;

      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x++)
         {
            double scaledIntensity = 255.0 * (pGrid->GetValue(x, y) - mmin) / (mmax - mmin);

            for (int bandNr = 0; bandNr < 3; bandNr ++)
            {
               double value = MathUtils::GetMin( MathUtils::GetMax( (1.5 - fabs( slope * ( scaledIntensity + (double)(bandNr-3.0) * peakPoint) ) ), 0.0 ), 1.0 );
               pJet->GetBands()[bandNr]->SetValue(x, y, 255.0 * value);
            }
         }
      }
      pJet->SetImageName( std::string("JetColorMap") );
      return pJet;
   }
   else
   {
      cerr << "Impossible to apply jet color map to image with more than 1 band" << endl << flush;
      return 0;
   }
}

//===================================================================================================

Image* ImageTools::ConvertToGrayImage( Image* pInImage )
{
   int width = pInImage->GetWidth();
   int height = pInImage->GetHeight();
   int nrBands = pInImage->GetNumberOfBands();

   Image* pGray = new Image(width, height, 1);

   if (nrBands == 3)
   {
      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x++)
         {
            pGray->GetBands()[0]->SetValue( x, y, TransformColorSpace::RGBToGray( pInImage->GetColor( x, y) ) );
         }
      }
      pGray->SetImageName( std::string("GrayImage") );
      return pGray;
   }
   else
   {
      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x++)
         {
            double avgIntensity = 0.0;
            for (int bandNr = 0; bandNr < nrBands; bandNr++)
            {
               avgIntensity += pInImage->GetBands()[bandNr]->GetValue( x, y );
            }
            pGray->GetBands()[0]->SetValue( x, y, (avgIntensity / (double)(nrBands)) );
         }
      }
      pGray->SetImageName( std::string("GrayImage") );
      return pGray;
   }
}

//===================================================================================================

Image* ImageTools::ConvertToSepiaImage( Image* pInImage )
{
   int width = pInImage->GetWidth();
   int height = pInImage->GetHeight();

   Image* pSepia = new Image(width, height, 3);
   bool needsDelete = false;
   Image* pGray = 0;
   if ( pInImage->GetNumberOfBands() > 1)
   {
      pGray = ImageTools::ConvertToGrayImage( pInImage );
      needsDelete = true;
   }
   else
   {
      pGray = pInImage;
   }

   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         pSepia->SetColor(x, y, TransformColorSpace::RGBToSepia2( pGray->GetBands()[0]->GetValue(x, y) ) );
      }
   }

   if (needsDelete)
   {
      delete pGray;
   }

   pSepia->SetImageName( std::string("SepiaImage") );
   return pSepia;
}

//===================================================================================================

Image* ImageTools::Negative( Image* pInImage )
{
   Image* pImageOut = pInImage->Clone();
   int nrBands = pInImage->GetNumberOfBands();

   int width = pInImage->GetWidth();
   int height = pInImage->GetHeight();
   for(int bandNr = 0; bandNr < nrBands; bandNr++)
   {
      ArrayGrid<double>* pGridIn  = pInImage->GetBands()[bandNr];
      ArrayGrid<double>* pGridOut = pImageOut->GetBands()[bandNr];
      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x++)
         {
            pGridOut->SetValue( x, y, (255.0 - pGridIn->GetValue( x, y) ) );
         }
      }
   }
   return pImageOut;
}

//===================================================================================================

// 5. ROTATE IMAGE LOSSLESS
///////////////////////////

Image* ImageTools::Rotate90DegreesClockwise( Image* pInImage )
{
   int width = pInImage->GetWidth();
   int height = pInImage->GetHeight();
   int nrBands = pInImage->GetNumberOfBands();
   Image* pOutImage = new Image( width, height );

   for (int bandID = 0; bandID < nrBands; bandID++ )
   {
      ArrayGrid<double>* pOutGrid = NumberGridTools<double>::Rotate90DegreesClockwise(  pInImage->GetBands()[ bandID ] );
      pOutImage->AddBand( pOutGrid );
   }
   return pOutImage;
}

//===================================================================================================

Image* ImageTools::Rotate90DegreesCounterClockwise( Image* pInImage )
{
   int width = pInImage->GetWidth();
   int height = pInImage->GetHeight();
   int nrBands = pInImage->GetNumberOfBands();
   Image* pOutImage = new Image( width, height );

   for (int bandID = 0; bandID < nrBands; bandID++ )
   {
      ArrayGrid<double>* pOutGrid = NumberGridTools<double>::Rotate90DegreesCounterClockwise(  pInImage->GetBands()[ bandID ] );
      pOutImage->AddBand( pOutGrid );
   }
   return pOutImage;
}

//===================================================================================================

Image* ImageTools::Rotate180Degrees( Image* pInImage )
{
   int width = pInImage->GetWidth();
   int height = pInImage->GetHeight();
   int nrBands = pInImage->GetNumberOfBands();
   Image* pOutImage = new Image( width, height );

   for (int bandID = 0; bandID < nrBands; bandID++ )
   {
      ArrayGrid<double>* pOutGrid = NumberGridTools<double>::Rotate180Degrees(  pInImage->GetBands()[ bandID ] );
      pOutImage->AddBand( pOutGrid );
   }
   return pOutImage;
}

//===================================================================================================

// 6. MISCELLANEOUS
///////////////////

double ImageTools::GetLocalDarkChannel( Image* pInImage, int xLocalCenter, int yLocalCenter, int windowSize )
{
   int nrBands = pInImage->GetNumberOfBands();
   double tmpMin = NumberGridTools<double>::GetLocalMinimum( pInImage->GetBands()[0], xLocalCenter, yLocalCenter, windowSize, windowSize );
   double darkChannelValue = tmpMin;
   for (int i = 1; i < nrBands; i++)
   {
      tmpMin = NumberGridTools<double>::GetLocalMinimum( pInImage->GetBands()[i], xLocalCenter, yLocalCenter, windowSize, windowSize );
      if (tmpMin < darkChannelValue) {darkChannelValue = tmpMin;}
   }
   return darkChannelValue;
}

//===================================================================================================


}
}
