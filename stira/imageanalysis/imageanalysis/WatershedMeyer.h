
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

#ifndef STIRA_IMAGEANALYSIS_WATERSHEDMEYER_H
#define STIRA_IMAGEANALYSIS_WATERSHEDMEYER_H

#include <vector>
#include <queue>
#include <cassert>

#include "../../common/common/Point.h"
#include "../../imagedata/datastructures/OrientationGrid.h"
#include "../../imagedata/datastructures/Image.h"
#include "../../imagetools/tools/NumberGridTools.h"
#include "../../filter/filter/NonSeparableFilter.h"
#include "Watershed.h"

// Minimum watershed segment label
#define LABEL_MINIMUM 0

// Label for the watersheds pixels
#define LABEL_RIDGE -1

// Label for pixels that are not local minima
#define LABEL_NOLOCALMINIMUM -2

// Label for pixels that are or have been in the OrderedQueques
#define LABEL_PROCESSING -3

// Label for unprocessed pixels
#define LABEL_UNPROCESSED -4

namespace stira {
namespace imageanalysis {

using namespace std;
using namespace stira::common;
using namespace stira::image;

/** \brief Template class for watershed transformations
  * variant of Meyer algorithm, as used in Matlab
  *    http://www.mathworks.com/access/helpdesk/help/toolbox/images/watershed.html
  *    Meyer, Fernand, "Topographic distance and watershed lines," Signal Processing , Vol. 38, July 1994, pp. 113-125
  * Alternative watershed algorithms with source code can be found on
  *    http://www.esiee.fr/~info/tw/ */
template < class T >
class WatershedMeyer
{
// /////////////////////////////////////////////////////
//                                                   //
//  0. Constructor  /  Destructor  /  Initializers   //
//                                                   //
// /////////////////////////////////////////////////////

public:
   /** \brief Default constructor*/
   WatershedMeyer( );

   /// \brief Destructor
   ~WatershedMeyer();

private:
   /** \brief Resets the class outputs to the initial values */
   bool InitializeInputs( );
   
   /** \brief Initialization of the class*/
   void InitializeClassParameters();

// //////////////////////////////
//                            //
//  1. Getters and setters    //
//                            //
// //////////////////////////////

public:
   /** \brief Gets upper limit for pixel to be considered a minimum and thus serve as starting seed for flooding*/
   double GetMaxMinimaLevel();
   
   /** \brief Sets upper limit for pixel to be considered a minimum and thus serve as starting seed for flooding
     * \param maxLevel the largest value for a minimum to be allowed as starting seed for flooding*/
   void SetMaxMinimaLevel(double maxLevel); 
   
   /** \brief Gets precision factor in pixel value comparison
     * What is the minimum difference in value between pixels in order to consider them actually different */
   double GetEqualityPrecision(); 
   
   /** \brief Sets precision factor in pixel value comparison
     * \param precision the minimum difference in value between pixels in order to consider them as different */
   void  SetEqualityPrecision(double precision);
   
private:
   bool mFlagWorkOnGradientImage;
   ArrayGrid< T > * CreateGradientAsInput( ArrayGrid< T > *pInputImage );
   double mMaxMinima; ///< upper limit for pixel to be considered a minimum
   double mPrecision; ///< precision in pixel value comparison

// //////////////////////////////
//                            //
//  2. Run method             //
//                            //
// //////////////////////////////

public:
   
   /** \brief Executes the transformation on iInputImage
     * \param iInputImage Input Image*/
   bool Run( ArrayGrid< T > *iInputImage, bool usegradientImage, std::string sourceDataName=std::string("") );

private:
   std::string mSourceDataName;
   ArrayGrid< T > *mpSourceImage;     ///< input source grid
   ArrayGrid< T > *mpDataInputImage;  ///< input grid on which the watershed is to be applied
                                      ///<    can be mpSourceImage if mFlagWorkOnGradientImage is false; 
                                      ///<    is a temporarly created gradient image otherwise

// //////////////////////////////////////////////
//                                            //
//  3. After Run, get Watersheds and Labels   //
//                                            //
// //////////////////////////////////////////////
public:
   /** \brief Get the number of detected watershed pixels*/
   int GetNumberOfWatershedPixels();
   
   /** \brief Get grid where watershed points have value true; other points have value false*/
   ArrayGrid<bool>* GetWatershedGrid( );

   /// \brief Get the number of watershed segments
   int GetNumberOfLabels();

