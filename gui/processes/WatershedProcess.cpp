
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

#include "WatershedProcess.h"
#include "../../stira/imageanalysis/imageanalysis/WatershedMeyer.h"

using namespace std;
using namespace stira::imagedata;
using namespace stira::imagetools;
using namespace stira::imageanalysis;

WatershedProcess::WatershedProcess( Image* pImage ) : Process( pImage )
{
   mProcessName = QString("Watershed Result");
}

//------------------------------------------------------------------

WatershedProcess::~WatershedProcess()
{
}

//------------------------------------------------------------------

int WatershedProcess::GetMaximalMinimumLevel()
{
   return mMaximalMinimumLevel;
}

//------------------------------------------------------------------

void WatershedProcess::SetMaximalMinimumLevel( int maxLevel )
{
   mMaximalMinimumLevel = maxLevel;
}

//------------------------------------------------------------------

int WatershedProcess::GetEqualityPrecision()
{
   return mEqualityPrecision;
}

//------------------------------------------------------------------

bool WatershedProcess::GetUseGradientImage()
{
   return mUseGradientImage;
}

//------------------------------------------------------------------

void WatershedProcess::SetUseGradientImage(bool flag)
{
   mUseGradientImage = flag;
}

//------------------------------------------------------------------

void WatershedProcess::SetEqualityPrecision( int precision )
{
   mEqualityPrecision = precision;
}

//------------------------------------------------------------------

void WatershedProcess::run()
{
   ArrayGrid<int>* pGridIn = NumberGridTools<double>::CreateIntGrid( mpImage->GetBands()[0] );

   // Create the watershed transformation
   WatershedMeyer< int > wm;

   wm.SetMaxMinimaLevel ( this->GetMaximalMinimumLevel() );
   wm.SetEqualityPrecision ( this->GetEqualityPrecision() );

   // Execute the transformation
   wm.Run ( pGridIn, this->GetUseGradientImage() );

   Image* pOutImage = wm.CreateLabelsIntensitiesImage();
   
   std::string outName = mpImage->GetImageName() + std::string("-WatershedMeyer");
   pOutImage->SetImageName(outName);
   AddResult( pOutImage );
   delete pGridIn;
   // ownership of this image is transfered through GetImage() to ImageDataList
}

//--------------------------------------------------------
