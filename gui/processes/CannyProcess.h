
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

#ifndef STIRAGUI_PROCESSES_CANNYPROCESS_H
#define STIRAGUI_PROCESSES_CANNYPROCESS_H

#include "Process.h"

#include "../src/ImageWindow.h"

class CannyProcess : public Process
{
    Q_OBJECT

public:
   /** \brief constructor
     * \param pImage input image */
   CannyProcess( stira::image::Image* pImage );
   
   /** \brief destructor */
   virtual ~CannyProcess();
   
   double GetUpperThreshold();
   void SetUpperThreshold( double upperThreshold );
   
   double GetLowerThreshold();
   void SetLowerThreshold( double lowerThreshold );
   
   double GetSigmaSmoothing();
   void SetSigmaSmoothing( double sigma );
   
   void run();

private:
   
   double mUpperThreshold;
   double mLowerThreshold;
   double mSigmaSmoothing;
};

#endif
