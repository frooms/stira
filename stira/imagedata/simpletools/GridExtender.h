
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

#ifndef STIRA_IMAGE_TOOLS_GRIDEXTENDER_H
#define STIRA_IMAGE_TOOLS_GRIDEXTENDER_H

#include "../../imagedata/datastructures/ArrayGrid.h"

namespace stira {
namespace imagedata {

/**  \brief Extends input grid in a user-selected way
  */
template <class T> 
class GridExtender
{
public:
   enum ExtensionType {EXTEND_MIRROR, EXTEND_TILED, EXTEND_ZERO };
   
   /** \brief constructor*/
   GridExtender();
   
   /** \brief destructor*/
   ~GridExtender();
   
   /** \brief generates a new larger grid from the input grid values with a predefined border around
     * the extra border mirrors the values inside the image:
     *   Old: ... 9 8 5 7 3 6 | becomes ... 9 8 5 7 3 6 | 6 3 7 ...
     * \param pGrid the (smaller) input grid
     * \param borderWidth width of extra border left and right
     * \param borderHeight height of extra border top and bottom*/
   static ArrayGrid<T>* MirrorBorder( ArrayGrid<T>* pGrid, int borderWidth, int borderHeight);
   
   /** \brief generates a new larger grid from the input grid values with a border of predefined values around it
     * the extra border mirrors the values inside the image:
     *   Old: ... 9 8 5 7 3 6 | becomes ... 9 8 5 7 3 6 | myValue myValue myValue ...
     * \param pGrid the (smaller) input grid
     * \param borderWidth width of extra border left and right
     * \param borderHeight height of extra border top and bottom
     * \param myValue value used to fill the border*/
   static ArrayGrid<T>* PaddBorder( ArrayGrid<T>* pGrid, int borderWidth, int borderHeight, T myValue=0);

   /** \brief generates a new larger grid from the input grid values with a border of predefined values around it
     * the extra border mirrors the values inside the image:
     *   Old: ... 9 8 5 7 3 6 | becomes ... 9 8 5 7 3 6 | myValue myValue myValue ...
     * \param pGrid the (smaller) input grid
     * \param borderWidth width of extra border left and right
     * \param borderHeight height of extra border top and bottom
     * \param myValue value used to fill the border*/
   static ArrayGrid<T>* PaddBorder( ArrayGrid<T>* pGrid, int borderWidthLeft, int borderWidthRight, int borderHeightTop, int borderHeightBottom, T myValue=0);
   
   /** \brief generates a new smaller grid from the input grid values cropping a predefined border from it
     * \param pGrid the (larger) input grid
     * \param borderWidth width of border to crop from left and right
     * \param borderHeight height of border to crop from top and bottom*/
   static ArrayGrid<T>* CropBorder( ArrayGrid<T>* pGrid, int borderWidth, int borderHeight);
};

//=====================================================================================================================

template <class T>
GridExtender<T>::GridExtender()
{
}

//----------------------------------------------------------------------------

template <class T>
GridExtender<T>::~GridExtender()
{
}

//----------------------------------------------------------------------------

template <class T>
ArrayGrid<T>* GridExtender<T>::MirrorBorder( ArrayGrid<T>* pGrid, int borderWidth, int borderHeight)
{
   int width = pGrid->GetWidth();
   int height = pGrid->GetHeight();

   int expandedWidth  = width  + 2 * borderWidth;
   int expandedHeight = height + 2 * borderHeight;

   if ((borderWidth >= 0) && (borderHeight >= 0))
   {
      ArrayGrid<T>* pExpandedGrid = new ArrayGrid<T>(expandedWidth, expandedHeight);  // NOT initialized at construction
      
      for (int yExpanded = 0; yExpanded < expandedHeight; yExpanded++)
      {
         for (int xExpanded = 0; xExpanded < expandedWidth; xExpanded ++)
         {
            int x = xExpanded - borderWidth;
            if (x < 0)
            {
               x = borderWidth - (xExpanded + 1);
            }
            if (x > width - 1)
            {
               x = borderWidth + 2 * width - 1 - xExpanded;
            }
            int y = yExpanded - borderHeight;
            if (y < 0)
            {
               y = borderHeight - (yExpanded + 1);
            }
            if (y > height - 1)
            {
               y = borderHeight + 2 * height - 1 - yExpanded;
            }
            
            pExpandedGrid->SetValue(xExpanded, yExpanded, pGrid->GetValue(x, y));
         }
      }
      return pExpandedGrid;
   }
   else
   {
      std::cerr << "Tried to extend grid with illegal border sizes (" << borderWidth << ", " << borderHeight << ")" << std::endl << std::flush;
      return 0;
   }
}

//----------------------------------------------------------------------------------

template <class T>
ArrayGrid<T>* GridExtender<T>::PaddBorder( ArrayGrid<T>* pGrid, int borderWidth, int borderHeight, T myValue )
{
   int width = pGrid->GetWidth();
   int height = pGrid->GetHeight();

   int expandedWidth  = width  + 2 * borderWidth;
   int expandedHeight = height + 2 * borderHeight;
   bool needsInitialization = true;
   if ((borderWidth >= 0) && (borderHeight >= 0))
   {
      ArrayGrid<T>* pExpandedGrid = new ArrayGrid<T>(expandedWidth, expandedHeight, needsInitialization, myValue );
      
      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x ++)
         {
            pExpandedGrid->SetValue( x + borderWidth, y + borderHeight, pGrid->GetValue( x, y ) );
         }
      }
      return pExpandedGrid;
   }
   else
   {
      std::cerr << "Tried to extend grid with illegal border sizes (" << borderWidth << ", " << borderHeight << ")" << std::endl << std::flush;
      return 0;
   }
}

