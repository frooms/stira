#include "BinaryBuffer.h"

#include <fstream>
#include <iostream>
#include <cstring>

BinaryBuffer::BinaryBuffer()
{
    m_pBufferStart = 0;
    m_pBufferNow = 0;
    mBufferSize = 0;
}

//-----------------------------------------------------------------------

BinaryBuffer::~BinaryBuffer()
{
    delete[]m_pBufferStart;
}

//-----------------------------------------------------------------------

unsigned long int BinaryBuffer::GetFileSize()
{
    return mBufferSize;
}

//-----------------------------------------------------------------------

unsigned long int BinaryBuffer::GetCurrentIndex()
{
    return (unsigned long int)(m_pBufferNow - m_pBufferStart);
}

//-----------------------------------------------------------------------

void BinaryBuffer::SetPtr(unsigned long int bufferPos)
{
    m_pBufferNow = m_pBufferStart + bufferPos;
}

//-----------------------------------------------------------------------

void BinaryBuffer::MovePtr(int deltaIndex)
{
    m_pBufferNow += deltaIndex;
}

//-----------------------------------------------------------------------

void BinaryBuffer::SetPtrToStart()
{
    m_pBufferNow = m_pBufferStart;
}

//-----------------------------------------------------------------------

void BinaryBuffer::SetPtrToEnd()
{
    m_pBufferNow = m_pBufferStart + mBufferSize;
}

//-----------------------------------------------------------------------

unsigned char BinaryBuffer::ReadChar( )
{
    unsigned char a;
    std::memcpy(&a, m_pBufferNow, cCharSize);
    m_pBufferNow += cCharSize;
    return a;
}

//-----------------------------------------------------------------------

double BinaryBuffer::ReadDouble( )
{
    double a;
    std::memcpy(&a, m_pBufferNow, cDoubleSize);
    m_pBufferNow += cDoubleSize;
    return a;
}

//-----------------------------------------------------------------------

double BinaryBuffer::ReadFloat()
{
    float a;
    memcpy(&a, m_pBufferNow, cFloatSize);
    m_pBufferNow += cFloatSize;
    return a;
}

//-----------------------------------------------------------------------

unsigned short BinaryBuffer::ReadUnsignedShort()
{
    unsigned short a;
    memcpy(&a, m_pBufferNow, cShortSize);
    m_pBufferNow += cShortSize;
    return a;
}

//-----------------------------------------------------------------------

signed short BinaryBuffer::ReadSignedShort()
{
    signed short a;
    memcpy(&a, m_pBufferNow, cShortSize);
    m_pBufferNow += cShortSize;
    return a;
}

//-----------------------------------------------------------------------

unsigned long BinaryBuffer::ReadUnsignedLong()
{
    unsigned long a;
    memcpy(&a, m_pBufferNow, cLongSize);
    m_pBufferNow += cLongSize;
    return a;
}

//-----------------------------------------------------------------------

signed long BinaryBuffer::ReadSignedLong()
{
    signed long a;
    memcpy(&a, m_pBufferNow, cLongSize);
    m_pBufferNow += cLongSize;
    return a;
}

//-----------------------------------------------------------------------

void BinaryBuffer::CopyBufferPart(void* destinationBuffer, int offset, int nrBytes)
{
    memcpy(destinationBuffer, m_pBufferNow + offset, nrBytes);
}

//-----------------------------------------------------------------------

void BinaryBuffer::PrintBufferChars(unsigned int startPos, int length)
{
    char* bufferPtr = m_pBufferStart + startPos;
    for (int i = 0; i < 3; i++)
    {
        std::cout << *(bufferPtr + i);
    }

    for (int i = 3; i < length; i++)
    {
        std::cout << (int)(*(bufferPtr + i));
    }
    std::cout << std::endl;
}

//-----------------------------------------------------------------------

bool BinaryBuffer::WriteFile(std::string fileName, unsigned int fileLength)
{
    std::ofstream myfile(fileName.c_str(), std::ios::out | std::ios::binary);

    float* pFloatArray = new float[fileLength];
    for (unsigned int i = 0; i < fileLength; i++)
    {
        pFloatArray[i] = (float)(i);
    }
    myfile.write((char*)pFloatArray, fileLength*sizeof(float));

    myfile.close();
    return true;
}

//-----------------------------------------------------------------------

bool BinaryBuffer::ReadDirectlyFromFile(std::string filename, unsigned int seekPosition, unsigned int readLength)
{
    char * array = new char[readLength]; //array to store file contents
    unsigned int position = 0; //keep track of array position where new character from file will be stored

    std::ifstream fin(filename.c_str(), std::ifstream::binary); // opening file in binary mode

    seekPosition *= cFloatSize;

    //checking whether file could be opened or not.
    if (fin.is_open())
    {
        fin.seekg(0, std::ios::end); //seeking to the end of the file
        std::streamoff fileLength = fin.tellg(); //Getting the length of file or positon of enf of file
        fin.seekg(0, std::ios::beg); //seeking to the start of the file

        if (seekPosition <= fileLength) // checking user entered position lie within file
        {
            fin.seekg(seekPosition, std::ios::beg); //seeking to the user specified position from begining of the file
            //Reading file from seek_position to end of file into array
            while (position < readLength)
            {
                fin.get(array[position]);
                position++;
            }

            float a;
            memcpy(&a, array, cFloatSize);

        }
        else //position entered by user in not with in the file range
        {
            std::cerr << "ERROR: Invalid Seek Position." << std::endl;
            return false;
        }
    }
    else //file could not be opened
    {
        std::cerr << "ERROR: File could not be opened." << std::endl;
        return false;
    }
    return true;
}

//-----------------------------------------------------------------------

bool BinaryBuffer::ReadCompleteFileInMemory(std::string filename)
{
    std::ifstream infile(filename.c_str(), std::ios_base::binary);

    if (infile)
    {
        // get length of file:
        infile.seekg(0, infile.end);
        mBufferSize = infile.tellg();   // was: length
        infile.seekg(0, infile.beg);

        // buffer contains the entire file
        m_pBufferStart = new char[mBufferSize];
        m_pBufferNow   = m_pBufferStart;

        std::cout << " \t Reading " << mBufferSize << " characters... " << std::endl;
        // read data as a block:
        infile.read(m_pBufferStart, mBufferSize);

        if (infile)
            std::cout << " \t all characters read successfully." << std::endl;
        else
            std::cout << " \t ERROR: only " << infile.gcount() << " could be read" << std::endl;
        infile.close();
    }
    else
    {
        std::cerr << "ERROR: could not open file " << filename << "for reading" << std::endl;
    }
    return true;
}
