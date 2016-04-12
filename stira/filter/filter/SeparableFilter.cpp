
/***********************************************************************************
 *   Copyright (C) 2016 by Filip Rooms                                             *
 *                                                                                 *
 *  Terms and conditions for using this software in any form are provided in the   *
 *  file COPYING, which can be found in the root directory of this project.        *
 *                                                                                 *
 *   Contact data: filip.rooms@gmail.com                                           *
 *                 http://www.filiprooms.be/                                       *
 *                                                                                 *
 ***********************************************************************************/

#include "SeparableFilter.h"
#include "../../image/datastructures/ArrayGrid.h"

namespace stira {
namespace filter {

using namespace image;
using namespace std;

//------------------------------------------------------------------------------------------

SeparableFilter::SeparableFilter()
{
}

//------------------------------------------------------------------------------------------

SeparableFilter::~SeparableFilter()
{
}

//------------------------------------------------------------------------------------------

bool SeparableFilter::RunRow( image::ArrayGrid<double>* pInputBand, image::ArrayGrid<double>* pOutputBand, double *filtx, int filterLengthX, image::GridExtender<double>::ExtensionType myType )
{
   int width = pInputBand->GetWidth();
   int height = pInputBand->GetHeight();

   assert ( pInputBand != 0 );
   assert ( pOutputBand != 0 );
   assert ( pOutputBand->GetWidth() == width );
   assert ( pOutputBand->GetHeight() == height  );

   // filter row by row with filtx
   ///////////////////////////////
   if (filterLengthX > 1)
   {
      double *pRowIn  = new double[ width ];
      double *pRowOut = new double[ width ];
      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x++)
         {
            pRowIn[x] = pInputBand->GetValue(x, y);
         }
         BasicFilter1D (&(*pRowIn), &(*filtx), &(*pRowOut), width, filterLengthX, myType);
         for (int x = 0; x < width; x++)
         {
            pOutputBand->SetValue(x, y, pRowOut[x]);
         }
      }
      delete []pRowIn;
      delete []pRowOut;
   }
   else
   {
      pOutputBand->SetGridValues( *pInputBand );
   }
   return true;
}

//------------------------------------------------------------------------------------------

bool SeparableFilter::RunColumn( ArrayGrid<double>* pInputBand, ArrayGrid<double>* pOutputBand, double *filty, int filterLengthY, GridExtender<double>::ExtensionType myType  )
{
   int width = pInputBand->GetWidth();
   int height = pInputBand->GetHeight();

   assert ( pInputBand != 0 );
   assert ( pOutputBand != 0 );
   assert ( pOutputBand->GetWidth() == width );
   assert ( pOutputBand->GetHeight() == height  );
   // filter column by column with filty
   /////////////////////////////////////
   if (filterLengthY > 1)
   {
      double *pColumnIn  = new double[ height ];
      double *pColumnOut = new double[ height ];
      for (int x = 0; x < width; x++)
      {
         for (int y = 0; y < height; y++)
         {
            pColumnIn[y] = pInputBand->GetValue(x, y);
         }
         BasicFilter1D (&(*pColumnIn), &(*filty), &(*pColumnOut), pInputBand->GetHeight(), filterLengthY, myType);
         for (int y = 0; y < height; y++)
         {
            pOutputBand->SetValue(x, y, pColumnOut[y]);
         }
      }
      delete []pColumnIn;
      delete []pColumnOut;
   }
   else
   {
      pOutputBand->SetGridValues( *pInputBand );
   }

   return true;
}

//------------------------------------------------------------------------------------------

ArrayGrid<double>* SeparableFilter::RunRowColumn( ArrayGrid<double>* pInputBand, double *filtx, double *filty, int filterLengthX, int filterLengthY, GridExtender<double>::ExtensionType myType )
{
   ArrayGrid<double>* pFilteredBand = 0;

   int width = pInputBand->GetWidth();
   int height = pInputBand->GetHeight();
   bool needInitialisation = true;
   double initialRealValue = 0.0;
   pFilteredBand = new ArrayGrid<double>( width, height, needInitialisation, initialRealValue );
   // filter row by row with filtx
   RunRow( pInputBand, pFilteredBand, filtx, filterLengthX, myType );

   // filter column by column with filty
   RunColumn( pFilteredBand, pFilteredBand, filty, filterLengthY, myType );

   return pFilteredBand;
}

//------------------------------------------------------------------------------------------

