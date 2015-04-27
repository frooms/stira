
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

#include "TextFileUtils.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <fstream>

namespace stira {

namespace common {

using namespace std;

TextFileUtils::TextFileUtils()
{
}

//------------------------------------------------------------------------

TextFileUtils::~TextFileUtils()
{
}

//------------------------------------------------------------------------

std::vector< std::string > TextFileUtils::ReadLinesFromTextFile( std::string inFileName )
{
   std::vector< std::string > linesRead;

   ifstream fileData( inFileName.c_str() );
   if (!fileData)
   {
      cerr << "ERROR in TextFileUtils::ReadLinesFromTextFile: Can't read input series from file " << inFileName << "!!!" << endl;
      return linesRead;
   }
   std::string dataFileName;

   //// DATA PARAMETERS FROM FILE
   //////////////////////////////
   cout << "\t Reading input series from file " << inFileName << "." << endl;

   int nrfiles = 0;
   while( !fileData.eof() )
   {
      dataFileName = std::string("");
      fileData >> dataFileName;

      if ( dataFileName.size() > 0 )
      {
         linesRead.push_back( dataFileName );
      }
      nrfiles++;
   }

   return linesRead;
}

//------------------------------------------------------------------------

Rows TextFileUtils::ReadTabSeparatedLineFromTextFile( std::string inFileName )
{
   Rows rows;
   ifstream input( inFileName.c_str() );
   if (!input)
   {
      cerr << "ERROR in TextFileUtils::ReadTabSeparatedLineFromTextFil: Can't read input series from file " << inFileName << "!!!" << endl;
      return rows;
   }
   char const row_delim = '\n';
   char const field_delim = '\t';
   for (string row; getline(input, row, row_delim); )
   {
      rows.push_back(Rows::value_type());
      istringstream ss(row);
      for (string field; getline(ss, field, field_delim); )
      {
         rows.back().push_back(field);
      }
   }
   return rows;
}

//------------------------------------------------------------------------

bool TextFileUtils::IsValidCell( int columnValue, int* pFilterValues, int filterLength )
{
   for ( int filterNr = 0; filterNr < filterLength; filterNr++ )
   {
      if ( columnValue == pFilterValues[ filterNr ] )
      {
         return true;
      }
   }
   return false;
}

//------------------------------------------------------------------------

bool TextFileUtils::IsValidRow( int* columnValues, int* pFilterValues, int filterLength, int nrColumns )
{
   for ( int columnNr = 0; columnNr < nrColumns; columnNr++ )
   {
      if ( !IsValidCell( columnValues[columnNr], pFilterValues, filterLength ) )
      {
         return false;
      }
   }
   return true;
}

//------------------------------------------------------------------------

bool TextFileUtils::FilterText( std::string inFileName, std::string outFileName, int* pFilterValues, int filterLength, int nrColumnsToFilter, int nrOtherColumns )
{
   ifstream fileData( inFileName.c_str() );
   if (!fileData)
   {
      cerr << "ERROR: TextFileUtils::FilterText can't read from file " << inFileName << "." << endl;
      return false;
   }

   ofstream ofp;
   ofp.open(const_cast<char*>( outFileName.c_str()), ios::out | ios::binary);

   if (!ofp)
   {
      cerr << "ERROR: TextFileUtils::FilterText Can't write to file " << outFileName << "." << endl;
      return false;
   }
   int count = 0;
   int* pValueTest = new int[ nrColumnsToFilter ];
   double* pValues = new double[ nrOtherColumns ];
   while( !fileData.eof() )
   {
      for (int i = 0; i < nrColumnsToFilter; i++)
      {
         fileData >> pValueTest[i];
      }
      if (IsValidRow( pValueTest, pFilterValues, filterLength, nrColumnsToFilter ) )
      {
         for (int i = 0; i < nrColumnsToFilter; i++)
         {
            ofp <<  pValueTest[i] << "\t";
         }
         for (int i = 0; i < nrOtherColumns; i++)
         {
            fileData >> pValues[i];
            ofp << pValues[i] << "\t";
         }
         ofp << "\r\n" << flush;
      }
      else
      {
         for (int i = 0; i < nrOtherColumns; i++)
         {
            double t;
            fileData >> t;
         }
      }
      count++;
      cout << "Processed line : " << count << endl << flush;
   }
   delete []pValueTest;
   delete []pValues;
   fileData.close();
   ofp.close();
   return true;
}

//------------------------------------------------------------------------

bool TextFileUtils::SaveVectorOfValuesToTextFile( std::vector<double> inVector, std::string outFileName )
{
   ofstream ofp;
   ofp.open(const_cast<char*>( outFileName.c_str()), ios::out | ios::binary);

   if (!ofp)
   {
      cerr << "Error in TextFileUtils::SaveVectorOfValuesToTextFile: Can't write to file " << outFileName << "." << endl;
      return false;
   }

   int count = 0;

   for( std::vector< double >::iterator it = inVector.begin();
        it != inVector.end();
        ++it
      )
   {
      ofp << count << "\t" << *it << endl;
      count++;
   }
   ofp.close();
   return true;
}

//------------------------------------------------------------------------

bool TextFileUtils::SaveVectorOfValuesToTextFile( std::vector<int> inVector, std::string outFileName )
{
   ofstream ofp;
   ofp.open(const_cast<char*>( outFileName.c_str()), ios::out | ios::binary);

   if (!ofp)
   {
      cerr << "Error TextFileUtils::SaveVectorOfValuesToTextFileCan't write to file " << outFileName << "." << endl;
      return false;
   }

   int count = 0;

   for( std::vector< int >::iterator it = inVector.begin();
        it != inVector.end();
        ++it
      )
   {
      ofp << count << "\t" << *it << endl;
      count++;
   }
   ofp.close();
   return true;
}

//------------------------------------------------------------------------

bool TextFileUtils::SaveVectorOfIntensityPointsToTextFile( std::vector< common::IntensityPoint > inVector, std::string outFileName )
{
   ofstream ofp;
   ofp.open(const_cast<char*>( outFileName.c_str()), ios::out | ios::binary);

   if (!ofp)
   {
      cerr << "ERROR: TextFileUtils::SaveVectorOfIntensityPointsToTextFile Can't write to file " << outFileName << "." << endl;
      return false;
   }

   int count = 0;

   for( std::vector< common::IntensityPoint >::iterator it = inVector.begin();
        it != inVector.end();
        ++it
      )
   {
      ofp << count << "\t" << (*it).x << "\t" << (*it).y << "\t" << (*it).intensity << endl;
      count++;
   }
   ofp.close();
   return true;
}


//------------------------------------------------------------------------

}
}
