/****************************************************************************
 **
 ** Copyright (C) 2005-2007 Trolltech ASA. All rights reserved.
 **
 ** This file is part of the example classes of the Qt Toolkit.
 **
 ** This file may be used under the terms of the GNU General Public
 ** License version 2.0 as published by the Free Software Foundation
 ** and appearing in the file LICENSE.GPL included in the packaging of
 ** this file.  Please review the following information to ensure GNU
 ** General Public Licensing requirements will be met:
 ** http://www.trolltech.com/products/qt/opensource.html
 **
 ** If you are unsure which license is appropriate for your use, please
 ** review the following information:
 ** http://www.trolltech.com/products/qt/licensing.html or contact the
 ** sales department at sales@trolltech.com.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **
 ****************************************************************************/
 
/***********************************************************************************
 *   Copyright (C) 2008 by Filip Rooms (modifications)                             *
 *                                                                                 *
 *  Terms and conditions for using this software in any form are provided in the   *
 *  file COPYING, which can be found in the root directory of this project.        *
 *                                                                                 *
 *   Contact data: filip.rooms@gmail.com                                           *
 *                 http://www.filiprooms.be/                                       *
 *                                                                                 *
 ***********************************************************************************/

#include <QtGui>
#include <string>
#include <QMainWindow>
#include <QSlider>
#include <iostream>

#include "ProcessManager.h"
#include "ImageWindow.h"
#include "MainWindow.h"
#include "ImageDataList.h"
#include "../../stira/common/common/MathUtils.h"
#include "../../stira/common/common/StringUtils.h"
#include "../../stira/imagetools/tools/ImageTools.h"

using namespace std;
using namespace stira::imagetools;
using namespace stira::imagedata;
using namespace stira::common;

//------------------------------------------------------------------

ImageWindow::ImageWindow ( QImage* pQImage )
{
   InitializePointers( );
   if ( pQImage != 0 )
   {
      SetupWindow();
      mpQImage = pQImage;
      mpImage1 = ImageDataList::QImageToImage ( mpQImage );
      SetupImage( );
   }
}

//------------------------------------------------------------------

ImageWindow::ImageWindow ( stira::imagedata::Image* pImage )
{
   InitializePointers( );
   if ( pImage != 0)
   {
      mpImage1 = pImage;
      SetupWindow();
      mpQImage = ImageDataList::ImageToQImage ( mpImage1 );
      SetupImage( );
   }
}

//------------------------------------------------------------------

ImageWindow::~ImageWindow( )
{
   if (mpQImage != 0)
   {
      delete mpQImage;
   }
   cout << " Now deleting ImageWindow " << this << endl << flush;
}

//------------------------------------------------------------------

void ImageWindow::InitializePointers( )
{
   mpProcessManager = 0;
   mpImage1 = 0;
   mpImage2 = 0;
   mpQImage = 0;
   mpParentWindow = 0;
   mIsFirstRendering = true;
}

//------------------------------------------------------------------

void ImageWindow::SetupImage( )
{
   if (mpQImage->format() != QImage::Format_RGB32)
   {
      QImage convertedImg = mpQImage->convertToFormat (QImage::Format_RGB32);
      delete mpQImage;
      mpQImage = new QImage( convertedImg );
   }
   RenderImage ( mpQImage );
   mpProcessManager = new ProcessManager( mpImage1 );
}

//------------------------------------------------------------------

void ImageWindow::CreateMenus( )
{
   // FILE
   ///////
   mpSubMenuFile = new QMenu( tr ( "&File" ), this );
   mpSubMenuFile->addAction ( mpSaveAction );
   mpSubMenuFile->addAction ( mpPrintAction );
   mpSubMenuFile->addAction ( mpExitAction );

   // VIEW
   /////////////
   mpSubMenuView = new QMenu( tr ( "&View" ), this );
   mpSubMenuView->addAction ( mpResetViewOneImageAction );
   mpSubMenuView->addAction ( mpZoomInAction );
   mpSubMenuView->addAction ( mpZoomOutAction );
   mpSubMenuView->addAction ( mpNormalSizeAction );
   mpSubMenuView->addAction ( mpFitToWindowAction );
}

