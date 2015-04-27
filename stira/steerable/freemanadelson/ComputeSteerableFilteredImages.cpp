
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

#include "ComputeSteerableFilteredImages.h"
#include "../orientationestimation/ComputeOrientation.h"
#include "../../filter/filter/SeparableFilter.h"
#include "../../image/tools/ImageIO.h"
#include <cassert>

//#define DEBUG

namespace stira {
namespace steerable {

using namespace image;
using namespace filter;

//----------------------------------------------------------------------

ComputeSteerableFilteredImages::ComputeSteerableFilteredImages( ArrayGrid<double>* pSourceGrid )
{
   assert( pSourceGrid != 0 );
   mpSourceGrid = pSourceGrid;
   mpTaps = new BasicFilterKernels();

   mpResponseH2a = 0;
   mpResponseH2b = 0;
   mpResponseH2c = 0;
   mpResponseH2d = 0;
   mpResponseG2a = 0;
   mpResponseG2b = 0;
   mpResponseG2c = 0;
   mHasBasicResponses = false;
}

//----------------------------------------------------------------------

ComputeSteerableFilteredImages::~ComputeSteerableFilteredImages()
{
   if (mpResponseH2a != 0)   {delete mpResponseH2a;}
   if (mpResponseH2b != 0)   {delete mpResponseH2b;}
   if (mpResponseH2c != 0)   {delete mpResponseH2c;}
   if (mpResponseH2d != 0)   {delete mpResponseH2d;}
   if (mpResponseG2a != 0)   {delete mpResponseG2a;}
   if (mpResponseG2b != 0)   {delete mpResponseG2b;}
   if (mpResponseG2c != 0)   {delete mpResponseG2c;}
   delete mpTaps;
}

//----------------------------------------------------------------------

image::ArrayGrid<double>* ComputeSteerableFilteredImages::InterpolateG( double theta )
{
   if (!mHasBasicResponses)
   {
      Run();
   }
   // data arrays to hold the filtered versions of the image in memory
   ArrayGrid<double>* pInterpolatedBand = 0;

   int width  = mpResponseG2a->GetWidth();
   int height = mpResponseG2a->GetHeight();
   bool needInitialisation = true;
   double initialRealValue = 0.0;

   double ka = cos( theta ) * cos( theta );
   double kb = -2.0 * cos( theta ) * sin( theta );
   double kc = sin( theta ) * sin( theta );

   pInterpolatedBand = new ArrayGrid<double>( width, height, needInitialisation, initialRealValue );
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         double tmpValue = ka * mpResponseG2a->GetValue( x, y ) + kb * mpResponseG2b->GetValue( x, y ) + kc * mpResponseG2c->GetValue( x, y );
         pInterpolatedBand->SetValue( x, y, tmpValue );
      }
   }
   return pInterpolatedBand;
}

//----------------------------------------------------------------------

image::ArrayGrid<double>* ComputeSteerableFilteredImages::InterpolateH( double theta )
{
   if (!mHasBasicResponses)
   {
      Run();
   }
   // data arrays to hold the filtered versions of the image in memory
   ArrayGrid<double>* pInterpolatedBand = 0;

   int width  = mpResponseG2a->GetWidth();
   int height = mpResponseG2a->GetHeight();
   bool needInitialisation = true;
   double initialRealValue = 0.0;

   double ka = cos( theta ) * cos( theta ) * cos( theta );
   double kb = -3.0 * cos( theta ) * cos( theta ) * sin( theta );
   double kc =  3.0 * cos( theta ) * sin( theta ) * sin( theta );
   double kd = - sin( theta ) * sin( theta ) * sin( theta );

   pInterpolatedBand = new ArrayGrid<double>( width, height, needInitialisation, initialRealValue );
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         double tmpValue = ka * mpResponseH2a->GetValue( x, y ) + kb * mpResponseH2b->GetValue( x, y ) + kc * mpResponseH2c->GetValue( x, y ) + kd * mpResponseH2d->GetValue( x, y );
         pInterpolatedBand->SetValue( x, y, tmpValue );
      }
   }
   return pInterpolatedBand;
}

//----------------------------------------------------------------------

