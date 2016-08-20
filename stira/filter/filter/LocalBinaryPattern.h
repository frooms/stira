
/***********************************************************************************
 *   Copyright (C) 2012 by Filip Rooms                                             *
 *                                                                                 *
 *  Terms and conditions for using this software in any form are provided in the   *
 *  file COPYING, which can be found in the root directory of this project.        *
 *                                                                                 *
 *   Contact data: filip.rooms@gmail.com                                           *
 *                 http://www.filiprooms.be/                                       *
 *                                                                                 *
 ***********************************************************************************/

#ifndef STIRA_FILTER__LOCALBINARYPATTERN_H
#define STIRA_FILTER__LOCALBINARYPATTERN_H

#define USE_BILINEAR_INTERPOLATION
#define GENERATE_INTERMEDIATE_IMAGES

#include "../../common/common/StiraMacros.h"
#include "../../common/common/Point.h"
#include "../../imagedata/datastructures/Image.h"
#include "../../histogram/histogram/FloatHistogram.h"

#ifdef USE_BILINEAR_INTERPOLATION
   #include "../../imagetools/interpolation/BilinearInterpolator.h"
#endif
namespace stira{
namespace filter{

using namespace imagedata;
using namespace imagetools;

/** \brief computes the Local Binary Pattern operation for each pixel in the image.
  *
  * The Local Binary Pattern is a pixel-wise value that encodes the local spatial
  * neighborhood of a pixel into a single value; histograms of these values over
  * the image provide information about the frequency of occurance of certain pixel configurations.
  * Reference   http://www.scholarpedia.org/article/Local_Binary_Patterns
  *
  * Bibtex reference:
  *     article{ Ojala96LBP,
  *                author  = {Ojala, T. and Pietik\"{a}inen, M. and Harwood, D.},
  *                title   = {A comparative study of texture measures with classification based on featured distributions},
  *                journal = {Pattern Recognition},
  *                volume  = {29},
  *                number  = {1},
  *                pages   = {51--59}
  *                year    = {1996}
  *            }
  *     @INPROCEEDINGS{ OrjuelaDSP2011,
  *                       author = {Orjuela-Vargas, S. and Quinones, R. and Ortiz-Jaramillo, B. and Rooms, F. and de Keyser, R. and Philips, W.},
  *                       title = {Improving Texture Discrimination in the Local Binary Patterns Technique by Using Symmetry and Group theory},
  *                       booktitle = {17th International Conference on Digital Signal Processing DSP 2011},
  *                       year = {2011}
  *                   }
  *
  * Two variants were proposed by Sergio Alejando Orjuela Vargas**
  */
class LocalBinaryPattern
{
public:
   /** \brief constructor*/
   LocalBinaryPattern();

   /** \brief destructor*/
   ~LocalBinaryPattern();

   LocalBinaryPattern( ArrayGrid<double>* pGrid, double initAngle, double radius, int nrPoints );

   LocalBinaryPattern( ArrayGrid<double>* pGrid, double initAngle, double radius, int nrPoints, std::vector< common::Point<int> > vPointsOfInterest );

public:

   /** \brief computes LBP for circle around given central pixel
     * \param x x coordinate of central pixel to compute LBP for
     * \param y y coordinate of central pixel to compute LBP for
     * \return a vector with a sequence of true's (pixel value was larger than value of central pixel) and false's (pixel value was smaller) */
   std::vector<bool> RunVector( int x, int y );

   /** \brief run method, gives a code number from vector with a sequence of true's and false's
     * This number is computes as follows: sum_i ( 2^i * vectorElement[i] )
     * \param x x coordinate of central pixel to compute LBP for
     * \param y y coordinate of central pixel to compute LBP for
     * \return number encoding the vector*/
   int RunCode( int x, int y );

   /** \brief computes a normalized histogram of the LBP pattern codes over the considered points */
   histogram::FloatHistogram* RunHistogram( int ID=0 );

   /** \brief Gets a vector with delta x anfd delta y's of the points around the central point on which the LBP is computed */
   std::vector< common::Point< double > > GetSamplePoints();

private:

   /** \brief visualizes the points on which the LBP is sampled for a central point (x,y)
     * \param pOutGrid the grid on which to visualize
     * \param x the x coordinate of the central point
     * \param y the y coordinate of the central point */
   void DrawDeltaPoints( ArrayGrid<double>* pOutGrid, int x, int y );

   /** \brief initializes the data structures and member variables
     * \param pGrid input grid
     * \param initAngle initial angle to start placing points in the circle to compute the LBP's
     * \param radius of the circle to compute the LBP's, double radius, int nrPoints
     * \param nrPoints number of points to put on the circle to compute the LBP's */
   void Initialize( ArrayGrid<double>* pGrid, double initAngle, double radius, int nrPoints );

