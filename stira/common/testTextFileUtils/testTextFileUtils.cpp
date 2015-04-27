#include <iostream>
#include <vector>
#include "../common/TextFileUtils.h"

using namespace std;
using namespace stira::common;

//-------------------------------------------------------------------

void TestTabSeparatedFile()
{
   Rows myData = TextFileUtils::ReadTabSeparatedLineFromTextFile( std::string("../../testdata/TabTextTest.txt") );
   int nrLines = myData.size();
   cout << "In TabTextTest.txt, there are " << nrLines << " lines..." << endl << flush;
   for (int lineID = 0; lineID < nrLines; lineID++)
   {
      int nrFields = myData[lineID].size();
      cout << "\t In line " << lineID << ", there are " << nrFields << " fields: " << flush;
      for (int fieldID = 0; fieldID < nrFields; fieldID++)
      {
         cout << "\t\t " << myData[lineID][fieldID] << endl << flush;
      }
   }
}

//-------------------------------------------------------------------

void TestReadLinesFromTextFile()
{
   std::string inFileName("TestFile.txt");
   static std::vector< std::string > vLinesRead = TextFileUtils::ReadLinesFromTextFile( inFileName );

   int nrLinesRead = vLinesRead.size();
   for( int i = 0; i < nrLinesRead; i++)
   {
      cout << "Line " << i << ":\t" << vLinesRead[i] << endl;
   }
}

//-------------------------------------------------------------------

int main()
{
   TestTabSeparatedFile();
   TestReadLinesFromTextFile();
   return 0;
}