//------------------------------------------------------------------

QMdiSubWindow* ImageWindow::GetParent()
{
   return mpParentWindow;
}

//------------------------------------------------------------------

void ImageWindow::SetParent( QMdiSubWindow* pParentWindow )
{
   mpParentWindow = pParentWindow;
}

//------------------------------------------------------------------

void ImageWindow::SetupWindow()
{
   mpImageLabel = new ClickableLabel(this);//QLabel;
   mpImageLabel->setBackgroundRole ( QPalette::Base );
   mpImageLabel->setSizePolicy ( QSizePolicy::Ignored, QSizePolicy::Ignored );
   mpImageLabel->setScaledContents ( true );

   mpScrollArea = new QScrollArea;
   mpScrollArea->setBackgroundRole ( QPalette::Dark );
   mpScrollArea->setWidget ( mpImageLabel );
   
   CreateActions();
   CreateMenus( );
   setWindowTitle ( tr ( "Image Viewer" ) );
   
   mpZoomInButton = new QPushButton( QIcon(":/icons/zoom-in-48x48.png"), QString(""), this);
   mpZoomOutButton = new QPushButton( QIcon(":/icons/zoom-out-48x48.png"), QString(""), this);
   mpRemove2ndImageButton = new QPushButton( QIcon(":/icons/bt-remove-48x48.png"), QString(""), this);
   mpRotateRightButton = new QPushButton( QIcon(":/icons/object-rotate-right.png"), QString(""), this);
   mpRotateLeftButton = new QPushButton( QIcon(":/icons/object-rotate-left.png"), QString(""), this);
   mpZoom100PercentButton = new QPushButton( QString("100%"), this);
   mpFitToWindowButton = new QPushButton( QString("Fit Window"), this);;
   connect( mpRemove2ndImageButton, SIGNAL( clicked() ), this, SLOT( SlotRemoveComparisonImage( ) ));
   connect( mpZoomInButton, SIGNAL( clicked() ), this, SLOT( SlotZoomIn() ));
   connect( mpZoomOutButton, SIGNAL( clicked() ), this, SLOT( SlotZoomOut() ));
   connect( mpZoom100PercentButton, SIGNAL( clicked() ), this, SLOT( SlotNormalSize() ));
   connect( mpFitToWindowButton, SIGNAL( clicked() ), this, SLOT( SlotClickFitToWindow() ));
   connect( mpRotateRightButton, SIGNAL( clicked() ), this, SLOT( SlotRotatePlus90Degrees() ));
   connect( mpRotateLeftButton, SIGNAL( clicked() ), this, SLOT( SlotRotateMinus90Degrees() ));
   //connect( mpImageLabel, SIGNAL( wheelUpEvent() ), wheelmpScrollArea->verticalScrollBar() http://www.techtomar.com/)
   
   mpSlider = new QSlider( Qt::Horizontal, this );
   mpRemove2ndImageButton->hide();
   mpSlider->hide();
   
   mpButtonLayout = new QHBoxLayout;
   mpButtonLayout->addWidget( mpRemove2ndImageButton );
   mpButtonLayout->addWidget( mpZoomInButton );
   mpButtonLayout->addWidget( mpZoomOutButton );
   mpButtonLayout->addWidget( mpRotateLeftButton );
   mpButtonLayout->addWidget( mpRotateRightButton );
   mpButtonLayout->addWidget( mpZoom100PercentButton );
   mpButtonLayout->addWidget( mpFitToWindowButton );
   mpButtonLayout->addWidget( mpSlider );
   
   mpWidgetsLayout = new QVBoxLayout;
   mpWidgetsLayout->addWidget( mpScrollArea );
   mpWidgetsLayout->addLayout( mpButtonLayout );
   mpWindowLayout = new QGridLayout( this );
   mpWindowLayout->addLayout( mpWidgetsLayout, 0, 0  );
}

