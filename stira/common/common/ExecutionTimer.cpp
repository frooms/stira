
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

#include "ExecutionTimer.h"
#include <iostream>

using namespace std;

namespace stira {
namespace common {

//------------------------------------------------------------------------------

ExecutionTimer::ExecutionTimer()
{
}

//------------------------------------------------------------------------------

ExecutionTimer::~ExecutionTimer()
{
}

//------------------------------------------------------------------------------
// Get current time (as double)

//------------------------------------------------------------------------------
// timer start
void ExecutionTimer::StartTimer()
{
   spStart = times( &spStartTime );
}

//------------------------------------------------------------------------------

// timer stop + print seconds elapse time
void ExecutionTimer::StopTimer()
{
   spStop = times( &spStopTime );
}

//------------------------------------------------------------------------------

float ExecutionTimer::GetElapsedUserTimeInSeconds()
{
   return ( ( (float)( spStopTime.tms_utime - spStartTime.tms_utime ) ) / HZ );
}

//------------------------------------------------------------------------------

float ExecutionTimer::GetElapsedSystemTimeInSeconds()
{
   return ( ( (float)( spStopTime.tms_stime - spStartTime.tms_stime ) ) / HZ );
}

//------------------------------------------------------------------------------

float ExecutionTimer::GetElapsedRealTimeInSeconds()
{
   return ( ( (float)( spStop - spStart ) ) / HZ );
}

//------------------------------------------------------------------------------
// Get time as user+system times
// HZ is the number of ticks per second. It is a system-dependent constant defined in sys/param.h

void ExecutionTimer::PrintTimeAsUserAndSystemTimes()
{
   //user time (the CPU time spent executing the user's code)
   cout << "\t User    time = " << GetElapsedUserTimeInSeconds() << " sec" << endl << flush;
   
   //system time (the CPU time spent by the operating system on behalf of the user's code)
   cout << "\t System  time = " << GetElapsedSystemTimeInSeconds() << " sec" << endl << flush;
   
   //real time (elapsed, or ``wall clock'' time)
   cout << "\t Real    time = " << GetElapsedRealTimeInSeconds() << " sec" << endl << flush;
}

//------------------------------------------------------------------------------

}
}
