#include "hog.h"
#include <iostream>
#include "../../image/tools/DrawImageTools.h"
#include "../../image/tools/ImageIO.h"
#include "../../filter/filter/SeparableFilter.h"
#include <opencv2/opencv.hpp>

namespace stira {
namespace imageanalysis {

HOG::HOG()
{
}


void HOG::ComputeHogDescriptorOpenCV( std::string fileName, std::vector<float>& descriptorValues )
{
    cv::Mat img_raw = cv::imread(fileName, 1); // load as color image

    //cv::resize(img_raw, img_raw, cv::Size(64,128) );

    cv::Mat img;
    cv::cvtColor(img_raw, img, CV_RGB2GRAY);


    cv::HOGDescriptor d( cv::Size(512, 512), cv::Size(16, 16),
                         cv::Size(8, 8), cv::Size(8, 8),
                         9, 1.0, 1.0, true,
                         64);
    // Size(128,64), //winSize
    // Size(16,16), //blocksize
    // Size(8,8), //blockStride,
    // Size(8,8), //cellSize,
    // 9, //nbins,
    // 0, //derivAper,
    // -1, //winSigma,
    // 0, //histogramNormType,
    // 0.2, //L2HysThresh,
    // 0 //gammal correction,
    // //nlevels=64
    //);

    // void HOGDescriptor::compute(const Mat& img, vector<float>& descriptors,
    //                             Size winStride, Size padding,
    //                             const vector<Point>& locations) const
    vector<cv::Point> locations;
    d.compute( img, descriptorValues, cv::Size(0,0), cv::Size(0,0), locations);

    cout << "HOG descriptor size is " << d.getDescriptorSize() << endl;
    cout << "img dimensions: " << img.cols << " width x " << img.rows << " height" << endl;
    cout << "Found " << descriptorValues.size() << " descriptor values" << endl;
    cout << "Nr of locations specified : " << locations.size() << endl;
    cv::imwrite("CvImgTestOut.png", img);
}

image::OrientationGrid* HOG::ComputeOrientations( image::Image* pImage )
{
    stira::filter::SeparableFilter sf;
    int width = pImage->GetWidth();
    int height = pImage->GetHeight();

    image::ArrayGrid<double>* pGradientX = new image::ArrayGrid<double>( width, height );
    image::ArrayGrid<double>* pGradientY = new image::ArrayGrid<double>( width, height );

    double pHX[ 3 ] = { -1.0, 0.0, 1.0 };
    double pHY[ 3 ] = {  1.0, 0.0, -1.0 };

    sf.SeparableFilter::RunRow(    pImage->GetBands()[0], pGradientX, pHX, 3 );
    sf.SeparableFilter::RunColumn( pImage->GetBands()[0], pGradientY, pHY, 3 );

    image::ImageIO::WritePGM(pGradientX, "GradX.pgm", image::ImageIO::GRADIENT_OUT );
    image::ImageIO::WritePGM(pGradientY, "GradY.pgm", image::ImageIO::GRADIENT_OUT );

    image::OrientationGrid* pOrientationGrid = new image::OrientationGrid(width, height);

    for ( int y = 0; y < height; y++ )
    {
        for (int x = 0; x < width; x++)
        {
            double localAngle = atan2( pGradientY->GetValue(x, y), pGradientX->GetValue(x, y) );
            if (localAngle < 0.0) { localAngle += 2.0 * M_PI; }
            pOrientationGrid->SetAngle( x, y, localAngle );
            pOrientationGrid->SetMagnitude(   x, y, sqrt(   ( pGradientX->GetValue(x, y) * pGradientX->GetValue(x, y) )
                                                          + ( pGradientY->GetValue(x, y) * pGradientY->GetValue(x, y) ) ) );
        }
    }

    pOrientationGrid->ExportMagnitudeImage("LocalEdgeMagnitude.ppm");
    pOrientationGrid->ExportOrientationImage("LocalEdgeOrientation.ppm");

    delete pGradientX;
    delete pGradientY;
    return pOrientationGrid;
}

std::vector<image::LocalOrientation> HOG::GetOrientationVector(image::OrientationGrid* pGrid, int xMin, int yMin, int xMax, int yMax)
{
    std::vector<image::LocalOrientation> vValues;
    for ( int y = yMin; y <= yMax; y++ )
    {
        for (int x = xMin; x <= xMax; x++)
        {
           vValues.push_back( *(pGrid->GetOrientation(x, y)) );
        }
    }
    return vValues;
}

void HOG::NormalizeVector( std::vector<float>& inVector )
{
    float myNorm = 0.0;

    for (int i = 0; i < inVector.size(); i++)
    {
        myNorm += ( inVector[i] * inVector[i] );
    }

    myNorm = sqrt(myNorm);

    for (int i = 0; i < inVector.size(); i++)
    {
        inVector[i] /= ( myNorm + 0.001 );
    }
}

std::vector<float> HOG::ComputeHogTotalDescriptorSingleCell( image::OrientationGrid* pOrientations, int nrBins,  int step_x,  int step_y, int idCellX, int idCellY )
{
    std::vector<float> H2 = std::vector<float>( nrBins, 0.0 );
    std::vector<image::LocalOrientation> vOrientations = GetOrientationVector( pOrientations, idCellX * step_x, idCellY * step_y, (idCellX + 2) * step_x - 1, (idCellY + 2) * step_y - 1 );
    int K = vOrientations.size();
    double angleStep = (2.0 * M_PI / nrBins);

    // assembling the histogram with 9 bins (range of 40 degrees per bin)
    int bin=0;
    for ( double ang_lim = angleStep; ang_lim <= 2.0 * M_PI; ang_lim += angleStep )
    {
        for (int k = 0; k < K; k++)
        {
            if (vOrientations[k].GetAngle() < ang_lim)
            {
                vOrientations[k].SetAngle( 100 );  // mark the angle in the vector as processed
                H2[bin] += vOrientations[k].GetMagnitude();
            }
        }
        bin++;
    }

    return H2;
}

// Image descriptor based on Histogram of Orientated Gradients for gray-level images. This code
// was developed for the work: O. Ludwig, D. Delgado, V. Goncalves, and U. Nunes, 'Trainable
// Classifier-Fusion Schemes: An Application To Pedestrian Detection,' In: 12th International IEEE
// Conference On Intelligent Transportation Systems, 2009, St. Louis, 2009. V. 1. P. 432-437. In
// case of publication with this code, please cite the paper above.
void HOG::ComputeHogDescriptorTotal( image::Image* pImage, std::vector<float>& descriptorValues )
{
    int nrCellsX = 64;   //set here the number of HOG windows per bound box
    int nrCellsY = 64;
    int nrBins = 9;        //set here the number of histogram bins

    int step_x = floor( pImage->GetWidth()  / ( nrCellsX + 1 ) );
    int step_y = floor( pImage->GetHeight() / ( nrCellsY + 1 ) );

    image::OrientationGrid* pOrientations = ComputeOrientations( pImage );

    for (int idCellY = 0; idCellY < nrCellsY-1; idCellY++)
    {
        for (int idCellX = 0; idCellX < nrCellsX-1; idCellX++ )
        {
            // compute gradient histogram per cell
            std::vector<float> H2_00 = ComputeHogTotalDescriptorSingleCell( pOrientations, nrBins, step_x, step_y, idCellX,   idCellY );
            std::vector<float> H2_10 = ComputeHogTotalDescriptorSingleCell( pOrientations, nrBins, step_x, step_y, idCellX+1, idCellY );
            std::vector<float> H2_01 = ComputeHogTotalDescriptorSingleCell( pOrientations, nrBins, step_x, step_y, idCellX,   idCellY+1 );
            std::vector<float> H2_11 = ComputeHogTotalDescriptorSingleCell( pOrientations, nrBins, step_x, step_y, idCellX+1, idCellY+1 );

            // concatenate cell gradient histograms into a block
            H2_00.insert( H2_00.end(), H2_10.begin(), H2_10.end() );
            H2_00.insert( H2_00.end(), H2_01.begin(), H2_01.end() );
            H2_00.insert( H2_00.end(), H2_11.begin(), H2_11.end() );

            // normalize the concatenated vector
            NormalizeVector( H2_00 );

            descriptorValues.insert( descriptorValues.end(), H2_00.begin(), H2_00.end() );
        }
    }
}

//http://www.juergenwiki.de/work/wiki/doku.php?id=public:hog_descriptor_computation_and_visualization
image::Image* HOG::VisualizeHogDescriptor( image::Image* pImage,
                                           std::vector<float>& descriptorValues,
                                           int winWidth, int winHeight,
                                           int cellWidth, int cellHeight,
                                           double scaleFactor,
                                           double viz_factor )
{
     image::Image* pVisualImage = pImage->Clone();
     int gradientBinSize = 9;
     // dividing 180° into 9 bins, how large (in rad) is one bin?
     float radRangeForOneBin = 3.14/(float)gradientBinSize;

     // prepare data structure: 9 orientation / gradient strenghts for each cell
     int cells_in_x_dir = winWidth / cellWidth;
     int cells_in_y_dir = winHeight / cellHeight;

     float*** gradientStrengths = new float**[cells_in_y_dir];
     int** cellUpdateCounter   = new int*[cells_in_y_dir];
     for (int y=0; y<cells_in_y_dir; y++)
     {
         gradientStrengths[y] = new float*[cells_in_x_dir];
         cellUpdateCounter[y] = new int[cells_in_x_dir];
         for (int x=0; x<cells_in_x_dir; x++)
         {
             gradientStrengths[y][x] = new float[gradientBinSize];
             cellUpdateCounter[y][x] = 0;

             for (int bin=0; bin<gradientBinSize; bin++)
                 gradientStrengths[y][x][bin] = 0.0;
         }
     }

     // nr of blocks = nr of cells - 1
     // since there is a new block on each cell (overlapping blocks!) but the last one
     int blocks_in_x_dir = cells_in_x_dir - 1;
     int blocks_in_y_dir = cells_in_y_dir - 1;

     // compute gradient strengths per cell
     int descriptorDataIdx = 0;

     for (int blocky=0; blocky<blocks_in_y_dir; blocky++)
     {
         for (int blockx=0; blockx<blocks_in_x_dir; blockx++)
         {
             // 4 cells per block ...
             for (int cellNr=0; cellNr<4; cellNr++)
             {
                 // compute corresponding cell nr
                 int cellx = blockx;
                 int celly = blocky;
                 if (cellNr==1) celly++;
                 if (cellNr==2) cellx++;
                 if (cellNr==3)
                 {
                     cellx++;
                     celly++;
                 }

                 for (int bin=0; bin<gradientBinSize; bin++)
                 {
                     float gradientStrength = descriptorValues[ descriptorDataIdx ];
                     descriptorDataIdx++;

                     gradientStrengths[celly][cellx][bin] += gradientStrength;

                 } // for (all bins)


                 // note: overlapping blocks lead to multiple updates of this sum!
                 // we therefore keep track how often a cell was updated,
                 // to compute average gradient strengths
                 cellUpdateCounter[celly][cellx]++;

             } // for (all cells)


         } // for (all block x pos)
     } // for (all block y pos)


     // compute average gradient strengths
     for (int celly=0; celly<cells_in_y_dir; celly++)
     {
         for (int cellx=0; cellx<cells_in_x_dir; cellx++)
         {

             float NrUpdatesForThisCell = (float)cellUpdateCounter[celly][cellx];

             // compute average gradient strenghts for each gradient bin direction
             for (int bin=0; bin<gradientBinSize; bin++)
             {
                 gradientStrengths[celly][cellx][bin] /= NrUpdatesForThisCell;
             }
         }
     }
     std::cout << "descriptorDataIdx = " << descriptorDataIdx << std::endl;

     // draw cells
     for (int celly = 0; celly < cells_in_y_dir; celly++)
     {
         for (int cellx = 0; cellx < cells_in_x_dir; cellx++)
         {
             int drawX = cellx * cellWidth;
             int drawY = celly * cellHeight;

             int mx = drawX + cellWidth/2;
             int my = drawY + cellHeight/2;

             image::DrawImageTools::DrawRectangle( pVisualImage,
                                                   common::Point<int>( drawX * scaleFactor,
                                                                       drawY * scaleFactor),
                                                   common::Point<int>( (drawX + cellWidth)  * scaleFactor,
                                                                       (drawY + cellHeight) * scaleFactor),
                                                   image::ColorValue(100,100,100),
                                                   false);

             // draw in each cell all 9 gradient strengths
             for (int bin=0; bin<gradientBinSize; bin++)
             {
                 float currentGradStrength = gradientStrengths[celly][cellx][bin];

                 // no line to draw?
                 if (currentGradStrength < 0.01 )
                     continue;

                 float currRad = bin * radRangeForOneBin + radRangeForOneBin/2;

                 float dirVecX = cos( currRad );
                 float dirVecY = sin( currRad );
                 float maxVecLen = cellWidth/2;
                 float scale = viz_factor; // just a visual_imagealization scale,
                                           // to see the lines better

                 // compute line coordinates
                 float x1 = mx - dirVecX * currentGradStrength * maxVecLen * scale;
                 float y1 = my - dirVecY * currentGradStrength * maxVecLen * scale;
                 float x2 = mx + dirVecX * currentGradStrength * maxVecLen * scale;
                 float y2 = my + dirVecY * currentGradStrength * maxVecLen * scale;

                 // draw gradient visual_imagealization
                 image::DrawImageTools::DrawLine( pVisualImage,
                                                  common::Point<int>( x1 * scaleFactor, y1 * scaleFactor ),
                                                  common::Point<int>( x2 * scaleFactor, y2 * scaleFactor ),
                                                  image::ColorValue( 255, 0, 0 ) );

             } // for (all bins)

         } // for (cellx)
     } // for (celly)


     // don't forget to free memory allocated by helper data structures!
     for (int y=0; y<cells_in_y_dir; y++)
     {
       for (int x=0; x<cells_in_x_dir; x++)
       {
            delete[] gradientStrengths[y][x];
       }
       delete[] gradientStrengths[y];
       delete[] cellUpdateCounter[y];
     }
     delete[] gradientStrengths;
     delete[] cellUpdateCounter;

     return pVisualImage;
}

}
}

