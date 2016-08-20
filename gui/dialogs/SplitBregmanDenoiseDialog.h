
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

#ifndef STIRAGUI_DIALOGS_SPLITBREGMANDENOISEDIALOG_H
#define STIRAGUI_DIALOGS_SPLITBREGMANDENOISEDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>

#include "DialogMaster.h"

class SplitBregmanDenoiseProcess;  ///< forward declaration of corresponding process; see subproject "processes"

/** \brief dialog for Split-Bregman denoise parameters
  * This class gathers the necessary inputs, creates an object that runs in a separate thread and 
  * creates a new window with the result*/
class SplitBregmanDenoiseDialog : public DialogMaster
{
    Q_OBJECT

public:
   /** \brief constructor
     * \param pImage input image */
   SplitBregmanDenoiseDialog( stira::imagedata::Image* pImage );
   
   /** \brief destructor*/
   virtual ~SplitBregmanDenoiseDialog();
   
   double GetMu();

   double GetLambda();

   int GetNumberOfGaussSeidelIterations();

   int GetNumberOfBregmanIterations();

   bool GetIsIsotropic();

   
public slots:
   /** \brief Creates the actual process that is started in a separate thread*/
   void SlotRun();

protected:
   /** \brief Gets pointer to the process*/
   Process* GetProcess();

private:
   SplitBregmanDenoiseProcess* mpProcess;  ///<  actual process
   
   QLabel* mpMuLabel;        ///< label "Mu"
   QLineEdit* mpMuLineEdit;   ///< line edit "Mu"
   QHBoxLayout* mpMuLayout;
   
   QLabel* mpLambdaLabel;        ///< label "Lambda"
   QLineEdit* mpLambdaLineEdit;   ///< line edit "Lambda"
   QHBoxLayout* mpLambdaLayout;
   
   QLabel* mpNumberOfGaussSeidelIterationsLabel;        ///< label "NumberOfGausSeidelIterations"
   QLineEdit* mpNumberOfGaussSeidelIterationsLineEdit;   ///< line edit "NumberOfGausSeidelIterations"
   QHBoxLayout* mpNumberOfGaussSeidelIterationsLayout;
   
   QLabel* mpNumberOfBregmanIterationsLabel;        ///< label "NumberOfBregmanIterations"
   QLineEdit* mpNumberOfBregmanIterationsLineEdit;   ///< line edit "NumberOfBregmanIterations"
   QHBoxLayout* mpNumberOfBregmanIterationsLayout;
   
   QCheckBox* mpIsIsotropic;

   QHBoxLayout* mpFlowParameterLayout; ///< layout to align the "FlowParameter" widgets
   QHBoxLayout* mpNrIterationsLayout; ///< layout to align the "NrIterations" widgets
};

#endif
