
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

#ifndef STIRA_HISTOGRAM_INTHISTOGRAM_H
#define STIRA_HISTOGRAM_INTHISTOGRAM_H

#include "HistogramMaster.h"
#include "../../imagedata/datastructures/Image.h"
#include "../../common/common/RectangularROI.h"

namespace stira {
namespace histogram {

using namespace stira::imagedata;

/** \brief simple histogram class
  * WARNING: currently only works for default case when bin size is 1*/
class IntHistogram : public HistogramMaster<int>
{
public:
   /** \brief constructor
     *
     * Constructs object and builds the histogram based on the input parameters.
     * After construction, the histogram is ready to be used
     *
     * \param pImage input image for which to construct the histogram
     * \param lowerFraction percentage of pixels with lowest intensities;  to be ignored
     * \param upperFraction (1 -upperFraction) is percentage of pixels with highest intensities to be ignored
     * \param binsize size for a histogram bin
     * \param pMaskGrid grid which pixels are taken into account (true) and which need to be ignored (false)*/
   IntHistogram( Image* pImage, bool useDataMinMax, double lowerFraction=0.01, double upperFraction=0.99, int binsize=1, ArrayGrid<bool>* pMaskGrid=0);

   /** \brief constructor
     *
     * Constructs object and builds the histogram based on the input parameters.
     * After construction, the histogram is ready to be used
     *
     * \param pImage input image for which to construct the histogram
     * \param rroi the rectangular Region Of Interest for which to build the histogram
     * \param lowerFraction percentage of pixels with lowest intensities;  to be ignored
     * \param upperFraction (1 -upperFraction) is percentage of pixels with highest intensities to be ignored
     * \param binsize size for a histogram bin
     * \param pMaskGrid grid which pixels are taken into account (true) and which need to be ignored (false)*/
   IntHistogram( Image* pImage, bool useDataMinMax, common::RectangularROI<int> rroi, double lowerFraction=0.01, double upperFraction=0.99, int binsize=1 );

   /** \brief constructor
     *
     * Constructs object and builds the histogram based on the input parameters.
     * After construction, the histogram is ready to be used
     *
     * \param pGrid input grid
     * \param lowerFraction lower fraction of pixel to set
     * \param upperFraction upper fraction of pixel to set
     * \param binsize size of bin
     * \param pMaskGrid boolean grid which pixels to count (at position with true) and which to ignore  (at position with false) */
   IntHistogram( ArrayGrid<double>* pGrid, bool useDataMinMax, double lowerFraction=0.01, double upperFraction=0.99, int binsize=1, ArrayGrid<bool>* pMaskGrid=0);

   /** \brief constructor
     *
     * Constructs object and builds the histogram based on the input parameters.
     * After construction, the histogram is ready to be used
     *
     * \param pGrid input grid for which to construct the histogram
     * \param rroi the rectangular Region Of Interest for which to build the histogram
     * \param lowerFraction lower percentile divided by 100 (value between 0 and 1) of pixels; pixels with lower intensities will be ignored
     * \param upperFraction upper percentile divided by 100 (value between 0 and 1) of pixels; pixels with higher intensities will be ignored
     * \param binsize size for a histogram bin
     * \param pMaskGrid grid which pixels are taken into account (true) and which need to be ignored (false)*/
   IntHistogram( ArrayGrid<double>* pGrid, bool useDataMinMax, common::RectangularROI<int> rroi, double lowerFraction=0.01, double upperFraction=0.99, int binsize=1 );

   /** \brief constructor
     *
     * Constructs object and builds an empty histogram based on the input parameters.
     * After construction, the histogram is initialized with all bins to 0
     *
     * \param binSize width of a single bin
     * \param nrOfBands number of bands (usually 3 (color images) or 1 (gray image))
     * \param minValue minimum value in the histogram
     * \param maxValue maximum value in the histogram */
   IntHistogram( double binSize, int nrOfBands, int minValue, int maxValue, double lowerFraction=0.01, double upperFraction=0.99 );

