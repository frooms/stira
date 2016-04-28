
/***********************************************************************************
 *   Copyright (C) 2008 by Filip Rooms                                             *
 *                                                                                 *
 *  Terms and conditions for using this software in any form are provided in the   *
 *  file COPYING, which can be found in the root directory of this project.        *
 *                                                                                 *
 *   Contact data: filip.rooms@gmail.com                                           *
 *                 http://www.filiprooms.be/                                       *
 *                                                                                 *
 ***********************************************************************************/

#ifndef STIRA_IMAGE_DATASTRUCTURES_IMAGE_H
#define STIRA_IMAGE_DATASTRUCTURES_IMAGE_H

#include <stdint.h>
#include <iostream>
#include <vector>
#include "../../common/common/Point.h"
#include "../../common/common/RectangularROI.h"
#include "../color/ColorValue.h"
#include "../color/TransformColorSpace.h"
#include "../color/ChromaticAdaptation.h"
#include "ArrayGrid.h"

namespace stira {
namespace image {

/** \brief A class to hold image data.
  * It consists of three things: the actual image data, the corresponding metadata and some operations that can be
  * executed on an image as a whole. The image data arev stored as a vector of ArrayGrids that represent the spectral
  * bands (like red, green, blue, ...) of an image. */
class Image
{
public:

   /** \brief Constructor. Creates an empty image with given width and height
     *
     * This image just has metadata, and no data structures allocated yet!! Bands must still be added.
     *
     * \param width width of image to be constructed
     * \param height height of image to be constructed
     * \param type underlying data type of image (not used yet)*/
   Image(int width, int height );

   /** \brief Constructor. Creates an image with one band with given width, height and number of bands
     * \param width width of image to be constructed
     * \param height height of image to be constructed
     * \param nrBands number of bands for image to be constructed
     */
   Image(int width, int height, int nrBands );

   /** \brief Constructor.
     * Creates an image with one band ArrayGrid as the only band
     * \param pDataGrid data grid to take as band in the image
     * \warning the image does take ownership of this band; don't delete it somewhere else!!*/
   Image( ArrayGrid<double>* pDataGrid );

   /** \brief Constructor.
     * Creates an image with one band created from a boolean grid with value 0 for false and 255 for true = 255
     * \param pBoolGrid data grid to take as band in the image
     * \warning the image does NOT take ownership of the boolean grid; you have to delete it yourself when you're finished with it!!*/
   Image( ArrayGrid<bool>* pBoolGrid );

   /** \brief Destructor.*/
   ~Image();

   /** \brief gets the name for this image */
   std::string GetImageName();

   /** \brief sets the name for this image to "imagename"
     * \param imagename name to set for this image*/
   void SetImageName( std::string imagename );

   /** \brief Makes a new image that is an exact, independant copy of the current image.
     * Also known as "deep copy"*/
   Image* Clone();

   /** \brief Copy constructor.
     * \param otherImage image to construct new image from*/
   Image( Image &otherImage );

   /** \brief Creates a new image cropped from ROI of this image
     * \param rroi rectangular ROI to create new subimage from
     * \return new subimage with same dimensions as rroi, which becomes the responsability of the caller to delete */
   Image* ExtractROIAsNewImage( common::RectangularROI<int> rroi );

   /** \brief overwrites part of an image with a subimage
     * \param pSubImage image to insert
     * \param xTop x coordinate in parent image where to insert top left corner of sub image
     * \param yTop y coordinate in parent image where to insert top left corner of sub image*/
   bool InsertSubImage( Image* pSubImage, int xTop, int yTop );

   /** \brief overwrites part of an image with a subimage
     * \param pSubGrid grid to insert
     * \param xTop x coordinate in parent image where to insert top left corner of sub image
     * \param yTop y coordinate in parent image where to insert top left corner of sub image*/
   bool InsertSubGrid( ArrayGrid<double>* pSubGrid, int xTop, int yTop );

   /** \brief adds a new band to the image.
     * \warning the image does take ownership of this band; don't delete it somewhere else!!
     * \param pBand band to be added to the image*/
   void AddBand( ArrayGrid<double>* pBand);

   /** \brief removes a band from the image.
     * \warning this band is also deleted; make sure it is no longer used somewhere else!!
     * \param pBand band to be removed from the image*/
   void RemoveBand( ArrayGrid<double>* pBand );

   /** \brief removes a band from the image.
     * \warning this band is also deleted; make sure it is no longer used somewhere else!!
     * \param i index of band to be removed from the image*/
   void RemoveBand(int i);

