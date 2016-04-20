
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

#include "RichardsonLucyDeconvolveDialog.h"
#include "../src/MainWindow.h"
#include "../processes/RichardsonLucyDeconvolveProcess.h"

using namespace std;
using namespace stira::image;

RichardsonLucyDeconvolveDialog::RichardsonLucyDeconvolveDialog( Image* pImage ) : DialogMaster( pImage )
{
   mpProcess = 0;
   mpTitelLabel->setText( QString("<b>Richardson-Lucy Deconvolve Dialog</b>") );
   
   SetupParameterLineEdits();
   ///////////////////////////////
   /*mpBlurLevelLabel = new QLabel( QString("Blur: "), this );
   mpBlurLevelLineEdit = new QLineEdit( QString("1.5"), this );
   mpBlurLevelLayout = new QHBoxLayout;
   mpBlurLevelLayout->addWidget(mpBlurLevelLabel );
   mpBlurLevelLayout->addWidget(mpBlurLevelLineEdit );

   mpLambdaLabel = new QLabel( QString("Lambda: "), this );
   mpLambdaLineEdit = new QLineEdit( QString("0.0001"), this );
   mpLambdaLayout = new QHBoxLayout;
   mpLambdaLayout->addWidget( mpLambdaLabel );
   mpLambdaLayout->addWidget( mpLambdaLineEdit );
   
   mpNrIterationsLabel = new QLabel( QString("nr. Iterations: "), this );
   mpNrIterationsLineEdit = new QLineEdit( QString("25"), this );
   mpNrIterationsLayout = new QHBoxLayout;
   mpNrIterationsLayout->addWidget( mpNrIterationsLabel );
   mpNrIterationsLayout->addWidget( mpNrIterationsLineEdit );*/
   
   SetupRegularizationWidgets();
   ///////////////////////////////
   /*mpRegularizationTypeGroupBox = new QGroupBox(tr("Regularization Type"));
   
   mpRegularizeNoneRadioButton           = new QRadioButton(tr("&None"));
   mpRegularizeTikhonovMillerRadioButton = new QRadioButton(tr("&Tikhonov-Miller"));
   mpRegularizeConchelloRadioButton      = new QRadioButton(tr("&Conchello"));
   mpRegularizeMaximumEntropyRadioButton = new QRadioButton(tr("&Maximum Entropy"));
   mpRegularizeTotalVariationRadioButton = new QRadioButton(tr("Total &Variation"));

   connect( mpRegularizeTikhonovMillerRadioButton, SIGNAL( clicked() ), this, SLOT( SlotSetDefaultTikhonovParameter() ) );
   connect( mpRegularizeConchelloRadioButton,      SIGNAL( clicked() ), this, SLOT( SlotSetDefaultConchelloParameter() ) );
   connect( mpRegularizeMaximumEntropyRadioButton, SIGNAL( clicked() ), this, SLOT( SlotSetDefaultMaxEntropyParameter() ) );
   connect( mpRegularizeTotalVariationRadioButton, SIGNAL( clicked() ), this, SLOT( SlotSetDefaultTotalVariationParameter() ) );
   
   mpRegularizeNoneRadioButton->setChecked(true);
   mpRegularizeRadioButtonLayout = new QVBoxLayout;
   
   mpRegularizeRadioButtonLayout->addWidget( mpRegularizeNoneRadioButton );
   mpRegularizeRadioButtonLayout->addWidget( mpRegularizeTikhonovMillerRadioButton );
   mpRegularizeRadioButtonLayout->addWidget( mpRegularizeConchelloRadioButton );
   mpRegularizeRadioButtonLayout->addWidget( mpRegularizeMaximumEntropyRadioButton );
   mpRegularizeRadioButtonLayout->addWidget( mpRegularizeTotalVariationRadioButton );
   mpRegularizationTypeGroupBox->setLayout( mpRegularizeRadioButtonLayout );*/
   
   SetupPSFWidgets();
   //////////////////
   /*mpPSFTypeGroupBox = new QGroupBox(tr("PSF Type"));
   
   mpPSFDiskRadioButton   = new QRadioButton(tr("&Disk"));
   mpPSFSquareRadioButton = new QRadioButton(tr("&Square"));
   mpPSFGaussRadioButton  = new QRadioButton(tr("&Gaussian"));
   mpPSFAiryRadioButton   = new QRadioButton(tr("&Airy"));
   
   mpPSFGaussRadioButton->setChecked(true);
   mpPSFRadioButtonLayout = new QVBoxLayout;
   
   mpPSFRadioButtonLayout->addWidget( mpPSFDiskRadioButton );
   mpPSFRadioButtonLayout->addWidget( mpPSFSquareRadioButton );
   mpPSFRadioButtonLayout->addWidget( mpPSFGaussRadioButton );
   mpPSFRadioButtonLayout->addWidget( mpPSFAiryRadioButton );
   mpPSFTypeGroupBox->setLayout( mpPSFRadioButtonLayout );*/

   ///////////////////////////////
   
   mpDialogLayout->addWidget( mpTitelLabel );
   mpDialogLayout->addLayout( mpBlurLevelLayout );
   mpDialogLayout->addLayout( mpLambdaLayout );
   mpDialogLayout->addLayout( mpNrIterationsLayout );
   mpDialogLayout->addWidget( mpRegularizationTypeGroupBox );
   mpDialogLayout->addWidget( mpPSFTypeGroupBox );
   mpDialogLayout->addWidget( mpMessageLabel );
   mpDialogLayout->addLayout( mpButtonLayout );
   this->show();
}

