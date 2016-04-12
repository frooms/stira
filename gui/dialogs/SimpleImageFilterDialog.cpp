
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

#include <QApplication>
#include "SimpleImageFilterDialog.h"
#include "../processes/SimpleImageFilterProcess.h"
#include "../src/MainWindow.h"

using namespace stira::filter;
using namespace stira::image;
using namespace std;

SimpleImageFilterDialog::SimpleImageFilterDialog( Image* pImage ) : DialogMaster( pImage )
{
   mpProcess = 0;
   mpTitelLabel->setText( QString("Simple Filter Parameters") );
   
   SetupFilterTypeButtons();
   SetupBorderExtensionTypeButtons();
   SetupParameterLineEdits();
    
   mpDialogLayout->addWidget( mpTitelLabel );
   mpDialogLayout->addWidget( mpFilterTypeGroupBox );
   mpDialogLayout->addLayout( mpFilterWidthLayout );
   mpDialogLayout->addLayout( mpSigmaLayout );
   mpDialogLayout->addLayout( mpAngleLayout );
   mpDialogLayout->addWidget( mpExtendTypeGroupBox );
   mpDialogLayout->addLayout( mpButtonLayout );
   this->show();
}

//--------------------------------------------------------

SimpleImageFilterDialog::~SimpleImageFilterDialog()
{
   if (mpProcess != 0)
   {
      delete mpProcess;
   }
}

//--------------------------------------------------------

void SimpleImageFilterDialog::SetupBorderExtensionTypeButtons()
{
   mpMirrorExtendRadioButton = new QRadioButton(tr("&Mirror intensities"));
   mpRepeatExtendRadioButton = new QRadioButton(tr("&Repeat intensities"));
   mpNullExtendRadioButton = new QRadioButton(tr("&Null intensities"));
   mpRepeatExtendRadioButton->setChecked(true);
   
   mExtendRadioButtonLayout = new QVBoxLayout;
   mExtendRadioButtonLayout->addWidget( mpMirrorExtendRadioButton );
   mExtendRadioButtonLayout->addWidget( mpRepeatExtendRadioButton );
   mExtendRadioButtonLayout->addWidget( mpNullExtendRadioButton );
   
   mpExtendTypeGroupBox = new QGroupBox(tr("Extension Type"));
   mpExtendTypeGroupBox->setLayout( mExtendRadioButtonLayout );
}

//--------------------------------------------------------

void SimpleImageFilterDialog::SetupFilterTypeButtons()
{
   mpLocalMeanFilterRadioButton = new QRadioButton(tr("&Local Mean Filter"));
   mpNonLocalMeanFilterRadioButton = new QRadioButton(tr("&Non-Local Mean Filter"));
   mpNormalMedianFilterRadioButton = new QRadioButton(tr("&Normal Median Filter"));
   mpHybridMedianFilterRadioButton = new QRadioButton(tr("&Hybrid Median Filter"));
   mpGaussianFilterRadioButton = new QRadioButton(tr("&Gaussian Filter"));
   mpKuwaharaFilterRadioButton = new QRadioButton(tr("&Kuwahara Filter"));
   mpLaplacianOfGaussianFilterRadioButton = new QRadioButton(tr("&Laplacian of Gaussian Filter"));
   mpAdaptiveBilateralFilterRadioButton = new QRadioButton(tr("&Adaptive Bilateral Filter"));
   mpUnsharpMaskFilterRadioButton = new QRadioButton(tr("&Unsharp Mask Filter"));
   mpSobelXFilterRadioButton = new QRadioButton(tr("&Sobel Filter X"));
   mpSobelYFilterRadioButton = new QRadioButton(tr("&Sobel Filter Y"));
   mpMotionBlurFilterRadioButton = new QRadioButton(tr("&Motion Blur"));
   mpGaussianFilterRadioButton->setChecked(true);
   
   mpFilterRadioButtonLayout = new QVBoxLayout;
   mpFilterRadioButtonLayout->addWidget( mpLocalMeanFilterRadioButton );
   mpFilterRadioButtonLayout->addWidget( mpNonLocalMeanFilterRadioButton );
   mpFilterRadioButtonLayout->addWidget( mpNormalMedianFilterRadioButton );
   mpFilterRadioButtonLayout->addWidget( mpHybridMedianFilterRadioButton );
   mpFilterRadioButtonLayout->addWidget( mpGaussianFilterRadioButton );
   mpFilterRadioButtonLayout->addWidget( mpKuwaharaFilterRadioButton );
   mpFilterRadioButtonLayout->addWidget( mpLaplacianOfGaussianFilterRadioButton );
   mpFilterRadioButtonLayout->addWidget( mpAdaptiveBilateralFilterRadioButton );
   mpFilterRadioButtonLayout->addWidget( mpUnsharpMaskFilterRadioButton );
   mpFilterRadioButtonLayout->addWidget( mpSobelXFilterRadioButton );
   mpFilterRadioButtonLayout->addWidget( mpSobelYFilterRadioButton );
   mpFilterRadioButtonLayout->addWidget( mpMotionBlurFilterRadioButton );
   
   mpFilterTypeGroupBox = new QGroupBox(tr("Filter Type"));
   mpFilterTypeGroupBox->setLayout( mpFilterRadioButtonLayout );
}

