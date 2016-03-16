
/***************************************************************************************
 *   Copyright (C) 2012 by Filip Rooms                                                 *
 *                                                                                     *
 *  Terms and conditions for using this software in any form are provided in the       *
 *  file COPYING, which can be found in the root directory of this project.            *
 *                                                                                     *
 *   Contact data: filip.rooms@gmail.com                                               *
 *                 http://www.filiprooms.be/                                           *
 *                                                                                     *
 ***************************************************************************************/

#include "../common/FileAccess.h"
#include "../common/TextFileUtils.h"
#include "../common/StringUtils.h"
#include <iostream>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <sstream>

using namespace std;
using namespace stira::common;

//-------------------------------------------------------------------

void TestFileAccess()
{
   cout << "+--------------+" << endl << flush;
   cout << "|TestFileAccess|" << endl << flush;
   cout << "+--------------+" << endl << flush;
   std::string prefix;
   bool usePrefix = false;

   std::vector< std::string > fileList = FileAccess::ListFilesOfType( std::string("../../testdata/"), prefix, std::string(".pgm"), usePrefix );

   cout << "Processing files " << fileList[0]  << " to " << fileList[ fileList.size() - 1 ] << endl;

   bool createSuccessfull = FileAccess::CreateNewDirectory( std::string( "/scratch/frooms/t01212/" ) );
   cout << "createSuccessfull returned " << createSuccessfull << endl;

   std::vector< std::string > subDirs = FileAccess::ListFilesInSubFoldersInFolder( std::string("../../testdata/"), std::string("BFP"), std::string(".pgm") );
   cout << " END TestFileAccess..." << endl << flush;
}

//-------------------------------------------------------------------

void TestFileExists()
{
   cout << "+--------------+" << endl << flush;
   cout << "|TestFileExists|" << endl << flush;
   cout << "+--------------+" << endl << flush;

   std::string fileExists = std::string("../../testdata/stitch.tif");

   std::string fileDoesNotExist = std::string("../../testdata/imaginary.tif");

   assert( FileAccess::CheckIfFileExists(fileExists) );

   assert( !FileAccess::CheckIfFileExists(fileDoesNotExist) );

   cout << " END TestFileExists..." << endl << flush;
}

//-------------------------------------------------------------------

int main()
{
   TestFileAccess();
   TestFileExists();
   //TestZipFile();
   return 0;
}

