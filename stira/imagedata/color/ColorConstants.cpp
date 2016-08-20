
/***********************************************************************************
 *   Copyright (C) 2009 by Filip Rooms                                             *
 *                                                                                 *
 *  Terms and conditions for using this software in any form are provided in the   *
 *  file COPYING, which can be found in the root directory of this project.        *
 *                                                                                 *
 *   Contact data: filip.rooms@gmail.com                                           *
 *                 http://www.filiprooms.be/                                       *
 *                                                                                 *
 ***********************************************************************************/

#include "ColorConstants.h"

namespace stira {
namespace imagedata {

//const double Color::sKappa = 903.3;  // actual CIE standard
const double ColorConstants::sKappa = 24389.0 / 27.0;  // CIE intent; benefit of continuous L function
//const double Color::sEpsilon = 0.008856;  // actual CIE standard
const double ColorConstants::sEpsilon = 216.0 / 24389.0;  // CIE intent; benefit of continuous L function


// XYZ values for different reference illuminants; note that values are normalized to Y=1
// Source: http://www.brucelindbloom.com/index.html?Eqn_ChromAdapt.html
// Corresponds with p15 of http://www.babelcolor.com/download/A review of RGB color spaces.pdf 
//         case of CIE 1931
const ColorValue ColorConstants::sA_XYZ          = ColorValue( 1.09850, 1.00000, 0.35585, TYPE_XYZ );
const ColorValue ColorConstants::sB_XYZ          = ColorValue( 0.99072, 1.00000, 0.85223, TYPE_XYZ );
const ColorValue ColorConstants::sC_XYZ          = ColorValue( 0.98074, 1.00000, 1.18232, TYPE_XYZ );

const ColorValue ColorConstants::sD50_XYZ        = ColorValue( 0.96422, 1.00000, 0.82521, TYPE_XYZ );
const ColorValue ColorConstants::sD55_XYZ        = ColorValue( 0.95682, 1.00000, 0.92149, TYPE_XYZ );
const ColorValue ColorConstants::sD65_XYZ        = ColorValue( 0.95047, 1.00000, 1.08883, TYPE_XYZ );
const ColorValue ColorConstants::sD75_XYZ        = ColorValue( 0.94972, 1.00000, 1.22638, TYPE_XYZ );
const ColorValue ColorConstants::sD93_XYZ        = ColorValue( 0.97135, 1.00000, 1.43929, TYPE_XYZ );

const ColorValue ColorConstants::sE_XYZ          = ColorValue( 1.00000, 1.00000, 1.00000, TYPE_XYZ );
const ColorValue ColorConstants::sF2_XYZ         = ColorValue( 0.99186, 1.00000, 0.67393, TYPE_XYZ );
const ColorValue ColorConstants::sF7_XYZ         = ColorValue( 0.95041, 1.00000, 1.08747, TYPE_XYZ );
const ColorValue ColorConstants::sF11_XYZ        = ColorValue( 1.00962, 1.00000, 0.64350, TYPE_XYZ );
const ColorValue ColorConstants::sPrintWhite_XYZ = ColorValue( 0.79489, 0.82172, 0.72894, TYPE_XYZ );

const double ColorConstants::sMatchingFunctionCIEx[ 40 ] 
   = { 0.0014, 0.0042, 0.0143, 0.0435, 0.1344, 0.2839, 0.3483, 0.3362, 0.2908, 0.1954, 
       0.0956, 0.0320, 0.0049, 0.0093, 0.0633, 0.1655, 0.2904, 0.4334, 0.5945, 0.7621, 
       0.9163, 1.0263, 1.0622, 1.0026, 0.8544, 0.6424, 0.4479, 0.2835, 0.1649, 0.0874, 
       0.0468, 0.0227, 0.0114, 0.0058, 0.0029, 0.0014, 0.0007, 0.0003, 0.0002, 0.0001};
      
const double ColorConstants::sMatchingFunctionCIEy[ 40 ] 
   = { 0.000, 0.0001, 0.0004, 0.0012, 0.004, 0.0116, 0.0230, 0.0380, 0.0600, 0.091, 
       0.139, 0.2080, 0.3230, 0.5030, 0.710, 0.8620, 0.9540, 0.9950, 0.9950, 0.952, 
       0.870, 0.7570, 0.6310, 0.5030, 0.381, 0.2650, 0.1750, 0.1070, 0.0610, 0.032, 
       0.017, 0.0082, 0.0041, 0.0021, 0.001, 0.0005, 0.0003, 0.0001, 0.0001, 0.000};

const double ColorConstants::sMatchingFunctionCIEz[ 40 ] 
   = { 0.0065, 0.0201, 0.0679, 0.2074, 0.6456, 1.3856, 1.7471, 1.7721, 1.6692, 1.2876, 
       0.8130, 0.4652, 0.2720, 0.1582, 0.0782, 0.0422, 0.0203, 0.0087, 0.0039, 0.0021, 
       0.0017, 0.0011, 0.0008, 0.0003, 0.0002, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 
       0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000 };

// http://www.cie.co.at/publ/abst/datatables15_2004/sia.txt
const double ColorConstants::sAIlluminantSpectrum[ 40 ] 
   = {   9.7951,  12.0853,  14.7080,  17.6753,  20.9950,  24.6709,  28.7027,  33.0859,  37.8121,  42.8693,
        48.2423,  53.9132,  59.8611,  66.0635,  72.4959,  79.1326,  85.9470,  92.9120, 100.0000, 107.1840,
       114.4360, 121.7310, 129.0430, 136.3460, 143.6180, 150.8360, 157.9790, 165.0280, 171.9630, 178.7690,
       185.4290, 191.9310, 198.2610, 204.4090, 210.3650, 216.1200, 221.6670, 227.0000, 232.1150, 237.0080 };

const double ColorConstants::sD50IlluminantSpectrum[ 40 ] 
   = {  24.49, 29.87, 49.31, 56.51, 60.03,  57.82,  74.82,  87.25,  90.61,  91.37, 
        95.11, 91.96, 95.72, 96.61, 97.13, 102.10, 100.75, 102.32, 100.00,  97.74, 
        98.92, 93.50, 97.69, 99.27, 99.04,  95.72,  98.86,  95.67,  98.19, 103.00, 
        99.13, 87.38, 91.60, 92.89, 76.85,  86.51,  92.58,  78.23,  57.69,  82.92 };

// http://cvrl.ioo.ucl.ac.uk/database/data/cie/Illuminantd65.txt
// http://www.cie.co.at/publ/abst/datatables15_2004/sid65.txt
const double ColorConstants::sD65IlluminantSpectrum[ 40 ]
   = {  49.98,  54.65,  82.75,  91.49,  93.43,  86.68, 104.87, 117.01, 117.81, 114.86,
       115.92, 108.81, 109.35, 107.80, 104.79, 107.69, 104.41, 104.05, 100.00,  96.33,
        95.79,  88.69,  90.00,  89.60,  87.70,  83.29,  83.70,  80.03,  80.21,  82.28,
        78.28,  69.72,  71.61,  74.35,  61.60,  69.89,  75.09,  63.59,  46.41,  66.81 };

// is hard-coded for D50; useless to repeat the summation of constants in an inner loop
const double ColorConstants::sSpectralNormalizationConstantD50 = 1050.565971;

// is hard-coded for D65; useless to repeat the summation of constants in an inner loop
const double ColorConstants::sSpectralNormalizationConstantD65 = 1056.807083;

}
}
