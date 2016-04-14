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
    mBlockWidth = blockWidth;
    mBlockHeight = blockHeight;

    mNrBlocksX = mWidth / mBlockWidth;
    mNrBlocksY = mHeight / mBlockHeight;

    mpHistogramPerBlock = new ArrayGrid<histogram::FloatHistogram*>(mNrBlocksX, mNrBlocksY);
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
                HistogramEqualizeSingleBlock( pInGrid, xi, yi );
           }
        }
    }
    return pImageOut;
}

//----------------------------------------------------------------------------------------------

void AdaptiveHistogramEqualizer::HistogramEqualizeSingleBlock( image::ArrayGrid<double>* pInGrid, int xi, int yi )
{
   int xStart, yStart, xStop, yStop;
   int desiredMax, desiredMin;
   double dataMin, dataMax;

   xStart = xi * mBlockWidth;
   yStart = yi * mBlockHeight;
   xStop  = (xi+1) * mBlockWidth;
   yStop  = (yi+1) * mBlockHeight;

   common::RectangularROI<int> rroi( xStart, yStart, xStop, yStop );

   NumberGridTools<double>::GetMinMax( pInGrid, dataMin, dataMax );
   bool useDataMinMax = false;
   IntHistogram* pStdHistogram       = new IntHistogram( pInGrid, useDataMinMax, rroi );
   IntHistogram* pCumulHistogram     = new IntHistogram( pInGrid, useDataMinMax, rroi );
   FloatHistogram *pNormCumulHistogram = new FloatHistogram( pStdHistogram->GetNrOfBins() );

   pCumulHistogram->ConvertInCumulativeHistogram();

   pNormCumulHistogram->InitializeWithNormalizedCumulativeHistogram( pStdHistogram, pCumulHistogram);
   delete pStdHistogram;
   delete pCumulHistogram;

   desiredMax = (int)(dataMax);
   desiredMin = 0;

   for (int y = yStart; y < yStop; y++)
   {
      for (int x = xStart; x < xStop; x++)
      {
         int binNr = pInGrid->GetValue(x, y) - dataMin;

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
