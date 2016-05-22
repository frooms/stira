
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

#ifndef STIRA_IMAGE_TOOLS_ARRAYGRIDTOOLS_H
#define STIRA_IMAGE_TOOLS_ARRAYGRIDTOOLS_H

#include "../datastructures/ArrayGrid.h"

namespace stira {
namespace image {

/**  \brief A class with operations to perform on a regular grid */
template <class T> 
class ArrayGridTools{
public:
   /** \brief constructor */
   ArrayGridTools();
  
   /** \brief destructor */
   ~ArrayGridTools();
  
   /**  \brief downsamples this grid (no interpolation is performed)
     *
     *   The reason that there is no interpolation before subsampling is that smoothing 
     *   is already performed in most pyramid decomposition schemes.
     *   The caller gets a newly created grid, that becomes his responsible to delete
     *  \param pGridIn the input grid (is left untouched)
     */
   static ArrayGrid<T>* DownSampleGrid( ArrayGrid<T>* pGridIn );
   
   /**  \brief Upsamples a band (no interpolation: newly inserted pixels are black)
    *
    *   The reason that there is no interpolation before subsampling is that smoothing (or interpolation)
    *   is performed directly after this method in most pyramid decomposition schemes.
    *   The caller gets a newly created band, and is responsible for deleting it after usage. Because of the 
    *   ambiguity (both width 2n-1 and 2n were downsampled to new width n), the upsampled width and height need 
    *   to be specified.
    *
    *   This method creates and returns a new object, that is the responsability of the caller to delete
    *
    *   \param pGridIn the input grid (is left untouched)
    *   \param upSampledWidth width of destination upsampled image
    *   \param upSampledHeight height of destination upsampled image
    *   \param myFactor factor with which all values in the grid are multiplied
    */
   static ArrayGrid<T>* UpSampleGrid( ArrayGrid<T>* pGridIn, int upSampledWidth, int upSampledHeight, double myFactor = 4.0);
   
   /** \brief Creates a grid object from an array
     * \param pArray array with source values
     * \param width width fo the source data
     * \param height height of the source data */
   static ArrayGrid<T>* CreateGridFromArray( T* pArray, int width, int height );

   /** \brief Creates a array from grid object
     * \param pGridIn grid with source values */
   static T* CreateArrayFromGrid( ArrayGrid<T>* pGridIn );
   
   /** \brief Creates a subgrid from a grid
     * \param pGridIn grid to extract subgrid from
     * \param xTop x coordinate of top left point in master grid to start extraction of subgrid (included in subgrid!)
     * \param yTop y coordinate of top left point in master grid to start extraction of subgrid (included in subgrid!)
     * \param xBottom x coordinate of bottom right point in master grid to stop extraction of subgrid (NOT included in subgrid!)
     * \param yBottom y coordinate of bottom right point in master grid to stop extraction of subgrid (NOT included in subgrid!)*/
   static ArrayGrid<T>* ExtractSubGrid( ArrayGrid<T>* pGridIn, int xTop, int yTop, int xBottom, int yBottom );
   
   /** \brief Copies values from a subgrid in a larger grid
     * \param pMasterGrid grid to write subgrid values to
     * \param pSubGrid grid to extract subgrid from
     * \param xTop x coordinate of top left point in master grid to start extraction of subgrid (included in subgrid!)
     * \param yTop y coordinate of top left point in master grid to start extraction of subgrid (included in subgrid!)
     * \param xBottom x coordinate of bottom right point in master grid to stop extraction of subgrid (NOT included in subgrid!)
     * \param yBottom y coordinate of bottom right point in master grid to stop extraction of subgrid (NOT included in subgrid!)*/
   static void InsertSubGrid( ArrayGrid<T>* pMasterGrid, ArrayGrid<T>* pSubGrid, int xTop, int yTop, int xBottom, int yBottom );

