#ifndef GRIDSTATISTICS_H
#define GRIDSTATISTICS_H

#include "../../common/common/RectangularROI.h"
#include "../../common/common/MathUtils.h"
#include "../datastructures/ArrayGrid.h"

namespace stira {
namespace imagedata {

template <class T>
class GridStatistics
{

public:
    GridStatistics();

    static void RescaleGrid( ArrayGrid<T>* pGrid, T desiredMin, T desiredMax );

    static void DiagnoseReal( ArrayGrid<double>* pGrid, std::string fileName );

    static bool CountNANandINF( ArrayGrid<T>* pGrid, int& nrNAN, int& nrINF, std::string ID );

    static bool CleanNANandINF( ArrayGrid<T>* pGrid );

    static int CountZero( ArrayGrid<T>* pGrid );

    ///////////////////////////////////////////////
    //                                           //
    // 2. GLOBAL GRID STATISTICS AND PROJECTIONS //
    //                                           //
    ///////////////////////////////////////////////

       /** \brief gets values of minimum and maximum of the grid
         * \param pGrid in: grid to investigate
         * \param mmin out: minimum value of the grid
         * \param mmax out: maximum value of the grid*/
       static void GetMinMax( ArrayGrid<T>* pGrid, double& mmin, double& mmax);

       /** \brief gets values and positions of minimum and maximum of the grid
         * \param pGrid in: grid to investigate
         * \param mmin out: minimum value of the grid
         * \param mmax out: maximum value of the grid
         * \param xMin out: x-coordinate of minimum value of the grid
         * \param yMin out: y-coordinate of minimum value of the grid
         * \param xMax out: x-coordinate of maximum value of the grid
         * \param yMax out: y-coordinate of maximum value of the grid*/
       static void GetMinMax( ArrayGrid<T>* pGrid, double& mmin, double& mmax, int& xMin, int& yMin, int& xMax, int& yMax);

       /** \brief gets value and position of minimum of the grid
         * \param pGrid in: grid to investigate
         * \param mmin out: minimum value of the grid
         * \param xMin out: x-coordinate of minimum value of the grid
         * \param yMin out: y-coordinate of minimum value of the grid*/
       static void GetMin( ArrayGrid<T>* pGrid, double& mmin, int& xMin, int& yMin);

       /** \brief gets value and position of maximum of the grid
         * \param pGrid in: grid to investigate
         * \param mmax out: maximum value of the grid
         * \param xMax out: x-coordinate of maximum value of the grid
         * \param yMax out: y-coordinate of maximum value of the grid*/
       static void GetMax( ArrayGrid<T>* pGrid, double& mmax, int& xMax, int& yMax);

       /** \brief gets maximum in absolute value of the grid
         * \param pGrid in: grid to investigate*/
       static double GetAbsMax( ArrayGrid<T>* pGrid );

       /** \brief computes sum of all values in this grid
         * \param pGrid in: grid to investigate*/
       static T GetGridIntegral( ArrayGrid<T>* pGrid );

       /** \brief Gets the L2 norm of all values in the grid */
       static double GetSquaredNorm( ArrayGrid<double>* pGrid );

       /** \brief Gets the L2 norm of all values in the grid */
       static double GetSquaredNorm( ArrayGrid< std::complex<double> >* pGrid );

       /** \brief computes mean of all values in this grid
         * \param pGrid in: grid to investigate*/
       static T GetGridMean( ArrayGrid<T>* pGrid );

       /** \brief computes variance of all values in this grid
         * \param mean mean of the grid; must already have been computed*/
       static T GetGridVariance( ArrayGrid<T>* pGrid, T mean);

       /** \brief computes kurtosis of all values in this grid
         * \param pGrid in: grid to investigate
         * Formula from
         *   http://en.wikipedia.org/wiki/Kurtosis#Sample_kurtosis
         * section "Sample kurtosis"
         * \param mean mean of the grid; must already have been computed*/
       static T GetGridKurtosis( ArrayGrid<T>* pGrid );

       /** \brief computes kurtosis of all values in this grid
         * Formula from
         *   http://en.wikipedia.org/wiki/Kurtosis#Sample_kurtosis
         * section "Sample kurtosis"
         * \param mean mean of the grid; must already have been computed*/
       static T GetGridKurtosis( ArrayGrid<T>* pGrid, T gridMean, T gridvariance );
       //////////////////////////////////////
       //                                  //
       // 3. LOCAL WINDOW GRID STATISTICS  //
       //                                  //
       //////////////////////////////////////

          /** \brief gets local minimum in a local window with given size
            * WARNING: does not perform boundary checking: moves from (x-(localWindowSize/2)) to (x+(localWindowSize/2))
            *            and from (y-(localWindowSize/2)) to (y+(localWindowSize/2)) without checking if values go out of range!!
            * \param pGrid grid on which to compute
            * \param x x coordinate of central pixel of local window
            * \param y y coordinate of central pixel of local window
            * \param localWindowWidth width of local window
            * \param localWindowHeight height of local window */
          static T GetLocalMinimum( ArrayGrid<T>* pGrid, int x, int y, int localWindowWidth, int localWindowHeight );

