
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
#include <cassert>

template<class T>
inline T SQR(const T a) {return a*a;}

template<class T>
inline const T &MAX(const T &a, const T &b)
        {return b > a ? (b) : (a);}

template<class T>
inline T SIGN(const T &a, const T &b)
    {return b >= 0 ? (a >= 0 ? a : -a) : (a >= 0 ? -a : a);}


#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>

#include "../lima/Vector.h"

namespace stira {
namespace lima {

/** \brief A class to help indexing a matrix with two indices. */
template <typename T>
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
//============================================================
//============================================================

/** \brief A class to represent a matrix class */
template <typename T>
class Matrix
{
public:

    /** \brief constructor
      * \param nrRows number of rows in matrix
      * \param nrColumns number of columns in matrix */
    Matrix( unsigned int nrRows, unsigned int nrColumns );

    Matrix(const Matrix & otherMatrix);

    /** \brief destructor */
    ~Matrix();

    /** \brief gets number of rows in this matrix */
    unsigned int GetNrRows() const { return mNrRows; }

    /** \brief gets number of columns in this matrix */
    unsigned int GetNrColumns() const { return mNrColumns; }

    T GetValue(int i, int j) const { return mppMatrix[i][j]; }

    /** \brief proxy operator to allow double indexing matrix [i][j] of matrices */
    Proxy<T> operator[](unsigned int index) { return Proxy<T>(mppMatrix[index]); }

    /** \brief overloaded multiplication operator to be able to multiply matrices
        TODO add checks if matrices have right number of rows and columns to be able to be multiplied */
    Matrix<T> operator * ( Matrix<T>& otherMatrix );

    /** \brief print current matrix using tag "name" to standard output */
    void Print( std::string name );

    T Trace( );

    T ComputeDeterminant();

    std::vector<double> ComputeEigenValues( );

    // LU Decomposition routines
    //////////////////////////////

    // http://www.sci.utah.edu/~wallstedt/LU.htm
    Matrix<T> LU_Doolittle( unsigned int d );
    Vector<T> SolveDoolittle( unsigned int d, Matrix<T>& LU, Vector<T>& b );
    static std::pair< Matrix<T>, Matrix<T> > SplitDoolittle( Matrix<T>& LU );

    static T Determinant( Matrix<T>& LU );

    Matrix<T> LU_Crout( unsigned int d );
    Vector<T> SolveCrout( unsigned int d, Matrix<T>& LU, Vector<T>& b );
    static std::pair< Matrix<T>, Matrix<T> > SplitCrout( Matrix<T>& LU );

    // QR decomposition, from Numerical Recipes
    void DecomposeQR( int n, Matrix<T>& qt, Matrix<T>& r, bool& sing );

