
/***************************************************************************************
 *   Copyright (C) 2016 by Filip Rooms                                                 *
 *                                                                                     *
 *  Terms and conditions for using this software in any form are provided in the       *
 *  file COPYING, which can be found in the root directory of this project.            *
 *                                                                                     *
 *   Contact data: filip.rooms@gmail.com                                               *
 *                 http://www.filiprooms.be/                                           *
 *                                                                                     *
 ***************************************************************************************/

#ifndef STIRA_COMMON_CLUSTERINGLEARNING_H
#define STIRA_COMMON_CLUSTERINGLEARNING_H

#include <vector>
#include "Point.h"

namespace stira {
namespace common {

struct PcaResult
{
    Point<double> center;
    std::vector< Point<double> > vector;
    std::vector<double> eigenValue;
};

struct pointCluster
{
    Point<double> center;
    std::vector<Point<double> > members;
};

/** \brief class for point cluster analysis
  *   Uses OpenCV's functionalities */
class ClusteringLearning
{
public:
    /** \brief constructor
      * \param inputPoints the points to which the data model has to be fitted */
    ClusteringLearning( std::vector< Point<double> > inputPoints );

    // http://docs.opencv.org/3.1.0/d1/dee/tutorial_introduction_to_pca.html
    PcaResult ComputePCA( );

    // https://en.wikipedia.org/wiki/K-means_clustering
    std::vector< pointCluster > ComputeKMeans( std::vector< Point<double> > clusterCenters );

private:
    std::vector< Point<double> > mvDataPoints;  ///< the input data points

};

}
}

#endif // CLUSTERINGLEARNING_H
