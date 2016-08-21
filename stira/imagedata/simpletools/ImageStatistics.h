
/***********************************************************************************
 *   Copyright (C) 2016 by Filip Rooms                                             *
 *                                                                                 *
 *  Terms and conditions for using this software in any form are provided in the   *
 *  file COPYING, which can be found in the root directory of this project.        *
 *                                                                                 *
 *   Contact data: filip.rooms@gmail.com                                           *
 *                 http://www.filiprooms.be/                                       *
 *                                                                                 *
 ***********************************************************************************/

#ifndef STIRA_IMAGEDATA_SIMPLETOOLS_IMAGESTATISTICS_H
#define STIRA_IMAGEDATA_SIMPLETOOLS_IMAGESTATISTICS_H

#include "../datastructures/ArrayGrid.h"
#include "../datastructures/Image.h"

namespace stira {
namespace imagedata {

class ImageStatistics
{
public:
    /** \brief constructor */
    ImageStatistics();

    /** \brief rescales image intensities
      * \param pImage input image
      * \param newMin new minimum intensity in image after rescaling
      * \param newMax new maximum intensity in image after rescaling */
    static void Rescale( Image* pImage, double newMin, double newMax );

    /** \brief gets minimum and maximum intensities of an image
      * \param pImage input image
      * \param mmin minimum intensity in image
      * \param mmax maximum intensity in image
      * \param minBandNr number of band in which minimum was found
      * \param maxBandNr number of band in which maximum was found */
    static void GetMinMax( Image* pImage, double& mmin, double& mmax, int& minBandNr, int& maxBandNr);

    /** \brief gets minimum and maximum intensities of an image
      * \param pImage input image
      * \param mmin minimum intensity in image
      * \param mmax maximum intensity in image */
    static void GetMinMax( Image* pImage, double& mmin, double& mmax );

    /** \brief gets maximum intensity in absolute value of an image
      * \param pImage input image */
    static double GetAbsMax( Image* pImage );
};

}
}

#endif // IMAGESTATISTICS_H
