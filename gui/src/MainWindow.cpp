
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

#include "MainWindow.h"
//#include "MovieViewer.h"
#include "../dialogs/GenerateImageDialog.h"
#include "../dialogs/GeneratePerlinNoiseDialog.h"
#include "../../stira/image/datastructures/Image.h"

#include <iostream>

#include <QToolBar>
#include <QToolButton>
#include <QMenuBar>
#include <QApplication>
#include <QMenu>
#include <QMessageBox>
#include <QLabel>
#include <QPushButton>
#include <QMdiSubWindow>
#include <QVBoxLayout>

#include "ImageDataList.h"


using namespace std;
using namespace stira::image;


MainWindow* MainWindow::spMainWindowInstance = 0;

//========================================================================================

MainWindow* MainWindow::GetInstance()
{
   if (spMainWindowInstance == 0)
   {
      spMainWindowInstance = new MainWindow();
   }
   return spMainWindowInstance;
}

//========================================================================================

MainWindow::MainWindow() : QMainWindow( )
{
   setWindowTitle( QString("STIRA GUI") );
   SetupWorkspace();
   
   SetupDataDockWidget();
   
   QAction* pAboutAction = new QAction(tr("&About"),this);
   QAction* pOpenImageAction = new QAction(tr("&Open Image"),this);
   //QAction* pOpenVideoAction = new QAction(tr("&Open Video"),this);
   QAction* pGenerateImageAction = new QAction(tr("&Generate Image"),this);
   QAction* pGeneratePerlinAction = new QAction(tr("&Generate Perlin Clouds"),this);
   QAction* pTileSubWindowAction = new QAction(tr("&Tile Subwindows"),this);
   QAction* pCascadeSubWindowAction = new QAction(tr("&Cascade Subwindows"),this);
   QAction* pCloseAllAction = new QAction(tr("&Close All"),this);
   QAction* pClearAllAction = new QAction(tr("&Clear All"),this);
   // Connect
   connect( pAboutAction,            SIGNAL( triggered() ), this, SLOT( SlotAbout()));
   connect( pOpenImageAction,        SIGNAL( triggered() ), ImageDataList::GetInstance(), SLOT( SlotReadImageFromFile( )));
   //connect( pOpenVideoAction,        SIGNAL( triggered() ), this, SLOT( SlotOpenVideo( )));
   connect( pGenerateImageAction,    SIGNAL( triggered() ), this, SLOT( SlotSelectGenerateImage()));
   connect( pGeneratePerlinAction,   SIGNAL( triggered() ), this, SLOT( SlotSelectGeneratePerlin()));
   connect( pTileSubWindowAction,    SIGNAL( triggered() ), mpMdiArea, SLOT( tileSubWindows() ));
   connect( pCascadeSubWindowAction, SIGNAL( triggered() ), mpMdiArea, SLOT( cascadeSubWindows () ));
   connect( pClearAllAction,         SIGNAL( triggered() ), ImageDataList::GetInstance(), SLOT( SlotRemoveAllImages(  ) ));
   connect( pCloseAllAction,         SIGNAL( triggered() ), ImageDataList::GetInstance(), SLOT( SlotCloseAllImages(  ) ));
   
   mpMainMenu = new QMenu(tr("&Start"));
   mpMainMenu->addAction( pOpenImageAction );
   mpMainMenu->addAction( pGenerateImageAction );
   mpMainMenu->addAction( pGeneratePerlinAction );
   //mpMainMenu->addAction( pOpenVideoAction );
   mpMainMenu->addAction( pTileSubWindowAction );
   mpMainMenu->addAction( pCascadeSubWindowAction );
   mpMainMenu->addAction( pCloseAllAction );
   mpMainMenu->addAction( pClearAllAction );
   menuBar()->addMenu( mpMainMenu );
   
   mpHelpMenu = new QMenu(tr("&Help"));
   mpHelpMenu->addAction( pAboutAction );
   menuBar()->addMenu( mpHelpMenu );
   
   mpSettings = new QSettings("/t/tmp/.stira.ini", QSettings::IniFormat);
   
   //setMinimumSize ( StiraDefinitions::maxWidth, StiraDefinitions::maxHeight );
}

//========================================================================================

MainWindow::~MainWindow()
{
}

//========================================================================================

QSettings* MainWindow::GetSettings()
{
   return mpSettings;
}

void MainWindow::ResetMainMenu()
{
   MainWindow::GetInstance()->menuBar()->clear();
   menuBar()->addMenu(mpMainMenu);
}

//========================================================================================

void MainWindow::SetupWorkspace()
{
   mpMdiArea = new QMdiArea( this );
   
   //mpScrollArea = new QScrollArea;
   //mpScrollArea->setBackgroundRole( QPalette::Dark );
   //mpScrollArea->setWidget( mpMdiArea );
   //setCentralWidget( mpScrollArea );
   setCentralWidget( mpMdiArea );
   //mpMdiArea->setScrollBarsEnabled( true );
}

//========================================================================================

void MainWindow::SetupDataDockWidget()
{
   mpDataDock = new QDockWidget(tr("Data loaded"), this);
   mpDataDock->setFeatures( QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable );
   mpDataDock->setAllowedAreas( Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea );
   
   mpDataDock->setWidget( ImageDataList::GetInstance() );
   addDockWidget(Qt::LeftDockWidgetArea, mpDataDock);
   mpDataDock->show();
   this->repaint();
}

//========================================================================================

void MainWindow::SlotAddSubWindow( QWidget* pWidget, QString windowname )
{
   QMdiSubWindow* pSubWindow = mpMdiArea->addSubWindow( pWidget );
   pSubWindow->setAttribute ( Qt::WA_DeleteOnClose, false );
   pSubWindow->setWindowTitle( windowname );
   pSubWindow->show();
   ImageWindow* pParent = dynamic_cast<ImageWindow*>(pWidget);
   if (pParent != 0)
   {
      pParent->SetParent( pSubWindow );
      connect( pSubWindow, SIGNAL( aboutToActivate () ), pParent, SLOT( SlotSetMainMenu() ) );
      pParent->SlotSetMainMenu();
   }
}

//========================================================================================

void MainWindow::SlotRemoveSubWindow( QMdiSubWindow* pSubWindow )
{
   mpMdiArea->removeSubWindow( pSubWindow );
}

//========================================================================================

void MainWindow::SlotSelectGenerateImage()
{
   mpGenerateImageDialog = new GenerateImageDialog( );
   mpGenerateImageDialog->show();
}

//========================================================================================

void MainWindow::SlotSelectGeneratePerlin()
{
   mpGeneratePerlinNoiseDialog = new GeneratePerlinNoiseDialog( );
   mpGeneratePerlinNoiseDialog->show();
}

//========================================================================================

void MainWindow::SlotOpenVideo()
{
   QString fileName = QFileDialog::getOpenFileName( this, tr("Open File"),
                                                    QDir::currentPath(),
                                                    tr("Video (*.avi *.mpg *.wmv *.mov)"));
   
   //MovieViewer* pMovieViewer = new MovieViewer( fileName );
   //pMovieViewer->show();
}

//========================================================================================

void MainWindow::SlotAbout()
{
    QMessageBox::about( this, tr("About STIRA"), 
                              tr(" This GUI gives a simple interface to the STIRA\n "
                                 " (Simple Toolkit for Image Restoration and Analysis).\n\n"
                                 " More info: http://www.filiprooms.be/stira-own-software\n\n"
                                 " Contact: filip.rooms@gmail.com\n\n"
                                 " Copyright Filip Rooms 2008-16")
                      );
}

//========================================================================================

