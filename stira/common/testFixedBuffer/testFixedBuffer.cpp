
#include "../common/FixedBuffer.h"
#include <iostream>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <sstream>

using namespace std;
using namespace stira::common;

//-------------------------------------------------------------------

void TestFixedBufferAddElements()
{
   cout << "Test Add Elements..." << endl << flush;
   cout << "--------------------" << endl << flush;
   int maxSize = 5;
   FixedBuffer<int> fb( maxSize );

   for (int i = 0; i < 10; i++)
   {
      cout << "i = " << i;
      fb.AddElement( i );
      int mySize = fb.GetSize();
      cout << "\t Size is now " << mySize << endl;
      for ( int j = 0; j < mySize; j++ )
      {
         cout << "\t" << fb.GetElementFromStart( j );
      }
      cout << endl << flush;
   }
}

//-------------------------------------------------------------------
//-------------------------------------------------------------------

void TestFixedBufferInsertElements()
{
   cout << "Test Insert Elements..." << endl << flush;
   cout << "-----------------------" << endl << flush;
   int maxSize = 13;
   FixedBuffer<int> fb( maxSize );

   for (int i = 0; i < maxSize; i++)
   {
      fb.AddElement( i );
   }

   int currentSize = fb.GetSize();
   cout << "\t Size before insert is " << currentSize << endl;
   for ( int j = 0; j < currentSize; j++ )
   {
      cout << "\t" << fb.GetElementFromStart( j );
   }
   cout << endl << flush;
   cout << endl << flush;

   int position = 5;
   int newElement = 17;
   cout << "Adding value " << newElement << " at position " << position << endl;
   cout << endl << flush;

   fb.InsertElementFromStart( newElement, position );

   currentSize = fb.GetSize();
   cout << "\t Size after insert is " << currentSize << endl;
   for ( int j = 0; j < currentSize; j++ )
   {
      cout << "\t" << fb.GetElementFromStart( j );
   }
   cout << endl << flush;

}

//-------------------------------------------------------------------

int main()
{
   TestFixedBufferAddElements();
   TestFixedBufferInsertElements();
   return 0;
}

