
/***************************************************************************************
 *   Copyright (C) 2008 by Filip Rooms                                                 *
 *                                                                                     *
 *  Terms and conditions for using this software in any form are provided in the       *
 *  file COPYING, which can be found in the root directory of this project.            *
 *                                                                                     *
 *   Contact data: filip.rooms@gmail.com                                               *
 *                 http://www.filiprooms.be/                                           *
 *                                                                                     *
 ***************************************************************************************/

#ifndef STIRA_COMMON_EXECUTIONTIMER_H
#define STIRA_COMMON_EXECUTIONTIMER_H

#include <ctime>

#include <sys/param.h>
#include <sys/times.h>
#include <sys/types.h>

namespace stira {
namespace common {

/** \brief small timer class to get execution timings of applications
  * Ref: http://osr600doc.sco.com/en/SDK_c++/_Measuring_Program_Execution_Tim.html
  * For windows, this becomes http://www.dreamincode.net/forums/showtopic24685.htm
  * with some code
  *  #include <windows.h>
  *    // code
  *    long int before = GetTickCount();
  *
  *    // Perform time-consuming operation
  *    long int after = GetTickCount();
  *    cout << "Execution Time : " << ( after - before ) << " ms."
  *
  * Alternative reference: 
  *    http://en.allexperts.com/q/C-1040/time-milliseconds-Windows.htm
  */
class ExecutionTimer{
public:

   /** \brief Constructor.*/
   ExecutionTimer();

   /** \brief Destructor. */
   ~ExecutionTimer();
   
   /** \brief Gets current calender time, converted internally from time_t object to double (in seconds)*/
   double GetCurrentTime ();
   
   /** \brief starts the timer (and resets the previous elapsed time to 0)*/
   void StartTimer();
   
   /** \brief stops the timer (and computes the latest elapsed time)*/
   void StopTimer();
   
   /** \brief gets user time (the CPU time spent executing the user's code) in seconds*/
   float GetElapsedUserTimeInSeconds();

   /** \brief gets system time (the CPU time spent by the operating system on behalf of the user's code) in seconds */
   float GetElapsedSystemTimeInSeconds();

   /** \brief gets real time (elapsed, or ``wall clock'' time) in seconds */
   float GetElapsedRealTimeInSeconds();
   
   /** \brief print elapsed times (user, system and real) on command line*/
   void PrintTimeAsUserAndSystemTimes();
   
private:
   tms spStartTime;  ///< The time the timer was started
   tms spStopTime;  ///< The time the timer was started
   long spStart; ///< start time in ticks
   long spStop; ///< stop time in ticks

};
}
}
#endif
