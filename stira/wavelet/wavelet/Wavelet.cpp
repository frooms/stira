
/***********************************************************************************
 *   Copyright (C) 2008 by Filip Rooms                                             *
 *                                                                                 *
 *  Terms and conditions for using this software in any form are provided in the   *
 *  file COPYING, which can be found in the root directory of this project.        *
 *                                                                                 *
 *   Contact data: filip.rooms@gmail.com                                           *
 *                 http://www.filiprooms.be/                                       *
 *                                                                                 *
 ***********************************************************************************/
 
#include "Wavelet.h"
#include "../../filter/filter/SeparableFilter.h"

namespace stira {
namespace wavelet {

using namespace std;
using namespace filter;
using namespace imagedata;
using namespace imagetools;

Wavelet::Wavelet()
{
   mpDecomposeReconstructGrid = 0;
   mNrOrientations = 0;
   mNrScales = 0;
   mpPyramid = 0;
}

//------------------------------------------------------------------------------------------

Wavelet::~Wavelet()
{
   delete mpPyramid;
   delete mpDecomposeReconstructGrid;
}

//------------------------------------------------------------------------------------------

void Wavelet::Initialize( ArrayGrid<double>* pSourceGrid, int nrScales, int nrOrientations, bool createBands, bool isSubsampled, bool isFinestScaleSubsampled )
{
   mNrOrientations = nrOrientations;
   mNrScales = nrScales;
   bool needsResidualScale = false;
   mpPyramid = new Pyramid<double>( pSourceGrid, mNrScales, mNrOrientations, isSubsampled, needsResidualScale, isFinestScaleSubsampled );
   if (createBands)
   {
      mpPyramid->CreateBands( pSourceGrid->GetWidth(),pSourceGrid->GetHeight(), isSubsampled, isFinestScaleSubsampled );
   }
}

//------------------------------------------------------------------------------------------

Pyramid<double>* Wavelet::GetPyramid()
{
   return mpPyramid;
}

//------------------------------------------------------------------------------------------

ArrayGrid<double>* Wavelet::GetCopyOfReconstructedGrid()
{
   return mpDecomposeReconstructGrid->Clone();
}

//------------------------------------------------------------------------------------------

int Wavelet::GetNumberOfOrientations()
{
   return mNrOrientations;
}

//------------------------------------------------------------------------------------------

int Wavelet::GetNumberOfScales()
{
   return mNrScales;
}

//------------------------------------------------------------------------------------------

}
}
