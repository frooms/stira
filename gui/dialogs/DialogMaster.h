
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

#ifndef STIRAGUI_DIALOGS_DIALOGMASTER_H
#define STIRAGUI_DIALOGS_DIALOGMASTER_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit> 
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>


#include "../src/ImageWindow.h"
#include "../processes/Process.h"
#include "../../stira/image/datastructures/Image.h"


/** \brief master for process parameter dialogs
  * This class gathers the necessary inputs, creates an object that runs in a separate thread and 
  * creates a new window with the result*/
class DialogMaster : public QDialog
{
    Q_OBJECT

public:
   
   /** \brief constructor
     * \param pImage the input image for processing */
   DialogMaster( stira::image::Image* pImage=0 );
   
   void AddResult( stira::image::Image* pResultImage );
   
public slots:
   /** \brief runs the operation; children should implement this slot*/
   virtual void SlotRun()=0;
   
   /** \brief after running the operation, the result is put in a new viewer window and shown*/
   void SlotProcessResult();
   
   /** \brief Duriong the run, the dialog buttons are disabled*/
   void SlotDisableButtons();
   
protected:
   /** \brief gets a pointer to the underlying process
     * Needed for retrieving the result after running*/
   virtual Process* GetProcess()=0;
   std::vector< stira::image::Image* > vpResults;
   ImageWindow* mpImWindow;  ///< image window with the input data for processing
   stira::image::Image* mpInputImage;
   
   QLabel* mpTitelLabel;        ///< Title widget
   QVBoxLayout* mpDialogLayout; ///< General layout for the dialog
   QPushButton* mpRunButton;    ///< button to start the processing
   QPushButton* mpCancelButton; ///< button to cancel
   QHBoxLayout* mpButtonLayout; ///< layout for run and cancel buttons
};

#endif
