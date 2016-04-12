
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

#include "SplitBregmanDenoiseProcess.h"
#include "../dialogs/SplitBregmanDenoiseDialog.h"
#include "../../stira/image/datastructures/Image.h"
#include "../../stira/diffusion/bregman/FlashROF.h"

using namespace stira;
using namespace stira::image;
using namespace std;

SplitBregmanDenoiseProcess::SplitBregmanDenoiseProcess( Image* pImage ) : Process( pImage )
{
   mProcessName = QString("Split-Bregman TV Denoising Result");
}

//--------------------------------------------------------

SplitBregmanDenoiseProcess::~SplitBregmanDenoiseProcess()
{
}

double SplitBregmanDenoiseProcess::GetMu()
{
   return mMu;
}

void SplitBregmanDenoiseProcess::SetMu( double mu )
{
   mMu = mu;
}

double SplitBregmanDenoiseProcess::GetLambda()
{
   return mLambda;
}

void SplitBregmanDenoiseProcess::SetLambda( double lambda )
{
   mLambda = lambda;
}

int SplitBregmanDenoiseProcess::GetNumberOfGaussSeidelIterations()
{
   return mNumberOfGaussSeidelIterations;
}

void SplitBregmanDenoiseProcess::SetNumberOfGaussSeidelIterations( int nGS )
{
   mNumberOfGaussSeidelIterations = nGS;
}

int SplitBregmanDenoiseProcess::GetNumberOfBregmanIterations()
{
   return mNumberOfBregmanIterations;
}

void SplitBregmanDenoiseProcess::SetNumberOfBregmanIterations( int nBreg )
{
   mNumberOfBregmanIterations = nBreg;
}

bool SplitBregmanDenoiseProcess::GetIsIsotropic( )
{
   return mIsIsotropic;
}

void SplitBregmanDenoiseProcess::SetIsIsotropic( bool flag )
{
   mIsIsotropic = flag;
}

//--------------------------------------------------------

void SplitBregmanDenoiseProcess::run()
{
   FlashROF frof;
   
   frof.SetMu( mMu );
   frof.SetLambda( mLambda );
   frof.SetNumberOfGaussSeidelIterations( mNumberOfGaussSeidelIterations );
   frof.SetNumberOfBregmanIterations( mNumberOfBregmanIterations );
   frof.SetIsIsotropic( mIsIsotropic );

   AddResult( frof.Run( mpImage ) );  // ownership of this image is transfered through GetImage() to ImageDataList*/
}

//--------------------------------------------------------
