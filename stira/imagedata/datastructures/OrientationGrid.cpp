
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

#include "OrientationGrid.h"

#include "../../common/common/MathUtils.h"

namespace stira {
namespace imagedata {
using namespace std;
using namespace common;

OrientationGrid::OrientationGrid(int myWidth, int myHeight)
{
   mpColorTransformer = new TransformColorSpace();
   mpOrientationGrid = new ArrayGrid< LocalOrientation* >( myWidth, myHeight );
   for (int y = 0; y < myHeight; y++)
   {
      for (int x = 0; x < myWidth; x++)
      {
         LocalOrientation* pLocalOrientation = new LocalOrientation();
         mpOrientationGrid->SetValue( x, y, pLocalOrientation );
      }
   }
}

//=================================================================================

OrientationGrid::~OrientationGrid()
{
   int height = mpOrientationGrid->GetHeight();
   int width  = mpOrientationGrid->GetWidth();
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         delete mpOrientationGrid->GetValue(x, y);
      }
   }
   delete mpOrientationGrid;
   delete mpColorTransformer;
}

//=================================================================================

OrientationGrid* OrientationGrid::Clone()
{
   int height = mpOrientationGrid->GetHeight();
   int width  = mpOrientationGrid->GetWidth();
   OrientationGrid* pGrid = new OrientationGrid( width, height );
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         pGrid->SetAngle( x, y, this->GetAngle( x, y ) );
         pGrid->SetMagnitude( x, y, this->GetMagnitude( x, y ) );
      }
   }
   return pGrid;
}

//=================================================================================

int OrientationGrid::GetWidth()
{
   return mpOrientationGrid->GetWidth();
}

//=================================================================================

int OrientationGrid::GetHeight()
{
   return mpOrientationGrid->GetHeight();
}

//=================================================================================

ArrayGrid<double>* OrientationGrid::ExtractMagnitudeGrid()
{
   int width  = GetWidth();
   int height = GetHeight();
   bool needInitialisation = true;
   double initialRealValue = 0.0;

   ArrayGrid<double>* pMagnitudeGrid = new ArrayGrid<double>( width, height, needInitialisation, initialRealValue );

   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         pMagnitudeGrid->SetValue(x, y, GetMagnitude(x, y) );
      }
   }

   return pMagnitudeGrid;
}

//=================================================================================

bool OrientationGrid::GetMinMaxMagnitude( double& mmin, double& mmax )
{
   int width  = GetWidth();
   int height = GetHeight();

   mmin =  10000000;
   mmax = -10000000;

   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         double localMagnitude = GetMagnitude( x, y );
         if ( localMagnitude > mmax ) { mmax = localMagnitude; }
         if ( localMagnitude < mmin ) { mmin = localMagnitude; }
      }
   }

   return true;
}

//--------------------------------------------------------------------------------------------------------------------------

std::vector<LocalOrientation> OrientationGrid::GetOrientationVector( int xMin, int yMin, int xMax, int yMax )
{
    std::vector<LocalOrientation> vValues;
    for ( int y = yMin; y <= yMax; y++ )
    {
        for (int x = xMin; x <= xMax; x++)
        {
           vValues.push_back( *(this->GetOrientation(x, y)) );
        }
    }
    return vValues;
}

//=================================================================================

ArrayGrid<double>* OrientationGrid::ExtractOrientationGrid()
{
   int width  = GetWidth();
   int height = GetHeight();
   bool needInitialisation = true;
   double initialRealValue = 0.0;

   ArrayGrid<double>* pOrientationGrid = new ArrayGrid<double>( width, height, needInitialisation, initialRealValue );

   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         pOrientationGrid->SetValue(x, y, GetAngle(x, y) );
      }
   }

   return pOrientationGrid;
}

//=================================================================================

void OrientationGrid::SetAngle(int x, int y, double myAngle)
{
   int height = mpOrientationGrid->GetHeight();
   int width  = mpOrientationGrid->GetWidth();
   if ((x>= 0) && (x < width) && (y >= 0) && (y < height))
   {
      mpOrientationGrid->GetValue(x,y)->SetAngle(myAngle);
   }
   else
   {
      cerr << "Invalid coordinate values to set orientation" << endl << flush;
   }
}

//=================================================================================

double OrientationGrid::GetAngle(int x, int y)
{
   int height = mpOrientationGrid->GetHeight();
   int width  = mpOrientationGrid->GetWidth();
   if ((x>= 0) && (x < width) && (y >= 0) && (y < height))
   {
      return mpOrientationGrid->GetValue(x,y)->GetAngle();
   }
   else
   {
      cerr << "Invalid coordinate values to get orientation" << endl << flush;
      return -10000;
   }
}

//=================================================================================

void OrientationGrid::SetOrientation(int x, int y, LocalOrientation* myLocalOrientation)
{
    mpOrientationGrid->SetValue(x,y, myLocalOrientation);
}

//=================================================================================

LocalOrientation* OrientationGrid::GetOrientation(int x, int y)
{
    return mpOrientationGrid->GetValue(x,y);
}

//=================================================================================

void OrientationGrid::SetMagnitude(int x, int y, double myMagnitude)
{
   int height = mpOrientationGrid->GetHeight();
   int width  = mpOrientationGrid->GetWidth();
   if ((x>= 0) && (x < width) && (y >= 0) && (y < height))
   {
      mpOrientationGrid->GetValue(x,y)->SetMagnitude(myMagnitude);
   }
   else
   {
      cerr << "Invalid coordinate values to set magnitude" << endl << flush;
   }
}

