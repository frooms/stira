
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

#ifndef STIRAGUI_PROCESSES_STEERABLEDENOISINGPROCESS_H
#define STIRAGUI_PROCESSES_STEERABLEDENOISINGPROCESS_H

#include "Process.h"

class SteerableDenoisingProcess : public Process
{
    Q_OBJECT

public:

   /** \brief constructor
     * \param pImage input image */
   SteerableDenoisingProcess( stira::image::Image* pImage );
   virtual ~SteerableDenoisingProcess();
   
   int GetNrScales(); 
   void SetNrScales(int nr);
   
   int GetNrOrientations();
   void SetNrOrientations(int nr);
   
   double GetNoiseLevel();
   void SetNoiseLevel(double nl);
   
   void run();
   
private:
   int mNrScales;
   int mNrOrientations;
   double mNoiseLevel;
};


#endif
