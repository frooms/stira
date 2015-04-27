
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

#ifndef STIRA_STEERABLE_PYRAMID_PYRAMIDMASTER_H
#define STIRA_STEERABLE_PYRAMID_PYRAMIDMASTER_H

#include <stdint.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <sstream>

#include "../../common/common/Definitions.h"

#include "../../image/datastructures/ArrayGrid.h"
#include "../../image/tools/ImageIO.h"
#include "../../image/datastructures/Pyramid.h"
#include "../../fouriertools/fouriertools/TransferFunctionGenerator.h"
#include "../../fouriertools/fouriertools/FFT.h"
#include "../../fouriertools/fouriertools/FFTBand.h"

//#define EXPORT_TRANSFERFUNCTIONS

namespace stira {
namespace steerable {

template <class T>

/** \brief parent class to compute FFT based real- and complex-valued steerable pyramids (decomposition/reconstruction)*/
class PyramidMaster
{
public:
   /** \brief constructor
     * \param pGridIn source input grid data
     * \param myNrScales nr of scales in which to decompose the image
     * \param myNrOrientations nr of orientations in which to decompose the image*/
   PyramidMaster( image::ArrayGrid<double>* pGridIn, int myNrScales, int myNrOrientations);
   
   /** \brief destructor
     * \warning: also deletes the mpPyramid data structure with all the subbands
     * Make sure you do not use the data structure you obtained with GetPyramid() after this point!!! */
   virtual ~PyramidMaster();
   
   /** \brief decomposes the source image in an steerable pyramid*/
   virtual bool Decompose()=0;
   
   /** \brief reconstructs the steerable pyramid back to an image */
   virtual bool Reconstruct()=0;
   
   /** \brief diagnoses the current steerable pyramid */
   virtual bool Diagnose( )=0;

   /** \brief calculates the sum over a set of FFTBands
     * creates a new FFTBand that becomes the responsability of the caller to delete 
     * \param fftSubbandSet stl vector with FFTBands to sum*/
   fouriertools::FFTBand* SumFFTBands( std::vector< fouriertools::FFTBand* > fftSubbandSet );
   
   /** \brief creates a copy of the grid after reconstruction 
     * This becomes the responsability of the caller to delete; the local member which contains the reconstructed grid 
     * is then deleted by the destructor of this class
     *
     * In case no grid is available, 0 is returned.
     */
   image::ArrayGrid<double>* GetCopyOfReconstructedGrid();
   
   /** \brief gets a pointer to the actual pyramid data*/
   image::Pyramid<T>* GetPyramid();
   
   /** \brief sets a pointer to new pyramid data
     * if old data exists already, they are deleted first
     * \warning: destructor of this class will also deletes the mpPyramid data structure with all the subbands
     * Make sure you do not use the data structure you are setting here after this destructor is called!!! 
     * \param pPyramid pointer to new pyramid data */
   void SetPyramid( image::Pyramid<T>* pPyramid );

protected:
   
   // DECOMPOSE
   ////////////
   
   /** \brief extracts the first L0 band*/
   image::ArrayGrid<double>* ExtractL0();
   
   /** \brief extracts a B0 band with given orientation index
     * \param myMode indicates whether we deal with real-valued or complex-valued pyramid*/
   fouriertools::FFTBand* ExtractB0( common::NumberMode myMode );
   
   /** \brief extracts recursive L band */
   image::ArrayGrid<double>* ExtractL( );
   
   /** \brief extracts a B band with given orientation index
     * \param myMode indicates whether we deal with real-valued or complex-valued pyramid*/
   fouriertools::FFTBand* ExtractB( common::NumberMode myMode );

   // RECONSTRUCT
   /////////////////
   
   /** \brief reconstructs the first L0 band 
     * Output is still in Fourier domain to save FFT's 
     * \param vpFFTBandSet set of input bands (already in Fourier domain)*/
   fouriertools::FFTBand* ReconstructL0( std::vector< fouriertools::FFTBand* > vpFFTBandSet );
   
   /** \brief reconstructs a B0 band with given orientation index
     * Output is still in Fourier domain to save FFT's 
     * \param pGridIn input B0 band (spatial domain)
     * \param myMode indicates whether we deal with real-valued or complex-values pyramid*/
   fouriertools::FFTBand* ReconstructB0( image::ArrayGrid<T>* pGridIn, common::NumberMode myMode);
   
