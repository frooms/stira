
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

#include "ContrastEnhanceDialog.h"
#include "../processes/ContrastEnhanceProcess.h"
#include "../src/MainWindow.h"

using namespace stira::image;

ContrastEnhanceDialog::ContrastEnhanceDialog( Image* pImage ) : DialogMaster( pImage )
{
   mpTitelLabel->setText( QString("<B>Contrast Enhancement Parameters</B>") );
   
   mpLowerFractionLabel = new QLabel( QString("Lower Fraction: "), this );
   mpLowerFractionLineEdit = new QLineEdit( QString("0.03"), this );
   mpLowerFractionLayout = new QHBoxLayout;
   mpLowerFractionLayout->addWidget( mpLowerFractionLabel );
   mpLowerFractionLayout->addWidget( mpLowerFractionLineEdit );
   
   mpUpperFractionLabel = new QLabel( QString("Upper Fraction: "), this );
   mpUpperFractionLineEdit = new QLineEdit( QString("0.99"), this );
   mpUpperFractionLayout = new QHBoxLayout;
   mpUpperFractionLayout->addWidget( mpUpperFractionLabel );
   mpUpperFractionLayout->addWidget( mpUpperFractionLineEdit );
   
   mpGammaLabel = new QLabel( QString("Gamma: "), this );
   mpGammaLineEdit = new QLineEdit( QString("1.2"), this );
   mpGammaLayout = new QHBoxLayout;
   mpGammaLayout->addWidget( mpGammaLabel );
   mpGammaLayout->addWidget( mpGammaLineEdit );
   
   mpAlphaFactorLabel = new QLabel( QString("Alpha factor: "), this );
   mpAlphaFactorLineEdit = new QLineEdit( QString("0.5"), this );
   mpAlphaFactorLayout = new QHBoxLayout;
   mpAlphaFactorLayout->addWidget( mpAlphaFactorLabel );
   mpAlphaFactorLayout->addWidget( mpAlphaFactorLineEdit );
   
   mpWindowSizeLabel = new QLabel( QString("Window Size: "), this );
   mpWindowSizeGammaLineEdit = new QLineEdit( QString("5"), this );
   mpWindowSizeGammaLayout = new QHBoxLayout;
   mpWindowSizeGammaLayout->addWidget( mpWindowSizeLabel );
   mpWindowSizeGammaLayout->addWidget( mpWindowSizeGammaLineEdit );
   
   mpFractionGroupBox = new QGroupBox(tr("Contrast enhancement method"));
   mpImageNegativeRadioButton              = new QRadioButton(tr("&Image Negative"));
   mpGammaRescaleRadioButton               = new QRadioButton(tr("&Apply Gamma"));
   mpLinearRescaleRadioButton              = new QRadioButton(tr("&Robust Linear Rescale"));
   mpDarkChannelHazeRemovalRadioButton     = new QRadioButton(tr("&Dark Channel Prior based Haze Removal"));
   mpRetinexRadioButton                    = new QRadioButton(tr("&Retinex (MSRCR)"));
   mpHistogramEqualizeRGBRadioButton       = new QRadioButton(tr("&Histogram Equalization (CIE Lab)"));
   mpHistogramEqualizePerBandRadioButton   = new QRadioButton(tr("&Histogram Equalization (per band)"));
   mpAdaptiveHistogramEqualizerRadioButton = new QRadioButton(tr("&Adaptive Histogram Equalization"));
   mpWaveletBasedRadioButton               = new QRadioButton(tr("&Murtagh Curvelet based"));
   mpAdaptiveLuongBasedRadioButton         = new QRadioButton(tr("&Adaptive Luong"));
   mpRadioButtonLayout = new QVBoxLayout;
   mpLinearRescaleRadioButton->setChecked(true);
   SlotShowFraction();
   mpRadioButtonLayout->addWidget( mpImageNegativeRadioButton );
   mpRadioButtonLayout->addWidget( mpGammaRescaleRadioButton );
   mpRadioButtonLayout->addWidget( mpLinearRescaleRadioButton );
   mpRadioButtonLayout->addWidget( mpDarkChannelHazeRemovalRadioButton );
   mpRadioButtonLayout->addWidget( mpRetinexRadioButton );
   mpRadioButtonLayout->addWidget( mpHistogramEqualizeRGBRadioButton );
   mpRadioButtonLayout->addWidget( mpHistogramEqualizePerBandRadioButton );
   mpRadioButtonLayout->addWidget( mpAdaptiveHistogramEqualizerRadioButton );
   mpRadioButtonLayout->addWidget( mpWaveletBasedRadioButton );
   mpRadioButtonLayout->addWidget( mpAdaptiveLuongBasedRadioButton );
   mpFractionGroupBox->setLayout( mpRadioButtonLayout );

   mpDialogLayout->addWidget( mpTitelLabel );
   mpDialogLayout->addWidget( mpFractionGroupBox );
   mpDialogLayout->addLayout( mpLowerFractionLayout );
   mpDialogLayout->addLayout( mpUpperFractionLayout );
   mpDialogLayout->addLayout( mpGammaLayout );
   mpDialogLayout->addLayout( mpAlphaFactorLayout );
   mpDialogLayout->addLayout( mpWindowSizeGammaLayout );
   mpDialogLayout->addLayout( mpButtonLayout );
   
   connect( mpImageNegativeRadioButton,            SIGNAL( clicked() ), this, SLOT( SlotHideEdits() ) );
   connect( mpGammaRescaleRadioButton,             SIGNAL( clicked() ), this, SLOT( SlotShowGamma() ) );
   connect( mpLinearRescaleRadioButton,            SIGNAL( clicked() ), this, SLOT( SlotShowFraction() ) );
   connect( mpDarkChannelHazeRemovalRadioButton,   SIGNAL( clicked() ), this, SLOT( SlotShowFraction() ) );
   connect( mpRetinexRadioButton,                  SIGNAL( clicked() ), this, SLOT( SlotShowFraction() ) );
   connect( mpHistogramEqualizeRGBRadioButton,     SIGNAL( clicked() ), this, SLOT( SlotHideEdits() ) );
   connect( mpHistogramEqualizePerBandRadioButton, SIGNAL( clicked() ), this, SLOT( SlotHideEdits() ) );
   connect( mpWaveletBasedRadioButton,             SIGNAL( clicked() ), this, SLOT( SlotHideEdits() ) );
   connect( mpAdaptiveLuongBasedRadioButton,       SIGNAL( clicked() ), this, SLOT( SlotShowAdaptiveLuong() ) );
   
   this->show();
}

