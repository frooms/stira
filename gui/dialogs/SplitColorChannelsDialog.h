
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

#ifndef STIRAGUI_DIALOGS_SPLITCOLORCHANNELSDIALOG_H
#define STIRAGUI_DIALOGS_SPLITCOLORCHANNELSDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QRadioButton>
#include <QComboBox>

#include "../../stira/imagedata/datastructures/Image.h"
#include "../../stira/imagedata/color/ColorValue.h"
#include "DialogMaster.h"

class SplitColorChannelsProcess;  ///< forward declaration of corresponding process; see subproject "processes"

class SplitColorChannelsDialog : public DialogMaster
{
   Q_OBJECT
   
public:

   /** \brief constructor
     * \param pImage the input image for processing */
   SplitColorChannelsDialog( stira::imagedata::Image* pImage );
   
   /** \brief destructor*/
   virtual ~SplitColorChannelsDialog();
   
   /** \brief gets the color space in which to extract the channels */
   enum stira::imagedata::ColorType GetColorSpace();
   
   /** \brief gets the reference illuminant */
   stira::imagedata::ColorValue GetReferenceIlluminant();

public slots:

   /** \brief Creates the actual process that is started in a separate thread*/
   void SlotRun();
   
   /** \brief slot to switch between showing and hiding the reference illuminant
     * The combo box to choose between the illuminants is only shown when a color space is chosen that requires one*/
   void SlotShowHideIlluminant( int index );
   
protected:
   /** \brief Gets pointer to the process*/
   Process* GetProcess();

private:
   SplitColorChannelsProcess* mpProcess;  ///<  actual process
   
   QComboBox* mpColorSpaceComboBox;    ///< combo box to choose between the color spaces
   QComboBox* mpIlluminantComboBox;    ///< combo box to choose between the illuminants
};

#endif
