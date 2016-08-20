
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

#ifndef STIRA_IMAGE_TOOLS_IMAGEIO_H
#define STIRA_IMAGE_TOOLS_IMAGEIO_H

#include <stdint.h>
#include <iostream>
#include <complex>

#include <opencv2/opencv.hpp>

#include "../../common/common/RectangularROI.h"
#include "../../imagedata/datastructures/Image.h"

namespace stira {
namespace imagetools {

using namespace imagedata;

/**
 * \brief A class to hold spectral bands of an image
 */
class ImageIO{

// 0. CONSTRUCTOR / DESTRUCTOR / OUTPUT TYPE ENUM
/////////////////////////////////////////////////

public:
   /** \brief type to identify how the image intensities  need to be rescaled for export*/
   enum outputType {
                        NULL_OUT,     ///< no rescaling applied; just use input values
                        GRADIENT_OUT, ///< gradient type: zero is grey, negative goes from grey to black, positive values go from grey to white
                        NORMAL_OUT,   ///< only positive values: linear scaling
                        LOG_OUT,      ///< take logarithm and rescale linearly
                        ABSOLUTE_NORM_OUT,  ///< take absolute values and rescale linearly
                        ABSOLUTE_POS_OUT,  ///< take absolute values and rescale linearly
                        ABSOLUTE_NEG_OUT  ///< take absolute values and rescale linearly
                   };

   /** \brief Constructor. */
   ImageIO();

   /** \brief Destructor. */
   ~ImageIO();

// 1. NATIVE SUPPORT FOR READING AND WRITING RAW PGM AND PPM IMAGES
///////////////////////////////////////////////////////////////////

   // 1.1. READING
   //--------------

public:

   /** \brief reads a file using the correct input help method
     * \param fname name of the file to read from */
   static Image* Read( std::string fname);

   /** \brief reads an image as a grid of integers
     * \param fname name of the file to read from */
   static ArrayGrid<int>* ReadPGMasInt( std::string fname);

private:
   /** \brief determines whether file is raw PPM or PGM and then reads image with appropriate method from file
     * \param fname name of the file to read from */
   static Image* ReadAsPXM( std::string fname );

   /** \brief reads a PGM image from disk
     * \param fname the name of the file to read from
     * \return an image object containing the imported data */
   static Image* ReadPGM( std::string fname);

   /** \brief reads a PPM image from disk
     * \param fname the name of the file to read from
     * \return an image object containing the imported data */
   static Image* ReadPPM( std::string fname);

   // 1.2. WRITING
   //--------------

public:

   /** \brief determines whether image object has 1 or three bands and then writes image with appropriate method to file
     * \param pImage image object to be written to file
     * \param fileName name of the file to write to
     * \param outtype type of rescaling to apply before writing to disk*/
   static bool Write( Image* pImage, std::string fname, outputType outtype=NULL_OUT );

   /** \brief writes an ArrayGrid of complex doubles from memory to disk .
     * It writes two files: one containing all the real values, one containing all the imaginary values
     * \param pGrid ArrayGrid object to be written to file
     * \param fileName name of the file to write to
     * \param outtype type of rescaling to apply before writing to disk*/
   static void WritePGM( ArrayGrid< std::complex<double> >* pGrid, std::string fileName, outputType outtype=NULL_OUT);

   /** \brief writes an ArrayGrid of doubles from memory to disk .
     * \param pGrid ArrayGrid object to be written to file
     * \param fileName name of the file to write to
     * \param outtype type of rescaling to apply before writing to disk*/
   static bool WritePGM( ArrayGrid<double>* pGrid, std::string fileName, outputType outtype=NULL_OUT);

   /** \brief writes an ArrayGrid of integers from memory to disk .
     * \param pGrid ArrayGrid object to be written to file
     * \param fileName name of the file to write to
     * \param outtype type of rescaling to apply before writing to disk*/
   static bool WritePGM( ArrayGrid<int>* pGrid, std::string fileName, outputType outtype=NULL_OUT);

   /** \brief writes an ArrayGrid of booleans from memory to disk .
     * \param pGrid ArrayGrid object to be written to file
     * \param fileName name of the file to write to disk*/
   static bool WritePGM( ArrayGrid<bool>* pGrid, std::string fileName );

   /** \brief writes an ArrayGrid of doubles from memory to disk in a simple text file.
     * \param pGrid ArrayGrid object to be written to file
     * \param fileName name of the file to write to*/
   static bool WriteTXT( ArrayGrid<double>* pGrid, std::string fileName);

private:

   /** \brief writes a PGM image object to a disk file
     * \param fname the name of the file to write to
     * \param pImage the image object containing the data
     * \param outtype type of rescaling to apply before writing to disk
     * \return true if written successfully; false otherwise */
   static bool WritePGM( Image* pImage, std::string fname, outputType outtype=NULL_OUT);

   /** \brief writes a PPM image object to a disk file
     * \param fname the name of the file to write to
     * \param pImage the image object containing the data
     * \param outtype type of rescaling to apply before writing to disk
     * \return true if written successfully; false otherwise */
   static bool WritePPM( Image* pImage, std::string fname, outputType outtype);

// 2.0 OTHER FORMATS THROUGH OpenCV
//   http://www.cs.iit.edu/~agam/cs512/lect-notes/opencv-intro/opencv-intro.html
//   http://opencv.willowgarage.com/documentation/cpp/index.html
/////////////////////////////////////////////////////////////////////////////////

public:
   /** \brief gets an intensity of an OpenCV image assuming it is a gray value
     * \param pIplImage OpenCV image to read from
     * \param x x coordinate to read from
     * \param y y coordinate to read from */
   static double GetOpenCvGrayValue(IplImage* pIplImage, int x, int y );

