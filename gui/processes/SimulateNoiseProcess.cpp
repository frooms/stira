
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

#include "SimulateNoiseProcess.h"
#include "../src/MainWindow.h"
#include <QMessageBox>

using namespace std;
using namespace stira::image;

SimulateNoiseProcess::SimulateNoiseProcess( Image* pImage ) : Process( pImage )
{
   mProcessName = QString("Simulated Noise Result");
}

//--------------------------------------------------------

SimulateNoiseProcess::~SimulateNoiseProcess()
{
}

//--------------------------------------------------------

double SimulateNoiseProcess::GetNoiseLevel()
{
   return mNoiseLevel;
}

//--------------------------------------------------------

void SimulateNoiseProcess::SetNoiseLevel(double f)
{
   mNoiseLevel = f;
}

//--------------------------------------------------------
StiraDefinitions::NoiseType SimulateNoiseProcess::GetNoiseType()
{
   return mNoiseType;
}

//--------------------------------------------------------

void SimulateNoiseProcess::SetNoiseType( StiraDefinitions::NoiseType myType )
{
   mNoiseType = myType;
}

//--------------------------------------------------------

bool SimulateNoiseProcess::GetUseColoredNoise()
{
   return mUseColoredNoise;
}

//--------------------------------------------------------

void SimulateNoiseProcess::SetUseColoredNoise( bool flag )
{
   mUseColoredNoise = flag;
}

//--------------------------------------------------------

void SimulateNoiseProcess::run()
{
   stira::image::Image* pOutImage = mpImage->Clone(); // Apply noise overwrites underlying image; create copy
   
   if (mUseColoredNoise && ( mpImage->GetNumberOfBands() != 3))
   {
      std::cerr << "The image to apply colored noise to has only one band; noise will be grey-valued." << endl << flush;
   }
   
   switch (mNoiseType)
   {
      case StiraDefinitions::NOISE_POISSON:
      {
         pOutImage->ApplyPoissonNoise( mNoiseLevel, mUseColoredNoise );
         std::string outName = mpImage->GetImageName() + std::string("-PoissonNoise");
         pOutImage->SetImageName(outName);
         break;
      }
      case StiraDefinitions::NOISE_GAUSSIAN:
      {
         pOutImage->AddGaussianNoise( mNoiseLevel, mUseColoredNoise);
         std::string outName = mpImage->GetImageName() + std::string("-GaussianNoise");
         pOutImage->SetImageName(outName);
         break;
      }
      case StiraDefinitions::NOISE_IMPULSE:
      {
         pOutImage->ApplySaltAnPepperNoise( mNoiseLevel, mUseColoredNoise);
         std::string outName = mpImage->GetImageName() + std::string("-ImpulseNoise");
         pOutImage->SetImageName(outName);
         break;
      }
   }
   AddResult( pOutImage );
   // ownership of this image is transfered through GetImage() to ImageDataList
}

//--------------------------------------------------------




