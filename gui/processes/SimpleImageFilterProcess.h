
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

#ifndef STIRAGUI_PROCESSES_SIMPELIMAGEFILTERPROCESS_H
#define STIRAGUI_PROCESSES_SIMPLEIMAGEFILTERPROCESS_H

#include "Process.h"

#include "../../stira/filter/filter/SeparableFilter.h"

class SimpleImageFilterProcess : public Process
{
    Q_OBJECT

public:

   /** \brief constructor
     * \param pImWindow image window to extract input from*/
   SimpleImageFilterProcess( stira::imagedata::Image* pImage );
   ~SimpleImageFilterProcess();
   
   void SetFilterType( StiraDefinitions::SimpleFilterType myType );
   
   StiraDefinitions::SimpleFilterType GetFilterType();
   
   void SetFilterWidth(int width);
   int GetFilterWidth();
   
   void SetSigma( double sigma );
   double GetSigma();
   
   void SetAngle( double angle );
   double GetAngle();
   
   void SetExtensionType( stira::imagedata::GridExtender<double>::ExtensionType myType );
   stira::imagedata::GridExtender<double>::ExtensionType GetExtensionType();
   
   void run();
   
private:
   StiraDefinitions::SimpleFilterType mType;
   int mFilterWidth; ///< the size of the local window (like for local mean, median, ...)
   double mSigma;  ///< width of the filter function (like sigma of a gaussian)
   double mAngle;

   stira::imagedata::GridExtender<double>::ExtensionType mExtensionType;
};
#endif
