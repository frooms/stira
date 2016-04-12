
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

#ifndef STIRAGUI_PROCESSES_PROCESS_H
#define STIRAGUI_PROCESSES_PROCESS_H

#include <QThread>

#include "../src/ImageWindow.h"
#include "../definitions/StiraDefinitions.h"
#include "../../stira/image/datastructures/Image.h"

/** \brief Parent class for all processes*/
class Process : public QThread
{
    Q_OBJECT

public:
   /** \brief constructor
     * \param pImWindow image window to extract input from*/
   Process( stira::image::Image* pImage=0 );
   
   /** \brief destructor */
   virtual ~Process();
   
   /** \brief virtual overloaded method to start new thread*/
   virtual void run()=0;
   
   /** \brief gets the result for output
     * pointer to object mpOutImage is returned; The caller becomes responsible to delete this */
   std::vector< stira::image::Image* > GetResultImages();
   
   void AddResult( stira::image::Image* pResultImage );

   QString GetProcessName();
protected:
   QString mProcessName;
   std::vector< stira::image::Image* > vpOutImageVector; ///< the result for output; is NOT deleted by destructor 
   stira::image::Image* mpImage; ///< image window to extract input from
};
#endif
