
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

#ifndef STIRA_HISTOGRAM_CONDITIONALHISTOGRAM_H
#define STIRA_HISTOGRAM_CONDITIONALHISTOGRAM_H

#include "../../image/datastructures/Image.h"

namespace stira {
namespace histogram {

/** \brief simple histogram class
  * WARNING: currently only works for default case when bin size is 1*/
class ConditionalHistogram
{
public:
   /** \brief constructor
     * \param horizontalBinSize size of a bin on the horizontal axis
     * \param verticalBinSize  size of a bin on the vertical axis
     * \param horizontalMin minimum value on the horizontal axis
     * \param horizontalMax maximum value on the horizontal axis
     * \param verticalMin minimum value on the vertical axis
     * \param verticalMax minimum value on the vertical axis 
     * All histogram values are initialized to 0 */
   ConditionalHistogram( double horizontalBinSize, double verticalBinSize, 
                         double horizontalMin, double horizontalMax, 
                         double verticalMin, double verticalMax, int nrBands=1 );

   /** \brief constructor
     * Initializes and builds conditional histogram based on the two input images
     * \param pImage1 first input image
     * \param pImage2 second  input image
     * \param useAbsoluteValues flag to use absolute values instead of normal values*/
   ConditionalHistogram( image::Image* pImage1, image::Image* pImage2, bool useAbsoluteValues=false );
   
   /** \brief constructor
     * Initializes and builds conditional histogram based on the two input grids
     * \param pGrid1 first input grid
     * \param pGrid2 second  input grid
     * \param useAbsoluteValues flag to use absolute values instead of normal values*/
   ConditionalHistogram( image::ArrayGrid<double>* pGrid1, image::ArrayGrid<double>* pGrid2, bool useAbsoluteValues=false );
   
   /** \brief destructor*/
   ~ConditionalHistogram();
   
   /** \brief writes current histogram to text file*/
   bool Write( std::string fileName);
   
   /** \brief Gets nr of bins on the horizontal axis in the histogram*/
   int GetNrOfHorizontalBins();
   
   /** \brief Gets nr of bins on the vertical axis in the histogram*/
   int GetNrOfVerticalBins();
   
   /** \brief visualizes the current conditional histogram as an image
     * \param imageName name for the exported image as disk file */
   void VisualizeAsImage( std::string imageName );

private:

   /** \brief Increases the value in the given grid for the given bin numbers by one
     * \param pGrid grid to add one to at location (x, y)
     * \param x bin nr on the horizontal axis 
     * \param y bin nr on the vertical axis */
   void AddOne( image::ArrayGrid<int>* pGrid, int x, int y);
   
   /** \brief Gets the value in the given band for the given bin numbers 
     * \param band nr of the band
     * \param x bin nr on the horizontal axis 
     * \param y bin nr on the vertical axis */
   int GetValue(int band, int x, int y);
   
   /** \brief builds a conditional histogram between the two given grids
     * \param pGrid1 first grid as input
     * \param pGrid2 second grid as input
     * \param absoluteValue flag whether to use the input values as they are or their absolute values*/
   void BuildConditionalHistogram( image::ArrayGrid<double>* pGrid1, image::ArrayGrid<double>* pGrid2, bool absoluteValue=false );
   
   std::vector< image::ArrayGrid<int>* > mvpData;  ///< the actual histogram data
   int mNrBands;  ///< nr of bands used
   int mHorizontalBinSize; ///< size of a bin on the horizontal axis
   int mVerticalBinSize;   ///< size of a bin on the vertical axis
   double mHorizontalMin;  ///< minimum value on the horizontal axis
   double mHorizontalMax;  ///< maximum value on the horizontal axis
   double mVerticalMin;    ///< minimum value on the vertical axis
   double mVerticalMax;    ///< maximum value on the vertical axis
};

}
}
#endif
