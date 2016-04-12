
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

#ifndef STIRAGUI_PROCESSES_GENERATEPERLINNOISEPROCESS_H
#define STIRAGUI_PROCESSES_GENERATEPERLINNOISEPROCESS_H

#include "Process.h"

#include "../src/ImageWindow.h"

class GeneratePerlinNoiseDialog;

class GeneratePerlinNoiseProcess : public Process
{
    Q_OBJECT

public:

   /** \brief constructor
     * \param pImWindow image window to extract input from*/
   GeneratePerlinNoiseProcess( );
   virtual ~GeneratePerlinNoiseProcess();
   
   int GetWidth();
   void SetWidth( int width );
   
   int GetHeight();
   void SetHeight( int height );
   
   double GetPersistence();
   void SetPersistence( double p );
   
   int GetNumberOfOctaves();
   void SetNumberOfOctaves( int nrOctaves );
   
   double GetRedFactor();
   void SetRedFactor( double factor );
   
   double GetGreenFactor();
   void SetGreenFactor( double factor );
   
   double GetBlueFactor();
   void SetBlueFactor( double factor );
   
   int GetSeed();
   void SetSeed( int seed );
   
   double GetZoom();
   void SetZoom( double zoom );
   
   bool GetUseNormalization();
   void SetUseNormalization( bool useNormalize );
   
   void run();
   
private:

   int mWidth;
   int mHeight;
   int mNrOctaves;
   double mRed;
   double mGreen;
   double mBlue;
   double mPersistence;
   int mSeed;
   double mZoom;
   
   bool mUseNormalization;
   
   enum StiraDefinitions::SyntheticImageType mImageType;
};

#endif
