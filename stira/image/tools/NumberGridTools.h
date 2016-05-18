
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

#ifndef STIRA_IMAGE_TOOLS_NUMBERGRIDTOOLS_H
#define STIRA_IMAGE_TOOLS_NUMBERGRIDTOOLS_H

#include <iostream>
#include <complex>
#include "../../common/common/StiraMacros.h"
#include "../../common/common/MathUtils.h"
#include "../../common/common/Statistics.h"
#include "../../common/common/Point.h"
#include "../../common/common/RectangularROI.h"
#include "../../histogram/histogram/JointHistogram.h"
#include "../datastructures/ArrayGrid.h"
#include "../tools/NearestNeighborInterpolator.h"
#include "ArrayGridTools.h"

//#define CHECK_INF_OR_NAN_VALUES

namespace stira {
namespace image {

/**  \brief Child class of ArrayGrid in specific case that the template represents numerical values
  * In this case, certain extra operations are possible, like finding min and max, add, multiply, subtract
  * Methods in this class are divided in the following "sections":
  *   0. CONSTRUCT / DESTRUCT
  *   1. GLOBAL DIAGNOSTICS
  *   2. GLOBAL GRID STATISTICS AND PROJECTIONS
  *   3. LOCAL WINDOW GRID STATISTICS
  *   4. COMPARISON GRIDS / COEFFICIENTS
  *   5. CONVERT GRID DATA TYPE
  *   6. GRID DERIVATIVES
  *   7. GRID ROTATION WITHOUT RESAMPLING
  *   8. SPECIAL TRANSFORMS
  *   9. GRID THRESHOLDING
  *  10. COMBINE GRIDS*/
template <class T>
class NumberGridTools : public ArrayGridTools<T>
{

///////////////////////////////
//                           //
// 0. CONSTRUCT / DESTRUCT   //
//                           //
///////////////////////////////

public:
   /** \brief Constructor. */
   NumberGridTools( );

   /** \brief Destructor. */
   virtual ~NumberGridTools();

////////////////////////////
//                        //
// 1. GLOBAL DIAGNOSTICS  //
//                        //
////////////////////////////

public:

   /** \brief Diagnoses a real-valued grid
     * \param pGrid input grid to diagnose
     * \param fileName name to differentiate cout's */
   static void DiagnoseReal( ArrayGrid<double>* pGrid, std::string fileName = std::string("") );

   /** \brief copies values from pSourceGrid to pDestinationGrid
     * \param pSourceGrid grid from which to copy values
     * \param pDestinationGrid grid to which to copy values*/
   static void CopyValues( ArrayGrid<T>* pSourceGrid, ArrayGrid<T>* pDestinationGrid );

   /** \brief counts nr of nan's and inf's in current grid
     * \param pGrid in: grid to investigate
     * \param nrNAN out: number of nan's, i.e., number of times that value in grid is "Not A Number"
     * \param nrINF out: number of inf's, i.e., number of times that value in grid is "infinite"*/
   static bool CountNANandINF( ArrayGrid<T>* pGrid, int& nrNAN, int& nrINF, std::string ID );

   /** \brief cleans nan's and inf's in current grid
     * \param pGrid in: grid to investigate*/
   static bool CleanNANandINF( ArrayGrid<T>* pGrid );

   /** \brief counts nr of zero's in current grid
     * \param pGrid in: grid to investigate*/
   static int CountZero( ArrayGrid<T>* pGrid );

///////////////////////////////////////////////
//                                           //
// 2. GLOBAL GRID STATISTICS AND PROJECTIONS //
//                                           //
///////////////////////////////////////////////

   /** \brief gets values of minimum and maximum of the grid
     * \param pGrid in: grid to investigate
     * \param mmin out: minimum value of the grid
     * \param mmax out: maximum value of the grid*/
   static void GetMinMax( ArrayGrid<T>* pGrid, double& mmin, double& mmax);

   /** \brief gets values and positions of minimum and maximum of the grid
     * \param pGrid in: grid to investigate
     * \param mmin out: minimum value of the grid
     * \param mmax out: maximum value of the grid
     * \param xMin out: x-coordinate of minimum value of the grid
     * \param yMin out: y-coordinate of minimum value of the grid
     * \param xMax out: x-coordinate of maximum value of the grid
     * \param yMax out: y-coordinate of maximum value of the grid*/
   static void GetMinMax( ArrayGrid<T>* pGrid, double& mmin, double& mmax, int& xMin, int& yMin, int& xMax, int& yMax);

   /** \brief gets value and position of minimum of the grid
     * \param pGrid in: grid to investigate
     * \param mmin out: minimum value of the grid
     * \param xMin out: x-coordinate of minimum value of the grid
     * \param yMin out: y-coordinate of minimum value of the grid*/
   static void GetMin( ArrayGrid<T>* pGrid, double& mmin, int& xMin, int& yMin);

   /** \brief gets value and position of maximum of the grid
     * \param pGrid in: grid to investigate
     * \param mmax out: maximum value of the grid
     * \param xMax out: x-coordinate of maximum value of the grid
     * \param yMax out: y-coordinate of maximum value of the grid*/
   static void GetMax( ArrayGrid<T>* pGrid, double& mmax, int& xMax, int& yMax);

   /** \brief gets maximum in absolute value of the grid
     * \param pGrid in: grid to investigate*/
   static double GetAbsMax( ArrayGrid<T>* pGrid );

   /** \brief computes sum of all values in this grid
     * \param pGrid in: grid to investigate*/
   static T GetGridIntegral( ArrayGrid<T>* pGrid );

   /** \brief Gets the L2 norm of all values in the grid */
   static double GetSquaredNorm( ArrayGrid<double>* pGrid );

   /** \brief Gets the L2 norm of all values in the grid */
   static double GetSquaredNorm( ArrayGrid< std::complex<double> >* pGrid );

   /** \brief computes mean of all values in this grid
     * \param pGrid in: grid to investigate*/
   static T GetGridMean( ArrayGrid<T>* pGrid );

   /** \brief computes variance of all values in this grid
     * \param mean mean of the grid; must already have been computed*/
   static T GetGridVariance( ArrayGrid<T>* pGrid, T mean);

   /** \brief computes kurtosis of all values in this grid
     * \param pGrid in: grid to investigate
     * Formula from
     *   http://en.wikipedia.org/wiki/Kurtosis#Sample_kurtosis
     * section "Sample kurtosis"
     * \param mean mean of the grid; must already have been computed*/
   static T GetGridKurtosis( ArrayGrid<T>* pGrid );

   /** \brief computes kurtosis of all values in this grid
     * Formula from
     *   http://en.wikipedia.org/wiki/Kurtosis#Sample_kurtosis
     * section "Sample kurtosis"
     * \param mean mean of the grid; must already have been computed*/
   static T GetGridKurtosis( ArrayGrid<T>* pGrid, T gridMean, T gridvariance );

   /** \brief rescales values in grid to be in the range [desiredMin, T desiredMax]
     * \param pGrid input grid before rescaling
     * \param desiredMin desired minimum after rescaling
     * \param desiredMax desired maximum after rescaling
     * \warning operates directly on source data; so old values are lost (but can be recomputed)*/
   static void RescaleGrid( ArrayGrid<T>* pGrid, T desiredMin, T desiredMax );

   /** \brief projects the values in the grid on the X axis
     * \param pGrid input grid to project*/
   static std::vector< common::IntensityPoint > ProjectGridOnX( ArrayGrid<T>* pGrid );

   /** \brief projects the values in the grid on the Y axis
     * \param pGrid input grid to project*/
   static std::vector< common::IntensityPoint > ProjectGridOnX( ArrayGrid<T>* pGrid, int xTopLeft, int yTopLeft, int xBottomRight, int yBottomRight  );

   /** \brief projects the values in the grid on the X axis
     * \param pGrid input grid to project*/
   static std::vector< common::IntensityPoint > ProjectGridOnY( ArrayGrid<T>* pGrid );

   /** \brief projects the values in the grid on the Y axis
     * \param pGrid input grid to project*/
   static std::vector< common::IntensityPoint > ProjectGridOnY( ArrayGrid<T>* pGrid, int xTopLeft, int yTopLeft, int xBottomRight, int yBottomRight  );

//////////////////////////////////////
//                                  //
// 3. LOCAL WINDOW GRID STATISTICS  //
//                                  //
//////////////////////////////////////

   /** \brief gets local minimum in a local window with given size
     * WARNING: does not perform boundary checking: moves from (x-(localWindowSize/2)) to (x+(localWindowSize/2))
     *            and from (y-(localWindowSize/2)) to (y+(localWindowSize/2)) without checking if values go out of range!!
     * \param pGrid grid on which to compute
     * \param x x coordinate of central pixel of local window
     * \param y y coordinate of central pixel of local window
     * \param localWindowWidth width of local window
     * \param localWindowHeight height of local window */
   static T GetLocalMinimum( ArrayGrid<T>* pGrid, int x, int y, int localWindowWidth, int localWindowHeight );

   /** \brief gets local maximum in a local window with given size
     * WARNING: does not perform boundary checking: moves from (x-(localWindowSize/2)) to (x+(localWindowSize/2))
     *            and from (y-(localWindowSize/2)) to (y+(localWindowSize/2)) without checking if values go out of range!!
     * \param pGrid grid on which to compute
     * \param x x coordinate of central pixel of local window
     * \param y y coordinate of central pixel of local window
     * \param localWindowWidth width of local window
     * \param localWindowHeight height of local window*/
   static T GetLocalMaximum( ArrayGrid<T>* pGrid, int x, int y, int localWindowWidth, int localWindowHeight );

   /** \brief gets local maximum in absolute value in a local window with given size
     * overloaded version for grid of integers
     * WARNING: does not perform boundary checking: moves from (x-(localWindowSize/2)) to (x+(localWindowSize/2))
     *            and from (y-(localWindowSize/2)) to (y+(localWindowSize/2)) without checking if values go out of range!!
     * \param pGrid grid on which to compute
     * \param x x coordinate of central pixel of local window
     * \param y y coordinate of central pixel of local window
     * \param localWindowWidth width of local window
     * \param localWindowHeight height of local window */
   static T GetLocalAbsMaximum( ArrayGrid<int>* pGrid, int x, int y, int localWindowWidth, int localWindowHeight );

   /** \brief gets local maximum in absolute value in a local window with given size
     * overloaded version for grid of floats
     * WARNING: does not perform boundary checking: moves from (x-(localWindowSize/2)) to (x+(localWindowSize/2))
     *            and from (y-(localWindowSize/2)) to (y+(localWindowSize/2)) without checking if values go out of range!!
     * \param pGrid grid on which to compute
     * \param x x coordinate of central pixel of local window
     * \param y y coordinate of central pixel of local window
     * \param localWindowWidth width of local window
     * \param localWindowHeight height of local window */
   static T GetLocalAbsMaximum( ArrayGrid<float>* pGrid, int x, int y, int localWindowWidth, int localWindowHeight );

   /** \brief gets local maximum in absolute value in a local window with given size
     * overloaded version for grid of doubles
     * WARNING: does not perform boundary checking: moves from (x-(localWindowSize/2)) to (x+(localWindowSize/2))
     *            and from (y-(localWindowSize/2)) to (y+(localWindowSize/2)) without checking if values go out of range!!
     * \param pGrid grid on which to compute
     * \param x x coordinate of central pixel of local window
     * \param y y coordinate of central pixel of local window
     * \param localWindowWidth width of local window
     * \param localWindowHeight height of local window */
   static T GetLocalAbsMaximum( ArrayGrid<double>* pGrid, int x, int y, int localWindowWidth, int localWindowHeight );

   /** \brief gets local mean of values in a local window defined by (xTopLeft, yTopLeft) as top left corner and (xBottomRight, yBottomRight) as bottom right corner (included!)
     *
     * does boundary checking: adjusts values of xTopLeft, xBottomRight, yTopLeft, yBottomRight to be clipped to fit inside the grid!!
     * \param pGrid grid on which to compute
     * \param xTopLeft x coordinate of top left corner of local window
     * \param yTopLeft y coordinate of top left corner of local window
     * \param xBottomRight x coordinate of bottom right corner of local window
     * \param yBottomRight y coordinate of bottom right corner of local window */
   static T ComputeLocalMean( ArrayGrid<T>* pGrid, int& xTopLeft, int& yTopLeft, int& xBottomRight, int& yBottomRight );

   /** \brief gets local mean of values in a local window defined by a RectangularROI
     *
     * does boundary checking: adjusts values of xTopLeft, xBottomRight, yTopLeft, yBottomRight to be clipped to fit inside the grid!!
     * \param pGrid grid on which to compute
     * \param xTopLeft x coordinate of top left corner of local window
     * \param yTopLeft y coordinate of top left corner of local window
     * \param xBottomRight x coordinate of bottom right corner of local window
     * \param yBottomRight y coordinate of bottom right corner of local window */
   static double ComputeLocalMean( ArrayGrid<double>* pGrid, common::RectangularROI<int> rroi );

