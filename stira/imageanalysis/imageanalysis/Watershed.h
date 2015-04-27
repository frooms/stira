
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

#ifndef STIRA_IMAGEANALYSIS_WATERSHED_H
#define STIRA_IMAGEANALYSIS_WATERSHED_H


namespace stira {
namespace imageanalysis {

/////////////////////////
// SMALL HELPER TYPES  //
/////////////////////////

/** \brief Little helper class to compare PixelElement's to order them in the priority queue*/
template < class T >
struct PixelElement
{
   T value;  ///< pixel intensity
   int x;      ///< x coordinate of pixel
   int y;      ///< y coordinate of pixel
};
   
/** \brief help class: needed by priority_queue for ordering the elements */
template < class T >
class mycomparison
{
   bool reverse;
public:
   /** \brief constructor 
     * \param revparam true if we want to sort from large to small*/
   mycomparison(const bool& revparam=true)
   {
      reverse=revparam;
   }
   
   /** \brief comparison operator: compares the values of two pixel elements
     * \param lhs first pixel element
     * \param rhs second pixel element*/
   bool operator() ( PixelElement<T>& lhs, PixelElement<T>& rhs) const
   {
      if (reverse) return (lhs.value > rhs.value );
      else return (lhs.value < rhs.value);
   }
};

}
}

#endif
