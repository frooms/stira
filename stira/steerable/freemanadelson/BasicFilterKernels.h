
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

#ifndef STIRA_STEERABLE_FREEMANADELSON_BASICFILTERKERNELS_H
#define STIRA_STEERABLE_FREEMANADELSON_BASICFILTERKERNELS_H
#include <stdint.h>

namespace stira {
namespace steerable {

/** \brief A container class to store taps for steerable filters G2 and H2 by Freeman and Adelson
  *
  * W. T. Freeman and E. H. Adelson, The design and use of steerable filters,
  * IEEE Trans. on Pattern Analysis and Machine Intelligence, vol. 13, no. 9, pp. 891 - 906, Sept. 1991.
  * also available as technical report from http://people.csail.mit.edu/billf/steerpaper.html */
class BasicFilterKernels{
public:
   
   /** \brief Constructor */
   BasicFilterKernels();

   /** \brief Destructor */
   ~BasicFilterKernels();

   /** \brief Gets the number of coefficients in the filter */
   static int GetBasicfilterLength();

   // definition of the filters; variations of filters of Adelson and Freeman (sampled from the same functions)
   // cfr http://people.csail.mit.edu/billf/papers/steerpaper91.pdf pp.39--40
   /** \brief Gets pointer to array with filter taps for filter G2F1*/
   static double* GetFilterG2F1();
   /** \brief Gets pointer to array with filter taps for filter G2F2*/
   static double* GetFilterG2F2();
   /** \brief Gets pointer to array with filter taps for filter G2F3*/
   static double* GetFilterG2F3();
   
   /** \brief Gets pointer to array with filter taps for filter H2F1*/
   static double* GetFilterH2F1();
   /** \brief Gets pointer to array with filter taps for filter H2F2*/
   static double* GetFilterH2F2();
   /** \brief Gets pointer to array with filter taps for filter H2F3*/
   static double* GetFilterH2F3();
   /** \brief Gets pointer to array with filter taps for filter H2F4*/
   static double* GetFilterH2F4();
   
private:

   static double spFilterG2F1[];  ///< array with filter taps for filter G2F1
   static double spFilterG2F2[];  ///< array with filter taps for filter G2F2
   static double spFilterG2F3[];  ///< array with filter taps for filter G2F3
   static double spFilterH2F1[];  ///< array with filter taps for filter H2F1
   static double spFilterH2F2[];  ///< array with filter taps for filter H2F2
   static double spFilterH2F3[];  ///< array with filter taps for filter H2F3
   static double spFilterH2F4[];  ///< array with filter taps for filter H2F4

};
}
}
#endif
