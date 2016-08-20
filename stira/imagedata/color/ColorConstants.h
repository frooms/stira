
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

#ifndef STIRA_IMAGE_COLOR_COLORCONSTANTS_H
#define STIRA_IMAGE_COLOR_COLORCONSTANTS_H

#include <iostream>
#include <vector>
#include "ColorValue.h"

namespace stira {
namespace imagedata {

/** \brief usefull constants related to color and color spaces  *
  * References: reference white points: http://www.digitalcolour.org/toolbox.htm
  *             Illuminants: Danny Pascale. "A Review of RGB color spaces". (Babel Color). 
  *                                          http://www.babelcolor.com/download/A review of RGB color spaces.pdf 
  */
class ColorConstants
{
public:
   
   /** \brief XYZ values of the "A" reference illuminant
     * Tungsten or incandescent, 2856 K */
   static const ColorValue sA_XYZ;
   
   /** \brief XYZ values of the "B" reference illuminant 
     * Direct sunlight at noon, 4874 K (obsolete)*/
   static const ColorValue sB_XYZ;
   
   /** \brief XYZ values of the "C" reference illuminant 
     * North sky daylight, 6774K */
   static const ColorValue sC_XYZ;
   
   /** \brief XYZ values of D50 reference illuminant  
     * Daylight, used for color rendering, 5000K */
   static const ColorValue sD50_XYZ;
   
   /** \brief XYZ values of D55 reference illuminant 
     * Daylight, used for photography, 5500K */
   static const ColorValue sD55_XYZ;
   
   /** \brief XYZ values of D65 reference illuminant 
     * New version of orth sky daylight, 6504K */
   static const ColorValue sD65_XYZ;
   
   /** \brief XYZ values of D75 reference illuminant 
     * Daylight, 7500K */
   static const ColorValue sD75_XYZ;
   
   /** \brief XYZ values of D93 reference illuminant 
     * High efficiency blue phosphor monitors, 9300K */
   static const ColorValue sD93_XYZ;
   
   /** \brief XYZ values of the "E" reference illuminant
     * Uniform energy, 5400K */
   static const ColorValue sE_XYZ;
   
   /** \brief XYZ values of the "F2" reference illuminant 
     * Cool white fluorescent, 4200K */
   static const ColorValue sF2_XYZ;
   
   /** \brief XYZ values of the "F7" reference illuminant 
     * Broad-band daylight fluorescent, 6500K*/
   static const ColorValue sF7_XYZ;
   
   /** \brief XYZ values of the "F11" reference illuminant 
     * Narrow-band white fluorescent, 4000K*/
   static const ColorValue sF11_XYZ;
   
   /** \brief XYZ values of the reference illuminant used in printing
     * Narrow-band white fluorescent, 5200K*/
   static const ColorValue sPrintWhite_XYZ;ColorValue mReferenceWhite;  ///< currently used reference white point (default D65)
   static const double sDifferenceThreshold;  ///< minimum difference between two color components
   double mMaxColorValue;  ///< maximum value of color component
   static const double sKappa;   ///< cte in conversion XYZ to Lab or Luv (see Lindbloom)
   static const double sEpsilon;   ///< cte in conversion XYZ to Lab or Luv (see Lindbloom)
   
   static const double sMatchingFunctionCIEx[];  ///< CIE standard observer function for x
   static const double sMatchingFunctionCIEy[];  ///< CIE standard observer function for y
   static const double sMatchingFunctionCIEz[];  ///< CIE standard observer function for z

   static const double sD50IlluminantSpectrum[];  ///< spectral power distribution of D50 between 380nm and 770 nm with steps 10 nm
   static const double sD65IlluminantSpectrum[];  ///< spectral power distribution of D65 between 380nm and 770 nm with steps 10 nm
   static const double sAIlluminantSpectrum[];    ///< spectral power distribution of A between 380nm and 770 nm with steps 10 nm
   static const double sSpectralNormalizationConstantD50;  ///< is for D50 in fact sum_i ( sMatchingFunctionCIEy[i] x sD50Illuminant[i] )
   static const double sSpectralNormalizationConstantD65;  ///< is for D65 in fact sum_i ( sMatchingFunctionCIEy[i] x sD50Illuminant[i] )
   static const int sMinimumWavelength  = 380;  ///< minimum wavelength for which we have reference values
   static const int sMaximumWavelength  = 770;  ///< maximum wavelength for which we have reference values
   static const int sWavelengthStepSize =  10;  ///< wavelength step size
   
};

}
}

#endif
