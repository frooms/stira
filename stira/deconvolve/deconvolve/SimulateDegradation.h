
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
#include "../../common/common/Definitions.h"
#include "../../imagedata/datastructures/Image.h"

#ifndef STIRA_DECONVOLVE_SIMULATEDEGRADATION_H
#define STIRA_DECONVOLVE_SIMULATEDEGRADATION_H

namespace stira{
namespace deconvolve{

/** \brief class to simulate image degradation, by blurring and applying noise */
class SimulateDegradation
{
public:
   /** \brief constructor */
   SimulateDegradation();

   /** \brief destructor */
   ~SimulateDegradation();

   static image::ArrayGrid<double>* GeneratePSF( int width, int height, common::BlurType myBlurType, std::vector<double> vBlurParameters );
   static bool SimulateNoise( image::ArrayGrid<double>* pGridIn, common::NoiseType myNoiseType, double noiseLevel );


   static image::ArrayGrid<double>* Run( image::ArrayGrid<double>* pGridIn, common::NoiseType myNoiseType, double noiseLevel, common::BlurType myBlurType, std::vector<double> vBlurParameters );
   static image::Image*             Run( image::Image* pImageIn,            common::NoiseType myNoiseType, double noiseLevel, common::BlurType myBlurType, std::vector<double> vBlurParameters );
};

}
}

#endif //  STIRA_DECONVOLVE_SIMULATEDEGRADATION_H
