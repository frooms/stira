#include "AdaptiveHistogramEqualizer.h"

#include "HistogramTools.h"
#include "../../common/common/MathUtils.h"
#include "../../filter/filter/GaussConvolve.h"
#include "../../histogram/histogram/IntHistogram.h"
#include "../../histogram/histogram/FloatHistogram.h"
#include "../../image/tools/NumberGridTools.h"

namespace stira {
namespace contrastenhance {

AdaptiveHistogramEqualizer::AdaptiveHistogramEqualizer()
{
}

/*
void AdaptiveHistogramEqualizer::HistogramEqualizeSingleBlock( image::ArrayGrid<double>* pInGrid, int xi, int yi  )
{
   int desiredMax, desiredMin;
   double dataMin, dataMax;
   common::RectangularROI<int> rroi();

   NumberGridTools<double>::GetMinMax( pInGrid, dataMin, dataMax );
   bool useDataMinMax = false;
   IntHistogram* pStdHistogram       = new IntHistogram( pInGrid, useDataMinMax, rroi );
   IntHistogram* pCumulHistogram     = new IntHistogram( pInGrid, useDataMinMax, rroi );
   FloatHistogram *pNormCumulHistogram = new FloatHistogram( pStdHistogram->GetNrOfBins() );

   pCumulHistogram->ConvertInCumulativeHistogram();

   pNormCumulHistogram->InitializeWithNormalizedCumulativeHistogram( pStdHistogram, pCumulHistogram);
   delete pStdHistogram;
   delete pCumulHistogram;

   desiredMax = (int)(dataMax);
   desiredMin = 0;

   for (int y = 0; y < pInGrid->GetHeight(); y++)
   {
      for (int x = 0; x < pInGrid->GetWidth(); x++)
      {
         int binNr = pInGrid->GetValue(x, y) - dataMin;

         double myEqualizedValue = desiredMax * ( pNormCumulHistogram->GetBinValue( 0, binNr ) / ((double)(pNormCumulHistogram->GetNrOfBins())));

         if (myEqualizedValue > static_cast<double>(desiredMax)) {myEqualizedValue = static_cast<double>(desiredMax);}
         if (myEqualizedValue < static_cast<double>(desiredMin)) {myEqualizedValue = static_cast<double>(desiredMin);}

         pInGrid->SetValue(x, y, myEqualizedValue);
      }
   }

   delete pNormCumulHistogram;
}
   */

}
}
