
/***********************************************************************************
 *   Copyright (C) 2011 by Filip Rooms                                             *
 *                                                                                 *
 *  Terms and conditions for using this software in any form are provided in the   *
 *  file COPYING, which can be found in the root directory of this project.        *
 *                                                                                 *
 *   Contact data: filip.rooms@gmail.com                                           *
 *                 http://www.filiprooms.be/                                       *
 *                                                                                 *
 ***********************************************************************************/
#include <vector>
#include "../../image/datastructures/Image.h"

#ifndef STIRA_DECONVOLVE_SIMULATEDEGRADATION_H
#define STIRA_DECONVOLVE_SIMULATEDEGRADATION_H

namespace stira{
namespace deconvolve{

enum NoiseType { NOISETYPE_GAUSSIAN, NOISETYPE_POISSON, NOISETYPE_SALTANDPEPPER };

enum BlurType { BLURTYPE_GAUSSIAN, BLURTYPE_AIRY, BLURTYPE_BOX, BLURTYPE_DISC, BLURTYPE_LINE };


class SimulateDegradation
{
public:
   SimulateDegradation();
   ~SimulateDegradation();

   static image::ArrayGrid<double>* GeneratePSF( int width, int height, BlurType myBlurType, std::vector<double> vBlurParameters );
   static bool SimulateNoise( image::ArrayGrid<double>* pGridIn, NoiseType myNoiseType, double noiseLevel );


   static image::ArrayGrid<double>* Run( image::ArrayGrid<double>* pGridIn, NoiseType myNoiseType, double noiseLevel, BlurType myBlurType, std::vector<double> vBlurParameters );
   static image::Image* Run( image::Image* pImageIn, NoiseType myNoiseType, double noiseLevel, BlurType myBlurType, std::vector<double> vBlurParameters );
};

}
}

#endif //  STIRA_DECONVOLVE_SIMULATEDEGRADATION_H
