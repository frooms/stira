#include "FisheyeCorrector.h"

namespace stira {
namespace image {

using namespace common;
using namespace std;

//===================================================================================================

FisheyeCorrector::FisheyeCorrector()
{
    mpInterpolator = new BilinearInterpolator();
}

FisheyeCorrector::~FisheyeCorrector( )
{
    delete mpInterpolator;
}

Point<double> FisheyeCorrector::TransformPixel(int x, int y, double halfWidth, double halfHeight, double correctionRadius, double zoom )
{
    double theta = 0.0;
    int newX = x - halfWidth;
    int newY = y - halfHeight;

    double distance = sqrt( newX * newX + newY * newY );
    double r = distance / correctionRadius;

    if ( r == 0)
    {
        theta = 1.0;
    }
    else
    {
        theta = atan(r) / r;
    }

    return Point<double>( halfWidth + theta * newX * zoom, halfHeight + theta * newY * zoom );
}

Image* FisheyeCorrector::ApplyCorrect( Image* pImageIn, double strength, double zoom )
{
    double width = (double)(pImageIn->GetWidth());
    double height = (double)(pImageIn->GetHeight());
    double halfWidth = width / 2.0;
    double halfHeight = height / 2.0;

    if (strength == 0.0) { strength = 0.00001;}

    Image* pImageOut = new Image(width, height, 3);

    double correctionRadius = sqrt( width * width + height * height ) / strength;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            Point<double> sourcePoint = TransformPixel( x, y, halfWidth, halfHeight, correctionRadius, zoom );

            if ( ( sourcePoint.x > 0 ) && ( sourcePoint.y > 0 ) && ( sourcePoint.x < width ) && ( sourcePoint.y < height ) )
            {
                for (int bandID = 0; bandID < 3; bandID++)
                {
                    ArrayGrid< double >* pGridIn = pImageIn->GetBands()[bandID];
                    pImageOut->GetBands()[bandID]->SetValue( x, y, mpInterpolator->Run( pGridIn, sourcePoint.x, sourcePoint.y ) );
                }
            }
        }
    }
    return pImageOut;
}

ArrayGrid<double>* FisheyeCorrector::ApplyCorrect( ArrayGrid<double>* pGridIn, double strength, double zoom )
{
    double width = (double)(pGridIn->GetWidth());
    double height = (double)(pGridIn->GetHeight());
    double halfWidth = width / 2.0;
    double halfHeight = height / 2.0;

    ArrayGrid<double>* pGridOut = new ArrayGrid<double>(width, height);

    if ( strength == 0.0) { strength = 0.00001;}

    double correctionRadius = sqrt( width * width + height * height ) / strength;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            Point<double> sourcePoint = TransformPixel( x, y, halfWidth, halfHeight, correctionRadius, zoom );
            if ( ( sourcePoint.x > 0 ) && ( sourcePoint.y > 0 ) && ( sourcePoint.x < width ) && ( sourcePoint.y < height ) )
            {
                pGridOut->SetValue(x, y, mpInterpolator->Run( pGridIn, sourcePoint.x, sourcePoint.y ));
            }
        }
    }
    return pGridOut;
}

}
}
