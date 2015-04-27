
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

#include "../../common/common/MathUtils.h"
#include "../../common/common/StiraMacros.h"
#include "ComputeOrientation.h"
#include "../../image/tools/ImageIO.h"
#include <cmath>

namespace stira {
namespace steerable {

using namespace std;
using namespace image;
using namespace common;

//============================================================================

ComputeOrientation::ComputeOrientation()
{
}

//============================================================================

ComputeOrientation::~ComputeOrientation()
{
}

//============================================================================

OrientationGrid* ComputeOrientation::ComputeDominantOrientationInputFreemanAdelson(
                      ArrayGrid<double>* pResponseH2a,
                      ArrayGrid<double>* pResponseH2b,
                      ArrayGrid<double>* pResponseH2c,
                      ArrayGrid<double>* pResponseH2d,
                      ArrayGrid<double>* pResponseG2a,
                      ArrayGrid<double>* pResponseG2b,
                      ArrayGrid<double>* pResponseG2c)
{
   int width, height;
   if (    ( pResponseH2a->GetWidth() == pResponseH2b->GetWidth() )
        && ( pResponseH2a->GetWidth() == pResponseH2c->GetWidth() )
        && ( pResponseH2a->GetWidth() == pResponseH2d->GetWidth() )
        && ( pResponseH2a->GetWidth() == pResponseG2a->GetWidth() )
        && ( pResponseH2a->GetWidth() == pResponseG2b->GetWidth() )
        && ( pResponseH2a->GetWidth() == pResponseG2c->GetWidth() )
      )
   {
      width = pResponseH2a->GetWidth();
   }
   else
   {
      cerr << "Input bands have different widths; aborting and returning 0;" << endl << flush;
      return 0;
   }

   if (    ( pResponseH2a->GetHeight() == pResponseH2b->GetHeight() )
        && ( pResponseH2a->GetHeight() == pResponseH2c->GetHeight() )
        && ( pResponseH2a->GetHeight() == pResponseH2d->GetHeight() )
        && ( pResponseH2a->GetHeight() == pResponseG2a->GetHeight() )
        && ( pResponseH2a->GetHeight() == pResponseG2b->GetHeight() )
        && ( pResponseH2a->GetHeight() == pResponseG2c->GetHeight() )
      )
   {
      height = pResponseH2a->GetHeight();
   }
   else
   {
      cerr << "Input bands have different heights; aborting and returning 0;" << endl << flush;
      return 0;
   }

   double C2, C3;
   OrientationGrid* pOrientationGrid = new OrientationGrid( width, height );
   double tmpAngle, tmpMagnitude;
   double halfPi = M_PI / 2.0;

   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         C2 =        0.5 * ( POWER2( pResponseG2a->GetValue(x, y) ) - POWER2( pResponseG2c->GetValue(x, y) ) )
               + 0.46875 * ( POWER2( pResponseH2a->GetValue(x, y) ) - POWER2( pResponseH2d->GetValue(x, y) ) )
               + 0.28125 * ( POWER2( pResponseH2b->GetValue(x, y) ) - POWER2( pResponseH2c->GetValue(x, y) ) )
               + 0.1875  * (    ( pResponseH2a->GetValue(x, y) * pResponseH2c->GetValue(x, y))
                              - ( pResponseH2b->GetValue(x, y) * pResponseH2d->GetValue(x, y))
                           );

         C3 =                 -  pResponseG2a->GetValue(x, y) * pResponseG2b->GetValue(x, y)
                -                pResponseG2b->GetValue(x, y) * pResponseG2c->GetValue(x, y)
                - 0.9375 * (   ( pResponseH2c->GetValue(x, y) * pResponseH2d->GetValue(x, y)) 
                             + ( pResponseH2a->GetValue(x, y) * pResponseH2b->GetValue(x, y))
                           )
                - 1.6875      *  pResponseH2b->GetValue(x, y) * pResponseH2c->GetValue(x, y)
                - 0.1875      *  pResponseH2a->GetValue(x, y) * pResponseH2d->GetValue(x, y);

         tmpAngle     = MathUtils::ComputeArgument(C2, C3) * 0.5;
         tmpMagnitude = L2NORM( C2, C3 );

         if (tmpAngle >= halfPi )
         {
             tmpAngle -= halfPi;
         }
         else
         {
             tmpAngle += halfPi;
         }

         pOrientationGrid->SetOrientation(x, y, tmpAngle);
         pOrientationGrid->SetMagnitude(x, y, tmpMagnitude);
      }
   }
   pOrientationGrid->ExportMagnitudeImage( string("EdgeMagnitude.ppm") );
   pOrientationGrid->ExportOrientationImage( string("EdgeDirection.ppm"), 50.0);
   return pOrientationGrid;
}

//============================================================================

