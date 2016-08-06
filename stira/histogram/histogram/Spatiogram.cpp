
/***********************************************************************************
 *   Copyright (C) 2011 by Filip Rooms                                             *
 *                                                                                 *
 *  Terms and conditions for using this software in any form are provided in the   *
 *  file COPYING, which can be found in the root directory of this project.        *
 *                                                                                 *
 *   Contact data: filip.rooms@gmail.com                                           *
 *                 http://www.filiprooms.be/                                       *
 *                                                                                 *
 ***********************************************************************************/
#include "../../common/common/Statistics.h"
#include "../../imagedata/simpletools/GridStatistics.h"
#include "Spatiogram.h"
#include <iostream>
#include <iomanip>
using namespace std;

namespace stira {
namespace histogram {

using namespace image;
using namespace common;

//--------------------------------------------------------------------------------------

Spatiogram::Spatiogram( image::ArrayGrid<double>* pGrid, int binSize, image::ArrayGrid<bool>* pMaskGrid)
{
   double mMin, mMax;
   GridStatistics<double>::GetMinMax( pGrid, mMin, mMax );
   mpHistogram = new IntHistogram( binSize, 1, mMin, mMax, 0, 1 );
   int nrBins = mpHistogram->GetNrOfBins();
   for (int i = 0; i < nrBins; i++)
   {
      mPointsPerBin.push_back( std::vector< Point<int> >()); // Add an empty row
   }
   int width  = pGrid->GetWidth();
   int height = pGrid->GetHeight();

   if (pMaskGrid == 0)
   {
      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x++)
         {
            int binNr = (int)(pGrid->GetValue(x, y) / (double)(binSize));
            if ((binNr < nrBins) && (binNr >= 0 ) )
            {
               mpHistogram->AddDataPoint( pGrid->GetValue(x, y) );
               mPointsPerBin[binNr].push_back( Point<int>( x, y ) );
            }
            else
            {
               cerr << "For pixel (" << x << ", " << y << ") with value " << pGrid->GetValue(x, y) << " Invalid bin nr " << binNr << " with nr of bins " << nrBins << endl << flush;
               cerr << "\t mMax = " << mMax << " mMin = " << mMin << " mBinSize = " << binSize << endl << flush;
            }
         }
      }
   }
   else
   {
      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x++)
         {
            if (pMaskGrid->GetValue(x, y) == true)
            {
               int binNr = (int)(pGrid->GetValue(x, y) / (double)(binSize));
               if ((binNr < nrBins) && (binNr >= 0))
               {
                  mpHistogram->AddDataPoint( pGrid->GetValue(x, y) );
                  mPointsPerBin[binNr].push_back( Point<int>( x, y ) );
               }
               else
               {
                  cerr << "For pixel (" << x << ", " << y << ") with value " << pGrid->GetValue(x, y) << " Invalid bin nr " << binNr
                       << " with current nr of bins " << nrBins << endl << flush;
                  cerr << "\t mMax = " << mMax << " mMin = " << mMin << " mBinSize = " << binSize << endl << flush;
               }
            }
         }
      }
   }

   for (int i = 0; i < nrBins; i++)
   {
      ComputeCovariance( i );
   }
}

//--------------------------------------------------------------------------------------

Spatiogram::~Spatiogram( )
{
   delete mpHistogram;
   for (unsigned int i = 0; i < mCovarianceMatrixVector.size(); i++)
   {
      delete mCovarianceMatrixVector[i];
   }
}

//--------------------------------------------------------------------------------------

