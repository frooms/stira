
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

#ifndef STIRA_IMAGE_TOOLS_IMAGETOOLS_H
#define STIRA_IMAGE_TOOLS_IMAGETOOLS_H

#include "../../common/common/StiraMacros.h"
#include "NumberGridTools.h"
#include "../../imagedata/datastructures/Image.h"

namespace stira {
namespace imagetools {

struct myMinMax{ double min;
                 double max;
               };

/** \brief Class with operations on image objects;
  * Each of these operations creates a new image object that the caller becomes responsable for
  *
  * The methods in this class are grouped thematically in the following categories
  *  <UL><LI> CONSTRUCTOR / DESTRUCTOR
  *      <LI> PADD / CROP IMAGE
  *      <LI> COMPARE IMAGES
  *      <LI> MIX TWO IMAGES
  *      <LI> REMAP IMAGE INTENSITIES
  *      <LI> ROTATE IMAGE LOSSLESS (ANGLE IS MULTIPLE OF 90 DEGREES)
  *      <LI> MISCELLANEOUS
  *  </UL>
  */
class ImageTools
{
public:

   // 0. CONSTRUCTOR / DESTRUCTOR
   //////////////////////////////

   /** \brief constructor */
   ImageTools();

   /** \brief destructor */
   ~ImageTools();

   // 1. PADD / CROP IMAGE
   ///////////////////////

   /** \brief Creates from source image a new image with added mirrored borders
     * The size of the border is borderWidth pixels left and right and borderHeight top and bottom
     * \param pInImage input image
     * \param borderWidth width of the extra border left and right
     * \param borderHeight height of the extra border top and bottom
     * \return new image (responsability of caller to delete) or 0 when mirroring couldn't be executed*/
   static Image* MirrorBorder( Image* pInImage, int borderWidth, int borderHeight);

   /** \brief Crops the image by cutting a border from around it of borderWidth pixels left and right and borderHeight top and bottom
     * \param pInImage input image
     * \param borderWidth width of the extra border left and right
     * \param borderHeight height of the extra border top and bottom
     * \return new image (responsability of caller to delete) or 0 when mirroring couldn't be executed*/
   static Image* CropBorder( Image* pInImage, int borderWidth, int borderHeight);

   /** \brief Creates from source image a new image with added padded borders
     * The size of the border is borderWidth pixels left and right and borderHeight top and bottom
     * \param pInImage input image
     * \param borderWidth width of the extra border left and right
     * \param borderHeight height of the extra border top and bottom
     * \param paddingValue value to be used for padding
     * \return new image (responsability of caller to delete) or 0 when mirroring couldn't be executed*/
   static Image* PaddBorder( Image* pInImage, int borderWidth, int borderHeight, double paddingValue );

   /** \brief Creates new subimage cropped from current image
     * \param pInImage input image
     * \param topLeft top left corner of region to crop
     * \param bottomRight bottom right corner of region to crop
     * \return new image (responsability of caller to delete) or 0 when mirroring couldn't be executed*/
   static Image* ExtractSubImage( Image* pInImage, common::Point<int> topLeft, common::Point<int> bottomRight );

   /** \brief overwrites part of an image with a subimage
     * \param pSubGrid grid to insert
     * \param xTop x coordinate in parent image where to insert top left corner of sub image
     * \param yTop y coordinate in parent image where to insert top left corner of sub image*/
   static bool InsertSubGrid( Image* pImage, ArrayGrid<double>* pSubGrid, int xTop, int yTop );

   // 2. IMAGE STATISTICS / DIAGNOSTICS
   /////////////////////////////////////

   /** \brief prints some image properties on std out for diagnostics
     * \param ID identifier which image is being diagnosed*/\
   static void Diagnose( Image* pImage, std::string ID=std::string("") );


   // 3. COMPARE IMAGES
   ////////////////////

   /** \brief creates new difference image between two images (squared difference measure)
     * \param pImage1 first image
     * \param pImage2 second image
     * \param printOutput flag if output needs to be printed to console
     * \return image with visualization of squared difference */
   static Image* CreateImageSSD( Image* pImage1, Image* pImage2, bool printOutput=false );

   /** \brief computes MSE (Mean Square Error) between two images
     * \param pImage1 first image
     * \param pImage2 second image
     * \return MSE value */
   static double ComputeMSE( Image* pImage1, Image* pImage2 );

   /** \brief computes PSNR (Peak Signal to noise Ratio) between two images
     * \param pImage1 first image
     * \param pImage2 second image
     * \return PSNR value */
   static double ComputePSNR( Image* pImage1, Image* pImage2 );

   /** \brief creates new difference image between two images (Structural SIMilarity measure)
     * \param pImage1 first image
     * \param pImage2 second image
     * \return image with visualization of Structural SIMilarity measure */
   static Image* CreateImageSSIM( Image* pImage1, Image* pImage2, int localWindowSize = 9 );

