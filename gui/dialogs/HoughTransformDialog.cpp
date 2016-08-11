/***********************************************************************************
 *   Copyright (C) 2016 by Filip Rooms                                             *
 *                                                                                 *
 *  Terms and conditions for using this software in any form are provided in the   *
 *  file COPYING, which can be found in the root directory of this project.        *
 *                                                                                 *
 *   Contact data: filip.rooms@gmail.com                                           *
 *                 http://www.filiprooms.be/                                       *
 *                                                                                 *
 ***********************************************************************************/

#include "HoughTransformDialog.h"
#include "../src/MainWindow.h"
#include "../processes/HoughTransformProcess.h"

using namespace std;
using namespace stira::image;


HoughTransformDialog::HoughTransformDialog( Image* pImage ) : DialogMaster( pImage )
{
    mpProcess = 0;
    mpTitelLabel->setText( QString("<b>Hough Transform Parameters</b>") );

    mpUseGradientCheckBox = new QCheckBox( tr( "&Start from Gradient Image?" ) );
    mpUseGradientCheckBox->setChecked ( true );

    mpMaximalMinimumLevelLabel = new QLabel( QString("Maximal level for starting seed: "), this );
    mpMaximalMinimumLevelLineEdit = new QLineEdit( QString("45"), this );
    mpMaximalMinimumLevelLayout = new QHBoxLayout;
    mpMaximalMinimumLevelLayout->addWidget( mpMaximalMinimumLevelLabel );
    mpMaximalMinimumLevelLayout->addWidget( mpMaximalMinimumLevelLineEdit );

    mpDialogLayout->addWidget( mpTitelLabel );
    mpDialogLayout->addWidget( mpUseGradientCheckBox );
    mpDialogLayout->addLayout( mpMaximalMinimumLevelLayout );
    mpDialogLayout->addWidget( mpMessageLabel );
    mpDialogLayout->addLayout( mpButtonLayout );
    this->show();
}

//------------------------------------------------------------------

HoughTransformDialog::~HoughTransformDialog()
{
   if (mpProcess != 0)
   {
      delete mpProcess;
   }
}

//------------------------------------------------------------------

int HoughTransformDialog::GetMaximalMinimumLevel()
{
   return mpMaximalMinimumLevelLineEdit->text().toInt();
}

//------------------------------------------------------------------

void HoughTransformDialog::SlotRun()
{
   mpProcess = new HoughTransformProcess( mpInputImage );
   connect( mpProcess, SIGNAL( finished() ), this, SLOT( SlotProcessResult() ) );
   mpProcess->SetMaximalMinimumLevel( this->GetMaximalMinimumLevel() );
   //mpProcess->SetUseGradientImage( this->GetUseGradientImage() );
   mpProcess->start();
}

//--------------------------------------------------------

Process* HoughTransformDialog::GetProcess()
{
   return mpProcess;
}

//------------------------------------------------------------------
