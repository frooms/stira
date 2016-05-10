
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

#ifndef STIRA_LIMA_VECTOR_H
#define STIRA_LIMA_VECTOR_H

#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

namespace stira {
namespace lima {

/** \brief A class to represent a vector of elements. */
template <typename T>
class Vector
{
public:
    Vector( unsigned int length );
    ~Vector( );

    unsigned int Length();

    T& operator[] (const unsigned int index) { return mpVector[index]; }


    /** \brief overloaded operator to add two Vectors
      * \param otherVector vector to add */
    Vector<T> operator + ( Vector<T>& otherVector );

    /** \brief overloaded operator to subtract two Vectors
      * \param otherVector vector to subtract */
    Vector<T> operator - ( Vector<T>& otherVector );

    T operator * ( Vector<T>& otherVector );

    Vector<T> operator ^ ( Vector<T>& otherVector );

    void Print( std::string name );

private:
    T* mpVector;
    unsigned int mLength;

};

//===================================================================

template <class T>
Vector<T>::Vector( unsigned int length )
{
    mLength = length;
    mpVector = new T[length];
    for ( unsigned int i = 0; i < length; i++ )
    {
       mpVector[i] = 0;
    }
}

//------------------------------------------------------------------

template <class T>
Vector<T>::~Vector( )
{
    delete []mpVector;
}

//------------------------------------------------------------------

template <class T>
unsigned int Vector<T>::Length()
{
    return mLength;
}

//------------------------------------------------------------------

template <class T>
void Vector<T>::Print( std::string name )
{
    std::cout << "Printing vector " << name  << std::endl;

    std::cout << "\t [ " << this->mpVector[0];
    for ( unsigned int i = 1; i < mLength; i++ )
    {
        std::cout << "\t " << this->mpVector[i];
    }
    std::cout << " ]" << std::endl;
}

//------------------------------------------------------------------

template <typename T>
Vector<T> Vector<T>::operator - ( Vector<T>& otherVector )
{
   Vector<T>* pSubVector = new Vector<T>( otherVector.Length() );

   for (unsigned int i = 0; i < this->Length(); i++)
   {
       (*pSubVector)[i] = this->mpVector[i] - otherVector[i];
   }
   return *pSubVector;
}

//------------------------------------------------------------------

template <typename T>
Vector<T> Vector<T>::operator + ( Vector<T>& otherVector )
{
   Vector<T>* pAddVector = new Vector<T>( otherVector.Length() );

   for (unsigned int i = 0; i < this->Length(); i++)
   {
       (*pAddVector)[i] = this->mpVector[i] + otherVector[i];
   }
   return *pAddVector;
}

//------------------------------------------------------------------

template <typename T>
T Vector<T>::operator * ( Vector<T>& otherVector )
{
   T tmpValue = 0;
   for (int i = 0; i < mLength; i++)
   {
       tmpValue += this->mpVector[i] + otherVector[i];
   }
   return tmpValue;
}

//------------------------------------------------------------------

template <typename T>
Vector<T> Vector<T>::operator ^ ( Vector<T>& otherVector )
{
   T tmpValue = 0;
   for (int i = 0; i < mLength; i++)
   {
       tmpValue += this->mpVector[i] + otherVector[i];
   }
   return tmpValue;
}

/*


template <class T>
Point<T> operator* (double a, const Point<T>& pt)
{
    return ( Point<T>( pt.x * a, pt.y * a, pt.GetMode(), pt.GetType() ) );
}

template <class T>
Point<T> operator* (const Point<T>& pt, double a)
{
    return ( Point<T>( pt.x * a, pt.y * a, pt.GetMode(), pt.GetType() ) );
}

//------------------------------------------------------------------

template <class T>
T Point<T>::operator ^ ( Point<T> otherPoint )
{
   return ( ( this->x * otherPoint.y ) - ( this->y * otherPoint.x ) );
}

//------------------------------------------------------------------

template <class T>
std::ostream& operator << ( std::ostream& output, const Point<T>& p )
{
   output << " ( " <<  p.x << ", " << p.y << " ) ";
   return output;  // for multiple << operators.
}

//------------------------------------------------------------------

template <class T>
bool Point<T>::operator== ( Point<T> otherPoint )
{
   if (    ( (double)(fabs( (double)(this->x) - (double)(otherPoint.x) )) < 0.0000001)
        && ( (double)(fabs( (double)(this->y) - (double)(otherPoint.y) )) < 0.0000001)
        && ( this->mode == otherPoint.mode )
      )
   {
      return true;
   }
   else
   {
      return false;
   }
}

//------------------------------------------------------------------

template <class T>
bool Point<T>::operator!= ( Point<T> otherPoint )
{
   return !( *this == otherPoint );
}*/


//------------------------------------------------------------------

}
}

#endif // VECTOR_H