          /** \brief gets local maximum in a local window with given size
            * WARNING: does not perform boundary checking: moves from (x-(localWindowSize/2)) to (x+(localWindowSize/2))
            *            and from (y-(localWindowSize/2)) to (y+(localWindowSize/2)) without checking if values go out of range!!
            * \param pGrid grid on which to compute
            * \param x x coordinate of central pixel of local window
            * \param y y coordinate of central pixel of local window
            * \param localWindowWidth width of local window
            * \param localWindowHeight height of local window*/
          static T GetLocalMaximum( ArrayGrid<T>* pGrid, int x, int y, int localWindowWidth, int localWindowHeight );

          /** \brief gets local maximum in absolute value in a local window with given size
            * overloaded version for grid of integers
            * WARNING: does not perform boundary checking: moves from (x-(localWindowSize/2)) to (x+(localWindowSize/2))
            *            and from (y-(localWindowSize/2)) to (y+(localWindowSize/2)) without checking if values go out of range!!
            * \param pGrid grid on which to compute
            * \param x x coordinate of central pixel of local window
            * \param y y coordinate of central pixel of local window
            * \param localWindowWidth width of local window
            * \param localWindowHeight height of local window */
          static T GetLocalAbsMaximum( ArrayGrid<int>* pGrid, int x, int y, int localWindowWidth, int localWindowHeight );

          /** \brief gets local maximum in absolute value in a local window with given size
            * overloaded version for grid of floats
            * WARNING: does not perform boundary checking: moves from (x-(localWindowSize/2)) to (x+(localWindowSize/2))
            *            and from (y-(localWindowSize/2)) to (y+(localWindowSize/2)) without checking if values go out of range!!
            * \param pGrid grid on which to compute
            * \param x x coordinate of central pixel of local window
            * \param y y coordinate of central pixel of local window
            * \param localWindowWidth width of local window
            * \param localWindowHeight height of local window */
          static T GetLocalAbsMaximum( ArrayGrid<float>* pGrid, int x, int y, int localWindowWidth, int localWindowHeight );

          /** \brief gets local maximum in absolute value in a local window with given size
            * overloaded version for grid of doubles
            * WARNING: does not perform boundary checking: moves from (x-(localWindowSize/2)) to (x+(localWindowSize/2))
            *            and from (y-(localWindowSize/2)) to (y+(localWindowSize/2)) without checking if values go out of range!!
            * \param pGrid grid on which to compute
            * \param x x coordinate of central pixel of local window
            * \param y y coordinate of central pixel of local window
            * \param localWindowWidth width of local window
            * \param localWindowHeight height of local window */
          static T GetLocalAbsMaximum( ArrayGrid<double>* pGrid, int x, int y, int localWindowWidth, int localWindowHeight );

          /** \brief gets local mean of values in a local window defined by (xTopLeft, yTopLeft) as top left corner and (xBottomRight, yBottomRight) as bottom right corner (included!)
            *
            * does boundary checking: adjusts values of xTopLeft, xBottomRight, yTopLeft, yBottomRight to be clipped to fit inside the grid!!
            * \param pGrid grid on which to compute
            * \param xTopLeft x coordinate of top left corner of local window
            * \param yTopLeft y coordinate of top left corner of local window
            * \param xBottomRight x coordinate of bottom right corner of local window
            * \param yBottomRight y coordinate of bottom right corner of local window */
          static T ComputeLocalMean( ArrayGrid<T>* pGrid, int& xTopLeft, int& yTopLeft, int& xBottomRight, int& yBottomRight );

          /** \brief gets local mean of values in a local window defined by a RectangularROI
            *
            * does boundary checking: adjusts values of xTopLeft, xBottomRight, yTopLeft, yBottomRight to be clipped to fit inside the grid!!
            * \param pGrid grid on which to compute
            * \param xTopLeft x coordinate of top left corner of local window
            * \param yTopLeft y coordinate of top left corner of local window
            * \param xBottomRight x coordinate of bottom right corner of local window
            * \param yBottomRight y coordinate of bottom right corner of local window */
          static double ComputeLocalMean( ArrayGrid<double>* pGrid, common::RectangularROI<int> rroi );

          /** \brief gets local variance of values in a local window defined by a RectangularROI
            *
            * \param pGrid grid on which to compute
            * \param rroi the rectangular ROI in which to compute the variance
            * \param thisMean the already computed mean of the values in the ROI */
          static double ComputeLocalVariance( ArrayGrid<double>* pGrid, common::RectangularROI<int> rroi, double thisMean);

