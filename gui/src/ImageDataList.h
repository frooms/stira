
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

#ifndef STIRAGUI_MAIN_IMAGEDATALIST_H
#define STIRAGUI_MAIN_IMAGEDATALIST_H

#include <map>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>
#include <QSettings>

#include "../../stira/imagedata/datastructures/Image.h"

#include "ImageWindow.h"

/** \brief Management of images and their corresponding ImageWindows for visualization
  * This singleton class is responsible for the management of all open images, either loaded from disk or 
  * created by processing. New data is added to the list and if data is removed from the list, 
  * the corresponding memeory is freed. */
class ImageDataList  : public QListWidget
{
    Q_OBJECT
public:
   struct DataListItem { 
                         ImageWindow* pViewer; 
                         stira::imagedata::Image* pData;
                       };
   
   /** \brief gets singleton instance*/
   static ImageDataList* GetInstance();
   
   /** \brief adds a new image to the data list
     * \param pImage image to add */
   void AddImage( stira::imagedata::Image* pImage );
   
   /** \brief adds a new image to the data list
     * \param pImage image to add */
   void ReplaceImage( stira::imagedata::Image* pImageOld, stira::imagedata::Image* pImageNew );

   /** \brief reads an image from file
     * \param fileName name of the file*/
   void ReadImageFromFile( QString fileName );
   
   ImageWindow* GetWindowFromImage( stira::imagedata::Image* pData );
   
  // BASIC CONVERSIONS BETWEEN FRIEP AND QT/FRIEPGUI
  //////////////////////////////////////////////////
   /** \brief converts our image format to QImage for display
     * \param pImage image in our internal format representation.*/
   static QImage* ImageToQImage( stira::imagedata::Image* pImage );

   /** \brief converts QImage to our image format*/
   static stira::imagedata::Image* QImageToImage( QImage* pQImg );
   
   /** \brief clips value to be in the range 0-255, as required for QColor*/
   static int ClipQColorValue(int value);
   
public slots:

   void SlotShowItem(QListWidgetItem *pItem);
   void SlotReadImageFromFile( );
   void SlotCloneImage();
   void SlotRemoveSingleImage( QListWidgetItem * pItem );
   void SlotRemoveSelectedImages(  );
   void SlotRemoveAllImages();
   void SlotCloseAllImages(  );
   
   void SlotCompareImagesMSE();
   void SlotCompareImagesSSIM();
   void SlotCompareImagesPearson();
   void SlotCheckerImages( );
   void SlotTransparantImages(  );
   void SlotRegisterImages(  );
   void SlotMergeImagesRGB( );

   /** \brief creates a context menu in the image data list*/
   void contextMenuEvent( QContextMenuEvent *event );
private:
   /** \brief static singleton item */
   static ImageDataList* spImageDataList;
   
   /** \brief constructor*/
   ImageDataList();
   
   /** \brief destructor*/
   ~ImageDataList();
 
 
  // OTHER STUFF
  ////////////////

   std::vector< stira::imagedata::Image* > GetImages( );

   void RegisterEntryInList( stira::imagedata::Image* pImage, ImageWindow* pImgWindow, QString entryName );
   QAction* mpReadNewImageAction;  ///< Read new image from file
   QAction* mpCloneImageAction;  ///< deep-copy existing image
   QAction* mpCompareImagesSSIMAction; ///< Compare images using the Structural SIMilarity measure
   QAction* mpCompareImagesMSEAction; ///< Compare images using the Mean Square Error measure
   QAction* mpCompareImagesPearsonAction; ///< Compare Pearson Correlation between two images
   QAction* mpCheckerImageAction;
   QAction* mpTransparantImageAction;
   QAction* mpRemoveImageAction;
   QAction* mpRemoveAllImagesAction;
   QAction* mpMergeRGBAction; ///< Merge three single-banded images into RGB image
   QAction* mpRegisterImageAction;
   //QSettings* mpSettings;
   std::map< QListWidgetItem* , DataListItem > mMap; ///< maps ImageViewer objects the Image objects
   QList< QListWidgetItem *> selectedItemsToDelete;
};

#endif
