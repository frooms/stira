
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

#include <QMessageBox>
#include "ImageDataList.h"
#include "MainWindow.h"
#include "../processes/RegisterImagesProcess.h"
#include "../../stira/imagedata/simpletools/ImageStatistics.h"
#include "../../stira/imagedata/datastructures/Image.h"
#include "../../stira/common/common/StringUtils.h"
#include "../../stira/imagetools/tools/ImageTools.h"
using namespace std;
using namespace stira::image;
using namespace stira::common;

ImageDataList* ImageDataList::spImageDataList=0;

//==========================================================

ImageDataList::ImageDataList() : QListWidget()
{
   setSelectionMode ( QAbstractItemView::ExtendedSelection );
   mpReadNewImageAction         = new QAction( tr ( "&Read Image" ),   this );
   mpCloneImageAction           = new QAction( tr ( "&Clone Image" ),  this );
   mpCompareImagesMSEAction     = new QAction( tr ( "&Compare MSE" ),  this );
   mpCompareImagesSSIMAction    = new QAction( tr ( "&Compare SSIM" ), this );
   mpCompareImagesPearsonAction = new QAction( tr ( "&Pearson Correlation" ), this );
   mpCheckerImageAction         = new QAction( tr ( "Checker Images"), this );
   mpTransparantImageAction     = new QAction( tr ( "Transparant Images"), this );
   mpRegisterImageAction        = new QAction( tr ( "Register Images"), this );
   mpMergeRGBAction             = new QAction( tr ( "Merge RGB"), this );
   mpRemoveImageAction          = new QAction( tr ( "&Remove Image" ), this );
   mpRemoveAllImagesAction      = new QAction( tr ( "&Remove All Images" ), this );
   
   connect ( this, SIGNAL ( itemClicked ( QListWidgetItem * ) ), this, SLOT ( SlotShowItem( QListWidgetItem *) ) );
   connect ( mpCloneImageAction,           SIGNAL ( triggered() ), this, SLOT ( SlotCloneImage() ) );
   connect ( mpReadNewImageAction,         SIGNAL ( triggered() ), this, SLOT ( SlotReadImageFromFile() ) );
   connect ( mpCompareImagesMSEAction,     SIGNAL ( triggered() ), this, SLOT ( SlotCompareImagesMSE() ) );
   connect ( mpCompareImagesSSIMAction,    SIGNAL ( triggered() ), this, SLOT ( SlotCompareImagesSSIM() ) );
   connect ( mpCompareImagesPearsonAction, SIGNAL ( triggered() ), this, SLOT ( SlotCompareImagesPearson() ) );
   connect ( mpRegisterImageAction,        SIGNAL ( triggered() ), this, SLOT ( SlotRegisterImages() ) );
   connect ( mpRemoveImageAction,          SIGNAL ( triggered() ), this, SLOT ( SlotRemoveSelectedImages() ) );
   connect ( mpRemoveAllImagesAction,      SIGNAL ( triggered() ), this, SLOT ( SlotRemoveAllImages() ) );
   connect ( mpCheckerImageAction,         SIGNAL ( triggered() ), this, SLOT ( SlotCheckerImages() ) );
   connect ( mpTransparantImageAction,     SIGNAL ( triggered() ), this, SLOT ( SlotTransparantImages() ) );
   connect ( mpMergeRGBAction,             SIGNAL ( triggered() ), this, SLOT ( SlotMergeImagesRGB() ) );
   
   //mpSettings = new QSettings("/t/tmp/.stira.ini", QSettings::IniFormat);
}

//==========================================================

ImageDataList::~ImageDataList()
{
}

//==========================================================

ImageDataList* ImageDataList::GetInstance()
{
   if (spImageDataList == 0)
   {
      spImageDataList = new ImageDataList();
   }
   return spImageDataList;
}

//==========================================================

void ImageDataList::SlotShowItem(QListWidgetItem *pItem)
{
   if ( !(selectedItemsToDelete.contains ( pItem )))
   {
      DataListItem dataItem = mMap[pItem];
      dataItem.pViewer->RepaintImage();
   }
   else
   {
      cout << "Ignored request to show item while deleting selected items!!!" << endl << flush;
   }
}

//==========================================================

