
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
 
#include "WienerDeconvolveDialog.h"
#include "../src/MainWindow.h"
#include "../processes/WienerDeconvolveProcess.h"

using namespace stira::imagedata;
using namespace stira::imagetools;

WienerDeconvolveDialog::WienerDeconvolveDialog( Image* pImage ) : DialogMaster( pImage )
{
   mpProcess = 0;
   
   mpTitelLabel->setText( QString("<b>Wiener Deconvolution Parameters</b>") );
   
   mpNoiseLevelLabel = new QLabel( QString("Noise level (sigma): "), this );
   mpNoiseLevelLineEdit = new QLineEdit( QString("5.0"), this );

   mpNoiseLevelLayout = new QHBoxLayout;
   mpNoiseLevelLayout->addWidget( mpNoiseLevelLabel );
   mpNoiseLevelLayout->addWidget( mpNoiseLevelLineEdit );
   
   mpBlurLevelLabel = new QLabel( QString("Blur level: "), this );
   mpBlurLevelLineEdit = new QLineEdit( QString("1.5"), this );
   
   mpBlurLevelLayout = new QHBoxLayout;
   mpBlurLevelLayout->addWidget( mpBlurLevelLabel );
   mpBlurLevelLayout->addWidget( mpBlurLevelLineEdit );
    
   mpDialogLayout->addWidget( mpTitelLabel );
   mpDialogLayout->addLayout( mpNoiseLevelLayout );
   mpDialogLayout->addLayout( mpBlurLevelLayout );
   mpDialogLayout->addWidget( mpMessageLabel );
   mpDialogLayout->addLayout( mpButtonLayout );
   this->show();
}

//------------------------------------------------------------------

WienerDeconvolveDialog::~WienerDeconvolveDialog()
{
   if (mpProcess != 0)
   {
      delete mpProcess;
   }
}

//------------------------------------------------------------------

double WienerDeconvolveDialog::GetNoiseLevel()
{
   return mpNoiseLevelLineEdit->text().toDouble();
}

//------------------------------------------------------------------

double WienerDeconvolveDialog::GetBlurLevel()
{
   return mpBlurLevelLineEdit->text().toDouble();
}

//------------------------------------------------------------------

void WienerDeconvolveDialog::SlotRun()
{
   mpProcess = new WienerDeconvolveProcess( mpInputImage );
   connect( mpProcess, SIGNAL( finished() ), this, SLOT( SlotProcessResult() ) );
   mpProcess->SetNoiseLevel( this->GetNoiseLevel() );
   mpProcess->SetBlurLevel( this->GetBlurLevel() );
   mpProcess->start();
}

//--------------------------------------------------------

Process* WienerDeconvolveDialog::GetProcess()
{
   return mpProcess;
}

//------------------------------------------------------------------
