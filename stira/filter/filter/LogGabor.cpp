#include "LogGabor.h"
#include "../../common/common/StiraMacros.h"
#include "../../imagedata/simpletools/ImageStatistics.h"
#include "../../fouriertools/fouriertools/FFT.h"
#include "../../fouriertools/fouriertools/TransferFunctionGenerator.h"
#include "../../imagetools/imagegenerator/GridGenerator.h"
#include "../../imagetools/tools/ImageIO.h"

namespace stira{
namespace filter{

using namespace image;
using namespace fouriertools;

//------------------------------------------------------------------

LogGabor::LogGabor( Image *pImage )
{
   mpImage = pImage;

   assert( mpImage != 0);

   mCenterFrequency = 5.0;
   mRadialWidth = 1.25;
   mCenterAngle = M_PI / 2.0;
   mAngleSpread = 0.3;
   int width  = mpImage->GetWidth();
   int height = mpImage->GetHeight();

   mpImageReal = new Image(width, height);
   std::string outNameReal = mpImage->GetImageName() + std::string("-LogGabor-Real");
   mpImageReal->SetImageName(outNameReal);

   mpImageImag = new Image( width, height );
   std::string outNameImag = mpImage->GetImageName() + std::string("-LogGabor-Imag");
   mpImageImag->SetImageName( outNameImag );

   mpImageTransfer = 0;
}

//------------------------------------------------------------------

LogGabor::~LogGabor( )
{
   if (mpImageReal != 0) {delete mpImageReal;}
   if (mpImageImag != 0) {delete mpImageImag;}
   if (mpImageTransfer != 0) {delete mpImageTransfer;}
}

//------------------------------------------------------------------

double LogGabor::GetCenterFrequency()
{
   return mCenterFrequency;
}

//------------------------------------------------------------------

void LogGabor::SetCenterFrequency( double centerFrequency )
{
   mCenterFrequency = centerFrequency;
}

//------------------------------------------------------------------

double LogGabor::GetRadialWidth()
{
   return mRadialWidth;
}

//------------------------------------------------------------------
void LogGabor::SetRadialWidth( double radialWidth )
{
   mRadialWidth = radialWidth;
}

//------------------------------------------------------------------

double LogGabor::GetCenterAngle()
{
   return mCenterAngle;
}

//------------------------------------------------------------------

void LogGabor::SetCenterAngle( double centerAngle )
{
   mCenterAngle = centerAngle;
}

//------------------------------------------------------------------

double LogGabor::GetAngleSpread()
{
   return mAngleSpread;
}

//------------------------------------------------------------------

void LogGabor::SetAngleSpread( double angleSpread )
{
   mAngleSpread = angleSpread;
}

//------------------------------------------------------------------

Image* LogGabor::GetRealResponse( bool rescaleVisualize )
{
   Image* pImgScale = mpImageReal->Clone();
   if ( rescaleVisualize )
   {
      ImageStatistics::Rescale( pImgScale, 0.0, 255.0 );
   }
   return pImgScale;
}

//------------------------------------------------------------------

Image* LogGabor::GetImagResponse( bool rescaleVisualize )
{
   Image* pImgScale = mpImageImag->Clone();
   if ( rescaleVisualize )
   {
       ImageStatistics::Rescale( pImgScale, 0.0, 255.0 );
   }
   return pImgScale;
}

//------------------------------------------------------------------

Image* LogGabor::GetTransferFunction( bool rescaleVisualize )
{
   Image* pImgScale = mpImageTransfer->Clone();
   if ( rescaleVisualize )
   {
       ImageStatistics::Rescale( pImgScale, 0.0, 255.0 );
   }
   std::string outName = mpImage->GetImageName() + std::string("-LogGabor-Transfer");
   pImgScale->SetImageName( outName );
   return pImgScale;
}

//------------------------------------------------------------------

Image* LogGabor::GetMagnitude( bool rescaleVisualize )
{
   Image* pImgMagnitude = mpImage->Clone();
   int width  = mpImage->GetWidth();
   int height = mpImage->GetHeight();
   int nrBands = mpImage->GetNumberOfBands();

   for(int bandID = 0; bandID < nrBands; bandID++)
   {
      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x++)
         {
            double tmpValueRe = mpImageReal->GetBands()[bandID]->GetValue( x, y );
            double tmpValueIm = mpImageImag->GetBands()[bandID]->GetValue( x, y );
            double tmpValue = fabs( sqrt( ( tmpValueRe * tmpValueRe ) + ( tmpValueIm * tmpValueIm ) ) );
            pImgMagnitude->GetBands()[bandID]->SetValue( x, y, tmpValue );
         }
      }
   }

   if ( rescaleVisualize )
   {
       ImageStatistics::Rescale( pImgMagnitude, 0.0, 255.0 );
   }
   std::string outName = mpImage->GetImageName() + std::string("-LogGabor-Magnitude");
   pImgMagnitude->SetImageName( outName );
   return pImgMagnitude;
}

//------------------------------------------------------------------

void LogGabor::PrintParameters()
{
   cout << "LogGabor Filter Parameters:" << endl << flush;
   cout << "\t Image Name:\t" << mpImage->GetImageName() << endl << flush;
   cout << "\t Center Freq.: \t" << mCenterFrequency << endl << flush;
   cout << "\t Radial Width: \t" << mRadialWidth << endl << flush;
   cout << "\t CenterAngle: \t" << mCenterAngle << endl << flush;
   cout << "\t AngleSpread: \t" << mAngleSpread << endl << flush;
}

//------------------------------------------------------------------

void LogGabor::Run()
{
   int width  = mpImage->GetWidth();
   int height = mpImage->GetHeight();
   int nrBands = mpImage->GetNumberOfBands();

   ArrayGrid<double>* pLogGaborTransferFunction = TransferFunctionGenerator::GenerateLogGaborBandTransferFunction( width, height, (width / mCenterFrequency), mRadialWidth, mCenterAngle, mAngleSpread);
   for(int bandID = 0; bandID < nrBands; bandID++)
   {
      std::pair< ArrayGrid<double>*, ArrayGrid<double>*> pComplexGridPair = FFT::ApplyTransferFunctionSpatialComplex( mpImage->GetBands()[bandID],
                                                                                                                      pLogGaborTransferFunction
                                                                                                                    );
      assert( pComplexGridPair.first != 0);
      assert( pComplexGridPair.second != 0);
      mpImageReal->AddBand( pComplexGridPair.first );
      mpImageImag->AddBand( pComplexGridPair.second );
   }
   pLogGaborTransferFunction->SwitchQuadrants();
   if ( mpImageTransfer != 0) {delete mpImageTransfer;}
   mpImageTransfer = new Image( pLogGaborTransferFunction );
}

}
}
