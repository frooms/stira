#include "HardLink.h"

bool HardLink::Phase1( int i, int j, ArrayGrid<int>* pNewGrid, ArrayGrid<int>* pOldGrid )
{
   Cell cell( i, j, pOldGrid );
   if (cell.Apz==1 && 4<= cell.Bpz && cell.Bpz <=7 && cell.C1==0 && cell.D1==0)
   {
      pNewGrid->SetValue( j, i, 255);
      return true;
   }
   return false;
}

bool HardLink::Phase2( int i, int j, ArrayGrid<int>* pNewGrid, ArrayGrid<int>* pOldGrid )
{
   Cell cell( i, j, pOldGrid );
   if (cell.Apz==1 && 5<= cell.Bpz && cell.Bpz <=7 && cell.C2==0 && cell.D2==0)
   {
      pNewGrid->SetValue( j, i, 255);
      return true;
   }
   return false;
}

ArrayGrid<int>* HardLink::MedialAxisTransform( ArrayGrid<int>* pGrid )
{
   int width  = pGrid->GetWidth();
   int height = pGrid->GetHeight();
   ArrayGrid<int>* pNewGrid = pGrid->Clone();
   ArrayGrid<int>* pOldGrid = pGrid->Clone();


   while (true)
   {
      int count=0;
      for (int i=0;i<height;i++)
      {
         for (int j=0;j<width;j++)
         {
            int c = pOldGrid->GetValue( j, i );
            if(c==0)
            {
               if(Phase1(i,j, pNewGrid, pOldGrid))
                  count++;
            }
         }
      }

      delete pOldGrid;
      pOldGrid = pNewGrid->Clone();
      if (count==0)
      {
         break;
      }

      count=0;
      for (int i=0;i<height;i++)
      {
         for (int j=0;j<width;j++)
         {
            int c = pOldGrid->GetValue( j, i );
            if(c==0)
            {
               if(Phase2(i,j, pNewGrid, pOldGrid) )
                  count++;
            }
         }
      }
      delete pOldGrid;
      pOldGrid = pNewGrid->Clone();

      if (count==0)
      {
         break;
      }
   }
   delete pNewGrid;
   return pOldGrid;
}

Cell::Cell(int i, int j, ArrayGrid<int>* pGridR ):Bpz(0),Apz(0)
{
   int width = pGridR->GetWidth();
   int height = pGridR->GetHeight();
   matrix = new bool [8];

   int y,x;
   y = i-1;
   x = j-1;
   if (y<0 || x <0)
   {
      matrix[7] = false;
   }
   else
   {
      int c= pGridR->GetValue( x, y );
      if(c==0)
      {
         matrix[7] = true;
      }
      else
      {
         matrix[7] = false;
      }
   }

   y = i-1;
   x = j;
   if (y<0)
   {
      matrix[0] = false;
   }
   else
   {
      int c= pGridR->GetValue( x, y );
      if(c==0)
      {
         matrix[0] = true;
      }
      else
      {
         matrix[0] = false;
      }
   }

   y = i-1;
   x = j+1;
   if (y<0|| x >= width)
   {
      matrix[1] = false;
   }
   else
   {
      int c= pGridR->GetValue( x, y );
      if(c==0)
      {
         matrix[1] = true;
      }
      else
      {
         matrix[1] = false;
      }
   }

   y = i;
   x = j+1;
   if (x >= width)
   {
      matrix[2] = false;
   }
   else
   {
      int c= pGridR->GetValue( x, y );
      if(c==0)
      {
         matrix[2] = true;
      }
      else
      {
         matrix[2] = false;
      }
   }

   y = i+1;
   x = j+1;
   if (y>=height || x >=width)
   {
      matrix[3] = false;
   }
   else
   {
      int c= pGridR->GetValue( x, y );
      if(c==0)
      {
         matrix[3] = true;
      }
      else
      {
         matrix[3] = false;
      }
   }

   y = i+1;
   x = j;
   if (y>=height)
   {
      matrix[4] = false;
   }
   else
   {
      int c= pGridR->GetValue( x, y );
      if(c==0)
      {
         matrix[4] = true;
      }
      else
      {
         matrix[4] = false;
      }
   }

   y = i+1;
   x = j-1;
   if (y>=height || x<0)
   {
      matrix[5] = false;
   }
   else
   {
      int c= pGridR->GetValue( x, y );
      if(c==0)
      {
         matrix[5] = true;
      }
      else
      {
         matrix[5] = false;
      }
   }

   y = i;
   x = j-1;
   if (x<0)
   {
      matrix[6] = false;
   }
   else
   {
      int c= pGridR->GetValue( x, y );
      if(c==0)
      {
         matrix[6] = true;
      }
      else
      {
         matrix[6] = false;
      }
   }

   for (int i=0;i<8;i++)
   {
      if (matrix[i]==true)
      {
         Bpz++;
      }
   }

   int prev=-1;
   int next=-1;
   for (int i=1;i<=8;i++)
   {
      if (i==1)
      {
         prev=matrix[7];
      }
      // FRO: was next=matrix[i]; however, an array of 8 elements can only be addressed from 0 to 7, not 1 to 8
      next=matrix[i-1];
      if (prev==false && next==true)
      {
         Apz++;
      }
      prev=next;
   }

   C1=matrix[0]*matrix[2]*matrix[4];
   C2=matrix[0]*matrix[2]*matrix[6];

   D1=matrix[2]*matrix[4]*matrix[6];
   D2=matrix[0]*matrix[4]*matrix[6];
}


Cell::~Cell(void)
{
   delete[] matrix;
}

