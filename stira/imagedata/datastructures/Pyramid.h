
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

#ifndef STIRA_IMAGEDATA_DATASTRUCTURES_PYRAMID_H
#define STIRA_IMAGEDATA_DATASTRUCTURES_PYRAMID_H

#include <stdint.h>
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <cassert>

#include "PyramidLevel.h"
#include "../../common/common/MathUtils.h"
#include "../../imagedata/simpletools/GridStatistics.h"

namespace stira {
namespace imagedata {

/** \brief A data class to contain all subbands of a pyramid decomposition
  * These bands are grouped per resolution level. All bands in one resolution level are grouped in a member class PyramidLevel.
  * So, a pyramid contains a vector of pointers to "PyramidLevel" objects for the recursive scales and an extra pointer to a
  * "PyramidLevel" object for the residual scale (like used in the steerable pyramid, is NULL if no residual scale is used) */
template <class T>
class Pyramid
{
public:

   enum PyramidSubsamplingArgument{ IS_SUBSAMPLED, IS_REDUNDANT };

   enum PyramidResidualLevelsArgument{ HAS_RESIDUALLEVELS, HAS_NO_RESIDUALLEVELS };

   /** \brief Constructor.
     * Creates an empty data structure to which the bands (allocated elsewhere) can be added
     *
     * \param pSourceBand input data
     * \param myNrScales nr of scales in pyramid
     * \param myNrOrientations nr of orientations
     * \param isSubsampled true if decomposition is subsampled to higher levels; false if representation is not subsampled
     * \param needsResidualLevels flag if residual levels are required (true for steerable pyramid, false for normal wavelets)*/
   Pyramid(ArrayGrid<double>* pSourceBand, int myNrScales, int myNrOrientations, bool isSubsampled, bool needsResidualLevels /*=false*/, bool isFinestScaleSubsampled=false);

   /** \brief creates bands and allocates the necessary memory for the bands
     *
     * \param sourceWidth width of data grid at full resolution
     * \param sourceHeight height of data grid at full resolution
     * \param isSubsampled flag if bands are subsampled or not
     * \param isFinestScaleSubsampled (for steerable pyramid) in case of subsampling indicates if first scale is subsampled or not
     * \return true if bands were created successfully */
   bool CreateBands( int sourceWidth, int sourceHeight, bool isSubsampled=false, bool isFinestScaleSubsampled=false );

   /** \brief Destructor. */
   ~Pyramid();

   /** \brief Gets the number of scales in this pyramid
     * This is the number of recursive scales in this pyramid and does *NOT* count the residual level if it is present!!*/
   int GetNumberOfScales();

   /** \brief Gets the number of orientations in this pyramid */
   int GetNumberOfOrientations();

   /** \brief Gets the width of the underlying source data grid */
   int GetSourceDataWidth();

   /** \brief Gets the height of the underlying source data grid */
   int GetSourceDataHeight();

   /** \brief Gets the scale factor for the residual level
     * Takes into account scaling of the energy content from level to level due to normalization of the coefficients*/
   double GetScaleFactorResidualLevel();

   /** \brief Sets the scale factor for the residual level
     * Takes into account scaling of the energy content from level to level due to normalization of the coefficients
     * \param factor the scaling factor */
   void SetScaleFactorResidualLevel( double factor );

   /** \brief Gets the scale factor between the residual and the first recursive level
     * Takes into account scaling of the energy content from level to level due to normalization of the coefficients */
   double GetScaleFactorResidualToRecursiveLevel();

   /** \brief Sets the scale factor between the residual and the first recursive level
     * Takes into account scaling of the energy content from level to level due to normalization of the coefficients
     * \param factor the scaling factor */
   void SetScaleFactorResidualToRecursiveLevel( double factor );

   /** \brief Gets the scale factor between two adjacent recursive levels
     * Takes into account scaling of the energy content from level to level due to normalization of the coefficients */
   double GetScaleFactorRecursiveLevel();

   /** \brief Gets the scale factor between two adjacent recursive levels
     * Takes into account scaling of the energy content from level to level due to normalization of the coefficients
     * \param factor the scaling factor */
   void   SetScaleFactorRecursiveLevel( double factor );

   /** \brief Gets a list of oriented subbands belonging to a recursive scale of the pyramid
     * \param scale number of scale to get*/
   PyramidLevel<T>* GetRecursiveScale(int scale);

