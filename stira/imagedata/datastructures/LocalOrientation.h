
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

#ifndef STIRA_IMAGE_DATASTRUCTURES_LOCALORIENTATION_H
#define STIRA_IMAGE_DATASTRUCTURES_LOCALORIENTATION_H

#include <stdint.h>
#include <iostream>
#include <stdlib.h>
#include <cmath>

namespace stira {
namespace imagedata {

/** \brief A class to contain the local orientation for a certain grid position */
class LocalOrientation{
public:

   /** \brief Constructor. */
   LocalOrientation();

   /** \brief Destructor. */
   ~LocalOrientation();

   /** \brief  Gets the local feature magnitude */
   double GetMagnitude();
   
   /**  \brief Sets the local feature magnitude 
     * \param myMagnitude the local magnitude to set*/
   void SetMagnitude(double myMagnitude);
   
   /** \brief  Gets the local feature orientation */
   double GetAngle();
    
   /** \brief  Sets the local feature orientation 
     * \param myAngle the local orientation to set*/
   void SetAngle(double myAngle);
   
   void SetMagnitudeAndAngle( double myMagnitude, double myAngle );
   
private:
   double mAngle;       ///< the orientation of the response of the feature
   double mMagnitude;   ///< magnitude of the response of the feature
   
};

}
}

#endif
