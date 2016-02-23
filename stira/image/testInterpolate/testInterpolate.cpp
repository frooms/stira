
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

#include <vector>
#include <fstream>
#include "../color/ProfileCorrect.h"

using namespace std;
using namespace stira::image;

//-------------------------------------------------------------

ProfileData* ReadText( std::string inFileName )
{
   ifstream inReferenceStream1( inFileName.c_str() );
   if ( !inReferenceStream1 )
   {
      cout << "Can't read from file " << inFileName << "." << endl;
      return false;
   }
   //else
   //{
   //   cout << "Successfully read default reference values from file " << inFileName << "." << endl;
  // }
   
   stira::image::ProfileData* pInputData = new ProfileData();
   
   while( !inReferenceStream1.eof() )
   {
      lut_entry_t sampleEntry;
      double sampleValues[7];
      for (int i = 0; i < 7; i++)
      {
         inReferenceStream1   >> sampleValues[ i ];
      }
      sampleEntry.cmyk.c = sampleValues[0];
      sampleEntry.cmyk.m = sampleValues[1];
      sampleEntry.cmyk.y = sampleValues[2];
      sampleEntry.cmyk.k = sampleValues[3];
      sampleEntry.lab.l  = sampleValues[4];
      sampleEntry.lab.a  = sampleValues[5];
      sampleEntry.lab.b  = sampleValues[6];
      
      pInputData->AddA2BEntry( sampleEntry );
   }
   inReferenceStream1.close();
   return pInputData;
}

//-------------------------------------------------------------

void WriteProfile(ProfileData* pInputData, std::string name )
{
   cout << "=========================================================================" << endl << flush;
   cout << "=========================================================================" << endl << flush;
   cout << "Writing profile " << name << endl << flush;
   cout << "-------------------------------------------------------------------------" << endl << flush;
   int nrEntries = pInputData->GetSizeA2B();
   for (int i = 0; i < nrEntries; i++)
   {
      cout // << "( " 
           << pInputData->GetA2BEntryCmyk( i ).c  << "\t" // << ", " 
           << pInputData->GetA2BEntryCmyk( i ).m  << "\t" // << ", "
           << pInputData->GetA2BEntryCmyk( i ).y  << "\t" // << ", "
           << pInputData->GetA2BEntryCmyk( i ).k  << "\t" // << ") -> ( "
           << pInputData->GetA2BEntryLab( i ).l   << "\t" // << ", "
           << pInputData->GetA2BEntryLab( i ).a   << "\t" // << ", "
           << pInputData->GetA2BEntryLab( i ).b   << "\t" // << ")" 
           << endl << flush;
   }
}

//-------------------------------------------------------------

int main()
{
   int nrGridPoints = 17;
   //ProfileData* pInputData = ReadText( std::string("/v/frooms/projects/color/warhol-110509/cms/build/neuge/Debug/Neugebauer-White/ModelValuesWhite2.txt") );
   //ProfileData* pInputData = ReadText( std::string("/v/frooms/projects/color/warhol-110509/cms/spectra-aug2009/ModelBeforeBiasCorrection.txt") );
   //ProfileData* pInputData = ReadText( std::string("/v/frooms/projects/color/warhol-110509/cms/spectra-aug2009/ModelAfterBiasCorrection.txt") );
   
   //WriteProfile( pInputData, std::string("Input table") );
   
   //ProfileCorrect PC( pInputData, nrGridPoints );
   
   //ProfileData* pProfileOut = PC.InterpolateSamplesToGrid( );
   
   //WriteProfile( pProfileOut, std::string("Interpolated table") );
   
   //delete pInputData;
   //delete pProfileOut;
   cout << "currently no valid test files avilable..." << endl << flush;
   return 0;
}