   /** \brief gets local variance of values in a local window defined by a RectangularROI
     *
     * \param pGrid grid on which to compute
     * \param rroi the rectangular ROI in which to compute the variance
     * \param thisMean the already computed mean of the values in the ROI */
   static double ComputeLocalVariance( ArrayGrid<double>* pGrid, common::RectangularROI<int> rroi, double thisMean);

   /** \brief gets local mean of ABSOLUTE values in a local window defined by (xTopLeft, yTopLeft) as top left corner and (xBottomRight, yBottomRight) as bottom right corner (included!)
     *
     * does boundary checking: adjusts values of xTopLeft, xBottomRight, yTopLeft, yBottomRight to be clipped to fit inside the grid!!
     * \param pGrid grid on which to compute
     * \param xTopLeft x coordinate of top left corner of local window
     * \param yTopLeft y coordinate of top left corner of local window
     * \param xBottomRight x coordinate of bottom right corner of local window
     * \param yBottomRight y coordinate of bottom right corner of local window */
   static T ComputeLocalAbsoluteMean( ArrayGrid<T>* pGrid, int& xTopLeft, int& yTopLeft, int& xBottomRight, int& yBottomRight );

   /** \brief computes the variance of the values a local window size defined by (xTopLeft, yTopLeft) as top left corner and
     *        (xBottomRight, yBottomRight) as bottom right corner (included!)
     *
     * does boundary checking: adjusts values of xTopLeft, xBottomRight, yTopLeft, yBottomRight to be clipped to fit inside the grid!!
     *
     * WARNING: mean value of local window must already be computed before executing this method
     *
     * \param pGrid source grid
     * \param xTopLeft x coordinate of top left corner of local window
     * \param yTopLeft y coordinate of top left corner of local window
     * \param xBottomRight x coordinate of bottom right corner of local window
     * \param yBottomRight y coordinate of bottom right corner of local window
     * \param thisMean the mean value of the values in the local window*/
   static double ComputeLocalVariance( ArrayGrid<double>* pGrid, int& xTopLeft, int& yTopLeft, int& xBottomRight, int& yBottomRight, double thisMean);

   /** \brief computes the variance of the values a local window size defined by (xTopLeft, yTopLeft) as top left corner and
     *        (xBottomRight, yBottomRight) as bottom right corner (included!)
     *
     * does boundary checking: adjusts values of xTopLeft, xBottomRight, yTopLeft, yBottomRight to be clipped to fit inside the grid!!
     *
     * \param pGrid source grid
     * \param xTopLeft x coordinate of top left corner of local window
     * \param yTopLeft y coordinate of top left corner of local window
     * \param xBottomRight x coordinate of bottom right corner of local window
     * \param yBottomRight y coordinate of bottom right corner of local window */
   static double ComputeLocalVariance( ArrayGrid<double>* pGrid, int& xTopLeft, int& yTopLeft, int& xBottomRight, int& yBottomRight );

   /** \brief computes the variance of values for a given real-valued grid given a certain central pixel location and a local window size
     *
     * Local mean is computed within this method.
     *
     * WARNING: does not perform boundary checking: moves from (x-(localWindowSize/2)) to (x+(localWindowSize/2))
     *            and from (y-(localWindowSize/2)) to (y+(localWindowSize/2)) without checking if values go out of range!!
     *
     * \param pGrid1 first source grid
     * \param pGrid2 second source grid
     * \param x x coordinate of central pixel
     * \param y y coordinate of central pixel
     * \param localWindowWidth width of local window
     * \param localWindowHeight height of local window
     * \param mean1 mean value of pGrid1,
     * \param mean2 mean value of pGrid2 */
   static double ComputeLocalCovariance( ArrayGrid<double>* pGrid1, ArrayGrid<double>* pGrid2, int& xTopLeft, int& yTopLeft, int& xBottomRight, int& yBottomRight, double mean1, double mean2 );

   static double ComputeLocalKurtosis( ArrayGrid<double>* pGrid, int& xTopLeft, int& yTopLeft, int& xBottomRight, int& yBottomRight, double localMean, double localVariance );

   static double ComputeLocalKurtosis( ArrayGrid<double>* pGrid, int& xTopLeft, int& yTopLeft, int& xBottomRight, int& yBottomRight );
/////////////////////////////////////////
//                                     //
// 4. COMPARISON GRIDS / COEFFICIENTS  //
//                                     //
/////////////////////////////////////////
   static ArrayGrid<double>* ComputeLocalAutoCorrelation( ArrayGrid<double>* pGridIn, int xCenter, int yCenter, int halfWindowSize );

   static double ComputeLocalSquaredDifference( ArrayGrid<double>* pGrid1, int xTop1, int yTop1, int xBottom1, int yBottom1,
                                                ArrayGrid<double>* pGrid2, int xTop2, int yTop2, int xBottom2, int yBottom2 );


   static double ComputeLocalCrossCorrelation( ArrayGrid<double>* pGrid1, int xTop1, int yTop1, int xBottom1, int yBottom1,
                                               ArrayGrid<double>* pGrid2, int xTop2, int yTop2, int xBottom2, int yBottom2 );

   // http://www.mathworks.com/matlabcentral/fileexchange/36538-very-fast-mutual-information-betweentwo-images
   static double ComputeLocalMutualInformation( ArrayGrid<double>* pGrid1, int xTop1, int yTop1, int xBottom1, int yBottom1,
                                                ArrayGrid<double>* pGrid2, int xTop2, int yTop2, int xBottom2, int yBottom2 );

   /** \brief computes grid with squared error values between two grids
     * \param pGrid1 First grid to compare
     * \param pGrid2 Second grid to compare
     * \param printOutput flag if output needs to be printed to console
     * Also writes max squared error, mean squared error and PSNR on standard output if "printOutput==true"*/
   static ArrayGrid<double>* CreateSquaredErrorGrid( ArrayGrid<double>* pGrid1, ArrayGrid<double>* pGrid2, bool printOutput=false );

   /** \brief computes MSE (Mean Squared Error) between two grids
     * \param pGrid1 First grid to compare
     * \param pGrid2 Second grid to compare */
   static double ComputeMSE( ArrayGrid<double>* pGrid1, ArrayGrid<double>* pGrid2 );

   /** \brief computes MSE (Mean Squared Error) between two grids in a given Region of Interest (ROI)
     * \param pGrid1 First grid to compare
     * \param pGrid2 Second grid to compare
     * \param topLeftX x coordinate of the top left corner of the ROI
     * \param topLeftY y coordinate of the top left corner of the ROI
     * \param bottomRightX x coordinate of the bottom right corner of the ROI
     * \param bottomRightY y coordinate of the bottom right corner of the ROI */
   static double ComputeMSEinROI( ArrayGrid<double>* pGrid1, ArrayGrid<double>* pGrid2, int topLeftX, int topLeftY, int bottomRightX, int bottomRightY );

   /** \brief computes PSNR (Peak Signal to Noise Ratio) between two grids
     * \param pGrid1 First grid to compare
     * \param pGrid2 Second grid to compare */
   static double ComputePSNR( ArrayGrid<double>* pGrid1, ArrayGrid<double>* pGrid2 );

   /** \brief computes PSNR (Peak Signal to Noise Ratio) between two grids in a given Region of Interest (ROI)
     * \param pGrid1 First grid to compare
     * \param pGrid2 Second grid to compare
     * \param topLeftX x coordinate of the top left corner of the ROI
     * \param topLeftY y coordinate of the top left corner of the ROI
     * \param bottomRightX x coordinate of the bottom right corner of the ROI
     * \param bottomRightY y coordinate of the bottom right corner of the ROI */
   static double ComputePSNRinROI( ArrayGrid<double>* pGrid1, ArrayGrid<double>* pGrid2, int topLeftX, int topLeftY, int bottomRightX, int bottomRightY );

   /** \brief compares the two grids using SSIM
     * SSIM stands for Structural SIMilarity measure, see http://en.wikipedia.org/wiki/SSIM
     * First published in Z. Wang, A. C. Bovik, H. R. Sheikh and E. P. Simoncelli,
     *                    "Image quality assessment: From error visibility to structural similarity,"
     *                    IEEE Trans. on Image Processing, vol. 13, no. 4, pp. 600-612, Apr. 2004.
     *
     * In order to evaluate the image quality this formula is applied only on the luminance.
     * Resultant SSIM index is a decimal value between -1 and 1
     *
     * \param pGrid1 first grid to compare
     * \param pGrid2 second grid to compare
     * \param localWindowSize size of local window to compute local image statistics used in SSIM
     * \param intensityRange range of the intensities present in the grids to compare*/
   static ArrayGrid<double>* ComputeSSIM( ArrayGrid<double>* pGrid1, ArrayGrid<double>* pGrid2, int localWindowSize, double intensityRange=255.0 );

   /** \brief compares the two grids using SSIM in a given Region of Interest (ROI)
     * SSIM stands for Structural SIMilarity measure, see http://en.wikipedia.org/wiki/SSIM
     * First published in Z. Wang, A. C. Bovik, H. R. Sheikh and E. P. Simoncelli,
     *                    "Image quality assessment: From error visibility to structural similarity,"
     *                    IEEE Trans. on Image Processing, vol. 13, no. 4, pp. 600-612, Apr. 2004.
     *
     * In order to evaluate the image quality this formula is applied only on the luminance.
     * Resulting SSIM index is a decimal value between -1 and 1
     *
     * \param pGrid1 first grid to compare
     * \param pGrid2 second grid to compare
     * \param topLeftX x coordinate of the top left corner of the ROI
     * \param topLeftY y coordinate of the top left corner of the ROI
     * \param bottomRightX x coordinate of the bottom right corner of the ROI
     * \param bottomRightY y coordinate of the bottom right corner of the ROI
     * \param localWindowSize size of local window to compute local image statistics used in SSIM
     * \param intensityRange range of the intensities present in the grids to compare*/
   static ArrayGrid<double>* ComputeSSIMinROI( ArrayGrid<double>* pGrid1, ArrayGrid<double>* pGrid2, int topLeftX, int topLeftY, int bottomRightX, int bottomRightY, int localWindowSize, double intensityRange=255.0 );

   /** \brief standard correlation/colocalization method
     * Ref.: http://support.svi.nl/wiki/ColocalizationTheory
     * \param pGrid1 first grid to check for correlation
     * \param pGrid2 second grid to check for correlation */
   static ArrayGrid<double>* ComputePearsonCorrelation( ArrayGrid<double>* pGrid1, ArrayGrid<double>* pGrid2 );

   /** \brief standard correlation/colocalization method
     * Ref.: http://support.svi.nl/wiki/ColocalizationTheory
     *       http://www.mediacy.com/pdfs/colocfluorprobes.pdf
     * \param pGrid1 first grid to check for overlap
     * \param pGrid2 second grid to check for overlap */
   static ArrayGrid<double>* ComputeMandersOverlap( ArrayGrid<double>* pGrid1, ArrayGrid<double>* pGrid2 );

////////////////////////////////
//                            //
// 5. CONVERT GRID DATA TYPE  //
//                            //
////////////////////////////////

   /** \brief creates a grid where all values of the source grid were casted to integers
     * \param pGrid the source grid */
   static ArrayGrid<int>* CreateIntGrid( ArrayGrid<T>* pGrid );

   /** \brief creates a grid where all values of the source grid were casted to doubles
     * \param pGrid the source grid */
   static ArrayGrid<double>* CreateDoubleGrid( ArrayGrid<T>* pGrid );

   /** \brief creates a grid with the norm of the complex values of the source grid
     * \param pGrid the complex-valued source grid */
   static ArrayGrid<double>* CreateDoubleGridFromComplexGrid( ArrayGrid< std::complex<double> >* pGrid );

   /** \brief creates a grid with as value the negative, i.e., maxvalue - current value at source grid
     * \param pGrid the grid to take negative of */
   static ArrayGrid<double>* NegateGrid( ArrayGrid< double >* pGrid );

   static void NegateGridSelf( ArrayGrid< double >* pGrid, double maxValue );

   /** \brief creates a grid with as value the negative, i.e., maxvalue - current value at source grid
     * \param pGrid the grid to take negative of */
   static ArrayGrid<int>* NegateGrid( ArrayGrid< int >* pGrid, int maxValue );

   static void NegateGridSelf( ArrayGrid< int >* pGrid, int maxValue );

/////////////////////////////
//                         //
// 6. GRID DERIVATIVES     //
//                         //
/////////////////////////////

