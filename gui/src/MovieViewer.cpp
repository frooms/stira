
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

#include "MovieViewer.h"
#include "MainWindow.h"
#include <QGridLayout>
#include <time.h>  
#include <stdio.h>
#include <iostream>

using namespace std;


MovieViewer::MovieViewer( QString filename ) : QDialog( MainWindow::GetInstance(), Qt::WindowStaysOnTopHint)
{
   /*mpLabel = new QLabel(filename, this );

   this->setAutoFillBackground( true );
   mpLabel->setAutoFillBackground( true );
   
   mpButtonLayout = new QHBoxLayout();
   mpWidgetLayout = new QVBoxLayout( this );
   mpPlayButton = new QPushButton( QString( "|>" ), this );
   mpStopButton = new QPushButton( QString( "||" ), this );
   mpButtonLayout->addWidget(mpPlayButton);
   mpButtonLayout->addWidget(mpStopButton);
   this->adjustSize();
   mpPlayButton->show();
   mpStopButton->show();
   mpPlayButton->repaint();
   mpStopButton->repaint();
   this->repaint();
   mpWidgetLayout->addWidget(mpLabel);
   mpWidgetLayout->addLayout(mpButtonLayout);
   this->show();
   this->adjustSize();
   this->repaint();
   mpLabel->show();
   Play( filename );
   this->update();*/
}

//-------------------------------------------------------------------

MovieViewer::~MovieViewer()
{
}

//-------------------------------------------------------------------
#if 0
int MovieViewer::__nsleep(const struct timespec *req, struct timespec *rem)
{
   struct timespec temp_rem;
   if( nanosleep( req, rem ) == -1 )
   {
      __nsleep( rem, &temp_rem );
   }
   return 1;
}

//-------------------------------------------------------------------

int MovieViewer::msleep(unsigned long milisec)  
{
    struct timespec req = {0, 0},rem = {0, 0};
    time_t sec = (int)( milisec / 1000 );
    milisec = milisec - ( sec * 1000 );
    req.tv_sec  = sec;
    req.tv_nsec = milisec * 1000000L;
    __nsleep( &req, &rem );
    return 1;
}

//-------------------------------------------------------------------

void MovieViewer::AVFrameToQImage ( AVFrame* pFrame, int width, int height )
{
   for ( int y = 0; y < height; y++ )
   {
      unsigned char *pI = pFrame->data[0]+y*pFrame->linesize[0]; // pointer to beginning of line y in frame
      for ( int x = 0; x < width; x++ )
      {
         int R = *(pI + 3 * x);
         int G = *(pI + 3 * x+1);
         int B = *(pI + 3 * x+2);
         QColor localColor ( R, G, B, 255 );
         mpFrameImage->setPixel ( x, y, localColor.rgba() );
      }
   }
   
   mpLabel->setPixmap ( QPixmap::fromImage ( *mpFrameImage ) );
   mpLabel->repaint();
   this->adjustSize();
   mpPlayButton->show();
   mpStopButton->show();
   mpPlayButton->repaint();
   mpStopButton->repaint();
   this->repaint();
}

//-------------------------------------------------------------------

