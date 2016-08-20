
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

#include "NonSeparableFilter.h"
#include "../../imagedata/simpletools/GridExtender.h"

#include <iostream>

namespace stira {
namespace filter {

using namespace imagedata;

using namespace std;

//===========================================================================================

NonSeparableFilter::NonSeparableFilter()
{
}

//===========================================================================================
   
NonSeparableFilter::~NonSeparableFilter()
{}

//===========================================================================================

ArrayGrid<double>* NonSeparableFilter::Run( ArrayGrid<double>* pInput, double *filterKernel, int filterWidth, int filterHeight)
{
   int filterHalfWidth = (int)(filterWidth / 2);
   int filterHalfHeight = (int)(filterHeight / 2);
   
   ArrayGrid<double>* pExtendedInput = GridExtender<double>::MirrorBorder( pInput, filterHalfWidth, filterHalfHeight );
   ArrayGrid<double>* pExtendedOutput = pExtendedInput->Clone();

   int dataWidth  = pExtendedInput->GetWidth();
   int dataHeight = pExtendedInput->GetHeight();
   
   for (int yData = filterHalfHeight; yData < dataHeight - filterHalfHeight; yData++)
   {
      for (int xData = filterHalfWidth; xData < dataWidth - filterHalfWidth; xData++)
      {
         double ttmpValue = 0.0;
         
         for (int yFilter = -filterHalfHeight; yFilter <= filterHalfHeight; yFilter++)
         {
            for (int xFilter = -filterHalfWidth; xFilter <= filterHalfWidth; xFilter++)
            {
               int filterIndex =                 ( xFilter + filterHalfWidth  )
                                 + filterWidth * ( yFilter + filterHalfHeight );
                                 
               ttmpValue += (   pExtendedInput->GetValue( xData+xFilter, yData+yFilter )
                              * filterKernel[ filterIndex ] );
            }
         }
         pExtendedOutput->SetValue(xData, yData, ttmpValue);
      }
   }
   delete pExtendedInput;
   ArrayGrid<double>* pOutput = GridExtender<double>::CropBorder( pExtendedOutput, filterHalfWidth, filterHalfHeight );
   delete pExtendedOutput;
   return pOutput;
}

//===========================================================================================

double* NonSeparableFilter::GetSobelXKernel()
{
   double* pSobelXKernel = new double[9];
   pSobelXKernel[0] = -1.0;    pSobelXKernel[1] = 0.0;    pSobelXKernel[2] = 1.0;
   pSobelXKernel[3] = -2.0;    pSobelXKernel[4] = 0.0;    pSobelXKernel[5] = 2.0;
   pSobelXKernel[6] = -1.0;    pSobelXKernel[7] = 0.0;    pSobelXKernel[8] = 1.0;
   return pSobelXKernel;
}

//===========================================================================================

double* NonSeparableFilter::GetSobelYKernel()
{
   double* pSobelYKernel = new double[9];
   pSobelYKernel[0] =  1.0;    pSobelYKernel[1] =  2.0;    pSobelYKernel[2] =  1.0;
   pSobelYKernel[3] =  0.0;    pSobelYKernel[4] =  0.0;    pSobelYKernel[5] =  0.0;
   pSobelYKernel[6] = -1.0;    pSobelYKernel[7] = -2.0;    pSobelYKernel[8] = -1.0;
   return pSobelYKernel;
}

//===========================================================================================

ArrayGrid<double>* NonSeparableFilter::RunSobelX( ArrayGrid<double>* pInput)
{
   double* pSobelXKernel = NonSeparableFilter::GetSobelXKernel();
   return NonSeparableFilter::Run( pInput, pSobelXKernel, 3, 3 );
   delete []pSobelXKernel;
}

//===========================================================================================

ArrayGrid<double>* NonSeparableFilter::RunSobelY( ArrayGrid<double>* pInput)
{
   double* pSobelYKernel = NonSeparableFilter::GetSobelYKernel();
   return NonSeparableFilter::Run( pInput, pSobelYKernel, 3, 3 );
   delete []pSobelYKernel;
}

//===========================================================================================

Image* NonSeparableFilter::RunSobelX( Image* pInput )
{
   int nrBands = pInput->GetNumberOfBands();
   int width = pInput->GetWidth();
   int height = pInput->GetHeight();
   Image* pOut = new Image( width, height );
   for (int i = 0; i < nrBands; i++)
   {
      ArrayGrid<double>* pGridOut = NonSeparableFilter::RunSobelX( pInput->GetBands()[i] );
      pOut->AddBand( pGridOut );
   }
   return pOut;
}

//===========================================================================================

Image* NonSeparableFilter::RunSobelY( Image* pInput )
{
   int nrBands = pInput->GetNumberOfBands();
   int width = pInput->GetWidth();
   int height = pInput->GetHeight();
   Image* pOut = new Image( width, height );
   for (int i = 0; i < nrBands; i++)
   {
      ArrayGrid<double>* pGridOut = NonSeparableFilter::RunSobelY( pInput->GetBands()[i] );
      pOut->AddBand( pGridOut );
   }
   return pOut;
}

//===========================================================================================

OrientationGrid* NonSeparableFilter::DetermineLocalMagnitudeAndOrientation( ArrayGrid<double>* pGridIn )
{
   ArrayGrid<double>* pSobelXResponse = NonSeparableFilter::RunSobelX( pGridIn );
   ArrayGrid<double>* pSobelYResponse = NonSeparableFilter::RunSobelY( pGridIn );
   
   int width = pGridIn->GetWidth();
   int height = pGridIn->GetHeight();
   OrientationGrid* pOrientationGrid = new OrientationGrid( width, height );
   
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         double xResponse = pSobelXResponse->GetValue(x, y);
         double yResponse = pSobelYResponse->GetValue(x, y);
         
         double tmpMag = sqrt( xResponse * xResponse + yResponse * yResponse );
         double tmpOri = atan2( xResponse, yResponse );
         if (tmpOri < 0.0) {tmpOri += M_PI;}
         
         pOrientationGrid->SetAngle( x, y, tmpOri );
         pOrientationGrid->SetMagnitude( x, y, tmpMag );
      }
   }
   delete pSobelXResponse;
   delete pSobelYResponse;
   return pOrientationGrid;
}

//===========================================================================================

}
}
