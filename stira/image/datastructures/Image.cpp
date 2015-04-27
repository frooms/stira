
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

#include "Image.h"
#include "../tools/NumberGridTools.h"
#include "../../common/common/Random.h"
#include "../../common/common/MathUtils.h"
#include "../color/TransformColorSpace.h"
#include <cassert>
namespace stira {
namespace image {

using namespace common;

Image::Image(int width, int height )
{
   assert(width > 0);
   assert(height > 0);
   mImageWidth = width;
   mImageHeight = height;
}

//---------------------------------------------------------------------------------------------------

Image::~Image()
{
   #ifdef DEBUG
   cout << "DELETING Image " << this << " which has " << vpBands.size() << " bands " << endl << flush;
   #endif
   for (int bandIndex = 0; bandIndex < GetNumberOfBands(); bandIndex ++)
   {
      #ifdef DEBUG
         cout << "DELETING band " << bandIndex << flush;
      #endif
      delete vpBands[bandIndex];
      #ifdef DEBUG
         cout << "\t after DELETING band " << bandIndex << " there are " << vpBands.size() << " bands left" << endl << flush;
      #endif
   }
}

//---------------------------------------------------------------------------------------------------

Image::Image(Image &otherImage)
{
   mImageWidth  = otherImage.GetWidth();
   mImageHeight = otherImage.GetHeight();

   for (int i = 0; i < otherImage.GetNumberOfBands(); i++)
   {
      ArrayGrid<double>* pNewBand;
      pNewBand = new ArrayGrid<double>(*(otherImage.GetBands()[i]));
      AddBand( pNewBand );
   }
   string imagename = otherImage.GetImageName() + string("-Clone");
   SetImageName( imagename );
}

//---------------------------------------------------------------------------------------------------

Image::Image(int width, int height, int nrBands )
{
   assert( width > 0);
   assert( height > 0);
   assert( nrBands > 0);
   mImageWidth = width;
   mImageHeight = height;
   bool needInitialisation = true;
   double initialRealValue = 0.0;

   for (int bandIndex = 0; bandIndex < nrBands; bandIndex++)
   {
      ArrayGrid<double>* pBand = new ArrayGrid<double>( mImageWidth, mImageHeight, needInitialisation, initialRealValue );
      AddBand(pBand);
   }
}

//---------------------------------------------------------------------------------------------------

Image::Image( ArrayGrid<double>* pDataGrid )
{
   assert( pDataGrid != 0);
   assert( pDataGrid->GetWidth() > 0);
   assert( pDataGrid->GetHeight() > 0);
   mImageWidth = pDataGrid->GetWidth();
   mImageHeight = pDataGrid->GetHeight();
   AddBand( pDataGrid );
}

//===================================================================================================

Image::Image( ArrayGrid<bool>* pBoolGrid )
{
   assert( pBoolGrid != 0);
   assert( pBoolGrid->GetWidth() > 0);
   assert( pBoolGrid->GetHeight() > 0);

   mImageWidth = pBoolGrid->GetWidth();
   mImageHeight = pBoolGrid->GetHeight();
   bool needInitialisation = true;
   double initialRealValue = 0.0;

   ArrayGrid<double>* pDataGrid = new ArrayGrid<double>( mImageWidth, mImageHeight, needInitialisation, initialRealValue );
   for (int y = 0; y < mImageHeight; y++)
   {
      for (int x = 0; x < mImageWidth; x++)
      {
         double value = (pBoolGrid->GetValue( x, y ) ) ? (255.0) : (0.0);
         pDataGrid->SetValue(x, y, value);
      }
   }
   AddBand( pDataGrid );
}

//===================================================================================================

Image* Image::ExtractROIAsNewImage( RectangularROI<int> rroi )
{
   Image* pSubImage = new Image( rroi.GetWidth(), rroi.GetHeight(), this->GetNumberOfBands() );
   for (int bandID = 0; bandID < this->GetNumberOfBands(); bandID++)
   {
      for (int y = 0; y < rroi.GetHeight(); y++)
      {
         for (int x = 0; x < rroi.GetWidth(); x++)
         {
            pSubImage->GetBands()[bandID]->SetValue( x, y, this->GetBands()[bandID]->GetValue( x + rroi.GetTopLeftCorner().GetX(),
                                                                                               y + rroi.GetTopLeftCorner().GetY() ) );
         }
      }
   }
   return pSubImage;
}

//===================================================================================================

Image* Image::Clone()
{
   return new Image(*this);
}

//===================================================================================================

std::string Image::GetImageName()
{
   return mImageName;
}

//===================================================================================================

void Image::SetImageName( std::string imagename )
{
   mImageName = imagename;
}

//===================================================================================================

void Image::AddBand( ArrayGrid<double>* myBand)
{
   if ( GetNumberOfBands() != 0)
   {
      if ( ( myBand->GetWidth() == mImageWidth ) && ( myBand->GetHeight() == mImageHeight ) )
      {
         vpBands.push_back(myBand);
      }
      else
      {
         cerr << "ERROR: Trying to add band with wrong dimensions" << endl << flush;
      }
   }
   else
   {
      mImageWidth  = myBand->GetWidth();
      mImageHeight = myBand->GetHeight();
      vpBands.push_back(myBand);
   }
}

//===================================================================================================

bool Image::InsertSubImage( Image* pSubImage, int xTop, int yTop )
{
   if ( pSubImage == 0 )
   {
      cerr << "Invalid subimage to insert." << endl << flush;
      return false;
   }

   if ( ( xTop < 0 ) || ( yTop < 0 ) || ( pSubImage->GetNumberOfBands() ==  this->GetNumberOfBands() ) )
   {
      cerr << "Invalid subimage insertion point / nr of bands." << endl << flush;
      return false;
   }

   int width  = this->GetWidth();
   int height = this->GetHeight();
   int nrBands = this->GetNumberOfBands();
   if ( ( xTop >= width ) || ( yTop > height ) )
   {
      cerr << "Invalid subimage start dimensions." << endl << flush;
      return false;
   }
   int subGridWidth  = pSubImage->GetWidth();
   int subGridHeight = pSubImage->GetHeight();

   if ( ( (xTop + subGridWidth) >= width ) || ( (yTop + subGridHeight) >= height ) )
   {
      cerr << "Invalid subimage stop dimensions." << endl << flush;
      return false;
   }

   for (int bandNr = 0; bandNr < nrBands; bandNr++ )
   {
      for (int y = 0; y < subGridHeight; y++)
      {
         for (int x = 0; x < subGridWidth; x++)
         {
            int xx = x + xTop;
            int yy = y + yTop;
            this->GetBands()[bandNr]->SetValue( xx, yy, pSubImage->GetBands()[bandNr]->GetValue( x, y ) );
         }
      }
   }
   return true;
}

//===================================================================================================

bool Image::InsertSubGrid( ArrayGrid<double>* pSubGrid, int xTop, int yTop )
{
   if ( pSubGrid == 0 )
   {
      cerr << "Invalid subimage to insert." << endl << flush;
      return false;
   }

   if ( ( xTop < 0 ) || ( yTop < 0 ) )
   {
      cerr << "Invalid subimage insertion point." << endl << flush;
      return false;
   }

   int width  = this->GetWidth();
   int height = this->GetHeight();
   int nrBands = this->GetNumberOfBands();
   if ( ( xTop >= width ) || ( yTop > height ) )
   {
      cerr << "Invalid subimage start dimensions." << endl << flush;
      return false;
   }
   int subGridWidth  = pSubGrid->GetWidth();
   int subGridHeight = pSubGrid->GetHeight();

   if ( ( (xTop + subGridWidth) >= width ) || ( (yTop + subGridHeight) >= height ) )
   {
      cerr << "Invalid subimage stop dimensions." << endl << flush;
      return false;
   }
   ArrayGrid<double>* pScaledGrid = pSubGrid->Clone();
   NumberGridTools<double>::RescaleGrid( pScaledGrid, 0.0, 255.0 );
   for (int bandNr = 0; bandNr < nrBands; bandNr++ )
   {
      for (int y = 0; y < subGridHeight; y++)
      {
         for (int x = 0; x < subGridWidth; x++)
         {
            int xx = x + xTop;
            int yy = y + yTop;
            this->GetBands()[bandNr]->SetValue( xx, yy, pScaledGrid->GetValue( x, y ) );
         }
      }
   }
   delete pScaledGrid;
   return true;
}

//===================================================================================================

void Image::RemoveBand( ArrayGrid<double>* pBand)
{
   delete pBand;
   vector< ArrayGrid<double>* >::iterator banditer = remove(vpBands.begin(), vpBands.end(), pBand);
   vpBands.erase(banditer, vpBands.end());
}

//===================================================================================================

void Image::ReplaceBand( ArrayGrid<double>* pBandOld, ArrayGrid<double>* pBandNew )
{
   delete pBandOld;  // object is deleted; "dangling" pointer is still present in vpBands

   for (int bandID = 0; bandID < GetNumberOfBands(); bandID++)
   {
      if ( vpBands[bandID] == pBandOld )
      {
         vpBands[bandID] = pBandNew;
      }
   }
}

//===================================================================================================

void Image::RemoveBand(int i)
{
   delete vpBands[i];
   vpBands.erase(vpBands.begin() + i);
}

//===================================================================================================

std::vector< ArrayGrid<double>* >& Image::GetBands()
{
   return vpBands;
}

//===================================================================================================

void Image::Diagnose( std::string ID )
{
   cout << "Image " << ID << " width = " << GetWidth() << " height = " << GetHeight() << " nr of bands = " << GetNumberOfBands() << endl << flush;

   if (GetNumberOfBands() > 0)
   {
      for (int bandNr = 0; bandNr < GetNumberOfBands(); bandNr ++)
      {
         ArrayGrid<double>* pGrid = this->GetBands()[bandNr];
         if (pGrid != 0)
         {
            double tmpMin, tmpMax, meanIntensity, varianceIntensity, kurtosisIntensity;
            cout << "\t band " << bandNr << flush;

            NumberGridTools<double>::GetMinMax( this->GetBands()[bandNr], tmpMin, tmpMax );

            meanIntensity = NumberGridTools<double>::GetGridMean( pGrid );
            varianceIntensity = NumberGridTools<double>::GetGridVariance( pGrid, meanIntensity );
            kurtosisIntensity = NumberGridTools<double>::GetGridKurtosis( pGrid, meanIntensity, varianceIntensity );
            cout << " has min = " << tmpMin << " and max = " << tmpMax << " meanIntensity = " << meanIntensity
                 << " variance = " << varianceIntensity << " and kurtosis = " << kurtosisIntensity << endl << flush;
         }
         else
         {
            cerr << "Image::Diagnose::ERROR: Image band " << bandNr << " is 0!!!" << endl << flush;
         }
      }
   }
   else
   {
      cerr << "Image::Diagnose::ERROR: Image contains no valid bands!!!" << endl << flush;
   }
}

//===================================================================================================

void Image::Rescale( double newMin, double newMax )
{
   if (GetNumberOfBands() > 0)
   {
      double mmin, mmax;
      this->GetMinMax( mmin, mmax );
      int height = GetHeight();
      int width = GetWidth();

      for (int bandNr = 0; bandNr < GetNumberOfBands(); bandNr ++)
      {
         ArrayGrid<double>* pGrid = this->GetBands()[bandNr];

         double gridMin, gridMax;
         NumberGridTools<double>::GetMinMax( pGrid, gridMin, gridMax );
         if (pGrid != 0)
         {
            if ((mmax - mmin) < 0.0001)
            {
               for (int y = 0; y < height; y++)
               {
                  for (int x = 0; x < width; x++)
                  {
                     pGrid->SetValue(x, y, mmax);
                  }
               }
            }
            else
            {
               for (int y = 0; y < height; y++)
               {
                  for (int x = 0; x < width; x++)
                  {
                     pGrid->SetValue(x, y, ( ((pGrid->GetValue(x, y) - mmin) / (mmax - mmin) ) * (newMax - newMin)) + newMin );
                  }
               }
            }
         }
         else
         {
            cerr << "Image band << " << bandNr << " is NULL!!!" << endl << flush;
            return;
         }
      }
   }
   else
   {
      cerr << "Image::GetMinMax::ERROR: Image contains no valid bands!!!" << endl << flush;
      return;
   }
}

//===================================================================================================

void Image::GetMinMax(double& mmin, double& mmax, int& minBandNr, int& maxBandNr)
{
   double tmpMin, tmpMax;
   mmin =  100000000000000000000000000.0;
   mmax = -100000000000000000000000000.0;

   if (GetNumberOfBands() > 0)
   {
      for (int bandNr = 0; bandNr < GetNumberOfBands(); bandNr ++)
      {
         ArrayGrid<double>* pGrid = this->GetBands()[bandNr];
         if (pGrid != 0)
         {
            NumberGridTools<double>::GetMinMax( pGrid, tmpMin, tmpMax );
            if (tmpMin < mmin) {mmin = tmpMin; minBandNr = bandNr;}
            if (tmpMax > mmax) {mmax = tmpMax; maxBandNr = bandNr;}
         }
         else
         {
            cerr << "Image::GetMinMax::ERROR: Image band " << bandNr << " is 0!!!" << endl << flush;
         }
      }
   }
   else
   {
      cerr << "Image::GetMinMax::ERROR: Image contains no valid bands!!!" << endl << flush;
   }
}

//===================================================================================================

void Image::GetMinMax(double& mmin, double& mmax )
{
   int i, j;
   GetMinMax( mmin, mmax, i, j );
}

//===================================================================================================

double Image::GetAbsMax( )
{
   double tmpMax;
   double mmax = 0.0;

   if (GetNumberOfBands() > 0)
   {
      for (int bandNr = 0; bandNr < GetNumberOfBands(); bandNr ++)
      {
         ArrayGrid<double>* pGrid = this->GetBands()[bandNr];
         if (pGrid != 0)
         {
            tmpMax = NumberGridTools<double>::GetAbsMax( pGrid );
            if (tmpMax > mmax) {mmax = tmpMax;}
         }
         else
         {
            cerr << "Image::GetMinMax::ERROR: Image band " << bandNr << " is 0!!!" << endl << flush;
         }
      }
   }
   else
   {
      cerr << "Image::GetMinMax::ERROR: Image contains no valid bands!!!" << endl << flush;
   }
   return mmax;
}

//===================================================================================================

int Image::GetWidth()
{
   return mImageWidth;
}

//===================================================================================================

int Image::GetNumberOfBands()
{
   return static_cast<int>(vpBands.size());
}

//===================================================================================================

int Image::GetHeight()
{
   return mImageHeight;
}

//===================================================================================================

void Image::CopyImageValues(Image* pOtherImage)
{
   int width   = pOtherImage->GetWidth();
   int height  = pOtherImage->GetHeight();
   int nrBands = pOtherImage->GetNumberOfBands();

   if (   ( pOtherImage->GetWidth() == width )
       && ( pOtherImage->GetHeight() == height )
       && ( pOtherImage->GetNumberOfBands() == nrBands )
      )
   {
      for (int bandNr=0; bandNr < nrBands; bandNr++)
      {
         for (int y = 0; y < height; y++)
         {
            for (int x = 0; x < width; x++)
            {
               this->GetBands()[bandNr]->SetValue(x, y, pOtherImage->GetBands()[bandNr]->GetValue(x, y));
            }
         }
      }
   }
   else
   {
      cerr << "ERROR: source image must have equal sizes and nr of bands to be able to copy its values" << endl << flush;
   }
}

//===================================================================================================

void Image::ClipImageValues( double clippedMin, double clippedMax )
{
   int width   = this->GetWidth();
   int height  = this->GetHeight();
   int nrBands = this->GetNumberOfBands();

   for (int bandNr=0; bandNr < nrBands; bandNr++)
   {
      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x++)
         {
            this->GetBands()[bandNr]->SetValue( x, y,
                                                MathUtils::ClipValue( this->GetBands()[bandNr]->GetValue(x, y),
                                                                      clippedMin,
                                                                      clippedMax
                                                                    )
                                              );
         }
      }
   }
}

