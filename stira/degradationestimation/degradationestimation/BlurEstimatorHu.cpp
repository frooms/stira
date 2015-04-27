
/***********************************************************************************
 *   Copyright (C) 2009 by Filip Rooms                                             *
 *                                                                                 *
 *  Terms and conditions for using this software in any form are provided in the   *
 *  file COPYING, which can be found in the root directory of this project.        *
 *                                                                                 *
 *   Contact data: filip.rooms@gmail.com                                           *
 *                 http://www.filiprooms.be/                                       *
 *                                                                                 *
 ***********************************************************************************/

#include <iostream>
#include "BlurEstimatorHu.h"
#include "../../filter/filter/GaussConvolve.h"
#include "../../image/tools/ImageIO.h"
#include "../../image/tools/NumberGridTools.h"

//#define CREATE_INTERMEDIATE_IMAGES

namespace stira {
namespace degradationestimation {

using namespace std;
using namespace image;
using namespace filter;

//----------------------------------------------------------------

BlurEstimatorHu::BlurEstimatorHu()
{
   mSigmaA = 2.0;
   mSigmaB = 4.0;
}

//----------------------------------------------------------------

BlurEstimatorHu::~BlurEstimatorHu()
{
}

//----------------------------------------------------------------

double BlurEstimatorHu::GetSigmaA()
{
   return mSigmaA;
}

//----------------------------------------------------------------

void BlurEstimatorHu::SetSigmaA( double sigmaA )
{
   mSigmaA = sigmaA;
}

//----------------------------------------------------------------

double BlurEstimatorHu::GetSigmaB()
{
   return mSigmaB;
}

//----------------------------------------------------------------

void BlurEstimatorHu::SetSigmaB( double sigmaB )
{
   mSigmaB = sigmaB;
}

//----------------------------------------------------------------

double BlurEstimatorHu::Run( image::ArrayGrid<double>* pGrid )
{
   int width  = pGrid->GetWidth();
   int height = pGrid->GetHeight();

   image::ArrayGrid<double>* pGridClone = pGrid->Clone();

   ArrayGrid<double>* pRatioGrid = new image::ArrayGrid<double>( width, height );
   ArrayGrid<double>* pBlurGrid = new image::ArrayGrid<double>( width, height );

   ArrayGrid<double>* pGridBlurredA = GaussConvolve::Convolve( pGridClone, mSigmaA );

#ifdef CREATE_INTERMEDIATE_IMAGES
   ImageIO::WritePGM( pGridBlurredA, std::string("SigmaGridA.pgm"), ImageIO::NULL_OUT );
#endif

   ArrayGrid<double>* pGridBlurredB = GaussConvolve::Convolve( pGridClone, mSigmaB );
#ifdef CREATE_INTERMEDIATE_IMAGES
   ImageIO::WritePGM( pGridBlurredB, std::string("SigmaGridB.pgm"), ImageIO::NULL_OUT );
#endif


   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         double ratioValue =    ( pGridClone->GetValue( x, y ) - pGridBlurredA->GetValue( x, y ) )
                              / ( pGridBlurredA->GetValue( x, y ) - pGridBlurredB->GetValue( x, y ) );

         if ( fabs( pGridClone->GetValue( x, y ) - pGridBlurredA->GetValue( x, y ) ) < 1.0 )
         {
            ratioValue = 0.5;
         }
         if ( fabs( pGridBlurredB->GetValue( x, y ) - pGridBlurredA->GetValue( x, y ) ) < 1.0 )
         {
            ratioValue = 0.5;
         }
         pRatioGrid->SetValue( x, y, ratioValue );
      }
   }

   for (int y = 0; y < height-8; y+=8)
   {
      for (int x = 0; x < width-8; x+=8)
      {
         double mmax = pRatioGrid->GetValue( x, y );
         for (int dy = 0; dy < 8; dy++)
         {
            for (int dx = 0; dx < 8; dx++)
            {
               if ( pRatioGrid->GetValue( x+dx, y+dy ) > mmax )
               {
                  mmax = pRatioGrid->GetValue( x+dx, y+dy );
               }
            }
         }
         double sigmaLocal = ( mSigmaA * mSigmaB ) / ( ( mSigmaB - mSigmaA ) * mmax + mSigmaB );
         for (int dy = 0; dy < 8; dy++)
         {
            for (int dx = 0; dx < 8; dx++)
            {
               pBlurGrid->SetValue( x+dx, y+dy, sigmaLocal );
            }
         }
      }
   }

#ifdef CREATE_INTERMEDIATE_IMAGES
   ImageIO::WritePGM( pRatioGrid, std::string("RatioGrid.pgm"), ImageIO::NORMAL_OUT );
#endif

   ImageIO::WritePGM( pBlurGrid, std::string("SigmaGrid.pgm"), ImageIO::NORMAL_OUT );

   delete pGridClone;
   delete pGridBlurredB;
   delete pGridBlurredA;
   delete pRatioGrid;
   delete pBlurGrid;

   return 0.0;
}

//----------------------------------------------------------------

}
}
