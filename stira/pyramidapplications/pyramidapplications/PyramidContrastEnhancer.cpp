
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

#include <vector>
#include "../../steerable/pyramid/PyramidReal.h"

#include "PyramidContrastEnhancer.h"
#include "../../imagedata/simpletools/GridStatistics.h"

namespace stira {
namespace pyramidapplications {

using namespace std;
using namespace steerable;
   
PyramidContrastEnhancer::PyramidContrastEnhancer( double sigma )
{
   mSigmaNoise = sigma;
   mNonLinearityDegree = 0.5;
   mNoiseThresholdFactor = 1.0;
   mUpperLimitAmplificationFactor = 0.85;
   mDynamicRangeCompressionFactor = 0.0;
   mNoiseThreshold = mSigmaNoise * mNoiseThresholdFactor;
}

//------------------------------------------------------------------------------

PyramidContrastEnhancer::~PyramidContrastEnhancer()
{
}

//------------------------------------------------------------------------------

double PyramidContrastEnhancer::GetSigmaNoise()
{
   return mSigmaNoise;
}

//------------------------------------------------------------------------------

void PyramidContrastEnhancer::SetSigmaNoise( double sigma )
{
   mSigmaNoise = sigma;
}

//------------------------------------------------------------------------------

double PyramidContrastEnhancer::GetNoiseThresholdFactor()
{
   return mNoiseThresholdFactor;
}

//------------------------------------------------------------------------------

void PyramidContrastEnhancer::SetNoiseThresholdFactor( double factor )
{
   mNoiseThresholdFactor = factor;
}

//------------------------------------------------------------------------------;

double PyramidContrastEnhancer::GetNoiseThreshold()
{
   return mNoiseThreshold;
}

//------------------------------------------------------------------------------;

void PyramidContrastEnhancer::SetNoiseThreshold( double threshold )
{
   mNoiseThreshold = threshold;
}

//------------------------------------------------------------------------------;

double PyramidContrastEnhancer::GetNonLinearityDegree()
{
   return mNonLinearityDegree;
}

//------------------------------------------------------------------------------;

void PyramidContrastEnhancer::SetNonLinearityDegree(double degree)
{
   mNonLinearityDegree = degree;
}

//------------------------------------------------------------------------------;

double PyramidContrastEnhancer::GetUpperLimitAmplificationFactor()
{
   return mUpperLimitAmplificationFactor;
}

//------------------------------------------------------------------------------;

void PyramidContrastEnhancer::SetUpperLimitAmplificationFactor( double limit )
{
   mUpperLimitAmplificationFactor = limit;
}

//------------------------------------------------------------------------------

double PyramidContrastEnhancer::GetDynamicRangeCompressionFactor()
{
   return mDynamicRangeCompressionFactor;
}

//------------------------------------------------------------------------------

void PyramidContrastEnhancer::SetDynamicRangeCompressionFactor( double factor )
{
   mDynamicRangeCompressionFactor = factor;
}

//------------------------------------------------------------------------------

double PyramidContrastEnhancer::GetUpperLimitAmplification()
{
   return mUpperLimitAmplification;
}

//------------------------------------------------------------------------------

void PyramidContrastEnhancer::SetUpperLimitAmplification( double limit )
{
   mUpperLimitAmplification = limit;
}

//------------------------------------------------------------------------------

bool PyramidContrastEnhancer::TestAmplificationfactor( std::string fileName, double myMin, double myMax, double stepSize )
{
   ofstream ofp;
   ofp.open(const_cast<char*>(fileName.c_str()), ios::out);

   if (!ofp) 
   {
      cerr << "Can't open file: " << fileName << endl;
      return false;
   }
   // convert the integer values to unsigned char
   for (double myCoefficient = myMin; myCoefficient < myMax; myCoefficient += stepSize )
   {
      ofp << myCoefficient << std::string("\t") << GetCoefficientMultiplierCurvelet( myCoefficient ) 
                           << std::string("\t") << GetCoefficientMultiplierWavelet( myCoefficient )
                           << endl;
   }

   ofp.close();
   return true;
}

//------------------------------------------------------------------------------

void PyramidContrastEnhancer::PrintParameters()
{
   cout << " Sigma Noise                   = " << mSigmaNoise                    << endl
        << " Noise Threshold Factor        = " << mNoiseThresholdFactor          << endl
        << " Noise Threshold               = " << mNoiseThreshold                << endl
        << " NonLinearityDegree            = " << mNonLinearityDegree            << endl
        << " UpperLimitAmplificationFactor = " << mUpperLimitAmplificationFactor << endl
        << " DynamicRangeCompressionFactor = " << mDynamicRangeCompressionFactor << endl
        << " UpperLimitAmplification       = " << mUpperLimitAmplification       << endl << flush;
}

//------------------------------------------------------------------------------

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NOTATIONS:
//----------------------------+------------------------------------------------------------------------------
//   paper                    |    code                            |  values
//----------------------------+------------------------------------------------------------------------------
//    c                       |   mNoiseThresholdFactor            | around 3
//    c * sigma ( of noise)   |   mNoiseThreshold                  |
//    m                       |   mUpperLimitAmplification         | K * sigma, or L * max coeff. in band
//    p                       |   mNonLinearityDegree              | suggested 0.5
//    s                       |   mDynamicRangeCompressionFactor   | neutral: s = 0; compressed range e.g. 0.6
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

double PyramidContrastEnhancer::GetCoefficientMultiplierCurvelet( double x )
{
   double myFactor;
   double absX = fabs( x );
   if ( absX < mNoiseThreshold )
   {
      myFactor = 1.0;
   }
   else if ( absX < 2.0 * mNoiseThreshold )
   {
      myFactor = ( (( absX - mNoiseThreshold) / (mNoiseThreshold)) * pow( ( mUpperLimitAmplification / mNoiseThreshold ), mNonLinearityDegree) + ((2.0 * mNoiseThreshold - absX) / mNoiseThreshold ) );
   }
   else if ( absX < mUpperLimitAmplification) 
   {
      myFactor = pow( ( mUpperLimitAmplification / absX ), mNonLinearityDegree);
   }
   else
   {
      myFactor = pow( ( mUpperLimitAmplification / absX ), mDynamicRangeCompressionFactor);
   }
   
   return myFactor;
}

//------------------------------------------------------------------------------

double PyramidContrastEnhancer::GetCoefficientMultiplierWavelet(double x )
{
   double m = 30.0; 
   double c = 3.0;
   double p = 0.5;
   
   double myFactor;
   double absX = fabs( x );
   
   if ( absX < c) 
   {
      myFactor = pow( ( m / c), p );
   }
   else if ( absX < m )
   {
      myFactor = pow( ( m / absX ), p );
   }
   else
   {
      myFactor = 1.0;
   }
   
   return myFactor;
}

//------------------------------------------------------------------------------

bool PyramidContrastEnhancer::ContrastEnhanceSingleBand( image::ArrayGrid<double>* pBand, bool applyWavelet )
{
   int width  = pBand->GetWidth();
   int height = pBand->GetHeight();
   
   double bandMax = image::GridStatistics<double>::GetAbsMax( pBand );
   
   mUpperLimitAmplification = bandMax * mUpperLimitAmplificationFactor;
   
   if (applyWavelet)
   {
      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x++)
         {
             pBand->MultiplyValue( x, y, GetCoefficientMultiplierWavelet( pBand->GetValue(x, y) ) );
         }
      }
   }
   else
   {
      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x++)
         {
            pBand->MultiplyValue( x, y, GetCoefficientMultiplierCurvelet( pBand->GetValue(x, y) ) );
         }
      }
   }
   return true;
}

