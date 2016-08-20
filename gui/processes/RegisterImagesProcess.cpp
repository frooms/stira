
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
#include "../src/ImageDataList.h"
#include "RegisterImagesProcess.h"
#include "../../stira/registration/registration/RegistrationWrapper.h"

using namespace stira::imagetools;
using namespace stira::imagedata;
using namespace stira::registration;

RegisterImagesProcess::RegisterImagesProcess( Image* pImageMaster, Image* pImageSlave )
{ 
   mpImageMaster = pImageMaster;
   mpImageSlave  = pImageSlave;
   run();
}

RegisterImagesProcess::~RegisterImagesProcess( )
{
}

void RegisterImagesProcess::run()
{
   int width   = mpImageMaster->GetWidth();
   int height  = mpImageMaster->GetHeight();
   int nrBands = mpImageMaster->GetNumberOfBands();
   
   if (    ( mpImageSlave->GetWidth() == width )
        && ( mpImageSlave->GetHeight() == height )
        && ( mpImageSlave->GetNumberOfBands() == nrBands )
      )
   {
      Image* pRegistered = new Image( width, height );
      for (int bandID = 0; bandID < nrBands; bandID++)
      {
         RegistrationWrapper rw( mpImageMaster->GetBands()[bandID], mpImageSlave->GetBands()[bandID] );
         rw.Run();
         rw.PrintTransform();
         pRegistered->AddBand( rw.GetRegisteredGrid() );
      }
      std::string fileName = std::string("Registered") + mpImageMaster->GetImageName() + std::string("-") + mpImageSlave->GetImageName();
      pRegistered->SetImageName( fileName );
      ImageDataList::GetInstance()->AddImage( pRegistered );
   }
}
