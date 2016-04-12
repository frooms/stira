
/*****************************************
 *   Copyright (C) 2008 by Filip Rooms   *
 *   filip.rooms@gmail.com               *
 *   http://www.filiprooms.be/           *
 *                                       *
 *****************************************/

#ifndef FRIEPGUI_PROCESSES_CANNYPROCESS_H
#define FRIEPGUI_PROCESSES_CANNYPROCESS_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit> 
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>

#include "../src/ImageWindow.h"

class CannyProcess : public QDialog
{
    Q_OBJECT

public:
   CannyProcess(ImageWindow* pImWindow );
   virtual ~CannyProcess();
   
   double GetUpperThreshold();
   double GetLowerThreshold();
   double GetSigmaSmoothing();
   
public slots:
   void SlotRunCannyEdgeDetect();

private:
   ImageWindow* mpImWindow;
   QLabel* mpTitelLabel;
   
   QLabel*      mpUpperThresholdLabel;
   QLineEdit*   mpUpperThresholdLineEdit;
   QHBoxLayout* mpUpperThresholdLayout;
   
   QLabel*      mpLowerThresholdLabel;
   QLineEdit*   mpLowerThresholdLineEdit;
   QHBoxLayout* mpLowerThresholdLayout;
   
   QLabel*      mpSigmaSmoothingLabel;
   QLineEdit*   mpSigmaSmoothingLineEdit;
   QHBoxLayout* mpSigmaSmoothingLayout;

   QHBoxLayout* mpButtonLayout;
   QVBoxLayout* mpDialogLayout;
   
   QPushButton* mpRunButton;
   QPushButton* mpCancelButton;
};

#endif
