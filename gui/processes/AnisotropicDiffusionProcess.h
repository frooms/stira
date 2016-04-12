
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

#ifndef STIRAGUI_PROCESSES_ANISOTROPICDIFFUSIONPROCESS_H
#define STIRAGUI_PROCESSES_ANISOTROPICDIFFUSIONPROCESS_H

#include "Process.h"

/** \brief class to actually run anisotropic diffusion process in a separate thread*/
class AnisotropicDiffusionProcess : public Process
{
    Q_OBJECT

public:

   /** \brief constructor
     * \param pImage input image */
   AnisotropicDiffusionProcess( stira::image::Image* pImage );
   virtual ~AnisotropicDiffusionProcess();
   
   double GetFlowParameter();
   void SetFlowParameter(double f);
   int GetNrOfIterations();
   void SetNrOfIterations(int i);
   
   void run();
   
private:
   int mNrIterations;
   double mFlowParameter;
};
#endif