   /** \brief replaces the old band by the new band
     * The old band is deleted!!
     * \param pBandOld pointer to old band
     * \param pBandNew pointer to band that will replace the old band */
   void ReplaceBand( ArrayGrid<double>* pBandOld, ArrayGrid<double>* pBandNew );

   /** \brief gets the STL vector containing the image bands.*/
   std::vector< ArrayGrid<double>* >& GetBands();

   /** \brief gets the width of this images.*/
   int GetWidth();

   /** \brief gets the height of this image.*/
   int GetHeight();

   /** \brief gets the number of bands in this image.*/
   int GetNumberOfBands();

   /** \brief Gets the minimum and maximum present in the current image
     * \param outMin minimum value actually present in current image
     * \param outMax maximum value actually present in current image
     * \param minBandNr number of color band in which the minimum value was found
     * \param maxBandNr number of color band in which the maximum value was found */
   void GetMinMax(double& outMin, double& outMax, int& minBandNr, int& maxBandNr);

   /** \brief Gets the minimum and maximum present in the current image
     * \param outMin minimum value actually present in current image
     * \param outMax maximum value actually present in current image*/
   void GetMinMax(double& outMin, double& outMax );

   /** \brief Gets the largest absolute value present in this image
     * \return the largest absolute value in this image*/
   double GetAbsMax( );

   /** \brief prints some image properties on std out for diagnostics
     * \param ID identifier which image is being diagnosed*/
   void Diagnose( std::string ID=std::string("") );

   /** \brief Linearly rescales image intensities
     * Values are rescaled from old min and max value over all bands to new min and max value for all bands
     * \param mmin minimum value after rescaling
     * \param mmax maximum value after rescaling */
   void Rescale( double mmin=0.0, double mmax=255.0 );

   /** \brief replace intensities in this image by intensities of another image
     * Condition: image has same width, height and number of bands; if not, nothing happens... */
   void CopyImageValues(Image* pOtherImage);

   void ClipImageValues( double clippedMin, double clippedMax );

   /** \brief multiplies image point by point with another image
     * \warning overwrites current image; old pixel values are lost
     * \param pImg other image to multiply current image with*/
   void MultiplyWith(Image* pImg);

   /** \brief scales all image intensities with a certain factor
     * \warning overwrites current image; old pixel values are lost
     * \param factor factor to scale pixel intensities with*/
   void Scale( double factor );

   /** \brief adds Gaussian noise to current image
     * \param sigma sigma of the noise to add
     * \param isColored flag if the noise to apply is colored or not
     * \warning overwrites old image values
     * \warning assumes image values are in range between 0 and 255 */
   void AddGaussianNoise(double sigma, bool isColored=true);

   /** \brief applies Poisson noise to current image
     * Here, we assume that the image is scaled for visualization, and that the underlying measured intensities
     * can be recomputed by applying a factor
     * \param factor factor with which the "measured" image values were multiplied to get them in the current range
     * \param isColored flag if the noise to apply is colored or not
     * \warning overwrites old image values
     * \warning assumes image values are in range between 0 and 255*/
   void ApplyPoissonNoise( double factor, bool isColored=true );

   /** \brief applies salt&pepper noise to current image
     * \param fraction fraction of the pixels to be corrupted
     * \param isColored flag if the noise to apply is colored or not
     * \warning overwrites old image values
     * \warning assumes image values are in range between 0 and 255*/
   void ApplySaltAnPepperNoise(double fraction, bool isColored=true);

   /** \brief Gets color at given coordinates (x, y)
     * \warning: assumes 3 color bands; make sure first you have (at least) three color bands!!*/
   ColorValue GetColor(int x, int y);

   /** \brief Gets color at given coordinates (x, y)
     * \warning: assumes 3 color bands; make sure first you have (at least) three color bands!!*/
   ColorValue GetColor( common::Point<int> pt );

   /** \brief Gets color at given coordinates (x, y)
     * \warning: assumes 3 color bands; make sure first you have (at least) three color bands!!*/
   void SetColor(int x, int y, ColorValue cv);

   /** \brief Sets color at given point pt
     * \warning: assumes 3 color bands; make sure first you have (at least) three color bands!!*/
   void SetColor( common::Point<int> pt, ColorValue cv );

   /** \brief Converts image from HSV color representation to RGB
     * \warning: assumes 3 color bands; make sure first you have (at least) three color bands!!
     * \warning these color spaces are not device independant*/
   bool HSVToRGB();

   /** \brief Converts image from RGB color representation to HSV
     * \warning: assumes 3 color bands; make sure first you have (at least) three color bands!!
     * H is between 0 and 360 degrees; S and V are between 0 and 1
     * \warning these color spaces are not device independant*/
   bool RGBToHSV();

