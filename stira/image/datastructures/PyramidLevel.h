
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
 
#ifndef STIRA_IMAGE_DATASTRUCTURES_PYRAMIDLEVEL_H
#define STIRA_IMAGE_DATASTRUCTURES_PYRAMIDLEVEL_H

#include <stdint.h>
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <string>

#include "ArrayGrid.h"
#include "../tools/NumberGridTools.h"
#include "../tools/ImageIO.h"

namespace stira {
namespace image {

/** \brief A class to contain a single level of a pyramid decomposition */
template <class T>
class PyramidLevel
{
public:

   /** \brief Constructor. */
   PyramidLevel();

   /** \brief Copy constructor. 
     * TODO now just an empty declaration; add implementation later*/
   PyramidLevel(const PyramidLevel<T>& otherLevel);

   /** \brief Destructor. */
   ~PyramidLevel();

   /** \brief Clones this object, making a deep-copy of all data structures
     * TODO now just an empty declaration; add implementation later*/
   PyramidLevel<T>* Clone();
   
   /** \brief Gets the number of orientations in this level of the steerable pyramid decomposition */
   int GetNumberOfOrientations();

   /** \brief Gets the oriented bandpass band with orientation index <code>orientation</code>
    * \param orientation the index of the oriented subband*/
   ArrayGrid<T>* GetOrientedBand( int orientation);

   /** \brief Adds a given band to the set of oriented bandpass bands
    * \param pBand pointer to the band to add to the set*/
   void AddOrientedBand( ArrayGrid<T>* pBand);

   /** \brief removes all occurences of the band pointed to by pBand from our set
    * Usually, this is just one band
    * \param pBand pointer of the band to be removed from the set
    * \warning check iterator syntax*/
   void RemoveOrientedBand( ArrayGrid<T>* pBand);
   
   /** \brief Puts band <code>pBand</code> in place of the band at index <code>orientationIndex</code>
    * \param orientationIndex index of the band to replace
    * \param pBand band to put instead of the old band */
   void ReplaceOrientedBand( int orientationIndex, ArrayGrid<T>* pBand);
   
   /** \brief Clears all oriented subbands at this pyramid level */
   void ClearThisLevel();
   
   /** \brief returns the width of the grid at this pyramid level */
   int GetWidth();
         
   /** \brief returns the height of the grid at this pyramid level */
   int GetHeight();
   
   /** \brief for diagnostics, write all bands in the pyramid to PGM files
     * \param token first part of filename for PGM's
     * \param level number of this pyramid level to be used in filename for PGM's */
   void ExportBandsToPGM( std::string token, int level);

   private:
      std::vector< ArrayGrid<T>* > mvBandsInLevel;  ///< set of all the oriented subbands for a single pyramid level
};

//===========================================================================================

template <class T>
PyramidLevel<T>::PyramidLevel()
{
}

//===========================================================================================

template <class T>
PyramidLevel<T>::PyramidLevel(const PyramidLevel<T>& otherPyramidLevel)
{
}
//===========================================================================================

template <class T>
PyramidLevel<T>::~PyramidLevel()
{
   ClearThisLevel();
}

//===========================================================================================

template <class T>
inline PyramidLevel<T>* PyramidLevel<T>::Clone()
{
   PyramidLevel<T>* pLevel = new PyramidLevel();
   int nrOfOrientations = this->GetNumberOfOrientations();
   for (int orientationID = 0; orientationID < nrOfOrientations; orientationID++)
   {
      pLevel->AddOrientedBand( (this->GetOrientedBand( orientationID ) )->Clone() );
   }
   return pLevel;
}

//===========================================================================================

template <class T>
inline int PyramidLevel<T>::GetNumberOfOrientations()
{
   return static_cast<int>( this->mvBandsInLevel.size() );
}

//===========================================================================================

template <class T>
inline ArrayGrid<T>* PyramidLevel<T>::GetOrientedBand( int orientationIndex)
{
   if (orientationIndex < (int)(mvBandsInLevel.size()))
   {
      return this->mvBandsInLevel[orientationIndex];
   }
   else 
   {
      return 0;
   }
}

//===========================================================================================

template <class T>
inline void PyramidLevel<T>::AddOrientedBand(ArrayGrid<T>* pBand)
{
   this->mvBandsInLevel.push_back(pBand);
}

//===========================================================================================

template <class T>
inline void PyramidLevel<T>::RemoveOrientedBand(ArrayGrid<T>* pBand)
{
   typename std::vector< ArrayGrid<T>* >::iterator tail = remove( mvBandsInLevel.begin(), mvBandsInLevel.end(), pBand);
   // moves all occurrences to the end, tail points at the first occurrence.
   // if not present, tail == end()
   
   for (typename std::vector< ArrayGrid<T>* >::iterator it = tail; it < mvBandsInLevel.end(); it ++)
   {
      delete (*it);
   }

   mvBandsInLevel.erase( tail, mvBandsInLevel.end() );
   // remove the moved occurrences from the vector
}

//===========================================================================================

template <class T>
inline void PyramidLevel<T>::ReplaceOrientedBand( int orientationIndex, ArrayGrid<T>* pBand)
{
   delete mvBandsInLevel[orientationIndex];
   mvBandsInLevel[orientationIndex] = pBand;
}

//===========================================================================================

template <class T>
inline void PyramidLevel<T>::ClearThisLevel()
{
   #ifdef DEBUG
      cout << "Before cleaning, we have " << mvBandsInLevel.size() << " oriented bands" << endl << flush;
   #endif
   for ( int orientationIndex = 0; orientationIndex < (int)(mvBandsInLevel.size()); orientationIndex++)
   {
      if (mvBandsInLevel[orientationIndex] != 0)
      {
         #ifdef DEBUG
            cout << "About to delete band " << mvBandsInLevel[orientationIndex] << endl << flush;
         #endif
         delete mvBandsInLevel[orientationIndex];
         mvBandsInLevel[orientationIndex] = 0;
         #ifdef DEBUG
            cout << "Finished delete band " << endl << flush;
         #endif
      }
   }
   mvBandsInLevel.clear();
   #ifdef DEBUG
      cout << " of which " << mvBandsInLevel.size() << " remain after cleaning" << endl << flush;
   #endif
}

//===========================================================================================

template <class T>
inline int PyramidLevel<T>::GetWidth()
{
   return mvBandsInLevel[0]->GetWidth();
}

//===========================================================================================

template <class T>
inline int PyramidLevel<T>::GetHeight()
{
   return mvBandsInLevel[0]->GetHeight();
}

//===========================================================================================

template <class T>
void PyramidLevel<T>::ExportBandsToPGM( std::string token, int level)
{
   int nrBands = (int)(mvBandsInLevel.size());
   for (int i = 0; i < nrBands; i++)
   {
      std::stringstream ss;
      ss << token << "-" << level << "-" << i << std::string(".pgm");
      std::string fileName = ss.str();
      ImageIO::WritePGM( mvBandsInLevel[i], fileName, ImageIO::GRADIENT_OUT);
   }
}

//===========================================================================================

}
}

#endif