void ImageDataList::contextMenuEvent(QContextMenuEvent *event)
{
   QMenu menu(this);
   menu.addAction( mpReadNewImageAction );
   if ( !(mMap.empty() ) && ( this->count() != 0) )  // in fact two times the same check, but better safe than sorry...
   {
      QListWidgetItem* pItem = currentItem ();
      DataListItem dataItem = mMap[pItem];
      dataItem.pViewer->RepaintImage();
      menu.addAction( mpCloneImageAction );
      menu.addAction( mpRemoveImageAction );
      menu.addAction( mpRemoveAllImagesAction );
      
      menu.addAction( mpCompareImagesMSEAction );
      menu.addAction( mpCompareImagesSSIMAction );
      menu.addAction( mpCompareImagesPearsonAction );
      menu.addAction( mpCheckerImageAction );
      menu.addAction( mpTransparantImageAction );
      menu.addAction( mpRegisterImageAction );
      menu.addAction( mpMergeRGBAction );
   }
   menu.exec(event->globalPos());
}

//==========================================================

std::vector< Image* > ImageDataList::GetImages( )
{
   std::vector< Image* > vImageVector;
   
   QList< QListWidgetItem *> selectedItems = this->selectedItems ();
   
   for (QList< QListWidgetItem * >::iterator it = selectedItems.begin(); it != selectedItems.end(); ++it)
   {
      QListWidgetItem *pItem = *it;
      
      DataListItem dataItem = mMap[pItem];
      vImageVector.push_back( dataItem.pData );
   }
   return vImageVector;
}

//==========================================================

ImageWindow* ImageDataList::GetWindowFromImage( stira::image::Image* pData )
{
   for( std::map< QListWidgetItem* , DataListItem >::iterator it = mMap.begin(); 
        it != mMap.end(); 
        it++
      )
   {
      if ( ((it->second).pData) == pData)
      {
         return (it->second).pViewer;
      }
   }
   return 0;
}

//==========================================================

void ImageDataList::SlotCompareImagesMSE(  )
{
   std::vector< Image* > vImageVector = GetImages( );
   if (vImageVector.size() == 2)
   {
      Image* pImage1 = vImageVector[0];
      Image* pImage2 = vImageVector[1];
      Image* pCompareImage = ImageTools::CreateImageSSD( pImage1, pImage2 );
      if (pCompareImage != 0)
      {
         AddImage( pCompareImage );
      }
      else
      {
         QMessageBox::information ( this, tr ( "Error" ), tr ( "Failed to compare images (check if image dimensions and nr of bands are equal)..." ) );
      }
   }
   else
   {
      QMessageBox::information ( this, tr ( "Warning" ), tr ( "Select exactly two images to compare..." ) );
   }
}

//==========================================================

void ImageDataList::SlotCompareImagesPearson(  )
{
   std::vector< Image* > vImageVector = GetImages( );
   if (vImageVector.size() == 2)
   {
      Image* pImage1 = vImageVector[0];
      Image* pImage2 = vImageVector[1];
      
      ArrayGrid<double>* pPearson = NumberGridTools<double>::ComputePearsonCorrelation( pImage1->GetBands()[0], pImage2->GetBands()[0] );
      Image* pCompareImage = new Image( pPearson );
      ImageStatistics::Rescale( pCompareImage, 0.0, 255.0 );
      
      std::string outName = std::string("Pearson-") + pImage1->GetImageName() + std::string("-") + pImage2->GetImageName();
      pCompareImage->SetImageName(outName);
      
      if (pCompareImage != 0)
      {
         AddImage( pCompareImage );
      }
      else
      {
         QMessageBox::information ( this, tr ( "Error" ), tr ( "Failed to compare images (check if image dimensions and nr of bands are equal)..." ) );
      }
   }
   else
   {
      QMessageBox::information ( this, tr ( "Warning" ), tr ( "Select exactly two images to compare..." ) );
   }
}

//==========================================================

