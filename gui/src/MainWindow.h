
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

#ifndef STIRAGUI_MAIN_MAINWINDOW_H
#define STIRAGUI_MAIN_MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include <QDockWidget>
#include <QFileDialog>

#include <QStackedWidget>
#include <QScrollArea>

#include "ImageWindow.h"
#include "ImageDataList.h"

class QTextEdit;
class GenerateImageDialog;
class GeneratePerlinNoiseDialog;

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
   
   /** \brief gets singleton instance*/
   static MainWindow* GetInstance();
   void ResetMainMenu();
   
   QSettings* GetSettings();
   
protected:
   /** \brief sets up the workspace (the space in which all dockwindows and image viewers appear*/
   void SetupWorkspace();
   
   /** \brief sets up the dock windows in which the images are shown (loaded or created) */
   void SetupDataDockWidget();

public slots:

   /** \brief slot to call dialog with some background information about this application*/
   void SlotAbout();
   
   /** \brief slot to generate new image */
   void SlotSelectGenerateImage();

   /** \brief slot to generate Perlin noise clouds */
   void SlotSelectGeneratePerlin();
   
   /** \brief slot to generate new image */
   void SlotOpenVideo();
   
   void SlotAddSubWindow( QWidget* pWidget, QString windowname );
   
   void SlotRemoveSubWindow( QMdiSubWindow* pSubWindow );
private:
   /** \brief singleton constructor*/
   MainWindow();
   
   /** \brief destructor*/
   virtual ~MainWindow();
   
   static MainWindow* spMainWindowInstance; ///< Main window singleton instance
   GenerateImageDialog* mpGenerateImageDialog;  ///< image generation dialog
   GeneratePerlinNoiseDialog* mpGeneratePerlinNoiseDialog;  ///< image with perlin noise generation dialog

   QScrollArea*    mpScrollArea;
   QMdiArea*       mpMdiArea;   ///< workspace of the MDI window (central widget)
   QDockWidget*    mpDataDock;
   QMenu* mpMainMenu;
   QMenu* mpHelpMenu;
   QSettings* mpSettings;
};

#endif
