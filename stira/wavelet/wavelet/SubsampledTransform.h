
#include "../../image/datastructures/Image.h"
#include "Wavelet.h"

namespace stira {
namespace wavelet {

//  which is loosely based on Numerical Recipes in C
class SubsampledTransform: public Wavelet
{
public:
   /** \brief constructor 
     * \param type type of wavelet to use (see enum in waveletTabs.h) */
   SubsampledTransform( WaveletType type = DAUBECHIES_2 );
   
   /** \brief destructor */
   ~SubsampledTransform();
   
   /** \brief decomposition
     * \param pSourceGrid grid to be deomposed
     * \param nrScales nr of scales in the decomposition
     * \return true if all went well*/
   virtual bool Decompose( image::ArrayGrid<double>* pSourceGrid, int nrScales );
   
   /** \brief reconstruction
     * \param threshold hard threshold for diagnostic purposes
     * \return true if all went well*/
   virtual bool Reconstruct( double threshold = 0.0 );
   
private:
   /** \brief applies decomposition on an array of single row or column 
     * \param pArray the array to decompose */
   void Decompose1D(double* pArray );
   
   /** \brief applies reconstruction on an array of single row or column 
     * \param pArray the array to reconstruct */
   void Reconstruct1D(double* pArray );
   
   /** \brief applies the multiscale decomposition */
   void MultiscaleDecompose( );
   
  /** \brief applies the multiscale reconstruction */
    void MultiscaleReconstruct( );
   
   /** \brief rearranges coefficients after 1D decomposition
     * Lowpass and highpass coefficients are alternating after 1D decomposition
     * from LP1 - HP1 - LP2 - ... to LP1 - LP2 - ... - HP1 - HP2 - ... 
     * \param pArray the array to rearrange */
   void Permute( double* pArray );
   
   /** \brief rearranges coefficients back for 1D reconstruction
     * from LP1 - LP2 - ... - HP1 - HP2 - ... to LP1 - HP1 - LP2 - ...
     * \param pArray the array to rearrange  */
   void InversePermute(double *array );
   
   /** \brief copies values from an array to a row of an ArrayGrid
     * \param pRow the array to copy the values from
     * \param pGrid the grid to copy the values to
     * \param rowNr the number of the row to write the values to */
   void CopyArrayRowToGrid( double* pRow, image::ArrayGrid<double>* pGrid, int rowNr );

   /** \brief copies values from an array to a column of an ArrayGrid
     * \param pRow the array to copy the values from
     * \param pGrid the grid to copy the values to
     * \param rowNr the number of the column to write the values to */
   void CopyArrayColumnToGrid( double* pColumn, image::ArrayGrid<double>* pGrid, int columnNr );

   /** \brief copies values from a row of an ArrayGrid to an array
     * \param pRow the array to copy the values from
     * \param pGrid the grid to copy the values to
     * \param rowNr the number of the column to write the values to */
   void CopyGridRowToArray( image::ArrayGrid<double>* pGrid, double* pRow, int rowNr );

   /** \brief copies values from a column of an ArrayGrid to an array
     * \param pRow the array to copy the values from
     * \param pGrid the grid to copy the values to
     * \param rowNr the number of the column to write the values to */
   void CopyGridColumnToArray( image::ArrayGrid<double>* pGrid, double* pColumn, int columnNr );
   
   /** \brief creates a pyramid datastructure from the grid
     * The transform was computed in-place; create pyramid for more convenient access*/
   void CreatePyramidFromGrid( );
   
   /** \brief creates a grid datastructure from the pyramid
     * Puts the pyramid data back in a grid for in-place reconstruction
     * \param threshold value of the hard threshold (for diagnostic purposes)*/
   void CreateGridFromPyramid(  double threshold=0.0 );
   
   /** \brief Copies values from one array to another 
     * \param pArrayIn array to copy the values from
     * \param pArrayOut array to copy the values to */
   void CopyArray( double* pArrayIn, double* pArrayOut );
   
   double *mpBuffer;   ///< buffer 
   int mBufferLength;  ///< size of the buffer
};

}
}
