
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

#include "TransformColorSpace.h"
#include "../../common/common/MathUtils.h"
#define ONETHIRD  (1.0 / 3.0)
#include <cassert>

namespace stira {
namespace image {

using namespace std;
using namespace common;
using std::showpoint;

const double TransformColorSpace::sDifferenceThreshold = 0.00000000001;

//----------------------------------------------------------

TransformColorSpace::TransformColorSpace()
{
   mReferenceWhite = ColorConstants::sD65_XYZ;
   mMaxColorValue = 255.0;
}

//----------------------------------------------------------

TransformColorSpace::~TransformColorSpace()
{
}

//----------------------------------------------------------

void TransformColorSpace::SetMaxColorValue(double maxColorValue)
{
   mMaxColorValue = maxColorValue;
}

//----------------------------------------------------------

void TransformColorSpace::SetReferenceWhite( ColorValue newWhite )
{
   mReferenceWhite = newWhite;
}

//----------------------------------------------------------

ColorValue TransformColorSpace::GetReferenceWhite( )
{
   return mReferenceWhite;
}

//----------------------------------------------------------

double TransformColorSpace::sRGBLargeToSmall(double inLarge)
{
   if (inLarge < 0.04045)
   {
      return (inLarge / 12.92);
   }
   else
   {
      return ( pow(((inLarge + 0.055) / 1.055), 2.4) );
   }
}

//----------------------------------------------------------

double TransformColorSpace::sRGBSmallToLarge(double inSmall )
{
   if (inSmall < 0.0031308)
   {
      return (inSmall * 12.92);
   }
   else
   {
      return ( ( 1.055 * pow(inSmall, (1.0 / 2.4) ) ) - 0.055 );
   }
}

//----------------------------------------------------------

ColorValue TransformColorSpace::sRGBtoXYZ(ColorValue rgbValue)
{
   //ColorValue normalizedColor = DivideComponents( rgbValue, sMaxColorValue );
   ColorValue normalizedColor = rgbValue / mMaxColorValue;
   double r = sRGBLargeToSmall( normalizedColor.c[0] );
   double g = sRGBLargeToSmall( normalizedColor.c[1] );
   double b = sRGBLargeToSmall( normalizedColor.c[2] );
   ColorValue xyzValue;
   
   xyzValue.c[0] = 0.4124240 * r + 0.357579 * g + 0.1804640 * b;
   xyzValue.c[1] = 0.2126560 * r + 0.715158 * g + 0.0721856 * b;
   xyzValue.c[2] = 0.0193324 * r + 0.119193 * g + 0.9504440 * b;
   xyzValue.type = TYPE_XYZ;
   return xyzValue;
}

//----------------------------------------------------------

ColorValue TransformColorSpace::XYZtosRGB(ColorValue xyzValue)
{
   ColorValue rgbValue;
   
   double r =  3.2407100 * xyzValue.c[0] - 1.53726  * xyzValue.c[1] - 0.498571  * xyzValue.c[2];
   double g = -0.9692580 * xyzValue.c[0] + 1.87599  * xyzValue.c[1] + 0.0415557 * xyzValue.c[2];
   double b =  0.0556352 * xyzValue.c[0] - 0.203996 * xyzValue.c[1] + 1.05707   * xyzValue.c[2];
   
   rgbValue.c[0] = mMaxColorValue * sRGBSmallToLarge( r );
   rgbValue.c[1] = mMaxColorValue * sRGBSmallToLarge( g );
   rgbValue.c[2] = mMaxColorValue * sRGBSmallToLarge( b );
   rgbValue.type = TYPE_RGB;
   return rgbValue;
}

//----------------------------------------------------------

ColorValue TransformColorSpace::AdobeRGBtoXYZ(ColorValue rgbValue)
{
   double gamma = 2.2;
   //ColorValue normalizedColor = DivideComponents( rgbValue, sMaxColorValue );
   ColorValue normalizedColor = rgbValue / mMaxColorValue;
   double r = pow( normalizedColor.c[0], gamma );
   double g = pow( normalizedColor.c[1], gamma );
   double b = pow( normalizedColor.c[2], gamma );
   ColorValue xyzValue;
   
   xyzValue.c[0] = MathUtils::ClipValue( (0.5767000 * r + 0.1855560 * g + 0.1882120 * b), 0.0, 1.0);
   xyzValue.c[1] = MathUtils::ClipValue( (0.2973610 * r + 0.6273550 * g + 0.0752847 * b), 0.0, 1.0);
   xyzValue.c[2] = MathUtils::ClipValue( (0.0270328 * r + 0.0706879 * g + 0.9912480 * b), 0.0, 1.0);
   xyzValue.type = TYPE_XYZ;
   return xyzValue;
}

//----------------------------------------------------------

ColorValue TransformColorSpace::XYZtoAdobeRGB(ColorValue xyzValue)
{
   double gamma = (1.0 / 2.2);
   ColorValue rgbValue;
   
   // clipping due to fact that pow(x, gamma) is nan when x < 0; results in max square error of 
   double r = MathUtils::ClipValue( ( 2.0414800 * xyzValue.c[0] - 0.564977 * xyzValue.c[1] - 0.3447130 * xyzValue.c[2]), 0.0, 1.0);
   double g = MathUtils::ClipValue( (-0.9692580 * xyzValue.c[0] + 1.875990 * xyzValue.c[1] + 0.0415557 * xyzValue.c[2]), 0.0, 1.0);
   double b = MathUtils::ClipValue( ( 0.0134455 * xyzValue.c[0] - 0.118373 * xyzValue.c[1] + 1.0152700 * xyzValue.c[2]), 0.0, 1.0);
   
   rgbValue.c[0] = mMaxColorValue * pow( r, gamma );
   rgbValue.c[1] = mMaxColorValue * pow( g, gamma );
   rgbValue.c[2] = mMaxColorValue * pow( b, gamma );
   rgbValue.type = TYPE_RGB;
   return rgbValue;
}

//----------------------------------------------------------

ColorValue TransformColorSpace::sRGBtoLuv(ColorValue rgbValue )
{
   return XYZtoLuv( sRGBtoXYZ( rgbValue ) );
}

//----------------------------------------------------------

ColorValue TransformColorSpace::LuvtosRGB(ColorValue luvValue )
{
   return XYZtosRGB( LuvtoXYZ( luvValue ) );
}

//----------------------------------------------------------

ColorValue TransformColorSpace::XYZtoLuv(ColorValue xyzValue )
{
   double X = xyzValue.c[0];
   double Y = xyzValue.c[1];
   double Z = xyzValue.c[2];
   
   double Xr = mReferenceWhite.c[0];
   double Yr = mReferenceWhite.c[1];
   double Zr = mReferenceWhite.c[2];
   
   double yr = Y / Yr;
   
   double udash, vdash;
   double denominator = (X + 15.0 * Y + 3.0 * Z);
   
   if (denominator < sDifferenceThreshold)
   {
      udash = 0.0; vdash = 0.0;
   }
   else
   {
      udash = (4.0 * X) / (X + 15.0 * Y + 3.0 * Z);
      vdash = (9.0 * Y) / (X + 15.0 * Y + 3.0 * Z);
   }
   
   double urdash = (4.0 * Xr) / (Xr + 15.0 * Yr + 3.0 * Zr);
   double vrdash = (9.0 * Yr) / (Xr + 15.0 * Yr + 3.0 * Zr);
   
   ColorValue luvValue;
   if (yr > ColorConstants::sEpsilon) 
   {
      luvValue.c[0] = 116.0 * pow(yr, (1.0 / 3.0))  - 16.0;
   }
   else
   {
      luvValue.c[0] = ColorConstants::sKappa * yr;
   }
   luvValue.c[1] = 13.0 * luvValue.c[0] * (udash - urdash);
   luvValue.c[2] = 13.0 * luvValue.c[0] * (vdash - vrdash);
   luvValue.type = TYPE_LUV;
   return luvValue;
}

//----------------------------------------------------------

ColorValue TransformColorSpace::LuvtoXYZ(ColorValue luvValue )
{
   ColorValue xyzValue;
   double L = luvValue.c[0];
   double u = luvValue.c[1];
   double v = luvValue.c[2];
   
   double Xr = mReferenceWhite.c[0];
   double Yr = mReferenceWhite.c[1];
   double Zr = mReferenceWhite.c[2];
   
   double u0 = (4.0 * Xr) / (Xr + 15.0 * Yr + 3.0 * Zr);
   double v0 = (9.0 * Yr) / (Xr + 15.0 * Yr + 3.0 * Zr);
   
   if (L > ( ColorConstants::sKappa * ColorConstants::sEpsilon) )
   {
      xyzValue.c[1] = pow( ((L + 16.0) / 116.0), 3.0);
   }
   else
   {
      xyzValue.c[1] = L / ColorConstants::sKappa;
   }
   
   double a, b, c, d;
   
   if ( fabs(u + 13.0 * L * u0) < sDifferenceThreshold)
   {
      a = 0.0;
   }
   else
   {
      a = ((52.0 * L / (u + 13.0 * L * u0)) - 1.0) / 3.0;
   }
   
   b = -5.0 * xyzValue.c[1];
   c = -1.0 / 3.0;
   
   if ( fabs(v + 13.0 * L * v0) < sDifferenceThreshold)
   {
      d = 0.0;
   }
   else
   {
      d = xyzValue.c[1] * ( ((39.0 * L) / (v + 13.0 * L * v0)) - 5.0);
   }
   
   if (a != c)
   {
      xyzValue.c[0] = (d-b) / (a-c);
   }
   else
   {
      xyzValue.c[0] = 0.0;
   }
   
   xyzValue.c[2] = xyzValue.c[0] * a + b;
   xyzValue.type = TYPE_XYZ;
   return xyzValue;
}

//----------------------------------------------------------

ColorValue TransformColorSpace::sRGBtoLab(ColorValue rgbValue )
{
   return XYZtoLab( sRGBtoXYZ( rgbValue ) );
}

//----------------------------------------------------------

ColorValue TransformColorSpace::LabtosRGB(ColorValue labValue )
{
   return XYZtosRGB( LabtoXYZ( labValue ) );
}
   
//----------------------------------------------------------

ColorValue TransformColorSpace::AdobeRGBtoLab(ColorValue rgbValue )
{
   return XYZtoLab( AdobeRGBtoXYZ( rgbValue ) );
}

//----------------------------------------------------------

ColorValue TransformColorSpace::LabtoAdobeRGB(ColorValue labValue )
{
   return XYZtoAdobeRGB( LabtoXYZ( labValue ) );
}

//----------------------------------------------------------

ColorValue TransformColorSpace::XYZtoLab( ColorValue xyzValue )
{
   double X = xyzValue.c[0];
   double Y = xyzValue.c[1];
   double Z = xyzValue.c[2];
   
   double Xr = mReferenceWhite.c[0];
   double Yr = mReferenceWhite.c[1];
   double Zr = mReferenceWhite.c[2];
   
   double xr = X / Xr;
   double yr = Y / Yr;
   double zr = Z / Zr;
   
   double oneThird = 1.0 / 3.0;
   double fx, fy, fz;
   double mySign;
   if ( xr > ColorConstants::sEpsilon )
   {
      mySign = xr / fabs( xr );
      fx = mySign * pow( fabs( xr ), oneThird );
   }
   else
   {
      fx = ( ColorConstants::sKappa * xr  + 16.0 ) / 116.0;
   }
   
   if ( yr > ColorConstants::sEpsilon )
   {
      mySign = yr / fabs(yr);
      fy = mySign * pow( fabs( yr ), oneThird);
   }
   else
   {
      fy = ( ColorConstants::sKappa * yr  + 16.0 ) / 116.0;
   }
   
   if ( zr > ColorConstants::sEpsilon )
   {
      mySign = zr / fabs( zr );
      fz = mySign * pow( fabs( zr ), oneThird );
   }
   else
   {
      fz = ( ColorConstants::sKappa * zr  + 16.0 ) / 116.0;
   }
   
   ColorValue LabValue;
   LabValue.c[0] = 116.0 *   fy - 16.0;
   LabValue.c[1] = 500.0 * ( fx - fy );
   LabValue.c[2] = 200.0 * ( fy - fz );
   LabValue.type = TYPE_LAB;
   return LabValue;
}

//----------------------------------------------------------

ColorValue TransformColorSpace::LabtoXYZ(ColorValue labValue )
{
   double L = labValue.c[0];
   double a = labValue.c[1];
   double b = labValue.c[2];
   
   double fy = (L + 16.0) / 116.0;
   double fx = (a / 500.0) + fy;
   double fz = fy - (b / 200.0);
   
   double xr, yr, zr;
   
   double fx3 = fx * fx * fx;
   double fy3 = fy * fy * fy;
   double fz3 = fz * fz * fz;
   
   if ( fx3 > ColorConstants::sEpsilon )
   {
      xr = fx3;
   }
   else
   {
      xr = (116.0 * fx - 16.0) / ColorConstants::sKappa;
   }
   
   if ( L > ( ColorConstants::sKappa * ColorConstants::sEpsilon) )
   {
      yr = fy3;
   }
   else
   {
      yr = L / ColorConstants::sKappa;
   }
   
   if ( fz3 > ColorConstants::sEpsilon )
   {
      zr = fz3;
   }
   else
   {
      zr = (116.0 * fz - 16.0) / ColorConstants::sKappa;
   }

   double Xr = mReferenceWhite.c[0];
   double Yr = mReferenceWhite.c[1];
   double Zr = mReferenceWhite.c[2];
   
   ColorValue xyzValue;
   
   xyzValue.c[0] = xr * Xr;
   xyzValue.c[1] = yr * Yr;
   xyzValue.c[2] = zr * Zr;
   xyzValue.type = TYPE_XYZ;
   
   return xyzValue;
}

//----------------------------------------------------------

ColorValue TransformColorSpace::RGBtoCMY(ColorValue rgbValue)
{
   ColorValue cmyValue;
   
   cmyValue.c[0] = mMaxColorValue - rgbValue.c[0];
   cmyValue.c[1] = mMaxColorValue - rgbValue.c[1];
   cmyValue.c[2] = mMaxColorValue - rgbValue.c[2];
   cmyValue.type = TYPE_CMY;
   return cmyValue;
}

//----------------------------------------------------------

ColorValue TransformColorSpace::CMYtoRGB(ColorValue cmyValue)
{
   ColorValue rgbValue;
   
   rgbValue.c[0] = mMaxColorValue - cmyValue.c[0];
   rgbValue.c[1] = mMaxColorValue - cmyValue.c[1];
   rgbValue.c[2] = mMaxColorValue - cmyValue.c[2];
   rgbValue.type = TYPE_RGB;
   return rgbValue;
}

//----------------------------------------------------------

ColorValue TransformColorSpace::RGBtoYUV(ColorValue rgbValue)
{
   ColorValue yuvValue;
   
   yuvValue.c[0] =  0.299 * rgbValue.c[0] + 0.587 * rgbValue.c[1] + 0.114 * rgbValue.c[2];
   yuvValue.c[1] = -0.147 * rgbValue.c[0] - 0.289 * rgbValue.c[1] + 0.436 * rgbValue.c[2];
   yuvValue.c[2] =  0.615 * rgbValue.c[0] - 0.515 * rgbValue.c[1] - 0.100 * rgbValue.c[2];
   yuvValue.type = TYPE_YUV;
   return yuvValue;
}

//----------------------------------------------------------

ColorValue TransformColorSpace::YUVtoRGB(ColorValue yuvValue)
{
   ColorValue rgbValue;
   
   rgbValue.c[0] = yuvValue.c[0] + 0.000 * yuvValue.c[1] + 1.140 * yuvValue.c[2];
   rgbValue.c[1] = yuvValue.c[0] - 0.396 * yuvValue.c[1] - 0.584 * yuvValue.c[2];
   rgbValue.c[2] = yuvValue.c[0] + 2.029 * yuvValue.c[1] + 0.000 * yuvValue.c[2];
   
   rgbValue.type = TYPE_RGB;
   return rgbValue;
}

//----------------------------------------------------------

ColorValue TransformColorSpace::RGBtoHSV(ColorValue rgbValue)
{
   ColorValue hsvValue;
   
   double H, S, V;
   
   double R = rgbValue.c[0] / mMaxColorValue;
   double G = rgbValue.c[1] / mMaxColorValue;
   double B = rgbValue.c[2] / mMaxColorValue;
   
   double myMinimum = rgbValue.GetMin() / mMaxColorValue;
   double myMaximum = rgbValue.GetMax() / mMaxColorValue;
   
   double myMaximumMinusMinimum = (myMaximum - myMinimum);
   
   V = myMaximum;
   
   if (myMaximum > sDifferenceThreshold)
   {
      S = myMaximumMinusMinimum / myMaximum;
   }
   else
   {
      S = 0.0;
   }
   
   if (myMaximumMinusMinimum < sDifferenceThreshold)
   { // grey values
      H = 0.0;
      S = 0.0;
   }
   else
   {
      if ( R == myMaximum )
      {
         H = (0.0 + ( G - B ) / myMaximumMinusMinimum) * 60.0;
      }
      else if (G == myMaximum )
      {
         H = (2.0 + ( B - R ) / myMaximumMinusMinimum) * 60.0;;
      }
      else // B is maximum
      {
         H = (4.0 + ( R - G ) / myMaximumMinusMinimum) * 60.0;
      }

      while (H < 0.0)
      {
         H += 360.0;
      }
      while (H > 360.0)
      {
         H -= 360.0;
      }
   }
   hsvValue.c[0] = H;
   hsvValue.c[1] = S;
   hsvValue.c[2] = V;
   
   hsvValue.type = TYPE_HSV;
   return hsvValue;
}

//----------------------------------------------------------

ColorValue TransformColorSpace::HSVtoRGB(ColorValue hsvValue)
{
   ColorValue rgbValue;
   
   double H = hsvValue.c[0];
   double S = hsvValue.c[1];
   double V = hsvValue.c[2];
   
   int hexDivision = (int)(H / 60.0);
   int primaryColor = (int)( hexDivision ) % 6;
   double secondaryColor = (H / 60.0) - (double)(hexDivision);
   
   double p = V * (1.0 - S);
   double q = V * (1.0 - (S * secondaryColor));
   double t = V * (1.0 - (S * (1.0 - secondaryColor)));
   
   double R, G, B;
   //if (primaryColor > 5) {primaryColor = 0;} // H == 360 degrees, is same as 0 degrees
   switch (primaryColor)
   {
      case 0:
      {
         R = V;
         G = t;
         B = p;
         break;
      }
      case 1:
      {
         R = q;
         G = V;
         B = p;
         break;
      }
      case 2:
      {
         R = p;
         G = V;
         B = t;
         break;
      }
      
      case 3:
      {
         R = p;
         G = q;
         B = V;
         break;
      }
      
      case 4:
      {
         R = t;
         G = p;
         B = V;
         break;
      }
      
      case 5:
      {
         R = V;
         G = p;
         B = q;
         break;
      }
      default:
      {
         cout << "Primary colour is not in [0, 5]: " << primaryColor << endl << flush;
         R = 0.0;
         G = 0.0;
         B = 0.0;
         break;
      }
   }
   
   rgbValue.c[0] = R * mMaxColorValue;
   rgbValue.c[1] = G * mMaxColorValue;
   rgbValue.c[2] = B * mMaxColorValue;

   rgbValue.type = TYPE_RGB;
   return rgbValue;
}

//----------------------------------------------------------

ColorValue TransformColorSpace::RGBtoHSI(ColorValue rgbValue)
{
   ColorValue hsiValue;
   
   double R = rgbValue.c[0] / mMaxColorValue;
   double G = rgbValue.c[1] / mMaxColorValue;
   double B = rgbValue.c[2] / mMaxColorValue;
   
   double H, S, I;
   
   double minValue = rgbValue.GetMin( ) / mMaxColorValue;
   
   double numerator = 0.5 * ((R-G) + (R - B));
   double denominator = sqrt( (R-G)*(R-G) + (R-B)*(G-B) );
   double theta = acos( numerator / (denominator + sDifferenceThreshold) );
   
   H = theta;
   if (B > G) {H = 2.0 * M_PI - H;}  // v1 in [0, 2*pi]
   H /= (2.0 * M_PI);
   
   numerator = minValue;
   denominator = (R + G + B);
   if (denominator < sDifferenceThreshold) {denominator = sDifferenceThreshold;}
   S = 1.0 - 3.0 * numerator / denominator;
   
   hsiValue.type = TYPE_HSI;
   I = (R + G + B) / 3.0;
   
   hsiValue.c[0] = H;
   hsiValue.c[1] = S;
   hsiValue.c[2] = I;
   hsiValue.type = TYPE_HSI;
   return hsiValue;
}

//----------------------------------------------------------

ColorValue TransformColorSpace::HSItoRGB(ColorValue hsiValue)
{
   ColorValue rgbValue;
   
   double R, G, B;
   
   double H = hsiValue.c[0] * 2.0 * M_PI;
   double S = hsiValue.c[1];
   double I = hsiValue.c[2];
   
   if ( (H >= 0.0) && (H < (2.0 * M_PI / 3.0) ) )
   {
      B = (1.0 - S) * I;
      R = I * (1.0 + ( (S * cos(H) ) / (cos (M_PI / 3.0 - H) )) );
      G = 3.0 * I - (B + R);
   }
   else
   {
      if ( (H >= 2.0 * M_PI / 3.0) && (H < 4.0 * M_PI / 3.0))
      {
         H -= (2.0 * M_PI / 3.0);
         R = I * (1.0 - S);
         G = I * (1.0 + ( (S * cos(H) ) / (cos(M_PI / 3.0 - H) ) ) );
         B = 3.0 * I - (R + G);
      }
      else 
      {
         if ( (H >= 4.0 * M_PI / 3.0) && (H <= 2.0 * M_PI))
         {
            H -= (4.0 * M_PI / 3.0);
            G = I * (1.0 - S);
            B = I * (1.0 + ( (S * cos(H) ) / (cos(M_PI / 3.0 - H) )) );
            R = 3.0 * I - (G + B);
         }
         else
         {
            G = 0.0;
            B = 0.0;
            R = 0.0;
            cerr << "Invalid value "<< H << " for H!!! Aborting..." << endl << flush;
         }
      }
   }
   
   rgbValue.c[0] = R * mMaxColorValue;
   rgbValue.c[1] = G * mMaxColorValue;
   rgbValue.c[2] = B * mMaxColorValue;
   
   rgbValue.type = TYPE_RGB;
   return rgbValue;
}

//----------------------------------------------------------


double TransformColorSpace::RGBToGray(ColorValue rgbValue)
{
   return ( 0.2125 * rgbValue.c[0] + 0.7154 * rgbValue.c[1] + 0.0721 * rgbValue.c[2] );
}

//----------------------------------------------------------

ColorValue TransformColorSpace::RGBToSepia(ColorValue rgbValue)
{
   ColorValue sepiaValue;
   double Rold = rgbValue.c[0];
   double Gold = rgbValue.c[1];
   double Bold = rgbValue.c[2];
   
   sepiaValue.c[0] = ((0.393 * Rold) + (0.769 * Gold) + (0.189 * Bold));
   sepiaValue.c[1] = ((0.349 * Rold) + (0.686 * Gold) + (0.168 * Bold));
   sepiaValue.c[2] = ((0.272 * Rold) + (0.534 * Gold) + (0.131 * Bold));
   sepiaValue.type = TYPE_RGB;
   return sepiaValue;
}

//----------------------------------------------------------

ColorValue TransformColorSpace::RGBToSepia2(ColorValue rgbValue)
{
   double grayValue = RGBToGray( rgbValue );
   return RGBToSepia2( grayValue );
}

//----------------------------------------------------------

ColorValue TransformColorSpace::RGBToSepia2( double grayValue )
{
   ColorValue sepiaValue;
   if (grayValue < 60.0)
   {
      sepiaValue.c[0] = 0.9 * grayValue;
      sepiaValue.c[1] = 0.9 * grayValue;
      sepiaValue.c[2] = 0.9 * grayValue;
   }
   else if (grayValue < 190.0)
   {
      sepiaValue.c[0] = grayValue;
      sepiaValue.c[1] = grayValue;
      sepiaValue.c[2] = 0.8 * grayValue;
   }
   else
   {
      sepiaValue.c[0] = grayValue;
      sepiaValue.c[1] = grayValue;
      sepiaValue.c[2] = 0.9 * grayValue;
   }
   sepiaValue.type = TYPE_RGB;
   return sepiaValue;
}

//----------------------------------------------------------

double TransformColorSpace::DeltaE1976( ColorValue lab1, ColorValue lab2 )
{
   double dv1 = lab1.c[0] - lab2.c[0];
   double dv2 = lab1.c[1] - lab2.c[1];
   double dv3 = lab1.c[2] - lab2.c[2];
   return sqrt( dv1 * dv1 + dv2 * dv2 + dv3 * dv3 );
}

//----------------------------------------------------------

ColorValue TransformColorSpace::LabtoLCH( ColorValue labValue )
{
   ColorValue lchValue;
   lchValue.c[0] = labValue.c[0];
   lchValue.c[1] = sqrt( labValue.c[1] * labValue.c[1] +  labValue.c[2] * labValue.c[2] );
   lchValue.c[2] = MathUtils::ApplyModulo( MathUtils::ToDegrees( atan2( labValue.c[2], labValue.c[1] ) ), 360.0);
   
   return lchValue;
}

//----------------------------------------------------------

ColorValue TransformColorSpace::LCHtoLab( ColorValue lchValue )
{
   ColorValue labValue;
   labValue.c[0] = lchValue.c[0];
   
   double Hradians = MathUtils::ToRadians( labValue.c[2] );
   labValue.c[1] = labValue.c[1] * cos( Hradians );
   labValue.c[2] = labValue.c[1] * sin( Hradians );
   
   return labValue;
}

//----------------------------------------------------------

double TransformColorSpace::DeltaE1994( ColorValue lab1, ColorValue lab2 )
{
   double dL = lab1.c[0] - lab2.c[0]; //Delta L*
   double da = lab1.c[1] - lab2.c[1]; //Delta a*
   double db = lab1.c[2] - lab2.c[2]; //Delta b*

   double C1 = sqrt( lab1.c[1] * lab1.c[1] + lab1.c[2] * lab1.c[2] );
   double C2 = sqrt( lab2.c[1] * lab2.c[1] + lab2.c[2] * lab2.c[2] );
   
   double dC = C1 - C2; //Delta C*
   double dH = sqrt( da * da + db * db - dC * dC ); //Delta H*

   /* Constants are for graphic arts (not textiles) */
   double K1 = 0.045;
   double K2 = 0.015;
   double KL = 1.0;
   double KC = 1.0;
   double KH = 1.0;
   double SL = 1.0;
   double SC = 1.0 + K1 * C1; 
   double SH = 1.0 + K2 * C1;

   double d1 = dL / ( KL * SL );
   double d2 = dC / ( KC * SC );
   double d3 = dH / ( KH * SH );

   return sqrt( d1 * d1 + d2 * d2 + d3 * d3 );
}

//----------------------------------------------------------

double TransformColorSpace::DeltaE2000( ColorValue lab1, ColorValue lab2 )
{
   double Hbarprime, T, dhprime, SL, SC, SH, KL, KC, KH, dtheta, RC, RT;
   ColorValue  dLCHprime;

   KL = 1.; KC = 1.; KH = 1.;
   double Lbarprime = ( lab1.c[0] + lab2.c[0] ) / 2.0;
   double C1 = sqrt( ( lab1.c[1] * lab1.c[1] ) + ( lab1.c[2] * lab1.c[2] ) );
   double C2 = sqrt( ( lab2.c[1] * lab2.c[1] ) + ( lab2.c[2] * lab2.c[2] ) );
   double Cbar = ( C1 + C2 ) / 2.0;
   double G = ( 1.0 - sqrt( pow( Cbar, 7.0 ) / ( pow( Cbar, 7.0 ) + pow( 25.0, 7.0 ) ) ) ) / 2.0;

   double a1prime = lab1.c[1] * ( 1.0 + G );
   double a2prime = lab2.c[1] * ( 1.0 + G );
   double C1prime = sqrt( ( a1prime * a1prime ) + ( lab1.c[2] * lab1.c[2] ) );
   double C2prime = sqrt( ( a2prime * a2prime ) + ( lab2.c[2] * lab2.c[2] ) );
   double Cbarprime = ( C1prime + C2prime ) / 2.0;
   
   double h1prime = atan2( lab1.c[2], a1prime );
   if ( h1prime < 0.0 )
   {
      h1prime += ( 2.0 * M_PI );
   }
   
   double h2prime = atan2( lab2.c[2], a2prime );
   if ( h2prime < 0.0 )
   {
      h2prime += ( 2.0 * M_PI);
   }
   
   if ( fabs( h1prime - h2prime ) > M_PI )
   {
      Hbarprime = ( ( h1prime + h2prime ) / 2.0 ) - M_PI;
   }
   else
   {
      Hbarprime = ( h1prime + h2prime ) / 2.0;
   }
   
   T = 1.0 - 0.17 * cos( Hbarprime - ( M_PI / 6.0 ) ) + 0.24 * cos( 2.0 * Hbarprime ) + 
       0.32 * cos( 3.0 * Hbarprime + ( M_PI / 30.0 ) ) - 0.20 * cos( 4.0 * Hbarprime - ( M_PI * 63.0 / 180.0 ) );

   if ( fabs( h1prime - h2prime ) <= M_PI )
   {
      dhprime = fabs( h1prime - h2prime );
   }
   else
   {
      dhprime = ( 2.0 * M_PI ) - fabs( h1prime - h2prime );
   }
   
   dLCHprime.c[0] = fabs( lab1.c[0] - lab2.c[0] );
   dLCHprime.c[1] = fabs( C1prime - C2prime );
   dLCHprime.c[2] = 2.0 * sqrt( C1prime * C2prime ) * sin( dhprime / 2.0 );

   SL = 1.0 + ( 0.015 * ( Lbarprime - 50.0 ) * ( Lbarprime - 50.0 ) ) / 
             sqrt( 20.0 + ( ( Lbarprime - 50.0 ) * ( Lbarprime - 50.0 ) ) ) ;
   SC = 1.0 + ( 0.045 * Cbarprime );
   SH = 1.0 + ( 0.015 * Cbarprime * T );
   dtheta = exp( - ( ( Hbarprime * 180.0 / M_PI - 275.0 ) / 25.0 ) * ( ( Hbarprime * 180.0 / M_PI - 275.0 ) / 25.0 ) ) * M_PI / 6.0;
   RC = 2.0 * sqrt( pow( Cbarprime, 7.0 ) / ( pow( Cbarprime, 7.0 ) + pow( 25.0, 7.0 ) ) );
   RT = - RC * sin( 2.0 * dtheta );

   return sqrt(   ( dLCHprime.c[0] / ( KL * SL ) ) * ( dLCHprime.c[0] / ( KL * SL ) )
                + ( dLCHprime.c[1] / ( KC * SC ) ) * ( dLCHprime.c[1] / ( KC * SC ) )
                + ( dLCHprime.c[2] / ( KH * SH ) ) * ( dLCHprime.c[2] / ( KH * SH ) )
                + ( RT * ( dLCHprime.c[1] / ( KC * SC ) ) * ( dLCHprime.c[2] / ( KH * SH ) ) ) 
              );
}
//----------------------------------------------------------

double TransformColorSpace::DeltaE2000( double *pSpectralValues1, double *pSpectralValues2, int wavelengthMin, int wavelengthMax )
{
   ColorValue lab1 = SpectralValuesToLab( pSpectralValues1, wavelengthMin, wavelengthMax );
   ColorValue lab2 = SpectralValuesToLab( pSpectralValues2, wavelengthMin, wavelengthMax );
   return DeltaE2000( lab1, lab2 );
}

//----------------------------------------------------------

ColorValue TransformColorSpace::SpectralValuesToXYZ( double *pSpectralValuesArray, int wavelengthMin, int wavelengthMax )
{
   ColorValue XYZ = ColorValue( 0.0, 0.0, 0.0, TYPE_XYZ );  // initialize zero value XYZ

   if ( wavelengthMin < ColorConstants::sMinimumWavelength )
   {
      cerr << "Minimum wavelength must be 380nm" << endl;
      return XYZ;  // return zero value XYZ
   }
   if ( wavelengthMax > ColorConstants::sMaximumWavelength )
   {
      cerr << "Maximum wavelength must be 770nm" << endl;
      return XYZ;  // return zero value XYZ
   }

   int indexFirstSampleInArray = (int) ( ( wavelengthMin - ColorConstants::sMinimumWavelength ) / (double) ColorConstants::sWavelengthStepSize );
   int nrSamples = (int) ( ( wavelengthMax - wavelengthMin + ColorConstants::sWavelengthStepSize ) / (double) ColorConstants::sWavelengthStepSize );

   for ( int i = indexFirstSampleInArray; i < nrSamples + indexFirstSampleInArray; i++ )
   {
      XYZ.c[ 0 ] += ColorConstants::sMatchingFunctionCIEx[ i ] * ColorConstants::sD50IlluminantSpectrum[ i ] * pSpectralValuesArray[ i - indexFirstSampleInArray ];
      XYZ.c[ 1 ] += ColorConstants::sMatchingFunctionCIEy[ i ] * ColorConstants::sD50IlluminantSpectrum[ i ] * pSpectralValuesArray[ i - indexFirstSampleInArray ];
      XYZ.c[ 2 ] += ColorConstants::sMatchingFunctionCIEz[ i ] * ColorConstants::sD50IlluminantSpectrum[ i ] * pSpectralValuesArray[ i - indexFirstSampleInArray ];
   }
   
   XYZ.c[ 0 ] = 100.0 * XYZ.c[ 0 ] / ColorConstants::sSpectralNormalizationConstantD50;
   XYZ.c[ 1 ] = 100.0 * XYZ.c[ 1 ] / ColorConstants::sSpectralNormalizationConstantD50;
   XYZ.c[ 2 ] = 100.0 * XYZ.c[ 2 ] / ColorConstants::sSpectralNormalizationConstantD50;
   return XYZ;
}

//----------------------------------------------------------

ColorValue TransformColorSpace::SpectralValuesToLab( double *pSpectralValuesArray, int wavelengthMin, int wavelengthMax )
{
   return XYZtoLab( SpectralValuesToXYZ( pSpectralValuesArray, wavelengthMin, wavelengthMax ) / 100.0 );
}

//----------------------------------------------------------

}
}
