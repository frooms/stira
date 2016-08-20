
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

#include "ImageIO.h"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include <cstdlib>

#include "../../common/common/StringUtils.h"
#include "../../common/common/MathUtils.h"
#include "NumberGridTools.h"
#include "../../imagedata/simpletools/GridConverter.h"

using namespace std;
namespace stira {
namespace imagetools {

using namespace common;

// 0. CONSTRUCTOR / DESTRUCTOR / OUTPUT TYPE ENUM
/////////////////////////////////////////////////

//------------------------------------------------------------------------------------------

ImageIO::ImageIO(){}

//------------------------------------------------------------------------------------------

ImageIO::~ImageIO(){}

//------------------------------------------------------------------------------------------

// 1. NATIVE SUPPORT FOR READING AND WRITING RAW PGM AND PPM IMAGES
///////////////////////////////////////////////////////////////////

   // 1.1. READING
   //--------------

Image* ImageIO::Read( std::string fname )
{
   std::string extension = StringUtils::ExtractFileExtension( fname, false );
   if(    ( extension == std::string("ppm") )
       || ( extension == std::string("pgm") )
       || ( extension == std::string("PPM") )
       || ( extension == std::string("PGM") )
     )
   {
      return ReadAsPXM( fname );
   }
   else
   {
      return ReadImageOpenCV( fname );
   }
}

Image* ImageIO::ReadAsPXM( std::string fname )
{
   ifstream ifp;
   char header [100];

   ifp.open(const_cast<char*>(fname.c_str()), ios::in | ios::binary);

   if (!ifp)
   {
      cout << "Can't read image: " << fname << endl;
      return 0;
   }

   // read header

   // 0049 = 1    ascii PBM
   // 0050 = 2    ascii PGM
   // 0051 = 3    ascii PPM
   // 0052 = 4    bin PBM
   // 0053 = 5    bin PGM
   // 0054 = 6    bin PPM

   ifp.getline(header,100,'\n');
   if (    (header[0] != 80)     /* ASCII code for 'P' */
        || (    (header[1] != 53)     /* ASCII code for '5' */
             && (header[1] != 54)     /* ASCII code for '6' */
           )
      )
   {
      cout << "Image " << fname << " is neither raw PGM nor PPM" << endl;
      exit(1);
   }
   ifp.close();

   switch (header[1])
   {
      case 53:
      {
         return ReadPGM( fname );
      }
      case 54:
      {
         return ReadPPM( fname );
      }
      default:
      {
         return 0;
      }
   }
}

//------------------------------------------------------------------------------------------

ArrayGrid<int>* ImageIO::ReadPGMasInt( std::string fname)
{
   unsigned char *charImage;
   char header [100], *ptr;

   ArrayGrid<int>* pGrid = 0;

   ifstream ifp;

   ifp.open(const_cast<char*>(fname.c_str()), ios::in | ios::binary);

   if (!ifp)
   {
      cout << "Can't read image: " << fname << endl;
      return 0;
   }

   // read header

   // 0049 = 1    ascii PBM
   // 0050 = 2    ascii PGM
   // 0051 = 3    ascii PPM
   // 0052 = 4    bin PBM
   // 0053 = 5    bin PGM
   // 0054 = 6    bin PPM

   ifp.getline(header,100,'\n');
   if (    (header[0] != 80)     /* ASCII code for 'P' */
        || (header[1] != 53)     /* ASCII code for '5' */
      )
   {
      cout << "Image " << fname << " is not PGM" << endl;
      exit(1);
   }

   ifp.getline(header,100,'\n');
   while(header[0]=='#')
   {
      ifp.getline(header,100,'\n');
   }

   int width  = strtol(header,&ptr,0);
   int height = atoi(ptr);

   pGrid = new ArrayGrid<int>(width, height);

   ifp.getline(header,100,'\n');
   //int maxIntensity = strtol(header, &ptr, 0);

   charImage = (unsigned char *) new unsigned char [width * height];

   ifp.read( reinterpret_cast<char *>(charImage), (width * height)*sizeof(unsigned char));

   if (ifp.fail())
   {
      cout << "Image " << fname << " has wrong size" << endl;
      return 0;
   }

   ifp.close();

   // Convert the unsigned characters to integers
   for(int y = 0; y<height; y++)
   {
      for(int x = 0; x<width; x++)
      {
         pGrid->SetValue(x, y, (int)(charImage[x + y * width]));
      }
   }

   delete [] charImage;

   return pGrid;
}

//------------------------------------------------------------------------------------------

Image* ImageIO::ReadPGM( std::string fname)
{
   //int maxIntensity;
   unsigned char *charImage;
   char header [100], *ptr;

   Image* pImage = 0;

   ifstream ifp;

   ifp.open(const_cast<char*>(fname.c_str()), ios::in | ios::binary);

   if (!ifp)
   {
      cout << "Can't read image: " << fname << endl;
      return 0;
   }

   // read header

   // 0049 = 1    ascii PBM
   // 0050 = 2    ascii PGM
   // 0051 = 3    ascii PPM
   // 0052 = 4    bin PBM
   // 0053 = 5    bin PGM
   // 0054 = 6    bin PPM

   ifp.getline(header,100,'\n');
   if (    (header[0] != 80)     // ASCII code for 'P'
        || (header[1] != 53)     // ASCII code for '5'
      )
   {
      cout << "Image " << fname << " is not PGM" << endl;
      exit(1);
   }

   ifp.getline(header,100,'\n');
   while(header[0]=='#')
   {
      ifp.getline(header,100,'\n');
   }

   int width  = strtol(header,&ptr,0);
   int height = atoi(ptr);

   pImage = new Image(width, height, 1);

   ifp.getline(header,100,'\n');

   charImage = (unsigned char *) new unsigned char [width * height];

   ifp.read( reinterpret_cast<char *>(charImage), (width * height)*sizeof(unsigned char));

   if (ifp.fail())
   {
      cout << "Image " << fname << " has wrong size" << endl;
      return 0;
   }

   ifp.close();

   // Convert the unsigned characters to integers
   for(int y = 0; y<height; y++)
   {
      for(int x = 0; x<width; x++)
      {
         pImage->GetBands()[0]->SetValue(x, y, (int)(charImage[x + y * width]));
      }
   }

   delete [] charImage;
   pImage->SetImageName( StringUtils::ExtractFileNameRoot( fname ) );
   return pImage;
}

//------------------------------------------------------------------------------------------

Image* ImageIO::ReadPPM( std::string fname)
{
   unsigned char *charImage;
   char header [100], *ptr;

   Image* pImage = 0;

   ifstream ifp;

   ifp.open( const_cast<char*>(fname.c_str()), ios::in | ios::binary );

   if (!ifp)
   {
      cout << "Can't read image: " << fname << endl;
      return 0;
   }

   // read header

   // 0049 = 1    ascii PBM
   // 0050 = 2    ascii PGM
   // 0051 = 3    ascii PPM
   // 0052 = 4    bin PBM
   // 0053 = 5    bin PGM
   // 0054 = 6    bin PPM

   ifp.getline(header,100,'\n');
   if (    (header[0] != 80)     /* ASCII code for 'P' */
        || (header[1] != 54)     /* ASCII code for '6' */
      )
   {
      cout << "Image " << fname << " is not PPM" << endl;
      exit(1);
   }

   ifp.getline(header,100,'\n');
   cout << header[0] << endl << flush;
   while ( (header[0]=='#') || (header[0]==35)) // contains comment or newline
   {
      cout << header[0] << header << endl << flush;
      ifp.getline(header,100,'\n');
   }
   cout << header[0] << header << endl << flush;

   int width  = strtol(header,&ptr,0);
   int height = atoi(ptr);

   pImage = new Image(width, height, 3);

   ifp.getline(header,100,'\n');
   //int maxIntensity = strtol(header, &ptr, 0);

   charImage = (unsigned char *) new unsigned char [3 * width * height];

   ifp.read( reinterpret_cast<char *>(charImage), (3 * width * height) * sizeof(unsigned char));

   if (ifp.fail())
   {
      cout << "Image " << fname << " has wrong size" << endl;
      return 0;
   }

   ifp.close();

   // Convert the unsigned characters to integers

   for(int y = 0; y<height; y++)
   {
      for(int x = 0; x<width; x++)
      {
         for (int bandNr = 0; bandNr < 3; bandNr++)
         {
            pImage->GetBands()[bandNr]->SetValue(x, y, (int)(charImage[3 * (x + y * width) + bandNr]));
         }
      }
   }

   delete [] charImage;

   pImage->SetImageName( StringUtils::ExtractFileNameRoot( fname ) );
   return pImage;
}

//------------------------------------------------------------------------------------------

