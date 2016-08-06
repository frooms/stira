#ifndef STIRA_IMAGEANALYSIS_HOG_H
#define STIRA_IMAGEANALYSIS_HOG_H

#include <vector>
#include "../../common/common/RectangularROI.h"
#include "../../imagedata/datastructures/Image.h"
#include "../../imagedata/datastructures/OrientationGrid.h"

namespace stira {
namespace imageanalysis {

/** \brief Class to compute Image descriptor based on Histogram of Orientated Gradients (HOG) for gray-level images
  * References: - https://software.intel.com/en-us/node/529070
  *             - http://stackoverflow.com/questions/32417531/hog-what-is-done-in-the-contrast-normalization-step
  * TODO: further implement rest of SIFT: http://www.vlfeat.org/api/sift.html
  */
class HOG
{
public:

    /** \brief constructor
      * \param pImage input image
      * \param myRoi Region of Interest to compute descriptor for (currently not used; HOG descriptor is computed for whole image)
      * \param cellWidth width of single cell in HOG
      * \param cellHeight height of single cell in HOG
      * \param nrBins number of bins for orientation histogram in single cell ;*/
    HOG( image::Image* pImage, common::RectangularROI<int> myRoi, int cellWidth, int cellHeight, int nrBins );

    /** \brief computes the HOG descriptor for the given ROI image
      *
      * \param descriptorValues output vector containing the output descriptor values
      */
    void ComputeHogDescriptor( std::vector<double>& descriptorValues );

    /** \brief visualization of HOG descriptor method
      *
      * \param descriptorValues vector containing the descriptor values to be visualized
      * \param winWidth width of window to be visualized
      * \param winHeight height of window to be visualized
      * \param scaleFactor factor to scale whole visualization grid
      * \param viz_factor factor to stretch the line of the HOG per cell with for easier visualization
      */
    image::Image* VisualizeHogDescriptor(        std::vector<double>& descriptorValues,
                                                 int winWidth, int winHeight,
                                                 double scaleFactor, double viz_factor);
private:

    /** \brief computes the HOG descriptor for a single cell
      *
      * \param pOrientations grid containing gradient angles and magnitudes for whole image
      * \param idCellX counter of current cell in x direction
      * \param idCellY counter of current cell in y direction
      */
    std::vector<double> ComputeHogDescriptorSingleCell( image::OrientationGrid* pOrientations, int idCellX, int idCellY );

    /** \brief computes angles and magnitudes of image gradients
      * \return grid with gradient magnitude and angle for all image locations
      */
    image::OrientationGrid* ComputeOrientations( );

    image::Image* mpImage;   ///< input image
    common::RectangularROI<int> mRoi;   ///< rectangular ROI (currently unused; HOG descriptor is computed for whole image)
    int mCellWidth;   ///< width of a singkle cell
    int mCellHeight;   ///< height of a single cell
    int mNrBins;   ///< number of bins to quantize the orientation histogram in
};
}
}
#endif // HOG_H