   bool mHasPointsOfInterest;  ///< flag if true: only certain points of interest are to be taken from a grid; if false all points are taken
   std::vector< common::Point<int> > mvPointsOfInterest;   ///< if mHasPointsOfInterest is true, the LBP's will be only computed for these points of mpGrid
   double mInitialAngle;  ///< angle between x axis and line origin - first point
   ArrayGrid<double>* mpGrid;  ///< input grid
   double mRadius;  ///< radius of neighborhood circle to consider
   int mNumberOfPoints;  ///< number of points per neighborhood circle to consider
   std::vector< common::Point< double > > mvDeltaPoints;  ///< input grid

public:

   /** \brief compares two values and assigns a 0/1 or 0/1/2 depending on the type
     * \param a first value in comparison
     * \param b second value in comparison
     * \param threshold comparison threshold
     * \param myType whether a binary or ternary comparison should be performed */
   int SignComparison(double a, double b, double threshold, bool myType);

   /** \brief computes classic Locally Binary Pattern filter for a whole image
     * assigns a code to each image pixel depending on the pixel's environment
     * \param pImageIn input image */
   static Image* RunClassic( Image* pImageIn);

   int ComputePointGLDP( ArrayGrid<double>* pGridIn, int x, int y, double threshold, bool myType );
   /** \brief computes label for Geometric Textural Pattern with 36 neighborhood points in three rings around the central point
     * \param pGridIn input image
     * \param x x coordinate of central point for which to compute label
     * \param y y coordinate of central point for which to compute label
     * \param threshold comparison threshold
     * \param myType whether a binary or ternary comparison should be performed */
   int ComputePointGLTP( ArrayGrid<double>* pGridIn, int x, int y, double threshold, bool myType );

   /** \brief computes Jensen-Shannon divergence between histograms of labels between two image patches
     * The labels are computed using symmetric Locally Binary Pattern with 12 neighborhood points
     * \param pGridIn input image
     * \param frameNr frame ID of image being processed
     * \param xTop1 x coordinate of the top left corner of image patch 1
     * \param yTop1 y coordinate of the top left corner of image patch 1
     * \param xBottom1 x coordinate of the bottom right corner of image patch 1
     * \param yBottom1 y coordinate of the bottom right corner of image patch 1
     * \param xTop2 x coordinate of the top left corner of image patch 2
     * \param yTop2 y coordinate of the top left corner of image patch 2
     * \param xBottom2 x coordinate of the bottom right corner of image patch 2
     * \param yBottom2 y coordinate of the bottom right corner of image patch 2 */
   double ComputeJensenShannonDivergenceBetweenImagePatches( ArrayGrid<double>* pGridIn, int frameNr,
                                                             int xTop1, int yTop1, int xBottom1, int yBottom1,
                                                             int xTop2, int yTop2, int xBottom2, int yBottom2 );

   /** \brief computes histogram of labels for symmetric Locally Binary Pattern with 12 neighborhood points for an image patche
     * \param pGridIn input image
     * \param frameNr frame ID of image being processed
     * \param topX x coordinate of the top left corner of image patch
     * \param topY y coordinate of the top left corner of image patch
     * \param bottomX x coordinate of the bottom right corner of image patch
     * \param bottomY y coordinate of the bottom right corner of image patch
     * \param threshold comparison threshold
     * \param myType whether a binary or ternary comparison should be performed  */
   histogram::FloatHistogram ComputePointLBPSymHistogram( ArrayGrid<double>* pGridIn, int frameNr,
                                                          int topX, int topY, int bottomX, int bottomY,
                                                          double threshold, bool myType );

   /** \brief computes image where each pixel shows the label for symmetric Locally Binary Pattern with 12 neighborhood points
     * \param pGridIn input image
     * \param threshold comparison threshold
     * \param myType whether a binary or ternary comparison should be performed  */
   ArrayGrid<int>* ComputeLBPSymImage( ArrayGrid<double>* pGridIn, double threshold, bool myType );

   /** \brief computes label for symmetric Locally Binary Pattern with 12 neighborhood points
     * assigns a label to each image pixel depending on the pixel's environment*/
   int ComputePointLBPSym( ArrayGrid<double>* pGridIn, int x, int y, double threshold, bool myType );

private:
   double mPointsGLTP[36][2];  ///< the 36 neighborhood points to compute Geometric Textural Patterns

   double mPointsLBPSym[12][2];  ///< the 12 neighborhood points to compute Symmetric Local Binary Patterns

#ifdef USE_BILINEAR_INTERPOLATION
   // in case of binlinear interpolation to find values in between exact pixel positions
   // for now, we approximate by nearest neighborhood for efficiency and speed
   BilinearInterpolator mBilinearInterpolator;  ///< bilinear interpolator to compute values in between integer pixel positions
#endif
};

}
}

#endif
