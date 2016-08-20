
/***********************************************************************************
 *   Copyright (C) 2009 by Filip Rooms                                             *
 *                                                                                 *
 *  Terms and conditions for using this software in any form are provided in the   *
 *  file COPYING, which can be found in the root directory of this project.        *
 *                                                                                 *
 *   Contact data: filip.rooms@gmail.com                                           *
 *                 http://www.filiprooms.be/                                       *
 *                                                                                 *
 ***********************************************************************************/

#ifndef STIRA_IMAGE_COLOR_COLORBALANCER_H
#define STIRA_IMAGE_COLOR_COLORBALANCER_H

#include <stdint.h>
#include <iostream>
#include <vector>
#include <cmath>
#include "../../imagedata/datastructures/Image.h"

namespace stira {
namespace imagetools {

using namespace imagedata;

/** \brief  ref: http://scien.stanford.edu/class/psych221/projects/00/trek/
*/
class ColorBalancer
{
public:
   
   ColorBalancer();
   
   ~ColorBalancer();
   
   /** \brief Weighted balance from following two color balancing results 
     * \warning Generates new image, that becomes responsability of the caller to delete
     * \param weightGM weight of result of GrayWorld result (added with (1-weightGM) times Perfect Reflector result)*/
   static Image* RunBalance( Image* pImageIn, double weightGM=0.5 );
   
   /** \brief Performs Gray World color balancing
     * \warning Generates new image, that becomes responsability of the caller to delete
     * Based on the assumption that given an image with sufficient amount of color variations, the average value of the 
     * R, G, and B components of the image should average to a common gray value. Color balancing algorithms can apply 
     * this assumption by forcing its images to have a common average gray value for its R, G, and B components.*/
   static Image* RunGrayWorld( Image* pImageIn );
   
   static Image* RunGrayColorPoint(Image* pImageIn);

   /** \brief Performs Perfect Reflector color balancing 
     * \warning Generates new image, that becomes responsability of the caller to delete
     * Based on the following fact: An illuminated glossy surface or specularity reflects a highlight known as Perfect 
     * Reflector or Specular Reflection. If the surface is shiny enough, it reflects the actual color of the light source, 
     * independently of the color of the surface. Therefore, the R, G, and B components of the brightest or most reflective 
     * spot are used to scale the RGBs of all other objects in the image */
   static Image* RunPerfectReflector( Image* pImageIn );

};

}
}

#endif
