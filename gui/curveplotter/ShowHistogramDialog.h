
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

#ifndef STIRAGUI_CURVEPLOTTER__SHOWHISTOGRAMDIALOG_H
#define STIRAGUI_CURVEPLOTTER__SHOWHISTOGRAMDIALOG_H

#include "CurvePlotDialog.h"
#include "../../stira/imagedata/datastructures/Image.h"

/** \brief Parent class for dialog to plot curve with image data in 
  * Warning: we set the extreme values (0 and the max value) to 0 in order to suppress the outliers*/
class ShowHistogramDialog : public CurvePlotDialog
{
    Q_OBJECT

public:
   /** \brief constructor
     * \param pImage input image for processing */
   ShowHistogramDialog( stira::imagedata::Image* pImage );
   
   /** \brief destructor*/
   virtual ~ShowHistogramDialog();
private:

   /** \brief computes image histogram and puts it in a form ready for QwtPlot 
     * \param pImage image for which to compute the histogram*/
   virtual void GetData( stira::imagedata::Image* pImage );

};

#endif
