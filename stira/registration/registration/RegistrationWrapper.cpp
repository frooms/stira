
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

#include <iostream>
#include "RegistrationWrapper.h"
#include "regFlt3d.h"
#include "phil.h"

using namespace std;

namespace stira {
namespace registration {

using namespace image;

RegistrationWrapper::RegistrationWrapper( image::ArrayGrid<double>* pMasterGrid, image::ArrayGrid<double>* pSlaveGrid )
{
   if (    ( pMasterGrid->GetWidth() ==  pSlaveGrid->GetWidth() )
        && ( pMasterGrid->GetHeight() ==  pSlaveGrid->GetHeight() )
      )
   {
      int width = pMasterGrid->GetWidth();
      int height = pMasterGrid->GetHeight();
      
      float* pMasterArray = CreateArrayFromGrid( pMasterGrid );
      float* pSlaveArray = CreateArrayFromGrid( pSlaveGrid );
      Initialize2D( width, height, pMasterArray, pSlaveArray );
      mpResultingTransform = new AffineTransform();
      mIsReadyToRun = true;
   }
   else
   {
      mIsReadyToRun = false;
      cerr << "Input images with different widths and/or heights not supported!!" << endl << flush;
   }
}

//===================================================================================================

RegistrationWrapper::~RegistrationWrapper()
{
}

//===================================================================================================

image::ArrayGrid<double>* RegistrationWrapper::CreateGridFromArray( float* pArray, int width, int height )
{
   image::ArrayGrid<double>* pGrid = new image::ArrayGrid<double>(width, height);
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         pGrid->SetValue(x, y, (double)(pArray[x + width * y]));
      }
   }
   return pGrid;
}

//===================================================================================================

float* RegistrationWrapper::CreateArrayFromGrid( image::ArrayGrid<double>* pGridIn )
{
   int width  = pGridIn->GetWidth();
   int height = pGridIn->GetHeight();
   float* pArray = new float[ width * height];
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         pArray[x + width * y] = (float)(pGridIn->GetValue(x, y));
      }
   }
   return pArray;
}

//===================================================================================================

