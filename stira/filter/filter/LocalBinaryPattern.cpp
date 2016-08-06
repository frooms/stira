
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

#include "LocalBinaryPattern.h"
#include "../../imagetools/tools/ImageTools.h"
#include "../../imagetools/tools/ImageIO.h"
#include "../../histogram/histogram/FloatHistogram.h"

#include "../../common/common/MathUtils.h"
#include "../../common/common/Curve.h"
#include "ColorLookupTable.h"


namespace stira{
namespace filter{

using namespace common;
using namespace image;
using namespace histogram;

// binomial weights:
//   1   2   4
// 128   0   8
//  64  32  16

double weightMask[9] = {1, 2, 4, 8, 0, 16, 32, 64, 128};

LocalBinaryPattern::LocalBinaryPattern()
{
   image::ArrayGrid<double>* pGrid = 0;
   double initAngle = 0;
   double radius = 1;
   int nrPoints = 8;
   Initialize( pGrid, initAngle, radius, nrPoints );
}

//----------------------------------------------------------------

LocalBinaryPattern::LocalBinaryPattern( image::ArrayGrid<double>* pGrid, double initAngle, double radius, int nrPoints )
{
   Initialize( pGrid, initAngle, radius, nrPoints );
   mHasPointsOfInterest = false;
}

//----------------------------------------------------------------

LocalBinaryPattern::LocalBinaryPattern( image::ArrayGrid<double>* pGrid, double initAngle, double radius, int nrPoints, std::vector< Point<int> > vPointsOfInterest )
{
   Initialize( pGrid, initAngle, radius, nrPoints );
   mHasPointsOfInterest = true;
   mvPointsOfInterest = vPointsOfInterest;
}

//----------------------------------------------------------------

void LocalBinaryPattern::Initialize( image::ArrayGrid<double>* pGrid, double initAngle, double radius, int nrPoints )
{
   mpGrid = pGrid;
   mRadius = radius;
   mInitialAngle = initAngle;
   mNumberOfPoints = nrPoints;
   double dTheta = 2.0 * M_PI / (double)(nrPoints);
   for (int i = 0; i < nrPoints; i++)
   {
      double countTheta = (double)(i) * dTheta;
      Point<double> dPoint( radius * cos( countTheta ), radius * sin( countTheta ) );
      //cout << "Point added " << dPoint << endl << flush;
      mvDeltaPoints.push_back(dPoint);
   }

   mPointsGLTP[ 0][0] = -2.1000;  mPointsGLTP[ 0][1] = -2.1000;
   mPointsGLTP[ 1][0] = -1.3500;  mPointsGLTP[ 1][1] = -2.6500;
   mPointsGLTP[ 2][0] = -0.4600;  mPointsGLTP[ 2][1] = -2.9300;
   mPointsGLTP[ 3][0] =  0.4600;  mPointsGLTP[ 3][1] = -2.9300;
   mPointsGLTP[ 4][0] =  1.3500;  mPointsGLTP[ 4][1] = -2.6500;
   mPointsGLTP[ 5][0] =  2.1000;  mPointsGLTP[ 5][1] = -2.1000;
   mPointsGLTP[ 6][0] = -2.6500;  mPointsGLTP[ 6][1] = -1.3500;
   mPointsGLTP[ 7][0] = -1.3700;  mPointsGLTP[ 7][1] = -1.3700;
   mPointsGLTP[ 8][0] = -0.5000;  mPointsGLTP[ 8][1] = -1.8700;
   mPointsGLTP[ 9][0] =  0.5000;  mPointsGLTP[ 9][1] = -1.8700;
   mPointsGLTP[10][0] =  1.3700;  mPointsGLTP[10][1] = -1.3700;
   mPointsGLTP[11][0] =  2.6500;  mPointsGLTP[11][1] = -1.3500;
   mPointsGLTP[12][0] = -2.9300;  mPointsGLTP[12][1] = -0.4600;
   mPointsGLTP[13][0] = -1.8700;  mPointsGLTP[13][1] = -0.5000;
   mPointsGLTP[14][0] = -0.5000;  mPointsGLTP[14][1] = -0.5000;
   mPointsGLTP[15][0] =  0.5000;  mPointsGLTP[15][1] = -0.5000;
   mPointsGLTP[16][0] =  1.8700;  mPointsGLTP[16][1] = -0.5000;
   mPointsGLTP[17][0] =  2.9300;  mPointsGLTP[17][1] = -0.4600;
   mPointsGLTP[18][0] = -2.9300;  mPointsGLTP[18][1] =  0.4600;
   mPointsGLTP[19][0] = -1.8700;  mPointsGLTP[19][1] =  0.5000;
   mPointsGLTP[20][0] = -0.5000;  mPointsGLTP[20][1] =  0.5000;
   mPointsGLTP[21][0] =  0.5000;  mPointsGLTP[21][1] =  0.5000;
   mPointsGLTP[22][0] =  1.8700;  mPointsGLTP[22][1] =  0.5000;
   mPointsGLTP[23][0] =  2.9300;  mPointsGLTP[23][1] =  0.4600;
   mPointsGLTP[24][0] = -2.6500;  mPointsGLTP[24][1] =  1.3500;
   mPointsGLTP[25][0] = -1.3700;  mPointsGLTP[25][1] =  1.3700;
   mPointsGLTP[26][0] = -0.5000;  mPointsGLTP[26][1] =  1.8700;
   mPointsGLTP[27][0] =  0.5000;  mPointsGLTP[27][1] =  1.8700;
   mPointsGLTP[28][0] =  1.3700;  mPointsGLTP[28][1] =  1.3700;
   mPointsGLTP[29][0] =  2.6500;  mPointsGLTP[29][1] =  1.3500;
   mPointsGLTP[30][0] = -2.1000;  mPointsGLTP[30][1] =  2.1000;
   mPointsGLTP[31][0] = -1.3500;  mPointsGLTP[31][1] =  2.6500;
   mPointsGLTP[32][0] = -0.4600;  mPointsGLTP[32][1] =  2.9300;
   mPointsGLTP[33][0] =  0.4600;  mPointsGLTP[33][1] =  2.9300;
   mPointsGLTP[34][0] =  1.3500;  mPointsGLTP[34][1] =  2.6500;
   mPointsGLTP[35][0] =  2.1000;  mPointsGLTP[35][1] =  2.1000;

   mPointsLBPSym[ 0][0] = -1.3700;   mPointsLBPSym[ 0][1] = -1.3700;
   mPointsLBPSym[ 1][0] = -0.5000;   mPointsLBPSym[ 1][1] = -1.8700;
   mPointsLBPSym[ 2][0] =  0.5000;   mPointsLBPSym[ 2][1] = -1.8700;
   mPointsLBPSym[ 3][0] =  1.3700;   mPointsLBPSym[ 3][1] = -1.3700;
   mPointsLBPSym[ 4][0] =  1.8700;   mPointsLBPSym[ 4][1] = -0.5000;
   mPointsLBPSym[ 5][0] =  1.8700;   mPointsLBPSym[ 5][1] =  0.5000;
   mPointsLBPSym[ 6][0] =  1.3700;   mPointsLBPSym[ 6][1] =  1.3700;
   mPointsLBPSym[ 7][0] =  0.5000;   mPointsLBPSym[ 7][1] =  1.8700;
   mPointsLBPSym[ 8][0] = -0.5000;   mPointsLBPSym[ 8][1] =  1.8700;
   mPointsLBPSym[ 9][0] = -1.3700;   mPointsLBPSym[ 9][1] =  1.3700;
   mPointsLBPSym[10][0] = -1.8700;   mPointsLBPSym[10][1] =  0.5000;
   mPointsLBPSym[11][0] = -1.8700;   mPointsLBPSym[11][1] = -0.5000;
}


//--------------------------------------------------------------------------

LocalBinaryPattern::~LocalBinaryPattern()
{
}

//---------------------------------------------------------------------------------------------

std::vector< common::Point< double > > LocalBinaryPattern::GetSamplePoints()
{
   return mvDeltaPoints;
}

//---------------------------------------------------------------------------------------------


void LocalBinaryPattern::DrawDeltaPoints( ArrayGrid<double>* pOutGrid, int x, int y )
{
   for (unsigned int i = 0; i < mvDeltaPoints.size(); i++)
   {
      pOutGrid->SetValue( x+mvDeltaPoints[i].x, y+mvDeltaPoints[i].y, 128 );
   }
}

//---------------------------------------------------------------------------------------------

std::vector<bool> LocalBinaryPattern::RunVector( int x, int y )
{
   std::vector<bool> vVector;

   double myCentralValue = mpGrid->GetValue( x, y );
   for (int i = 0; i < mNumberOfPoints; i++)
   {
      double myValue = 0;
#ifdef USE_BILINEAR_INTERPOLATION
      myValue = mBilinearInterpolator.Run( mpGrid, x + mvDeltaPoints[i].x, y + mvDeltaPoints[i].y );
#else
      myValue = mpGrid->GetValue( (int)((double)(x) + mvDeltaPoints[i].x + 0.5),
                                  (int)((double)(y) + mvDeltaPoints[i].y +0.5 ) ) );
#endif
      bool boolValue;
      if ( (int)(myValue + 0.5) >= (int)(myCentralValue + 0.5) )
      {
         boolValue = true;
      }
      else
      {
         boolValue = false;
      }
      vVector.push_back( boolValue );
   }
   return vVector;
}

//---------------------------------------------------------------------------------------------

int LocalBinaryPattern::RunCode( int x, int y )
{
   std::vector<bool> vVector = RunVector( x, y );
   int outCode = 0;
   int myFactor = 1;

   for (int i = 0; i < mNumberOfPoints; i++)
   {
      if ( vVector[i] )
      {
         outCode += myFactor;
      }
      myFactor *= 2;
   }
   return outCode;
}

//---------------------------------------------------------------------------------------------

histogram::FloatHistogram* LocalBinaryPattern::RunHistogram( int /*ID*/ )
{
   int nrBins = MathUtils::ComputeIntegerPower( 2, mNumberOfPoints );
   int height = mpGrid->GetHeight();
   int width  = mpGrid->GetWidth();

#ifdef WRITE_OUTPUTS
   image::ArrayGrid<double>* pLbpGrid = new image::ArrayGrid<double>( width, height );
#endif

   double binSize = 1;
   int nrOfBands = 1;
   int minValue = 0;
   int maxValue = nrBins;

   histogram::IntHistogram* pIH = new histogram::IntHistogram( binSize, nrOfBands, minValue, maxValue );

   if ( !mHasPointsOfInterest )
   {
      cout << "Analysing full grid!" << endl << flush;
      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x++)
         {
            int myValue = RunCode( x, y );
#ifdef WRITE_OUTPUTS
            pLbpGrid->SetValue( x, y, myValue );
#endif
            pIH->AddDataPoint( myValue );
         }
      }
   }
   else
   {
      cout << "Only analysing points of interest!" << endl << flush;
      int myLength = mvPointsOfInterest.size();
      for (int i = 0; i < myLength; i++)
      {
         int myValue = RunCode( mvPointsOfInterest[i].x, mvPointsOfInterest[i].y );
#ifdef WRITE_OUTPUTS
         pLbpGrid->SetValue( mvPointsOfInterest[i].x, mvPointsOfInterest[i].y, myValue );
#ifdef DRAW_DELTA_POINTS
         if (    ( i%15 == 0 )
              && ( ( mvPointsOfInterest[i].GetX() - mRadius) > 0 )
              && ( ( mvPointsOfInterest[i].GetX() + mRadius) < pLbpGrid->GetWidth()-1 )
              && ( ( mvPointsOfInterest[i].GetY() - mRadius) > 0 )
              && ( ( mvPointsOfInterest[i].GetY() + mRadius) < pLbpGrid->GetHeight()-1 )
            )
         {
            DrawDeltaPoints( pLbpGrid, mvPointsOfInterest[i].GetX(), mvPointsOfInterest[i].GetY() );
         }
#endif
#endif
         pIH->AddDataPoint( myValue );
      }
   }
