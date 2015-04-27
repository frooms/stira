
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

#ifndef STIRA_COMMON_TEXTFILEUTILS_H
#define STIRA_COMMON_TEXTFILEUTILS_H

#include <string>
#include <vector>
#include "Point.h"

namespace stira {
namespace common {

typedef std::vector< std::vector< std::string > > Rows;

/** \brief A class with some handy functions to manipulate ASCII text files. */
class TextFileUtils{
public:

   /** \brief Constructor.*/
   TextFileUtils();

   /** \brief Constructor.*/
   ~TextFileUtils();

   /** \brief Reads a text file where fields on a line are separated by tabs
     *  Reference http://stackoverflow.com/questions/1075712/reading-delimited-files-in-c
     * \param inFileName input text file */
   static Rows ReadTabSeparatedLineFromTextFile( std::string inFileName );

   /** \brief Reads single-word lines from a text file
     * \param inFileName file name to read from
     *
     * \return vector of strings per line */
   static std::vector< std::string > ReadLinesFromTextFile( std::string inFileName );

   /** \brief Filters a text file with numbers, keeping only valid rows
     * The first columns contain values to be filtered;
     *    only if all those values in these columns are valid, the row is kept
     * \param inFileName file name for input data
     * \param outFileName file name for output datap
     * \param pFilterValues array with the valid values:
     *     if all of the first nrColumnsToFilter have values that are also in the array, the row is kept
     * \param filterLength length of array with valid values
     * \param nrColumnsToFilter how many columns must contain values that are in pFilterValue
     * \param nrOtherColumns nr of other columns to copy when a row is valid */
   static bool FilterText( std::string inFileName, std::string outFileName, int* pFilterValues, int filterLength, int nrColumnsToFilter, int nrOtherColumns );

   /** \brief Saves the values in a vector of doubles to a text file
     * \param inVector vector with values to be written
     * \param outFileName file name for output data */
   static bool SaveVectorOfValuesToTextFile( std::vector<double> inVector, std::string outFileName );

   /** \brief Saves the values in a vector of integers to a text file
     * \param inVector vector with values to be written
     * \param outFileName file name for output data */
   static bool SaveVectorOfValuesToTextFile( std::vector<int> inVector, std::string outFileName );

   /** \brief Saves the values in a vector of doubles to a text file
     * \param inVector vector with values to be written
     * \param outFileName file name for output data */
   static bool SaveVectorOfIntensityPointsToTextFile( std::vector< common::IntensityPoint > inVector, std::string outFileName );

private:
   /** \brief checks if a cell in a table is valid
     * Help method for FilterText. It checks if the value found at a certain position is one of a list of predefined values
     * \param columnValue value to check
     * \param pFilterValues array with the valid values
     * \param filterLength length of the array with the valid values */
   static bool IsValidCell( int columnValue, int* pFilterValues, int filterLength );

   /** \brief checks if all values in a row of a table are valid
     * Help method for FilterText. It checks if all values in a table row are also found in a list of predefined values
     * \param pColumnValue array with values to check
     * \param pFilterValues array with the valid values
     * \param filterLength length of the array with the valid values */
   static bool IsValidRow( int* pColumnValues, int* pFilterValues, int filterLength, int nrColumns );
};

}
}

#endif