          /** \brief gets local mean of ABSOLUTE values in a local window defined by (xTopLeft, yTopLeft) as top left corner and (xBottomRight, yBottomRight) as bottom right corner (included!)
            *
            * does boundary checking: adjusts values of xTopLeft, xBottomRight, yTopLeft, yBottomRight to be clipped to fit inside the grid!!
            * \param pGrid grid on which to compute
            * \param xTopLeft x coordinate of top left corner of local window
            * \param yTopLeft y coordinate of top left corner of local window
            * \param xBottomRight x coordinate of bottom right corner of local window
            * \param yBottomRight y coordinate of bottom right corner of local window */
          static T ComputeLocalAbsoluteMean( ArrayGrid<T>* pGrid, int& xTopLeft, int& yTopLeft, int& xBottomRight, int& yBottomRight );

          /** \brief computes the variance of the values a local window size defined by (xTopLeft, yTopLeft) as top left corner and
            *        (xBottomRight, yBottomRight) as bottom right corner (included!)
            *
            * does boundary checking: adjusts values of xTopLeft, xBottomRight, yTopLeft, yBottomRight to be clipped to fit inside the grid!!
            *
            * WARNING: mean value of local window must already be computed before executing this method
            *
            * \param pGrid source grid
            * \param xTopLeft x coordinate of top left corner of local window
            * \param yTopLeft y coordinate of top left corner of local window
            * \param xBottomRight x coordinate of bottom right corner of local window
            * \param yBottomRight y coordinate of bottom right corner of local window
            * \param thisMean the mean value of the values in the local window*/
          static double ComputeLocalVariance( ArrayGrid<double>* pGrid, int& xTopLeft, int& yTopLeft, int& xBottomRight, int& yBottomRight, double thisMean);

          /** \brief computes the variance of the values a local window size defined by (xTopLeft, yTopLeft) as top left corner and
            *        (xBottomRight, yBottomRight) as bottom right corner (included!)
            *
            * does boundary checking: adjusts values of xTopLeft, xBottomRight, yTopLeft, yBottomRight to be clipped to fit inside the grid!!
            *
            * \param pGrid source grid
            * \param xTopLeft x coordinate of top left corner of local window
            * \param yTopLeft y coordinate of top left corner of local window
            * \param xBottomRight x coordinate of bottom right corner of local window
            * \param yBottomRight y coordinate of bottom right corner of local window */
          static double ComputeLocalVariance( ArrayGrid<double>* pGrid, int& xTopLeft, int& yTopLeft, int& xBottomRight, int& yBottomRight );

          /** \brief computes the covariance between values in local windows of two given real-valued grids
            *
            * \param pGrid1 first source grid
            * \param pGrid2 second source grid
            * \param xTopLeft x coordinate of left top corner of local window
            * \param yTopLeft y coordinate of left top corner of local window
            * \param xBottomRight x coordinate of bottom right corner of local window
            * \param yBottomRight y coordinate of bottom right corner of local window
            * \param mean1 mean value of pGrid1,
            * \param mean2 mean value of pGrid2 */
          static double ComputeLocalCovariance( ArrayGrid<double>* pGrid1, ArrayGrid<double>* pGrid2, int& xTopLeft, int& yTopLeft, int& xBottomRight, int& yBottomRight, double mean1, double mean2 );

          /** \brief computes the kurtosis of values in local window of given real-valued grid
            *
            * \param pGrid source grid
            * \param xTopLeft x coordinate of left top corner of local window
            * \param yTopLeft y coordinate of left top corner of local window
            * \param xBottomRight x coordinate of bottom right corner of local window
            * \param yBottomRight y coordinate of bottom right corner of local window
            * \param localMean pre-computed mean value of values in local window of pGrid
            * \param localVariance pre-computed variance of values in local window of pGrid */
          static double ComputeLocalKurtosis( ArrayGrid<double>* pGrid, int& xTopLeft, int& yTopLeft, int& xBottomRight, int& yBottomRight, double localMean, double localVariance );

