
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

#include <stdint.h>
#include <iostream>
#include "FFTBand.h"
#include "KISSFFTCalculator.h"
#include "FFTWCalculator.h"
#include "../../image/tools/ImageIO.h"

// to use FFTW (www.fftw.org), uncomment the following line
#define USE_FFTW
// if the line above is in commment, we use internal KISS FFT

using namespace std;

namespace stira {
namespace fouriertools {

using namespace image;

//============================================================================================

FFTBand::FFTBand( ArrayGrid<double>* pGrid, bool isreal )
{
   InitializeFFTBandValuesFromGrid( pGrid, isreal );
}

//============================================================================================

void FFTBand::InitializeFFTBandValuesFromGrid( ArrayGrid<double>* pGrid, bool isreal )
{
   mpFFTGrid = new ArrayGrid<complex<double> >( pGrid->GetWidth(), pGrid->GetHeight() );  // NOT initialized at construction
   if ( isreal )
   {
      InitializeBandWithRealValues( pGrid );
   }
   else
   {
      InitializeBandWithImagValues( pGrid );
   }
   
}
//============================================================================================

FFTBand::FFTBand( ArrayGrid< std::complex <double> >* pGrid)
{
   mpFFTGrid = new ArrayGrid< complex<double> >( pGrid->GetWidth(), pGrid->GetHeight() );  // NOT initialized at construction
   InitializeBandWithComplexValues( pGrid );
}

//============================================================================================

FFTBand::FFTBand( int width, int height, std::complex<double> initValue )
{
   bool needInitialisation = true;
   mpFFTGrid = new ArrayGrid< complex<double> >( width, height, needInitialisation, initValue );
   
   #ifdef DEBUG
      cout << "New FFTGrid with pointer " << mpFFTGrid << endl << flush;
   #endif
   
   InitializeBandWithConstantValue();
}

//==================================================================================================

FFTBand* FFTBand::Clone()
{
   return new FFTBand(*this);
}

//==================================================================================================

FFTBand::FFTBand( FFTBand &otherFFTBand )
{
   int width  = otherFFTBand.GetWidth();
   int height = otherFFTBand.GetHeight();
   bool needInitialisation = true;
   complex<double> initialComplexValue( 0.0, 0.0);
   mpFFTGrid = new ArrayGrid< complex<double> >( width, height, needInitialisation, initialComplexValue );

   for (int y = 0; y < otherFFTBand.GetHeight(); y++)
   {
      for (int x = 0; x < otherFFTBand.GetWidth(); x++)
      {
         this->SetValue(x, y, otherFFTBand.GetValue(x, y));
      }
   }
}

//============================================================================================

FFTBand::~FFTBand()
{
   delete mpFFTGrid;
   mpFFTGrid = 0;
}

//============================================================================================

double FFTBand::GetBandMaximum(FFTDataType type)
{
   double mmax = -10000000000000000.0;
   for (int y = 0; y < GetHeight(); y++)
   {
      for (int x = 0; x < GetWidth(); x++)
      {
         if (type == RE)
         {
            if ((GetValue(x, y).real()) > mmax)
            {
               mmax = GetValue(x, y).real();
            }
         }
         else
         {
            if ((GetValue(x, y).imag()) > mmax)
            {
               mmax = GetValue(x, y).imag();
            }
         }
      }
   }
   return mmax;
}

//============================================================================================

double FFTBand::GetBandMinimum(FFTDataType type)
{
   double mmin = 10000000000000000.0;
   for (int y = 0; y < GetHeight(); y++)
   {
      for (int x = 0; x < GetWidth(); x++)
      {
         if (type == RE)
         {
            if ((GetValue(x, y).real()) < mmin)
            {
               mmin = GetValue(x, y).real();
            }
         }
         else
         {
            if ((GetValue(x, y).imag()) < mmin)
            {
               mmin = GetValue(x, y).imag();
            }
         }
      }
   }
   return mmin;
}

//============================================================================================
   
void FFTBand::Multiply(FFTBand* other)
{
   for (int y = 0; y < GetHeight(); y++)
   {
      for (int x = 0; x < GetWidth(); x++)
      {
         SetValue( x, y, GetValue( x, y) * other->GetValue( x, y) );
      }
   }
}

//============================================================================================

void FFTBand::Multiply( ArrayGrid<double>* grid)
{
   for (int y = 0; y < GetHeight(); y++)
   {
      for (int x = 0; x < GetWidth(); x++)
      {
         SetValue( x, y, GetValue( x, y) * grid->GetValue( x, y) );
      }
   }
}

//============================================================================================

void FFTBand::Multiply(std::complex<double> myFactor)
{
   for (int y = 0; y < GetHeight(); y++)
   {
      for (int x = 0; x < GetWidth(); x++)
      {
         SetValue( x, y, GetValue( x, y) * myFactor );
      }
   }
}

//============================================================================================

void FFTBand::Multiply(double myFactor)
{
   for (int y = 0; y < GetHeight(); y++)
   {
      for (int x = 0; x < GetWidth(); x++)
      {
         SetValue( x, y, GetValue( x, y) * myFactor );
      }
   }
}

//============================================================================================

complex<double> FFTBand::GetValue(int x, int y) const
{
   return mpFFTGrid->GetValue(x, y);
}

//============================================================================================

void FFTBand::SetValue(int x, int y, std::complex<double> complexValue)
{
   mpFFTGrid->SetValue(x, y, complexValue);
}

//============================================================================================

void FFTBand::SetValue(int x, int y, double realValue, double imagValue)
{
   complex<double> complexValue(realValue, imagValue);
   mpFFTGrid->SetValue(x, y, complexValue);
}

//============================================================================================

int FFTBand::GetWidth() const
{
   return mpFFTGrid->GetWidth();
}

//============================================================================================

int FFTBand::GetHeight() const
{
   return mpFFTGrid->GetHeight();
}

//============================================================================================

bool FFTBand::InitializeBandWithConstantValue( std::complex<double> initValue)
{
   for (int y = 0; y < GetHeight(); y ++)
   {
      for (int x = 0; x < GetWidth(); x++)
      {
         SetValue(x, y, initValue);
      }
   }
   return true;
}

//============================================================================================

bool FFTBand::InitializeBandWithRealValues( image::ArrayGrid<double>* pGrid )
{
   if ( pGrid == 0)
   {
      InitializeBandWithConstantValue();
      return false;
   }
   else
   {
      for (int y = 0; y < GetHeight(); y ++)
      {
         for (int x = 0; x < GetWidth(); x++)
         {
            SetValue(x, y, std::complex<double>( pGrid->GetValue(x, y), 0.0) );
         }
      }
      return true;
   }
}

//============================================================================================
   
bool FFTBand::InitializeBandWithImagValues( image::ArrayGrid<double>* pGrid )
{
   if ( pGrid == 0)
   {
      InitializeBandWithConstantValue();
      return false;
   }
   else
   {
      for (int y = 0; y < GetHeight(); y ++)
      {
         for (int x = 0; x < GetWidth(); x++)
         {
            SetValue(x, y, std::complex<double>(0.0, pGrid->GetValue(x, y) ) );
         }
      }
      return true;
   }
}

//============================================================================================;
bool FFTBand::InitializeBandWithComplexValues( image::ArrayGrid< std::complex<double> >* pGrid )
{
   if ( pGrid == 0)
   {
      InitializeBandWithConstantValue();
      return false;
   }
   else
   {
      for (int y = 0; y < GetHeight(); y ++)
      {
         for (int x = 0; x < GetWidth(); x++)
         {
            SetValue(x, y, pGrid->GetValue(x, y) );
         }
      }
      return true;
   }
}

//============================================================================================

void FFTBand::ApplyForwardTransform()
{
   #ifdef USE_FFTW
   FFTWCalculator ft(mpFFTGrid);
   #else
   KISSFFTCalculator ft(mpFFTGrid);
   #endif
   ft.ApplyForwardTransform();
}

//============================================================================================

void FFTBand::ApplyInverseTransform()
{
   #ifdef USE_FFTW
   FFTWCalculator ft(mpFFTGrid);
   #else
   KISSFFTCalculator ft(mpFFTGrid);
   #endif
   ft.ApplyInverseTransform();
   ft.SwitchQuadrants();
}

//============================================================================================

ArrayGrid<double>* FFTBand::ConvertToRealGrid( )
{
   bool needInitialisation = true;
   double initialRealValue = 0.0;
   ArrayGrid<double>* pGrid = new ArrayGrid<double>( GetWidth(), GetHeight(), needInitialisation, initialRealValue );

   for (int y = 0; y < GetHeight(); y++)
   {
      for (int x = 0; x < GetWidth(); x++)
      {
         pGrid->SetValue(x, y, GetValue(x, y).real());
      }
   }
   return pGrid;
}

//============================================================================================

void FFTBand::ExportAbsImage( std::string fileName )
{
   bool needInitialisation = true;
   double initialRealValue = 0.0;
   ArrayGrid<double>* pGrid = new ArrayGrid<double>( GetWidth(), GetHeight(), needInitialisation, initialRealValue );

   for (int y = 0; y < GetHeight(); y++)
   {
      for (int x = 0; x < GetWidth(); x++)
      {
         pGrid->SetValue(x, y, std::abs( GetValue(x, y) ) );
      }
   }
   pGrid->SwitchQuadrants();
   ImageIO::WritePGM( pGrid, fileName, ImageIO::NORMAL_OUT);
   delete pGrid;
}

//============================================================================================

ArrayGrid<double>* FFTBand::ConvertToImaginaryGrid( )
{
   bool needInitialisation = true;
   double initialRealValue = 0.0;
   ArrayGrid<double>* pGrid = new ArrayGrid<double>( GetWidth(), GetHeight(), needInitialisation, initialRealValue );

   for (int y = 0; y < GetHeight(); y++)
   {
      for (int x = 0; x < GetWidth(); x++)
      {
         pGrid->SetValue(x, y, GetValue(x, y).imag());
      }
   }
   return pGrid;
}

//============================================================================================

ArrayGrid< complex<double> >* FFTBand::ConvertToComplexGrid( )
{
   return mpFFTGrid->Clone();
}

//============================================================================================

void FFTBand::PointMirrorBand()
{
   FFTBand* pTmpOriginalBand = this->Clone();

   for (int y = 0; y < GetHeight(); y++)
   {
      for (int x = 0; x < GetWidth(); x++)
      { 
         int xMirrored = GetWidth() - 1 - x;
         int yMirrored = GetHeight() - 1 - y;
         this->SetValue(x, y, pTmpOriginalBand->GetValue(xMirrored, yMirrored));
      }
   }
   delete pTmpOriginalBand;
}

//============================================================================================

void FFTBand::Conjugate()
{
   for (int y = 0; y < GetHeight(); y++)
   {
      for (int x = 0; x < GetWidth(); x++)
      {
         this->SetValue(x, y, std::conj(this->GetValue(x, y)));
      }
   }
}


//============================================================================================

void FFTBand::SwitchQuadrants()
{
   mpFFTGrid->SwitchQuadrants();
}

//============================================================================================
}
}