   /** \brief Get the grid with watershed labels*/
   ArrayGrid<int>* GetLabelImage();
   
   /** \brief Creates image on which labels and ridges are rendered */
   Image* CreateLabelsRidgeImage();
   
   /** \brief Creates image on which ridges are rendered on top of the original image intensities*/
   Image* CreateLabelsIntensitiesImage();
   
private:
   ArrayGrid<int>  *mpLabelImage;          /// labeled result of the watershed (each region has a unique label: 0,1,2,... N) 
   vector< Point<int> > mvWatershedRidges;  /// the watershed ridges coordinates are stored in the vector

   int mNumberOfLabels;  ///< Number of labels

// //////////////////////////////////////////////
//                                            //
//  4. Internal kitchen: helper methods       //
//                                            //
// //////////////////////////////////////////////

private:
   //  4.1 Highest level helper methods
   
    //  4.1.1 LocalMinimaDetection and subroutines
      /** \brief checks if pixel at given coordinates is a local intensity minimum
        * \param x x coordinate of point to check
        * \param y y coordinate of point to check*/
      void CheckForLocalMinimum( int x, int y);
      
      /** \brief checks a single neighbour of element popped from fifo queue
        * \param peNeighbour neighbour to check
        * \param peCenter pixel element that was popped from fifo queue*/
      void HandleFifoElementNeighbours( PixelElement<T> peNeighbour, PixelElement<T> peCenter );
      
      /** \brief checks all neighbours of element popped from fifo queue
        * \param fifoElement pixel element that was popped from fifo queue*/
      void ProcessFifoElementNeighbours( PixelElement<T> fifoElement );

      /** \brief Main routine for detecting the local minima*/
      void LocalMinimaDetection();
   
    //  4.1.2 Flooding and subroutines
   
      /** \brief Main routine for flooding */
      void Flooding();
      
      /** \brief checks if point at given coordinates can be labeled from already labeled neighbours
        * \param x x coordinate of pixel to be labeled
        * \param y y coordinate of pixel to be labeled
        * \param outLabeledNeighbour output parameter: neighbour with known label
        * \param outLabel output parameter: label of known labeled neighbour*/
      bool CheckForAlreadyLabeledNeighbours( int x, int y, Point<int>& outLabeledNeighbour, int& outLabel );

      bool CheckIfPixelIsWatershed( int x, int y, Point<int> inLabeledNeighbour, int inLabelOfNeighbour );
      
      void UpdateLabel( int x, int y, int inLabelOfNeighbour );
public:
   //  4.2 Lower level helper methods

      
      /** \brief Checks if intensity at pe1 is not a local miminum
        *
        * \param pe1 first element in the comparison
        * \param pe2 second element in the comparison
        * \return true if value in pe2 is smaller than in pe1; false otherwise */
      bool IsElementNoMinima( PixelElement<T> pe1, PixelElement<T> pe2);
   
      /** \brief Checks if intensities of pe1 and pe2 are the same
        * 
        * \param pe1  first element in the comparison
        * \param pe2 second element in the comparison
        * \return true if value in pe2 is the same as in pe1; false otherwise */
      bool IsElementSame( PixelElement<T> pe1, PixelElement<T> pe2);
      
      /** \brief creates a pixel element for the given coordinates (x, y)
        * 
        * \param x x coordinate for which to create a pixel element
        * \param y y coordinate for which to create a pixel element
        * \return pixel element for the given position */
      PixelElement<T> CreatePixelElement(int x, int y );
   
      /** \brief creates a pixel element for the given point pt
        * 
        * \param pt point for which to create a pixel element 
        * \return pixel element for the given position */
      PixelElement<T> CreatePixelElement( stira::common::Point<int> pt );
      
      /** \brief checks if point (x+dx, y+dx) is a valid neighbour of (x, y)
       * Basically, we check (1) if (x+dx, y+dx) doesn't fall out of the image
       * and (2) that (x+dx, y+dx) is not the point (x, y) itself (case dx == dy == 0)
       * 
       * \param x x coordinate of reference point
       * \param y y coordinate of reference point
       * \param dx difference in x direction to neighbour
       * \param dy difference in y direction to neighbour
       * \return true if (x+dx, y+dy) is within the grid, and dx or dy is different from 0 (if both zero, it's the point itself)
       */
      bool IsValidNeighbour(int x, int y, int dx, int dy);
private:
   //  4.3 Lower level internal data structures

