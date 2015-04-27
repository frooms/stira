#include "CurveSet.h"

namespace stira {
namespace common {

CurveSet::CurveSet( std::vector< Curve > curveSet, int ID )
{
   mvCurveSet = curveSet;  // Copy vector content; see http://www.cplusplus.com/reference/stl/vector/operator=/
   mID = ID;
}

//---------------------------------------------------------------

int CurveSet::GetCurveSetID( )
{
   return mID;
}

//---------------------------------------------------------------

std::vector< Curve > CurveSet::GetCurveVector()
{
   return mvCurveSet;
}

//---------------------------------------------------------------

int CurveSet::GetNumberOfCurves( )
{
   return ((int)(mvCurveSet.size()));
}

//---------------------------------------------------------------

Curve CurveSet::GetTopCurve( int minimumLength )
{
   double averageY = 450.0;
   int mySize = this->GetNumberOfCurves();
   Curve candidateCurve = this->mvCurveSet[mySize-1];
   for(int i = 0; i < mySize; i++)
   {
      if ( ( this->mvCurveSet[i].GetAverageY() < averageY ) && ( this->mvCurveSet[i].GetLength() > minimumLength ) && ( this->mvCurveSet[i].GetAverageY() > 3 ) )
      {
         candidateCurve = this->mvCurveSet[i];
         averageY = this->mvCurveSet[i].GetAverageY();
      }
   }
   return candidateCurve;
}

//---------------------------------------------------------------

}
}