   /** \brief reconstructs L band 
     * Output is still in Fourier domain to save FFT's
     * \param pGridIn input L band (spatial domain)*/
   fouriertools::FFTBand* ReconstructL( image::ArrayGrid<double>* pGridIn );

   /** \brief reconstructs a B0 band with given orientation index
     * Output is still in Fourier domain to save FFT's 
     * \param pGridIn input B0 band (spatial domain)
     * \param myMode indicates whether we deal with real-valued or complex-values pyramid*/
   fouriertools::FFTBand* ReconstructB( image::ArrayGrid<T>* pGridIn, common::NumberMode myMode );
   
   /** \brief computes sum, followed by inverse Fourier Transform
     * \param fftSubbandSet stl vector with FFTBands to merge*/
   image::ArrayGrid<double>* MergeAndReconstructFFTBands( std::vector< fouriertools::FFTBand* > fftSubbandSet );
   
   // HELP METHODS
   /////////////////
   /** \brief clears an STL vector with FFTBands
     * also deletes elements in the vector
     * \param set STL vector with FFTBands to clean*/
   void ClearFFTVector( std::vector< fouriertools::FFTBand* >& set );
   
   /** \brief sets current input FFTBand
     * For computational efficiency, we compute the FFT of the input grid for a scale just once and keep 
     * this to extract the different bands from it
     * \param pFFTBand the input FFTBand*/
   void SetFFTBand( fouriertools::FFTBand* pFFTBand );
   
   /** \brief gets current input FFTBand
     * For computational efficiency, we compute the FFT of the input grid for a scale just once and keep 
     * this to extract the different bands from it*/
   fouriertools::FFTBand* GetFFTBand();
   
   /** \brief cleans current input FFTBand
     * Also sets its pointer to 0*/
   void CleanFFTBand();
   
   /** \brief Writes a transfer function to PGM for diagnostics
    * 
    * \param pTransferFunction transfer function to be visualized
    * \param token file name token
    * \param scale number of scale to be incorporated in file name
    * \param orientation number of orientation to be incorporated in file name
    * \param maxNrOfOrientations max number of orientations, needed to make grid real-valued again
    * \param isForward flag if transfer function is in forward or backward transform, needed to make grid real-valued again
    * \return true if all went well
    */
   bool ViewTransferFunction( fouriertools::FFTBand* pTransferFunction, std::string token, int scale, int orientation, int maxNrOfOrientations, bool isForward);
   // DATA STRUCTURES
   ///////////////////
   
   image::Pyramid<T>* mpPyramid; ///< the pyramid bands
   
   image::ArrayGrid<double>* mpSourceGrid; ///< the source data grid
   image::ArrayGrid<double>* mpReconstructedGrid; ///< the data grid after reconstruction
   int mNrScales; ///< nr of scales in the pyramid
   int mNrOrientations; ///< nr of orientations (in paper called K) per scale in the pyramid
   int mWidth; ///< width of the source image
   int mHeight; ///< height of the source image
   bool mIsForwardTransform; ///< flag if we are computing the forward transform
   
   image::ArrayGrid<double>* mpTmpHighpassGrid; ///< tmp member in order to avoid recomputation of this transfer function for each oriented subband
   
   std::complex<double> mDecompositionFactor; ///< modulation factor for oriented bands (-i)^(K-1) during decomposition
   
   std::complex<double> mReconstructionFactor; ///< modulation factor for oriented bands (-i)^(K-1) during reconstruction
   
   fouriertools::FFTBand* mpFFTBand; ///< FFT of the input grid for a scale
   
