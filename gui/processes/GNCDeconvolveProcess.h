
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

#ifndef STIRAGUI_PROCESSES_GNCDECONVOLVEPROCESS_H
#define STIRAGUI_PROCESSES_GNCDECONVOLVEPROCESS_H

#include "Process.h"

#include "../definitions/StiraDefinitions.h"

class GNCDeconvolveProcess : public Process
{
    Q_OBJECT

public:
   /** \brief constructor
     * \param pImage input image */
   GNCDeconvolveProcess( stira::image::Image* pImage );
   virtual ~GNCDeconvolveProcess();

   double GetBlurLevel();
   void SetBlurLevel( double blurLevel );
   
   int GetNrOfScales();
   void SetNrOfScales( int nrOfScales );
   
   int GetNrOfOrientations( );
   void SetNrOfOrientations( int nrOfOrientations );
   
   double GetLambda();
   void SetLambda( double lambda );
   
   double GetMu();
   void SetMu( double mu );

   double GetGammaInitial();
   void SetGammaInitial( double gammaInitial );
   
   double GetGammaFinal();
   void SetGammaFinal( double gammaFinal );
   
   double GetUpdateFactor();
   void SetUpdateFactor( double updateFactor );
   
   int GetNrOfIterations();
   void SetNrOfIterations( int nrIterations );
   
   void run();
   
private:
   double mBlurLevel;
   
   int mNrOfScales;
   int mNrOfOrientations;
   double mLambda;
   double mMu;
   double mGammaInitial;
   double mGammaFinal;
   double mUpdateFactor;
   int mNrOfIterations;
};

#endif
