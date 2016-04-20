
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

#include "SplitBregmanDenoiseDialog.h"
#include "../src/MainWindow.h"
#include "../processes/SplitBregmanDenoiseProcess.h"
using namespace std;
using namespace stira::image;

SplitBregmanDenoiseDialog::SplitBregmanDenoiseDialog( stira::image::Image* pImage ) : DialogMaster( pImage )
{
   mpProcess = 0;
   mpTitelLabel->setText( QString("<b>Split-Bregman TV Denoising Parameters</b>") );
   
   mpMuLabel = new QLabel( QString("Mu: "), this );
   mpMuLineEdit = new QLineEdit( QString("0.1"), this );
   mpMuLayout = new QHBoxLayout;
   mpMuLayout->addWidget( mpMuLabel );
   mpMuLayout->addWidget( mpMuLineEdit );
   
   mpLambdaLabel = new QLabel( QString("Lambda: "), this );
   mpLambdaLineEdit = new QLineEdit( QString("0.2"), this );
   mpLambdaLayout = new QHBoxLayout;
   mpLambdaLayout->addWidget( mpLambdaLabel );
   mpLambdaLayout->addWidget( mpLambdaLineEdit );
   
   mpNumberOfGaussSeidelIterationsLabel = new QLabel( QString("Number of Gauss-Seidel iterations: "), this );
   mpNumberOfGaussSeidelIterationsLineEdit = new QLineEdit( QString("1"), this );
   mpNumberOfGaussSeidelIterationsLayout = new QHBoxLayout;
   mpNumberOfGaussSeidelIterationsLayout->addWidget( mpNumberOfGaussSeidelIterationsLabel );
   mpNumberOfGaussSeidelIterationsLayout->addWidget( mpNumberOfGaussSeidelIterationsLineEdit );
   
   mpNumberOfBregmanIterationsLabel = new QLabel( QString("Number of Bregman iterations: "), this );
   mpNumberOfBregmanIterationsLineEdit = new QLineEdit( QString("50"), this );
   mpNumberOfBregmanIterationsLayout = new QHBoxLayout;
   mpNumberOfBregmanIterationsLayout->addWidget( mpNumberOfBregmanIterationsLabel );
   mpNumberOfBregmanIterationsLayout->addWidget( mpNumberOfBregmanIterationsLineEdit );
   
   mpIsIsotropic = new QCheckBox( tr( "&Is Isotropic?" ) );
    
   mpDialogLayout->addWidget( mpTitelLabel );
   mpDialogLayout->addWidget( mpIsIsotropic );
   mpDialogLayout->addLayout( mpMuLayout );
   mpDialogLayout->addLayout( mpLambdaLayout );
   mpDialogLayout->addLayout( mpNumberOfGaussSeidelIterationsLayout );
   mpDialogLayout->addLayout( mpNumberOfBregmanIterationsLayout );
   mpDialogLayout->addWidget( mpMessageLabel );
   mpDialogLayout->addLayout( mpButtonLayout );
   this->show();
}

//--------------------------------------------------------

SplitBregmanDenoiseDialog::~SplitBregmanDenoiseDialog()
{
   if (mpProcess != 0)
   {
      delete mpProcess;
   }
}

double SplitBregmanDenoiseDialog::GetMu()
{
   return mpMuLineEdit->text().toDouble();
}

double SplitBregmanDenoiseDialog::GetLambda()
{
   return mpLambdaLineEdit->text().toDouble();
}

int SplitBregmanDenoiseDialog::GetNumberOfGaussSeidelIterations()
{
   return mpNumberOfGaussSeidelIterationsLineEdit->text().toInt();
}

int SplitBregmanDenoiseDialog::GetNumberOfBregmanIterations()
{
   return mpNumberOfBregmanIterationsLineEdit->text().toInt();
}

bool SplitBregmanDenoiseDialog::GetIsIsotropic()
{
   return mpIsIsotropic->isChecked () ;
}

//--------------------------------------------------------

Process* SplitBregmanDenoiseDialog::GetProcess()
{
   return mpProcess;
}

//--------------------------------------------------------

void SplitBregmanDenoiseDialog::SlotRun()
{
   mpProcess = new SplitBregmanDenoiseProcess( mpInputImage );
   connect( mpProcess, SIGNAL( finished() ), this, SLOT( SlotProcessResult() ) );
   
   mpProcess->SetMu( this->GetMu() );
   mpProcess->SetLambda( this->GetLambda() );
   mpProcess->SetNumberOfGaussSeidelIterations( this->GetNumberOfGaussSeidelIterations() );
   mpProcess->SetNumberOfBregmanIterations( this->GetNumberOfBregmanIterations() );
   mpProcess->SetIsIsotropic( this->GetIsIsotropic() );
   
   mpProcess->start();
}

//--------------------------------------------------------