image::ArrayGrid<double>* ComputeSteerableFilteredImages::FilterAlongDominantOrientationG( )
{
   if (!mHasBasicResponses)
   {
      Run();
   }
   ComputeOrientation co;
   OrientationGrid* pOrientationGrid = co.ComputeDominantOrientationInputFreemanAdelson( mpResponseH2a, mpResponseH2b, mpResponseH2c, mpResponseH2d,
                                                                                         mpResponseG2a, mpResponseG2b, mpResponseG2c
                                                                                       );
   // data arrays to hold the filtered versions of the image in memory
   ArrayGrid<double>* pInterpolatedBand = 0;

   int width  = mpResponseG2a->GetWidth();
   int height = mpResponseG2a->GetHeight();
   bool needInitialisation = true;
   double initialRealValue = 0.0;

   pInterpolatedBand = new ArrayGrid<double>( width, height, needInitialisation, initialRealValue );
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         double theta = pOrientationGrid->GetOrientation( x, y );
         double ka = cos( theta ) * cos( theta );
         double kb = -2.0 * cos( theta ) * sin( theta );
         double kc = sin( theta ) * sin( theta );
         double tmpValue = ka * mpResponseG2a->GetValue( x, y ) + kb * mpResponseG2b->GetValue( x, y ) + kc * mpResponseG2c->GetValue( x, y );
         pInterpolatedBand->SetValue( x, y, tmpValue );
      }
   }
   return pInterpolatedBand;
}

//----------------------------------------------------------------------

image::ArrayGrid<double>* ComputeSteerableFilteredImages::FilterAlongDominantOrientationH( )
{
   if (!mHasBasicResponses)
   {
      Run();
   }
   ComputeOrientation co;
   OrientationGrid* pOrientationGrid = co.ComputeDominantOrientationInputFreemanAdelson( mpResponseH2a, mpResponseH2b, mpResponseH2c, mpResponseH2d,
                                                                                         mpResponseG2a, mpResponseG2b, mpResponseG2c
                                                                                       );
   // data arrays to hold the filtered versions of the image in memory
   ArrayGrid<double>* pInterpolatedBand = 0;

   int width  = mpResponseH2a->GetWidth();
   int height = mpResponseH2a->GetHeight();
   bool needInitialisation = true;
   double initialRealValue = 0.0;

   pInterpolatedBand = new ArrayGrid<double>( width, height, needInitialisation, initialRealValue );
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         double theta = pOrientationGrid->GetOrientation( x, y );

         double ka = cos( theta ) * cos( theta ) * cos( theta );
         double kb = -3.0 * cos( theta ) * cos( theta ) * sin( theta );
         double kc =  3.0 * cos( theta ) * sin( theta ) * sin( theta );
         double kd = - sin( theta ) * sin( theta ) * sin( theta );

         double tmpValue = ka * mpResponseH2a->GetValue( x, y ) + kb * mpResponseH2b->GetValue( x, y ) + kc * mpResponseH2c->GetValue( x, y ) + kd * mpResponseH2d->GetValue( x, y );
         pInterpolatedBand->SetValue( x, y, tmpValue );
      }
   }
   return pInterpolatedBand;
}

//----------------------------------------------------------------------

OrientationGrid* ComputeSteerableFilteredImages::GetOrientationGrid( )
{
   if (!mHasBasicResponses)
   {
      Run();
   }
   ComputeOrientation co;
   OrientationGrid* pOrientationGrid = co.ComputeDominantOrientationInputFreemanAdelson( mpResponseH2a, mpResponseH2b, mpResponseH2c, mpResponseH2d,
                                                                                         mpResponseG2a, mpResponseG2b, mpResponseG2c
                                                                                       );

   //pOrientationGrid->ExportMagnitudeImage( string("EdgeMagnitude.ppm") );
   //pOrientationGrid->ExportOrientationImage( string("EdgeDirection.ppm"), 50.0, OrientationGrid::EXPORT_RGB_MODE );
   //pOrientationGrid->ExportOrientationImage( string("EdgeDirection.ppm"), 50.0, OrientationGrid::EXPORT_HSV_MODE );
   return ( pOrientationGrid );
}

//----------------------------------------------------------------------

image::ArrayGrid<double>* ComputeSteerableFilteredImages::GetH2a()
{
   if (!mHasBasicResponses)
   {
      Run();
   }
   return mpResponseH2a;
}

//----------------------------------------------------------------------

