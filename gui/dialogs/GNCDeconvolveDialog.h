
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

#ifndef STIRAGUI_DIALOGS_GNCDECONVOLVEDIALOG_H
#define STIRAGUI_DIALOGS_GNCDECONVOLVEDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QRadioButton>

#include "../../stira/imagedata/datastructures/Image.h"
#include "DialogMaster.h"

class GNCDeconvolveProcess;  ///< forward declaration of corresponding process; see subproject "processes"
   
class GNCDeconvolveDialog : public DialogMaster
{
    Q_OBJECT

public:

   /** \brief constructor
     * \param pImage the input image for processing */
   GNCDeconvolveDialog( stira::imagedata::Image* pImage );
   
   /** \brief destructor*/
   virtual ~GNCDeconvolveDialog();

   double GetBlurLevel();
   
   int GetNrOfScales();
   int GetNrOfOrientations( );
   
   double GetLambda();
   double GetMu();

   double GetGammaInitial();
   double GetGammaFinal();
   double GetUpdateFactor();
   
   int GetNrOfIterations();

public slots:
   /** \brief Creates the actual process that is started in a separate thread*/
   void SlotRun();
   
protected:
   /** \brief Gets pointer to the process*/
   Process* GetProcess();

private:
   GNCDeconvolveProcess* mpProcess;  ///<  actual process
   
   QVBoxLayout* mpLabelsLayout;
   QVBoxLayout* mpLineEditsLayout;
   QHBoxLayout* mpParametersLayout;
   
   QLabel*      mpNrScalesLabel; ///< label for nr of scales in the pyramid 
   QLineEdit*   mpNrScalesLineEdit; ///< line edit for nr of scales in the pyramid

   QLabel*      mpNrOrientationsLabel; ///< label for nr of orientations in the pyramid
   QLineEdit*   mpNrOrientationsLineEdit; ///< line edit for for nr of orientations in the pyramid
   
   QLabel*      mpLambdaLabel;  ///< label for regularization parameter lambda
   QLineEdit*   mpLambdaLineEdit;  ///< line edit for regularization parameter lambda

   QLabel*      mpMuLabel; ///< label for data fit parameter mu
   QLineEdit*   mpMuLineEdit; ///< line edit for data fit parameter mu
   
   QLabel*      mpNrIterationsLabel;  ///< label for nr of iterations
   QLineEdit*   mpNrIterationsLineEdit;  ///< line edit for nr of iterations
   
   QLabel*      mpBlurLevelLabel;  ///< label for width of blur (e.g., sigma for for gaussian PSF)
   QLineEdit*   mpBlurLevelLineEdit;  ///< line edit for width of blur (e.g., sigma for for gaussian PSF)

   QLabel*      mpGammaInitLabel;
   QLineEdit*   mpGammaInitLineEdit;
   QHBoxLayout* mpGammaInitLayout;

   QLabel*      mpGammaFinalLabel;
   QLineEdit*   mpGammaFinalLineEdit;
   QHBoxLayout* mpGammaFinalLayout;

   QLabel*      mpUpdateFactorLabel;
   QLineEdit*   mpUpdateFactorLineEdit;
   QHBoxLayout* mpUpdateFactorLayout;
   
};

#endif