//------------------------------------------------------------------

void ImageWindow::RepaintImage()
{
   this->show();
   mpImageLabel->update();
   mpImageLabel->show();
   mpScrollArea->update();
   mpScrollArea->show();
   this->update();
}

//------------------------------------------------------------------

void ImageWindow::RenderImage ( QImage* pQImage )
{
   if ( pQImage->isNull() )
   {
      QMessageBox::information ( this, tr ( "Image Viewer" ), tr ( "Cannot load." ) );
      return;
   }
   
   if (mIsFirstRendering == true)
   {
      SlotSetSizeCondition();
      mIsFirstRendering = false;
   }
   
   mpImageLabel->setPixmap ( QPixmap::fromImage ( *pQImage ) );
   UpdateActions();
   
   if ( !mpFitToWindowAction->isChecked() && mIsFirstRendering )
   {
      mpImageLabel->adjustSize();
      SlotFitToWindow();
   }
   
   ScaleImage ( );
}

//------------------------------------------------------------------

void ImageWindow::SlotCompareImages( stira::imagedata::Image* pImage, ComparisonMode mode )
{
   if ( (pImage != 0) && ( ( mpImage1->GetNumberOfBands() == 3) || ( mpImage1->GetNumberOfBands() == 1) )
                      && ( (   pImage->GetNumberOfBands() == 3) || (   pImage->GetNumberOfBands() == 1) )
      )
   {
      mpRemove2ndImageButton->show();
      mpSlider->show();
      mpImage2 = pImage;
      mComparisonMode = mode;
      switch (mode)
      {
         case COMPARE_CHECKERED:
         {
            mpSlider->setValue( 50 );
            mpSlider->setMaximum( mpImage1->GetWidth() );
            SlotReRenderCheckerImage( 50 );
            connect( mpSlider, SIGNAL( valueChanged( int )  ), this, SLOT( SlotReRenderCheckerImage( int ) ) );
            break;
         }
         case COMPARE_TRANSPARANT:
         default:
         {
            mpSlider->setValue( 50 );
            mpSlider->setMaximum( 100 );
            SlotReRenderTransparantImage ( 50 );
            connect( mpSlider, SIGNAL( valueChanged( int ) ), this, SLOT( SlotReRenderTransparantImage( int ) ) );
            break;
         }
      }
   }
}


//------------------------------------------------------------------

void ImageWindow::SlotRemoveComparisonImage( )
{
   if (mpImage2 != 0)
   {
      mpRemove2ndImageButton->hide();
      mpSlider->hide();
      mpImage2 = 0;
      mComparisonMode = COMPARE_NONE;
      RenderImage ( ImageDataList::ImageToQImage( mpImage1 ) );
      disconnect( mpSlider, SIGNAL( valueChanged( int ) ), this, SLOT( SlotReRenderCheckerImage( int ) ) );
      disconnect( mpSlider, SIGNAL( valueChanged( int ) ), this, SLOT( SlotReRenderTransparantImage( int ) ) );
   }
}

//------------------------------------------------------------------

QRgb ImageWindow::GetMixedColor33(int x, int y, double fraction)
{
   return qRgb( (int)( MathUtils::ClipValue( fraction * mpImage1->GetBands()[0]->GetValue( x, y ) + (1.0 - fraction) * mpImage2->GetBands()[0]->GetValue( x, y ), 0.0, 255.0 ) ), 
                (int)( MathUtils::ClipValue( fraction * mpImage1->GetBands()[1]->GetValue( x, y ) + (1.0 - fraction) * mpImage2->GetBands()[1]->GetValue( x, y ), 0.0, 255.0 ) ),
                (int)( MathUtils::ClipValue( fraction * mpImage1->GetBands()[2]->GetValue( x, y ) + (1.0 - fraction) * mpImage2->GetBands()[2]->GetValue( x, y ), 0.0, 255.0 ) )
                );
}