//--------------------------------------------------------

void SimpleImageFilterDialog::SetupParameterLineEdits()
{
   mpFilterWidthLabel = new QLabel( QString("Filter Width: "), this );
   mpFilterWidthLineEdit = new QLineEdit( QString("3"), this );
   mpFilterWidthLayout = new QHBoxLayout;
   mpFilterWidthLayout->addWidget( mpFilterWidthLabel );
   mpFilterWidthLayout->addWidget( mpFilterWidthLineEdit );
   
   mpSigmaLabel = new QLabel( QString("Sigma: "), this );
   mpSigmaLineEdit = new QLineEdit( QString("1.5"), this );
   mpSigmaLayout = new QHBoxLayout;
   mpSigmaLayout->addWidget( mpSigmaLabel );
   mpSigmaLayout->addWidget( mpSigmaLineEdit );
   
   mpAngleLabel = new QLabel( QString("Angle: "), this );
   mpAngleLineEdit = new QLineEdit( QString("-0.5"), this );
   mpAngleLayout = new QHBoxLayout;
   mpAngleLayout->addWidget( mpAngleLabel );
   mpAngleLayout->addWidget( mpAngleLineEdit );

   connect( mpLocalMeanFilterRadioButton, SIGNAL( clicked() ), this, SLOT( SlotShowLengthHideSigma() ) );
   connect( mpNonLocalMeanFilterRadioButton, SIGNAL( clicked() ), this, SLOT( SlotShowSigmaShowLength() ) );
   connect( mpNormalMedianFilterRadioButton, SIGNAL( clicked() ), this, SLOT( SlotShowLengthHideSigma() ) );
   connect( mpHybridMedianFilterRadioButton, SIGNAL( clicked() ), this, SLOT( SlotShowLengthHideSigma() ) );
   connect( mpGaussianFilterRadioButton,  SIGNAL( clicked() ), this, SLOT( SlotShowSigmaHideLength() ) );
   connect( mpKuwaharaFilterRadioButton,  SIGNAL( clicked() ), this, SLOT( SlotShowLengthHideSigma() ) );
   connect( mpLaplacianOfGaussianFilterRadioButton,  SIGNAL( clicked() ), this, SLOT( SlotHideAll() ) );
   connect( mpAdaptiveBilateralFilterRadioButton,  SIGNAL( clicked() ), this, SLOT( SlotHideAll() ) );
   connect( mpUnsharpMaskFilterRadioButton,  SIGNAL( clicked() ), this, SLOT( SlotShowSigmaHideLength() ) );
   connect( mpSobelXFilterRadioButton,  SIGNAL( clicked() ), this, SLOT( SlotHideAll() ) );
   connect( mpSobelYFilterRadioButton,  SIGNAL( clicked() ), this, SLOT( SlotHideAll() ) );
   connect( mpMotionBlurFilterRadioButton,  SIGNAL( clicked() ), this, SLOT( SlotShowLengthAndAngle() ) );

   connect( mpLocalMeanFilterRadioButton, SIGNAL( clicked() ), this, SLOT( SlotSetNormalDefaultValues() ) );
   connect( mpNonLocalMeanFilterRadioButton, SIGNAL( clicked() ), this, SLOT( SlotSetNonLocalMeansDefaultValues() ) );
   connect( mpNormalMedianFilterRadioButton, SIGNAL( clicked() ), this, SLOT( SlotSetNormalDefaultValues() ) );
   connect( mpHybridMedianFilterRadioButton, SIGNAL( clicked() ), this, SLOT( SlotSetNormalDefaultValues() ) );
   connect( mpGaussianFilterRadioButton,  SIGNAL( clicked() ), this, SLOT( SlotSetNormalDefaultValues() ) );
   connect( mpKuwaharaFilterRadioButton,  SIGNAL( clicked() ), this, SLOT( SlotSetNormalDefaultValues() ) );
   connect( mpLaplacianOfGaussianFilterRadioButton,  SIGNAL( clicked() ), this, SLOT( SlotSetNormalDefaultValues() ) );
   connect( mpAdaptiveBilateralFilterRadioButton,  SIGNAL( clicked() ), this, SLOT( SlotSetNormalDefaultValues() ) );
   connect( mpUnsharpMaskFilterRadioButton,  SIGNAL( clicked() ), this, SLOT( SlotSetNormalDefaultValues() ) );
   connect( mpSobelXFilterRadioButton,  SIGNAL( clicked() ), this, SLOT( SlotSetNormalDefaultValues() ) );
   connect( mpSobelYFilterRadioButton,  SIGNAL( clicked() ), this, SLOT( SlotSetNormalDefaultValues() ) );
   connect( mpMotionBlurFilterRadioButton,  SIGNAL( clicked() ), this, SLOT( SlotSetNormalDefaultValues() ) );
   
   SlotShowSigmaHideLength();
   
}

