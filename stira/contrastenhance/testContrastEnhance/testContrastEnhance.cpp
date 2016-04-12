
/***************************************************************************************
 *   Copyright (C) 2008 by Filip Rooms                                                 *
 *                                                                                     *
 *  Terms and conditions for using this software in any form are provided in the       *
 *  file COPYING, which can be found in the root directory of this project.            *
 *                                                                                     *
 *   Contact data: filip.rooms@gmail.com                                               *
 *                 http://www.filiprooms.be/                                           *
 *                                                                                     *
 ***************************************************************************************/

#include "../../common/common/ExecutionTimer.h"
#include "../../image/datastructures/Image.h"
#include "../../image/tools/ImageIO.h"
#include "../../histogram/histogram/IntHistogram.h"
#include "../contrastenhance/HistogramTools.h"
#include "../contrastenhance/Retinex.h"
#include "../contrastenhance/AdaptiveEnhanceLuong.h"
#include "../contrastenhance/HazeRemover.h"

using namespace stira;
using namespace stira::common;
using namespace stira::image;
using namespace stira::histogram;
using namespace stira::contrastenhance;
using namespace std;


//============================================================================

bool RobustRescaleTest(Image* pInImage)
{
    double lfrac = 0.01; // 0.03 emperically seemed a good value for turtle test image
    double ufrac = 0.99; //0.995 emperically seemed a good value for turtle test image
    Image* pOutImage = HistogramTools::RobustLinearRescale( pInImage, lfrac, ufrac );
    ImageIO::Write( pOutImage, string("RobustRescale.ppm"), ImageIO::NORMAL_OUT );

    delete pOutImage;
    return true;
 }

//============================================================================

bool RetinexTest(Image* pInImage)
{
   double lfrac = 0.03; // 0.03 emperically seemed a good value for turtle test image
   double ufrac = 0.995; //0.995 emperically seemed a good value for turtle test image

   Image* pOutImage = Retinex::RunMSRCR( pInImage, lfrac, ufrac, true );
   ImageIO::Write( pOutImage, string("Retinex.ppm"), ImageIO::NORMAL_OUT );

   delete pOutImage;
   return true;
}

//============================================================================

bool HazeRemoveTest(Image* pInImage)
{
   HazeRemover hr;
   Image* pOutImage = hr.Run( pInImage );
   ImageIO::Write( pOutImage, string("HazeRemover.ppm"), ImageIO::NORMAL_OUT );

   delete pOutImage;
   return true;
}

//============================================================================

bool EqualizeTest(Image* pInImage)
{
   Image* pOutImage = HistogramTools::HistogramEqualizePerBand( pInImage );
   ImageIO::Write( pOutImage, string("HistogramEqualizedPerBand.ppm"), ImageIO::NULL_OUT );
   delete pOutImage;

   if (pInImage->GetNumberOfBands() == 3)
   {
      Image* pOutImage2 = HistogramTools::HistogramEqualizeHSI( pInImage );
      ImageIO::Write( pOutImage2, string("HistogramEqualizedRGB.ppm"), ImageIO::NULL_OUT );
      delete pOutImage2;
      Image* pOutImage3 = HistogramTools::ColorHistogramEqualize( pInImage );
      ImageIO::Write( pOutImage3, string("HistogramEqualizedLab.ppm"), ImageIO::NULL_OUT );
      delete pOutImage3;
   }

   return true;
}

//============================================================================