          /** \brief computes the kurtosis of values in local window of given real-valued grid
            *
            * \param pGrid source grid
            * \param xTopLeft x coordinate of left top corner of local window
            * \param yTopLeft y coordinate of left top corner of local window
            * \param xBottomRight x coordinate of bottom right corner of local window
            * \param yBottomRight y coordinate of bottom right corner of local window */
          static double ComputeLocalKurtosis( ArrayGrid<double>* pGrid, int& xTopLeft, int& yTopLeft, int& xBottomRight, int& yBottomRight );

};


////////////////////////////////
//                            //
// 2. GLOBAL GRID STATISTICS  //
//                            //
////////////////////////////////

//----------------------------------------------------------------------------------

template <class T>
void GridStatistics<T>::RescaleGrid( ArrayGrid<T>* pGrid, T desiredMin, T desiredMax )
{
   double currentMin;
   double currentMax;
   GridStatistics<T>::GetMinMax( pGrid, currentMin, currentMax );

   for (int y = 0; y < pGrid->GetHeight(); y++)
   {
      for (int x = 0; x < pGrid->GetWidth(); x ++)
      {
         double normalizedValue = ((double)(pGrid->GetValue(x, y)) - currentMin) / (currentMax - currentMin);
         double rescaledValue = normalizedValue * (desiredMax -desiredMin) + desiredMin;
         pGrid->SetValue(x, y, rescaledValue );
      }
   }
}


template <class T>
void GridStatistics<T>::DiagnoseReal( ArrayGrid<double>* pGrid, std::string fileName )
{
   double tmpMin, tmpMax, meanIntensity, varianceIntensity, kurtosisIntensity;

   GetMinMax( pGrid, tmpMin, tmpMax );

   meanIntensity     = GetGridMean( pGrid );
   varianceIntensity = GetGridVariance( pGrid, meanIntensity );
   kurtosisIntensity = GetGridKurtosis( pGrid, meanIntensity, varianceIntensity );
   std::cout << fileName << " has min = " << tmpMin << " and max = " << tmpMax
             << " meanIntensity = " << meanIntensity
             << " variance = " << varianceIntensity << " and kurtosis = " << kurtosisIntensity
             << std::endl << std::flush;

   int nrNAN = 0;
   int nrINF = 0;
   CountNANandINF( pGrid, nrNAN, nrINF, fileName );
}

//------------------------------------------------------------------------------------------

template <class T>
bool GridStatistics<T>::CountNANandINF( ArrayGrid<T>* pGrid, int& nrNAN, int& nrINF, std::string ID )
{
   nrNAN = 0;
   nrINF = 0;
   int width = pGrid->GetWidth();
   int height = pGrid->GetHeight();

   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x ++)
      {
#if defined (__WIN32__) || defined(_WIN64)
         if ( _isnan( pGrid->GetValue( x, y ) ) ) {nrNAN++;}
#else
         if (  isnan( pGrid->GetValue( x, y ) ) ) {nrNAN++;}
#endif
         if (  isinf( pGrid->GetValue( x, y ) ) ) {nrINF++;}
      }
   }
   std::cout << ID << " nrNAN = " << nrNAN << " and nrINF = " << nrINF << std::endl << std::flush;
   return true;
}



//------------------------------------------------------------------------------------------

template <class T>
bool GridStatistics<T>::CleanNANandINF( ArrayGrid<T>* pGrid )
{
   int width = pGrid->GetWidth();
   int height = pGrid->GetHeight();

   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x ++)
      {
#if defined (__WIN32__) || defined(_WIN64)
         if ( _isnan( pGrid->GetValue(x, y) ) ) { pGrid->SetValue(x, y, 0 ); }
#else
         if ( isnan( pGrid->GetValue(x, y) ) ) { pGrid->SetValue(x, y, 0 ); }
#endif
         if (isinf( pGrid->GetValue(x, y) ) ) { pGrid->SetValue(x, y, 255);}
      }
   }
   return true;
}

//------------------------------------------------------------------------------------------

template <class T>
int GridStatistics<T>::CountZero( ArrayGrid<T>* pGrid )
{
   int nrZero = 0;
   int width = pGrid->GetWidth();
   int height = pGrid->GetHeight();

   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x ++)
      {
         if ( pGrid->GetValue(x, y) == 0 ) {nrZero++;}
      }
   }
   std::cout << " nrZero = " << nrZero << std::endl << std::flush;
   return nrZero;
}

//------------------------------------------------------------------------------------------

template <class T>
void GridStatistics<T>::GetMinMax( ArrayGrid<T>* pGrid, double& mmin, double& mmax, int& xMin, int& yMin, int& xMax, int& yMax )
{
   double tmpMax = -1000000000000.0;
   double tmpMin =  1000000000000.0;

   int width = pGrid->GetWidth();
   int height = pGrid->GetHeight();

   double tmpValue = 0.0;
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x ++)
      {
         tmpValue = static_cast<double>(pGrid->GetValue(x, y));

         if ( tmpValue > tmpMax )
         {
            tmpMax = tmpValue;
            xMax = x;
            yMax = y;
         }
         if ( tmpValue < tmpMin )
         {
            tmpMin = tmpValue;
            xMin = x;
            yMin = y;
         }

         #ifdef CHECK_INF_OR_NAN_VALUES
            if (isinf(tmpValue) )
            {
               std::cout << "Array is inf at (" << x << ", " << y << ")" << std::endl << std::flush;
            }
#if defined (__WIN32__) || defined(_WIN64)
            if ( _isnan( tmpValue ) )
#else
            if (isnan(tmpValue) )
#endif
            {
               std::cout << "Array is nan at (" << x << ", " << y << ")" << std::endl << std::flush;
            }
         #endif
      }
   }
   mmax = tmpMax;
   mmin = tmpMin;
}

//------------------------------------------------------------------------------------------

template <class T>
void GridStatistics<T>::GetMinMax( ArrayGrid<T>* pGrid, double& mmin, double& mmax )
{
   int xMin, yMin, xMax, yMax;
   GetMinMax( pGrid, mmin, mmax, xMin, yMin, xMax, yMax );
}

//------------------------------------------------------------------------------------------