#ifdef WRITE_OUTPUTS
   ImageIO::WritePGM( pLbpGrid, StringUtils::ConstructFileName( std::string("Lbp-pattern-"), ID, std::string(".pgm") ), ImageIO::NORMAL_OUT);
   delete pLbpGrid;
#endif

   bool requiresNormalization = true;
   histogram::FloatHistogram* pFH = new histogram::FloatHistogram( pIH, requiresNormalization );
   delete pIH;
   return pFH;
}

//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------

int LocalBinaryPattern::SignComparison(double a, double b, double threshold, bool myType)
{
   int Res, R1, R2;
   if (myType)
   {
      if ( ( b - a ) > threshold ) {R1 = 1;} else {R1 = 0;}
      if ( ( a - b ) > threshold ) {R2 = 1;} else {R2 = 0;}
      Res = 2-(R1+R2*2);
   }
   else //if Type==0
   {
      if ( ( a - b ) > threshold )
      {
         Res = 1;
      }
      else
      {
         Res = 0;
      }
   }
   return Res;
}

//--------------------------------------------------------------------------

int LocalBinaryPattern::ComputePointGLDP( image::ArrayGrid<double>* pGridIn, int x, int y, double threshold, bool myType )
{
   double p[6][6];
   int k = 0;

   for (int m = 0; m < 6; m++ )
   {
       for (int n = 0; n < 6; n++ )
       {
          double value = 0;
#ifdef USE_BILINEAR_INTERPOLATION
          value = mBilinearInterpolator.Run( pGridIn, (double)(x) + mPointsGLTP[k][0],
                                                      (double)(y) + mPointsGLTP[k][1] );
#else
          // approximation: nearest neighbor interpolation instead of bilinear interpolation
          value = pGridIn->GetValue( (int)((double)(x) + mPointsGLTP[k][0] + 0.5), (int)((double)(y + mPointsGLTP[k][1] +0.5 ) ) );
#endif
          p[m][n] = value;
          k++;
       }
   }
   int b11 = SignComparison( p[0][0],   p[1][1],                 threshold, myType );
   int b12 = SignComparison( p[0][1], ( p[1][2] + p[1][1] ) / 2, threshold, myType );
   int b13 = SignComparison( p[0][2],   p[1][2],                 threshold, myType );
   int b14 = SignComparison( p[0][3],   p[1][3],                 threshold, myType );
   int b15 = SignComparison( p[0][4], ( p[1][3] + p[1][4] ) / 2, threshold, myType );
   int b16 = SignComparison( p[0][5],   p[1][4],                 threshold, myType );
   int b21 = SignComparison( p[1][0], ( p[2][1] + p[1][1] ) / 2, threshold, myType );
   int b22 = SignComparison( p[1][1],   p[2][2],                 threshold, myType );
   int b23 = SignComparison( p[1][2],   p[2][2],                 threshold, myType );
   int b24 = SignComparison( p[1][3],   p[2][3],                 threshold, myType );
   int b25 = SignComparison( p[1][4],   p[2][3],                 threshold, myType );
   int b26 = SignComparison( p[1][5], ( p[2][4] + p[1][4] ) / 2, threshold, myType );
   int b31 = SignComparison( p[2][0],   p[2][1],                 threshold, myType );
   int b32 = SignComparison( p[2][1],   p[2][2],                 threshold, myType );
   int b33 = SignComparison( p[2][2], pGridIn->GetValue(x,y),    threshold, myType );
   int b34 = SignComparison( p[2][3], pGridIn->GetValue(x,y),    threshold, myType );
   int b35 = SignComparison( p[2][4],   p[2][3],                 threshold, myType );
   int b36 = SignComparison( p[2][5],   p[2][4],                 threshold, myType );
   int b41 = SignComparison( p[3][0],   p[3][1],                 threshold, myType );
   int b42 = SignComparison( p[3][1],   p[3][2],                 threshold, myType );
   int b43 = SignComparison( p[3][2], pGridIn->GetValue(x,y),    threshold, myType );
   int b44 = SignComparison( p[3][3], pGridIn->GetValue(x,y),    threshold, myType );
   int b45 = SignComparison( p[3][4],   p[3][3],                 threshold, myType );
   int b46 = SignComparison( p[3][5],   p[3][4],                 threshold, myType );
   int b51 = SignComparison( p[4][0], ( p[3][1] + p[4][1] ) / 2, threshold, myType );
   int b52 = SignComparison( p[4][1],   p[3][2],                 threshold, myType );
   int b53 = SignComparison( p[4][2],   p[3][2],                 threshold, myType );
   int b54 = SignComparison( p[4][3],   p[3][3],                 threshold, myType );
   int b55 = SignComparison( p[4][4],   p[3][3],                 threshold, myType );
   int b56 = SignComparison( p[4][5], ( p[3][4]+p[4][4])/2,      threshold, myType );
   int b61 = SignComparison( p[5][0],   p[4][1],                 threshold, myType );
   int b62 = SignComparison( p[5][1], ( p[4][2]+p[4][1])/2,      threshold, myType );
   int b63 = SignComparison( p[5][2],   p[4][2],                 threshold, myType );
   int b64 = SignComparison( p[5][3],   p[4][3],                 threshold, myType );
   int b65 = SignComparison( p[5][4], ( p[4][3] + p[4][4] ) / 2, threshold, myType );
   int b66 = SignComparison( p[5][5],   p[4][4],                 threshold, myType );

   int bd13 = SignComparison( ( p[0][5] + p[1][5] + p[2][5] ) / 3, ( p[1][4] + p[2][4] ) / 2, threshold, myType);
   int bd23 = SignComparison( ( p[0][3] + p[0][4] + p[0][5] ) / 3, ( p[1][4] + p[1][3] ) / 2, threshold, myType);
   int bd33 = SignComparison( ( p[0][0] + p[0][1] + p[0][2] ) / 3, ( p[1][1] + p[1][2] ) / 2, threshold, myType);
   int bd43 = SignComparison( ( p[0][0] + p[1][0] + p[2][0] ) / 3, ( p[1][1] + p[2][1] ) / 2, threshold, myType);
   int bd53 = SignComparison( ( p[3][0] + p[4][0] + p[5][0] ) / 3, ( p[3][1] + p[4][1] ) / 2, threshold, myType);
   int bd63 = SignComparison( ( p[5][0] + p[5][1] + p[5][2] ) / 3, ( p[4][1] + p[4][2] ) / 2, threshold, myType);
   int bd73 = SignComparison( ( p[0][3] + p[5][4] + p[5][5] ) / 3, ( p[4][4] + p[4][3] ) / 2, threshold, myType);
   int bd83 = SignComparison( ( p[3][5] + p[4][5] + p[5][5] ) / 3, ( p[3][4] + p[4][4] ) / 2, threshold, myType);

   int bd12 = SignComparison( ( p[1][4] + p[2][4] ) / 2,            p[2][3], threshold, myType);
   int bd22 = SignComparison( ( p[1][4] + p[1][3] ) / 2,            p[2][3], threshold, myType);
   int bd32 = SignComparison( ( p[1][1] + p[1][2] ) / 2,            p[2][2], threshold, myType);
   int bd42 = SignComparison( ( p[1][1] + p[2][1] ) / 2,            p[2][2], threshold, myType);
   int bd52 = SignComparison( ( p[3][1] + p[4][1] ) / 2,            p[3][2], threshold, myType);
   int bd62 = SignComparison( ( p[4][1] + p[4][2] ) / 2,            p[3][2], threshold, myType);
   int bd72 = SignComparison( ( p[4][3] + p[4][4] ) / 2,            p[3][3], threshold, myType);
   int bd82 = SignComparison( ( p[3][4] + p[4][4] ) / 2,            p[3][3], threshold, myType);

   int d[8];

   d[0] = bd13 * bd12;
   d[1] = bd23 * bd22;
   d[2] = bd33 * bd32;
   d[3] = bd43 * bd42;
   d[4] = bd53 * bd52;
   d[5] = bd63 * bd62;
   d[6] = bd73 * bd72;
   d[7] = bd83 * bd82;

   int d11 = bd12 * b34;
   int d21 = bd22 * b34;
   int d31 = bd32 * b33;
   int d41 = bd42 * b33;
   int d51 = bd52 * b43;
   int d61 = bd62 * b43;
   int d71 = bd72 * b44;
   int d81 = bd82 * b44;


   int w1, w2, w3, w4, w5, w6, wwa, wwb;

   wwa = MathUtils::ComputeIntegerPower( 2, 7 );
   wwb = MathUtils::ComputeIntegerPower( 2, 6 );

   if (myType)
   {
      w1 = 243;
      w2 = 81;
      w3 = 27;
      w4 = 9;
      w5 = 3;
      w6 = 1;
   }
   else
   {
      w1 = 32;
      w2 = 16;
      w3 = 8;
      w4 = 4;
      w5 = 2;
      w6 = 1;
   }

   int Result[8];

   Result[0] =             b34 * w1 + b25 * w3  + b16 * w6;
   Result[1] = Result[0] + b24 * w2 + b14 * w4  + b15 * w5;
   Result[0] = Result[0] + b35 * w2 + b36 * w4  + b26 * w5;

   Result[2] =             b33 * w1 + b22 * w3  + b11 * w6;
   Result[3] = Result[2] + b23 * w2 + b13 * w4  + b12 * w5;
   Result[2] = Result[2] + b32 * w2 + b31 * w4  + b21 * w5;

   Result[4] =             b43 * w1 + b52 * w3  + b61 * w6;
   Result[5] = Result[4] + b42 * w2 + b41 * w4  + b51 * w5;
   Result[4] = Result[4] + b53 * w2 + b63 * w4  + b62 * w5;

   Result[6] =             b44 * w1 + b55 * w3  + b66 * w6;
   Result[7] = Result[6] + b54 * w2 + b64 * w4  + b65 * w5;
   Result[6] = Result[6] + b45 * w2 + b46 * w4  + b56 * w5;

   int Result2[8];

   Result2[0] = Result[0] + d11 * wwa + d[0] * wwb;
   Result2[1] = Result[1] + d21 * wwa + d[1] * wwb;
   Result2[2] = Result[2] + d31 * wwa + d[2] * wwb;
   Result2[3] = Result[3] + d41 * wwa + d[3] * wwb;
   Result2[4] = Result[4] + d51 * wwa + d[4] * wwb;
   Result2[5] = Result[5] + d61 * wwa + d[5] * wwb;
   Result2[6] = Result[6] + d71 * wwa + d[6] * wwb;
   Result2[7] = Result[7] + d81 * wwa + d[7] * wwb;

   return ( (   Result2[0] + Result2[1] + Result2[2] + Result2[3]
              + Result2[4] + Result2[5] + Result2[6] + Result2[7]
            ) / 8
          );
}

