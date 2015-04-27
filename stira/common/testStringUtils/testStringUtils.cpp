
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

#include "../common/ExecutionTimer.h"
#include "../common/FileAccess.h"
#include "../common/TextFileUtils.h"
#include "../common/FixedBuffer.h"
#include "../common/StringUtils.h"
#include <iostream>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <sstream>

using namespace std;
using namespace stira::common;

//-------------------------------------------------------------------

void TestConvertStringToNumber()
{
   int i = 7480;
   float f = 256.1254;
   double d = 3.141592;


   std::string s1("7480");
   std::string s2("256.1254");
   std::string s3("3.141592");

   int iTest = StringUtils::ConvertStringToInt(s1);
   float fTest = StringUtils::ConvertStringToFloat(s2);
   double dTest = StringUtils::ConvertStringToDouble(s3);

   cout << "number i " << i << " and string converted to number " << iTest << " equal? " << (i == iTest) << endl;
   cout << "number f " << f << " and string converted to number " << fTest << " equal? " << (f == fTest) << endl;
   cout << "number d " << d << " and string converted to number " << dTest << " equal? " << (d == dTest) << endl;

   assert ( abs(i - iTest) < 0.000001);
   assert ( fabs(f - fTest) < 0.000001);
   assert ( fabs(d - dTest) < 0.000001);
}

//-------------------------------------------------------------------

void TestStringIsDigit()
{
   std::string s1("7480");
   std::string s2("256,266,2103,2128,4245,8409,8540,9759");
   std::string s3("NO_ERRORS");

   long int li1;
   bool b1 = StringUtils::IsDigit( s1, li1 );
   cout << s1 << "\t" << li1 << "\t" << b1 << endl;

   long int li2;
   bool b2 = StringUtils::IsDigit( s2, li2 );
   cout << s2 << "\t" << li2 << "\t" << b2 << endl;

   long int li3;
   bool b3 = StringUtils::IsDigit( s3, li3 );
   cout << s3 << "\t" << li3 << "\t" << b3 << endl;
}

//-------------------------------------------------------------------

void TestStringAnalyse()
{
   bool useUnderscoreAsSeparator = false;
   bool includeDotInExtension = true;

   std::string fileIn = std::string("/scratch/hdd/frooms/IntermediaryImages/U0049/LocalWidthAndPosition/LocalWidth-0078.txt");

   std::string pathName      = StringUtils::ExtractPathOfFileName( fileIn );
   std::string fileName      = StringUtils::ExtractFileName( fileIn );
   std::string rootName      = StringUtils::ExtractFileNameRoot( fileIn );
   std::string prefixName    = StringUtils::ExtractFilePrefix( fileIn, useUnderscoreAsSeparator );
   int fileIndex             = StringUtils::GetIndexFromFileName( fileIn, useUnderscoreAsSeparator );
   std::string extensionName = StringUtils::ExtractFileExtension( fileIn, includeDotInExtension );

   std::string pathNameRef      = std::string("/scratch/hdd/frooms/IntermediaryImages/U0049/LocalWidthAndPosition/");
   std::string fileNameRef      = std::string("LocalWidth-0078.txt");
   std::string rootNameRef      = std::string("LocalWidth-0078");
   std::string prefixNameRef    = std::string("LocalWidth");
   int fileIndexRef             = 78;
   std::string extensionNameRef = std::string(".txt");

   cout << "In: " << fileIn << endl << flush;
   cout << "\t path        = " << pathName      << "\n\t\t ref = " << pathNameRef << endl << flush;
   cout << "\t path        = " << fileName      << "\n\t\t ref = " << fileNameRef << endl << flush;
   cout << "\t root name   = " << rootName      << "\n\t\t ref = " << rootNameRef << endl << flush;
   cout << "\t prefix name = " << prefixName    << "\n\t\t ref = " << prefixNameRef << endl << flush;
   cout << "\t index       = " << fileIndex     << "\n\t\t ref = " << fileIndexRef << endl << flush;
   cout << "\t extension   = " << extensionName << "\n\t\t ref = " << extensionNameRef << endl << flush;

   assert( pathName == pathNameRef );
   assert( fileName == fileNameRef );
   assert( rootName == rootNameRef );
   assert( prefixName == prefixNameRef );
   assert( fileIndex == fileIndexRef );
   assert( extensionName == extensionNameRef );
}
//-------------------------------------------------------------------

void TestStringUtils()
{
   bool includeDotInExtension = true;

   std::string fileIn = std::string("/v/frooms/research/projects/color/warhol-last/matlab/SpectraleRegressie/references-all-sorted-bis.txt");

   std::string pathName = StringUtils::ExtractPathOfFileName( fileIn );
   std::string rootName = StringUtils::ExtractFileNameRoot( fileIn );
   std::string extensionName = StringUtils::ExtractFileExtension( fileIn, includeDotInExtension );

   std::string pathNameRef = std::string("/v/frooms/research/projects/color/warhol-last/matlab/SpectraleRegressie/");
   std::string rootNameRef = std::string("references-all-sorted-bis");
   std::string extensionNameRef = std::string(".txt");

   cout << "In: " << fileIn << endl << flush;
   cout << "\t path      = " << pathName << "\n\t\t ref = " << pathNameRef << endl << flush;
   cout << "\t root name = " << rootName  << "\n\t\t ref = " << rootNameRef << endl << flush;
   cout << "\t extension = " << extensionName << "\n\t\t ref = " << extensionNameRef << endl << flush;

   assert( pathName == pathNameRef );
   assert( rootName == rootNameRef );
   assert( extensionName == extensionNameRef );


   std::vector< std::string > fileList;
   std::string testFile1("File_0001.txt");   fileList.push_back( testFile1 );
   std::string testFile3("File_0034.txt");   fileList.push_back( testFile3 );
   std::string testFile4("File_0465.txt");   fileList.push_back( testFile4 );
   std::string testFile6("File_1692.txt");   fileList.push_back( testFile6 );
   std::string testFile9("File_2982.txt");   fileList.push_back( testFile9 );

   int findID = 465;
   std::string findFile = StringUtils::FindFileNameInListFromIndex( findID, fileList );

   cout << "File found in list with " <<  findID << " is " << findFile << endl;

   std::string fileName = std::string("T0498_123456.pgm");

   int index =  StringUtils::GetIndexFromFileName( fileName );
   cout << " index is " << index << endl << flush;
}

//-------------------------------------------------------------------

void TestStringSplit()
{
   std::string stringToSplit = std::string("10, 20, 35, 45, 12");
   cout << "Splitting string " << stringToSplit << endl;

   std::vector<int> vectorStrings;

   StringUtils::SplitStringInIntegers( stringToSplit, ',', vectorStrings );
   int nrStrings = vectorStrings.size();

   for (int i = 0; i < nrStrings; i++)
   {
      cout << "String " << i << " = " << vectorStrings[i] << endl;
   }
}

//-------------------------------------------------------------------

void TestRandomString()
{
   int nrRandomStrings = 25;
   int stringLength = 35;
   for (int i=0; i < nrRandomStrings; i++)
   {
      cout << /*"RandomString " << i << " is " <<*/ StringUtils::GenerateRandomString( stringLength ) << endl;
   }
}

int main()
{
   TestConvertStringToNumber();
   TestStringIsDigit();
   TestStringAnalyse();
   TestStringUtils();
   TestStringSplit();
   TestRandomString();

   return 0;
}

