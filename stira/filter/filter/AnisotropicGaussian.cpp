

#include <stdlib.h>
#include <math.h>
#include "../../common/common/StiraMacros.h"
#include "../../common/common/MathUtils.h"
#include "AnisotropicGaussian.h"
#include "anigauss.h"

#include <iostream>

namespace stira{
namespace filter{

using namespace common;

using namespace std;

//-----------------------------------------------------------------------------------------

AnisotropicGaussian::AnisotropicGaussian()
{
}

//-----------------------------------------------------------------------------------------

AnisotropicGaussian::~AnisotropicGaussian()
{
}

//-----------------------------------------------------------------------------------------

double AnisotropicGaussian::ComputeFilterCoefficients( double* pFilterX, double* pFilterTanp, double sigmav, double sigmau, double phi )
{
   return aniComputeFilterCoefficients( pFilterX, pFilterTanp, sigmav, sigmau, phi );
}

//-----------------------------------------------------------------------------------------

ArrayGrid<double>* AnisotropicGaussian::Run( ArrayGrid<double> *pInput, double sigmav, double sigmau, double phi, int orderv, int orderu)
{
   double pFilterX[7];
   double pFilterTanp[7];
   int width  = pInput->GetWidth();
   int height = pInput->GetHeight();

   double tanp = ComputeFilterCoefficients( pFilterX, pFilterTanp, sigmav, sigmau, phi );
   ArrayGrid<double>* pGridOut = new ArrayGrid<double>( width, height );
   RunLean( pInput->GetDataPointer(), pGridOut->GetDataPointer(), width, height, pFilterX, pFilterTanp, phi, orderv, orderu, tanp );
   return pGridOut;
}

//-----------------------------------------------------------------------------------------

bool AnisotropicGaussian::RunLean( double *pInput, double *pOutput, int width, int height, double* pFilterX, double* pFilterTanp, double phi, int orderv, int orderu, double tanp )
{
   anigausslean( pInput, pOutput, width, height, phi, orderv, orderu, pFilterX, pFilterTanp, tanp );
   return true;
}

//-----------------------------------------------------------------------------------------

}
}