//--------------------------------------------------------------------------

int LocalBinaryPattern::ComputePointGLTP( image::ArrayGrid<double>* pGridIn, int x, int y, double threshold, bool myType )
{
   double p[6][6];
   int k = 0;

   for (int m = 0; m < 6; m++ )
   {
       for (int n = 0; n < 6; n++ )
       {
          double value = 0;
#ifdef USE_BILINEAR_INTERPOLATION
          value = mBilinearInterpolator.Run( pGridIn, (double)(x) + mPointsGLTP[k][0],
                                                      (double)(y) + mPointsGLTP[k][1] );
#else
          // approximation: nearest neighbor interpolation instead of bilinear interpolation
          value = pGridIn->GetValue( (int)((double)(x) + mPointsGLTP[k][0] + 0.5), (int)((double)(y + mPointsGLTP[k][1] +0.5 ) ) );
#endif
          p[m][n] = value;
          k++;
       }
   }
   int b11 = SignComparison( p[0][0],   p[1][1],                 threshold, myType );
   int b12 = SignComparison( p[0][1], ( p[1][2] + p[1][1] ) / 2, threshold, myType );
   int b13 = SignComparison( p[0][2],   p[1][2],                 threshold, myType );
   int b14 = SignComparison( p[0][3],   p[1][3],                 threshold, myType );
   int b15 = SignComparison( p[0][4], ( p[1][3] + p[1][4] ) / 2, threshold, myType );
   int b16 = SignComparison( p[0][5],   p[1][4],                 threshold, myType );
   int b21 = SignComparison( p[1][0], ( p[2][1] + p[1][1] ) / 2, threshold, myType );
   int b22 = SignComparison( p[1][1],   p[2][2],                 threshold, myType );
   int b23 = SignComparison( p[1][2],   p[2][2],                 threshold, myType );
   int b24 = SignComparison( p[1][3],   p[2][3],                 threshold, myType );
   int b25 = SignComparison( p[1][4],   p[2][3],                 threshold, myType );
   int b26 = SignComparison( p[1][5], ( p[2][4] + p[1][4] ) / 2, threshold, myType );
   int b31 = SignComparison( p[2][0],   p[2][1],                 threshold, myType );
   int b32 = SignComparison( p[2][1],   p[2][2],                 threshold, myType );
   int b33 = SignComparison( p[2][2], pGridIn->GetValue(x,y),    threshold, myType );
   int b34 = SignComparison( p[2][3], pGridIn->GetValue(x,y),    threshold, myType );
   int b35 = SignComparison( p[2][4],   p[2][3],                 threshold, myType );
   int b36 = SignComparison( p[2][5],   p[2][4],                 threshold, myType );
   int b41 = SignComparison( p[3][0],   p[3][1],                 threshold, myType );
   int b42 = SignComparison( p[3][1],   p[3][2],                 threshold, myType );
   int b43 = SignComparison( p[3][2], pGridIn->GetValue(x,y),    threshold, myType );
   int b44 = SignComparison( p[3][3], pGridIn->GetValue(x,y),    threshold, myType );
   int b45 = SignComparison( p[3][4],   p[3][3],                 threshold, myType );
   int b46 = SignComparison( p[3][5],   p[3][4],                 threshold, myType );
   int b51 = SignComparison( p[4][0], ( p[3][1] + p[4][1] ) / 2, threshold, myType );
   int b52 = SignComparison( p[4][1],   p[3][2],                 threshold, myType );
   int b53 = SignComparison( p[4][2],   p[3][2],                 threshold, myType );
   int b54 = SignComparison( p[4][3],   p[3][3],                 threshold, myType );
   int b55 = SignComparison( p[4][4],   p[3][3],                 threshold, myType );
   int b56 = SignComparison( p[4][5], ( p[3][4]+p[4][4])/2,      threshold, myType );
   int b61 = SignComparison( p[5][0],   p[4][1],                 threshold, myType );
   int b62 = SignComparison( p[5][1], ( p[4][2]+p[4][1])/2,      threshold, myType );
   int b63 = SignComparison( p[5][2],   p[4][2],                 threshold, myType );
   int b64 = SignComparison( p[5][3],   p[4][3],                 threshold, myType );
   int b65 = SignComparison( p[5][4], ( p[4][3] + p[4][4] ) / 2, threshold, myType );
   int b66 = SignComparison( p[5][5],   p[4][4],                 threshold, myType );

   int w1, w2, w3, w4, w5, w6;//, WB;

   if (myType)
   {
      w1 = 243;
      w2 = 81;
      w3 = 27;
      w4 = 9;
      w5 = 3;
      w6 = 1;
      //WB = 728;
   }
   else
   {
      w1 = 32;
      w2 = 16;
      w3 = 8;
      w4 = 4;
      w5 = 2;
      w6 = 1;
      //WB = 63;
   }

   int Result[8];

   Result[0] =             b34 * w1 + b25 * w3  + b16 * w6;
   Result[1] = Result[0] + b24 * w2 + b14 * w4  + b15 * w5;
   Result[0] = Result[0] + b35 * w2 + b36 * w4  + b26 * w5;

   Result[2] =             b33 * w1 + b22 * w3  + b11 * w6;
   Result[3] = Result[2] + b23 * w2 + b13 * w4  + b12 * w5;
   Result[2] = Result[2] + b32 * w2 + b31 * w4  + b21 * w5;

   Result[4] =             b43 * w1 + b52 * w3  + b61 * w6;
   Result[5] = Result[4] + b42 * w2 + b41 * w4  + b51 * w5;
   Result[4] = Result[4] + b53 * w2 + b63 * w4  + b62 * w5;

   Result[6] =             b44 * w1 + b55 * w3  + b66 * w6;
   Result[7] = Result[6] + b54 * w2 + b64 * w4  + b65 * w5;
   Result[6] = Result[6] + b45 * w2 + b46 * w4  + b56 * w5;

   return ( (   Result[0] + Result[1] + Result[2] + Result[3]
              + Result[4] + Result[5] + Result[6] + Result[7]
            ) / 8
          );
}