   /** \brief Gets value of first derivative in x-direction for given position
     * Computes first derivative in x = I(x+1,y) -  I(x-1,y)
     * Does NOT perform boundary checking; be sure you check ranges of x and y yourself
     * \param pGrid source grid
     * \param x x coordinate of where to get value of first derivative
     * \param y y coordinate of where to get value of first derivative */
   static T GetFirstDerivativeX( ArrayGrid<T>* pGrid, int x, int y);

   /** \brief Gets value of first derivative in x-direction for given position
     * Computes first derivative in y = I(x,y+1) -  I(x,y-1)
     * Does NOT perform boundary checking; be sure you check ranges of x and y yourself
     * \param pGrid source grid
     * \param x x coordinate of where to get value of first derivative
     * \param y y coordinate of where to get value of first derivative */
   static T GetFirstDerivativeY( ArrayGrid<T>* pGrid, int x, int y);

   /** \brief Gets value of second derivative in x-direction for given position
     * Computes second derivative in x = - I(x-2,y) + 2 I(x,y) - I(x+2,y)
     * Does NOT perform boundary checking; be sure you check ranges of x and y yourself
     * \param pGrid source grid
     * \param x x coordinate of where to get value of second derivative
     * \param y y coordinate of where to get value of second derivative */
   static T GetSecondDerivativeXX( ArrayGrid<T>* pGrid, int x, int y);

   /** \brief Gets value of mixed derivative in x and y for given position
     * Computes mixed derivative in x and y =     ( I( x+1, y+1 ) - I( x-1, y+1 ) )
     *                                          - ( I( x+1, y-1 ) - I( x-1, y-1 ) )
     * Does NOT perform boundary checking; be sure you check ranges of x and y yourself
     * \param pGrid source grid
     * \param x x coordinate of where to get value of mixed derivative
     * \param y y coordinate of where to get value of mixed derivative */
   static T GetSecondDerivativeXY( ArrayGrid<T>* pGrid, int x, int y);

   /** \brief Gets value of second derivative in y-direction for given position
     * Computes second derivative in y = - I(x,y-2) + 2 I(x,y) - I(x,y+2 )
     * Does NOT perform boundary checking; be sure you check ranges of x and y yourself
     * \param pGrid source grid
     * \param x x coordinate of where to get value of second derivative
     * \param y y coordinate of where to get value of second derivative */
   static T GetSecondDerivativeYY( ArrayGrid<T>* pGrid, int x, int y);

//////////////////////////////////////////
//                                      //
// 7. GRID ROTATION WITHOUT RESAMPLING  //
//                                      //
//////////////////////////////////////////

   /** \brief Rotates the input grid 90 degrees clockwise
     * \param pGrid grid to rotate */
   static ArrayGrid<double>* Rotate90DegreesClockwise( ArrayGrid<double>* pGrid );

   /** \brief Rotates the input grid 90 degrees counter-clockwise
     * \param pGrid grid to rotate */
   static ArrayGrid<double>* Rotate90DegreesCounterClockwise( ArrayGrid<double>* pGrid );

   /** \brief Rotates the input grid 180 degrees
     * \param pGrid grid to rotate */
   static ArrayGrid<double>* Rotate180Degrees( ArrayGrid<double>* pGrid );

///////////////////////////////
//                           //
// 8. SPECIAL TRANSFORMS     //
//                           //
///////////////////////////////


   /** \brief Transforms grid using the log-polar transform
     * Reference: ROBUST IMAGE REGISTRATION USING LOG-POLAR TRANSFORM George Wolberg
     *            http://www.cis.rit.edu/~cnspci/references/wolberg2000.pdf
     *            http://homepages.inf.ed.ac.uk/rbf/CVonline/LOCAL_COPIES/YOUNG2/
     * \param pGrid grid to transform */
   static ArrayGrid<double>* LogPolarTransform( ArrayGrid<double>* pGrid );

/////////////////////////////
//                         //
// 9. GRID THRESHOLDING    //
//                         //
/////////////////////////////

   /** \brief Clips all values in the grid between a desired minimum and maximum value
     * \param pGrid input grid; values are overwritten
     * \param desiredMin desired minimum after clipping
     * \param desiredMax desired maximum after clipping*/
   static void ClipValues( ArrayGrid<T>* pGrid, T desiredMin, T desiredMax );

   /** \brief Sets values with absolute values smaller than threshold to 0; keeps other values
     * \param pGrid input grid to be thresholded
     * \param threshold value of the hard threshold
     * Generates new grid with output that caller should delete */
   static ArrayGrid<double>* HardThreshold( ArrayGrid<double>* pGrid, double threshold );

   /** \brief Sets values with absolute values smaller than threshold to false and others to true
     * \param pGrid input grid to be thresholded
     * \param threshold value of the hard threshold
     * \param thresholdAbsoluteValue if true, we apply the threshold on the absolute value; if false, we apply the threshold directly on the value
     * Generates new grid with output that caller should delete */
   static ArrayGrid<bool>* BinaryThreshold( ArrayGrid<double>* pGrid, double threshold, bool thresholdAbsoluteValue=false );

   /** \brief Sets values with absolute values smaller than threshold to false and others to true
     * \param pGrid input grid to be thresholded
     * \param threshold value of the hard threshold
     * \param thresholdAbsoluteValue if true, we apply the threshold on the absolute value; if false, we apply the threshold directly on the value
     * Generates new grid with output that caller should delete */
   static ArrayGrid<int>* BinaryThresholdInteger( ArrayGrid<double>* pGrid, int threshold );

   ///////////////////////////
   //                       //
   // 10. COMBINE GRIDS     //
   //                       //
   ///////////////////////////

   static void UpdateAverageGrid( ArrayGrid<T>* pAverageGrid, ArrayGrid<T>* pNewGrid, int previousNrOfGridsProcessed );

   /** \brief Averages a vector of grids
     * \param gridVector the set of grids to average */
   static ArrayGrid<T>* AverageGrids( std::vector< ArrayGrid<T>* > gridVector );
};

//===========================================================================================================
//===========================================================================================================

///////////////////////////////
//                           //
// 0. CONSTRUCT / DESTRUCT   //
//                           //
///////////////////////////////

template <class T>
NumberGridTools<T>::NumberGridTools( )
{
}

//------------------------------------------------------------------------------------------

template <class T>
NumberGridTools<T>::~NumberGridTools()
{
}

//------------------------------------------------------------------------------------------

////////////////////////////
//                        //
// 1. GLOBAL DIAGNOSTICS  //
//                        //
////////////////////////////

template <class T>
void NumberGridTools<T>::DiagnoseReal( ArrayGrid<double>* pGrid, std::string fileName )
{
   double tmpMin, tmpMax, meanIntensity, varianceIntensity, kurtosisIntensity;

   GetMinMax( pGrid, tmpMin, tmpMax );

   meanIntensity     = GetGridMean( pGrid );
   varianceIntensity = GetGridVariance( pGrid, meanIntensity );
   kurtosisIntensity = GetGridKurtosis( pGrid, meanIntensity, varianceIntensity );
   std::cout << fileName << " has min = " << tmpMin << " and max = " << tmpMax
             << " meanIntensity = " << meanIntensity
             << " variance = " << varianceIntensity << " and kurtosis = " << kurtosisIntensity
             << std::endl << std::flush;

   int nrNAN = 0;
   int nrINF = 0;
   CountNANandINF( pGrid, nrNAN, nrINF, fileName );
}

//------------------------------------------------------------------------------------------

template <class T>
void NumberGridTools<T>::CopyValues( ArrayGrid<T>* pSourceGrid, ArrayGrid<T>* pDestinationGrid )
{
   assert ( pSourceGrid != 0);
   assert ( pDestinationGrid != 0);
   assert (pSourceGrid->GetHeight() == pDestinationGrid->GetHeight());
   assert (pSourceGrid->GetWidth()  == pDestinationGrid->GetWidth());
   for (int y = 0; y < pSourceGrid->GetHeight(); y++)
   {
      for (int x = 0; x < pSourceGrid->GetWidth(); x ++)
      {
         pDestinationGrid->SetValue( x, y, pSourceGrid->GetValue( x, y ) );
      }
   }
}

//------------------------------------------------------------------------------------------

template <class T>
bool NumberGridTools<T>::CountNANandINF( ArrayGrid<T>* pGrid, int& nrNAN, int& nrINF, std::string ID )
{
   nrNAN = 0;
   nrINF = 0;
   int width = pGrid->GetWidth();
   int height = pGrid->GetHeight();

   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x ++)
      {
#if defined (__WIN32__) || defined(_WIN64)
         if ( _isnan( pGrid->GetValue( x, y ) ) ) {nrNAN++;}
#else
         if (  isnan( pGrid->GetValue( x, y ) ) ) {nrNAN++;}
#endif
         if (  isinf( pGrid->GetValue( x, y ) ) ) {nrINF++;}
      }
   }
   std::cout << ID << " nrNAN = " << nrNAN << " and nrINF = " << nrINF << std::endl << std::flush;
   return true;
}



//------------------------------------------------------------------------------------------

template <class T>
bool NumberGridTools<T>::CleanNANandINF( ArrayGrid<T>* pGrid )
{
   int width = pGrid->GetWidth();
   int height = pGrid->GetHeight();

   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x ++)
      {
#if defined (__WIN32__) || defined(_WIN64)
         if ( _isnan( pGrid->GetValue(x, y) ) ) { pGrid->SetValue(x, y, 0 ); }
#else
         if ( isnan( pGrid->GetValue(x, y) ) ) { pGrid->SetValue(x, y, 0 ); }
#endif
         if (isinf( pGrid->GetValue(x, y) ) ) { pGrid->SetValue(x, y, 255);}
      }
   }
   return true;
}

//------------------------------------------------------------------------------------------

template <class T>
int NumberGridTools<T>::CountZero( ArrayGrid<T>* pGrid )
{
   int nrZero = 0;
   int width = pGrid->GetWidth();
   int height = pGrid->GetHeight();

   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x ++)
      {
         if ( pGrid->GetValue(x, y) == 0 ) {nrZero++;}
      }
   }
   std::cout << " nrZero = " << nrZero << std::endl << std::flush;
   return nrZero;
}

//------------------------------------------------------------------------------------------

////////////////////////////////
//                            //
// 2. GLOBAL GRID STATISTICS  //
//                            //
////////////////////////////////

template <class T>
void NumberGridTools<T>::GetMinMax( ArrayGrid<T>* pGrid, double& mmin, double& mmax, int& xMin, int& yMin, int& xMax, int& yMax )
{
   double tmpMax = -1000000000000.0;
   double tmpMin =  1000000000000.0;

   int width = pGrid->GetWidth();
   int height = pGrid->GetHeight();

   double tmpValue = 0.0;
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x ++)
      {
         tmpValue = static_cast<double>(pGrid->GetValue(x, y));

         if ( tmpValue > tmpMax )
         {
            tmpMax = tmpValue;
            xMax = x;
            yMax = y;
         }
         if ( tmpValue < tmpMin )
         {
            tmpMin = tmpValue;
            xMin = x;
            yMin = y;
         }

         #ifdef CHECK_INF_OR_NAN_VALUES
            if (isinf(tmpValue) )
            {
               std::cout << "Array is inf at (" << x << ", " << y << ")" << std::endl << std::flush;
            }
#if defined (__WIN32__) || defined(_WIN64)
            if ( _isnan( tmpValue ) )
#else
            if (isnan(tmpValue) )
#endif
            {
               std::cout << "Array is nan at (" << x << ", " << y << ")" << std::endl << std::flush;
            }
         #endif
      }
   }
   mmax = tmpMax;
   mmin = tmpMin;
}

//------------------------------------------------------------------------------------------

template <class T>
void NumberGridTools<T>::GetMinMax( ArrayGrid<T>* pGrid, double& mmin, double& mmax )
{
   int xMin, yMin, xMax, yMax;
   GetMinMax( pGrid, mmin, mmax, xMin, yMin, xMax, yMax );
}

//------------------------------------------------------------------------------------------

template <class T>
void NumberGridTools<T>::GetMin( ArrayGrid<T>* pGrid, double& mmin, int& xMin, int& yMin)
{
   double mmax;
   int xMax, yMax;
   GetMinMax( pGrid, mmin, mmax, xMin, yMin, xMax, yMax );
}

//------------------------------------------------------------------------------------------

template <class T>
void NumberGridTools<T>::GetMax( ArrayGrid<T>* pGrid, double& mmax, int& xMax, int& yMax)
{
   double mmin;
   int xMin, yMin;
   GetMinMax( pGrid, mmin, mmax, xMin, yMin, xMax, yMax );
}

//------------------------------------------------------------------------------------------

