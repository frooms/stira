
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

#include "GenerateImageDialog.h"
#include "../src/MainWindow.h"
#include "../processes/GenerateImageProcess.h"

using namespace std;

GenerateImageDialog::GenerateImageDialog( ) : DialogMaster()
{
   mpProcess = 0;
   mpTitelLabel->setText( QString("<b>Generate Synthetic Test Image</b>") );

   mpImageWidthLabel = new QLabel( QString("width: "), this );
   mpImageWidthLineEdit = new QLineEdit( QString("256"), this );
   
   mpImageHeightLabel = new QLabel( QString("height: "), this );
   mpImageHeightLineEdit = new QLineEdit( QString("256"), this );

   mpImageSizeLayout = new QHBoxLayout;
   mpImageSizeLayout->addWidget( mpImageWidthLabel );
   mpImageSizeLayout->addWidget( mpImageWidthLineEdit );
   
   mpImageSizeLayout->addWidget( mpImageHeightLabel );
   mpImageSizeLayout->addWidget( mpImageHeightLineEdit );
   
   
   mpFrequencyLabel = new QLabel( QString("frequency: "), this );
   mpFrequencyLineEdit = new QLineEdit( QString("3"), this );
   
   mpMaxSigmaLabel = new QLabel( QString("Max. sigma: "), this );
   mpMaxSigmaLineEdit = new QLineEdit( QString("17"), this );
   
   mpImageParametersLayout = new QHBoxLayout;
   
   mpImageParametersLayout->addWidget( mpFrequencyLabel );
   mpImageParametersLayout->addWidget( mpFrequencyLineEdit );
   
   mpImageParametersLayout->addWidget( mpMaxSigmaLabel );
   mpImageParametersLayout->addWidget( mpMaxSigmaLineEdit );
   
   mpImageTypeGroupBox = new QGroupBox(tr("Image types"));
   
   mpEmptyImageRadioButton            = new QRadioButton(tr("&Empty Image"));
   mpEmptyPlusNoiseImageRadioButton   = new QRadioButton(tr("&Empty Image plus Gaussian noise"));
   mpHorizontalGradientRadioButton    = new QRadioButton(tr("&Horizontal Gradient"));
   mpVerticalGradientRadioButton      = new QRadioButton(tr("&Vertical Gradient"));
   mpHorizontalSineWaveRadioButton    = new QRadioButton(tr("&Horizontal Sine Wave"));
   mpVerticalSineWaveRadioButton      = new QRadioButton(tr("&Vertical Sine Wave"));
   mpEuclideanSpotRadioButton         = new QRadioButton(tr("&Euclidean Spots"));
   mpBlurredBarsRadioButton           = new QRadioButton(tr("&Blurred Bars"));
   mpInverseZonePlateRadioButton      = new QRadioButton(tr("&Inverse Zoneplate"));
   mpZonePlateRadioButton             = new QRadioButton(tr("&Zoneplate"));
   mpStarChartRadioButton             = new QRadioButton(tr("&Star Chart"));
   mpLogFrequencyContrastRadioButton  = new QRadioButton(tr("&LogFrequencyContrast"));
   mpSheppLoganRadioButton            = new QRadioButton(tr("&Shepp-Logan Phantom"));
   mpIsingRadioButton                 = new QRadioButton(tr("&Ising Random Texture"));
   mpGretaMacbethRadioButton          = new QRadioButton(tr("Gretag-Macbeth Color Checker"));
   mpHorizontalGradientRadioButton->setChecked(true);
   mpRadioButtonLayout = new QVBoxLayout;
   
   mpRadioButtonLayout->addWidget( mpEmptyImageRadioButton );
   mpRadioButtonLayout->addWidget( mpEmptyPlusNoiseImageRadioButton );
   mpRadioButtonLayout->addWidget( mpHorizontalGradientRadioButton );
   mpRadioButtonLayout->addWidget( mpVerticalGradientRadioButton );
   mpRadioButtonLayout->addWidget( mpHorizontalSineWaveRadioButton );
   mpRadioButtonLayout->addWidget( mpVerticalSineWaveRadioButton );
   mpRadioButtonLayout->addWidget( mpEuclideanSpotRadioButton );
   mpRadioButtonLayout->addWidget( mpBlurredBarsRadioButton );
   mpRadioButtonLayout->addWidget( mpInverseZonePlateRadioButton );
   mpRadioButtonLayout->addWidget( mpZonePlateRadioButton );
   mpRadioButtonLayout->addWidget( mpStarChartRadioButton );
   mpRadioButtonLayout->addWidget( mpLogFrequencyContrastRadioButton );
   mpRadioButtonLayout->addWidget( mpSheppLoganRadioButton );
   mpRadioButtonLayout->addWidget( mpGretaMacbethRadioButton );
   mpRadioButtonLayout->addWidget( mpIsingRadioButton );
   mpImageTypeGroupBox->setLayout( mpRadioButtonLayout );
   
   mpDialogLayout->addWidget( mpTitelLabel );
   mpDialogLayout->addLayout( mpImageSizeLayout );
   mpDialogLayout->addLayout( mpImageParametersLayout );
   mpDialogLayout->addWidget( mpImageTypeGroupBox );
   mpDialogLayout->addWidget( mpMessageLabel );
   mpDialogLayout->addLayout( mpButtonLayout );
   
   connect( mpEmptyImageRadioButton,           SIGNAL( clicked() ), this, SLOT( SlotHideAll() ) );
   connect( mpEmptyPlusNoiseImageRadioButton,  SIGNAL( clicked() ), this, SLOT( SlotShowSigma() ) );
   connect( mpHorizontalGradientRadioButton,   SIGNAL( clicked() ), this, SLOT( SlotHideAll() ) );
   connect( mpVerticalGradientRadioButton,     SIGNAL( clicked() ), this, SLOT( SlotHideAll() ) );
   connect( mpHorizontalSineWaveRadioButton,   SIGNAL( clicked() ), this, SLOT( SlotShowFrequency() ) );
   connect( mpVerticalSineWaveRadioButton,     SIGNAL( clicked() ), this, SLOT( SlotShowFrequency() ) );
   connect( mpBlurredBarsRadioButton,          SIGNAL( clicked() ), this, SLOT( SlotShowSigmaAndFrequency() ) );
   connect( mpEuclideanSpotRadioButton,        SIGNAL( clicked() ), this, SLOT( SlotShowFrequency() ) );
   connect( mpInverseZonePlateRadioButton,     SIGNAL( clicked() ), this, SLOT( SlotHideAll() ) );
   connect( mpZonePlateRadioButton,            SIGNAL( clicked() ), this, SLOT( SlotHideAll() ) );
   connect( mpStarChartRadioButton,            SIGNAL( clicked() ), this, SLOT( SlotShowFrequency() ) );
   connect( mpLogFrequencyContrastRadioButton, SIGNAL( clicked() ), this, SLOT( SlotHideAll() ) );
   connect( mpSheppLoganRadioButton,           SIGNAL( clicked() ), this, SLOT( SlotHideAll() ) );
   connect( mpIsingRadioButton,                SIGNAL( clicked() ), this, SLOT( SlotHideAll() ) );
   connect( mpGretaMacbethRadioButton,         SIGNAL( clicked() ), this, SLOT( SlotHideAll() ) );
   
   this->show();
}

