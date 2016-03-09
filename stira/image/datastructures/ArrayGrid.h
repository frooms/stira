
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

#ifndef STIRA_IMAGE_DATASTRUCTURES_ARRAYGRID_H
#define STIRA_IMAGE_DATASTRUCTURES_ARRAYGRID_H

#include <stdint.h>
#include <iostream>
#include <cassert>
#include <fstream>
#include <cfloat>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <complex>
#include <string>

#include "../../common/common/Point.h"

// extra debug diagnoses when calling method GetMinMax()
//#ifdef CHECK_INF_OR_NAN_VALUES

#define USE_BOUNDARY_CHECKS

namespace stira {
namespace image {

/**  \brief A class to contain a regular grid of integer or float numbers, structs and even more complex objects */
template <class T>
class ArrayGrid{

   // 0. CONSTRUCT / DESTRUCT
   //////////////////////////
public:
   /** \brief Constructor.
     * \param width width for grid to construct
     * \param height height for grid to construct
     * \warning this constructor does initialize all grid values to '0' using memset*/
   ArrayGrid( int width, int height );

   /** \brief Constructor.
     * \param width width for grid to construct
     * \param height height for grid to construct
     * \param needsInitialization flag if grid values need to be initialized
     * \param intensity value to initialize grid values with if needsInitialization has value true
     * \warning this constructor does *NOT* initialize the grid values if needsInitialization has value false*/
   ArrayGrid( int width, int height, bool needsInitialization, T intensity );

   /** \brief Constructor.
     * \param width width for grid to construct
     * \param height height for grid to construct
     * \param pArray the grid data in array form;
     * \warning the user is responsable for passing pArray of the correct size and type!!
     * \warning this constructor takes ownership of the data array pArray */
   ArrayGrid( int width, int height, T* pArray );

   /** \brief Copy constructor.
     * \param pArrayGrid grid from which to initialize this new grid */
   ArrayGrid( const ArrayGrid<T>& pArrayGrid );

   /** \brief Destructor. */
   ~ArrayGrid();

   /** \brief Creates a clone of this arraygrid
     * This clone becomes the responsability of the caller to delete */
   ArrayGrid<T>* Clone();

protected:
   /** \brief help method to copy internal data from other ArrayGrid
     * \param otherArrayGrid the other grid to copy from*/
   bool CreateGridCopy(const ArrayGrid<T>& otherArrayGrid);

   // 1. ACCESS ELEMENTS
   /////////////////////
public:

   /** \brief Overloaded operator (x, y)
     * \param x row index (along width)
     * \param y column index (along height)
     * http://www.parashift.com/c++-faq-lite/operator-overloading.html#faq-13.10 */
   T& operator() (int x, int y);

   /** \brief Overloaded operator (x, y)
     * \param x row index (along width)
     * \param y column index (along height)
     * http://www.parashift.com/c++-faq-lite/operator-overloading.html#faq-13.10
     */
   T  operator() (int x, int y) const;

   /** \brief sets all values for all grid positions to 'value'
     * \param value value to assign to all grid positions as initialization */
   void SetGridValues( T value );

   /** \brief copies all values for all grid positions from corresponding positions in otherGrid */
   void SetGridValues(const ArrayGrid<T>& otherGrid );

   /** \brief Gets copy of the i'th row of the image
     * \param i nr of row to get a copy of*/
   T* GetRowCopy(int i);

   /** \brief Gets copy of the i'th column of the image
     * \param i nr of column to get a copy of*/
   T* GetColumnCopy(int i);

   /** \brief Gets the grid value at position (x,y)
     * \param x the x coordinate
     * \param y the y coordinate */
   T GetValue(int x, int y) const;

   /** \brief Sets the value myValue at position (x,y)
     * \param x the x coordinate
     * \param y the y coordinate
     * \param myValue value to set */
   void SetValue(int x, int y, T myValue);

   /** \brief Sets the value myValue at the positions indicated in the vector of points
     * \param ptVector the vector of points of which the value must be set\
     * \param myValue value to set */
   void SetValue( std::vector< common::Point<int> > ptVector, T myValue);

