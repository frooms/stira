
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

#include <algorithm>
#include <cassert>
#include "Curve.h"
#include "DrawFigures.h"

namespace stira {
namespace common {

bool MyPointSortPredicateX(const Point<int>& d1, const Point<int>& d2)
{
  return d1.GetX() < d2.GetX();
}

//---------------------------------------------------------------------------

bool MyPointSortPredicateY(const Point<int>& d1, const Point<int>& d2)
{
  return d1.GetY() < d2.GetY();
}

//===========================================================================

Curve::Curve( )
{
   mPointsOnCurve.clear();
   mIsUsed = false;
   mHadBranches = false;
   mDoesCurveSpanFullImage = true;
}

//---------------------------------------------------------------------------

Curve::Curve( std::vector< Point<int> > pointsOnCurve )
{
   mPointsOnCurve.clear();
   mPointsOnCurve = pointsOnCurve;
}

//---------------------------------------------------------------------------

void Curve::Clear()
{
   mPointsOnCurve.clear();
   mIsUsed = false;
   mHadBranches = false;
   mDoesCurveSpanFullImage = false;
}

//---------------------------------------------------------------------------

double Curve::GetAverageX() const
{
   double avgX = 0;
   for (unsigned int i = 0; i < mPointsOnCurve.size(); i++)
   {
      avgX += mPointsOnCurve[i].GetX();
   }
   return ( avgX / mPointsOnCurve.size() );
}

//---------------------------------------------------------------------------

double Curve::GetAverageY() const
{
   double avgY = 0;
   for (unsigned int i = 0; i < mPointsOnCurve.size(); i++)
   {
      avgY += mPointsOnCurve[i].GetY();
   }
   return ( avgY / mPointsOnCurve.size() );
}

//---------------------------------------------------------------------------

int Curve::GetCorrespondingY( int x ) const
{
   for (unsigned int i = 0; i < mPointsOnCurve.size(); i++)
   {
      if ( mPointsOnCurve[i].GetX() == x )
      {
         return mPointsOnCurve[i].GetY();
      }
   }
   return -1;
}

//---------------------------------------------------------------------------

std::vector< Point<int> > Curve::GetPointsMinimumX( int& xMin, bool usePoints )
{
   unsigned int myLength = mPointsOnCurve.size();
   if (!usePoints)
   {
      xMin = 100000000;
      for (unsigned int i = 0; i < myLength; i++)
      {
         if ( mPointsOnCurve[i].GetX() < xMin ) { xMin = mPointsOnCurve[i].GetX(); }
      }
   }
   std::vector< Point<int> > minimumXPoints;
   for (unsigned int i = 0; i < myLength; i++)
   {
      if ( mPointsOnCurve[i].GetX() == xMin ) { minimumXPoints.push_back( mPointsOnCurve[i] ); }
   }

   return minimumXPoints;
}

//---------------------------------------------------------------------------

std::vector< Point<int> > Curve::GetPointsMaximumX( int& xMax, bool usePoints )
{
   unsigned int myLength = mPointsOnCurve.size();
   if (!usePoints)
   {
      xMax = -100000000;
      for (unsigned int i = 0; i < myLength; i++)
      {
         if ( mPointsOnCurve[i].GetX() > xMax ) { xMax = mPointsOnCurve[i].GetX(); }
      }
   }
   std::vector< Point<int> > maximumXPoints;
   for (unsigned int i = 0; i < myLength; i++)
   {
      if ( mPointsOnCurve[i].GetX() == xMax ) { maximumXPoints.push_back( mPointsOnCurve[i] ); }
   }
   return maximumXPoints;
}

//---------------------------------------------------------------------------

std::vector< Point<int> > Curve::GetExtremePointsX( int& xMin, int& xMax, bool usePoints )
{
   std::vector< Point<int> > minVector = GetPointsMinimumX( xMin, usePoints );
   std::vector< Point<int> > maxVector = GetPointsMaximumX( xMax, usePoints );

   minVector.insert( minVector.end(), maxVector.begin(), maxVector.end() );

   return minVector;
}

//---------------------------------------------------------------------------

int Curve::GetLength() const
{
   return mPointsOnCurve.size();
}

//---------------------------------------------------------------------------

int Curve::GetY( int x ) const
{
   unsigned int myLength = mPointsOnCurve.size();
   for (unsigned int i = 0; i < myLength; i++)
   {
      if (mPointsOnCurve[i].GetX() == x) {return mPointsOnCurve[i].GetY();}
   }
   return -1;
}

//---------------------------------------------------------------------------

void Curve::AddPoint( Point<int> point )
{
   int length = mPointsOnCurve.size();
   if ( length > 0 ) // if there are already points on the curve, check if the point is already part of the curve
   {
      bool isInCurve = false;
      for (int i = 0; i < length; i++)
      {
         if (mPointsOnCurve[i] == point)
         {
            isInCurve = true;
         }
      }

      if ( !isInCurve )  // avoid adding a point that is already on the curve
      {
         mPointsOnCurve.push_back( point );
      }
   }
   else  // no points in curve yet, so point can be added
   {
      mPointsOnCurve.push_back( point );
   }
}

//---------------------------------------------------------------------------

void Curve::AddPoints( std::vector< Point<int> > points )
{
   for (unsigned int i = 0; i < points.size(); i++)
   {
      AddPoint( points[i] );
   }
}

//---------------------------------------------------------------------------

std::vector< Point<int> > Curve::GetPoints()
{
   return mPointsOnCurve;
}

//---------------------------------------------------------------------------

Point<int> Curve::GetStartPoint() const
{
   if ( mPointsOnCurve.size() > 0 )
   {
      return mPointsOnCurve[0];
   }
   else
   {
      return Point<int>( -1, -1 );
   }
}

//---------------------------------------------------------------------------

Point<int> Curve::GetEndPoint() const
{
   int myLength = mPointsOnCurve.size();
   if ( myLength > 0 )
   {
      return mPointsOnCurve[ myLength - 1 ];
   }
   else
   {
      return Point<int>( -1, -1 );
   }
}

//---------------------------------------------------------------------------

Point<int> Curve::GetPoint( int i ) const
{
   int myLength = mPointsOnCurve.size();
   if ( ( i >= 0) && ( i < myLength ) )
   {
      return mPointsOnCurve[ i ];
   }
   else
   {
      return Point<int>( -1, -1 );
   }
}

//---------------------------------------------------------------------------

bool Curve::ChangeCoordinatesForPoint( int i, int x, int y )
{
   mPointsOnCurve[i].SetXAndY( x, y );
   return true;
}

//---------------------------------------------------------------------------

void Curve::SortOnCoordinateX()
{
   std::sort( mPointsOnCurve.begin(), mPointsOnCurve.end(), MyPointSortPredicateX );
}

//---------------------------------------------------------------------------

void Curve::SortOnCoordinateY()
{
   std::sort( mPointsOnCurve.begin(), mPointsOnCurve.end(), MyPointSortPredicateY );
}

//---------------------------------------------------------------------------

std::pair< Point<int>, Point<int> > Curve::GetClosestEndPoints( Curve otherCurve )
{
   Point<int> thisEndPoint1 = this->GetStartPoint();
   Point<int> thisEndPoint2 = this->GetEndPoint();

   Point<int> otherEndPoint1 = otherCurve.GetStartPoint();
   Point<int> otherEndPoint2 = otherCurve.GetEndPoint();

   double distance1121 = thisEndPoint1.GetDistance( otherEndPoint1 );
   double distance1122 = thisEndPoint1.GetDistance( otherEndPoint2 );
   double distance1221 = thisEndPoint2.GetDistance( otherEndPoint1 );
   double distance1222 = thisEndPoint2.GetDistance( otherEndPoint2 );

   std::pair< Point<int>, Point<int> > pointCouple;
   if ( ( distance1121 <= distance1122 ) && ( distance1121 <= distance1221 ) && ( distance1121 <= distance1222 ) )
   {
      pointCouple.first = thisEndPoint1;
      pointCouple.second = otherEndPoint1;

      pointCouple.first.SetType( TYPE_START );
      pointCouple.second.SetType( TYPE_START );
   }

   if ( ( distance1122 <= distance1121 ) && ( distance1122 <= distance1221 ) && ( distance1122 <= distance1222 ) )
   {
      pointCouple.first = thisEndPoint1;
      pointCouple.second = otherEndPoint2;

      pointCouple.first.SetType( TYPE_START );
      pointCouple.second.SetType( TYPE_END );
   }

   if ( ( distance1221 <= distance1122 ) && ( distance1221 <= distance1121 ) && ( distance1221 <= distance1222 ) )
   {
      pointCouple.first = thisEndPoint2;
      pointCouple.second = otherEndPoint1;
      pointCouple.first.SetType( TYPE_END );
      pointCouple.second.SetType( TYPE_START );
   }

   if ( ( distance1222 <= distance1122 ) && ( distance1222 <= distance1221 ) && ( distance1222 <= distance1121 ) )
   {
      pointCouple.first = thisEndPoint2;
      pointCouple.second = otherEndPoint2;
      pointCouple.first.SetType( TYPE_END );
      pointCouple.second.SetType( TYPE_END );
   }

   //cout << "Curve 1 between point " << thisEndPoint1 << " and point " << thisEndPoint2 << "; curve 2 between point " << otherEndPoint1 << " and point " << otherEndPoint2 << endl;
   //cout << "Closest points are " << pointCouple.first << " and " << pointCouple.second << endl << flush;

   return pointCouple;
}

//---------------------------------------------------------------------------

void Curve::WritePointsToStdOut( int intervalSize )
{
   for (unsigned int i = 0; i < mPointsOnCurve.size(); i++)
   {
      if ( i % intervalSize == 0 )
      {
         cout << "\t " << mPointsOnCurve[i] << endl;
      }
   }
   cout << endl;
}

//---------------------------------------------------------------------------

bool Curve::GetIsUsed()
{
   return mIsUsed;
}

//---------------------------------------------------------------------------

void Curve::SetIsUsed( bool isUsed )
{
   mIsUsed = isUsed;
}

//---------------------------------------------------------------------------

bool Curve::GetHadBranches()
{
   return mHadBranches;
}

//---------------------------------------------------------------------------

void Curve::SetHadBranches( bool hadBranches )
{
   mHadBranches = hadBranches;
}

//---------------------------------------------------------------------------

bool Curve::GetDoesCurveSpanFullImage()
{
   return mDoesCurveSpanFullImage;
}

//---------------------------------------------------------------------------

void Curve::SetDoesCurveSpanFullImage( bool doesSpan )
{
   mDoesCurveSpanFullImage = doesSpan;
}

//---------------------------------------------------------------------------

Curve Curve::CreateMergedCurve( Curve otherCurve )
{
   Curve newCurve;

   // copy points from this curve to the new curve
   newCurve.AddPoints( mPointsOnCurve );

   newCurve.ConnectToCurve( otherCurve );

   return newCurve;
}

//---------------------------------------------------------------------------

bool Curve::AreNeighbors( Point<int> inPoint1, Point<int> inPoint2 )
{
   if (    ( abs( inPoint1.GetX() - inPoint2.GetX() ) <= 1 )
        && ( abs( inPoint1.GetY() - inPoint2.GetY() ) <= 1 )
        && ( inPoint1 != inPoint2 )
      )
   {
      return true;
   }
   else
   {
      return false;
   }
}

//---------------------------------------------------------------------------

void Curve::ConnectToCurve( Curve otherCurve )
{
   // determine which two curve end points are closest
   int startX, startY, endX, endY;

   this->SortOnCoordinateX();
   otherCurve.SortOnCoordinateX();

   Point<int> thisEndPoint1 = this->GetStartPoint();
   Point<int> thisEndPoint2 = this->GetEndPoint();

   Point<int> otherEndPoint1 = otherCurve.GetStartPoint();
   Point<int> otherEndPoint2 = otherCurve.GetEndPoint();

   double distance1121 = thisEndPoint1.GetDistance( otherEndPoint1 );
   double distance1122 = thisEndPoint1.GetDistance( otherEndPoint2 );
   double distance1221 = thisEndPoint2.GetDistance( otherEndPoint1 );
   double distance1222 = thisEndPoint2.GetDistance( otherEndPoint2 );

   if ( ( distance1121 <= distance1122 ) && ( distance1121 <= distance1221 ) && ( distance1121 <= distance1222 ) )
   {
      startX = thisEndPoint1.GetX();
      startY = thisEndPoint1.GetY();
      endX   = otherEndPoint1.GetX();
      endY   = otherEndPoint1.GetY();
   }
   else if ( ( distance1122 <= distance1121 ) && ( distance1122 <= distance1221 ) && ( distance1122 <= distance1222 ) )
   {
      startX = thisEndPoint1.GetX();
      startY = thisEndPoint1.GetY();
      endX   = otherEndPoint2.GetX();
      endY   = otherEndPoint2.GetY();
   }
   else if ( ( distance1221 <= distance1122 ) && ( distance1221 <= distance1121 ) && ( distance1221 <= distance1222 ) )
   {
      startX = thisEndPoint2.GetX();
      startY = thisEndPoint2.GetY();
      endX   = otherEndPoint1.GetX();
      endY   = otherEndPoint1.GetY();
   }
   else // if ( ( distance1222 <= distance1122 ) && ( distance1222 <= distance1221 ) && ( distance1222 <= distance1121 ) )
   {
      startX = thisEndPoint2.GetX();
      startY = thisEndPoint2.GetY();
      endX   = otherEndPoint2.GetX();
      endY   = otherEndPoint2.GetY();
   }

   // draw a bresenham line to connect both curves
   std::vector< Point<int> > connectingPoints = DrawFigures::BresenhamDrawLine( startX, startY, endX, endY );

   AddPoints( connectingPoints );

   // copy points from this curve to the new curve
   AddPoints( otherCurve.GetPoints() );
   this->SortOnCoordinateX();
}

//-----------------------------------------------------------

std::pair<double, double> Curve::ComputeVerticalDistanceToCurve( Curve otherCurve )
{
   double totalDistance = 0;
   double maxDistance = -1;
   assert ( this->GetLength() == otherCurve.GetLength() );
   int curveLength = this->GetLength();

   for (int i = 0; i < curveLength; i++)
   {
      double tmpDistance = abs( this->GetPoints()[i].GetY() - otherCurve.GetPoints()[i].GetY() );
      if (tmpDistance > maxDistance)
      {
         maxDistance = tmpDistance;
      }
      totalDistance += tmpDistance;
   }
   std::pair<double, double> maxDistanceMeanDistance;

   maxDistanceMeanDistance.first = maxDistance;
   maxDistanceMeanDistance.second = totalDistance / (double)(curveLength);

   return maxDistanceMeanDistance;
}

//-----------------------------------------------------------

void Curve::SmoothCurveY( int smoothHalfDistance )
{
   this->SortOnCoordinateX();
   int length = this->GetLength();

   double* pPointsY = new double[length];
   for ( int i = 0; i < length; i++ )
   {
      pPointsY[i] = this->mPointsOnCurve[i].GetY();
   }

   double myDenominator = 2.0 * (double)(smoothHalfDistance) + 1.0;
   for ( int i = smoothHalfDistance; i < length - smoothHalfDistance; i++ )
   {
      double tmpValue = 0;
      for (int k = -smoothHalfDistance; k <= smoothHalfDistance; k++)
      {
         tmpValue += pPointsY[i+k];
      }
      tmpValue /= myDenominator;
      this->mPointsOnCurve[i].SetY( tmpValue );
   }
   delete []pPointsY;
}

//-----------------------------------------------------------

bool Curve::WritePointsToText( std::string fileName )
{
   ofstream ofp;

   ofp.open(const_cast<char*>(fileName.c_str()), ios::out);

   if (!ofp)
   {
      cerr << "Can't open file: " << fileName.c_str() << endl;
      return false;
   }

   int length = this->mPointsOnCurve.size();
   for (int i = 0; i < length; i++)
   {
      ofp << this->mPointsOnCurve[i].GetX() << "\t" << this->mPointsOnCurve[i].GetY() << endl;
   }

   ofp.close();
   return true;
}

//-----------------------------------------------------------

}
}