//see maple file steerodd.mws
OrientationGrid* ComputeOrientation::ComputeDominantOrientationInputComplexPyramidLevel( PyramidLevel< std::complex<double> >* pPyrLevel)
{
    int nrOfOrientations = pPyrLevel->GetNumberOfOrientations();
    
    if (nrOfOrientations != 4)
    {
      cerr << "ComputeDominantOrientationInputComplexPyramidLevel only implemented fro 4 orientations; aborting" << endl << flush;
      return 0;
    }
    else
    {
      int width = pPyrLevel->GetWidth();
      int height = pPyrLevel->GetHeight();
      OrientationGrid* pOrientationGrid = new OrientationGrid( width, height);
      double tmpAngle, tmpMagnitude;
      double C2, C3;
      
      ArrayGrid< complex<double> >* pB0 = pPyrLevel->GetOrientedBand(0);
      ArrayGrid< complex<double> >* pB1 = pPyrLevel->GetOrientedBand(1);
      ArrayGrid< complex<double> >* pB2 = pPyrLevel->GetOrientedBand(2);
      ArrayGrid< complex<double> >* pB3 = pPyrLevel->GetOrientedBand(3);
    
      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x++)
         {

            //terms with cos(2theta)
            C2 =   3.0     * pB0->GetValue(x, y).real() * pB0->GetValue(x, y).real() /  8.0
                 - 3.0     * pB2->GetValue(x, y).real() * pB2->GetValue(x, y).real() /  8.0
                 + M_SQRT2 * pB0->GetValue(x, y).real() * pB1->GetValue(x, y).real() / 16.0
                 - M_SQRT2 * pB0->GetValue(x, y).real() * pB3->GetValue(x, y).real() / 16.0
                 - M_SQRT2 * pB1->GetValue(x, y).real() * pB2->GetValue(x, y).real() / 16.0
                 +           pB1->GetValue(x, y).real() * pB3->GetValue(x, y).real() /  8.0
                 - M_SQRT2 * pB2->GetValue(x, y).real() * pB3->GetValue(x, y).real() / 16.0
                 
                 // imaginary parts in theory not steerable, but we assume they are (which seems to work)
                 + 3.0     * pB0->GetValue(x, y).imag() * pB0->GetValue(x, y).imag() /  8.0
                 - 3.0     * pB2->GetValue(x, y).imag() * pB2->GetValue(x, y).imag() /  8.0
                 + M_SQRT2 * pB0->GetValue(x, y).imag() * pB1->GetValue(x, y).imag() / 16.0
                 - M_SQRT2 * pB0->GetValue(x, y).imag() * pB3->GetValue(x, y).imag() / 16.0
                 - M_SQRT2 * pB1->GetValue(x, y).imag() * pB2->GetValue(x, y).imag() / 16.0
                 +           pB1->GetValue(x, y).imag() * pB3->GetValue(x, y).imag() /  8.0
                 - M_SQRT2 * pB2->GetValue(x, y).imag() * pB3->GetValue(x, y).imag() / 16.0;

            //terms with sin(2theta)
            C3 =  3.0        * pB1->GetValue(x, y).real() * pB1->GetValue(x, y).real() /  8.0
                 -3.0        * pB3->GetValue(x, y).real() * pB3->GetValue(x, y).real() /  8.0
                 + M_SQRT2   * pB0->GetValue(x, y).real() * pB1->GetValue(x, y).real() / 16.0
                 -             pB0->GetValue(x, y).real() * pB2->GetValue(x, y).real() /  8.0
                 + M_SQRT2   * pB0->GetValue(x, y).real() * pB3->GetValue(x, y).real() / 16.0
                 + M_SQRT2   * pB1->GetValue(x, y).real() * pB2->GetValue(x, y).real() / 16.0
                 - M_SQRT2   * pB2->GetValue(x, y).real() * pB3->GetValue(x, y).real() / 16.0
                 
                 // imaginary parts in theory not steerable, but we assume they are (and it seems to work)
                 + 3.0       * pB1->GetValue(x, y).imag() * pB1->GetValue(x, y).imag() /  8.0
                 - 3.0       * pB3->GetValue(x, y).imag() * pB3->GetValue(x, y).imag() /  8.0
                 + M_SQRT2   * pB0->GetValue(x, y).imag() * pB1->GetValue(x, y).imag() / 16.0
                 -             pB0->GetValue(x, y).imag() * pB2->GetValue(x, y).imag() /  8.0
                 + M_SQRT2   * pB0->GetValue(x, y).imag() * pB3->GetValue(x, y).imag() / 16.0
                 + M_SQRT2   * pB1->GetValue(x, y).imag() * pB2->GetValue(x, y).imag() / 16.0
                 - M_SQRT2   * pB2->GetValue(x, y).imag() * pB3->GetValue(x, y).imag() / 16.0;

            tmpAngle     = MathUtils::ComputeArgument(C2, C3) * 0.5;
            tmpMagnitude = L2NORM( C2, C3 );
   
            pOrientationGrid->SetOrientation(x, y, tmpAngle);
            pOrientationGrid->SetMagnitude(x, y, tmpMagnitude);
         }
      }
      return pOrientationGrid;
   }
}

}
}
