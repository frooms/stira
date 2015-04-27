
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

#ifndef STIRA_IMAGEANALYSIS_THINNING_H
#define STIRA_IMAGEANALYSIS_THINNING_H

#include "../../common/common/RectangularROI.h"
#include "../../common/common/MathUtils.h"
#include "../../image/datastructures/Image.h"

namespace stira {
namespace imageanalysis {

/** \brief Morphological thinning: applies the following set of structure elements;
  * <PRE>
  * [ 0 0 0 ]    [ 0   1 ]    [ 1 1 1 ]    [ 1   0 ]
  * [   1   ]    [ 0 1 1 ]    [   1   ]    [ 1 1 0 ]
  * [ 1 1 1 ]    [ 0   1 ]    [ 0 0 0 ]    [ 1   0 ]
  *
  * [   0 0 ]    [   1   ]    [   1   ]    [ 0 0   ]
  * [ 1 1 0 ]    [ 1 1 0 ]    [ 0 1 1 ]    [ 0 1 1 ]
  * [   1   ]    [   0 0 ]    [ 0 0   ]    [   1   ]
  * </PRE>
  * if one of the structure elements fits, the central pixel is set to the value of
  * the neighbouring 0. This process is repeated until nothing changes anymore
  *
  * Pruning end branches: only if we assume structure goes from border to border in image;
  * otherwise all structure will be "eaten"
  *
  * <PRE>
  * [ 1 0 0 ]    [ 0 1 0 ]    [ 0 0 1 ]    [ 0 0 0 ]
  * [ 0 1 0 ]    [ 0 1 0 ]    [ 0 1 0 ]    [ 0 1 1 ]
  * [ 0 0 0 ]    [ 0 0 0 ]    [ 0 0 0 ]    [ 0 0 0 ]
  *
  * [ 0 0 0 ]    [ 0 0 0 ]    [ 0 0 0 ]    [ 0 0 0 ]
  * [ 0 1 0 ]    [ 0 1 0 ]    [ 0 1 0 ]    [ 1 1 0 ]
  * [ 0 0 1 ]    [ 0 1 0 ]    [ 1 0 0 ]    [ 0 0 0 ]
  * </PRE>
  * if one of the structure elements fits, the central pixel is set to the value of
  * the neighbouring 0. This process is repeated until nothing changes anymore
  */
template <class T>
class Thinning
{
public:
   /** \brief constructor */
   Thinning();

   /** \brief destructor */
   ~Thinning();

   /** \brief run method
     * \param pGridIn input grid
     * \param value value that is considered "foreground"
     * \return new grid with result after thinning; responsability of the caller to delete this*/
   image::ArrayGrid<T>* RunThinning( image::ArrayGrid<T>* pGridIn, common::RectangularROI<int> rroi, T value );

   /** \brief run method
     * \param pGridIn input grid
     * \param value value that is considered "foreground"
     * \return new grid with result after pruning; responsability of the caller to delete this*/
   image::ArrayGrid<T>* RunPruning( image::ArrayGrid<T>* pGridIn, common::RectangularROI<int> rroi, T value );

private:
   /** \brief swipes raster once and applies set of 8 strcuture elements each once per pixel
     * \param pGridIn input grid
     * \param value value that is considered "foreground"
     * \return number of pixels that were thinned during this sweep*/
   int SingleThinningSweep( image::ArrayGrid<T>* pGridIn, common::RectangularROI<int> rroi, T value );

// we assume that the test if the central pixel equals value is done separately before the following
// tests are performed

   /** \brief checks first structure elements for pixel position (x, y)
     * \param pGridIn input grid
     * \param x x coordinate of pixel to check
     * \param y y coordinate of pixel to check
     * \param value value that is considered "foreground"
     * \return 1 if pixel was removed; 0 otherwise*/
   int ThinElement1( image::ArrayGrid<T>* pGridIn, int x, int y, T value );

   /** \brief checks secondfirst structure elements for pixel position (x, y)
     * \param pGridIn input grid
     * \param x x coordinate of pixel to check
     * \param y y coordinate of pixel to check
     * \param value value that is considered "foreground"
     * \return 1 if pixel was removed; 0 otherwise*/
   int ThinElement2( image::ArrayGrid<T>* pGridIn, int x, int y, T value );