   /** \brief checks if the pyramid has a residual scale*/
   bool HasResidualScale();

   /** \brief gets number of finest scale
     * Is 0 for standard decomposition; is -1 when residual scale is available like with complete steerable pyramid*/
   int GetFinestScaleNumber();

   /** \brief Gets a list of oriented subbands belonging to the finest residual scale of the pyramid*/
   PyramidLevel<T>* GetResidualScale();

   /** \brief Gets the lowpass residual after decomposition*/
   ArrayGrid<double>* GetLowpassResidual();

   /** \brief sets the current lowpass residual by pGrid
     * If no lowpass residual was present, the input grid is set; if one was present, it is deleted and replaced
     * \param pGrid input grid */
   void SetLowpassResidual(ArrayGrid<double>* pGrid);

   /** \brief writes all bands in all levels to PGM's*/
   //void ExportBandsToPGM();

   /** \brief makes a deep copy of the current pyramid
     * The caller is responsible for cleaning the returned object*/
   Pyramid<T>* Clone();

   /** \brief Copies the values in the bands of "pOtherPyramid" to the bands in this pyramid
     * Pyramids must have equal number of scales and orientations and sizes per band.
     * No new objects or memory is allocated!!!
     * \param pOtherPyramid the pyramid with the source data*/
   void CopyValuesFrom(Pyramid<T>* pOtherPyramid);

   /** \brief computes the so-called Average Cone Ratio of pyramid coefficients in case the pyramid is subsampled
     *
     * Ref: PhD thesis A. Pizurica "Image Denoising Using Wavelets and Spatial Context Modeling" p. 87
     *       http://telin.ugent.be/~sanja/
     * \param x x coordinate of the coefficient
     * \param y y coordinate of the coefficient
     * \param orientationNr identifier of orientation band
     * \param coarsestScale the coarsest scale to compute the ratio for
     * \param finestScale the finest scale to compute the ratio for*/
   T GetAverageConeRatioSubSampled( int x, int y, int orientationNr, int coarsestScale, int finestScale );

   /** \brief computes the so-called Average Cone Ratio of pyramid coefficients in case the pyramid is redundant (ie, not subsampled)
     *
     * Ref: PhD thesis A. Pizurica "Image Denoising Using Wavelets and Spatial Context Modeling" p. 87
     *       http://telin.ugent.be/~sanja/
     * \param x x coordinate of the coefficient
     * \param y y coordinate of the coefficient
     * \param orientationNr identifier of orientation band
     * \param coarsestScale the coarsest scale to compute the ratio for
     * \param finestScale the finest scale to compute the ratio for*/
   T GetAverageConeRatioRedundant( int x, int y, int orientationNr, int coarsestScale, int finestScale );

   /** \brief gets flag whether coarser scales are subsampled
     * true if decomposition is subsampled to coarser levels; false if representation is not subsampled */
   bool IsSubsampled();

   bool IsFinestScaleSubsampled();

protected:

   /** \brief downsamples a given band
    * The caller gets a newly created band, and is responsible for deleting it after usage
    * \param pBandIn the band to be downsampled*/
   ArrayGrid<T>* DownSampleGrid(ArrayGrid<T>* pBandIn);

   /** \brief Upsamples a band
    * The caller gets a newly created band, and is responsible for deleting it after usage. Because of the
    * ambiguity (both width 2n-1 and 2n were downsampled to new width n), the upsampled width and height need
    * to be specified
    * \param pBandIn the band to be upsampled
    * \param upSampledWidth width of destination upsampled image
    * \param upSampledHeight height of destination upsampled image*/
   ArrayGrid<T>* UpSampleGrid(ArrayGrid<T>* pBandIn, int upSampledWidth, int upSampledHeight);

   std::vector<PyramidLevel<T>* > mvpRecursivePyramidLevels;  ///< oriented bandpass bands for all recursive scales
   PyramidLevel<T>* mpResidualPyramidLevels;  ///< oriented bandpass bands for the residual highpass scale
   ArrayGrid<double>* mpLowPassResidual;  ///< Band with final lowpass residual of the pyramid

