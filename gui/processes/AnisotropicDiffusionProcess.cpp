
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

#include "AnisotropicDiffusionProcess.h"
#include "../dialogs/AnisotropicDiffusionDialog.h"
#include "../../stira/imagedata/datastructures/Image.h"
#include "../../stira/diffusion/diffusion/AnisotropicDiffusion.h"

using namespace stira::diffusion;
using namespace stira::image;
using namespace std;

AnisotropicDiffusionProcess::AnisotropicDiffusionProcess( Image* pImage ) : Process( pImage )
{
   mProcessName = QString("Anisotropic Diffusion Result");
}

//--------------------------------------------------------

AnisotropicDiffusionProcess::~AnisotropicDiffusionProcess()
{
}

//--------------------------------------------------------

double AnisotropicDiffusionProcess::GetFlowParameter()
{
   return mFlowParameter;
}

//--------------------------------------------------------;

void AnisotropicDiffusionProcess::SetFlowParameter(double f)
{
   mFlowParameter = f;
}

//--------------------------------------------------------;
int AnisotropicDiffusionProcess::GetNrOfIterations()
{
   return mNrIterations;
}

//--------------------------------------------------------;

void AnisotropicDiffusionProcess::SetNrOfIterations(int i)
{
   mNrIterations = i;
}

//--------------------------------------------------------

void AnisotropicDiffusionProcess::run()
{
   cout << "Applying Diffusion Process directly with Image*" << endl << flush;
   AnisotropicDiffusion ad ( mpImage );
   
   ad.SetMaxNumberOfIterations ( mNrIterations );
   ad.SetFlowFactor ( mFlowParameter );
   
   AddResult( ad.Run() );  // ownership of this image is transfered through GetImage() to ImageDataList
}

//--------------------------------------------------------
