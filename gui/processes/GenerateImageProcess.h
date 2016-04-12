
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

#ifndef STIRAGUI_PROCESSES_GENERATEIMAGEPROCESS_H
#define STIRAGUI_PROCESSES_GENERATEIMAGEPROCESS_H

#include "Process.h"

#include "../src/ImageWindow.h"

class GenerateImageDialog;

class GenerateImageProcess : public Process
{
    Q_OBJECT

public:

   /** \brief constructor
     * \param pImWindow image window to extract input from*/
   GenerateImageProcess( );
   virtual ~GenerateImageProcess();
   
   int GetWidth();
   void SetWidth( int);
   
   int GetHeight();
   void SetHeight( int);
   
   double GetFrequency();
   void SetFrequency( double frequency );
   
   double GetMaxSigma();
   void SetMaxSigma( double maxSigma );
   
   enum StiraDefinitions::SyntheticImageType GetType();
   void SetType( enum StiraDefinitions::SyntheticImageType);
   
   void run();
   
private:

   int mWidth;
   int mHeight;
   double mFrequency;
   double mMaxSigma;
   enum StiraDefinitions::SyntheticImageType mImageType;
};

#endif
