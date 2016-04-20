
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
#include <QTime>
#include <QApplication>
#include "../src/MainWindow.h"
#include "DialogMaster.h"
#include "../src/ImageDataList.h"

using namespace stira::image;
using namespace std;

DialogMaster::DialogMaster( Image* pImage ) : QDialog(0, Qt::WindowStaysOnTopHint)
{
   mpInputImage = pImage;
   mpTitelLabel = new QLabel( QString(""), this );
   mpDialogLayout = new QVBoxLayout(this);

   mpMessageLabel = new QLabel( QString(""), this );
   
   mpButtonLayout = new QHBoxLayout;
   mpRunButton = new QPushButton( QString("Run"), this );
   mpCancelButton = new QPushButton( QString("Cancel"), this );
   mpButtonLayout->addWidget( mpRunButton );
   mpButtonLayout->addWidget( mpCancelButton );
   connect( mpRunButton,    SIGNAL( clicked() ), this, SLOT( SlotDisableButtons() ) );
   connect( mpRunButton,    SIGNAL( clicked() ), this, SLOT( SlotRun() ) );
   connect( mpCancelButton, SIGNAL( clicked() ), this, SLOT( reject()  ) );
}

//--------------------------------------------------------

void DialogMaster::SlotDisableButtons()
{
   mpMessageLabel->setText( QString(" <B>Processing...</B>") );
   mpRunButton->setEnabled( false );
   mpCancelButton->setEnabled( false );
}

void DialogMaster::EnableButtons()
{
    mpRunButton->setEnabled( true );
    mpCancelButton->setEnabled( true );
}

//--------------------------------------------------------
   
void DialogMaster::AddResult( stira::image::Image* pResultImage )
{
   vpResults.push_back( pResultImage );
}

//--------------------------------------------------------

void DialogMaster::SlotProcessResult()
{
   // WARNING: CAN'T CREATE WIDGETS IN OTHER THREAD; REALLY MAKE SURE IT'S FINISHED FIRST
   if ( !( GetProcess()->isFinished() ) )
   {
      QTime dieTime= QTime::currentTime().addSecs(1);
      while( QTime::currentTime() < dieTime )
      QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

      SlotProcessResult();
   }
   else
   {
      std::vector< stira::image::Image* > vResultVector = GetProcess()->GetResultImages();
      std::vector< stira::image::Image* >::iterator it;
      for(it = vResultVector.begin(); it != vResultVector.end(); it++)
      {
         ImageDataList::GetInstance()->AddImage( (*it) );
      }
      mpMessageLabel->setText( QString(" <B>Ready!</B>") );
      EnableButtons();
   }
   //this->accept();
}

//--------------------------------------------------------
