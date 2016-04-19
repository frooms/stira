
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

#ifndef STIRA_COMMON_POLYGON_H
#define STIRA_COMMON_POLYGON_H
#include <vector>
#include <string>
#include "Point.h"

using namespace std;

namespace stira {
namespace common {

/** \brief class that contains a polygon.
  * For us, a polygon is a list of vertices in an stl vector, where the first point equals the last point */
class Polygon
{
public:
    /** \brief constructor */
    Polygon();

    /** \brief Adds a vertex to the polygon (inserted at the end)
      * \param newVertex vertex to be added to the polygon at the end of list of vertices */
    void AddVertex( Point<double> newVertex );

    /** \brief Gets the number of vertices in the polygon */
    unsigned int GetNumberOfVertices( );

    /** \brief Gets the vertex with given index with coordinates as doubles
      * \param nr index of vertex to get */
    Point<double> GetVertex( int nr );

    /** \brief Gets the vertex with given index with coordinates rounded to integers
      * \param nr index of vertex to get */
    Point<int> GetVertexInt( int nr );

    /** \brief Changes the coordinates of the given vertex
      * \param testPoint point to be tested if it is inside the polygon */
    void ChangeVertex( int nr, double x, double y );

    /** \brief Checks if a point is inside a polygon
      * Source http://www.ecse.rpi.edu/Homepages/wrf/Research/Short_Notes/pnpoly.html
      * \param testPoint point to be tested if it is inside the polygon */
    bool IsPointInPolygon( Point<int> testPoint );

    /** \brief Computes area of a polygon
      * Source   http://www.mathopenref.com/coordpolygonarea2.html */
    double GetPolygonArea( );

private:
    std::vector< Point<double> > mvVertices;  ///< list of vertices of the polygon
};

}
}
#endif // POLYGON_H
