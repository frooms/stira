
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
   cout << "Applying Dialog Master directly with Image*" << endl << flush;
   mpInputImage = pImage;
   mpTitelLabel = new QLabel( QString(""), this );
   mpDialogLayout = new QVBoxLayout(this);
   
   mpButtonLayout = new QHBoxLayout;
   mpRunButton = new QPushButton( QString("Run"), this );
   mpCancelButton = new QPushButton( QString("Cancel"), this );
   mpButtonLayout->addWidget( mpRunButton );
   mpButtonLayout->addWidget( mpCancelButton );
   connect( mpRunButton,    SIGNAL( clicked() ), this, SLOT( SlotRun() ) );
   connect( mpRunButton,    SIGNAL( clicked() ), this, SLOT( SlotDisableButtons() ) );
   connect( mpCancelButton, SIGNAL( clicked() ), this, SLOT( reject()  ) );
}

//--------------------------------------------------------

void DialogMaster::SlotDisableButtons()
{
   QString titleValue = mpTitelLabel->text();
   titleValue.append( QString(" <B>Processing...</B>") );
   mpTitelLabel->setText(titleValue);
   mpRunButton->setEnabled( false );
   mpCancelButton->setEnabled( false );
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
      //QThread::sleep ( 0.2 )
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
   }
   this->accept();
}

//--------------------------------------------------------
