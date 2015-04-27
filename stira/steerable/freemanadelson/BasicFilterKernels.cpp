
/***********************************************************************************
 *   Copyright (C) 2008, 2010 by Filip Rooms                                       *
 *                                                                                 *
 *  Terms and conditions for using this software in any form are provided in the   *
 *  file COPYING, which can be found in the root directory of this project.        *
 *                                                                                 *
 *   Contact data: filip.rooms@gmail.com                                           *
 *                 http://www.filiprooms.be/                                       *
 *   Original taps also added to this implementation in aug 2010                   *
 *                                                                                 *
 ***********************************************************************************/

#include "BasicFilterKernels.h"

//#define USE_ORIGINAL_TAPS

#ifdef USE_ORIGINAL_TAPS
  // same taps as in Freeman and Adelson's paper
  #define FILTERLENGTH 9
#else
  // Modified kernels, resampled myself from same functions as Freeman and Adelson's paper
  #define FILTERLENGTH 7
#endif

//----------------------------------------------------------------------------------------------------------------

namespace stira {
namespace steerable {

#ifdef USE_ORIGINAL_TAPS
  // same taps as Freeman and Adelson's paper, length 9
  double BasicFilterKernels::spFilterG2F1[FILTERLENGTH] = { 0.0094,  0.1148,  0.3964, -0.0601, -0.9213, -0.0601,  0.3964,  0.1148,  0.0094 };
  double BasicFilterKernels::spFilterG2F2[FILTERLENGTH] = { 0.0008,  0.0176,  0.1660,  0.6383,  1.0000,  0.6383,  0.1660,  0.0176,  0.0008 };
  double BasicFilterKernels::spFilterG2F3[FILTERLENGTH] = {-0.0028, -0.0480, -0.3020, -0.5806,  0.0000,  0.5806,  0.3020,  0.0480,  0.0028 };
  double BasicFilterKernels::spFilterH2F1[FILTERLENGTH] = {-0.0098, -0.0618,  0.0998,  0.7551,  0.0000, -0.7551, -0.0998,  0.0618,  0.0098 };
  double BasicFilterKernels::spFilterH2F2[FILTERLENGTH] = { 0.0008,  0.0176,  0.1660,  0.6383,  1.0000,  0.6383,  0.1660,  0.0176,  0.0008 };
  double BasicFilterKernels::spFilterH2F3[FILTERLENGTH] = {-0.0020, -0.0354, -0.2225, -0.4277,  0.0000,  0.4277,  0.2225,  0.0354,  0.0002 };
  double BasicFilterKernels::spFilterH2F4[FILTERLENGTH] = { 0.0048,  0.0566,  0.1695, -0.1889, -0.7349, -0.1889,  0.1695,  0.0566,  0.0048 };
#else
  // Modified kernels, resampled from same functions as Freeman and Adelson's paper, length 7
  double BasicFilterKernels::spFilterG2F1[FILTERLENGTH] = { 0.001933,  0.118119,  0.338927, -0.921300,  0.338927, 0.118119, 0.001933};
  double BasicFilterKernels::spFilterG2F2[FILTERLENGTH] = { 0.000123,  0.018316,  0.367879,  1.000000,  0.367879, 0.018316, 0.000123};
  double BasicFilterKernels::spFilterG2F3[FILTERLENGTH] = {-0.000503, -0.049745, -0.499580,  0.000000,  0.499580, 0.049745, 0.000503};
  double BasicFilterKernels::spFilterH2F1[FILTERLENGTH] = {-0.002443, -0.062551,  0.451172,  0.000000, -0.451172, 0.062551, 0.002443};
  double BasicFilterKernels::spFilterH2F2[FILTERLENGTH] = { 0.000123,  0.018316,  0.367879,  1.000000,  0.367879, 0.018316, 0.000123};
  double BasicFilterKernels::spFilterH2F3[FILTERLENGTH] = {-0.000370, -0.036631, -0.367879,  0.000000,  0.367879, 0.036631, 0.000370};
  double BasicFilterKernels::spFilterH2F4[FILTERLENGTH] = { 0.001018,  0.059498,  0.091418, -0.751500,  0.091418, 0.059498, 0.001018};
#endif

//---------------------------------------------------------------------------------------------------------------

BasicFilterKernels::BasicFilterKernels()
{
}

//----------------------------------------------------------------------------------------------------------------

BasicFilterKernels::~BasicFilterKernels()
{
}

//---------------------------------------------------------------------------------------------------------------

int BasicFilterKernels::GetBasicfilterLength()
{
   return FILTERLENGTH;
}

//---------------------------------------------------------------------------------------------------------------

double* BasicFilterKernels::GetFilterG2F1()
{
   return spFilterG2F1;
}

//---------------------------------------------------------------------------------------------------------------

double* BasicFilterKernels::GetFilterG2F2()
{
   return spFilterG2F2;
}

//---------------------------------------------------------------------------------------------------------------

double* BasicFilterKernels::GetFilterG2F3()
{
   return spFilterG2F3;
}

//---------------------------------------------------------------------------------------------------------------

double* BasicFilterKernels::GetFilterH2F1()
{
   return spFilterH2F1;
}

//---------------------------------------------------------------------------------------------------------------

double* BasicFilterKernels::GetFilterH2F2()
{
   return spFilterH2F2;
}

//---------------------------------------------------------------------------------------------------------------

double* BasicFilterKernels::GetFilterH2F3()
{
   return spFilterH2F3;
}

//---------------------------------------------------------------------------------------------------------------

double* BasicFilterKernels::GetFilterH2F4()
{
   return spFilterH2F4;
}

//---------------------------------------------------------------------------------------------------------------

}
}
