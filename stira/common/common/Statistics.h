
/***************************************************************************************
 *   Copyright (C) 2010 by Filip Rooms                                                 *
 *                                                                                     *
 *  Terms and conditions for using this software in any form are provided in the       *
 *  file COPYING, which can be found in the root directory of this project.            *
 *                                                                                     *
 *   Contact data: filip.rooms@gmail.com                                               *
 *                 http://www.filiprooms.be/                                           *
 *                                                                                     *
 ***************************************************************************************/

#include <iostream>
#include <vector>

#include <cassert>
#include <fstream>
#include <cfloat>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>

#include "Point.h"

#ifndef STIRA_COMMON_STATISTICS_H
#define STIRA_COMMON_STATISTICS_H

using namespace std;

namespace stira {
namespace common {

/** \brief class to compute some simple statistics
  * Note void ProcessArray ( const int * , size_t numInts ) ;
  * can be called directly with an stl vector as follows
  *           ProcessArray ( &foo[0], foo.size() );*/
template <class T>
class Statistics
{
public:
   // 1. AVERAGES
   //////////////

   /** \brief Computes the average of the elements in the given array
     * \param pData pointer to array of values
     * \param nrElements number of elements in the array*/
   static double GetAverage( T* pData, int nrElements );

   /** \brief Computes the average of the elements in the given STL vector (Calls pointer-based method)
     * \param vData STL vector of values */
   static double GetAverage( std::vector<T> vData );

   // 2. VARIANCES
   ///////////////

   /** \brief Computes the variance of the elements in the given array
     * Computes implicitely the average of the elements to be able to compute the variance
     * \param pData pointer to array of values
     * \param nrElements number of elements in the array*/
   static double GetVariance( T* pData, int nrElements );

   /** \brief Computes the variance of the elements in the given vector (Calls pointer-based method)
     * Computes implicitely the average of the elements to be able to compute the variance
     * \param vData vector of values */
   static double GetVariance( std::vector<T> vData );

   /** \brief Computes the variance of the elements in the given array
     * Uses the average passed as argument to compute the variance
     * \param pData pointer to array of values
     * \param nrElements number of elements in the array
     * \param average Uses this value as average to compute the variance*/
   static double GetVariance( T* pData, int nrElements, double average );

   /** \brief Computes the variance of the elements in the given vector (Calls pointer-based method)
     * Uses the average passed as argument to compute the variance
     * \param vData vector of values
     * \param average Uses this value as average to compute the variance*/
   static double GetVariance( std::vector<T> vData, double average );

   // 3. CORRELATIONS
   //////////////////

   /** \brief Computes the correlation between the elements in two given vectors
     * \param pData1 pointer to first array of values
     * \param pData2 pointer to second array of values
     * \param nrElements number of elements */
   static double GetCorrelation( double* pData1, double* pData2, int nrElements );

   /** \brief Computes the correlation between the elements in two given vectors
     * \param vData1 vector 1 of values
     * \param vData2 vector 2 of values */
   static double GetCorrelation( std::vector<double> vData1,  std::vector<double> vData2 );

   // 4. OTHERS
   ////////////

   static std::pair< double, double > ComputeFirstTwoCentralMoments( std::vector< Point<double> > inPoints );

};

//====================================================================================

// 1. AVERAGES
//////////////

template <class T>
double Statistics<T>::GetAverage( T* pData, int nrElements )
{
   double average = 0.0;
   for (int i = 0; i < nrElements; i++)
   {
      average += pData[i];
   }
   return average / nrElements;
}

//-----------------------------------------------------------------------------

template <class T>
double Statistics<T>::GetAverage( std::vector<T> vData )
{
   return GetAverage( &vData[0], vData.size() );
}

//-----------------------------------------------------------------------------

// 2. VARIANCES
///////////////

template <class T>
double Statistics<T>::GetVariance( T* pData, int nrElements, double average )
{
   double tmpVariance = 0.0;

   for (int i = 0; i < nrElements; i++ )
   {
      double ttt = pData[i] - average;
      tmpVariance += (ttt * ttt);
   }
   return (tmpVariance / (double)( nrElements - 1));
}

//-----------------------------------------------------------------------------

template <class T>
double Statistics<T>::GetVariance( std::vector<T> vData, double average )
{
   return GetVariance( &vData[0], vData.size(), average );
}

//-----------------------------------------------------------------------------

template <class T>
double Statistics<T>::GetVariance( T* pData, int nrElements )
{
   return GetVariance( pData, nrElements, GetAverage( pData, nrElements ) );
}

//-----------------------------------------------------------------------------

template <class T>
double Statistics<T>::GetVariance( std::vector<T> vData )
{
   return GetVariance( &vData[0], vData.size(), GetAverage( &vData[0], vData.size() ) );
}

//-----------------------------------------------------------------------------

// 3. CORRELATIONS
//////////////////
//https://en.wikipedia.org/wiki/Correlation_and_dependence
template <class T>
double Statistics<T>::GetCorrelation( double* pData1, double* pData2, int nrElements )
{
   double sumX = 0.0;
   double sumY = 0.0;
   double sumX2 = 0.0;
   double sumY2 = 0.0;
   double sumXY = 0.0;

   for ( int i = 0; i < nrElements; i++ )
   {
      double x = pData1[ i ];
      double y = pData2[ i ];
      sumX += x;
      sumY += y;
      sumX2 += (x*x);
      sumY2 += (y*y);
      sumXY += (x*y);
   }

   double correlation =  ( nrElements * sumXY - ( sumX * sumY ) )
                       / (   sqrt(   ( nrElements * sumX2 - ( sumX * sumX ) )
                                   * ( nrElements * sumY2 - ( sumY * sumY ) )
                                 )
                         );
   return correlation;
}


//-----------------------------------------------------------------------------

template <class T>
double Statistics<T>::GetCorrelation( std::vector<double> vData1,  std::vector<double> vData2 )
{
   int vSize = vData1.size();

   return GetCorrelation( &vData1[0], &vData2[0], vSize );
}

//----------------------------------------------------------------------------------------------------

// 4. OTHERS
////////////

template <class T>
std::pair< double, double > Statistics<T>::ComputeFirstTwoCentralMoments( std::vector< Point<double> > inPoints )
{
   std::pair< double, double > ppp;
   int length = inPoints.size();

   // normalize
   double total = 0.0;
   for (int i = 0; i < length; i++)
   {
      total += inPoints[i].GetY();
   }
   for (int i = 0; i < length; i++)
   {
      inPoints[i].SetY( inPoints[i].GetY() / total );
   }

   // estimate first moment, the expectance value
   double teller = 0.0;
   double noemer = 0.0;
   for (int i = 0; i < length; i++)
   {
      teller += inPoints[i].GetX() * inPoints[i].GetY();
      noemer += inPoints[i].GetY();
   }
   double mu = teller / noemer;

   // estimate second moment, the variance
   double sigma = 0.0;
   for (int i = 0; i < length; i++)
   {
      double tmpValue = fabs( inPoints[i].GetX() - mu );
      sigma += tmpValue * tmpValue * inPoints[i].GetY();
   }
   sigma = sqrt(sigma);

   ppp.first = mu;
   ppp.second = sigma;
   return ppp;
}

//-----------------------------------------------------------------------------

}
}

#endif // STATISTICS_H
