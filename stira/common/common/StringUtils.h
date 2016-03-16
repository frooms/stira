
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

#ifndef STIRA_COMMON_STRINGUTILS_H
#define STIRA_COMMON_STRINGUTILS_H

#include <string>
#include <vector>

namespace stira {

namespace common {

/** \brief A class with some handy functions to manipulate STL strings. */
class StringUtils{
public:

   /** \brief Constructor.*/
   StringUtils();

   /** \brief Constructor.*/
   ~StringUtils();

   /** \brief converts integer to std::string
    *  \param i integer to convert to std::string */
   static std::string ConvertIntegerToString( int i );

   /** \brief converts float to std::string
    *  \param f float to convert to std::string */
   static std::string ConvertFloatToString( float f );

   /** \brief converts double to std::string
    *  \param d double to convert to std::string */
   static std::string ConvertDoubleToString( double d );

   /** \brief converts boolean to std::string
    *  \param b boolean to convert to std::string */
   static std::string ConvertBoolToString( bool b );

   /** \brief converts std::string to boolean
    *  \param inputString std::string to convert to boolean */
   static bool ConvertStringToBoolean( std::string inputString );

   /** \brief converts std::string to integer
    *  \param inputString std::string to convert to integer */
   static int ConvertStringToInt( std::string inputString );

   /** \brief converts std::string to float
    *  \param inputString std::string to convert to float */
   static float ConvertStringToFloat( std::string inputString );

   /** \brief converts std::string to double
    *  \param inputString std::string to convert to double */
   static double ConvertStringToDouble( std::string inputString );

   /** \brief extracts file name from a path string, thus removing all until the last slash
    *  Inherently uses position of last slash, so works only for Unix path names
    *  \param inputString input string from which to extract file name */
   static std::string ExtractFileName( std::string inputString );

   /** \brief extracts the root filename for a file, so removes path and extension
     * e.g., if a certain path to a file is "/home/UserName/Filedir/SomeFileName_XXXX.txt",
     * this function extracts "SomeFileName_XXXX"
     * \param inputString string containing full path to file, like in example above  */
   static std::string ExtractFileNameRoot( std::string inputString );

   /** \brief gets the index from a string
     * We often encounter file names of type "SomeName_XXXX.pnm" where "XXXX" represents a number.
     * This function extracts that number from the file name
     * \param inputString string containing a file name with a number before the extension, like in the example above*/
   static long int GetIndexFromFileName( std::string inputString, bool useUnderscoreAsSeparator=true );

   static std::string FindFileNameInListFromIndex( int myIndex, std::vector< std::string > fileList );

   /** \brief finds the position of the first dot in a string
     * \param inputString string containing a dot somewhere
     * \return the position of the first dot in the string; -1 if no dot was found */
   static int FindFirstDot( std::string inputString );

   /** \brief finds the position of the last slash in a string that represents a path
     * Uses macro __WIN32__ (sometimes it can be _WIN32, __CYGWIN32__, or _MSC_VER) to determine if slash (unix) or backslash (windows) is to be used.
     * \param inputString string that represents a path, containing slashes or backslashes
     * \return the position of the last slash in the string; -1 if no dot was found */
   static int FindLastSlash( std::string inputString );

   static int FindLastUnderscore( std::string inputString );

   static int FindLastMinus( std::string inputString );

   /** \brief extracts the extension from a filename for a file
     * e.g., if a certain path to a file is "/home/UserName/Filedir/SomeFileName.txt",
     * this function extracts if includeDot true ".txt" and "txt" otherwise
     * \param inputString string containing full path to file, like in example above
     * \param includeDot flag if the dot should be included in the file extension */
   static std::string ExtractFileExtension( std::string inputString, bool includeDot=true );

   /** \brief extracts the prefix filename for a file, so removes path, extension and file index
     * e.g., if a certain path to a file is "/home/UserName/Filedir/SomeFileName_XXXX.txt",
     * this function extracts "SomeFileName"
     * \param inputString string containing full path to file, like in example above  */
   static std::string ExtractFilePrefix( std::string inputString, bool useUnderscoreAsSeparator=true );

   /** \brief extracts the path for a file
     * e.g., if a certain path to a file is "/home/UserName/Filedir/SomeFileName.txt",
     * this function extracts "/home/UserName/Filedir"
     * \param inputString string containing full path to file, like in example above */
   static std::string ExtractPathOfFileName( std::string inputString );

   /** \brief extracts the path for a file
     * e.g., if a certain path to a file is "/home/UserName/Filedir/SomeFileName.txt",
     * this function extracts "SomeFileName.txt"
     * \param inputString string containing full path to file, like in example above */
   static std::string ExtractFileNameFromPathPlusFileName( std::string inputString );


   static std::string GoOneLevelUpInPathName( std::string inputString );


   /** \brief synthesizes a file name from a prefix, a counter and an extension
     * \param path path of the file name
     * \param preFix prefix of the file name
     * \param indexNr counter for file name
     * \param extension extension of file name
     * \return a string with the synthesized file name*/
   static std::string ConstructPathAndFileName( std::string path, std::string preFix, int indexNr, std::string extension );

   /** \brief composes a file name from a prefix, two counters and an extension
     * \param path path of the file name
     * \param preFix prefix of the file name
     * \param indexNr1 first counter for file name
     * \param indexNr2 second counter for file name
     * \param extension extension of file name
     * \return a string with the synthesized file name*/
   static std::string ConstructPathAndFileName( std::string path, std::string preFix, int indexNr1, int indexNr2, std::string extension );

   //http://www.cplusplus.com/reference/string/string/compare/
   //http://www.cplusplus.com/reference/clibrary/cstdlib/strtol/
   static bool IsDigit( std::string s, long int& myDigit );

   /** \brief Splits a delimited string in integers
     * http://www.blog.highub.com/c-plus-plus/c-parse-split-delimited-string/
     * http://www.cplusplus.com/forum/general/13135/ */
   static void SplitStringInIntegers( const std::string& s, char c, std::vector<int>& v );

   /** \brief creates a string based on current time to build experiment output folders or files using this string */
   static std::string GetCurrentTimeAsStringID();

};

}
}

#endif
