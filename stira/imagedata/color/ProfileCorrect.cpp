
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

#include "../../common/common/MathUtils.h"
#include "ProfileCorrect.h"
#include "TransformColorSpace.h"

namespace stira {
namespace image {

using namespace common;

//-------------------------------------------------------------

ProfileCorrect::ProfileCorrect( ProfileData* pInputProfile, int nrGridPoints )
{
   mMinL =    0.0;
   mMaxL =  100.0;
   mMinA = -100.0;   // can in fact be -128
   mMaxA =  100.0;   // can in fact be +127
   mMinB = -100.0;   // can in fact be -128
   mMaxB =  100.0;   // can in fact be +127
   
   mToleranceDEClosestMatch = 3.0;
   mToleranceDENeighbors = 3.0;
   
   mGridStepL = (mMaxL - mMinL) / (double)(nrGridPoints);
   mGridStepA = (mMaxA - mMinA) / (double)(nrGridPoints);
   mGridStepB = (mMaxB - mMinB) / (double)(nrGridPoints);

   mNrOfGridPoints = nrGridPoints;
   cout << "For " << nrGridPoints << "points, mGridStepL = " << mGridStepL << ", mGridStepA = " << mGridStepA << " and mGridStepB = " << mGridStepB << endl << flush;
   mpInputProfile = pInputProfile;
}

//-------------------------------------------------------------

ProfileCorrect::~ProfileCorrect()
{
}

//-------------------------------------------------------------

bool ProfileCorrect::FindInList( vector< lut_entry_t > myTable, cmyk_t cmykEntry, lut_entry_t &foundEntry )
{
   int nrItems = myTable.size();
   for (int i = 0; i < nrItems; i++)
   {
      if (    ( myTable[i].cmyk.c == cmykEntry.c ) && ( myTable[i].cmyk.m == cmykEntry.m )
           && ( myTable[i].cmyk.y == cmykEntry.y ) && ( myTable[i].cmyk.k == cmykEntry.k )
         )
      {
         foundEntry = myTable[i];
         return true;
      }
   }
   return false;
}

//-------------------------------------------------------------

compare_neighbor_entry_t ProfileCorrect::FindClosestGridPoint( vector< lut_entry_t > myTable, lab_t gridLabValue )
{
   compare_neighbor_entry_t closestEntry;
   closestEntry.dE = 9999999999999999999999999999999.0;
   int nrItems = myTable.size();
   
   TransformColorSpace tcs;
   
   for (int i = 0; i < nrItems; i++)
   {
      ColorValue labGrid     = ColorValue( gridLabValue.l, gridLabValue.a, gridLabValue.b, TYPE_LAB );
      ColorValue labNeighbor = ColorValue( myTable[ i ].lab.l, myTable[ i ].lab.a, myTable[ i ].lab.b, TYPE_LAB );
      double dEtmp = tcs.DeltaE2000( labGrid, labNeighbor );
      if ( dEtmp < closestEntry.dE )
      {
         closestEntry.dE = dEtmp;
         closestEntry.entry = myTable[ i ];
      }
   }
   
   return closestEntry;
}

//-------------------------------------------------------------

vector< compare_neighbor_entry_t > ProfileCorrect::FindNearestNeighbors( vector< lut_entry_t > myTable, lut_entry_t myEntry )
{
   vector< compare_neighbor_entry_t > neighborEntries;
   
   int nrItems = myTable.size();
   
   TransformColorSpace tcs;
   
   for (int i = 0; i < nrItems; i++)
   {
      ColorValue labGrid     = ColorValue( myEntry.lab.l, myEntry.lab.a, myEntry.lab.b, TYPE_LAB );
      ColorValue labNeighbor = ColorValue( myTable[ i ].lab.l, myTable[ i ].lab.a, myTable[ i ].lab.b, TYPE_LAB );
      double dEtmp = tcs.DeltaE2000( labGrid, labNeighbor );
      if ( dEtmp < mToleranceDENeighbors )
      {
         compare_neighbor_entry_t myEntry;
         myEntry.entry = myTable[ i ];
         myEntry.dE = dEtmp;
         neighborEntries.push_back( myEntry );
      }
   }
   
   mEntryCounter++;
   
   return neighborEntries;
}

//-------------------------------------------------------------

//function to correct lab2cmyk for the new paper
//not so simple because lab has to be on a grid
ProfileData* ProfileCorrect::InterpolateSamplesToGrid( )
{
   int countValid = 0;
   int countInvalid = 0;
   
   ProfileData* pProfileOut = new ProfileData();
   mEntryCounter = 0;
   for (double itL = mMinL; itL <= mMaxL; itL += mGridStepL )
   {
      for (double itA = mMinA; itA <= mMaxA; itA += mGridStepA )
      {
         for (double itB = mMinB; itB <= mMaxB; itB +=mGridStepB )
         {
            lab_t gridLabValue = { itL, itA, itB };
            compare_neighbor_entry_t listEntry = FindClosestGridPoint( mpInputProfile->A2B, gridLabValue );
         
            //cout << "For Grid point (" << itL << ", " << itA << ", " << itB << "), closest match is (" 
            //      << listEntry.entry.lab.l << ", " << listEntry.entry.lab.a << ", " << listEntry.entry.lab.b << ", and dE = " << listEntry.dE << endl << flush;
      
            lut_entry_t outEntry;  //initialize counts with zeros
            outEntry.cmyk.c = 0.0;
            outEntry.cmyk.m = 0.0;
            outEntry.cmyk.y = 0.0;
            outEntry.cmyk.k = 0.0;
            outEntry.lab.l = itL;
            outEntry.lab.a = itA;
            outEntry.lab.b = itB;
            outEntry.lab.b = itB;
            outEntry.isValid = false;
            float sumWeights = 0.0;

            if ( listEntry.dE < mToleranceDEClosestMatch )
            {
               vector< compare_neighbor_entry_t > neighbors = FindNearestNeighbors( mpInputProfile->A2B, listEntry.entry );
               int nrNeighbors = neighbors.size();
               
               for (int j = 0; j < nrNeighbors; j++)
               {
                  compare_neighbor_entry_t currentNeighbor = neighbors[ j ];
                  float weightTotal = 1.0 / ( currentNeighbor.dE + 0.001 );
      
                  outEntry.cmyk.c += currentNeighbor.entry.cmyk.c * weightTotal;
                  outEntry.cmyk.m += currentNeighbor.entry.cmyk.m * weightTotal;
                  outEntry.cmyk.y += currentNeighbor.entry.cmyk.y * weightTotal;
                  outEntry.cmyk.k += currentNeighbor.entry.cmyk.k * weightTotal;
                  sumWeights += weightTotal;
               }
               
               if ( sumWeights > 0.001 )
               {
                  outEntry.cmyk.c = ( outEntry.cmyk.c / ( sumWeights + 0.001 ) );
                  outEntry.cmyk.m = ( outEntry.cmyk.m / ( sumWeights + 0.001 ) );
                  outEntry.cmyk.y = ( outEntry.cmyk.y / ( sumWeights + 0.001 ) );
                  outEntry.cmyk.k = ( outEntry.cmyk.k / ( sumWeights + 0.001 ) );
                  outEntry.isValid = true;
               }
               countValid++;
            }
            else
            {
               countInvalid++;
               outEntry.isValid = false;
            }
            
            pProfileOut->AddA2BEntry( outEntry );
            
            //one more steps: some output lut_entry_t's may have counts[k]=0
            //These must be located and the cmyk must be interpolated from the
            //neighbours
         }
      }
   }
   cout << "Nr of valid entries is " << countValid << ", and invalid entries is " << countInvalid << endl << flush;
   return pProfileOut;
}

}
}

