
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

#ifndef STIRA_COMMON_CURVE_H
#define STIRA_COMMON_CURVE_H
#include <vector>
#include <string>
#include "Point.h"
#include "LineSegment.h"

using namespace std;

namespace stira {
namespace common {

struct NeighborPointPair
{
   Point<int> pt1;
   Point<int> pt2;
   int id1;
   int id2;
   double length;
};

/** \brief class that contains a curve.
  * For us, a curve is a list of 8-neighborhood connected pixels in an stl vector */
class Curve
{
public:
   /** \brief empty constructor */
   Curve( );

   /** \brief constructor with initial set of points
     * \param pointsOnCurve stl vector containing all points on the curve
     * \warning does not check if the points are connected to each other; please do this yourself */
   Curve( std::vector< Point<int> > pointsOnCurve );

   void Clear();

   /** \brief gets the average of all the x coordinates of the pixels on the curve */
   double GetAverageX() const;

   /** \brief gets the average of all the y coordinates of the pixels on the curve */
   double GetAverageY() const;

   /** \brief gets the y coordinate of point on the curve for a given x coordinate
     * for now, we assume 1 point on the curve for a given x coordinate
     * if no point with this x coordinate is found, -1 is returned */
   int GetCorrespondingY( int x ) const;

   /** \brief gets the number of the pixels on the curve */
   int GetLength() const;

   /** \brief Gets y coordinate that corresponds to the given x coordinate along the curve
     * If there are more points, the first that is encountered is returned; if no point was found, -1 is returned
     * \param x x coordinate */
   int GetY( int x ) const;

   /** \brief adds a single point at the end of the curve
     * \param point point added at end of curve
     * \warning does not check if the point is connected to the curve; please do this yourself */
   void AddPoint( Point<int> point );

   /** \brief adds a series of points at the end of the curve
     * \warning does not check if the points are connected to each other or to the curve; please do this yourself  */
   void AddPoints( std::vector< Point<int> > points );

   /** \brief gets the stl vector with the points on the curve */
   std::vector< Point<int> > GetPoints();

   /** \brief gets first point in the stl vector with the points on the curve */
   Point<int> GetStartPoint() const;

   /** \brief gets last point in the stl vector with the points on the curve */
   Point<int> GetEndPoint() const;

   /** \brief Gets the points on the curve with minimum and maximum x coordinate
     * \param xMin the minimum x coordinate; if usePoints is false, it will be computed in this method
     * \param xMax the maximum x coordinate; if usePoints is false, it will be computed in this method
     * \param usePoints if true, the xMin and xMax values will be used without checking; if false, the values are determined in this method */
   std::vector< Point<int> > GetExtremePointsX( int& xMin, int& xMax, bool usePoints=false );

   /** \brief Gets the points on the curve with minimum x coordinate
     * \param xMin the minimum x coordinate; if usePoints is false, it will be computed in this method
     * \param usePoints if true, the xMin value will be used without checking; if false, the values are determined in this method */
   std::vector< Point<int> > GetPointsMinimumX( int& xMin, bool usePoints=false );

   /** \brief Gets the points on the curve with maximum x coordinate
     * \param xMax the maximum x coordinate; if usePoints is false, it will be computed in this method
     * \param usePoints if true, the xMax value the points will be used without checking; if false, the values are determined in this method */
   std::vector< Point<int> > GetPointsMaximumX( int& xMax, bool usePoints=false );

   /** \brief gets point with index i in the stl vector with the points on the curve */
   Point<int> GetPoint( int i ) const;

   bool ChangeCoordinatesForPoint( int i, int x, int y );

   /** \brief sorts all points in the stl vector on their x coordinates */
   void SortOnCoordinateX();

   /** \brief sorts all points in the stl vector on their y coordinates */
   void SortOnCoordinateY();

   /** \brief writes points of the curve to standard out
     * \param intervalSize we write only every intervalSize'th point to standard out */
   void WritePointsToStdOut( int intervalSize=10 );

   /** \brief Gets if the curve is already used */
   bool GetIsUsed();

   /** \brief Sets if the curve is already used
     * \param isUsed flag if current curve is used */
   void SetIsUsed( bool isUsed );

   bool GetHadBranches();

   void SetHadBranches( bool hadBranches );

   bool GetDoesCurveSpanFullImage();

   void SetDoesCurveSpanFullImage( bool doesSpan );

   /** \brief given two open curves, we find which of the end points of the two curves are closest
     * This method is used to determine how to connect two curves by their closest end points
     * \param otherCurve the other curve to check the end points from
     * \return a pair of end points, the first from the first curve and the second from the second curve */
   std::pair< Point<int>, Point<int> > GetClosestEndPoints( Curve otherCurve );

   /** \brief creates a new curve that is build from the current curve connected with the curve passed in the argument
     * \param otherCurve the other curve to merge this curve with (returns new merged curve, leaving this curve unaltered) */
   Curve CreateMergedCurve( Curve otherCurve );

   /** \brief connects the curve passed in the argument to the current curve
     * \param otherCurve the other curve to merge this curve with (adds it to this curve, so original curve doen not exist anymore ) */
   void ConnectToCurve( Curve otherCurve );

   /** \brief computes point-to-point absolute distance between the y coordinates of the curve passed in the argument and this curve
     * \param otherCurve the other curve to merge this curve with (adds it to this curve, so original curve doen not exist anymore )
     * \return a pair of doubles, representing first the maximum distance between the curves and second the mean distance between the curves*/
   std::pair<double, double> ComputeVerticalDistanceToCurve( Curve otherCurve );

   /** \brief checks if two given points are neighbors
     * \param inPoint1 first point to be checked
     * \param inPoint2 second point to be checked */
   bool AreNeighbors( Point<int> inPoint1, Point<int> inPoint2 );

   /** \brief smooths a curve in the y direction by averaging y coordinates of points along the curve
     * \param smoothHalfDistance half of the smoothing window*/
   void SmoothCurveY( int smoothHalfDistance );

   /** \brief writes points of current curve to a text file
     * \param fileName name of text file to write the points to */
   bool WritePointsToText( std::string fileName );

private:
   std::vector< Point<int> > mPointsOnCurve; ///< stl vector containing all points on the curve
   bool mIsUsed; ///< flag that keeps track if the curve is already used
   bool mHadBranches; ///< flag that keeps track if the curve had branches before pruning
   bool mDoesCurveSpanFullImage; ///< flag that keeps track if the curve goes from the left to the right side of the image
};

}
}

#endif // CURVE_H
