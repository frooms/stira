
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
#include "InteractiveImageWindow.h"
#include "MainWindow.h"
#include "ImageDataList.h"
#include "../../stira/common/common/MathUtils.h"
#include "../../stira/common/common/StringUtils.h"
#include "../../stira/imagetools/tools/ImageTools.h"
#include "../../stira/imagedata/simpletools/GridExtender.h"
#include "../../stira/filter/filter/GaussConvolve.h"

using namespace std;
using namespace stira::image;
using namespace stira::common;
using namespace stira::filter;

//------------------------------------------------------------------

InteractiveImageWindow::InteractiveImageWindow (  double centerX, double centerY, double width )
{
   InitializePointers( );
   mpFractalGenerator = new FractalGenerator();
   mpImage = mpFractalGenerator->CreateMandelbrot( centerX, centerY, width );

   if ( mpImage != 0)
   {
      SetupWindow();
      mpQImage = ImageDataList::ImageToQImage ( mpImage );
      SetupImage( );
      this->show();
   }
}

//------------------------------------------------------------------

InteractiveImageWindow::~InteractiveImageWindow( )
{
    SlotCleanData();
}

//------------------------------------------------------------------

void InteractiveImageWindow::InitializePointers( )
{
   mpImage = 0;
   mpQImage = 0;
   mpParentWindow = 0;
   mIsFirstRendering = true;
}

//------------------------------------------------------------------

void InteractiveImageWindow::SetupImage( )
{
   if (mpQImage->format() != QImage::Format_RGB32)
   {
      QImage convertedImg = mpQImage->convertToFormat (QImage::Format_RGB32);
      delete mpQImage;
      mpQImage = new QImage( convertedImg );
   }
   RenderImage ( mpQImage );
}

//------------------------------------------------------------------

void InteractiveImageWindow::CreateZoomFractal( double factor )
{
    Point<double> mathCenter = mpFractalGenerator->GetMathCenterPoint();
    double resolutionX = mpFractalGenerator->GetResolutionX();
    double resolutionY = mpFractalGenerator->GetResolutionY();
    cout << "resolutionX = " << resolutionX << endl;

    Point<int> clickPoint = mpImageLabel->GetPointClicked();

    double mathClickX = (double)(clickPoint.x - mpFractalGenerator->GetPixelWidth()  / 2.0 ) / (double)(resolutionX) + mathCenter.x;
    double mathClickY = (double)(clickPoint.y - mpFractalGenerator->GetPixelHeight() / 2.0 ) / (double)(resolutionY) + mathCenter.y;

    cout << "Previous mathCenter = (" << mathCenter.x << ", " << mathCenter.y << ")" << endl;

    cout << "clickPoint = (" << clickPoint.x << ", " << clickPoint.y << ")" << endl;
    cout << "mathClick = (" << mathClickX << ", " << mathClickY << ")" << endl;

    // full size
    double width = mpFractalGenerator->GetMathWidth() / factor;

    Image* pFractal = mpFractalGenerator->CreateMandelbrot( mathClickX, mathClickY, width );
    this->ReplaceImage(  pFractal );
}

//------------------------------------------------------------------

void InteractiveImageWindow::ReplaceImage( Image* pNewImage )
{
   if (mpImage != 0) {delete mpImage; }
   mpImage = pNewImage;

   QImage* pQImageOld =  mpQImage;
   mpQImage = ImageDataList::ImageToQImage ( mpImage );
   delete pQImageOld;
   if (mpQImage->format() != QImage::Format_RGB32)
   {
      QImage convertedImg = mpQImage->convertToFormat (QImage::Format_RGB32);
      delete mpQImage;
      mpQImage = new QImage( convertedImg );
   }
   RenderImage ( mpQImage );
}

//------------------------------------------------------------------

QMdiSubWindow* InteractiveImageWindow::GetParent()
{
   return mpParentWindow;
}

//------------------------------------------------------------------

void InteractiveImageWindow::SetParent( QMdiSubWindow* pParentWindow )
{
   mpParentWindow = pParentWindow;
}

//------------------------------------------------------------------

