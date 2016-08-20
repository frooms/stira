
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

#include "TikhonovMillerDeconvolve.h"
#include "../../fouriertools/fouriertools/FFT.h"
#include "../../fouriertools/fouriertools/FFTBand.h"

namespace stira{
namespace deconvolve{

using namespace fouriertools;
using namespace std;

TikhonovMillerDeconvolve::TikhonovMillerDeconvolve( Image* pDegradedImage, int maxNrOfIterations )
                           : IterativeDeconvolve( pDegradedImage, maxNrOfIterations )
{
   mFlagEnforcePositivity = true;
}

//--------------------------------------------------------------------------

TikhonovMillerDeconvolve::TikhonovMillerDeconvolve( Image* pDegradedImage, Image* pPSF, int maxNrOfIterations )
                           : IterativeDeconvolve( pDegradedImage, pPSF, maxNrOfIterations )
{
   mFlagEnforcePositivity = true;
}

//--------------------------------------------------------------------------

TikhonovMillerDeconvolve::~TikhonovMillerDeconvolve( )
{
}

//--------------------------------------------------------------------------

void TikhonovMillerDeconvolve::PrintParameters()
{
   cout << "\t Current iteration nr = " << mCurrentIterationNr << endl << flush;
   cout << "\t Maximum nr of iterations =  " << mMaximumNrOfIterations << endl << flush;
   cout << "\t mpNewEstimate  = " << mpNewEstimate << endl << flush;
   cout << "\t mpCurrentBandNr = " << mCurrentBandNr << endl << flush;
   cout << "\t mLambda = " << mLambda << endl << flush;
   cout << "\t mFlagEnforcePositivity = " << mFlagEnforcePositivity << endl << flush;
   cout << "\t mStepSize = " << mStepSize << endl << flush;
}

//--------------------------------------------------------------------------

void TikhonovMillerDeconvolve::SetEnforcePositivity(bool flag)
{
   mFlagEnforcePositivity = flag;
}

//--------------------------------------------------------------------------

bool TikhonovMillerDeconvolve::GetEnforcePositivity()
{
   return mFlagEnforcePositivity;
}

//--------------------------------------------------------------------------

bool TikhonovMillerDeconvolve::Run()
{
   std::string outName;
   if (IsReadyToRun() == true)
   {
      PrintParameters();
      for (mCurrentIterationNr = 0; mCurrentIterationNr < mMaximumNrOfIterations; mCurrentIterationNr++)
      {
         cout << "\t iteration " << mCurrentIterationNr << endl << flush;
         for (int mpCurrentBandNr = 0; mpCurrentBandNr < mpDegradedImage->GetNumberOfBands(); mpCurrentBandNr++)
         {
            RunSingleIterationSingleBand( );
         }
      }
      mpRestoredImage = mpNewEstimate->Clone();

      outName = mpDegradedImage->GetImageName() + std::string("-Tikhonov-Miller");

      mpRestoredImage->SetImageName(outName);
   }
   else
   {
      cerr << "Unable to start RL iterations; return 0 and abort..." << endl << flush;
   }
   return true;
}

//--------------------------------------------------------------------------

bool TikhonovMillerDeconvolve::ApplyPositivityConstraint( ArrayGrid<double>* pGrid )
{
   int width = pGrid->GetWidth();
   int height = pGrid->GetHeight();
   for (int y = 0; y < height; y++)
   {
      for (int x = 0; x < width; x++)
      {
         if ( pGrid->GetValue( x, y ) < 0.0 ) { pGrid->SetValue( x, y, 0.0); }
      }
   }
   return true;
}

//--------------------------------------------------------------------------;

bool TikhonovMillerDeconvolve::IsReadyToRun()
{
   return AreParentConditionsOK();
}

//--------------------------------------------------------------------------;

// For the moment still Landweber
bool TikhonovMillerDeconvolve::RunSingleIterationSingleBand( )
{
   PrepareCurrentGrids( );

   ArrayGrid<double>* pConvolved = FFT::Convolve( mpNewGrid, mpPSFGrid );
   ArrayGrid<double>* pTmpGrid = mpDegradedGrid->Clone();
   pTmpGrid->SubtractGrid( pConvolved ); delete pConvolved;

   pConvolved = FFT::Convolve( pTmpGrid, mpPSFGrid );    delete pTmpGrid;
   pConvolved->MultiplyWith( mStepSize );

   mpNewGrid->AddGrid( pConvolved );   delete pConvolved;
   if (mFlagEnforcePositivity == true)
   {
      ApplyPositivityConstraint( mpNewGrid );
   }

   return true;
}

//--------------------------------------------------------------------------;

// frooms@animal:~/develop/c/thesis/tim/thesistim.pdf
// Thesis Van Kempen on page 40: http://www.tnw.tudelft.nl/live/pagina.jsp?id=d45bad79-71f7-4358-98d2-6bd78f432b3a&lang=en
// Thyesis Verveer p 18          http://www.tnw.tudelft.nl/live/pagina.jsp?id=8c72f32d-48cf-4943-ae98-0677d581021f&lang=en
// lambda = energy_noise / energy_signal = energy (laplacian-filtered data) / energy last estimate
/*double TikhonovMillerDeconvolve::compute_lambda(int w, int h, int z, fftw_complex *C, fftw_complex *G, fftw_complex *g)
{
   fftw_complex *RES;
   fftwnd_plan pinv;
   double nom, denom, lambda;
   long i, nr_pix;
   pinv = fftw3d_create_plan(w, h, z, FFTW_BACKWARD, FFTW_ESTIMATE | FFTW_IN_PLACE);
   nr_pix = w*h*z;
   RES = (fftw_complex *) malloc(nr_pix*sizeof(fftw_complex));
   for (i = 0; i < nr_pix; i++) {
     RES[i].re = (C[i].re*G[i].re - C[i].im*G[i].im)/nr_pix;
     RES[i].im = (C[i].re*G[i].im + C[i].im*G[i].re)/nr_pix;
   }
   fftwnd_one(pinv, &RES[0], NULL); //kwadranten juistzetten niet nodig, enkel norm nodig
   nom = denom = 0;
   for (i = 0; i < nr_pix; i++) {
     nom += pow(RES[i].re,2);
     denom += pow(g[i].re,2);
   }
   lambda = nom/denom;
   printf("%f %f %f\n", nom, denom, lambda);
   fftwnd_destroy_plan(pinv);
   free(RES);
   return lambda;
}*/

stira::fouriertools::FFTBand* stira::deconvolve::TikhonovMillerDeconvolve::GenerateLaplacian( int width, int height )
{
   FFTBand* pLaplacianOperator = new FFTBand( width, height );
   std::complex<double> complexValue(1.0, 0.0);
   pLaplacianOperator->SetValue( width / 2,     height / 2    , -4.0 * complexValue );
   pLaplacianOperator->SetValue( width / 2 - 1, height / 2    ,        complexValue );
   pLaplacianOperator->SetValue( width / 2 + 1, height / 2    ,        complexValue );
   pLaplacianOperator->SetValue( width / 2    , height / 2 - 1,        complexValue );
   pLaplacianOperator->SetValue( width / 2    , height / 2 + 1,        complexValue );
   pLaplacianOperator->ApplyForwardTransform();
   return pLaplacianOperator;
}

//De waarden in de array data worden overschreven!
void TikhonovMillerDeconvolve::ICTM_filter( int nr_iter, ArrayGrid<double> *pData, ArrayGrid<double> *pPsf )
{
   /*double lambda, gamma, norm_r_vorig, norm_r, beta;
   fftw_complex *H, *A, *C, *g, *b, *B, *G;
   fftw_complex *d, *r, *R, *f, *F, *F2, temp;
   fftwnd_plan p1,p2,p3;
   long i,nr_pix;
   int j;*/
   double lambda = 0.001;
   int width  = pData->GetWidth();
   int height = pData->GetHeight();
   //Bepalen van r_k = A.f_k - b

   FFTBand* pH = new FFTBand( pPsf );       pH->ApplyForwardTransform();
   FFTBand* pG = new FFTBand( pData );      pG->ApplyForwardTransform();
   FFTBand* pC = GenerateLaplacian( width, height );

   FFTBand* pA     = new FFTBand( width, height );  // initialized at construction to a grid with all values 0 + 0j
   FFTBand* pB     = new FFTBand( width, height );
   FFTBand* pF2    = new FFTBand( width, height );
   FFTBand* pRlast = new FFTBand( width, height );
   FFTBand* pRnext = new FFTBand( width, height );
   FFTBand* pDlast = new FFTBand( width, height );
   FFTBand* pDnext = new FFTBand( width, height );
   // steepest gradient r_k = A * f_k - h^* x g =   A * f_k - B
   //     with A = h^* x h + lambda (c^* x c)

   //Bepalen van lambda gebeurt in aparte procedure
   //lambda = compute_lambda(w,h,z,C,G,g);
   //Bepalen van A en b

   for ( int y = 0; y < height; y++)
   {
      for ( int x = 0; x < width; x++)
      {
         pA->SetValue( x, y, std::norm( pH->GetValue( x, y ) ) + lambda * std::norm( pC->GetValue( x, y ) ) );   // scale factor in fourier domain; cte over iterations
         pB->SetValue( x, y, std::conj( pH->GetValue( x, y ) ) * pG->GetValue( x, y ) );  // in fourier domain
         pRnext->SetValue( x, y, pG->GetValue( x, y ) * pA->GetValue( x, y ) - pB->GetValue( x, y ) );  // first gradient: f_k = g
      }
   }

   //double gamma = NumberGridTools<std::complex<double> >::GetSquaredNorm( Rnext );

   /*for (i = 0; i < nr_pix; i++)
   {
      A[i].re = (H[i].re * H[i].re + H[i].im * H[i].im + lambda * (C[i].re * C[i].re + C[i].im * C[i].im ) );
      A[i].im = 0;
      B[i].re = (H[i].re*G[i].re + H[i].im*G[i].im)/nr_pix;
      B[i].im = (H[i].re*G[i].im - H[i].im*G[i].re)/nr_pix;
   }
  //IFT van b
  fftwnd_one(p3, &B[0], NULL);
  //juistzetten van de kwadranten
  verwissel_kwadr(w,h,z,B,b);
  //Vanaf hier wordt de geheugenruimte anders verdeeld om plaats te besparen;
  d = H; r = C; R = G; f = g; F = B;
  //Initialisatie van norm_r
  norm_r = 1;  //zodat niet gedeeld wordt door 0 bij eerste gamma!
  //Initialisatie van d
  for (i = 0; i < nr_pix; i++) d[i].re = 0;   //JUIST??
  //Hier is het voorbereidingswerk gedaan en begint de eigenlijke iteratie
  for (j = 0; j < nr_iter; j++) {
    //bepalen van r = Af - b;
    fftwnd_one(p2, &f[0], &F[0]);
    for (i = 0; i < nr_pix; i++) {
      R[i].re = (A[i].re*F[i].re - A[i].im*F[i].im)/nr_pix;
      R[i].im = (A[i].re*F[i].im + A[i].im*F[i].re)/nr_pix;   //r is hier nog niet volledig berekend!!
    }
    fftwnd_one(p3, &R[0], NULL);
    verwissel_kwadr(w,h,z,R,r);
    norm_r_vorig = norm_r;
    norm_r = 0;
    for (i = 0; i < nr_pix; i++) {
      r[i].re -= b[i].re;
      norm_r += (r[i].re*r[i].re);
    }
    gamma = norm_r/norm_r_vorig;
    for (i = 0; i < nr_pix; i++) d[i].re = r[i].re + gamma*d[i].re;
    //Bepalen van beta
    //Hiervoor gebruiken we het stuk geheugen gereserveerd door F  en R
    for (i = 0; i < nr_pix; i++) {
      if (f[i].re > 0) F[i].re = d[i].re;
      else F[i].re = 0;
      beta += F[i].re*r[i].re;   //teller van beta berekend (zonder - teken)
    }
    fftwnd_one(p2, &F[0], &F2[0]);
    for (i = 0; i < nr_pix; i++) {
      temp.re = A[i].re*F2[i].re - A[i].im*F2[i].im;
      temp.im = A[i].re*F2[i].im + A[i].im*F2[i].re;
      F2[i].re = temp.re/nr_pix;
      F2[i].im = temp.im/nr_pix;
    }
    fftwnd_one(p3, &F2[0], NULL);
    verwissel_kwadr(w,h,z,F2,R);
    temp.re = 0; //temp.re gebruiken als noemer van beta
    for (i = 0; i < nr_pix; i++) temp.re += F[i].re*R[i].re;
    beta = -beta/temp.re;
    //Uiteindelijk resultaat
    for (i = 0; i < nr_pix; i++) {
      f[i].re = f[i].re + beta*d[i].re;
      if (f[i].re < 0) f[i].re = 0;
    }
  }
  for (i = 0; i < nr_pix; i++) data[i] = (f[i].re > 255) ? 255 : f[i].re;
  free(d);free(F);free(r);free(R);free(f);free(F2);free(A);free(b);*/
}

}
}
