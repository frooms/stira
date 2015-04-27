
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

#include "WaveletTapGenerator.h"
#include "WaveletTaps.h"
#include <iostream>

namespace stira {
namespace wavelet {

using namespace std;

WaveletTapGenerator::WaveletTapGenerator()
{
}

//------------------------------------------------------------------

WaveletTapGenerator::~WaveletTapGenerator()
{
}

//------------------------------------------------------------------

WaveletFilterSet WaveletTapGenerator::Generate( WaveletType type )
{
   Initialize( type );
   FillInFirstFilterTaps( );
   FillInOtherTaps( );
   return mSet;
}

//------------------------------------------------------------------

void WaveletTapGenerator::FillInFirstFilterTaps( )
{
   int length = mSet.length;
   switch ( mSet.type )
   {
      case DAUBECHIES_1:
      {
         for (int i = 0; i < length; i++)  { mSet.pLowpassForward[i] = Daub1[i]; }
         break;
      }
      case DAUBECHIES_2:
      {
         //Original 
         for (int i = 0; i < length; i++)  { mSet.pLowpassForward[i] = Daub2[i]; }
         
         //NR version
         //length++;
         //mSet.pLowpassForward[0] = 0.0;
         //for (int i = 1; i < length; i++)  { mSet.pLowpassForward[i] = Daub2[length-1-i]; }
         break;
      }
      case DAUBECHIES_4:
      {
         for (int i = 0; i < length; i++)  { mSet.pLowpassForward[i] = Daub4[i]; }
         break;
      }
      case DAUBECHIES_8:
      {
         for (int i = 0; i < length; i++)  { mSet.pLowpassForward[i] = Daub8[i]; }
         break;
      }
      case SYMLET_1:
      {
         for (int i = 0; i < length; i++)  { mSet.pLowpassForward[i] = Sym1[i]; }
         break;
      }
      case SYMLET_2:
      {
         for (int i = 0; i < length; i++)  { mSet.pLowpassForward[i] = Sym2[i]; }
         mSet.length = 4;
         break;
      }
      case SYMLET_4:
      {
         for (int i = 0; i < length; i++)  { mSet.pLowpassForward[i] = Sym4[i]; }
         mSet.length = 8;
         break;
      }
      case SYMLET_8:
      {
         for (int i = 0; i < length; i++)  { mSet.pLowpassForward[i] = Sym8[i]; }
         break;
      }
      case COIFLET_1:
      {
         for (int i = 0; i < length; i++)  { mSet.pLowpassForward[i] = Coif1[i]; }
         break;
      }
      case COIFLET_2:
      {
         for (int i = 0; i < length; i++)  { mSet.pLowpassForward[i] = Coif2[i]; }
         break;
      }
      case COIFLET_3:
      {
         for (int i = 0; i < length; i++)  { mSet.pLowpassForward[i] = Coif3[i]; }
         break;
      }
      case COIFLET_4:
      {
         for (int i = 0; i < length; i++)  { mSet.pLowpassForward[i] = Coif4[i]; }
         break;
      }
      default:
         break;
   }
}

//------------------------------------------------------------------

void WaveletTapGenerator::FillInOtherTaps()
{
   int length = mSet.length;
   for (int i = 0; i < length; i++)  { mSet.pLowpassInvers[i]   = mSet.pLowpassForward[length - i - 1]; }
   for (int i = 0; i < length; i++)  { mSet.pHighpassForward[i] = mSet.pLowpassForward[length - i - 1];    if (i%2 == 0) {mSet.pHighpassForward[i] *= -1.0;} }
   for (int i = 0; i < length; i++)  { mSet.pHighpassInvers[i]  = mSet.pLowpassForward[i];                 if ((length-i-1)%2 == 0) { mSet.pHighpassInvers[i] *= -1.0;} }
}

//------------------------------------------------------------------

void WaveletTapGenerator::Initialize( WaveletType type )
{
   mSet.type = type;
   switch ( type )
   {
      case DAUBECHIES_1:
      {
         mSet.length = 2;
         break;
      }
      case DAUBECHIES_2:
      {
         mSet.length = 4;
         break;
      }
      case DAUBECHIES_4:
      {
         mSet.length = 8;
         break;
      }
      case DAUBECHIES_8:
      {
         mSet.length = 16;
         break;
      }
      case SYMLET_1:
      {
         mSet.length = 2;
         break;
      }
      case SYMLET_2:
      {
         mSet.length = 4;
         break;
      }
      case SYMLET_4:
      {
         mSet.length = 8;
         break;
      }
      case SYMLET_8:
      {
         mSet.length = 16;
         break;
      }
      case COIFLET_1:
      {
         mSet.length = 6;
         break;
      }
      case COIFLET_2:
      {
         mSet.length = 12;
         break;
      }
      case COIFLET_3:
      {
         mSet.length = 18;
         break;
      }
      case COIFLET_4:
      {
         mSet.length = 24;
         break;
      }
      default:
         break;
   }
   mSet.pLowpassForward  = new double[ mSet.length + 1 ];
   mSet.pLowpassInvers   = new double[ mSet.length + 1 ];
   mSet.pHighpassForward = new double[ mSet.length + 1 ];
   mSet.pHighpassInvers  = new double[ mSet.length + 1 ];
}

//------------------------------------------------------------------

}
}
