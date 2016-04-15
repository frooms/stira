#include "AdaptiveHistogramEqualizer.h"

#include "HistogramTools.h"
#include "../../common/common/MathUtils.h"
#include "../../filter/filter/GaussConvolve.h"
#include "../../histogram/histogram/IntHistogram.h"
#include "../../histogram/histogram/FloatHistogram.h"
#include "../../image/tools/NumberGridTools.h"
#include "../../image/tools/BilinearInterpolator.h"

using namespace stira::common;
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

AdaptiveHistogramEqualizer::~AdaptiveHistogramEqualizer( )
{
   if ( mpHistogramPerBlock != 0 )
   {
       delete mpHistogramPerBlock;
   }
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

    mpHistogramPerBlock = new ArrayGrid< std::pair< common::Point<double>, histogram::FloatHistogram*> >(mNrBlocksX, mNrBlocksY);
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
                BuildNormHistogramSingleBlock( pInGrid, xi, yi );
           }
        }

        for (int y = 0; y < mHeight; y++)
        {
           for (int x = 0; x < mWidth; x++)
           {
                pInGrid->SetValue(x, y, InterpolateEqualizedValue( pInGrid, x, y ) );
           }
        }
    }
    return pImageOut;
}

//----------------------------------------------------------------------------------------------

double AdaptiveHistogramEqualizer::GetEqualizedValueSingleBlock( image::ArrayGrid<double>* pInGrid, int x, int y, int xi, int yi )
{
    FloatHistogram* pNormCumulHistogram = mpHistogramPerBlock->GetValue( xi, yi ).second;
    int binNr = pInGrid->GetValue(x, y);

    double myEqualizedValue = mDesiredMax * ( pNormCumulHistogram->GetBinValue( 0, binNr ) / ((double)(pNormCumulHistogram->GetNrOfBins())));

    if (myEqualizedValue > static_cast<double>(mDesiredMax)) {myEqualizedValue = static_cast<double>(mDesiredMax);}
    if (myEqualizedValue < static_cast<double>(mDesiredMin)) {myEqualizedValue = static_cast<double>(mDesiredMin);}

    return myEqualizedValue;
}

//----------------------------------------------------------------------------------------------

double AdaptiveHistogramEqualizer::InterpolateEqualizedValue( image::ArrayGrid<double>* pInGrid, int x, int y )
{
    double xi = (double)(x) / (double)(mBlockWidth);
    double yi = (double)(y) / (double)(mBlockHeight);

    int idx1 = MathUtils::ClipValue( (int)(floor(xi)), 0, mpHistogramPerBlock->GetWidth() - 1);
    int idx2 = MathUtils::ClipValue( (int)( ceil(xi)), 0, mpHistogramPerBlock->GetWidth() - 1);
    int idy1 = MathUtils::ClipValue( (int)(floor(yi)), 0, mpHistogramPerBlock->GetHeight() - 1);
    int idy2 = MathUtils::ClipValue( (int)( ceil(yi)), 0, mpHistogramPerBlock->GetHeight() - 1);

    double equalizeValue_11 = GetEqualizedValueSingleBlock( pInGrid, x, y, idx1, idy1 );
    double equalizeValue_12 = GetEqualizedValueSingleBlock( pInGrid, x, y, idx1, idy2 );
    double equalizeValue_21 = GetEqualizedValueSingleBlock( pInGrid, x, y, idx2, idy1 );
    double equalizeValue_22 = GetEqualizedValueSingleBlock( pInGrid, x, y, idx2, idy2 );

    int x1 = idx1 * mBlockWidth  + mBlockWidth  / 2;
    int y1 = idy1 * mBlockHeight + mBlockHeight / 2;
    int x2 = idx2 * mBlockWidth  + mBlockWidth  / 2;
    int y2 = idy2 * mBlockHeight + mBlockHeight / 2;
    double interpolatedValue = image::BilinearInterpolator::Run( x1, x2, y1, y2, equalizeValue_11, equalizeValue_12 , equalizeValue_21, equalizeValue_22, x, y );

    return interpolatedValue;
}

//----------------------------------------------------------------------------------------------

void AdaptiveHistogramEqualizer::BuildNormHistogramSingleBlock( image::ArrayGrid<double>* pInGrid, int xi, int yi )
{
    int xStart = xi     * mBlockWidth;
    int yStart = yi     * mBlockHeight;
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

    common::Point<double> blockCenter(xStart + mBlockWidth / 2, yStart + mBlockHeight / 2);

    mpHistogramPerBlock->SetValue( xi, yi, std::pair< common::Point<double>, histogram::FloatHistogram*>( blockCenter, pNormCumulHistogram ) );
}

//----------------------------------------------------------------------------------------------

}
}