      ArrayGrid<int>* mpRegionalMinimaGrid; ///< regional minima image 
                                             ///< During flooding, it becomes labeled image with LABEL_RIDGE labels
   
      std::queue< PixelElement<int> >* mpFifo; ///< fifo queue of pixel elements
      
      priority_queue< PixelElement<T>, vector<PixelElement<T> >, mycomparison<T> > mvSortedQueue;
      
};

// END PROTOTYPES
// ////////////////

//==============================================================================================================
//==============================================================================================================
//==============================================================================================================

//////////////////////////
// BEGIN IMPLEMENTATIONS

/// ////////////////////////////////////////////////////
//                                                   //
//  0. Constructor  /  Destructor  /  Initializers   //
//                                                   //
// /////////////////////////////////////////////////////

template <class T >
WatershedMeyer< T >::WatershedMeyer( )
{
   InitializeClassParameters();
}

//------------------------------------------------------------------------

template <class T >
WatershedMeyer< T >::~WatershedMeyer()
{
   if(mpLabelImage)
   {
      delete mpLabelImage;
      mpLabelImage = 0;
   }
   
   if (mpDataInputImage != mpSourceImage)   // only delete when it refers to self-created gradient image
   {
      delete mpDataInputImage;
   }
   mpDataInputImage = 0;
   mpSourceImage = 0;
   mNumberOfLabels = 0;
   
   if( mpRegionalMinimaGrid )
   {
      delete mpRegionalMinimaGrid;
      mpRegionalMinimaGrid = 0;
   }
}

//------------------------------------------------------------------------

template <class T >
void WatershedMeyer< T >::InitializeClassParameters()
{
   mMaxMinima = 110.0;
   mPrecision = 30.0;
   mpSourceImage = 0;
   mpDataInputImage = 0;
   mpLabelImage = 0;
   mNumberOfLabels = 0;
   mpRegionalMinimaGrid = 0;
}

//------------------------------------------------------------------------

template <class T >
bool WatershedMeyer< T >::InitializeInputs( )
{
   if( !mpDataInputImage )
   {
      return false;
   }

   if(mpLabelImage)
   {
      delete mpLabelImage;
      mpLabelImage = 0;
   }

   mNumberOfLabels = 0;
   mvWatershedRidges.clear();
   
   if( mpDataInputImage )
   {
      mpLabelImage = new ArrayGrid<int>( mpDataInputImage->GetWidth(), mpDataInputImage->GetHeight() );
      mpLabelImage->SetGridValues( false );
   }
   return(true);
}


//------------------------------------------------------------------------

template <class T >
ArrayGrid< T > * WatershedMeyer< T >::CreateGradientAsInput( ArrayGrid< T > *pInputGrid )
{
   int width  = pInputGrid->GetWidth();
   int height = pInputGrid->GetHeight();
   ArrayGrid<double>* pDoubleGrid = NumberGridTools<T>::CreateDoubleGrid( pInputGrid );
   
   OrientationGrid* pOrientationGrid = filter::NonSeparableFilter::DetermineLocalMagnitudeAndOrientation( pDoubleGrid );
   ArrayGrid<double>* pMagnitudeGrid = pOrientationGrid->ExtractMagnitudeGrid();
   delete pOrientationGrid;
   delete pDoubleGrid;
   ArrayGrid< T > *pGrid = new ArrayGrid< T >( width, height );

   for (int y = 0; y < height; y++)
   {
      for(int x = 0; x < width; x++)
      {
         pGrid->SetValue(x, y, (T) pMagnitudeGrid->GetValue(x, y));
      }
   }
   delete pMagnitudeGrid;
   return pGrid;
}
// =================================================================

// //////////////////////////////
//                            //
//  1. Getters and setters    //
//                            //
// //////////////////////////////

template <class T >
double WatershedMeyer< T >::GetMaxMinimaLevel()
{
   return mMaxMinima;
}

//------------------------------------------------------------------------

template <class T >
void WatershedMeyer< T >::SetMaxMinimaLevel(double maxLevel)
{
   mMaxMinima = maxLevel;
}

//------------------------------------------------------------------------

template <class T >
double WatershedMeyer< T >::GetEqualityPrecision()
{
   return mPrecision;
}

//------------------------------------------------------------------------

template <class T >
void WatershedMeyer< T >::SetEqualityPrecision(double precision)
{
   mPrecision = precision;
}

// =================================================================

// //////////////////////////////
//                            //
//  2. Run method             //
//                            //
// //////////////////////////////

template <class T >
inline bool WatershedMeyer< T >::Run( ArrayGrid< T > *pInputImage, bool usegradientImage, std::string sourceDataName )
{
   mFlagWorkOnGradientImage = usegradientImage;
   mSourceDataName = sourceDataName;
   mpSourceImage = pInputImage;
   
   if (usegradientImage)
   {
      mpDataInputImage = this->CreateGradientAsInput(pInputImage);
      assert(mpSourceImage != mpDataInputImage);
   }
   else
   {
      mpDataInputImage = pInputImage;
   }
   if( !InitializeInputs( ) )
   {
      return false;
   }
   
   LocalMinimaDetection();
   Flooding();
   if( mpRegionalMinimaGrid )
   {
      delete mpRegionalMinimaGrid;
      mpRegionalMinimaGrid = 0;
   }
   
   return true;
}

// =================================================================

// //////////////////////////////////////////////
//                                            //
//  3. After Run, get Watersheds and Labels   //
//                                            //
// //////////////////////////////////////////////

template <class T >
int WatershedMeyer< T >::GetNumberOfWatershedPixels()
{
   return (int)( mvWatershedRidges.size() );
}

//------------------------------------------------------------------------

template <class T >
ArrayGrid<bool>* WatershedMeyer< T >::GetWatershedGrid( )
{
   int height = mpDataInputImage->GetHeight();
   int width  = mpDataInputImage->GetWidth();

   ArrayGrid<bool>* pWatershedGrid = new ArrayGrid<bool>(width, height);
   pWatershedGrid->SetGridValues( false );
   
   for( vector< common::Point<int> >::iterator it = mvWatershedRidges.begin();
        it != mvWatershedRidges.end();
        ++it
      )
   {
      pWatershedGrid->SetValue( (*it), true);
   }
   return pWatershedGrid;
}

//------------------------------------------------------------------------

template <class T >
int WatershedMeyer< T >::GetNumberOfLabels()
{
   return mNumberOfLabels;
}

//------------------------------------------------------------------------

template <class T >
ArrayGrid<int>* WatershedMeyer< T >::GetLabelImage()
{
   return mpLabelImage;
}

//------------------------------------------------------------------------

template <class T >
Image* WatershedMeyer< T >::CreateLabelsRidgeImage()
{
   ArrayGrid<int>* pLabelGrid = this->GetLabelImage();
   ArrayGrid<bool>* pWatershedGrid = this->GetWatershedGrid();
   int width  = pLabelGrid->GetWidth();
   int height = pLabelGrid->GetHeight();
   Image* pSegmented = new Image(width, height, 3);
   
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         if (pWatershedGrid->GetValue(x, y) )
         {
            pSegmented->GetBands()[0]->SetValue(x, y, 255);
            pSegmented->GetBands()[1]->SetValue(x, y, 0);
            pSegmented->GetBands()[2]->SetValue(x, y, 0);
         }
         else
         {
            int value = pLabelGrid->GetValue(x, y);
            pSegmented->GetBands()[0]->SetValue(x, y, value);
            pSegmented->GetBands()[1]->SetValue(x, y, value);
            pSegmented->GetBands()[2]->SetValue(x, y, value);
         }
      }
   }
   //std::string outName = pImage->GetImageName() + std::string("-WatershedMeyer");
   //pOutImage->SetImageName(outName);
   return pSegmented;
}

