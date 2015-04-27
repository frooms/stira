
/***************************************************************************************
 *   Copyright (C) 2011 by Filip Rooms                                                 *
 *                                                                                     *
 *  Terms and conditions for using this software in any form are provided in the       *
 *  file COPYING, which can be found in the root directory of this project.            *
 *                                                                                     *
 *   Contact data: filip.rooms@gmail.com                                               *
 *                 http://www.filiprooms.be/                                           *
 *                                                                                     *
 ***************************************************************************************/

#ifndef STIRA_COMMON_FIXEDBUFFER_H
#define STIRA_COMMON_FIXEDBUFFER_H

#include <iostream>
#include <vector>
#include <cassert>
#include <iomanip>

enum SideOverflow{ DELETE_FROM_BEGIN, DELETE_FROM_END };

using namespace std;

namespace stira {
namespace common {

/** \brief A class to represent a buffer of fixed size. */
template <class T>
class FixedBuffer
{
public:
   /** \brief constructor
     * \param maxSize maximum size of the buffer */
   FixedBuffer( int maxSize, SideOverflow mySide=DELETE_FROM_BEGIN );

   /** \brief destructor */
   ~FixedBuffer( );

   /** \brief Adds a new element to the buffer end
     * Oldest added element is still at mvVector.begin()
     * If the size of the after adding the new element exceeds the maximum length, the oldest element is removed
     * \param newElement new element to add to the buffer */
   void AddElement( T newElement );

   /** \brief Inserts a new element to the buffer
     * If the size of the after adding the new element exceeds the maximum length, the oldest element is removed
     * \param newElement new element to add to the buffer */
   void InsertElementFromStart( T newElement, int positionFromStart=0 );

   void InsertElementFromEnd( T newElement, int positionFromEnd=0 );

   /** \brief Gets element from end
     * \param index index of element to retrieve: for last element, index is 0; for one but last, index = 1; for second but last, index = 2 and so on */
   T GetElementFromStart( int index );

   /** \brief Gets element from end
     * \param index index of element to retrieve: for last element, index is 0; for one but last, index = 1; for second but last, index = 2 and so on */
   T GetElementFromEnd( int index );

   /** \brief Gets the size of the buffer */
   int GetSize();

   /** \brief empties all elements from the buffer */
   void Clear();

protected:
   unsigned int mMaxSize; ///< maximum size of the buffer
   SideOverflow mSide;   ///< side of buffer from which to remove the elements when buffer is too large
   std::vector<T> mvVector;   ///< an STL vector containing the elements
};

//==============================================================================================

template <class T>
FixedBuffer<T>::FixedBuffer( int maxSize, SideOverflow mySide )
{
   mMaxSize = maxSize;
   mvVector.clear();
   mSide = mySide;
}

//-----------------------------------------------------------------------------------------------

template <class T>
FixedBuffer<T>::~FixedBuffer( )
{
   mvVector.clear();
}

//-----------------------------------------------------------------------------------------------
template <class T>
void FixedBuffer<T>::AddElement( T newElement )
{
   mvVector.push_back( newElement );

   if ( mvVector.size() > mMaxSize )
   {
      typename std::vector<T>::iterator it;
      if (mSide==DELETE_FROM_BEGIN)
      {
         it = mvVector.begin();
      }
      else
      {
         it = mvVector.end();
         it--;
      }
      mvVector.erase ( it );
   }
}

//-----------------------------------------------------------------------------------------------

template <class T>
void FixedBuffer<T>::InsertElementFromStart( T newElement, int positionFromStart )
{
   typename std::vector<T>::iterator it;

   it = mvVector.begin();
   it += positionFromStart;

   mvVector.insert ( it , newElement );

   if ( mvVector.size() > mMaxSize )
   {
      typename std::vector<T>::iterator it;
      if (mSide==DELETE_FROM_BEGIN)
      {
         it = mvVector.begin();
      }
      else
      {
         it = mvVector.end();
         it--;
      }
      mvVector.erase ( it );
   }
}

//-----------------------------------------------------------------------------------------------

template <class T>
void FixedBuffer<T>::InsertElementFromEnd( T newElement, int positionFromEnd )
{
   typename std::vector<T>::iterator it;

   int distanceFromStart = mvVector.size() - positionFromEnd - 1;
   it = mvVector.begin();
   it += distanceFromStart;

   mvVector.insert ( it , newElement );

   if ( mvVector.size() > mMaxSize )
   {
      typename std::vector<T>::iterator it;
      if (mSide==DELETE_FROM_BEGIN)
      {
         it = mvVector.begin();
      }
      else
      {
         it = mvVector.end();
         it--;
      }
      mvVector.erase ( it );
   }
}

//-----------------------------------------------------------------------------------------------

template <class T>
T FixedBuffer<T>::GetElementFromStart( int index )
{
   assert( index >= 0 );
   int bufferSize = mvVector.size();
   assert( index < bufferSize );
   if ( index < bufferSize )
   {
      return mvVector[ index ];
   }
   return mvVector[ 0 ];
}

//-----------------------------------------------------------------------------------------------

template <class T>
T FixedBuffer<T>::GetElementFromEnd( int index )
{
   assert( index >= 0 );
   int bufferSize = mvVector.size();
   assert( index < bufferSize );
   if ( index < bufferSize )
   {
      return mvVector[ bufferSize - index - 1 ];
   }
   return mvVector[ 0 ];
}

//-----------------------------------------------------------------------------------------------

template <class T>
int FixedBuffer<T>::GetSize()
{
   return mvVector.size();
}

//-----------------------------------------------------------------------------------------------

template <class T>
void FixedBuffer<T>::Clear()
{
   mvVector.clear();
}

//-----------------------------------------------------------------------------------------------

}
}

#endif // FIXEDBUFFER_H