   int mCurrentScale; ///< current scale we are at (while decomposing or reconstructing)
   int mCurrentOrientation; ///< current orientation within current scale we are at (while decomposing or reconstructing)
};

//=========================================================================================

template <class T>
PyramidMaster<T>::PyramidMaster(image::ArrayGrid<double>* pGridIn, int myNrScales, int myNrOrientations)
{
   mpSourceGrid = pGridIn;
   mpReconstructedGrid = 0;
   mNrScales = myNrScales;
   mNrOrientations = myNrOrientations;
   mWidth = mpSourceGrid->GetWidth();
   mHeight = mpSourceGrid->GetHeight();
   mpFFTBand = 0;
   mpPyramid = 0;

   mpTmpHighpassGrid = 0;
   
   mDecompositionFactor  = pow( std::complex<double>(0.0, -1.0), (double)( myNrOrientations - 1 ) );
   mReconstructionFactor = pow( std::complex<double>(0.0,  1.0), (double)( myNrOrientations - 1 ) );
   //std::cout << ">>> myNrScales = " << myNrScales << " and myNrOrientations = " << myNrOrientations << std::endl << std::flush;
   //std::cout << ">>> DecompositionFactor = " <<  mDecompositionFactor << " and ReconstructionFactor = " << mReconstructionFactor << std::endl << std::flush;
}

//------------------------------------------------------------------------------------------

template <class T>
PyramidMaster< T >::~PyramidMaster( )
{
   delete mpPyramid;
   if (mpFFTBand != 0)
   {
      delete mpFFTBand;
   }
   if (mpReconstructedGrid != 0)
   {
      delete mpReconstructedGrid;
   }
}

//------------------------------------------------------------------------------------------

template <class T>
void PyramidMaster< T >::SetPyramid( image::Pyramid<T>* pPyramid )
{
   if (mpPyramid != 0)
   {
      delete mpPyramid;
      mpPyramid = 0;
   }
   mpPyramid = pPyramid;
}

//------------------------------------------------------------------------------------------

template <class T>
image::Pyramid< T >* PyramidMaster< T >::GetPyramid( )
{
   return mpPyramid;
}

//------------------------------------------------------------------------------------------

template <class T>
image::ArrayGrid<double>* PyramidMaster< T >::GetCopyOfReconstructedGrid( )
{
   if (mpReconstructedGrid != 0)
   {
      return mpReconstructedGrid->Clone();
   }
   else
   {
      return 0;
   }
}

//------------------------------------------------------------------------------------------

template <class T>
void PyramidMaster< T >::ClearFFTVector( std::vector< fouriertools::FFTBand* >& mySet )
{
   for ( std::vector< fouriertools::FFTBand* >::iterator it = mySet.begin(); it != mySet.end(); ++it)
   {
      delete (*it);
   }
   mySet.clear();
}

//------------------------------------------------------------------------------------------

template <class T>
void PyramidMaster< T >::SetFFTBand( fouriertools::FFTBand* pFFTBand)
{
   if (mpFFTBand != 0)
   {
      delete mpFFTBand;
   }
   mpFFTBand = pFFTBand;
}

//------------------------------------------------------------------------------------------

template <class T>
fouriertools::FFTBand* PyramidMaster< T >::GetFFTBand()
{
   return mpFFTBand;
}

//------------------------------------------------------------------------------------------

template <class T>
void PyramidMaster< T >::CleanFFTBand()
{
   delete mpFFTBand;
   mpFFTBand = 0;
}

//------------------------------------------------------------------------------------------

///////////////////
//               //
//  DECOMPOSE    //
//               //
///////////////////

template <class T>
image::ArrayGrid<double>* PyramidMaster< T >::ExtractL0( )
{
   fouriertools::FFTBand* pFFTInBand = GetFFTBand();
   int width  = pFFTInBand->GetWidth();
   int height = pFFTInBand->GetHeight();

   image::ArrayGrid<double>* pfLPBand = fouriertools::TransferFunctionGenerator::GenerateLowPassTransferFunction(width, height, width / 4, width / 2);

   fouriertools::FFTBand* pFFTFilteredBand = fouriertools::FFT::ApplyTransferFunction( pFFTInBand, pfLPBand );
   image::ArrayGrid<double>* pResultingGrid = pFFTFilteredBand->ConvertToRealGrid( );
   delete pFFTFilteredBand;
   delete pfLPBand;

   return pResultingGrid;
}

//------------------------------------------------------------------------------------------

template <class T>
image::ArrayGrid<double>* PyramidMaster< T >::ExtractL( )
{
   fouriertools::FFTBand* pFFTInBand = GetFFTBand();
   int width  = pFFTInBand->GetWidth();
   int height = pFFTInBand->GetHeight();
   
   image::ArrayGrid<double>* pfLPBand = fouriertools::TransferFunctionGenerator::GenerateLowPassTransferFunction(width, height, width / 8, width / 4);

   fouriertools::FFTBand* pFFTFilteredBand = fouriertools::FFT::ApplyTransferFunction( pFFTInBand, pfLPBand );
   image::ArrayGrid<double>* pResultingGrid = pFFTFilteredBand->ConvertToRealGrid();
   delete pFFTFilteredBand;
   delete pfLPBand;

   return pResultingGrid;
}

//------------------------------------------------------------------------------------------

template <class T>
bool PyramidMaster< T >::ViewTransferFunction( fouriertools::FFTBand* pTransferFunction, std::string token, int scale, int orientation, int maxNrOfOrientations, bool isForward)
{
   std::complex<double> modulationFactor;
   if (isForward)
   {
      modulationFactor = pow( std::complex<double>(0.0, -1.0), (double)(maxNrOfOrientations-1));
   }
   else
   {
      modulationFactor = pow( std::complex<double>(0.0, 1.0), (double)(maxNrOfOrientations-1));
   }
   
   int width = pTransferFunction->GetWidth();
   int height = pTransferFunction->GetHeight();
   

   image::ArrayGrid<double>* pGrid = new image::ArrayGrid<double>( width, height );
   
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         std::complex<double> cv = pTransferFunction->GetValue(x, y) / modulationFactor;
         pGrid->SetValue(x, y, cv.real() );
      }
   }
   std::stringstream ss;
   ss << token << "-" << scale << "-" << orientation << ".pgm";
   image::ImageIO::WritePGM( pGrid, ss.str(), image::ImageIO::GRADIENT_OUT );
   delete  pGrid;
   
