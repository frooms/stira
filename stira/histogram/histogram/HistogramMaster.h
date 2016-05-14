
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

#ifndef STIRA_HISTOGRAM_HISTOGRAMMASTER_H
#define STIRA_HISTOGRAM_HISTOGRAMMASTER_H

//#define USE_SAFE

#include <iostream>

namespace stira {
namespace histogram {

/** \brief simple histogram class */

template <class T>
class HistogramMaster
{
public:

   /** \brief adds a value to the histogram
     * This is a generalization of AddOneToBin, since here also bin sizes not equal to one can be used;
     * the bin number will be calculated depending on the bin size and then one will be added to that bin.
     * \param valueToAdd the value to the histogram
     * \param binNr the bin number to read out */
   void AddDataPoint( int valueToAdd, int bandNr=0 );

   /** \brief set all bins to zero */
   void SetBinsToZero();

   /** \brief gets nr of counts in given bin nr for a given band nr
     * if the macro USE_SAFE is defined, we use the version with boundary checking, else we use the fast
     * (unsafe) call to get the data from the array
     * \param bandNr for multidimensional histograms, e.g. one histogram per color band in an image
     * \param binNr the bin number to read out */
   T GetBinValue( int bandNr, int binNr ) const;

   /** \brief gets nr of counts in given bin nr for a given band nr
     * Specific safe call for above with extra boundary checking
     * \param bandNr for multidimensional histograms, e.g. one histogram per color band in an image
     * \param binNr the bin number to read out */
   T GetBinValueSafe( int bandNr, int binNr ) const;

   /** \brief Gets nr of bins in the histogram
     * For now, we assume bin size is 1, so the number of bins is the data range mRange*/
   int GetNrOfBins() const;

   /** \brief Gets nr of bands in the histogram*/
   int GetNrOfBands() const;

   /** \brief for diagnostics, write histogram to file
     * To be implemented by child classes
     * \param fileName name of file to write to */
   virtual bool Write( std::string fileName )=0;

   /** \brief Gets total nr of counts in the histogram
     * This number is the number of pixels in the image that were counted. We don't
     * count the same pixel over and over again for different bands in the image; we just
     * assume that the ROI for which the histogram was computed is the same for all bands
     * in an image */
   int GetNrOfCounts() const;

   /** \brief Gets the width of a histogram bin */
   T GetBinSize() const;

   /** \brief Gets the minimum of the data range */
   T GetDataMinimum() const;

   /** \brief Gets the maximum of the data range */
   T GetDataMaximum() const;

   /** \brief sets nr of counts in given bin nr for a given band nr
     * if the macro USE_SAFE is defined, we use the version with boundary checking, else we use the fast
     * (unsafe) call to get the data from the array
     * \param bandNr for multidimensional histograms, e.g. one histogram per color band in an image
     * \param binNr the bin number to write a value in */
   void SetBinValue( int bandNr, int binNr, T value );

protected:

   /** \brief adds one count in given bin nr for a given band nr
     * if the macro USE_SAFE is defined, we use the version with boundary checking, else we use the fast
     * (unsafe) call to get the data from the array
     * \param bandNr for multidimensional histograms, e.g. one histogram per color band in an image
     * \param binNr the bin number to add one count to */
   void AddOneToBin( int bandNr, int binNr );

   /** \brief adds one count in given bin nr for a given band nr
     * Specific safe call for above with extra boundary checking
     * \param bandNr for multidimensional histograms, e.g. one histogram per color band in an image
     * \param binNr the bin number to add one count to */
   void AddOneToBinSafe( int bandNr, int binNr );

   /** \brief adds one count in given bin nr in case there is just a single band
     * if the macro USE_SAFE is defined, we use the version with boundary checking, else we use the fast
     * (unsafe) call to get the data from the array
     * \param bandNr for multidimensional histograms, e.g. one histogram per color band in an image
     * \param binNr the bin number to add one count to */
   void AddOneToBin( int binNr );

   /** \brief adds one count in given bin nr in case there is just a single band
     * Specific safe call for above with extra boundary checking
     * \param bandNr for multidimensional histograms, e.g. one histogram per color band in an image
     * \param binNr the bin number to add one count to */
   void AddOneToBinSafe( int binNr );

   /** \brief constructor
     * only to be called from child classes */
   HistogramMaster( );

   /** \brief Copy constructor.
     * \param pHistogram histogram from which to initialize this new histogram */
   HistogramMaster( const HistogramMaster& pHistogram );

   /** \brief destructor
     * only to be called from child classes */
   virtual ~HistogramMaster();

