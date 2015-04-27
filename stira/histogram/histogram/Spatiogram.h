
/***********************************************************************************
 *   Copyright (C) 2011 by Filip Rooms                                             *
 *                                                                                 *
 *  Terms and conditions for using this software in any form are provided in the   *
 *  file COPYING, which can be found in the root directory of this project.        *
 *                                                                                 *
 *   Contact data: filip.rooms@gmail.com                                           *
 *                 http://www.filiprooms.be/                                       *
 *                                                                                 *
 ***********************************************************************************/

#ifndef STIRA_HISTOGRAM_SPATIOGRAM_H
#define STIRA_HISTOGRAM_SPATIOGRAM_H


#include "../../common/common/Point.h"
#include "../../image/datastructures/ArrayGrid.h"
#include "IntHistogram.h"

namespace stira {
namespace histogram {
//http://en.wikipedia.org/wiki/Estimation_of_covariance_matrices
//http://opencv.willowgarage.com/documentation/cpp/operations_on_arrays.html

// Spatiograms Versus Histograms for Region-Based Tracking, S. Birchfield, S. Rangarajan, IEEE Conference on Computer Vision and Pattern Recognition (CVPR), San Diego, California, June 2005

class Spatiogram
{
public:
   /** Constructor
     *
     * \param pGrid input grid
     * \param binsize size of bin
     * \param pMaskGrid boolean grid which pixels to count (at position with true) and which to ignore  (at position with false) */
    Spatiogram( image::ArrayGrid<double>* pGrid, int binsize, image::ArrayGrid<bool>* pMaskGrid=0);

    /** \brief destructor */
    ~Spatiogram();

    /** \brief Gets value of given bin */
    int GetBinValue( int binNr );

    /** \brief Gets center of gravety of points that contributed to given bin
      * \param the number of the bin */
    common::Point<double> GetAveragePoint( int binNr );

    /** \brief Gets covariance matrix of pixels of points that contributed to given bin
      * \param the number of the bin * */
    image::ArrayGrid<double>* GetCovarianceMatrix( int binNr );

    /** \brief Writes spatiogram to file
      * \param fileName name of file to write to
      * \param threshold no bins with less than "threshold" counts are written to file */
    void Write( std::string fileName, int threshold=100 );

private:
    void ComputeCovariance( int binNr );

    IntHistogram* mpHistogram;  ///< the histogram itself
    std::vector< std::vector< common::Point<int> > > mPointsPerBin;  ///< the coordinates of the points that contributed to each bin
    std::vector< image::ArrayGrid<double>* > mCovarianceMatrixVector;  ///< one covariance matrix per bin
    std::vector< common::Point<double> > mAveragPointVector;  ///< one average point per bin
};

}
}
#endif // SPATIOGRAM_H
