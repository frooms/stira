
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

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>

#if defined (__WIN32__) || defined(_WIN64)
   #include <sys/utime.h>
   #include <direct.h>
#else
   #include <utime.h>
#endif

#include <sys/stat.h>
#include <sys/types.h>

#include "FileAccess.h"
#include "StringUtils.h"

using namespace std;

namespace stira {
namespace common {

// sorts file names based on the last four digits before the extension
bool MyDirEntrySortPredicateUseUnderscore(const std::string& d1, const std::string& d2)
{
   return StringUtils::GetIndexFromFileName( d1, true ) < StringUtils::GetIndexFromFileName( d2, true );
}

bool MyDirEntrySortPredicateUseMinus(const std::string& d1, const std::string& d2)
{
   return StringUtils::GetIndexFromFileName( d1, false ) < StringUtils::GetIndexFromFileName( d2, false );
}

//-------------------------------------------------------------

FileAccess::FileAccess( )
{}

//-------------------------------------------------------------

FileAccess::~FileAccess( )
{}

//-------------------------------------------------------------
// Code based on http://www.gnu.org/software/libc/manual/html_node/Simple-Directory-Lister.html#Simple-Directory-Lister
std::vector< std::string > FileAccess::ListFilesInSubFoldersInFolder( std::string pathToAccess, std::string prefix, std::string extension, bool separatorIsUnderscore )
{
   DIR *dp;
   struct dirent *ep;

   bool usePrefixFile = false;
   std::string prefixFile;

   dp = opendir ( pathToAccess.c_str() );

   std::vector< std::string > foundFilesInSubFolders;

   if (dp != NULL)
   {
      while ( ep = readdir (dp) )
      {
         cout << "Reading subdirs under path " << pathToAccess << endl;
         std::string dirEntry = std::string(ep->d_name);

         size_t found;

         // different member versions of find in the same order as above:
         found = dirEntry.find( prefix );
         if ( found != string::npos )
         {
            std::string pathSubDir = pathToAccess + dirEntry + string("/");
            cout << "\t\tReading files from subdir " << pathSubDir << endl;

            std::vector< std::string > filesInDir = FileAccess::ListFilesOfType( pathSubDir, prefixFile, extension, usePrefixFile, -1, -1 );
            int nrFiles = filesInDir.size();
            for (int i = 0; i < nrFiles; i++)
            {
               foundFilesInSubFolders.push_back( filesInDir[i] );
            }
         }
      }
      (void) closedir (dp);
   }
   else
   {
      std::cerr << "Couldn't open directory" << pathToAccess << std::endl;
   }

   if ( separatorIsUnderscore )
   {
      std::sort( foundFilesInSubFolders.begin(), foundFilesInSubFolders.end(), MyDirEntrySortPredicateUseUnderscore );
   }
   else
   {
      std::sort( foundFilesInSubFolders.begin(), foundFilesInSubFolders.end(), MyDirEntrySortPredicateUseMinus );
   }

   return foundFilesInSubFolders;
}

//-------------------------------------------------------------
// Code based on http://www.gnu.org/software/libc/manual/html_node/Simple-Directory-Lister.html#Simple-Directory-Lister
std::vector< std::string > FileAccess::ListFilesOfType( std::string pathToAccess, std::string prefix, std::string extension, bool usePrefix, bool separatorIsUnderscore, int startNrImage, int maxNrFiles )
{
   DIR *dp;
   struct dirent *ep;

   int fileCounter = 0;
   std::vector< std::string > fileList;

   dp = opendir ( pathToAccess.c_str() );
   if (dp != NULL)
   {
      cout << "Reading files from dir " << pathToAccess << endl;
      while ( ep = readdir (dp) )
      {
         std::string dirEntry = std::string(ep->d_name);

         int dotPosition = StringUtils::FindFirstDot( dirEntry );

         if ( ( dotPosition > 0 ) && ( StringUtils::ExtractFileExtension( dirEntry ) == extension ) )
         {
            if (!usePrefix)
            {
               //cout << "\t\t\t adding " << pathToAccess + dirEntry << endl;
               fileList.push_back( pathToAccess + dirEntry );
               fileCounter++;
            }
            else
            {
               if ( StringUtils::ExtractFilePrefix( dirEntry, separatorIsUnderscore ) == prefix )
               {
                  //cout << "\t\t\t adding " << pathToAccess + dirEntry << endl;
                  fileList.push_back( pathToAccess + dirEntry );
                  fileCounter++;
               }
               else
               {
                  // ignore this file: has right extension but wrong prefix
               }
            }
         }
      }
      (void) closedir (dp);
   }
   else
   {
      std::cerr << "Couldn't open directory" << pathToAccess << std::endl;
   }

   if ( separatorIsUnderscore )
   {
      std::sort( fileList.begin(), fileList.end(), MyDirEntrySortPredicateUseUnderscore );
   }
   else
   {
      std::sort( fileList.begin(), fileList.end(), MyDirEntrySortPredicateUseMinus );
   }
   int totalNrFiles = fileList.size();
   std::vector< std::string > restrictedFileList;

   // Case 1: add all files that are found
   ///////////////////////////////////////
   if ( ( maxNrFiles == -1 ) && ( startNrImage == -1 ) )
   {
      std::cout << "Case 1: add all files that are found." << std::endl;
      for (int i = 0; i < totalNrFiles; i++)
      {
        restrictedFileList.push_back( fileList[i] );
      }
   }

   // Case 2: add all files starting from a given start number
   ///////////////////////////////////////////////////////////
   if ( ( maxNrFiles == -1 ) && ( startNrImage > -1 ) )
   {
      std::cout << "Case 2: add all files starting from a given start number." << std::endl;

      for (int i = 0; i < totalNrFiles; i++)
      {
         int fileNr = StringUtils::GetIndexFromFileName( fileList[i] );
         if ( fileNr >= startNrImage )
         {
            restrictedFileList.push_back( fileList[i] );
         }
      }
   }

   // Case 3: add the first "maxNrFiles" from the given directory
   //////////////////////////////////////////////////////////////
   if ( ( maxNrFiles > -1 ) && ( startNrImage == -1 ) )
   {
      std::cout << "Case 3: add the first " << maxNrFiles << " from the given directory." << std::endl;

      int nrFilesAdded = 0;
      for (int i = 0; i < totalNrFiles; i++)
      {
         if ( nrFilesAdded < maxNrFiles )
         {
            restrictedFileList.push_back( fileList[i] );
            nrFilesAdded++;
         }
      }
   }

   // Case 4: add "maxNrFiles" starting from image "startNrImage" from the given directory
   ///////////////////////////////////////////////////////////////////////////////////////
   if ( ( maxNrFiles > -1 ) && ( startNrImage > -1 ) )
   {
      std::cout << "Case 4: add " << maxNrFiles << " starting from image " << startNrImage << " from the given directory." << std::endl;

      int nrFilesAdded = 0;
      for (int i = 0; i < totalNrFiles; i++)
      {
         int fileNr = StringUtils::GetIndexFromFileName( fileList[i] );
         if ( ( fileNr >= startNrImage ) && ( nrFilesAdded < maxNrFiles ) )
         {
            restrictedFileList.push_back( fileList[i] );
            nrFilesAdded++;
         }
      }
   }
   std::cout << "FileAccess::ListFilesOfType added " << restrictedFileList.size() << " files to the list." << std::endl;
   return restrictedFileList;
}


//-------------------------------------------------------------

std::string FileAccess::FindFileName( std::vector< std::string > fileList, int frameNr )
{
   int nrFilesInList = fileList.size();
   for (int i = 0; i < nrFilesInList; i++)
   {
      int fileID = StringUtils::GetIndexFromFileName( fileList[i] );
      if ( fileID == frameNr )
      {
         return fileList[i];
      }
   }
   return std::string("");
}

//-------------------------------------------------------------

bool FileAccess::CheckIfDirectoryExists( std::string dirName )
{
   size_t size = dirName.size();

   if (size == 0) return true; // current directory

   char c = dirName[size-1]; // get last character
   bool trailingSlash = (c == '/') || (c == '\\');

   if (size == 1 && trailingSlash) return true; // root directory

   string dirNameTest = (trailingSlash) ? dirName.substr(0,size-1) : dirName;

   struct stat st;
   if( stat( dirNameTest.c_str(), &st ) == 0 )
   {
      return true;
   }
   else
   {
      return false;
   }
}

//-------------------------------------------------------------

bool FileAccess::CreateNewDirectory( std::string dirName )
{
   cout << "Creating " << dirName << endl << flush;
   if ( !CheckIfDirectoryExists( dirName ) )
   {
   #if defined (__WIN32__) || defined(_WIN64)
      if( _mkdir( dirName.c_str() ) == -1 )//creating a directory
      {
          cerr << "Error :  " << strerror( errno ) << endl;
          return false;
      }
      else
      {
         return true;
      }
   #else
      if( mkdir( dirName.c_str(), 0777) == -1 )//creating a directory
      {
          cerr << "Error :  " << strerror( errno ) << endl;
          return false;
      }
      else
      {
         return true;
      }
   #endif
   }
   else
   {
      cout << "Did NOT create " << dirName << " since it already exists." << endl << flush;
      return true;
   }
}

//-------------------------------------------------------------

bool FileAccess::CreateSymbolicLink2File( std::string sourcePathAndFileName, std::string linkPathAndFileName )
{
#if defined(__WIN32__) || defined(__WIN64)
   if (sourcePathAndFileName.length() == 0 && linkPathAndFileName.length() == 0) return true;
   return false;
#else
   cout << "Linking " << sourcePathAndFileName << " to " << linkPathAndFileName << endl << flush;

   int result = symlink( sourcePathAndFileName.c_str(), linkPathAndFileName.c_str() );

   if ( result == 0 )
   {
      return true;  // success
   }
   else
   {
      cerr << strerror( errno ) << endl;
      return false;
   }
#endif
}

//-------------------------------------------------------------
}
}