//------------------------------------------------------------------

QRgb ImageWindow::GetMixedColor31(int x, int y, double fraction)
{
   double component2 = (1.0 - fraction) * mpImage2->GetBands()[0]->GetValue( x, y );
   return qRgb( (int)( MathUtils::ClipValue( fraction * mpImage1->GetBands()[0]->GetValue( x, y ) + component2, 0.0, 255.0 ) ), 
                (int)( MathUtils::ClipValue( fraction * mpImage1->GetBands()[1]->GetValue( x, y ) + component2, 0.0, 255.0 ) ),
                (int)( MathUtils::ClipValue( fraction * mpImage1->GetBands()[2]->GetValue( x, y ) + component2, 0.0, 255.0 ) )
              );
}

//------------------------------------------------------------------

QRgb ImageWindow::GetMixedColor13(int x, int y, double fraction)
{
   double component1 = fraction * mpImage1->GetBands()[0]->GetValue( x, y );
   double w2 = 1.0 - fraction;
   return  qRgb( (int)( MathUtils::ClipValue( component1 + w2 * mpImage2->GetBands()[0]->GetValue( x, y ), 0.0, 255.0 ) ), 
                 (int)( MathUtils::ClipValue( component1 + w2 * mpImage2->GetBands()[1]->GetValue( x, y ), 0.0, 255.0 ) ),
                 (int)( MathUtils::ClipValue( component1 + w2 * mpImage2->GetBands()[2]->GetValue( x, y ), 0.0, 255.0 ) )
               );
}

//------------------------------------------------------------------

QRgb ImageWindow::GetMixedColor11(int x, int y, double fraction)
{
   int mixedvalue = (int)( MathUtils::ClipValue( (            fraction * mpImage1->GetBands()[0]->GetValue( x, y ) 
                                                    + (1.0 - fraction) * mpImage2->GetBands()[0]->GetValue( x, y )
                                                 ),
                                                 0.0, 255.0 ) );
                                                 
   return  qRgb( mixedvalue, mixedvalue, mixedvalue );
}

//------------------------------------------------------------------
QRgb ImageWindow::GetQColor3BandsImage1(int x, int y)
{
   return qRgb( (int)( MathUtils::ClipValue( mpImage1->GetBands()[0]->GetValue( x, y ), 0.0, 255.0 ) ),
                (int)( MathUtils::ClipValue( mpImage1->GetBands()[1]->GetValue( x, y ), 0.0, 255.0 ) ),
                (int)( MathUtils::ClipValue( mpImage1->GetBands()[2]->GetValue( x, y ), 0.0, 255.0 ) )
              );
}

//------------------------------------------------------------------

QRgb ImageWindow::GetQColor1BandImage1(int x, int y)
{
   return qRgb( (int)( MathUtils::ClipValue( mpImage1->GetBands()[0]->GetValue( x, y ), 0.0, 255.0 ) ),
                (int)( MathUtils::ClipValue( mpImage1->GetBands()[0]->GetValue( x, y ), 0.0, 255.0 ) ),
                (int)( MathUtils::ClipValue( mpImage1->GetBands()[0]->GetValue( x, y ), 0.0, 255.0 ) )
              );
}

//------------------------------------------------------------------

QRgb ImageWindow::GetQColor3BandsImage2(int x, int y)
{
   return qRgb( (int)( MathUtils::ClipValue( mpImage2->GetBands()[0]->GetValue( x, y ), 0.0, 255.0 ) ),
                (int)( MathUtils::ClipValue( mpImage2->GetBands()[1]->GetValue( x, y ), 0.0, 255.0 ) ),
                (int)( MathUtils::ClipValue( mpImage2->GetBands()[2]->GetValue( x, y ), 0.0, 255.0 ) )
              );
}

//------------------------------------------------------------------

