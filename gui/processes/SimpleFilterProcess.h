
/*****************************************
 *   Copyright (C) 2008 by Filip Rooms   *
 *   filip.rooms@gmail.com               *
 *   http://www.filiprooms.be/           *
 *                                       *
 *****************************************/

#ifndef FRIEPGUI_PROCESSES_SIMPLEFILTERPROCESS_H
#define FRIEPGUI_PROCESSES_SIMPLEFILTERPROCESS_H

#include <QDialog>
#include <QThread>
#include <QLabel>
#include <QLineEdit> 
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>

#include "../src/ImageWindow.h"

class stira::image::Image;
class AnisotropicDiffusionProcess;

#include "../src/ImageWindow.h"


//==========================================================================
//==========================================================================
//==========================================================================

/** \brief dialog for anisotropic diffusion parameters
  * This class gathers the necessary inputs, creates an object that runs in a separate thread and 
  * creates a new window with the result*/
class SimpleFilterDialog : public QDialog
{
    Q_OBJECT

public:
   /** \brief constructor
     * \param pImWindow window from which the input image for processing will be extracted*/
   SimpleFilterDialog( ImageWindow* pImWindow  );
   
   /** \brief destructor*/
   ~SimpleFilterDialog();
};

#endif
