
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

#ifndef STIRA_IMAGE_COLOR_TRANSFORMCOLORSPACE_H
#define STIRA_IMAGE_COLOR_TRANSFORMCOLORSPACE_H

#include <stdint.h>
#include <iostream>
#include <vector>
#include <cmath>
#include "ColorValue.h"
#include "ColorConstants.h"

namespace stira {
namespace imagedata {

/** \brief transformations between color spaces
  *
  * If used with standard settings (reference white point D65; RGB in range 0-255), the static member functions can be used without object. 
  * If however different settings are required, you MUST first create a Color object and set the appropriate variables.
  *
  * References: http://www.poynton.com/PDFs/coloureq.pdf
  *             HSI: Digital Image Processing Using MATLAB (DIPUM) by Gonzalez, Woods, and Eddins http://www.imageprocessingplace.com/
  *             HSV: http://nl.wikipedia.org/wiki/HSV_(kleurruimte)
  *             XYZ: http://www.brucelindbloom.com/
  *             Delta E and reference white points: http://www.digitalcolour.org/toolbox.htm
  *             Illuminants: Danny Pascale. "A Review of RGB color spaces". Babel Color. "http://www.babelcolor.com/download/A review of RGB color spaces.pdf".
  */
class TransformColorSpace
{
public:

   /** \brief constructor */
   TransformColorSpace();
   
   /** \brief destructor */
   ~TransformColorSpace();
   
   /** \brief sets new maximum value for color component
     * WARNING: use this class as an object instead of directly the static methods when using this method
     *          if not, the standard value 255 is going to be used no matter what*/
   void SetMaxColorValue( double maxColorValue );
   
   /** \brief sets new reference white level
     * WARNING: use this class as an object instead of directly the static methods when using this method
     *          if not, the standard value D65 is going to be used no matter what*/
   void SetReferenceWhite( ColorValue referenceWhite );
   
   /** \brief sets new reference white level
     * WARNING: use this class as an object instead of directly the static methods when using this method
     *          if not, the standard value D65 is going to be used no matter what*/
   ColorValue GetReferenceWhite( );
   
   /** \brief converts incoming sRGB color to XYZ 
     * conversion coefficients and formulae from http://www.brucelindbloom.com/
     * XYZ values are normalized in range 0 to 1
     * \param rgbValue incoming RGB color*/
   ColorValue sRGBtoXYZ( ColorValue rgbValue );
   
   /** \brief converts incoming XYZ color to sRGB
     * conversion coefficients and formulae from http://www.brucelindbloom.com/
     * XYZ values are normalized in range 0 to 1
     * \param xyzValue incoming XYZ color*/
   ColorValue XYZtosRGB( ColorValue xyzValue );
   
   /** \brief converts incoming AdobeRGB color to XYZ 
     * conversion coefficients and formulae from http://www.brucelindbloom.com/
     * XYZ values are normalized in range 0 to 1
     * \param rgbValue incoming RGB color*/
   ColorValue AdobeRGBtoXYZ( ColorValue rgbValue );
   
   /** \brief converts incoming XYZ color to AdobeRGB
     * conversion coefficients and formulae from http://www.brucelindbloom.com/
     * \param xyzValue incoming XYZ color in range 0 to 1*/
   ColorValue XYZtoAdobeRGB( ColorValue xyzValue );
   
   /** \brief converts incoming sRGB color to Luv
     * conversion coefficients and formulae from http://www.brucelindbloom.com/
     * WARNING: default, we use D65 as reference white; use TransformColorSpace as an object 
     *          instead of directly calling this static method to be able to set a different 
     *          reference white
     * \param rgbValue incoming RGB color */
   ColorValue sRGBtoLuv( ColorValue rgbValue );
   
   /** \brief converts incoming Luv color to sRGB
     * conversion coefficients and formulae from http://www.brucelindbloom.com/
     * WARNING: default, we use D65 as reference white; use TransformColorSpace as an object 
     *          instead of directly calling this static method to be able to set a different 
     *          reference white
     * \param luvValue incoming Luv color */
   ColorValue LuvtosRGB( ColorValue luvValue );
   
