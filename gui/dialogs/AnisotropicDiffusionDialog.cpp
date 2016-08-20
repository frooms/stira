
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

#include "AnisotropicDiffusionDialog.h"
#include "../src/MainWindow.h"
#include "../processes/AnisotropicDiffusionProcess.h"
using namespace std;

AnisotropicDiffusionDialog::AnisotropicDiffusionDialog( stira::imagedata::Image* pImage ) : DialogMaster( pImage )
{
   mpProcess = 0;
   mpTitelLabel->setText( QString("<b>Anisotropic Diffusion Parameters</b>" ) );
   mpNrIterationsLabel = new QLabel( QString("Nr. iterations: "), this );
   mpNrIterationsLineEdit = new QLineEdit( QString("5"), this );
   mpNrIterationsLayout = new QHBoxLayout;
   mpNrIterationsLayout->addWidget( mpNrIterationsLabel );
   mpNrIterationsLayout->addWidget( mpNrIterationsLineEdit );
   
   mpFlowParameterLabel = new QLabel( QString("Flow constant: "), this );
   mpFlowParameterLineEdit = new QLineEdit( QString("0.5"), this );
   mpFlowParameterLayout = new QHBoxLayout;
   mpFlowParameterLayout->addWidget( mpFlowParameterLabel );
   mpFlowParameterLayout->addWidget( mpFlowParameterLineEdit );
    
   mpDialogLayout->addWidget( mpTitelLabel );
   mpDialogLayout->addLayout( mpNrIterationsLayout );
   mpDialogLayout->addLayout( mpFlowParameterLayout );
   mpDialogLayout->addWidget( mpMessageLabel );
   mpDialogLayout->addLayout( mpButtonLayout );
   this->show();
}

//--------------------------------------------------------

AnisotropicDiffusionDialog::~AnisotropicDiffusionDialog()
{
   if (mpProcess != 0)
   {
      delete mpProcess;
   }
}

//--------------------------------------------------------

double AnisotropicDiffusionDialog::GetFlowParameter()
{
   return mpFlowParameterLineEdit->text().toDouble();
}

//--------------------------------------------------------

int AnisotropicDiffusionDialog::GetNrOfIterations()
{
   return mpNrIterationsLineEdit->text().toInt();
}

//--------------------------------------------------------

Process* AnisotropicDiffusionDialog::GetProcess()
{
   return mpProcess;
}

//--------------------------------------------------------

void AnisotropicDiffusionDialog::SlotRun()
{
   double flowFactor =  GetFlowParameter();

   if (flowFactor <= 0.5)
   {
       mpProcess = new AnisotropicDiffusionProcess( mpInputImage );
       connect( mpProcess, SIGNAL( finished() ), this, SLOT( SlotProcessResult() ) );
       mpProcess->SetFlowParameter( this->GetFlowParameter() );
       mpProcess->SetNrOfIterations( this->GetNrOfIterations() );
       mpProcess->start();
   }
   else
   {
        mpMessageLabel->setText( QString("<b>ERROR: Flow constant must be &le; 0.5 !!</b>"));
        this->EnableButtons();
   }
}

//--------------------------------------------------------
