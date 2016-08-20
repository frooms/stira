
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

#ifndef STIRA_STEERABLE_FREEMANADELSON_COMPUTESTEERABLEFILTEREDIMAGES_H
#define STIRA_STEERABLE_FREEMANADELSON_COMPUTESTEERABLEFILTEREDIMAGES_H

#include <cstdio>
#include <cstdlib>
#include <string.h>
#include "../../imagedata/datastructures/Image.h"
#include "../orientationestimation/ComputeOrientation.h"
#include "BasicFilterKernels.h"

using namespace std;

namespace stira {
namespace steerable {

/** \brief A class to compute the basic steerable filtered images according to Freeman and Adelson
  *
  *    W. T. Freeman and E. H. Adelson, The design and use of steerable filters,
  *    IEEE Trans. on Pattern Analysis and Machine Intelligence, vol. 13, no. 9, pp. 891 - 906, September, 1991.
  *    also available as technical report from http://people.csail.mit.edu/billf/steerpaper.html */
class ComputeSteerableFilteredImages
{
public:
   /** \brief constructor
     * \param mpSourceGrid input grid */
   ComputeSteerableFilteredImages( ArrayGrid<double>* mpSourceGrid );

   /** \brief destructor*/
   ~ComputeSteerableFilteredImages();

   /** \brief computes responses for steerable filters for a given image*/
   int Run();

   /** \brief Gets grid with dominant orientation and local energy
     * Based on expression in paper of Freeman and Adelson in Appendix 1 for G2 and H2
     * Creates a new grid for which the caller becomes responsible*/
   OrientationGrid* GetOrientationGrid( );

   /** \brief Creates new interpolated image as if filtered with even G kernels steered under theta degrees
     * \param theta angle in radians under which to compute interpolated filter response
     * Creates a new grid for which the caller becomes responsible */
   ArrayGrid<double>* InterpolateG( double theta );

   /** \brief Creates new interpolated image as if filtered with odd H kernels steered under theta degrees
     * \param theta angle in radians under which to compute interpolated filter response
     * Creates a new grid for which the caller becomes responsible */
   ArrayGrid<double>* InterpolateH( double theta );

   /** \brief Creates new filtered image as if filtered under local dominant orientation
     * Creates a new grid for which the caller becomes responsible */
   ArrayGrid<double>* FilterAlongDominantOrientationG( );

   /** \brief Creates new filtered image as if filtered under local dominant orientation
     * Creates a new grid for which the caller becomes responsible */
   ArrayGrid<double>* FilterAlongDominantOrientationH( );

   /** \brief Gets pointer to image filtered with odd H2a kernel
     * gets pointer to local array that is deleted by destructor of this class;
     * make a copy when this grid is needed longer than the life span of this class */
   ArrayGrid<double>* GetH2a();

   /** \brief Gets pointer to image filtered with odd H2b kernel
     * gets pointer to local array that is deleted by destructor of this class;
     * make a copy when this grid is needed longer than the life span of this class */
   ArrayGrid<double>* GetH2b();

   /** \brief Gets pointer to image filtered with odd H2c kernel
     * gets pointer to local array that is deleted by destructor of this class;
     * make a copy when this grid is needed longer than the life span of this class */
   ArrayGrid<double>* GetH2c();

   /** \brief Gets pointer to image filtered with odd H2d kernel
     * gets pointer to local array that is deleted by destructor of this class;
     * make a copy when this grid is needed longer than the life span of this class */
   ArrayGrid<double>* GetH2d();

   /** \brief Gets pointer to image filtered with even G2a kernel
     * gets pointer to local array that is deleted by destructor of this class;
     * make a copy when this grid is needed longer than the life span of this class */
   ArrayGrid<double>* GetG2a();

   /** \brief Gets pointer to image filtered with even G2b kernel
     * gets pointer to local array that is deleted by destructor of this class;
     * make a copy when this grid is needed longer than the life span of this class */
   ArrayGrid<double>* GetG2b();

   /** \brief Gets pointer to image filtered with odd G2c kernel
     * gets pointer to local array that is deleted by destructor of this class;
     * make a copy when this grid is needed longer than the life span of this class */
   ArrayGrid<double>* GetG2c();

private:

   bool mHasBasicResponses; ///< flag if the basic responses have been computed yet
   ArrayGrid<double>* mpSourceGrid;  ///< source image

   ArrayGrid<double>* mpResponseH2a;  ///< H2a response image (see paper)
   ArrayGrid<double>* mpResponseH2b;  ///< H2b response image (see paper)
   ArrayGrid<double>* mpResponseH2c;  ///< H2c response image (see paper)
   ArrayGrid<double>* mpResponseH2d;  ///< H2d response image (see paper)
   ArrayGrid<double>* mpResponseG2a;  ///< G2a response image (see paper)
   ArrayGrid<double>* mpResponseG2b;  ///< G2b response image (see paper)
   ArrayGrid<double>* mpResponseG2c;  ///< G2c response image (see paper)

   BasicFilterKernels* mpTaps;  ///< object containing the filter taps
};
}
}

#endif

