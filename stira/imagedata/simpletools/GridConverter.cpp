
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

#include "GridConverter.h"

namespace stira {
namespace imagedata {

//-------------------------------------------------------------------------------------

GridConverter::GridConverter()
{
}

//-------------------------------------------------------------------------------------

ArrayGrid<int>* GridConverter::ConvertToInt( ArrayGrid<bool>* pGridIn )
{
   int width  = pGridIn->GetWidth();
   int height = pGridIn->GetHeight();
   ArrayGrid<int>* pGridOut = new ArrayGrid<int>( width, height );
   for ( int y = 0; y < height; y++ )
   {
      for ( int x = 0; x < width; x++ )
      {
         pGridOut->SetValue( x, y, 255 * (int)(pGridIn->GetValue( x, y ) ) );
      }
   }
   return pGridOut;
}

//-------------------------------------------------------------------------------------

ArrayGrid<int>* GridConverter::ConvertToInt( ArrayGrid<double>* pGridIn )
{
   int width  = pGridIn->GetWidth();
   int height = pGridIn->GetHeight();
   ArrayGrid<int>* pGridOut = new ArrayGrid<int>( width, height );
   for ( int y = 0; y < height; y++ )
   {
      for ( int x = 0; x < width; x++ )
      {
         pGridOut->SetValue( x, y, (int)(pGridIn->GetValue( x, y ) + 0.5) );
      }
   }
   return pGridOut;
}

//-------------------------------------------------------------------------------------

ArrayGrid<double>* GridConverter::ConvertToDouble( ArrayGrid<bool>* pGridIn, double factor )
{
   int width  = pGridIn->GetWidth();
   int height = pGridIn->GetHeight();

   ArrayGrid<double>* pGridOut = new ArrayGrid<double>( width, height );
   for ( int y = 0; y < height; y++ )
   {
      for ( int x = 0; x < width; x++ )
      {
         pGridOut->SetValue( x, y, factor * (double)(pGridIn->GetValue( x, y ) ) );
      }
   }
   return pGridOut;
}

//-------------------------------------------------------------------------------------

ArrayGrid<double>* GridConverter::ConvertToDouble( ArrayGrid<int>* pGridIn )
{
   int width  = pGridIn->GetWidth();
   int height = pGridIn->GetHeight();
   ArrayGrid<double>* pGridOut = new ArrayGrid<double>( width, height );
   for ( int y = 0; y < height; y++ )
   {
      for ( int x = 0; x < width; x++ )
      {
         pGridOut->SetValue( x, y, (double)(pGridIn->GetValue( x, y ) ) );
      }
   }
   return pGridOut;
}

//-------------------------------------------------------------------------------------

}
}
