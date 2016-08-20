
/***********************************************************************************
 *   Copyright (C) 2010 by Filip Rooms                                             *
 *                                                                                 *
 *      C++ wrapper for anigauss.c and anigauss.h by Jan-Mark Geusebroek           *
 *              Original copyright notice in anigauss.h                            *
 *           http://staff.science.uva.nl/~mark/downloads.html#anigauss             *
 *                                                                                 *
 *  Terms and conditions for using this software in any form are provided in the   *
 *  file COPYING, which can be found in the root directory of this project.        *
 *                                                                                 *
 *   Contact data: filip.rooms@gmail.com                                           *
 *                 http://www.filiprooms.be/                                       *
 *                                                                                 *
 ***********************************************************************************/

#ifndef STIRA_FILTER_ANISOTROPICGAUSSIAN_H
#define STIRA_FILTER_ANISOTROPICGAUSSIAN_H

#include "../../imagedata/datastructures/Image.h"

namespace stira{
namespace filter{

using namespace imagedata;

class AnisotropicGaussian
{
public:
   /** \brief constructor */
   AnisotropicGaussian();

   /** \brief destructor */
   ~AnisotropicGaussian();

   /** \brief executes an anisotropic gaussian filtering according to algorithm (and implementation) of Jan-Mark Geusebroek
     * \param pInput input grid to be filtered
     * \param sigmav sigma along short axis
     * \param sigmau sigma along long axis
     * \param theta orientation of long axis in radians
     * \param orderv order of derivative of the Gaussian along short axis
     * \param orderu order of derivative of the Gaussian along long axis
    */
   ArrayGrid<double>* Run( ArrayGrid<double> *pInput, double sigmav, double sigmau, double theta, int orderv, int orderu);

   double ComputeFilterCoefficients( double* pFilterX, double* pFilterTanp, double sigmav, double sigmau, double phi );

   bool RunLean( double *pInput, double *pOutput, int width, int height, double* pFilterX, double* pFilterTanp, double phi, int orderv, int orderu, double tanp );

private:
   /** \brief converts the angle of the real rotated anisotropic gaussian filter kernel to phi
     * This phi is used in paper of original author and further computations, and represents the angle between the x axis
     * and the line that connects the origin and the point where the ellipse reaches its maximum y value
     * \warning NOT FUNCTIONAL YET; gives strange unexpected results
     * \param theta orientation of long axis in radians
     * \param sigmau sigma along long axis
     * \param sigmav sigma along short axis */
   double GetPhi( double theta, double sigmau, double sigmav );

};

}
}

#endif // ANISOTROPICGAUSSIAN_H
