#ifndef IMAGESTATISTICS_H
#define IMAGESTATISTICS_H

#include "../datastructures/ArrayGrid.h"
#include "../datastructures/Image.h"

namespace stira {
namespace imagedata {

class ImageStatistics
{
public:
    ImageStatistics();

    static void Rescale( Image* pImage, double newMin, double newMax );

    static void GetMinMax( Image* pImage, double& mmin, double& mmax, int& minBandNr, int& maxBandNr);

    static void GetMinMax( Image* pImage, double& mmin, double& mmax );

    static double GetAbsMax( Image* pImage );
};

}
}

#endif // IMAGESTATISTICS_H