   /** \brief Creates copy of image which is circularly shifted */
   static ArrayGrid<T>* CircularShiftGrid( ArrayGrid<T>* pGridIn, int deltaX, int deltaY );
};

//===========================================================================================

/** \brief constructor */
template <class T>
inline ArrayGridTools<T>::ArrayGridTools() { }

/** \brief destructor */
template <class T>
inline ArrayGridTools<T>::~ArrayGridTools() {}


template <class T>
inline ArrayGrid<T>* ArrayGridTools<T>::DownSampleGrid( ArrayGrid<T>* pGridIn )
{
   int downSampledWidth  = (int)( (double)( pGridIn->GetWidth()  ) / 2.0 + 0.5);
   int downSampledHeight = (int)( (double)( pGridIn->GetHeight() ) / 2.0 + 0.5);

   ArrayGrid<T>* pDownSampledGrid = new ArrayGrid<T>( downSampledWidth, downSampledHeight );  // NOT initialized at construction

   for (int y = 0; y < downSampledHeight; y++)
   {
      for (int x = 0; x < downSampledWidth; x++)
      {
         pDownSampledGrid->SetValue( x, y, pGridIn->GetValue( 2 * x, 2 * y ) );
      }
   }

   return pDownSampledGrid;
}

//===================================================================================================

template <class T>
inline ArrayGrid<T>* ArrayGridTools<T>::UpSampleGrid( ArrayGrid<T>* pGridIn, int upSampledWidth, int upSampledHeight, double myFactor)
{
   assert ( pGridIn != 0);
   assert ( upSampledWidth  <= 2 * pGridIn->GetWidth()  + 1 );
   assert ( upSampledHeight <= 2 * pGridIn->GetHeight() + 1 );

   ArrayGrid<T>* pUpSampledGrid = new ArrayGrid<T>( upSampledWidth, upSampledHeight );
   pUpSampledGrid->SetGridValues( 0 );
   for (int y = 0; y < pGridIn->GetHeight(); y++)
   {
      for (int x = 0; x < pGridIn->GetWidth(); x++)
      {
         pUpSampledGrid->SetValue( 2 * x, 2 * y, myFactor * pGridIn->GetValue( x, y ) );
         // compensate for energy lost in downsampling by x 4
      }
   }
   
   return pUpSampledGrid;
}

//===================================================================================================

template <class T>
inline ArrayGrid<T>* ArrayGridTools<T>::CreateGridFromArray( T* pArray, int width, int height )
{
   ArrayGrid<T>* pGrid = new ArrayGrid<T>(width, height);  // NOT initialized at construction
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         pGrid->SetValue( x, y, pArray[x + width * y] );
      }
   }
   return pGrid;
}

//===================================================================================================

template <class T>
inline T* ArrayGridTools<T>::CreateArrayFromGrid( ArrayGrid<T>* pGridIn )
{
   int width  = pGridIn->GetWidth();
   int height = pGridIn->GetHeight();
   T* pArray = new T[ width * height];
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         pArray[x + width * y] = pGridIn->GetValue(x, y);
      }
   }
   return pArray;
}

//===================================================================================================

template <class T>
inline ArrayGrid<T>* ArrayGridTools<T>::ExtractSubGrid( ArrayGrid<T>* pGridIn, int xTop, int yTop, int xBottom, int yBottom )
{
   int sourceWidth  = pGridIn->GetWidth();
   int sourceHeight = pGridIn->GetHeight();
   
   assert ( xTop >= 0);
   assert ( yTop >= 0);
   assert ( xBottom >= 0);
   assert ( yBottom >= 0);
   assert ( xTop < sourceWidth );
   assert ( yTop < sourceHeight);
   assert ( xBottom <= sourceWidth );
   assert ( yBottom <= sourceHeight);
   
   assert ( xBottom > xTop );
   assert ( yBottom > yTop );
   
   int subWidth  = xBottom - xTop;
   int subHeight = yBottom - yTop;
   
   ArrayGrid<T>* pSubGrid = new ArrayGrid<T>(subWidth, subHeight);
   
   for (int y = 0; y < subHeight; y++)
   {
      for (int x = 0; x < subWidth; x++)
      {
         pSubGrid->SetValue(x, y, pGridIn->GetValue( x+xTop, y+yTop) );
      }
   }
   return pSubGrid;
}

//===================================================================================================

template <class T>
inline void ArrayGridTools<T>::InsertSubGrid( ArrayGrid<T>* pMasterGrid, ArrayGrid<T>* pSubGrid, int xTop, int yTop, int xBottom, int yBottom )
{
   int sourceWidth  = pMasterGrid->GetWidth();
   int sourceHeight = pMasterGrid->GetHeight();
   
   assert ( xTop >= 0);
   assert ( yTop >= 0);
   assert ( xBottom >= 0);
   assert ( yBottom >= 0);
   assert ( xTop < sourceWidth );
   assert ( yTop < sourceHeight);
   assert ( xBottom <= sourceWidth );
   assert ( yBottom <= sourceHeight);
   
   assert ( xBottom > xTop );
   assert ( yBottom > yTop );
   
   int subWidth  = xBottom - xTop;
   int subHeight = yBottom - yTop;
   
   for (int y = 0; y < subHeight; y++)
   {
      for (int x = 0; x < subWidth; x++)
      {
         pMasterGrid->SetValue(x+xTop, y+yTop, pSubGrid->GetValue( x, y) );
      }
   }
}


//===================================================================================================

template <class T>
inline ArrayGrid<T>* ArrayGridTools<T>::CircularShiftGrid( ArrayGrid<T>* pGridIn, int deltaX, int deltaY )
{
    int width  = pGridIn->GetWidth();
    int height = pGridIn->GetHeight();
    ArrayGrid<T>* pGridOut = new ArrayGrid<T>( width, height );

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int shiftX = x - deltaX;
            if (shiftX >= width) {shiftX -= width;}
            if (shiftX < 0) {shiftX += width;}
            int shiftY = y - deltaY;
            if (shiftY >= height) {shiftY -= height;}
            if (shiftY < 0) {shiftY += height;}
            pGridOut->SetValue(x, y, pGridIn->GetValue(shiftX, shiftY));
        }
    }
    return pGridOut;
}

//===================================================================================================

}
}

#endif