//===================================================================================================

void Image::MultiplyWith(Image* pImg)
{
   if ((pImg->GetWidth() == this->GetWidth() ) && (pImg->GetHeight() == this->GetHeight() ) && (pImg->GetNumberOfBands() == this->GetNumberOfBands() ))
   {
      for (int bandNr = 0; bandNr <  this->GetNumberOfBands(); bandNr++ )
      {
         this->GetBands()[bandNr]->MultiplyWith(pImg->GetBands()[bandNr]);
      }
   }
}

//===================================================================================================

void Image::Scale( double factor )
{
   int width   = this->GetWidth();
   int height  = this->GetHeight();
   int nrBands = this->GetNumberOfBands();
   for (int bandNr=0; bandNr < nrBands; bandNr++)
   {
      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x++)
         {
            this->GetBands()[bandNr]->SetValue(x, y, this->GetBands()[bandNr]->GetValue(x, y ) * factor );
         }
      }
   }
}

//===================================================================================================

void Image::AddGaussianNoise( double sigma, bool isColored )
{
   int nrBands = this->GetNumberOfBands();
   int width  = this->GetWidth();
   int height = this->GetHeight();

   double mmin = 0.0;
   double mmax = 255.0;
   Random rn;

   if (isColored)
   {
      for (int bandNr = 0; bandNr < nrBands; bandNr++ )
      {
         ArrayGrid<double>* pGrid = this->GetBands()[bandNr];
         for (int y = 0; y < height; y++)
         {
            for (int x = 0; x < width; x++)
            {
               GetBands()[bandNr]->SetValue(x, y, MathUtils::ClipValue( (pGrid->GetValue(x, y) + rn.normal( 0.0, sigma ) ), mmin, mmax) );
            }
         }
      }
   }
   else
   {
      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x++)
         {
            double noiseAddition = rn.normal( 0.0, sigma );
            for (int bandNr = 0; bandNr < nrBands; bandNr++ )
            {
               double noiseValue = MathUtils::ClipValue( (GetBands()[bandNr]->GetValue(x, y) + noiseAddition), mmin, mmax );
               GetBands()[bandNr]->SetValue(x, y, noiseValue );
            }
         }
      }
   }
}

