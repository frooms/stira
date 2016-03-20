
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

//=======================================================================================

/** \brief struct to hold results of a PCA analysis of the passed points */
struct PcaResult
{
    Point<double> center;                  ///< center of the point cloud
    std::vector< Point<double> > vector;   ///< vector of eigenvector; each point represents the vector wrt the center above
    std::vector<double> eigenValue;        ///< vector of eigenvalues corresponding with the vectors above
};

//=======================================================================================

/** \brief struct to hold results of a single point cluster */
struct pointCluster
{
    Point<double> center;                  ///< center of this cluster
    std::vector<Point<double> > members;   ///< vector of points in this cluster
};

//=======================================================================================

/** \brief class for 2D point cloud analysis
  *   Uses OpenCV's functionalities */
class ClusteringLearning
{
public:
    /** \brief constructor
      * \param inputPoints cloud of input points to be analysed */
    ClusteringLearning( std::vector< Point<double> > inputPoints );

    /** \brief PCA analysis of this 2D point cloud (uses OpenCV)
     * Ref: http://docs.opencv.org/3.1.0/d1/dee/tutorial_introduction_to_pca.html
     *  \return a PcaResult struct */
    PcaResult ComputePCA( );

    /** \brief K-Means clustering of this 2D point cloud
     * Ref: https://en.wikipedia.org/wiki/K-means_clustering
     * \param clusterCenters vector of initial cluster centroids
     * \return a vector of pointCluster structs, one per cluster */
    std::vector< pointCluster > ComputeKMeans( std::vector< Point<double> > clusterCenters );

private:
    std::vector< Point<double> > mvDataPoints;  ///< the input data points

};

}
}

#endif // CLUSTERINGLEARNING_H