   return true;
}

//------------------------------------------------------------------------------------------

template <class T>
fouriertools::FFTBand* PyramidMaster< T >::ExtractB0( common::NumberMode myMode )
{
   fouriertools::FFTBand* pFFTInBand = GetFFTBand();
   int width  = pFFTInBand->GetWidth();
   int height = pFFTInBand->GetHeight();

   fouriertools::FFTBand* pfOPBand = fouriertools::TransferFunctionGenerator::GenerateOrientedTransferFunction( width, height, mCurrentOrientation, mNrOrientations, mIsForwardTransform, myMode);
   pfOPBand->Multiply( mpTmpHighpassGrid );  // mpTmpHighpassGrid is created and deleted outside this method

   #ifdef EXPORT_TRANSFERFUNCTIONS
   std::stringstream ss;
   ss << "Transfer-0-" << mCurrentOrientation << ".pgm";
   std::string fileName = ss.str();
   pfOPBand->ExportAbsImage( fileName );
   #endif

   fouriertools::TransferFunctionGenerator::HighFrequencyCrossMask( pfOPBand, mNrOrientations ); // trick to avoid artefacts due to highest frequency cross

   fouriertools::FFTBand* pFFTFilteredBand = fouriertools::FFT::ApplyTransferFunction( GetFFTBand(), pfOPBand );
   
   delete pfOPBand;
   
   return pFFTFilteredBand;
}

//------------------------------------------------------------------------------------------

template <class T>
fouriertools::FFTBand* PyramidMaster< T >::ExtractB( common::NumberMode myMode )
{
   fouriertools::FFTBand* pFFTInBand = GetFFTBand();
   int width  = pFFTInBand->GetWidth();
   int height = pFFTInBand->GetHeight();
   
   fouriertools::FFTBand* pfOPBand = fouriertools::TransferFunctionGenerator::GenerateOrientedTransferFunction(width, height, mCurrentOrientation, mNrOrientations, mIsForwardTransform, myMode);
   pfOPBand->Multiply( mpTmpHighpassGrid );  // mpTmpHighpassGrid is created and deleted outside this method
   
   #ifdef EXPORT_TRANSFERFUNCTIONS
   std::stringstream ss;
   ss << "Transfer-" << mCurrentScale << "-" << mCurrentOrientation << ".pgm";
   std::string fileName = ss.str();
   pfOPBand->ExportAbsImage( fileName );
   #endif

   fouriertools::FFTBand* pFFTFilteredBand = fouriertools::FFT::ApplyTransferFunction( GetFFTBand(), pfOPBand );
   
   delete pfOPBand;
   return pFFTFilteredBand;
}

//------------------------------------------------------------------------------------------

///////////////////
//               //
//  RECONSTRUCT  //
//               //
///////////////////

template <class T>
fouriertools::FFTBand* PyramidMaster< T >::ReconstructL0( std::vector< fouriertools::FFTBand* > vpFFTBandSet )
{
   fouriertools::FFTBand* pSum = SumFFTBands( vpFFTBandSet );
   
   int width  = pSum->GetWidth();
   int height = pSum->GetHeight();

   image::ArrayGrid<double>* pfLPBand = fouriertools::TransferFunctionGenerator::GenerateLowPassTransferFunction(width, height, width / 4, width / 2);
   pSum->Multiply( pfLPBand );
   delete pfLPBand;
   return pSum;
}

//------------------------------------------------------------------------------------------

