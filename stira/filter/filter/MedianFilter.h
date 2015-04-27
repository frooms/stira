#ifndef STIRA_FILTER__MEDIANFILTER_H
#define STIRA_FILTER__MEDIANFILTER_H

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

#include <stdint.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "../../image/datastructures/Image.h"

namespace stira{
namespace filter{

enum MedianType{ CLASSIC_MEDIAN, HYBRID_MEDIAN };

/** \brief class for classical and hybrid median filter*/
class MedianFilter
{
public:
   /** \brief constructor*/
   MedianFilter();

    /** \brief destructor*/
   ~MedianFilter();

   /** \brief runs classical median filter
     * \param pImageIn Image to filter
     * \param size half of (window size-1); e.g., for 5x5 window, size = (5-1)/2 = 2*/
   static image::ArrayGrid<double>* RunMedian( image::ArrayGrid<double>* pGridIn, int size);

   /** \brief runs classical median filter
     * \param pImageIn Image to filter
     * \param size half of (window size-1); e.g., for 5x5 window, size = (5-1)/2 = 2*/
   static image::ArrayGrid<int>* RunMedian( image::ArrayGrid<int>* pGridIn, int size);

   /** \brief runs hybrid median filter
     * Reference: http://www.biomecardio.com/matlab/hmf.html
     * \param pImageIn Image to filter
     * \param size half of (window size-1); e.g., for 3x3 window, size = (3-1)/2 = 1*/
   static image::ArrayGrid<double>* RunHybridMedian( image::ArrayGrid<double>* pGridIn, int size);

   /** \brief runs classical median filter
     * \param pImageIn Image to filter
     * \param size half of (window size-1); e.g., for 5x5 window, size = (5-1)/2 = 2*/
   static image::Image* RunMedian( image::Image* pImageIn, int size);

   /** \brief runs hybrid median filter
     * Reference: http://www.biomecardio.com/matlab/hmf.html
     * \param pImageIn Image to filter
     * \param size half of (window size-1); e.g., for 3x3 window, size = (3-1)/2 = 1*/
   static image::Image* RunHybridMedian( image::Image* pImageIn, int size);
};

}
}

#endif // MEDIANFILTER_H