template <class T>
void GridStatistics<T>::GetMin( ArrayGrid<T>* pGrid, double& mmin, int& xMin, int& yMin)
{
   double mmax;
   int xMax, yMax;
   GetMinMax( pGrid, mmin, mmax, xMin, yMin, xMax, yMax );
}

//------------------------------------------------------------------------------------------

template <class T>
void GridStatistics<T>::GetMax( ArrayGrid<T>* pGrid, double& mmax, int& xMax, int& yMax)
{
   double mmin;
   int xMin, yMin;
   GetMinMax( pGrid, mmin, mmax, xMin, yMin, xMax, yMax );
}

//------------------------------------------------------------------------------------------

template <class T>
double GridStatistics<T>::GetAbsMax( ArrayGrid<T>* pGrid )
{
   double mmax = -1.0;

   for (int y = 0; y < pGrid->GetHeight(); y++)
   {
      for (int x = 0; x < pGrid->GetWidth(); x ++)
      {
         double tmpValue = fabs( static_cast<double>( pGrid->GetValue(x, y)) );
         if ( tmpValue > mmax )
         {
            mmax = tmpValue;
         }
      }
   }
   return mmax;
}

//----------------------------------------------------------------------------------

template <class T>
T GridStatistics<T>::GetGridIntegral( ArrayGrid<T>* pGrid )
{
   T totalIntensity = 0.0;
   for (int y = 0; y < pGrid->GetHeight(); y++)
   {
      for (int x = 0; x < pGrid->GetWidth(); x ++)
      {
         totalIntensity += pGrid->GetValue(x, y);
      }
   }
   return totalIntensity;
}

//----------------------------------------------------------------------------------

template <class T>
double GridStatistics<T>::GetSquaredNorm( ArrayGrid<double>* pGrid )
{
   T totalIntensity = 0.0;
   for (int y = 0; y < pGrid->GetHeight(); y++)
   {
      for (int x = 0; x < pGrid->GetWidth(); x ++)
      {
         totalIntensity += ( pGrid->GetValue(x, y) *  pGrid->GetValue(x, y));
      }
   }
   return totalIntensity;
}

//----------------------------------------------------------------------------------

template <class T>
double GridStatistics<T>::GetSquaredNorm( ArrayGrid< std::complex<double> >* pGrid )
{
   double totalIntensity = 0.0;
   for (int y = 0; y < pGrid->GetHeight(); y++)
   {
      for (int x = 0; x < pGrid->GetWidth(); x ++)
      {
         totalIntensity += ( std::norm( pGrid->GetValue(x, y) ) );
      }
   }
   return totalIntensity;
}

//----------------------------------------------------------------------------------

template <class T>
T GridStatistics<T>::GetGridMean( ArrayGrid<T>* pGrid )
{
   T totalIntensity = GetGridIntegral( pGrid );
   double nrPixels = (double)( pGrid->GetHeight() * pGrid->GetWidth());
   return (totalIntensity / nrPixels );
}

//----------------------------------------------------------------------------------

template <class T>
T GridStatistics<T>::GetGridVariance( ArrayGrid<T>* pGrid, T gridMean)
{
   T totalIntensity = 0.0;
   for (int y = 0; y < pGrid->GetHeight(); y++)
   {
      for (int x = 0; x < pGrid->GetWidth(); x ++)
      {
         T ttt = pGrid->GetValue(x, y) - gridMean;
         totalIntensity += (ttt * ttt);
      }
   }
   return (totalIntensity / (pGrid->GetHeight() * pGrid->GetWidth() - 1) );
}

//----------------------------------------------------------------------------------

template <class T>
T GridStatistics<T>::GetGridKurtosis( ArrayGrid<T>* pGrid, T gridMean, T gridVariance )
{
   T totalNumerator = 0.0;

   T nrSamples = (T)( pGrid->GetHeight() * pGrid->GetWidth() );

   for (int y = 0; y < pGrid->GetHeight(); y++)
   {
      for (int x = 0; x < pGrid->GetWidth(); x ++)
      {
         T ttt = pGrid->GetValue(x, y) - gridMean;
         totalNumerator += (ttt * ttt * ttt * ttt);
      }
   }
   totalNumerator /= nrSamples;

   return ( ( totalNumerator / (gridVariance * gridVariance)) - 3.0 );
}

//----------------------------------------------------------------------------------

template <class T>
T GridStatistics<T>::GetGridKurtosis( ArrayGrid<T>* pGrid )
{
   T myMean     = GetGridMean( pGrid );
   T myVariance = GetGridVariance( pGrid, myMean );

   return GetGridKurtosis( pGrid, myMean, myVariance );
}
//////////////////////////////////////
//                                  //
// 3. LOCAL WINDOW GRID STATISTICS  //
//                                  //
//////////////////////////////////////

