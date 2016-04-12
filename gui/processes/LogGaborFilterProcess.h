
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

#ifndef STIRAGUI_PROCESSES_LOGGABORFILTERPROCESS_H
#define STIRAGUI_PROCESSES_LOGGABORFILTERPROCESS_H

#include "Process.h"

#include "../src/ImageWindow.h"

#include "../definitions/StiraDefinitions.h"

class LogGaborFilterProcess : public Process
{
    Q_OBJECT

public:
   /** \brief constructor
     * \param pImage input image */
   LogGaborFilterProcess( stira::image::Image* pImage );
   virtual ~LogGaborFilterProcess();
   
   double GetCenterFrequency();
   void SetCenterFrequency( double centerFrequency );
   
   double GetRadialWidth();
   void SetRadialWidth( double radialWidth );
   
   double GetCenterAngle();
   void SetCenterAngle( double centerAngle );
   
   double GetAngleSpread();
   void SetAngleSpread( double angleSpread );
   
   void SetCreateRealResponse( bool createOut );
   void SetCreateImagResponse( bool createOut );
   void SetCreateMagnitude( bool createOut );
   void SetCreateTransferResponse( bool createOut );

   void run();
   
private:
   double mCenterFrequency;
   double mRadialWidth;
   double mCenterAngle;
   double mAngleSpread;
   bool mCreateRealResponse;
   bool mCreateImagResponse;
   bool mCreateMagnitude;
   bool mCreateTransferResponse;
};

#endif
