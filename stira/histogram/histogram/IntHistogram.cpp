
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

#include "IntHistogram.h"
#include "../../common/common/MathUtils.h"
#include "../../imagedata/simpletools/GridStatistics.h"
#include "../../imagedata/simpletools/ImageStatistics.h"


//#define DEBUG

namespace stira {
namespace histogram {

using namespace std;
using namespace image;
using namespace common;

IntHistogram::IntHistogram( image::Image* pImage, bool useDataMinMax, double lowerFraction, double upperFraction, int binsize, image::ArrayGrid<bool>* pMaskGrid)
{
   mIscumulativeHistogram = false;
   mLowerFraction = lowerFraction;
   mUpperFraction = upperFraction;

   double mmin, mmax;
   mUsesROI = false;

   if (useDataMinMax)
   {
      ImageStatistics::GetMinMax( pImage, mmin, mmax );
   }
   else
   {
      mmin =   0.0;
      mmax = 255.0;
   }

   Initialize( binsize, pImage->GetNumberOfBands(), mmin, mmax );

   mInitializedFromGrid = true;

   BuildHistogram( pImage, pMaskGrid );
   #ifdef DEBUG
     Write( std::string("Histogram.txt") );
   #endif
}

//----------------------------------------------------------------

IntHistogram::IntHistogram( image::Image* pImage, bool useDataMinMax, common::RectangularROI<int> rroi, double lowerFraction, double upperFraction, int binsize )
{
   mIscumulativeHistogram = false;
   mLowerFraction = lowerFraction;
   mUpperFraction = upperFraction;

   double mmin, mmax;
   mUsesROI = true;
   mROI = rroi;

   if (useDataMinMax)
   {
      ImageStatistics::GetMinMax( pImage, mmin, mmax );
   }
   else
   {
      mmin =   0.0;
      mmax = 255.0;
   }

   Initialize( binsize, pImage->GetNumberOfBands(), mmin, mmax );

   mInitializedFromGrid = true;

   BuildHistogram( pImage, 0 );
   #ifdef DEBUG
     Write( std::string("Histogram.txt") );
   #endif
}

//----------------------------------------------------------------

IntHistogram::IntHistogram( image::ArrayGrid<double>* pGrid, bool useDataMinMax, double lowerFraction, double upperFraction, int binsize, image::ArrayGrid<bool>* pMaskGrid)
{
   mIscumulativeHistogram = false;
   mLowerFraction = lowerFraction;
   mUpperFraction = upperFraction;
   int numberOfBands = 1;
   int bandNr = 0;
   double mmin, mmax;
   mUsesROI = false;

   if (useDataMinMax)
   {
      GridStatistics<double>::GetMinMax( pGrid, mmin, mmax );
   }
   else
   {
      mmin =   0.0;
      mmax = 255.0;
   }

   mInitializedFromGrid = true;

   Initialize( binsize, numberOfBands, mmin, mmax );

   BuildHistogram( pGrid, bandNr, pMaskGrid  );
   #ifdef DEBUG
     Write( std::string("Histogram.txt") );
   #endif
}

//----------------------------------------------------------------

IntHistogram::IntHistogram( image::ArrayGrid<double>* pGrid, bool useDataMinMax, common::RectangularROI<int> rroi, double lowerFraction, double upperFraction, int binsize )
{
   mIscumulativeHistogram = false;
   mLowerFraction = lowerFraction;
   mUpperFraction = upperFraction;
   int numberOfBands = 1;
   int bandNr = 0;
   double mmin, mmax;

   mUsesROI = true;
   mROI = rroi;

   if (useDataMinMax)
   {
      GridStatistics<double>::GetMinMax( pGrid, mmin, mmax );
   }
   else
   {
      mmin =   0.0;
      mmax = 255.0;
   }

   mInitializedFromGrid = true;

   Initialize( binsize, numberOfBands, mmin, mmax );

   BuildHistogram( pGrid, bandNr, 0 );
   #ifdef DEBUG
     Write( std::string("Histogram.txt") );
   #endif
}

//----------------------------------------------------------------

IntHistogram::IntHistogram( double binSize, int nrOfBands, int minValue, int maxValue, double lowerFraction, double upperFraction )
{
   mIscumulativeHistogram = false;
   mInitializedFromGrid = false;
   mLowerFraction = lowerFraction;
   mUpperFraction = upperFraction;
   Initialize( binSize, nrOfBands, minValue, maxValue );
}

//----------------------------------------------------------------

IntHistogram::~IntHistogram()
{
   // parent cleans histogram data structure
}

//-----------------------------------------------------------------

IntHistogram* IntHistogram::Clone()
{
   return new IntHistogram(*this);
}

//---------------------------------------------------------------------------------------

bool IntHistogram::UpdateHistogram( IntHistogram* pIntHistogram, double alpha )
{
   for (int band = 0; band < mNrOfBands; band++)
   {
      for (int bin = 0; bin < mNrOfBins; bin++)
      {
         double newbinValue =           alpha  * (double)(pIntHistogram->GetBinValue( band, bin ))
                               + (1.0 - alpha) * this->GetBinValue( band, bin );

         SetBinValue( band, bin, (int)newbinValue );
      }
   }
   return 0;
}

//-----------------------------------------------------------------

double IntHistogram::GetLowerBound(int bandNr)
{
   if ( bandNr < (int)( mvLowerBound.size() ) )
   {
      return mvLowerBound[ bandNr ];
   }
   else
   {
      return 0.0;
   }
}

//-----------------------------------------------------------------

double IntHistogram::GetLowerFraction()
{
   return mLowerFraction;
}

//-----------------------------------------------------------------

void IntHistogram::SetLowerFraction(double myFraction)
{
   mLowerFraction = myFraction;
}

//-----------------------------------------------------------------

double IntHistogram::GetUpperBound(int bandNr)
{
   if (bandNr < (int)(mvUpperBound.size()))
   {
      return mvUpperBound[bandNr];
   }
   else
   {
      return 0.0;
   }
}

//-----------------------------------------------------------------

double IntHistogram::GetUpperFraction()
{
   return mUpperFraction;
}

//-----------------------------------------------------------------

void IntHistogram::SetUpperFraction(double myFraction)
{
   mUpperFraction = myFraction;
}

//-----------------------------------------------------------------

bool IntHistogram::DetermineBounds(int bandNr)
{
   int cumulNrPixels = 0;
   double cumulFraction;
   double lowerBound = 0;
   double upperBound = mNrOfBins - 1;
   for (int binNr = 0; binNr < mNrOfBins; binNr++)
   {
      double binValue = (((double)(binNr) * mBinSize) + mMin);

      cumulNrPixels += mpHistogram[bandNr][binNr];
      cumulFraction = (double)(cumulNrPixels) / (double)(mNrOfCounts);

      if (cumulFraction < mLowerFraction)
      {
         lowerBound = binValue;
      }

      if (cumulFraction < mUpperFraction)
      {
         upperBound = binValue;
      }
   }

   #ifdef DEBUG
     cout << "For band " << bandNr << " mMin = " << mMin << ", mMax = " << mMax << ", mBinSize = " << mBinSize
          << ", lowerBound = " << lowerBound << " and upperBound = " << upperBound << endl << flush;
   #endif

   mvLowerBound.push_back( lowerBound );
   mvUpperBound.push_back( upperBound );

   return true;
}

//-----------------------------------------------------------------

double IntHistogram::GetQuantile( int bandNr, double probability )
{
   double quantile = 0;
   int cumulNrPixels = 0;
   double cumulFraction;
   for (int binNr = 0; binNr < mNrOfBins; binNr++)
   {
      double binValue = (((double)(binNr) * mBinSize) + mMin);

      cumulNrPixels += mpHistogram[bandNr][binNr];
      cumulFraction = (double)(cumulNrPixels) / (double)(mNrOfCounts);

      if (cumulFraction < probability)
      {
         quantile = binValue;
      }
   }
   return quantile;
}

//-----------------------------------------------------------------

bool IntHistogram::Write( std::string fileName)
{
   ofstream ofp;
   ofp.open(const_cast<char*>(fileName.c_str()), ios::out | ios::binary);

   if (!ofp)
   {
      cout << "Can't open file: " << fileName << " for writing" << endl;
      return false;
   }

   if ( !(this->mIscumulativeHistogram) )
   {
      for (int bandNr = 0; bandNr < mNrOfBands; bandNr++)
      {
         int cumulNrPixels = 0;
         double cumulFraction;
         for (int binNr = 0; binNr < mNrOfBins; binNr++)
         {
            double binValue = ( (double)(binNr) * mBinSize );
            ofp << binValue << "\t" << mpHistogram[ bandNr ][ binNr ] << "\t";
            cumulNrPixels += mpHistogram[ bandNr ][ binNr ];
            cumulFraction = (double)(cumulNrPixels) / (double)(mNrOfCounts);

            ofp << cumulFraction << endl;
         }
      }
   }
   else
   {
      for (int bandNr = 0; bandNr < mNrOfBands; bandNr++)
      {
         for (int binNr = 0; binNr < mNrOfBins; binNr++)
         {
            double binValue = ( (double)(binNr) * mBinSize );
            ofp << binValue << "\t" << mpHistogram[ bandNr ][ binNr ] << "\t";
            double cumulFraction = (double)(mpHistogram[ bandNr ][ binNr ]) / (double)(mpHistogram[ bandNr ][ mNrOfBins-1 ]);

            ofp << cumulFraction << endl;
         }
      }
   }

   if (ofp.fail())
   {
      cout << "Couldn't write file " << fileName << endl;
      return false;
   }

   ofp.close();
   return true;
}

//-----------------------------------------------------------------

bool IntHistogram::BuildHistogram(image::Image* pImage, image::ArrayGrid<bool>* pMaskGrid)
{
   int nrBands = pImage->GetNumberOfBands();

   for (int bandNr = 0; bandNr < nrBands; bandNr++)
   {
      BuildHistogram( pImage->GetBands()[bandNr], bandNr, pMaskGrid);
   }
   return true;
}

//-----------------------------------------------------------------

bool IntHistogram::BuildHistogram(image::ArrayGrid<double>* pGrid, int bandNr, image::ArrayGrid<bool>* pMaskGrid)
{
   int width  = pGrid->GetWidth();
   int height = pGrid->GetHeight();

   int xMin, xMax, yMin, yMax;
   if ( mUsesROI )
   {
      xMin = MathUtils::ClipValue( mROI.GetTopLeftCorner().x, 0, pGrid->GetWidth() );
      yMin = MathUtils::ClipValue( mROI.GetTopLeftCorner().y, 0, pGrid->GetHeight() );
      xMax = MathUtils::ClipValue( mROI.GetBottomRightCorner().x, 0, pGrid->GetWidth() );
      yMax = MathUtils::ClipValue( mROI.GetBottomRightCorner().y, 0, pGrid->GetHeight() );
   }
   else
   {
      xMin = 0;
      xMax = pGrid->GetWidth();
      yMin = 0;
      yMax = pGrid->GetHeight();
   }

   if (pMaskGrid == 0)
   {
      mNrOfCounts = 0;
      for (int y = yMin; y < yMax; y++)
      {
         for (int x = xMin; x < xMax; x++)
         {
            int binNr = (int)((pGrid->GetValue(x, y) - mMin) / (double)(mBinSize));
            if ((binNr < mNrOfBins) && (binNr >= 0 ) )
            {
               mpHistogram[bandNr][binNr] ++;
               mNrOfCounts++;
            }
            else
            {
               cerr << "For pixel (" << x << ", " << y << ") with value " << pGrid->GetValue(x, y) << " Invalid bin nr " << binNr << " with nr of bins " << mNrOfBins << endl << flush;
               cerr << "\t mMax = " << mMax << " mMin = " << mMin << " mBinSize = " << mBinSize << endl << flush;
               //return false;
            }
         }
      }
   }
   else
   {
      mNrOfCounts = 0;
      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x++)
         {
            if (pMaskGrid->GetValue(x, y) == true)
            {
               int binNr = (int)((pGrid->GetValue(x, y) - mMin) / (double)(mBinSize));
               if ((binNr < mNrOfBins) && (binNr >= 0))
               {
                  mpHistogram[bandNr][binNr] ++;
                  mNrOfCounts++;
               }
               else
               {
                  cerr << "For pixel (" << x << ", " << y << ") with value " << pGrid->GetValue(x, y) << " Invalid bin nr " << binNr << " with current nr of bins " << mNrOfBins
                       << endl << flush;
                  cerr << "\t mMax = " << mMax << " mMin = " << mMin << " mBinSize = " << mBinSize << endl << flush;
                  //return false;
               }
            }
         }
      }
   }

   DetermineBounds( bandNr );
   return true;
}

//-----------------------------------------------------------------

void IntHistogram::ConvertInCumulativeHistogram()
{
   mIscumulativeHistogram = true;
   for (int bandNr = 0; bandNr < mNrOfBands; bandNr++)
   {
      // mpHistogramData[k][0] stays the same
      for (int binNr = 1; binNr < mNrOfBins; binNr++)
      {
         mpHistogram[ bandNr ][ binNr ] += mpHistogram[ bandNr ][ binNr - 1 ];
         if ( mpHistogram[ bandNr ][ binNr ] < 0 )
         {
            //#ifdef DEBUG
               cout << "Overflow (cumulative) in: band = " << bandNr << "  bin = " << binNr << endl << flush;
            //#endif
         }
      }
   }
}

//-----------------------------------------------------------------

}
}
