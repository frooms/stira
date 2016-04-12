
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

#include "GeneratePerlinNoiseDialog.h"
#include "../src/MainWindow.h"
#include "../processes/GeneratePerlinNoiseProcess.h"

using namespace std;

GeneratePerlinNoiseDialog::GeneratePerlinNoiseDialog( ) : DialogMaster()
{
   mpProcess = 0;
   mpTitelLabel->setText( QString("<B>Generate Perlin Clouds</B>") );

   mpImageWidthLabel = new QLabel( QString("Width: "), this );
   mpImageWidthLineEdit = new QLineEdit( QString("512"), this );
   
   mpImageHeightLabel = new QLabel( QString("Height: "), this );
   mpImageHeightLineEdit = new QLineEdit( QString("512"), this );
   
   
   mpRedFactorLabel = new QLabel( QString("Red: "), this );
   mpRedFactorLineEdit = new QLineEdit( QString("3"), this );
   
   mpGreenFactorLabel = new QLabel( QString("Green: "), this );
   mpGreenFactorLineEdit = new QLineEdit( QString("1.0"), this );
   
   mpBlueFactorLabel = new QLabel( QString("Blue: "), this );
   mpBlueFactorLineEdit = new QLineEdit( QString("2.0"), this );
   
   
   mpEmptyLabel1 = new QLabel( QString(""), this );
   mpEmptyLabel2 = new QLabel( QString(""), this );
   
   mpColorLabelsLayout = new QVBoxLayout;
   mpColorLabelsLayout->addWidget( mpImageWidthLabel );
   mpColorLabelsLayout->addWidget( mpRedFactorLabel );
   mpColorLabelsLayout->addWidget( mpGreenFactorLabel );
   mpColorLabelsLayout->addWidget( mpBlueFactorLabel );
   mpColorLabelsLayout->addWidget( mpEmptyLabel1 );
   
   mpColorEditsLayout = new QVBoxLayout;
   mpColorEditsLayout->addWidget( mpImageWidthLineEdit );
   mpColorEditsLayout->addWidget( mpRedFactorLineEdit );
   mpColorEditsLayout->addWidget( mpGreenFactorLineEdit );
   mpColorEditsLayout->addWidget( mpBlueFactorLineEdit );
   mpColorEditsLayout->addWidget( mpEmptyLabel2 );
   
   //////////////////////////////
   
   mpPersistenceLabel = new QLabel( QString("Persistence: "), this );
   mpPersistenceLineEdit = new QLineEdit( QString("0.7"), this );
   
   mpNrOctavesLabel = new QLabel( QString("# Octaves: "), this );
   mpNrOctavesLineEdit = new QLineEdit( QString("7"), this );
   
   mpSeedLabel = new QLabel( QString("Seed: "), this );
   mpSeedLineEdit = new QLineEdit( QString("0"), this );
   
   mpZoomLabel = new QLabel( QString("Zoom: "), this );
   mpZoomLineEdit = new QLineEdit( QString("75"), this );
   
   mpUseNormalizationCheckBox = new QCheckBox( QString("Use Normalization?"), this );
   
   mpOtherParametersLabelsLayout = new QVBoxLayout;
   mpOtherParametersEditsLayout = new QVBoxLayout;
   
   mpOtherParametersLabelsLayout->addWidget( mpImageHeightLabel );
   mpOtherParametersLabelsLayout->addWidget( mpPersistenceLabel );
   mpOtherParametersLabelsLayout->addWidget( mpNrOctavesLabel );
   mpOtherParametersLabelsLayout->addWidget( mpSeedLabel );
   mpOtherParametersLabelsLayout->addWidget( mpZoomLabel );
   
   mpOtherParametersEditsLayout->addWidget( mpImageHeightLineEdit );
   mpOtherParametersEditsLayout->addWidget( mpPersistenceLineEdit );
   mpOtherParametersEditsLayout->addWidget( mpNrOctavesLineEdit );
   mpOtherParametersEditsLayout->addWidget( mpSeedLineEdit );
   mpOtherParametersEditsLayout->addWidget( mpZoomLineEdit );
   
   mpParametersLayout = new QHBoxLayout;
   
   mpParametersLayout->addLayout( mpColorLabelsLayout );
   mpParametersLayout->addLayout( mpColorEditsLayout );
   mpParametersLayout->addLayout( mpOtherParametersLabelsLayout );
   mpParametersLayout->addLayout( mpOtherParametersEditsLayout );
   
   mpDialogLayout->addWidget( mpTitelLabel );
   mpDialogLayout->addLayout( mpParametersLayout );
   mpDialogLayout->addWidget( mpUseNormalizationCheckBox );
   mpDialogLayout->addLayout( mpButtonLayout );
   
   this->show();
}

//--------------------------------------------------------

GeneratePerlinNoiseDialog::~GeneratePerlinNoiseDialog()
{
   if (mpProcess != 0)
   {
      delete mpProcess;
   }
}

//--------------------------------------------------------

void GeneratePerlinNoiseDialog::SlotRun()
{
   mpProcess = new GeneratePerlinNoiseProcess( );
   connect( mpProcess, SIGNAL( finished() ), this, SLOT( SlotProcessResult() ) );
   
   mpProcess->SetWidth( this->GetWidth() );
   mpProcess->SetHeight( this->GetHeight() );
   mpProcess->SetPersistence( this->GetPersistence() );
   mpProcess->SetNumberOfOctaves( this->GetNumberOfOctaves() );
   mpProcess->SetRedFactor( this->GetRedFactor() );
   mpProcess->SetGreenFactor( this->GetGreenFactor() );
   mpProcess->SetBlueFactor( this->GetBlueFactor() );
   mpProcess->SetSeed( this->GetSeed() );
   mpProcess->SetZoom( this->GetZoom() );
   mpProcess->SetUseNormalization( this->GetUseNormalization() );
   
   mpProcess->start();
}

//--------------------------------------------------------

int GeneratePerlinNoiseDialog::GetWidth()
{
   return mpImageWidthLineEdit->text().toInt();
}

//--------------------------------------------------------

int GeneratePerlinNoiseDialog::GetHeight()
{
   return mpImageHeightLineEdit->text().toInt();
}

//--------------------------------------------------------

double GeneratePerlinNoiseDialog::GetPersistence()
{
   return mpPersistenceLineEdit->text().toDouble();
}

//--------------------------------------------------------

int GeneratePerlinNoiseDialog::GetNumberOfOctaves()
{
   return mpNrOctavesLineEdit->text().toInt();
}

//--------------------------------------------------------

double GeneratePerlinNoiseDialog::GetRedFactor()
{
   return mpRedFactorLineEdit->text().toDouble();
}

//--------------------------------------------------------

double GeneratePerlinNoiseDialog::GetGreenFactor()
{
   return mpGreenFactorLineEdit->text().toDouble();
}

//--------------------------------------------------------

double GeneratePerlinNoiseDialog::GetBlueFactor()
{
   return mpBlueFactorLineEdit->text().toDouble();
}

//--------------------------------------------------------

int GeneratePerlinNoiseDialog::GetSeed()
{
   return mpSeedLineEdit->text().toInt();
}

//--------------------------------------------------------

double GeneratePerlinNoiseDialog::GetZoom()
{
   return mpZoomLineEdit->text().toDouble();
}

//--------------------------------------------------------

bool GeneratePerlinNoiseDialog::GetUseNormalization()
{
   return mpUseNormalizationCheckBox->isChecked();
}

//--------------------------------------------------------

Process* GeneratePerlinNoiseDialog::GetProcess()
{
   return mpProcess;
}

//--------------------------------------------------------
