
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

#ifndef STIRAGUI_CURVEPLOTTER_SHOWRADIALLYAVERAGEDFOURIERSPECTRUMDIALOG_H
#define STIRAGUI_CURVEPLOTTER_SHOWRADIALLYAVERAGEDFOURIERSPECTRUMDIALOG_H

#include "CurvePlotDialog.h"
#include "../../stira/imagedata/datastructures/Image.h"

/** \brief dialog to plot the radially averaged Fourier spectrum of an image
  * Plots separately for all color bands */
class ShowRadiallyAveragedFourierSpectrumDialog : public CurvePlotDialog
{
    Q_OBJECT

public:
   /** \brief constructor
     * \param pImage input image for processing */
   ShowRadiallyAveragedFourierSpectrumDialog( stira::imagedata::Image* pImage );
   
   /** \brief destructor*/
   virtual ~ShowRadiallyAveragedFourierSpectrumDialog();
private:

   /** \brief computes image histogram and puts it in a form ready for QwtPlot 
     * \param pImage image for which to compute the histogram*/
    virtual void GetData( stira::imagedata::Image* pImage );
};

#endif
