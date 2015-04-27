
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

#include "StegerLineDetector.h"
#include "../../filter/filter/GaussConvolve.h"
#include "../../image/datastructures/OrientationGrid.h"
#include "../../image/tools/ImageIO.h"
#include "../../common/common/MathUtils.h"
#include <string>

#define EDGE_THRESHOLD 0.6

namespace stira {
namespace imageanalysis {

using namespace std;
using namespace image;
using namespace filter;
using namespace common;

//----------------------------------------------------------------
   
StegerLineDetector::StegerLineDetector()
{
}

//----------------------------------------------------------------

StegerLineDetector::~StegerLineDetector()
{
}

//----------------------------------------------------------------

bool StegerLineDetector::EigenValueComputation( double App, double Aqq, double Apq, 
                                                double& outEigenValue1, double& outEigenValue2, 
                                                Point<double>& outEigenVector1, Point<double>& outEigenVector2)
{
   double tmpEigenValue1, tmpEigenValue2;
   double myCos, mySin;
   if (Apq != 0.0)
   {
      double theta = (Aqq - App) / (2.0 * Apq);
      
      double mySign = theta / fabs(theta);
      double myTan = mySign / ( fabs(theta) + sqrt( theta * theta + 1.0) );
      
      myCos = 1.0 / ( sqrt ( myTan * myTan + 1.0 ) );
      mySin = myTan * myCos;
      
      tmpEigenValue1 = App - myTan * Apq;
      tmpEigenValue2 = Aqq + myTan * Apq;
   }
   else
   {
      myCos = 1.0;
      mySin = 0.0;
      tmpEigenValue1 = App;
      tmpEigenValue2 = Aqq;
   }
   
   Point<double> tmpEigenVector1( myCos, -mySin );
   Point<double> tmpEigenVector2( mySin,  myCos );

   /* If the absolute value of one eigenvalue is larger than the absolute value of the other, 
      it becomes the first eigenvector.  If both have the same absolute value, put
      the negative one first. */
   if (fabs (tmpEigenValue1) > fabs (tmpEigenValue2))
   {
      outEigenValue1 = tmpEigenValue1;
      outEigenValue2 = tmpEigenValue2;
      outEigenVector1 = tmpEigenVector1;
      outEigenVector2 = tmpEigenVector2;
   }
   else if (fabs (tmpEigenValue1) < fabs (tmpEigenValue2))
   {
      outEigenValue1 = tmpEigenValue2;
      outEigenValue2 = tmpEigenValue1;
      outEigenVector1 = tmpEigenVector2;
      outEigenVector2 = tmpEigenVector1;
   }
   else
   {
      if (tmpEigenValue1 < tmpEigenValue2)
      {
         outEigenValue1 = tmpEigenValue1;
         outEigenValue2 = tmpEigenValue2;
         outEigenVector1 = tmpEigenVector1;
         outEigenVector2 = tmpEigenVector2;
      }
      else
      {
         outEigenValue1 = tmpEigenValue2;
         outEigenValue2 = tmpEigenValue1;
         outEigenVector1 = tmpEigenVector2;
         outEigenVector2 = tmpEigenVector1;
      }
   }
   
   return true;
}

//----------------------------------------------------------------

image::ArrayGrid<bool>* StegerLineDetector::Run( image::ArrayGrid<double>* pGridIn, double sigmaSmooth, double lowerThreshold, double higherThreshold, bool isModeLight )
{
   int width = pGridIn->GetWidth();
   int height = pGridIn->GetHeight();
   OrientationGrid* pOrientationGrid = new OrientationGrid(width, height);  // NOT initialized at construction; values are set below
   ArrayGrid<bool>* pLineGrid = new ArrayGrid<bool>(width, height);  // NOT initialized at construction; values are set below
   pLineGrid->SetGridValues( false );
   
   ArrayGrid<double>* pGx  = GaussConvolve::DerivativeConvolveFFT( pGridIn, sigmaSmooth, sigmaSmooth, GaussConvolve::DERIVATIVE_X  );
   ArrayGrid<double>* pGy  = GaussConvolve::DerivativeConvolveFFT( pGridIn, sigmaSmooth, sigmaSmooth, GaussConvolve::DERIVATIVE_Y  );
   ArrayGrid<double>* pGxx = GaussConvolve::DerivativeConvolveFFT( pGridIn, sigmaSmooth, sigmaSmooth, GaussConvolve::DERIVATIVE_XX );
   ArrayGrid<double>* pGyy = GaussConvolve::DerivativeConvolveFFT( pGridIn, sigmaSmooth, sigmaSmooth, GaussConvolve::DERIVATIVE_YY );
   ArrayGrid<double>* pGxy = GaussConvolve::DerivativeConvolveFFT( pGridIn, sigmaSmooth, sigmaSmooth, GaussConvolve::DERIVATIVE_XY );
   
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         double eigenValue1, eigenValue2, eigenValue;
         common::Point<double> eigenVector1;
         common::Point<double> eigenVector2;
         
         EigenValueComputation( pGxx->GetValue(x, y), pGyy->GetValue(x, y), pGxy->GetValue(x, y),
                                eigenValue1, eigenValue2, eigenVector1, eigenVector2);

         if (isModeLight == true)
         {
            eigenValue = -eigenValue1;
         }
         else
         {
            eigenValue = eigenValue1;
         }
         
         if (eigenValue > 0.0)
         {
            double n1 = eigenVector1.GetX();
            double n2 = eigenVector1.GetY();
            
            double a = pGxx->GetValue(x, y) * n1 * n1 + 2.0 * pGxy->GetValue(x, y) * n1 * n2 + pGyy->GetValue(x, y) * n2 * n2;
            double b = pGx->GetValue(x, y) * n1 + pGy->GetValue(x, y) * n2;
            double linearSolution;
            if ( MathUtils::SolveLinearEquation( a, b, linearSolution ) == true )
            {
               double p1 = linearSolution * n1;
               double p2 = linearSolution * n2;
               if ((fabs (p1) <= EDGE_THRESHOLD) && (fabs (p2) <= EDGE_THRESHOLD))
               {
                  int xx = (int)(x + p1 + 0.5);
                  int yy = (int)(y + p2 + 0.5);
                  if (  (xx >= 0) && (xx < width) && (yy >=0) && (yy < height))
                  {
                     if (eigenValue >= lowerThreshold)
                     {
                        if (eigenValue >= higherThreshold)
                        {
                           pLineGrid->SetValue(xx, yy, true);
                        }
                     }
                     else
                     {
                        pLineGrid->SetValue(xx, yy, false);
                     }
                  }
               }
            }
            
            pOrientationGrid->SetOrientation( x, y, MathUtils::ComputeArgument( eigenVector1.GetX(),  eigenVector1.GetY() ) );
            pOrientationGrid->SetMagnitude( x, y, eigenValue1);
         }
      }
   }
   pOrientationGrid->ExportMagnitudeImage( string("StegerMagnitude.pgm") );
   pOrientationGrid->ExportOrientationImage( string("StegerOrientation.pgm"), -100000.0 );
   
   delete pGx;
   delete pGy;
   delete pGxx;
   delete pGyy;
   delete pGxy;
   delete pOrientationGrid;
   return pLineGrid;
}

//----------------------------------------------------------------

}
}