template <class T>
double NumberGridTools<T>::GetAbsMax( ArrayGrid<T>* pGrid )
{
   double mmax = -1.0;

   for (int y = 0; y < pGrid->GetHeight(); y++)
   {
      for (int x = 0; x < pGrid->GetWidth(); x ++)
      {
         double tmpValue = fabs( static_cast<double>( pGrid->GetValue(x, y)) );
         if ( tmpValue > mmax )
         {
            mmax = tmpValue;
         }
      }
   }
   return mmax;
}

//----------------------------------------------------------------------------------

template <class T>
T NumberGridTools<T>::GetGridIntegral( ArrayGrid<T>* pGrid )
{
   T totalIntensity = 0.0;
   for (int y = 0; y < pGrid->GetHeight(); y++)
   {
      for (int x = 0; x < pGrid->GetWidth(); x ++)
      {
         totalIntensity += pGrid->GetValue(x, y);
      }
   }
   return totalIntensity;
}

//----------------------------------------------------------------------------------

template <class T>
double NumberGridTools<T>::GetSquaredNorm( ArrayGrid<double>* pGrid )
{
   T totalIntensity = 0.0;
   for (int y = 0; y < pGrid->GetHeight(); y++)
   {
      for (int x = 0; x < pGrid->GetWidth(); x ++)
      {
         totalIntensity += ( pGrid->GetValue(x, y) *  pGrid->GetValue(x, y));
      }
   }
   return totalIntensity;
}

//----------------------------------------------------------------------------------

template <class T>
double NumberGridTools<T>::GetSquaredNorm( ArrayGrid< std::complex<double> >* pGrid )
{
   double totalIntensity = 0.0;
   for (int y = 0; y < pGrid->GetHeight(); y++)
   {
      for (int x = 0; x < pGrid->GetWidth(); x ++)
      {
         totalIntensity += ( std::norm( pGrid->GetValue(x, y) ) );
      }
   }
   return totalIntensity;
}

//----------------------------------------------------------------------------------

template <class T>
T NumberGridTools<T>::GetGridMean( ArrayGrid<T>* pGrid )
{
   T totalIntensity = GetGridIntegral( pGrid );
   double nrPixels = (double)( pGrid->GetHeight() * pGrid->GetWidth());
   return (totalIntensity / nrPixels );
}

//----------------------------------------------------------------------------------

template <class T>
T NumberGridTools<T>::GetGridVariance( ArrayGrid<T>* pGrid, T gridMean)
{
   T totalIntensity = 0.0;
   for (int y = 0; y < pGrid->GetHeight(); y++)
   {
      for (int x = 0; x < pGrid->GetWidth(); x ++)
      {
         T ttt = pGrid->GetValue(x, y) - gridMean;
         totalIntensity += (ttt * ttt);
      }
   }
   return (totalIntensity / (pGrid->GetHeight() * pGrid->GetWidth() - 1) );
}

//----------------------------------------------------------------------------------

template <class T>
T NumberGridTools<T>::GetGridKurtosis( ArrayGrid<T>* pGrid, T gridMean, T gridVariance )
{
   T totalNumerator = 0.0;

   T nrSamples = (T)( pGrid->GetHeight() * pGrid->GetWidth() );

   for (int y = 0; y < pGrid->GetHeight(); y++)
   {
      for (int x = 0; x < pGrid->GetWidth(); x ++)
      {
         T ttt = pGrid->GetValue(x, y) - gridMean;
         totalNumerator += (ttt * ttt * ttt * ttt);
      }
   }
   totalNumerator /= nrSamples;

   return ( ( totalNumerator / (gridVariance * gridVariance)) - 3.0 );
}

//----------------------------------------------------------------------------------

template <class T>
T NumberGridTools<T>::GetGridKurtosis( ArrayGrid<T>* pGrid )
{
   T totalNumerator = 0.0;

   double nrSamples = (double)( pGrid->GetHeight() * pGrid->GetWidth() );

   T myMean     = GetGridMean( pGrid );
   T myVariance = GetGridVariance( pGrid, myMean );

   return GetGridKurtosis( pGrid, myMean, myVariance );
}

//----------------------------------------------------------------------------------

template <class T>
void NumberGridTools<T>::RescaleGrid( ArrayGrid<T>* pGrid, T desiredMin, T desiredMax )
{
   double currentMin;
   double currentMax;
   GetMinMax( pGrid, currentMin, currentMax );

   for (int y = 0; y < pGrid->GetHeight(); y++)
   {
      for (int x = 0; x < pGrid->GetWidth(); x ++)
      {
         double normalizedValue = ((double)(pGrid->GetValue(x, y)) - currentMin) / (currentMax - currentMin);
         double rescaledValue = normalizedValue * (desiredMax -desiredMin) + desiredMin;
         pGrid->SetValue(x, y, rescaledValue );
      }
   }
}

//----------------------------------------------------------------------------------

template <class T>
std::vector< common::IntensityPoint > ProjectGridOnX( ArrayGrid<T>* pGrid, int xTopLeft, int yTopLeft, int xBottomRight, int yBottomRight )
{
   int height = pGrid->GetHeight();
   int width  = pGrid->GetWidth();

   common::MathUtils::ClipValue( xTopLeft,     0, width );     common::MathUtils::ClipValue( yTopLeft,     0, height );
   common::MathUtils::ClipValue( xBottomRight, 0, width );     common::MathUtils::ClipValue( yBottomRight, 0, height );

   std::vector< common::IntensityPoint > vProjectionRoiY;

   for (int x = xTopLeft; x < xBottomRight; x++ )
   {
      double tmpTotal = 0.0;
      for (int y = yTopLeft; y < yBottomRight; y++ )
      {
         tmpTotal += pGrid->GetValue( x, y );
      }
      common::IntensityPoint pt;
      pt.x = x;
      pt.y = (yTopLeft + yBottomRight) / 2;
      pt.intensity = ( tmpTotal / ( yBottomRight - yTopLeft ) );
      vProjectionRoiY.push_back( pt );
   }

   return vProjectionRoiY;
}

//----------------------------------------------------------------------------------

template <class T>
std::vector< common::IntensityPoint > NumberGridTools<T>::ProjectGridOnX( ArrayGrid<T>* pGrid )
{
   return ProjectGridOnX( pGrid, 0, 0, pGrid->GetWidth(), pGrid->GetHeight() );
}

//----------------------------------------------------------------------------------

template <class T>
std::vector< common::IntensityPoint > NumberGridTools<T>::ProjectGridOnY( ArrayGrid<T>* pGrid, int xTopLeft, int yTopLeft, int xBottomRight, int yBottomRight )
{
   int height = pGrid->GetHeight();
   int width  = pGrid->GetWidth();

   common::MathUtils::ClipValue( xTopLeft,     0, width );     common::MathUtils::ClipValue( yTopLeft,     0, height );
   common::MathUtils::ClipValue( xBottomRight, 0, width );     common::MathUtils::ClipValue( yBottomRight, 0, height );

   std::vector< common::IntensityPoint > vProjectionRoiX;

   for (int y = yTopLeft; y < yBottomRight; y++ )
   {
      double tmpTotal = 0.0;
      for (int x = xTopLeft; x < xBottomRight; x++ )
      {
         tmpTotal += pGrid->GetValue( x, y );
      }
      common::IntensityPoint pt;
      pt.x = (xTopLeft + xBottomRight) / 2;
      pt.y = y;
      pt.intensity = ( tmpTotal / ( xBottomRight - xTopLeft ) );
      vProjectionRoiX.push_back( pt );
   }

   return vProjectionRoiX;
}

//----------------------------------------------------------------------------------

template <class T>
std::vector< common::IntensityPoint > NumberGridTools<T>::ProjectGridOnY( ArrayGrid<T>* pGrid )
{
   return ProjectGridOnY( pGrid, 0, 0, pGrid->GetWidth(), pGrid->GetHeight() );
}

//----------------------------------------------------------------------------------

//////////////////////////////////////
//                                  //
// 3. LOCAL WINDOW GRID STATISTICS  //
//                                  //
//////////////////////////////////////

template <class T>
T NumberGridTools<T>::GetLocalMinimum( ArrayGrid<T>* pGrid, int x, int y, int localWindowWidth, int localWindowHeight )
{
   int localWindowHalfWidth = localWindowWidth / 2;
   int localWindowHalfHeight = localWindowHeight / 2;
   T tmpMin = pGrid->GetValue(x, y);

   for (int dy = -localWindowHalfHeight; dy <= localWindowHalfHeight; dy++)
   {
      for (int dx = -localWindowHalfWidth; dx <= localWindowHalfWidth; dx++)
      {
         if ( pGrid->GetValue( x + dx, y + dy ) < tmpMin ) { tmpMin = pGrid->GetValue( x + dx, y + dy ); }
      }
   }
   return tmpMin;
}

//----------------------------------------------------------------------------------

template <class T>
T NumberGridTools<T>::GetLocalMaximum( ArrayGrid<T>* pGrid, int x, int y, int localWindowWidth, int localWindowHeight )
{
   int localWindowHalfWidth = localWindowWidth / 2;
   int localWindowHalfHeight = localWindowHeight / 2;
   T tmpMax = pGrid->GetValue(x, y);

   for (int dy = -localWindowHalfHeight; dy <= localWindowHalfHeight; dy++)
   {
      for (int dx = -localWindowHalfWidth; dx <= localWindowHalfWidth; dx++)
      {
         if ( pGrid->GetValue( x + dx, y + dy ) > tmpMax ) { tmpMax = pGrid->GetValue( x + dx, y + dy ); }
      }
   }
   return tmpMax;
}

//----------------------------------------------------------------------------------

template <class T>
T NumberGridTools<T>::GetLocalAbsMaximum( ArrayGrid<int>* pGrid, int x, int y, int localWindowWidth, int localWindowHeight )
{
   int localWindowHalfWidth = localWindowWidth / 2;
   int localWindowHalfHeight = localWindowHeight / 2;
   T tmpMax = pGrid->GetValue(x, y);

   for (int dy = -localWindowHalfHeight; dy <= localWindowHalfHeight; dy++)
   {
      for (int dx = -localWindowHalfWidth; dx <= localWindowHalfWidth; dx++)
      {
         if ( abs(pGrid->GetValue( x + dx, y + dy ) ) > tmpMax ) { tmpMax = abs( pGrid->GetValue( x + dx, y + dy ) ); }
      }
   }
   return tmpMax;
}

//----------------------------------------------------------------------------------

template <class T>
T NumberGridTools<T>::GetLocalAbsMaximum( ArrayGrid<float>* pGrid, int x, int y, int localWindowWidth, int localWindowHeight )
{
   int localWindowHalfWidth = localWindowWidth / 2;
   int localWindowHalfHeight = localWindowHeight / 2;
   T tmpMax = pGrid->GetValue(x, y);

   for (int dy = -localWindowHalfHeight; dy <= localWindowHalfHeight; dy++)
   {
      for (int dx = -localWindowHalfWidth; dx <= localWindowHalfWidth; dx++)
      {
         if ( fabs(pGrid->GetValue( x + dx, y + dy ) ) > tmpMax ) { tmpMax = fabs( pGrid->GetValue( x + dx, y + dy ) ); }
      }
   }
   return tmpMax;
}

//----------------------------------------------------------------------------------

template <class T>
T NumberGridTools<T>::GetLocalAbsMaximum( ArrayGrid<double>* pGrid, int x, int y, int localWindowWidth, int localWindowHeight )
{
   int localWindowHalfWidth = localWindowWidth / 2;
   int localWindowHalfHeight = localWindowHeight / 2;
   T tmpMax = pGrid->GetValue(x, y);

   for (int dy = -localWindowHalfHeight; dy <= localWindowHalfHeight; dy++)
   {
      for (int dx = -localWindowHalfWidth; dx <= localWindowHalfWidth; dx++)
      {
         if ( fabs( pGrid->GetValue( x + dx, y + dy ) ) > tmpMax) { tmpMax = fabs( pGrid->GetValue( x + dx, y + dy ) ); }
      }
   }
   return tmpMax;
}

//----------------------------------------------------------------------------------

template <class T>
T NumberGridTools<T>::ComputeLocalMean( ArrayGrid<T>* pGrid, int& xTopLeft, int& yTopLeft, int& xBottomRight, int& yBottomRight )
{
   T tmpMean = 0.0;

   xTopLeft     = common::MathUtils::ClipValue( xTopLeft,     0, pGrid->GetWidth()-1 );
   xBottomRight = common::MathUtils::ClipValue( xBottomRight, 0, pGrid->GetWidth()-1 );
   yTopLeft     = common::MathUtils::ClipValue( yTopLeft,     0, pGrid->GetHeight()-1 );
   yBottomRight = common::MathUtils::ClipValue( yBottomRight, 0, pGrid->GetHeight()-1 );

   for (int yy = yTopLeft; yy <= yBottomRight; yy++)
   {
      for (int xx = xTopLeft; xx <= xBottomRight; xx++)
      {
         tmpMean += pGrid->GetValue( xx, yy );
      }
   }
   return ( tmpMean / (double)( ( xBottomRight - xTopLeft + 1 ) * ( yBottomRight - yTopLeft + 1 ) ) );
}