   /** \brief converts incoming XYZ color to Luv
     * conversion coefficients and formulae from http://www.brucelindbloom.com/
     * WARNING: default, we use D65 as reference white; use TransformColorSpace as an object 
     *          instead of directly calling this static method to be able to set a different 
     *          reference white
     * \param xyzValue incoming XYZ color in range 0 to 1 */
   ColorValue XYZtoLuv( ColorValue xyzValue );
   
   /** \brief converts incoming Luv color to XYZ
     * XYZ values are normalized in range 0 to 1
     * conversion coefficients and formulae from http://www.brucelindbloom.com/
     * WARNING: default, we use D65 as reference white; use TransformColorSpace as an object 
     *          instead of directly calling this static method to be able to set a different 
     *          reference white
     * \param luvValue incoming Luv color */
   ColorValue LuvtoXYZ( ColorValue luvValue );
   
   /** \brief converts incoming sRGB color to Lab
     * conversion coefficients and formulae from http://www.brucelindbloom.com/
     * WARNING: default, we use D65 as reference white; use TransformColorSpace as an object 
     *          instead of directly calling this static method to be able to set a different 
     *          reference white
     * \param rgbValue incoming RGB color */
   ColorValue sRGBtoLab( ColorValue rgbValue );
   
   /** \brief converts incoming Lab color to sRGB
     * conversion coefficients and formulae from http://www.brucelindbloom.com/
     * WARNING: default, we use D65 as reference white; use TransformColorSpace as an object 
     *          instead of directly calling this static method to be able to set a different 
     *          reference white
     * \param labValue incoming Lab color */
   ColorValue LabtosRGB( ColorValue luvValue );
   
   /** \brief converts incoming Adobe RGB color to Lab
     * conversion coefficients and formulae from http://www.brucelindbloom.com/
     * WARNING: default, we use D65 as reference white; use TransformColorSpace as an object 
     *          instead of directly calling this static method to be able to set a different 
     *          reference white
     * \param rgbValue incoming RGB color */
   ColorValue AdobeRGBtoLab( ColorValue rgbValue );
   
   /** \brief converts incoming Lab color to Adobe RGB
     * conversion coefficients and formulae from http://www.brucelindbloom.com/
     * WARNING: default, we use D65 as reference white; use TransformColorSpace as an object 
     *          instead of directly calling this static method to be able to set a different 
     *          reference white
     * \param labValue incoming Lab color */
   ColorValue LabtoAdobeRGB( ColorValue luvValue );
   
   /** \brief converts incoming XYZ color to Lab
     * conversion coefficients and formulae from http://www.brucelindbloom.com/
     * WARNING: default, we use D65 as reference white; use TransformColorSpace as an object 
     *          instead of directly calling this static method to be able to set a different 
     *          reference white
     * \param xyzValue incoming XYZ color in range 0 to 1 */
   ColorValue XYZtoLab( ColorValue xyzValue );
   
   /** \brief converts incoming Lab color to XYZ
     * XYZ values are normalized in range 0 to 1
     * conversion coefficients and formulae from http://www.brucelindbloom.com/
     * WARNING: default, we use D65 as reference white; use TransformColorSpace as an object 
     *          instead of directly calling this static method to be able to set a different 
     *          reference white
     * \param labValue incoming Lab color */
   ColorValue LabtoXYZ( ColorValue labValue );
   
   /** \brief converts incoming RGB color to CMY
     * Beware, since RGB and CMYK spaces are both device-dependent spaces, there is no simple or general 
     * conversion formula that converts between them. This indicative implementation is based on the 
     * simplest textbook formulae C=1-R; M=1-R and Y=1-B...
     * \param rgbValue incoming RGB color*/
   ColorValue RGBtoCMY( ColorValue rgbValue );
   
   /** \brief converts incoming CMY color to RGB
     * Beware, since RGB and CMYK spaces are both device-dependent spaces, there is no simple or general 
     * conversion formula that converts between them. This indicative implementation is based on the 
     * simplest textbook formulae...
     * \param cmyValue incoming CMY color*/
   ColorValue CMYtoRGB( ColorValue cmyValue );
   