//--------------------------------------------------------

ContrastEnhanceDialog::~ContrastEnhanceDialog()
{
   if (mpProcess != 0)
   {
      delete mpProcess;
   }
}

//--------------------------------------------------------

void ContrastEnhanceDialog::SlotShowGamma()
{
   mpLowerFractionLabel->hide();
   mpLowerFractionLineEdit->hide();
   
   mpUpperFractionLabel->hide();
   mpUpperFractionLineEdit->hide();
   
   mpAlphaFactorLabel->hide();
   mpAlphaFactorLineEdit->hide();
   
   mpWindowSizeLabel->hide();
   mpWindowSizeGammaLineEdit->hide(); 
   
   mpGammaLabel->show();
   mpGammaLineEdit->show();
}

//--------------------------------------------------------

void ContrastEnhanceDialog::SlotShowFraction()
{
   mpLowerFractionLabel->show();
   mpLowerFractionLineEdit->show();
   
   mpUpperFractionLabel->show();
   mpUpperFractionLineEdit->show();
   
   mpAlphaFactorLabel->hide();
   mpAlphaFactorLineEdit->hide();
   
   mpWindowSizeLabel->hide();
   mpWindowSizeGammaLineEdit->hide(); 
   
   mpGammaLabel->hide();
   mpGammaLineEdit->hide();
}

//--------------------------------------------------------

void ContrastEnhanceDialog::SlotHideEdits()
{
   mpLowerFractionLabel->hide();
   mpLowerFractionLineEdit->hide();
   
   mpUpperFractionLabel->hide();
   mpUpperFractionLineEdit->hide();
   
   mpAlphaFactorLabel->hide();
   mpAlphaFactorLineEdit->hide();
   
   mpWindowSizeLabel->hide();
   mpWindowSizeGammaLineEdit->hide(); 
   
   mpGammaLabel->hide();
   mpGammaLineEdit->hide();
}

