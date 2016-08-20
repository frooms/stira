
/***************************************************************************************
 *   Copyright (C) 2009 by Filip Rooms                                                 *
 *                                                                                     *
 *  Terms and conditions for using this software in any form are provided in the       *
 *  file COPYING, which can be found in the root directory of this project.            *
 *                                                                                     *
 *   Contact data: filip.rooms@gmail.com                                               *
 *                 http://www.filiprooms.be/                                           *
 *                                                                                     *
 ***************************************************************************************/

#include "HazeRemover.h"
#include "../../common/common/MathUtils.h"
#include "../../imagetools/tools/ImageTools.h"
#include "../../imagetools/tools/ImageIO.h"
#include "../../histogram/histogram/IntHistogram.h"

#define DIAGNOSE_DEBUG

namespace stira {
namespace contrastenhance {

using namespace imagedata;
using namespace imagetools;
using namespace histogram;
using namespace common;

//----------------------------------------------------------------------------

HazeRemover::HazeRemover()
{
   mLocalWindowSize = 9;
   mLocalWindowHalfSize = (int)(mLocalWindowSize / 2);
   mpSourceImage = 0;
   mWidth = 0;
   mHeight = 0;
   mNrOfBands = 0;
   mOmega = 0.95;  // constant value, as chosen in the reference paper
}

//----------------------------------------------------------------------------

HazeRemover::~HazeRemover()
{
}

//----------------------------------------------------------------------------

double HazeRemover::EstimateAtmosphericLight()
{
   double binSize = 1;
   int nrOfBands = 1;
   int minValue =   0;
   int maxValue = 255;
   IntHistogram ih( binSize, nrOfBands, minValue, maxValue );
   for ( int y = mLocalWindowHalfSize; y < mHeight - mLocalWindowHalfSize; y++ )
   {
      for ( int x = mLocalWindowHalfSize; x < mWidth - mLocalWindowHalfSize; x++ )
      {
         double darkValue = ImageTools::GetLocalDarkChannel( mpSourceImage, x, y, mLocalWindowSize );
         ih.AddDataPoint( (int)(darkValue) );
      }
   }
   ih.DetermineBounds();
   return ih.GetUpperBound();
}

//----------------------------------------------------------------------------

Image* HazeRemover::Run( Image* pInImage )
{
   Image* pOutImage = pInImage->Clone();
   mpSourceImage = pInImage;
   mWidth =  mpSourceImage->GetWidth();
   mHeight = mpSourceImage->GetHeight();
   mNrOfBands = pInImage->GetNumberOfBands();

   #ifdef DIAGNOSE_DEBUG
      Image* pTransmissionImage = new Image( mWidth, mHeight, 1 );
   #endif

   double atmosphericLight = EstimateAtmosphericLight();

   for ( int y = mLocalWindowHalfSize; y < mHeight - mLocalWindowHalfSize; y++ )
   {
      for ( int x = mLocalWindowHalfSize; x < mWidth - mLocalWindowHalfSize; x++ )
      {
         double darkValue = ImageTools::GetLocalDarkChannel( pInImage, x, y, mLocalWindowSize );
         double transmission = MathUtils::GetMax(1.0 - 0.95 * (darkValue / atmosphericLight), 0.1);
         for(int bandNr = 0; bandNr < mNrOfBands; bandNr++)
         {
            double sceneRadiance = atmosphericLight + ( mpSourceImage->GetBands()[ bandNr ]->GetValue( x, y ) - atmosphericLight ) / transmission;
            pOutImage->GetBands()[ bandNr ]->SetValue( x, y, sceneRadiance );
         }

         #ifdef DIAGNOSE_DEBUG
            pTransmissionImage->GetBands()[ 0 ]->SetValue( x, y, transmission );
         #endif
      }
   }

   #ifdef DIAGNOSE_DEBUG
      ImageIO::Write( pTransmissionImage, std::string("pTransmissionImage.ppm"), ImageIO::NORMAL_OUT );
      delete pTransmissionImage;
   #endif
   return pOutImage;
}

}
}

