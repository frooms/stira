
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

#ifndef STIRA_IMAGE_COLOR_PROFILEDATA_H
#define STIRA_IMAGE_COLOR_PROFILEDATA_H

#include <iostream>
#include <cstdlib>
#include <cassert>
#include <vector>

using namespace std;

namespace stira {
namespace imagedata {

/** \brief Elementary color profile representations
  * In this file, we have a few data structures and a class to represent some elementary color profiles 
  * that translate between a machine dependant CMYK space and a device independant Lab space.*/

   /** \brief Representation of a single L*a*b* color */
   struct lab_t {
      double l;    ///< L* component
      double a;    ///< a* component
      double b;    ///< b* component
   };
   
   //-------------------------------------------------------------
   /** \brief Representation of a single CMYK color */
   struct cmyk_t {
      double c;    ///< C component
      double m;    ///< M component
      double y;    ///< Y component
      double k;    ///< K component
   };
   
   //-------------------------------------------------------------
   /** \brief Single entry in a lookup table that translates between a CMYK color and a Lab color*/
   struct lut_entry_t
   {
      lab_t lab;       ///< L*a*b* color
      cmyk_t cmyk;     ///< CMYK color
      bool isValid;    ///< flag if this LUT entry is valid
   };


//=============================================================================================

/** \brief class to manage data in a color profile
  * Basically consists of a color LookUp Table (CLUT) between a device space (A) and an independant space (B)
  * This independant space is usually L*a*b*. In a profile, we usually have two tables: 
  * in A2B, the values in the A space are on a regular grid and the corresponding B values usually aren't; 
  * in the B2A, the values in the B space are on a regular grid and the corresponding A values usually aren't */
class ProfileData
{
public:
   /** \brief constructor */
   ProfileData();
   
   /** \brief destructor */
   ~ProfileData();
   
// OPERATIONS ON THE A2B CLUT
///////////////////////////////
   
   /** \brief gets the number of entries in the A2B CLUT */
   int GetSizeA2B();
   
   /** \brief gets entry number k from the A2B CLUT
     * \param k number of entry to retrieve */
   lut_entry_t GetA2BEntry(int k);
   
   /** \brief gets the CMYK component from entry number k from the A2B CLUT
     * \param k number of entry of which we wish to retrieve the CMYK values */
   cmyk_t GetA2BEntryCmyk(int k);
   
   /** \brief gets the L*a*b* component from entry number k from the A2B CLUT
     * \param k number of entry of which we wish to retrieve the L*a*b* values */
   lab_t GetA2BEntryLab(int k);
   
   /** \brief adds entry to the A2B CLUT 
     * \param entry new entry to append at end of CLUT */
   void AddA2BEntry( lut_entry_t entry );
   
   /** \brief replaces the CMYK values in A2B entry k by the new CMYK values
     * \param k number of entry to modify
     * \param cmyk new CMYK values */
   void SetA2BEntryCmyk( int k, cmyk_t cmyk );
   
   /** \brief replaces the L*a*b* values in A2B entry k by the new L*a*b* values 
     * \param k number of entry to modify
     * \param lab new L*a*b* values*/
   void SetA2BEntryLab(  int k, lab_t lab );
   
// OPERATIONS ON THE B2A CLUT
///////////////////////////////

   /** \brief gets the number of entries in the B2A CLUT */
   int         GetSizeB2A();
   
   /** \brief gets entry number k from the B2A CLUT
     * \param k number of entry to retrieve */
   lut_entry_t GetB2AEntry(int k);
   
   /** \brief gets the CMYK component from entry number k from the B2A CLUT
     * \param k number of entry of which we wish to retrieve the CMYK values */
   cmyk_t      GetB2AEntryCmyk(int k);
   
   /** \brief gets the L*a*b* component from entry number k from the A2B CLUT
     * \param k number of entry of which we wish to retrieve the L*a*b* values */
   lab_t       GetB2AEntryLab(int k);
   
   /** \brief adds entry to the B2A CLUT 
     * \param entry new entry to append at end of CLUT */
   void AddB2AEntry( lut_entry_t entry );
   
   /** \brief replaces the CMYK values in B2A entry k by the new CMYK values
     * \param k number of entry to modify
     * \param cmyk new CMYK values */
   void SetB2AEntryCmyk( int k, cmyk_t cmyk );
   
   /** \brief replaces the L*a*b* values in B2A entry k by the new L*a*b* values 
     * \param k number of entry to modify
     * \param lab new L*a*b* values*/
   void SetB2AEntryLab(  int k, lab_t lab );
   
   std::vector< lut_entry_t > A2B; ///< the A2B conversion LUT
   std::vector< lut_entry_t > B2A; ///< the B2A conversion LUT
};

}
}

#endif