image::ArrayGrid<int>* LocalBinaryPattern::ComputeLBPSymImage( image::ArrayGrid<double>* pGridIn, double threshold, bool myType )
{
   int width  = pGridIn->GetWidth();
   int height = pGridIn->GetHeight();
   image::ArrayGrid<int>* pLBPGrid = new image::ArrayGrid<int>(width, height);
   for (int y = 3; y < height-3; y++)
   {
      for (int x = 3; x < width-3; x++)
      {
         pLBPGrid->SetValue( x, y, ComputePointLBPSym( pGridIn, x, y, threshold, myType ) );
      }
   }
   return pLBPGrid;
}

//--------------------------------------------------------------------------

int LocalBinaryPattern::ComputePointLBPSym( image::ArrayGrid<double>* pGridIn, int x, int y, double threshold, bool myType )
{
   int Res = 1;

   for (int i=0; i < 12; i++)
   {
      double value = 0;
#ifdef USE_BILINEAR_INTERPOLATION
      value = mBilinearInterpolator.Run( pGridIn, x + mPointsLBPSym[ i][0],
                                                  y + mPointsLBPSym[ i][1] );
#else
      // approximation: nearest neighbor interpolation instead of bilinear interpolation
      double value = pGridIn->GetValue( (int)((double)(x) + mPointsLBPSym[ i][0] + 0.5), (int)((double)(y + mPointsLBPSym[ i][1] +0.5 ) ) );
#endif
      int b = SignComparison( value, pGridIn->GetValue( x, y ), threshold , myType );
      Res += b * MathUtils::ComputeIntegerPower( 2, i );
   }
   return (Res-1);
}

