
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

#ifndef STIRA_IMAGEANALYSIS_WATERSHEDTOBOGGAN_H
#define STIRA_IMAGEANALYSIS_WATERSHEDTOBOGGAN_H

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <queue>

#include "../../common/common/Point.h"
#include "../../imagedata/datastructures/Image.h"
#include "Watershed.h"

namespace stira {
namespace imageanalysis {

using namespace imagedata;

#define LABEL_INITIAL -1
#define LABEL_MASK -2
#define LABEL_WATERSHED 0

/** \brief Watershed segmentation immersion according to Lin et al (Algorithm 1), as described in 
  * article{ lin06toboggan,
  *          author  = {Yung-Chieh Lin, Yu-Pao Tsai, Yi-Ping Hung, and Zen-Chung Shih.},
  *          title   = {Comparison Between Immersion-Based and Toboggan-Based Watershed Image Segmentation},
  *          journal = {IEEE Trans. Image Processing},
  *          volume  = {15},
  *          number  = {3},
  *          pages   = {632--640},
  *          year    = {2006}
  *        }
  * http://ippr.csie.ntu.edu.tw
  * \warning Own implementation, not completely functional!!! Use WatershedMeyer instead.
  */
class WatershedToboggan
{
public:
   
   /** \brief Constructor. */
   WatershedToboggan();
   
   /** \brief Destructor. */
   ~WatershedToboggan();
   
   /** \brief runs the watershed
     * \param pGridIn the input grid*/
   ArrayGrid<int>* Run( ArrayGrid<double>* pGridIn );

private:
   /** \brief clears all elements that still were present in the queue*/
   void ResetQueue();
   
   /** \brief for diagnostics; prints vector of all sorted pixel elements on standard output*/
   void PrintPixelElementVector( );
   
   /** \brief Gets rounded value as integer from source grid
     * \param x x coordinate where to get the intensity
     * \param y y coordinate where to get the intensity*/
   int GetSourceIntensity( int x, int y );
   
   /** \brief Gets label currently assigned to this pixel
     * \param x x coordinate of pixel of which to get the label
     * \param y y coordinate of pixel of which to get the label*/
   int GetLabel( int x, int y );
   
   /** \brief Sets label currently assigned to this pixel
     * \param x x coordinate of pixel of which to set the label
     * \param y y coordinate of pixel of which to set the label
     * \param label the value of the label to set*/
   void SetLabel( int x, int y, int label );
   
   /** \brief Gets distance currently assigned to this pixel
     * \param x x coordinate of pixel of which to get the distance
     * \param y y coordinate of pixel of which to get the distance*/
   int GetDistance( int x, int y );
   
   /** \brief Sets distance currently assigned to this pixel
     * \param x x coordinate of pixel of which to set the distance
     * \param y y coordinate of pixel of which to set the distance
     * \param distance the distance to set*/
   void SetDistance( int x, int y, int distance );
   
   /** \brief Given the current pixel, gets the neighbour with the smallest intensity
     * \param x x coordinate of pixel of which to find smallest neighbour
     * \param y y coordinate of pixel of which to find smallest neighbour*/
   PixelElement<int> GetSmallestNeighbour( int x, int y );
   
   /** \brief Label current pixel from its neighbours that already obtained a label
     * \param x x coordinate of pixel of which to check the neighbours
     * \param y y coordinate of pixel of which to check the neighbours*/
   int GetLabelFromNeighbours( int x, int y );
   
   /** \brief Creates a pixel element for the given position
     * \param x x coordinate of pixel of which to create a pixel element
     * \param y y coordinate of pixel of which to create a pixel element*/
   PixelElement<int> CreatePixelElement( int x, int y );
   
   int DetermineMaskLabelsFromLabeledNeighbours( std::vector< PixelElement<int> >& maskedPixelVector );
   
   /** \brief processes neighbours of last element popped from the queue during flooding step
     * \param x x coordinate of pixel of which to check the neighbours
     * \param y y coordinate of pixel of which to check the neighbours*/
   void ProcessNeighboursOfQueueElements(int x, int y);
   
   /** \brief processes new minima that arise as water level rises
     * When a certain water level is reached, all pixels are labeled from their neighbours;
     * however, new minima have no neighbours that were already labeled. So after all pixels 
     * for a certain level were labeled that were connected to already labeled pixels, the remaining 
     * pixels must belong to new minima
     * \param vCurrentLevelPixels all pixels with current level*/
   void ProcessNewMinima( std::vector< PixelElement<int> > vCurrentLevelPixels );
   
   /** \brief Checks if the neighbour is valid
     * Checks if neighbour is within the image, and is NOT the same as the original pixel*/
   bool IsValidNeighbour(int x, int y, int dx, int dy);

   /** \brief masks for the current water level the pixels to be labeled
     * \param currentIndex index in the vector up to which we already labeled the pixels*/
   std::vector< PixelElement<int> > MaskInitialCandidates( int currentIndex );

   /** \brief Inspects neighbour of newly assigned minimum
     * if it is masked for labeling, it gets mCurrentLabel just as its neighbouring minimum
     * \param x x coordinate of neighbour of minimum
     * \param y y coordinate of neighbour of minimum*/
   void InspectNeighboursOfNewMinima( int x, int y );
   
   /** \brief creates the list (in fact a vector) in which all pixels are sorted from darkest to brightest*/
   void CreateSortedPixelList( );
   
   std::queue< PixelElement<int> > mpFifoQueue;     ///< queue for processing pixels
   std::vector< PixelElement<int> > mvSortedPixelElementVector; ///< all pixels sorted from smallest to largest intensity
   ArrayGrid<int>* mpLabelGrid;   ///< grid with the assigned labels
   ArrayGrid<int>* mpDistanceGrid;///< grid with the assigned distances
   ArrayGrid<bool>* mpWatershedGrid;///< grid with the watersheds
   int mCurrentDistance;  ///< current distance
   int mCurrentLabel;  ///< last label assigned
   int mCurrentLevel;  ///< current water level

   ArrayGrid<double>* mpSourceGrid;  ///< original ource grid (single banded image)
};

}
}

#endif