//--------------------------------------------------------

void SimpleImageFilterDialog::SlotShowSigmaShowLength()
{
   mpFilterWidthLabel->show();
   mpFilterWidthLineEdit->show();
   
   mpSigmaLabel->show();
   mpSigmaLineEdit->show();
   
   mpAngleLabel->hide();
   mpAngleLineEdit->hide();
}

//--------------------------------------------------------

void SimpleImageFilterDialog::SlotShowSigmaHideLength()
{
   mpFilterWidthLabel->hide();
   mpFilterWidthLineEdit->hide();
   
   mpSigmaLabel->show();
   mpSigmaLineEdit->show();
   
   mpAngleLabel->hide();
   mpAngleLineEdit->hide();
}

//--------------------------------------------------------

void SimpleImageFilterDialog::SlotShowLengthHideSigma()
{
   mpFilterWidthLabel->show();
   mpFilterWidthLineEdit->show();
   
   mpSigmaLabel->hide();
   mpSigmaLineEdit->hide();
   
   mpAngleLabel->hide();
   mpAngleLineEdit->hide();
}

//--------------------------------------------------------

void SimpleImageFilterDialog::SlotShowLengthAndAngle()
{
   mpFilterWidthLabel->show();
   mpFilterWidthLineEdit->show();
   
   mpSigmaLabel->hide();
   mpSigmaLineEdit->hide();
   
   mpAngleLabel->show();
   mpAngleLineEdit->show();
}

//--------------------------------------------------------

void SimpleImageFilterDialog::SlotHideAll()
{
   mpFilterWidthLabel->hide();
   mpFilterWidthLineEdit->hide();
   
   mpSigmaLabel->hide();
   mpSigmaLineEdit->hide();
   
   mpAngleLabel->hide();
   mpAngleLineEdit->hide();
}

//--------------------------------------------------------

void SimpleImageFilterDialog::SlotSetNonLocalMeansDefaultValues()
{
   mpFilterWidthLineEdit->setText( QString("7") );
   mpSigmaLineEdit->setText( QString("75") );
}

//--------------------------------------------------------

