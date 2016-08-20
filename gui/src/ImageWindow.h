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
#ifndef STIRAGUI_MAIN_IMAGEWINDOW_H
#define STIRAGUI_MAIN_IMAGEWINDOW_H

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

class ProcessManager;

class QAction;
class QLabel;
class QMenu;
class QScrollArea;
class QScrollBar;
class QSlider;

class MainWindow;


/** \brief a widget to view an image in the GUI
  * Is embedded in an MDI subwindow */
class ImageWindow : public QWidget
{
   Q_OBJECT

public:
   /** \brief constructor
     * Creates an image viewer and creates an image from reading a disk file */
   ImageWindow( QImage* pQImage );
   
   /** \brief constructor
     * Creates an image viewer with an externally created image */
   ImageWindow( stira::imagedata::Image* pImage );
   
   /** \brief destructor */
   ~ImageWindow( );
   
   stira::imagedata::Image* GetImage( );
   
   enum ComparisonMode{COMPARE_TRANSPARANT, COMPARE_CHECKERED, COMPARE_NONE};
   
   void RepaintImage();
   QMdiSubWindow* GetParent();
   void SetParent( QMdiSubWindow* pParentWindow );
   
public slots:
   void SlotSetMainMenu();
   void SlotSave();
   void SlotPrint();
   void SlotZoomIn();
   void SlotZoomOut();
   void SlotNormalSize();
   void SlotFitToWindow();
   void SlotClickFitToWindow();
   void SlotSetSizeCondition();

   void contextMenuEvent( QContextMenuEvent *event );
   void SlotRemoveComparisonImage( );
   void SlotCompareImages( stira::imagedata::Image* pImage, ComparisonMode mode );

   void SlotReRenderTransparantImage( int sliderPosition );

   void SlotReRenderCheckerImage( int blockSize );

   void SlotRotatePlus90Degrees();
   void SlotRotateMinus90Degrees();

private:
   // creates a mixed color from intensities at given position (x,y) from 2 input images 
   // for all combinations where the images have 1 or three bands (31 means that the first 
   // image has three bands and the second image only 1)
   QRgb GetMixedColor33( int x, int y, double fraction );
   QRgb GetMixedColor31( int x, int y, double fraction );
   QRgb GetMixedColor13( int x, int y, double fraction );
   QRgb GetMixedColor11( int x, int y, double fraction );
   
   // creates a QRgb from intensities at given position (x,y) from an input image
   // (GetQColor1BandImage2 means we get the color from image 2 which has only 1 band)
   QRgb GetQColor3BandsImage1( int x, int y );
   QRgb GetQColor1BandImage1(  int x, int y );
   QRgb GetQColor3BandsImage2( int x, int y );
   QRgb GetQColor1BandImage2(  int x, int y );

   ProcessManager* mpProcessManager;  ///< object that does the actual processing of the image 
                                      ///< shown in this viewer window. Is initialized at construction 
                                      ///< of ImageWindow; also has a method "SetImage" when the image 
                                      ///< in the window changes
   
   /** \brief sets all member pointers initially to "0" */
   void InitializePointers( );
   void SetupWindow();
   void SetupImage( );
   void RenderImage ( QImage* pQImage );
   
   /** \brief creates the menus that are specific for the image viewer
     * These are the "File" and "View" menu's
     * The processing menuss are handled by the ProcessManager object*/
   void CreateMenus( );

   bool mIsFirstRender;
   
  // WAS ALREADY IN ORIGINAL IMAGE VIEWER
  ///////////////////////////////////////

   void OpenImage(QString fileName);
   void CreateActions();
  
   void UpdateActions();
   void ScaleImage( );
   void RescaleImage ( double factor );
   void AdjustScrollBar(QScrollBar *scrollBar, double factor);


   ClickableLabel* mpImageLabel;
   //QLabel* mpImageLabel;
   QImage* mpQImage;
   QMdiSubWindow* mpParentWindow;
   QScrollArea* mpScrollArea;
   double mScaleFactor;

   QPrinter mPrinter;

   QAction* mpSaveAction;
   QAction* mpPrintAction;
   QAction* mpExitAction;
   QAction* mpZoomInAction;
   QAction* mpZoomOutAction;
   QAction* mpNormalSizeAction;
   QAction* mpFitToWindowAction;
   QAction* mpAboutAction;
   QAction* mpAboutQtAction;
   QAction* mpResetViewOneImageAction;
   
   QMenu* mpSubMenuFile;
   QMenu* mpSubMenuView;
   
   QPushButton* mpZoomInButton;
   QPushButton* mpZoomOutButton;
   QPushButton* mpZoom100PercentButton;
   QPushButton* mpFitToWindowButton;
   QPushButton* mpRemove2ndImageButton;
   QPushButton* mpRotateRightButton;
   QPushButton* mpRotateLeftButton;
   
   QHBoxLayout* mpButtonLayout;
   QVBoxLayout* mpWidgetsLayout;
   QGridLayout* mpWindowLayout;
   QSlider* mpSlider;  ///< slider to control checker size or transparancy amaount
   
   bool mIsFirstRendering;  ///< keeps track if this is the first time that the image is rendered in the window

   ComparisonMode mComparisonMode;  ///< hwn comparing two images, choose mode transparant or checkered
   stira::imagedata::Image* mpImage1;  ///< the underlying image data of image window
   stira::imagedata::Image* mpImage2;  ///< the underlying image data of the comparison image when viewed checkered or transparant
};

#endif