//===================================================================================================

void Image::ApplyPoissonNoise( double factor, bool isColored )
{
   int nrBands = this->GetNumberOfBands();
   int width  = this->GetWidth();
   int height = this->GetHeight();

   Random rn;
   double mmin = 0.0;
   double mmax = 255.0;

   if (isColored || nrBands != 3)
   {
      for (int bandNr = 0; bandNr < nrBands; bandNr++ )
      {
         ArrayGrid<double>* pGrid = this->GetBands()[bandNr];
         for (int y = 0; y < height; y++)
         {
            for (int x = 0; x < width; x++)
            {
               double noiseValue = MathUtils::ClipValue( factor * ( (rn.poisson( (pGrid->GetValue(x, y)  / factor) + 0.5) ) ), mmin, mmax );

               pGrid->SetValue(x, y, noiseValue);
            }
         }
      }
   }
   else
   {
      TransformColorSpace tcs;
      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x++)
         {
            ColorValue cv1 =tcs.RGBtoHSV( this->GetColor( x, y ) );

            // little trick: poisson random variable generation is integer-based, while V is between 0 and 1;
            // so we stretch the range in 256 bins and rescale afterwards back to between 0 and 1
            double tmpValue = 256.0 * cv1.c[2] / factor;
            if ( tmpValue > 0 )
            {
               cv1.c[2] = MathUtils::ClipValue( factor * ( rn.poisson( tmpValue ) ) / 256.0, 0.0, 1.0 );
            }

            ColorValue cv2 = tcs.HSVtoRGB( cv1 );
            this->SetColor( x, y, cv2 );
         }
      }
   }
}