void SimpleImageFilterDialog::SlotSetNormalDefaultValues()
{
   mpFilterWidthLineEdit->setText( QString("3") );
   mpSigmaLineEdit->setText( QString("1.5") );
}

//--------------------------------------------------------

int SimpleImageFilterDialog::GetFilterWidth()
{
   return mpFilterWidthLineEdit->text().toInt();
}

//--------------------------------------------------------

double SimpleImageFilterDialog::GetSigma()
{
   return mpSigmaLineEdit->text().toDouble();
}

//--------------------------------------------------------

double SimpleImageFilterDialog::GetAngle()
{
   return mpAngleLineEdit->text().toDouble();
}

//--------------------------------------------------------

StiraDefinitions::SimpleFilterType SimpleImageFilterDialog::GetFilterType()
{
   if ( mpLocalMeanFilterRadioButton->isChecked ( ) ) 
   {
      return StiraDefinitions::FILTER_LOCALMEAN;
   }
   else if ( mpNonLocalMeanFilterRadioButton->isChecked ( ) )
   {
      return StiraDefinitions::FILTER_NONLOCALMEAN;
   }
   else if ( mpNormalMedianFilterRadioButton->isChecked ( ) )
   {
      return StiraDefinitions::FILTER_NORMALMEDIAN;
   }
   else if ( mpHybridMedianFilterRadioButton->isChecked ( ) )
   {
      return StiraDefinitions::FILTER_HYBRIDMEDIAN;
   }
   else if( mpGaussianFilterRadioButton->isChecked ( ) )
   {
      return StiraDefinitions::FILTER_GAUSSIAN;
   }
   else if( mpKuwaharaFilterRadioButton->isChecked ( ) )
   {
      return StiraDefinitions::FILTER_KUWAHARA;
   }
   else if( mpLaplacianOfGaussianFilterRadioButton->isChecked ( )  )
   {
      return StiraDefinitions::FILTER_LAPLACIANOFGAUSSIAN;
   }
   else if( mpAdaptiveBilateralFilterRadioButton->isChecked ( )  )
   {
      return StiraDefinitions::FILTER_ADAPTIVEBILATERAL;
   }
   else if ( mpSobelXFilterRadioButton->isChecked ( )  )
   {
      return StiraDefinitions::FILTER_SOBELX;
   }
   else if ( mpSobelYFilterRadioButton->isChecked ( )  )
   {
      return StiraDefinitions::FILTER_SOBELY;
   }
   else if ( mpMotionBlurFilterRadioButton->isChecked ( )  )
   {
      return StiraDefinitions::FILTER_MOTIONBLUR;
   }
   else //if( mpUnsharpMaskFilterRadioButton->isChecked ( )  )
   {
      return StiraDefinitions::FILTER_UNSHARPMASK;
   }
}

//--------------------------------------------------------
   
stira::image::GridExtender<double>::ExtensionType SimpleImageFilterDialog::GetExtensionType()
{
   if ( mpMirrorExtendRadioButton->isChecked ( ) ) 
   {
      return  stira::image::GridExtender<double>::EXTEND_MIRROR;
   }
   else if ( mpRepeatExtendRadioButton->isChecked ( ) ) 
   {
      return  stira::image::GridExtender<double>::EXTEND_TILED;
   }
   else //mpNullExtendRadioButton is checked
   {
      return  stira::image::GridExtender<double>::EXTEND_ZERO;
   }
}

//--------------------------------------------------------

void SimpleImageFilterDialog::SlotRun()
{
   mpProcess = new SimpleImageFilterProcess( mpInputImage );
   connect( mpProcess, SIGNAL( finished() ), this, SLOT( SlotProcessResult() ) );
   mpProcess->SetFilterType( this->GetFilterType() );
   mpProcess->SetFilterWidth( this->GetFilterWidth() );
   mpProcess->SetSigma( this->GetSigma() );
   mpProcess->SetAngle( this->GetAngle() );
   mpProcess->SetExtensionType( this->GetExtensionType() );
   mpProcess->start();
}

//--------------------------------------------------------

Process* SimpleImageFilterDialog::GetProcess()
{
   return mpProcess;
}

//--------------------------------------------------------