//--------------------------------------------------------------------------

FloatHistogram LocalBinaryPattern::ComputePointLBPSymHistogram( image::ArrayGrid<double>* pGridIn, int frameNr, int topX, int topY, int bottomX, int bottomY, double threshold, bool myType )
{
   int nrBins = 4096;
   int nrBands = 1;
   FloatHistogram flh( nrBins, nrBands );
   topX = MathUtils::ClipValue(topX, 0, pGridIn->GetWidth() );
   topY = MathUtils::ClipValue(topY, 0, pGridIn->GetHeight() );
   bottomX = MathUtils::ClipValue(bottomX, 0, pGridIn->GetWidth() );
   bottomY = MathUtils::ClipValue(bottomY, 0, pGridIn->GetHeight() );

   ArrayGrid<int>* pGrid = new ArrayGrid<int>(bottomX-topX+1, bottomY-topY+1);

   for (int y = topY; y < bottomY; y++)
   {
      for (int x = topX; x < bottomX; x++)
      {
         int label = ComputePointLBPSym( pGridIn, x, y, threshold, myType );
         flh.AddDataPoint( label );
         pGrid->SetValue(x-topX, y-topY, label);
      }
   }

   stringstream ss;
   ss << "LBP" << frameNr << ".png";
   std::string fileName = ss.str();
   ImageIO::WriteOpenCV(pGrid, fileName);
   delete pGrid;


   flh.Normalize( );

   return flh;
}