template <class T>
T GridStatistics<T>::GetLocalMinimum( ArrayGrid<T>* pGrid, int x, int y, int localWindowWidth, int localWindowHeight )
{
   int localWindowHalfWidth = localWindowWidth / 2;
   int localWindowHalfHeight = localWindowHeight / 2;
   T tmpMin = pGrid->GetValue(x, y);

   for (int dy = -localWindowHalfHeight; dy <= localWindowHalfHeight; dy++)
   {
      for (int dx = -localWindowHalfWidth; dx <= localWindowHalfWidth; dx++)
      {
         if ( pGrid->GetValue( x + dx, y + dy ) < tmpMin ) { tmpMin = pGrid->GetValue( x + dx, y + dy ); }
      }
   }
   return tmpMin;
}

//----------------------------------------------------------------------------------

template <class T>
T GridStatistics<T>::GetLocalMaximum( ArrayGrid<T>* pGrid, int x, int y, int localWindowWidth, int localWindowHeight )
{
   int localWindowHalfWidth = localWindowWidth / 2;
   int localWindowHalfHeight = localWindowHeight / 2;
   T tmpMax = pGrid->GetValue(x, y);

   for (int dy = -localWindowHalfHeight; dy <= localWindowHalfHeight; dy++)
   {
      for (int dx = -localWindowHalfWidth; dx <= localWindowHalfWidth; dx++)
      {
         if ( pGrid->GetValue( x + dx, y + dy ) > tmpMax ) { tmpMax = pGrid->GetValue( x + dx, y + dy ); }
      }
   }
   return tmpMax;
}

//----------------------------------------------------------------------------------

template <class T>
T GridStatistics<T>::GetLocalAbsMaximum( ArrayGrid<int>* pGrid, int x, int y, int localWindowWidth, int localWindowHeight )
{
   int localWindowHalfWidth = localWindowWidth / 2;
   int localWindowHalfHeight = localWindowHeight / 2;
   T tmpMax = pGrid->GetValue(x, y);

   for (int dy = -localWindowHalfHeight; dy <= localWindowHalfHeight; dy++)
   {
      for (int dx = -localWindowHalfWidth; dx <= localWindowHalfWidth; dx++)
      {
         if ( abs(pGrid->GetValue( x + dx, y + dy ) ) > tmpMax ) { tmpMax = abs( pGrid->GetValue( x + dx, y + dy ) ); }
      }
   }
   return tmpMax;
}

//----------------------------------------------------------------------------------

template <class T>
T GridStatistics<T>::GetLocalAbsMaximum( ArrayGrid<float>* pGrid, int x, int y, int localWindowWidth, int localWindowHeight )
{
   int localWindowHalfWidth = localWindowWidth / 2;
   int localWindowHalfHeight = localWindowHeight / 2;
   T tmpMax = pGrid->GetValue(x, y);

   for (int dy = -localWindowHalfHeight; dy <= localWindowHalfHeight; dy++)
   {
      for (int dx = -localWindowHalfWidth; dx <= localWindowHalfWidth; dx++)
      {
         if ( fabs(pGrid->GetValue( x + dx, y + dy ) ) > tmpMax ) { tmpMax = fabs( pGrid->GetValue( x + dx, y + dy ) ); }
      }
   }
   return tmpMax;
}

//----------------------------------------------------------------------------------

template <class T>
T GridStatistics<T>::GetLocalAbsMaximum( ArrayGrid<double>* pGrid, int x, int y, int localWindowWidth, int localWindowHeight )
{
   int localWindowHalfWidth = localWindowWidth / 2;
   int localWindowHalfHeight = localWindowHeight / 2;
   T tmpMax = pGrid->GetValue(x, y);

   for (int dy = -localWindowHalfHeight; dy <= localWindowHalfHeight; dy++)
   {
      for (int dx = -localWindowHalfWidth; dx <= localWindowHalfWidth; dx++)
      {
         if ( fabs( pGrid->GetValue( x + dx, y + dy ) ) > tmpMax) { tmpMax = fabs( pGrid->GetValue( x + dx, y + dy ) ); }
      }
   }
   return tmpMax;
}

//----------------------------------------------------------------------------------

template <class T>
T GridStatistics<T>::ComputeLocalMean( ArrayGrid<T>* pGrid, int& xTopLeft, int& yTopLeft, int& xBottomRight, int& yBottomRight )
{
   T tmpMean = 0.0;

   xTopLeft     = common::MathUtils::ClipValue( xTopLeft,     0, pGrid->GetWidth()-1 );
   xBottomRight = common::MathUtils::ClipValue( xBottomRight, 0, pGrid->GetWidth()-1 );
   yTopLeft     = common::MathUtils::ClipValue( yTopLeft,     0, pGrid->GetHeight()-1 );
   yBottomRight = common::MathUtils::ClipValue( yBottomRight, 0, pGrid->GetHeight()-1 );

   for (int yy = yTopLeft; yy <= yBottomRight; yy++)
   {
      for (int xx = xTopLeft; xx <= xBottomRight; xx++)
      {
         tmpMean += pGrid->GetValue( xx, yy );
      }
   }
   return ( tmpMean / (double)( ( xBottomRight - xTopLeft + 1 ) * ( yBottomRight - yTopLeft + 1 ) ) );
}

