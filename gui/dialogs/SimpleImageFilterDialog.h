
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

#ifndef STIRAGUI_DIALOGS_SIMPLEIMAGEFILTERDIALOG_H
#define STIRAGUI_DIALOGS_SIMPLEIMAGEFILTERDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QRadioButton>
#include <QGroupBox>
#include <QLineEdit> 
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>

#include "../src/ImageWindow.h"
#include "DialogMaster.h"

#include "../../stira/imagedata/simpletools/GridExtender.h"

class SimpleImageFilterProcess;  ///< forward declaration of corresponding process; see subproject "processes"

/** \brief dialog for simple image filtering operations like local average, gaussian and median filtering
  *
  * Simple means that the process can be described with just a few simple input parameters and does not have
  * a long dependency tree.
  *
  * This class gathers the necessary inputs, creates an object that runs in a separate thread and 
  * creates a new window with the result*/
class SimpleImageFilterDialog : public DialogMaster
{
    Q_OBJECT

public:
   /** \brief constructor
     * \param pImage input image */
   SimpleImageFilterDialog( stira::imagedata::Image* pImage );
   
   /** \brief destructor*/
   ~SimpleImageFilterDialog();
   
   /** \brief gets the filter type */
   StiraDefinitions::SimpleFilterType GetFilterType();
   
   /** \brief gets how the image should be treated at the image borders */
   stira::imagedata::GridExtender<double>::ExtensionType GetExtensionType();
   
   /** \brief gets the filter width (or length) */
   int GetFilterWidth();
   
   /** \brief gets sigma */
   double GetSigma();
   
   /** \brief gets the angle */
   double GetAngle();
   
public slots:
   /** \brief Creates the actual process that is started in a separate thread*/
   void SlotRun();
   
   /** \brief Shows widgets for sigma and length and hides widgets for angle */
   void SlotShowSigmaShowLength();
   
   /** \brief Shows widgets for sigma and hides widgets for length and angle */
   void SlotShowSigmaHideLength();
   
   /** \brief Shows widgets for length and hides widgets for sigma and angle */
   void SlotShowLengthHideSigma();
   
   /** \brief Shows widgets for length and angle; hides widgets for sigma */
   void SlotShowLengthAndAngle();
   
   /** \brief Hides all parameter widgets */
   void SlotHideAll();
   
   /** \brief Sets default values for Non-Local Means filter */
   void SlotSetNonLocalMeansDefaultValues();
   
   /** \brief Sets default values for other filters */
   void SlotSetNormalDefaultValues();
   
protected:
   /** \brief Gets pointer to the process*/
   Process* GetProcess();
   
private:

   void SetupFilterTypeButtons();
   void SetupBorderExtensionTypeButtons();

   void SetupParameterLineEdits();
   
   SimpleImageFilterProcess* mpProcess;  ///< actual process
   
   QRadioButton* mpLocalMeanFilterRadioButton;   ///< button to choose Local Mean Filtering
   QRadioButton* mpNonLocalMeanFilterRadioButton;   ///< button to choose Non-Local Means Filtering (Buades)
   QRadioButton* mpNormalMedianFilterRadioButton; ///< button to choose the normal median Filter
   QRadioButton* mpHybridMedianFilterRadioButton; ///< button to choose the hybrid median Filter
   QRadioButton* mpGaussianFilterRadioButton; ///< button to choose a Gaussian Filter
   QRadioButton* mpKuwaharaFilterRadioButton; ///< button to choose the Kuwahara Filter
   QRadioButton* mpLaplacianOfGaussianFilterRadioButton; ///< button to choose the Laplacian-of-Gaussian (LoG) Filter
   QRadioButton* mpAdaptiveBilateralFilterRadioButton; ///< button to choose the Adaptive Bilateral Filter
   QRadioButton* mpUnsharpMaskFilterRadioButton; ///< button to choose Unsharp Masking
   QRadioButton* mpSobelXFilterRadioButton; ///< button to choose the Sobel filter in the X direction
   QRadioButton* mpSobelYFilterRadioButton; ///< button to choose the Sobel filter in the Y direction
   QRadioButton* mpMotionBlurFilterRadioButton; ///< button to choose to apply motion blur to an image
   
   QGroupBox* mpFilterTypeGroupBox;
   QVBoxLayout* mpFilterRadioButtonLayout;
   
   QRadioButton* mpMirrorExtendRadioButton;
   QRadioButton* mpRepeatExtendRadioButton;
   QRadioButton* mpNullExtendRadioButton;
   QGroupBox* mpExtendTypeGroupBox;
   QVBoxLayout* mExtendRadioButtonLayout;
   
   QLabel* mpFilterWidthLabel;
   QLineEdit* mpFilterWidthLineEdit;
   QHBoxLayout* mpFilterWidthLayout;
   
   QLabel* mpSigmaLabel;
   QLineEdit* mpSigmaLineEdit;
   QHBoxLayout* mpSigmaLayout;
   
   QLabel* mpAngleLabel;
   QLineEdit* mpAngleLineEdit;
   QHBoxLayout* mpAngleLayout;
};

#endif
