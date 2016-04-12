
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

#include "WatershedDialog.h"
#include "../src/MainWindow.h"
#include "../processes/WatershedProcess.h"

using namespace std;
using namespace stira::image;

WatershedDialog::WatershedDialog( Image* pImage ) : DialogMaster( pImage )
{
   mpProcess = 0;
   mpTitelLabel->setText( QString("Watershed Parameters") );
   
   mpUseGradientCheckBox = new QCheckBox( tr( "&Start from Gradient Image?" ) );
   mpUseGradientCheckBox->setChecked ( true );
   
   mpMaximalMinimumLevelLabel = new QLabel( QString("Maximal level for starting seed: "), this );
   mpMaximalMinimumLevelLineEdit = new QLineEdit( QString("45"), this );
   mpMaximalMinimumLevelLayout = new QHBoxLayout;
   mpMaximalMinimumLevelLayout->addWidget( mpMaximalMinimumLevelLabel );
   mpMaximalMinimumLevelLayout->addWidget( mpMaximalMinimumLevelLineEdit );
   
   mpEqualityPrecisionLineEdit = new QLineEdit( QString("30"), this );
   mpEqualityPrecisionLabel = new QLabel( QString("Precision: "), this );
   mpEqualityPrecisionLayout = new QHBoxLayout;
   mpEqualityPrecisionLayout->addWidget( mpEqualityPrecisionLabel );
   mpEqualityPrecisionLayout->addWidget( mpEqualityPrecisionLineEdit );
   
   mpDialogLayout->addWidget( mpTitelLabel );
   mpDialogLayout->addWidget( mpUseGradientCheckBox );
   mpDialogLayout->addLayout( mpMaximalMinimumLevelLayout );
   mpDialogLayout->addLayout( mpEqualityPrecisionLayout );
   mpDialogLayout->addLayout( mpButtonLayout );
   this->show();
}

//------------------------------------------------------------------

WatershedDialog::~WatershedDialog()
{
   if (mpProcess != 0)
   {
      delete mpProcess;
   }
}

//------------------------------------------------------------------

bool WatershedDialog::GetUseGradientImage()
{
   return mpUseGradientCheckBox->isChecked( );
}

//------------------------------------------------------------------

int WatershedDialog::GetEqualityPrecision()
{
   return mpEqualityPrecisionLineEdit->text().toInt();
}

//------------------------------------------------------------------

int WatershedDialog::GetMaximalMinimumLevel()
{
   return mpMaximalMinimumLevelLineEdit->text().toInt();
}

//------------------------------------------------------------------

void WatershedDialog::SlotRun()
{
   mpProcess = new WatershedProcess( mpInputImage );
   connect( mpProcess, SIGNAL( finished() ), this, SLOT( SlotProcessResult() ) );
   mpProcess->SetEqualityPrecision( this->GetEqualityPrecision() );
   mpProcess->SetMaximalMinimumLevel( this->GetMaximalMinimumLevel() );
   mpProcess->SetUseGradientImage( this->GetUseGradientImage() );
   mpProcess->start();
}

//--------------------------------------------------------

Process* WatershedDialog::GetProcess()
{
   return mpProcess;
}

//------------------------------------------------------------------
