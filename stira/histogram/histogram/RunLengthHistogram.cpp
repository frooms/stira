
/***********************************************************************************
 *   Copyright (C) 2012 by Filip Rooms                                             *
 *                                                                                 *
 *  Terms and conditions for using this software in any form are provided in the   *
 *  file COPYING, which can be found in the root directory of this project.        *
 *                                                                                 *
 *   Contact data: filip.rooms@gmail.com                                           *
 *                 http://www.filiprooms.be/                                       *
 *                                                                                 *
 ***********************************************************************************/

#include <iostream>
#include <algorithm>
#include "RunLengthHistogram.h"
#include "../../image/tools/NumberGridTools.h"

using namespace image;

using namespace std;
using namespace stira::common;

namespace stira {
namespace histogram {


bool MySegmentSortPredicate(const CurveSegment& d1, const CurveSegment& d2)
{
  return d1.length > d2.length;
}

//-------------------------------------------------------------------------------

RunLengthHistogram::RunLengthHistogram( int maxWidth, int maxLengthHistogram )
{
   mMaxWidth = maxWidth;
   mMaxLengthHistogram = maxLengthHistogram;

   mvvHistogram2D.resize( maxWidth );

   for (int i = 0; i < maxWidth; ++i)
   {
      mvvHistogram2D[i].resize( maxLengthHistogram );
   }

   Initialize( );
}

//-------------------------------------------------------------------------------

RunLengthHistogram::RunLengthHistogram( const RunLengthHistogram& runLengthHistogram )
{
   /*mMaxWidth = */runLengthHistogram.GetMaxValue();
   /*mMaxLengthHistogram = */runLengthHistogram.GetMaxLengthInHistogram();
   /*mvvWidthLengthHistogram = */runLengthHistogram.GetWidthLengthHistogram();
   /*mvvHistogram2D = */runLengthHistogram.GetHistogram2D();
   /*mvCurrentWidthVector = */runLengthHistogram.GetCurrentWidthVector();
   /*mvSegmentStartPointVector = */runLengthHistogram.GetSegmentStartPointVector();
}

//-------------------------------------------------------------------------------

RunLengthHistogram* RunLengthHistogram::Clone( )
{
   return new RunLengthHistogram(*this);
}

//-------------------------------------------------------------------------------

int RunLengthHistogram::GetMaxValue() const
{
   return mMaxWidth;
}

//-------------------------------------------------------------------------------

int RunLengthHistogram::GetMaxLengthInHistogram() const
{
   return mMaxLengthHistogram;
}

//-------------------------------------------------------------------------------

std::vector< std::vector< CurveSegment > > RunLengthHistogram::GetWidthLengthHistogram() const
{
   return mvvWidthLengthHistogram;
}

//-------------------------------------------------------------------------------

std::vector< std::vector<double> > RunLengthHistogram::GetHistogram2D() const
{
   return mvvHistogram2D;
}

//-------------------------------------------------------------------------------

std::vector< CurveSegment > RunLengthHistogram::GetCurrentWidthVector() const
{
   return mvCurrentWidthVector;
}

//-------------------------------------------------------------------------------
std::vector< common::Point<int> > RunLengthHistogram::GetSegmentStartPointVector() const
{
   return mvSegmentStartPointVector;
}

//-------------------------------------------------------------------------------

bool RunLengthHistogram::Analyse( std::vector<int> vYarnWidths, int startIndex )
{
   int curveLength = vYarnWidths.size();

   int lastWidth = vYarnWidths[startIndex];

   for (int i = 0; i < mMaxWidth; i++)
   {
      mvCurrentWidthVector[i].startX = startIndex;
   }

   lastWidth = MathUtils::ClipValue(lastWidth, 0, mMaxWidth - 1 );
   for (int i = 0; i <= lastWidth; i++)
   {
      mvCurrentWidthVector[i].length++;
   }

   if ( lastWidth > mMaxWidth-1 ) {lastWidth = mMaxWidth-1;}  // clip to avoid segmentation faults

   // go over yarn length
   for (int x = startIndex+1; x < curveLength; x++)
   {
      int currentWidth = vYarnWidths[x];
      if ( currentWidth > mMaxWidth-1 ) { currentWidth = mMaxWidth - 1; }  // clip to avoid segmentation faults

      if (currentWidth > lastWidth)  // some segment ends; store these in the histogram
      {
         for (int w = lastWidth+1; w <= currentWidth; w++)
         {
            mvCurrentWidthVector[w].startX = x;
         }
      }

      for (int i = 0; i <= currentWidth; i++)
      {
         mvCurrentWidthVector[i].length++;
      }

      if (lastWidth > currentWidth)  // some segment ends; store these in the histogram
      {
         for (int w = lastWidth; w > currentWidth; w--)
         {
            mvvWidthLengthHistogram[w].push_back( mvCurrentWidthVector[w] );
         }
      }

      // reset values for these terminated segments
      for (int i = currentWidth+1; i < mMaxWidth; i++)
      {
         mvCurrentWidthVector[i].startX = x+1;
         mvCurrentWidthVector[i].length = 0;
      }

      lastWidth = currentWidth;
   }

   // At end of image: terminate all still open segments
   for (int w = lastWidth; w > 0; w--)
   {
      mvvWidthLengthHistogram[w].push_back( mvCurrentWidthVector[w] );
   }

   // now from the list of segments, build the actual Runlength histogram
   for (int w = 1; w < mMaxWidth; w++)
   {
      std::vector< CurveSegment > vSegments = GetSegmentsWithWidth( w );
      for (unsigned int i = 0; i < vSegments.size(); i++)
      {
         if ( vSegments[i].length > mMaxLengthHistogram-1 )
         {
            int weight = vSegments[i].length / mMaxLengthHistogram-1;
            mvvHistogram2D[w][mMaxLengthHistogram-1] += weight;
         }
         else
         {
            mvvHistogram2D[w][vSegments[i].length] ++;
         }
      }
   }

   return true;
}

//-------------------------------------------------------------------------------

std::vector< CurveSegment > RunLengthHistogram::GetSegmentsWithWidth( int width )
{
   return mvvWidthLengthHistogram[width];
}

//-------------------------------------------------------------------------------

std::vector< CurveSegment > RunLengthHistogram::GetSegmentsWithGivenWidthOfGivenLength( int width, int length )
{
   std::vector< CurveSegment > selectedWidthSegments = mvvWidthLengthHistogram[width];

   int nrSegments = selectedWidthSegments.size();

   std::vector< CurveSegment > selectedWidthSegmentsWithLength;

   for (int i = 0; i < nrSegments; i++)
   {
      if ( selectedWidthSegments[i].length == length )
      {
         selectedWidthSegmentsWithLength.push_back( selectedWidthSegments[i] );
      }
   }
   return selectedWidthSegmentsWithLength;
}

//-------------------------------------------------------------------------------

std::vector< CurveSegment > RunLengthHistogram::GetLongestSegmentsWithGivenWidth( int width, unsigned int nrSegments )
{
   std::vector< CurveSegment > allSegments = GetSegmentsWithWidth( width );

   std::sort( allSegments.begin(), allSegments.end(), MySegmentSortPredicate );
   std::vector< CurveSegment > selectedSegments;
   if ( nrSegments > allSegments.size() ) {nrSegments = allSegments.size();}

   for ( unsigned int i = 0; i < nrSegments; i++ )
   {
      selectedSegments.push_back( allSegments[i] );
   }
   return selectedSegments;
}

//-------------------------------------------------------------------------------

int RunLengthHistogram::CountSegmentsWithGivenWidthOfGivenLength( int width, int length )
{
   std::vector< CurveSegment > selectedWidthSegmentsWithLength = GetSegmentsWithGivenWidthOfGivenLength( width, length );
   return selectedWidthSegmentsWithLength.size();
}

//-------------------------------------------------------------------------------

void RunLengthHistogram::WriteSegments( std::string fileName, int index )
{
   ofstream ofp;
   ofp.open(const_cast<char*>( fileName.c_str()), ios::out );

   if (!ofp)
   {
      cerr << "Can't open file: " << fileName << endl;
      return;
   }

   ofp << "File nr " << index << endl << endl;

   for (int w = 1; w < mMaxWidth; w++)
   {
      std::vector< CurveSegment > vSegments = GetSegmentsWithWidth( w );
      ofp << "For width " << w << endl;
      for (unsigned int i = 0; i < vSegments.size(); i++)
      {
         ofp << "\t start " << vSegments[i].startX << "\t and length " << vSegments[i].length << endl;
      }
   }

   ofp.close();
}

//-------------------------------------------------------------------------------

double RunLengthHistogram::ComputeEntropy()
{
   double myHistTotal = 0.0;

   // norm the run length histogram
   for (int w = 1; w < mMaxWidth; w++)
   {
      for (int l = 0; l < mMaxLengthHistogram; l++)
      {
         myHistTotal += mvvHistogram2D[ w ][ l ];
      }
   }

   double myEntropy = 0.0;
   // normalize and compute entropy, ignoring zero values
   for (int w = 1; w < mMaxWidth; w++)
   {
      for (int l = 0; l < mMaxLengthHistogram; l++)
      {
         if ( mvvHistogram2D[ w ][ l ] > 0.0 )
         {
            double tmpValue = mvvHistogram2D[ w ][ l ] /= myHistTotal;
            myEntropy -= ( tmpValue * log( tmpValue ) );
         }
      }
   }
   return myEntropy;
}
//-------------------------------------------------------------------------------

void RunLengthHistogram::WriteHistogram( std::string fileName, int index )
{
   ofstream ofp;
   ofp.open(const_cast<char*>( fileName.c_str()), ios::out );

   if (!ofp)
   {
      cerr << "Can't open file: " << fileName << endl;
      return;
   }

   ofp << "File nr " << index << endl << endl;

   for (int w = 1; w < mMaxWidth; w++)
   {
      for (int l = 0; l < mMaxLengthHistogram; l++)
      {
         ofp << "\t" << mvvHistogram2D[ w ][ l ];
      }
      ofp << endl;
   }

   ofp.close();
}

//-------------------------------------------------------------------------------

void RunLengthHistogram::Initialize( )
{
   Point<int> pt( 0, 0 );
   CurveSegment cs;
   cs.startX = 0;
   cs.length = 0;

   for (int i = 0; i < mMaxWidth; i++)
   {
      mvvWidthLengthHistogram.push_back( std::vector< CurveSegment >()); // Add an empty row
      mvCurrentWidthVector.push_back( cs );
      mvSegmentStartPointVector.push_back( pt );
   }
}

//-------------------------------------------------------------------------------

}
}