   /** \brief Initializes member variables and creates and initializes histogram data structure
     * Creation and initialization of the histogram data structure is done by calling CreateInitializedDataStructure,
     * which does not initialize the other member variables
     * \param binSize the width of a histogram bin
     * \param nrOfBands nr of spectral bands in an image
     * \param minValue minimum value represented in the histogram
     * \param maxValue maximum value represented in the histogram*/
   void Initialize( T binSize, int nrOfBands, T minValue, T maxValue );

   /** \brief Just creates and initializes histogram data structure
     * does not initialize the other member variables */
   void CreateInitializedDataStructure( );

   /** \brief sets nr of counts in given bin nr for a given band nr
     * Specific safe call for above with extra boundary checking
     * \param bandNr for multidimensional histograms, e.g. one histogram per color band in an image
     * \param binNr the bin number to write a value in */
   void SetBinValueSafe( int bandNr, int binNr, T value );

   T** mpHistogram;  ///< the actual histogram (we count nr of intensities per colour band)
   T mBinSize;  ///< size of histogram bin
   int mNrOfBands;  ///< nr of bands in image
   int mNrOfBins;  ///< nr of bins in histogram
   int mNrOfCounts;  ///< nr of pixels in image = nr of counts in histogram per band
   T mMin;  ///< min intensity in histogram
   T mMax;  ///< max intensity in histogram
};

//===========================================================================================

template <class T>
HistogramMaster<T>::HistogramMaster( )
{
   mBinSize = 1;
   mNrOfBands = 0;
   mNrOfCounts = 0;
   mMin = 0;
   mMax = 0;

   mNrOfBins = 0;

   mpHistogram = 0;
}

//-------------------------------------------------------------------

template <class T>
HistogramMaster<T>::HistogramMaster( const HistogramMaster<T>& pHistogram )
{
   mBinSize = pHistogram.GetBinSize();
   mNrOfBands = pHistogram.GetNrOfBands();
   mNrOfCounts = pHistogram.GetNrOfCounts();
   mMin = pHistogram.GetDataMinimum();
   mMax = pHistogram.GetDataMaximum();

   mNrOfBins = pHistogram.GetNrOfBins();

   mpHistogram = new T*[mNrOfBands];
   for (int bandNr = 0; bandNr < mNrOfBands; bandNr++)
   {
      mpHistogram[bandNr] = new T[mNrOfBins];
      for (int binNr = 0; binNr < mNrOfBins; binNr++)
      {
         mpHistogram[bandNr][binNr] = pHistogram.GetBinValue( bandNr, binNr );
      }
   }
}

//-------------------------------------------------------------------

template <class T>
void HistogramMaster<T>::Initialize( T binSize, int nrOfBands, T minValue, T maxValue )
{
   mBinSize = binSize;
   mNrOfBands = nrOfBands;
   mNrOfCounts = 0;
   mMin = minValue;
   mMax = maxValue;

   mNrOfBins = (int)((( maxValue - minValue ) / binSize) + 1.0);

   this->CreateInitializedDataStructure( );
}

//-------------------------------------------------------------------

template <class T>
void HistogramMaster<T>::CreateInitializedDataStructure( )
{
   mpHistogram = new T*[mNrOfBands];
   for (int bandNr = 0; bandNr < mNrOfBands; bandNr++)
   {
      mpHistogram[bandNr] = new T[mNrOfBins];
   }
   SetBinsToZero();
}

//-------------------------------------------------------------------

template <class T>
void HistogramMaster<T>::SetBinsToZero()
{
   mNrOfCounts = 0;
   for (int bandNr = 0; bandNr < mNrOfBands; bandNr++)
   {
      for (int binNr = 0; binNr < mNrOfBins; binNr++)
      {
         mpHistogram[bandNr][binNr] = 0;
      }
   }
}

//-------------------------------------------------------------------

template <class T>
HistogramMaster<T>::~HistogramMaster()
{
   for (int bandNr = 0; bandNr < mNrOfBands; bandNr++)
   {
      delete []mpHistogram[bandNr];
   }
   delete []mpHistogram;
}

//-------------------------------------------------------------------

template <class T>
inline T HistogramMaster<T>::GetBinValueSafe( int bandNr, int binNr ) const
{
   if ( (bandNr < mNrOfBands) && ( binNr < mNrOfBins ) )
   {
      return mpHistogram[bandNr][binNr];
   }
   else
   {
      std::cerr << "HistogramMaster : getting bandNr " <<  bandNr << " while mNrOfBands is " << mNrOfBands
           << " binNr " << binNr << " while mNrOfBins is " << mNrOfBins << std::endl << std::flush;
      return -1.0;
   }
}

//-------------------------------------------------------------------

template <class T>
inline T HistogramMaster<T>::GetBinValue( int bandNr, int binNr ) const
{
   #ifdef USE_SAFE
   return this->GetBinValueSafe( bandNr, binNr );
   #else
   return mpHistogram[bandNr][binNr];
   #endif
}

//----------------------------------------------------------------
template <class T>
inline void HistogramMaster<T>::AddOneToBin( int bandNr, int binNr )
{
   #ifdef USE_SAFE
      AddOneToBinSafe( bandNr, binNr );
   #else
      mpHistogram[ bandNr ][ binNr ] ++;
      mNrOfCounts++;
   #endif
}

//-----------------------------------------------------------------
template <class T>
inline void HistogramMaster<T>::AddOneToBinSafe( int bandNr, int binNr )
{
   if ( ( bandNr < mNrOfBands) && ( binNr < mNrOfBins ) )
   {
      mpHistogram[ bandNr ][ binNr ] ++;
      mNrOfCounts++;
   }
   else
   {
      std::cerr << "HistogramMaster : setting bandNr " <<  bandNr << " while mNrOfBands is " << mNrOfBands
           << " binNr " << binNr << " while mNrOfBins is " << mNrOfBins << std::endl << std::flush;
   }
}

//----------------------------------------------------------------

template <class T>
inline void HistogramMaster<T>::AddDataPoint( int valueToAdd, int bandNr )
{
   int binNr = valueToAdd / mBinSize;
   #ifdef USE_SAFE
      AddOneToBinSafe( bandNr, binNr );
   #else
      mpHistogram[ bandNr ][ binNr ] ++;
      mNrOfCounts++;
   #endif
}

//----------------------------------------------------------------
template <class T>
inline void HistogramMaster<T>::AddOneToBin( int binNr )
{
   #ifdef USE_SAFE
      AddOneToBinSafe( 0, binNr );
   #else
      mpHistogram[ 0 ][ binNr ] ++;
      mNrOfCounts++;
   #endif
}

//-----------------------------------------------------------------
template <class T>
inline void HistogramMaster<T>::AddOneToBinSafe( int binNr )
{
   if ( ( mNrOfBands > 0) && ( binNr < mNrOfBins ) )
   {
      mpHistogram[ 0 ][ binNr ] ++;
      mNrOfCounts++;
   }
   else
   {
      std::cerr << "HistogramMaster : setting bandNr 0 while mNrOfBands is " << mNrOfBands
           << " binNr " << binNr << " while mNrOfBins is " << mNrOfBins << std::endl << std::flush;
   }
}

//-------------------------------------------------------------------

template <class T>
inline void HistogramMaster<T>::SetBinValueSafe( int bandNr, int binNr, T value )
{
   if ( (bandNr < mNrOfBands) && ( binNr < mNrOfBins ) )
   {
      mpHistogram[bandNr][binNr] = value;
   }
   else
   {
      std::cerr << "HistogramMaster : setting bandNr " <<  bandNr << " while mNrOfBands is " << mNrOfBands
           << " binNr " << binNr << " while mNrOfBins is " << mNrOfBins << std::endl << std::flush;
   }
}

//-------------------------------------------------------------------

template <class T>
inline void HistogramMaster<T>::SetBinValue( int bandNr, int binNr, T value )
{
   #ifdef USE_SAFE
   SetBinValueSafe( bandNr, binNr, value );
   #else
   mpHistogram[bandNr][binNr] = value;
   #endif
}

//-------------------------------------------------------------------

template <class T>
inline int HistogramMaster<T>::GetNrOfBands() const
{
   return mNrOfBands;
}

//-------------------------------------------------------------------

template <class T>
inline int HistogramMaster<T>::GetNrOfBins() const
{
   return mNrOfBins;
}

//-------------------------------------------------------------------

template <class T>
inline int HistogramMaster<T>::GetNrOfCounts() const
{
   return mNrOfCounts;
}

//-------------------------------------------------------------------

template <class T>
inline T HistogramMaster<T>::GetBinSize() const
{
   return mBinSize;
}

//-------------------------------------------------------------------

template <class T>
inline T HistogramMaster<T>::GetDataMinimum() const
{
   return mMin;
}

//-------------------------------------------------------------------

template <class T>
inline T HistogramMaster<T>::GetDataMaximum() const
{
   return mMax;
}


//-------------------------------------------------------------------

}
}
#endif
