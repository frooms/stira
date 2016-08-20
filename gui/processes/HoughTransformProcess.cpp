
/***********************************************************************************
 *   Copyright (C) 2016 by Filip Rooms                                             *
 *                                                                                 *
 *  Terms and conditions for using this software in any form are provided in the   *
 *  file COPYING, which can be found in the root directory of this project.        *
 *                                                                                 *
 *   Contact data: filip.rooms@gmail.com                                           *
 *                 http://www.filiprooms.be/                                       *
 *                                                                                 *
 ***********************************************************************************/

#include "HoughTransformProcess.h"
#include "../../stira/common/common/LineSegment.h"
#include "../../stira/imagetools/tools/DrawImageTools.h"
#include "../../stira/imageanalysis/imageanalysis/CannyEdgeDetector.h"
#include "../../stira/imageanalysis/imageanalysis/HoughTransform.h"

using namespace std;
using namespace stira::imagetools;
using namespace stira::imagedata;
using namespace stira::imageanalysis;

HoughTransformProcess::HoughTransformProcess( Image* pImage ) : Process( pImage )
{
   mProcessName = QString("Hough Transform Result");
}

//------------------------------------------------------------------

HoughTransformProcess::~HoughTransformProcess()
{
}

int HoughTransformProcess::GetMaximalRadius()
{
    return mMaximalRadius;
}

void HoughTransformProcess::SetMaximalRadius( int maxRadius )
{
    mMaximalRadius = maxRadius;
}

int HoughTransformProcess::GetMinimalRadius()
{
    return mMinimalRadius;
}

void HoughTransformProcess::SetMinimalRadius( int minRadius )
{
    mMinimalRadius = minRadius;
}

bool HoughTransformProcess::GetChooseCircles()
{
    return mChooseCircles;
}

void HoughTransformProcess::SetChooseCircles( bool chooseCircles )
{
    mChooseCircles = chooseCircles;
}

//------------------------------------------------------------------

Image* HoughTransformProcess::RunLines()
{
    Image* pOutImage = mpImage->Clone();
    double sigmaSmooth =  2.0;
    double loThreshold = 30.0;
    double hiThreshold = 80.0;
    ArrayGrid<bool>* pEdgeGrid = CannyEdgeDetector::Run( pOutImage->GetBands()[0], sigmaSmooth, loThreshold, hiThreshold );

    int threshold = 150;
    HoughTransform* pHT = new HoughTransform();
    std::vector< stira::common::LineSegment<int> > lines = pHT->GetLines( pEdgeGrid, threshold );

    int nrLines = lines.size();
    for (int i = 0; i < nrLines; i++)
    {
        DrawImageTools::DrawLine( pOutImage, lines[i].GetPoint1(), lines[i].GetPoint2(), ColorValue(255,0,0,TYPE_RGB));
    }
    delete pEdgeGrid;
    delete pHT;
    return pOutImage;
}

//------------------------------------------------------------------

Image* HoughTransformProcess::RunCircles()
{
    Image* pOutImage = mpImage->Clone();
    double sigmaSmooth =  1.5;
    double loThreshold = 10.0;
    double hiThreshold = 55.0;
    ArrayGrid<bool>* pEdgeGrid = CannyEdgeDetector::Run( pOutImage->GetBands()[0], sigmaSmooth, loThreshold, hiThreshold );

    HoughTransform* pHT = new HoughTransform();
    for (int radius = mMinimalRadius; radius < mMaximalRadius; radius++)
    {
        int threshold = 0.6 * M_PI * radius;
        std::cout << "Inspecting radius " << radius << ", threshold = " << threshold << std::endl;
        std::vector< stira::common::Point<int> > circleCenters = pHT->GetCirclesRadius( pEdgeGrid, radius, threshold );

        int nrCircles = circleCenters.size();
        for (int i = 0; i < nrCircles; i++)
        {
            DrawImageTools::DrawCircle(pOutImage, circleCenters[i], radius, ColorValue(255,0,0,TYPE_RGB));

            std::cout << "\t -> " << nrCircles << " circles found" << std::endl;
        }
    }

    delete pEdgeGrid;
    delete pHT;
    return pOutImage;
}

//------------------------------------------------------------------

void HoughTransformProcess::run()
{
   Image* pOutImage = 0;
   std::string outName;

   if( mChooseCircles )
   {
       pOutImage = RunCircles();
       outName = mpImage->GetImageName() + std::string("-HoughCircles");
   }
   else
   {
       pOutImage = RunLines();
       outName = mpImage->GetImageName() + std::string("-HoughLines");
   }

   pOutImage->SetImageName(outName);
   AddResult( pOutImage );
   // ownership of this image is transfered through GetImage() to ImageDataList
}

//--------------------------------------------------------
