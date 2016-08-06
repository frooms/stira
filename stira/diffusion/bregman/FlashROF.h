/*				FlashROF.h  by Tom Goldstein
 *   This code performs isotropic ROF denoising using the "Split Bregman" algorithm.
 *
 * http://www.math.ucla.edu/~tagoldst/code.html
 *
 * An image of dimensions mxn is denoised using the following command
 *
 *   rof_iso(u,f,x,y,bx,by,mu,lambda,nGS,nBreg,m,n);
 * 
 * where:
 * 
 *   - ppDenoised is an mxn array which holds the denoised image
 *   - f is the mxn noisy image
 *   - x is the (m-1)xn array which holds the x-derivative (I call this d_x in the paper)
 *   - y is the mx(n-1) array which holds the y-derivative
 *   - bx is the (m-1)xn array which holds the Bregman parameter associated with x
 *   - by is the mx(n-1) array which holds the Bregman parameter associated with y 
 *   - mu is the weighting parameter for the fidelity term (mu should be about 0.5 for images with pixels on the 0-255 scale)
 *   - lambda is the Bregman weight (usually, one should choose lambda=mu)
 *   - nGS is the number of Gauss-Seidel sweeps per iteration (I recommend choosing nGS=1) 
 *   - nBreg is the total number of iterations of Split-Bregman to be performed (50 works well for most applications)
 *  
 */

#ifndef STIRA_DIFFUSION_FLASHROF_H_
#define STIRA_DIFFUSION_FLASHROF_H_

typedef double num;
enum neighbortype{ROF_ISOTROPIC, ROF_ANISOTROPIC};
#include "../../imagedata/datastructures/Image.h"

namespace stira{

class FlashROF
{
public:
   
   FlashROF();
   ~FlashROF();
   
   image::Image* Run( image::Image* pImageIn );
   
   double GetMu();
   void SetMu( double mu );
   
   double GetLambda();
   void SetLambda( double lambda );
   
   int GetNumberOfGaussSeidelIterations();
   void SetNumberOfGaussSeidelIterations( int nGS );
   
   int GetNumberOfBregmanIterations();
   void SetNumberOfBregmanIterations( int nBreg );
   
   bool GetIsIsotropic();
   void SetIsIsotropic( bool flag );
   
private:
   
   double mMu;
   double mLambda;
   int mNumberOfGaussSeidelIterations;
   int mNumberOfBregmanIterations;
   bool mIsIsotropic;
   
   
   static void rof_iso(num** ppDenoised, num** f, num** x, num** y, num** bx, num** by ,
                                                                     double mu, double lambda, int nGS, int nBreg, int width, int height);
   
   static void rof_an(num** ppDenoised, num** f, num** x, num** y, num** bx, num** by ,
                                                                     double mu, double lambda, int nGS, int nBreg, int width, int height);
   /*****************Minimization Methods*****************/
   static void gs_an(num** ppDenoised,  num** f, num** x, num** y, num** bx, num** by , double mu, double lambda, int width, int height, int iter);
   static void gs_iso(num** ppDenoised, num** f, num** x, num** y, num** bx, num** by , double mu, double lambda, int width, int height, int iter);
   
   /******************Relaxation Methods*****************/
   static void gsU(num** ppDenoised, num** f, num** x, num** y, num** bx, num** by , double mu, double lambda, int width, int height);
   static void gsX(num** ppDenoised, num** x, num** bx , double lambda, int width, int height);
   static void gsY(num** ppDenoised, num** y, num** by , double lambda, int width, int height);
   static void gsSpace(num** ppDenoised, num** x, num** y, num** bx, num** by, double lambda, int width, int height);
   
   /************************Bregman***********************/
   static void bregmanX(num** x,num** ppDenoised, num** bx, int width, int height);
   static void bregmanY(num** y,num** ppDenoised, num** by, int width, int height);

   /**********************Memory************/
   static num** newMatrix(int rows, int cols);
   static void deleteMatrix(num ** a);
};
}
#endif /*FLASHROF_H_*/