   // 1.2. WRITING
   //--------------

bool ImageIO::Write( Image* pImage, std::string fname, outputType outtype)
{
   if (pImage != 0)
   {
      if (pImage->GetNumberOfBands() == 1)
      {
         WritePGM( pImage, fname, outtype);
         return true;
      }
      if (pImage->GetNumberOfBands() == 3)
      {
         WritePPM( pImage, fname, outtype);
         return true;
      }
   }
   return false;
}

//------------------------------------------------------------------------------------------

void ImageIO::WritePGM( ArrayGrid< std::complex<double> >* pGrid, std::string fileName, outputType myOutType)
{
   ArrayGrid<double>* pRealGrid = new ArrayGrid<double>(pGrid->GetWidth(), pGrid->GetHeight());
   ArrayGrid<double>* pImagGrid = new ArrayGrid<double>(pGrid->GetWidth(), pGrid->GetHeight());
   for (int y = 0; y < pGrid->GetHeight(); y++)
   {
      for (int x = 0; x < pGrid->GetWidth(); x++)
      {
         pRealGrid->SetValue( x, y, (pGrid->GetValue(x, y)).real() );
         pImagGrid->SetValue( x, y, (pGrid->GetValue(x, y)).imag() );
      }
   }
   std::stringstream ss1, ss2;
   ss1 << fileName << "-real.ppm";
   ss2 << fileName << "-imag.ppm";

   std::string string1 = ss1.str();
   std::string string2 = ss2.str();

   WritePGM( pRealGrid, string1, myOutType );
   WritePGM( pImagGrid, string2, myOutType );
}

//------------------------------------------------------------------------------------------

bool ImageIO::WritePGM( ArrayGrid<double>* pGrid, std::string fileName, outputType outtype)
{
   unsigned char *charImage;
   ofstream ofp;

   int width  = pGrid->GetWidth();
   int height = pGrid->GetHeight();

   ArrayGrid<double>* pRescaledGrid = pGrid->Clone();

   RescaleGrid(pRescaledGrid, outtype);

   charImage = (unsigned char *) new unsigned char [width * height];

   // convert the integer values to unsigned char
   for(int y=0; y<height; y++)
   {
      for(int x=0; x<width; x++)
      {
         double tmpValue = (double)(pRescaledGrid->GetValue(x, y) + 0.5);
         if (tmpValue > 255.0) {tmpValue = 255.0;}
         if (tmpValue <   0.0) {tmpValue =   0.0;}
         charImage[x + y * width] = (unsigned char)(tmpValue);
      }
   }

   delete pRescaledGrid;

   ofp.open(const_cast<char*>( fileName.c_str()), ios::out);

   if (!ofp)
   {
      cout << "Can't open file: " << fileName << endl;
      return false;
   }

   ofp << "P5" << endl;
   ofp << width << " " << height << endl;
   ofp << 255 << endl;

   ofp.write( reinterpret_cast<char *>(charImage), (width * height)*sizeof(unsigned char));

   if (ofp.fail())
   {
      cout << "Can't write image " << fileName << endl;
      return false;
   }

   ofp.close();

   delete [] charImage;

   return true;
}

//------------------------------------------------------------------------------------------

bool ImageIO::WritePGM( ArrayGrid<int>* pGrid, std::string fileName, outputType outtype)
{
   ArrayGrid<double>* pDoubleGrid = 0;

   int width  = pGrid->GetWidth();
   int height = pGrid->GetHeight();

   pDoubleGrid = new ArrayGrid<double>(width, height);

   for(int y=0; y<height; y++)
   {
      for(int x=0; x<width; x++)
      {
         pDoubleGrid->SetValue( x, y, (double)(pGrid->GetValue( x, y ) ) );
      }
   }
   WritePGM( pDoubleGrid, fileName, outtype);
   delete pDoubleGrid;

   return true;
}

//------------------------------------------------------------------------------------------

bool ImageIO::WritePGM( ArrayGrid<bool>* pGrid, std::string fileName )
{
   unsigned char *charImage;
   ofstream ofp;

   int width  = pGrid->GetWidth();
   int height = pGrid->GetHeight();

   charImage = (unsigned char *) new unsigned char [width * height];

   // convert the integer values to unsigned char
   int nrTruePixels = 0;
   for(int y=0; y<height; y++)
   {
      for(int x=0; x<width; x++)
      {
         if (pGrid->GetValue(x, y) == true )
         {
            charImage[x + y * width] = (unsigned char)(255);
            nrTruePixels++;
         }
         else
         {
            charImage[x + y * width] = (unsigned char)(0);
         }
      }
   }

   ofp.open(const_cast<char*>( fileName.c_str()), ios::out);

   if (!ofp)
   {
      cout << "Can't open file: " << fileName << endl;
      return false;
   }

   ofp << "P5" << endl;
   ofp << width << " " << height << endl;
   ofp << 255 << endl;

   ofp.write( reinterpret_cast<char *>(charImage), (width * height)*sizeof(unsigned char));

   if (ofp.fail())
   {
      cout << "Can't write image " << fileName << endl;
      return false;
   }

   ofp.close();

   delete [] charImage;

   return true;
}

//------------------------------------------------------------------------------------------

bool ImageIO::WriteTXT( ArrayGrid<double>* pGrid, std::string fileName)
{
   ofstream ofp;

   int width  = pGrid->GetWidth();
   int height = pGrid->GetHeight();

   ofp.open(const_cast<char*>(fileName.c_str()), ios::out);

   if (!ofp)
   {
      cerr << "Can't open file: " << fileName << endl;
      return false;
   }
   // convert the integer values to unsigned char

   ofp << std::string("\t");
   for(int x = 0; x < width; x++)
   {
      ofp << x << std::string("\t");
   }
   ofp << endl;

   for(int y = 0; y < height; y++)
   {
      ofp << y << std::string("\t");
      for(int x = 0; x < width; x++)
      {
         ofp << pGrid->GetValue(x, y) << std::string("\t");
      }
      ofp << endl;
   }

   ofp.close();
   return true;
}

//------------------------------------------------------------------------------------------

bool ImageIO::WritePGM(Image* pImage, std::string fname, outputType outtype)
{
   unsigned char *charImage;
   ofstream ofp;

   int width  = pImage->GetWidth();
   int height = pImage->GetHeight();

   Image* pImageOut = pImage->Clone();

   for (int bandID = 0; bandID < pImage->GetNumberOfBands(); bandID++)
   {
      RescaleGrid(pImageOut->GetBands()[bandID], outtype);
   }

   charImage = (unsigned char *) new unsigned char [width * height];

   // convert the integer values to unsigned char
   for(int y=0; y<height; y++)
   {
      for(int x=0; x<width; x++)
      {
         double ttmp = pImageOut->GetBands()[0]->GetValue(x, y);
         if (ttmp > 254.5) {ttmp = 255.0;}
         if (ttmp <   0.5) {ttmp =   0.0;}
         charImage[x + y * width] = (unsigned char)(ttmp);
      }
   }
   delete pImageOut;
   ofp.open(const_cast<char*>(fname.c_str()), ios::out);

   if (!ofp)
   {
      cout << "Can't open file: " << fname << endl;
      return false;
   }

   ofp << "P5" << endl;
   ofp << width << " " << height << endl;
   ofp << 255 << endl;

   ofp.write( reinterpret_cast<char *>(charImage), (width * height)*sizeof(unsigned char));

   if (ofp.fail())
   {
      cout << "Can't write image " << fname << endl;
      return false;
   }

   ofp.close();

   delete [] charImage;

   return true;
}

//------------------------------------------------------------------------------------------

bool ImageIO::WritePPM(Image* pImage, std::string fname, outputType outtype)
{
   unsigned char *charImage;
   bool hasNan;

   int width  = pImage->GetWidth();
   int height = pImage->GetHeight();

   Image* pImageOut = pImage->Clone(); // otherwise rescaling source image itself

   for (int bandID = 0; bandID < pImage->GetNumberOfBands(); bandID++)
   {
      RescaleGrid(pImageOut->GetBands()[bandID], outtype);
   }

   charImage = (unsigned char *) new unsigned char [3 * width * height];

   // convert the integer values to unsigned char
   for(int y=0; y<height; y++)
   {
      for(int x=0; x<width; x++)
      {
         hasNan = false;
         for (int bandNr = 0; bandNr < 3; bandNr++)
         {
            double ttmp = pImageOut->GetBands()[bandNr]->GetValue(x, y);
#if defined (__WIN32__) || defined(_WIN64)
            if ( _isnan( ttmp ) )
#else
            if ( isnan( ttmp ) )
#endif
            {
               hasNan = true;
            }
            if (ttmp > 254.5) {ttmp = 255.0;}
            if (ttmp <   0.5) {ttmp =   0.0;}
            charImage[3*(x + y * width) + bandNr] = (unsigned char)(ttmp);
         }
         if ( hasNan == true )
         {
            charImage[3*(x + y * width)] = (unsigned char)(255);
            charImage[3*(x + y * width) + 1] = (unsigned char)(0);
            charImage[3*(x + y * width) + 2] = (unsigned char)(0);

         }
      }
   }
   delete pImageOut;

   ofstream ofp;
   ofp.open(const_cast<char*>(fname.c_str()), ios::out | ios::binary);

   if (!ofp)
   {
      cout << "Can't open file: " << fname << endl;
      return false;
   }

   ofp << "P6" << endl;
   ofp << width << " " << height << endl;
   ofp << 255 << endl;

   ofp.write( reinterpret_cast<char *>(charImage), (3 * width * height) * sizeof( unsigned char ) );

   if (ofp.fail())
   {
      cout << "Can't write image " << fname << endl;
      return false;
   }

   ofp.close();

   delete [] charImage;

   return true;
}

//------------------------------------------------------------------------------------------

// 2.0 OTHER FORMATS THROUGH OpenCV
/////////////////////////////////////

double ImageIO::GetOpenCvGrayValue(IplImage* pIplImage, int x, int y )
{
   return (double)( ((uchar *)( pIplImage->imageData + y * pIplImage->widthStep ) )[ x ] );
}

//------------------------------------------------------------------------------------------------------------

void ImageIO::SetOpenCvGrayValue(IplImage* pIplImage, int x, int y, double value )
{
   ((uchar *)( pIplImage->imageData + y * pIplImage->widthStep ) )[ x ] = (uchar)( MathUtils::ClipValue( value, 0.0, 255.0 ) );
}

//------------------------------------------------------------------------------------------------------------

double ImageIO::GetOpenCvColorValue(IplImage* pIplImage, int x, int y, int bandNr )
{
   return (double)( ((uchar *)( pIplImage->imageData + y * pIplImage->widthStep ) )[ x * pIplImage->nChannels + ( 2 - bandNr) ] );
}

//------------------------------------------------------------------------------------------------------------

void ImageIO::SetOpenCvColorValue(IplImage* pIplImage, int x, int y, int bandNr, double value )
{
    ((uchar *)( pIplImage->imageData + y * pIplImage->widthStep ) )[ x * pIplImage->nChannels + bandNr ] = (uchar)(value);
}

//------------------------------------------------------------------------------------------------------------

ArrayGrid<double>* ImageIO::ConvertOpenCvToDoubleArrayGrid( IplImage* pIplImage, ArrayGrid<double>* pGrid )
{
   int width = pIplImage->width;
   int height = pIplImage->height;
   int nrBands = pIplImage->nChannels;

   if ( pGrid == 0 )
   {
      pGrid = new ArrayGrid<double>( width, height );
   }

   if (nrBands == 3)
   {
      for ( int y = 0; y < height; y++ )
      {
         for ( int x = 0; x < width; x++ )
         {
            double tmpValue = 0.0;
            for (int k = 0; k < nrBands; k++ )
            {
               tmpValue += GetOpenCvColorValue( pIplImage, x, y, k );
            }
            pGrid->SetValue( x, y, tmpValue / nrBands );
         }
      }
   }
   else
   {
      for ( int y = 0; y < height; y++ )
      {
         for ( int x = 0; x < width; x++ )
         {
            pGrid->SetValue( x, y, GetOpenCvGrayValue( pIplImage, x, y ) );
         }
      }
   }
   return pGrid;
}

//------------------------------------------------------------------------------------------------------------

ArrayGrid<bool>* ImageIO::ConvertOpenCvToBooleanArrayGrid( IplImage* pIplImage, double threshold )
{
   int width = pIplImage->width;
   int height = pIplImage->height;
   ArrayGrid<bool>* pGrid = new ArrayGrid<bool>( width, height );

   for ( int y = 0; y < height; y++ )
   {
      for ( int x = 0; x < width; x++ )
      {
         int tmpValue = GetOpenCvGrayValue( pIplImage, x, y );
         if ( tmpValue > threshold )
         {
            pGrid->SetValue( x, y, true );
         }
         else
         {
            pGrid->SetValue( x, y, false );
         }
      }
   }

   return pGrid;
}

//------------------------------------------------------------------------------------------------------------

IplImage* ImageIO::ConvertArrayGridToOpenCv( ArrayGrid<double>* pGrid, IplImage* pIplImage )
{
   int width  = pGrid->GetWidth();
   int height = pGrid->GetHeight();

   int nrBands = 1;

   if ( pIplImage == 0 )
   {
      pIplImage = cvCreateImage( cvSize(width, height), IPL_DEPTH_8U, nrBands );
   }
   else
   {
      assert( pIplImage->width == width );
      assert( pIplImage->height == height );
   }

   for ( int y = 0; y < height; y++ )
   {
      for ( int x = 0; x < width; x++ )
      {
         SetOpenCvGrayValue( pIplImage, x, y, pGrid->GetValue( x, y ) );
      }
   }
   return pIplImage;
}

//------------------------------------------------------------------------------------------------------------

Image* ImageIO::ConvertOpenCvToImage( IplImage* pIplImage )
{
   int width = pIplImage->width;
   int height = pIplImage->height;
   int nrBands = pIplImage->nChannels;
   Image* pImage = new Image( width, height, nrBands );

   if (nrBands == 3)
   {
      for (int k = 0; k < nrBands; k++ )
      {
         for ( int y = 0; y < height; y++ )
         {
            for ( int x = 0; x < width; x++ )
            {
               pImage->GetBands()[k]->SetValue( x, y, GetOpenCvColorValue( pIplImage, x, y, k ) );
            }
         }
      }
   }
   else
   {
      for ( int y = 0; y < height; y++ )
      {
         for ( int x = 0; x < width; x++ )
         {
            pImage->GetBands()[0]->SetValue( x, y, GetOpenCvGrayValue( pIplImage, x, y ) );
         }
      }
   }
   return pImage;
}

//------------------------------------------------------------------------------------------------------------

IplImage* ImageIO::ConvertImageToOpenCv( Image* pImage )
{
   int width  = pImage->GetWidth();
   int height = pImage->GetHeight();

   int nrBands = pImage->GetNumberOfBands();

   IplImage* pIplImage = cvCreateImage( cvSize(width, height), IPL_DEPTH_8U, nrBands );

   if (nrBands == 3)
   {
      for (int k = 0; k < nrBands; k++ )
      {
         for ( int y = 0; y < height; y++ )
         {
            for ( int x = 0; x < width; x++ )
            {
               SetOpenCvColorValue( pIplImage, x, y, k, pImage->GetBands()[k]->GetValue( x, y ) );
            }
         }
      }
   }
   else
   {
      for ( int y = 0; y < height; y++ )
      {
         for ( int x = 0; x < width; x++ )
         {
            SetOpenCvGrayValue( pIplImage, x, y, pImage->GetBands()[0]->GetValue( x, y ) );
         }
      }
   }
   return pIplImage;
}

//------------------------------------------------------------------------------------------------------------

Image* ImageIO::ReadImageOpenCV( std::string fname, bool useROI, RectangularROI<int> myImageROI )
{
   // flag: >0 the loaded image is forced to be a 3-channel color image
   //       =0 the loaded image is forced to be a 1 channel grayscale image
   //       <0 the loaded image is loaded as is (with number of channels in the file).
   int flag = -1;
   IplImage* pImg = 0;
   pImg = cvLoadImage( fname.c_str(), flag );

   if ( pImg != 0)
   {
      int height    = pImg->height;
      int width     = pImg->width;
      int channels  = pImg->nChannels;

      int bottomX = 0;
      int bottomY = 0;
      int topX = 0;
      int topY = 0;
      if (useROI)
      {
         topX = myImageROI.GetTopLeftCorner().x;
         topY = myImageROI.GetTopLeftCorner().y;
         bottomX = myImageROI.GetBottomRightCorner().x;
         bottomY = myImageROI.GetBottomRightCorner().y;
      }
      else
      {
         topX = 0;
         topY = 0;
         bottomX = width;
         bottomY = height;
      }

      int nrBands = channels;
      if ( nrBands > 3) { nrBands = 3; }
      assert ( topX < bottomX );
      assert ( topY < bottomY );

      topX    = common::MathUtils::ClipValue( topX,    0, width );
      bottomX = common::MathUtils::ClipValue( bottomX, 0, width );
      topY    = common::MathUtils::ClipValue( topY,    0, height );
      bottomY = common::MathUtils::ClipValue( bottomY, 0, height );

      assert ( topX >= 0 );      assert ( bottomX >= 0 );       assert ( topY >= 0 );       assert ( bottomY >= 0 );
      assert ( topX <= width );  assert ( bottomX <= width );   assert ( topY <= height );  assert ( bottomY <= height );

      int subWidth  = bottomX - topX;
      int subHeight = bottomY - topY;

      Image* pImage = new Image( subWidth, subHeight, nrBands );

      if (pImg->channelSeq[0] == 'B')  // first channel B, so BGR
      {
         for (int y = topY; y < bottomY; y++)
         {
            for (int x = topX; x < bottomX; x++)
            {
               for (int k = 0; k < nrBands; k++)
               {
                  double tmpValue = (double)(((unsigned char *)( pImg->imageData + y * pImg->widthStep ) )[ x * pImg->nChannels + k ] );
                  pImage->GetBands()[2-k]->SetValue( x - topX, y - topY, tmpValue );
               }
            }
         }
      }
      else
      {
         for (int y = topY; y < bottomY; y++)
         {
            for (int x = topX; x < bottomX; x++)
            {
               for (int k = 0; k < nrBands; k++)
               {
                  double tmpValue = (double)(((unsigned char *)( pImg->imageData + y * pImg->widthStep ) )[ x * pImg->nChannels + k ] );
                  pImage->GetBands()[k]->SetValue( x - topX, y - topY, tmpValue );
               }
            }
         }
      }

      cvReleaseImage( &pImg );
      return pImage;
   }
   else
   {
      cerr << "ERROR: failed to load image : " << fname << endl << flush;
      return 0;
   }
}

//------------------------------------------------------------------------------------------------------------

ArrayGrid<double>* ImageIO::ReadArrayOpenCVAsDouble( std::string fname, ArrayGrid<double>* pGrid, bool useROI, RectangularROI<int> myImageROI )
{
   // flag: >0 the loaded image is forced to be a 3-channel color image
   //       =0 the loaded image is forced to be a 1 channel grayscale image
   //       <0 the loaded image is loaded as is (with number of channels in the file).
   int flag = -1;
   IplImage* pImg = 0;
   pImg = cvLoadImage( fname.c_str(), flag );

   if ( pImg != 0)
   {
      int height    = pImg->height;
      int width     = pImg->width;

      int bottomX = 0;
      int bottomY = 0;
      int topX = 0;
      int topY = 0;
      if (useROI)
      {
         topX = myImageROI.GetTopLeftCorner().x;
         topY = myImageROI.GetTopLeftCorner().y;
         bottomX = myImageROI.GetBottomRightCorner().x;
         bottomY = myImageROI.GetBottomRightCorner().y;
      }
      else
      {
         topX = 0;
         topY = 0;
         bottomX = width;
         bottomY = height;
      }

      assert ( topX < bottomX );
      assert ( topY < bottomY );

      topX    = common::MathUtils::ClipValue( topX,    0, width );
      bottomX = common::MathUtils::ClipValue( bottomX, 0, width );
      topY    = common::MathUtils::ClipValue( topY,    0, height );
      bottomY = common::MathUtils::ClipValue( bottomY, 0, height );

      assert ( topX >= 0 );      assert ( bottomX >= 0 );       assert ( topY >= 0 );       assert ( bottomY >= 0 );
      assert ( topX <= width );  assert ( bottomX <= width );   assert ( topY <= height );  assert ( bottomY <= height );

      int subWidth  = bottomX - topX;
      int subHeight = bottomY - topY;

      if ( pGrid == 0 )
      {
         pGrid = new ArrayGrid<double>( subWidth, subHeight );
      }

      for (int y = topY; y < bottomY; y++)
      {
         for (int x = topX; x < bottomX; x++)
         {
            double tmpValue = (double)(((unsigned char *)( pImg->imageData + y * pImg->widthStep ) )[ x * pImg->nChannels ] );
            pGrid->SetValue( x - topX, y - topY, tmpValue );
         }
      }

      cvReleaseImage( &pImg );
      return pGrid;
   }
   else
   {
      cerr << "ERROR: failed to load image : " << fname << endl << flush;
      return 0;
   }
}


//------------------------------------------------------------------------------------------------------------

ArrayGrid<int>* ImageIO::ReadArrayOpenCVAsInt( std::string fname, bool useROI, RectangularROI<int> myImageROI )
{
   // flag: >0 the loaded image is forced to be a 3-channel color image
   //       =0 the loaded image is forced to be a 1 channel grayscale image
   //       <0 the loaded image is loaded as is (with number of channels in the file).
   int flag = -1;
   IplImage* pImg = 0;
   pImg = cvLoadImage( fname.c_str(), flag );

   if ( pImg != 0)
   {
      int height    = pImg->height;
      int width     = pImg->width;

      int bottomX = 0;
      int bottomY = 0;
      int topX = 0;
      int topY = 0;
      if (useROI)
      {
         topX = myImageROI.GetTopLeftCorner().x;
         topY = myImageROI.GetTopLeftCorner().y;
         bottomX = myImageROI.GetBottomRightCorner().x;
         bottomY = myImageROI.GetBottomRightCorner().y;
      }
      else
      {
         topX = 0;
         topY = 0;
         bottomX = width;
         bottomY = height;
      }

      assert ( topX < bottomX );
      assert ( topY < bottomY );

      topX    = common::MathUtils::ClipValue( topX,    0, width );
      bottomX = common::MathUtils::ClipValue( bottomX, 0, width );
      topY    = common::MathUtils::ClipValue( topY,    0, height );
      bottomY = common::MathUtils::ClipValue( bottomY, 0, height );

      assert ( topX >= 0 );      assert ( bottomX >= 0 );       assert ( topY >= 0 );       assert ( bottomY >= 0 );
      assert ( topX <= width );  assert ( bottomX <= width );   assert ( topY <= height );  assert ( bottomY <= height );

      int subWidth  = bottomX - topX;
      int subHeight = bottomY - topY;

      ArrayGrid<int>* pGrid = new ArrayGrid<int>( subWidth, subHeight );

      for (int y = topY; y < bottomY; y++)
      {
         for (int x = topX; x < bottomX; x++)
         {
            int tmpValue = (int)(((unsigned char *)( pImg->imageData + y * pImg->widthStep ) )[ x * pImg->nChannels ] );
            pGrid->SetValue( x - topX, y - topY, tmpValue );
         }
      }

      cvReleaseImage( &pImg );
      return pGrid;
   }
   else
   {
      cerr << "ERROR: failed to load image : " << fname << endl << flush;
      return 0;
   }
}

//------------------------------------------------------------------------------------------

bool ImageIO::WriteOpenCV( Image* pImage, std::string fname, outputType outtype )
{
   int height    = pImage->GetHeight();
   int width     = pImage->GetWidth();
   int channels  = pImage->GetNumberOfBands();

   Image* pImageClone = 0;

   if ( outtype != ImageIO::NULL_OUT )
   {
      pImageClone = pImage->Clone();
      for (int k = 0; k < channels; k++)
      {
         RescaleGrid( pImageClone->GetBands()[k], outtype );
      }
   }
   else
   {
      pImageClone = pImage;
   }

   IplImage* pImg = cvCreateImage(cvSize( width, height ), IPL_DEPTH_8U, channels);

   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         for (int k = 0; k < channels; k++)
         {
            ( (unsigned char *)( pImg->imageData + y * pImg->widthStep) )[ x * pImg->nChannels + k]
                  = (unsigned char)(pImage->GetBands()[k]->GetValue( x, y ));
         }
      }
   }
   cvSaveImage( fname.c_str(), pImg );
   if ( outtype != ImageIO::NULL_OUT )
   {
      delete pImageClone;
   }

