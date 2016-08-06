#include "HOG.h"
#include <iostream>
#include "../../imagetools/tools/DrawImageTools.h"
#include "../../imagetools/tools/ImageIO.h"
#include "../../filter/filter/SeparableFilter.h"

namespace stira {
namespace imageanalysis {

HOG::HOG( image::Image* pImage, common::RectangularROI<int> myRoi, int cellWidth, int cellHeight, int nrBins )
{
    mpImage = pImage;
    mRoi = myRoi;
    mCellWidth = cellWidth;
    mCellHeight = cellHeight;
    mNrBins = nrBins;
}

//--------------------------------------------------------------------------------------------------------------------------

image::OrientationGrid* HOG::ComputeOrientations( )
{
    stira::filter::SeparableFilter sf;
    int width  = mpImage->GetWidth();
    int height = mpImage->GetHeight();

    image::ArrayGrid<double>* pGradientX = new image::ArrayGrid<double>( width, height );
    image::ArrayGrid<double>* pGradientY = new image::ArrayGrid<double>( width, height );

    double pHX[ 3 ] = { -1.0, 0.0, 1.0 };

    sf.SeparableFilter::RunRow(    mpImage->GetBands()[0], pGradientX, pHX, 3 );
    sf.SeparableFilter::RunColumn( mpImage->GetBands()[0], pGradientY, pHX, 3 );

    image::OrientationGrid* pOrientationGrid = new image::OrientationGrid(width, height);

    for ( int y = 0; y < height; y++ )
    {
        for (int x = 0; x < width; x++)
        {
            // result between -180 and 180
            double localAngle = atan2( -pGradientY->GetValue(x, y), pGradientX->GetValue(x, y) );

            //unsigned gradients: project between 0 and 180 degrees!!
            if (localAngle < 0.0) { localAngle += M_PI; }
            if (localAngle < 0.0) { localAngle += M_PI; }
            if (localAngle > M_PI) { localAngle -= M_PI; }
            if (localAngle > M_PI) { localAngle -= M_PI; }
            pOrientationGrid->SetAngle( x, y, localAngle );
            pOrientationGrid->SetMagnitude(   x, y, sqrt(   ( pGradientX->GetValue(x, y) * pGradientX->GetValue(x, y) )
                                                          + ( pGradientY->GetValue(x, y) * pGradientY->GetValue(x, y) ) ) );
        }
    }

    delete pGradientX;
    delete pGradientY;
    return pOrientationGrid;
}

//--------------------------------------------------------------------------------------------------------------------------

std::vector<double> HOG::ComputeHogDescriptorSingleCell( image::OrientationGrid* pOrientations, int idCellX, int idCellY )
{
    std::vector<double> H2 = std::vector<double>( mNrBins, 0.0 );
    std::vector<image::LocalOrientation> vOrientations = pOrientations->GetOrientationVector( idCellX * mCellWidth, idCellY * mCellHeight, (idCellX + 1) * mCellWidth - 1, (idCellY + 1) * mCellHeight - 1 );
    int K = vOrientations.size();
    double angleStep = M_PI / mNrBins;

    // assembling the histogram with 9 bins (range of 20 degrees per bin)
    int bin=0;
    for ( double ang_lim = angleStep; ang_lim <= M_PI; ang_lim += angleStep )
    {
        for (int k = 0; k < K; k++)
        {
            if (vOrientations[k].GetAngle() < ang_lim)
            {
                vOrientations[k].SetAngle( 100 );  // mark the angle in the vector as processed
                H2[bin] += vOrientations[k].GetMagnitude();  // add magnitude of orientation to designated angle bin
            }
        }
        bin++;
    }

    return H2;
}

//--------------------------------------------------------------------------------------------------------------------------

void HOG::ComputeHogDescriptor( std::vector<double>& descriptorValues )
{
    int nrCellsX = mpImage->GetWidth()  / mCellWidth;   //set here the number of HOG windows per bound box
    int nrCellsY = mpImage->GetHeight() / mCellHeight;

    image::OrientationGrid* pOrientations = ComputeOrientations( );

    for (int idCellY = 0; idCellY < nrCellsY-1; idCellY++)
    {
        for (int idCellX = 0; idCellX < nrCellsX-1; idCellX++ )
        {
            // compute gradient histogram per cell in this block
            std::vector<double> H2_cell0 = ComputeHogDescriptorSingleCell( pOrientations, idCellX,   idCellY );
            std::vector<double> H2_cell1 = ComputeHogDescriptorSingleCell( pOrientations, idCellX,   idCellY+1 );
            std::vector<double> H2_cell2 = ComputeHogDescriptorSingleCell( pOrientations, idCellX+1, idCellY );
            std::vector<double> H2_cell3 = ComputeHogDescriptorSingleCell( pOrientations, idCellX+1, idCellY+1 );

            // concatenate cell gradient histograms into a block
            H2_cell0.insert( H2_cell0.end(), H2_cell1.begin(), H2_cell1.end() );
            H2_cell0.insert( H2_cell0.end(), H2_cell2.begin(), H2_cell2.end() );
            H2_cell0.insert( H2_cell0.end(), H2_cell3.begin(), H2_cell3.end() );

            // normalize the concatenated vector
            common::MathUtils::NormalizeVector( H2_cell0 );

            descriptorValues.insert( descriptorValues.end(), H2_cell0.begin(), H2_cell0.end() );
        }
    }
    delete pOrientations;
}

//--------------------------------------------------------------------------------------------------------------------------
\
image::Image* HOG::VisualizeHogDescriptor( std::vector<double>& descriptorValues,
                                           int winWidth, int winHeight,
                                           double scaleFactor, double viz_factor )
{
     image::Image* pVisualImage = mpImage->Clone();

     // dividing 180° into 9 bins, how large (in rad) is one bin?
     double radRangeForOneBin = M_PI / (double)(mNrBins);

     // prepare data structure: 9 orientation / gradient strenghts for each cell
     int cells_in_x_dir = winWidth  / mCellWidth;
     int cells_in_y_dir = winHeight / mCellHeight;

     double*** gradientStrengths = new double**[cells_in_y_dir];
     int** cellUpdateCounter   = new int*[cells_in_y_dir];
     for (int y=0; y<cells_in_y_dir; y++)
     {
         gradientStrengths[y] = new double*[cells_in_x_dir];
         cellUpdateCounter[y] = new int[cells_in_x_dir];
         for (int x=0; x<cells_in_x_dir; x++)
         {
             gradientStrengths[y][x] = new double[mNrBins];
             cellUpdateCounter[y][x] = 0;

             for (int bin = 0; bin < mNrBins; bin++)
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

                 for (int bin = 0; bin < mNrBins; bin++)
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
     for (int celly = 0; celly < cells_in_y_dir; celly++)
     {
         for (int cellx = 0; cellx < cells_in_x_dir; cellx++)
         {
             double NrUpdatesForThisCell = (double)cellUpdateCounter[celly][cellx];

             // compute average gradient strenghts for each gradient bin direction
             for (int bin = 0; bin < mNrBins; bin++)
             {
                 gradientStrengths[celly][cellx][bin] /= NrUpdatesForThisCell;
             }
         }
     }
     std::cout << "descriptorDataIdx = " << descriptorDataIdx << std::endl;

     for (int celly = 0; celly < cells_in_y_dir; celly++)
     {
         for (int cellx = 0; cellx < cells_in_x_dir; cellx++)
         {
             // draw cell rectangles
             int drawX = cellx * mCellWidth;
             int drawY = celly * mCellHeight;

             int mx = drawX + mCellWidth  / 2;
             int my = drawY + mCellHeight / 2;

             image::DrawImageTools::DrawRectangle( pVisualImage,
                                                   common::Point<int>( drawX * scaleFactor,
                                                                       drawY * scaleFactor),
                                                   common::Point<int>( (drawX + mCellWidth)  * scaleFactor,
                                                                       (drawY + mCellHeight) * scaleFactor),
                                                   image::ColorValue(100,100,100),
                                                   false);

             // draw in each cell all 9 gradient strengths
             for (int bin = 0; bin < mNrBins; bin++)
             {
                 double currentGradStrength = gradientStrengths[celly][cellx][bin];

                 // no line to draw?
                 if (currentGradStrength < 0.01 )
                 {
                     continue;
                 }
                 else
                 {
                     double currRad = bin * radRangeForOneBin + radRangeForOneBin/2;

                     double dirVecX = cos( currRad );
                     double dirVecY = -sin( currRad );
                     double maxVecLen = mCellWidth / 2.0;
                     double scale = viz_factor; // just a visualization scale, to see the lines better

                     // compute line coordinates
                     double x1 = mx - dirVecX * currentGradStrength * maxVecLen * scale;
                     double y1 = my - dirVecY * currentGradStrength * maxVecLen * scale;
                     double x2 = mx + dirVecX * currentGradStrength * maxVecLen * scale;
                     double y2 = my + dirVecY * currentGradStrength * maxVecLen * scale;

                     // draw gradient visual_imagealization
                     image::DrawImageTools::DrawLine( pVisualImage,
                                                      common::Point<int>( x1 * scaleFactor, y1 * scaleFactor ),
                                                      common::Point<int>( x2 * scaleFactor, y2 * scaleFactor ),
                                                      image::ColorValue(0,  255, 0 ) );
                 }

             } // for (all bins)

         } // for (cellx)
     } // for (celly)

     // don't forget to free memory allocated by helper data structures!
     for (int y = 0; y < cells_in_y_dir; y++)
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

//--------------------------------------------------------------------------------------------------------------------------

}
}