//----------------------------------------------------------------------------------

template <class T>
ArrayGrid<T>* GridExtender<T>::PaddBorder( ArrayGrid<T>* pGrid, int borderWidthLeft, int borderWidthRight, int borderHeightTop, int borderHeightBottom, T myValue)
{
   int width = pGrid->GetWidth();
   int height = pGrid->GetHeight();

   int expandedWidth  = width  + borderWidthLeft + borderWidthRight;
   int expandedHeight = height + borderHeightTop + borderHeightBottom;
   bool needsInitialization = true;
   if ((borderWidthLeft >= 0) && (borderWidthRight >= 0) && (borderHeightTop >= 0) && (borderHeightBottom >= 0))
   {
      ArrayGrid<T>* pExpandedGrid = new ArrayGrid<T>(expandedWidth, expandedHeight, needsInitialization, myValue );

      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x ++)
         {
            pExpandedGrid->SetValue( x + borderWidthLeft, y + borderHeightTop, pGrid->GetValue( x, y ) );
         }
      }
      return pExpandedGrid;
   }
   else
   {
      std::cerr << "Tried to extend grid with illegal border sizes (" <<  borderWidthLeft << ", " << borderWidthRight << ", " << borderHeightTop << ", " << borderHeightBottom << ")" << std::endl << std::flush;
      return 0;
   }
}

//----------------------------------------------------------------------------------

template <class T>
ArrayGrid<T>* GridExtender<T>::CropBorder( ArrayGrid<T>* pGrid, int borderWidth, int borderHeight)
{
   int width = pGrid->GetWidth();
   int height = pGrid->GetHeight();
  
   int croppedWidth  = width  - 2 * borderWidth;
   int croppedHeight = height - 2 * borderHeight;
   
   if ( ( borderWidth >= 0 ) && ( borderHeight >= 0 ) )
   {
      if ( ( croppedWidth > 5 ) && ( croppedHeight > 5 ) )
      {
         ArrayGrid<T>* pCroppedGrid = new ArrayGrid<T>( croppedWidth, croppedHeight) ;  // NOT initialized at construction
         
         for ( int yCropped = 0; yCropped < croppedHeight; yCropped++ )
         {
            for ( int xCropped = 0; xCropped < croppedWidth; xCropped ++ )
            {
               int x = xCropped + borderWidth;
               int y = yCropped + borderHeight;
            
               pCroppedGrid->SetValue( xCropped, yCropped, pGrid->GetValue( x, y ) );
            }
         }
         return pCroppedGrid;
      }
      else
      {
         std::cerr << "Grid would be to small after cropping: sizes (" << croppedWidth << ", " << croppedHeight << ")" << std::endl << std::flush;
         return 0;
      }
   }
   else
   {
      std::cerr << "Tried to crop grid with illegal border sizes (" << borderWidth << ", " << borderHeight << ")" << std::endl << std::flush;
      return 0;
   }
}

//----------------------------------------------------------------------------

}
}

#endif