//--------------------------------------------------------

void ContrastEnhanceDialog::SlotShowAdaptiveLuong()
{
   mpLowerFractionLabel->hide();
   mpLowerFractionLineEdit->hide();
   
   mpUpperFractionLabel->hide();
   mpUpperFractionLineEdit->hide();
   
   mpAlphaFactorLabel->show();
   mpAlphaFactorLineEdit->show();
   
   mpWindowSizeLabel->show();
   mpWindowSizeGammaLineEdit->show();
   
   mpGammaLabel->hide();
   mpGammaLineEdit->hide();
}

//--------------------------------------------------------

double ContrastEnhanceDialog::GetLowerFraction()
{
   return mpLowerFractionLineEdit->text().toDouble();
}

//--------------------------------------------------------

double ContrastEnhanceDialog::GetGamma()
{
   return mpGammaLineEdit->text().toDouble();
}

//--------------------------------------------------------

double ContrastEnhanceDialog::GetUpperFraction()
{
   return mpUpperFractionLineEdit->text().toDouble();
}

//--------------------------------------------------------

int ContrastEnhanceDialog::GetWindowSize()
{
   return mpWindowSizeGammaLineEdit->text().toInt();
}

//--------------------------------------------------------

double ContrastEnhanceDialog::GetAlphaFactor()
{
   return mpAlphaFactorLineEdit->text().toDouble();
}

//--------------------------------------------------------

StiraDefinitions::ContrastEnhanceType ContrastEnhanceDialog::GetEnhanceType()
{
   if (mpImageNegativeRadioButton->isChecked ( ) )
   {
      return StiraDefinitions::CONTRAST_NEGATIVE;
   }
   else if (mpGammaRescaleRadioButton->isChecked ( ) )
   {
      return StiraDefinitions::CONTRAST_GAMMA;
   }
   else if (mpRetinexRadioButton->isChecked ( ) )
   {
      return StiraDefinitions::CONTRAST_RETINEX;
   }
   else if (mpLinearRescaleRadioButton->isChecked ( ) )
   {
      return StiraDefinitions::CONTRAST_LINEARSCALE;
   }
   else if (mpDarkChannelHazeRemovalRadioButton->isChecked ( ) )
   {
      return StiraDefinitions::CONTRAST_DARKCHANNEL;
   }
   else if (mpWaveletBasedRadioButton->isChecked ( ) )
   {
      return StiraDefinitions::CONTRAST_WAVELET;
   }
   else if (mpHistogramEqualizeRGBRadioButton->isChecked ( ) )
   {
      return StiraDefinitions::CONTRAST_HISTOGRAM_EQUALIZE_RGB;
   }
   else if (mpAdaptiveHistogramEqualizerRadioButton->isChecked ( ) )
   {
      return StiraDefinitions::CONTRAST_HISTOGRAM_ADAPTIVE;
   }
   else if (mpAdaptiveLuongBasedRadioButton->isChecked ( ) )
   {
      return StiraDefinitions::CONTRAST_ADAPTIVE_LUONG;
   }
   else //if (mpHistogramEqualizePerBandRadioButton->isChecked ( ) )
   {
      return StiraDefinitions::CONTRAST_HISTOGRAM_EQUALIZE_PERBAND;
   }
}

//--------------------------------------------------------
   
void ContrastEnhanceDialog::SlotRun()
{
   mpProcess = new ContrastEnhanceProcess( mpInputImage );
   connect( mpProcess, SIGNAL( finished() ), this, SLOT( SlotProcessResult() ) );
   mpProcess->SetLowerFraction( this->GetLowerFraction() );
   mpProcess->SetUpperFraction( this->GetUpperFraction() );
   mpProcess->SetGamma( this->GetGamma() );
   mpProcess->SetWindowSize( this->GetWindowSize() );
   mpProcess->SetAlphaFactor( this->GetAlphaFactor() );
   mpProcess->SetContrastEnhanceType( this->GetEnhanceType() );
   mpProcess->start();
}

//--------------------------------------------------------

Process* ContrastEnhanceDialog::GetProcess()
{
   return mpProcess;
}

//--------------------------------------------------------
