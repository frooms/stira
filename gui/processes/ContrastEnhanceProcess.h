
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

#ifndef STIRAGUI_PROCESSES_CONTRASTENHANCEPROCESS_H
#define STIRAGUI_PROCESSES_CONTRASTENHANCEPROCESS_H

#include "Process.h"

class ContrastEnhanceProcess : public Process
{
    Q_OBJECT

public:

   /** \brief constructor
     * \param pImage input image */
   ContrastEnhanceProcess( stira::imagedata::Image* pImage );
   virtual ~ContrastEnhanceProcess();
   
   void SetLowerFraction( double fraction );
   double GetLowerFraction( );
   
   void SetGamma( double gamma );
   double GetGamma( );
   
   void SetUpperFraction( double fraction );
   double GetUpperFraction( );

   void SetWindowSize( int wsize );
   int GetWindowSize( );

   void SetAlphaFactor( double factor );
   double GetAlphaFactor( );
  
   void SetContrastEnhanceType( StiraDefinitions::ContrastEnhanceType );
   StiraDefinitions::ContrastEnhanceType GetContrastEnhanceType();

   void run();
   
private:
   double mGamma;
   double mLowerFraction;
   double mUpperFraction;
   int mWindowSize;
   double mAlphaFactor;
   
   StiraDefinitions::ContrastEnhanceType mType;
   stira::imagedata::Image* RunRetinex( stira::imagedata::Image* pImage, double lowerFraction, double upperFraction);
   stira::imagedata::Image* RunHistogramEqualize( stira::imagedata::Image* pImage );
};
#endif