//===================================================================================================

void Image::ApplySaltAnPepperNoise(double fraction, bool isColored)
{
   int nrBands = this->GetNumberOfBands();
   int width  = this->GetWidth();
   int height = this->GetHeight();

   double mmin = 0.0;
   double mmax = 255.0;

   Random rn;

   if (isColored)
   {
      for (int bandNr = 0; bandNr < nrBands; bandNr++ )
      {
         ArrayGrid<double>* pGrid = this->GetBands()[bandNr];
         for (int y = 0; y < height; y++)
         {
            for (int x = 0; x < width; x++)
            {
               double value1 = rn.uniform( );
               double value2 = rn.uniform( );
               if (value1 < fraction)
               {
                  if (value2 < 0.5)
                  {
                     pGrid->SetValue(x, y, mmin);
                  }
                  else
                  {
                     pGrid->SetValue(x, y, mmax);
                  }
               }
            }
         }
      }
   }
   else
   {
      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x++)
         {
            double newValue;
            double value1 = rn.uniform( );
            double value2 = rn.uniform( );
            if (value1 < fraction)
            {
               if (value2 < 0.5)
               {
                  newValue = mmin;
               }
               else
               {
                  newValue = mmax;
               }
               for (int bandNr = 0; bandNr < nrBands; bandNr++ )
               {
                  GetBands()[bandNr]->SetValue(x, y, newValue);
               }
            }
         }
      }
   }
}