void ImageDataList::SlotCompareImagesSSIM(  )
{
   std::vector< Image* > vImageVector = GetImages( );
   if (vImageVector.size() == 2)
   {
      Image* pImage1 = vImageVector[0];
      Image* pImage2 = vImageVector[1];
      
      Image* pCompareImage = ImageTools::CreateImageSSIM( pImage1, pImage2 );
      if (pCompareImage != 0)
      {
         AddImage( pCompareImage );
      }
      else
      {
         QMessageBox::information ( this, tr ( "Error" ), tr ( "Failed to compare images (check if image dimensions and nr of bands are equal)..." ) );
      }
   }
   else
   {
      QMessageBox::information ( this, tr ( "Warning" ), tr ( "Select exactly two images to compare..." ) );
   }
}


//==========================================================

void ImageDataList::SlotMergeImagesRGB( )
{
   std::vector< Image* > vImageVector = GetImages( );
   int nrImages = vImageVector.size();
   if ( (nrImages > 1) && (nrImages <= 3) )
   {
      int width  = vImageVector[0]->GetWidth();
      int height = vImageVector[0]->GetHeight();
      bool haveEqualDimensions = true;
      for (int i = 1; i < nrImages; i++)
      {
         if (vImageVector[i]->GetWidth() != width) {haveEqualDimensions = false;}
         if (vImageVector[i]->GetHeight() != height) {haveEqualDimensions = false;}
      }
      if (haveEqualDimensions)
      {
         bool hasExactlyOneBand = true;
         for (int i = 0; i < nrImages; i++)
         {
            if (vImageVector[i]->GetNumberOfBands() != 1) {hasExactlyOneBand = false;}
         }
         if ( hasExactlyOneBand )
         {
            Image* pRGBImage = new Image( vImageVector[0]->GetWidth(), vImageVector[0]->GetHeight() );
            std::string outNameReal = std::string("MergeRGB");
            pRGBImage->SetImageName(outNameReal);
            
            for (int i = 0; i < nrImages; i++)
            {
               pRGBImage->AddBand( vImageVector[i]->GetBands()[0]->Clone() );
            }
            if (nrImages < 3)
            {
               ArrayGrid<double>* pGrid = new ArrayGrid<double>( vImageVector[0]->GetWidth(), vImageVector[0]->GetHeight() );
               pRGBImage->AddBand( pGrid );
            }
            AddImage( pRGBImage );
         }
         else
         {
            QMessageBox::information ( this, tr ( "Error" ), tr ( "Failed to merge images: input images must all have exactly 1 band!!" ) );
         }
      }
      else
      {
         QMessageBox::information ( this, tr ( "Error" ), tr ( "Failed to merge images: input images must all have the same dimensions!!" ) );
      }
   }
   else
   {
      QMessageBox::information ( this, tr ( "Warning" ), tr ( "Select exactly two images to compare..." ) );
   }
}

//==========================================================

void ImageDataList::SlotCheckerImages(  )
{
   std::vector< Image* > vImageVector = GetImages( );
   if (vImageVector.size() == 2)
   {
      Image* pImage1 = vImageVector[0];
      Image* pImage2 = vImageVector[1];
      
      ImageWindow* pWindow = GetWindowFromImage( pImage1 );
      pWindow->SlotCompareImages( pImage2, /*ImageWindow::COMPARE_TRANSPARANT,*/ ImageWindow::COMPARE_CHECKERED );
   }
   else
   {
      QMessageBox::information ( this, tr ( "Warning" ), tr ( "Select exactly two images to checker..." ) );
   }
}

//==========================================================

void ImageDataList::SlotTransparantImages(  )
{
   std::vector< Image* > vImageVector = GetImages( );
   if (vImageVector.size() == 2)
   {
      Image* pImage1 = vImageVector[0];
      Image* pImage2 = vImageVector[1];
      
      ImageWindow* pWindow = GetWindowFromImage( pImage1 );
      pWindow->SlotCompareImages( pImage2, ImageWindow::COMPARE_TRANSPARANT );
   }
   else
   {
      QMessageBox::information ( this, tr ( "Warning" ), tr ( "Select exactly two images to view transparantly..." ) );
   }
}

//==========================================================

void ImageDataList::ReplaceImage( stira::image::Image* pImageOld, stira::image::Image* pImageNew )
{
   for (std::map< QListWidgetItem* , DataListItem >::iterator it = mMap.begin(); it != mMap.end(); it++ )
   {
      Image* pImageTmp = (*it).second.pData;
      if (pImageTmp == pImageOld)
      {
         (*it).second.pData = pImageNew;
         delete pImageOld;
      }
   }
}

