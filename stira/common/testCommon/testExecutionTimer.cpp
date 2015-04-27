
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

#include "../common/ExecutionTimer.h"
#include "../common/FileAccess.h"
#include "../common/FixedBuffer.h"
#include "../common/StringUtils.h"
#include <iostream>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <sstream>

using namespace std;
using namespace stira::common;

//-------------------------------------------------------------------

void TestTimer()
{
   ExecutionTimer et;

   et.StartTimer();
   for (int i = 0; i < 1000000000; i++)
   {
      int j = i * i * i * i;  // just keep the timer busy
   }
   et.StopTimer();
   et.PrintTimeAsUserAndSystemTimes();
   cout << "Elapsed time is " << et.GetElapsedRealTimeInSeconds() << " seconds " << endl << flush;
}

//-------------------------------------------------------------------

int main()
{
   TestTimer();
}

