
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

#ifndef STIRA_DECONVOLVE_RICHARDSONLUCYDECONVOLVE_H
#define STIRA_DECONVOLVE_RICHARDSONLUCYDECONVOLVE_H

#include "../../imagedata/datastructures/Image.h"
#include "../../fouriertools/fouriertools/FFTBand.h"
#include "IterativeDeconvolve.h"

namespace stira{
namespace deconvolve{

using namespace imagedata;

/** \brief child class for computing Richardson-Lucy deconvolution

  * INRIA Techical Report N° 5272, July 2004
  * "3D Microscopy Deconvolution using Richardson-Lucy Algorithm with Total Variation Regularization"
  * Dey, N. and Blanc-F\'{e}raud, L. and Zimmer, C. and Roux, P. and Kam, Z. and Olivo-Marin, J.C and 
  * Zerubia, J.
  * ftp://ftp.inria.fr/INRIA/publication/publi-ps-gz/RR/RR-5272.ps.gz
  *
  *  PhD Thesis "Accelerated iterative blind deconvolution, University of Auckland, New Zealand
  *  Biggs, David S.C.
  *  http://hdl.handle.net/2292/1760
  */
class RichardsonLucyDeconvolve: public IterativeDeconvolve
{
public:
   /** \brief constructor without setting PSF, so is still to be determined before run
     * \param pDegradedImage the input image to be restored
     * \param myRegularizationType type of regularization to be applied
     * \param maxNrOfIterations maximum number of iterations */
   RichardsonLucyDeconvolve( Image* pDegradedImage, regularizationType myRegularizationType=REGULARIZE_NONE, int maxNrOfIterations=20 );
   
   /** \brief constructor with PSF
     * \param pDegradedImage the input image to be restored
     * \param pPSF the input PSF (needs same width and height as pDegradedImage)
     * \param myRegularizationType type of regularization to be applied
     * \param maxNrOfIterations maximum number of iterations */
   RichardsonLucyDeconvolve( Image* pDegradedImage, Image* pPSF, regularizationType myRegularizationType=REGULARIZE_NONE, int maxNrOfIterations=20  );
   
   /** \brief destructor*/
   ~RichardsonLucyDeconvolve( );
   
   /** \brief starts the deconvolution if all inputs are available
     * After completion, get the result with GetRestoredImage() from the parent class*/
   bool Run();
   
   /** \brief sets regularization type*/
   regularizationType GetRegularizationType();
   
   /** \brief gets regularization type
     * \param myType type of regularization to be applied*/
   void SetRegularizationType(regularizationType myType);
   
   /** \brief sets flag whether or not to enforce the solution to fit within an intensity range
     * \param flag boolean value of the flag to set*/
   void SetEnforceIntensityRange( bool flag );
   
   /** \brief gets flag whether or not to enforce the solution to fit within an intensity range */
   bool GetEnforceIntensityRange();

   /** \brief prints for diagnostic purposes parameters to standard output*/
   void PrintParameters();
   
private:
   
   /** \brief initializes initial parameters, called from constructor*/
   virtual void RegularizeIteration( );
   
   /** \brief Regularizes current solution by Total Variation*/
   void RegularizeTotalVariation( );

   /** \brief help function for RegularizeTotalVariation; computes M function (see reference Dey et. al.)
     * if both a and b are positive, it returns half of the minimum of a and b
     * if one is positive and one negative, it returns zero
     * if oboth a and b are negative, it returns half of the minimum of a and b
     * \param a first number 
     * \param b second number */
   double MFunction(double a, double b);

   /** \brief help function for RegularizeTotalVariation; computes x contribution (see reference Dey et. al.) 
     * \param pLastSolutionGrid input grid, result of last iteration
     * \param x x coordinate for pixel of which to compute x contribution
     * \param y y coordinate for pixel of which to compute x contribution*/
   double GetXContribution( ArrayGrid<double>* pLastSolutionGrid, int x, int y);

   /** \brief help function for RegularizeTotalVariation; computes y contribution (see reference Dey et. al.) 
     * \param pLastSolutionGrid
     * \param x x coordinate for pixel of which to compute y contribution
     * \param y y coordinate for pixel of which to compute y contribution*/
   double GetYContribution( ArrayGrid<double>* pLastSolutionGrid, int x, int y);
   
   /** \brief Regularizes current solution by Tikhonov-Miller*/
   void RegularizeTikhonovMiller( );
   
   /** \brief Regularizes current solution by Conchello*/
   void RegularizeConchello( );

   /** \brief Regularizes current solution by Maximum Entropy*/
   void RegularizeMaximumEntropy( );

   regularizationType mRegularizationType; ///< Regularization method 

   /** \brief checks if all inputs are available*/
   bool IsReadyToRun();

   /** \brief Runs a single iteration on a single colour band of the image */
   bool RunSingleIterationSingleBand( );
   
   bool mEnforceIntensityRange;  ///< flag whether to enforce the solution to fit within an intensity range

   /** \brief composes the file name of the solution, depending on the chosen regularization method */
   std::string ComposeOutputName();

   /** \brief Clips the intensities of the solution to the rang 0 - 255 */
   void ClipIntensities( );

};

}
}

#endif