ColorValue Image::GetColor(int x, int y)
{
   ColorValue cv;
   if ( this->GetNumberOfBands() == 3 )
   {
      for(int i = 0; i < 3; i++)
      {
         cv.c[i] = this->GetBands()[i]->GetValue(x, y);
      }
   }
   else
   {
      for(int i = 0; i < 3; i++)
      {
         cv.c[i] = this->GetBands()[0]->GetValue(x, y);
      }
   }
   return cv;
}

//===================================================================================================

void Image::SetColor(int x, int y, ColorValue cv)
{
   if ( this->GetNumberOfBands() == 3 )
   {
      for(int i = 0; i < 3; i++)
      {
         this->GetBands()[i]->SetValue(x, y, cv.c[i]);
      }
   }
}

//===================================================================================================

ColorValue Image::GetColor( Point<int> pt )
{
   return GetColor( pt.GetX(), pt.GetY() );
}

//===================================================================================================

void Image::SetColor( Point<int> pt, ColorValue cv)
{
   SetColor( pt.GetX(), pt.GetY(), cv);
}

//===================================================================================================

// H is between 0 and 360 degrees; S and V are between 0 and 1
bool Image::HSVToRGB()
{
   int nrBands = this->GetNumberOfBands();

   TransformColorSpace tcsp;

   if (nrBands == 3)
   {
      int width = this->GetWidth();
      int height = this->GetHeight();

      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x++)
         {
            ColorValue hsvValue = this->GetColor( x, y);
            ColorValue rgbValue = tcsp.HSVtoRGB( hsvValue );
            this->SetColor( x,  y, rgbValue );
         }
      }
      return true;
   }
   else
   {
      cerr << "Impossible to convert image with " << nrBands << " band(s) from HSV to RGB." << endl << flush;
      return false;
   }
}