//--------------------------------------------------------

RichardsonLucyDeconvolveDialog::~RichardsonLucyDeconvolveDialog()
{
   if (mpProcess != 0)
   {
      delete mpProcess;
   }
}

//--------------------------------------------------------

void RichardsonLucyDeconvolveDialog::SetupParameterLineEdits()
{
   mpBlurLevelLabel = new QLabel( QString("Blur: "), this );
   mpBlurLevelLineEdit = new QLineEdit( QString("1.5"), this );
   mpBlurLevelLayout = new QHBoxLayout;
   mpBlurLevelLayout->addWidget(mpBlurLevelLabel );
   mpBlurLevelLayout->addWidget(mpBlurLevelLineEdit );

   mpLambdaLabel = new QLabel( QString("Lambda: "), this );
   mpLambdaLineEdit = new QLineEdit( QString("0.0001"), this );
   mpLambdaLayout = new QHBoxLayout;
   mpLambdaLayout->addWidget( mpLambdaLabel );
   mpLambdaLayout->addWidget( mpLambdaLineEdit );
   
   mpNrIterationsLabel = new QLabel( QString("nr. Iterations: "), this );
   mpNrIterationsLineEdit = new QLineEdit( QString("25"), this );
   mpNrIterationsLayout = new QHBoxLayout;
   mpNrIterationsLayout->addWidget( mpNrIterationsLabel );
   mpNrIterationsLayout->addWidget( mpNrIterationsLineEdit );
}

//--------------------------------------------------------

void RichardsonLucyDeconvolveDialog::SetupRegularizationWidgets()
{
   mpRegularizationTypeGroupBox = new QGroupBox(tr("Regularization Type"));
   
   mpRegularizeNoneRadioButton           = new QRadioButton(tr("&None"));
   mpRegularizeTikhonovMillerRadioButton = new QRadioButton(tr("&Tikhonov-Miller"));
   mpRegularizeConchelloRadioButton      = new QRadioButton(tr("&Conchello"));
   mpRegularizeMaximumEntropyRadioButton = new QRadioButton(tr("&Maximum Entropy"));
   mpRegularizeTotalVariationRadioButton = new QRadioButton(tr("Total &Variation"));

   connect( mpRegularizeTikhonovMillerRadioButton, SIGNAL( clicked() ), this, SLOT( SlotSetDefaultTikhonovParameter() ) );
   connect( mpRegularizeConchelloRadioButton,      SIGNAL( clicked() ), this, SLOT( SlotSetDefaultConchelloParameter() ) );
   connect( mpRegularizeMaximumEntropyRadioButton, SIGNAL( clicked() ), this, SLOT( SlotSetDefaultMaxEntropyParameter() ) );
   connect( mpRegularizeTotalVariationRadioButton, SIGNAL( clicked() ), this, SLOT( SlotSetDefaultTotalVariationParameter() ) );
   
   mpRegularizeNoneRadioButton->setChecked(true);
   mpRegularizeRadioButtonLayout = new QVBoxLayout;
   
   mpRegularizeRadioButtonLayout->addWidget( mpRegularizeNoneRadioButton );
   mpRegularizeRadioButtonLayout->addWidget( mpRegularizeTikhonovMillerRadioButton );
   mpRegularizeRadioButtonLayout->addWidget( mpRegularizeConchelloRadioButton );
   mpRegularizeRadioButtonLayout->addWidget( mpRegularizeMaximumEntropyRadioButton );
   mpRegularizeRadioButtonLayout->addWidget( mpRegularizeTotalVariationRadioButton );
   mpRegularizationTypeGroupBox->setLayout( mpRegularizeRadioButtonLayout );
}

//--------------------------------------------------------

