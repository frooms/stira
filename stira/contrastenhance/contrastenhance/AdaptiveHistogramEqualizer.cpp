#include "AdaptiveHistogramEqualizer.h"

#include "HistogramTools.h"
#include "../../common/common/MathUtils.h"
#include "../../filter/filter/GaussConvolve.h"
#include "../../histogram/histogram/IntHistogram.h"
#include "../../histogram/histogram/FloatHistogram.h"
#include "../../imagetools/tools/NumberGridTools.h"
#include "../../imagetools/interpolation/BilinearInterpolator.h"

using namespace stira::common;
using namespace stira::image;
using namespace stira::histogram;

namespace stira {
namespace contrastenhance {

AdaptiveHistogramEqualizer::AdaptiveHistogramEqualizer( image::Image* pSourceImage, int blockWidth, int blockHeight )
{
    mpSourceImage = pSourceImage;

    mWidth = pSourceImage->GetWidth();
    mHeight = pSourceImage->GetHeight();
    mDesiredMin = 0;
    mDesiredMax = 255;
    mBlockWidth = blockWidth;
    mBlockHeight = blockHeight;

    mNrBlocksX = mWidth / mBlockWidth;
    mNrBlocksY = mHeight / mBlockHeight;

    mpHistogramPerBlock = new ArrayGrid< histogram::FloatHistogram*>(mNrBlocksX, mNrBlocksY);
}

//----------------------------------------------------------------------------------------------

AdaptiveHistogramEqualizer::~AdaptiveHistogramEqualizer( )
{
   if ( mpHistogramPerBlock != 0 )
   {
      for (int yi = 0; yi < mNrBlocksY; yi++)
      {
         for (int xi = 0; xi < mNrBlocksX; xi++)
         {
            delete mpHistogramPerBlock->GetValue( xi, yi );
         }
      }
      delete mpHistogramPerBlock;
   }
}

//----------------------------------------------------------------------------------------------

image::Image* AdaptiveHistogramEqualizer::Run()
{
    image::Image* pImageOut = mpSourceImage->Clone();

    for (int yi = 0; yi < mNrBlocksY; yi++)
    {
       for (int xi = 0; xi < mNrBlocksX; xi++)
       {
            BuildNormHistogramSingleBlock( pImageOut, xi, yi );
       }
    }

    for (int bandNr = 0; bandNr < mpSourceImage->GetNumberOfBands(); bandNr++)
    {
        image::ArrayGrid<double>* pInGrid = pImageOut->GetBands()[bandNr];
        for (int y = 0; y < mHeight; y++)
        {
           for (int x = 0; x < mWidth; x++)
           {
                pInGrid->SetValue(x, y, InterpolateEqualizedValue( pInGrid, bandNr, x, y ) );
           }
        }
    }
    return pImageOut;
}

//----------------------------------------------------------------------------------------------

double AdaptiveHistogramEqualizer::GetEqualizedValueSingleBlock( image::ArrayGrid<double>* pInGrid, int bandNr, int x, int y, int xi, int yi )
{
    FloatHistogram* pNormCumulHistogram = mpHistogramPerBlock->GetValue( xi, yi );
    int binNr = pInGrid->GetValue(x, y);

    double myEqualizedValue = mDesiredMax * ( pNormCumulHistogram->GetBinValue( bandNr, binNr ) / ((double)(pNormCumulHistogram->GetNrOfBins())));

    if (myEqualizedValue > static_cast<double>(mDesiredMax)) {myEqualizedValue = static_cast<double>(mDesiredMax);}
    if (myEqualizedValue < static_cast<double>(mDesiredMin)) {myEqualizedValue = static_cast<double>(mDesiredMin);}

    return myEqualizedValue;
}

//----------------------------------------------------------------------------------------------

double AdaptiveHistogramEqualizer::InterpolateEqualizedValue( image::ArrayGrid<double>* pInGrid, int bandNr, int x, int y )
{
    double xi = (double)(x) / (double)(mBlockWidth);
    double yi = (double)(y) / (double)(mBlockHeight);

    int idx1 = MathUtils::ClipValue( (int)(floor(xi)), 0, mpHistogramPerBlock->GetWidth() - 1);
    int idx2 = MathUtils::ClipValue( (int)( ceil(xi)), 0, mpHistogramPerBlock->GetWidth() - 1);
    int idy1 = MathUtils::ClipValue( (int)(floor(yi)), 0, mpHistogramPerBlock->GetHeight() - 1);
    int idy2 = MathUtils::ClipValue( (int)( ceil(yi)), 0, mpHistogramPerBlock->GetHeight() - 1);

    double equalizeValue_11 = GetEqualizedValueSingleBlock( pInGrid, bandNr, x, y, idx1, idy1 );
    double equalizeValue_12 = GetEqualizedValueSingleBlock( pInGrid, bandNr, x, y, idx1, idy2 );
    double equalizeValue_21 = GetEqualizedValueSingleBlock( pInGrid, bandNr, x, y, idx2, idy1 );
    double equalizeValue_22 = GetEqualizedValueSingleBlock( pInGrid, bandNr, x, y, idx2, idy2 );

    int x1 = idx1 * mBlockWidth;
    int y1 = idy1 * mBlockHeight;
    int x2 = idx2 * mBlockWidth;
    int y2 = idy2 * mBlockHeight;
    double interpolatedValue = image::BilinearInterpolator::Run( x1, x2, y1, y2, equalizeValue_11, equalizeValue_12 , equalizeValue_21, equalizeValue_22, x, y );

    return interpolatedValue;
}

//----------------------------------------------------------------------------------------------

void AdaptiveHistogramEqualizer::BuildNormHistogramSingleBlock( image::Image* pImageIn, int xi, int yi )
{
    common::RectangularROI<int> rroi( xi * mBlockWidth, yi * mBlockHeight, (xi+1) * mBlockWidth, (yi+1) * mBlockHeight );

    bool useDataMinMax = false;
    IntHistogram* pStdHistogram       = new IntHistogram( pImageIn, useDataMinMax, rroi );
    IntHistogram* pCumulHistogram     = new IntHistogram( pImageIn, useDataMinMax, rroi );
    FloatHistogram *pNormCumulHistogram = new FloatHistogram( pStdHistogram->GetNrOfBins(), pImageIn->GetNumberOfBands() );

    pCumulHistogram->ConvertInCumulativeHistogram();

    pNormCumulHistogram->InitializeWithNormalizedCumulativeHistogram( pStdHistogram, pCumulHistogram);
    delete pStdHistogram;
    delete pCumulHistogram;

    mpHistogramPerBlock->SetValue( xi, yi, pNormCumulHistogram );
}

//----------------------------------------------------------------------------------------------

}
}
