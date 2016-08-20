
/***********************************************************************************
 *   Copyright (C) 2009 by Filip Rooms                                             *
 *                                                                                 *
 *  Terms and conditions for using this software in any form are provided in the   *
 *  file COPYING, which can be found in the root directory of this project.        *
 *                                                                                 *
 *   Contact data: filip.rooms@gmail.com                                           *
 *                 http://www.filiprooms.be/                                       *
 *                                                                                 *
 ***********************************************************************************/

#ifndef STIRAGUI_PROCESSES_SPLITCOLORCHANNELSPROCESS_H
#define STIRAGUI_PROCESSES_SPLITCOLORCHANNELSPROCESS_H

#include "Process.h"
#include "../../stira/imagedata/color/ColorValue.h"

class SplitColorChannelsProcess : public Process
{
    Q_OBJECT

public:

   /** \brief constructor
     * \param pImage input image */
   SplitColorChannelsProcess( stira::imagedata::Image* pImage );

   /** \brief destructor */
   virtual ~SplitColorChannelsProcess();

   /** \brief sets the color space in which to separate the different bands
     * \param colorSpace enum to identify the color space */
   void SetColorSpace( stira::imagedata::ColorType colorSpace );
   
   /** \brief gets the color space in which to separate the different bands */
   stira::imagedata::ColorType GetColorSpace( );

   stira::imagedata::ColorValue GetReferenceIlluminant();
   void SetReferenceIlluminant( stira::imagedata::ColorValue referenceIlluminant );
   
   void run();
   
private:
   stira::imagedata::ColorType mColorSpace; ///< the color space in which to separate the different bands
   stira::imagedata::ColorValue mReferenceIlluminant;
};
#endif
