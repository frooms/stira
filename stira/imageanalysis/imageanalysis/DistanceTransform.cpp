

#include <algorithm>
#include "../../common/common/StiraMacros.h"
#include "DistanceTransform.h"

namespace stira {
namespace imageanalysis {

DistanceTransform::DistanceTransform()
{
    mpValuesIn = 0;
    mpDistanceTransformValues = 0;
    mpParabolaLocations = 0;
    mpParabolaBoundary = 0;
}

DistanceTransform::~DistanceTransform()
{
    ResetBuffers();
}

//------------------------------------------------------------------------------------------

double DistanceTransform::ComputeParabolaIntersection( double *f, int* v, int q, int k )
{
    double tmpValue = ( ( f[q] + POWER2(q) ) - ( f[ v[k] ] + POWER2(v[k]) ) ) / ( 2 * q - 2 * v[k] );
    return tmpValue;
}

//------------------------------------------------------------------------------------------

// distance transform of 1D function using Euclidean squared distance
void DistanceTransform::DistanceTransform1D( int n )
{
   int parabolaIndex = 0;                      // Index of rightmost parabola in lower envelope
   mpParabolaLocations[0] = 0;
   mpParabolaBoundary[0] = -STIRA_INFINITE;
   mpParabolaBoundary[1] = +STIRA_INFINITE;

   for (int q = 1; q <= n-1; q++)   // Compute lower envelope
   {
      double intersection  = ComputeParabolaIntersection( mpValuesIn, mpParabolaLocations, q, parabolaIndex );
      while (intersection <= mpParabolaBoundary[ parabolaIndex ] )
      {
         parabolaIndex--;
         intersection  = ComputeParabolaIntersection( mpValuesIn, mpParabolaLocations, q, parabolaIndex );
      }
      parabolaIndex++;
      mpParabolaLocations[parabolaIndex] = q;
      mpParabolaBoundary[parabolaIndex] = intersection;
      mpParabolaBoundary[parabolaIndex+1] = +STIRA_INFINITE;
   }

   // Fill in values of distance transform
   parabolaIndex = 0;
   for (int q = 0; q <= n-1; q++)
   {
      while (mpParabolaBoundary[parabolaIndex+1] < q)
      {
         parabolaIndex++;
      }
      mpDistanceTransformValues[q] = POWER2(q-mpParabolaLocations[parabolaIndex]) + mpValuesIn[mpParabolaLocations[parabolaIndex]];
   }
}

//------------------------------------------------------------------------------------------

// dt of 2d function using squared distance
void DistanceTransform::DistanceTransform2D(image::ArrayGrid<double> *pGridInOut )
{
   int width = pGridInOut->GetWidth();
   int height = pGridInOut->GetHeight();
   int n  = std::max( width, height );

   // allocate memory buffers just once per image instead of for every row and every column
   mpValuesIn = new double[ n ];
   mpDistanceTransformValues = new double[n];
   mpParabolaLocations = new int[n];            // Locations of parabolas in lower envelope
   mpParabolaBoundary = new double[n+1];     // Locations of boundaries between parabolas

   // transform along columns
   for (int x = 0; x < width; x++)
   {
      pGridInOut->GetColumnCopy( x, mpValuesIn );

      DistanceTransform1D( height );
      for (int y = 0; y < height; y++)
      {
         pGridInOut->SetValue( x, y, mpDistanceTransformValues[ y ] );
      }
   }

   // transform along rows
   for (int y = 0; y < height; y++)
   {
      pGridInOut->GetRowCopy( y, mpValuesIn );
      DistanceTransform1D( width );
      for (int x = 0; x < width; x++)
      {
         pGridInOut->SetValue(x, y, mpDistanceTransformValues[x]);
      }
   }
   ResetBuffers();
}

void DistanceTransform::ResetBuffers()
{
    if (mpValuesIn != 0)
    {
        delete []mpValuesIn;
        mpValuesIn = 0;
    }

    if (mpDistanceTransformValues != 0)
    {
        delete []mpDistanceTransformValues;
        mpDistanceTransformValues = 0;
    }

    if (mpParabolaLocations != 0)
    {
       delete []mpParabolaLocations;
       mpParabolaLocations = 0;
    }

    if (mpParabolaBoundary != 0)
    {
       delete []mpParabolaBoundary;
        mpParabolaBoundary = 0;
    }
}

//------------------------------------------------------------------------------------------

image::ArrayGrid<double>* DistanceTransform::Run(image::ArrayGrid<double> *pGridIn)
{
   int width = pGridIn->GetWidth();
   int height = pGridIn->GetHeight();

   image::ArrayGrid<double> *pGridOut = new image::ArrayGrid<double>(width, height, false, 0.0);
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         if (pGridIn->GetValue(x, y) > 245 )  // objects of interest to compute distance to
         {
            pGridOut->SetValue(x, y, 0);
         }
         else                                 // image background
         {
            pGridOut->SetValue( x, y, STIRA_INFINITE);
         }
      }
   }

   DistanceTransform2D( pGridOut );
   return pGridOut;
}

//------------------------------------------------------------------------------------------

}
}
