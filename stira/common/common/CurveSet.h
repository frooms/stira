
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

#ifndef STIRA_COMMON_CURVESET_H
#define STIRA_COMMON_CURVESET_H

#include <vector>
#include "Curve.h"

using namespace std;

namespace stira {
namespace common {

/** \brief class to manage a set of curves */
class CurveSet
{
public:
   /** \brief constructor
     * \param curveSet input set of curves as an stl vector
     * \param ID identifier of the current curveset */
   CurveSet( std::vector< Curve > curveSet, int ID );

   /** \brief Gets the curve set as an stl vector of curve objects */
   std::vector< Curve > GetCurveVector();

   /** \brief Gets the number of curves in the set */
   int GetNumberOfCurves( );

   /** \brief Gets the number of curves in the set */
   int GetCurveSetID( );

   /** \brief gets the tpo curve in the set
     * \param minimumLength the minimum length of a curve to be taken as valid */
   Curve GetTopCurve( int minimumLength=400 );

private:
   std::vector< Curve > mvCurveSet;   ///< the stl vector containing the curve objects
   int mID;   ///< identifier of the current curveset
};

}
}

#endif // CURVESET_H
