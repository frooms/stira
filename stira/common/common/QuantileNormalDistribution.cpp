#include "QuantileNormalDistribution.h"
#include "Point.h"
#include "FitCurve.h"
#include "Statistics.h"

namespace stira {
namespace common {

const double QuantileNormalDistribution::a[6]
= { -3.969683028665376e+01,  2.209460984245205e+02,  -2.759285104469687e+02,
     1.383577518672690e+02, -3.066479806614716e+01,   2.506628277459239e+00
  };

const double QuantileNormalDistribution::b[5]
= { -5.447609879822406e+01,  1.615858368580409e+02,  -1.556989798598866e+02,
     6.680131188771972e+01, -1.328068155288572e+01
  };

const double QuantileNormalDistribution::c[6]
= { -7.784894002430293e-03, -3.223964580411365e-01,  -2.400758277161838e+00,
    -2.549732539343734e+00,  4.374664141464968e+00,   2.938163982698783e+00
  };

const double QuantileNormalDistribution::d[4]
= {  7.784695709041462e-03,  3.224671290700398e-01,
     2.445134137142996e+00,  3.754408661907416e+00
  };

//---------------------------------------------------------------------------------------------------------------------


QuantileNormalDistribution::QuantileNormalDistribution()
{
}

//---------------------------------------------------------------------------------------------------------------------

double QuantileNormalDistribution::Run(double p)
{
   double q, r;

   errno = 0;

   if (p < 0 || p > 1)
   {
      errno = EDOM;
      return 0.0;
   }
   else if (p == 0)
   {
      errno = ERANGE;
      return -HUGE_VAL; // minus "infinity"
   }
   else if (p == 1)
   {
      errno = ERANGE;
      return HUGE_VAL; // "infinity"
   }
   else if (p < LOW)
   {
      // Rational approximation for lower region
      q = sqrt( -2.0 * log( p ) );

      return (    ( ( ( ( ( c[0] * q + c[1] ) * q + c[2] ) * q + c[3] ) * q + c[4] ) * q + c[5] )
               /    ( ( ( ( d[0] * q + d[1] ) * q + d[2] ) * q + d[3] ) * q + 1.0 )
             );
   }
   else if (p > HIGH)
   {
      // Rational approximation for upper region
      q  = sqrt( - 2.0 * log( 1.0 - p ) );

      return (   -( ( ( ( ( c[0] * q + c[1] ) * q + c[2] ) * q + c[3] ) * q + c[4] ) * q + c[5] )
               /  ( ( ( (   d[0] * q + d[1] ) * q + d[2] ) * q + d[3] ) * q + 1.0 )
             );
   }
   else
   {
      // Rational approximation for central region
      q = p - 0.5;
      r = q * q;

      return (   ( ( ( ( ( a[0] * r + a[1] ) * r + a[2] ) * r + a[3] ) * r + a[4] ) * r + a[5] ) * q
               / ( ( ( ( ( b[0] * r + b[1] ) * r + b[2] ) * r + b[3] ) * r + b[4] ) * r + 1.0 )
             );
   }
}

//---------------------------------------------------------------------------------------------------------------------

std::vector<double> QuantileNormalDistribution::AnalyseNormalizedHistogram( std::vector<double> normalizedHistogram, double& rho, bool writeQuantiles )
{
   int histLength = normalizedHistogram.size();
   const int nrQuantiles = 9;
   double  dataQuantiles[nrQuantiles];
   double modelQuantiles[nrQuantiles];

   double total = 0.0;
   for (unsigned int i = 0; i < normalizedHistogram.size(); i++)
   {
      total += normalizedHistogram[i];
   }

   for (unsigned int i = 0; i < normalizedHistogram.size(); i++)
   {
      normalizedHistogram[i] /= total;
   }


   double cumulSum = 0.0;
   double fraction = 1.0 / double(nrQuantiles+1);
   if (writeQuantiles)
   {
      for (int i = 0; i < histLength; i++)
      {
         cumulSum += normalizedHistogram[i];
         cout << "Bin " << i << ", hist cumulative sum = " << cumulSum << endl;
         for ( int j = 0; j < nrQuantiles; j++)
         {
            if ( cumulSum <= (j+1)*fraction )
            {
               dataQuantiles[j] = i;
               cout << "\t\t " << cumulSum << " <= " << (j+1)*fraction << ", so dataQuantiles " << j << " set to " << i << endl;
            }
         }
      }
   }
   else
   {
      for (int i = 0; i < histLength; i++)
      {
         cumulSum += normalizedHistogram[i];
         for ( int j = 0; j < nrQuantiles; j++)
         {
            if ( cumulSum <= ( j + 1 ) * fraction ) { dataQuantiles[j] = i; }
         }
      }
   }

   for ( int j = 0; j < nrQuantiles; j++)
   {
      modelQuantiles[j] = QuantileNormalDistribution::Run( (j+1)*fraction );
      if (writeQuantiles)
      {
         cout << "Model quantile generated for p = " << (j+1)*fraction << " is " << modelQuantiles[j] << endl;
      }
   }

   std::vector< Point<double> > myPoints;
   myPoints.clear();
   for (int i = 0; i < nrQuantiles; i++)
   {
      Point<double> pt(dataQuantiles[i], modelQuantiles[i]);
      myPoints.push_back( pt );
   }

   if (writeQuantiles)
   {
      int nrPoints = myPoints.size();
      for (int i = 0; i < nrPoints; i++)
      {
         cout << myPoints[i] << endl;
      }
   }

   FitCurve fc( myPoints );

   std::vector<double> paramsLinear = fc.FitLinear( );

   rho = Statistics<double>::GetCorrelation( dataQuantiles, modelQuantiles, nrQuantiles );
   return paramsLinear;
}

//---------------------------------------------------------------------------------------------------------------------

}
}
