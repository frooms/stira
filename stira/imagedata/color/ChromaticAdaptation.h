
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

#ifndef STIRA_IMAGE_COLOR_CHROMATICADAPTATION_H
#define STIRA_IMAGE_COLOR_CHROMATICADAPTATION_H

#include "ColorValue.h"
#include "../../common/common/Definitions.h"

namespace stira {
namespace image {

/** \brief For generalization, unity matrix used for XYZ scaling */
const double sUnityMatrix[3][3] = 
{
  {  1.0000,  0.0000,  0.0000 },
  {  0.0000,  1.0000,  0.0000 },
  {  0.0000,  0.0000,  1.0000 }
};

/** \brief Bradford forward transformation matrix */
const double sBradfordForwardMatrix[3][3] = 
{
  {  0.8951, -0.7502,  0.0389 },
  {  0.2664,  1.7135, -0.0685 },
  { -0.1614,  0.0367,  1.0296 }
};

/** \brief Bradford inverse transformation matrix */
const double sBradfordInverseMatrix[3][3] = 
{
  {  0.986993,  0.432305, -0.008529 },
  { -0.147054,  0.518360,  0.040043 },
  {  0.159963,  0.049291,  0.968487 }
};

/** \brief Von Kries forward transformation matrix */
const double sVonKriesForwardMatrix[3][3] = 
{
  {  0.40024,  -0.22630,   0.00000 },
  {  0.70760,   1.16532,   0.00000 },
  { -0.08081,   0.04570,   0.91822 }
};

/** \brief Von Kries Bradford inverse transformation matrix */
const double sVonKriesInverseMatrix[3][3] = 
{
  {  1.859936,  0.361191,  0.000000 },
  { -1.129382,  0.638812,  0.000000 },
  {  0.219897, -0.000006,  1.089064 }
};

/** \brief Sharp forward transformation matrix */
const double sSharpForwardMatrix[3][3] = 
{
  {  1.2694,  -0.8364,  0.0297 },
  { -0.0988,   1.8006, -0.0315 },
  { -0.1706,   0.0357,  1.0018 }
};

/** \brief Sharp inverse transformation matrix */
const double sSharpInverseMatrix[3][3] = 
{
  {  0.8156,  0.0472,  0.1372 },
  {  0.3791,  0.5769,  0.0440 },
  { -0.0123,  0.0167,  0.9955 }
};

/** \brief CMC2000 forward transformation matrix */
const double sCMC200ForwardMatrix[3][3] = 
{
  {  0.7982, -0.5918,  0.0008 },
  {  0.3389,  1.5512,  0.0239 },
  { -0.1371,  0.0406,  0.9753 }
};

/** \brief CMC2000 inverse transformation matrix */
const double sCMC200InverseMatrix[3][3] = 
{
  {  1.0765,  0.4110, -0.0110 },
  { -0.2377,  0.5543, -0.0134 },
  {  0.1612,  0.0347,  1.0243 }
};

/** \brief identifier of type of chromatic adaptation*/
enum ChromaticAdaptationType { CHROMATICADAPTATION_XYZSCALING, ///< adaptation through XYZ scaling
                               CHROMATICADAPTATION_BRADFORD,   ///< adaptation according to Bradford
                               CHROMATICADAPTATION_VONKRIES,   ///< adaptation according to Von Kries
                               CHROMATICADAPTATION_SHARP,      ///< adaptation according to sharp
                               CHROMATICADAPTATION_CMC2000     ///< adaptation according to CMC2000
                             };

// COLOR ADAPTATION CLASS
/////////////////////////

/** \brief A class for color adaptation
  * Chromatic adaptation is the estimation of the representation of an object under a different 
  * light source than the one in which it was recorded. 
  *
  * References: 1) http://www.brucelindbloom.com/index.html?Eqn_ChromAdapt.html
  *             2) http://infoscience.epfl.ch/record/34049:
  *                  "Chromatic adaptation performance of different RGB sensors"
  *                   Süsstrunk et al, In: Proc. IS&T/SPIE Electronic Imaging 2001: Color Imaging,
  *                   vol. 4300, 2001, p. 172-183
  */
class ChromaticAdaptation
{
public:
   /** \brief constructor 
     * \param sourceReferenceWhite source reference white in XYZ coordinates in the nominal range [0.0, 1.0].
     * \param destinationReferenceWhite destination reference white in XYZ coordinates in the nominal range [0.0, 1.0].
     * \param myType type of chromatic adaptation */
   ChromaticAdaptation( const ColorValue sourceReferenceWhite, 
                        const ColorValue destinationReferenceWhite, 
                        ChromaticAdaptationType myType = CHROMATICADAPTATION_BRADFORD );
   
   /** \brief destructor */
   ~ChromaticAdaptation();
   
   /** \brief adapt color in XYZ coordinates to destination reference white 
     * \param inValue input color in XYZ in the nominal range [0.0, 1.0]. */
   ColorValue AdaptXYZColor( ColorValue inValue );
   
   /** \brief adapt color in sRGB coordinates to destination reference white 
     * \param inValue input color in sRGB in the range [0.0, 255.0]. */
   ColorValue AdaptsRGBColor( ColorValue inValue );
   
   /** \brief adapt color in L*a*b* coordinates to destination reference white
     * L*a*b* space is expressed with D55 as reference white
     * \param inValue input color in L*a*b*. */
   ColorValue AdaptLabColor( ColorValue inValue );

private:
   /** \brief apply MA matrix to color 
     * \param inValue color to transform*/
   ColorValue TransformColor( ColorValue inValue );
   
   double mppForwardMatrix[3][3];  ///< MA matrix on website of Lindbloom
   double mppInverseMatrix[3][3];  ///< MA^-1 matrix on website of Lindbloom
   ChromaticAdaptationType mType; ///< type of chromatic adaptation to apply
   void InitializeTransformMatrices( );  ///< Compute the adaptation matrix
   
   ColorValue mSourceReferenceWhite;  ///< source reference white in the nominal range [0.0, 1.0].
   ColorValue mDestinationReferenceWhite; ///< destination reference white in the nominal range [0.0, 1.0].
   
   ColorValue mTransformedSourceReferenceWhite; ///< MA transformed source reference white
   ColorValue mTransformedDestinationReferenceWhite; ///< MA transformed destination reference white
   ColorValue mRatiotransformedReferenceWhite; ///< matrix to transform input color to chromatic adapted color
   double mTransformMatrix[3][3];  ///< matrix to transform input color to chromatic adapted color
   double mppTmpMatrix[3][3];///< matrix to transform input color to chromatic adapted color
};

}
}
#endif