//==========================================================

void ImageDataList::SlotRemoveSingleImage( QListWidgetItem * pItem )
{
   cout << "Now removing item " << pItem << " from list with " << count() << " items left. " << endl << flush;
   
   std::map< QListWidgetItem* , DataListItem >::iterator it = mMap.find(pItem);
   if( it != mMap.end())
   {
      DataListItem dataItem = mMap[pItem];
      
      dataItem.pViewer->hide();
      delete pItem;
      mMap.erase( pItem );
      MainWindow::GetInstance()->SlotRemoveSubWindow( (dataItem.pViewer)->GetParent() );  // Note that the subwindow is not deleted by QMdiArea and that its parent is set to 0.
      delete dataItem.pViewer;
      delete dataItem.pData;
      if (this->count () == 0) {MainWindow::GetInstance()->ResetMainMenu();}
      
      update();
   }
}

//==========================================================

void ImageDataList::SlotRegisterImages(  )
{
   std::vector< Image* > vImageVector = GetImages( );
   if (vImageVector.size() == 2)
   {
      Image* pImageMaster = vImageVector[0];
      Image* pImageSlave  = vImageVector[1];
      RegisterImagesProcess rip( pImageMaster, pImageSlave );
   }
   else
   {
      QMessageBox::information ( this, tr ( "Warning" ), tr ( "Select exactly two images to view transparantly..." ) );
   }
}

//==========================================================

void ImageDataList::SlotRemoveSelectedImages(  )
{
   selectedItemsToDelete.clear ();
   selectedItemsToDelete = this->selectedItems();
   
   for( QList< QListWidgetItem *>::iterator it = selectedItemsToDelete.begin(); 
        it != selectedItemsToDelete.end(); 
        it++
      )
   {
      SlotRemoveSingleImage( *it );
   }
   update();
}

//==========================================================

void ImageDataList::SlotRemoveAllImages(  )
{
   int nrItems = this->count();
   
   for( int i = nrItems-1; i >= 0; i--)
   {
      QListWidgetItem * pItem = this->item( i );
      SlotRemoveSingleImage( pItem );
   }
   update();
}

//==========================================================

void ImageDataList::SlotCloseAllImages(  )
{
   int nrItems = this->count();
   
   for( int i = 0; i < nrItems; i++ )
   {
      QListWidgetItem * pItem = this->item( i );
      std::map< QListWidgetItem* , DataListItem >::iterator it = mMap.find(pItem);
      if( it != mMap.end())
      {
         DataListItem dataItem = mMap[pItem];
      
         (dataItem.pViewer)->GetParent()->close();
      }
   }
   update();
}

//==========================================================

void ImageDataList::AddImage( stira::image::Image* pImage )
{
   if ( pImage != 0)
   {
      ImageWindow* pImgWindow = new ImageWindow ( pImage );
      RegisterEntryInList( pImage, pImgWindow, QString( (pImage->GetImageName()).c_str() ) );
   }
   else
   {
      QMessageBox::information ( this, tr ( "Error" ), tr ( "No image to create an image viewer with." ) );
   }
}

//==========================================================

void ImageDataList::SlotReadImageFromFile( )
{
   QStringList fileNameList = QFileDialog::getOpenFileNames( this, 
                                                             "Select one or more files to open", 
                                                             MainWindow::GetInstance()->GetSettings()->value("lastReadPath").toString (),
                                                             //QDir::currentPath(), 
                                                             "Images (*.gif *.ppm *.pgm *.bmp *.png *.jpg *.tif *.tiff);; All Files (*)"
                                                           );
   
   for (QStringList::const_iterator it = fileNameList.constBegin(); it != fileNameList.constEnd(); it++)
   {
      ReadImageFromFile( (*it) );
   }
}



//==========================================================

void ImageDataList::SlotCloneImage()
{
   std::vector< Image* > vImageVector = GetImages( );
   for (std::vector< Image* >::iterator it = vImageVector.begin(); it != vImageVector.end(); it++ )
   {
      AddImage( (*it)->Clone() );
   }
}

//==========================================================

