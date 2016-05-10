
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

#ifndef STIRA_LIMA_MATRIX_H
#define STIRA_LIMA_MATRIX_H

#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>

#include "../lima/Vector.h"

namespace stira {
namespace lima {

/** \brief A class to represent a matrix class. */
template <typename T>
class Matrix
{
public:
    Matrix( unsigned int nrRows, unsigned int nrColumns )
    {
        mNrRows = nrRows;
        mNrColumns = nrColumns;
        mppMatrix = new T*[mNrRows];
        for( unsigned int i = 0; i < mNrRows; i++)
        {
           mppMatrix[i] = new T[mNrColumns];
           for (unsigned int j = 0; j < mNrColumns; j++)
           {
               mppMatrix[i][j] = 0;
           }
        }
    }

    unsigned int GetNrRows() { return mNrRows; }
    unsigned int GetNrColumns() { return mNrColumns; }

    class Proxy
    {
        public:
            Proxy(T* _array) : _array(_array) { }

            T& operator[](unsigned int index)
            {
                return _array[index];
            }
        private:
            T* _array;
    };

    Proxy operator[](unsigned int index) {
        return Proxy(mppMatrix[index]);
    }

    Matrix<T> operator * ( Matrix<T>& otherMatrix );

    ~Matrix();

    void Print( std::string name );

    // http://www.sci.utah.edu/~wallstedt/LU.htm
    Matrix<T> Doolittle( unsigned int d );
    Vector<T> SolveDoolittle( unsigned int d, Matrix<T>& LU, Vector<T>& b );
    std::pair< Matrix<T>, Matrix<T> > SplitDoolittle( Matrix<T>& LU );

    std::string name;
private:
    T** mppMatrix;
    unsigned int mNrRows;
    unsigned int mNrColumns;

};

//============================================================

template <typename T>
Matrix<T>::~Matrix( )
{
    std::cout << "Deleting matrix" << name << std::endl;
    for (unsigned int j = 0; j < mNrRows; j++)
    {
        delete []mppMatrix[j];
    }
    delete []mppMatrix;
}

//------------------------------------------------------------------

template <typename T>
Matrix<T> Matrix<T>::operator * ( Matrix<T>& otherMatrix )
{
   Matrix<T>* pMultMatrix = 0;

   if( this->mNrColumns == otherMatrix.GetNrRows() )
   {
      pMultMatrix = new Matrix<T>( this->mNrRows, otherMatrix.GetNrColumns() );

      for( unsigned int i = 0; i < pMultMatrix->GetNrRows(); i++ )
      {
         for( unsigned int j = 0; j < pMultMatrix->GetNrColumns(); j++ )
         {
            (*pMultMatrix)[i][j] = 0;
            for( unsigned int k = 0; k < mNrColumns; k++ )
               {
                  (*pMultMatrix)[i][j] += ( (*this)[i][k] * otherMatrix[k][j] );
               }
           }
       }
   }
   else
   {
      std::cerr << "\n Number of columns in Matrix1 is not equal to Number of rows in Matrix2.";
      std::cerr << "\n Therefore Multiplication of Matrix1 with Matrix2 is not possible";
   }

   return *pMultMatrix;
}

//------------------------------------------------------------------

template <typename T>
Matrix<T> Matrix<T>::Doolittle( unsigned int d )
{
    unsigned int n = mNrRows;
    Matrix<T>* pDest = new Matrix<T>( mNrRows, mNrColumns );
    pDest->name = std::string("doolittleDest");
    for( unsigned int k = 0; k < n; ++k )
    {
       for( unsigned int j = k; j < d; ++j )
       {
          double sum=0.;
          for( unsigned int p = 0; p < k; ++p )
          {
              sum += (*pDest)[k][p] * (*pDest)[p][j];
          }
          (*pDest)[k][j] = ( (*this)[k][j] - sum ); // not dividing by diagonals
       }

       for( unsigned int i = k + 1; i < d; ++i )
       {
          double sum = 0.;
          for( unsigned int p = 0; p < k; ++p )
          {
              sum += (*pDest)[i][p] * (*pDest)[p][k];
          }
          (*pDest)[i][k] = ( (*this)[i][k] - sum )/ (*pDest)[k][k];
       }
    }
    return *pDest;
}

//------------------------------------------------------------------

template <typename T>
std::pair< Matrix<T>, Matrix<T> > Matrix<T>::SplitDoolittle( Matrix<T>& LU )
{
    unsigned int n = mNrRows;
    Matrix<T>* L = new Matrix<T>( mNrRows, mNrColumns );
    Matrix<T>* U = new Matrix<T>( mNrRows, mNrColumns );
    L->name = std::string("splitL");
    U->name = std::string("splitU");

    // ROWS
    for( unsigned int row = 0; row < n; ++row )
    {
       // COLUMNS
       for( unsigned int col = 0; col < n; ++col )
       {
          if (col < row)
          {
              (*L)[row][col] = LU[row][col];
          }
          if (col == row)
          {
              (*L)[row][col] = 1;
          }
          if (col >= row)
          {
              (*U)[row][col] = LU[row][col];
          }
       }
    }
    return std::pair< Matrix<T>, Matrix<T> >( (*L), (*U) );
}

//------------------------------------------------------------------

template <typename T>
Vector<T> Matrix<T>::SolveDoolittle( unsigned int d, Matrix<T>& LU, Vector<T>& b )
{
   Vector<T>* x = new Vector<T>( d );
   double y[d];
   for( unsigned int i = 0; i < d; ++i )
   {
      double sum=0.;
      for( unsigned int k = 0; k < i; ++k )
      {
          sum += LU[i][k] * y[k];
      }
      y[i] = ( b[i] - sum ); // not dividing by diagonals
   }
   for(int i=d-1;i>=0;--i)
   {
      double sum=0.;
      for( unsigned int k = i + 1; k < d; ++k )
      {
          sum += LU[i][k] * (*x)[k];
      }
      (*x)[i] = ( y[i] - sum ) / LU[i][i];
   }
   return (*x);
}

//------------------------------------------------------------------

template <class T>
void Matrix<T>::Print( std::string name )
{
    std::cout << "Printing matrix " << name  << std::endl;
    for ( unsigned int j = 0; j < mNrRows; j++ )
    {
        std::cout << "\t [ " << this->mppMatrix[j][0];
        for ( unsigned int i = 1; i < mNrColumns; i++ )
        {
            std::cout << "\t " << this->mppMatrix[j][i];
        }
        std::cout << " ]" << std::endl;
    }
}

//------------------------------------------------------------------


}
}
#endif // MATRIX_H
