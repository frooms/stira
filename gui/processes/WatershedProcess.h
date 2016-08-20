
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

#ifndef STIRAGUI_PROCESSES_WATERSHEDPROCESS_H
#define STIRAGUI_PROCESSES_WATERSHEDPROCESS_H

#include "Process.h"

class WatershedProcess : public Process
{
    Q_OBJECT

public:
   /** \brief constructor
     * \param pImage input image */
   WatershedProcess( stira::imagedata::Image* pImage );
   
   virtual ~WatershedProcess();
   
   int GetMaximalMinimumLevel();
   void SetMaximalMinimumLevel( int maxLevel );
   
   int GetEqualityPrecision();
   void SetEqualityPrecision( int precision );
   
   bool GetUseGradientImage();
   void SetUseGradientImage(bool flag);
   
   void run();

private:
   int mMaximalMinimumLevel;
   int mEqualityPrecision;
   bool mUseGradientImage;
};

#endif