void RichardsonLucyDeconvolveDialog::SetupPSFWidgets()
{
   mpPSFTypeGroupBox = new QGroupBox(tr("PSF Type"));
   
   mpPSFDiskRadioButton   = new QRadioButton(tr("&Disk"));
   mpPSFSquareRadioButton = new QRadioButton(tr("&Square"));
   mpPSFGaussRadioButton  = new QRadioButton(tr("&Gaussian"));
   mpPSFAiryRadioButton   = new QRadioButton(tr("&Airy"));
   
   mpPSFGaussRadioButton->setChecked(true);
   mpPSFRadioButtonLayout = new QVBoxLayout;
   
   mpPSFRadioButtonLayout->addWidget( mpPSFDiskRadioButton );
   mpPSFRadioButtonLayout->addWidget( mpPSFSquareRadioButton );
   mpPSFRadioButtonLayout->addWidget( mpPSFGaussRadioButton );
   mpPSFRadioButtonLayout->addWidget( mpPSFAiryRadioButton );
   mpPSFTypeGroupBox->setLayout( mpPSFRadioButtonLayout );
}

//--------------------------------------------------------

void RichardsonLucyDeconvolveDialog::SlotRun()
{
   mpProcess = new RichardsonLucyDeconvolveProcess( mpInputImage );
   connect( mpProcess, SIGNAL( finished() ), this, SLOT( SlotProcessResult() ) );
   mpProcess->SetLambda( this->GetLambda() );
   mpProcess->SetBlurLevel( this->GetBlurLevel() );
   mpProcess->SetRegularizationType( this->GetRegularizationType() );
   mpProcess->SetPSFType( this->GetPSFType() );
   mpProcess->SetNrOfIterations( this->GetNrOfIterations() );
   mpProcess->start();
}

//--------------------------------------------------------

double RichardsonLucyDeconvolveDialog::GetLambda()
{
   return mpLambdaLineEdit->text().toDouble();
}

//--------------------------------------------------------

double RichardsonLucyDeconvolveDialog::GetBlurLevel()
{
   return mpBlurLevelLineEdit->text().toDouble();
}

//--------------------------------------------------------

StiraDefinitions::RLRegularizationType RichardsonLucyDeconvolveDialog::GetRegularizationType()
{
   if ( mpRegularizeNoneRadioButton->isChecked ( ) )
   {
      return StiraDefinitions::RLREGULARIZE_NONE;
   }
   else if ( mpRegularizeTikhonovMillerRadioButton->isChecked ( ) )
   {
      return StiraDefinitions::RLREGULARIZE_TIKHONOV_MILLER;
   }
   else if ( mpRegularizeConchelloRadioButton->isChecked ( ) )
   {
      return StiraDefinitions::RLREGULARIZE_CONCHELLO;
   }
   else if ( mpRegularizeMaximumEntropyRadioButton->isChecked ( ) )
   {
      return StiraDefinitions::RLREGULARIZE_MAXIMUM_ENTROPY;
   }
   else //if ( mpRegularizeTotalVariationRadioButton->isChecked ( ) ) 
   {
      return StiraDefinitions::RLREGULARIZE_TOTAL_VARIATION;
   }
}

//--------------------------------------------------------

StiraDefinitions::PSFType RichardsonLucyDeconvolveDialog::GetPSFType()
{
   if ( mpPSFDiskRadioButton->isChecked ( ) )
   {
      return StiraDefinitions::PSF_DISK;
   }
   else if ( mpPSFSquareRadioButton->isChecked ( ) )
   {
      return StiraDefinitions::PSF_SQUARE;
   }
   else if ( mpPSFGaussRadioButton->isChecked ( ) )
   {
      return StiraDefinitions::PSF_GAUSS;
   }
   else if ( mpPSFAiryRadioButton->isChecked ( ) )
   {
      return StiraDefinitions::PSF_AIRY;
   }
   else //if ( mpRegularizeTotalVariationRadioButton->isChecked ( ) ) 
   {
      return StiraDefinitions::PSF_GAUSS;
   }
}

//--------------------------------------------------------

void RichardsonLucyDeconvolveDialog::SlotSetDefaultTikhonovParameter()
{
   mpLambdaLineEdit->setText( QString("0.0006") );
}

//--------------------------------------------------------

void RichardsonLucyDeconvolveDialog::SlotSetDefaultConchelloParameter()
{
   mpLambdaLineEdit->setText( QString("0.00005") );
}

//--------------------------------------------------------

void RichardsonLucyDeconvolveDialog::SlotSetDefaultMaxEntropyParameter()
{
   mpLambdaLineEdit->setText( QString("0.0005") );
}

//--------------------------------------------------------

void RichardsonLucyDeconvolveDialog::SlotSetDefaultTotalVariationParameter()
{
   mpLambdaLineEdit->setText( QString("0.004") );
}

//--------------------------------------------------------

int RichardsonLucyDeconvolveDialog::GetNrOfIterations()
{
   return mpNrIterationsLineEdit->text().toInt();
}

//--------------------------------------------------------

Process* RichardsonLucyDeconvolveDialog::GetProcess()
{
   return mpProcess;
}

//--------------------------------------------------------