//--------------------------------------------------------

GenerateImageDialog::~GenerateImageDialog()
{
   if (mpProcess != 0)
   {
      delete mpProcess;
   }
}

//--------------------------------------------------------

void GenerateImageDialog::SlotHideAll()
{
   mpFrequencyLabel->hide();
   mpFrequencyLineEdit->hide();
   
   mpMaxSigmaLabel->hide();
   mpMaxSigmaLineEdit->hide();
}

//--------------------------------------------------------

void GenerateImageDialog::SlotShowSigma()
{
   mpFrequencyLabel->hide();
   mpFrequencyLineEdit->hide();
   
   mpMaxSigmaLabel->show();
   mpMaxSigmaLineEdit->show();
}

//--------------------------------------------------------

void GenerateImageDialog::SlotShowFrequency()
{
   mpFrequencyLabel->show();
   mpFrequencyLineEdit->show();
   
   mpMaxSigmaLabel->hide();
   mpMaxSigmaLineEdit->hide();
}

//--------------------------------------------------------

void GenerateImageDialog::SlotShowSigmaAndFrequency()
{
   mpImageWidthLineEdit->setText( QString("512") );
   mpImageHeightLineEdit->setText( QString("512") );
   
   mpFrequencyLineEdit->setText( QString("50") );
   mpMaxSigmaLineEdit->setText( QString("15") );
   
   mpFrequencyLabel->show();
   mpFrequencyLineEdit->show();
   
   mpMaxSigmaLabel->show();
   mpMaxSigmaLineEdit->show();
}