   /** \brief checks third structure elements for pixel position (x, y)
     * \param pGridIn input grid
     * \param x x coordinate of pixel to check
     * \param y y coordinate of pixel to check
     * \param value value that is considered "foreground"
     * \return 1 if pixel was removed; 0 otherwise*/
   int ThinElement3( image::ArrayGrid<T>* pGridIn, int x, int y, T value );

   /** \brief checks fourth structure elements for pixel position (x, y)
     * \param pGridIn input grid
     * \param x x coordinate of pixel to check
     * \param y y coordinate of pixel to check
     * \param value value that is considered "foreground"
     * \return 1 if pixel was removed; 0 otherwise*/
   int ThinElement4( image::ArrayGrid<T>* pGridIn, int x, int y, T value );

   /** \brief checks fifth structure elements for pixel position (x, y)
     * \param pGridIn input grid
     * \param x x coordinate of pixel to check
     * \param y y coordinate of pixel to check
     * \param value value that is considered "foreground"
     * \return 1 if pixel was removed; 0 otherwise*/
   int ThinElement5( image::ArrayGrid<T>* pGridIn, int x, int y, T value );

   /** \brief checks sixth structure elements for pixel position (x, y)
     * \param pGridIn input grid
     * \param x x coordinate of pixel to check
     * \param y y coordinate of pixel to check
     * \param value value that is considered "foreground"
     * \return 1 if pixel was removed; 0 otherwise*/
   int ThinElement6( image::ArrayGrid<T>* pGridIn, int x, int y, T value );

   /** \brief checks seventh structure elements for pixel position (x, y)
     * \param pGridIn input grid
     * \param x x coordinate of pixel to check
     * \param y y coordinate of pixel to check
     * \param value value that is considered "foreground"
     * \return 1 if pixel was removed; 0 otherwise*/
   int ThinElement7( image::ArrayGrid<T>* pGridIn, int x, int y, T value );

   /** \brief checks eightth structure elements for pixel position (x, y)
     * \param pGridIn input grid
     * \param x x coordinate of pixel to check
     * \param y y coordinate of pixel to check
     * \param value value that is considered "foreground"
     * \return 1 if pixel was removed; 0 otherwise*/
   int ThinElement8( image::ArrayGrid<T>* pGridIn, int x, int y, T value );




   /** \brief swipes raster once and applies set of 8 strcuture elements each once per pixel
     * \param pGridIn input grid
     * \param value value that is considered "foreground"
     * \return number of pixels that were thinned during this sweep*/
   int SinglePruningSweep( image::ArrayGrid<T>* pGridIn, common::RectangularROI<int> rroi, T value );

// we assume that the test if the central pixel equals value is done separately before the following
// tests are performed

   /** \brief checks first structure elements for pixel position (x, y)
     * \param pGridIn input grid
     * \param x x coordinate of pixel to check
     * \param y y coordinate of pixel to check
     * \param value value that is considered "foreground"
     * \return 1 if pixel was removed; 0 otherwise*/
   int PruneElement1( image::ArrayGrid<T>* pGridIn, int x, int y, T value );

   /** \brief checks secondfirst structure elements for pixel position (x, y)
     * \param pGridIn input grid
     * \param x x coordinate of pixel to check
     * \param y y coordinate of pixel to check
     * \param value value that is considered "foreground"
     * \return 1 if pixel was removed; 0 otherwise*/
   int PruneElement2( image::ArrayGrid<T>* pGridIn, int x, int y, T value );

   /** \brief checks third structure elements for pixel position (x, y)
     * \param pGridIn input grid
     * \param x x coordinate of pixel to check
     * \param y y coordinate of pixel to check
     * \param value value that is considered "foreground"
     * \return 1 if pixel was removed; 0 otherwise*/
   int PruneElement3( image::ArrayGrid<T>* pGridIn, int x, int y, T value );