//------------------------------------------------------------------------

template <class T >
Image* WatershedMeyer< T >::CreateLabelsIntensitiesImage()
{
   ArrayGrid<bool>* pWatershedGrid = this->GetWatershedGrid();
   int width  = pWatershedGrid->GetWidth();
   int height = pWatershedGrid->GetHeight();
   Image* pSegmented = new Image(width, height, 3);
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         if (pWatershedGrid->GetValue(x, y) )
         {
            pSegmented->GetBands()[0]->SetValue(x, y, 255);
            pSegmented->GetBands()[1]->SetValue(x, y, 0);
            pSegmented->GetBands()[2]->SetValue(x, y, 0);
         }
         else
         {
            int value = mpSourceImage->GetValue(x, y);
            pSegmented->GetBands()[0]->SetValue(x, y, value);
            pSegmented->GetBands()[1]->SetValue(x, y, value);
            pSegmented->GetBands()[2]->SetValue(x, y, value);
         }
      }
   }
   return pSegmented;
}

// =================================================================

// //////////////////////////////////////////////
//                                            //
//  4. Internal kitchen: helper methods       //
//                                            //
// //////////////////////////////////////////////

   //  4.1 Highest level helper methods
   
    //  4.1.1 LocalMinimaDetection and subroutines
    
      template <class T >
      void WatershedMeyer< T >::HandleFifoElementNeighbours( PixelElement<T> peNeighbour, PixelElement<T> peCenter)
      {
         int x = peNeighbour.x;
         int y = peNeighbour.y;
         for (int dy = -1; dy <= 1; dy++)
         {
            for (int dx = -1; dx <= 1; dx++)
            {
               if ( IsValidNeighbour( x, y, dx, dy ) )
               {
                  if( mpRegionalMinimaGrid->GetValue( x+dx, y+dy ) == LABEL_UNPROCESSED)
                  {
                     PixelElement<int> peNextNeighbour = CreatePixelElement( x+dx, y+dy);
                     
                     if( IsElementSame( peNextNeighbour, peCenter ) )
                     {
                        mpRegionalMinimaGrid->SetValue( x+dx, y+dy, LABEL_NOLOCALMINIMUM );
                        mpFifo->push( peNextNeighbour );
                     }
                  }
                  else
                  {
                     // skip, go to next
                  }
               }
            }
         }
      }

      //-------------------------------------------------------------------------------
      
      template <class T >
      void WatershedMeyer< T >::CheckForLocalMinimum( int x, int y)
      {
         PixelElement<int> pe1 = CreatePixelElement( x, y );
                  
         for (int dy = -1; dy <= 1; dy++)
         {
            for (int dx = -1; dx <= 1; dx++)
            {
               if ( this->IsValidNeighbour( x, y, dx, dy ) )
               {
                  PixelElement<T> pe2 = CreatePixelElement( x+dx, y+dy);
                  
                  if( IsElementNoMinima( pe1, pe2 ) )  // If pe2.value < pe1.value, pe1 is not a local minimum
                  {
                     mpRegionalMinimaGrid->SetValue( x, y, LABEL_NOLOCALMINIMUM);
                     mpFifo->push( pe1 );
                     
                     while ( !(mpFifo->empty() ))
                     {
                        PixelElement<int> pe3 = mpFifo->front();
                        mpFifo->pop();
                        
                        HandleFifoElementNeighbours( pe3, pe1);
                     }
                  }
               }
            }
         }
      }

      //-------------------------------------------------------------------------------
      
      template <class T >
      inline void WatershedMeyer< T >::ProcessFifoElementNeighbours( PixelElement<T> fifoElement )
      {
         int x = fifoElement.x;
         int y = fifoElement.y;
         for (int dy = -1; dy <= 1; dy++)
         {
            for (int dx = -1; dx <= 1; dx++)
            {
               if ( IsValidNeighbour( x, y, dx, dy ) )
               {
                  PixelElement<int> peNeighbour = CreatePixelElement(  x+dx, y+dy );
                  if( mpRegionalMinimaGrid->GetValue( x+dx, y+dy ) == LABEL_UNPROCESSED )
                  {
                     mpRegionalMinimaGrid->SetValue( x+dx, y+dy, mNumberOfLabels );
                     mpFifo->push( peNeighbour );
                  }
                  else if( mpRegionalMinimaGrid->GetValue( x+dx, y+dy ) == LABEL_NOLOCALMINIMUM )
                  {
                     mpRegionalMinimaGrid->SetValue(  x+dx, y+dy, LABEL_PROCESSING );
                     
                     mvSortedQueue.push( peNeighbour );
                  }
               }
            }
         }
      }

      //-------------------------------------------------------------------------------

      template <class T >
      inline void WatershedMeyer< T >::LocalMinimaDetection()
      {
         // 1) Initialize local minima detection
         
         mpRegionalMinimaGrid = new ArrayGrid<int>( mpDataInputImage->GetWidth(), mpDataInputImage->GetHeight());
         mpRegionalMinimaGrid->SetGridValues( LABEL_UNPROCESSED );
      
         // 2) Identify non-minima: check if a neighbour pixel has smaller intensity
         
         mpFifo = new queue< PixelElement<int> >();
         
         int width  = mpRegionalMinimaGrid->GetWidth();
         int height = mpRegionalMinimaGrid->GetHeight();
      
         for (int y = 0; y < height; y++)
         {
            for(int x = 0; x < width; x++)
            {
               if( mpRegionalMinimaGrid->GetValue( x, y ) == LABEL_UNPROCESSED)
               {
                  CheckForLocalMinimum( x, y);
               }
            }
         }
         
         delete mpFifo;
         mpFifo = new queue< PixelElement<int> >();
         mNumberOfLabels = LABEL_MINIMUM;
      
         // 3) process elements in fifo queue and their neighbours
         
         for (int y = 0; y < height; y++)
         {
            for(int x = 0; x < width; x++)
            {
               if( mpRegionalMinimaGrid->GetValue( x, y ) == LABEL_UNPROCESSED)
               {
                  mpRegionalMinimaGrid->SetValue( x, y, mNumberOfLabels);
                  
                  mpFifo->push( CreatePixelElement( x, y ) );
                  
                  while ( !(mpFifo->empty() ))
                  {
                     ProcessFifoElementNeighbours( mpFifo->front() );
                     mpFifo->pop();
                  }
                  mNumberOfLabels++;
               }
               else
               {
                  // skip this item
               }
            }
         }
         delete mpFifo;
      }
      
    //=========================================================================
   
    //  4.1.2 Flooding and subroutines

      template <class T >
      bool WatershedMeyer< T >::CheckForAlreadyLabeledNeighbours( int x, int y, Point<int>& outLabeledNeighbour, int& outLabel )
      {
         for (int dy = -1; dy <= 1; dy++)
         {
            for (int dx = -1; dx <= 1; dx++)
            {
               if ( IsValidNeighbour( x, y, dx, dy ) )
               {
                  if( mpRegionalMinimaGrid->GetValue( x+dx, y+dy ) > LABEL_RIDGE)
                  {
                     outLabeledNeighbour.SetXAndY( x+dx, y+dy);
                     outLabel = mpRegionalMinimaGrid->GetValue(x+dx, y+dy);
                     return true;
                  }
               }
            }
         }
         return false;
      }
      
      //---------------------------------------------------------------

      template <class T >
      bool WatershedMeyer< T >::CheckIfPixelIsWatershed( int x, int y, Point<int> inLabeledNeighbour, int inLabelOfNeighbour )
      {
         for (int dy = -1; dy <= 1; dy++)
         {
            for (int dx = -1; dx <= 1; dx++)
            {
               if ( this->IsValidNeighbour( x, y, dx, dy ) )
               {
                  if(    ( mpRegionalMinimaGrid->GetValue( x+dx, y+dy ) >= LABEL_MINIMUM )
                      && ( mpRegionalMinimaGrid->GetValue( x+dx, y+dy ) != mpRegionalMinimaGrid->GetValue( inLabeledNeighbour ) )
                      && ( ( inLabeledNeighbour.x != x+dx) || ( inLabeledNeighbour.y != y+dy))
                  )
                  {
                     mpRegionalMinimaGrid->SetValue( x, y, LABEL_RIDGE );
                     mvWatershedRidges.push_back( common::Point<int>( x, y ) );
                     mpLabelImage->SetValue( x, y, inLabelOfNeighbour );
                     return true;
                  }
               }
            }
         }
         return false;
      }
      
      //---------------------------------------------------------------

      template <class T >
      void WatershedMeyer< T >::UpdateLabel( int x, int y, int inLabelOfNeighbour )
      {
         // from c) assign label of neighbour
         mpRegionalMinimaGrid->SetValue( x, y, inLabelOfNeighbour );
      
         for (int dy = -1; dy <= 1; dy++)
         {
            for (int dx = -1; dx <= 1; dx++)
            {
               if ( IsValidNeighbour( x, y, dx, dy ) )
               {
                  if( mpRegionalMinimaGrid->GetValue( x+dx, y+dy ) == LABEL_NOLOCALMINIMUM )
                  {
                     mpRegionalMinimaGrid->SetValue( x+dx, y+dy, LABEL_PROCESSING );
                     PixelElement<int> pe = CreatePixelElement( x+dx, y+dy );
                     mvSortedQueue.push( pe );
                  }
               }
            }
         }
      }
      
      //---------------------------------------------------------------

      // The algorithm pops a PixelElement of the priority_queue. Because it was put in the queue, we know that it must 
      // have at least one neighbour that has already been assigned a label
      //
      // * pop one by one elements from fifo (a)
      //     - check for each popped element whether a neighbour was already assigned a final label
      //       - if several neighbours have different final labels, (b)
      //            pixel is marked as watershed pixel (stored separately from label grid) and gets label from first finally 
      //            labeled neighbour (label is ambiguous at watershed pixels however)
      //         else (c)
      //            pixel gets label from this finally labeled neighbour
      //            check neighbours of this pixel if they need to be added for processing
      // * finalize (d)
      template <class T >
      void WatershedMeyer< T >::Flooding()
      {
         int width  = mpDataInputImage->GetWidth();
         int height = mpDataInputImage->GetHeight();
      
         while ( !(mvSortedQueue.empty()))
         {
            PixelElement<int> lItemA = mvSortedQueue.top();  mvSortedQueue.pop();
            int labelOfNeighbour = 0;
            
            // (a) Pop element and find positive labeled neighbour
            stira::common::Point<int> alreadyLabeledNeighbour;
            int x = lItemA.x;
            int y = lItemA.y;
      
            // (b) Check if current pixel is watershed pixel by checking if there are different finally labeled neighbours
            if ( CheckForAlreadyLabeledNeighbours( x, y, alreadyLabeledNeighbour, labelOfNeighbour ) )
            {
               if ( ! ( CheckIfPixelIsWatershed( x, y, alreadyLabeledNeighbour, labelOfNeighbour ) ) )
               {
                  // c) if not watershed pixel, assign label of neighbour and add the LABEL_NOLOCALMINIMUM neighbours to priority_queue for processing
                  UpdateLabel( x, y, labelOfNeighbour );
               }
            }
         }
         
         // d) finalize the labelImage
         for (int y = 0; y < height; y++)
         {
            for (int x = 0; x < width; x++)
            {
               if( mpRegionalMinimaGrid->GetValue(x, y) != LABEL_RIDGE)
               {
                  mpLabelImage->SetValue(x, y, mpRegionalMinimaGrid->GetValue(x, y));
               }
            }
         }
      }

   //=====================================================================================

   //  4.2 Lower level helper methods

      template <class T >
      PixelElement<T> WatershedMeyer< T >::CreatePixelElement(int x, int y )
      {
         PixelElement<T> pe;
         pe.x = x;
         pe.y = y;
         pe.value = mpDataInputImage->GetValue( x, y );
         return pe;
      }
      
      //------------------------------------------------------------------------
      
      template <class T >
      PixelElement<T> WatershedMeyer< T >::CreatePixelElement( stira::common::Point<int> pt )
      {
         return CreatePixelElement( pt.x(), pt.y() );
      }
      
      //------------------------------------------------------------------------
      
      template <class T >
      bool WatershedMeyer< T >::IsValidNeighbour(int x, int y, int dx, int dy)
      {
         if ( (dx != 0 ) || (dy != 0) ) // otherwise, neighbour is pixel itself
         {
            int xx = x + dx;
            int yy = y + dy;
            if (     (xx >= 0) 
                  && (xx < mpRegionalMinimaGrid->GetWidth()) 
                  && (yy >= 0) 
                  && (yy < mpRegionalMinimaGrid->GetHeight())
               )
            {
               return true;
            }
         }
         return false;
      }
      
      //------------------------------------------------------------------------
      
      template <class T>
      bool WatershedMeyer< T >::IsElementSame( PixelElement<T> pe1, PixelElement<T> pe2)
      {
         double value1 = (double)( pe1.value ) / mPrecision;
         double value2 = (double)( pe2.value ) / mPrecision;
         return( floor(value1) == floor(value2) );
      }
      
      //------------------------------------------------------------------------
      
      template <class T >
      bool WatershedMeyer< T >::IsElementNoMinima( PixelElement<T> pe1, PixelElement<T> pe2)
      {
         if((double)( pe1.value ) >= mMaxMinima) //too large to be a minima
         {
            return(true);
         }
      
         double value1 = (double)( pe1.value )/mPrecision;
         double value2 = (double)( pe2.value )/mPrecision;
      
         return(floor(value2)<floor(value1));
      }

//------------------------------------------------------------------------

#undef LABEL_MINIMUM
#undef LABEL_RIDGE
#undef LABEL_NOLOCALMINIMUM
#undef LABEL_PROCESSING
#undef LABEL_UNPROCESSED
// =================================================================

}
}

#endif