ArrayGrid<double>* SeparableFilter::RunColumnRow( ArrayGrid<double>* pInputBand, double *filtx, double *filty, int filterLengthX, int filterLengthY, GridExtender<double>::ExtensionType myType  )
{
   ArrayGrid<double>* pFilteredBand = 0;

   int width = pInputBand->GetWidth();
   int height = pInputBand->GetHeight();
   bool needInitialisation = true;
   double initialRealValue = 0.0;
   pFilteredBand = new ArrayGrid<double>( width, height, needInitialisation, initialRealValue );

   // filter column by column with filty
   RunColumn( pInputBand, pFilteredBand, filty, filterLengthY, myType );

   // filter row by row with filtx
   RunRow( pFilteredBand, pFilteredBand, filtx, filterLengthX, myType );

   return pFilteredBand;
}
//------------------------------------------------------------------------------------------

image::Image* SeparableFilter::RunRowColumn( image::Image* pImageIn, double *filterTapX, double *filterTapY, int filterLengthX, int filterLengthY, GridExtender<double>::ExtensionType myType )
{
   int nrBands = pImageIn->GetNumberOfBands();
   int width = pImageIn->GetWidth();
   int height = pImageIn->GetHeight();

   Image* pImageOut = new Image(width, height);
   SeparableFilter sf;
   for (int i = 0; i < nrBands; i++)
   {
      ArrayGrid<double>* pGridOut = sf.RunRowColumn( pImageIn->GetBands()[i], filterTapX, filterTapY, filterLengthX, filterLengthY, myType );
      pImageOut->AddBand( pGridOut );
   }
   return pImageOut;
}

//------------------------------------------------------------------------------------------

image::Image* SeparableFilter::RunColumnRow( image::Image* pImageIn, double *filterTapX, double *filterTapY, int filterLengthX, int filterLengthY, GridExtender<double>::ExtensionType myType )
{
   int nrBands = pImageIn->GetNumberOfBands();
   int width = pImageIn->GetWidth();
   int height = pImageIn->GetHeight();

   Image* pImageOut = new Image(width, height);

   SeparableFilter sf;
   for (int i = 0; i < nrBands; i++)
   {
      ArrayGrid<double>* pGridOut = sf.RunColumnRow( pImageIn->GetBands()[i], filterTapX, filterTapY, filterLengthX, filterLengthY, myType );
      pImageOut->AddBand( pGridOut );
   }
   return pImageOut;
}

//------------------------------------------------------------------------------------------

double* SeparableFilter::GenerateExtendedInput(double* pInputArray1D, int inputLength, GridExtender<double>::ExtensionType myType )
{
   double *pExtendedInput = new double[3 * inputLength];

   // Solving the border problems: Input vector should be made periodical and mirrored
   switch (myType)
   {
      case GridExtender<double>::EXTEND_MIRROR:
      {
         for (int i = 0; i < inputLength; i++)
         {
            pExtendedInput[i + inputLength] = pInputArray1D[i];
            pExtendedInput[3 * inputLength - 1 - i] = pInputArray1D[i];
            pExtendedInput[inputLength - 1 - i] = pInputArray1D[i];
         }
         break;
      }
      case GridExtender<double>::EXTEND_ZERO:
      {
         for (int i = 0; i < inputLength; i++)
         {
            pExtendedInput[i + inputLength] = pInputArray1D[i];
            pExtendedInput[i] = 0.0;
            pExtendedInput[i +2*inputLength] = 0.0;
         }
         break;
      }
      case GridExtender<double>::EXTEND_TILED:
      default:
      {
         for (int i = 0; i < inputLength; i++)
         {
            pExtendedInput[i + inputLength] = pInputArray1D[i];
            pExtendedInput[i] = pInputArray1D[i];
            pExtendedInput[i +2*inputLength] = pInputArray1D[i];
         }
         break;
      }
   }
   return pExtendedInput;
}

//------------------------------------------------------------------------------------------

void SeparableFilter::BasicFilter1D (double *pInputArray1D, double *pFilterKernel, double *pOutputArray1D, int inputLength, int filterLength, GridExtender<double>::ExtensionType myType)
{
   int len;
   double *pExtendedInput = GenerateExtendedInput( pInputArray1D, inputLength, myType);
   // Convolution: c=conv(ap,he)

   int filterKernelIndex = ((filterLength - 1) / 2);	//index of the element pFilterKernel(0)

   for (int j = 0; j < inputLength; j++)
   {
      pOutputArray1D[j] = 0;
      int dataIndex = inputLength + j;       //index of the element pInputArray1D(0+j) in the vector pExtendedInput
      if ((dataIndex + filterKernelIndex + 1) >= filterLength)
      {
         len = filterLength;
      }
      else
      {
         len = dataIndex + filterKernelIndex + 1;
      }
      for (int i = 0; i < len; i++)
      {
         pOutputArray1D[j] += pFilterKernel[i] * pExtendedInput[dataIndex + i - filterKernelIndex ];
      }
   }
   delete []pExtendedInput;
}

//------------------------------------------------------------------------------------------

}
}