QRgb ImageWindow::GetQColor1BandImage2(int x, int y)
{
   return qRgb( (int)( MathUtils::ClipValue( mpImage2->GetBands()[0]->GetValue( x, y ), 0.0, 255.0 ) ),
                (int)( MathUtils::ClipValue( mpImage2->GetBands()[0]->GetValue( x, y ), 0.0, 255.0 ) ),
                (int)( MathUtils::ClipValue( mpImage2->GetBands()[0]->GetValue( x, y ), 0.0, 255.0 ) )
              );
}

//------------------------------------------------------------------

void ImageWindow::SlotReRenderTransparantImage( int sliderPosition )
{
   double fraction = (double)( sliderPosition ) / 100.0;
   int height = mpQImage->height();
   int width  = mpQImage->width();
   
   if ( ( mpImage1->GetNumberOfBands() == 3) && ( mpImage2->GetNumberOfBands() == 3) )
   {
      for ( int y = 0; y < height; y++ )
      {
         for ( int x = 0; x < width; x++ )
         {
            mpQImage->setPixel ( x, y, GetMixedColor33(x, y, fraction) );
         }
      }
   }
   if ( ( mpImage1->GetNumberOfBands() == 3) && ( mpImage2->GetNumberOfBands() == 1) )
   {
      for ( int y = 0; y < height; y++ )
      {
         for ( int x = 0; x < width; x++ )
         {
            mpQImage->setPixel ( x, y, GetMixedColor31(x, y, fraction) );
         }
      }
   }
   if ( ( mpImage1->GetNumberOfBands() == 1) && ( mpImage2->GetNumberOfBands() == 3) )
   {
      for ( int y = 0; y < height; y++ )
      {
         for ( int x = 0; x < width; x++ )
         {
            mpQImage->setPixel ( x, y, GetMixedColor13(x, y, fraction) );
         }
      }
   }
   if ( ( mpImage1->GetNumberOfBands() == 1) && ( mpImage2->GetNumberOfBands() == 1) )
   {
      for ( int y = 0; y < height; y++ )
      {
         for ( int x = 0; x < width; x++ )
         {
            cout << "for mixed color, we get " << GetMixedColor11(x, y, fraction) << endl << flush;
            mpQImage->setPixel ( x, y, GetMixedColor11(x, y, fraction) );
         }
      }
   }
   RenderImage ( mpQImage );
}

//------------------------------------------------------------------

void ImageWindow::SlotReRenderCheckerImage( int blockSize )
{
   if (blockSize > 0)
   {
      int height = mpQImage->height ();
      int width  = mpQImage->width();
      if ( ( mpImage1->GetNumberOfBands() == 3) && ( mpImage2->GetNumberOfBands() == 3) )
      {
         for (int y = 0; y < height; y++)
         {
            for (int x = 0; x < width; x++)
            {
               if (( (x / blockSize + y / blockSize ) % 2) == 0) { mpQImage->setPixel ( x, y, GetQColor3BandsImage1( x, y ) );}
                                                            else { mpQImage->setPixel ( x, y, GetQColor3BandsImage2( x, y ) );}
            }
         }
      }
      if ( ( mpImage1->GetNumberOfBands() == 3) && ( mpImage2->GetNumberOfBands() == 1) )
      {
         for (int y = 0; y < height; y++)
         {
            for (int x = 0; x < width; x++)
            {
               if (( (x / blockSize + y / blockSize) % 2) == 0) { mpQImage->setPixel ( x, y, GetQColor3BandsImage1( x, y ) );}
                                                           else { mpQImage->setPixel ( x, y,  GetQColor1BandImage2( x, y ) );}
            }
         }
      }
      if ( ( mpImage1->GetNumberOfBands() == 1) && ( mpImage2->GetNumberOfBands() == 3) )
      {
         for (int y = 0; y < height; y++)
         {
            for (int x = 0; x < width; x++)
            {
               if (( (x / blockSize + y / blockSize) % 2) == 0) { mpQImage->setPixel ( x, y,  GetQColor1BandImage1( x, y ) );}
                                                           else { mpQImage->setPixel ( x, y, GetQColor3BandsImage2( x, y ) );}
            }
         }
      }
      if ( ( mpImage1->GetNumberOfBands() == 1) && ( mpImage2->GetNumberOfBands() == 1) )
      {
         for (int y = 0; y < height; y++)
         {
            for (int x = 0; x < width; x++)
            {
               if (( (x / blockSize + y / blockSize) % 2) == 0) { mpQImage->setPixel ( x, y, GetQColor1BandImage1( x, y ) );}
                                                           else { mpQImage->setPixel ( x, y, GetQColor1BandImage2( x, y ) );}
            }
         }
      }
      RenderImage ( mpQImage );
   }
}

