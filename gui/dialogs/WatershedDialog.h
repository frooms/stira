
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

#ifndef STIRAGUI_DIALOGS_WATERSHEDDIALOG_H
#define STIRAGUI_DIALOGS_WATERSHEDDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit> 
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QCheckBox>

#include "DialogMaster.h"

class WatershedProcess; ///< forward declaration of corresponding process; see subproject "processes"

class WatershedDialog : public DialogMaster
{
    Q_OBJECT

public:
   /** \brief constructor
     * \param pImage input image */
   WatershedDialog( stira::image::Image* pImage );
   
   /** \brief destructor*/
   virtual ~WatershedDialog();
   
   int GetMaximalMinimumLevel();
   int GetEqualityPrecision();
   bool GetUseGradientImage();
public slots:
   /** \brief Creates the actual process that is started in a separate thread*/
   void SlotRun();
   
protected:
   /** \brief Gets pointer to the process*/
   Process* GetProcess();
   
private:
   WatershedProcess* mpProcess;  ///<  actual process
   QCheckBox*   mpUseGradientCheckBox;
   QLabel*      mpMaximalMinimumLevelLabel;
   QHBoxLayout* mpMaximalMinimumLevelLayout;
   QLineEdit*   mpMaximalMinimumLevelLineEdit;
   
   QLabel*      mpEqualityPrecisionLabel;
   QLineEdit*   mpEqualityPrecisionLineEdit;
   QHBoxLayout* mpEqualityPrecisionLayout;
};

#endif
