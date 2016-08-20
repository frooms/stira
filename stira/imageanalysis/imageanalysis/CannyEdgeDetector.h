
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

#ifndef STIRA_IMAGEANALYSIS_CANNYEDGEDETECTOR_H
#define STIRA_IMAGEANALYSIS_CANNYEDGEDETECTOR_H

#include <iostream>
#include <cstdlib>
#include <cmath>
#include "../../common/common/Point.h"
#include "../../imagedata/datastructures/Image.h"
#include "../../imagedata/datastructures/OrientationGrid.h"

namespace stira {
namespace imageanalysis {

using namespace imagedata;

enum edgeLabel {IS_EDGE, IS_CANDIDATE_EDGE, IS_NO_EDGE};
   
/** \brief Canny edge detector 
  * inspired on  http://en.wikipedia.org/wiki/Canny_edge_detector
  *              ftp://figment.csee.usf.edu/pub/Edge_Comparison/source_code
  *              http://www.pages.drexel.edu/~nk752/cannyTut2.html
  *              http://www.cvmt.dk/education/teaching/f09/VGIS8/AIP/canny_09gr820.pdf
  */
class CannyEdgeDetector
{
public:
   
   /** \brief Constructor. */
   CannyEdgeDetector();
   
   /** \brief Destructor. */
   ~CannyEdgeDetector();
   
   /** \brief input data
     * \param pGridIn input data
     * \param sigmaSmooth sigma for the Gaussian smoothing applied as preprocessing for edge detection
     * \param lowerThreshold low threshold for edge strength in hysteresis test
     * \param upperThreshold high threshold for edge strength in hysteresis test
     * \return grid with the edges */
   static ArrayGrid<bool>* Run( ArrayGrid<double>* pGridIn, double sigmaSmooth, double lowerThreshold, double upperThreshold);

private:

   /** \brief creates a map where all pixels that are not local maxima on the edge magnitude map are suppressed
     * This map will then be used as initial edge candidates, whch then have to pass the hysteresis test
     * \param pOrientationGrid grid with local edge strengths and orientations
     * \return map with candidate edges */
   static ArrayGrid<bool>* CreateNonMaximaSuppressedMap( OrientationGrid* pOrientationGrid );

   /** \brief Checks a candidate pixel location if it is a local maximum under a certain angle
     * \param x x coordinate of candidate pixel
     * \param y y coordinate of candidate pixel
     * \param quantized quantized angle as a multiple of 45 degrees (0, 1, 2 and 3)
     * \param pOrientationGrid grid with edge strengths and edge orientations
     * \return true if pixel is local maximum in the specified direction; false if not */
   static bool IsCandidateLocalMaximum( int x, int y, int quantized, OrientationGrid* pOrientationGrid );

   /** \brief applies hysteresis based thresholding
     * Keep only edges that are connected to a pixel with edge strength above the high threshold, and 
     * have an edge strength themself above the low threshold
     *
     * \param pOrientationGrid grid with edge strengths and edge orientations
     * \param pCandidateGrid grid with candidate edges from NonMaximaSuppression
     * \param lowerThreshold pixel edge strength must anyway be above this threshold to be an edge
     * \param upperThreshold  pixel edge strength must be above this threshold to be an edge seed
     * \return boolean grid with final edges */
   static ArrayGrid<bool>* ApplyHysteresis( OrientationGrid* pOrientationGrid,
                                            ArrayGrid<bool>* pCandidateGrid,
                                            double lowerThreshold,
                                            double upperThreshold );

   /** \brief Create candidate edge label image as input for hysteresis step
     * As output of the non-maxima suppression, we got a thinned edge image. These edges are labeled as candidate edge; other 
     * pixels are no longer considered. The candidate edges are then subjected to the hysteresis test: if they are higher than a low
     * threshold and belong to the same edge with at least one pixel above the high threshold, it us considered an edge, otherwise 
     * it is no edge.
     * 
     * \param pOrientationGrid input edge strength and orientation grid
     * \param pCandidateGrid boolean grid from non-maxima suppression
     * \param loThreshold lower edge strength threshold
     * \return grid with candidate edge labels */
   static ArrayGrid<edgeLabel>* CreateCandidateLabelGrid( OrientationGrid* pOrientationGrid,
                                                          ArrayGrid<bool>* pCandidateGrid,
                                                          double loThreshold);

   /** \brief checks for a next start seed for the edge tracking
     * This test checks if there are any pixels left labeled as candidate edge and:
     *  - either they are above the high threshold to get the tracking started,
     *  - or they are above the low threshold, but are connected to a pixel that was already confirmed as an edge
     * 
     * \param pOrientationGrid grid with edge strengths and edge orientations
     * \param pLabelGrid grid with candidate edges from NonMaximaSuppression
     * \param lastSeed last seed used to start edge tracking (to avoid checking same edge multiple times)
     * \param hiThreshold high threshold for edge strength in hysteresis test
     * \param loThreshold low threshold for edge strength in hysteresis test
     * \return  */
   static common::Point<int> GetStartSeed( OrientationGrid* pOrientationGrid,
                                           ArrayGrid<edgeLabel>* pLabelGrid,
                                           common::Point<int> lastSeed,
                                           double hiThreshold,
                                           double loThreshold);
   
   /** \brief During edge tracking, check next candidate edge neighbor to last confimed edge pixel on the current edge tracking
     * 
     * \param pOrientationGrid grid with edge strengths and edge orientations
     * \param pLabelGrid grid with candidate edges from NonMaximaSuppression
     * \param lastNeighbor last neighbor pixel on current edge that was confirmed as edge
     * \param loThreshold low threshold for edge strength in hysteresis test 
     * \return coordinates of next neighbor confirmed as an edge, or (-1, -1) if no more pixels can be confirmed as edge */
   static common::Point<int> GetNextNeighbor( OrientationGrid* pOrientationGrid,
                                              ArrayGrid<edgeLabel>* pLabelGrid,
                                              common::Point<int> lastNeighbor, 
                                              double loThreshold);
   
   /** \brief Create a boolean grid with the finally confirmed edges
     * 
     * \param pLabelGrid Intermediate grid previously containing candidate edges, now used to extract the confirmed edges
     * \param alsoTakeCandidates flag whether just confirmed edges or also candidate edge pixels are written to the output
     * \return boolean grid with the finally confirmed edges */
   static ArrayGrid<bool>* CreateOutPut( ArrayGrid<edgeLabel>* pLabelGrid,
                                         bool alsoTakeCandidates=false );

   /** \brief quantify the orientations to 0,45, 90 and 135 degrees
     * \param pOrientationGrid orientation grid to be quantified */
   static void QuantifyOrientations( OrientationGrid* pOrientationGrid );
};

}
}

#endif