//------------------------------------------------------------------

void ImageWindow::SlotSave()
{
   Q_ASSERT ( mpImageLabel->pixmap() );
   
   std::string tmpString = MainWindow::GetInstance()->GetSettings()->value("lastWritePath").toString().toStdString ()
                                   + mpImage1->GetImageName() 
                                   + std::string(".ppm");
   
   QString fileName = QFileDialog::getSaveFileName( this, tr("Save Image As..."),
                                 ( tmpString ).c_str(),
                                 tr("Images (*.ppm *.pgm *.png *.jpg *.tif *.tiff)"));

   if (!fileName.isEmpty())
   {
      mpImageLabel->pixmap()->save ( fileName  );
      
      std::string pathName = StringUtils::ExtractPathOfFileName(fileName.toStdString () );
      MainWindow::GetInstance()->GetSettings()->setValue( "lastWritePath", pathName.c_str() );
   }
}

//------------------------------------------------------------------

void ImageWindow::SlotPrint()
{
   Q_ASSERT ( mpImageLabel->pixmap() );
   QPrintDialog dialog ( &mPrinter, this );
   if ( dialog.exec() )
   {
      QPainter painter ( &mPrinter );
      QRect rect = painter.viewport();
      QSize size = mpImageLabel->pixmap()->size();
      size.scale ( rect.size(), Qt::KeepAspectRatio );
      painter.setViewport ( rect.x(), rect.y(), size.width(), size.height() );
      painter.setWindow ( mpImageLabel->pixmap()->rect() );
      painter.drawPixmap ( 0, 0, *mpImageLabel->pixmap() );
   }
}

//------------------------------------------------------------------

void ImageWindow::SlotZoomIn()
{
   mpFitToWindowAction->setChecked ( false );
   mpScrollArea->setWidgetResizable ( false );
   mpImageLabel->adjustSize();
   RescaleImage ( 2.0 );
   this->update();
}

//------------------------------------------------------------------

void ImageWindow::SlotZoomOut()
{
   mpFitToWindowAction->setChecked ( false );
   mpScrollArea->setWidgetResizable ( false );
   mpImageLabel->adjustSize();
   RescaleImage ( 0.5 );
   this->update();
}

//------------------------------------------------------------------

void ImageWindow::SlotNormalSize()
{
   mpFitToWindowAction->setChecked ( false );
   mpScrollArea->setWidgetResizable ( false );
   mpImageLabel->adjustSize();
   mScaleFactor = 1.0;
   this->update();
}

//------------------------------------------------------------------

void ImageWindow::SlotRotatePlus90Degrees()
{
   Image* pRotatedImage = ImageTools::Rotate90DegreesClockwise( mpImage1 );
   pRotatedImage->SetImageName( mpImage1->GetImageName() );
   
   QImage* pQRotatedImage = ImageDataList::ImageToQImage( pRotatedImage );
   QImage* pQTmpImage = mpQImage;
   mpQImage = pQRotatedImage;
   
   ImageDataList::GetInstance()->ReplaceImage( mpImage1, pRotatedImage );
   mpImage1 = pRotatedImage;
   mpProcessManager->SetImage( pRotatedImage );
   
   delete pQTmpImage;
   RenderImage ( pQRotatedImage );
   this->update();
}

//------------------------------------------------------------------

