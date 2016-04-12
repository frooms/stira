
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

#ifndef STIRAGUI_PROCESSES_REGISTERIMAGESPROCESS_H
#define STIRAGUI_PROCESSES_REGISTERIMAGESPROCESS_H

#include "Process.h"

#include "../definitions/StiraDefinitions.h"

class RegisterImagesProcess : public Process
{
    Q_OBJECT

public:
   RegisterImagesProcess( stira::image::Image* pImageMaster, stira::image::Image* pImageSlave );
   ~RegisterImagesProcess();
   virtual void run();
private:
   stira::image::Image* mpImageMaster;
   stira::image::Image* mpImageSlave;
};

#endif