   /** \brief destructor*/
   virtual ~IntHistogram();

   /** \brief Copy constructor.
     * \param pHistogram histogram from which to initialize this new histogram */
   IntHistogram( const IntHistogram& pHistogram ) : HistogramMaster<int>(pHistogram)
   {
      mIscumulativeHistogram = false;
      //std::cout << "Child copy constructor IntHistogram" << std::endl << std::flush;
   }

   /** \brief Creates a clone of this arraygrid
     * This clone becomes the responsability of the caller to delete */
   IntHistogram* Clone();

   bool UpdateHistogram( IntHistogram* pIntHistogram, double alpha );

   /** \brief gets lower fraction
     * when the lower fraction is 5%, it means that we consider the 5% of the pixels with smallest intensities*/
   double GetLowerFraction();

   /** \brief sets lower fraction
     * when the lower fraction is 5%, it means that we consider the 5% of the pixels with smallest intensities
     * \param myFraction fraction of the pixels*/
   void SetLowerFraction(double myFraction);

   /** \brief gets lower bound for given band nr
     * The lower bound depends on the lower fraction: when the lower fraction is 5%, the lower bound is that image band
     * intensity that 5% of the pixels has an intensity (in the given band) smaller than the lower bound
     * \param bandNr nr of band*/
   double GetLowerBound(int bandNr=0);

   /** \brief gets lower fraction
     * when the upper fraction is 95%, it means that we consider the 95% of the pixels with smallest intensities*/
   double GetUpperFraction();

   /** \brief sets upper fraction
     * when the upper fraction is 95%, it means that we consider the 95% of the pixels with smallest intensities
     * \param myFraction  the upper fraction*/
   void SetUpperFraction(double myFraction);

   /** \brief gets upper bound for given band nr
     * The upper bound depends on the upper fraction: when the upper fraction is 95%, the upper bound is that image band
     * intensity that 95% of the pixels has an intensity (in the given band) smaller than the lower bound
     * \param bandNr nr of band*/
   double GetUpperBound(int bandNr=0);

   /** \brief Gets the quantile value for a given probability
     * I.e., if we give as probability 0.25, this function will return where in the histogram you reach the point that 25% of the samples are below this point
     * Is actually the same as GetLowerBound for a given LowerFraction and GetUpperBound for a given UpperFraction*/
   double GetQuantile( int bandNr, double probability );

   /** \brief converts histogram data to cumulative histogram */
   void ConvertInCumulativeHistogram();

   virtual bool Write( std::string fileName);

   /** \brief determines bound of histogram where lower fraction and upper fraction of the histogram are situated*/
   bool DetermineBounds(int bandNr = 0);

private:

   /** \brief computes the histogram for the input image
     * \param pImage image for which to build histogram
     * \param pMaskGrid boolean grid which pixels to count (at position with true) and which to ignore  (at position with false)*/
   bool BuildHistogram( Image* pImage, ArrayGrid<bool>* pMaskGrid=0);

   /** \brief computes the histogram for the input grid
     * \param pGrid grid for which to build histogram
     * \param pMaskGrid boolean grid which pixels to count (at position with true) and which to ignore  (at position with false)*/
   bool BuildHistogram( ArrayGrid<double>* pGrid, int bandNr=0, ArrayGrid<bool>* pMaskGrid=0);

   bool mInitializedFromGrid;

   bool mUsesROI;
   bool mIscumulativeHistogram;
   common::RectangularROI<int> mROI;

   double mLowerFraction;  ///< lower fraction of pixels (i.e., with minimal intensity)
   double mUpperFraction;  ///< upper fraction of pixels (i.e., with maximal intensity)

   std::vector<double> mvLowerBound;  ///< vector of lower bounds (one per band)
   std::vector<double> mvUpperBound;  ///< vector of upper bounds (one per band)
};

}
}
#endif
