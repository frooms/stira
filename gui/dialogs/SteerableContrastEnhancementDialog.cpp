
/*****************************************
 *   Copyright (C) 2008 by Filip Rooms   *
 *   filip.rooms@gmail.com               *
 *   http://www.filiprooms.be/           *
 *                                       *
 *****************************************/

#include <QApplication>
#include "AnisotropicDiffusionProcess.h"
#include "../src/FriepMainWindow.h"
#include "../../friepcore/image/Image.h"
#include "../../friepcore/diffusion/AnisotropicDiffusion.h"

using namespace stira::diffusion;
using namespace stira::image;
using namespace std;



AnisotropicDiffusionDialog::AnisotropicDiffusionDialog( ImageWindow* pImWindow ) : QDialog()
{
   mpImWindow = pImWindow;
   mpTitelLabel = new QLabel( QString("Anisotropic Diffusion Parameters"), this );
   mpNrIterationsLabel = new QLabel( QString("Nr. iterations: "), this );
   mpNrIterationsLineEdit = new QLineEdit( QString("5"), this );
   mpNrIterationsLayout = new QHBoxLayout;
   mpNrIterationsLayout->addWidget( mpNrIterationsLabel );
   mpNrIterationsLayout->addWidget( mpNrIterationsLineEdit );
   
   mpFlowParameterLabel = new QLabel( QString("Flow constant: "), this );
   mpFlowParameterLineEdit = new QLineEdit( QString("3.0"), this );
   mpFlowParameterLayout = new QHBoxLayout;
   mpFlowParameterLayout->addWidget( mpFlowParameterLabel );
   mpFlowParameterLayout->addWidget( mpFlowParameterLineEdit );
   
   mpButtonLayout = new QHBoxLayout;
   mpRunButton = new QPushButton( QString("Run"), this );
   mpCancelButton = new QPushButton( QString("Cancel"), this );
   mpButtonLayout->addWidget( mpRunButton );
   mpButtonLayout->addWidget( mpCancelButton );
    
   mpDialogLayout = new QVBoxLayout(this);
   mpDialogLayout->addWidget( mpTitelLabel );
   mpDialogLayout->addLayout( mpNrIterationsLayout );
   mpDialogLayout->addLayout( mpFlowParameterLayout );
   mpDialogLayout->addLayout( mpButtonLayout );
   connect( mpRunButton,    SIGNAL( clicked() ), this, SLOT( SlotRun() ) );
   connect( mpCancelButton, SIGNAL( clicked() ), this, SLOT( reject()  ) );
   this->show();
}

AnisotropicDiffusionDialog::~AnisotropicDiffusionDialog()
{
}

//--------------------------------------------------------

void AnisotropicDiffusionDialog::SlotRun()
{
   mpProcess = new AnisotropicDiffusionProcess( mpImWindow, this );
   connect( mpProcess, SIGNAL( finished() ), this, SLOT( ProcessResult() ) );
   mpProcess->SetFlowParameter( mpFlowParameterLineEdit->text().toDouble() );
   mpProcess->SetNrOfIterations( mpNrIterationsLineEdit->text().toInt() );
   mpProcess->start();
}

//--------------------------------------------------------

void AnisotropicDiffusionDialog::ProcessResult()
{
   // WARNING: CAN'T CREATE WIDGETS IN OTHER THREAD; REALLY MAKE SURE IT'S FINISHED FIRST
   if ( !(mpProcess->isFinished()) )
   {
      sleep(0.2);
      ProcessResult();
   }
   else
   {
      stira::image::Image* pImage = mpProcess->GetResultImage();
      ImageWindow* pIW = new ImageWindow ( pImage );
   
      FriepMainWindow::GetInstance()->SlotShowNewResultWindow ( pIW );
      delete pImage;
   }
   accept();
}

//====================================================================
//====================================================================
//====================================================================

AnisotropicDiffusionProcess::AnisotropicDiffusionProcess( ImageWindow* pImWindow, AnisotropicDiffusionDialog* pDialog ) : QThread()
{
   mpImWindow = pImWindow;
   mpDialog = pDialog;
   mpOutImage = 0;
}

//--------------------------------------------------------

AnisotropicDiffusionProcess::~AnisotropicDiffusionProcess()
{
}

//--------------------------------------------------------

double AnisotropicDiffusionProcess::GetFlowParameter()
{
   return mFlowParameter;
}

//--------------------------------------------------------;

void AnisotropicDiffusionProcess::SetFlowParameter(double f)
{
   mFlowParameter = f;
}

//--------------------------------------------------------;
int AnisotropicDiffusionProcess::GetNrOfIterations()
{
   return mNrIterations;
}

//--------------------------------------------------------;

void AnisotropicDiffusionProcess::SetNrOfIterations(int i)
{
   mNrIterations = i;
}

//--------------------------------------------------------

void AnisotropicDiffusionProcess::run()
{
   Image* pImage = mpImWindow->GetQImageAsImage( );
   AnisotropicDiffusion ad ( pImage );
   ad.SetMaxNumberOfIterations ( mNrIterations );
   
   ad.SetFlowFactor ( mFlowParameter );
   mpOutImage = ad.Run();
   delete pImage;
}

//--------------------------------------------------------

stira::image::Image* AnisotropicDiffusionProcess::GetResultImage()
{
   return mpOutImage;
}

//==========================================================================
//==========================================================================
//==========================================================================