   /** \brief checks fourth structure elements for pixel position (x, y)
     * \param pGridIn input grid
     * \param x x coordinate of pixel to check
     * \param y y coordinate of pixel to check
     * \param value value that is considered "foreground"
     * \return 1 if pixel was removed; 0 otherwise*/
   int PruneElement4( image::ArrayGrid<T>* pGridIn, int x, int y, T value );

   /** \brief checks fifth structure elements for pixel position (x, y)
     * \param pGridIn input grid
     * \param x x coordinate of pixel to check
     * \param y y coordinate of pixel to check
     * \param value value that is considered "foreground"
     * \return 1 if pixel was removed; 0 otherwise*/
   int PruneElement5( image::ArrayGrid<T>* pGridIn, int x, int y, T value );

   /** \brief checks sixth structure elements for pixel position (x, y)
     * \param pGridIn input grid
     * \param x x coordinate of pixel to check
     * \param y y coordinate of pixel to check
     * \param value value that is considered "foreground"
     * \return 1 if pixel was removed; 0 otherwise*/
   int PruneElement6( image::ArrayGrid<T>* pGridIn, int x, int y, T value );

   /** \brief checks seventh structure elements for pixel position (x, y)
     * \param pGridIn input grid
     * \param x x coordinate of pixel to check
     * \param y y coordinate of pixel to check
     * \param value value that is considered "foreground"
     * \return 1 if pixel was removed; 0 otherwise*/
   int PruneElement7( image::ArrayGrid<T>* pGridIn, int x, int y, T value );

