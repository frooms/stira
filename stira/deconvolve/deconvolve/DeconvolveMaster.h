
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

#ifndef STIRA_DECONVOLVE_DECONVOLVEMASTER_H
#define STIRA_DECONVOLVE_DECONVOLVEMASTER_H

#include "../../imagedata/datastructures/Image.h"

namespace stira{
namespace deconvolve{

using namespace imagedata;

/** \brief parent class for computing deconvolutions
  */
class DeconvolveMaster
{
public:
   
   /** \brief Runs the actual restoration algorithm
     * After completion, get the result with GetRestoredImage() */
   virtual bool Run()=0;
   
   /** \brief Gets the degraded input image*/
   Image* GetDegradedImage();
   
   /** \brief sets the degraded image to restore
     * \param pDegradedImage the image to restore*/
   void SetDegradedImage( Image* pDegradedImage);
   
   /** \brief gets the Point Spread Function (PSF)
     * The PSF is a model of the blur; it is how every single point is imaged in the degraded image.
     * For an ideal image, it would be a delta function; in reality, it is mostly a certain spot. */
   Image* GetPSF();
   
   /** \brief sets the Point Spread Function (PSF)
     * \param pPSF The PSF. */
   void SetPSF( Image* pPSF);
   
   /** \brief gets the result after running the deconvolution */
   Image* GetRestoredImage();
   
   /** \brief sets the noise level 
     * \param sigma the sigma of the noise*/
   void SetSigmaNoise( double sigma );
   
   /** \brief gets the noise level */
   double GetSigmaNoise();
   
   /** \brief checks if all conditions are fulfilled for this deconvolution method*/
   virtual bool IsReadyToRun()=0;
   
protected:

   /** \brief constructor
     * Sets degraded input image; PSF is estimated or entered in later stage
     * \param pDegradedImage degraded input image*/
   DeconvolveMaster(Image* pDegradedImage );
   
   /** \brief constructor
     * Sets degraded input image and PSF
     * \param pDegradedImage degraded input image
     * \param pPSF Point Spread Function (models the blur in the image)*/
   DeconvolveMaster(Image* pDegradedImage, Image* pPSF );
   
   /** \brief constructor*/
   virtual ~DeconvolveMaster();
   
   /** \brief checks basic conditions are fulfilled for all deconvolution methods*/
   bool AreParentConditionsOK();
   
   Image* mpDegradedImage;   ///< degraded input image
   Image* mpRestoredImage;   ///< restored image for output
   Image* mpPSF;  ///< image containing the Point Spread Function
   
   double mSigmaNoise;   ///< sigma of the noise
};
}
}
#endif
