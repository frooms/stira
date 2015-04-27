
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

#ifndef STIRA_FILTER__KUWAHARAFILTER_H
#define STIRA_FILTER__KUWAHARAFILTER_H

#include "../../image/datastructures/Image.h"

namespace stira{
namespace filter{

/** \brief computes Kuwahara filtered image
  *
  * The filtering window is divided in four subwindows. For each subwindow, mean and varince are computed.
  * The central pixel value is then replaced by the mean of the window with the smallest variance.
  *
  * Reference: http://www.ph.tn.tudelft.nl/Courses/FIP/noframes/fip-Smoothin.html
  */
class KuwaharaFilter
{
public:
   /** \brief constructor*/
   KuwaharaFilter();
   
   /** \brief destructor*/
   ~KuwaharaFilter();
   
   /** \brief applies Kuwahara filter to image*/
   static image::Image* Run(image::Image* pImageIn, int windowSize=5);
   
   /** \brief gets the index at which position the smallest member of the given array is located
     * \param pArray the array with values
     * \param size size of the array */
   static int GetSmallestIndex(double* pArray, int size );
};

}
}

#endif
