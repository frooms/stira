
/***************************************************************************************
 *   Copyright (C) 2011 by Filip Rooms                                                 *
 *                                                                                     *
 *  Terms and conditions for using this software in any form are provided in the       *
 *  file COPYING, which can be found in the root directory of this project.            *
 *                                                                                     *
 *   Contact data: filip.rooms@gmail.com                                               *
 *                 http://www.filiprooms.be/                                           *
 *                                                                                     *
 ***************************************************************************************/

#ifndef STIRA_COMMON_FILEACCESS_H
#define STIRA_COMMON_FILEACCESS_H

#include <string>
#include <vector>
#include <zip.h>

namespace stira {
namespace common {

/** \brief class to facilitate file access in directories. */
class FileAccess
{
public:
   /** constructor */
   FileAccess( );

   /** destructor */
   ~FileAccess( );


   /** \brief Gets a list of subdirectories with given prefix in a directory
     * References: http://www.linuxquestions.org/questions/programming-9/c-list-files-in-directory-379323/
     *             http://www.gnu.org/software/libc/manual/html_node/File-System-Interface.html#File-System-Interface
     *             http://en.wikipedia.org/wiki/Dirent.h
     *             http://www.gnu.org/software/libc/manual/html_node/Simple-Directory-Lister.html#Simple-Directory-Lister
     * \param pathToAccess the path to the directory containing the subdirectories
     * \param prefix the wanted subdirectory prefix
     * \param extension the wanted file extension
     * \return a vector of file names found in the given directory with the given file extension */
   static std::vector< std::string > ListFilesInSubFoldersInFolder( std::string pathToAccess, std::string prefix, std::string extension, bool separatorIsUnderscore=false );

   /** \brief Gets a list of files in a directory with given extension
     * References: http://www.linuxquestions.org/questions/programming-9/c-list-files-in-directory-379323/
     *             http://www.gnu.org/software/libc/manual/html_node/File-System-Interface.html#File-System-Interface
     *             http://en.wikipedia.org/wiki/Dirent.h
     *             http://www.gnu.org/software/libc/manual/html_node/Simple-Directory-Lister.html#Simple-Directory-Lister
     * \param pathToAccess the path to the directory containing the files
     * \param extension the wanted file extension
     * \param startNrImage to restrict which files are taken, we can set a certain start number; if set to -1, the smallest possible file index will be taken
     * \param maxNrFiles to restrict which files are taken, we can set a certain maximum number of files; if set to -1, all available files will be taken
     * \return a vector of file names found in the given directory with the given file extension */
   static std::vector< std::string > ListFilesOfType( std::string pathToAccess, std::string prefix, std::string extension, bool usePrefix, bool separatorIsUnderscore=false, int startNrImage=-1, int maxNrFiles=-1 );

   /** \brief finds file name from that contains a given index number in a list of file names
     * \param fileList the list of files in which to search;
     * \param frameNr the frame number for which to find the full file name */
   static std::string FindFileName( std::vector< std::string > fileList, int frameNr );

   /** \brief checks if a given directory name exists
     * \param dirName the directory name to check if it exists */
   static bool CheckIfDirectoryExists( std::string dirName );

   /** \brief creates a directory with given name
     * Reference: http://www.go4expert.com/forums/showthread.php?t=9031 (create a directory)
     * \param dirName the directory name to create */
   static bool CreateNewDirectory( std::string dirName );

   /** \brief creates a directory with given name
     * Reference: http://www.dreamincode.net/forums/topic/200281-creating-a-symbolic-link-from-c-program/
     * \param sourcePathAndFileName the source file and its path
     * \param linkPathAndFileName the path and name for the symbolic link */
   static bool CreateSymbolicLink2File( std::string sourcePathAndFileName, std::string linkPathAndFileName );
};

}
}

#endif // FILEACCESS_H
