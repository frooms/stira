
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

#ifndef STIRA_PYRAMIDAPPLICATIONS_PYRAMIDKEYPOINTDETECTOR_H
#define STIRA_PYRAMIDAPPLICATIONS_PYRAMIDKEYPOINTDETECTOR_H

#include <complex>

#include "../../image/datastructures/Pyramid.h"

namespace stira {
namespace pyramidapplications {
   
/** \brief A class to demonstrate simple contrast enhancement using a steerable pyramid
  * reference:
  *
  * BMVA symposium at British Computer Society, March 1st 2006.
  * www.bmva.ac.uk/meetings      J. Fauqueur  (U. of Cambridge)
  * Multiscale keypoint detection using the Dual-Tree Complex Wavelet Transform
  * Also presented at ICIP 2006
  *   J Fauqueur, N Kingsbury and R Anderson:
  *   "Multiscale keypoint detection using the dual-tree complex wavelet transform",
  *   Proc. IEEE Conference on Image Processing, Atlanta, GA, 8-11 Oct 2006.
  *   copy available at http://www-sigproc.eng.cam.ac.uk/~ngk/
  */
class PyramidKeyPointDetector
{
public:

   /** \brief constructor
     * \param pPyramid pyramid with input data */
   PyramidKeyPointDetector( image::Pyramid< std::complex<double> >* pPyramid );
   
   /** \brief destructor*/
   ~PyramidKeyPointDetector();
   
   /** \brief run method*/
   void Run();
   
private:

   bool MergeOrientations1( int scale );

   bool MergeOrientations2( int scale );
   
   void AccumulateScales( );
   
   image::ArrayGrid<bool>* FindLocalMaxima(image::ArrayGrid<double>* pGrid );

   image::Pyramid< std::complex<double> >* mpPyramid;
   
   std::vector< image::ArrayGrid<double>* > mvAccumulatedMaps;
   
   std::vector< image::ArrayGrid<double>* > mvEnergyMaps;
   
   //std::vector< image::ArrayGrid<double>* > mvKeyPointMaps;
};

}
}

#endif
