
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

using namespace imagedata;

/** \brief class to simulate image degradation, by blurring and applying noise */
class SimulateDegradation
{
public:
   /** \brief constructor */
   SimulateDegradation();

   /** \brief destructor */
   ~SimulateDegradation();

   static ArrayGrid<double>* GeneratePSF( int width, int height, common::BlurType myBlurType, std::vector<double> vBlurParameters );
   static bool SimulateNoise( ArrayGrid<double>* pGridIn, common::NoiseType myNoiseType, double noiseLevel );


   static ArrayGrid<double>* Run( ArrayGrid<double>* pGridIn, common::NoiseType myNoiseType, double noiseLevel, common::BlurType myBlurType, std::vector<double> vBlurParameters );
   static Image*             Run( Image* pImageIn,            common::NoiseType myNoiseType, double noiseLevel, common::BlurType myBlurType, std::vector<double> vBlurParameters );
};

}
}

#endif //  STIRA_DECONVOLVE_SIMULATEDEGRADATION_H
