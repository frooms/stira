#include "FlashROF.h"

#include <cmath>

#include <iostream>

namespace stira{

using namespace image;

FlashROF::FlashROF()
{
   mMu = .1;
   mLambda=.2;
   mNumberOfGaussSeidelIterations = 1;			// number of Gauss-Seidel iterations per loop
   mNumberOfBregmanIterations = 50;			// total iterations to perform per denoise;
   mIsIsotropic = true;
}

FlashROF::~FlashROF()
{
}

double FlashROF::GetMu()
{
   return mMu;
}

void FlashROF::SetMu( double mu )
{
   mMu = mu;
}

double FlashROF::GetLambda()
{
   return mLambda;
}

void FlashROF::SetLambda( double lambda )
{
   mLambda = lambda;
}

int FlashROF::GetNumberOfGaussSeidelIterations()
{
   return mNumberOfGaussSeidelIterations;
}

void FlashROF::SetNumberOfGaussSeidelIterations( int nGS )
{
   mNumberOfGaussSeidelIterations = nGS;
}

int FlashROF::GetNumberOfBregmanIterations()
{
   return mNumberOfBregmanIterations;
}

void FlashROF::SetNumberOfBregmanIterations( int nBreg )
{
   mNumberOfBregmanIterations = nBreg;
}

bool FlashROF::GetIsIsotropic()
{
   return mIsIsotropic;
}

void FlashROF::SetIsIsotropic( bool flag )
{
   mIsIsotropic = flag;
}

image::Image* FlashROF::Run( image::Image* pImageIn )
{
   int height = pImageIn->GetHeight();
   int width  = pImageIn->GetWidth();
   int nrBands = pImageIn->GetNumberOfBands();
   Image* pResult = new Image( width, height, nrBands);

   num** f  = FlashROF::newMatrix( width,     height     );
   num** u  = FlashROF::newMatrix( width,     height     );
   num** x  = FlashROF::newMatrix( width - 1, height     );
   num** y  = FlashROF::newMatrix( width,     height - 1 );
   num** bx = FlashROF::newMatrix( width - 1, height     );
   num** by = FlashROF::newMatrix( width,     height - 1 );
   
   for (int bandID = 0; bandID < nrBands; bandID++)
   {
      //  load the "test image" into f
      for(int r = 0; r < height; r++)
      {
         for(int c = 0; c < width; c++)
         {
            f[c][r] = pImageIn->GetBands()[bandID]->GetValue(c,r);
         }
      }
      
      //  To denoise the image with Isotropic Split bregman, just do this:
      /////////////////////////////////////////////////////////////////////
      if ( mIsIsotropic )
      {
         FlashROF::rof_iso( u, f, x, y, bx, by, mMu, mLambda, mNumberOfGaussSeidelIterations, mNumberOfBregmanIterations, width, height);
      }
      else
      {
         FlashROF::rof_an( u, f, x, y, bx, by, mMu, mLambda, mNumberOfGaussSeidelIterations, mNumberOfBregmanIterations, width, height);
      }
      
      // Export denoised result
      /////////////////////////
      for( int r = 0; r < height; r++ )
      {
         for( int c = 0; c < width; c++ )
         {
            pResult->GetBands()[bandID]->SetValue( c, r, u[ c ][ r ]);
         }
      }
   }
   
   FlashROF::deleteMatrix( f );
   FlashROF::deleteMatrix( u );
   FlashROF::deleteMatrix( x );
   FlashROF::deleteMatrix( y );
   FlashROF::deleteMatrix( bx );
   FlashROF::deleteMatrix( by );
   
   std::string outName = pImageIn->GetImageName() + std::string("-FlashROF");
   pResult->SetImageName(outName);
   
   return pResult;
}


/******************Isotropic TV**************/
void FlashROF::rof_iso(num** ppDenoised, num** f, num** x, num** y, num** bx, num** by ,
								 double mu, double lambda, int nGS, int nBreg, int width, int height)
{
   for( int breg = 0; breg < nBreg; breg++ )
   {
      gs_iso( ppDenoised, f, x, y, bx, by, mu, lambda, width, height, nGS );
      bregmanX( x, ppDenoised, bx, width, height );
      bregmanY( y, ppDenoised, by, width, height );
   }
}	


void FlashROF::gs_iso(num** ppDenoised, num** f, num** x, num** y, num** bx, num** by , double mu, double lambda, int width, int height, int iter)
{
   for( int j = 0;j < iter; j++)
   {
      gsU(  ppDenoised, f, x, y, bx, by, mu, lambda, width, height );
      gsSpace( ppDenoised, x, y, bx, by, lambda, width, height );
   }
}


/******************Anisotropic TV**************/
void FlashROF::rof_an(num** ppDenoised, num** f, num** x, num** y, num** bx, num** by ,
								 double mu, double lambda, int nGS, int nBreg, int width, int height)
{
   for( int breg = 0; breg < nBreg; breg++ )
   {
      gs_an( ppDenoised, f, x, y, bx, by, mu, lambda, width, height,nGS);
      bregmanX( x, ppDenoised, bx, width, height );
      bregmanY( y, ppDenoised, by, width, height );
   }
}	


void FlashROF::gs_an(num** ppDenoised, num** f, num** x, num** y, num** bx, num** by , double mu, double lambda, int width, int height, int iter)
{
   for(int j=0;j<iter;j++)
   {
      gsU( ppDenoised, f, x,  y, bx, by, mu, lambda, width, height );
      gsX( ppDenoised, x, bx, lambda, width, height );
      gsY( ppDenoised, y, by, lambda, width, height );
   }
}


/****Relaxation operators****/

void FlashROF::gsU(num** ppDenoised, num** f, num** x, num** y, num** bx, num** by , double mu, double lambda, int width, int height)
{
   int w,h;
   double sum;
   int wm1,hm1;
   double normConst = 1.0 / (mu + 4 * lambda);
   
   // do the central pixels
   ////////////////////////
   int wSent = width-1, hSent = height-1;
   for( w = 1; w < wSent; w++)
   {
      wm1 = w-1;
      for( h = 1; h < hSent; h++)
      {
         hm1 = h-1;
         sum = x[wm1][h] - x[w][h]+y[w][hm1] - y[w][h]
                                 -bx[wm1][h] + bx[w][h] - by[w][hm1] + by[w][h];
         sum += ( ppDenoised[w+1][h] + ppDenoised[wm1][h] + ppDenoised[w][h+1] + ppDenoised[w][hm1]);
         sum *= lambda;
         sum += mu * f[w][h];
         sum *= normConst;
         //sum/=mu+4*lambda;
         ppDenoised[w][h] = sum;
      }
   }
   // do the left pixels
   /////////////////////
   w=0;
   for( h = 1; h < hSent; h++)
   {
      sum = - x[w][h]+y[w][h-1] - y[w][h]
                              + bx[w][h] - by[w][h-1] + by[w][h];
      sum += ( ppDenoised[w+1][h] + ppDenoised[w][h+1] + ppDenoised[w][h-1]);
      sum *= lambda;
      sum += mu * f[w][h];
      sum /= mu + 3 * lambda;
      ppDenoised[w][h] = sum;
   }
   
   // do the right pixels
   //////////////////////
   w = width-1;
   for(h=1;h<hSent;h++)
   {
      sum = x[w-1][h] +y[w][h-1] - y[w][h]
                                       -bx[w-1][h] -by[w][h-1] + by[w][h];
      sum += ppDenoised[w-1][h] + ppDenoised[w][h+1] + ppDenoised[w][h-1];
      sum *= lambda;
      sum += mu * f[w][h];
      sum /= mu + 3 * lambda;
      ppDenoised[w][h] = sum;
   }

   // do the top pixels
   //////////////////////
   h = 0;
   for( w = 1; w < wSent; w++ )
   {
      sum = x[w-1][h] - x[w][h] - y[w][h]
                                       -bx[w-1][h] + bx[w][h] + by[w][h];
      sum += ppDenoised[w+1][h] + ppDenoised[w-1][h] + ppDenoised[w][h+1];
      sum *= lambda;
      sum += mu * f[w][h];
      sum /= mu + 3 * lambda;
      ppDenoised[w][h] = sum;
   }
         
   // do the bottom pixels
   ///////////////////////
   h = height-1;
   for( w = 1; w < wSent; w++)
   {
      sum = x[w-1][h] - x[w][h]+y[w][h-1] 
                                       -bx[w-1][h] + bx[w][h]-by[w][h-1];
      sum += ppDenoised[w+1][h] + ppDenoised[w-1][h] + ppDenoised[w][h-1];
      sum *= lambda;
      sum += mu * f[w][h];
      sum /= mu + 3 * lambda;
      ppDenoised[w][h] = sum;
   }
   
   // do the top left pixel
   ////////////////////////
   w=h=0;
   sum =  - x[w][h] - y[w][h]
                                    + bx[w][h] + by[w][h];
   sum += ppDenoised[w+1][h] + ppDenoised[w][h+1];
   sum *= lambda;
   sum += mu * f[w][h];
   sum /= mu + 2 * lambda;
   ppDenoised[w][h] = sum;
   
   // do the top right pixel
   /////////////////////////
   w=width-1; h=0;
   sum = x[w-1][h]  - y[w][h]
                                    -bx[w-1][h] + by[w][h];
   sum += ppDenoised[w-1][h] + ppDenoised[w][h+1];
   sum *= lambda;
   sum += mu*f[w][h];
   sum /= mu + 2 * lambda;
   ppDenoised[w][h] = sum;
   
   // do the bottom left pixel
   ///////////////////////////
   w=0; h=height-1;
   sum =  - x[w][h]+y[w][h-1] 
                                    + bx[w][h]-by[w][h-1] ;
   
   sum += ppDenoised[w+1][h] + ppDenoised[w][h-1];
   sum *= lambda;
   sum += mu * f[w][h];
   sum /= mu + 2 * lambda;
   ppDenoised[w][h] = sum;
   
   // do the bottom right pixel	
   ////////////////////////////	
   w = width-1; h = height-1;
   sum = x[w-1][h] + y[w][h-1] 
                                    -bx[w-1][h] -by[w][h-1];	
   sum += ppDenoised[w-1][h] + ppDenoised[w][h-1];
   sum *= lambda;
   sum += mu * f[w][h];
   sum /= mu + 2 * lambda;
   ppDenoised[w][h] = sum;
}


void FlashROF::gsSpace(num** ppDenoised, num** x, num** y, num** bx, num** by, double lambda, int width, int height)
{
   int w,h;
   num a, b, s;
   num flux  =  1.0 / lambda;
   num mflux = -1.0 / lambda;
   num flux2 = flux * flux;
   num *uw, *uwp1, *bxw, *byw, *xw, *yw;
   for( w = 0; w < width - 1; w++)
   {
      uw   = ppDenoised[w];
      uwp1 = ppDenoised[w+1];
      bxw = bx[w];
      byw = by[w];
      xw = x[w];
      yw = y[w];
      for(h=0;h<height-1;h++)
      {
         a =  uwp1[h]-uw[h]+bxw[h];
         b =  uw[h+1]-uw[h]+byw[h];
         s = a*a+b*b;
         if(s<flux2)
         {
            xw[h]=0;
            yw[h]=0;
            continue;
         }
         s = sqrt(s);
         s=(s-flux)/s;
         xw[h] = s*a;
         yw[h] = s*b;
      }
   }
   num base;
   h = height-1;
   for(w=0;w<width-1;w++)
   {
      base =  ppDenoised[w+1][h] - ppDenoised[w][h] + bx[w][h];
      if( base > flux)  { x[w][h] = base-flux; continue;}
      if( base < mflux) { x[w][h] = base+flux; continue;}
      x[w][h] = 0;
   }
   w = width-1;
   for(h=0;h<height-1;h++)
   {
      base =  ppDenoised[w][h+1]-ppDenoised[w][h]+by[w][h];
      if(base>flux) {y[w][h] = base-flux; continue;}
      if(base<mflux){y[w][h] = base+flux; continue;}
      y[w][h] = 0;
   }
}


void FlashROF::gsX(num** u, num** x, num** bx , double lambda, int width, int height)
{
   width = width-1;
   int w,h;
   double base;
   const double flux = 1.0/lambda;
   const double mflux = -1.0/lambda;
   num* uwp1;
   num* uw;
   num* bxw;
   num* xw;
   for(w=0;w<width;w++)
   {
      uwp1 = u[w+1];
      uw = u[w];
      bxw = bx[w];
      xw = x[w];
      for(h=0;h<height;h++)
      {
         base = uwp1[h]-uw[h]+bxw[h];
         if(base>flux) {xw[h] = base-flux; continue;}
         if(base<mflux){xw[h] = base+flux; continue;}
         xw[h] = 0;
      }
   }
}

void FlashROF::gsY(num** u, num** y, num** by , double lambda, int width, int height)
{
   height = height-1;
   int w,h;
   double base;				
   const double flux = 1.0/lambda;
   const double mflux = -1.0/lambda;
   num* uw;
   num* yw;
   num* bw;
   for(w=0;w<width;w++)
   {
      uw = u[w];
      yw = y[w];
      bw = by[w];
      for(h=0;h<height;h++)
      {
         base = uw[h+1]-uw[h]+bw[h];
         if(base>flux) {yw[h] = base-flux; continue;}
         if(base<mflux){yw[h] = base+flux; continue;}
         yw[h] = 0;
      }
   }
}

void FlashROF::bregmanX(num** x,num** u, num** bx, int width, int height)
{
   int w,h;
   double d;
   num* uwp1,*uw,*bxw,*xw;
   for(w=0;w<width-1;w++)
   {
      uwp1=u[w+1];uw=u[w];bxw=bx[w];xw=x[w];
      for(h=0;h<height;h++)
      {
         d = uwp1[h]-uw[h];
         bxw[h]+= d-xw[h];		
      }
   }
}


void FlashROF::bregmanY(num** y,num** u, num** by, int width, int height)
{
   int w,h;
   double d;
   int hSent = height-1;
   num* uw,*byw,*yw;
   for( w = 0; w < width; w++)
   {
      uw = u[ w ]; byw = by[ w ]; yw = y[ w ];
      for( h = 0; h < hSent; h++ )
      {
         d = uw[h+1]-uw[h];
         byw[h]+= d-yw[h];
      }
   }
}

/************************memory****************/

num** FlashROF::newMatrix(int rows, int cols)
{
   num* a = new num[rows*cols];
   num** rval = new num*[rows];
   if(rval==0 || a == 0)
   {
      std::cout<<"ERROR: Out of Memory\n";
      std::exit(0);
   }

   rval[0] = a;
   for( int j = 1; j < rows; j++ )
   {
      rval[j] = &a[j*cols];
   }
   
   for( int j = 0; j < rows; j++ )
   {
      for( int g = 0; g < cols; g++)
      {
         rval[j][g] = 0;
      }
   }
   return rval;
}

void FlashROF::deleteMatrix(num ** a)
{
   delete[] a[0];
   delete[] a;
}
}

