
/****************************************************************************
 **
 ** Copyright (C) 2005-2007 Trolltech ASA. All rights reserved.
 **
 ** This file is part of the example classes of the Qt Toolkit.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **
 ****************************************************************************/

/***********************************************************************************
 *   Copyright (C) 2008 by Filip Rooms        (modifications)                      *
 *                                                                                 *
 *  Terms and conditions for using this software in any form are provided in the   *
 *  file COPYING, which can be found in the root directory of this project.        *
 *                                                                                 *
 *   Contact data: filip.rooms@gmail.com                                           *
 *                 http://www.filiprooms.be/                                       *
 *                                                                                 *
 ***********************************************************************************/
#ifndef STIRAGUI_MAIN_INTERACTIVEIMAGEWINDOW_H
#define STIRAGUI_MAIN_INTERACTIVEIMAGEWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QPrinter>
#include <QMenuBar>
#include <QMdiSubWindow>
#include <QVBoxLayout>
#include <QContextMenuEvent>
#include <QFrame>

#include "ClickableLabel.h"
#include "../../stira/imagedata/datastructures/Image.h"
#include "../../stira/imagetools/imagegenerator/FractalGenerator.h"

class ProcessManager;

class QAction;
class QLabel;
class QMenu;
class QScrollArea;
class QScrollBar;
class QSlider;

class MainWindow;


/** \brief a widget to interactively view a fractal image in the GUI
  * Is embedded in an MDI subwindow */
class InteractiveImageWindow : public QWidget
{
   Q_OBJECT

public:

   /** \brief constructor
     * Creates an image viewer with an externally created fractal image */
   InteractiveImageWindow( double centerX, double centerY, double width, bool createMandelbrot=true );

   /** \brief destructor */
   ~InteractiveImageWindow( );

   stira::imagedata::Image* GetImage( );

   QMdiSubWindow* GetParent();
   void SetParent( QMdiSubWindow* pParentWindow );

public slots:
   void SlotZoomIn();
   void SlotZoomOut();
   void SlotSetSizeCondition();
   void SlotNormalSize();
   void SlotCleanData();
   void SlotAddToImageList();
   void SlotComputeJulia();

private:

   /** \brief sets all member pointers initially to "0" */
   void InitializePointers( );
   void SetupWindow();
   void SetupImage( );
   void RenderImage ( QImage* pQImage );
   void ReplaceImage( stira::imagedata::Image* pNewImage );

   void CreateZoomFractal(double factor );

   bool mIsFirstRender;

  // WAS ALREADY IN ORIGINAL IMAGE VIEWER
  ///////////////////////////////////////

   void ScaleImage( );
   void AdjustScrollBar(QScrollBar *scrollBar, double factor);

   ClickableLabel* mpImageLabel;
   QImage* mpQImage;
   QMdiSubWindow* mpParentWindow;
   QScrollArea* mpScrollArea;
   double mScaleFactor;

   QVBoxLayout* mpWidgetsLayout;
   QGridLayout* mpWindowLayout;
   QSlider* mpSlider;  ///< slider to control checker size or transparancy amaount

   bool mIsFirstRendering;  ///< keeps track if this is the first time that the image is rendered in the window

   bool mIsMandelbrot;
   double mCX;
   double mCY;
   stira::imagedata::Image* mpImage;  ///< the underlying image data of image window
   stira::imagetools::FractalGenerator* mpFractalGenerator;  ///< the underlying image data of image window
};


#endif // INTERACTIVEIMAGEWINDOW_H