   cvReleaseImage( &pImg );
   return true;
}

//------------------------------------------------------------------------------------------

bool ImageIO::WriteOpenCV( ArrayGrid<double>* pGrid, std::string fname, outputType outtype )
{
   int height    = pGrid->GetHeight();
   int width     = pGrid->GetWidth();
   //cout << "At ImageIO: width = " << width << " and height = " << height << endl;

   ArrayGrid<double>* pGridClone = 0;

   if ( outtype != ImageIO::NULL_OUT )
   {
      pGridClone = pGrid->Clone();
      RescaleGrid( pGridClone, outtype );
   }
   else
   {
      pGridClone = pGrid;
   }

   int channels = 1;
   IplImage* pImg = cvCreateImage( cvSize( width, height ), IPL_DEPTH_8U, channels );

   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         ( (unsigned char *)( pImg->imageData + y * pImg->widthStep) )[ x ]
               = (unsigned char)( pGridClone->GetValue( x, y ));
      }
   }
   cvSaveImage( fname.c_str(), pImg );
   if ( outtype != ImageIO::NULL_OUT )
   {
      delete pGridClone;
   }

   cvReleaseImage( &pImg );
   return true;
}

//------------------------------------------------------------------------------------------

bool ImageIO::WriteOpenCV( ArrayGrid<int>* pGrid, std::string fname, outputType outtype )
{
   int height    = pGrid->GetHeight();
   int width     = pGrid->GetWidth();
   ArrayGrid<double>* pGridDouble = GridConverter::ConvertToDouble( pGrid );

   if ( outtype != ImageIO::NULL_OUT )
   {
      RescaleGrid( pGridDouble, outtype );
   }

   int channels = 1;
   IplImage* pImg = cvCreateImage( cvSize( width, height ), IPL_DEPTH_8U, channels );

   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         ( (unsigned char *)( pImg->imageData + y * pImg->widthStep) )[ x ]
               = (unsigned char)( pGridDouble->GetValue( x, y ));
      }
   }
   cvSaveImage( fname.c_str(), pImg );

   delete pGridDouble;

   cvReleaseImage( &pImg );
   return true;
}