   /** \brief converts incoming RGB color to YUV
     * In fact European R'G'B' to Y'U'V' for non-linear signals. The YUV standard 
     * (also called CCIR 601), known before as YCrCb (Y Cr Cb), is a colour representation
     * model dedicated to analogue video. 
     *   Equation (73) in http://www.poynton.com/PDFs/coloureq.pdf
     *   or formula on http://en.wikipedia.org/wiki/YUV
     * \param rgbValue incoming RGB color*/
   static ColorValue RGBtoYUV( ColorValue rgbValue );
   
   /** \brief converts incoming YUV color to RGB
     * In fact European Y'U'V' to R'G'B' for non-linear signals. The YUV standard 
     * (also called CCIR 601), known before as YCrCb (Y Cr Cb), is a colour representation
     * model dedicated to analogue video. 
     *   Equation (74) in http://www.poynton.com/PDFs/coloureq.pdf
     *   or formula on http://en.wikipedia.org/wiki/YUV
     * \param yuvValue incoming YUV color*/
   static ColorValue YUVtoRGB( ColorValue yuvValue );
   
   /** \brief converts incoming RGB color to HSV
     * HSV = Hue, Saturation and Value, according to Travis.
     * H is between 0 and 360 degrees; S and V are between 0 and 1
     * \param rgbValue incoming YUV color*/
   ColorValue RGBtoHSV( ColorValue rgbValue );
   
   /** \brief converts incoming HSV color to RGB
     * \param hsvValue incoming HSV color*/
   ColorValue HSVtoRGB( ColorValue hsvValue );
      
   /** \brief converts incoming RGB color to HSI
     * HSI = Hue, Saturation and Intensity, according to definition by Gonzalez and Woods.
     * \param rgbValue incoming RGB color*/
   ColorValue RGBtoHSI( ColorValue rgbValue );
   
   /** \brief converts incoming HSI color to RGB
     * \param hsiValue incoming HSI color*/
   ColorValue HSItoRGB( ColorValue hsiValue );

   /** \brief converts incoming RGB color to HSL
     * http://www.rapidtables.com/convert/color/rgb-to-hsl.htm
     * HSL = Hue, Saturation and Lightness  H=[0..360]  S=[0..1]  L=[0..1]
     * \param rgbValue incoming RGB color*/
   ColorValue RGBtoHSL( ColorValue rgbValue );

   /** \brief converts incoming HSL color to RGB
     * \param hslValue incoming HSL color*/
   ColorValue HSLtoRGB( ColorValue hslValue );

   /** \brief Computes for an RGB triplet the corresponding gray value
     * \param rgbValue the input RGB triplet*/
   static double RGBToGray( ColorValue rgbValue );
   
   /** \brief converts incoming Lab color to LCH
     * \param labValue incoming Lab color*/
   ColorValue LabtoLCH( ColorValue labValue );
   
   /** \brief converts incoming LCH color to  Lab 
     * \param labValue incoming LCH color*/
   ColorValue LCHtoLab( ColorValue lchValue );
   
   /** \brief converts an RGB color into its corresponding sepia color
     * Sepia tone refers to the coloring of grayscale images to simulate the faded brownish color of 
     * some early photographs: http://blogs.techrepublic.com.com/howdoi/?p=120
     * warning: do not use NORMAL_OUT when writing result to disk, because this will make the image 
     * appear gray instead of sepia since its scales all channels independently
     * \param rgbValue the input RGB triplet */
   static ColorValue RGBToSepia( ColorValue rgbValue );
   
   /** \brief converts an RGB color into its corresponding sepia color (alternative method)
     * www.wvutech.edu/mclark/CSCI121-2006/Lectures/ConditionalStatements.pdf 
     * \param rgbValue the input RGB triplet */
   static ColorValue RGBToSepia2( ColorValue rgbValue );

   /** \brief converts a gray value into its corresponding sepia color (same as above, but with grayscale input)
     * www.wvutech.edu/mclark/CSCI121-2006/Lectures/ConditionalStatements.pdf 
     * \param grayValue the input gray value */
   static ColorValue RGBToSepia2( double grayValue );
   
