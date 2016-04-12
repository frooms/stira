
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

#ifndef STIRAGUI_PROCESSES_RICHARDSONLUCYDECONVOLVEPROCESS_H
#define STIRAGUI_PROCESSES_RICHARDSONLUCYDECONVOLVEPROCESS_H

#include "Process.h"

#include "../src/ImageWindow.h"

#include "../definitions/StiraDefinitions.h"
#include "../../stira/deconvolve/deconvolve/RichardsonLucyDeconvolve.h"

class RichardsonLucyDeconvolveProcess : public Process
{
    Q_OBJECT

public:
   /** \brief constructor
     * \param pImage input image */
   RichardsonLucyDeconvolveProcess( stira::image::Image* pImage );
   virtual ~RichardsonLucyDeconvolveProcess();
   
   double GetLambda();
   void SetLambda( double lambda );
   
   double GetBlurLevel();
   void SetBlurLevel( double blurLevel );
   
   int GetNrOfIterations();
   void SetNrOfIterations( int nrIterations );
   
   StiraDefinitions::RLRegularizationType GetRegularizationType();
   void SetRegularizationType( StiraDefinitions::RLRegularizationType myType );
   
   StiraDefinitions::PSFType GetPSFType();
   void SetPSFType( StiraDefinitions::PSFType myType );
   
   void run();
   
private:
   stira::deconvolve::regularizationType ConvertRegularizationType( );
   
   stira::image::ArrayGrid<double>* GeneratePSF();
   
   StiraDefinitions::RLRegularizationType mRegularizationType;
   
   StiraDefinitions::PSFType mPSFType;
   double mLambda;
   double mBlurLevel;
   int mNrOfIterations;
};

#endif