void ImageWindow::SlotRotateMinus90Degrees()
{
   Image* pRotatedImage = ImageTools::Rotate90DegreesCounterClockwise( mpImage1 );
   pRotatedImage->SetImageName( mpImage1->GetImageName() );
   
   QImage* pQRotatedImage = ImageDataList::ImageToQImage( pRotatedImage );
   QImage* pQTmpImage = mpQImage;
   mpQImage = pQRotatedImage;
   
   ImageDataList::GetInstance()->ReplaceImage( mpImage1, pRotatedImage );
   mpImage1 = pRotatedImage;
   mpProcessManager->SetImage( pRotatedImage );
   
   delete pQTmpImage;
   RenderImage ( pQRotatedImage );
   this->update();
}

//------------------------------------------------------------------

void ImageWindow::SlotSetSizeCondition()
{
   if ( GetImage()->GetWidth() < StiraDefinitions::maxWidth )
   {
      setMinimumWidth ( GetImage()->GetWidth() + 13 );
   }
   else
   {
      setMaximumWidth ( StiraDefinitions::maxWidth );
      setMinimumWidth ( StiraDefinitions::maxWidth );
   }
   
   if ( GetImage()->GetHeight() < StiraDefinitions::maxHeight )
   {
      setMinimumHeight ( GetImage()->GetHeight() + 38 );
   }
   else
   {
      setMaximumHeight ( StiraDefinitions::maxHeight );
      setMinimumHeight ( StiraDefinitions::maxHeight );
   }
   SlotNormalSize();
}

//------------------------------------------------------------------

void ImageWindow::SlotClickFitToWindow()
{
   mpFitToWindowAction->setChecked ( true );
   
   cout << "In SlotClickFitToWindow is checked is set to : " << mpFitToWindowAction->isChecked() << endl << flush;
   
   SlotFitToWindow();
}

//------------------------------------------------------------------

void ImageWindow::SlotFitToWindow()
{
   //mpFitToWindowAction->setChecked ( true );
   bool fitToWindow = mpFitToWindowAction->isChecked();
   mpScrollArea->setWidgetResizable ( fitToWindow );
   if ( !fitToWindow )
   {
      SlotSetSizeCondition();
      SlotNormalSize();
   }
   else
   {
      setMinimumSize ( GetImage()->GetWidth() / 10, GetImage()->GetHeight() / 10 );
   }
   UpdateActions();
}

//------------------------------------------------------------------

void ImageWindow::SlotSetMainMenu()
{
   MainWindow::GetInstance()->ResetMainMenu();
   MainWindow::GetInstance()->menuBar()->addMenu ( mpSubMenuFile );
   MainWindow::GetInstance()->menuBar()->addMenu ( mpSubMenuView );
   
   std::vector<QMenu*> menuVector = mpProcessManager->GetMenus();
   for( std::vector<QMenu*>::iterator it = menuVector.begin(); it != menuVector.end(); it++)
   {
      MainWindow::GetInstance()->menuBar()->addMenu ( (*it) );
   }
   MainWindow::GetInstance()->menuBar()->repaint();
}

//------------------------------------------------------------------

Image* ImageWindow::GetImage( )
{
   return mpImage1;
}

//------------------------------------------------------------------

