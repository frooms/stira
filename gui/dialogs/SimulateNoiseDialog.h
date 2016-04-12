
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

#ifndef STIRAGUI_DIALOGS_SIMULATENOISEDIALOG_H
#define STIRAGUI_DIALOGS_SIMULATENOISEDIALOG_H

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

#include "DialogMaster.h"

class SimulateNoiseProcess;  ///< forward declaration of corresponding process; see subproject "processes"
   
class SimulateNoiseDialog : public DialogMaster
{
    Q_OBJECT

public:

   /** \brief constructor
     * \param pImage input image for processing */
   SimulateNoiseDialog( stira::image::Image* pImage );
   
   /** \brief destructor*/
   virtual ~SimulateNoiseDialog();
   
   double GetNoiseLevel();

   enum StiraDefinitions::NoiseType GetNoiseType();

   bool GetUseColoredNoise();

public slots:
   /** \brief Creates the actual process that is started in a separate thread*/
   void SlotRun();
   void SlotSetDefaultGaussianLevel();
   void SlotSetDefaultPoissonLevel();
   void SlotSetDefaultImpulseLevel();
   
   
protected:
   /** \brief Gets pointer to the process*/
   Process* GetProcess();
   
private: 

   SimulateNoiseProcess* mpProcess;  ///<  actual process
   
   QLabel*      mpNoiseLevelLabel;
   QLineEdit*   mpNoiseLevelLineEdit;
   QHBoxLayout* mpNoiseLevelLayout;
   
   QGroupBox* mpNoiseTypeGroupBox;
   
   QRadioButton *mpGaussianNoiseRadioButton;
   QRadioButton *mpPoissonNoiseRadioButton;
   QRadioButton *mpImpulseNoiseRadioButton;

   QCheckBox *mpNoiseIsColoredCheckBox;

   QVBoxLayout* mpRadioButtonLayout;
};

#endif