   /** \brief Gets the value at a given point
     * \param pt point where to get the value */
   T GetValue( common::Point<int> pt ) const;

   /** \brief Sets a value at a given point
     * \param pt point where to set the value
     * \param myValue the value to set at position pt */
   void SetValue( common::Point<int> pt, T myValue);

   /** \brief Gets the width of the grid */
   int GetWidth() const;

   /** \brief Gets the height of the grid */
   int GetHeight() const;

   /** \brief Gets a copy of the array
     * \warning the user gets ownership of the returned array, and needs to clean it when finished with it!!*/
   T* GetDataCopy();

   /** \brief Gets the pointer to the data array
     * \warning this is potentially dangerous; to not delete this pointer!!*/
   T* GetDataPointer();

   // 2. MOVE ELEMENTS
   /////////////////////
public:

   /** \brief Point-mirrors the current grid.
     * The actual grid is changed*/
   void PointMirrorGrid();

   /** \brief switches upperleft <-> lowerright quadrants and upperright <-> lowerleft */
   void SwitchQuadrants();

   // 3. OPERATION ON SINGLE PIXEL
   ///////////////////////////////
public:

   /** \brief adds myValue to the value at position (x,y)
     * \param x x coordinate of position where value is to be added
     * \param y y coordinate of position where value is to be added
     * \param myValue the value that is to be added to the current value at the specified location*/
   void AddValue(int x, int y, T myValue);

   /** \brief adds one to the value at position (x,y)
     * \param x x coordinate of position where value is to be added
     * \param y y coordinate of position where value is to be added */
   void AddOne(int x, int y );

   /** \brief muliplies current value at position (x,y) with myValue
     * \param x x coordinate of position of which value is to be multiplied
     * \param y y coordinate of position of which value is to be multiplied
     * \param myValue the value with which the current value at the specified location is to be multiplied*/
   void MultiplyValue(int x, int y, T myValue);

   /** \brief divides current value at position (x,y) by myValue
     * \param x x coordinate of position of which value is to be divided
     * \param y y coordinate of position of which value is to be divided
     * \param myValue the value that is to be added to the current value at the specified location*/
   void DivideValue(int x, int y, T myValue);

   // 4. OPERATION ON WHOLE GRID
   /////////////////////////////
public:

   /** \brief muliplies all grid values with real-valued myValue
     * \param myValue the value with which all current grid values are to be multiplied*/
   void MultiplyWith( double factor);

   /** \brief muliplies all grid values with complex-valued myValue
     * \param myValue the value with which all current grid values are to be multiplied*/
   void MultiplyWith( std::complex<double> factor);

   /** \brief divides all grid values by real-valued myValue
     * \param myValue the value by which all current grid values are to be divided*/
   void DivideBy( double factor);

   /** \brief divides all grid values by complex-valued myValue
     * \param myValue the value by which all current grid values are to be divided*/
   void DivideBy( std::complex<double> factor);

   // 5. multiply / divide grid point by point with other grid
   ////////////////////////////////////////////////////////////
public:

   ArrayGrid<T>& operator+=(const ArrayGrid<T> &otherGrid);
   ArrayGrid<T>& operator-=(const ArrayGrid<T> &otherGrid);
   ArrayGrid<T>& operator*=(const ArrayGrid<T> &otherGrid);
   ArrayGrid<T>& operator/=(const ArrayGrid<T> &otherGrid);

   /** \brief sums all values of this grid point by point with values of otherGrid
     * Current grid is result, otherGrid stays the same
     * \param otherGrid grid used for adding to current grid */
   void AddGrid( ArrayGrid<T>* otherGrid );

   /** \brief subtracts from all values of this grid point by point values of otherGrid
     * Current grid is result, otherGrid stays the same
     * \param otherGrid grid used for adding to current grid */
   void SubtractGrid( ArrayGrid<T>* otherGrid);