//------------------------------------------------------------------------------------------

bool ImageIO::WriteOpenCV( ArrayGrid<bool>* pGrid, std::string fname )
{
   int height    = pGrid->GetHeight();
   int width     = pGrid->GetWidth();

   int channels = 1;
   IplImage* pImg = cvCreateImage( cvSize( width, height ), IPL_DEPTH_8U, channels );

   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         bool localValue = pGrid->GetValue( x, y );
         if ( localValue )
         {
            ( (unsigned char *)( pImg->imageData + y * pImg->widthStep) )[ x ] = (unsigned char)( 255 );
         }
         else
         {
            ( (unsigned char *)( pImg->imageData + y * pImg->widthStep) )[ x ] = (unsigned char)( 0 );
         }
      }
   }
   cvSaveImage( fname.c_str(), pImg );
   cvReleaseImage( &pImg );
   return true;
}

//------------------------------------------------------------------------------------------

// 3.0 HELPER METHODS
/////////////////////

void ImageIO::GetInputMinMax( ArrayGrid<double>* pGrid, double& mmin, double& mmax, outputType myType )
{
   mmax = -1000000000000000000000.0;
   mmin =  1000000000000000000000.0;

   int width  = pGrid->GetWidth();
   int height = pGrid->GetHeight();

   switch( myType )
   {
      case NORMAL_OUT:
      case GRADIENT_OUT:
      case NULL_OUT:
      case ABSOLUTE_NEG_OUT:
      case ABSOLUTE_POS_OUT:
      {
         for (int y = 0; y < height; y++)
         {
            for (int x = 0; x < width; x++)
            {
               double tmpValue = pGrid->GetValue(x, y);
               if ( tmpValue < mmin ) { mmin = tmpValue; }
               if ( tmpValue > mmax ) { mmax = tmpValue; }
            }
         }
         break;
      }
      case ABSOLUTE_NORM_OUT:
      {
         for (int y = 0; y < height; y++)
         {
            for (int x = 0; x < width; x++)
            {
               double tmpValue = fabs( pGrid->GetValue(x, y) );
               if ( tmpValue < mmin ) { mmin = tmpValue; }
               if ( tmpValue > mmax ) { mmax = tmpValue; }
            }
         }
         break;
      }
      case LOG_OUT:
      {
         for (int y = 0; y < height; y++)
         {
            for (int x = 0; x < width; x++)
            {
               double tmpValue = log( pGrid->GetValue(x, y) + 1.0);
               if ( tmpValue < mmin ) { mmin = tmpValue; }
               if ( tmpValue > mmax ) { mmax = tmpValue; }
            }
         }
         break;
      }
   }
}

