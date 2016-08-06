
/*****************************************************************************************
 *   Copyright (C) 2010 by Filip Rooms, implementing an idea of prof. Wilfried Philips   *
 *                                                                                       *
 *  Terms and conditions for using this software in any form are provided in the         *
 *  file COPYING, which can be found in the root directory of this project.              *
 *                                                                                       *
 *   Contact data: filip.rooms@gmail.com                                                 *
 *                 http://www.filiprooms.be/                                             *
 *                                                                                       *
 *****************************************************************************************/

#include "ContourTracing.h"
#include "../../common/common/StringUtils.h"
#include "../../imagetools/tools/ImageIO.h"
#include <iostream>

//#define CREATE_OUTPUTS

using namespace std;
using namespace stira::common;

namespace stira {
namespace imageanalysis {

ContourTracing::ContourTracing( double alphaStraight, double alphaNotStraight, std::string filePath )
{
   mAlphaStraight = alphaStraight;
   mOneMinusAlphaStraight = 1.0 - mAlphaStraight;

   mAlphaNotStraight = alphaNotStraight;
   mOneMinusAlphaNotStraight = 1.0 - mAlphaNotStraight;
   mFilePath = filePath;
}

//-----------------------------------------------------------------------------

ContourTracing::~ContourTracing( )
{
}

//-----------------------------------------------------------------------------

ArrayGrid<double>* ContourTracing::RunLeftRight( ArrayGrid<double>* pGridIn, int /*ID*/ )
{
   ArrayGrid<double>* pGridOut = pGridIn->Clone();

#ifdef CREATE_OUTPUT
   std::string fileNameIn = StringUtils::ConstructPathAndFileName( mFilePath, std::string("CCInput-"), ID, std::string(".pgm") );
   ImageIO::WritePGM( pGridOut, fileNameIn, ImageIO::NORMAL_OUT );
#endif

   ArrayGrid<double>* pGridTmp = new ArrayGrid<double>( pGridIn->GetWidth(), pGridIn->GetHeight() );  // all values are initialized by default to 0
   ForwardPropagateLeft( pGridIn, pGridOut, pGridTmp );

#ifdef CREATE_OUTPUTS
   std::string fileNameForwardLeft = StringUtils::ConstructPathAndFileName( mFilePath, std::string("CCForwardLeft-"), ID, std::string(".pgm") );
   ImageIO::WritePGM( pGridOut, fileNameForwardLeft, ImageIO::NORMAL_OUT );
   //cerr << "Creating contour tracing output " << fileNameForwardLeft << endl << flush;
#endif

   BackwardRecoverRight( pGridOut, pGridTmp );

#ifdef CREATE_OUTPUTS
   std::string fileNameBackwardRight = StringUtils::ConstructPathAndFileName( mFilePath, std::string("CCBackwardRight-"), ID, std::string(".pgm") );
   ImageIO::WritePGM( pGridOut, fileNameBackwardRight, ImageIO::NORMAL_OUT );
   //cerr << "Creating contour tracing output " << fileNameBackwardRight << endl << flush;
#endif

   delete pGridTmp;
   return pGridOut;
}

//-----------------------------------------------------------------------------

ArrayGrid<double>* ContourTracing::RunRightLeft( ArrayGrid<double>* pGridIn, int /*ID*/ )
{
   ArrayGrid<double>* pGridOut = pGridIn->Clone();

#ifdef CREATE_OUTPUTS
   std::string fileNameIn = StringUtils::ConstructPathAndFileName( mFilePath, std::string("CCInput-"), ID, std::string(".pgm") );
   ImageIO::WritePGM( pGridOut, fileNameIn, ImageIO::NORMAL_OUT );
#endif

   ArrayGrid<double>* pGridTmp = new ArrayGrid<double>( pGridIn->GetWidth(), pGridIn->GetHeight(), true, 0 );  // all values are initialized by default to 0
   ForwardPropagateRight( pGridIn, pGridOut, pGridTmp );

#ifdef CREATE_OUTPUTS
   std::string fileNameForwardRight = StringUtils::ConstructPathAndFileName( mFilePath, std::string("CCForwardRight-"), ID, std::string(".pgm") );
   ImageIO::WritePGM( pGridOut, fileNameForwardRight, ImageIO::NORMAL_OUT );
#endif

   BackwardRecoverLeft( pGridOut, pGridTmp );

#ifdef CREATE_OUTPUTS
   std::string fileNameBackwardLeft = StringUtils::ConstructPathAndFileName( mFilePath, std::string("CCBackwardLeft-"), ID, std::string(".pgm") );
   ImageIO::WritePGM( pGridOut, fileNameBackwardLeft, ImageIO::NORMAL_OUT );
#endif

   delete pGridTmp;
   return pGridOut;
}

//-----------------------------------------------------------------------------

std::pair< ArrayGrid<double>*, ArrayGrid<double>* > ContourTracing::Run( ArrayGrid<double>* pGridIn, int ID )
{
   ArrayGrid<double>* pGridOutLeft  = RunLeftRight( pGridIn, ID );
   ArrayGrid<double>* pGridOutRight = RunRightLeft( pGridIn, ID );

   std::pair< ArrayGrid<double>*, ArrayGrid<double>* > pairLR_RL;
   pairLR_RL.first  = pGridOutLeft;
   pairLR_RL.second = pGridOutRight;
   return pairLR_RL;
}

//-----------------------------------------------------------------------------

void ContourTracing::ForwardPropagateRight( ArrayGrid<double>* pGridIn, ArrayGrid<double>* pGridOut, ArrayGrid<double>* pGridTmp )
{
   int width = pGridOut->GetWidth();
   int height = pGridOut->GetHeight();
   for ( int x = 1; x < width; x++ )
   {
      for ( int y = 1; y < height - 1; y++ )
      {
         int dY=0;
         double newValue;
         double mmax = pGridOut->GetValue( x-1, y );
         for (int dy = -1; dy <=1; dy++)
         {
            if ( pGridOut->GetValue( x-1, y+dy ) > mmax )
            {
               mmax = pGridOut->GetValue( x-1, y+dy );
               dY = dy;
            }
         }

         if (dY == 0)
         {
            newValue = ( mAlphaStraight * mmax + mOneMinusAlphaStraight * pGridIn->GetValue( x, y ) );
         }
         else
         {
            newValue = ( mAlphaNotStraight * mmax + mOneMinusAlphaNotStraight * pGridIn->GetValue( x, y ) );
         }
         pGridTmp->SetValue(x, y, dY );
         pGridOut->SetValue(x, y, newValue );
      }
   }
}

//-----------------------------------------------------------------------------

void ContourTracing::BackwardRecoverLeft( ArrayGrid<double>* pGridOut, ArrayGrid<double>* pGridTmp )
{
   int width = pGridOut->GetWidth();
   int height = pGridOut->GetHeight();
   for ( int x = width - 1; x > 0; x-- )
   {
      for ( int y = 0; y < height; y++ )
      {
         pGridOut->MultiplyValue( x-1, y, mOneMinusAlphaStraight );
      }
      for ( int y = 1; y < height - 1; y++ )
      {
         double myValue = mAlphaStraight * pGridOut->GetValue( x, y );
         int dY = pGridTmp->GetValue( x, y );
         pGridOut->AddValue( x-1, y+dY, myValue);
      }
   }
}

//-----------------------------------------------------------------------------

void ContourTracing::ForwardPropagateLeft( ArrayGrid<double>* pGridIn, ArrayGrid<double>* pGridOut, ArrayGrid<double>* pGridTmp )
{
   int width = pGridOut->GetWidth();
   int height = pGridOut->GetHeight();
   for ( int x = width - 2; x > 0; x-- )
   {
      for ( int y = 1; y < height - 1; y++ )
      {
         int dY=0;
         double newValue;
         double mmax = pGridOut->GetValue( x+1, y );
         for (int dy = -1; dy <=1; dy++)
         {
            if ( pGridOut->GetValue( x+1, y+dy ) > mmax )
            {
               mmax = pGridOut->GetValue( x+1, y+dy );
               dY = dy;
            }
         }

         if (dY == 0)
         {
            newValue = ( mAlphaStraight * mmax + mOneMinusAlphaStraight * pGridIn->GetValue( x, y ) );
         }
         else
         {
            newValue = ( mAlphaNotStraight * mmax + mOneMinusAlphaNotStraight * pGridIn->GetValue( x, y ) );
         }

         pGridTmp->SetValue(x, y, dY );
         pGridOut->SetValue(x, y, newValue );
      }
   }
}

//-----------------------------------------------------------------------------

void ContourTracing::BackwardRecoverRight( ArrayGrid<double>* pGridOut, ArrayGrid<double>* pGridTmp )
{
   int width = pGridOut->GetWidth();
   int height = pGridOut->GetHeight();
   for ( int x = 1; x < width - 1; x++ )
   {
      for ( int y = 0; y < height; y++ )
      {
         pGridOut->MultiplyValue( x+1, y, mOneMinusAlphaStraight );
      }
      for ( int y = 1; y < height - 1; y++ )
      {
         double myValue = mAlphaStraight * pGridOut->GetValue( x, y );
         int dY = pGridTmp->GetValue( x, y );
         pGridOut->AddValue( x+1, y+dY, myValue);
      }
   }
}

//-----------------------------------------------------------------------------

}
}