//--------------------------------------------------------------------------

double LocalBinaryPattern::ComputeJensenShannonDivergenceBetweenImagePatches( ArrayGrid<double>* pGridIn, int frameNr,
                                                                              int topX1, int topY1, int bottomX1, int bottomY1,
                                                                              int topX2, int topY2, int bottomX2, int bottomY2  )
{
   double threshold = 1.0;
   bool myType = false;
   int imWidth  = pGridIn->GetWidth();
   int imHeight = pGridIn->GetHeight();

#ifdef GENERATE_INTERMEDIATE_IMAGES
   ColorLookupTable cLUT;
   image::Image* pImage = new Image( pGridIn->GetWidth(), pGridIn->GetHeight(), 3 );
#endif
   for (int y = 3; y < imHeight-3; y++)
   {
      for (int x = 3; x < imWidth-3; x++)
      {
         int myValue = ComputePointLBPSym( pGridIn, x, y, threshold, false );

#ifdef GENERATE_INTERMEDIATE_IMAGES
         ColorValue cv( (double)(255) * cLUT.mLUT_R_last[myValue][2],
                        (double)(255) * cLUT.mLUT_R_last[myValue][1],
                        (double)(255) * cLUT.mLUT_R_last[myValue][0], TYPE_RGB );
         pImage->SetColor( x, y, cv);
#endif
      }
   }

#ifdef GENERATE_INTERMEDIATE_IMAGES
   stringstream ss;
   ss << "LBP_fullImage" << frameNr << ".png";
   std::string fileName = ss.str();
   ImageIO::WriteOpenCV(pImage, fileName);
   delete pImage;
#endif

   FloatHistogram myHistogram1 = ComputePointLBPSymHistogram( pGridIn, 10 + frameNr, topX1, topY1, bottomX1, bottomY1, threshold, myType );
   stringstream ss1;
   ss1 << std::string("Histogram-") << 10 + frameNr << ".txt";
   std::string fileName1 = ss1.str();
   myHistogram1.Write( fileName1 );

   FloatHistogram myHistogram2 = ComputePointLBPSymHistogram( pGridIn, 20 + frameNr, topX2, topY2, bottomX2, bottomY2, threshold, myType );
   stringstream ss2;
   ss2 << std::string("Histogram-") << 20 + frameNr << ".txt";
   std::string fileName2 = ss2.str();
   myHistogram1.Write( fileName2 );

   double distance = myHistogram1.ComputeJensenShannonMetric( &myHistogram2 );
   return distance;
}

