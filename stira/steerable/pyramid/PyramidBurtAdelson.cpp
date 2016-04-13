#include "PyramidBurtAdelson.h"

#include "../../image/tools/ArrayGridTools.h"
#include "../../image/tools/ImageIO.h"
namespace stira {
namespace steerable {

double pH[ 5 ] = { 0.05, 0.25, 0.4, 0.25, 0.05 };

PyramidBurtAdelson::PyramidBurtAdelson()
{
    mpPyramid = 0;
    mSeparableFilter = new filter::SeparableFilter();
}

//-------------------------------------------------------------------------------------------------------------------


PyramidBurtAdelson::~PyramidBurtAdelson()
{
    if ( mpPyramid != 0 )
    {
        delete mpPyramid;
    }
    delete mSeparableFilter;
}

//-------------------------------------------------------------------------------------------------------------------


image::Pyramid<double>* PyramidBurtAdelson::GetPyramid()
{
    return mpPyramid;
}

//-------------------------------------------------------------------------------------------------------------------

image::ArrayGrid<double>* PyramidBurtAdelson::DecomposeSingleScale( image::ArrayGrid<double>* pGridIn, int scale )
{
    // smoothened input
    image::ArrayGrid<double>* pLowpassTmp = mSeparableFilter->RunRowColumn( pGridIn, pH, pH, 5, 5 );

    // smoothened and downsampled input
    image::ArrayGrid<double>* pNextLowpass = image::ArrayGridTools<double>::DownSampleGrid( pLowpassTmp );
    delete pLowpassTmp;

    // upsample again to subtract from original input
    int currentScaleWidth = pNextLowpass->GetWidth();
    int currentScaleHeight = pNextLowpass->GetHeight();

    image::ArrayGrid<double>* pUpscaleTmp = image::ArrayGridTools<double>::UpSampleGrid( pNextLowpass, currentScaleWidth * 2, currentScaleHeight * 2 );
    image::ArrayGrid<double>* pUpscale2 = mSeparableFilter->RunRowColumn( pUpscaleTmp, pH, pH, 5, 5 );
    delete pUpscaleTmp;

    pGridIn->SubtractGrid(pUpscale2);
    delete pUpscale2;

    mpPyramid->GetRecursiveScale( scale )->AddOrientedBand( pGridIn );

    return pNextLowpass;
}

//-------------------------------------------------------------------------------------------------------------------

bool PyramidBurtAdelson::Decompose( image::Image* pImage, int nrScales )
{
    mNrScales = nrScales;
    image::ArrayGrid<double>* pGridIn = pImage->GetBands()[0]->Clone();

    if (mpPyramid != 0) {delete mpPyramid;}
    mpPyramid = new image::Pyramid<double>( pGridIn, nrScales, 1, true, false );

    for (int currentScale = 0; currentScale < nrScales; currentScale++)
    {
        // DecomposeSingleScale subtracts next level gaussian smoothed image, uses this as bandpass in the pyramid and next lowpass level is returned
        image::ArrayGrid<double>* pTmp = DecomposeSingleScale( pGridIn, currentScale );
        pGridIn = pTmp;
    }

    // last returned lowpass is set as lowpass residual
    mpPyramid->SetLowpassResidual( pGridIn );
    return true;
}

//-------------------------------------------------------------------------------------------------------------------

image::ArrayGrid<double>* PyramidBurtAdelson::ReconstructSingleScale( image::ArrayGrid<double>* pGridIn, int scale )
{
    int thisScaleWidth  = pGridIn->GetWidth();
    int thisScaleHeight = pGridIn->GetHeight();
    image::ArrayGrid<double>* pUpscaleTmp = image::ArrayGridTools<double>::UpSampleGrid( pGridIn, thisScaleWidth * 2, thisScaleHeight * 2 );
    image::ArrayGrid<double>* pUpscale2 = mSeparableFilter->SeparableFilter::RunRowColumn( pUpscaleTmp, pH, pH, 5, 5 );
    delete pUpscaleTmp;

    pUpscale2->AddGrid( mpPyramid->GetRecursiveScale( scale )->GetOrientedBand( 0 ) );

    return pUpscale2;
}

//-------------------------------------------------------------------------------------------------------------------

image::ArrayGrid<double>* PyramidBurtAdelson::Reconstruct( )
{
    image::ArrayGrid<double>* pGridIn = mpPyramid->GetLowpassResidual();
    for (int currentScale = mNrScales-1; currentScale >= 0; currentScale--)
    {
        image::ArrayGrid<double>* pTmp = ReconstructSingleScale( pGridIn, currentScale );
        if ( currentScale < mNrScales-1)
        {
            delete pGridIn;
        }
        pGridIn = pTmp;
    }
    return pGridIn;
}

//-------------------------------------------------------------------------------------------------------------------

}
}
