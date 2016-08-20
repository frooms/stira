
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

#include "../../stira/fouriertools/fouriertools/FFT.h"

#include "ShowRadiallyAveragedFourierSpectrumDialog.h"

using namespace std;
using namespace stira::fouriertools;

ShowRadiallyAveragedFourierSpectrumDialog::ShowRadiallyAveragedFourierSpectrumDialog( Image* pImage ) : CurvePlotDialog( QString("Radially Averaged Log-power spectrum") )
{
   GetData( pImage );
   PlotData( );
}

//--------------------------------------------------------

ShowRadiallyAveragedFourierSpectrumDialog::~ShowRadiallyAveragedFourierSpectrumDialog()
{
}

//--------------------------------------------------------

void ShowRadiallyAveragedFourierSpectrumDialog::GetData( Image* pImage )
{
   mNrOfBands = pImage->GetNumberOfBands();
   mppY = new double*[ mNrOfBands ];
   vector<double> averagedSpectrum = FFT::ComputeRadiallyAveragedSpectrum( pImage->GetBands()[0] );
   
   mNrOfDataPoints = averagedSpectrum.size();
   mpX  = new double[  mNrOfDataPoints  ];
   mppY[0] = new double[ mNrOfDataPoints ];
   for (int binNr = 0; binNr < mNrOfDataPoints; binNr++)
   {
      mpX[binNr] = binNr;
      mppY[0][binNr] = log10( averagedSpectrum[ binNr ] );
   }
   
   for (int bandNr = 1; bandNr < mNrOfBands; bandNr++)
   {
      mppY[bandNr] = new double[ mNrOfDataPoints ];
      vector<double> averagedSpectrum = FFT::ComputeRadiallyAveragedSpectrum( pImage->GetBands()[bandNr] );
      for (int binNr = 0; binNr < mNrOfDataPoints; binNr++)
      {
         mppY[bandNr][binNr] = log10( averagedSpectrum[ binNr ] );
      }
   }
}

//--------------------------------------------------------
