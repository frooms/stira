
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

#ifndef STIRA_IMAGE_TOOLS_GRIDCONVERTER_H
#define STIRA_IMAGE_TOOLS_GRIDCONVERTER_H

#include "../../imagedata/datastructures/ArrayGrid.h"

namespace stira {
namespace image {

/** \brief class to convert a grid of one data type to another*/
class GridConverter
{
public:
   /** \brief constructor */
   GridConverter();

   /** \brief converts a grid of booleans (0 or 1) to a grid of integers (0 or 255)
     * \param pGrid input grid of booleans */
   static ArrayGrid<int>* ConvertToInt( ArrayGrid<bool>* pGrid );

   /** \brief converts a grid of doubles to a grid of integers
     * \param pGrid input grid of doubles */
   static ArrayGrid<int>* ConvertToInt( ArrayGrid<double>* pGrid );

   /** \brief converts a grid of booleans (0 or 1) to a grid of integers (0 or factor)
     * \param pGrid input grid of booleans
     * \param factor number to scale the boolean values with */
   static ArrayGrid<double>* ConvertToDouble( ArrayGrid<bool>* pGrid, double factor=1.0 );

   /** \brief converts a grid of integers to a grid of doubles
     * \param pGrid input grid of integers */
   static ArrayGrid<double>* ConvertToDouble( ArrayGrid<int>* pGrid );
};
}
}

#endif // GRIDCONVERTER_H
