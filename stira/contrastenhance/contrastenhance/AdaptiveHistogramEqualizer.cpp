#include "AdaptiveHistogramEqualizer.h"

#include "HistogramTools.h"
#include "../../common/common/MathUtils.h"
#include "../../filter/filter/GaussConvolve.h"
#include "../../histogram/histogram/IntHistogram.h"
#include "../../histogram/histogram/FloatHistogram.h"
#include "../../image/tools/NumberGridTools.h"

using namespace stira::image;
using namespace stira::histogram;

namespace stira {
namespace contrastenhance {

AdaptiveHistogramEqualizer::AdaptiveHistogramEqualizer( image::Image* pSourceImage )
{
    mpSourceImage = pSourceImage;

    mWidth = pSourceImage->GetWidth();
    mHeight = pSourceImage->GetHeight();
    mBlockWidth = -1;
    mBlockHeight = -1;

    mNrBlocksX = -1;
    mNrBlocksY = -1;

    mpHistogramPerBlock = 0;
}

//----------------------------------------------------------------------------------------------

bool AdaptiveHistogramEqualizer::Initialize( int blockWidth, int blockHeight)
{
    mDesiredMin = 0;
    mDesiredMax = 255;
    mBlockWidth = blockWidth;
    mBlockHeight = blockHeight;

    mNrBlocksX = mWidth / mBlockWidth;
    mNrBlocksY = mHeight / mBlockHeight;

    mpHistogramPerBlock = new ArrayGrid<histogram::FloatHistogram*>(mNrBlocksX, mNrBlocksY);
    mpDataMinMaxPerBlock = new ArrayGrid< std::pair<double, double> >(mNrBlocksX, mNrBlocksY);
    return true;
}

//----------------------------------------------------------------------------------------------

image::Image* AdaptiveHistogramEqualizer::Run()
{
    image::Image* pImageOut = mpSourceImage->Clone();

    for (int i = 0; i < mpSourceImage->GetNumberOfBands(); i++)
    {
        image::ArrayGrid<double>* pInGrid = pImageOut->GetBands()[i];
        for (int yi = 0; yi < mNrBlocksY; yi++)
        {
           for (int xi = 0; xi < mNrBlocksX; xi++)
           {
                //HistogramEqualizeSingleBlock( pInGrid, xi, yi );
                BuildNormHistogramSingleBlock( pInGrid, xi, yi );
           }
        }

        for (int y = 0; y < mHeight; y++)
        {
           for (int x = 0; x < mWidth; x++)
           {
                pInGrid->SetValue(x, y, ComputeEqualizedValue( pInGrid, x, y ) );
           }
        }
    }
    return pImageOut;
}

//----------------------------------------------------------------------------------------------

double AdaptiveHistogramEqualizer::ComputeEqualizedValue( image::ArrayGrid<double>* pInGrid, int x, int y )
{
    int xi = x / mBlockWidth;
    int yi = y / mBlockHeight;
    FloatHistogram* pNormCumulHistogram = mpHistogramPerBlock->GetValue( xi, yi );
    int binNr = pInGrid->GetValue(x, y);

    double myEqualizedValue = mDesiredMax * ( pNormCumulHistogram->GetBinValue( 0, binNr ) / ((double)(pNormCumulHistogram->GetNrOfBins())));

    if (myEqualizedValue > static_cast<double>(mDesiredMax)) {myEqualizedValue = static_cast<double>(mDesiredMax);}
    if (myEqualizedValue < static_cast<double>(mDesiredMin)) {myEqualizedValue = static_cast<double>(mDesiredMin);}

    return myEqualizedValue;
}

//----------------------------------------------------------------------------------------------

void AdaptiveHistogramEqualizer::BuildNormHistogramSingleBlock( image::ArrayGrid<double>* pInGrid, int xi, int yi )
{
    int xStart = xi * mBlockWidth;
    int yStart = yi * mBlockHeight;
    int xStop  = (xi+1) * mBlockWidth;
    int yStop  = (yi+1) * mBlockHeight;

    common::RectangularROI<int> rroi( xStart, yStart, xStop, yStop );

    bool useDataMinMax = false;
    IntHistogram* pStdHistogram       = new IntHistogram( pInGrid, useDataMinMax, rroi );
    IntHistogram* pCumulHistogram     = new IntHistogram( pInGrid, useDataMinMax, rroi );
    FloatHistogram *pNormCumulHistogram = new FloatHistogram( pStdHistogram->GetNrOfBins() );

    pCumulHistogram->ConvertInCumulativeHistogram();

    pNormCumulHistogram->InitializeWithNormalizedCumulativeHistogram( pStdHistogram, pCumulHistogram);
    delete pStdHistogram;
    delete pCumulHistogram;

    mpHistogramPerBlock->SetValue( xi, yi, pNormCumulHistogram );
}

//----------------------------------------------------------------------------------------------

void AdaptiveHistogramEqualizer::HistogramEqualizeSingleBlock( image::ArrayGrid<double>* pInGrid, int xi, int yi )
{
   int xStart = xi * mBlockWidth;
   int yStart = yi * mBlockHeight;
   int xStop  = (xi+1) * mBlockWidth;
   int yStop  = (yi+1) * mBlockHeight;

   common::RectangularROI<int> rroi( xStart, yStart, xStop, yStop );

   bool useDataMinMax = false;
   IntHistogram* pStdHistogram       = new IntHistogram( pInGrid, useDataMinMax, rroi );
   IntHistogram* pCumulHistogram     = new IntHistogram( pInGrid, useDataMinMax, rroi );
   FloatHistogram *pNormCumulHistogram = new FloatHistogram( pStdHistogram->GetNrOfBins() );

   pCumulHistogram->ConvertInCumulativeHistogram();

   pNormCumulHistogram->InitializeWithNormalizedCumulativeHistogram( pStdHistogram, pCumulHistogram);
   delete pStdHistogram;
   delete pCumulHistogram;

   int desiredMax = 255;
   int desiredMin = 0;

   for (int y = yStart; y < yStop; y++)
   {
      for (int x = xStart; x < xStop; x++)
      {
         int binNr = pInGrid->GetValue(x, y);

         double myEqualizedValue = desiredMax * ( pNormCumulHistogram->GetBinValue( 0, binNr ) / ((double)(pNormCumulHistogram->GetNrOfBins())));

         if (myEqualizedValue > static_cast<double>(desiredMax)) {myEqualizedValue = static_cast<double>(desiredMax);}
         if (myEqualizedValue < static_cast<double>(desiredMin)) {myEqualizedValue = static_cast<double>(desiredMin);}

         pInGrid->SetValue(x, y, myEqualizedValue);
      }
   }

   delete pNormCumulHistogram;
}

//----------------------------------------------------------------------------------------------

}
}