template <class T>
fouriertools::FFTBand* PyramidMaster< T >::ReconstructL( image::ArrayGrid<double>* pGridIn )
{
   int width  = pGridIn->GetWidth();
   int height = pGridIn->GetHeight();

   image::ArrayGrid<double>* pfLPBand = fouriertools::TransferFunctionGenerator::GenerateLowPassTransferFunction(width, height, width / 8, width / 4);
   
   fouriertools::FFTBand* pFFTFilteredBand = fouriertools::FFT::ApplyTransferFunctionFFT(pGridIn, pfLPBand);
   delete pfLPBand;
   return pFFTFilteredBand;
}

//------------------------------------------------------------------------------------------

template <class T>
fouriertools::FFTBand* PyramidMaster< T >::ReconstructB0( image::ArrayGrid<T>* pGridIn, common::NumberMode myMode)
{
   int width = pGridIn->GetWidth();
   int height = pGridIn->GetHeight();
   
   fouriertools::FFTBand* pfOPBand = fouriertools::TransferFunctionGenerator::GenerateOrientedTransferFunction(width, height, mCurrentOrientation, mNrOrientations, mIsForwardTransform, myMode);
   pfOPBand->Multiply( mpTmpHighpassGrid );   // mpTmpHighpassGrid is created and deleted outside this method
   if (myMode == common::MODE_COMPLEX)   // compensate energy loss due to zero'ing half of the fourier frequencies
   {
      pfOPBand->Multiply( 2.0 );
   }
   fouriertools::TransferFunctionGenerator::HighFrequencyCrossMask( pfOPBand, mNrOrientations ); // trick to avoid artefacts due to highest frequency cross

   fouriertools::FFTBand* pFFTFilteredBand = fouriertools::FFT::ApplyTransferFunctionFFT( pGridIn, pfOPBand );

   delete pfOPBand;
   return pFFTFilteredBand;
}

//------------------------------------------------------------------------------------------

template <class T>
fouriertools::FFTBand* PyramidMaster< T >::ReconstructB( image::ArrayGrid<T>* pGridIn, common::NumberMode myMode )
{
   int width  = pGridIn->GetWidth();
   int height = pGridIn->GetHeight();
   
   fouriertools::FFTBand* pfOPBand = fouriertools::TransferFunctionGenerator::GenerateOrientedTransferFunction(width, height, mCurrentOrientation, mNrOrientations, mIsForwardTransform, myMode);

   pfOPBand->Multiply( mpTmpHighpassGrid );  // mpTmpHighpassGrid is created and deleted outside this method
   if (myMode == common::MODE_COMPLEX)    // compensate energy loss due to zero'ing half of the fourier frequencies
   {
      pfOPBand->Multiply( 2.0 );
   }

   fouriertools::FFTBand* pFFTFilteredBand = fouriertools::FFT::ApplyTransferFunctionFFT( pGridIn, pfOPBand );
   delete pfOPBand;
   
   return pFFTFilteredBand;
}

//------------------------------------------------------------------------------------------

template <class T>
fouriertools::FFTBand* PyramidMaster< T >::SumFFTBands( std::vector< fouriertools::FFTBand* > fftSubbandSet )
{
   int h = fftSubbandSet[0]->GetHeight();
   int w = fftSubbandSet[0]->GetWidth();
   
   fouriertools::FFTBand* pSum = new fouriertools::FFTBand( w, h );
   
   for (int y = 0; y < h; y++)
   {
      for (int x = 0; x < w; x++)
      {
         std::complex<double> tmpValue(0.0, 0.0);
         for (int i = 0; i < (int)(fftSubbandSet.size()); i++)
         {
            tmpValue += fftSubbandSet[i]->GetValue( x, y ) ;
         }
         pSum->SetValue( x, y, tmpValue );
      }
   }
   return pSum;
}

//------------------------------------------------------------------------------------------

template <class T>
image::ArrayGrid<double>* PyramidMaster< T >::MergeAndReconstructFFTBands( std::vector< fouriertools::FFTBand* > fftSubbandSet )
{
   fouriertools::FFTBand* pSum = SumFFTBands( fftSubbandSet );
   
   pSum->ApplyInverseTransform();
   pSum->SwitchQuadrants();
   image::ArrayGrid<double>* pResultGrid = pSum->ConvertToRealGrid( );
   delete pSum;
   return pResultGrid;
}

//------------------------------------------------------------------------------------------

}
}

#endif
