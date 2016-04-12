
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

#include "ShowHistogramDialog.h"
#include "../../stira/histogram/histogram/IntHistogram.h"

using namespace std;
using namespace stira::histogram;
using namespace stira::image;

ShowHistogramDialog::ShowHistogramDialog( Image* pImage ) : CurvePlotDialog( QString("Histogram") )
{
   GetData( pImage );
   PlotData( );
}

//--------------------------------------------------------

ShowHistogramDialog::~ShowHistogramDialog()
{
}

//--------------------------------------------------------

void ShowHistogramDialog::GetData( Image* pImage )
{
   IntHistogram myIntHistogram( pImage, true );


   
   mNrOfDataPoints = myIntHistogram.GetNrOfBins();
   mNrOfBands = myIntHistogram.GetNrOfBands();
   
   double binSize = myIntHistogram.GetBinSize();
   double dataMin = myIntHistogram.GetDataMinimum();
   mpX  = new double[  mNrOfDataPoints  ];
   mppY = new double*[ mNrOfBands ];
   
   for (int bandNr = 0; bandNr < mNrOfBands; bandNr++)
   {
      mppY[bandNr] = new double[ mNrOfDataPoints ];
   }
   
   for (int binNr = 0; binNr < mNrOfDataPoints; binNr++)
   {
      mpX[binNr] = ((double)(binNr) + dataMin) * binSize;
      for (int bandNr = 0; bandNr < mNrOfBands; bandNr++)
      {
         mppY[bandNr][binNr] = myIntHistogram.GetBinValue( bandNr, binNr );
      }
   }
   
   for (int bandNr = 0; bandNr < mNrOfBands; bandNr++)
   {
      mppY[bandNr][0] = 0;
      mppY[bandNr][mNrOfDataPoints-1] = 0;
   }
}

//--------------------------------------------------------
