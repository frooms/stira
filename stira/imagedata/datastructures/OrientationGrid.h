
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

#ifndef STIRA_IMAGE_DATASTRUCTURES_ORIENTATIONGRID_H
#define STIRA_IMAGE_DATASTRUCTURES_ORIENTATIONGRID_H

#include <stdint.h>
#include <iostream>
#include <stdlib.h>
#include <cmath>

#include "ArrayGrid.h"
#include "Image.h"
#include "../color/ColorValue.h"
#include "../color/TransformColorSpace.h"
#include "LocalOrientation.h"

namespace stira {
namespace image {

/** \brief A data class to hold a grid of local orientations: for each pixel, a local orientation and magnitude are kept
  * \TODO from this representation, it should be fairly easy to implement the Hough transform for different parametric
  *       models like straight lines and circles:
  *         loop over all possible values of the parameter sets for the lines to check
  *           a) based on parameters, generate parametric representation of candidate line (circle, curve)
  *           b) for all pixels along this line, check if the orientation map (direction/strength) supports
  *              the presence of this candidate
  *                     if yes, add 1 to accumulator for the given parameters
  */
class OrientationGrid
{
public:
   /** \brief enum that describes color mapping from angle to color*/
   enum ColorExportMode { EXPORT_RGB_MODE,  ///< linear interpolation in R, G and B (see ConvertAngleToRGBMap for details)
                          EXPORT_HSV_MODE  ///< angle mapped to H, (S and V are both set to 1). HSV is then converted to RGB
                        };

   /** \brief Constructor.
     * \param width width of the grid
     * \param height height of the grid*/
   OrientationGrid(int width, int height);

   /** \brief Destructor. */
   ~OrientationGrid();

   OrientationGrid* Clone();

   /** \brief Gets the width of the grid */
   int GetWidth();

   /** \brief Gets the height of the grid */
   int GetHeight();

   /** \brief Sets the local angle at specified position of the grid
     * \param x the x coordinate
     * \param y the y coordinate
     * \param myAngle the angle to set for position (x,y) */
   void SetAngle(int x, int y, double myAngle);

   /** \brief Gets the local angle at specified position of the grid
     * \param x the x coordinate
     * \param y the y coordinate */
   double GetAngle(int x, int y);

   /** \brief Sets the local orientation (angle,magnitude) at specified position of the grid
     * \param x the x coordinate
     * \param y the y coordinate
     * \param myLocalOrientation the local orientation to set for position (x,y) */
   void SetOrientation(int x, int y, LocalOrientation* pLocalOrientation);

   /** \brief Gets the local orientation (angle,magnitude) at specified position of the grid
     * \param x the x coordinate
     * \param y the y coordinate */
   LocalOrientation* GetOrientation(int x, int y);

   /** \brief Sets the magnitude of the feature response at position (x, y)
     * \param x the x coordinate
     * \param y the y coordinate
     * \param myMagnitude the magnitude to set for position (x,y)*/
   void SetMagnitude(int x, int y, double myMagnitude);

   /** \brief Gets the magnitude of the feature response at position (x, y)
     * \param x the x coordinate
     * \param y the y coordinate */
   double GetMagnitude(int x, int y);

   /** \brief Gets a vector with the orientations within the specified ROI
     * \param xMin minimum x coordinate of the ROI
     * \param yMin minimum y coordinate of the ROI
     * \param xMax maximum x coordinate of the ROI
     * \param yMax maximum y coordinate of the ROI */
   std::vector<image::LocalOrientation> GetOrientationVector( int xMin, int yMin, int xMax, int yMax);

   /** \brief Gets the minimum and maximum magnitude of the features in the grid
     * \param mmin (output) the minimum magnitude
     * \param mmax (output) the maximum magnitude */
   bool GetMinMaxMagnitude( double& mmin, double& mmax );

   /** \brief extracts a grid with only edge magnitudes
     * Becomes responsability of the caller to free this newly created object*/
   ArrayGrid<double>* ExtractMagnitudeGrid();

   /** \brief creates current magnitude image ready for exporting to disk or viewing on screen*/
   Image* VisualizeMagnitudeImage( );

   /** \brief extracts a grid with only edge orientations
     * Becomes responsability of the caller to free this newly created object*/
   ArrayGrid<double>* ExtractOrientationGrid();

   /** \brief creates current orientation image ready for exporting to disk or viewing on screen
     * \param threshold threshold value for magnitude (below this, we just put black instead of coded orientation)
     * \param myMode color mapping scheme to use*/
   Image* VisualizeOrientationImage( double threshold, ColorExportMode myMode=EXPORT_HSV_MODE);

private:
   /** \brief converts currenty angle into an RGB triplet
     * This triplet is derived from the angle to HSV mapping: hue varies between 0 and 360; S and V are fixed to 1.
     * The result is converted to RGB and returned.
     * \param angle  angle to map to color triplet*/
   ColorValue ConvertAngleToHSVMap(double angle);

   /** \brief converts currenty angle into an RGB triplet
     * This triplet makes simple RGB interpolation:
     *  - Between        0 and   pi / 3, R drops from 255 to 0, and B increases from 0 to 255
     *  - Between   pi / 3 and 2 pi / 3, B drops from 255 to 0, and G increases from 0 to 255
     *  - Between 2 pi / 3 and   pi    , G drops from 255 to 0, and R increases from 0 to 255
     * \param angle  angle to map to color triplet
     */
   ColorValue ConvertAngleToRGBMap(double angle);

   ArrayGrid< LocalOrientation* >* mpOrientationGrid; ///< the arraygrid of local magnitudes and orientations
   TransformColorSpace* mpColorTransformer;
};
}
}
#endif