   /** \brief sets the intensity at position (x,y) in an OpenCV image assuming it is a gray value
     * \param pIplImage OpenCV image to write to
     * \param x x coordinate to write to
     * \param y y coordinate to write to
     * \param value value to set*/
   static void SetOpenCvGrayValue(IplImage* pIplImage, int x, int y, double value );

   /** \brief gets an intensity at position (x,y) in an OpenCV image in the specified color band
     * \param pIplImage OpenCV image to read from
     * \param x x coordinate to read from
     * \param y y coordinate to read from
     * \param bandNr number of the color band to read the value from */
   static double GetOpenCvColorValue(IplImage* pIplImage, int x, int y, int bandNr );

   /** \brief sets an intensity at position (x,y) in an OpenCV image in the specified color band
     * \param pIplImage OpenCV image to write to
     * \param x x coordinate to write to
     * \param y y coordinate to write to
     * \param bandNr number of the color band to write the value to */
   static void SetOpenCvColorValue(IplImage* pIplImage, int x, int y, int bandNr, double value );

   static ArrayGrid<double>* ConvertOpenCvToDoubleArrayGrid( IplImage* pIplImage );

   static ArrayGrid<double>*  ConvertOpenCvToDoubleArrayGrid( IplImage* pIplImage, ArrayGrid<double>* pGrid );

   static ArrayGrid<bool>* ConvertOpenCvToBooleanArrayGrid( IplImage* pIplImage, double threshold=0 );

   static IplImage* ConvertArrayGridToOpenCv( ArrayGrid<double>* pGridIn, IplImage* pImgOut );

   /** \brief converts an OpenCV image structure to our library image class
     * \param pIplImage input OpenCV image structure
     * \return object of our own image class */
   static Image* ConvertOpenCvToImage( IplImage* pIplImage );

   /** \brief converts object of our own image class into an OpenCV image structure
     * \param pImage object of our own image class
     * \return OpenCV image structure */
   static IplImage* ConvertImageToOpenCv( Image* pImage );

   /** \brief reads an image from a disk file using OpenCVuseBGR
     * \param fname the name of the file to read from
     * \param useROI flag whether to read the whole image or an ROI of the image
     * \param myImageROI if useROI is true, only image data within this ROI will read from the image
     * \return image object containing the data */
   static Image* ReadImageOpenCV( std::string fname, bool useROI=false, common::RectangularROI<int> myImageROI = common::RectangularROI<int>( 0, 0, 0, 0) );

   /** \brief reads a single band of an image from a disk file using OpenCV
     * \param fname the name of the file to read from
     * \param pGrid pointer to output grid; will create a new grid if NULL
     * \param useROI flag whether to read the whole image or an ROI of the image
     * \param myImageROI if useROI is true, only image data within this ROI will read from the image
     * \return image object containing the data */
   static ArrayGrid<double>* ReadArrayOpenCVAsDouble( std::string fname, ArrayGrid<double>* pGrid=0, bool useROI=false, common::RectangularROI<int> myImageROI = common::RectangularROI<int>( 0, 0, 0, 0) );

   /** \brief reads a single band of an image from a disk file using OpenCV
     * \param fname the name of the file to read from
     * \param useROI flag whether to read the whole image or an ROI of the image
     * \param myImageROI if useROI is true, only image data within this ROI will read from the image
     * \return image object containing the data */
   static ArrayGrid<int>* ReadArrayOpenCVAsInt( std::string fname, bool useROI=false, common::RectangularROI<int> myImageROI = common::RectangularROI<int>( 0, 0, 0, 0) );

   /** \brief writes an image object to a disk file
     * \param fname the name of the file to write to
     * \param outtype type of rescaling to apply before writing to disk
     * \return true if written successfully; false otherwise */
   static bool WriteOpenCV( Image* pImage, std::string fname, outputType outtype=NORMAL_OUT );

   /** \brief writes a single grid object of double precision float values to a disk file
     * \param fname the name of the file to write to
     * \param outtype type of rescaling to apply before writing to disk
     * \return true if written successfully; false otherwise */
   static bool WriteOpenCV( ArrayGrid<double>* pGrid, std::string fname, outputType outtype=NORMAL_OUT );

   /** \brief writes a single grid object of integer values to a disk file
     * \param fname the name of the file to write to
     * \param outtype type of rescaling to apply before writing to disk
     * \return true if written successfully; false otherwise */
   static bool WriteOpenCV( ArrayGrid<int>* pGrid, std::string fname, outputType outtype=NORMAL_OUT );

   /** \brief writes a single grid object of booleans to a disk file
     * \param fname the name of the file to write to
     * \return true if written successfully; false otherwise */
   static bool WriteOpenCV( ArrayGrid<bool>* pGrid, std::string fname );

// 3.0 HELPER METHODS
/////////////////////

public:
   /** \brief gets minimum and maximum value of values in pGrid, or of function of values in pGrid (abs(intensity), log(intensity), ...)
     *
     * \param pGrid input grid
     * \param mmin output value with minimum
     * \param mmax output value with maximum
     * \param myType type of function to apply to grid values before comparing them */
   static void GetInputMinMax( ArrayGrid<double>* pGrid, double& mmin, double& mmax, outputType myType=NULL_OUT);

   /** \brief Rescales the values in a real-valued grid according to type <code>outtype</code>
     *
     * \warning operates on pGrid values; values before rescaling are lost
     *
     * \param pGrid ArrayGrid object of which values needed to be rescaled
     * \param outtype type of rescaling to apply before writing to disk*/
   static bool RescaleGrid( ArrayGrid<double>* pGrid, outputType outtype=NULL_OUT);
};
}
}
#endif