//----------------------------------------------------------------------------------

template <class T>
double GridStatistics<T>::ComputeLocalMean( ArrayGrid<double>* pGrid, common::RectangularROI<int> rroi )
{
   int xTopLeft = rroi.GetTopLeftCorner().x();
   int yTopLeft = rroi.GetTopLeftCorner().y();
   int xBottomRight = rroi.GetBottomRightCorner().x();
   int yBottomRight = rroi.GetBottomRightCorner().y();
   return ComputeLocalMean( pGrid, xTopLeft, yTopLeft, xBottomRight, yBottomRight );
}

//----------------------------------------------------------------------------------

template <class T>
double GridStatistics<T>::ComputeLocalVariance( ArrayGrid<double>* pGrid, common::RectangularROI<int> rroi, double localMean )
{
   int xTopLeft = rroi.GetTopLeftCorner().x();
   int yTopLeft = rroi.GetTopLeftCorner().y();
   int xBottomRight = rroi.GetBottomRightCorner().x();
   int yBottomRight = rroi.GetBottomRightCorner().y();
   return ComputeLocalVariance( pGrid, xTopLeft, yTopLeft, xBottomRight, yBottomRight, localMean );
}

//----------------------------------------------------------------------------------

template <class T>
T GridStatistics<T>::ComputeLocalAbsoluteMean( ArrayGrid<T>* pGrid, int& xTopLeft, int& yTopLeft, int& xBottomRight, int& yBottomRight )
{
   T tmpMean = 0.0;

   xTopLeft     = common::MathUtils::ClipValue( xTopLeft,     0, pGrid->GetWidth()-1 );
   xBottomRight = common::MathUtils::ClipValue( xBottomRight, 0, pGrid->GetWidth()-1 );
   yTopLeft = common::MathUtils::ClipValue( yTopLeft,     0, pGrid->GetHeight()-1 );
   yBottomRight = common::MathUtils::ClipValue( yBottomRight, 0, pGrid->GetHeight()-1 );

   for (int yy = yTopLeft; yy <= yBottomRight; yy++)
   {
      for (int xx = xTopLeft; xx <= xBottomRight; xx++)
      {
         tmpMean += fabs( pGrid->GetValue( xx, yy ) );
      }
   }
   return ( tmpMean / (double)( ( xBottomRight - xTopLeft + 1 ) * ( yBottomRight - yTopLeft + 1 ) ) );
}

//----------------------------------------------------------------------------------

template <class T>
double GridStatistics<T>::ComputeLocalVariance( ArrayGrid<double>* pGrid, int& xTopLeft, int& yTopLeft, int& xBottomRight, int& yBottomRight, double thisMean)
{
   xTopLeft     = common::MathUtils::ClipValue( xTopLeft,     0, pGrid->GetWidth()-1 );
   xBottomRight = common::MathUtils::ClipValue( xBottomRight, 0, pGrid->GetWidth()-1 );
   yTopLeft     = common::MathUtils::ClipValue( yTopLeft,     0, pGrid->GetHeight()-1 );
   yBottomRight = common::MathUtils::ClipValue( yBottomRight, 0, pGrid->GetHeight()-1 );

   double tmpVariance = 0.0;
   for (int yy = yTopLeft; yy <= yBottomRight; yy++)
   {
      for (int xx = xTopLeft; xx <= xBottomRight; xx++)
      {
         double ttt = pGrid->GetValue( xx, yy ) - thisMean;
         tmpVariance += (ttt * ttt);
      }
   }
   return ( tmpVariance / (double)( ( xBottomRight - xTopLeft + 1 ) * ( yBottomRight - yTopLeft + 1 ) - 1 ) );
}

//----------------------------------------------------------------------------------

template <class T>
double GridStatistics<T>::ComputeLocalVariance( ArrayGrid<double>* pGrid, int& xTopLeft, int& yTopLeft, int& xBottomRight, int& yBottomRight )
{
   xTopLeft     = common::MathUtils::ClipValue( xTopLeft,     0, pGrid->GetWidth()-1 );
   xBottomRight = common::MathUtils::ClipValue( xBottomRight, 0, pGrid->GetWidth()-1 );
   yTopLeft     = common::MathUtils::ClipValue( yTopLeft,     0, pGrid->GetHeight()-1 );
   yBottomRight = common::MathUtils::ClipValue( yBottomRight, 0, pGrid->GetHeight()-1 );

   double tmpMean = 0.0;
   for (int yy = yTopLeft; yy <= yBottomRight; yy++)
   {
      for (int xx = xTopLeft; xx <= xBottomRight; xx++)
      {
         tmpMean += pGrid->GetValue( xx, yy );
      }
   }

   double myDenominator = (double)( ( xBottomRight - xTopLeft + 1 ) * ( yBottomRight - yTopLeft + 1 ) );

   tmpMean /= myDenominator;

   double tmpVariance = 0.0;
   for (int yy = yTopLeft; yy <= yBottomRight; yy++)
   {
      for (int xx = xTopLeft; xx <= xBottomRight; xx++)
      {
         double ttt = pGrid->GetValue( xx, yy ) - tmpMean;
         tmpVariance += (ttt * ttt);
      }
   }
   return ( tmpVariance / (double)( myDenominator - 1 ) );
}