//------------------------------------------------------------------------------

void PyramidContrastEnhancer::RunPyramid( image::Pyramid<double>* pPyramid, bool applyWavelet )
{
   int nrScales = pPyramid->GetNumberOfScales();
   int nrOrientations = pPyramid->GetNumberOfOrientations();
   
   for (int scaleNr = 0; scaleNr < nrScales; scaleNr++)
   {
      for (int orientationNr = 0; orientationNr < nrOrientations; orientationNr++)
      {
         ContrastEnhanceSingleBand( pPyramid->GetRecursiveScale( scaleNr )->GetOrientedBand( orientationNr ), applyWavelet );
      }
   }
   if ( pPyramid->GetResidualScale() != 0 )
   {
      for (int orientationNr = 0; orientationNr < nrOrientations; orientationNr++)
      {
         ContrastEnhanceSingleBand( pPyramid->GetResidualScale()->GetOrientedBand( orientationNr ), applyWavelet );
      }
   }
}

//------------------------------------------------------------------------------

image::Image* PyramidContrastEnhancer::Run( image::Image* pImage, int nrScales, int nrOrientations, bool applyWavelet )
{
   if ( (pImage != 0) && (pImage->GetNumberOfBands() > 0))
   {
      int nrbands = pImage->GetNumberOfBands();
         
      image::Image* pFilteredImage = new image::Image( pImage->GetWidth(), pImage->GetHeight() );
      for (int bandNr = 0; bandNr < nrbands; bandNr++)
      {
         PyramidReal np( pImage->GetBands()[bandNr], nrScales, nrOrientations);  np.Decompose();
         
         RunPyramid( np.GetPyramid(), applyWavelet );
         np.Reconstruct(); 
         pFilteredImage->AddBand( np.GetCopyOfReconstructedGrid() );
      }
      return pFilteredImage;
   }
   else
   {
      cerr << "Invalid input for pyramid contrast enhancement" << endl << flush;
      return 0;
   }
}


//------------------------------------------------------------------------------

