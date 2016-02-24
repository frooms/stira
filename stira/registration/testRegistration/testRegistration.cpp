
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

#include "../registration/RegistrationWrapper.h"
#include "../../image/tools/ImageIO.h"
#include <string>

using namespace std;
using namespace stira::image;
using namespace stira::registration;

int main(int argc, char *argv[])
{
   Image* pImage1 = 0;
   Image* pImage2 = 0;

   const char* inputname1;
   const char* inputname2;
   
   if (argc == 3)
   {
      inputname1 =  argv[1];
      inputname2 =  argv[2];
   }
   else
   {
      inputname1 = "../../testdata/lena-crop1.ppm";
      inputname2 = "../../testdata/lena-crop2.ppm";
   }
   
   pImage1 = ImageIO::Read( inputname1 );
   pImage2 = ImageIO::Read( inputname2 );
   
   int width  = pImage1->GetWidth();
   int height = pImage1->GetHeight();
   int nrBands = pImage1->GetNumberOfBands();
   
   if (    ( pImage2->GetWidth() == width )
        && ( pImage2->GetHeight() == height )
        && ( pImage2->GetNumberOfBands() == nrBands )
      )
   {
      Image* pRegistered = new Image( width, height );
      for (int bandID = 0; bandID < pImage1->GetNumberOfBands(); bandID++)
      {
         RegistrationWrapper rw( pImage1->GetBands()[bandID], pImage2->GetBands()[bandID] );
         rw.Run();
         pRegistered->AddBand( rw.GetRegisteredGrid( ) );
      }
      
      ImageIO::Write( pRegistered, string("Registered.ppm"), ImageIO::NULL_OUT);
   }
   else
   {
      cerr << "Current implementation requires identical dimensions for master and slave!!" << endl << flush;
   }
}
