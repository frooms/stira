

/***********************************************************************************
 *   Copyright (C) 2016 by Filip Rooms                                             *
 *                                                                                 *
 *  Terms and conditions for using this software in any form are provided in the   *
 *  file COPYING, which can be found in the root directory of this project.        *
 *                                                                                 *
 *   Contact data: filip.rooms@gmail.com                                           *
 *                 http://www.filiprooms.be/                                       *
 *                                                                                 *
 ***********************************************************************************/

#ifndef STIRAGUI_DIALOGS_HOUGHTRANSFORMDIALOG_H
#define STIRAGUI_DIALOGS_HOUGHTRANSFORMDIALOG_H


#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QRadioButton>
#include <QGroupBox>

#include "DialogMaster.h"

class HoughTransformProcess; ///< forward declaration of corresponding process; see subproject "processes"

class HoughTransformDialog : public DialogMaster
{
    Q_OBJECT

public:
   /** \brief constructor
     * \param pImage input image */
   HoughTransformDialog( stira::imagedata::Image* pImage );

   /** \brief destructor*/
   virtual ~HoughTransformDialog();

   int GetMaximalRadius();

   int GetMinimalRadius();

   bool DidChooseCircles();

public slots:
   /** \brief Creates the actual process that is started in a separate thread*/
   void SlotRun();

protected:
   /** \brief Gets pointer to the process*/
   Process* GetProcess();

private:
   HoughTransformProcess* mpProcess;  ///<  actual process
   QRadioButton*   mpChooseCircleHoughTransformRadioButton;
   QRadioButton*   mpChooseLineHoughTransformRadioButton;
   QGroupBox*      mpChooseHoughTransformTypeBox;
   QVBoxLayout*    mpChooseHoughTransformLayout;

   QLabel*      mpMaximalRadiusLabel;
   QHBoxLayout* mpMaximalRadiusLayout;
   QLineEdit*   mpMaximalRadiusLineEdit;

   QLabel*      mpMinimalRadiusLabel;
   QHBoxLayout* mpMinimalRadiusLayout;
   QLineEdit*   mpMinimalRadiusLineEdit;
};


#endif // HOUGHTRANSFORMDIALOG_H
