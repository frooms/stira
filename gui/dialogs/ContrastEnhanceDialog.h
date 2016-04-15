
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

#ifndef STIRAGUI_DIALOGS_CONTRASTENHANCEDIALOG_H
#define STIRAGUI_DIALOGS_CONTRASTENHANCEDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QRadioButton>

#include "../../stira/image/datastructures/Image.h"
#include "DialogMaster.h"

class ContrastEnhanceProcess;  ///< forward declaration of corresponding process; see subproject "processes"

class ContrastEnhanceDialog : public DialogMaster
{
   Q_OBJECT
   
public:

   /** \brief constructor
     * \param pImage the input image for processing */
   ContrastEnhanceDialog( stira::image::Image* pImage );
   
   /** \brief destructor*/
   virtual ~ContrastEnhanceDialog();
   
   /** \brief gets the enhancement type from its corresponding widget*/
   enum StiraDefinitions::ContrastEnhanceType GetEnhanceType();
   
   /** \brief gets the upper fraction of most intense pixels its corresponding widget
     * Above this fraction, we assume pixels are saturated*/
   double GetLowerFraction();

   /** \brief gets the lower fraction of most intense pixels its corresponding widget
     * Under this fraction, we assume pixels are just empty (black) */
   double GetUpperFraction();
   
   double GetGamma();
   
   int GetWindowSize();
   
   double GetAlphaFactor();

public slots:

   /** \brief Creates the actual process that is started in a separate thread*/
   void SlotRun();
   
   void SlotShowGamma();
   
   void SlotShowFraction();
   
   void SlotShowAdaptiveLuong();
   
   void SlotHideEdits();
   
protected:
   /** \brief Gets pointer to the process*/
   Process* GetProcess();

private:
   ContrastEnhanceProcess* mpProcess;  ///<  actual process
   
   QLabel*      mpLowerFractionLabel;  ///< label with explanation "LowerFraction"
   QLineEdit*   mpLowerFractionLineEdit;  ///< line edit to set "LowerFraction"
   QHBoxLayout* mpLowerFractionLayout;  ///< layout  to align the "LowerFraction" widgets
   
   QLabel*      mpUpperFractionLabel;  ///< label with explanation "UpperFraction"
   QLineEdit*   mpUpperFractionLineEdit;  ///< line edit to set "UpperFraction"
   QHBoxLayout* mpUpperFractionLayout;  ///< layout  to align the "UpperFraction" widgets
   
   QLabel*      mpGammaLabel;  ///< label with explanation "Gamma"
   QLineEdit*   mpGammaLineEdit;  ///< line edit to set "Gamma"
   QHBoxLayout* mpGammaLayout;  ///< layout to align the "Gamma" widgets
   
   QLabel*      mpAlphaFactorLabel;  ///< label with explanation "Alpha factor"
   QLineEdit*   mpAlphaFactorLineEdit;  ///< line edit to set "Alpha factor"
   QHBoxLayout* mpAlphaFactorLayout;  ///< layout to align the "Alpha factor" widgets
   
   QLabel*      mpWindowSizeLabel;  ///< label with explanation "Window Size"
   QLineEdit*   mpWindowSizeGammaLineEdit;  ///< line edit to set "Window Size"
   QHBoxLayout* mpWindowSizeGammaLayout;  ///< layout to align the "Window Size" widgets
   
   QGroupBox* mpFractionGroupBox;  ///< Groupbox for the enhancement type radio buttons
   QRadioButton* mpImageNegativeRadioButton;  ///< get image negative
   QRadioButton* mpGammaRescaleRadioButton;  ///< apply gamma compensation
   QRadioButton* mpLinearRescaleRadioButton;  ///< Robust Linear Intensity Rescaling (ignore a given fraction of outliers)
   QRadioButton* mpDarkChannelHazeRemovalRadioButton;  ///< Dark Channel Prior based Haze Removal
   QRadioButton* mpRetinexRadioButton;  ///< select Retinex contrast enhancement (MSRCR)
   QRadioButton* mpAdaptiveHistogramEqualizerRadioButton;  ///< select contrast enhancement by adaptive histogram equalization
   QRadioButton* mpHistogramEqualizeRGBRadioButton;  ///< select contrast enhancement by histogram equalization
   QRadioButton* mpHistogramEqualizePerBandRadioButton;  ///< select contrast enhancement by histogram equalization
   QRadioButton* mpWaveletBasedRadioButton; ///< select wavelet-based contrast enhancement
   QRadioButton* mpAdaptiveLuongBasedRadioButton;
   QVBoxLayout* mpRadioButtonLayout;  ///< layout for the enhancement type radio buttons
};

#endif