//------------------------------------------------------------------------------------------

bool ImageIO::RescaleGrid( ArrayGrid<double>* pGrid, outputType outtype)
{
   double mmax = -1000000000000000000000.0;
   double mmin =  1000000000000000000000.0;

   ImageIO::GetInputMinMax( pGrid, mmin, mmax, outtype );

   int width  = pGrid->GetWidth();
   int height = pGrid->GetHeight();

   #ifdef DEBUG_OUT_BEFORE
   cout << "ImageIO::RescaleGrid mmax = " << mmax << "\t mmin = " << mmin << endl << flush;
   #endif

   if ((mmax - mmin) < 0.0001)
   {
      for (int y = 0; y < pGrid->GetHeight(); y++)
      {
         for (int x = 0; x < pGrid->GetWidth(); x++)
         {
            pGrid->SetValue(x, y, mmax);
         }
      }
   }
   else
   {
      switch(outtype)
      {
         case NORMAL_OUT:
         {
            #ifdef DEBUG_OUT_AFTER
            cout << "rescaling normal" << endl << flush;
            #endif
            for (int y = 0; y < height; y++)
            {
               for (int x = 0; x < width; x++)
               {
                  double ttmp = (255.0 / (mmax - mmin)) * (pGrid->GetValue(x, y) - mmin);
                  if (ttmp < 0.0) {ttmp = 0.0;}
                  if (ttmp > 255.0) {ttmp = 255.0;}
                  pGrid->SetValue(x, y, ttmp);
               }
            }
            break;
         }
         case GRADIENT_OUT:
         {
            #ifdef DEBUG_OUT_AFTER
            cout << "rescaling gradient" << endl << flush;
            #endif
            for (int y = 0; y < height; y++)
            {
               for (int x = 0; x < width; x++)
               {
                  double ttmp = 127.0 + (127.0 / (mmax - mmin)) * pGrid->GetValue(x, y);
                  if (ttmp < 0.0) {ttmp = 0.0;}
                  if (ttmp > 255.0) {ttmp = 255.0;}
                  pGrid->SetValue(x, y, ttmp);
               }
            }
            break;
         }

         case ABSOLUTE_NORM_OUT:
         {
            #ifdef DEBUG_OUT_AFTER
            cout << "rescaling absolute value" << endl << flush;
            #endif
            for (int y = 0; y < height; y++)
            {
               for (int x = 0; x < width; x++)
               {
                  double ttmp = (255.0 / (mmax - mmin)) * (fabs(pGrid->GetValue(x, y)) - mmin);
                  if (ttmp < 0.0) {ttmp = 0.0;}
                  if (ttmp > 255.0) {ttmp = 255.0;}
                  pGrid->SetValue(x, y, ttmp);
               }
            }
            break;
         }

         case ABSOLUTE_POS_OUT:
         case ABSOLUTE_NEG_OUT:
         {
            if (outtype == ABSOLUTE_NEG_OUT)
            {
               pGrid->MultiplyWith( -1.0 );

               if ( mmin < 0 && mmax > 0)
               GetInputMinMax( pGrid, mmin, mmax, outtype );
            }
            NumberGridTools<double>::ClipValues( pGrid, 0, mmax );

            #ifdef DEBUG_OUT_AFTER
            cout << "rescaling absolute value" << endl << flush;
            #endif
            for (int y = 0; y < height; y++)
            {
               for (int x = 0; x < width; x++)
               {
                  double ttmp = (255.0 / mmax ) * pGrid->GetValue(x, y);
                  if (ttmp < 0.0) {ttmp = 0.0;}
                  if (ttmp > 255.0) {ttmp = 255.0;}
                  pGrid->SetValue(x, y, ttmp);
               }
            }
            break;
         }
         case LOG_OUT:
         {
            #ifdef DEBUG_OUT_AFTER
            cout << "rescaling log" << endl << flush;
            #endif
            for (int y = 0; y < height; y++)
            {
               for (int x = 0; x < width; x++)
               {
                  double ttmp = (255.0 / (mmax - mmin)) * (log(pGrid->GetValue(x, y) + 1.0) - mmin);
                  if (ttmp < 0.0) {ttmp = 0.0;}
                  if (ttmp > 255.0) {ttmp = 255.0;}
                  pGrid->SetValue(x, y, ttmp);
               }
            }
            break;
         }
         case NULL_OUT:
         {
            #ifdef DEBUG_OUT_AFTER
            cout << "no rescaling" << endl << flush;
            #endif
            break;
            // do nothing
         }
      }
   }

   mmax = -1000000000000000000000.0;
   mmin =  1000000000000000000000.0;

   for (int y = 0; y < pGrid->GetHeight(); y++)
   {
      for (int x = 0; x < pGrid->GetWidth(); x++)
      {
         if (pGrid->GetValue(x, y) < mmin) {mmin = pGrid->GetValue(x, y);}
         if (pGrid->GetValue(x, y) > mmax) {mmax = pGrid->GetValue(x, y);}
      }
   }

   #ifdef DEBUG_OUT_AFTER
   cout << "mmax = " << mmax << "\t mmin = " << mmin << endl << flush;
   #endif
   return true;
}

//------------------------------------------------------------------------------------------


}
}