void Spatiogram::ComputeCovariance( int binNr )
{
   Point<double> averagePoint;
   std::vector< Point<int> > points = mPointsPerBin[binNr];
   ArrayGrid<double>* pCovarianceMatrix = new ArrayGrid<double>(2, 2);
   int vSize = points.size();

   if ( vSize > 0 )
   {
      std::vector<double> xVector;
      std::vector<double> yVector;
      for (int i = 0; i < vSize; i++)
      {
         xVector.push_back(points[i].x);
         yVector.push_back(points[i].y);
      }

      double meanX = Statistics<double>::GetAverage( xVector );
      double meanY = Statistics<double>::GetAverage( yVector );
      averagePoint.x = meanX;
      averagePoint.y = meanY;
      pCovarianceMatrix->SetValue( 0, 0, Statistics<double>::GetVariance( xVector, meanX ) );
      pCovarianceMatrix->SetValue( 1, 1, Statistics<double>::GetVariance( yVector, meanY ) );

      double covarianceXY = 0.0;
      for (int i = 0; i < vSize; i++)
      {
         covarianceXY += ((xVector[i] - meanX) * (yVector[i] - meanY ));
      }
      covarianceXY /= (vSize-1);

      pCovarianceMatrix->SetValue( 1, 0, covarianceXY );
      pCovarianceMatrix->SetValue( 0, 1, covarianceXY );
   }
   else
   {
      averagePoint.x = 0;
      averagePoint.y = 0;
      pCovarianceMatrix->SetValue( 0, 0, 0 );
      pCovarianceMatrix->SetValue( 1, 1, 0 );

      pCovarianceMatrix->SetValue( 1, 0, 0 );
      pCovarianceMatrix->SetValue( 0, 1, 0 );
   }

   mCovarianceMatrixVector.push_back( pCovarianceMatrix );  ///< one covariance matrix per bin
   mAveragPointVector.push_back( averagePoint );  ///< one average point per bin
}

//--------------------------------------------------------------------------------------

int Spatiogram::GetBinValue( int binNr )
{
   return mpHistogram->GetBinValue( 0, binNr );
}

//--------------------------------------------------------------------------------------

common::Point<double> Spatiogram::GetAveragePoint( int binNr )
{
   return mAveragPointVector[ binNr ];
}

//--------------------------------------------------------------------------------------

image::ArrayGrid<double>* Spatiogram::GetCovarianceMatrix( int binNr )
{
   return mCovarianceMatrixVector[ binNr ];
}

//--------------------------------------------------------------------------------------

void Spatiogram::Write( std::string fileName, int threshold )
{
   ofstream ofp;

   ofp.open(const_cast<char*>(fileName.c_str()), ios::out);

   if (!ofp)
   {
      cerr << "Can't open file: " << fileName << endl;
      return;
   }

   int nrBins = mpHistogram->GetNrOfBins();

   for ( int i = 0; i < nrBins; i++ )
   {
      int binValue = mpHistogram->GetBinValue( 0, i );
      if (binValue > threshold)
      {
         ofp << setfill ('0') << std::setw( 3 ) << setprecision(4) << i << "\t"
             << setfill ('0') << std::setw( 3 ) << setprecision(4) << binValue << "\t"
             << setfill ('0') << std::setw( 3 ) << setprecision(4) << mAveragPointVector[ i ].x << "\t"
             << setfill ('0') << std::setw( 3 ) << setprecision(4) << mAveragPointVector[ i ].y << "\t\t\t"


             << setfill ('0') << std::setw( 3 ) << setprecision(4) << mCovarianceMatrixVector[ i ]->GetValue( 0, 0 ) << "\t"
             << setfill ('0') << std::setw( 3 ) << setprecision(4) << mCovarianceMatrixVector[ i ]->GetValue( 0, 1 ) << "\t"
             << setfill ('0') << std::setw( 3 ) << setprecision(4) << mCovarianceMatrixVector[ i ]->GetValue( 1, 0 ) << "\t"
             << setfill ('0') << std::setw( 3 ) << setprecision(4) << mCovarianceMatrixVector[ i ]->GetValue( 1, 1 ) << endl;
      }
   }
   ofp.close();

}

//--------------------------------------------------------------------------------------

}
}
