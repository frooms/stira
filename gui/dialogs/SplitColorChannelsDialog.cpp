
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

#include "../processes/SplitColorChannelsProcess.h"
#include "SplitColorChannelsDialog.h"

using namespace std;
using namespace stira::image;

SplitColorChannelsDialog::SplitColorChannelsDialog( Image* pImage ) : DialogMaster( pImage )
{
   mpProcess = 0;
   mpTitelLabel->setText( QString("Split into color channels") );
   
   mpColorSpaceComboBox = new QComboBox;
   mpColorSpaceComboBox->addItem ( QString("RGB"));
   mpColorSpaceComboBox->addItem ( QString("HSV"));
   mpColorSpaceComboBox->addItem ( QString("HSI"));
   mpColorSpaceComboBox->addItem ( QString("CMY"));
   mpColorSpaceComboBox->addItem ( QString("YUV"));
   mpColorSpaceComboBox->addItem ( QString("XYZ"));
   mpColorSpaceComboBox->addItem ( QString("L*a*b*"));
   mpColorSpaceComboBox->addItem ( QString("Luv"));
   mpColorSpaceComboBox->setCurrentIndex ( 0 );
  
   mpIlluminantComboBox = new QComboBox;
   mpIlluminantComboBox->addItem ( QString("A") );
   mpIlluminantComboBox->addItem ( QString("B") );
   mpIlluminantComboBox->addItem ( QString("C") );

   mpIlluminantComboBox->addItem ( QString("D50") );
   mpIlluminantComboBox->addItem ( QString("D55") );
   mpIlluminantComboBox->addItem ( QString("D65") );
   mpIlluminantComboBox->addItem ( QString("D75") );
   mpIlluminantComboBox->addItem ( QString("D93") );

   mpIlluminantComboBox->addItem ( QString("E") );
   mpIlluminantComboBox->addItem ( QString("F2") );
   mpIlluminantComboBox->addItem ( QString("F7") );
   mpIlluminantComboBox->addItem ( QString("F11") );
   mpIlluminantComboBox->addItem ( QString("Print") );
   mpIlluminantComboBox->setCurrentIndex ( 5 );

   mpDialogLayout->addWidget( mpTitelLabel );
   mpDialogLayout->addWidget( mpColorSpaceComboBox );
   mpDialogLayout->addWidget( mpIlluminantComboBox );
   mpDialogLayout->addLayout( mpButtonLayout );
   connect( mpColorSpaceComboBox, SIGNAL( currentIndexChanged ( int ) ), this, SLOT( SlotShowHideIlluminant( int ) ) );
   SlotShowHideIlluminant( 0 );
   this->show();
}

//------------------------------------------------------------------

SplitColorChannelsDialog::~SplitColorChannelsDialog()
{
   if (mpProcess != 0)
   {
      delete mpProcess;
   }
}

//------------------------------------------------------------------

enum stira::image::ColorType SplitColorChannelsDialog::GetColorSpace()
{
   switch( mpColorSpaceComboBox->currentIndex() )
   {
      case 0:
      {
         return stira::image::TYPE_RGB;
      }
      case 1:
      {
         return stira::image::TYPE_HSV;
      }
      case 2:
      {
         return stira::image::TYPE_HSI;
      }
      case 3:
      {
         return stira::image::TYPE_CMY;
      }
      case 4:
      {
         return stira::image::TYPE_YUV;
      }
      case 5:
      {
         return stira::image::TYPE_XYZ;
      }
      case 6:
      {
         return stira::image::TYPE_LAB;
      }
      case 7:
      {
         return stira::image::TYPE_LUV;
      }
      default:
      {
         return stira::image::TYPE_RGB;
      }
   }
}

//------------------------------------------------------------------

void SplitColorChannelsDialog::SlotShowHideIlluminant( int index )
{
   cout << "Current index is now " << index << endl << flush;
   if (index < 6)
   {
      mpIlluminantComboBox->hide();
   }
   else
   {
      mpIlluminantComboBox->show();
   }
}

//------------------------------------------------------------------

stira::image::ColorValue SplitColorChannelsDialog::GetReferenceIlluminant()
{
   switch( mpIlluminantComboBox->currentIndex() )
   {
      case 0:
      {
         return ColorConstants::sA_XYZ;
      }
      case 1:
      {
         return ColorConstants::sB_XYZ;
      }
      case 2:
      {
         return ColorConstants::sC_XYZ;
      }
      case 3:
      {
         return ColorConstants::sD50_XYZ;
      }
      case 4:
      {
         return ColorConstants::sD55_XYZ;
      }
      case 5:
      {
         return ColorConstants::sD65_XYZ;
      }
      case 6:
      {
         return ColorConstants::sD75_XYZ;
      }
      case 7:
      {
         return ColorConstants::sD93_XYZ;
      }
      case 8:
      {
         return ColorConstants::sE_XYZ;
      }
      case 9:
      {
         return ColorConstants::sF2_XYZ;
      }
      case 10:
      {
         return ColorConstants::sF7_XYZ;
      }
      case 11:
      {
         return ColorConstants::sF11_XYZ;
      }
      case 12:
      {
         return ColorConstants::sPrintWhite_XYZ;
      }
      default:
      {
         return ColorConstants::sD65_XYZ;
      }
   }
}

//--------------------------------------------------------

void SplitColorChannelsDialog::SlotRun()
{
   mpProcess = new SplitColorChannelsProcess( mpInputImage );
   connect( mpProcess, SIGNAL( finished() ), this, SLOT( SlotProcessResult() ) );
   mpProcess->SetColorSpace( this->GetColorSpace() );
   mpProcess->SetReferenceIlluminant( this->GetReferenceIlluminant() );
   
   mpProcess->start();
}

//--------------------------------------------------------

Process* SplitColorChannelsDialog::GetProcess()
{
   return mpProcess;
}

//--------------------------------------------------------