bool PyramidContrastEnhancer::ContrastEnhanceSingleBand3Colors( image::ArrayGrid<double>* pBandColor1,                   
                                                                image::ArrayGrid<double>* pBandColor2, image::ArrayGrid<double>* pBandColor3, bool applyWavelet )
{
   int width  = pBandColor1->GetWidth();
   int height = pBandColor1->GetHeight();
   
   if (applyWavelet)  // Test which of both different contrast enhancement methods to apply
   {
      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x++)
         {
            double myMagnitude = sqrt(   (pBandColor1->GetValue(x, y) * pBandColor1->GetValue(x, y) ) 
                                       + (pBandColor2->GetValue(x, y) * pBandColor2->GetValue(x, y) ) 
                                       + (pBandColor3->GetValue(x, y) * pBandColor3->GetValue(x, y) ) 
                                     );
            // implementation difference is in the inner loop -> split test to avoid testing for every coefficient
            double coefficientMultiplier = GetCoefficientMultiplierWavelet( myMagnitude );
            
            pBandColor1->MultiplyValue( x, y, coefficientMultiplier );
            pBandColor2->MultiplyValue( x, y, coefficientMultiplier );
            pBandColor3->MultiplyValue( x, y, coefficientMultiplier );
         }
      }
   }
   else
   {
      double bandMax1 = image::GridStatistics<double>::GetAbsMax( pBandColor1 );
      double bandMax2 = image::GridStatistics<double>::GetAbsMax( pBandColor2 );
      double bandMax3 = image::GridStatistics<double>::GetAbsMax( pBandColor3 );
   
      mUpperLimitAmplification = ( bandMax1 + bandMax2 + bandMax3) * mUpperLimitAmplificationFactor / 3.0;
      
      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x++)
         {
            double myMagnitude = sqrt(   (pBandColor1->GetValue(x, y) * pBandColor1->GetValue(x, y) ) 
                                       + (pBandColor2->GetValue(x, y) * pBandColor2->GetValue(x, y) ) 
                                       + (pBandColor3->GetValue(x, y) * pBandColor3->GetValue(x, y) ) 
                                     );
            // implementation difference is in the inner loop -> split test to avoid testing for every coefficient
            double coefficientMultiplier = GetCoefficientMultiplierCurvelet( myMagnitude );
            
            pBandColor1->MultiplyValue( x, y, coefficientMultiplier );
            pBandColor2->MultiplyValue( x, y, coefficientMultiplier );
            pBandColor3->MultiplyValue( x, y, coefficientMultiplier );
         }
      }
   }
   return true;
}

//------------------------------------------------------------------------------

image::Image* PyramidContrastEnhancer::Run3Colors( image::Image* pImage, int nrScales, int nrOrientations, bool applyWavelet )
{
   if (pImage != 0) 
   {
      if (pImage->GetNumberOfBands() == 3)
      {
         PyramidReal np1( pImage->GetBands()[0], nrScales, nrOrientations);  np1.Decompose();
         image::Pyramid<double>* pPyramidColor1 = np1.GetPyramid();
         
         PyramidReal np2( pImage->GetBands()[1], nrScales, nrOrientations);  np2.Decompose();
         image::Pyramid<double>* pPyramidColor2 = np2.GetPyramid();
         
         PyramidReal np3( pImage->GetBands()[2], nrScales, nrOrientations);  np3.Decompose();
         image::Pyramid<double>* pPyramidColor3 = np3.GetPyramid();
         
         for (int scaleNr = 0; scaleNr < nrScales; scaleNr++)
         {
            for (int orientationNr = 0; orientationNr < nrOrientations; orientationNr++)
            {
               ContrastEnhanceSingleBand3Colors( pPyramidColor1->GetRecursiveScale( scaleNr )->GetOrientedBand( orientationNr ),
                                                pPyramidColor2->GetRecursiveScale( scaleNr )->GetOrientedBand( orientationNr ),
                                                pPyramidColor3->GetRecursiveScale( scaleNr )->GetOrientedBand( orientationNr ), 
                                                applyWavelet
                                             );
            }
         }
         if ( pPyramidColor1->GetResidualScale() != 0 )
         {
            for (int orientationNr = 0; orientationNr < nrOrientations; orientationNr++)
            {
               ContrastEnhanceSingleBand3Colors( pPyramidColor1->GetResidualScale( )->GetOrientedBand( orientationNr ),
                                                pPyramidColor2->GetResidualScale( )->GetOrientedBand( orientationNr ),
                                                pPyramidColor3->GetResidualScale( )->GetOrientedBand( orientationNr ), 
                                                applyWavelet 
                                             );
            }
         }
         
         image::Image* pFilteredImage = new image::Image( pImage->GetWidth(), pImage->GetHeight() );
         
         np1.Reconstruct(); 
         pFilteredImage->AddBand( np1.GetCopyOfReconstructedGrid() );
         
         np2.Reconstruct(); 
         pFilteredImage->AddBand( np2.GetCopyOfReconstructedGrid() );
         
         np3.Reconstruct(); 
         pFilteredImage->AddBand( np3.GetCopyOfReconstructedGrid() );
         std::string outName = pImage->GetImageName() + std::string("-WaveletContrastEnhanced");
         pFilteredImage->SetImageName(outName);
         return pFilteredImage;
      }
      else
      {
         return Run( pImage, nrScales, nrOrientations, applyWavelet );
      }
   }
   else
   {
      cerr << "Invalid NULL input for pyramid contrast enhancement" << endl << flush;
      return 0;
   }
}

//------------------------------------------------------------------------------

}
}
