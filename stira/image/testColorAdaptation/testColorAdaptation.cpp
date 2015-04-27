
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
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

#include <cstdlib>
#include <cassert>
#include "../../common/common/MathUtils.h"
#include "../tools/ImageIO.h"
#include "../color/ColorValue.h"
#include "../color/TransformColorSpace.h"
#include "../tools/NumberGridTools.h"
#include "../tools/GridGenerator.h"
#include "../tools/ImageTools.h"
#include "../color/ChromaticAdaptation.h"

using namespace std;
using namespace stira::image;
using namespace stira::common;

//----------------------------------------------------------

ColorValue*** CreateInitializedColorCube( int maxL, int maxA, int maxB )
{
   ColorValue*** pLABCube;  // cube of color values
   
   // allocate L*a*b* color cube
   //////////////////////////////
   pLABCube = new ColorValue**[maxL];
   {
      for( int l = 0; l < maxL; l++)
      {
         pLABCube[ l ] = new ColorValue*[maxA];
         for( int a = 0; a < maxA; a++)
         {
            pLABCube[ l ][ a ] = new ColorValue[maxB];
         }
      }
   }
   
   // intialize color cube
   ///////////////////////
   ColorValue cv0 = ColorValue( 0, 0, 0, TYPE_LAB );
   
   for (int l=0; l < maxL; l++)
   {
      for (int a=0; a < maxA; a++)
      {
         for (int b=0; b < maxB; b++)
         {
            pLABCube[ l ][ a ][ b ] = cv0;
         }
      }
   }
   return pLABCube;
}

//----------------------------------------------------------

void FillColorCubeWithsRGBValues( ColorValue*** pLABCube, int maxL, int maxA, int maxB )
{
   TransformColorSpace tcsp;
   double maxRgbValue = 255.0;
   
   int halfMaxA = (int)( maxA / 2.0 );
   int halfMaxB = (int)( maxB / 2.0 );
   
   double rStep, gStep, bStep;
   rStep = gStep = bStep = 1.0;
   
   for (double r = 0.0; r <= maxRgbValue; r += rStep )
   {
      for (double g = 0.0; g <= maxRgbValue; g += gStep )
      {
         for (double b = 0.0; b <= maxRgbValue; b += bStep )
         {
            ColorValue cv1 = ColorValue( r, g, b, TYPE_RGB );
            ColorValue cv2 = tcsp.sRGBtoLab( cv1 );
            if (    ( cv2.c[0] >    0      )
                 && ( cv2.c[0] <  maxL     )
                 && ( cv2.c[1] > -halfMaxA )
                 && ( cv2.c[1] <  halfMaxA )
                 && ( cv2.c[2] > -halfMaxB )
                 && ( cv2.c[2] <  halfMaxB )
               )
            {
               ColorValue cvRGB  = ColorValue( r, g, b, TYPE_RGB );
               pLABCube[ (int)(cv2.c[0]) ]
                       [ (int)(cv2.c[1] + halfMaxA ) ]
                       [ (int)(cv2.c[2] + halfMaxB ) ] = cvRGB;
            }
         }
      }
   }
}


//----------------------------------------------------------

