
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

#include "AnisotropicDiffusion.h"

namespace stira {
namespace diffusion {

using namespace std;

//-----------------------------------------------------------

AnisotropicDiffusion::AnisotropicDiffusion(Image* pSourceImage)
{
   mpSourceImage = pSourceImage->Clone();
   std::string outName = pSourceImage->GetImageName() + std::string("-AnisotropicDiffusion");
   mpSourceImage->SetImageName(outName);
   mFlowFactor = 0.5;
   mMaxNumberOfIterations = 15;
}

//-----------------------------------------------------------

AnisotropicDiffusion::~AnisotropicDiffusion()
{
}

//-----------------------------------------------------------

void AnisotropicDiffusion::SetMaxNumberOfIterations( int maxnr)
{
   mMaxNumberOfIterations = maxnr;
}

//-----------------------------------------------------------

int AnisotropicDiffusion::GetMaxNumberOfIterations()
{
   return mMaxNumberOfIterations;
}

//-----------------------------------------------------------

void AnisotropicDiffusion::SetFlowFactor(double fc)
{
   mFlowFactor = fc;
}

//-----------------------------------------------------------

double AnisotropicDiffusion::GetFlowFactor()
{
   return mFlowFactor;
}

//-----------------------------------------------------------

double AnisotropicDiffusion::DetermineMeanGradient(ArrayGrid<double>* pGrid)
{
   double meanGradient = 0.0;
   double pixelCount = 0.0;
   
   for (int y = 1; y < pGrid->GetHeight()-1; y++) 
   {
      for (int x=1; x < pGrid->GetWidth()-1 ; x++) 
      {
         double deltaIxu, deltaIyu;

         deltaIxu =  pGrid->GetValue(x+1, y) - pGrid->GetValue(x,  y);
         deltaIyu =  pGrid->GetValue(x, y+1) - pGrid->GetValue(x, y);

         meanGradient += fabs(deltaIxu + deltaIyu);
         pixelCount++;
      }
   }
   return (meanGradient / pixelCount);
}

//-----------------------------------------------------------

Image* AnisotropicDiffusion::Run()
{
   for (int bandNr = 0; bandNr < mpSourceImage->GetNumberOfBands(); bandNr++) 
   {
      cout << "Processing band nr " << bandNr << endl << flush;
      for (int iterationNr = 0; iterationNr < mMaxNumberOfIterations; iterationNr++)
      {
         cout << "\t\t iteration nr " << iterationNr << flush;
         
         ArrayGrid<double>* pPreviousIterationGrid = mpSourceImage->GetBands()[bandNr]->Clone();
         
         double flowConstant = DetermineMeanGradient( pPreviousIterationGrid ) * mFlowFactor;
         cout << "\t\t FlowConstant =  " << flowConstant << endl << flush;
         for (int y = 1; y < mpSourceImage->GetHeight()-1; y++) 
         {
            for (int x=1; x < mpSourceImage->GetWidth()-1 ; x++) 
            {
               double deltaIxu, deltaIxl, deltaIyu, deltaIyl;
               double cxu, cxl, cyu, cyl, deltaI, ttmp;

               deltaIxu = pPreviousIterationGrid->GetValue(x+1, y) - pPreviousIterationGrid->GetValue(x,   y);
               deltaIxl = pPreviousIterationGrid->GetValue(x,   y) - pPreviousIterationGrid->GetValue(x-1, y);
               deltaIyu = pPreviousIterationGrid->GetValue(x, y+1) - pPreviousIterationGrid->GetValue(x, y);
               deltaIyl = pPreviousIterationGrid->GetValue(x, y)   - pPreviousIterationGrid->GetValue(x, y-1);

               cxu = 1.0 / (1.0 + pow( ( abs( deltaIxu) / flowConstant ), (1.8) ) );
               cxl = 1.0 / (1.0 + pow( ( abs( deltaIxl) / flowConstant ), (1.8) ) );
               cyu = 1.0 / (1.0 + pow( ( abs( deltaIyu) / flowConstant ), (1.8) ) );
               cyl = 1.0 / (1.0 + pow( ( abs( deltaIyl) / flowConstant ), (1.8) ) );

               deltaI= (cxu*deltaIxu-cxl*deltaIxl)+(cyu*deltaIyu-cyl*deltaIyl);

               ttmp = pPreviousIterationGrid->GetValue(x,y) + mFlowFactor * deltaI;

               mpSourceImage->GetBands()[bandNr]->SetValue(x,y,ttmp);
            } //for x
         }//for y
         delete pPreviousIterationGrid;
      } //for iterationNr
   } // for bandNr
   return mpSourceImage;
}

//-----------------------------------------------------------

}
}
