
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

#include "StringUtils.h"
#include "StiraMacros.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <sstream>
#include <ctime>
#include <cctype>

using namespace std;

namespace stira {
namespace common {

template <class T>
bool from_string(T& t,
                 const std::string& s,
                 std::ios_base& (*f)(std::ios_base&))
{
  std::istringstream iss(s);
  return !(iss >> f >> t).fail();
}

//-------------------------------------------------------------


static const char alphanum[] =
    "0123456789"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz";

//-------------------------------------------------------------

StringUtils::StringUtils()
{
}

//-------------------------------------------------------------

StringUtils::~StringUtils()
{
}

//-------------------------------------------------------------

std::string StringUtils::ConvertIntegerToString( int i )
{
   std::stringstream out;
   out << i;
   return out.str();
}

//-------------------------------------------------------------

std::string StringUtils::ConvertFloatToString( float i )
{
   std::stringstream out;
   out << i;
   return out.str();
}

//-------------------------------------------------------------

std::string StringUtils::ConvertDoubleToString( double i )
{
   std::stringstream out;
   out << i;
   return out.str();
}

//-------------------------------------------------------------

std::string StringUtils::ConvertBoolToString( bool i )
{
   if ( i )
   {
      return std::string("true");
   }
   else
   {
      return std::string("false");
   }
}

//-------------------------------------------------------------

bool StringUtils::ConvertStringToBoolean( std::string inputString )
{
   if (    ( inputString == std::string("true") )
        || ( inputString == std::string("yes") )
      )
   {
      return true;
   }
   else
   {
      return false;
   }
}

//-------------------------------------------------------------

int StringUtils::ConvertStringToInt( std::string inputString )
{
   int i = -1;

   // the third parameter of from_string() should be
   // one of std::hex, std::dec or std::oct
   if(from_string<int>(i, inputString, std::dec))
   {
   }
   else
   {
     std::cout << "from_string failed" << std::endl;
   }
   return i;
}

//-------------------------------------------------------------

float StringUtils::ConvertStringToFloat( std::string inputString )
{
   float f=-1.0;
   if(from_string<float>(f, inputString, std::dec))
   {
   }
   else
   {
     std::cout << "from_string failed" << std::endl;
   }
   return f;
}

//-------------------------------------------------------------

double StringUtils::ConvertStringToDouble( std::string inputString )
{
   double dd=-1.0;
   if(from_string<double>(dd, inputString, std::dec))
   {
   }
   else
   {
     std::cout << "from_string failed" << std::endl;
   }
   return dd;
}


std::vector<std::string> StringUtils::TokenizeString( std::string inputString, char const field_delim )
{
    std::vector<std::string> stringTokens;
    istringstream ss(inputString);
    for (string field; getline(ss, field, field_delim); )
    {
       stringTokens.push_back( field );
    }
    return stringTokens;
}

//-------------------------------------------------------------

std::string StringUtils::ExtractFileName( std::string inputString )
{
   std::string justFileName;

   int lastSlashPosition = FindLastSlash( inputString );

   int stringLength = inputString.size();

   justFileName.insert( 0, inputString, (lastSlashPosition+1), (stringLength - lastSlashPosition) );

   return justFileName;
}

//-------------------------------------------------------------

std::string StringUtils::ExtractFileNameRoot( std::string inputString )
{
   std::string justFileName;

   int lastSlashPosition = FindLastSlash( inputString );

   int stringLength = inputString.size();

   justFileName.insert( 0, inputString, (lastSlashPosition+1), (stringLength - lastSlashPosition) );

   std::string fileNameRoot;
   fileNameRoot.insert( 0, justFileName, 0, FindFirstDot( justFileName ) );

   return fileNameRoot;
}

//-------------------------------------------------------------

long int StringUtils::GetIndexFromFileName( std::string inputString, bool useUnderscoreAsSeparator )
{
   std::string fileNameIndex;
   int dotPosition = FindFirstDot( inputString );
   int separatorPosition;
   if (useUnderscoreAsSeparator)
   {
      separatorPosition = FindLastUnderscore( inputString );
   }
   else
   {
      separatorPosition = FindLastMinus( inputString );
   }

   //cout << "separatorPosition = " << separatorPosition << ", dotPosition = " << dotPosition << endl;

   fileNameIndex.insert( 0, inputString, separatorPosition+1, dotPosition - separatorPosition-1 );
   //cout << "fileNameIndex = " << fileNameIndex << ", index = " << atoi(fileNameIndex.c_str()) << endl;

   return atoi(fileNameIndex.c_str());
}

//-------------------------------------------------------------

std::string StringUtils::FindFileNameInListFromIndex( int myIndex, std::vector< std::string > fileList )
{
   for( std::vector< std::string >::iterator it = fileList.begin();
        it != fileList.end();
        ++it
      )
   {
      if ( GetIndexFromFileName( *it ) == myIndex ) { return *it; }
   }
   return std::string("0");  //not found
}

//-------------------------------------------------------------

int StringUtils::FindFirstDot( std::string inputString )
{
   size_t found;

   // different member versions of find in the same order as above:
   found = inputString.find( std::string(".") );
   if (found!=string::npos)
   {
      return (int)(found);
   }
   else
   {
      //cerr << "No dot found in " << inputString << endl << flush;
      return -1;
   }
}

//-------------------------------------------------------------

int StringUtils::FindLastSlash( std::string inputString )
{
   size_t lastSlashPosition;

   // different member versions of find in the same order as above:
#if defined (__WIN32__) || defined(_WIN64)
   lastBackSlashPosition = inputString.rfind( std::string("\\") );
   lastSlashPosition = inputString.rfind( std::string("/") );
   if (lastBackSlashPosition != string::npos) {
      if (lastSlashPosition == string::npos || lastBackSlashPosition > lastSlashPosition) {
         lastSlashPosition = lastBackSlashPosition;
      }
   }
#else
   lastSlashPosition = inputString.rfind( std::string("/") );
#endif

   if (lastSlashPosition != string::npos)
   {
      return (int)(lastSlashPosition);
   }
   else
   {
      return -1;
   }
}

//-------------------------------------------------------------

int StringUtils::FindLastUnderscore( std::string inputString )
{
   size_t lastUnderscorePosition;

   // different member versions of find in the same order as above:
   lastUnderscorePosition = inputString.rfind( std::string("_") );

   if (lastUnderscorePosition != string::npos)
   {
      return (int)(lastUnderscorePosition);
   }
   else
   {
      return -1;
   }
}

//-------------------------------------------------------------

int StringUtils::FindLastMinus( std::string inputString )
{
   size_t lastMinusPosition;

   // different member versions of find in the same order as above:
   lastMinusPosition = inputString.rfind( std::string("-") );

   if (lastMinusPosition != string::npos)
   {
      return (int)(lastMinusPosition);
   }
   else
   {
      return -1;
   }
}

//-------------------------------------------------------------

std::string StringUtils::ExtractFileExtension( std::string inputString, bool includeDot )
{
   std::string justFileName;

   int lastSlashPosition = FindLastSlash( inputString );
   int stringLength = inputString.size();

   justFileName.insert( 0, inputString, (lastSlashPosition+1), (stringLength - lastSlashPosition) );

   int dotPosition = FindFirstDot( justFileName );

   std::string fileNameExtension;
   if ( includeDot )
   {
      fileNameExtension.insert( 0, justFileName, dotPosition, stringLength-1 );
   }
   else
   {
      fileNameExtension.insert( 0, justFileName, dotPosition+1, stringLength-1 );
   }

   return fileNameExtension;
}

//-------------------------------------------------------------

std::string StringUtils::ExtractFilePrefix( std::string inputString, bool useUnderscoreAsSeparator )
{
   std::string prefixName;

   int lastSlashPosition = FindLastSlash( inputString );

   int separatorPosition;

   if (useUnderscoreAsSeparator)
   {
      separatorPosition = FindLastUnderscore( inputString );
   }
   else
   {
      separatorPosition = FindLastMinus( inputString );
   }

   prefixName.insert( 0, inputString, (lastSlashPosition+1), (separatorPosition - 1 - lastSlashPosition ) );

   return prefixName;
}

//-------------------------------------------------------------

std::string StringUtils::ExtractPathOfFileName( std::string inputString )
{
   std::string pathName;

   int lastSlashPosition = FindLastSlash( inputString );

   pathName.insert( 0, inputString, 0, lastSlashPosition+1 );

   return pathName;
}

//-------------------------------------------------------------

std::string StringUtils::ExtractFileNameFromPathPlusFileName( std::string inputString )
{
   std::string pathName;

   int lastSlashPosition = FindLastSlash( inputString );

   pathName.insert( 0, inputString, lastSlashPosition+1, inputString.length() );

   return pathName;
}

//-------------------------------------------------------------

std::string StringUtils::GoOneLevelUpInPathName( std::string inputString )
{
   std::string pathName = ExtractPathOfFileName( inputString );

   int pos = FindLastSlash( pathName );
   std::string pathName1;

   pathName1.insert( 0, pathName, 0, pos-1 );
   pos = FindLastSlash( pathName1 );
   std::string pathName2;
   pathName2.insert( 0, pathName1, 0, pos+1 );
   return pathName2;
}

//-------------------------------------------------------------

std::string StringUtils::ConstructPathAndFileName( std::string path, std::string preFix, int indexNr, std::string extension )
{
   stringstream ss;
   ss << setfill('0');
   ss << path << preFix << setw( STIRA_INDEX_WIDTH ) << indexNr << extension;
   std::string fileName = ss.str();
   return fileName;
}

//-------------------------------------------------------------

std::string StringUtils::ConstructPathAndFileName( std::string path, std::string preFix, int indexNr1, int indexNr2, std::string extension )
{
   stringstream ss;
   ss << setfill('0');
   ss << path << preFix << setw(4) << indexNr1 << std::string("-") << setw(4) << indexNr2 << extension;
   std::string fileName = ss.str();
   return fileName;
}

//-------------------------------------------------------------

void StringUtils::SplitStringInIntegers( const string& s, char c, vector<int>& v )
{
   string::size_type i = 0;
   string::size_type j = s.find(c);

   // case of a single integer, without separator characters
   long int myDigit;
   if ( (j == string::npos) && StringUtils::IsDigit( s, myDigit ))
   {
      v.push_back( (int)(myDigit) );
      return;
   }

   // case of multiple integers, with the character defined by char c as separator characters
   while (j != string::npos)
   {
      v.push_back( atoi( (s.substr(i, j-i)).c_str() ));
      i = ++j;
      j = s.find(c, j);
      if (j == string::npos)
      {
         v.push_back( atoi( (s.substr(i, s.length( ))).c_str() ));
      }
   }
}

//-------------------------------------------------------------

bool StringUtils::IsDigit( string s, long int& myDigit )
{
   char * pEnd;

   myDigit = strtol ( s.c_str(), &pEnd, 10);

   stringstream ss1;
   ss1 << myDigit;

   if ( s.compare(ss1.str()) == 0 )
   {
      return true;
   }
   else
   {
      return false;
   }
}

//-------------------------------------------------------------

std::string StringUtils::GetCurrentTimeAsStringID()
{
   time_t rawtime;
   struct tm* ptm;

   time ( &rawtime );

   ptm = localtime ( &rawtime );

   stringstream ssTime;
   ssTime << (2000 + ptm->tm_year - 100)
          << std::string("_") << std::setw(2) << setfill('0') << ptm->tm_mon + 1
          << std::string("_") << std::setw(2) << setfill('0') << ptm->tm_mday
          << std::string("_") << std::setw(2) << setfill('0') << ptm->tm_hour
          << std::string("h") << std::setw(2) << setfill('0') << ptm->tm_min<< std::string("m");

   std::string timeOutString = ssTime.str();
   return timeOutString;
}

//-------------------------------------------------------------


}
}
