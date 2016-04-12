
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

#ifndef STIRAGUI_DIALOGS_LOGGABORFILTERDIALOG_H
#define STIRAGUI_DIALOGS_LOGGABORFILTERDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QRadioButton>
#include <QCheckBox>

#include "../src/ImageWindow.h"
#include "DialogMaster.h"

class LogGaborFilterProcess;  ///< forward declaration of corresponding process; see subproject "processes"
   
class LogGaborFilterDialog : public DialogMaster
{
    Q_OBJECT

public:

   /** \brief constructor
     * \param pImage the input image for processing */
   LogGaborFilterDialog( stira::image::Image* pImage );
   
   /** \brief destructor*/
   virtual ~LogGaborFilterDialog();
   
   double GetCenterFrequency();
   double GetRadialWidth();
   double GetCenterAngle();
   double GetAngleSpread();

public slots:
   /** \brief Creates the actual process that is started in a separate thread*/
   void SlotRun();
   
protected:
   /** \brief Gets pointer to the process*/
   Process* GetProcess();

private:
   LogGaborFilterProcess* mpProcess;  ///<  actual process
   
   QVBoxLayout* mpLabelsLayout;
   QVBoxLayout* mpLineEditsLayout;
   QVBoxLayout* mpOutputsLayout;
   QHBoxLayout* mpParametersLayout;
   
   QLabel*      mpCenterFrequencyLabel; ///< label for nr of scales in the pyramid 
   QLineEdit*   mpCenterFrequencyLineEdit; ///< line edit for nr of scales in the pyramid

   QLabel*      mpRadialWidthLabel; ///< label for nr of orientations in the pyramid
   QLineEdit*   mpRadialWidthLineEdit; ///< line edit for for nr of orientations in the pyramid
   
   QLabel*      mpCenterAngleLabel;  ///< label for regularization parameter lambda
   QLineEdit*   mpCenterAngleLineEdit;  ///< line edit for regularization parameter lambda

   QLabel*      mpAngleSpreadLabel; ///< label for data fit parameter mu
   QLineEdit*   mpAngleSpreadLineEdit; ///< line edit for data fit parameter mu

   QCheckBox *mpCreateRealResponseCheckBox;
   QCheckBox *mpCreateImagResponseCheckBox;
   QCheckBox *mpCreateMagnitudeResponseCheckBox;
   QCheckBox *mpCreateTransferResponseCheckBox;
};

#endif