//----------------------------------------------------------------------------------

template <class T>
double NumberGridTools<T>::ComputeLocalMean( ArrayGrid<double>* pGrid, common::RectangularROI<int> rroi )
{
   int xTopLeft = rroi.GetTopLeftCorner().x();
   int yTopLeft = rroi.GetTopLeftCorner().y();
   int xBottomRight = rroi.GetBottomRightCorner().x();
   int yBottomRight = rroi.GetBottomRightCorner().y();
   return ComputeLocalMean( pGrid, xTopLeft, yTopLeft, xBottomRight, yBottomRight );
}

//----------------------------------------------------------------------------------

template <class T>
double NumberGridTools<T>::ComputeLocalVariance( ArrayGrid<double>* pGrid, common::RectangularROI<int> rroi, double localMean )
{
   int xTopLeft = rroi.GetTopLeftCorner().x();
   int yTopLeft = rroi.GetTopLeftCorner().y();
   int xBottomRight = rroi.GetBottomRightCorner().x();
   int yBottomRight = rroi.GetBottomRightCorner().y();
   return ComputeLocalVariance( pGrid, xTopLeft, yTopLeft, xBottomRight, yBottomRight, localMean );
}

//----------------------------------------------------------------------------------

template <class T>
T NumberGridTools<T>::ComputeLocalAbsoluteMean( ArrayGrid<T>* pGrid, int& xTopLeft, int& yTopLeft, int& xBottomRight, int& yBottomRight )
{
   T tmpMean = 0.0;

   xTopLeft     = common::MathUtils::ClipValue( xTopLeft,     0, pGrid->GetWidth()-1 );
   xBottomRight = common::MathUtils::ClipValue( xBottomRight, 0, pGrid->GetWidth()-1 );
   yTopLeft = common::MathUtils::ClipValue( yTopLeft,     0, pGrid->GetHeight()-1 );
   yBottomRight = common::MathUtils::ClipValue( yBottomRight, 0, pGrid->GetHeight()-1 );

   for (int yy = yTopLeft; yy <= yBottomRight; yy++)
   {
      for (int xx = xTopLeft; xx <= xBottomRight; xx++)
      {
         tmpMean += fabs( pGrid->GetValue( xx, yy ) );
      }
   }
   return ( tmpMean / (double)( ( xBottomRight - xTopLeft + 1 ) * ( yBottomRight - yTopLeft + 1 ) ) );
}

//----------------------------------------------------------------------------------

template <class T>
double NumberGridTools<T>::ComputeLocalVariance( ArrayGrid<double>* pGrid, int& xTopLeft, int& yTopLeft, int& xBottomRight, int& yBottomRight, double thisMean)
{
   xTopLeft     = common::MathUtils::ClipValue( xTopLeft,     0, pGrid->GetWidth()-1 );
   xBottomRight = common::MathUtils::ClipValue( xBottomRight, 0, pGrid->GetWidth()-1 );
   yTopLeft     = common::MathUtils::ClipValue( yTopLeft,     0, pGrid->GetHeight()-1 );
   yBottomRight = common::MathUtils::ClipValue( yBottomRight, 0, pGrid->GetHeight()-1 );

   double tmpVariance = 0.0;
   for (int yy = yTopLeft; yy <= yBottomRight; yy++)
   {
      for (int xx = xTopLeft; xx <= xBottomRight; xx++)
      {
         double ttt = pGrid->GetValue( xx, yy ) - thisMean;
         tmpVariance += (ttt * ttt);
      }
   }
   return ( tmpVariance / (double)( ( xBottomRight - xTopLeft + 1 ) * ( yBottomRight - yTopLeft + 1 ) - 1 ) );
}

//----------------------------------------------------------------------------------

template <class T>
double NumberGridTools<T>::ComputeLocalVariance( ArrayGrid<double>* pGrid, int& xTopLeft, int& yTopLeft, int& xBottomRight, int& yBottomRight )
{
   xTopLeft     = common::MathUtils::ClipValue( xTopLeft,     0, pGrid->GetWidth()-1 );
   xBottomRight = common::MathUtils::ClipValue( xBottomRight, 0, pGrid->GetWidth()-1 );
   yTopLeft     = common::MathUtils::ClipValue( yTopLeft,     0, pGrid->GetHeight()-1 );
   yBottomRight = common::MathUtils::ClipValue( yBottomRight, 0, pGrid->GetHeight()-1 );

   double tmpMean = 0.0;
   for (int yy = yTopLeft; yy <= yBottomRight; yy++)
   {
      for (int xx = xTopLeft; xx <= xBottomRight; xx++)
      {
         tmpMean += pGrid->GetValue( xx, yy );
      }
   }

   double myDenominator = (double)( ( xBottomRight - xTopLeft + 1 ) * ( yBottomRight - yTopLeft + 1 ) );

   tmpMean /= myDenominator;

   double tmpVariance = 0.0;
   for (int yy = yTopLeft; yy <= yBottomRight; yy++)
   {
      for (int xx = xTopLeft; xx <= xBottomRight; xx++)
      {
         double ttt = pGrid->GetValue( xx, yy ) - tmpMean;
         tmpVariance += (ttt * ttt);
      }
   }
   return ( tmpVariance / (double)( myDenominator - 1 ) );
}

//----------------------------------------------------------------------------------

template <class T>
double NumberGridTools<T>::ComputeLocalCovariance( ArrayGrid<double>* pGrid1, ArrayGrid<double>* pGrid2, int& xTopLeft, int& yTopLeft, int& xBottomRight, int& yBottomRight, double grid1Mean, double grid2Mean )
{
   assert( pGrid1->GetWidth() == pGrid2->GetWidth() );
   assert( pGrid1->GetHeight() == pGrid2->GetHeight() );

   xTopLeft     = common::MathUtils::ClipValue( xTopLeft,     0, pGrid1->GetWidth()  - 1 );
   xBottomRight = common::MathUtils::ClipValue( xBottomRight, 0, pGrid1->GetWidth()  - 1 );
   yTopLeft     = common::MathUtils::ClipValue( yTopLeft,     0, pGrid1->GetHeight() - 1 );
   yBottomRight = common::MathUtils::ClipValue( yBottomRight, 0, pGrid1->GetHeight() - 1 );

   int localWindowWidth  = xBottomRight - xTopLeft + 1;
   int localWindowHeight = yBottomRight - yTopLeft + 1;

   double tmpCovariance = 0.0;

   for (int y = yTopLeft; y <= yBottomRight; y++)
   {
      for (int x = xTopLeft; x <= xBottomRight; x++)
      {
         tmpCovariance += ( (pGrid1->GetValue( x, y ) - grid1Mean ) * ( pGrid2->GetValue( x, y ) - grid2Mean ) );
      }
   }
   return (tmpCovariance / (double)( localWindowWidth * localWindowHeight - 1 ) );
}

//----------------------------------------------------------------------------------

template <class T>
double NumberGridTools<T>::ComputeLocalKurtosis( ArrayGrid<double>* pGrid, int& xTopLeft, int& yTopLeft, int& xBottomRight, int& yBottomRight, double localMean, double localVariance )
{
   xTopLeft     = common::MathUtils::ClipValue( xTopLeft,     0, pGrid->GetWidth()  - 1 );
   xBottomRight = common::MathUtils::ClipValue( xBottomRight, 0, pGrid->GetWidth()  - 1 );
   yTopLeft     = common::MathUtils::ClipValue( yTopLeft,     0, pGrid->GetHeight() - 1 );
   yBottomRight = common::MathUtils::ClipValue( yBottomRight, 0, pGrid->GetHeight() - 1 );

   T totalNumerator = 0.0;

   T nrSamples = (T)( ( xBottomRight - xTopLeft ) * ( yBottomRight - yTopLeft ) );

   for (int y = yTopLeft; y <= yBottomRight; y++)
   {
      for (int x = xTopLeft; x < xBottomRight; x ++)
      {
         T ttt = pGrid->GetValue(x, y) - localMean;
         totalNumerator += (ttt * ttt * ttt * ttt);
      }
   }
   totalNumerator /= nrSamples;

   return ( ( totalNumerator / (localVariance * localVariance)) - 3.0 );
}

//----------------------------------------------------------------------------------

template <class T>
double NumberGridTools<T>::ComputeLocalKurtosis( ArrayGrid<double>* pGrid, int& xTopLeft, int& yTopLeft, int& xBottomRight, int& yBottomRight )
{
   xTopLeft     = common::MathUtils::ClipValue( xTopLeft,     0, pGrid->GetWidth()  - 1 );
   xBottomRight = common::MathUtils::ClipValue( xBottomRight, 0, pGrid->GetWidth()  - 1 );
   yTopLeft     = common::MathUtils::ClipValue( yTopLeft,     0, pGrid->GetHeight() - 1 );
   yBottomRight = common::MathUtils::ClipValue( yBottomRight, 0, pGrid->GetHeight() - 1 );
   double localMean     = ComputeLocalMean(     pGrid, xTopLeft, yTopLeft, xBottomRight, yBottomRight );
   double localVariance = ComputeLocalVariance( pGrid, xTopLeft, yTopLeft, xBottomRight, yBottomRight, localMean );
   double totalNumerator = 0.0;

   double nrSamples = (double)( ( xBottomRight - xTopLeft ) * ( yBottomRight - yTopLeft ) );

   for (int y = yTopLeft; y <= yBottomRight; y++)
   {
      for (int x = xTopLeft; x < xBottomRight; x ++)
      {
         T ttt = pGrid->GetValue(x, y) - localMean;
         totalNumerator += (ttt * ttt * ttt * ttt);
      }
   }
   totalNumerator /= nrSamples;

   return ( ( totalNumerator / (localVariance * localVariance)) - 3.0 );
}

//----------------------------------------------------------------------------------

/////////////////////////////////////////
//                                     //
// 4. COMPARISON GRIDS / COEFFICIENTS  //
//                                     //
/////////////////////////////////////////


template <class T>
ArrayGrid<double>* NumberGridTools<T>::ComputeLocalAutoCorrelation( ArrayGrid<double>* pGridIn, int xCenterRef, int yCenterRef, int halfWindowSize )
{
    double autoCorrelation;
    double gridMean = NumberGridTools<double>::GetGridMean( pGridIn );
    double gridVariance = NumberGridTools<double>::GetGridVariance( pGridIn, gridMean);
    double normFactor = ( ( 2 * halfWindowSize + 1 ) * ( 2 * halfWindowSize + 1 ) * gridVariance );

    ArrayGrid<double>* pGridOut = new ArrayGrid<double>( 2 * halfWindowSize + 1, 2 * halfWindowSize + 1 );

    for (int yCenterMov = yCenterRef - halfWindowSize; yCenterMov <= yCenterRef + halfWindowSize; yCenterMov++ )
    {
        for (int xCenterMov = xCenterRef - halfWindowSize; xCenterMov <= xCenterRef + halfWindowSize; xCenterMov++ )
        {
            autoCorrelation = 0.0;
            for (int y0 = yCenterMov - halfWindowSize; y0 <= yCenterMov + halfWindowSize; y0++ )
            {
                for (int x0 = xCenterMov - halfWindowSize; x0 <= xCenterMov + halfWindowSize; x0++ )
                {
                    autoCorrelation += ( pGridIn->GetValue(x0 + xCenterRef - xCenterMov, y0 + yCenterRef - yCenterMov ) - gridMean ) * ( pGridIn->GetValue( x0, y0 ) - gridMean );
                }
            }
            autoCorrelation /= normFactor;
            pGridOut->SetValue( xCenterMov - xCenterRef + halfWindowSize, yCenterMov - yCenterRef + halfWindowSize, autoCorrelation );
        }
    }
    return pGridOut;
}


//----------------------------------------------------------------------------------

template <class T>
double NumberGridTools<T>::ComputeLocalSquaredDifference( ArrayGrid<double>* pGrid1, int xTop1, int yTop1, int xBottom1, int yBottom1,
                                                          ArrayGrid<double>* pGrid2, int xTop2, int yTop2, int xBottom2, int yBottom2 )
{
    assert( xBottom1 > xTop1 );  assert( xBottom2 > xTop2 );   int width  = xBottom1 - xTop1; assert( (xBottom2 - xTop2 ) == width );
    assert( yBottom1 > yTop1 );  assert( yBottom2 > yTop2 );   int height = yBottom1 - yTop1; assert( (yBottom2 - yTop2 ) == height );

    double meanSquaredDifference = 0;

    for (int dy = 0; dy <= height; dy++ )
    {
        for (int dx = 0; dx <= width; dx++ )
        {
            double difference = ( pGrid1->GetValue( xTop1 + dx, yTop1 + dy ) - pGrid2->GetValue( xTop2 + dx, yTop2 + dy ) );
            meanSquaredDifference += ( difference * difference );
        }
    }
    meanSquaredDifference /= ( width * height );

    return meanSquaredDifference;

}

