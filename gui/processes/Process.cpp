
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

#include "Process.h"
#include "../../stira/imagedata/datastructures/Image.h"

using namespace stira::image;
using namespace std;

Process::Process( Image* pImage ) : QThread()
{
   cout << "Applying master Process directly with Image*" << endl << flush;
   mpImage = pImage;
}

//--------------------------------------------------------

Process::~Process()
{
}

//--------------------------------------------------------

QString Process::GetProcessName()
{
   return mProcessName;
}

//--------------------------------------------------------

void Process::AddResult( stira::image::Image* pResultImage )
{
   vpOutImageVector.push_back( pResultImage );
}

//--------------------------------------------------------

std::vector< stira::image::Image* > Process::GetResultImages()
{
   return vpOutImageVector;
}

//--------------------------------------------------------




