
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
#include "SteerableDenoisingDialog.h"
#include "../src/MainWindow.h"
#include "../processes/SteerableDenoisingProcess.h"

using namespace std;
using namespace stira::image;

SteerableDenoisingDialog::SteerableDenoisingDialog( Image* pImage ) : DialogMaster( pImage )
{
   mpProcess = 0;
   mpTitelLabel->setText( QString("Steerable Pyramid based bivariate denoising") );
   mpNrScalesLabel = new QLabel( QString("Nr. scales: "), this );
   mpNrScalesLineEdit = new QLineEdit( QString("4"), this );
   mpNrScalesLayout = new QHBoxLayout;
   mpNrScalesLayout->addWidget( mpNrScalesLabel );
   mpNrScalesLayout->addWidget( mpNrScalesLineEdit );
   
   mpNrOrientationsLabel = new QLabel( QString("Nr. Orientations: "), this );
   mpNrOrientationsLineEdit = new QLineEdit( QString("6"), this );
   mpNrOrientationsLayout = new QHBoxLayout;
   mpNrOrientationsLayout->addWidget( mpNrOrientationsLabel );
   mpNrOrientationsLayout->addWidget( mpNrOrientationsLineEdit );
   
   mpNoiseLevelLabel = new QLabel( QString("Noise Level: "), this );
   mpNoiseLevelLineEdit = new QLineEdit( QString("2.0"), this );
   mpNoiseLevelLayout = new QHBoxLayout;
   mpNoiseLevelLayout->addWidget( mpNoiseLevelLabel );
   mpNoiseLevelLayout->addWidget( mpNoiseLevelLineEdit );
    
   mpDialogLayout->addWidget( mpTitelLabel );
   mpDialogLayout->addLayout( mpNrScalesLayout );
   mpDialogLayout->addLayout( mpNrOrientationsLayout );
   mpDialogLayout->addLayout( mpNoiseLevelLayout );
   mpDialogLayout->addLayout( mpButtonLayout );
   this->show();
}

//--------------------------------------------------------

SteerableDenoisingDialog::~SteerableDenoisingDialog()
{
   if (mpProcess != 0)
   {
      delete mpProcess;
   }
}

//--------------------------------------------------------

void SteerableDenoisingDialog::SlotRun()
{
   mpProcess = new SteerableDenoisingProcess( mpInputImage );
   connect( mpProcess, SIGNAL( finished() ), this, SLOT( SlotProcessResult() ) );
   mpProcess->SetNoiseLevel( mpNoiseLevelLineEdit->text().toDouble() );
   mpProcess->SetNrScales( mpNrScalesLineEdit->text().toInt() );
   mpProcess->SetNrOrientations( mpNrOrientationsLineEdit->text().toInt() );
   mpProcess->start();
}

//--------------------------------------------------------

Process* SteerableDenoisingDialog::GetProcess()
{
   return mpProcess;
}

//--------------------------------------------------------
