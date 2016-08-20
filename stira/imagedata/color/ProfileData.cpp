
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

#include "ProfileData.h"

namespace stira {
namespace imagedata {

ProfileData::ProfileData()
{
}

//------------------------------------------------------------------------

ProfileData::~ProfileData()
{
}

//------------------------------------------------------------------------

int ProfileData::GetSizeA2B()
{
   return A2B.size();
}

//------------------------------------------------------------------------

lut_entry_t ProfileData::GetA2BEntry(int k)
{
   return A2B[k];
}

//------------------------------------------------------------------------

cmyk_t ProfileData::GetA2BEntryCmyk(int k)
{
   return A2B[k].cmyk;
}

//------------------------------------------------------------------------

lab_t ProfileData::GetA2BEntryLab(int k)
{
   return A2B[k].lab;
}

//------------------------------------------------------------------------

void ProfileData::AddA2BEntry( lut_entry_t entry )
{
   A2B.push_back( entry );
}

//------------------------------------------------------------------------

void ProfileData::SetA2BEntryCmyk( int k, cmyk_t cmyk )
{
   A2B[k].cmyk = cmyk;
}

//------------------------------------------------------------------------

void ProfileData::SetA2BEntryLab(  int k, lab_t lab )
{
   A2B[k].lab = lab;
}

//------------------------------------------------------------------------

int ProfileData::GetSizeB2A()
{
   return B2A.size();
}

//------------------------------------------------------------------------

lut_entry_t ProfileData::GetB2AEntry( int k )
{
   return B2A[k];
}

//------------------------------------------------------------------------

cmyk_t ProfileData::GetB2AEntryCmyk( int k )
{
   return B2A[k].cmyk;
}

//------------------------------------------------------------------------

lab_t       ProfileData::GetB2AEntryLab( int k )
{
   return B2A[k].lab;
}

//------------------------------------------------------------------------

void ProfileData::AddB2AEntry( lut_entry_t entry )
{
   B2A.push_back( entry );
}

//------------------------------------------------------------------------

void ProfileData::SetB2AEntryCmyk( int k, cmyk_t cmyk )
{
   B2A[k].cmyk = cmyk;
}

//------------------------------------------------------------------------

void ProfileData::SetB2AEntryLab(  int k, lab_t lab )
{
   B2A[k].lab = lab;
}

//------------------------------------------------------------------------

}
}
