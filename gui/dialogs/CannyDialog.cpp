
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

#include "CannyDialog.h"
#include "../../stira/imageanalysis/imageanalysis/CannyEdgeDetector.h"
#include "../../stira/image/datastructures/Image.h"

#include "../src/MainWindow.h"
#include "../processes/CannyProcess.h"

using namespace stira::image;
using namespace stira::imageanalysis;

CannyDialog::CannyDialog( Image* pImage ) : DialogMaster( pImage )
{
   mpProcess = 0;
   mpTitelLabel->setText( QString("<b>Canny Edge Detection Parameters</b>") );
   
   mpUpperThresholdLabel = new QLabel( QString("Hysteresis upper threshold: "), this );
   mpUpperThresholdLineEdit = new QLineEdit( QString("70"), this );;
   mpUpperThresholdLayout = new QHBoxLayout;
   mpUpperThresholdLayout->addWidget( mpUpperThresholdLabel );
   mpUpperThresholdLayout->addWidget( mpUpperThresholdLineEdit );
   
   mpLowerThresholdLabel = new QLabel( QString("Hysteresis lower threshold: "), this );
   mpLowerThresholdLineEdit = new QLineEdit( QString("25"), this );;
   mpLowerThresholdLayout = new QHBoxLayout;
   mpLowerThresholdLayout->addWidget( mpLowerThresholdLabel );
   mpLowerThresholdLayout->addWidget( mpLowerThresholdLineEdit );
   
   mpSigmaSmoothingLabel = new QLabel( QString("Sigma for smoothing: "), this );
   mpSigmaSmoothingLineEdit = new QLineEdit( QString("1.0"), this );;
   mpSigmaSmoothingLayout = new QHBoxLayout;
   mpSigmaSmoothingLayout->addWidget( mpSigmaSmoothingLabel );
   mpSigmaSmoothingLayout->addWidget( mpSigmaSmoothingLineEdit );
    
   mpDialogLayout->addWidget( mpTitelLabel );
   mpDialogLayout->addLayout( mpUpperThresholdLayout );
   mpDialogLayout->addLayout( mpLowerThresholdLayout );
   mpDialogLayout->addLayout( mpSigmaSmoothingLayout );
   mpDialogLayout->addWidget( mpMessageLabel );
   mpDialogLayout->addLayout( mpButtonLayout );
   this->show();
}

//--------------------------------------------------------

CannyDialog::~CannyDialog()
{
   if (mpProcess != 0)
   {
      delete mpProcess;
   }
}

//--------------------------------------------------------

double CannyDialog::GetUpperThreshold()
{
   return mpUpperThresholdLineEdit->text().toDouble();
}

//--------------------------------------------------------

double CannyDialog::GetLowerThreshold()
{
   return mpLowerThresholdLineEdit->text().toDouble();
}

//--------------------------------------------------------

double CannyDialog::GetSigmaSmoothing()
{
   return mpSigmaSmoothingLineEdit->text().toDouble();
}

//------------------------------------------------------------------

void CannyDialog::SlotRun()
{
   mpProcess = new CannyProcess( mpInputImage );
   connect( mpProcess, SIGNAL( finished() ), this, SLOT( SlotProcessResult() ) );
   mpProcess->SetUpperThreshold( this->GetUpperThreshold() );
   mpProcess->SetLowerThreshold( this->GetLowerThreshold() );
   mpProcess->SetSigmaSmoothing( this->GetSigmaSmoothing() );
   mpProcess->start();
}

//--------------------------------------------------------

Process* CannyDialog::GetProcess()
{
   return mpProcess;
}

//------------------------------------------------------------------
