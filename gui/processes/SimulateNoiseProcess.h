
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

#ifndef STIRAGUI_PROCESSES_SIMULATENOISEPROCESS_H
#define STIRAGUI_PROCESSES_SIMULATENOISEPROCESS_H

#include "Process.h"

class SimulateNoiseProcess : public Process
{
    Q_OBJECT

public:

   /** \brief constructor
     * \param pImWindow input image window for processing */
   SimulateNoiseProcess( stira::imagedata::Image* pImage );
   ~SimulateNoiseProcess();
   
   double GetNoiseLevel();
   void SetNoiseLevel(double f);

   StiraDefinitions::NoiseType GetNoiseType();
   void SetNoiseType( StiraDefinitions::NoiseType myType );
   
   bool GetUseColoredNoise();
   void SetUseColoredNoise( bool flag );
   
   void run();
private:
   bool mUseColoredNoise;
   double mNoiseLevel;
   StiraDefinitions::NoiseType  mNoiseType;
};

#endif
