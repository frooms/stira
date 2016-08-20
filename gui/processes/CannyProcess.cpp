
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

#include "CannyProcess.h"
#include "../../stira/imageanalysis/imageanalysis/CannyEdgeDetector.h"

using namespace stira::imageanalysis;

CannyProcess::CannyProcess( Image* pImage ) : Process( pImage )
{
   mProcessName = QString("Canny Edge Detection Result");
}

//--------------------------------------------------------

CannyProcess::~CannyProcess()
{
}

//--------------------------------------------------------

double CannyProcess::GetUpperThreshold()
{
   return mUpperThreshold;
}

//--------------------------------------------------------

void CannyProcess::SetUpperThreshold( double upperThreshold )
{
   mUpperThreshold = upperThreshold;
}

//--------------------------------------------------------

double CannyProcess::GetLowerThreshold()
{
   return mLowerThreshold;
}

//--------------------------------------------------------
void CannyProcess::SetLowerThreshold( double lowerThreshold )
{
   mLowerThreshold = lowerThreshold;
}

//--------------------------------------------------------;

double CannyProcess::GetSigmaSmoothing()
{
   return mSigmaSmoothing;
}

//--------------------------------------------------------;
void CannyProcess::SetSigmaSmoothing( double sigma )
{
   mSigmaSmoothing = sigma;
}

//--------------------------------------------------------

void CannyProcess::run()
{
   ArrayGrid<bool>* pEdgeGrid = CannyEdgeDetector::Run( mpImage->GetBands() [0], mSigmaSmoothing, mLowerThreshold, mUpperThreshold );

   Image* pOutImage = new Image ( pEdgeGrid );  // does NOT take ownership of pEdgeGrid!!
   std::string outName = mpImage->GetImageName() + std::string("-CannyEdge");
   pOutImage->SetImageName(outName);
   
   AddResult( pOutImage );
   // ownership of this image is transfered through GetImage() to ImageDataList
}

//--------------------------------------------------------
