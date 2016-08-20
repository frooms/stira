
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

#include "SimulateNoiseDialog.h"
#include "../src/MainWindow.h"
#include "../processes/SimulateNoiseProcess.h"

using namespace std;
using namespace stira::imagedata;
using namespace stira::imagetools;

SimulateNoiseDialog::SimulateNoiseDialog( Image* pImage ) : DialogMaster( pImage )
{
   mpProcess = 0;
   mpTitelLabel->setText( QString("<b>Generate Synthetic Test Image</b>") );
   
   mpNoiseLevelLabel = new QLabel( QString("Noise Level:"), this );
   mpNoiseLevelLineEdit = new QLineEdit( QString("10.0"), this );
   mpNoiseLevelLayout = new QHBoxLayout;
   mpNoiseLevelLayout->addWidget( mpNoiseLevelLabel );
   mpNoiseLevelLayout->addWidget( mpNoiseLevelLineEdit );
   
   mpNoiseTypeGroupBox = new QGroupBox(tr("Noise types"));
   
   mpGaussianNoiseRadioButton = new QRadioButton(tr("&Gaussian Noise"));
   mpPoissonNoiseRadioButton  = new QRadioButton(tr("&Poisson Noise"));
   mpImpulseNoiseRadioButton  = new QRadioButton(tr("&Impulse Noise"));
   mpRadioButtonLayout = new QVBoxLayout;
   mpRadioButtonLayout->addWidget( mpGaussianNoiseRadioButton );
   mpRadioButtonLayout->addWidget( mpPoissonNoiseRadioButton );
   mpRadioButtonLayout->addWidget( mpImpulseNoiseRadioButton );
   
   connect( mpGaussianNoiseRadioButton, SIGNAL( clicked() ), this, SLOT( SlotSetDefaultGaussianLevel() ) );
   connect( mpPoissonNoiseRadioButton,  SIGNAL( clicked() ), this, SLOT( SlotSetDefaultPoissonLevel() ) );
   connect( mpImpulseNoiseRadioButton,  SIGNAL( clicked() ), this, SLOT( SlotSetDefaultImpulseLevel() ) );
   
   mpNoiseTypeGroupBox->setLayout( mpRadioButtonLayout );
   mpGaussianNoiseRadioButton->setChecked(true);

   mpNoiseIsColoredCheckBox = new QCheckBox( tr( "&Apply Colored Noise?" ) );
   mpNoiseIsColoredCheckBox->setChecked ( true );
   mpDialogLayout->addWidget( mpTitelLabel );
   mpDialogLayout->addLayout( mpNoiseLevelLayout );
   mpDialogLayout->addWidget( mpNoiseTypeGroupBox );
   mpDialogLayout->addWidget( mpNoiseIsColoredCheckBox );
   mpDialogLayout->addWidget( mpMessageLabel );
   mpDialogLayout->addLayout( mpButtonLayout );
   this->show();
}

//--------------------------------------------------------

SimulateNoiseDialog::~SimulateNoiseDialog()
{
   if (mpProcess != 0)
   {
      delete mpProcess;
   }
}

//--------------------------------------------------------

void SimulateNoiseDialog::SlotRun()
{
   mpProcess = new SimulateNoiseProcess( mpInputImage );
   connect( mpProcess, SIGNAL( finished() ), this, SLOT( SlotProcessResult() ) );
   mpProcess->SetNoiseType( this->GetNoiseType() );
   mpProcess->SetNoiseLevel( this->GetNoiseLevel() );
   mpProcess->SetUseColoredNoise( this->GetUseColoredNoise() );
   mpProcess->start();
}

//--------------------------------------------------------

double SimulateNoiseDialog::GetNoiseLevel()
{
   return mpNoiseLevelLineEdit->text().toDouble();
}

//--------------------------------------------------------

void SimulateNoiseDialog::SlotSetDefaultGaussianLevel()
{
   mpNoiseLevelLineEdit->setText( QString("10.0") );
}

//--------------------------------------------------------

void SimulateNoiseDialog::SlotSetDefaultPoissonLevel()
{
   mpNoiseLevelLineEdit->setText( QString("12.5") );
}

//--------------------------------------------------------

void SimulateNoiseDialog::SlotSetDefaultImpulseLevel()
{
   mpNoiseLevelLineEdit->setText( QString("0.1") );
}

//--------------------------------------------------------

StiraDefinitions::NoiseType SimulateNoiseDialog::GetNoiseType()
{
   if ( mpGaussianNoiseRadioButton->isChecked ( ) ) { return StiraDefinitions::NOISE_GAUSSIAN; }
   if ( mpPoissonNoiseRadioButton->isChecked ( ) ) { return StiraDefinitions::NOISE_POISSON; }
   if ( mpImpulseNoiseRadioButton->isChecked ( ) ) { return StiraDefinitions::NOISE_IMPULSE; }
   return StiraDefinitions::NOISE_GAUSSIAN;
}

//--------------------------------------------------------

bool SimulateNoiseDialog::GetUseColoredNoise()
{
   return mpNoiseIsColoredCheckBox->isChecked();
}

//--------------------------------------------------------

Process* SimulateNoiseDialog::GetProcess()
{
   return mpProcess;
}

//--------------------------------------------------------
