
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

#ifndef STIRAGUI_DIALOGS_ANISOTROPICDIFFUSIONDIALOG_H
#define STIRAGUI_DIALOGS_ANISOTROPICDIFFUSIONDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit> 
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>

#include "DialogMaster.h"

class AnisotropicDiffusionProcess;  ///< forward declaration of corresponding process; see subproject "processes"

/** \brief dialog for anisotropic diffusion parameters
  * This class gathers the necessary inputs, creates an object that runs in a separate thread and 
  * creates a new window with the result*/
class AnisotropicDiffusionDialog : public DialogMaster
{
    Q_OBJECT

public:
   /** \brief constructor
     * \param pImage input image */
   AnisotropicDiffusionDialog( stira::image::Image* pImage );
   
   /** \brief destructor*/
   virtual ~AnisotropicDiffusionDialog();
   
   /** \brief gets the flow parameter from its corresponding widget*/
   double GetFlowParameter();
   
   /** \brief gets the number of iterations from its corresponding widget*/
   int GetNrOfIterations();
   
public slots:
   /** \brief Creates the actual process that is started in a separate thread*/
   void SlotRun();

protected:
   /** \brief Gets pointer to the process*/
   Process* GetProcess();

private:
   AnisotropicDiffusionProcess* mpProcess;  ///<  actual process
   QLabel* mpNrIterationsLabel;        ///< label with explanation "NrIterations"
   QLabel* mpFlowParameterLabel;       ///< label with explanation "FlowParameter"
   QLineEdit* mpNrIterationsLineEdit;   ///< line edit to set "NrIterations"
   QLineEdit* mpFlowParameterLineEdit; ///< line edit to set "FlowParameter"

   QHBoxLayout* mpFlowParameterLayout; ///< layout to align the "FlowParameter" widgets
   QHBoxLayout* mpNrIterationsLayout; ///< layout to align the "NrIterations" widgets
};

#endif