void ImageDataList::ReadImageFromFile( QString fileName )
{
   if (!fileName.isEmpty())
   {
      QImage* pQImage = new QImage ( fileName );
      
      ImageWindow* pImgWindow = new ImageWindow( pQImage );
      Image* pImage = pImgWindow->GetImage( );
      
      std::string justFileName = StringUtils::ExtractFileNameRoot( fileName.toStdString() );
      std::string pathName = StringUtils::ExtractPathOfFileName( fileName.toStdString() );
      MainWindow::GetInstance()->GetSettings()->setValue( "lastReadPath", pathName.c_str() );
      pImage->SetImageName( justFileName );
      RegisterEntryInList( pImage, pImgWindow, QString( justFileName.c_str() ) );
   }
}

//==========================================================

void ImageDataList::RegisterEntryInList( Image* pImage, ImageWindow* pImgWindow, QString entryName )
{
   QListWidgetItem* pItem = new QListWidgetItem( entryName, this );
   
   DataListItem dataItem;
   dataItem.pViewer = pImgWindow;
   dataItem.pData = pImage;
   mMap[pItem] = dataItem;
   MainWindow::GetInstance()->SlotAddSubWindow( pImgWindow, entryName );
   
   connect( pImgWindow->GetParent(), SIGNAL( aboutToActivate () ), pImgWindow, SLOT( SlotSetMainMenu() ) );
   
   cout << "RegisterEntryInList::AddImage -> pItem = " << pItem << " dataItem.pViewer = " << dataItem.pViewer << " and dataItem.pData = " << dataItem.pData << endl << flush;
}

//==========================================================

int ImageDataList::ClipQColorValue ( int value )
{
   if ( value < 0 )
   {
      value = 0;
   }
   if ( value > 255 )
   {
      value = 255;
   }
   return value;
}

//==========================================================

QImage* ImageDataList::ImageToQImage ( stira::image::Image* pImage )
{
   int width = pImage->GetWidth();
   int height = pImage->GetHeight();
   int nrBands = pImage->GetNumberOfBands();
   QImage* pQImg = new QImage ( width, height, QImage::Format_RGB32 );
   if ( nrBands >= 3 )
   {
      for ( int y = 0; y < height; y++ )
      {
         for ( int x = 0; x < width; x++ )
         {
            int R = ClipQColorValue ( ( int ) ( pImage->GetBands() [0]->GetValue ( x, y ) ) );
            int G = ClipQColorValue ( ( int ) ( pImage->GetBands() [1]->GetValue ( x, y ) ) );
            int B = ClipQColorValue ( ( int ) ( pImage->GetBands() [2]->GetValue ( x, y ) ) );
            QColor localColor ( R, G, B, 255 );
            pQImg->setPixel ( x, y, localColor.rgba() );
         }
      }
   }
   else
   {
      for ( int y = 0; y < height; y++ )
      {
         for ( int x = 0; x < width; x++ )
         {
            int R = ClipQColorValue ( ( int ) ( pImage->GetBands() [0]->GetValue ( x, y ) ) );
            int G = R;
            int B = R;
            QColor localColor ( R, G, B, 255 );
            pQImg->setPixel ( x, y, localColor.rgba() );
         }
      }
   }
   return pQImg;
}

//==========================================================

stira::image::Image* ImageDataList::QImageToImage ( QImage* pQImage )
{
   int width = pQImage->width();
   int height = pQImage->height();
   stira::image::Image* pImage = 0;
   if ( pQImage->allGray() )
   {
      pImage = new Image( width, height, 1 );
      for ( int y = 0; y < height; y++ )
      {
         for ( int x = 0; x < width; x++ )
         {
            QRgb qcolor = pQImage->pixel( x, y );
            pImage->GetBands() [0]->SetValue ( x, y, qRed( qcolor ) );
         }
      }
   }
   else
   {
      pImage = new Image( width, height, 3 );
      for ( int y = 0; y < height; y++ )
      {
         for ( int x = 0; x < width; x++ )
         {
            QRgb qcolor = pQImage->pixel( x, y );
            pImage->GetBands()[0]->SetValue ( x, y, qRed ( qcolor ) );
            pImage->GetBands()[1]->SetValue ( x, y, qGreen( qcolor ) );
            pImage->GetBands()[2]->SetValue ( x, y, qBlue ( qcolor ) );
         }
      }
   }
   return pImage;
}



