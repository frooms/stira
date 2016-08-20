
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

#ifndef STIRA_HISTOGRAM_JOINTHISTOGRAM_H
#define STIRA_HISTOGRAM_JOINTHISTOGRAM_H
#include "FloatHistogram.h"
#include "../../imagedata/datastructures/Image.h"

namespace stira {
namespace histogram {

/** \brief conditional or joint histogram class
  * WARNING: currently only works for default case when bin size is 1*/
class JointHistogram
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
   JointHistogram( double horizontalBinSize, double verticalBinSize,
                   double horizontalMin, double horizontalMax,
                   double verticalMin, double verticalMax, int nrBands=1 );

   /** \brief constructor
     * Initializes and builds conditional histogram based on the two input images
     * \param pImage1 first input image
     * \param pImage2 second  input image
     * \param useAbsoluteValues flag to use absolute values instead of normal values*/
   JointHistogram( Image* pImage1, Image* pImage2, bool useAbsoluteValues=false );

   /** \brief constructor
     * Initializes and builds conditional histogram based on the two input grids
     * \param pGrid1 first input grid
     * \param pGrid2 second  input grid
     * \param useAbsoluteValues flag to use absolute values instead of normal values*/
   JointHistogram( ArrayGrid<double>* pGrid1, int xTop1, int yTop1, int xBottom1, int yBottom1,
                   ArrayGrid<double>* pGrid2, int xTop2, int yTop2, int xBottom2, int yBottom2,
                   bool useAbsoluteValues=false );

   /** \brief constructor
     * Initializes and builds conditional histogram based on the two input grids
     * \param pGrid1 first input grid
     * \param pGrid2 second  input grid
     * \param useAbsoluteValues flag to use absolute values instead of normal values*/
   JointHistogram( ArrayGrid<double>* pGrid1, ArrayGrid<double>* pGrid2, bool useAbsoluteValues=false );
   
   /** \brief destructor*/
   ~JointHistogram();
   
   /** \brief writes current histogram to text file*/
   bool Write( std::string fileName);
   
   /** \brief Gets nr of bins on the horizontal axis in the histogram*/
   int GetNrOfHorizontalBins();
   
   /** \brief Gets nr of bins on the vertical axis in the histogram*/
   int GetNrOfVerticalBins();

   int GetBinValue( int bandNr, int binX, int binY );
   double GetNormalizedBinValue( int bandNr, int binX, int binY );

   FloatHistogram* GetMarginalPDF1();
   FloatHistogram* GetMarginalPDF2();
   
   /** \brief visualizes the current conditional histogram as an image*/
   Image* VisualizeAsImage( );
   void ExportText(std::string fileName);

private:

   /** \brief Increases the value in the given grid for the given bin numbers by one
     * \param pGrid grid to add one to at location (x, y)
     * \param x bin nr on the horizontal axis 
     * \param y bin nr on the vertical axis */
   void AddOne( ArrayGrid<int>* pGrid, int x, int y);
   
   /** \brief Gets the value in the given band for the given bin numbers 
     * \param band nr of the band
     * \param x bin nr on the horizontal axis 
     * \param y bin nr on the vertical axis */
   int GetValue(int band, int x, int y);
   
   /** \brief builds a conditional histogram between the two given grids
     * \param pGrid1 first grid as input
     * \param pGrid2 second grid as input
     * \param absoluteValue flag whether to use the input values as they are or their absolute values*/
   void BuildJointHistogram( ArrayGrid<double>* pGrid1, ArrayGrid<double>* pGrid2, bool absoluteValue=false );
   
   std::vector< ArrayGrid<int>* > mvpData;  ///< the actual histogram data
   std::vector< ArrayGrid<double>* > mvpDataNormalized;  ///< the actual histogram data

   int mRoiTopX1;
   int mRoiTopY1;
   int mRoiTopX2;
   int mRoiTopY2;
   int mRoiBottomX1;
   int mRoiBottomY1;
   int mRoiBottomX2;
   int mRoiBottomY2;

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
