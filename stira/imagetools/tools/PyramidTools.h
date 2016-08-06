
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

#ifndef STIRA_IMAGE_TOOLS_PYRAMIDTOOLS_H
#define STIRA_IMAGE_TOOLS_PYRAMIDTOOLS_H

#include "../../imagedata/datastructures/Image.h"
#include "../../imagedata/datastructures/Pyramid.h"

namespace stira {
namespace image {

/** \brief Class with operations on Pyramid objects */
class PyramidTools
{
public:
   /** \brief constructor */
   PyramidTools();
   
   /** \brief destructor */
   ~PyramidTools();
   
   /** \brief Creates a single image representing all bands of the pyramid
     * \param pPyramid the pyramid to represent */
   static Image* VisualizeRealPyramid( Pyramid< double>* pPyramid );

   static Image* VisualizeClassicWavelet( Pyramid< double >* pPyramid );

private:
   /** \brief Determines the width for the single image in which to draw all bands of the pyramid
     * \param pPyramid the pyramid to represent */
   static int DetermineWidth( Pyramid< double >* pPyramid );

   /** \brief Determines the height for the single image in which to draw all bands of the pyramid
     * \param pPyramid the pyramid to represent */
   static int DetermineHeight( Pyramid< double >* pPyramid );
   
};

}
}

#endif