//--------------------------------------------------------

void GenerateImageDialog::SlotRun()
{
   mpProcess = new GenerateImageProcess( );
   connect( mpProcess, SIGNAL( finished() ), this, SLOT( SlotProcessResult() ) );
   mpProcess->SetWidth( this->GetWidth() );
   mpProcess->SetHeight( this->GetHeight() );
   mpProcess->SetFrequency( this->GetFrequency() );
   mpProcess->SetMaxSigma( this->GetMaxSigma() );
   mpProcess->SetType( this->GetType() );
   mpProcess->start();
}

//--------------------------------------------------------

int GenerateImageDialog::GetWidth()
{
   return mpImageWidthLineEdit->text().toInt();
}

//--------------------------------------------------------

int GenerateImageDialog::GetHeight()
{
   return mpImageHeightLineEdit->text().toInt();
}

//--------------------------------------------------------

double GenerateImageDialog::GetFrequency()
{
   return mpFrequencyLineEdit->text().toDouble();
}

//--------------------------------------------------------

double GenerateImageDialog::GetMaxSigma()
{
   return mpMaxSigmaLineEdit->text().toDouble();
}

//--------------------------------------------------------

StiraDefinitions::SyntheticImageType GenerateImageDialog::GetType()
{
   if ( mpEmptyPlusNoiseImageRadioButton->isChecked ( ) ) { return StiraDefinitions::SYNTHETIC_EMPTYPLUSNOISE; }
   if ( mpEmptyImageRadioButton->isChecked ( ) ) { return StiraDefinitions::SYNTHETIC_EMPTY; }
   if ( mpHorizontalGradientRadioButton->isChecked ( ) ) { return StiraDefinitions::SYNTHETIC_HORIZONTALGRADIENT; }
   if ( mpVerticalGradientRadioButton->isChecked ( ) ) { return StiraDefinitions::SYNTHETIC_VERTICALGRADIENT; }
   if ( mpHorizontalSineWaveRadioButton->isChecked ( ) ) { return StiraDefinitions::SYNTHETIC_HORIZONTALSINE; }
   if ( mpVerticalSineWaveRadioButton->isChecked ( ) ) { return StiraDefinitions::SYNTHETIC_VERTICALSINE; }
   if ( mpEuclideanSpotRadioButton->isChecked ( ) ) { return StiraDefinitions::SYNTHETIC_EUCLIDEANSPOTS; }
   if ( mpBlurredBarsRadioButton->isChecked ( ) ) { return StiraDefinitions::SYNTHETIC_BLURREDBARS; }
   if ( mpInverseZonePlateRadioButton->isChecked ( ) ) { return StiraDefinitions::SYNTHETIC_INVERSEZONEPLATE; }
   if ( mpZonePlateRadioButton->isChecked ( ) ) { return StiraDefinitions::SYNTHETIC_ZONEPLATE; }
   if ( mpStarChartRadioButton->isChecked ( ) ) { return StiraDefinitions::SYNTHETIC_STARCHART; }
   if ( mpLogFrequencyContrastRadioButton->isChecked ( ) ) { return StiraDefinitions::SYNTHETIC_LOGFREQUENCYCONTRAST; }
   if ( mpSheppLoganRadioButton->isChecked ( ) ) { return StiraDefinitions::SYNTHETIC_SHEPPLOGAN; }
   if ( mpIsingRadioButton->isChecked ( ) ) { return StiraDefinitions::SYNTHETIC_ISING; }
   if ( mpGretaMacbethRadioButton->isChecked ( ) ) { return StiraDefinitions::SYNTHETIC_GRETAGMACBETH; }
   return StiraDefinitions::SYNTHETIC_HORIZONTALGRADIENT;
}

//--------------------------------------------------------

Process* GenerateImageDialog::GetProcess()
{
   return mpProcess;
}

//--------------------------------------------------------
