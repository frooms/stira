
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

#ifndef STIRA_HISTOGRAM_FLOATHISTOGRAM_H
#define STIRA_HISTOGRAM_FLOATHISTOGRAM_H

#include "IntHistogram.h"
#include "HistogramMaster.h"

namespace stira {
namespace histogram {

/** \brief Class for floating point valued histograms
  * E.g. needed to represent an normailzed histogram when performing histogram equalization
  * WARNING: currently only works for default case when bin size is 1*/
class FloatHistogram: public HistogramMaster<double>
{
public:

   /** \brief constructor for histogram object
     * \param nrOfBins number of bins in the histogram
     * \param nrBands number of bands in the histogram (on per colour chanel) */
   FloatHistogram( int nrOfBins, int nrBands );

   /** \brief constructor with initialization from IntHistogram
     * \param pIntHistogram histogram to initialize this histogram from
     * \param requiresNormalization flag whether the values need to be normalized */
   FloatHistogram( IntHistogram* pIntHistogram, bool requiresNormalization );

   /** \brief Copy constructor.
     * \param pFloatHistogram histogram from which to initialize this new histogram */
   FloatHistogram( const FloatHistogram& pFloatHistogram ) : HistogramMaster<double>( pFloatHistogram ){}

   /** \brief Creates a clone of this FloatHistogram
     * This clone becomes the responsability of the caller to delete */
   FloatHistogram* Clone();

   bool UpdateHistogram( IntHistogram* pIntHistogram, double alpha );

private:
   /** \brief help method to copy internal data from other FloatHistogram
     * \param otherArrayGrid the other grid to copy from*/
   bool CreateHistogramCopy(const FloatHistogram& otherFloatHistogram);

public:
   /**  \brief destructor for histogram object */
   virtual ~FloatHistogram();

   /** \brief Normalizes each band in the current histogram to 1 */
   void Normalize( );

   /** \brief Gets the value that corresponds with the given band and bin
     * \param band the image band for which to get the histogram value
     * \param bin  the bin for which to get the histogram value
     * \return value that corresponds with \e band and \e bin */
   double GetBinValueHistogramData(int band, int bin);

   /** \brief compute normalized histogram by dividing the histogram values by the total number of counts in the histogram
     * \param pStandardHistogram   standard histogram, needed to normalize the cumulative histogram  */
   void InitializeWithNormalizedHistogram( IntHistogram* pStandardHistogram );

   /** \brief compute normalized cumulative histogram by dividing the cumulative histogram values by the standard histogram values
     * \param pStandardHistogram   standard histogram, needed to normalize the cumulative histogram
     * \param pCumulativeHistogram histogram to be normalized */
   void InitializeWithNormalizedCumulativeHistogram( IntHistogram* pStandardHistogram, IntHistogram* pCumulativeHistogram );

   /** \brief computes standard Kullback-Leibler divergence between this histogram and the histogram in the argument
     * Reference http://en.wikipedia.org/wiki/Kullback–Leibler_divergence
     *  Zero entries: http://mathoverflow.net/questions/72668/how-to-compute-kl-divergence-when-pmf-contains-0s
     * Warning: assumes that both histograms are normalized
     * \param pOtherHistogram histogram to compute distance with */
   double ComputeStandardKullbackLeiblerDistance( FloatHistogram* pOtherHistogram );

   /** \brief computes entropy of this histogram
     * Reference: http://en.wikipedia.org/wiki/Entropy_(information_theory)
     *  Zero entries: http://mathoverflow.net/questions/72668/how-to-compute-kl-divergence-when-pmf-contains-0s
     * Warning: assumes that this histogram is normalized */
   double ComputeEntropy( );

   /** \brief computes symmetric Kullback-Leibler divergence between this histogram and the histogram in the argument
     * Reference http://en.wikipedia.org/wiki/Kullback–Leibler_divergence
     * Warning: assumes that both histograms are normalized
     * \param pOtherHistogram histogram to compute distance with */
   double ComputeSymmetricKullbackLeiblerDistance( FloatHistogram* pOtherHistogram );

   /** \brief computes the square root of the Jensen–Shannon divergence between the current histogram and the histogram passed as argument
     * the Jensen–Shannon divergence is a popular method of measuring the similarity between two probability distributions.
     * It is based on the Kullback–Leibler divergence, with the notable (and useful) difference that it is always a finite value.
     * The square root of the Jensen–Shannon divergence is a metric.
     * Reference: - http://en.wikipedia.org/wiki/Jensen–Shannon_divergence
     *            - A New Metric for Probability Distributions, D. Endres & J. Schindelin, IEEE Trans. Information Theory,
     *              VOL. 49, NO. 7, JULY 2003, pp. 1858 -- 1860
     * \param pOtherHistogram histogram to compute distance with*/
   double ComputeJensenShannonMetric( FloatHistogram* pOtherHistogram );

   /** \brief computes Csiszar's I-divergence between this histogram and the histogram in the argument
     * Reference  Csiszar, I. (1991). "Why least squares and maximum entropy? an axiomatic approach to
     *            inference for linear inverse problems. Annals of Statistics, 19(4):2032–2066.
     *            See online access at http://www.jstor.org/
     * \param pOtherHistogram histogram to compute distance with */
   double ComputeIDivergence( FloatHistogram* pOtherHistogram );

   /** \brief writes values from current histogram to a file
     * \param fileName name of file to write values in*/
   virtual bool Write( std::string fileName);

   /** \brief Sets the threshold value to compare values in the histogram with each other or with zero
     * \param epsilonValue the epsilon threshold value*/
   void SetEpsilonThreshold( double epsilonValue );

   /** \brief Gets the threshold value to compare values in the histogram with each other or with zero */
   double GetEpsilonThreshold( );

private:

   double mEpsilonThreshold; ///< threshold for values that are close to zero
};
}
}
#endif
