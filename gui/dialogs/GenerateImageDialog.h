
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

#ifndef STIRAGUI_DIALOGS_GENERATEIMAGEDIALOG_H
#define STIRAGUI_DIALOGS_GENERATEIMAGEDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QRadioButton>

#include "../src/ImageWindow.h"
#include "DialogMaster.h"

class GenerateImageProcess;  ///< forward declaration of corresponding process; see subproject "processes"
   
class GenerateImageDialog : public DialogMaster
{
    Q_OBJECT

public:

   /** \brief constructor*/
   GenerateImageDialog( );
   
   /** \brief destructor*/
   virtual ~GenerateImageDialog();
   
   /** \brief gets the width of the image to generate from its corresponding widget*/
   int GetWidth();
   
   /** \brief gets the height of the image to generate from its corresponding widget*/
   int GetHeight();
   
   /** \brief gets the height of the image to generate from its corresponding widget*/
   double GetFrequency();
   
   double GetMaxSigma();
   
   /** \brief gets the type of the image to generate from its corresponding widget*/
   enum StiraDefinitions::SyntheticImageType GetType();

public slots:
   /** \brief Creates the actual process that is started in a separate thread*/
   void SlotRun();
   
   /** \brief Switches which parameter edits to show*/
   void SlotHideAll();
   
    /** \brief Switches which parameter edits to show*/
   void SlotShowSigma();
   
    /** \brief Switches which parameter edits to show*/
   void SlotShowFrequency();
   
    /** \brief Switches which parameter edits to show*/
   void SlotShowSigmaAndFrequency();
   
protected:
   /** \brief Gets pointer to the process*/
   Process* GetProcess();

private:
   GenerateImageProcess* mpProcess;  ///<  actual process
   
   QLabel*    mpImageWidthLabel;  ///< label with explanation "ImageWidth"
   QLineEdit* mpImageWidthLineEdit;  ///< line edit to set "ImageWidth"
   
   QLabel*    mpImageHeightLabel;  ///< label with explanation "ImageHeight"
   QLineEdit* mpImageHeightLineEdit;  ///< line edit to set "ImageHeight"
   
   QLabel*    mpFrequencyLabel;  ///< label with explanation "Frequency"
   QLineEdit* mpFrequencyLineEdit;  ///< line edit to set "Frequency"
   
   QLabel*    mpMaxSigmaLabel;
   QLineEdit* mpMaxSigmaLineEdit;
   
   QGroupBox* mpImageTypeGroupBox;
   
   QRadioButton *mpEmptyImageRadioButton;
   QRadioButton *mpEmptyPlusNoiseImageRadioButton;
   QRadioButton *mpHorizontalGradientRadioButton;
   QRadioButton *mpVerticalGradientRadioButton;
   QRadioButton *mpHorizontalSineWaveRadioButton;
   QRadioButton *mpVerticalSineWaveRadioButton;
   QRadioButton *mpEuclideanSpotRadioButton;
   QRadioButton *mpBlurredBarsRadioButton;
   QRadioButton *mpStarChartRadioButton;
   QRadioButton *mpInverseZonePlateRadioButton;
   QRadioButton *mpZonePlateRadioButton;
   QRadioButton *mpLogFrequencyContrastRadioButton;
   QRadioButton *mpSheppLoganRadioButton;
   QRadioButton *mpGretaMacbethRadioButton;
   QRadioButton *mpIsingRadioButton;

   QHBoxLayout* mpImageSizeLayout;
   QHBoxLayout* mpImageParametersLayout;
   
   QVBoxLayout* mpRadioButtonLayout;
};

#endif
