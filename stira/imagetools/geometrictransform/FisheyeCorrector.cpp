#include "FisheyeCorrector.h"
#include "../../common/common/MathUtils.h"

namespace stira {
namespace imagetools {

using namespace common;
using namespace std;


FisheyeCorrector::FisheyeCorrector()
{
    //mpInterpolator = new BilinearInterpolator();
    mpInterpolator = new BicubicInterpolator();
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
    Image* pImageOut = new Image( pImageIn->GetWidth(),  pImageIn->GetHeight(), 3);
    for (int bandID = 0; bandID < 3; bandID++)
    {
        ApplyCorrect( pImageIn->GetBands()[bandID], pImageOut->GetBands()[bandID], strength, zoom );
    }
    return pImageOut;
}

void FisheyeCorrector::ApplyCorrect( ArrayGrid<double>* pGridIn, ArrayGrid<double>* pGridOut, double strength, double zoom )
{
    double width = (double)(pGridIn->GetWidth());
    double height = (double)(pGridIn->GetHeight());
    double halfWidth = width / 2.0;
    double halfHeight = height / 2.0;

    if ( strength == 0.0) { strength = 0.00001;}

    double correctionRadius = sqrt( width * width + height * height ) / strength;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            Point<double> sourcePoint = TransformPixel( x, y, halfWidth, halfHeight, correctionRadius, zoom );
            if ( ( sourcePoint.x > 1 ) && ( sourcePoint.y > 1 ) && ( sourcePoint.x < width-1 ) && ( sourcePoint.y < height-1 ) )
            {
                double interpolatedValue = MathUtils::ClipValue( mpInterpolator->Run( pGridIn, sourcePoint.x, sourcePoint.y ), 1.0, 254.0 );
                pGridOut->SetValue(x, y, interpolatedValue );
            }
        }
    }
}

}
}