   /** \brief checks eightth structure elements for pixel position (x, y)
     * \param pGridIn input grid
     * \param x x coordinate of pixel to check
     * \param y y coordinate of pixel to check
     * \param value value that is considered "foreground"
     * \return 1 if pixel was removed; 0 otherwise*/
   int PruneElement8( image::ArrayGrid<T>* pGridIn, int x, int y, T value );
};

//=========================================================================

template <class T>
Thinning<T>::Thinning()
{
}

//----------------------------------------------------------------
template <class T>
Thinning<T>::~Thinning()
{
}

//----------------------------------------------------------------

template <class T>
      image::ArrayGrid<T>* Thinning<T>::RunThinning( image::ArrayGrid<T>* pGridIn, common::RectangularROI<int> rroi, T value )
{
   image::ArrayGrid<T>* pGridThinned = pGridIn->Clone();
   int nrPixelsThinned = SingleThinningSweep( pGridThinned, rroi, value );

   while (nrPixelsThinned > 0)
   {
      nrPixelsThinned = SingleThinningSweep( pGridThinned, rroi, value );
   }
   return pGridThinned;
}

//----------------------------------------------------------------

template <class T>
int Thinning<T>::SingleThinningSweep( image::ArrayGrid<T>* pGridThinning, common::RectangularROI<int> rroi, T value )
{
   int height = pGridThinning->GetHeight();
   int width  = pGridThinning->GetWidth();

   int minX = rroi.GetTopLeftCorner().GetX();
   int minY = rroi.GetTopLeftCorner().GetY();
   int maxX = rroi.GetBottomRightCorner().GetX();
   int maxY = rroi.GetBottomRightCorner().GetY();

   common::MathUtils::ClipValue( minX, 1, width - 1 );
   common::MathUtils::ClipValue( maxX, 1, width - 1 );
   common::MathUtils::ClipValue( minY, 1, height - 1 );
   common::MathUtils::ClipValue( maxY, 1, height - 1 );

   int nrPixelsThinned = 0;
   for (int y = minY; y < maxY; y++)
   {
      for (int x = minX; x < maxX; x++)
      {
         if (pGridThinning->GetValue( x, y) == value) // test for central pixel of structure element
         {
            nrPixelsThinned += ThinElement1( pGridThinning, x, y, value );
            nrPixelsThinned += ThinElement2( pGridThinning, x, y, value );
            nrPixelsThinned += ThinElement3( pGridThinning, x, y, value );
            nrPixelsThinned += ThinElement4( pGridThinning, x, y, value );
            nrPixelsThinned += ThinElement5( pGridThinning, x, y, value );
            nrPixelsThinned += ThinElement6( pGridThinning, x, y, value );
            nrPixelsThinned += ThinElement7( pGridThinning, x, y, value );
            nrPixelsThinned += ThinElement8( pGridThinning, x, y, value );
         }
      }
   }
   return nrPixelsThinned;
}

//----------------------------------------------------------------


//  0 0 0
//    1
//  1 1 1
template <class T>
int Thinning<T>::ThinElement1( image::ArrayGrid<T>* pGridIn, int x, int y, T value )
{
   if (    (pGridIn->GetValue( x-1, y-1) != value)
        && (pGridIn->GetValue( x  , y-1) != value)
        && (pGridIn->GetValue( x+1, y-1) != value)
        && (pGridIn->GetValue( x-1, y+1) == value)
        && (pGridIn->GetValue( x  , y+1) == value)
        && (pGridIn->GetValue( x+1, y+1) == value)
      )
   {
      pGridIn->SetValue( x, y, pGridIn->GetValue( x  , y-1) );
      return 1;
   }
   else
   {
      return 0;
   }
}

//----------------------------------------------------------------

//  0   1
//  0 1 1
//  0   1
template <class T>
int Thinning<T>::ThinElement2( image::ArrayGrid<T>* pGridIn, int x, int y, T value )
{
   if (    (pGridIn->GetValue( x-1, y-1) != value)
        && (pGridIn->GetValue( x-1, y  ) != value)
        && (pGridIn->GetValue( x-1, y+1) != value)
        && (pGridIn->GetValue( x+1, y-1) == value)
        && (pGridIn->GetValue( x+1, y  ) == value)
        && (pGridIn->GetValue( x+1, y+1) == value)
      )
   {
      pGridIn->SetValue( x, y, pGridIn->GetValue( x-1, y ) );
      return 1;
   }
   else
   {
      return 0;
   }
}

//----------------------------------------------------------------

//  1 1 1
//    1
//  0 0 0
template <class T>
int Thinning<T>::ThinElement3( image::ArrayGrid<T>* pGridIn, int x, int y, T value )
{
   if (    (pGridIn->GetValue( x-1, y-1) == value)
        && (pGridIn->GetValue( x  , y-1) == value)
        && (pGridIn->GetValue( x+1, y-1) == value)
        && (pGridIn->GetValue( x-1, y+1) != value)
        && (pGridIn->GetValue( x  , y+1) != value)
        && (pGridIn->GetValue( x+1, y+1) != value)
      )
   {
      pGridIn->SetValue( x, y, pGridIn->GetValue( x  , y+1) );
      return 1;
   }
   else
   {
      return 0;
   }
}

//----------------------------------------------------------------

//  1   0
//  1 1 0
//  1   0
template <class T>
int Thinning<T>::ThinElement4( image::ArrayGrid<T>* pGridIn, int x, int y, T value )
{
   if (    (pGridIn->GetValue( x-1, y-1) == value)
        && (pGridIn->GetValue( x-1, y  ) == value)
        && (pGridIn->GetValue( x-1, y+1) == value)
        && (pGridIn->GetValue( x+1, y-1) != value)
        && (pGridIn->GetValue( x+1, y  ) != value)
        && (pGridIn->GetValue( x+1, y+1) != value)
      )
   {
      pGridIn->SetValue( x, y, pGridIn->GetValue( x+1, y ) );
      return 1;
   }
   else
   {
      return 0;
   }
}

//----------------------------------------------------------------

//    0 0
//  1 1 0
//    1
template <class T>
int Thinning<T>::ThinElement5( image::ArrayGrid<T>* pGridIn, int x, int y, T value )
{
   if (    (pGridIn->GetValue( x  , y-1) != value)
        && (pGridIn->GetValue( x+1, y-1) != value)
        && (pGridIn->GetValue( x+1, y  ) != value)
        && (pGridIn->GetValue( x-1, y  ) == value)
        && (pGridIn->GetValue( x  , y+1) == value)
      )
   {
      pGridIn->SetValue( x, y, pGridIn->GetValue( x+1, y-1 ) );
      return 1;
   }
   else
   {
      return 0;
   }
}

//----------------------------------------------------------------

//    1
//  1 1 0
//    0 0
template <class T>
int Thinning<T>::ThinElement6( image::ArrayGrid<T>* pGridIn, int x, int y, T value )
{
   if (    (pGridIn->GetValue( x  , y-1) == value)
        && (pGridIn->GetValue( x-1, y  ) == value)
        && (pGridIn->GetValue( x+1, y  ) != value)
        && (pGridIn->GetValue( x  , y+1) != value)
        && (pGridIn->GetValue( x+1, y+1) != value)
      )
   {
      pGridIn->SetValue( x, y, pGridIn->GetValue( x+1, y+1 ) );
      return 1;
   }
   else
   {
      return 0;
   }
}

//----------------------------------------------------------------

//    1
//  0 1 1
//  0 0
template <class T>
int Thinning<T>::ThinElement7( image::ArrayGrid<T>* pGridIn, int x, int y, T value )
{
   if (    (pGridIn->GetValue( x  , y-1) == value)
        && (pGridIn->GetValue( x-1, y  ) == value)
        && (pGridIn->GetValue( x+1, y  ) != value)
        && (pGridIn->GetValue( x  , y+1) != value)
        && (pGridIn->GetValue( x+1, y+1) != value)
      )
   {
      pGridIn->SetValue( x, y, pGridIn->GetValue( x+1, y+1 ) );
      return 1;
   }
   else
   {
      return 0;
   }
}

//----------------------------------------------------------------

// 0 0
// 0 1 1
//   1
template <class T>
int Thinning<T>::ThinElement8( image::ArrayGrid<T>* pGridIn, int x, int y, T value )
{
   if (    (pGridIn->GetValue( x  , y-1) == value)
        && (pGridIn->GetValue( x-1, y  ) == value)
        && (pGridIn->GetValue( x+1, y  ) != value)
        && (pGridIn->GetValue( x  , y+1) != value)
        && (pGridIn->GetValue( x+1, y+1) != value)
      )
   {
      pGridIn->SetValue( x, y, pGridIn->GetValue( x+1, y+1 ) );
      return 1;
   }
   else
   {
      return 0;
   }
}

//----------------------------------------------------------------

template <class T>
image::ArrayGrid<T>* Thinning<T>::RunPruning( image::ArrayGrid<T>* pGridIn, common::RectangularROI<int> rroi, T value )
{
   image::ArrayGrid<T>* pGridPruned = pGridIn->Clone();
   int nrPixelsPruned = SinglePruningSweep( pGridPruned, rroi, value );

   while (nrPixelsPruned > 0)
   {
      nrPixelsPruned = SinglePruningSweep( pGridPruned, rroi, value );
   }
   return pGridPruned;
}

//----------------------------------------------------------------

template <class T>
int Thinning<T>::SinglePruningSweep( image::ArrayGrid<T>* pGridPruning, common::RectangularROI<int> rroi, T value )
{
   int height = pGridPruning->GetHeight();
   int width  = pGridPruning->GetWidth();

   int minX = rroi.GetTopLeftCorner().GetX();
   int minY = rroi.GetTopLeftCorner().GetY();
   int maxX = rroi.GetBottomRightCorner().GetX();
   int maxY = rroi.GetBottomRightCorner().GetY();

   common::MathUtils::ClipValue( minX, 1, width - 1 );
   common::MathUtils::ClipValue( maxX, 1, width - 1 );
   common::MathUtils::ClipValue( minY, 1, height - 1 );
   common::MathUtils::ClipValue( maxY, 1, height - 1 );

   int nrPixelsPruned = 0;
   for (int y = minY; y < maxY; y++)
   {
      for (int x = minX; x < maxX; x++)
      {
         if ( pGridPruning->GetValue( x, y) == value) // test for central pixel of structure element
         {
            nrPixelsPruned += PruneElement1( pGridPruning, x, y, value );
            nrPixelsPruned += PruneElement2( pGridPruning, x, y, value );
            nrPixelsPruned += PruneElement3( pGridPruning, x, y, value );
            nrPixelsPruned += PruneElement4( pGridPruning, x, y, value );
            nrPixelsPruned += PruneElement5( pGridPruning, x, y, value );
            nrPixelsPruned += PruneElement6( pGridPruning, x, y, value );
            nrPixelsPruned += PruneElement7( pGridPruning, x, y, value );
            nrPixelsPruned += PruneElement8( pGridPruning, x, y, value );
         }
      }
   }
   return nrPixelsPruned;
}

//----------------------------------------------------------------

//  1 0 0
//  0 1 0
//  0 0 0
template <class T>
int Thinning<T>::PruneElement1( image::ArrayGrid<T>* pGridIn, int x, int y, T value )
{
   if (    (pGridIn->GetValue( x-1, y-1) == value)
        && (pGridIn->GetValue( x  , y-1) != value)
        && (pGridIn->GetValue( x+1, y-1) != value)

        && (pGridIn->GetValue( x-1, y  ) != value)
        && (pGridIn->GetValue( x  , y  ) == value)
        && (pGridIn->GetValue( x+1, y  ) != value)

        && (pGridIn->GetValue( x-1, y+1) != value)
        && (pGridIn->GetValue( x  , y+1) != value)
        && (pGridIn->GetValue( x+1, y+1) != value)
      )
   {
      pGridIn->SetValue( x, y, pGridIn->GetValue( x  , y-1) );
      return 1;
   }
   else
   {
      return 0;
   }
}

//----------------------------------------------------------------

//  0 1 0
//  0 1 0
//  0 0 0
template <class T>
int Thinning<T>::PruneElement2( image::ArrayGrid<T>* pGridIn, int x, int y, T value )
{
   if (    (pGridIn->GetValue( x-1, y-1) != value)
        && (pGridIn->GetValue( x  , y-1) == value)
        && (pGridIn->GetValue( x+1, y-1) != value)

        && (pGridIn->GetValue( x-1, y  ) != value)
        && (pGridIn->GetValue( x  , y  ) == value)
        && (pGridIn->GetValue( x+1, y  ) != value)

        && (pGridIn->GetValue( x-1, y+1) != value)
        && (pGridIn->GetValue( x  , y+1) != value)
        && (pGridIn->GetValue( x+1, y+1) != value)
      )
   {
      pGridIn->SetValue( x, y, pGridIn->GetValue( x  , y-1) );
      return 1;
   }
   else
   {
      return 0;
   }
}

//----------------------------------------------------------------

//  0 0 1
//  0 1 0
//  0 0 0
template <class T>
int Thinning<T>::PruneElement3( image::ArrayGrid<T>* pGridIn, int x, int y, T value )
{
   if (    (pGridIn->GetValue( x-1, y-1) != value)
        && (pGridIn->GetValue( x  , y-1) != value)
        && (pGridIn->GetValue( x+1, y-1) == value)

        && (pGridIn->GetValue( x-1, y  ) != value)
        && (pGridIn->GetValue( x  , y  ) == value)
        && (pGridIn->GetValue( x+1, y  ) != value)

        && (pGridIn->GetValue( x-1, y+1) != value)
        && (pGridIn->GetValue( x  , y+1) != value)
        && (pGridIn->GetValue( x+1, y+1) != value)
      )
   {
      pGridIn->SetValue( x, y, pGridIn->GetValue( x  , y-1) );
      return 1;
   }
   else
   {
      return 0;
   }
}

//----------------------------------------------------------------

//  0 0 0
//  0 1 1
//  0 0 0
template <class T>
int Thinning<T>::PruneElement4( image::ArrayGrid<T>* pGridIn, int x, int y, T value )
{
   if (    (pGridIn->GetValue( x-1, y-1) != value)
        && (pGridIn->GetValue( x  , y-1) != value)
        && (pGridIn->GetValue( x+1, y-1) != value)

        && (pGridIn->GetValue( x-1, y  ) != value)
        && (pGridIn->GetValue( x  , y  ) == value)
        && (pGridIn->GetValue( x+1, y  ) == value)

        && (pGridIn->GetValue( x-1, y+1) != value)
        && (pGridIn->GetValue( x  , y+1) != value)
        && (pGridIn->GetValue( x+1, y+1) != value)
      )
   {
      pGridIn->SetValue( x, y, pGridIn->GetValue( x  , y-1) );
      return 1;
   }
   else
   {
      return 0;
   }
}

//----------------------------------------------------------------

//  0 0 0
//  0 1 0
//  0 0 1
template <class T>
int Thinning<T>::PruneElement5( image::ArrayGrid<T>* pGridIn, int x, int y, T value )
{
   if (    (pGridIn->GetValue( x-1, y-1) != value)
        && (pGridIn->GetValue( x  , y-1) != value)
        && (pGridIn->GetValue( x+1, y-1) != value)

        && (pGridIn->GetValue( x-1, y  ) != value)
        && (pGridIn->GetValue( x  , y  ) == value)
        && (pGridIn->GetValue( x+1, y  ) != value)

        && (pGridIn->GetValue( x-1, y+1) != value)
        && (pGridIn->GetValue( x  , y+1) != value)
        && (pGridIn->GetValue( x+1, y+1) == value)
      )
   {
      pGridIn->SetValue( x, y, pGridIn->GetValue( x  , y-1) );
      return 1;
   }
   else
   {
      return 0;
   }
}

//----------------------------------------------------------------

//  0 0 0
//  0 1 0
//  0 1 0
template <class T>
int Thinning<T>::PruneElement6( image::ArrayGrid<T>* pGridIn, int x, int y, T value )
{
   if (    (pGridIn->GetValue( x-1, y-1) != value)
        && (pGridIn->GetValue( x  , y-1) != value)
        && (pGridIn->GetValue( x+1, y-1) != value)

        && (pGridIn->GetValue( x-1, y  ) != value)
        && (pGridIn->GetValue( x  , y  ) == value)
        && (pGridIn->GetValue( x+1, y  ) != value)

        && (pGridIn->GetValue( x-1, y+1) != value)
        && (pGridIn->GetValue( x  , y+1) == value)
        && (pGridIn->GetValue( x+1, y+1) != value)
      )
   {
      pGridIn->SetValue( x, y, pGridIn->GetValue( x  , y-1) );
      return 1;
   }
   else
   {
      return 0;
   }
}

//----------------------------------------------------------------

//  0 0 0
//  0 1 0
//  0 1 0
template <class T>
int Thinning<T>::PruneElement7( image::ArrayGrid<T>* pGridIn, int x, int y, T value )
{
   if (    (pGridIn->GetValue( x-1, y-1) != value)
        && (pGridIn->GetValue( x  , y-1) != value)
        && (pGridIn->GetValue( x+1, y-1) != value)

        && (pGridIn->GetValue( x-1, y  ) != value)
        && (pGridIn->GetValue( x  , y  ) == value)
        && (pGridIn->GetValue( x+1, y  ) != value)

        && (pGridIn->GetValue( x-1, y+1) != value)
        && (pGridIn->GetValue( x  , y+1) == value)
        && (pGridIn->GetValue( x+1, y+1) != value)
      )
   {
      pGridIn->SetValue( x, y, pGridIn->GetValue( x  , y-1) );
      return 1;
   }
   else
   {
      return 0;
   }
}

//----------------------------------------------------------------

//  0 0 0
//  0 1 0
//  1 0 0
template <class T>
int Thinning<T>::PruneElement8( image::ArrayGrid<T>* pGridIn, int x, int y, T value )
{
   if (    (pGridIn->GetValue( x-1, y-1) != value)
        && (pGridIn->GetValue( x  , y-1) != value)
        && (pGridIn->GetValue( x+1, y-1) != value)

        && (pGridIn->GetValue( x-1, y  ) != value)
        && (pGridIn->GetValue( x  , y  ) == value)
        && (pGridIn->GetValue( x+1, y  ) != value)

        && (pGridIn->GetValue( x-1, y+1) == value)
        && (pGridIn->GetValue( x  , y+1) != value)
        && (pGridIn->GetValue( x+1, y+1) != value)
      )
   {
      pGridIn->SetValue( x, y, pGridIn->GetValue( x  , y-1) );
      return 1;
   }
   else
   {
      return 0;
   }
}

//==============================================================================

}
}

#endif