void RegistrationWrapper::Initialize2D( int width, int height, float* pMasterArray, float* pSlaveArray )
{
   mRegistrationParameters.directives.maskCombine = BRAND_AND;
   mRegistrationParameters.directives.referenceMask = blank;
   mRegistrationParameters.directives.testMask = blank;
   mRegistrationParameters.directives.interpolation = three;
   mRegistrationParameters.directives.convergence = Marquardt;

   mRegistrationParameters.directives.clipping = TRUE;
   mRegistrationParameters.directives.importFit = 0;
   mRegistrationParameters.directives.exportFit = TRUE; 
   
   mRegistrationParameters.directives.xTrans = TRUE;
   mRegistrationParameters.directives.yTrans = TRUE;
   mRegistrationParameters.directives.zTrans = FALSE;
   
   mRegistrationParameters.directives.xRot = FALSE;
   mRegistrationParameters.directives.yRot = FALSE;
   mRegistrationParameters.directives.zRot = TRUE; 

   mRegistrationParameters.directives.isoScaling = FALSE; 
   
   mRegistrationParameters.directives.xSkew = FALSE;
   mRegistrationParameters.directives.ySkew = FALSE;
   mRegistrationParameters.directives.zSkew = FALSE;

   mRegistrationParameters.directives.matchGrey = FALSE;

   mRegistrationParameters.directives.greyRendering = FALSE;
   mRegistrationParameters.directives.zapMean = FALSE;

   mRegistrationParameters.directives.zSqueeze = FALSE;
   
   mRegistrationParameters.nx = width;
   mRegistrationParameters.ny = height;
   mRegistrationParameters.nz = 1;

   /* This pointer should hold the test data. The organization of the data is as follows:
    * contiguous memory, raster order, the fastest running index is x, then y, then z.*/
   mRegistrationParameters.inPtr1 = pSlaveArray;//(float *)malloc( mRegistrationParameters.nx * mRegistrationParameters.ny * mRegistrationParameters.nz * sizeof(float));

   /* This pointer should hold the reference data: the template toward which the test data
    * is aligned. Might be modified according to 'zapMean'. */
   mRegistrationParameters.inPtr2 = pMasterArray;//(float *)malloc( mRegistrationParameters.nx * mRegistrationParameters.ny * mRegistrationParameters.nz * sizeof(float));

   /* This pointer should hold the test mask if 'testMask == provided', or a mask workspace
    * else. In this latter case, the created mask will be returned. */
   mRegistrationParameters.inMsk1 = (float *)malloc( mRegistrationParameters.nx * mRegistrationParameters.ny * mRegistrationParameters.nz * sizeof(float));
   mRegistrationParameters.inMsk2 = (float *)malloc( mRegistrationParameters.nx * mRegistrationParameters.ny * mRegistrationParameters.nz * sizeof(float));

   /* This pointer should provide the space for returning the transformed test data. */
   mRegistrationParameters.outPtr = (float *)malloc( mRegistrationParameters.nx * mRegistrationParameters.ny * mRegistrationParameters.nz * sizeof(float));

   /* This pointer should provide the space for returning the transformed test mask. */
   mRegistrationParameters.mskPtr = (float *)malloc( mRegistrationParameters.nx * mRegistrationParameters.ny * mRegistrationParameters.nz * sizeof(float));

   mRegistrationParameters.inFit  = (char*)("import.txt");
   mRegistrationParameters.outFit = (char*)("export.txt");

   /* These variables determine the amount of smoothing along the x, y, and z axis */
   mRegistrationParameters.sx = 3.0;
   mRegistrationParameters.sy = 3.0;
   mRegistrationParameters.sz = 3.0;

   mRegistrationParameters.firstLambda = 1.0;
   mRegistrationParameters.lambdaScale = 4.0;

   mRegistrationParameters.minGain = 0.0;
   mRegistrationParameters.epsilon = 1.192092896E-09;
   mRegistrationParameters.backgrnd = 0.0;
   mRegistrationParameters.levels = 5;
   mRegistrationParameters.lastLevel = 1;
}

//===================================================================================================

bool RegistrationWrapper::Run()
{
   if (mIsReadyToRun == true)
   {
      struct fitRec transformParameters;
      if (regFloat3d( &mRegistrationParameters, &transformParameters ) != ERROR)
      {
         mpResultingTransform->SetA11( transformParameters.skew[0][0] );
         mpResultingTransform->SetA12( transformParameters.skew[0][1] );
         mpResultingTransform->SetA21( transformParameters.skew[1][0] );
         mpResultingTransform->SetA22( transformParameters.skew[1][1] );
         
         mpResultingTransform->SetDeltaX( transformParameters.dx[0] );
         mpResultingTransform->SetDeltaY( transformParameters.dx[1] );
   
         cout << "Registration successful!!" << endl << flush;
         return true;
      }
   }
   cerr << "Registration failed!!" << endl << flush;
   return false;
}

//===================================================================================================
   
void RegistrationWrapper::PrintTransform( )
{
   cout << " [ " << mpResultingTransform->GetA11( ) << "    " << mpResultingTransform->GetA12( ) << " ] [x] + [ " << mpResultingTransform->GetDeltaX( ) << " ] " << endl << flush;
   cout << " [ " << mpResultingTransform->GetA21( ) << "    " << mpResultingTransform->GetA22( ) << " ] [y] + [ " << mpResultingTransform->GetDeltaY( ) << " ] " << endl << flush;
}

//===================================================================================================

image::ArrayGrid<double>* RegistrationWrapper::GetRegisteredGrid()
{
   return CreateGridFromArray( mRegistrationParameters.outPtr, 
                               mRegistrationParameters.nx, 
                               mRegistrationParameters.ny 
                             );
}

//===================================================================================================

image::AffineTransform* RegistrationWrapper::GetResultingTransform( )
{
   return mpResultingTransform;
}

//===================================================================================================

}
}
