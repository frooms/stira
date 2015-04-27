
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

#ifndef STIRA_FILTER_NONLOCALMEANSFILTER_H
#define STIRA_FILTER_NONLOCALMEANSFILTER_H

#include <stdint.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include "../../image/datastructures/Image.h"

namespace stira{
namespace filter{

/** \brief structure to compare image blocks
  * We use the coordinates of the center of the candidate block and its Euclidean intensity 
  * distance with a given reference block. This distance is the summed squared intensity 
  * difference of two blocks*/
struct blockMatch
{
   int x;  ///< x coordinate of the center of a block
   int y;  ///< y coordinate of the center of a block
   double distance;   ///< Euclidean intensity difference to reference block
};

//===============================================================================

/** \brief non-local means filter 
  *
  * Experimental version; last satisfactory tested version 22 september 2009
  *
  * Reference: "A non-local algorithm for image denoising"
  *               Buades, A. and  Coll, B. and  Morel, J.-M.  
  *               Computer Vision and Pattern Recognition, 2005. CVPR 2005.
  *               Volume: 2,  pages: 60- 65 vol. 2
  *               http://dmi.uib.es/~abuades/nlmeanscode.html
  *    (planned but not yet implemented)
  *            "An improved non-local means algorithm for image denoising",
  *                Goossens, B. and Luong, H.Q. and Pizurica, A. and Philips, W., 
  *                2008 International Workshop on Local and Non-Local Approximation in Image Processing (LNLA2008), 
  *                Lausanne, Switzerland, Aug. 25-29 
  */
class NonLocalMeansFilter
{
public:
   /** \brief constructor
     * \param size filter window size to consider */
   NonLocalMeansFilter( int size=7 );
   
    /** \brief destructor*/
   ~NonLocalMeansFilter(); 
   
   /** \brief sets block size
     * \param size filter window size to consider */
   void SetBlockSize( int size );
   
   /** \brief gets block size*/
   int GetBlockSize( );
   
   /** \brief sets sigma of the Gaussian weight function to be applied within the window
     * \param sigma sigma of the Gaussian weight function to be applied */
   void SetSigma( double sigma );
   
   /** \brief gets sigma of the Gaussian weight function to be applied within the window*/
   double GetSigma( );
   
   /** \brief runs non-local means filter 
     * \param pImageIn Image to filter*/
   image::Image* Run( image::Image* pImageIn );
   
private:
   /** \brief computes Euclidean distance of intensities of two image blocks, weighted with Gaussian weights
     * \param xCenter1 x coordinate of center of first block
     * \param yCenter1 y coordinate of center of first block
     * \param xCenter2 x coordinate of center of second block
     * \param yCenter2 y coordinate of center of second block*/
   double ComputeEuclideanDistance( int xCenter1, int yCenter1, int xCenter2, int yCenter2 );
   
   /** \brief checks for a block with given center coordinates the distance with the neighboring blocks 
     * \param xCenter x coordinate of center of current block
     * \param yCenter y coordinate of center of current block
     * \return center coordinates of candidate neighbor blocks and their distances to the current block */
   std::vector< blockMatch > CheckNeighboringBlocks( int xCenter, int yCenter );
   
   /** \brief Filters current block given center coordinates and distances of neighboring blocks 
     * \param xCenter x coordinate of center of current block
     * \param yCenter y coordinate of center of current block
     * \param myBlocks center coordinates of candidate neighbor blocks and their distances to the current block*/
   void FilterCurrentBlock( int xCenter, int yCenter, std::vector< blockMatch > myBlocks );
   
   /** \brief loops over all image blocks */
   void LoopOverImage( );
   
   int mBlockSize;  ///< Size of an image block (in a 7x7 block, this is 7)
   double mSigma;  ///< sigma of the Gaussian weight function to be applied within the window
   int mNrIterations;
   int mSearchWindowSize;
   int mBlockHalfSize;  ///< Half size of an image block (in a 7x7 block, this is 3)
   int mSourceWidth;;  ///< width of image currently being processed
   int mSourceHeight;;  ///< height of image Grid currently being processed
   int mExtendedWidth;;  ///< width of image currently being processed
   int mExtendedHeight;;  ///< height of image Grid currently being processed
   int mNrBands;;  ///< nr of bands of image currently being processed
   image::ArrayGrid<double>* mpGridIn;  ///< Grid currently being processed
   image::ArrayGrid<double>* mpGridOut;  ///< Grid currently being processed
};

}
}

#endif