   /** \brief Converts from spectral data to XYZ, default with reference illuminant D50
     * Calculation of tristimulus values from spectral data at 10nm intervals
     * according to the "CIE Method"
     * See: http://www.digitalcolour.org/understanding/Tristimulus.htms
     *
     * The reason for the choice of D50 is that we also need the spectral reflectances of the illuminant.
     *
     * \param pSpectralValuesArray  spectral data (step size 10nm).
     * \param wavelengthMin lowest wavelength (min. 380nm).
     * \param wavelengthMax highest wavelength (max. 770nm).
     * \return  XYZ value in range 0 to 100 (using D50). */
   ColorValue SpectralValuesToXYZ( double *pSpectralValuesArray, int wavelengthMin, int wavelengthMax );
   
   /** \brief Converts from spectral data to Lab, default with reference illuminant D50
     * Calculation of tristimulus values from spectral data at 10nm intervals
     * according to the "CIE Method"
     * See: http://www.digitalcolour.org/understanding/Tristimulus.htms
     *
     * The reason for the choice of D50 is that we also need the spectral reflectances of the illuminant.
     *
     * \param pSpectralValuesArray  spectral data (step size 10nm).
     * \param wavelengthMin lowest wavelength (min. 380nm).
     * \param wavelengthMax highest wavelength (max. 770nm).
     * \return Lab value (using D50). */
   ColorValue SpectralValuesToLab( double *pSpectralValuesArray, int wavelengthMin, int wavelengthMax );

   /** \brief computes difference between two colours in Lab space according to 1976 formulation
     * http://en.wikipedia.org/wiki/Color_difference 
     * \param lab1 first colour
     * \param lab2 second colour */
   double DeltaE1976( ColorValue lab1, ColorValue lab2 );
   
   /** \brief computes difference between two colours in Lab space according to 1994 formulation
     * http://en.wikipedia.org/wiki/Color_difference 
     * \param lab1 first colour
     * \param lab2 second colour */
   double DeltaE1994( ColorValue lab1, ColorValue lab2 );
   
   /** \brief computes difference between two colours in Lab space according to 2000 formulation
     * http://www.brucelindbloom.com/index.html?Eqn_DeltaE_CIE2000.html
     * \param lab1 first colour
     * \param lab2 second colour */
   double DeltaE2000( ColorValue lab1, ColorValue lab2 );
   
   /** \brief computes difference between two colours expressed as arrays of spectral values to delta E 2000 formulation
     * http://www.brucelindbloom.com/index.html?Eqn_DeltaE_CIE2000.html
     * \param pSpectralValues1 spectral data for first colour (step size 10nm).
     * \param pSpectralValues2 spectral data for second colour (step size 10nm).
     * \param wavelengthMin lowest wavelength (min. 380nm).
     * \param wavelengthMax highest wavelength (max. 770nm). */
   double DeltaE2000( double *pSpectralValues1, double *pSpectralValues2, int wavelengthMin, int wavelengthMax );
   
private:

   /** \brief color correction (cfr gamma) specific for sRGB to undo gamma of screen
     * Uppercase noted RGB's are as displayed on screen, with gamma applied to them; lowercase 
     * noted rgb's are linearized
     * \param inLarge component for which to 'undo' gamma correction, i.e., to linearize for 
     *       computations*/
   double sRGBLargeToSmall(double inLarge);

   /** \brief color correction (cfr gamma) specific for sRGB to redo gamma of screen
     * Uppercase noted RGB's are as displayed on screen, with gamma applied to them; lowercase noted rgb's are linearized
     * \param inSmall component for which to re-apply gamma correction ,i.e., to display again on screen*/
   double sRGBSmallToLarge(double inSmall );
   
   ColorValue mReferenceWhite;  ///< currently used reference white point (default D65)
   static const double sDifferenceThreshold;  ///< minimum difference between two color components
   double mMaxColorValue;  ///< maximum value of color component

};

}
}

#endif
