
/***************************************************************************************
 *   Copyright (C) 2016 by Filip Rooms                                                 *
 *                                                                                     *
 *  Terms and conditions for using this software in any form are provided in the       *
 *  file COPYING, which can be found in the root directory of this project.            *
 *                                                                                     *
 *   Contact data: filip.rooms@gmail.com                                               *
 *                 http://www.filiprooms.be/                                           *
 *                                                                                     *
 ***************************************************************************************/

#include "../lima/Vector.h"
#include "../lima/Matrix.h"
#include <iostream>
#include <cassert>
#include <sstream>

using namespace std;
using namespace stira::lima;

//-------------------------------------------------------------------

bool TestVector()
{
   bool result = true;

   Vector<int> myVector1( 3 );
   myVector1[0] = 2;
   myVector1[1] = 4;
   myVector1[2] = 6;
   for (unsigned int i = 0; i < myVector1.Length(); i++)
   {
       cout << "Before: element i = " << myVector1[i] << endl;
   }
   cout << flush;

   assert( myVector1.Length() == 3 );
   assert( myVector1[1] == 4 );
   myVector1[1] = 7;
   for (unsigned int i = 0; i < myVector1.Length(); i++)
   {
       cout << "After: element i = " << myVector1[i] << endl;
   }

   Vector<int> myVector2( 3 );
   myVector2[0] = 1;
   myVector2[1] = -2;
   myVector2[2] = 3;
   cout << flush;

   Vector<int> addVector = myVector1 + myVector2;
   cout << flush;
   for (unsigned int i = 0; i < myVector1.Length(); i++)
   {
       cout << "Add: element i = " << addVector[i] << endl;
   }
   cout << flush;

   Vector<int> subVector = myVector1 - myVector2;
   cout << flush;
   for (unsigned int i = 0; i < subVector.Length(); i++)
   {
       cout << "Sub: element i = " << subVector[i] << endl;
   }
   cout << flush;

   return result;
}

//-------------------------------------------------------------------

bool TestMatrixMultiplication()
{
   bool result = true;

   //http://code.wikia.com/wiki/Matrix_multiplication
   unsigned int aRows = 2;
   unsigned int aCols = 4;
   Matrix<double> a( aRows, aCols );

   a[0][0] = 2;
   a[0][1] = 3;
   a[0][2] = -1;
   a[0][3] = 0;
   a[1][0] = -7;
   a[1][1] = 2;
   a[1][2] = 1;
   a[1][3] = 10;
   a.Print(std::string("a"));

   unsigned int bRows = 4;
   unsigned int bCols = 2;
   Matrix<double> b( bRows, bCols );
   b[0][0] = 3;
   b[0][1] = 4;
   b[1][0] = 2;
   b[1][1] = 1;
   b[2][0] = -1;
   b[2][1] = 2;
   b[3][0] = 2;
   b[3][1] = 7;
   b.Print(std::string("b"));

   Matrix<double> c = a * b;
   c.Print(std::string("c"));

   return result;
}

//-------------------------------------------------------------------

bool TestMatrixEigenValues()
{
   bool result = true;

   // https://en.wikipedia.org/wiki/Eigenvalue_algorithm
   unsigned int aRows = 3;
   unsigned int aCols = 3;
   Matrix<double> a( aRows, aCols );

   a[0][0] = 3;
   a[0][1] = 2;
   a[0][2] = 6;

   a[1][0] = 2;
   a[1][1] = 2;
   a[1][2] = 5;

   a[2][0] = -2;
   a[2][1] = -1;
   a[2][2] = -4;

   a.Print(std::string("a"));

   std::vector<double> eigenValues = a.ComputeEigenValues();

   for (int i = 0; i < eigenValues.size(); i++)
   {
       std::cout << eigenValues[i] << std:: endl;
   }

   return result;
}

//-------------------------------------------------------------------

bool TestDecomposeLU()
{
   bool result = true;

   unsigned int aRows = 3;
   unsigned int aCols = 3;
   Matrix<double> a( aRows, aCols );

   a[0][0] = 1;
   a[0][1] = 2;
   a[0][2] = 4;
   a[1][0] = 3;
   a[1][1] = 8;
   a[1][2] = 14;
   a[2][0] = 2;
   a[2][1] = 6;
   a[2][2] = 13;
   a.Print(std::string("a"));

   Matrix<double> dDL = a.LU_Doolittle( 3 );
   dDL.Print(std::string("dDoolittle"));
   std::cout << "Determinant Doolittle = " << Matrix<double>::Determinant( dDL) << std::endl;

   std::pair< Matrix<double>, Matrix<double> > luDL = Matrix<double>::SplitDoolittle( dDL );

   luDL.first.Print("lDoolittle");
   luDL.second.Print("uDoolittle");


   Matrix<double> aBackDL = luDL.first * luDL.second;
   aBackDL.Print("aBackDoolittle");

   Matrix<double> dCr = a.LU_Crout( 3 );
   dCr.Print(std::string("dCrout"));
   std::cout << "Determinant Crout = " << Matrix<double>::Determinant( dCr ) << std::endl;

   std::pair< Matrix<double>, Matrix<double> > luCr = Matrix<double>::SplitCrout( dCr );

   luCr.first.Print("lCrout");
   luCr.second.Print("uCrout");

   Matrix<double> aBackCr = luCr.first * luCr.second;
   aBackCr.Print("aBackCrout");

   return result;
}

//-------------------------------------------------------------------

bool TestSolveSystem()
{
   bool result = true;

   unsigned int aRows = 2;
   unsigned int aCols = 2;
   Matrix<double> a( aRows, aCols );

   a[0][0] = 2;
   a[0][1] = -3;
   a[1][0] = 4;
   a[1][1] = 1;
   a.Print(std::string("a"));

   unsigned int bLength = 2;
   Vector<double> b( bLength );
   b[0] = -2;
   b[1] = 24;
   b.Print(std::string("b"));

   Matrix<double> luDL = a.LU_Doolittle( 2 );
   Vector<double> xDL = a.SolveDoolittle(2, luDL, b);
   xDL.Print(std::string("xDoolittle"));

   std::cout << "Determinant Doolittle = " << Matrix<double>::Determinant( luDL) << std::endl;

   Matrix<double> luCr = a.LU_Crout( 2 );
   Vector<double> xCr = a.SolveCrout( 2, luCr, b );
   xCr.Print(std::string("xCrout"));

   std::cout << "Determinant Crout = " << Matrix<double>::Determinant( luCr ) << std::endl;

   return result;
}

//-------------------------------------------------------------------
// example from https://en.wikipedia.org/wiki/QR_decomposition
bool TestDecomposeQR()
{
   bool result = true;
   bool sing = false;

   unsigned int aRows = 3;
   unsigned int aCols = 3;
   Matrix<double>  a( aRows, aCols );
   Matrix<double> qt( aRows, aCols );

   a[0][0] = 12;
   a[0][1] = -51;
   a[0][2] = 4;
   a[1][0] = 6;
   a[1][1] = 167;
   a[1][2] = -68;
   a[2][0] = -4;
   a[2][1] = 24;
   a[2][2] = -41;

   Matrix<double>  r( a );

   a.Print(std::string("a"));

   a.DecomposeQR( aRows, qt, r, sing );

   qt.Print("Q transpose");
   r.Print("R");

   return result;
}

//-------------------------------------------------------------------

int main()
{
   TestVector();
   TestMatrixMultiplication();

   TestMatrixEigenValues();

   TestDecomposeLU();
   TestSolveSystem();
   TestDecomposeQR();
}
