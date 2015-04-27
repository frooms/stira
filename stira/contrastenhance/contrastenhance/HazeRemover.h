
/***************************************************************************************
 *   Copyright (C) 2009 by Filip Rooms                                                 *
 *                                                                                     *
 *  Terms and conditions for using this software in any form are provided in the       *
 *  file COPYING, which can be found in the root directory of this project.            *
 *                                                                                     *
 *   Contact data: filip.rooms@gmail.com                                               *
 *                 http://www.filiprooms.be/                                           *
 *                                                                                     *
 ***************************************************************************************/

#ifndef STIRA_CONTRASTENHANCE_HAZEREMOVER_H
#define STIRA_CONTRASTENHANCE_HAZEREMOVER_H

#include "../../common/common/Random.h"
#include "../../image/datastructures/Image.h"

namespace stira {
namespace contrastenhance {

/** \brief Haze removal from single image
  * Ref: 1)  Single Image Haze Removal using Dark Channel Prior
  *          Kaiming He, Jian Sun, and Xiaoou Tang
  *          IEEE Conference on Computer Vision and Pattern Recognition (CVPR), June 2009 
  *          http://personal.ie.cuhk.edu.hk/~hkm007/
  *       2) TODO: add matting to refine processing at depth transitions
  *          A Closed Form Solution to Natural Image Matting. 
  *          A. Levin D. Lischinski and Y. Weiss.
  *          IEEE Trans. Pattern Analysis and Machine Intelligence, Feb 2008
  *             Current website: http://www.wisdom.weizmann.ac.il/~levina/
  *             Older, with pdf          http://people.csail.mit.edu/alevin/papers/Matting-Levin-Lischinski-Weiss-CVPR06.pdf
  *                    and matlab code   http://people.csail.mit.edu/alevin/matting.tar.gz
  */
class HazeRemover
{
public:

//////////////////////////
//                      //
// 1) GENERAL STUFF     //
//                      //
//////////////////////////

   /** \brief constructor */
   HazeRemover();
   
   /** \brief destructor */
   ~HazeRemover();
   
   /** \brief Run method
     * \param pImage input image */
   image::Image* Run( image::Image* pImage );

private:
   /** \brief estimates the environment light intensity */
   double EstimateAtmosphericLight();

   int mWidth;   ///< width of the source data
   int mHeight;   ///< width of the source data
   int mLocalWindowSize;   ///< size of local patch
   int mLocalWindowHalfSize;   ///< half size of local patch
   int mNrOfBands;   ///< number of bands in the source data
   double mOmega; ///< constant from the reference paper
   image::Image* mpSourceImage;   ///< the source data
};

}
}

#endif


