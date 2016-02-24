
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
#include <strstream>

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

void TestZipFile()
{
   //Open the ZIP archive
   int err = 0;
   zip *pZipFile = zip_open("/u/frooms/research/develop/stira-env/stira/testdata/testZipFile.zip", 0, &err);

   //Search for the file of given name
   const char *pNameText = "testTextFile-0010.txt";
   struct zip_stat stText;
   zip_stat_init(&stText);
   zip_stat(pZipFile, pNameText, 0, &stText);

   //Alloc memory for its uncompressed contents
   char *pContentsText = new char[stText.size];

   //Read the compressed file
   zip_file *fText = zip_fopen(pZipFile, "testTextFile-0010.txt", 0);
   zip_fread(fText, pContentsText, stText.size);
   cout << pContentsText << endl;
   zip_fclose(fText);

   //And close the archive
   zip_close(pZipFile);
}

//-------------------------------------------------------------------

int main()
{
   TestFileAccess();
   //TestZipFile();
   return 0;
}