//----------------------------------------------------------------------------------

template <class T>
double NumberGridTools<T>::ComputeLocalCrossCorrelation( ArrayGrid<double>* pGrid1, int xTop1, int yTop1, int xBottom1, int yBottom1,
                                                         ArrayGrid<double>* pGrid2, int xTop2, int yTop2, int xBottom2, int yBottom2 )
{
    assert( xBottom1 > xTop1 );  assert( xBottom2 > xTop2 );   int width  = xBottom1 - xTop1; assert( (xBottom2 - xTop2 ) == width );
    assert( yBottom1 > yTop1 );  assert( yBottom2 > yTop2 );   int height = yBottom1 - yTop1; assert( (yBottom2 - yTop2 ) == height );

    double mean1 = ComputeLocalMean( pGrid1, xTop1, yTop1, xBottom1, yBottom1 );
    double mean2 = ComputeLocalMean( pGrid2, xTop2, yTop2, xBottom2, yBottom2 );
    double sigma1 = sqrt( ComputeLocalVariance( pGrid1, xTop1, yTop1, xBottom1, yBottom1, mean1) );
    double sigma2 = sqrt( ComputeLocalVariance( pGrid2, xTop2, yTop2, xBottom2, yBottom2, mean2) );

    double crossCorrelation = 0;

    for (int dy = 0; dy <= height; dy++ )
    {
        for (int dx = 0; dx <= width; dx++ )
        {
            crossCorrelation += ( pGrid1->GetValue( xTop1 + dx, yTop1 + dy ) - mean1 ) * ( pGrid2->GetValue( xTop2 + dx, yTop2 + dy ) - mean2 );
        }
    }
    crossCorrelation /= ( width * height * sigma1 * sigma2 );

    return crossCorrelation;
}

//----------------------------------------------------------------------------------

template <class T>
double NumberGridTools<T>::ComputeLocalMutualInformation( ArrayGrid<double>* pGrid1, int xTop1, int yTop1, int xBottom1, int yBottom1,
                                                          ArrayGrid<double>* pGrid2, int xTop2, int yTop2, int xBottom2, int yBottom2 )
{
    assert( xBottom1 > xTop1 );  assert( xBottom2 > xTop2 );   int width  = xBottom1 - xTop1; assert( (xBottom2 - xTop2 ) == width );
    assert( yBottom1 > yTop1 );  assert( yBottom2 > yTop2 );   int height = yBottom1 - yTop1; assert( (yBottom2 - yTop2 ) == height );

    histogram::JointHistogram* pJH = new histogram::JointHistogram( pGrid1, xTop1, yTop1, xBottom1, yBottom1,
                                                                    pGrid2, xTop2, yTop2, xBottom2, yBottom2 );
    histogram::FloatHistogram* pdf1 = pJH->GetMarginalPDF1();
    histogram::FloatHistogram* pdf2 = pJH->GetMarginalPDF2();

    double mutualInformation = 0;

    //Hx = - sum(x_marg.*log2(x_marg + (x_marg == 0))); % Entropy of X
    int nrBins1 = pdf1->GetNrOfBins();
    double entropy1 = 0;
    for (int i = 0; i < nrBins1; i++)
    {
        double binValue = pdf1->GetBinValue(0,i);
        if (binValue != 0)
        {
            entropy1 -= ( binValue * log2( binValue ) );
        }
    }

    //Hy = - sum(y_marg.*log2(y_marg + (y_marg == 0))); % Entropy of Y
    int nrBins2 = pdf2->GetNrOfBins();
    double entropy2 = 0;
    for (int i = 0; i < nrBins2; i++)
    {
        double binValue = pdf2->GetBinValue(0,i);
        if (binValue != 0)
        {
            entropy2 -= ( binValue * log2( binValue ) );
        }
    }

    //arg_xy2 = hn.*(log2(hn+(hn==0)));
    //h_xy = sum(-arg_xy2(:)); % joint entropy
    double jointEntropy = 0;
    for (int y = 0; y < pJH->GetNrOfVerticalBins(); y++)
    {
        for (int x = 0; x < pJH->GetNrOfHorizontalBins(); x++)
        {
            double binValue = pJH->GetBinValue(0, x, y);
            if (binValue != 0)
            {
                jointEntropy -= ( binValue * log2( binValue ) );
            }
        }
    }

    //M = Hx + Hy - h_xy; % mutual information
    mutualInformation = entropy1 + entropy2 - jointEntropy;

    delete pJH;
    delete pdf1;
    delete pdf2;

    return mutualInformation;
}

//----------------------------------------------------------------------------------

template <class T>
ArrayGrid<double>* NumberGridTools<T>::CreateSquaredErrorGrid( ArrayGrid<double>* pGrid1, ArrayGrid<double>* pGrid2, bool printOutput )
{
   double SSD = 0.0;
   double MSE, PSNR;
   double mmax = 0.0;

   int width = pGrid1->GetWidth();
   int height = pGrid1->GetHeight();
   int nrPixels = width * height;
   bool needInitialisation = true;
   double initialRealValue = 0.0;

   if ((width == pGrid2->GetWidth()) && (height == pGrid2->GetHeight()))
   {
      ArrayGrid<double>* pDifferenceGrid = new ArrayGrid<double>( width, height, needInitialisation, initialRealValue );
      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x ++)
         {
#if defined (__WIN32__) || defined(_WIN64)
            if ( _isnan( pGrid2->GetValue( x, y ) ) )
#else
            if ( isnan( pGrid2->GetValue( x, y ) ) )
#endif
            {
               std::cout << "at (" << x << ", " << y << "), value in grid 2 was nan" << std::endl << std::flush;
            }
            double tmpVal = (double)( pGrid1->GetValue( x, y ) ) - (double)( pGrid2->GetValue( x, y ) );
            double squaredDifference = ( tmpVal * tmpVal );
            if ( squaredDifference > mmax ) { mmax = squaredDifference; }
            SSD += squaredDifference;
            pDifferenceGrid->SetValue( x, y, fabs( tmpVal ) );
         }
      }
      if (printOutput)
      {
         MSE = SSD / (double)( nrPixels );
         PSNR = common::MathUtils::ComputePSNR( MSE );
         std::cout << " max SD is " << mmax << " MSE = " << MSE << " and PSNR = " << PSNR << std::endl << std::flush;
      }
      return pDifferenceGrid;
   }
   else
   {
      std::cerr << "ERROR: cannot compare grids for which dimensions are not equal: (" << width << ", " << height
                << ") >< (" << pGrid2->GetWidth() << ", " << pGrid2->GetHeight() << ")" << std::endl << std::flush;
      return 0;
   }
}

//----------------------------------------------------------------------------------

template <class T>
double NumberGridTools<T>::ComputeMSE( ArrayGrid<double>* pGrid1, ArrayGrid<double>* pGrid2 )
{
   int width = pGrid1->GetWidth();
   int height = pGrid1->GetHeight();
   if ( ( width == pGrid2->GetWidth() ) && ( height == pGrid2->GetHeight() ) )
   {
      double SSD = 0.0;
      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x ++)
         {
            double tmpVal = (double)(pGrid1->GetValue(x, y)) - (double)(pGrid2->GetValue(x, y));
            SSD += (tmpVal * tmpVal);
         }
      }
      return ( SSD / (double)( width * height ) );
   }
   else
   {
      std::cerr << "ERROR: cannot compare grids for which dimensions are not equal: (" << width << ", " << height
                << ") >< (" << pGrid2->GetWidth() << ", " << pGrid2->GetHeight() << ")" << std::endl << std::flush;
      return 0;
   }
}

//----------------------------------------------------------------------------------

template <class T>
double NumberGridTools<T>::ComputeMSEinROI( ArrayGrid<double>* pGrid1, ArrayGrid<double>* pGrid2, int topLeftX, int topLeftY, int bottomRightX, int bottomRightY )
{
   int width = pGrid1->GetWidth();
   int height = pGrid1->GetHeight();
   if ( ( width == pGrid2->GetWidth() ) && ( height == pGrid2->GetHeight() ) )
   {
      if (    (     topLeftX >= 0 ) && (     topLeftX < width ) && (     topLeftY >= 0 ) && ( topLeftY     < height )
           && ( bottomRightX >= 0 ) && ( bottomRightX < width ) && ( bottomRightY >= 0 ) && ( bottomRightY < height )
           && ( bottomRightX > topLeftX) && ( bottomRightY > topLeftY )
         )
      {
         double SSD = 0.0;
         double roiWidth  = bottomRightX - topLeftX + 1;
         double roiHeight = bottomRightY - topLeftY + 1;
         for (int y = topLeftY; y < bottomRightY; y++)
         {
            for (int x = topLeftX; x < bottomRightX; x ++)
            {
               double tmpVal = (double)(pGrid1->GetValue(x, y)) - (double)(pGrid2->GetValue(x, y));
               SSD += (tmpVal * tmpVal);
            }
         }
         return ( SSD / (double)( roiWidth * roiHeight ) );
      }
      else
      {
         std::cerr << "ERROR: invalid corner points (" << topLeftX << ", " << topLeftY << ") and (" << bottomRightX << ", " << bottomRightY
                   << ") for image width " << width << " and height " << height << std::endl << std::flush;
         return 0;
      }
   }
   else
   {
      std::cerr << "ERROR: cannot compare grids for which dimensions are not equal: (" << width << ", " << height
                << ") >< (" << pGrid2->GetWidth() << ", " << pGrid2->GetHeight() << ")" << std::endl << std::flush;
      return 0;
   }
}

//----------------------------------------------------------------------------------

template <class T>
double NumberGridTools<T>::ComputePSNR( ArrayGrid<double>* pGrid1, ArrayGrid<double>* pGrid2 )
{
   if ( ( pGrid1->GetWidth() == pGrid2->GetWidth() ) && ( pGrid1->GetHeight() == pGrid2->GetHeight() ) )
   {
      return common::MathUtils::ComputePSNR( ComputeMSE( pGrid1, pGrid2 ) );
   }
   else
   {
      std::cerr << "ERROR: cannot compare grids for which dimensions are not equal: ("
                << pGrid1->GetWidth() << ", " << pGrid1->GetHeight() << ") >< ("
                << pGrid2->GetWidth() << ", " << pGrid2->GetHeight() << ")"
                << std::endl << std::flush;
      return 0;
   }
}

//----------------------------------------------------------------------------------

template <class T>
double NumberGridTools<T>::ComputePSNRinROI( ArrayGrid<double>* pGrid1, ArrayGrid<double>* pGrid2, int topLeftX, int topLeftY, int bottomRightX, int bottomRightY )
{
   int width = pGrid1->GetWidth();
   int height = pGrid1->GetHeight();
   if ( ( width == pGrid2->GetWidth() ) && ( height == pGrid2->GetHeight() ) )
   {
      if (    (     topLeftX >= 0 ) && (     topLeftX < width ) && (     topLeftY >= 0 ) && ( topLeftY     < height )
           && ( bottomRightX >= 0 ) && ( bottomRightX < width ) && ( bottomRightY >= 0 ) && ( bottomRightY < height )
           && ( bottomRightX > topLeftX) && ( bottomRightY > topLeftY )
         )
      {
         return common::MathUtils::ComputePSNR( ComputeMSE( pGrid1, pGrid2, topLeftX, topLeftY, bottomRightX, bottomRightY ) );
      }
      else
      {
         std::cerr << "ERROR: invalid corner points (" << topLeftX << ", " << topLeftY << ") and (" << bottomRightX << ", " << bottomRightY
                   << ") for image width " << width << " and height " << height << std::endl << std::flush;
         return 0;
      }
   }
   else
   {
      std::cerr << "ERROR: cannot compare grids for which dimensions are not equal: ("
                << pGrid1->GetWidth() << ", " << pGrid1->GetHeight() << ") >< ("
                << pGrid2->GetWidth() << ", " << pGrid2->GetHeight() << ")"
                << std::endl << std::flush;
      return 0;
   }
}

//----------------------------------------------------------------------------------

