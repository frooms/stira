
/*****************************************************************************************
 *  Copyright (C) 2010 by Filip Rooms, implementing an idea of prof. Wilfried Philips    *
 *                                                                                       *
 *   Reference prototype on  /v/frooms/research/philips-recursive/arcelor                *
 *                                                                                       *
 *   Similar idea as in H.Q. Luong, W. Philips, "Robust Reconstruction of Low-Resolution *
 *                       Document Images by Exploiting Repetitive Character Behaviour",  *
 *                       in International Journal on Document Analysis and Recognition   *
 *                       (IJDAR), vol. 11, nr. 1, pp. 39-51, 2008.                       *
 *                                                                                       *
 *  Terms and conditions for using this software in any form are provided in the         *
 *  file COPYING, which can be found in the root directory of this project.              *
 *                                                                                       *
 *   Contact data: filip.rooms@gmail.com                                                 *
 *                 http://www.filiprooms.be/                                             *
 *                                                                                       *
 *****************************************************************************************/

#ifndef STIRA_IMAGEANALYSIS_CONTOURTRACING_H
#define STIRA_IMAGEANALYSIS_CONTOURTRACING_H

#include "../../imagedata/datastructures/Image.h"
#include <string>
namespace stira {
namespace imageanalysis {

using namespace image;

/** \brief Contour tracing class
  * Traces contours that go mainly horizontally*/
class ContourTracing
{
public:

   /** \brief constructor
     * \param pGridIn input grid in which to trace contours
     * \param alphaStraight larger forgetting factor for straight lines, making them be forgotten less quickly
     * \param alphaNotStraight smaller forgetting factor penalizing non-straight lines
     * \param filePath string with path to be able to write intermediate files to */
   ContourTracing( double alphaStraight, double alphaNotStraight, std::string filePath );

   /** \brief destructor */
   ~ContourTracing( );

   /** \brief Run method
     * returns a pair where the first ArrayGrid is the result left-right, and the second right-left */
   std::pair< ArrayGrid<double>*, ArrayGrid<double>* > Run( ArrayGrid<double>* pGridIn, int ID=0 );

   /** \brief Run method
     * Forward propagate from left to right; backward collection from right to left */
   ArrayGrid<double>* RunLeftRight( ArrayGrid<double>* pGridIn, int ID );

   /** \brief Run method
     * Forward propagate from right to left to right; backward collection from left to right */
   ArrayGrid<double>* RunRightLeft( ArrayGrid<double>* pGridIn, int ID );

private:

   /** \brief propagates energy forward from left to right */
   void ForwardPropagateLeft( ArrayGrid<double>* pGridIn, ArrayGrid<double>* pGridOut, ArrayGrid<double>* pGridTmp );

   /** \brief recovers energy back from right to left */
   void BackwardRecoverRight( ArrayGrid<double>* pGridOut, ArrayGrid<double>* pGridTmp );

   /** \brief propagates energy forward from right to left */
   void ForwardPropagateRight( ArrayGrid<double>* pGridIn, ArrayGrid<double>* pGridOut, ArrayGrid<double>* pGridTmp );

   /** \brief recovers energy back from left to right */
   void BackwardRecoverLeft( ArrayGrid<double>* pGridOut, ArrayGrid<double>* pGridTmp );

   double mAlphaStraight;  ///< forgetting factor for straight lines
   double mOneMinusAlphaStraight;  ///< one minus forgetting factor for straight lines; to save recomputation every time in loop

   double mAlphaNotStraight;  ///< smaller forgetting factor penalizing non-straight lines
   double mOneMinusAlphaNotStraight;  ///< one minus forgetting factor for non-straight lines; to save recomputation every time in loop
   std::string mFilePath;  ///< string with path to be able to write intermediate files to
};

}
}

#endif // CONTOURTRACING_H