//===================================================================================================

// H is between 0 and 360 degrees; S and V are between 0 and 1
bool Image::RGBToHSV()
{
   TransformColorSpace tcsp;
   int nrBands = this->GetNumberOfBands();

   if (nrBands == 3)
   {
      int width = this->GetWidth();
      int height = this->GetHeight();

      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x++)
         {
            ColorValue rgbValue = this->GetColor( x, y);
            ColorValue hsvValue = tcsp.RGBtoHSV( rgbValue );
            this->SetColor( x, y, hsvValue );
         }
      }
      return true;
   }
   else
   {
      cerr << "Impossible to convert image with " << nrBands << " band(s) from RGB to HSV." << endl << flush;
      return false;
   }
}

//===================================================================================================

bool Image::HSIToRGB()
{
   TransformColorSpace tcsp;
   int nrBands = this->GetNumberOfBands();
   if (nrBands == 3)
   {
      int width = this->GetWidth();
      int height = this->GetHeight();

      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x++)
         {
            ColorValue hsiValue = this->GetColor( x, y);
            ColorValue rgbValue = tcsp.HSItoRGB( hsiValue );
            this->SetColor( x, y, rgbValue );
         }
      }
      return true;
   }
   else
   {
      cerr << "Impossible to convert image with " << nrBands << " band(s) from HSI to RGB." << endl << flush;
      return false;
   }
}

//===================================================================================================

bool Image::RGBToHSI()
{
   TransformColorSpace tcsp;
   int nrBands = this->GetNumberOfBands();
   if (nrBands == 3)
   {
      int width = this->GetWidth();
      int height = this->GetHeight();

      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x++)
         {
            ColorValue rgbValue = this->GetColor( x, y);
            ColorValue hsiValue = tcsp.RGBtoHSI( rgbValue );
            this->SetColor( x, y, hsiValue );
         }
      }
      return true;
   }
   else
   {
      cerr << "Impossible to convert image with " << nrBands << " band(s) from RGB to HSI." << endl << flush;
      return false;
   }
}

//===================================================================================================