template <class T>
ArrayGrid<double>* NumberGridTools<T>::ComputeSSIM( ArrayGrid<double>* pGrid1, ArrayGrid<double>* pGrid2, int localWindowSize, double intensityRange )
{
   int width = pGrid1->GetWidth();
   int height = pGrid1->GetHeight();
   bool needInitialisation = true;
   double initialRealValue = 0.0;
   int localWindowHalfSize = localWindowSize / 2;
   double C1 = ( 0.01 * intensityRange ) *  (0.01 * intensityRange );   // stabilizes term with mean; see paper Wang for this value
   double C2 = ( 0.03 * intensityRange ) *  (0.03 * intensityRange );   // stabilizes term with variance; see paper Wang for this value
   ArrayGrid<double>* pSSIMGrid = new ArrayGrid<double>( width, height, needInitialisation, initialRealValue );

   double integratedSSIM = 0.0;

   for (int y = localWindowHalfSize; y < height - localWindowHalfSize; y++)
   {
      for (int x = localWindowHalfSize; x < width - localWindowHalfSize; x++)
      {
         int xTopLeft = x - localWindowHalfSize;
         int yTopLeft = y - localWindowHalfSize;
         int xBottomRight = x + localWindowHalfSize;
         int yBottomRight = y + localWindowHalfSize;
         double localMean1 = ComputeLocalMean( pGrid1, xTopLeft, yTopLeft, xBottomRight, yBottomRight );
         double localMean2 = ComputeLocalMean( pGrid2, xTopLeft, yTopLeft, xBottomRight, yBottomRight );
         double localMean1Squared = localMean1 * localMean1;
         double localMean2Squared = localMean2 * localMean2;
         double localVariance1 = ComputeLocalVariance( pGrid1, xTopLeft, yTopLeft, xBottomRight, yBottomRight, localMean1 );
         double localVariance2 = ComputeLocalVariance( pGrid2, xTopLeft, yTopLeft, xBottomRight, yBottomRight, localMean2 );
         double localCovariance = ComputeLocalCovariance( pGrid1, pGrid2, xTopLeft, yTopLeft, xBottomRight, yBottomRight, localMean1, localMean2 );
         double SSIM =   ( ( 2.0 * localMean1 * localMean2 + C1 ) * ( 2.0 * localCovariance + C2) )
                       / ( ( localMean1Squared + localMean2Squared + C1 ) * ( localVariance1 + localVariance2 + C2 ) );
         pSSIMGrid->SetValue( x, y, SSIM );
         integratedSSIM += SSIM;
      }
   }
   std::cout << "In NumberGridTools::CompareSSIM -> integrated SSIM = " << integratedSSIM << ", Mean = " << integratedSSIM / ( ( height - 2 * localWindowHalfSize ) * ( width - 2 * localWindowHalfSize ) ) << std::endl << std::flush;
   return pSSIMGrid;
}

//----------------------------------------------------------------------------------

template <class T>
ArrayGrid<double>* NumberGridTools<T>::ComputeSSIMinROI( ArrayGrid<double>* pGrid1, ArrayGrid<double>* pGrid2, int topLeftX, int topLeftY, int bottomRightX, int bottomRightY, int localWindowSize, double intensityRange )
{
   int width = pGrid1->GetWidth();
   int height = pGrid1->GetHeight();
   int localWindowHalfSize = localWindowSize / 2;
   if (     (     topLeftX >= localWindowHalfSize ) && (     topLeftX < width  - localWindowHalfSize )
         && (     topLeftY >= localWindowHalfSize ) && (     topLeftY < height - localWindowHalfSize )
         && ( bottomRightX >= localWindowHalfSize ) && ( bottomRightX < width  - localWindowHalfSize )
         && ( bottomRightY >= localWindowHalfSize ) && ( bottomRightY < height - localWindowHalfSize )
         && ( bottomRightX > topLeftX) && ( bottomRightY > topLeftY )
      )
   {
      bool needInitialisation = true;
      double initialRealValue = 0.0;
      double C1 = (0.01 * 255.0) *  (0.01 * 255.0);   // stabilizes term with mean; see paper Wang for this value
      double C2 = (0.03 * 255.0) *  (0.03 * 255.0);   // stabilizes term with variance; see paper Wang for this value
      ArrayGrid<double>* pSSIMGrid = new ArrayGrid<double>( width, height, needInitialisation, initialRealValue );

      double integratedSSIM = 0.0;

      for (int y = topLeftY; y < bottomRightY; y++)
      {
         for (int x = topLeftX; x < bottomRightX; x++)
         {
            double localMean1 = ComputeLocalMean( pGrid1, topLeftX, topLeftY, bottomRightX, bottomRightY );
            double localMean2 = ComputeLocalMean( pGrid2, topLeftX, topLeftY, bottomRightX, bottomRightY );
            double localMean1Squared = localMean1 * localMean1;
            double localMean2Squared = localMean2 * localMean2;
            double localVariance1 = ComputeLocalVariance( pGrid1, topLeftX, topLeftY, bottomRightX, bottomRightY, localMean1 );
            double localVariance2 = ComputeLocalVariance( pGrid2, topLeftX, topLeftY, bottomRightX, bottomRightY, localMean2 );
            double localCovariance = ComputeLocalCovariance( pGrid1, pGrid2, topLeftX, topLeftY, bottomRightX, bottomRightY, localMean1, localMean2 );
            double SSIM =   ( ( 2.0 * localMean1 * localMean2 + C1 ) * ( 2.0 * localCovariance + C2) )
                        / ( ( localMean1Squared + localMean2Squared + C1) * ( localVariance1 + localVariance2 + C2));
            pSSIMGrid->SetValue( x, y, SSIM );
            integratedSSIM += SSIM;
         }
      }
      std::cout << "In NumberGridTools::CompareSSIM -> integrated SSIM = " << integratedSSIM << ", Mean = " << integratedSSIM / ( ( height - 2 * localWindowHalfSize ) * ( width - 2 * localWindowHalfSize ) ) << std::endl << std::flush;
      return pSSIMGrid;
   }
   else
   {
      std::cerr << "ERROR: invalid corner points (" << topLeftX << ", " << topLeftY << ") and (" << bottomRightX << ", " << bottomRightY
                  << ") for image width " << width << " and height " << height << std::endl << std::flush;
      return 0;
   }
}

//----------------------------------------------------------------------------------

template <class T>
ArrayGrid<double>* NumberGridTools<T>::ComputePearsonCorrelation( ArrayGrid<double>* pGrid1, ArrayGrid<double>* pGrid2 )
{
   int width = pGrid1->GetWidth();
   int height = pGrid1->GetHeight();
   bool needInitialisation = true;
   double initialRealValue = 0.0;

   if ((width == pGrid2->GetWidth()) && (height == pGrid2->GetHeight()))
   {
      double mean1 = NumberGridTools<double>::GetGridMean( pGrid1 );
      double mean2 = NumberGridTools<double>::GetGridMean( pGrid2 );
      double myNumerator    = 0.0;
      double myDenominator1 = 0.0;
      double myDenominator2 = 0.0;
      ArrayGrid<double>* pDifferenceGrid = new ArrayGrid<double>( width, height, needInitialisation, initialRealValue );
      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x ++)
         {
            double value1 = (double)(pGrid1->GetValue(x, y));
            double value2 = (double)(pGrid2->GetValue(x, y));
            double tmpValue = (value1 - mean1) * (value2 - mean2);
            myNumerator    += tmpValue;
            myDenominator1 += POWER2( (value1 - mean1) );
            myDenominator2 += POWER2( (value2 - mean2) );
            pDifferenceGrid->SetValue( x, y, tmpValue );  // temporary store value
         }
      }
      double myDenominator = sqrt(myDenominator1 * myDenominator2);
      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x ++)
         {
            pDifferenceGrid->DivideValue( x, y, myDenominator);
         }
      }
      std::cout << " Pearson correlation coefficient is " << (myNumerator / myDenominator) << std::endl << std::flush;
      return pDifferenceGrid;
   }
   else
   {
      std::cerr << "ERROR: cannot compare grids for which dimensions are not equal: (" << width << ", " << height
                << ") >< (" << pGrid2->GetWidth() << ", " << pGrid2->GetHeight() << ")" << std::endl << std::flush;
      return 0;
   }
}

//----------------------------------------------------------------------------------

template <class T>
ArrayGrid<double>* NumberGridTools<T>::ComputeMandersOverlap( ArrayGrid<double>* pGrid1, ArrayGrid<double>* pGrid2 )
{
   int width = pGrid1->GetWidth();
   int height = pGrid1->GetHeight();
   bool needInitialisation = true;
   double initialRealValue = 0.0;

   if ((width == pGrid2->GetWidth()) && (height == pGrid2->GetHeight()))
   {
      double myNumerator    = 0.0;
      double myDenominator1 = 0.0;
      double myDenominator2 = 0.0;
      ArrayGrid<double>* pDifferenceGrid = new ArrayGrid<double>( width, height, needInitialisation, initialRealValue );
      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x ++)
         {
            double value1 = (double)(pGrid1->GetValue(x, y));
            double value2 = (double)(pGrid2->GetValue(x, y));
            double tmpValue = value1 * value2;
            myNumerator    += tmpValue;
            myDenominator1 += POWER2( value1 );
            myDenominator2 += POWER2( value2 );
            pDifferenceGrid->SetValue( x, y, tmpValue );
         }
      }
      double myDenominator = sqrt(myDenominator1 * myDenominator2);
      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x ++)
         {
            pDifferenceGrid->DivideValue( x, y, myDenominator);
         }
      }
      std::cout << " Manders Overlap coefficient is " << (myNumerator / myDenominator) << std::endl << std::flush;
      return pDifferenceGrid;
   }
   else
   {
      std::cerr << "ERROR: cannot compare grids for which dimensions are not equal: (" << width << ", " << height
                << ") >< (" << pGrid2->GetWidth() << ", " << pGrid2->GetHeight() << ")" << std::endl << std::flush;
      return 0;
   }
}

//----------------------------------------------------------------------------------

////////////////////////////////
//                            //
// 5. CONVERT GRID DATA TYPE  //
//                            //
////////////////////////////////

template <class T>
ArrayGrid<int>* NumberGridTools<T>::CreateIntGrid( ArrayGrid<T>* pGrid )
{
   int width = pGrid->GetWidth();
   int height = pGrid->GetHeight();
   ArrayGrid<int>* pIntGrid = new ArrayGrid<int>( width, height );  // NOT initialized at construction
   for (int y = 0; y < height; y ++)
   {
      for (int x = 0; x < width; x ++)
      {
         pIntGrid->SetValue( x, y, static_cast<int>( pGrid->GetValue(x, y) ) );
      }
   }
   return pIntGrid;
}

//----------------------------------------------------------------------------------

template <class T>
ArrayGrid<double>* NumberGridTools<T>::CreateDoubleGrid( ArrayGrid<T>* pGrid )
{
   int width = pGrid->GetWidth();
   int height = pGrid->GetHeight();
   ArrayGrid<double>* pDoubleGrid = new ArrayGrid<double>( width, height );  // NOT initialized at construction
   for (int y = 0; y < height; y ++)
   {
      for (int x = 0; x < width; x ++)
      {
         pDoubleGrid->SetValue( x, y, static_cast<double>( pGrid->GetValue(x, y) ) );
      }
   }
   return pDoubleGrid;
}

//----------------------------------------------------------------------------------

template <class T>
ArrayGrid<double>* NumberGridTools<T>::CreateDoubleGridFromComplexGrid( ArrayGrid< std::complex<double> >* pGrid )
{
   int width = pGrid->GetWidth();
   int height = pGrid->GetHeight();
   ArrayGrid<double>* pDoubleGrid = new ArrayGrid<double>( width, height );  // NOT initialized at construction
   for (int y = 0; y < height; y ++)
   {
      for (int x = 0; x < width; x ++)
      {
         pDoubleGrid->SetValue( x, y, std::abs( ( pGrid->GetValue(x, y) ) ) );
      }
   }
   return pDoubleGrid;
}

//----------------------------------------------------------------------------------

template <class T>
ArrayGrid<double>* NumberGridTools<T>::NegateGrid( ArrayGrid< double >* pGrid )
{
   int width = pGrid->GetWidth();
   int height = pGrid->GetHeight();
   ArrayGrid<double>* pNegativeGrid = new ArrayGrid<double>( width, height );  // NOT initialized at construction
   for (int y = 0; y < height; y ++)
   {
      for (int x = 0; x < width; x ++)
      {
         pNegativeGrid->SetValue( x, y, -1.0 * pGrid->GetValue(x, y) );
      }
   }
   return pNegativeGrid;
}

//----------------------------------------------------------------------------------

template <class T>
void NumberGridTools<T>::NegateGridSelf( ArrayGrid< double >* pGrid, double maxValue )
{
   int width = pGrid->GetWidth();
   int height = pGrid->GetHeight();
   for (int y = 0; y < height; y ++)
   {
      for (int x = 0; x < width; x ++)
      {
         pGrid->SetValue( x, y, maxValue - pGrid->GetValue(x, y) );
      }
   }
}

