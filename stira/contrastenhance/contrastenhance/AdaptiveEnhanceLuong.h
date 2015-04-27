
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

#ifndef STIRA_CONTRASTENHANCE_ADAPTIVECONTRASTENHANCELUONG_H
#define STIRA_CONTRASTENHANCE_ADAPTIVECONTRASTENHANCELUONG_H

#include "../../image/datastructures/Image.h"

namespace stira {
namespace contrastenhance {

/** \brief Adaptive contrast enhancement accoring to method of Hiep Luong
  * The implementation is based on the text of his PhD thesis 
  * "Advanced Image and Video Resolution Enhancement Techniques", 2008,
  * Ghent University, TELIN-IPI, page 57 and following
  */
class AdaptiveEnhanceLuong
{
public:
   /** \brief constructor 
     * \param windowSize size of blocks for local processing */
   AdaptiveEnhanceLuong( int windowSize=9 );

   /** \brief destructor */
   ~AdaptiveEnhanceLuong();
   
   /** \brief overloaded Run method per image
     * \param pSourceImage the input image
     * \return a newly created image as result of contrast enhancement, becomes responsability of the caller*/
   image::Image* Run( image::Image* pSourceImage );
   
   /** \brief sets the factor with which parameter is to be multiplied factor
     * \param factor multiplication factor
     * usually between 0.5 and 1.0 */
   void SetAlphaFactor( double factor );
   
   /** \brief sets the size of the local window around a central pixel
     * \param size size of the local window around a central pixel
     * usually between 5 and 11 */
   void SetWindowSize( int size );

private:

   void Initialize( );
   void Cleanup();
   
   /** \brief the Run method per grid
     * \param pSourceGrid the input grid
     * \return a newly created grid as result of contrast enhancement, becomes responsability of the caller*/
   void RunSingleGrid( );

   void GetBlockStatistics( );
   void RemapGridIntensities( );

   double mFinalAlphaFactor; ///< the factor with which parameter is to be multiplied 
   double mTmpAlphaFactor;
   int mWindowSize; ///< size of a local window in the image  
   image::ArrayGrid<double>* mpSourceGrid; 
   image::ArrayGrid<double>* mpLastStepGrid;
   image::ArrayGrid<double>* mpNextStepGrid;
   image::ArrayGrid<double>* mpMeanGrid;
   image::ArrayGrid<double>* mpVarianceGrid;
   image::ArrayGrid<double>* mpAlphaGrid;
   
   double mLowerBound;
   double mUpperBound;
   
   int mWidth;
   int mHeight;
   int mHalfBlockSize;

};

}
}

#endif