   /** \brief help function to adjust global color perception of one image compared to another
     * \param pImage1 reference image
     * \param pImage2 image to compare with reference image
     * \return vector of ratios of color channel means */
   static std::vector<double> GetColorMappingFactors( Image* pImage1, Image* pImage2 );

   // 4. MIX TWO IMAGES
   ////////////////////

   /** \brief creates a new checkerboard image of the two input images
     * Displays squares of size blockSize of alternating the first and the second image
     * \param pImage1 first image
     * \param pImage2 second image
     * \param blockSize size of alternating blocks
     * \return checker board image; 0 if images have different dimensions or nr of bands*/
   static Image* CreateCheckeredImage( Image* pImage1, Image* pImage2, int blockSize=35);

   /** \brief creates a new transparant image from a weighted average of the two input images
     * \param pImage1 first image
     * \param pImage2 second image
     * \param thisWeight weight for the current image (must be > 0 and < 1; else 0.5 is used)
     * \return transparant image; 0 if images have different dimensions or nr of bands*/
   static Image* CreateTransparantlyMixedImage( Image* pImage1, Image* pImage2, double thisWeight=0.5);

   // 5. REMAP IMAGE INTENSITIES
   /////////////////////////////

   /** \brief creates new image with adjusted gamma
     * \param pInImage input image
     * \param gamma gamma factor to apply*/
   static Image* ApplyGamma( Image* pInImage, double gamma );

   /** \brief creates a new linear rescaled image of an input image
     * \param pImage1 first image
     * \param pImage2 second image
     * \param bandsIndependent flag if all bands are rescaled independant of each other
     * \return linearly rescaled image */
   static Image* CreateLinearRescaledImage( Image* pImage, bool bandsIndependent );

   /** \brief Creates a new image in false color using the "jet" color mapping
     * This false color mapping for gray value images is well known from usage in Matlab. It ranges from blue for
     * dark intensities to red for bright intensities, and passes through the colors cyan, yellow, and orange.
     * \return RGB image according to jet color map*/
   static Image* ApplyJetColorMap( Image* pInImage );

   /** \brief Converts current image to gray image
     * \param pInImage input image
     * This is just the simplest possible technique; to be extended later with e.g., projection on a PCA basis*/
   static Image* ConvertToGrayImage( Image* pInImage );

   /** \brief Converts current image to sepia-toned image
     * \param pInImage input image*/
   static Image* ConvertToSepiaImage( Image* pInImage );

   /** \brief Converts current image to its negative image
     * Cfr photographic negative; each values is replaced by the maximum allowed value minus the current value
     * \param pInImage input image*/
   static Image* Negative( Image* pInImage );

   // 6. ROTATE IMAGE LOSSLESS
   ///////////////////////////

   /** \brief Creates a new image: rotates input image 90 degrees clockwise
     * \param pInImage input image
     * \return new rotated image (responsability of caller to delete) */
   static Image* Rotate90DegreesClockwise( Image* pInImage );

   /** \brief Creates a new image: rotates input image 90 degrees counterclockwise
     * \param pInImage input image
     * \return new rotated image (responsability of caller to delete) */
   static Image* Rotate90DegreesCounterClockwise( Image* pInImage );

   /** \brief Creates a new image: rotates input image 180 degrees
     * \param pInImage input image (responsability of caller to delete) */
   static Image* Rotate180Degrees( Image* pInImage );

   // 7. MISCELLANEOUS
   ///////////////////

   /** \brief determines the minimum value in a local window over all spectral bands
     * \param pImage image to investigate
     * \param xLocalCenter x coordinate of local patch under consideration
     * \param yLocalCenter y coordinate of local patch under consideration
     * \param windowSize size of local patches to take */
   static double GetLocalDarkChannel( Image* pImage, int xLocalCenter, int yLocalCenter, int windowSize );

   /** \brief creates an array of 32bit unsigned int values, where each int value combines the three color band values per pixel (each 8bit) in one 32bit value
     *     [ 0 0 0 0 0 0 0 0 0 ] [ 1 1 1 1 1 1 1 1 ] [ 1 1 1 1 1 1 1 1 ] [ 1 1 1 1 1 1 1 1 ]
     *            unused                value R            value G            value B
     * \param pImage input image, assumes that values per band internally can be cast to unsigned char */
   static unsigned int* CreateIntArrayFromColorImage( Image* pImage );

   /** \brief creates an image from an array of 32bit integers by splitting again the integers in unsigned chars per band value
     * \param pIntArray the input array of 32bit integers
     * \param width     the width of the target image
     * \param height    the height of the target image */
   static Image* CreateColorImageFromIntArray( unsigned int* pIntArray, int width, int height );
};

}
}

#endif
