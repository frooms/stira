
/***********************************************************************************
 *   Copyright (C) 2009 by Filip Rooms                                             *
 *                                                                                 *
 *  Terms and conditions for using this software in any form are provided in the   *
 *  file COPYING, which can be found in the root directory of this project.        *
 *                                                                                 *
 *   Contact data: filip.rooms@gmail.com                                           *
 *                 http://www.filiprooms.be/                                       *
 *                                                                                 *
 ***********************************************************************************/

#include <iostream>
#include "ChromaticAdaptation.h"

namespace stira {
namespace image {

ChromaticAdaptation::ChromaticAdaptation( ColorValue sourceReferenceWhite, ColorValue destinationReferenceWhite, ChromaticAdaptationType myType )
{
   mType = myType;
   
   mSourceReferenceWhite      = sourceReferenceWhite;
   mDestinationReferenceWhite = destinationReferenceWhite;
   InitializeTransformMatrices( );
}

//------------------------------------------------------------------------

ChromaticAdaptation::~ChromaticAdaptation()
{
}

void ChromaticAdaptation::ChangeSourceWhite( ColorValue sourceReferenceWhite )
{
   mSourceReferenceWhite      = sourceReferenceWhite;
}

void ChromaticAdaptation::ChangeDestinationWhite( ColorValue destinationReferenceWhite )
{
   mDestinationReferenceWhite = destinationReferenceWhite;
}

void ChromaticAdaptation::ChangeAdaptationType( ChromaticAdaptationType myType )
{
   mType = myType;
   InitializeTransformMatrices( );
}

//------------------------------------------------------------------------

void ChromaticAdaptation::InitializeTransformMatrices( )
{
   for(int j = 0; j < 3; j++)
   {
      for(int i = 0; i < 3; i++)
      {
         mTransformMatrix[i][j] = .0;
         mppTmpMatrix[i][j] = .0;
      }
   }
   switch (mType)
   {
      case CHROMATICADAPTATION_BRADFORD:
      {
         for(int j = 0; j < 3; j++)
         {
            for(int i = 0; i < 3; i++) 
            {
               mppForwardMatrix[i][j] = sBradfordForwardMatrix[i][j];
               mppInverseMatrix[i][j] = sBradfordInverseMatrix[i][j];
            }
         }
         break;
      }
      case CHROMATICADAPTATION_VONKRIES:
      {
         for(int j = 0; j < 3; j++)
         {
            for(int i = 0; i < 3; i++) 
            {
               mppForwardMatrix[i][j] = sVonKriesForwardMatrix[i][j];
               mppInverseMatrix[i][j] = sVonKriesInverseMatrix[i][j];
            }
         }
         break;
      }
      case CHROMATICADAPTATION_SHARP:
      {
         for(int j = 0; j < 3; j++)
         {
            for(int i = 0; i < 3; i++) 
            {
               mppForwardMatrix[i][j] = sSharpForwardMatrix[i][j];
               mppInverseMatrix[i][j] = sSharpInverseMatrix[i][j];
            }
         }
         break;
      }
      case CHROMATICADAPTATION_CMC2000:
      {
         for(int j = 0; j < 3; j++)
         {
            for(int i = 0; i < 3; i++) 
            {
               mppForwardMatrix[i][j] = sCMC200ForwardMatrix[i][j];
               mppInverseMatrix[i][j] = sCMC200InverseMatrix[i][j];
            }
         }
         break;
      }
      case CHROMATICADAPTATION_XYZSCALING:
      default:
      {
         for(int j = 0; j < 3; j++)
         {
            for(int i = 0; i < 3; i++) 
            {
               mppForwardMatrix[i][j] = mppInverseMatrix[i][j] = sUnityMatrix[i][j];
            }
         }
         break;
      }
   }

   mTransformedSourceReferenceWhite      = TransformColor( mSourceReferenceWhite );
   mTransformedDestinationReferenceWhite = TransformColor( mDestinationReferenceWhite );
   
   mRatiotransformedReferenceWhite = mTransformedDestinationReferenceWhite / mTransformedSourceReferenceWhite;
   
   // multiplication of diagonal matrix with MA^-1
   for(int i = 0; i < 3; i++)
   {
      for(int j = 0; j < 3; j++)
      {
         mppTmpMatrix[i][j] = mppInverseMatrix[i][j] * mRatiotransformedReferenceWhite.c[i];
      }
   }
   
   // multiplication of resulting matrix with MA
   for(int i = 0; i < 3; i++)
   {
      for(int j = 0; j < 3; j++)
      {
         mTransformMatrix[i][j] = 0.0;
         for(int k = 0; k < 3; k++) 
         {
            mTransformMatrix[i][j] += mppForwardMatrix[i][k] * mppTmpMatrix[k][j];
         }
      }
   }
}

//------------------------------------------------------------------------

ColorValue ChromaticAdaptation::TransformColor( ColorValue inValue )
{
   ColorValue outValue;
   for(int i = 0; i < 3; i++)
   {
      outValue.c[i] = 0.0;
      for(int j = 0; j < 3; j++)
      {
         outValue.c[i] += mppForwardMatrix[j][i] * inValue.c[j];
      }
   }
   return outValue;
}

//------------------------------------------------------------------------

ColorValue ChromaticAdaptation::AdaptXYZColor( ColorValue inValue )
{
   ColorValue outValue;
   for(int i = 0; i < 3; i++)
   {
      outValue.c[i] = 0.0;
      for(int j = 0; j < 3; j++)
      {
         outValue.c[i] += mTransformMatrix[j][i] * inValue.c[j];
      }
   }
   outValue.type = TYPE_XYZ;
   return outValue;
}

//------------------------------------------------------------------------

ColorValue ChromaticAdaptation::AdaptsRGBColor( ColorValue inValue )
{
   TransformColorSpace tcSource;
   TransformColorSpace tcDestination;
   
   tcSource.SetReferenceWhite( mSourceReferenceWhite );
   tcDestination.SetReferenceWhite( mDestinationReferenceWhite );
   
   ColorValue inXyzValue = tcSource.sRGBtoXYZ( inValue );
   ColorValue outXyzValue = AdaptXYZColor( inXyzValue );
   return tcDestination.XYZtosRGB( outXyzValue );
}

//------------------------------------------------------------------------

ColorValue ChromaticAdaptation::AdaptLabColor( ColorValue inValue )
{
   TransformColorSpace tc;
   
   tc.SetReferenceWhite( ColorConstants::sD50_XYZ );
   
   ColorValue inXyzValue = tc.LabtoXYZ( inValue );
   ColorValue outXyzValue = AdaptXYZColor( inXyzValue );
   return tc.XYZtoLab( outXyzValue );
}

//------------------------------------------------------------------------

bool ChromaticAdaptation::ChromaticAdapt( Image* pImage )
{
   int nrBands = pImage->GetNumberOfBands();
   if (nrBands == 3)
   {
      int width = pImage->GetWidth();
      int height = pImage->GetHeight();

      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x++)
         {
            pImage->SetColor( x, y, this->AdaptsRGBColor( pImage->GetColor( x, y) ) );
         }
      }
      return true;
   }
   else
   {
      std::cerr << "Impossible to applu chromatic adaptation on an image with " << nrBands << " band(s)." << std::endl << std::flush;
      return false;
   }
}

}
}

