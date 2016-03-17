
/***************************************************************************************
 *   Copyright (C) 2011 by Filip Rooms                                                 *
 *                                                                                     *
 *  Terms and conditions for using this software in any form are provided in the       *
 *  file COPYING, which can be found in the root directory of this project.            *
 *                                                                                     *
 *   Contact data: filip.rooms@gmail.com                                               *
 *                 http://www.filiprooms.be/                                           *
 *                                                                                     *
 ***************************************************************************************/

#include "ClusteringLearning.h"
#include "MathUtils.h"
#include <opencv2/opencv.hpp>

using namespace std;

namespace stira {
namespace common {

struct clusterEntry
{
    int ID;
    int label;
    double centerDistance;
};

//---------------------------------------------------------------------------------

ClusteringLearning::ClusteringLearning( vector< Point<double> > inputPoints )
{
    mvDataPoints = inputPoints;
}

//---------------------------------------------------------------------------------

PcaResult ClusteringLearning::ComputePCA( )
{
    int sz = static_cast<int>( mvDataPoints.size());

    //Construct a buffer used by the pca analysis
    cv::Mat data_pts = cv::Mat( sz, 2, CV_64FC1);

    for (int i = 0; i < sz; i++)
    {
       data_pts.at<double>(i, 0) = mvDataPoints[i].x;
       data_pts.at<double>(i, 1) = mvDataPoints[i].y;
    }

    //Perform PCA analysis
    cv::PCA pca_analysis(data_pts, cv::Mat(), CV_PCA_DATA_AS_ROW);

    PcaResult pcaRes;
    //Store the center of the object

    pcaRes.center.x = pca_analysis.mean.at<double>(0, 0);
    pcaRes.center.y = pca_analysis.mean.at<double>(0, 1);

    for (int i = 0; i < 2; i++)
    {
        pcaRes.vector.push_back( Point<double>( pca_analysis.eigenvectors.at<double>(i, 0),
                                                pca_analysis.eigenvectors.at<double>(i, 1) ) );
        pcaRes.eigenValue.push_back( pca_analysis.eigenvalues.at<double>(0, i) );
    }
    return pcaRes;
}

std::vector< pointCluster > ClusteringLearning::ComputeKMeans( std::vector< Point<double> > clusterCenters )
{
    std::vector< clusterEntry > clusterLabels;   // pair that matches point index with current cluster label
    bool hasChanged = true;
    std::vector< pointCluster > clusters;

    int nrClusters = clusterCenters.size();
    int nrPoints   = mvDataPoints.size();

    for (int c = 0; c < nrClusters; c++ )
    {
        pointCluster currentCluster;
        currentCluster.center = clusterCenters[c];
        clusters.push_back(currentCluster);
    }

    // initialize: create data structure and assign all points to cluster 0
    for (int p = 0; p < nrPoints; p++)
    {
        clusterEntry ce;
        ce.ID = p;
        ce.label = 0;
        ce.centerDistance = 100000000000000000000000000000000000000000000000000000000000000000000.0;

        clusterLabels.push_back( ce );
    }

    while (hasChanged)
    {
        hasChanged = false;
        cout << "======================================================================================================================" << endl;

        //assign to each point the cluster of which the cluster center point is closest
        for (int p = 0; p < nrPoints; p++)
        {
            int closestCluster = 0;
            double distanceMin = 100000000000000000000000000000000000000000000000000000000000000000000.0;

            for (int c = 0; c < nrClusters; c++ )
            {
                double distanceCurrent = mvDataPoints[p].GetDistance( clusterCenters[c] );
                //cout << "Test: ( " << mvDataPoints[p].x << ", " << mvDataPoints[p].y << " ) distance to cluster " << c << " with center ( "
                //     << clusterCenters[c].x << ", " << clusterCenters[c].y << " ) is " << mvDataPoints[p].GetDistance( clusterCenters[c] ) << endl;
                if (distanceCurrent < distanceMin)
                {
                    distanceMin = distanceCurrent;
                    closestCluster = c;
                }
            }

            if ( (clusterLabels[p].label != closestCluster) || (clusterLabels[p].centerDistance != distanceMin) )
            {
                hasChanged = true;
            }
            clusterLabels[p].label = closestCluster;
            clusterLabels[p].centerDistance = distanceMin;
            std::cout << "Point ( " << mvDataPoints[p].x << ", " << mvDataPoints[p].y << " ) now in cluster " << clusterLabels[p].label << ", distance to ( "
                      << clusterCenters[clusterLabels[p].label].x << ", " << clusterCenters[clusterLabels[p].label].y << " ) is " << distanceMin << endl;
        }

        // compute from the new point clusters the centroids
        for (int c = 0; c < nrClusters; c++ )
        {
            std::vector< Point<double> > clusterPoints;
            for (int p = 0; p < nrPoints; p++)
            {
                if (clusterLabels[p].label == c)
                {
                    clusterPoints.push_back(mvDataPoints[p]);
                }
            }
            clusterCenters[c] = Point<double>::GetCentroid( clusterPoints );
        }
    }

    // now gather the points per cluster for export
    for (int c = 0; c < nrClusters; c++ )
    {
        pointCluster pc;
        for (int p = 0; p < nrPoints; p++)
        {
            if (clusterLabels[p].label == c)
            {
                pc.members.push_back(mvDataPoints[p]);
                pc.center = clusterCenters[c];
            }
        }
        clusters.push_back(pc);
    }

    return clusters;
}

//---------------------------------------------------------------------------------

}
}