   ArrayGrid<double>* mpSourceDataGrid;  ///< pointer to the grid with the source data
   bool mIsSubsampled;
   bool mIsFinestScaleSubsampled;
   int mNrScales; ///< number of (recursive) scales in this pyramid; doesn't count the residual level if it is present!!
   int mNrOrientations; ///< number of orientations in this pyramid
   double mScaleFactorResidualLevel;  ///< scale factor normal noise variance in spatial domain and in recursive level
   double mScaleFactorResidualToRecursiveLevel;  ///< scale factor coefficients between residual and first recursive level
   double mScaleFactorRecursiveLevel;  ///< scale factor coefficients between two successive recursive levels
};

//===========================================================================================

template <class T>
Pyramid<T>::Pyramid( ArrayGrid<double>* pSourceBand, int myNrScales, int myNrOrientations, bool isSubsampled, bool needsResidualLevels, bool isFinestScaleSubsampled )
{
   mpSourceDataGrid = pSourceBand;
   mNrScales = myNrScales;
   mNrOrientations = myNrOrientations;
   mIsSubsampled = isSubsampled;
   mpLowPassResidual = 0;
   mIsFinestScaleSubsampled = isFinestScaleSubsampled;

   for (int scaleIndex = 0; scaleIndex < mNrScales; scaleIndex++)
   {
      PyramidLevel<T>* pNewPyramidLevel = new PyramidLevel< T >( );
      mvpRecursivePyramidLevels.push_back( pNewPyramidLevel );
   }

   assert(static_cast<int>( mvpRecursivePyramidLevels.size() ) == mNrScales);
   if (needsResidualLevels)
   {
      mpResidualPyramidLevels = new PyramidLevel<T>();
   }
   else
   {
      mpResidualPyramidLevels = 0;
   }
   // for the steerable pyramid, variance in the residual level is 1 x sigma,
   //                                     in the first recursive level sigma / 2
   //                                     each consecutive level up, variance is further divided by 4
   mScaleFactorResidualLevel = 1.0;
   mScaleFactorResidualToRecursiveLevel = sqrt(2.0);
   mScaleFactorRecursiveLevel = 2.0;
}

//===========================================================================================

template <class T>
Pyramid<T>::~Pyramid()
{
   for (int scaleIndex = 0; scaleIndex < GetNumberOfScales(); scaleIndex++)
   {
      delete mvpRecursivePyramidLevels[scaleIndex];  //should call the destructor of SteerableBands
   }
   mvpRecursivePyramidLevels.clear();

   if (mpResidualPyramidLevels != 0)
   {
      delete mpResidualPyramidLevels;  //should call the destructor of SteerableBands
   }
   delete mpLowPassResidual;
}

//===========================================================================================

template <class T>
Pyramid<T>* Pyramid<T>::Clone()
{
   bool needsResidualLevels;
   if (mpResidualPyramidLevels != 0)
   {
      needsResidualLevels = true;
   }
   else
   {
      needsResidualLevels = false;
   }
   Pyramid<T>* pClonePyramid = new Pyramid( this->mpSourceDataGrid, mNrScales, mNrOrientations, needsResidualLevels );
   pClonePyramid->CopyValuesFrom(this);

   return pClonePyramid;
}

//===========================================================================================

template <class T>
bool Pyramid<T>::IsFinestScaleSubsampled()
{
   return mIsFinestScaleSubsampled;
}

//===========================================================================================

template <class T>
bool Pyramid<T>::IsSubsampled()
{
   return mIsSubsampled;
}

//===========================================================================================

template <class T>
void Pyramid<T>::CopyValuesFrom(Pyramid<T>* pOtherPyramid)
{
   int nrScales       = this->GetNumberOfScales();
   int nrOrientations = this->GetNumberOfOrientations();
   bool needsResidualLevels;
   if (mpResidualPyramidLevels != 0)
   {
      needsResidualLevels = true;
   }
   else
   {
      needsResidualLevels = false;
   }

   assert (nrScales == pOtherPyramid->GetNumberOfScales());
   assert (nrOrientations == pOtherPyramid->GetNumberOfOrientations());

   int lowpassWidth  = pOtherPyramid->GetLowpassResidual()->GetWidth();
   int lowpassHeight = pOtherPyramid->GetLowpassResidual()->GetHeight();

   assert (lowpassWidth == GetLowpassResidual()->GetWidth());
   assert (lowpassHeight == GetLowpassResidual()->GetHeight());

   for (int y = 0; y < lowpassHeight; y++)
   {
      for (int x = 0; x < lowpassWidth; x++)
      {
         GetLowpassResidual()->SetValue(x, y, pOtherPyramid->GetLowpassResidual()->GetValue(x, y));
      }
   }

   for (int scaleIndex = 0; scaleIndex < nrScales; scaleIndex++)
   {
      PyramidLevel<T>* pOtherPyramidLevel = pOtherPyramid->GetRecursiveScale(scaleIndex);
      PyramidLevel<T>* pThisPyramidLevel = this->GetRecursiveScale(scaleIndex);

      for (int orientationIndex = 0; orientationIndex < nrOrientations; orientationIndex++)
      {
         ArrayGrid<T>* pOtherBand = pOtherPyramidLevel->GetOrientedBand( orientationIndex );
         ArrayGrid<T>* pThisBand  = pThisPyramidLevel->GetOrientedBand( orientationIndex );
         int width  = pOtherBand->GetWidth();
         int height = pOtherBand->GetHeight();

         assert( width == pThisBand->GetWidth());
         assert( height == pThisBand->GetHeight());

         for (int y = 0; y < height; y++)
         {
            for (int x = 0; x < width; x++)
            {
               pThisBand->SetValue(x, y, pOtherBand->GetValue(x, y));
            }
         }
      }
   }
   if (needsResidualLevels)
   {
      PyramidLevel<T>* pOtherPyramidLevel = pOtherPyramid->GetResidualScale();
      PyramidLevel<T>* pThisPyramidLevel = this->GetResidualScale();
      for (int orientationIndex = 0; orientationIndex < nrOrientations; orientationIndex++)
      {
         ArrayGrid<T>* pOtherBand = pOtherPyramidLevel->GetOrientedBand( orientationIndex );
         ArrayGrid<T>* pThisBand  = pThisPyramidLevel->GetOrientedBand( orientationIndex );
         int width  = pOtherBand->GetWidth();
         int height = pOtherBand->GetHeight();

         assert( width == pThisBand->GetWidth());
         assert( height == pThisBand->GetHeight());

         for (int y = 0; y < height; y++)
         {
            for (int x = 0; x < width; x++)
            {
               pThisBand->SetValue(x, y, pOtherBand->GetValue(x, y));
            }
         }
      }
   }
}

//===========================================================================================

template <class T>
T Pyramid<T>::GetAverageConeRatioSubSampled( int x, int y, int orientationNr, int finestScale, int coarsestScale )
{
   T ACR = 0;
   int windowSize = 3;
   int coarserX, coarserY, finerX, finerY;
   if ( finestScale   <         0 ) { finestScale   =         0; }
   if ( coarsestScale > mNrScales ) { coarsestScale = mNrScales; }

   coarserX = x / common::MathUtils::ComputeIntegerPower(2, coarsestScale-1);
   coarserY = y / common::MathUtils::ComputeIntegerPower(2, coarsestScale-1);

   int windowHalfSize = windowSize / 2;

   int xTopLeft = coarserX - windowHalfSize;
   int yTopLeft = coarserY - windowHalfSize;
   int xBottomRight = coarserX + windowHalfSize;
   int yBottomRight = coarserY + windowHalfSize;

   T coarserAbsMean = GridStatistics<double>::ComputeLocalAbsoluteMean(  this->GetRecursiveScale( coarsestScale-1 )->GetOrientedBand( orientationNr ), xTopLeft, yTopLeft, xBottomRight, yBottomRight );
   T finerAbsMean;

   for (int scaleNr = coarsestScale-2; scaleNr >= finestScale; scaleNr--)
   {
      finerX = x / common::MathUtils::ComputeIntegerPower(2, scaleNr);
      finerY = y / common::MathUtils::ComputeIntegerPower(2, scaleNr);

      xTopLeft = finerX - windowHalfSize;
      yTopLeft = finerY - windowHalfSize;
      xBottomRight = finerX + windowHalfSize;
      yBottomRight = finerY + windowHalfSize;

      finerAbsMean = GridStatistics<double>::ComputeLocalAbsoluteMean(  this->GetRecursiveScale( scaleNr )->GetOrientedBand( orientationNr ), xTopLeft, yTopLeft, xBottomRight, yBottomRight );

      T tmpValue = ( ( 4.0 * coarserAbsMean / GetScaleFactorResidualLevel() ) / finerAbsMean );
      if (tmpValue > 10000.0)
      {
         std::cout << " scaleNr = " << scaleNr << " orientationNr = " << orientationNr << " tmpValue = " << tmpValue << "\t coarser (" << coarserX << ", " << coarserY << ") -> finer (" << finerX << ", " << finerY << "), coarserAbsMean = "
                   << coarserAbsMean << " and finerAbsMean " << finerAbsMean << std::endl << std::flush;
      }
      ACR += ( ( 4.0 * coarserAbsMean / GetScaleFactorResidualLevel() ) / finerAbsMean );
      coarserAbsMean    = finerAbsMean;  // going to the next even finer level
      coarserX = finerX;
      coarserY = finerY;
   }
   return ( log( ACR / (coarsestScale - finestScale) ) / log(2.0) ); // log2(x) = log(x) / log(2)
}

//===========================================================================================

template <class T>
T Pyramid<T>::GetAverageConeRatioRedundant( int x, int y, int orientationNr, int finestScale, int coarsestScale )
{
   T ACR = 0;
   int scaleExponent = 1;

   if ( finestScale   <         0 ) { finestScale   =         0; }
   if ( coarsestScale > mNrScales ) { coarsestScale = mNrScales; }

   // starting from (mNrScales-1) which is the coarsest level, going to ever finer levels
   int coarserWindowSize = common::MathUtils::ComputeIntegerPower( 2, scaleExponent ) + 1;
   int coarserWindowHalfSize = coarserWindowSize / 2;
   T   coarserAbsMean    = GridStatistics<double>::ComputeLocalAbsoluteMean(  this->GetRecursiveScale( coarsestScale-1 )->GetOrientedBand( orientationNr ), x - coarserWindowHalfSize, y - coarserWindowHalfSize,
                                                                                                                                                             x + coarserWindowHalfSize, y + coarserWindowHalfSize );
   T   finerAbsMean;
   int finerWindowSize;

   scaleExponent++;

   for (int scaleNr = coarsestScale-2; scaleNr >= finestScale; scaleNr--)
   {
      finerWindowSize = common::MathUtils::ComputeIntegerPower( 2, scaleExponent ) + 1;
      int finerWindowHalfSize = finerWindowSize / 2;
      finerAbsMean = GridStatistics<double>::ComputeLocalAbsoluteMean(  this->GetRecursiveScale( scaleNr )->GetOrientedBand( orientationNr ), x - finerWindowHalfSize, y - finerWindowHalfSize,
                                                                                                                                               x + finerWindowHalfSize, y + finerWindowHalfSize);
      ACR += ( ( coarserAbsMean / GetScaleFactorResidualLevel() ) / finerAbsMean );
      coarserAbsMean    = finerAbsMean;  // going to the next even finer level
      coarserWindowSize = finerWindowSize;
      scaleExponent++;
   }
   return ( log( ACR / (coarsestScale - finestScale) ) / log(2.0) ); // log2(x) = log(x) / log(2)
}

//===========================================================================================

template <class T>
bool Pyramid<T>::CreateBands( int sourceWidth, int sourceHeight, bool isSubsampled, bool isLowestScaleSubsampled )
{
   if (mNrScales == (int)(mvpRecursivePyramidLevels.size()))
   {
      for (int scaleIndex = 0; scaleIndex < mNrScales; scaleIndex++)
      {
         PyramidLevel<T>* pPyramidLevel = mvpRecursivePyramidLevels[ scaleIndex ];
         int scaleWidth;
         int scaleHeight;

         if (isSubsampled )
         {
            if (isLowestScaleSubsampled)
            {
               scaleWidth  = sourceWidth  / common::MathUtils::ComputeIntegerPower( 2, scaleIndex + 1);
               scaleHeight = sourceHeight / common::MathUtils::ComputeIntegerPower( 2, scaleIndex + 1);
            }
            else
            {
               scaleWidth  = sourceWidth  / common::MathUtils::ComputeIntegerPower( 2, scaleIndex );
               scaleHeight = sourceHeight / common::MathUtils::ComputeIntegerPower( 2, scaleIndex );
            }
         }
         else
         {
            scaleWidth = sourceWidth;
            scaleHeight = sourceHeight;
         }
         bool needInitialisation = true;
         double initialValue = 0.0;

         if (scaleIndex == mNrScales-1)
         {
            mpLowPassResidual = new ArrayGrid<double>( scaleWidth, scaleHeight, needInitialisation, initialValue );
         }
         for (int orientationIndex = 0; orientationIndex < mNrOrientations; orientationIndex++)
         {
            ArrayGrid<T>* pGrid = new ArrayGrid<T>( scaleWidth, scaleHeight, needInitialisation, 0 );
            pPyramidLevel->AddOrientedBand( pGrid );
         }
      }

      bool needInitialisation = true;
      if (mpResidualPyramidLevels != 0)
      {
         for (int orientationIndex = 0; orientationIndex < mNrOrientations; orientationIndex++)
         {
            ArrayGrid<T>* pGrid = new ArrayGrid<T>( sourceWidth, sourceHeight, needInitialisation, 0 );
            mpResidualPyramidLevels->AddOrientedBand( pGrid );
         }
      }
      return true;
   }
   else
   {
      return false;
   }
}

//===========================================================================================

template <class T>
inline int Pyramid<T>::GetNumberOfScales()
{
   return mNrScales;
}

//===========================================================================================

template <class T>
inline int Pyramid<T>::GetNumberOfOrientations()
{
   return mNrOrientations;
}

//===========================================================================================

template <class T>
inline int Pyramid<T>::GetSourceDataWidth()
{
   return mpSourceDataGrid->GetWidth();
}

//===========================================================================================

template <class T>
inline int Pyramid<T>::GetSourceDataHeight()
{
   return mpSourceDataGrid->GetHeight();
}

//===================================================================================================

template <class T>
inline double Pyramid<T>::GetScaleFactorResidualLevel()
{
   return mScaleFactorResidualLevel;
}

//===================================================================================================

template <class T>
inline void Pyramid<T>::SetScaleFactorResidualLevel( double factor )
{
   mScaleFactorResidualLevel = factor;
}

//===================================================================================================

template <class T>
inline double Pyramid<T>::GetScaleFactorResidualToRecursiveLevel()
{
   return mScaleFactorResidualToRecursiveLevel;
}

//===================================================================================================

template <class T>
inline void Pyramid<T>::SetScaleFactorResidualToRecursiveLevel( double factor )
{
   mScaleFactorResidualToRecursiveLevel = factor;
}

//===================================================================================================

template <class T>
inline double Pyramid<T>::GetScaleFactorRecursiveLevel()
{
   return mScaleFactorRecursiveLevel;
}

//===================================================================================================

template <class T>
inline void Pyramid<T>::SetScaleFactorRecursiveLevel( double factor )
{
   mScaleFactorRecursiveLevel = factor;
}

//===========================================================================================

template <class T>
inline ArrayGrid<double>* Pyramid<T>::GetLowpassResidual()
{
   return mpLowPassResidual;
}

//===========================================================================================

template <class T>
inline void Pyramid<T>::SetLowpassResidual( ArrayGrid<double>* pGrid)
{
   if (mpLowPassResidual != 0)
   {
      delete mpLowPassResidual;
      mpLowPassResidual = 0;
   }
   mpLowPassResidual = pGrid;
}

//===========================================================================================

template <class T>
inline PyramidLevel<T>* Pyramid<T>::GetRecursiveScale(int scale)
{
   if (scale < this->GetNumberOfScales())
   {
      return mvpRecursivePyramidLevels[scale];
   }
   else
   {
      return 0;
   }
}

//===========================================================================================

template <class T>
inline PyramidLevel<T>* Pyramid<T>::GetResidualScale()
{
   return mpResidualPyramidLevels;
}

//===========================================================================================

template <class T>
inline bool Pyramid<T>::HasResidualScale()
{
   return (mpResidualPyramidLevels != 0);
}

//===========================================================================================

template <class T>
inline int Pyramid<T>::GetFinestScaleNumber()
{
   if ( HasResidualScale() )
   {
      return -1;
   }
   else
   {
      return 0;
   }
}

//===========================================================================================

//template <class T>
//void Pyramid<T>::ExportBandsToPGM()
//{
//   int nrLevels = (int)(mvpRecursivePyramidLevels.size());
//
//   for (int i = 0; i < nrLevels; i++)
//   {
//      mvpRecursivePyramidLevels[i]->ExportBandsToPGM( std::string("B"), i);
//   }
//   if (mpResidualPyramidLevels != 0)
//   {
//      mpResidualPyramidLevels->ExportBandsToPGM( std::string("A"), 0);
//   }
//   if (mpLowPassResidual != 0)
//   {
//      ImageIO::WritePGM( mpLowPassResidual, std::string("LowpassResidual.pgm"), ImageIO::NORMAL_OUT);
//   }
//}

//===========================================================================================

}
}

#endif