//--------------------------------------------------------------------------

image::Image* LocalBinaryPattern::RunClassic( image::Image* pImageIn )
{
   int borderSize = 1;
   Image* pExpandedImage = ImageTools::MirrorBorder( pImageIn, borderSize, borderSize );
   Image* pCloneImage = pExpandedImage->Clone();

   int widthExpanded  = pExpandedImage->GetWidth();
   int heightExpanded = pExpandedImage->GetHeight();
   int nrBands = pExpandedImage->GetNumberOfBands();

   for (int bandNr = 0; bandNr < nrBands; bandNr++)
   {
      ArrayGrid<double>* pInGrid  = pExpandedImage->GetBands()[bandNr];
      ArrayGrid<double>* pOutGrid = pCloneImage->GetBands()[bandNr];
      for (int y = 1; y < heightExpanded-1; y++)
      {
         for (int x = 1; x < widthExpanded-1; x++)
         {
            double ttmpValue = 0.0;
            int positionCounter = 0;
            for (int yi = -1; yi <= 1; yi++)
            {
               for (int xi = -1; xi <= 1; xi++)
               {
                  if ( pInGrid->GetValue(x + xi, y + yi) >= pInGrid->GetValue( x, y))
                  {
                     ttmpValue += (double((pInGrid->GetValue(x + xi, y + yi) * weightMask[positionCounter])));
                  }
                  positionCounter++;
               }
            }
            pOutGrid->SetValue(x, y, ttmpValue);
         }
      }
   }
   delete pExpandedImage;
   Image* pOutImage = ImageTools::CropBorder( pCloneImage, borderSize, borderSize );
   delete pCloneImage;
   std::string outName = pImageIn->GetImageName() + std::string("-LBP");
   pOutImage->SetImageName(outName);
   return pOutImage;
}

//--------------------------------------------------------------------------

}
}

