
/***********************************************************************************
 *   Copyright (C) 2012 by Filip Rooms                                             *
 *                                                                                 *
 *  Terms and conditions for using this software in any form are provided in the   *
 *  file COPYING, which can be found in the root directory of this project.        *
 *                                                                                 *
 *   Contact data: filip.rooms@gmail.com                                           *
 *                 http://www.filiprooms.be/                                       *
 *                                                                                 *
 ***********************************************************************************/

#ifndef STIRA_HISTOGRAM_RUNLENGTHHISTOGRAM_H
#define STIRA_HISTOGRAM_RUNLENGTHHISTOGRAM_H

#include <string>
#include <vector>
#include "../../image/datastructures/ArrayGrid.h"
#include "../../common/common/Point.h"


using namespace stira;
using namespace stira::image;

namespace stira {
namespace histogram {

struct CurveSegment
{
   int startX;
   int length;
};

/** \brief histogram to keep track which widths are found over which yarn lengths
  * Reference: http://www.nlpr.ia.ac.cn/2008papers/gjhy/gh87.pdf
  *            http://www.roborealm.com/help/ShapeHistogram.php */
class RunLengthHistogram
{
public:
   /** \brief constructor
     * \param maxWidth maximal possible yarn width, even in case of severe yarn defect
     * \param maxLength maximal possible segment length */
   RunLengthHistogram( int maxWidth, int maxLengthHistogram );

   /** \brief Copy constructor. */
   RunLengthHistogram( const RunLengthHistogram& runLengthHistogram );

   /** \brief Copy constructor. */
   RunLengthHistogram* Clone( );

   int GetMaxWidth() const;
   int GetMaxLengthInHistogram() const;
   std::vector< std::vector< CurveSegment > > GetWidthLengthHistogram() const;
   std::vector< std::vector<double> > GetHistogram2D() const;
   std::vector< CurveSegment > GetCurrentWidthVector() const;
   std::vector< common::Point<int> > GetSegmentStartPointVector() const;


   /** \brief analyse run lengths of yarn widths
     * \param vYarnWidths vector of yarn width per point along the yarn
     * \param startIndex index from where to start */
   bool Analyse( std::vector<int> vYarnWidths, int startIndex=0 );

   /** \brief Gets all segments with a specified width
     * \param width specified width to find all segments of */
   std::vector< CurveSegment > GetSegmentsWithWidth( int width );

   /** \brief Gets all segments with a specified width of a given length
     * \param width specified width to find all segments of
     * \param length width specified lengthwidth to find all segments of */
   std::vector< CurveSegment > GetSegmentsWithGivenWidthOfGivenLength( int width, int length );

   /** \brief Gets a number of the longest segments with specified width
     * \param width specified width to find longest segments */
   std::vector< CurveSegment > GetLongestSegmentsWithGivenWidth( int width, int nrSegments );

   /** \brief Counts all segments with a specified width of a given length
     * \param width specified width to find all segments of */
   int CountSegmentsWithGivenWidthOfGivenLength( int width, int length );

   /** \brief Gets longest segment with specified width
     * \param width specified width to find longest segments */
   double ComputeEntropy();

   /** \brief Writes current run length segments to a file on disk
     * \param fileName the name of the file to write to */
   void WriteSegments( std::string fileName, int index );

   /** \brief Writes current run length histogram to a file on disk
     * \param fileName the name of the file to write to */
   void WriteHistogram( std::string fileName, int index );

private:
   /** \brief initializer function */
   void Initialize( );

   int mMaxWidth;  ///< maximal possible yarn width, as needed to allocate sufficient space for the histogram
   int mMaxLengthHistogram;  ///< maximal possible segment length represented in histogram
   std::vector< std::vector< CurveSegment > > mvvWidthLengthHistogram;  ///< the actual run length histogram
   std::vector< std::vector<double> > mvvHistogram2D;
   std::vector< CurveSegment > mvCurrentWidthVector;   ///< help structure to keep track of the current widths
   std::vector< common::Point<int> > mvSegmentStartPointVector; ///< help structure to keep track of the current start points for segments
};

}
}

#endif // YARNRUNLENGTHHISTOGRAM_H