Image* InteractiveImageWindow::GetImage( )
{
   return mpImage;
}

//------------------------------------------------------------------

void InteractiveImageWindow::SetupWindow()
{
   mpImageLabel = new ClickableLabel(this);//QLabel;
   mpImageLabel->setBackgroundRole ( QPalette::Base );
   mpImageLabel->setSizePolicy ( QSizePolicy::Ignored, QSizePolicy::Ignored );
   mpImageLabel->setScaledContents ( true );

   mpScrollArea = new QScrollArea;
   mpScrollArea->setBackgroundRole ( QPalette::Dark );
   mpScrollArea->setWidget ( mpImageLabel );

   setWindowTitle ( tr ( "Image Viewer" ) );

   connect( mpImageLabel, SIGNAL( leftButtonClicked() ), this, SLOT( SlotZoomIn() ));
   connect( mpImageLabel, SIGNAL( rightButtonClicked() ), this, SLOT( SlotZoomOut() ));
   connect( mpImageLabel, SIGNAL( middleButtonClicked() ), this, SLOT( SlotAddToImageList() ) );

   mpSlider = new QSlider( Qt::Horizontal, this );
   mpSlider->hide();

   mpWidgetsLayout = new QVBoxLayout;
   mpWidgetsLayout->addWidget( mpScrollArea );
   mpWidgetsLayout->addWidget( mpSlider );
   mpWindowLayout = new QGridLayout( this );
   mpWindowLayout->addLayout( mpWidgetsLayout, 0, 0  );
}

//------------------------------------------------------------------

void InteractiveImageWindow::SlotCleanData()
{
    if (mpQImage != 0)
    {
       delete mpQImage;
    }

    if (mpImage != 0)
    {
       delete mpImage;
    }

    delete mpFractalGenerator;
}

//------------------------------------------------------------------

void InteractiveImageWindow::SlotSetSizeCondition()
{
   if ( mpImage->GetWidth() < StiraDefinitions::maxWidth )
   {
      setMinimumWidth ( mpImage->GetWidth() + 13 );
   }
   else
   {
      setMaximumWidth ( StiraDefinitions::maxWidth );
      setMinimumWidth ( StiraDefinitions::maxWidth );
   }

   if ( mpImage->GetHeight() < StiraDefinitions::maxHeight )
   {
      setMinimumHeight ( mpImage->GetHeight() + 38 );
   }
   else
   {
      setMaximumHeight ( StiraDefinitions::maxHeight );
      setMinimumHeight ( StiraDefinitions::maxHeight );
   }
   SlotNormalSize();
}

//------------------------------------------------------------------

void InteractiveImageWindow::SlotNormalSize()
{
   mpScrollArea->setWidgetResizable ( false );
   mpImageLabel->adjustSize();
   mScaleFactor = 1.0;
   this->update();
}

//------------------------------------------------------------------

void InteractiveImageWindow::SlotZoomIn()
{
    CreateZoomFractal( 1.5 );
}

//------------------------------------------------------------------

void InteractiveImageWindow::SlotZoomOut()
{
    CreateZoomFractal( 2.0 / 3.0 );
}

//------------------------------------------------------------------

void InteractiveImageWindow::SlotAddToImageList()
{
    Image* pImageSnapshot = mpImage->Clone();
    pImageSnapshot->SetImageName("MandelbrotSnapshot");
    ImageDataList::GetInstance()->AddImage( pImageSnapshot );
}

//------------------------------------------------------------------

void InteractiveImageWindow::RenderImage ( QImage* pQImage )
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

   ScaleImage ( );
}

//------------------------------------------------------------------

void InteractiveImageWindow::ScaleImage ( )
{
   mpImageLabel->resize ( mScaleFactor * mpImageLabel->pixmap()->size() );
}

//------------------------------------------------------------------

void InteractiveImageWindow::AdjustScrollBar ( QScrollBar *scrollBar, double factor )
{
   scrollBar->setValue ( int ( factor * scrollBar->value()
                              + ( ( factor - 1 ) * scrollBar->pageStep() /2 ) ) );
}

