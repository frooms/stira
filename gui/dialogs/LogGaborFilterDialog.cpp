
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

#include "LogGaborFilterDialog.h"
#include "../src/MainWindow.h"
#include "../processes/LogGaborFilterProcess.h"

using namespace std;
using namespace stira::imagedata;
using namespace stira::imagetools;

LogGaborFilterDialog::LogGaborFilterDialog( Image* pImage ) : DialogMaster( pImage )
{
   mpProcess = 0;
   mpTitelLabel->setText( QString("<B>Log-Gabor Filter Dialog</B>") );
   
   // Create widget layouts
   ////////////////////////
   mpLabelsLayout = new QVBoxLayout;
   mpLineEditsLayout = new QVBoxLayout;
   mpParametersLayout = new QHBoxLayout;
   mpOutputsLayout = new QVBoxLayout;
   
   // Create Labels + Line edits to enter parameters, and add them to their layouts
   ////////////////////////////////////////////////////////////////////////////////
   mpCenterFrequencyLabel = new QLabel( QString("Center Frequency factor: "), this );
   mpCenterFrequencyLineEdit = new QLineEdit( QString("5.0"), this );
   mpLabelsLayout->addWidget( mpCenterFrequencyLabel );
   mpLineEditsLayout->addWidget( mpCenterFrequencyLineEdit );

   mpRadialWidthLabel = new QLabel( QString("Frequency Radial Width: "), this );
   mpRadialWidthLineEdit = new QLineEdit( QString("1.25"), this );
   mpLabelsLayout->addWidget( mpRadialWidthLabel );
   mpLineEditsLayout->addWidget( mpRadialWidthLineEdit );

   mpCenterAngleLabel = new QLabel( QString("Central Angle: "), this );
   mpCenterAngleLineEdit = new QLineEdit( QString("1.570796"), this );
   mpLabelsLayout->addWidget( mpCenterAngleLabel );
   mpLineEditsLayout->addWidget( mpCenterAngleLineEdit );

   mpAngleSpreadLabel = new QLabel( QString("Angle Spread Width: "), this );
   mpAngleSpreadLineEdit = new QLineEdit( QString("0.3"), this );
   mpLabelsLayout->addWidget( mpAngleSpreadLabel );
   mpLineEditsLayout->addWidget( mpAngleSpreadLineEdit );

   mpParametersLayout->addLayout( mpLabelsLayout );
   mpParametersLayout->addLayout( mpLineEditsLayout );

   // Create Checkboxes to specify which output to create
   //////////////////////////////////////////////////////
   mpCreateRealResponseCheckBox = new QCheckBox( tr( "&Create Real Response?" ) );
   mpCreateRealResponseCheckBox->setChecked ( true );
   mpOutputsLayout->addWidget( mpCreateRealResponseCheckBox );

   mpCreateImagResponseCheckBox = new QCheckBox( tr( "&Create Imaginary Response?" ) );
   mpCreateImagResponseCheckBox->setChecked ( true );

   mpCreateMagnitudeResponseCheckBox = new QCheckBox( tr( "&Create Magnitude Image?" ) );
   mpCreateMagnitudeResponseCheckBox->setChecked ( false );

   mpCreateTransferResponseCheckBox = new QCheckBox( tr( "&Create Transfer Function?" ) );
   mpCreateTransferResponseCheckBox->setChecked ( false );

   mpOutputsLayout->addWidget( mpCreateImagResponseCheckBox );
   mpOutputsLayout->addWidget( mpCreateMagnitudeResponseCheckBox );
   mpOutputsLayout->addWidget( mpCreateTransferResponseCheckBox );
   
   mpDialogLayout->addWidget( mpTitelLabel );
   
   mpDialogLayout->addLayout( mpParametersLayout );
   mpDialogLayout->addLayout( mpOutputsLayout );
   mpDialogLayout->addWidget( mpMessageLabel );
   mpDialogLayout->addLayout( mpButtonLayout );
   this->show();
}

//--------------------------------------------------------

LogGaborFilterDialog::~LogGaborFilterDialog()
{
   if (mpProcess != 0)
   {
      delete mpProcess;
   }
}

//--------------------------------------------------------

void LogGaborFilterDialog::SlotRun()
{
   mpProcess = new LogGaborFilterProcess( mpInputImage );
   connect( mpProcess, SIGNAL( finished() ), this, SLOT( SlotProcessResult() ) );
   
   mpProcess->SetCenterFrequency( this->GetCenterFrequency() );
   mpProcess->SetRadialWidth( this->GetRadialWidth() );
   mpProcess->SetCenterAngle( this->GetCenterAngle( ) );
   mpProcess->SetAngleSpread( this->GetAngleSpread() );

   mpProcess->SetCreateRealResponse( mpCreateRealResponseCheckBox->isChecked() );
   mpProcess->SetCreateImagResponse( mpCreateImagResponseCheckBox->isChecked() );
   mpProcess->SetCreateMagnitude( mpCreateMagnitudeResponseCheckBox->isChecked() );
   mpProcess->SetCreateTransferResponse( mpCreateTransferResponseCheckBox->isChecked() );

   mpProcess->start();
}

//--------------------------------------------------------

double LogGaborFilterDialog::GetCenterFrequency()
{
   return mpCenterFrequencyLineEdit->text().toDouble();
}

//--------------------------------------------------------

double LogGaborFilterDialog::GetRadialWidth()
{
   return mpRadialWidthLineEdit->text().toDouble();
}

//--------------------------------------------------------

double LogGaborFilterDialog::GetCenterAngle()
{
   return mpCenterAngleLineEdit->text().toDouble();
}

//--------------------------------------------------------

double LogGaborFilterDialog::GetAngleSpread()
{
   return mpAngleSpreadLineEdit->text().toDouble();
}

//--------------------------------------------------------

Process* LogGaborFilterDialog::GetProcess()
{
   return mpProcess;
}

//--------------------------------------------------------