void ChromaticAdaptColorCube( ColorValue*** pLABCubeReference, int maxL, int maxA, int maxB, int stepSize )
{
   int halfMaxA = (int)( maxA / 2.0 );
   int halfMaxB = (int)( maxB / 2.0 );
   TransformColorSpace tc;
   TransformColorSpace tcsp;
   ChromaticAdaptationType adaptType = CHROMATICADAPTATION_XYZSCALING;
   //ChromaticAdaptationType adaptType = CHROMATICADAPTATION_BRADFORD;
   //ChromaticAdaptationType adaptType = CHROMATICADAPTATION_VONKRIES;
   
   ColorValue cvRefWhiteAdapted = ColorConstants::sD65_XYZ;
   cout << "Before adaptation, ref. white is " << cvRefWhiteAdapted << " and after ";
   cvRefWhiteAdapted.c[0] = 0.78;
   cvRefWhiteAdapted.c[1] = 0.82;
   cvRefWhiteAdapted.c[2] = 0.81;
   cout << ", ref. white is " << cvRefWhiteAdapted << endl << flush;
   
   ChromaticAdaptation ca( ColorConstants::sD65_XYZ, cvRefWhiteAdapted, adaptType );
   tc.SetReferenceWhite( cvRefWhiteAdapted );
   
   ofstream ofp1;
   ofp1.open( const_cast< char* >( "/v/frooms/public_html/warhol/AdaptationTest.html" ), ios::out | ios::binary );
   ofstream ofp2;
   ofp2.open( const_cast< char* >( "/v/frooms/public_html/warhol/LabVsLabAdapted.txt" ), ios::out | ios::binary );
   ofp1 << "<HTML><BODY><TABLE BORDER=1>" << endl;
   ofp1 << "<TR><TH> " << ColorConstants::sD65_XYZ << " </TH><TH> " << cvRefWhiteAdapted << " </TH><TH>Delta E 2000</TH></TR>" << endl;
   for (int l=0; l < maxL; l += stepSize )
   {
      for (int a=0; a < maxA; a += stepSize )
      {
         for (int b=0; b < maxB; b += stepSize )
         {
            ColorValue cvLAB  = ColorValue( l, (a - halfMaxA), (b - halfMaxB), TYPE_LAB );
            
            ColorValue cvLabAdapted = ca.AdaptLabColor( cvLAB );
            ColorValue cvRGBRef     = pLABCubeReference[ l ] [ a ][ b ];
            ColorValue cvRGBAdapted = ca.AdaptsRGBColor( cvRGBRef ); //tc.LabtosRGB( cvLabAdapted );
            
            ofp2 << cvLAB << "\t" << cvLabAdapted << endl << flush;
            
            cvRGBAdapted.c[0] = MathUtils::ClipValue( cvRGBAdapted.c[0], 0.0, 255.0);
            cvRGBAdapted.c[1] = MathUtils::ClipValue( cvRGBAdapted.c[1], 0.0, 255.0);
            cvRGBAdapted.c[2] = MathUtils::ClipValue( cvRGBAdapted.c[2], 0.0, 255.0);
            
            if ( ( cvRGBRef.c[0] > 0) && (cvRGBRef.c[1] > 0) && (cvRGBRef.c[2] > 0))
            {
               ofp1.precision(1);

               ofp1 << "<TR><TD WIDTH=600 BGCOLOR=#";
               ofp1 << hex << setfill('0') << setw(2) << (int)(cvRGBRef.c[0])
                    << hex << setfill('0') << setw(2) << (int)(cvRGBRef.c[1])
                    << hex << setfill('0') << setw(2) << (int)(cvRGBRef.c[2])
                    << dec << ">" << cvLAB << "<BR>" << cvRGBRef << "</TD><TD WIDTH=600 BGCOLOR=#"
                    << hex << setfill('0') << setw(2) << (int)(cvRGBAdapted.c[0])
                    << hex << setfill('0') << setw(2) << (int)(cvRGBAdapted.c[1])
                    << hex << setfill('0') << setw(2) << (int)(cvRGBAdapted.c[2])
                    << dec << ">" << cvLabAdapted << "<BR>" << cvRGBAdapted << "</TD><TD>" 
                    << tcsp.DeltaE2000( cvLAB, cvLabAdapted ) 
                    << "</TD></TR>" 
                    << endl << flush;
            }
         }
      }
   }
   ofp1 << "</TABLE></BODY></HTML>" << endl;
   ofp1.close();
   ofp2.close();
}

//----------------------------------------------------------

void VisualizeColorcube( ColorValue*** pLABCube, int maxL, int maxA, int maxB )
{
   // This allows us to visualize the sRGB space in L*a*b* coordinate space.
   // It is consistent with the slicer output from ColorThink software of Chromix.
   for (int l = 0; l < maxL; l+= 5 )
   {
      Image* pImg = new Image( maxA, maxB, 3 );
      for (int a=0; a < maxA; a++)
      {
         for (int b=0; b < maxB; b++)
         {
            pImg->SetColor( a, b, pLABCube[ l ][ a ][ b ] );
         }
      }
      stringstream ss;
      ss << "ImageRGB-" << setfill('0') << setw(3) << l << ".ppm";
      std::string fileName = ss.str();
      ImageIO::Write( pImg, fileName );
      delete pImg;
   }
}

//----------------------------------------------------------

void CleanupColorCube( ColorValue*** pLABCube, int maxL, int maxA )
{
   for (int l = 0; l < maxL; l++)
   {
      for( int a = 0; a < maxA; a++)
      {
         delete []pLABCube[ l ][ a ];
      }
      delete []pLABCube[ l ];
   }
   delete []pLABCube;
}

//----------------------------------------------------------

int main( /*int argc, char *argv[]*/ )
{
   int maxL = 110; // 0 to 100%
   int maxA = 256; // -128 to 127
   int maxB = 256; // -128 to 127
   
   ColorValue*** pLABCubeReference = CreateInitializedColorCube( maxL, maxA, maxB );
   
   cout << "Cube initialized" << endl << flush;
   
   FillColorCubeWithsRGBValues( pLABCubeReference, maxL, maxA, maxB );
   
   cout << "Cube filled with sRGB values " << endl << flush;
   
   //VisualizeColorcube( pLABCubeReference, maxL, maxA, maxB );
   
   //cout << "Cube visualization written to disc" << endl << flush;
   
   ChromaticAdaptColorCube( pLABCubeReference, maxL, maxA, maxB, 5 );
   
   cout << "Chromatic adaptation finished" << endl << flush;
   
   CleanupColorCube( pLABCubeReference, maxL, maxA );
   
   cout << "Data structure cleaned successfully; end..." << endl << flush;
  
   return EXIT_SUCCESS;
}
