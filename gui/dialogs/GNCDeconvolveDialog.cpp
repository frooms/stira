
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

#include "GNCDeconvolveDialog.h"
#include "../src/MainWindow.h"
#include "../processes/GNCDeconvolveProcess.h"

using namespace std;
using namespace stira::imagedata;
using namespace stira::imagetools;

GNCDeconvolveDialog::GNCDeconvolveDialog( Image* pImage ) : DialogMaster( pImage )
{
   mpProcess = 0;
   mpTitelLabel->setText( QString("<B>GNC-based Deconvolution Dialog</B>") );
   
   mpLabelsLayout = new QVBoxLayout;
   mpLineEditsLayout = new QVBoxLayout;
   mpParametersLayout = new QHBoxLayout;
   
   mpBlurLevelLabel = new QLabel( QString("Blur: "), this );
   mpBlurLevelLineEdit = new QLineEdit( QString("1.5"), this );
   mpLabelsLayout->addWidget(mpBlurLevelLabel );
   mpLineEditsLayout->addWidget(mpBlurLevelLineEdit );

   mpNrScalesLabel = new QLabel( QString("Number Of Scales: "), this );
   mpNrScalesLineEdit = new QLineEdit( QString("4"), this );
   mpLabelsLayout->addWidget( mpNrScalesLabel );
   mpLineEditsLayout->addWidget( mpNrScalesLineEdit );

   mpNrOrientationsLabel = new QLabel( QString("Number Of Orientations: "), this );
   mpNrOrientationsLineEdit = new QLineEdit( QString("8"), this );
   mpLabelsLayout->addWidget( mpNrOrientationsLabel );
   mpLineEditsLayout->addWidget( mpNrOrientationsLineEdit );

   mpLambdaLabel = new QLabel( QString("Scale Regularization Factor: "), this );
   mpLambdaLineEdit = new QLineEdit( QString("0.8"), this );
   mpLabelsLayout->addWidget( mpLambdaLabel );
   mpLineEditsLayout->addWidget( mpLambdaLineEdit );

   mpMuLabel = new QLabel( QString("Scale Datafit Factor: "), this );
   mpMuLineEdit = new QLineEdit( QString("0.8"), this );
   mpLabelsLayout->addWidget( mpMuLabel );
   mpLineEditsLayout->addWidget( mpMuLineEdit );

   mpGammaInitLabel = new QLabel( QString("Gamma (initial): "), this );
   mpGammaInitLineEdit = new QLineEdit( QString("4.0"), this );
   mpLabelsLayout->addWidget( mpGammaInitLabel );
   mpLineEditsLayout->addWidget( mpGammaInitLineEdit );

   mpGammaFinalLabel = new QLabel( QString("Gamma (final): "), this );
   mpGammaFinalLineEdit = new QLineEdit( QString("2.0"), this );
   mpLabelsLayout->addWidget( mpGammaFinalLabel );
   mpLineEditsLayout->addWidget( mpGammaFinalLineEdit );

   mpUpdateFactorLabel = new QLabel( QString("Update Factor: "), this );
   mpUpdateFactorLineEdit = new QLineEdit( QString("0.7"), this );
   mpLabelsLayout->addWidget( mpUpdateFactorLabel );
   mpLineEditsLayout->addWidget( mpUpdateFactorLineEdit );
   
   mpNrIterationsLabel = new QLabel( QString("Nr. Iterations: "), this );
   mpNrIterationsLineEdit = new QLineEdit( QString("12"), this );
   mpLabelsLayout->addWidget( mpNrIterationsLabel );
   mpLineEditsLayout->addWidget( mpNrIterationsLineEdit );
   
   mpParametersLayout->addLayout( mpLabelsLayout );
   mpParametersLayout->addLayout( mpLineEditsLayout );
   
   mpDialogLayout->addWidget( mpTitelLabel );
   
   mpDialogLayout->addLayout( mpParametersLayout );
   mpDialogLayout->addWidget( mpMessageLabel );
   mpDialogLayout->addLayout( mpButtonLayout );
   this->show();
}

//--------------------------------------------------------

GNCDeconvolveDialog::~GNCDeconvolveDialog()
{
   if (mpProcess != 0)
   {
      delete mpProcess;
   }
}

//--------------------------------------------------------

void GNCDeconvolveDialog::SlotRun()
{
   mpProcess = new GNCDeconvolveProcess( mpInputImage );
   connect( mpProcess, SIGNAL( finished() ), this, SLOT( SlotProcessResult() ) );
   
   mpProcess->SetBlurLevel( this->GetBlurLevel() );
   mpProcess->SetNrOfScales( this->GetNrOfScales() );
   mpProcess->SetNrOfOrientations( this->GetNrOfOrientations( ) );
   mpProcess->SetLambda( this->GetLambda() );
   mpProcess->SetMu( this->GetMu() );

   mpProcess->SetGammaInitial( this->GetGammaInitial() );
   mpProcess->SetGammaFinal( this->GetGammaFinal() );
   mpProcess->SetUpdateFactor( this->GetUpdateFactor() );
   mpProcess->SetNrOfIterations( this->GetNrOfIterations() );

   mpProcess->start();
}

//--------------------------------------------------------

double GNCDeconvolveDialog::GetBlurLevel()
{
   return mpBlurLevelLineEdit->text().toDouble();
}

//--------------------------------------------------------

int GNCDeconvolveDialog::GetNrOfScales()
{
   return mpNrScalesLineEdit->text().toInt();
}

//--------------------------------------------------------

int GNCDeconvolveDialog::GetNrOfOrientations( )
{
   return mpNrOrientationsLineEdit->text().toInt();
}

//--------------------------------------------------------

double GNCDeconvolveDialog::GetLambda()
{
   return mpLambdaLineEdit->text().toDouble();
}

//--------------------------------------------------------

double GNCDeconvolveDialog::GetMu()
{
   return mpMuLineEdit->text().toDouble();
}

//--------------------------------------------------------

double GNCDeconvolveDialog::GetGammaInitial()
{
   return mpGammaInitLineEdit->text().toDouble();
}

//--------------------------------------------------------

double GNCDeconvolveDialog::GetGammaFinal()
{
   return mpGammaFinalLineEdit ->text().toDouble();
}

//--------------------------------------------------------

double GNCDeconvolveDialog::GetUpdateFactor()
{
   return mpUpdateFactorLineEdit->text().toDouble();
}

//--------------------------------------------------------

int GNCDeconvolveDialog::GetNrOfIterations()
{
   return mpNrIterationsLineEdit->text().toInt();
}

//--------------------------------------------------------

Process* GNCDeconvolveDialog::GetProcess()
{
   return mpProcess;
}

//--------------------------------------------------------