bool Image::sRGBToXYZ( ColorValue referenceIlluminant )
{
   TransformColorSpace tcsp;
   tcsp.SetReferenceWhite( referenceIlluminant );
   int nrBands = this->GetNumberOfBands();
   if (nrBands == 3)
   {
      int width = this->GetWidth();
      int height = this->GetHeight();

      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x++)
         {
            ColorValue rgbValue = this->GetColor( x, y);
            ColorValue xyzValue = tcsp.sRGBtoXYZ( rgbValue );
            this->SetColor( x, y, xyzValue );
         }
      }
      return true;
   }
   else
   {
      cerr << "Impossible to convert image with " << nrBands << " band(s) from sRGB to XYZ." << endl << flush;
      return false;
   }
}

//===================================================================================================

bool Image::XYZTosRGB( ColorValue referenceIlluminant )
{
   TransformColorSpace tcsp;
   tcsp.SetReferenceWhite( referenceIlluminant );
   int nrBands = this->GetNumberOfBands();
   if (nrBands == 3)
   {
      int width = this->GetWidth();
      int height = this->GetHeight();

      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x++)
         {
            ColorValue xyzValue = this->GetColor( x, y);
            ColorValue rgbValue = tcsp.XYZtosRGB( xyzValue );
            this->SetColor( x, y, rgbValue );
         }
      }
      return true;
   }
   else
   {
      cerr << "Impossible to convert image with " << nrBands << " band(s) from XYZ to sRGB." << endl << flush;
      return false;
   }
}

//===================================================================================================

bool Image::AdobeRGBToXYZ( ColorValue referenceIlluminant )
{
   TransformColorSpace tcsp;
   tcsp.SetReferenceWhite( referenceIlluminant );
   int nrBands = this->GetNumberOfBands();
   if (nrBands == 3)
   {
      int width = this->GetWidth();
      int height = this->GetHeight();

      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x++)
         {
            if ( (x == 450) && (y == 50) )
            {
               cout << "NAN" << endl << flush;
            }
            ColorValue rgbValue = this->GetColor( x, y);
            ColorValue xyzValue = tcsp.AdobeRGBtoXYZ( rgbValue );
            this->SetColor( x, y, xyzValue );
         }
      }
      return true;
   }
   else
   {
      cerr << "Impossible to convert image with " << nrBands << " band(s) from AdobeRGB to XYZ." << endl << flush;
      return false;
   }
}

//===================================================================================================

bool Image::XYZToAdobeRGB( ColorValue referenceIlluminant )
{
   TransformColorSpace tcsp;
   tcsp.SetReferenceWhite( referenceIlluminant );
   int nrBands = this->GetNumberOfBands();
   if (nrBands == 3)
   {
      int width = this->GetWidth();
      int height = this->GetHeight();

      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x++)
         {
            if ( (x == 450) && (y == 50) )
            {
               cout << "NAN" << endl << flush;
            }
            ColorValue xyzValue = this->GetColor( x, y);
            ColorValue rgbValue = tcsp.XYZtoAdobeRGB( xyzValue );
            this->SetColor( x, y, rgbValue );
         }
      }
      return true;
   }
   else
   {
      cerr << "Impossible to convert image with " << nrBands << " band(s) from XYZ to AdobeRGB." << endl << flush;
      return false;
   }
}

//===================================================================================================

bool Image::sRGBToLuv( ColorValue referenceIlluminant )
{
   TransformColorSpace tcsp;
   tcsp.SetReferenceWhite( referenceIlluminant );
   int nrBands = this->GetNumberOfBands();
   if (nrBands == 3)
   {
      int width = this->GetWidth();
      int height = this->GetHeight();

      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x++)
         {
            this->SetColor( x, y, tcsp.sRGBtoLuv( this->GetColor( x, y) ) );
         }
      }
      return true;
   }
   else
   {
      cerr << "Impossible to convert image with " << nrBands << " band(s) from sRGB to Luv." << endl << flush;
      return false;
   }
}

//===================================================================================================

bool Image::LuvTosRGB( ColorValue referenceIlluminant )
{
   TransformColorSpace tcsp;
   tcsp.SetReferenceWhite( referenceIlluminant );
   int nrBands = this->GetNumberOfBands();
   if (nrBands == 3)
   {
      int width = this->GetWidth();
      int height = this->GetHeight();

      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x++)
         {
            this->SetColor( x, y, tcsp.LuvtosRGB( this->GetColor( x, y) ) );
         }
      }
      return true;
   }
   else
   {
      cerr << "Impossible to convert image with " << nrBands << " band(s) from Luv to sRGB." << endl << flush;
      return false;
   }
}

//===================================================================================================