//=================================================================================

double OrientationGrid::GetMagnitude(int x, int y)
{
   int height = mpOrientationGrid->GetHeight();
   int width  = mpOrientationGrid->GetWidth();
   if ((x>= 0) && (x < width) && (y >= 0) && (y < height))
   {
      return mpOrientationGrid->GetValue(x,y)->GetMagnitude();
   }
   else
   {
      cerr << "Invalid coordinate values to get magnitude" << endl << flush;
      return -1;     // error code: magnitude can't normally be negative
   }
}

//============================================================================

ColorValue OrientationGrid::ConvertAngleToHSVMap(double angle)
{
   ColorValue hsvValue;
   hsvValue.c[0] = MathUtils::ToDegrees( 2.0 * angle );
   hsvValue.c[1] = 1.0;
   hsvValue.c[2] = 1.0;
   hsvValue.type = TYPE_HSV;
   return mpColorTransformer->HSVtoRGB( hsvValue );
}

//============================================================================


ColorValue OrientationGrid::ConvertAngleToRGBMap(double angle)
{
   ColorValue rgbValue;

   if (angle > M_PI) {angle -= M_PI;}

   if ( ( angle >=  0.0) && ( angle < M_PI / 3.0))
   {
      rgbValue.c[0] = (int)( ( 255.0 - ( angle / M_PI) * 3.0 * 255.0));
      rgbValue.c[1] = (int)(   0.0 );
      rgbValue.c[2] = (int)( (( angle / M_PI) * 3.0 * 255.0));
   }
   if ( ( angle >= M_PI / 3.0) && ( angle <= 2.0 * M_PI / 3.0))
   {
      rgbValue.c[0] = (int)( ( 0.0));
      rgbValue.c[1] = (int)( (( angle - M_PI / 3.0) / M_PI) * 3.0 * 255.0 );
      rgbValue.c[2] = (int)( (255.0 - (( angle - M_PI / 3.0) / M_PI) * 3.0 * 255.0));
   }
   if ( ( angle >=  2.0 * M_PI / 3.0) && ( angle <= M_PI))
   {
      rgbValue.c[0] = (int)( (( angle - 2.0 * M_PI / 3.0) / M_PI) * 3.0 * 255.0);
      rgbValue.c[1] = (int)( (255.0 - (( angle - 2.0 * M_PI / 3.0) / M_PI) * 3.0 * 255.0));
      rgbValue.c[2] = (int)( 0.0 );
   }

   return rgbValue;
}

//============================================================================

Image* OrientationGrid::VisualizeMagnitudeImage( )
{
   double tmpMagnitude, mmax, mmin, ttmp;

   int width  = GetWidth();
   int height = GetHeight();

   Image *pMagnitudeImage;

   pMagnitudeImage = new Image( width, height, 3 );

   pMagnitudeImage->SetImageName( std::string("MagnitudeImage") );

   mmax = -100000000000.0;
   mmin =  100000000000.0;
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         if ( GetMagnitude(x, y) > mmax) {mmax = GetMagnitude(x, y);}
         if ( GetMagnitude(x, y) < mmin) {mmin = GetMagnitude(x, y);}
      }
   }

   //cout << "Exporting magnitude image " << endl << flush;
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         tmpMagnitude = GetMagnitude(x, y);

         ttmp = 255.0 * (tmpMagnitude - mmin) / (mmax - mmin);
         if (ttmp > 255.0) {ttmp = 255.0;}
         if (ttmp <   0.0) {ttmp =   0.0;}

         pMagnitudeImage->GetBands()[0]->SetValue(x, y, ttmp);
         pMagnitudeImage->GetBands()[1]->SetValue(x, y, ttmp);
         pMagnitudeImage->GetBands()[2]->SetValue(x, y, ttmp);
      }
   }
   return pMagnitudeImage;
}

//============================================================================

Image* OrientationGrid::VisualizeOrientationImage( double threshold, ColorExportMode myMode )
{
   int width  = GetWidth();
   int height = GetHeight();

   Image *pOrientationImage = new Image( width, height, 3);
   pOrientationImage->SetImageName( std::string("OrientationImage") );

   //cout << "Exporting orientation image with threshold " << threshold << endl << flush;
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         if ( GetMagnitude(x, y) > threshold)
         {
            ColorValue rgbColor;
            if (myMode == EXPORT_RGB_MODE)
            {
               rgbColor = ConvertAngleToRGBMap( GetAngle(x, y) );
            }
            else
            {
               rgbColor = ConvertAngleToHSVMap( GetAngle(x, y) );
            }
            pOrientationImage->GetBands()[0]->SetValue(x, y, rgbColor.c[0] );
            pOrientationImage->GetBands()[1]->SetValue(x, y, rgbColor.c[1] );
            pOrientationImage->GetBands()[2]->SetValue(x, y, rgbColor.c[2] );
         }
         else
         {
            pOrientationImage->GetBands()[0]->SetValue(x, y, 0.0);
            pOrientationImage->GetBands()[1]->SetValue(x, y, 0.0);
            pOrientationImage->GetBands()[2]->SetValue(x, y, 0.0);
         }
      }
   }
   return pOrientationImage;
}

//============================================================================

}
}
