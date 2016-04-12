
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

#ifndef STIRAGUI_PROCESSES_WIENERDECONVOLVEPROCESS_H
#define STIRAGUI_PROCESSES_WIENERDECONVOLVEPROCESS_H

#include "Process.h"

class WienerDeconvolveProcess : public Process
{
    Q_OBJECT

public:
   /** \brief constructor
     * \param pImWindow image window to extract input from*/
   WienerDeconvolveProcess( stira::image::Image* pImage );
   virtual ~WienerDeconvolveProcess();
   
   double GetNoiseLevel();
   void SetNoiseLevel( double noiseLevel );
   
   double GetBlurLevel();
   void SetBlurLevel( double blurLevel );
   
   void run();
   
private:
   double mNoiseLevel;
   double mBlurLevel;
};

#endif
