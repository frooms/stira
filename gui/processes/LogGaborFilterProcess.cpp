
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
 
#include "LogGaborFilterProcess.h"

#include "../../stira/filter/filter/LogGabor.h"

using namespace stira::image;
using namespace stira::filter;

LogGaborFilterProcess::LogGaborFilterProcess( Image* pImage ) : Process( pImage )
{
   mProcessName = QString("LogGaborFilter Result");
   mCreateRealResponse = true;
   mCreateImagResponse = true;
   mCreateMagnitude = false;
   mCreateTransferResponse = false;
}

//------------------------------------------------------------------

LogGaborFilterProcess::~LogGaborFilterProcess()
{
}

//------------------------------------------------------------------

double LogGaborFilterProcess::GetCenterFrequency()
{
   return mCenterFrequency;
}

//------------------------------------------------------------------

void LogGaborFilterProcess::SetCenterFrequency( double centerFrequency )
{
   mCenterFrequency = centerFrequency;
}

//------------------------------------------------------------------

double LogGaborFilterProcess::GetRadialWidth()
{
   return mRadialWidth;
}

//------------------------------------------------------------------
void LogGaborFilterProcess::SetRadialWidth( double radialWidth )
{
   mRadialWidth = radialWidth;
}

//------------------------------------------------------------------

double LogGaborFilterProcess::GetCenterAngle()
{
   return mCenterAngle;
}

//------------------------------------------------------------------

void LogGaborFilterProcess::SetCenterAngle( double centerAngle )
{
   mCenterAngle = centerAngle;
}

//------------------------------------------------------------------

double LogGaborFilterProcess::GetAngleSpread()
{
   return mAngleSpread;
}

//------------------------------------------------------------------

void LogGaborFilterProcess::SetAngleSpread( double angleSpread )
{
   mAngleSpread = angleSpread;
}

//------------------------------------------------------------------

void LogGaborFilterProcess::SetCreateRealResponse( bool createOut )
{
   mCreateRealResponse = createOut;
}

//------------------------------------------------------------------

void LogGaborFilterProcess::SetCreateImagResponse( bool createOut )
{
   mCreateImagResponse = createOut;
}

//------------------------------------------------------------------

void LogGaborFilterProcess::SetCreateMagnitude( bool createOut )
{
   mCreateMagnitude = createOut;
}

//------------------------------------------------------------------

void LogGaborFilterProcess::SetCreateTransferResponse( bool createOut )
{
   mCreateTransferResponse = createOut;
}

//------------------------------------------------------------------

void LogGaborFilterProcess::run()
{
   LogGabor lg( mpImage );
   lg.SetCenterFrequency( this->GetCenterFrequency() );
   lg.SetRadialWidth( this->GetRadialWidth() );
   lg.SetCenterAngle( this->GetCenterAngle() );
   lg.SetAngleSpread( this->GetAngleSpread() );
   lg.Run();

   if ( mCreateRealResponse ) { AddResult( lg.GetRealResponse( ) ); }
   if ( mCreateImagResponse ) { AddResult( lg.GetImagResponse( ) ); }
   if ( mCreateMagnitude ) { AddResult( lg.GetMagnitude() ); }
   if ( mCreateTransferResponse ) { AddResult( lg.GetTransferFunction( ) ); }
}

//------------------------------------------------------------------
