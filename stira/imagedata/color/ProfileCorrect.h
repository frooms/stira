
/***********************************************************************************
 *   Copyright (C) 2009 by Filip Rooms                                             *
 *                                                                                 *
 *  Terms and conditions for using this software in any form are provided in the   *
 *  file COPYING, which can be found in the root directory of this project.        *
 *                                                                                 *
 *   Contact data: filip.rooms@gmail.com                                           *
 *                 http://www.filiprooms.be/                                       *
 *                                                                                 *
 ***********************************************************************************/

#ifndef STIRA_IMAGE_COLOR_PROFILECORRECT_H
#define STIRA_IMAGE_COLOR_PROFILECORRECT_H

#include <iostream>
#include <cstdlib>
#include <cassert>
#include <vector>
#include "ProfileData.h"

using namespace std;

namespace stira {
namespace image {

//-------------------------------------------------------------

struct compare_neighbor_entry_t
{
   lut_entry_t entry;   ///< an entry that translates between a CMYK and an L*a*b* color
   double dE;           ///< delta E 2000 difference value towards a reference color
};

//-------------------------------------------------------------

/** \brief experimental class to interpolate CLUTS in ICC color profiles from measured or estimated values */
class ProfileCorrect
{
public:
   /** \brief constructor
     * \param pInputProfile input table of CLUT entries to interpolate
     * \param nrGridPoints number of  */
   ProfileCorrect( ProfileData* pInputProfile, int nrGridPoints );
   
   /** \brief constructor */
   ~ProfileCorrect();
   
   /** \brief Interpolates the given list with samples (measured ort modeled) to a regular grid*/
   ProfileData* InterpolateSamplesToGrid( );
   
   /** \brief Finds in a list the entry with given cmyk value
     * \param myTable the table to search
     * \param cmykEntry the cmyk value to find in the list
     * \param foundEntry the found entry as output */
   bool FindInList( vector< lut_entry_t > myTable, cmyk_t cmykEntry, lut_entry_t &foundEntry );

   /** \brief Finds in a list the entry with the smallest color difference (delta E 2000) with gridLabValue
     * \param myTable the table to search
     * \param gridLabValue the reference L*a*b* color to compare with */
   compare_neighbor_entry_t FindClosestGridPoint( vector< lut_entry_t > myTable, lab_t gridLabValue );

   /** \brief Finds in a list the entry with given cmyk value
     * \param dataTable the table to search
     * \param myEntry the entry for which to find its nearest neighbors in the list */
   vector< compare_neighbor_entry_t > FindNearestNeighbors(  vector< lut_entry_t > dataTable, lut_entry_t myEntry );
   
private:
   float mGridStepL;  ///< size of grid interval in the L* direction
   float mGridStepA;  ///< size of grid interval in the a* direction
   float mGridStepB;  ///< size of grid interval in the b* direction
   float mMinL;       ///< minimum value for L* ( can in fact be    0 )
   float mMaxL;       ///< maximum value for L* ( can in fact be  100 )
   float mMinA;       ///< minimum value for a* ( can in fact be -128 )
   float mMaxA;       ///< maximum value for a* ( can in fact be +127 )
   float mMinB;       ///< minimum value for b* ( can in fact be -128 )
   float mMaxB;       ///< maximum value for b* ( can in fact be +127 )
   
   float mToleranceDEClosestMatch;  ///< tolerance in delta E for closest match between two colors
   float mToleranceDENeighbors;  ///< tolerance in delta E for closest neighborsmatch between two colors

   int mNrOfGridPoints; ///< nr of grid points per color dimension 
   ProfileData* mpInputProfile;  ///< data structure for color mapping
   int mEntryCounter;   ///< counts nr of entries
};

}
}

#endif
