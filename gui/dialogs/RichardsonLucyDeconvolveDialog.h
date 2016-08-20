
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

#ifndef STIRAGUI_DIALOGS_RICHARDSONLUCYDECONVOLVEDIALOG_H
#define STIRAGUI_DIALOGS_RICHARDSONLUCYDECONVOLVEDIALOG_H

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

class RichardsonLucyDeconvolveProcess;  ///< forward declaration of corresponding process; see subproject "processes"
   
class RichardsonLucyDeconvolveDialog : public DialogMaster
{
    Q_OBJECT

public:

   /** \brief constructor
     * \param pImage the input image for processing */
   RichardsonLucyDeconvolveDialog( stira::imagedata::Image* pImage );
   
   /** \brief destructor*/
   virtual ~RichardsonLucyDeconvolveDialog();
   
   double GetLambda();
   
   double GetBlurLevel();
   
   StiraDefinitions::RLRegularizationType GetRegularizationType();
   
   StiraDefinitions::PSFType GetPSFType();

   int GetNrOfIterations();

public slots:
   /** \brief Creates the actual process that is started in a separate thread*/
   void SlotRun();

   /** \brief sets a suitable value for the regularization parameter for Tikhonov-Miller regularization*/
   void SlotSetDefaultTikhonovParameter();
   
   /** \brief sets a suitable value for the regularization parameter for Conchello regularization*/
   void SlotSetDefaultConchelloParameter();
   
   /** \brief sets a suitable value for the regularization parameter for Maximum Entropy regularization*/
   void SlotSetDefaultMaxEntropyParameter();
  
   /** \brief sets a suitable value for the regularization parameter for Total Variation regularization*/
    void SlotSetDefaultTotalVariationParameter();

   
protected:
   /** \brief Gets pointer to the process*/
   Process* GetProcess();

private:
   void SetupParameterLineEdits();
   void SetupRegularizationWidgets();
   void SetupPSFWidgets();
   
   RichardsonLucyDeconvolveProcess* mpProcess;  ///<  actual process
   
   QLabel*      mpLambdaLabel;  ///< label with explanation "ImageWidth"
   QLineEdit*   mpLambdaLineEdit;  ///< line edit to set "ImageWidth"
   QHBoxLayout* mpLambdaLayout;
   
   QLabel*      mpNrIterationsLabel;  ///< label with explanation "ImageHeight"
   QLineEdit*   mpNrIterationsLineEdit;  ///< line edit to set "ImageHeight"
   QHBoxLayout* mpNrIterationsLayout;
   
   QLabel*      mpBlurLevelLabel;  ///< label with explanation "Blur LevelImage"
   QLineEdit*   mpBlurLevelLineEdit;  ///< line edit to set "ImageHeight"
   QHBoxLayout* mpBlurLevelLayout;
   
   QGroupBox* mpRegularizationTypeGroupBox;
   
   QRadioButton *mpRegularizeNoneRadioButton;
   QRadioButton *mpRegularizeTikhonovMillerRadioButton;
   QRadioButton *mpRegularizeConchelloRadioButton;
   QRadioButton *mpRegularizeMaximumEntropyRadioButton;
   QRadioButton *mpRegularizeTotalVariationRadioButton;

   QVBoxLayout* mpRegularizeRadioButtonLayout;
   
   QGroupBox* mpPSFTypeGroupBox;
   
   QRadioButton *mpPSFDiskRadioButton;
   QRadioButton *mpPSFSquareRadioButton;
   QRadioButton *mpPSFGaussRadioButton;
   QRadioButton *mpPSFAiryRadioButton;

   QVBoxLayout* mpPSFRadioButtonLayout;
};

#endif
