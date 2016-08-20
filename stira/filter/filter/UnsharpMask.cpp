
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

#include "UnsharpMask.h"
#include "GaussConvolve.h"
namespace stira {
namespace filter {

UnsharpMask::UnsharpMask() { }

//------------------------------------------------------------------------------------------

UnsharpMask::~UnsharpMask() { }

//------------------------------------------------------------------------------------------

Image* UnsharpMask::Run( Image* pImageIn, double sigma, double factor )
{
   int nrBands = pImageIn->GetNumberOfBands();
   Image* pImageOut = pImageIn->Clone();
   
   for (int bandID = 0; bandID < nrBands; bandID++)
   {
      ArrayGrid<double>* pGridX = GaussConvolve::DerivativeConvolveFFT(pImageIn->GetBands()[bandID], sigma, sigma, GaussConvolve::DERIVATIVE_X);
      ArrayGrid<double>* pGridY = GaussConvolve::DerivativeConvolveFFT(pImageIn->GetBands()[bandID], sigma, sigma, GaussConvolve::DERIVATIVE_Y);
      ArrayGrid<double>* pGridXX = GaussConvolve::DerivativeConvolveFFT(pImageIn->GetBands()[bandID], sigma, sigma, GaussConvolve::DERIVATIVE_XX);
      ArrayGrid<double>* pGridYY = GaussConvolve::DerivativeConvolveFFT(pImageIn->GetBands()[bandID], sigma, sigma, GaussConvolve::DERIVATIVE_YY);
      ArrayGrid<double>* pGridXY = GaussConvolve::DerivativeConvolveFFT(pImageIn->GetBands()[bandID], sigma, sigma, GaussConvolve::DERIVATIVE_XY);
      pGridX->MultiplyWith( factor );
      pGridY->MultiplyWith( factor );
      pGridXX->MultiplyWith( -1.5 * factor );
      pGridYY->MultiplyWith( -1.5 * factor );
      pGridXY->MultiplyWith( -1.5 * factor );
      
      pGridX-> MultiplyWith( factor );
      
      *( pImageOut->GetBands()[bandID] ) += *pGridX ;
      *( pImageOut->GetBands()[bandID] ) += *pGridY ;
      *( pImageOut->GetBands()[bandID] ) += *pGridXX ;
      *( pImageOut->GetBands()[bandID] ) += *pGridYY ;
      *( pImageOut->GetBands()[bandID] ) += *pGridXY ;
      delete pGridX;
      delete pGridY;
      delete pGridXX;
      delete pGridYY;
      delete pGridXY;
   }
      
   std::string outName = pImageIn->GetImageName() + std::string("-UnsharpMask");
   pImageOut->SetImageName(outName);
   return pImageOut;
}

//------------------------------------------------------------------------------------------

}

}