bool HistogramMapTest()
{
   std::string fileName1 = string("../../../../stira/stira/testdata/testhaze.ppm");

   Image* pImage1 = ImageIO::Read( fileName1 );
   Image* pImage2 = ImageIO::Read( fileName1 );

   RectangularROI<int> rroi1(   0, 0,  45, 25 );
   RectangularROI<int> rroi2( 345, 5, 390, 30 );

   bool useDataMinMax = false;
   IntHistogram* pIH_Orig = new IntHistogram( pImage1->GetBands()[0], useDataMinMax, rroi1 );
   pIH_Orig->ConvertInCumulativeHistogram();
   pIH_Orig->Write("RemapOrigBeforeCumul.txt");

   IntHistogram* pIH_Ref = new IntHistogram( pImage2->GetBands()[0], useDataMinMax, rroi2 );
   pIH_Ref->ConvertInCumulativeHistogram();
   pIH_Ref->Write("RemapRefCumul.txt");


   bool requiresNormalization = false;
   FloatHistogram* pFH_Ref = new FloatHistogram( pIH_Ref, requiresNormalization );
   pFH_Ref->Write("RemapRefFloatCumul.txt");

   HistogramTools::RemapHistogramInROI( pImage1->GetBands()[0], rroi1, pIH_Orig, pFH_Ref );

   ImageIO::WriteOpenCV( pImage1->GetBands()[0], std::string("Remapped.png") );

   IntHistogram ihTestAfter( pImage2->GetBands()[0], useDataMinMax, rroi2 );     ihTestAfter.ConvertInCumulativeHistogram();
   ihTestAfter.Write("RemapOrigAfterRemapCumul.txt");

   delete pImage1;
   delete pImage2;

   return true;
}

//============================================================================

bool AdaptiveLuongTest(Image* pInImage)
{
   ExecutionTimer et;
   et.StartTimer();
   AdaptiveEnhanceLuong ael;
   ael.SetAlphaFactor( 0.75 );
   ael.SetWindowSize( 7 );
   Image* pOutImage = ael.Run( pInImage );
   et.StopTimer();
   cout.precision(5);
   cout.setf(ios::fixed,ios::floatfield);
   et.PrintTimeAsUserAndSystemTimes();
   ImageIO::Write( pOutImage, std::string("AdaptiveEnhance.ppm") );
   delete pOutImage;
   return true;
}

//============================================================================

int main(int argc, char *argv[])
{
   string fileNamePPM;
   if (argc < 2)
   {
      //fileNamePPM = string("../../../../stira/stira/testdata/Lenna-degraded.ppm");
      //fileNamePPM = string("../../../../stira/stira/testdata/circles-Gauss-GaussianNoise.ppm");
      //fileNamePPM = string("../../../../stira/stira/testdata/Lenna.ppm");
      fileNamePPM = string("../../../../stira/stira/testdata/testhaze.ppm");
      //fileNamePPM = string("../../../../stira/stira/testdata/canon3.ppm");
      //fileNamePPM = string("../../../../stira/stira/testdata/train.ppm");

   }
   else
   {
      fileNamePPM = string( argv[1] );
   }
   cout << "File name is " << fileNamePPM << endl << flush;

   Image* pImage = ImageIO::Read( fileNamePPM );



   if (RobustRescaleTest( pImage) == true )
   {
      cout << "RobustRescaleTest test success!!" << endl << flush;
   }
   else
   {
      cout << "RRobustRescale test FAILED!!" << endl << flush;
   }

   if (RetinexTest( pImage) == true )
   {
      cout << "Retinex test success!!" << endl << flush;
   }
   else
   {
      cout << "Retinex test FAILED!!" << endl << flush;
   }

   if ( EqualizeTest( pImage ) == true )
   {
      cout << "HistogramEqualize test success!!" << endl << flush;
   }
   else
   {
      cout << "HistogramEqualize test FAILED!!" << endl << flush;
   }

   if ( AdaptiveLuongTest( pImage ) == true )
   {
      cout << "Adaptive Luong test success!!" << endl << flush;
   }
   else
   {
      cout << "Adaptive Luong test FAILED!!" << endl << flush;
   }

   if ( HistogramMapTest() == true )
   {
      cout << "Histogram Map Test success!!" << endl << flush;
   }
   else
   {
      cout << "Histogram Map Test test FAILED!!" << endl << flush;
   }

   if ( HazeRemoveTest( pImage ) == true )
   {
      cout << "Haze Removal Test success!!" << endl << flush;
   }
   else
   {
      cout << "Haze Removal Test FAILED!!" << endl << flush;
   }

   delete pImage;
   return 1;
}
