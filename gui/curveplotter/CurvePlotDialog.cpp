
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

#include "CurvePlotDialog.h"

using namespace std;
using namespace stira::image;

CurvePlotDialog::CurvePlotDialog( QString plotTitle ) : QDialog(0, Qt::WindowStaysOnTopHint)
{
   mPlotName = plotTitle;
   Initialize( );
}

//--------------------------------------------------------

CurvePlotDialog::~CurvePlotDialog()
{
   delete []mpX;
   for (int bandNr = 0; bandNr < mNrOfBands; bandNr++)
   {
      delete []mppY[bandNr];
   }
   delete []mppY;
}

//--------------------------------------------------------

void CurvePlotDialog::Initialize( )
{
   srand((unsigned)time(0));

   setMinimumWidth ( 750 );
   setAttribute( Qt::WA_DeleteOnClose );
   mpDialogLayout = new QGridLayout( this );
   mpQwtPlot = new QwtPlot( QwtText( mPlotName ), this );
}

//--------------------------------------------------------

void CurvePlotDialog::PlotData( )
{
   for (int bandNr = 0; bandNr < mNrOfBands; bandNr++)
   {
      FormatNextCurve( bandNr );
      QwtPlotCurve *pCurve = new QwtPlotCurve(""); // add curve
      pCurve->setSamples( mpX, mppY[bandNr], mNrOfDataPoints );  // copy the data into the curves
      pCurve->setPen( mPen );
      pCurve->setBrush( mBrush );
      pCurve->attach( mpQwtPlot );
   }
   mpQwtPlot->replot();   // finally, refresh the plot
   
   mpDialogLayout->addWidget( mpQwtPlot );
   this->show();
}

//--------------------------------------------------------

void CurvePlotDialog::FormatNextCurve( int bandNr )
{
   mBrush.setStyle( Qt::SolidPattern );
   if (mNrOfBands == 1)
   {
      mPen.setColor ( QColor(0,0,0) );
      mBrush.setColor ( QColor(0,0,0,50) );;
   }
   else if (mNrOfBands <= 3)
   {
      switch (bandNr)
      {
         case 0:
         {
            mPen.setColor ( QColor(255,0,0) );
            mBrush.setColor ( QColor(255,0,0,50) );
            break;
         }
         case 1:
         {
            mPen.setColor ( QColor(0,255,0) );
            mBrush.setColor ( QColor(0,255,0,50) );
            break;
         }
         case 2:
         {
            mPen.setColor ( QColor(0,0,255) );
            mBrush.setColor ( QColor(0,0,255,50) );
            break;
         }
      }
   }
   else
   {
      int R = int( (double)(COLORRANGE) * ((double)(rand()) / (double)(RAND_MAX + 1.0)));
      int G = int( (double)(COLORRANGE) * ((double)(rand()) / (double)(RAND_MAX + 1.0)));
      int B = int( (double)(COLORRANGE) * ((double)(rand()) / (double)(RAND_MAX + 1.0)));
      mPen.setColor ( QColor(R, G, B) );
      mBrush.setColor ( QColor(R, G, B,50) );
   }
}

//--------------------------------------------------------