bool Image::sRGBToLab( ColorValue referenceIlluminant )
{
   TransformColorSpace tcsp;
   tcsp.SetReferenceWhite( referenceIlluminant );
   int nrBands = this->GetNumberOfBands();
   if (nrBands == 3)
   {
      int width = this->GetWidth();
      int height = this->GetHeight();

      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x++)
         {
            this->SetColor( x, y, tcsp.sRGBtoLab( this->GetColor( x, y) ) );
         }
      }
      return true;
   }
   else
   {
      cerr << "Impossible to convert image with " << nrBands << " band(s) from sRGB to Lab." << endl << flush;
      return false;
   }
}

//===================================================================================================

bool Image::LabTosRGB( ColorValue referenceIlluminant )
{
   TransformColorSpace tcsp;
   tcsp.SetReferenceWhite( referenceIlluminant );
   int nrBands = this->GetNumberOfBands();
   if (nrBands == 3)
   {
      int width = this->GetWidth();
      int height = this->GetHeight();

      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x++)
         {
            this->SetColor( x, y, tcsp.LabtosRGB( this->GetColor( x, y) ) );
         }
      }
      return true;
   }
   else
   {
      cerr << "Impossible to convert image with " << nrBands << " band(s) from Lab to sRGB." << endl << flush;
      return false;
   }
}

//===================================================================================================

bool Image::RGBToYUV()
{
   TransformColorSpace tcsp;
   int nrBands = this->GetNumberOfBands();
   if (nrBands == 3)
   {
      int width = this->GetWidth();
      int height = this->GetHeight();

      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x++)
         {
            this->SetColor( x, y, tcsp.RGBtoYUV( this->GetColor( x, y) ) );
         }
      }
      return true;
   }
   else
   {
      cerr << "Impossible to convert image with " << nrBands << " band(s) from RGB to YUV." << endl << flush;
      return false;
   }
}

//===================================================================================================

bool Image::YUVToRGB()
{
   TransformColorSpace tcsp;
   int nrBands = this->GetNumberOfBands();
   if (nrBands == 3)
   {
      int width = this->GetWidth();
      int height = this->GetHeight();

      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x++)
         {
            this->SetColor( x, y, tcsp.YUVtoRGB( this->GetColor( x, y) ) );
         }
      }
      return true;
   }
   else
   {
      cerr << "Impossible to convert image with " << nrBands << " band(s) from YUV to RGB." << endl << flush;
      return false;
   }
}

//===================================================================================================

bool Image::RGBToCMY()
{
   TransformColorSpace tcsp;
   int nrBands = this->GetNumberOfBands();
   if (nrBands == 3)
   {
      int width = this->GetWidth();
      int height = this->GetHeight();

      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x++)
         {
            this->SetColor( x, y, tcsp.RGBtoCMY( this->GetColor( x, y) ) );
         }
      }
      return true;
   }
   else
   {
      cerr << "Impossible to convert image with " << nrBands << " band(s) from RGB tot CMY." << endl << flush;
      return false;
   }
}

//===================================================================================================

bool Image::CMYToRGB()
{
   TransformColorSpace tcsp;
   int nrBands = this->GetNumberOfBands();
   if (nrBands == 3)
   {
      int width = this->GetWidth();
      int height = this->GetHeight();

      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x++)
         {
            this->SetColor( x, y, tcsp.CMYtoRGB( this->GetColor( x, y) ) );
         }
      }
      return true;
   }
   else
   {
      cerr << "Impossible to convert image with " << nrBands << " band(s) from CMY to RGB." << endl << flush;
      return false;
   }
}

//===================================================================================================

bool Image::ChromaticAdapt( ColorValue sourceWhite, ColorValue destinationWhite, ChromaticAdaptationType myType )
{
   int nrBands = this->GetNumberOfBands();
   if (nrBands == 3)
   {
      int width = this->GetWidth();
      int height = this->GetHeight();

      ChromaticAdaptation ca( sourceWhite, destinationWhite, myType );

      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x++)
         {
            this->SetColor( x, y, ca.AdaptsRGBColor( this->GetColor( x, y) ) );
         }
      }
      return true;
   }
   else
   {
      cerr << "Impossible to applu chromatic adaptation on an image with " << nrBands << " band(s)." << endl << flush;
      return false;
   }
}

//===================================================================================================

}
}