//----------------------------------------------------------------------------------

template <class T>
ArrayGrid<int>* NumberGridTools<T>::NegateGrid( ArrayGrid< int >* pGrid, int maxValue )
{
   int width = pGrid->GetWidth();
   int height = pGrid->GetHeight();
   ArrayGrid<int>* pNegativeGrid = new ArrayGrid<int>( width, height );  // NOT initialized at construction
   for (int y = 0; y < height; y ++)
   {
      for (int x = 0; x < width; x ++)
      {
         pNegativeGrid->SetValue( x, y, maxValue - pGrid->GetValue(x, y) );
      }
   }
   return pNegativeGrid;
}

//----------------------------------------------------------------------------------
template <class T>
void NumberGridTools<T>::NegateGridSelf( ArrayGrid< int >* pGrid, int maxValue )
{
   int width = pGrid->GetWidth();
   int height = pGrid->GetHeight();
   for (int y = 0; y < height; y ++)
   {
      for (int x = 0; x < width; x ++)
      {
         pGrid->SetValue( x, y, maxValue - pGrid->GetValue(x, y) );
      }
   }
}

//----------------------------------------------------------------------------------

/////////////////////////////
//                         //
// 6. GRID DERIVATIVES     //
//                         //
/////////////////////////////

template <class T>
inline T NumberGridTools<T>::GetFirstDerivativeX( ArrayGrid<T>* pGrid, int x, int y)
{
   return ( pGrid->GetValue(x+1, y) - pGrid->GetValue( x-1, y) );
}

//----------------------------------------------------------------------------------

template <class T>
inline T NumberGridTools<T>::GetFirstDerivativeY( ArrayGrid<T>* pGrid, int x, int y)
{
   return (  pGrid->GetValue(x, y+1) - pGrid->GetValue( x, y-1 ) );
}

//----------------------------------------------------------------------------------

template <class T>
inline T NumberGridTools<T>::GetSecondDerivativeXX( ArrayGrid<T>* pGrid, int x, int y)
{
   return (       - pGrid->GetValue( x-2, y )
            + 2.0 * pGrid->GetValue( x  , y )
                  - pGrid->GetValue( x+2, y )
          );
}

//----------------------------------------------------------------------------------

template <class T>
inline T NumberGridTools<T>::GetSecondDerivativeXY( ArrayGrid<T>* pGrid, int x, int y)
{
   return (  ( pGrid->GetValue( x+1, y+1 ) - pGrid->GetValue( x-1, y+1   ) ) // equivalent to GetFirstDerivativeY( x, y+1)
           - ( pGrid->GetValue( x+1, y-1 ) - pGrid->GetValue( x-1, y-1   ) ) // equivalent to GetFirstDerivativeY( x, y-1)
          );
}

//----------------------------------------------------------------------------------

template <class T>
inline T NumberGridTools<T>::GetSecondDerivativeYY( ArrayGrid<T>* pGrid, int x, int y)
{
   return (       - pGrid->GetValue( x, y-2 )
            + 2.0 * pGrid->GetValue( x, y   )
                  - pGrid->GetValue( x, y+2 )
          );
}

//----------------------------------------------------------------------------------

//////////////////////////////////////////
//                                      //
// 7. GRID ROTATION WITHOUT RESAMPLING  //
//                                      //
//////////////////////////////////////////

template <class T>
ArrayGrid<double>* NumberGridTools<T>::Rotate90DegreesClockwise( ArrayGrid<double>* pGrid )
{
   int width = pGrid->GetWidth();
   int height = pGrid->GetHeight();
   int rotatedWidth = height;
   int rotatedHeight = width;

   ArrayGrid<double>* pDoubleGrid = new ArrayGrid<double>( rotatedWidth, rotatedHeight );  // NOT initialized at construction

   for (int rotatedY = 0; rotatedY < rotatedHeight; rotatedY++)
   {
      for (int rotatedX = 0; rotatedX < rotatedWidth; rotatedX++)
      {
         int x = rotatedY;
         int y = rotatedWidth - rotatedX - 1;
         pDoubleGrid->SetValue( rotatedX, rotatedY, static_cast<double>( pGrid->GetValue( x, y ) ) );
      }
   }
   return pDoubleGrid;
}

//----------------------------------------------------------------------------------

template <class T>
ArrayGrid<double>* NumberGridTools<T>::Rotate90DegreesCounterClockwise( ArrayGrid<double>* pGrid )
{
   int width = pGrid->GetWidth();
   int height = pGrid->GetHeight();
   int rotatedWidth = height;
   int rotatedHeight = width;

   ArrayGrid<double>* pDoubleGrid = new ArrayGrid<double>( rotatedWidth, rotatedHeight );  // NOT initialized at construction

   for (int rotatedY = 0; rotatedY < rotatedHeight; rotatedY++)
   {
      for (int rotatedX = 0; rotatedX < rotatedWidth; rotatedX++)
      {
         int x = rotatedHeight - rotatedY - 1;
         int y = rotatedX;
         pDoubleGrid->SetValue( rotatedX, rotatedY, static_cast<double>( pGrid->GetValue( x, y ) ) );
      }
   }
   return pDoubleGrid;
}

//----------------------------------------------------------------------------------

template <class T>
ArrayGrid<double>* NumberGridTools<T>::Rotate180Degrees( ArrayGrid<double>* pGrid )
{
   int width = pGrid->GetWidth();
   int height = pGrid->GetHeight();

   ArrayGrid<double>* pDoubleGrid = new ArrayGrid<double>( width, height );  // NOT initialized at construction
   for (int y = 0; y < height; y ++)
   {
      for (int x = 0; x < width; x ++)
      {
         int rotatedX = width  - x - 1;
         int rotatedY = height - y - 1;
         pDoubleGrid->SetValue( rotatedX, rotatedY, static_cast<double>( pGrid->GetValue(x, y) ) );
      }
   }
   return pDoubleGrid;
}

//----------------------------------------------------------------------------------

///////////////////////////////
//                           //
// 8. SPECIAL TRANSFORMS     //
//                           //
///////////////////////////////

template <class T>
ArrayGrid<double>* NumberGridTools<T>::LogPolarTransform( ArrayGrid<double>* pGrid )
{
   double width  = (double)(pGrid->GetWidth());
   double height = (double)(pGrid->GetHeight());
   double w2 = width  / 2.0;
   double h2 = height / 2.0;

   int nrWedges = 720;
   int nrRings  = 720;

   double maxRadius = sqrt( w2 * w2 + h2 * h2);
   double minRadius = maxRadius * exp( -2.0 * M_PI * (nrRings -1) / nrWedges );

   NearestNeighborInterpolator nni;
   ArrayGrid<double>* pLogPolar = new ArrayGrid<double>( nrRings, nrWedges );

   for (int ringNr = 0; ringNr < nrRings; ringNr++)
   {
      double radius = minRadius + exp( ringNr * log(maxRadius / minRadius) / (nrRings-1) );
      for (int wedgeNr = 0; wedgeNr < nrWedges; wedgeNr++)
      {
         double theta = (2.0 * M_PI * (double)(wedgeNr) / (double)(nrWedges) ) -  M_PI;
         common::Point<double> pt;
         pt.SetRadiusAndTheta( radius, theta );
         pt.ToCartesian( );
         double xx = pt.x + width/2;
         double yy = pt.y + height/2;
         if ( (xx >= 0) && ( xx < width) && (yy >= 0) && (yy < height) )
         {
            pLogPolar->SetValue( ringNr, wedgeNr, nni.Run( pGrid, xx, yy ) );
         }
      }
   }
   return pLogPolar;
}

//----------------------------------------------------------------------------------

/////////////////////////////
//                         //
// 9. GRID THRESHOLDING    //
//                         //
/////////////////////////////

template <class T>
void NumberGridTools<T>::ClipValues( ArrayGrid<T>* pGrid, T desiredMin, T desiredMax )
{
   for (int y = 0; y < pGrid->GetHeight(); y++)
   {
      for (int x = 0; x < pGrid->GetWidth(); x ++)
      {
         pGrid->SetValue( x, y, common::MathUtils::ClipValue( pGrid->GetValue( x, y ), desiredMin, desiredMax ) );
      }
   }
}

//----------------------------------------------------------------------------------

template <class T>
ArrayGrid<double>* NumberGridTools<T>::HardThreshold( ArrayGrid<double>* pGrid, double threshold )
{
   ArrayGrid<double>* pThresholdedGrid = pGrid->Clone();

   int width = pGrid->GetWidth();
   int height = pGrid->GetHeight();

   for (int y = 0; y < height; y ++)
   {
      for (int x = 0; x < width; x ++)
      {
         if ( pGrid->GetValue(x, y) < threshold)
         {
            pThresholdedGrid->SetValue(x, y, 0.0);
         }
         else
         {
            pThresholdedGrid->SetValue(x, y, pGrid->GetValue(x, y) );
         }
      }
   }
   return pThresholdedGrid;
}

//----------------------------------------------------------------------------------

template <class T>
ArrayGrid<bool>* NumberGridTools<T>::BinaryThreshold( ArrayGrid<double>* pGrid, double threshold, bool thresholdAbsoluteValue )
{
   ArrayGrid<bool>* pThresholdedGrid = new ArrayGrid<bool>( pGrid->GetWidth(), pGrid->GetHeight() );
   int width = pGrid->GetWidth();
   int height = pGrid->GetHeight();

   int nrTruePixels = 0;
   if ( thresholdAbsoluteValue )
   {
      for (int y = 0; y < height; y ++)
      {
         for (int x = 0; x < width; x ++)
         {
            if ( fabs( pGrid->GetValue(x, y) ) < threshold )
            {
               pThresholdedGrid->SetValue(x, y, false );
            }
            else
            {
               pThresholdedGrid->SetValue(x, y, true );
               nrTruePixels++;
            }
         }
      }
   }
   else
   {
      for (int y = 0; y < height; y ++)
      {
         for (int x = 0; x < width; x ++)
         {
            if ( pGrid->GetValue(x, y) < threshold )
            {
               pThresholdedGrid->SetValue(x, y, false );
            }
            else
            {
               pThresholdedGrid->SetValue(x, y, true );
               nrTruePixels++;
            }
         }
      }
   }
#ifdef DEBUG
   std::cout << " nrTruePixels = " << nrTruePixels << std::endl << std::flush;
#endif
   return pThresholdedGrid;
}

//----------------------------------------------------------------------------------

template <class T>
ArrayGrid<int>* NumberGridTools<T>::BinaryThresholdInteger( ArrayGrid<double>* pGrid, int threshold )
{
   ArrayGrid<int>* pThresholdedGrid = new ArrayGrid<int>( pGrid->GetWidth(), pGrid->GetHeight() );
   int width = pGrid->GetWidth();
   int height = pGrid->GetHeight();

   for (int y = 0; y < height; y ++)
   {
      for (int x = 0; x < width; x ++)
      {
         if ( pGrid->GetValue(x, y) < threshold )
         {
            pThresholdedGrid->SetValue(x, y, 0 );
         }
         else
         {
            pThresholdedGrid->SetValue(x, y, threshold );
         }
      }
   }

   return pThresholdedGrid;
}

//===========================================================================================

///////////////////////////
//                       //
// 10. COMBINE GRIDS     //
//                       //
///////////////////////////

template <class T>
void NumberGridTools<T>::UpdateAverageGrid( ArrayGrid<T>* pAverageGrid, ArrayGrid<T>* pNewGrid, int previousNrOfGridsProcessed )
{
   int height = pAverageGrid->GetHeight();
   int width  = pAverageGrid->GetWidth();

   int newNrOfGridsProcessed = previousNrOfGridsProcessed + 1;
   for ( int y = 0; y < height; y++ )
   {
      for ( int x = 0; x < width; x++ )
      {
         double tmpValue = ( pAverageGrid->GetValue( x, y ) * previousNrOfGridsProcessed ) + pNewGrid->GetValue( x, y );
         pAverageGrid->SetValue( x, y, tmpValue / newNrOfGridsProcessed );
      }
   }
}

//----------------------------------------------------------------------------------

template <class T>
ArrayGrid<T>* NumberGridTools<T>::AverageGrids( std::vector< ArrayGrid<T>* > gridVector )
{
   typename std::vector< ArrayGrid<T>* >::iterator it = gridVector.begin();
   ArrayGrid<T>* pAverageGrid = (*it)->Clone();
   int nrGrids = 1;
   it++;
   for ( ; it != gridVector.end(); ++it )
   {
      UpdateAverageGrid( pAverageGrid, (*it), nrGrids );
      nrGrids++;
   }
   return pAverageGrid;
}

//===========================================================================================

}
}

#endif
