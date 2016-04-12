
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

#ifndef STIRAGUI_MAIN_MOVIEVIEWER_H
#define STIRAGUI_MAIN_MOVIEVIEWER_H

#include <QDialog>
#include <QMdiSubWindow>
#include <QLabel>
#include <QProcess>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>

//#include <avcodec.h>
//#include <avformat.h>


/** \brief dialog to show movies; 
  * experimenting launching mplayer by qt based on :
  *      http://www.inb.uni-luebeck.de/~boehme/libavcodec_update.html
  * with code corrections from 
  *      http://www.cryptosystem.org/archives/2006/03/libavcodec-libavformat-sample-code/ */
class MovieViewer : public QDialog
{

    Q_OBJECT

public:
   /** \brief constructor
     * \param pImWindow window from which the input image for processing will be extracted*/
   MovieViewer( QString filename );
   
   /** \brief destructor*/
   virtual ~MovieViewer();
#if 0
   /** \brief load movie in file fn and play
     * \param fn name of movie file to be loaded and played */
   int Play(QString fn);
   
private:

   int __nsleep(const struct timespec *req, struct timespec *rem);

   int msleep(unsigned long milisec);

   void AVFrameToQImage ( AVFrame* pFrameRGB, int width, int height );
   QImage* mpFrameImage;
   QLabel* mpLabel;
   QHBoxLayout* mpButtonLayout;
   QVBoxLayout* mpWidgetLayout;
   QGridLayout* mpDialogLayout;
   QPushButton* mpPlayButton;
   QPushButton* mpStopButton;
#endif
};

#endif
