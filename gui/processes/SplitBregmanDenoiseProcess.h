
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

#ifndef STIRAGUI_PROCESSES_SPLITBREGMANDENOISEPROCESS_H
#define STIRAGUI_PROCESSES_SPLITBREGMANDENOISEPROCESS_H

#include "Process.h"

/** \brief class to actually run anisotropic diffusion process in a separate thread*/
class SplitBregmanDenoiseProcess : public Process
{
    Q_OBJECT

public:

   /** \brief constructor
     * \param pImage input image */
   SplitBregmanDenoiseProcess( stira::imagedata::Image* pImage );
   virtual ~SplitBregmanDenoiseProcess();
   
   double GetMu();
   void SetMu( double mu );
   
   double GetLambda();
   void SetLambda( double lambda );
   
   int GetNumberOfGaussSeidelIterations();
   void SetNumberOfGaussSeidelIterations( int nGS );
   
   int GetNumberOfBregmanIterations();
   void SetNumberOfBregmanIterations( int nBreg );

   bool GetIsIsotropic( );
   void SetIsIsotropic( bool flag );
   
   void run();
   
private:
   
   double mMu;
   double mLambda;
   int mNumberOfGaussSeidelIterations;
   int mNumberOfBregmanIterations;
   bool mIsIsotropic;
};
#endif