image::ArrayGrid<double>* ComputeSteerableFilteredImages::GetH2b()
{
   if (!mHasBasicResponses)
   {
      Run();
   }
   return mpResponseH2b;
}

//----------------------------------------------------------------------

image::ArrayGrid<double>* ComputeSteerableFilteredImages::GetH2c()
{
   if (!mHasBasicResponses)
   {
      Run();
   }
   return mpResponseH2c;
}

//----------------------------------------------------------------------

image::ArrayGrid<double>* ComputeSteerableFilteredImages::GetH2d()
{
   return mpResponseH2d;
}

//----------------------------------------------------------------------

image::ArrayGrid<double>* ComputeSteerableFilteredImages::GetG2a()
{
   if (!mHasBasicResponses)
   {
      Run();
   }
   return mpResponseG2a;
}

//----------------------------------------------------------------------

image::ArrayGrid<double>* ComputeSteerableFilteredImages::GetG2b()
{
   if (!mHasBasicResponses)
   {
      Run();
   }
   return mpResponseG2b;
}

//----------------------------------------------------------------------

image::ArrayGrid<double>* ComputeSteerableFilteredImages::GetG2c()
{
   if (!mHasBasicResponses)
   {
      Run();
   }
   return mpResponseG2c;
}

//----------------------------------------------------------------------

int ComputeSteerableFilteredImages::Run()
{
   // data arrays to hold the filtered versions of the image in memory

   SeparableFilter sf;
   mpResponseH2a = sf.RunRowColumn( mpSourceGrid, mpTaps->GetFilterH2F1(), mpTaps->GetFilterH2F2(), mpTaps->GetBasicfilterLength(), mpTaps->GetBasicfilterLength() );
   mpResponseH2b = sf.RunRowColumn( mpSourceGrid, mpTaps->GetFilterH2F4(), mpTaps->GetFilterH2F3(), mpTaps->GetBasicfilterLength(), mpTaps->GetBasicfilterLength() );
   mpResponseH2c = sf.RunRowColumn( mpSourceGrid, mpTaps->GetFilterH2F3(), mpTaps->GetFilterH2F4(), mpTaps->GetBasicfilterLength(), mpTaps->GetBasicfilterLength() );
   mpResponseH2d = sf.RunRowColumn( mpSourceGrid, mpTaps->GetFilterH2F2(), mpTaps->GetFilterH2F1(), mpTaps->GetBasicfilterLength(), mpTaps->GetBasicfilterLength() );

   mpResponseG2a = sf.RunRowColumn( mpSourceGrid, mpTaps->GetFilterG2F1(), mpTaps->GetFilterG2F2(), mpTaps->GetBasicfilterLength(), mpTaps->GetBasicfilterLength() );
   mpResponseG2b = sf.RunRowColumn( mpSourceGrid, mpTaps->GetFilterG2F3(), mpTaps->GetFilterG2F3(), mpTaps->GetBasicfilterLength(), mpTaps->GetBasicfilterLength() );
   mpResponseG2c = sf.RunRowColumn( mpSourceGrid, mpTaps->GetFilterG2F2(), mpTaps->GetFilterG2F1(), mpTaps->GetBasicfilterLength(), mpTaps->GetBasicfilterLength() );

   #ifdef DEBUG
      ImageIO::WritePGM( mpResponseH2a, string("imH2a.ppm"), ImageIO::GRADIENT_OUT);
      ImageIO::WritePGM( mpResponseH2b, string("imH2b.ppm"), ImageIO::GRADIENT_OUT);
      ImageIO::WritePGM( mpResponseH2c, string("imH2c.ppm"), ImageIO::GRADIENT_OUT);
      ImageIO::WritePGM( mpResponseH2d, string("imH2d.ppm"), ImageIO::GRADIENT_OUT);

      ImageIO::WritePGM( mpResponseG2a, string("imG2a.ppm"), ImageIO::GRADIENT_OUT);
      ImageIO::WritePGM( mpResponseG2b, string("imG2b.ppm"), ImageIO::GRADIENT_OUT);
      ImageIO::WritePGM( mpResponseG2c, string("imG2c.ppm"), ImageIO::GRADIENT_OUT);
   #endif

   mHasBasicResponses = true;

   return 1;
}

//----------------------------------------------------------------------

//----------------------------------------------------------------------

}
}
