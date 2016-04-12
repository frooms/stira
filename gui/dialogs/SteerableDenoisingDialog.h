
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

#ifndef STIRAGUI_PROCESSES_STEERABLEDENOISING_H
#define STIRAGUI_PROCESSES_STEERABLEDENOISING_H

#include <QDialog>
#include <QThread>
#include <QLabel>
#include <QLineEdit> 
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>

#include "DialogMaster.h"

class SteerableDenoisingProcess;  ///< forward declaration of corresponding process; see subproject "processes"

/** \brief dialog for anisotropic diffusion parameters
  * This class gathers the necessary inputs, creates an object that runs in a separate thread and 
  * creates a new window with the result*/
class SteerableDenoisingDialog : public DialogMaster
{
    Q_OBJECT

public:
   /** \brief constructor
     * \param pImage the input image for processing */
   SteerableDenoisingDialog( stira::image::Image* pImage );
   
   /** \brief destructor*/
   ~SteerableDenoisingDialog();
   
   double GetFlowParameter();
   
   int GetNrOfIterations();
   
public slots:
   /** \brief Creates the actual process that is started in a separate thread*/
   void SlotRun();
   
protected:
   /** \brief Gets pointer to the process*/
   Process* GetProcess();
   
private:
   SteerableDenoisingProcess* mpProcess;  ///<  actual process
   
   QLabel* mpNrScalesLabel;
   QLineEdit* mpNrScalesLineEdit;
   QHBoxLayout* mpNrScalesLayout;
   
   QLabel* mpNrOrientationsLabel;
   QLineEdit* mpNrOrientationsLineEdit;
   QHBoxLayout* mpNrOrientationsLayout;
   
   QLabel* mpNoiseLevelLabel;
   QLineEdit* mpNoiseLevelLineEdit;
   QHBoxLayout* mpNoiseLevelLayout;
};

#endif
