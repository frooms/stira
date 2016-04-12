
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

#ifndef STIRAGUI_CURVEPLOTTER_CURVEPLOTDIALOG_H
#define STIRAGUI_CURVEPLOTTER_CURVEPLOTDIALOG_H

#include <qwt/qwt_plot.h>
#include <qwt/qwt_plot_curve.h>

#include "../../stira/image/datastructures/Image.h"

#include <QDialog>
#include <QBrush>
#include <QPen>
#include <QLabel>
#include <QGridLayout>

#define COLORRANGE 255

/** \brief parent class for plotting curves (based on QWT) */
class CurvePlotDialog : public QDialog
{
    Q_OBJECT

public:
   /** \brief constructor
     * \param pImWindow window from which the input image for processing will be extracted*/
   CurvePlotDialog( QString plotName );
   
   /** \brief destructor*/
   virtual ~CurvePlotDialog();
   
protected:
   /** \brief Initializes parent object */
   void Initialize( );

   /** \brief Actually plots the data sets */
   void PlotData( );
   
   /** \brief Prepares data to be plotted in a form ready for QwtPlot
     * To be implemented in the child classes, depending on what is to be plotted
     * \param pImage image for which to compute the histogram*/
   virtual void GetData( stira::image::Image* pImage )=0;
   
   QString mPlotName;  ///< Title for plot window
   
   QwtPlot* mpQwtPlot;  ///< actual QWT plot object 
   QGridLayout* mpDialogLayout;  ///< grid layout to align plot object in widget
   void FormatNextCurve( int bandNr );  ///< Sets formatting for plotting next curve
   
   QPen mPen;        ///< contains properties for formatting the plot line
   QBrush mBrush;  ///< contains properties for formatting area under the plot line
   int mNrOfBands; ///< nr of spectral bands in the input image
   int mNrOfDataPoints; ///< nr of data points in the plots
   double* mpX;  ///< Numbers for the x axis, format for QwtPlot
   double** mppY;  ///< histogram values for the different bands, format for QwtPlot

};

#endif
