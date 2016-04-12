
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

#ifndef STIRAGUI_DIALOGS_CANNYDIALOG_H
#define STIRAGUI_DIALOGS_CANNYDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit> 
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>

#include "DialogMaster.h"

class CannyProcess;  ///< forward declaration of corresponding process; see subproject "processes"

/** \brief dialog for canny edge detection
  * This class gathers the necessary inputs, creates an object that runs in a separate thread and 
  * creates a new window with the result*/
class CannyDialog : public DialogMaster
{
    Q_OBJECT

public:
   /** \brief constructor
     * \param pImage input image */
   CannyDialog( stira::image::Image* pImage );
   
   /** \brief destructor*/
   virtual ~CannyDialog();
   
   /** \brief gets hysteresis upper threshold from its corresponding widget*/
   double GetUpperThreshold();
   
   /** \brief gets hysteresis lower threshold from its corresponding widget*/
   double GetLowerThreshold();
   
   /** \brief gets smoothing level from the widget*/
   double GetSigmaSmoothing();
   
public slots:
   /** \brief Creates the actual process that is started in a separate thread*/
   void SlotRun();
   
protected:
   /** \brief Gets pointer to the process*/
   Process* GetProcess();

private:

   CannyProcess* mpProcess;  ///<  actual process
   
   QLabel*      mpUpperThresholdLabel;  ///< label with explanation "UpperThreshold"
   QLineEdit*   mpUpperThresholdLineEdit;  ///< line edit to set "UpperThreshold"
   QHBoxLayout* mpUpperThresholdLayout;  ///< layout  to align the "UpperThreshold" widgets
   
   QLabel*      mpLowerThresholdLabel;  ///< label with explanation "LowerThreshold"
   QLineEdit*   mpLowerThresholdLineEdit;  ///< line edit to set "LowerThreshold"
   QHBoxLayout* mpLowerThresholdLayout;  ///< layout  to align the "LowerThreshold" widgets
   
   QLabel*      mpSigmaSmoothingLabel;  ///< label with explanation "SigmaSmoothing"
   QLineEdit*   mpSigmaSmoothingLineEdit;  ///< line edit to set "SigmaSmoothing"
   QHBoxLayout* mpSigmaSmoothingLayout;  ///< layout  to align the "SigmaSmoothing" widgets
};

#endif