void ImageWindow::CreateActions()
{
   // FILE
   /////////////
   mpSaveAction = new QAction (QIcon(":/filenew.xpm"), tr ( "&Save..." ), this );
   mpSaveAction->setShortcut ( QKeySequence::Save );
   mpSaveAction->setEnabled ( true );
   connect ( mpSaveAction, SIGNAL ( triggered() ), this, SLOT ( SlotSave() ) );
   
   mpPrintAction = new QAction ( tr ( "&Print..." ), this );
   mpPrintAction->setShortcut ( QKeySequence(tr ( "Ctrl+P" ) ));
   mpPrintAction->setEnabled ( true );
   connect ( mpPrintAction, SIGNAL ( triggered() ), this, SLOT ( SlotPrint() ) );

   mpExitAction = new QAction ( tr ( "E&xit" ), this );
   mpExitAction->setShortcut ( QKeySequence(tr ( "Ctrl+Q" ) ));
   connect ( mpExitAction, SIGNAL ( triggered() ), this, SLOT ( close() ) );
   
   // VIEW
   /////////

   mpResetViewOneImageAction = new QAction ( tr ( "Remove 2nd Image" ), this );
   mpResetViewOneImageAction->setEnabled ( true );
   connect ( mpResetViewOneImageAction, SIGNAL ( triggered() ), this, SLOT ( SlotRemoveComparisonImage() ) );
   
   mpZoomInAction = new QAction ( tr ( "Zoom &In (x2)" ), this );
   mpZoomInAction->setShortcut ( tr ( "Ctrl++" ) );
   mpZoomInAction->setEnabled ( true );
   connect ( mpZoomInAction, SIGNAL ( triggered() ), this, SLOT ( SlotZoomIn() ) );

   mpZoomOutAction = new QAction ( tr ( "Zoom &Out (:2)" ), this );
   mpZoomOutAction->setShortcut ( tr ( "Ctrl+-" ) );
   mpZoomOutAction->setEnabled ( true );
   connect ( mpZoomOutAction, SIGNAL ( triggered() ), this, SLOT ( SlotZoomOut() ) );

   mpNormalSizeAction = new QAction ( tr ( "&Normal Size" ), this );
   mpNormalSizeAction->setShortcut ( tr ( "Ctrl+S" ) );
   mpNormalSizeAction->setEnabled ( false );
   connect ( mpNormalSizeAction, SIGNAL ( triggered() ), this, SLOT ( SlotNormalSize() ) );

   mpFitToWindowAction = new QAction ( tr ( "&Fit to Window" ), this );
   mpFitToWindowAction->setEnabled ( true );
   mpFitToWindowAction->setCheckable ( true );
   mpFitToWindowAction->setShortcut ( tr ( "Ctrl+F" ) );
   connect ( mpFitToWindowAction, SIGNAL ( triggered() ), this, SLOT ( SlotFitToWindow() ) );
   
}

//------------------------------------------------------------------

void ImageWindow::contextMenuEvent(QContextMenuEvent *event)
{
   QMenu menu(this);

   menu.addMenu ( mpSubMenuFile );
   menu.addMenu ( mpSubMenuView );
   
   std::vector<QMenu*> menuVector = mpProcessManager->GetMenus();
   for( std::vector<QMenu*>::iterator it = menuVector.begin(); it != menuVector.end(); it++)
   {
      menu.addMenu ( (*it) );
   }
   
   menu.exec(event->globalPos());
}

//------------------------------------------------------------------

void ImageWindow::UpdateActions()
{
   mpZoomInAction->setEnabled ( !mpFitToWindowAction->isChecked() );
   mpZoomOutAction->setEnabled ( !mpFitToWindowAction->isChecked() );
   mpNormalSizeAction->setEnabled ( !mpFitToWindowAction->isChecked() );
}

//------------------------------------------------------------------

void ImageWindow::RescaleImage ( double factor )
{
   Q_ASSERT ( mpImageLabel->pixmap() );
   mScaleFactor *= factor;
   
   ScaleImage ( );

   AdjustScrollBar ( mpScrollArea->horizontalScrollBar(), factor );
   AdjustScrollBar ( mpScrollArea->verticalScrollBar(), factor );
}

//------------------------------------------------------------------

void ImageWindow::ScaleImage ( )
{
   mpImageLabel->resize ( mScaleFactor * mpImageLabel->pixmap()->size() );
}

//------------------------------------------------------------------

void ImageWindow::AdjustScrollBar ( QScrollBar *scrollBar, double factor )
{
   scrollBar->setValue ( int ( factor * scrollBar->value()
                              + ( ( factor - 1 ) * scrollBar->pageStep() /2 ) ) );
}