    std::string name;
private:
    T** mppMatrix;
    unsigned int mNrRows;
    unsigned int mNrColumns;
};

//============================================================

template <typename T>
Matrix<T>::Matrix( unsigned int nrRows, unsigned int nrColumns )
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

//------------------------------------------------------------------

template <typename T>
Matrix<T>::Matrix( const Matrix & otherMatrix )
{
    mNrRows = otherMatrix.GetNrRows();
    mNrColumns = otherMatrix.GetNrColumns();
    mppMatrix = new T*[mNrRows];

    for( unsigned int i = 0; i < mNrRows; i++)
    {
       mppMatrix[i] = new T[mNrColumns];
       for (unsigned int j = 0; j < mNrColumns; j++)
       {
           mppMatrix[i][j] = otherMatrix.GetValue( i, j );
       }
    }

}

//------------------------------------------------------------------

template <typename T>
Matrix<T>::~Matrix( )
{
    //std::cout << "Deleting matrix" << name << std::endl;
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
Matrix<T> Matrix<T>::LU_Doolittle( unsigned int d )
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
    unsigned int n = LU.GetNrRows();
    Matrix<T>* L = new Matrix<T>( LU.GetNrRows(), LU.GetNrColumns() );
    Matrix<T>* U = new Matrix<T>( LU.GetNrRows(), LU.GetNrColumns() );
    L->name = std::string("splitDoolittleL");
    U->name = std::string("splitDoolittleU");

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
T Matrix<T>::Determinant( Matrix<T>& LU )
{
    unsigned int n = LU.GetNrRows();
    T determinantValue = 1;
    for ( unsigned int i = 0; i < n; i++)
    {
        determinantValue *= LU[i][i];
    }
    return determinantValue;
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
   for( int i = d - 1; i >= 0; --i )
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

template <typename T>
Matrix<T> Matrix<T>::LU_Crout( unsigned int d )
{
   Matrix<T>* pDest = new Matrix<T>( mNrRows, mNrColumns );
   pDest->name = std::string("croutDest");
   for( unsigned int k = 0; k < d; ++k )
   {
      for( unsigned int i = k; i < d; ++i )
      {
         double sum = 0.0;
         for( unsigned int p = 0; p < k; ++p )
         {
             sum += (*pDest)[i][p] * (*pDest)[p][k];
         }
         (*pDest)[i][k] = (*this)[i][k] - sum; // not dividing by diagonals
      }
      for( unsigned int j = k + 1; j < d; ++j )
      {
         double sum = 0.;
         for( unsigned int p = 0; p < k; ++p )
         {
             sum += (*pDest)[k][p] * (*pDest)[p][j];
         }
         (*pDest)[k][j] = ( (*this)[k][j] - sum) / (*pDest)[k][k];
      }
   }
   return *pDest;
}

//------------------------------------------------------------------

template <typename T>
std::pair< Matrix<T>, Matrix<T> > Matrix<T>::SplitCrout( Matrix<T>& LU )
{
    unsigned int n = LU.GetNrRows();
    Matrix<T>* L = new Matrix<T>( LU.GetNrRows(), LU.GetNrColumns() );
    Matrix<T>* U = new Matrix<T>( LU.GetNrRows(), LU.GetNrColumns() );
    L->name = std::string("splitCroutL");
    U->name = std::string("splitCroutU");

    // ROWS
    for( unsigned int row = 0; row < n; ++row )
    {
       // COLUMNS
       for( unsigned int col = 0; col < n; ++col )
       {
          if (col <= row)
          {
              (*L)[row][col] = LU[row][col];
          }
          if (col == row)
          {
              (*U)[row][col] = 1;
          }
          if (col > row)
          {
              (*U)[row][col] = LU[row][col];
          }
       }
    }
    return std::pair< Matrix<T>, Matrix<T> >( (*L), (*U) );
}

//------------------------------------------------------------------

template <typename T>
Vector<T> Matrix<T>::SolveCrout( unsigned int d, Matrix<T>& LU, Vector<T>& b )
{
   Vector<T>* x = new Vector<T>( d );
   double y[d];
   for( unsigned int i = 0; i < d; ++i )
   {
      double sum = 0.0;
      for( unsigned int k = 0; k < i; ++k )
      {
          sum += LU[i][k] * y[k];
      }
      y[i] = ( b[i] - sum ) / LU[i][i];
   }
   for( int i = d - 1; i >= 0; i-- )
   {
      double sum = 0.0;
      for( unsigned int k = i + 1; k < d; k++ )
      {
          sum += LU[i][k] * (*x)[k];
      }
      (*x)[i] = ( y[i] - sum ); // not dividing by diagonals
   }
   return (*x);
}

//------------------------------------------------------------------

template <typename T>
void Matrix<T>::DecomposeQR( int n, Matrix<T>& qt, Matrix<T>& r, bool& sing )
{
    int i, j, k;
    Vector<T> c(n), d(n);
    double scale, sigma, sum, tau;

    for ( k = 0; k < n-1; k++ )
    {
        scale = 0.0;
        for ( i = k; i < n; i++ )
        {
            scale = MAX( scale, fabs( r[i][k] ) );
        }

        if (scale == 0.0)
        {
            sing = true;
            c[k] = d[k] = 0.0;
        }
        else
        {
            for ( i = k; i < n; i++ )
            {
                r[i][k] /= scale;
            }
            for ( sum = 0.0, i = k; i < n; i++ )
            {
                sum += SQR( r[i][k] );
            }
            sigma = SIGN( sqrt(sum), r[k][k] );
            r[k][k] += sigma;
            c[k] = sigma * r[k][k];
            d[k] = - scale * sigma;
            for ( j = k + 1; j < n; j++ )
            {
                for ( sum = 0.0, i = k; i < n; i++ )
                {
                    sum += r[i][k]*r[i][j];
                }
                tau = sum / c[k];
                for ( i = k; i < n; i++ )
                {
                    r[ i ][ j ] -= tau * r[ i ][ k ];
                }
            }
        }
    }
    d[ n - 1 ] = r[ n - 1 ][ n - 1 ];
    if ( d[ n - 1 ] == 0.0 )
        sing = true;
    for ( i = 0; i < n; i++ )
    {
        for (int j = 0; j < n; j++ )
            qt[i][j] = 0.0;
        qt[i][i] = 1.0;
    }
    for ( k = 0; k < n - 1 ; k++ )
    {
        if ( c[k] != 0.0 )
        {
            for ( j = 0; j < n; j++ )
            {
                sum = 0.0;
                for ( i = k; i < n; i++ )
                {
                    sum += r[i][k] * qt[i][j];
                }
                sum /= c[k];
                for (int i = k; i < n; i++ )
                {
                    qt[i][j] -= sum * r[i][k];
                }
            }
        }
    }
    for ( i = 0; i < n; i++ )
    {
        r[i][i]=d[i];
        for ( j = 0; j < i; j++ )
        {
            r[i][j] = 0.0;
        }
    }
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

template <class T>
T Matrix<T>::Trace( )
{
    T  resultTrace = 0;
    assert(mNrRows==mNrColumns);
    for ( unsigned int j = 0; j < mNrRows; j++ )
    {
        for ( unsigned int i = 0; i < mNrColumns; i++ )
        {
            if (i == j) {resultTrace += this->mppMatrix[j][i];}
        }
    }
    return resultTrace;
}
//------------------------------------------------------------------

template <class T>
T Matrix<T>::ComputeDeterminant()
{
    T  resultDeterminant = 0;

    assert(mNrRows==mNrColumns);
    Matrix<double> dCr = this->LU_Crout( mNrColumns );
    resultDeterminant = Matrix<double>::Determinant( dCr );
    return resultDeterminant;
}

//------------------------------------------------------------------
// https://en.wikipedia.org/wiki/Eigenvalue_algorithm
// Given a real symmetric 3x3 matrix A, compute the eigenvalues
template <class T>
std::vector<double> Matrix<T>::ComputeEigenValues( )
{
    double eig1, eig2, eig3;
    std::vector<double> eigenValues;
    double p1 = mppMatrix[0][1] * mppMatrix[0][1] + mppMatrix[0][2] * mppMatrix[0][2] + mppMatrix[1][2] * mppMatrix[1][2];
    if (p1 == 0)
    {
        // A is diagonal.
        eig1 = mppMatrix[0][0];
        eig2 = mppMatrix[1][1];
        eig3 = mppMatrix[2][2];
    }
    else
    {
        double q = this->Trace() / 3.0;
        double aq0 = mppMatrix[0][0] - q;
        double aq1 = mppMatrix[1][1] - q;
        double aq2 = mppMatrix[2][2] - q;
        double p2 = aq0*aq0 + aq1*aq1 + aq2*aq2 + 2.0 * p1;
        double p = sqrt(p2 / 6.0);
        Matrix<T> B(*this);

        B[0][0] = mppMatrix[0][0] - q;
        B[1][1] = mppMatrix[1][1] - q;
        B[2][2] = mppMatrix[2][2] - q;
        for ( unsigned int j = 0; j < mNrRows; j++ )
        {
            for ( unsigned int i = 0; i < mNrColumns; i++ )
            {
                B[j][i] /= p;
            }
        }

        double r  = this->ComputeDeterminant() / 2.0;

        // In exact arithmetic for a symmetric matrix  -1 <= r <= 1
        // but computation error can leave it slightly outside this range.
        double phi;
        if (r <= -1.0)
           phi = M_PI / 3.0;
        else if (r >= 1.0)
           phi = 0.0;
        else
           phi = acos(r) / 3.0;

        // the eigenvalues satisfy eig3 <= eig2 <= eig1
        eig1 = q + 2.0 * p * cos(phi);
        eig3 = q + 2.0 * p * cos(phi + (2.0 * M_PI / 3.0 ) );
        eig2 = 3.0 * q - eig1 - eig3;     // since trace(A) = eig1 + eig2 + eig3
    }
    eigenValues.push_back(eig1);
    eigenValues.push_back(eig2);
    eigenValues.push_back(eig3);
    return eigenValues;
}

}
}
#endif // MATRIX_H
