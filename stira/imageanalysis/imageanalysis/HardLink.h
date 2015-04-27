
#include <iostream>
#include <exception>
#include <list>
#include "../../image/datastructures/ArrayGrid.h"

// http://mafahir.wordpress.com/2011/02/02/image-thinningskeletonization-cc-implementation/

using namespace std;
using namespace stira;
using namespace stira::image;
class HardLink
{
public:

   static ArrayGrid<int>* MedialAxisTransform( ArrayGrid<int>* pGrid );

private:
   static bool Phase1( int i, int j, ArrayGrid<int>* pNewGrid, ArrayGrid<int>* pOriginalGrid );
   static bool Phase2( int i, int j, ArrayGrid<int>* pNewGrid, ArrayGrid<int>* pOriginalGrid );
};

class Cell
{
public:
   Cell(int i, int j, ArrayGrid<int>* pGridR);
   ~Cell(void);
   int Apz;
   int Bpz;
   int C1;
   int C2;
   int D1;
   int D2;
private:
   bool *matrix;
};
