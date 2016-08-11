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

    mpChooseHoughTransformTypeBox = new QGroupBox( tr( "&Choose Hough type" ) );
    mpChooseCircleHoughTransformRadioButton = new QRadioButton( "Circles" );
    mpChooseLineHoughTransformRadioButton = new QRadioButton( "Lines" );

    mpChooseHoughTransformLayout = new QVBoxLayout;
    mpChooseHoughTransformLayout->addWidget(mpChooseCircleHoughTransformRadioButton);
    mpChooseHoughTransformLayout->addWidget(mpChooseLineHoughTransformRadioButton);
    mpChooseHoughTransformTypeBox->setLayout(mpChooseHoughTransformLayout);

    mpMaximalRadiusLabel = new QLabel("Max circle radius");
    mpMaximalRadiusLayout = new QHBoxLayout;
    mpMaximalRadiusLineEdit = new QLineEdit("100");
    mpMaximalRadiusLayout->addWidget(mpMaximalRadiusLabel);
    mpMaximalRadiusLayout->addWidget(mpMaximalRadiusLineEdit);

    mpMinimalRadiusLabel = new QLabel("Min circle radius");
    mpMinimalRadiusLayout = new QHBoxLayout;
    mpMinimalRadiusLineEdit = new QLineEdit("80");
    mpMinimalRadiusLayout->addWidget(mpMinimalRadiusLabel);
    mpMinimalRadiusLayout->addWidget(mpMinimalRadiusLineEdit);

    mpDialogLayout->addWidget( mpTitelLabel );
    mpDialogLayout->addWidget( mpChooseHoughTransformTypeBox );
    mpDialogLayout->addLayout( mpMaximalRadiusLayout );
    mpDialogLayout->addLayout( mpMinimalRadiusLayout );
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

int HoughTransformDialog::GetMaximalRadius()
{
   return mpMaximalRadiusLineEdit->text().toInt();
}

//------------------------------------------------------------------

int HoughTransformDialog::GetMinimalRadius()
{
   return mpMinimalRadiusLineEdit->text().toInt();
}

bool HoughTransformDialog::DidChooseCircles()
{
    return mpChooseCircleHoughTransformRadioButton->isChecked();
}

//------------------------------------------------------------------

void HoughTransformDialog::SlotRun()
{
   mpProcess = new HoughTransformProcess( mpInputImage );
   connect( mpProcess, SIGNAL( finished() ), this, SLOT( SlotProcessResult() ) );
   mpProcess->SetMaximalRadius( this->GetMaximalRadius() );
   mpProcess->SetMinimalRadius( this->GetMinimalRadius() );
   mpProcess->SetChooseCircles( this->DidChooseCircles() );
   mpProcess->start();
}

//--------------------------------------------------------

Process* HoughTransformDialog::GetProcess()
{
   return mpProcess;
}

//------------------------------------------------------------------
