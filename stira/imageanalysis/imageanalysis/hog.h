#ifndef STIRA_IMAGEANALYSIS_HOG_H
#define STIRA_IMAGEANALYSIS_HOG_H

#include <vector>
#include "../../image/datastructures/Image.h"
#include "../../image/datastructures/OrientationGrid.h"

namespace stira {
namespace imageanalysis {
//http://users.utcluj.ro/~raluca/prs/prs_lab_05e.pdf

//Image descriptor based on Histogram of Orientated Gradients for gray-level images. This code
//was developed for the work: O. Ludwig, D. Delgado, V. Goncalves, and U. Nunes, 'Trainable
//Classifier-Fusion Schemes: An Application To Pedestrian Detection,' In: 12th International IEEE
//Conference On Intelligent Transportation Systems, 2009, St. Louis, 2009. V. 1. P. 432-437. In
//case of publication with this code, please cite the paper above.
class HOG
{
public:
    HOG();

    static void ComputeHogDescriptorOpenCV( std::string fileName, std::vector<float>& descriptorValues);

    static void ComputeHogDescriptorTotal( image::Image* pImage, std::vector<float>& descriptorValues );

    static image::Image* VisualizeHogDescriptorSelf( image::Image* pImage, std::vector<float>& descriptorValues,
                                                     int winWidth, int winHeight, int cellWidth, int cellHeight,
                                                     double scaleFactor, double viz_factor);

    static image::Image* VisualizeHogDescriptorCV( image::Image* pImage, std::vector<float>& descriptorValues,
                                                   int winWidth, int winHeight, int cellWidth, int cellHeight,
                                                   double scaleFactor, double viz_factor);
private:

    static std::vector<float> ComputeHogTotalDescriptorSingleCell( image::OrientationGrid* pOrientations, int nrBins, int step_x,  int step_y, int idCellX, int idCellY );
    static void NormalizeVector( std::vector<float>& inVector );
    static std::vector<image::LocalOrientation> GetOrientationVector( image::OrientationGrid* pGrid, int xMin, int yMin, int xMax, int yMax);

    static image::OrientationGrid* ComputeOrientations( image::Image* pImage );

};
}
}
#endif // HOG_H
