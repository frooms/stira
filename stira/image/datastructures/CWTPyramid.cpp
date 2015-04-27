
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

#include "CWTPyramid.h"

namespace stira {
namespace image {

CWTPyramid::CWTPyramid( ArrayGrid<double>* pSourceBand, int myNrScales) : Pyramid< std::complex< double > >( pSourceBand, myNrScales, 6, true, false)
{
   mpLowPassResidual1 = 0;
   mpLowPassResidual2 = 0;
}

//---------------------------------------------------------------------------

CWTPyramid::~CWTPyramid()
{
   delete mpLowPassResidual1;
   delete mpLowPassResidual2;
}

//---------------------------------------------------------------------------
   
ArrayGrid< std::complex< double > >* CWTPyramid::GetLowPassResidual1()
{
   return mpLowPassResidual1;
}

//---------------------------------------------------------------------------
   
void CWTPyramid::SetLowPassResidual1( ArrayGrid< std::complex< double > >* pBand)
{
   if ( mpLowPassResidual1 != 0 )
   {
      delete mpLowPassResidual1;
   }
   mpLowPassResidual1 = pBand;
}

//---------------------------------------------------------------------------
   
ArrayGrid< std::complex< double > >* CWTPyramid::GetLowPassResidual2()
{
   return mpLowPassResidual2;
}

//---------------------------------------------------------------------------

void CWTPyramid::SetLowPassResidual2(ArrayGrid< std::complex< double > >* pBand)
{
   if ( mpLowPassResidual2 != 0 )
   {
      delete mpLowPassResidual2;
   }
   mpLowPassResidual2 = pBand;
}

//---------------------------------------------------------------------------

void CWTPyramid::ExportBandsToPGM()
{
   Pyramid< std::complex< double > >::ExportBandsToPGM();
   
   if (mpLowPassResidual1 != 0)
   {
      ImageIO::WritePGM( mpLowPassResidual1, std::string("LowpassResidualComplex1.pgm"), ImageIO::NORMAL_OUT);
   }
   
   if (mpLowPassResidual2 != 0)
   {
       ImageIO::WritePGM( mpLowPassResidual2, std::string("LowpassResidualComplex1.pgm"), ImageIO::NORMAL_OUT);
   }
}

//---------------------------------------------------------------------------

}
}