   /** \brief multiplies all values of this grid point by point with values of otherGrid
     * Current grid is result, otherGrid stays the same
     * \param otherGrid grid used for multiplying current grid */
   void MultiplyWith( ArrayGrid<T>* otherGrid);

   /** \brief divides all values of this grid point by point by values of otherGrid
     * Current grid is result, otherGrid stays the same
     * \param otherGrid grid used for adding to current grid */
   void DivideBy( ArrayGrid<T>* otherGrid);

protected:

   T* mpArrayGrid;      ///< The grid array
   int mWidth;     ///< width of the grid
   int mHeight;    ///< height of the grid
};

//===========================================================================================

// 0. CONSTRUCT / DESTRUCT
//////////////////////////

template <class T>
ArrayGrid<T>::ArrayGrid( int width, int height )
{
   mpArrayGrid = 0;

   if ( (width > 0) && (height > 0) )
   {
      mHeight = height;
      mWidth  = width;

      mpArrayGrid = new T[ height * width ];
      memset( mpArrayGrid, 0, height * width * sizeof(T));

      #ifdef DEBUG
         std::cout << "Constructor: New arraygrid pointer " << mpArrayGrid << std::endl << std::flush;
      #endif
   }
   else
   {
      std::cerr << "Not allowed to construct an ArrayGrid with negative dimensions" << std::endl << std::flush;
   }
}

//------------------------------------------------------------------------------------------

template <class T>
ArrayGrid<T>::ArrayGrid( int width, int height, bool needsInitialization, T intensity )
{
   mpArrayGrid = 0;

   if ( (width > 0) && (height > 0) )
   {
      mHeight = height;
      mWidth  = width;

      mpArrayGrid = new T[ height * width ];

      if (needsInitialization == true)
      {
         SetGridValues( intensity );
      }

      #ifdef DEBUG
         std::cout << "Constructor: New arraygrid pointer " << mpArrayGrid << std::endl << std::flush;
      #endif
   }
   else
   {
      std::cerr << "Not allowed to construct an ArrayGrid with negative dimensions" << std::endl << std::flush;
   }
}

//------------------------------------------------------------------------------------------

template <class T>
ArrayGrid<T>::ArrayGrid( int width, int height, T* pArray )
{
   mpArrayGrid = pArray;

   mHeight = height;
   mWidth  = width;
}

//------------------------------------------------------------------------------------------

template <class T>
ArrayGrid<T>::ArrayGrid(const ArrayGrid<T>& otherArrayGrid)
{
   CreateGridCopy( otherArrayGrid );
}

//------------------------------------------------------------------------------------------

template <class T>
ArrayGrid<T>::~ArrayGrid()
{
   if (mpArrayGrid)
   {
      #ifdef DEBUG
         std::cout << "Deleting arraygrid pointer " << mpArrayGrid << std::endl << std::flush;
      #endif
      delete []mpArrayGrid;
   }
}

//------------------------------------------------------------------------------------------

template <class T>
inline ArrayGrid<T>* ArrayGrid<T>::Clone()
{
   return new ArrayGrid<T>(*this);
}

//------------------------------------------------------------------------------------------

template <class T>
bool ArrayGrid<T>::CreateGridCopy(const ArrayGrid<T>& otherArrayGrid)
{
   mHeight = otherArrayGrid.GetHeight();
   mWidth  = otherArrayGrid.GetWidth();

   mpArrayGrid = new T[mHeight * mWidth];

   #ifdef DEBUG
      std::cout << "Copy constructor New arraygrid pointer " << mpArrayGrid << std::endl << std::flush;
   #endif
   this->SetGridValues( otherArrayGrid );
   return true;
}

//------------------------------------------------------------------------------------------

// 1. ACCESS ELEMENTS
/////////////////////

template <class T>
inline T& ArrayGrid<T>::operator() (int x, int y)
{
   #ifdef DEBUG
   if (x < 0 || y < 0 || x >= mWidth || y >= mHeight )
   {
      std::cerr << "Array subscript (" << x << ", " << y << ") out of bounds" << std::endl << std::flush;
   }
   #endif
   return mpArrayGrid[ x + y * mWidth ];
}

//------------------------------------------------------------------------------------------

template <class T>
inline T ArrayGrid<T>::operator() (int x, int y) const
{
   #ifdef DEBUG
   if (x < 0 || y < 0 || x >= mWidth || y >= mHeight )
   {
      std::cerr << "Array subscript (" << x << ", " << y << ") out of bounds" << std::endl << std::flush;
   }
   #endif
   return mpArrayGrid[ x + y * mWidth ];
}

//------------------------------------------------------------------------------------------

template <class T>
inline void ArrayGrid<T>::SetGridValues(T value)
{
   for (int y = 0; y < mHeight; y++)
   {
      for (int x = 0; x < mWidth; x++)
      {
         this->SetValue(x, y, value );
      }
   }
}

//------------------------------------------------------------------------------------------

template <class T>
inline void ArrayGrid<T>::SetGridValues(const ArrayGrid<T>& otherGrid )
{
   assert( otherGrid.GetWidth() == mWidth);
   assert( otherGrid.GetHeight() == mHeight);
   for (int y = 0; y < mHeight; y++)
   {
      for (int x = 0; x < mWidth; x++)
      {
         this->SetValue(x, y, otherGrid.GetValue( x, y ) );
      }
   }
}

//------------------------------------------------------------------------------------------

template <class T>
inline T* ArrayGrid<T>::GetRowCopy(int y)
{
   T* pRowCopy = new T[ mWidth ];
   for (int x = 0; x < mWidth; x++)
   {
      pRowCopy[x] = mpArrayGrid[x + mWidth * y];
   }
   return pRowCopy;
}

//------------------------------------------------------------------------------------------

template <class T>
inline T* ArrayGrid<T>::GetColumnCopy(int x)
{
   T* pColumnCopy = new T[ mHeight ];
   for (int y = 0; y < mHeight; y++)
   {
      pColumnCopy[y] = mpArrayGrid[x + mWidth * y];
   }
   return pColumnCopy;
}

//------------------------------------------------------------------------------------------

template <class T>
inline T ArrayGrid<T>::GetValue(int x, int y) const
{
   assert( x >= 0);
   assert( x < mWidth );
   assert( y >= 0);
   assert( y < mHeight );
   return mpArrayGrid[x + mWidth * y];
}

//------------------------------------------------------------------------------------------

template <class T>
inline void ArrayGrid<T>::SetValue(int x, int y, T myValue)
{
   assert( x >= 0);
   assert( x < mWidth );
   assert( y >= 0);
   assert( y < mHeight );
   mpArrayGrid[x + mWidth * y] = myValue;
}

//------------------------------------------------------------------------------------------

template <class T>
inline T ArrayGrid<T>::GetValue( common::Point<int> pt ) const
{
   assert( pt.x >= 0);
   assert( pt.x < mWidth );
   assert( pt.y >= 0);
   assert( pt.y < mHeight );
   return GetValue( pt.x, pt.y );
}

//------------------------------------------------------------------------------------------

template <class T>
inline void ArrayGrid<T>::SetValue( common::Point<int> pt, T myValue)
{
   assert( pt.x >= 0);
   assert( pt.x < mWidth );
   assert( pt.y >= 0);
   assert( pt.y < mHeight );
   SetValue( pt.x, pt.y, myValue );
}

//------------------------------------------------------------------------------------------

template <class T>
inline void ArrayGrid<T>::SetValue( std::vector< common::Point<int> > ptVector, T myValue)
{
   for( std::vector< common::Point<int> >::iterator it = ptVector.begin();
        it != ptVector.end();
        ++it
      )
   {
      if (    ( (*it).x >= 0 ) && ( (*it).x < this->GetWidth() )
           && ( (*it).x >= 0 ) && ( (*it).y < this->GetHeight() )
         )
      {
         this->SetValue( (*it).x, (*it).y, myValue );
      }
   }
}

//------------------------------------------------------------------------------------------

template <class T>
inline int ArrayGrid<T>::GetWidth() const
{
   return mWidth;
}

//------------------------------------------------------------------------------------------

template <class T>
inline int ArrayGrid<T>::GetHeight() const
{
   return mHeight;
}

//------------------------------------------------------------------------------------------

template <class T>
inline T* ArrayGrid<T>::GetDataCopy()
{
   T* pArray = new T[ mWidth * mHeight ];
   memcpy ( pArray, mpArrayGrid, ( mWidth * mHeight * sizeof(T) ) );
   return pArray;
}

//------------------------------------------------------------------------------------------

template <class T>
inline T* ArrayGrid<T>::GetDataPointer()
{
   return mpArrayGrid;
}

//------------------------------------------------------------------------------------------

// 2. MOVE ELEMENTS
/////////////////////

template <class T>
inline void ArrayGrid<T>::PointMirrorGrid()
{
   ArrayGrid<T>* pTmpOriginalGrid = this->Clone();

   for (int y = 0; y < mHeight; y++)
   {
      for (int x = 0; x < mWidth; x++)
      {
         int xMirrored = mWidth - 1 - x;
         int yMirrored = mHeight - 1 - y;
         this->SetValue(x, y, pTmpOriginalGrid->GetValue(xMirrored, yMirrored));
      }
   }
   delete pTmpOriginalGrid;
}

//------------------------------------------------------------------------------------------

template <class T>
void ArrayGrid<T>::SwitchQuadrants()
{
   // regroup four quadrants of image so that the origin is in the center of the image
   ArrayGrid<T>* pTmpGridBeforeSwitch = new ArrayGrid<T>( *this );

   int halfWidthFirst  = (int)( floor( (double)( pTmpGridBeforeSwitch->GetWidth()  ) / 2.0) );
   int halfHeightFirst = (int)( floor( (double)( pTmpGridBeforeSwitch->GetHeight() ) / 2.0) );

   int halfWidthLast   = (int)( ceil( (double)( pTmpGridBeforeSwitch->GetWidth()  ) / 2.0) );
   int halfHeightLast  = (int)( ceil( (double)( pTmpGridBeforeSwitch->GetHeight() ) / 2.0) );

   for (int y = 0; y < mHeight; y++)
   {
      for (int x = 0; x < mWidth; x ++)
      {
         int xn, yn;

         if (x < halfWidthFirst)  {xn = x + halfWidthLast;}  else {xn = x - halfWidthFirst;}
         if (y < halfHeightFirst) {yn = y + halfHeightLast;} else {yn = y - halfHeightFirst;}

         T myValue = pTmpGridBeforeSwitch->GetValue(x, y);
         SetValue(xn, yn, myValue);
      }
   }
   delete pTmpGridBeforeSwitch;
}

//------------------------------------------------------------------------------------------

// 3. OPERATION ON SINGLE PIXEL
///////////////////////////////

template <class T>
inline void ArrayGrid<T>::AddValue(int x, int y, T myValue)
{
   assert( x >= 0);
   assert( x < mWidth );
   assert( y >= 0);
   assert( y < mHeight );
   this->mpArrayGrid[x + this->mWidth * y] += myValue;
}

//----------------------------------------------------------------------------------

template <class T>
inline void ArrayGrid<T>::AddOne(int x, int y )
{
   if ( ( x >= 0 ) && ( x < mWidth ) && ( y >= 0) && ( y < mHeight ) )
   {
      assert( x >= 0);
      assert( x < mWidth );
      assert( y >= 0);
      assert( y < mHeight );
      this->mpArrayGrid[x + this->mWidth * y] ++;
   }
   else
   {
      std::cerr << "Adding one to ( " << x << ", " <<  y  << " )is not possible since not within " << mWidth << " x " << mHeight << std::endl << std::flush;
   }
}

//----------------------------------------------------------------------------------

template <class T>
inline void ArrayGrid<T>::MultiplyValue(int x, int y, T myValue)
{
   assert( x >= 0);
   assert( x < mWidth );
   assert( y >= 0);
   assert( y < mHeight );
   this->mpArrayGrid[x + this->mWidth * y] *= myValue;
}

//----------------------------------------------------------------------------------

template <class T>
inline void ArrayGrid<T>::DivideValue(int x, int y, T myValue)
{
   assert( x >= 0);
   assert( x < mWidth );
   assert( y >= 0);
   assert( y < mHeight );
   this->mpArrayGrid[x + this->mWidth * y] /= myValue;
}

//===========================================================================================

// 4. OPERATION ON WHOLE GRID
/////////////////////////////

template <class T>
void ArrayGrid<T>::MultiplyWith( double factor)
{
   for (int y = 0; y < mHeight; y++)
   {
      for (int x = 0; x < mWidth; x++)
      {
         this->mpArrayGrid[x + this->mWidth * y] *= factor;
      }
   }
}

//----------------------------------------------------------------------------------

template <class T>
void ArrayGrid<T>::MultiplyWith( std::complex<double> factor)
{
   for (int y = 0; y < mHeight; y++)
   {
      for (int x = 0; x < mWidth; x++)
      {
         this->mpArrayGrid[x + this->mWidth * y] *= factor;
      }
   }
}

//----------------------------------------------------------------------------------

template <class T>
void ArrayGrid<T>::DivideBy( double factor)
{
   double divider = factor;
   if ( fabs(divider) < DBL_EPSILON ) { divider = DBL_EPSILON;}

   for (int y = 0; y < mHeight; y++)
   {
      for (int x = 0; x < mWidth; x++)
      {
         this->mpArrayGrid[x + this->mWidth * y] /= divider;
      }
   }
}

//----------------------------------------------------------------------------------

template <class T>
void ArrayGrid<T>::DivideBy( std::complex<double> factor)
{
   std::complex<double> divider = factor;
   if ( abs(divider) < DBL_EPSILON ) { divider = DBL_EPSILON;}

   for (int y = 0; y < mHeight; y++)
   {
      for (int x = 0; x < mWidth; x++)
      {
         this->mpArrayGrid[x + this->mWidth * y] /= divider;
      }
   }
}

//----------------------------------------------------------------------------------

// 5. multiply / divide grid point by point with other grid
////////////////////////////////////////////////////////////

template <class T>
ArrayGrid<T>& ArrayGrid<T>::operator+=(const ArrayGrid<T> &otherGrid)
{
   if ( (otherGrid.GetWidth() == this->GetWidth()) && (otherGrid.GetHeight() == this->GetHeight()))
   {
      for (int y = 0; y < mHeight; y++)
      {
         for (int x = 0; x < mWidth; x++)
         {
            this->mpArrayGrid[x + this->mWidth * y] += otherGrid.GetValue(x, y);
         }
      }
   }
   else
   {
      std::cerr << "grid += otherGrid impossible due to different grid sizes!!" << std::endl << std::flush;
   }
   return *this;
}

//----------------------------------------------------------------------------------

template <class T>
ArrayGrid<T>& ArrayGrid<T>::operator-=(const ArrayGrid<T> &otherGrid)
{
   if ( (otherGrid.GetWidth() == this->GetWidth()) && (otherGrid.GetHeight() == this->GetHeight()))
   {
      for (int y = 0; y < mHeight; y++)
      {
         for (int x = 0; x < mWidth; x++)
         {
            this->SetValue(x, y, this->GetValue(x, y) - otherGrid.GetValue(x, y));
         }
      }
   }
   else
   {
      std::cerr << "grid -= otherGrid impossible due to different grid sizes!!" << std::endl << std::flush;
   }
   return *this;
}

//----------------------------------------------------------------------------------

template <class T>
ArrayGrid<T>& ArrayGrid<T>::operator*=(const ArrayGrid<T> &otherGrid)
{
   if ( (otherGrid.GetWidth() == this->GetWidth()) && (otherGrid.GetHeight() == this->GetHeight()))
   {
      for (int y = 0; y < mHeight; y++)
      {
         for (int x = 0; x < mWidth; x++)
         {
            this->SetValue(x, y, this->GetValue(x, y) * otherGrid.GetValue(x, y));
         }
      }
   }
   else
   {
      std::cerr << "grid *= otherGrid impossible due to different grid sizes!!" << std::endl << std::flush;
   }
   return *this;
}

//----------------------------------------------------------------------------------

template <class T>
ArrayGrid<T>& ArrayGrid<T>::operator/=(const ArrayGrid<T> &otherGrid)
{
   if ( (otherGrid.GetWidth() == this->GetWidth()) && (otherGrid.GetHeight() == this->GetHeight()))
   {
      for (int y = 0; y < mHeight; y++)
      {
         for (int x = 0; x < mWidth; x++)
         {
            T divider = otherGrid.GetValue(x, y);
            if ( fabs(divider) < DBL_EPSILON ) { divider = DBL_EPSILON;}
            this->SetValue(x, y, this->GetValue(x, y) / divider);
         }
      }
   }
   else
   {
      std::cerr << "grid /= otherGrid impossible due to different grid sizes!!" << std::endl << std::flush;
   }
   return *this;
}

//----------------------------------------------------------------------------------

template <class T>
void ArrayGrid<T>::AddGrid( ArrayGrid<T>* otherGrid )
{
   if ((otherGrid != 0) && (otherGrid->GetWidth() == this->GetWidth()) && (otherGrid->GetHeight() == this->GetHeight()))
   {
      for (int y = 0; y < mHeight; y++)
      {
         for (int x = 0; x < mWidth; x++)
         {
            this->SetValue(x, y, this->GetValue(x, y) + otherGrid->GetValue(x, y));
         }
      }
   }
   else
   {
      std::cerr << "No valid grid as argument for AddTo " << std::endl << std::flush;
   }
}

//----------------------------------------------------------------------------------

template <class T>
void ArrayGrid<T>::SubtractGrid( ArrayGrid<T>* otherGrid)
{
   if ((otherGrid != 0) && (otherGrid->GetWidth() == this->GetWidth()) && (otherGrid->GetHeight() == this->GetHeight()))
   {
      for (int y = 0; y < mHeight; y++)
      {
         for (int x = 0; x < mWidth; x++)
         {
            this->SetValue(x, y, this->GetValue(x, y) - otherGrid->GetValue(x, y));
         }
      }
   }
   else
   {
      std::cerr << "No valid grid as argument for SubtractGrid " << std::endl << std::flush;
   }
}

//----------------------------------------------------------------------------------


template <class T>
void ArrayGrid<T>::MultiplyWith( ArrayGrid<T>* otherGrid)
{
   if ((otherGrid != 0) && (otherGrid->GetWidth() == this->GetWidth()) && (otherGrid->GetHeight() == this->GetHeight()))
   {
      for (int y = 0; y < mHeight; y++)
      {
         for (int x = 0; x < mWidth; x++)
         {
            this->SetValue(x, y, this->GetValue(x, y) * otherGrid->GetValue(x, y));
         }
      }
   }
   else
   {
      std::cerr << "No valid grid as argument for MultiplyWith " << std::endl << std::flush;
   }
}

//----------------------------------------------------------------------------------

template <class T>
void ArrayGrid<T>::DivideBy( ArrayGrid<T>* otherGrid)
{
   if ((otherGrid != 0) && (otherGrid->GetWidth() == this->GetWidth()) && (otherGrid->GetHeight() == this->GetHeight()))
   {
      for (int y = 0; y < mHeight; y++)
      {
         for (int x = 0; x < mWidth; x++)
         {
            T divider = otherGrid->GetValue(x, y);
            if ( fabs(divider) < DBL_EPSILON ) { divider = DBL_EPSILON;}
            this->SetValue(x, y, this->GetValue(x, y) / divider);
         }
      }
   }
   else
   {
      std::cerr << "No valid grid as argument for DivideBy " << std::endl << std::flush;
   }
}

//----------------------------------------------------------------------------------

}
}
#endif
