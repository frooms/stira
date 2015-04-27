
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

#ifndef STIRA_FILTER_SEPARABLEFILTER_H
#define STIRA_FILTER_SEPARABLEFILTER_H

#include <stdint.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "../../image/datastructures/Image.h"
#include "../../image/tools/GridExtender.h"

namespace stira {
namespace filter {

/** \brief Filters an image using a separable filter kernel */
class SeparableFilter
{
public:

   /** \brief Constructor. */
   SeparableFilter();

   /** \brief Destructor. */
   ~SeparableFilter();

   /** \brief Applies row by row filtering on a single grid with 1 1D filter kernel
     * \param pInput the input grid
     * \param pOutput the output grid (allocated but not necessarely initialized)
     * \param filtx the 1D filter taps
     * \param filterLengthX length of the filter
     * \param myType identifies how borders should be extended (mirrored, tiled, padded with zeros)
     *
     * If the filter length is 1, the output grid is just a copy of the input grid*/
   static bool RunRow( image::ArrayGrid<double>* pInput, image::ArrayGrid<double>* pOutput, double *filtx, int filterLengthX, image::GridExtender<double>::ExtensionType myType = image::GridExtender<double>::EXTEND_MIRROR );

   /** \brief Applies column by column filtering on a single grid with 1 1D filter kernel
     * \param pInput the input grid
     * \param pOutput the output grid (allocated but not necessarely initialized)
     * \param filty the 1D filter taps
     * \param filterLengthY length of the filter
     * \param myType identifies how borders should be extended (mirrored, tiled, padded with zeros)
     *
     * If the filter length is 1, the output grid is just a copy of the input grid*/
   static bool RunColumn( image::ArrayGrid<double>* pInputBand, image::ArrayGrid<double>* pOutputBand, double *filty, int filterLengthY, image::GridExtender<double>::ExtensionType myType = image::GridExtender<double>::EXTEND_MIRROR  );

   /** \brief Applies filtering on a single grid, first row by row and then column by column
     * \param pInput the input grid
     * \param filterTapX the 1D filter taps for the x direction
     * \param filterTapY the 1D filter taps for the y direction
     * \param filterLengthX length of the filter for the x direction
     * \param filterLengthY length of the filter for the y direction
     * \param myType identifies how borders should be extended (mirror, tile, black)
     *
     * mallocs memory and returns response of input image filtered with filterTapX on the rows and filterTapY on the columns */
   static image::ArrayGrid<double>* RunRowColumn( image::ArrayGrid<double>* pInput, double *filterTapX, double *filterTapY, int filterLengthX, int filterLengthY, image::GridExtender<double>::ExtensionType myType = image::GridExtender<double>::EXTEND_MIRROR );

   /** \brief Applies filtering on a single grid, first column by column and then row by row
     * \param pInput the input grid
     * \param filterTapX the 1D filter taps for the x direction
     * \param filterTapY the 1D filter taps for the y direction
     * \param filterLengthX length of the filter for the x direction
     * \param filterLengthY length of the filter for the y direction
     * \param myType identifies how borders should be extended (mirror, tile, black)
     *
     * mallocs memory and returns response of input image filtered with filterTapX on the rows and filterTapY on the columns  */
   static image::ArrayGrid<double>* RunColumnRow( image::ArrayGrid<double>* pInput, double *filterTapX, double *filterTapY, int filterLengthX, int filterLengthY, image::GridExtender<double>::ExtensionType myType = image::GridExtender<double>::EXTEND_MIRROR );

   /** \brief Applies filtering on a multiband image, first row by row and then column by column
     * \param pInput the input image
     * \param filterTapX the 1D filter taps for the x direction
     * \param filterTapY the 1D filter taps for the y direction
     * \param filterLengthX length of the filter for the x direction
     * \param filterLengthY length of the filter for the y direction
     * \param myType identifies how borders should be extended (mirror, tile, black)
     *
     * mallocs memory and returns response of input image filtered with filterTapX on the rows and filterTapY on the columns
     */
   static image::Image* RunRowColumn( image::Image* pInput, double *filterTapX, double *filterTapY, int filterLengthX, int filterLengthY, image::GridExtender<double>::ExtensionType myType = image::GridExtender<double>::EXTEND_MIRROR );

   /** \brief Applies filtering on a multiband image, first column by column and then row by row
     * \param pInput the input image
     * \param filterTapX the 1D filter taps for the x direction
     * \param filterTapY the 1D filter taps for the y direction
     * \param filterLengthX length of the filter for the x direction
     * \param filterLengthY length of the filter for the y direction
     * \param myType identifies how borders should be extended (mirror, tile, black)
     *
     * mallocs memory and returns response of input image filtered with filterTapX on the rows and filterTapY on the columns
     */
   static image::Image* RunColumnRow( image::Image* pInput, double *filterTapX, double *filterTapY, int filterLengthX, int filterLengthY, image::GridExtender<double>::ExtensionType myType = image::GridExtender<double>::EXTEND_MIRROR );

   /** \brief Filters a one dimensional data set (a single row or column)
     * \param pInputArray1D   1D input array to filter (a row or a column of the image)
     * \param pFilterKernel   the 1D filter kernel
     * \param pOutputArray1D   output array after filtering
     * \param inputLength   length of the 1D array
     * \param filterLength   length of the filter
     * \param myType identifies how borders should be extended (mirror, tile, black)
     */
   static void BasicFilter1D (double *pInputArray1D, double *pFilterKernel, double *pOutputArray1D, int inputLength, int filterLength, image::GridExtender<double>::ExtensionType myType=image::GridExtender<double>::EXTEND_MIRROR );

private:
   /** \brief Generates an extended 1D input array
     * \param pInputArray1D  original 1D input array
     * \param inputLength    length of the original input array
     * \param myType         identifier how array should be extended at the borders (mirror, tile, black)
     */
   static double* GenerateExtendedInput(double* pInputArray1D, int inputLength, image::GridExtender<double>::ExtensionType myType = image::GridExtender<double>::EXTEND_MIRROR );

};
}
}
#endif
