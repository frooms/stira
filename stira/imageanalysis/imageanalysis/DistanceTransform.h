
/***********************************************************************************
 *   Copyright (C) 2016 by Filip Rooms                                             *
 *                                                                                 *
 *  Terms and conditions for using this software in any form are provided in the   *
 *  file COPYING, which can be found in the root directory of this project.        *
 *                                                                                 *
 *   Contact data: filip.rooms@gmail.com                                           *
 *                 http://www.filiprooms.be/                                       *
 *                                                                                 *
 ***********************************************************************************/

#ifndef STIRA_IMAGEANALYSIS_DISTANCETRANSFORM_H
#define STIRA_IMAGEANALYSIS_DISTANCETRANSFORM_H

#include <iostream>
#include "../../imagedata/datastructures/Image.h"

namespace stira {
namespace imageanalysis {

using namespace imagedata;

/** \brief class to compute distance transform based on method below
  * Distance Transforms of Sampled Functions
  * P. Felzenszwalb, D. Huttenlocher
  * Theory of Computing, Vol. 8, No. 19, September 2012
  * http://cs.brown.edu/~pff/dt/ */
class DistanceTransform
{
public:
    /** \brief constructor */
    DistanceTransform();

    /** \brief destructor */
    ~DistanceTransform();

    /** \brief run that computes distance transform of binary image using squared distance
     *  \param pGridIn grid containing binary input image
     * \return grid with values of distance transform of input image */
    ArrayGrid<double>* Run( ArrayGrid<double> *pGridIn );

private:
    double ComputeParabolaIntersection( double *f, int* v, int q, int k );

    /** \brief computes distance transform of 1D function
     * \param n size of 1D buffer */
    void DistanceTransform1D( int n );

    /** \brief computes distance transform of 2D function
     * \param pGridIn input grid */
    void DistanceTransform2D( ArrayGrid<double> *pGridIn );

    /** \brief resets 1D memory buffers */
    void ResetBuffers();

    double *mpValuesIn;
    double *mpDistanceTransformValues;
    int    *mpParabolaLocations;
    double *mpParabolaBoundary;

};

}
}

#endif // DISTANCETRANSFORM_H