//----------------------------------------------------------------------------------

template <class T>
double GridStatistics<T>::ComputeLocalCovariance( ArrayGrid<double>* pGrid1, ArrayGrid<double>* pGrid2, int& xTopLeft, int& yTopLeft, int& xBottomRight, int& yBottomRight, double grid1Mean, double grid2Mean )
{
   assert( pGrid1->GetWidth() == pGrid2->GetWidth() );
   assert( pGrid1->GetHeight() == pGrid2->GetHeight() );

   xTopLeft     = common::MathUtils::ClipValue( xTopLeft,     0, pGrid1->GetWidth()  - 1 );
   xBottomRight = common::MathUtils::ClipValue( xBottomRight, 0, pGrid1->GetWidth()  - 1 );
   yTopLeft     = common::MathUtils::ClipValue( yTopLeft,     0, pGrid1->GetHeight() - 1 );
   yBottomRight = common::MathUtils::ClipValue( yBottomRight, 0, pGrid1->GetHeight() - 1 );

   int localWindowWidth  = xBottomRight - xTopLeft + 1;
   int localWindowHeight = yBottomRight - yTopLeft + 1;

   double tmpCovariance = 0.0;

   for (int y = yTopLeft; y <= yBottomRight; y++)
   {
      for (int x = xTopLeft; x <= xBottomRight; x++)
      {
         tmpCovariance += ( (pGrid1->GetValue( x, y ) - grid1Mean ) * ( pGrid2->GetValue( x, y ) - grid2Mean ) );
      }
   }
   return (tmpCovariance / (double)( localWindowWidth * localWindowHeight - 1 ) );
}

//----------------------------------------------------------------------------------

template <class T>
double GridStatistics<T>::ComputeLocalKurtosis( ArrayGrid<double>* pGrid, int& xTopLeft, int& yTopLeft, int& xBottomRight, int& yBottomRight, double localMean, double localVariance )
{
   xTopLeft     = common::MathUtils::ClipValue( xTopLeft,     0, pGrid->GetWidth()  - 1 );
   xBottomRight = common::MathUtils::ClipValue( xBottomRight, 0, pGrid->GetWidth()  - 1 );
   yTopLeft     = common::MathUtils::ClipValue( yTopLeft,     0, pGrid->GetHeight() - 1 );
   yBottomRight = common::MathUtils::ClipValue( yBottomRight, 0, pGrid->GetHeight() - 1 );

   T totalNumerator = 0.0;

   T nrSamples = (T)( ( xBottomRight - xTopLeft ) * ( yBottomRight - yTopLeft ) );

   for (int y = yTopLeft; y <= yBottomRight; y++)
   {
      for (int x = xTopLeft; x < xBottomRight; x ++)
      {
         T ttt = pGrid->GetValue(x, y) - localMean;
         totalNumerator += (ttt * ttt * ttt * ttt);
      }
   }
   totalNumerator /= nrSamples;

   return ( ( totalNumerator / (localVariance * localVariance)) - 3.0 );
}

//----------------------------------------------------------------------------------

template <class T>
double GridStatistics<T>::ComputeLocalKurtosis( ArrayGrid<double>* pGrid, int& xTopLeft, int& yTopLeft, int& xBottomRight, int& yBottomRight )
{
   xTopLeft     = common::MathUtils::ClipValue( xTopLeft,     0, pGrid->GetWidth()  - 1 );
   xBottomRight = common::MathUtils::ClipValue( xBottomRight, 0, pGrid->GetWidth()  - 1 );
   yTopLeft     = common::MathUtils::ClipValue( yTopLeft,     0, pGrid->GetHeight() - 1 );
   yBottomRight = common::MathUtils::ClipValue( yBottomRight, 0, pGrid->GetHeight() - 1 );
   double localMean     = ComputeLocalMean(     pGrid, xTopLeft, yTopLeft, xBottomRight, yBottomRight );
   double localVariance = ComputeLocalVariance( pGrid, xTopLeft, yTopLeft, xBottomRight, yBottomRight, localMean );
   double totalNumerator = 0.0;

   double nrSamples = (double)( ( xBottomRight - xTopLeft ) * ( yBottomRight - yTopLeft ) );

   for (int y = yTopLeft; y <= yBottomRight; y++)
   {
      for (int x = xTopLeft; x < xBottomRight; x ++)
      {
         T ttt = pGrid->GetValue(x, y) - localMean;
         totalNumerator += (ttt * ttt * ttt * ttt);
      }
   }
   totalNumerator /= nrSamples;

   return ( ( totalNumerator / (localVariance * localVariance)) - 3.0 );
}

//----------------------------------------------------------------------------------

}
}

#endif // GRIDSTATISTICS_H
