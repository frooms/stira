
/***********************************************************************************
 *   Copyright (C) 2009 by Filip Rooms                                             *
 *                                                                                 *
 *  Terms and conditions for using this software in any form are provided in the   *
 *  file COPYING, which can be found in the root directory of this project.        *
 *                                                                                 *
 *   Contact data: filip.rooms@gmail.com                                           *
 *                 http://www.filiprooms.be/                                       *
 *                                                                                 *
 ***********************************************************************************/

#include "ColorBalancer.h"
#include "../tools/NumberGridTools.h"
#include "../tools/ImageTools.h"
#include "../tools/ImageIO.h"

using namespace std;

namespace stira {
namespace image {

ColorBalancer::ColorBalancer()
{
}

//----------------------------------------------------------------

ColorBalancer::~ColorBalancer()
{
}

//----------------------------------------------------------------

Image* ColorBalancer::RunGrayWorld(Image* pImageIn)
{
   if ( (pImageIn != 0) && (pImageIn->GetNumberOfBands() == 3) )
   {
      Image* pOutImage = pImageIn->Clone();
      double meanPerBand[3];

      for (int bandNr = 0; bandNr < 3; bandNr++)
      {
         meanPerBand[ bandNr ] = NumberGridTools<double>::GetGridMean( pImageIn->GetBands()[ bandNr ] );
      }

      double meanGray = ( meanPerBand[0] + meanPerBand[1] + meanPerBand[2] ) / 3.0;

      for (int bandNr = 0; bandNr < 3; bandNr++)
      {
         if ( meanPerBand[ bandNr ] != 0.0)
         {
            pOutImage->GetBands()[ bandNr ]->MultiplyWith( meanGray / meanPerBand[ bandNr ] );
         }
      }
      double mmin, mmax;
      pOutImage->GetMinMax( mmin, mmax );

      for (int bandNr = 0; bandNr < 3; bandNr++)
      {
         if ( mmax != 0.0)
         {
            pOutImage->GetBands()[ bandNr ]->DivideBy( mmax / 255.0 );
         }
      }
      std::string outName = pImageIn->GetImageName() + std::string("-GrayWorldBalanced");
      pOutImage->SetImageName(outName);
      return pOutImage;
   }
   else
   {
      cerr << "Invalid input at ColorBalancer::RunGrayWorld" << endl << flush;
      return 0;
   }
}

//----------------------------------------------------------------

Image* ColorBalancer::RunPerfectReflector(Image* pImageIn)
{
   if ( (pImageIn != 0) && (pImageIn->GetNumberOfBands() == 3) )
   {
      Image* pTmpImage = pImageIn->Clone();
      Image* pOutImage = pImageIn->Clone();

      pTmpImage->sRGBToLab();
      ImageIO::WritePGM( pTmpImage->GetBands()[0], std::string("IntensityImage.pgm"), ImageIO::NORMAL_OUT );
      double mmax;
      int xMax=0, yMax=0;
      NumberGridTools<double>::GetMax( pTmpImage->GetBands()[0], mmax, xMax, yMax );

      cout << "Max L " << mmax << " found at (" << xMax << ", " << yMax << ")" << endl << flush;

      ColorValue whitePoint = pImageIn->GetColor( xMax, yMax );

      pOutImage->GetBands()[0]->MultiplyWith(255.0 / whitePoint.c[0] );
      pOutImage->GetBands()[1]->MultiplyWith(255.0 / whitePoint.c[1] );
      pOutImage->GetBands()[2]->MultiplyWith(255.0 / whitePoint.c[2] );
      delete pTmpImage;
      std::string outName = pImageIn->GetImageName() + std::string("-PerfectReflectorBalanced");
      pOutImage->SetImageName(outName);
      return pOutImage;
   }
   else
   {
      cerr << "Invalid input at ColorBalancer::RunPerfectReflector" << endl << flush;
      return 0;
   }
}


//----------------------------------------------------------------

Image* ColorBalancer::RunGrayColorPoint(Image* pImageIn)
{
   if ( (pImageIn != 0) && (pImageIn->GetNumberOfBands() == 3) )
   {
      Image* pTmpImage = pImageIn->Clone();
      Image* pOutImage = pImageIn->Clone();

      pTmpImage->RGBToYUV();
      int width  = pImageIn->GetWidth();
      int height = pImageIn->GetHeight();

      ArrayGrid<bool>* pROI = new ArrayGrid<bool>( width, height );
      pROI->SetGridValues( false );

      double meanRed = 0.0, meanGreen = 0.0, meanBlue = 0.0;
      int nrGrayPixels = 0;

      double threshold = 0.55;   // pretty random threshold; should be selected or estimated more robustly

      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x++)
         {
            ColorValue colorPixel = pTmpImage->GetColor(x, y);
            if ( (fabs(colorPixel.c[1] - colorPixel.c[2]) / colorPixel.c[0]) < threshold)
            {
               meanRed   += pImageIn->GetBands()[0]->GetValue(x,y);
               meanGreen += pImageIn->GetBands()[1]->GetValue(x,y);
               meanBlue  += pImageIn->GetBands()[2]->GetValue(x,y);
               nrGrayPixels++;
               pROI->SetValue(x, y, true);
            }
         }
      }
      ImageIO::WritePGM(pROI, std::string("GraValues.pgm"));
      delete pROI;

      cout << "nrGrayPixels = " << nrGrayPixels << endl << flush;

      meanRed /= nrGrayPixels;
      meanGreen /= nrGrayPixels;
      meanBlue /= nrGrayPixels;

      if ( (meanRed >= meanGreen ) && (meanRed >= meanBlue ))
      {
         meanGreen /= meanRed;
         meanBlue /= meanRed;
         meanRed = 1.0;
      }
      else if ( (meanGreen >= meanRed ) && ( meanGreen >= meanBlue ))
      {
         meanRed /= meanGreen;
         meanBlue /= meanGreen;
         meanGreen = 1.0;
      }
      else
      {
         meanRed /= meanBlue;
         meanGreen /= meanBlue;
         meanBlue = 1.0;
      }

      cout << "meanRed = " << meanRed << "  meanGreen = " << meanGreen << "  meanBlue = " << meanBlue << endl << flush;

      pOutImage->GetBands()[0]->DivideBy( meanRed );
      pOutImage->GetBands()[1]->DivideBy( meanGreen );
      pOutImage->GetBands()[2]->DivideBy( meanBlue );
      delete pTmpImage;
      std::string outName = pImageIn->GetImageName() + std::string("-GrayPointBalanced");
      pOutImage->SetImageName(outName);
      return pOutImage;
   }
   else
   {
      cerr << "Invalid input at ColorBalancer::RunGrayPoint" << endl << flush;
      return 0;
   }
}

//----------------------------------------------------------------

Image* ColorBalancer::RunBalance(Image* pImageIn, double weight )
{
   if ( (pImageIn != 0) && (pImageIn->GetNumberOfBands() == 3) )
   {
      Image* pOutImageGW = RunGrayWorld( pImageIn );
      Image* pOutImagePR = RunPerfectReflector( pImageIn );

      Image* ImageOut = ImageTools::CreateTransparantlyMixedImage( pOutImageGW, pOutImagePR, weight );

      std::string outName = pImageIn->GetImageName() + std::string("-CombinedColorBalanced");
      ImageOut->SetImageName(outName);
      delete pOutImageGW;
      delete pOutImagePR;
      return ImageOut;
   }
   else
   {
      cerr << "Invalid input at ColorBalancer::RunBalance" << endl << flush;
      return 0;
   }
}

//----------------------------------------------------------------

}
}