   /** \brief Converts image from HSI color representation to RGB
     * \warning: assumes 3 color bands; make sure first you have (at least) three color bands!!
     * \warning these color spaces are not device independant*/
   bool HSIToRGB();

   /** \brief Converts image from RGB color representation to HSI
     * \warning: assumes 3 color bands; make sure first you have (at least) three color bands!!
     * \warning these color spaces are not device independant*/
   bool RGBToHSI();

   /** \brief Converts image from HSL color representation to RGB
     * \warning: assumes 3 color bands; make sure first you have (at least) three color bands!!
     * \warning these color spaces are not device independant*/
   bool HSLToRGB();

   /** \brief Converts image from RGB color representation to HSL
     * \warning: assumes 3 color bands; make sure first you have (at least) three color bands!!
     * \warning these color spaces are not device independant*/
   bool RGBToHSL();

   /** \brief Converts image from sRGB color representation to XYZ
     * \param referenceIlluminant reference illuminant (or white point)
     * \warning: assumes 3 color bands; make sure first you have (at least) three color bands!!*/
   bool sRGBToXYZ( ColorValue referenceIlluminant = ColorConstants::sD65_XYZ );

   /** \brief Converts image from XYZ color representation to sRGB
     * \param referenceIlluminant reference illuminant (or white point)
     * \warning: assumes 3 color bands; make sure first you have (at least) three color bands!!*/
   bool XYZTosRGB( ColorValue referenceIlluminant = ColorConstants::sD65_XYZ );

   /** \brief Converts image from AdobeRGB color representation to XYZ
     * \param referenceIlluminant reference illuminant (or white point)
     * \warning: assumes 3 color bands; make sure first you have (at least) three color bands!!*/
   bool AdobeRGBToXYZ( ColorValue referenceIlluminant = ColorConstants::sD65_XYZ );

   /** \brief Converts image from XYZ color representation to AdobeRGB
     * \param referenceIlluminant reference illuminant (or white point)
     * \warning: assumes 3 color bands; make sure first you have (at least) three color bands!!*/
   bool XYZToAdobeRGB( ColorValue referenceIlluminant = ColorConstants::sD65_XYZ );

   /** \brief Converts image from sRGB color representation to Luv
     * \param referenceIlluminant reference illuminant (or white point)
     * \warning: assumes 3 color bands; make sure first you have (at least) three color bands!!*/
   bool sRGBToLuv( ColorValue referenceIlluminant = ColorConstants::sD65_XYZ );

   /** \brief Converts image from Luv color representation to sRGB
     * \param referenceIlluminant reference illuminant (or white point)
     * \warning: assumes 3 color bands; make sure first you have (at least) three color bands!!*/
   bool LuvTosRGB( ColorValue referenceIlluminant = ColorConstants::sD65_XYZ );

   /** \brief Converts image from sRGB color representation to (CIE)Lab
     * \param referenceIlluminant reference illuminant (or white point)
     * \warning: assumes 3 color bands; make sure first you have (at least) three color bands!!*/
   bool sRGBToLab( ColorValue referenceIlluminant = ColorConstants::sD65_XYZ );

   /** \brief Converts image from (CIE)Lab color representation to sRGB
     * \param referenceIlluminant reference illuminant (or white point)
     * \warning: assumes 3 color bands; make sure first you have (at least) three color bands!!*/
   bool LabTosRGB( ColorValue referenceIlluminant = ColorConstants::sD65_XYZ );

   /** \brief Converts image from RGB color representation to YUV
     * \warning: assumes 3 color bands; make sure first you have (at least) three color bands!!
     * \warning these color spaces are not device independant*/
   bool RGBToYUV();

   /** \brief Converts image from YUV color representation to RGB
     * \warning: assumes 3 color bands; make sure first you have (at least) three color bands!!
     * \warning these color spaces are not device independant*/
   bool YUVToRGB();

   /** \brief Converts image from RGB color representation to CMY
     * \warning: assumes 3 color bands; make sure first you have (at least) three color bands!!
     * \warning these color spaces are not device independant*/
   bool RGBToCMY();

   /** \brief Converts image from XYZ color representation to sRGB
     * \warning: assumes 3 color bands; make sure first you have (at least) three color bands!!
     * \warning these color spaces are not device independant*/
   bool CMYToRGB();

   bool ChromaticAdapt( ColorValue sourceWhite, ColorValue destinationWhite, ChromaticAdaptationType myType  );

private:
   int mImageWidth;   ///< width of the image.
   int mImageHeight;  ///< height of the image.
   std::string mImageName; ///< Image identifier
   std::vector< ArrayGrid<double>* > vpBands; ///< Vector containing the bands in this image.
};
}
}

#endif

