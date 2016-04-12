
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

#ifndef STIRAGUI_DIALOGS_GENERATEPERLINNOISEDIALOG_H
#define STIRAGUI_DIALOGS_GENERATEPERLINNOISEDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QRadioButton> 
#include <QCheckBox>

#include "../src/ImageWindow.h"
#include "DialogMaster.h"

class GeneratePerlinNoiseProcess;  ///< forward declaration of corresponding process; see subproject "processes"
   
class GeneratePerlinNoiseDialog : public DialogMaster
{
    Q_OBJECT

public:

   /** \brief constructor*/
   GeneratePerlinNoiseDialog( );
   
   /** \brief destructor*/
   virtual ~GeneratePerlinNoiseDialog();
   
   /** \brief gets the width of the image to generate from its corresponding widget*/
   int GetWidth();
   
   /** \brief gets the height of the image to generate from its corresponding widget*/
   int GetHeight();
   
   /** \brief gets the persistance parameter */
   double GetPersistence();
   
   bool GetUseNormalization();
   
   int GetNumberOfOctaves();
   double GetRedFactor();
   double GetGreenFactor();
   double GetBlueFactor();
   int GetSeed();
   double GetZoom();
   
public slots:
   /** \brief Creates the actual process that is started in a separate thread*/
   void SlotRun();
   
protected:
   /** \brief Gets pointer to the process*/
   Process* GetProcess();

private:
   GeneratePerlinNoiseProcess* mpProcess;  ///<  actual process
   
   QLabel*    mpImageWidthLabel;  ///< label with explanation "ImageWidth"
   QLineEdit* mpImageWidthLineEdit;  ///< line edit to set "ImageWidth"
   
   QLabel*    mpImageHeightLabel;  ///< label with explanation "ImageHeight"
   QLineEdit* mpImageHeightLineEdit;  ///< line edit to set "ImageHeight"
   
   QLabel*    mpRedFactorLabel;  ///< label with explanation "RedFactor"
   QLineEdit* mpRedFactorLineEdit;  ///< line edit to set "RedFactor"
   
   QLabel*    mpGreenFactorLabel;  ///< label with explanation "GreenFactor"
   QLineEdit* mpGreenFactorLineEdit;  ///< line edit to set "GreenFactor"
   
   QLabel*    mpBlueFactorLabel;  ///< label with explanation "BlueFactor"
   QLineEdit* mpBlueFactorLineEdit;  ///< line edit to set "BlueFactor"
   QLabel*    mpEmptyLabel1;
   QLabel*    mpEmptyLabel2;
   
   QLabel*    mpPersistenceLabel;  ///< label with explanation "NumberOfOctaves"
   QLineEdit* mpPersistenceLineEdit;  ///< line edit to set "NumberOfOctaves"
   
   QLabel*    mpNrOctavesLabel;  ///< label with explanation "NumberOfOctaves"
   QLineEdit* mpNrOctavesLineEdit;  ///< line edit to set "NumberOfOctaves"
   
   QCheckBox* mpUseNormalizationCheckBox;  ///< Use Normalization
   
   QVBoxLayout* mpColorLabelsLayout;
   QVBoxLayout* mpColorEditsLayout;
   
   QLabel*    mpSeedLabel;
   QLineEdit* mpSeedLineEdit;
   QHBoxLayout* mpSeedLayout;
   
   QLabel*    mpZoomLabel;
   QLineEdit* mpZoomLineEdit;
   QHBoxLayout* mpZoomLayout;
   
   QVBoxLayout* mpOtherParametersLabelsLayout;
   QVBoxLayout* mpOtherParametersEditsLayout;
   
   QHBoxLayout* mpParametersLayout;

};

#endif
