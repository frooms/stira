
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

#ifndef STIRAGUI_DIALOGS_WIENERDECONVOLVEDIALOG_H
#define STIRAGUI_DIALOGS_WIENERDECONVOLVEDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit> 
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include "DialogMaster.h"

class WienerDeconvolveProcess; ///< forward declaration of corresponding process; see subproject "processes"

class WienerDeconvolveDialog : public DialogMaster
{
    Q_OBJECT

public:
   /** \brief constructor
     * \param pImage input image */
   WienerDeconvolveDialog( stira::imagedata::Image* pImage );
   
   /** \brief destructor*/
   virtual ~WienerDeconvolveDialog();
   
   double GetNoiseLevel();
   double GetBlurLevel();
   
public slots:
   /** \brief Creates the actual process that is started in a separate thread*/
   void SlotRun();

protected:
   /** \brief Gets pointer to the process*/
   Process* GetProcess();
   
private:
   WienerDeconvolveProcess* mpProcess;  ///<  actual process
   
   QLabel*      mpNoiseLevelLabel;
   QLineEdit*   mpNoiseLevelLineEdit;
   QHBoxLayout* mpNoiseLevelLayout;
   
   QLabel*      mpBlurLevelLabel;
   QLineEdit*   mpBlurLevelLineEdit;
   QHBoxLayout* mpBlurLevelLayout;
};

#endif