int MovieViewer::Play(QString fn) // fn is the file name you want to play (with path)
{
   AVFormatContext *pFormatCtx;
   int             i, videoStream;
   AVCodecContext  *pCodecCtx;
   AVCodec         *pCodec;
   AVFrame         *pFrame; 
   AVFrame         *pFrameRGB;
   AVPacket        packet;
   int             frameFinished;
   int             numBytes;
   uint8_t         *buffer;
   std::string stlFileName = fn.toStdString ();
   char* charFileName = const_cast<char*>(stlFileName.c_str());
   
   // Register all formats and codecs
   av_register_all();

   // Open video file
   if(av_open_input_file(&pFormatCtx, charFileName, NULL, 0, NULL)!=0)
      return -1; // Couldn't open file

    // Retrieve stream information
   if(av_find_stream_info(pFormatCtx)<0)
      return -1; // Couldn't find stream information

   // Dump information about file onto standard error
   dump_format(pFormatCtx, 0, charFileName, false);

   // Find the first video stream
   videoStream=-1;
   for(i = 0; i < (int)(pFormatCtx->nb_streams); i++)
   {
      if(pFormatCtx->streams[i]->codec->codec_type==CODEC_TYPE_VIDEO)
      {
         videoStream=i;
         break;
      }
   } 
   if(videoStream==-1)
   {
      return -1; // Didn't find a video stream
   }
    
   // Get a pointer to the codec context for the video stream
   pCodecCtx=pFormatCtx->streams[videoStream]->codec;

   // Find the decoder for the video stream
   pCodec=avcodec_find_decoder(pCodecCtx->codec_id);
   if(pCodec==NULL)
   {
      return -1; // Codec not found
   }
    
   // Open codec
   if(avcodec_open(pCodecCtx, pCodec)<0)
   {
      return -1; // Could not open codec
   }
   
   // Hack to correct wrong frame rates that seem to be generated by some 
   // codecs
   // if(pCodecCtx->frame_rate>1000 && pCodecCtx->frame_rate_base==1)
   //    pCodecCtx->frame_rate_base=1000;

   // Allocate video frame
   pFrame=avcodec_alloc_frame();

   // Allocate an AVFrame structure
   pFrameRGB=avcodec_alloc_frame();
   if(pFrameRGB==NULL)
        return -1;

    // Determine required buffer size and allocate buffer
   numBytes=avpicture_get_size(PIX_FMT_RGB24, pCodecCtx->width,
        pCodecCtx->height);
   buffer=new uint8_t[numBytes];

   // Assign appropriate parts of buffer to image planes in pFrameRGB
   avpicture_fill((AVPicture *)pFrameRGB, buffer, PIX_FMT_RGB24,
        pCodecCtx->width, pCodecCtx->height);

   mpFrameImage = new QImage ( pCodecCtx->width, pCodecCtx->height, QImage::Format_RGB32 );
   mpLabel->setPixmap ( QPixmap::fromImage ( *mpFrameImage ) );
   mpLabel->adjustSize ();
   this->adjustSize();
   mpLabel->show();
   mpLabel->repaint();
   this->repaint();

   // Read frames and save first five frames to disk
   i=0;
   while(av_read_frame(pFormatCtx, &packet)>=0)
   {
      // Is this a packet from the video stream?
      if(packet.stream_index==videoStream)
      {
         // Decode video frame
         avcodec_decode_video( pCodecCtx, pFrame, &frameFinished, packet.data, packet.size );

         // Did we get a video frame?
         if(frameFinished)
         {
        // Older removed code: uses deprecated "img_convert"
        /////////////////////////////////////////////////////
               // Convert the image from its native format to RGB swscale
               img_convert((AVPicture *)pFrameRGB, PIX_FMT_RGB24, (AVPicture*)pFrame, pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height);

                
        /*
        // BEGIN new code: uses "img_convert_ctx"
        /////////////////////////////////////////////////////
            // function template, for reference
               int sws_scale(struct SwsContext *context, uint8_t* src[], int srcStride[], int srcSliceY, int srcSliceH, uint8_t* dst[], int dstStride[]);
            
            // Convert the image into YUV format that SDL uses
            static struct SwsContext *img_convert_ctx = NULL;
            if (img_convert_ctx == NULL)
            {
               int w = pCodecCtx->width;
               int h = pCodecCtx->height;
               
               img_convert_ctx = sws_getContext( w, h, pCodecCtx->pix_fmt, 
                                                 w, h, PIX_FMT_RGB24, SWS_BICUBIC,
                                                 NULL, NULL, NULL
                                               );
               if(img_convert_ctx == NULL)
               {
                  fprintf(stderr, "Cannot initialize the conversion context!\n");
                  exit(1);
               }
            }
            // function template, for reference
            //  int sws_scale(struct SwsContext *context, uint8_t* src[], int srcStride[], int srcSliceY, int srcSliceH, uint8_t* dst[], int dstStride[]);
            int ret = sws_scale( img_convert_ctx, pFrame->data, pFrame->linesize, 0, 
                                 pCodecCtx->height, pFrameRGB->data, pFrameRGB->linesize
                               );
            if ( ret )
            {
               fprintf(stderr, "SWS_Scale failed [%d]!\n", ret);
               exit(-1);
            }
        // END new code: uses "img_convert_ctx"
        /////////////////////////////////////////////////////
             */

            AVFrameToQImage ( pFrameRGB, pCodecCtx->width, pCodecCtx->height );
            msleep( 70 );
         }
      }

      // Free the packet that was allocated by av_read_frame
      av_free_packet(&packet);
   }

   // Free the RGB image
   delete [] buffer;
   av_free(pFrameRGB);

   // Free the YUV frame
   av_free(pFrame);

   // Close the codec
   avcodec_close(pCodecCtx);

   // Close the video file
   av_close_input_file(pFormatCtx);
   return 0;
}
#endif

//-------------------------------------------------------------------
