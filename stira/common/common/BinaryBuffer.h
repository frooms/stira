#ifndef BINARYBUFFER_H
#define BINARYBUFFER_H

#include <string>
//#include <cstdint>

const unsigned long int cCharSize   = sizeof(unsigned char);
const unsigned long int cShortSize  = sizeof(unsigned short);
const unsigned long int cLongSize   = sizeof(unsigned long);
const unsigned long int cFloatSize  = sizeof(float);
const unsigned long int cDoubleSize = sizeof(double);

class BinaryBuffer
{
public:
    BinaryBuffer();
    ~BinaryBuffer();

    // 1. READ DIRECTLY FROM FILE STREAM
    /////////////////////////////////////

    /** \brief Reads direectly from a file */
    bool ReadDirectlyFromFile(std::string filename, unsigned int seekPosition, unsigned int readLength );

    // 2. READ FILE IN MEMORY BUFFER NAD READ FROM IT
    //////////////////////////////////////////////////

    /** \brief Reads a complete file in memory */
    bool ReadCompleteFileInMemory(std::string filename);

    /** \brief Gets the number of bytes of the file that has been read in memory */
    unsigned long int GetFileSize();

    /** \brief gets the number of bytes from the start of the buffer to the current pointer position */
    unsigned long int GetCurrentIndex();

    /** \brief sets the pointer at "bufferPos" bytes from the start of the buffer */
    void SetPtr(unsigned long int bufferPos);

    /** \brief moves the current buffer pointer by "deltaIndex" bytes */
    void MovePtr(int deltaIndex);

    /** \brief sets the pointer at the start of the buffer */
    void SetPtrToStart();

    /** \brief sets the pointer at the end of the buffer */
    void SetPtrToEnd();

    /** \brief Gets a character from the current buffer position, which increases sizeof(char) after reading */
    unsigned char ReadChar( );

    /** \brief Gets a double from the current buffer position, which increases sizeof(double) after reading */
    double ReadDouble( );

    /** \brief Gets a float from the current buffer position, which increases sizeof(float) after reading */
    double ReadFloat();

    /** \brief Gets an unsigned short integer from the current buffer position, which increases sizeof(short int) after reading */
    unsigned short ReadUnsignedShort();

    /** \brief Gets an unsigned short integer from the current buffer position, which increases sizeof(short int) after reading */
    signed short ReadSignedShort();

    /** \brief Gets an unsigned long integer from the current buffer position, which increases sizeof(long int) after reading */
    unsigned long ReadUnsignedLong();

    /** \brief Gets an unsigned long integer from the current buffer position, which increases sizeof(long int) after reading */
    signed long ReadSignedLong();

    /** \brief Gets a part of the buffer from a given offset with a certain buffer length; position is first byte behind this buffer length after reading
        \param pDestinationBuffer pointer to buffer to write into
        \param offset start position in buffer to start writing from
        \param nrBytes number of bytes to write in pDestinationBuffer, starting from position offset in source buffer*/
    void CopyBufferPart(void* pDestinationBuffer, int offset, int nrBytes);

    /** \brief prints a series of characters from the buffer starting from startPos with length length as characters to stdout */
    void PrintBufferChars(unsigned int startPos, int length);

    /** \brief writes a simple series of floats in a binary file for test purposes */
    bool WriteFile(std::string fileName, unsigned int fileLength);

private:
    char * m_pBufferStart;	///< pointer to beginning of memory block containing the file data
    char * m_pBufferNow;	///< current position of pointer in the memory block containing the file data
    unsigned long int mBufferSize;  ///< size of the memory buffer
};

#endif // BINARYBUFFER_H
