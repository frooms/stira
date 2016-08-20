
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

#include "../../common/common/MathUtils.h"
#include "FloatHistogram.h"

//#define DEBUG

using namespace std;

namespace stira {
namespace histogram {

using namespace common;
using namespace imagedata;

FloatHistogram::FloatHistogram( int nrOfBins, int nrBands )
{
   mEpsilonThreshold = 0.0000000000001;  // arbitrary tiny constant to avoid taking log of zero values
   mNrOfBins = nrOfBins;
   mNrOfBands = nrBands;

   CreateInitializedDataStructure( );
}

//---------------------------------------------------------------------------------------

FloatHistogram::~FloatHistogram()
{
}

//---------------------------------------------------------------------------------------

FloatHistogram* FloatHistogram::Clone()
{
   return new FloatHistogram(*this);
}

//---------------------------------------------------------------------------------------

void FloatHistogram::SetEpsilonThreshold( double epsilonValue )
{
   mEpsilonThreshold = epsilonValue;
}

//---------------------------------------------------------------------------------------

double FloatHistogram::GetEpsilonThreshold( )
{
   return mEpsilonThreshold;
}

//---------------------------------------------------------------------------------------

FloatHistogram::FloatHistogram( IntHistogram* pOther, bool requiresNormalization)
{
   mNrOfBins =  pOther->GetNrOfBins();
   mNrOfBands = pOther->GetNrOfBands();

   CreateInitializedDataStructure( );
   if (requiresNormalization)
   {
      InitializeWithNormalizedHistogram( pOther );
   }
   else  // just copy the histogram values casted as doubles
   {
      for (int band = 0; band < mNrOfBands; band++)
      {
         for (int bin = 0; bin < mNrOfBins; bin++)
         {
            SetBinValue( band, bin, (double)( pOther->GetBinValue( band, bin ) ) );
         }
      }
   }
}

//---------------------------------------------------------------------------------------

bool FloatHistogram::UpdateHistogram( IntHistogram* pIntHistogram, double alpha )
{
   for (int band = 0; band < mNrOfBands; band++)
   {
      for (int bin = 0; bin < mNrOfBins; bin++)
      {
         double newbinValue =           alpha  * (double)(pIntHistogram->GetBinValue( band, bin ))
                               + (1.0 - alpha) * this->GetBinValue( band, bin );

         SetBinValue( band, bin, newbinValue );
      }
   }
   return 0;
}

//---------------------------------------------------------------------------------------

void FloatHistogram::InitializeWithNormalizedHistogram( IntHistogram* pStandardHistogram )
{
   double myDenominator = double( pStandardHistogram->GetNrOfCounts( ) );

   for (int band = 0; band < mNrOfBands; band++)
   {
      for (int bin = 0; bin < mNrOfBins; bin++)
      {
         SetBinValue( band, bin, pStandardHistogram->GetBinValue( band, bin ) / myDenominator );
      }
   }
}

//---------------------------------------------------------------------------------------

void FloatHistogram::InitializeWithNormalizedCumulativeHistogram( IntHistogram* pStandardHistogram, IntHistogram* pCumulativeHistogram )
{
   double myNumerator, myDenominator;

   for (int band = 0; band < mNrOfBands; band++)
   {
      SetBinValue( band, 0, 0.0);

      myDenominator =   ( double( pStandardHistogram->GetNrOfCounts( ) ) )
                      - ( double( pStandardHistogram->GetBinValue( band, ( mNrOfBins - 1 ) ) ) );

      for (int bin = 1; bin < mNrOfBins; bin++)
      {
         myNumerator = ( double( mNrOfBins - 1 ) ) * ( double ( pCumulativeHistogram->GetBinValue( band, bin - 1 ) ) );
         SetBinValue( band, bin, myNumerator / myDenominator );
      }
   }
}

//---------------------------------------------------------------------------------------

void FloatHistogram::Normalize( )
{
   for (int band = 0; band < mNrOfBands; band++)
   {
      double bandTotal = 0.0;

      for (int bin = 0; bin < mNrOfBins; bin++)
      {
         bandTotal += GetBinValue( band, bin );
      }

      for (int bin = 0; bin < mNrOfBins; bin++)
      {
         SetBinValue( band, bin, GetBinValue( band, bin ) / bandTotal );
      }
   }
}

//---------------------------------------------------------------------------------------

bool FloatHistogram::Write( std::string fileName)
{
   ofstream ofp;
   ofp.open(const_cast<char*>(fileName.c_str()), ios::out | ios::binary);

   if (!ofp)
   {
      cout << "Can't open file: " << fileName << " for writing" << endl;
      return false;
   }

   for (int bandNr = 0; bandNr < mNrOfBands; bandNr++)
   {
      for (int binNr = 0; binNr < mNrOfBins; binNr++)
      {
         ofp << binNr << "\t" << GetBinValue( bandNr, binNr ) << endl;
      }
   }

   if (ofp.fail())
   {
      cout << "Couldn't write file " << fileName << endl;
      return false;
   }

   ofp.close();
   return true;
}

//---------------------------------------------------------------------------------------

double FloatHistogram::ComputeEntropy( )
{
   double tmpValue = 0.0;
   // actually compute entropy
   for (int bandNr = 0; bandNr < mNrOfBands; bandNr++)
   {
      for (int binNr = 0; binNr < mNrOfBins; binNr++)
      {
         if ( this->GetBinValue( bandNr, binNr ) > 0.0 )
         {
            tmpValue -= ( this->GetBinValue( bandNr, binNr ) * log( this->GetBinValue( bandNr, binNr) ) );
         }
      }
   }
   return tmpValue;
}

//---------------------------------------------------------------------------------------

double FloatHistogram::ComputeStandardKullbackLeiblerDistance( FloatHistogram* pOtherHistogram )
{
   if( ( pOtherHistogram->GetNrOfBands() != this->mNrOfBands ) || ( this->mNrOfBins != pOtherHistogram->GetNrOfBins() ) )
   {
      cerr << "ERROR: not possible to compute the KL distance for histogram with different nr of bands or bins!!!" << endl << flush;
      return -1;
   }
   else
   {
      double tmpValue = 0.0;
      for (int bandNr = 0; bandNr < mNrOfBands; bandNr++)
      {
         for (int binNr = 0; binNr < mNrOfBins; binNr++)
         {
            double thisBinValue  =            this->GetBinValue( bandNr, binNr );
            double otherBinValue = pOtherHistogram->GetBinValue( bandNr, binNr );
            if ( thisBinValue  <= 0.0 ) { thisBinValue  = mEpsilonThreshold; }
            if ( otherBinValue <= 0.0 ) { otherBinValue = mEpsilonThreshold; }

            double tmpLocalValue = thisBinValue * log( thisBinValue / otherBinValue );

            tmpValue += tmpLocalValue;
         }
      }
      return tmpValue;
   }
}

//---------------------------------------------------------------------------------------

double FloatHistogram::ComputeSymmetricKullbackLeiblerDistance( FloatHistogram* pOtherHistogram )
{
   if( ( pOtherHistogram->GetNrOfBands() != this->mNrOfBands ) || ( this->mNrOfBins != pOtherHistogram->GetNrOfBins() ) )
   {
      cerr << "ERROR: not possible to compute the KL distance for histogram with different nr of bands or bins!!!" << endl << flush;
      return -1;
   }
   else
   {
      double tmpValue1 = 0.0;
      double tmpValue2 = 0.0;
      double tmpValue3 = 0.0;
      for (int bandNr = 0; bandNr < mNrOfBands; bandNr++)
      {
         for (int binNr = 0; binNr < mNrOfBins; binNr++)
         {
            double binValue1 =            this->GetBinValue( bandNr, binNr );
            double binValue2 = pOtherHistogram->GetBinValue( bandNr, binNr );
            double binValue3 = binValue1 + binValue2;

            if ( binValue1 < mEpsilonThreshold ) { binValue1 = mEpsilonThreshold; }
            if ( binValue2 < mEpsilonThreshold ) { binValue2 = mEpsilonThreshold; }
            if ( binValue3 < mEpsilonThreshold ) { binValue3 = mEpsilonThreshold; }

            tmpValue1 += ( binValue1 * log( binValue1 ) );
            tmpValue2 += ( binValue2 * log( binValue2 ) );
            tmpValue3 += ( binValue3 * log( binValue3 ) );
         }
      }
      return ( tmpValue1 + tmpValue2 - tmpValue3 + 2.0 * log( 2.0 ) );
   }
}

//---------------------------------------------------------------------------------------

double FloatHistogram::ComputeJensenShannonMetric( FloatHistogram* pOtherHistogram )
{
   FloatHistogram* pSumHistogram = this->Clone();

   for (int bandNr = 0; bandNr < mNrOfBands; bandNr++)
   {
      for (int binNr = 0; binNr < mNrOfBins; binNr++)
      {
         double myValue = 0.5 * ( this->GetBinValue( bandNr, binNr ) + pOtherHistogram->GetBinValue( bandNr, binNr ) );
         pSumHistogram->SetBinValue( bandNr, binNr, myValue );
      }
   }
   double value1 = ComputeStandardKullbackLeiblerDistance( pSumHistogram );
   double value2 = pOtherHistogram->ComputeStandardKullbackLeiblerDistance( pSumHistogram );
   delete pSumHistogram;
   return ( sqrt( 0.5 * ( value1 + value2) ) );
}


//---------------------------------------------------------------------------------------

double FloatHistogram::ComputeIDivergence( FloatHistogram* pOtherHistogram )
{
   if( ( pOtherHistogram->GetNrOfBands() != this->mNrOfBands ) || ( this->mNrOfBins != pOtherHistogram->GetNrOfBins() ) )
   {
      cerr << "ERROR: not possible to compute the I-Divergence for histogram with different nr of bands or bins!!!" << endl << flush;
      return -1;
   }
   else
   {
      double tmpValue = 0.0;
      for (int bandNr = 0; bandNr < mNrOfBands; bandNr++)
      {
         for (int binNr = 0; binNr < mNrOfBins; binNr++)
         {
            tmpValue += ( (   this->GetBinValue( bandNr, binNr )
                            * log( this->GetBinValue( bandNr, binNr) / pOtherHistogram->GetBinValue( bandNr, binNr) )
                          )
                          - this->GetBinValue( bandNr, binNr )
                          + pOtherHistogram->GetBinValue( bandNr, binNr)
                        );
         }
      }
      return tmpValue;
   }
}

//---------------------------------------------------------------------------------------

} // end namespace preprocesstools
} // end namespace incgeo
