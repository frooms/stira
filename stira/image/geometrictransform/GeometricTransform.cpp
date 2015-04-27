#include "GeometricTransform.h"
#include "../tools/BilinearInterpolator.h"
#include "../tools/NearestNeighborInterpolator.h"


namespace stira {
namespace image {

GeometricTransform::GeometricTransform( )
{
   mpInterpolator = new BilinearInterpolator();
}

//===================================================================================================

GeometricTransform::~GeometricTransform( )
{
   delete mpInterpolator;
}

//===================================================================================================
   
void GeometricTransform::SetInterpolatorType( InterpolatorType type )
{
   mInterpolatorType = type;
   
   delete mpInterpolator;
   switch (mInterpolatorType)
   {
      case TYPE_NEAREST_NEIGHBOR:
      {
         mpInterpolator = new NearestNeighborInterpolator();
         break;
      }
      case TYPE_BILINEAR:
      default:
      {
         mpInterpolator = new BilinearInterpolator();
      }
   }
}

//===================================================================================================

InterpolatorType GeometricTransform::GetInterpolatorType( )
{
   return mInterpolatorType;
}

//===================================================================================================

Image* GeometricTransform::Apply( Image* pImageIn )
{
   int nrbands = pImageIn->GetNumberOfBands();
   int width  = pImageIn->GetWidth();
   int height = pImageIn->GetHeight();
   
   Image* pImageOut = new Image( width, height, pImageIn->GetNumberOfBands() );
   
   for(int bandID = 0; bandID < nrbands; bandID++)
   {
      ArrayGrid< double >* pGrid = pImageIn->GetBands()[bandID];
      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x++)
         {
            common::Point<double> myPoint = GetInverseTransformedPoint( x, y );
            pImageOut->GetBands()[bandID]->SetValue( x, y, mpInterpolator->Run( pGrid, myPoint.GetX(), myPoint.GetY() ) );
         }
      }
   }
   return pImageOut;
}

//===================================================================================================

Image* GeometricTransform::ApplyInverse( Image* pImageIn )
{
   int nrbands = pImageIn->GetNumberOfBands();
   int width  = pImageIn->GetWidth();
   int height = pImageIn->GetHeight();
   
   Image* pImageOut = new Image( width, height, pImageIn->GetNumberOfBands() );
   
   for(int bandID = 0; bandID < nrbands; bandID++)
   {
      ArrayGrid< double >* pGrid = pImageIn->GetBands()[bandID];
      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x++)
         {
            common::Point<double> myPoint = GetTransformedPoint( x, y );
            pImageOut->GetBands()[bandID]->SetValue( x, y, mpInterpolator->Run( pGrid, myPoint.GetX(), myPoint.GetY() ) );
         }
      }
   }
   return pImageOut;
}

//===================================================================================================

}
}
