
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

#include <QMessageBox>
#include "ProcessManager.h"
#include "MainWindow.h"

#include "../../stira/imagetools/tools/ImageTools.h"
#include "../dialogs/SimulateNoiseDialog.h"
#include "../dialogs/SimpleImageFilterDialog.h"
#include "../dialogs/LogGaborFilterDialog.h"
#include "../dialogs/AnisotropicDiffusionDialog.h"
#include "../dialogs/WatershedDialog.h"
#include "../dialogs/HoughTransformDialog.h"
#include "../dialogs/WienerDeconvolveDialog.h"
#include "../dialogs/RichardsonLucyDeconvolveDialog.h"
#include "../dialogs/GNCDeconvolveDialog.h"
#include "../dialogs/CannyDialog.h"
#include "../dialogs/ContrastEnhanceDialog.h"
#include "../dialogs/SplitBregmanDenoiseDialog.h"
#include "../dialogs/SteerableDenoisingDialog.h"
#include "../dialogs/SplitColorChannelsDialog.h"
#include "../curveplotter/ShowHistogramDialog.h"
#include "../curveplotter/ShowRadiallyAveragedFourierSpectrumDialog.h"

#include "../../stira/common/common/Point.h"
#include "../../stira/common/common/RectangularROI.h"
#include "../../stira/imagedata/simpletools/GridStatistics.h"
#include "../../stira/imagedata/datastructures/Image.h"
#include "../../stira/imagetools/tools/NumberGridTools.h"
#include "../../stira/imagetools/colortools/ColorBalancer.h"
#include "../../stira/fouriertools/fouriertools/FFT.h"
#include "../../stira/contrastenhance/contrastenhance/HistogramTools.h"
#include "../../stira/steerable/freemanadelson/ComputeSteerableFilteredImages.h"
#include "../../stira/imageanalysis/imageanalysis/HOG.h"

using namespace std;
using namespace stira::common;
using namespace stira::image;
using namespace stira::imageanalysis;
using namespace stira::steerable;

//==========================================================

ProcessManager::ProcessManager( stira::image::Image* pImage )
{
   mpImage = pImage;
   CreateActions();
   CreateMenus( );
}

//==========================================================

ProcessManager::~ProcessManager()
{
}

//==========================================================

void ProcessManager::SetImage( stira::image::Image* pImage )
{
   mpImage = pImage;
}

//==========================================================

std::vector<QMenu*> ProcessManager::GetMenus()
{
   return mvSubMenus;
}

//==========================================================

void ProcessManager::CreateMenus( )
{
   // FILTER
   /////////////
   mpSubMenuNoiseFilterProcess = new QMenu( tr ( "&Noise / Filter" ), 0);
   mpSubMenuNoiseFilterProcess->addAction ( mpSimulateNoiseAction );
   mpSubMenuNoiseFilterProcess->addAction ( mpLogGaborFilterAction );
   mpSubMenuNoiseFilterProcess->addAction ( mpSimpleFilterAction );
   mpSubMenuNoiseFilterProcess->addAction ( mpDiffusionAction );
   mpSubMenuNoiseFilterProcess->addAction ( mpSplitBregmanDenoiseAction );
   mpSubMenuNoiseFilterProcess->addAction ( mpWienerDeconvolveAction );
   mpSubMenuNoiseFilterProcess->addAction ( mpRichardsonLucyDeconvolveAction );
   mpSubMenuNoiseFilterProcess->addAction ( mpGNCDeconvolveAction );
   mpSubMenuNoiseFilterProcess->addAction ( mpSteerableDenoiseAction );
   
   mvSubMenus.push_back( mpSubMenuNoiseFilterProcess );
  
   // COLOR
   /////////////
   mpSubMenuColor = new QMenu( tr ( "&Color / Contrast" ), 0 );
   mpSubMenuColor->addAction ( mpContrastEnhanceAction );
   mpSubMenuColor->addAction ( mpSplitChannelsAction );
   mpSubMenuColor->addAction ( mpApplyJetColorMapAction );
   mpSubMenuColor->addAction ( mpConvertToGrayAction );
   mpSubMenuColor->addAction ( mpConvertToSepiaAction );
   mpSubMenuColor->addAction ( mpColorBalanceAction );
   
   mvSubMenus.push_back( mpSubMenuColor );
   
   // PROPERTIES / ANALYSIS
   ////////////////////////
   mpSubMenuProperties = new QMenu( tr ( "&Analysis / Properties" ), 0 );
   mpSubMenuProperties->addAction ( mpShowHistogramAction );
   mpSubMenuProperties->addAction ( mpFourierSpectrumAction );
   mpSubMenuProperties->addAction ( mpRadiallyAveragedFourierSpectrumAction );
   mpSubMenuProperties->addAction ( mpShowImagePropertiesAction );
   mpSubMenuProperties->addAction ( mpWatershedAction );
   mpSubMenuProperties->addAction ( mpHoughTransformAction );
   mpSubMenuProperties->addAction ( mpCannyAction );
   mpSubMenuProperties->addAction ( mpOrientationAnalysisAction );
   mpSubMenuProperties->addAction ( mpHistogramOrientedGradientsAction );
   
   mvSubMenus.push_back( mpSubMenuProperties );
}

//==========================================================

void ProcessManager::CreateActions()
{
   // FILTER
   ///////////
   
   mpSimulateNoiseAction = new QAction ( tr ( "&Simulate Noise" ), this );
   mpSimulateNoiseAction->setShortcut ( tr ( "Ctrl+D" ) );
   mpSimulateNoiseAction->setEnabled ( true );
   connect ( mpSimulateNoiseAction, SIGNAL ( triggered() ), this, SLOT ( SlotSelectSimulateNoise() ) );
   
   mpLogGaborFilterAction = new QAction ( tr ( "&Log Gabor Filter" ), this );
   mpLogGaborFilterAction->setShortcut ( tr ( "Ctrl+L" ) );
   mpLogGaborFilterAction->setEnabled ( true );
   connect ( mpLogGaborFilterAction, SIGNAL ( triggered() ), this, SLOT ( SlotSelectLogGaborFilter() ) );
   
   mpSimpleFilterAction = new QAction ( tr ( "&Simple Filter" ), this );
   mpSimpleFilterAction->setShortcut ( tr ( "Ctrl+S" ) );
   mpSimpleFilterAction->setEnabled ( true );
   connect ( mpSimpleFilterAction, SIGNAL ( triggered() ), this, SLOT ( SlotSelectSimpleFilter() ) );

   mpDiffusionAction = new QAction ( tr ( "&Anisotropic Diffusion" ), this );
   mpDiffusionAction->setShortcut ( tr ( "Ctrl+A" ) );
   mpDiffusionAction->setEnabled ( true );
   connect ( mpDiffusionAction, SIGNAL ( triggered() ), this, SLOT ( SlotSelectAnisotropicDiffusion() ) );

   mpSplitBregmanDenoiseAction = new QAction ( tr ( "&Split-Bregman TV Denoise" ), this );
   mpSplitBregmanDenoiseAction->setShortcut ( tr ( "Ctrl+A" ) );
   mpSplitBregmanDenoiseAction->setEnabled ( true );
   connect ( mpSplitBregmanDenoiseAction, SIGNAL ( triggered() ), this, SLOT ( SlotSelectSplitBregmanDenoise() ) );
   
   mpWienerDeconvolveAction = new QAction ( tr ( "&Wiener Deconvolution" ), this );
   mpWienerDeconvolveAction->setShortcut ( tr ( "Ctrl+W" ) );
   mpWienerDeconvolveAction->setEnabled ( true );
   connect ( mpWienerDeconvolveAction, SIGNAL ( triggered() ), this, SLOT ( SlotSelectWienerDeconvolve() ) );

   mpRichardsonLucyDeconvolveAction = new QAction ( tr ( "&Richardson-Lucy Deconvolution" ), this );
   mpRichardsonLucyDeconvolveAction->setShortcut ( tr ( "Ctrl+R" ) );
   mpRichardsonLucyDeconvolveAction->setEnabled ( true );
   connect ( mpRichardsonLucyDeconvolveAction, SIGNAL ( triggered() ), this, SLOT ( SlotSelectRichardsonLucyDeconvolve() ) );

   mpGNCDeconvolveAction = new QAction ( tr ( "&GNC-based Deconvolution" ), this );
   mpGNCDeconvolveAction->setShortcut ( tr ( "Ctrl+G" ) );
   mpGNCDeconvolveAction->setEnabled ( true );
   connect ( mpGNCDeconvolveAction, SIGNAL ( triggered() ), this, SLOT ( SlotSelectGNCDeconvolve() ) );

   mpSteerableDenoiseAction = new QAction ( tr ( "&Steerable Denoising" ), this );
   mpSteerableDenoiseAction->setShortcut ( tr ( "Ctrl+D" ) );
   mpSteerableDenoiseAction->setEnabled ( true );
   connect ( mpSteerableDenoiseAction, SIGNAL ( triggered() ), this, SLOT ( SlotSelectSteerableDenoise() ) );

   // COLOR
   ///////////
   mpApplyJetColorMapAction = new QAction ( tr ( "Apply Jet Colormap" ), this );
   mpApplyJetColorMapAction->setShortcut ( tr ( "Ctrl+J") );
   mpApplyJetColorMapAction->setEnabled ( true );
   connect ( mpApplyJetColorMapAction, SIGNAL ( triggered() ), this, SLOT ( SlotApplyJetColorMap() ) );
   
   mpSplitChannelsAction = new QAction ( tr ( "Split Color Channels"), this ); 
   mpSplitChannelsAction->setShortcut ( tr ( "Ctrl+A") );
   connect ( mpSplitChannelsAction, SIGNAL ( triggered() ), this, SLOT ( SlotSplitChannels() ) );
  
   mpConvertToGrayAction = new QAction ( tr ( "&Convert To Gray" ), this );
   mpConvertToGrayAction->setEnabled ( true );
   connect ( mpConvertToGrayAction, SIGNAL ( triggered() ), this, SLOT ( SlotConvertToGray() ) );
  
   mpConvertToSepiaAction = new QAction ( tr ( "&Convert To Sepia" ), this );
   mpConvertToSepiaAction->setEnabled ( true );
   connect ( mpConvertToSepiaAction, SIGNAL ( triggered() ), this, SLOT ( SlotConvertToSepia() ) );
  
   mpColorBalanceAction = new QAction ( tr ( "&Balance Colors" ), this );
   mpColorBalanceAction->setEnabled ( true );
   connect ( mpColorBalanceAction, SIGNAL ( triggered() ), this, SLOT ( SlotColorBalance() ) );
   
   // CONTRAST
   /////////////

   mpContrastEnhanceAction = new QAction ( tr ( "Contrast &Enhance" ), this );
   mpContrastEnhanceAction->setShortcut ( tr ( "Ctrl+E" ) );
   mpContrastEnhanceAction->setEnabled ( true );
   connect ( mpContrastEnhanceAction, SIGNAL ( triggered() ), this, SLOT ( SlotSelectContrastEnhance() ));
   
   // PROPERTIES / ANALYSIS
   /////////////////////////
   
   mpShowHistogramAction = new QAction ( tr ( "&Plot Histogram" ), this );
   mpShowHistogramAction->setShortcut ( tr ( "Ctrl+H" ) );
   mpShowHistogramAction->setEnabled ( true );
   connect ( mpShowHistogramAction, SIGNAL ( triggered() ), this, SLOT ( SlotShowHistogram() ) );

   mpFourierSpectrumAction = new QAction ( tr ( "&Fourier Spectrum" ), this );
   mpFourierSpectrumAction->setShortcut ( tr ( "Ctrl+F" ) );
   mpFourierSpectrumAction->setEnabled ( true );
   connect ( mpFourierSpectrumAction, SIGNAL ( triggered() ), this, SLOT ( SlotSelectCreateFourierSpectrum() ) );
   
   mpRadiallyAveragedFourierSpectrumAction = new QAction ( tr ( "&Radially Averaged Fourier Spectrum" ), this );
   mpRadiallyAveragedFourierSpectrumAction->setShortcut ( tr ( "Ctrl+R" ) );
   mpRadiallyAveragedFourierSpectrumAction->setEnabled ( true );
   connect ( mpRadiallyAveragedFourierSpectrumAction, SIGNAL ( triggered() ), this, SLOT ( SlotRadiallyAveragedFourierSpectrum() ) );
   
   mpShowImagePropertiesAction = new QAction ( tr ( "&Show Image Properties" ), this );
   mpShowImagePropertiesAction->setEnabled ( true );
   connect ( mpShowImagePropertiesAction, SIGNAL ( triggered() ), this, SLOT ( SlotImageProperties() ) );

   mpWatershedAction = new QAction ( tr ( "&Watershed" ), this );
   mpWatershedAction->setShortcut ( tr ( "Ctrl+W" ) );
   mpWatershedAction->setEnabled ( true );
   connect ( mpWatershedAction, SIGNAL ( triggered() ), this, SLOT ( SlotSelectWatershedMeyer() ) );

   mpHoughTransformAction = new QAction ( tr ( "&HoughTransform" ), this );
   mpHoughTransformAction->setShortcut ( tr ( "Ctrl+H" ) );
   mpHoughTransformAction->setEnabled ( true );
   connect ( mpHoughTransformAction, SIGNAL ( triggered() ), this, SLOT ( SlotSelectHoughTransform() ) );

   mpCannyAction = new QAction ( tr ( "&Canny Edge Detect" ), this );
   mpCannyAction->setShortcut ( tr ( "Ctrl+C" ) );
   mpCannyAction->setEnabled ( true );
   connect ( mpCannyAction, SIGNAL ( triggered() ), this, SLOT ( SlotSelectCannyEdgeDetect() ) );

   mpOrientationAnalysisAction = new QAction ( tr ( "&Analyse Orientations" ), this );
   mpOrientationAnalysisAction->setEnabled ( true );
   connect ( mpOrientationAnalysisAction, SIGNAL ( triggered() ), this, SLOT ( SlotAnalyseOrientations() ) );

   mpHistogramOrientedGradientsAction = new QAction ( tr ( "&Histogram of Oriented Gradients" ), this );
   mpHistogramOrientedGradientsAction->setEnabled ( true );
   connect ( mpHistogramOrientedGradientsAction, SIGNAL ( triggered() ), this, SLOT ( SlotHistogramOrientedGradients() ) );
}

//------------------------------------------------------------------

void ProcessManager::SlotSelectAnisotropicDiffusion()
{
   mpAnisotropicDiffusionDialog = new AnisotropicDiffusionDialog( mpImage );
}

//------------------------------------------------------------------

void ProcessManager::SlotSelectSplitBregmanDenoise()
{
   mpSplitBregmanDenoiseDialog = new SplitBregmanDenoiseDialog( mpImage );
}

//------------------------------------------------------------------

void ProcessManager::SlotSelectWatershedMeyer()
{
   mpWatershedDialog = new WatershedDialog ( mpImage );
   mpWatershedDialog->show();
}

//------------------------------------------------------------------

void ProcessManager::SlotSelectHoughTransform()
{
   mpHoughTransformDialog = new HoughTransformDialog ( mpImage );
   mpHoughTransformDialog->show();
}

//------------------------------------------------------------------

void ProcessManager::SlotSelectCreateFourierSpectrum()
{
   stira::fouriertools::FFT myFft;
  
   int nrBands = mpImage->GetNumberOfBands();
   int width   = mpImage->GetWidth();
   int height  = mpImage->GetWidth();
   
   Image* pImageOut = new Image( width, height );
   for (int i = 0; i < nrBands; i++)
   {
      ArrayGrid<double>* pSpectrumGrid = myFft.ComputeLogPowerSpectrum ( mpImage->GetBands() [i] );
      pImageOut->AddBand( pSpectrumGrid );
   }
   std::string outName = mpImage->GetImageName() + std::string("-FourierSpectrum");
   pImageOut->SetImageName(outName);

   ImageDataList::GetInstance()->AddImage( pImageOut );
}

//------------------------------------------------------------------

void ProcessManager::SlotApplyJetColorMap()
{
   if ( mpImage->GetNumberOfBands() == 1 )
   {
      Image* pImageOut = ImageTools::ApplyJetColorMap( mpImage );

      ImageDataList::GetInstance()->AddImage( pImageOut );
   }
   else
   {
      QMessageBox::information ( 0, tr ( "Error" ), tr ( "Jet Color map is only applicable to images with 1 band!!" ) );
   }
}

//------------------------------------------------------------------

void ProcessManager::SlotSelectContrastEnhance()
{
   mpContrastEnhanceDialog = new ContrastEnhanceDialog( mpImage );
}

//------------------------------------------------------------------

void ProcessManager::SlotSelectWienerDeconvolve()
{
   mpWienerDeconvolveDialog = new WienerDeconvolveDialog ( mpImage );
   mpWienerDeconvolveDialog->show();
}

//------------------------------------------------------------------

void ProcessManager::SlotSelectRichardsonLucyDeconvolve()
{
   mpRichardsonLucyDeconvolveDialog = new RichardsonLucyDeconvolveDialog ( mpImage );
   mpRichardsonLucyDeconvolveDialog->show();
}

//------------------------------------------------------------------

void ProcessManager::SlotSelectCannyEdgeDetect()
{
   mpCannyDialog = new CannyDialog( mpImage );
   mpCannyDialog->show();
}

//------------------------------------------------------------------

void ProcessManager::SlotSelectSteerableDenoise()
{
   mpSteerableDenoisingDialog = new SteerableDenoisingDialog( mpImage );
   mpSteerableDenoisingDialog->show();
}

//------------------------------------------------------------------

void ProcessManager::SlotSelectSimpleFilter()
{
   mpSimpleImageFilterDialog = new SimpleImageFilterDialog( mpImage );
   mpSimpleImageFilterDialog->show();
}

//------------------------------------------------------------------

void ProcessManager::SlotSelectSimulateNoise()
{
   mpSimulateNoiseDialog = new SimulateNoiseDialog( mpImage );
   mpSimulateNoiseDialog->show();
}

//------------------------------------------------------------------

void ProcessManager::SlotShowHistogram()
{
   mpShowHistogramDialog = new ShowHistogramDialog( mpImage );
   mpShowHistogramDialog->show();
}

//------------------------------------------------------------------

void ProcessManager::SlotRadiallyAveragedFourierSpectrum()
{
   mpShowRadiallyAveragedFourierSpectrumDialog = new ShowRadiallyAveragedFourierSpectrumDialog( mpImage );
   mpShowRadiallyAveragedFourierSpectrumDialog->show();
}

//------------------------------------------------------------------

void ProcessManager::SlotConvertToGray()
{
   Image* pImageOut = ImageTools::ConvertToGrayImage( mpImage );

   ImageDataList::GetInstance()->AddImage( pImageOut );
}

//------------------------------------------------------------------

void ProcessManager::SlotImageProperties()
{
   QDialog*     pDialog = new QDialog( 0, Qt::WindowStaysOnTopHint );
   QVBoxLayout* pLayout = new QVBoxLayout( pDialog );
   QLabel*  pTitleLabel = new QLabel( QString("<B>Image properties</B> "), 0 );
   std::string imageName = mpImage->GetImageName();
   QLabel* pNameLabel       = new QLabel( QString("Name: %1 " ).arg( imageName.c_str() ), 0 );
   QLabel* pDimensionsLabel = new QLabel( QString("width: %1 \t height: %2" ).arg( mpImage->GetWidth() ).arg( mpImage->GetHeight() ), 0 );
   int nrBands = mpImage->GetNumberOfBands();
   QLabel* pNrBandsLabel    = new QLabel( QString("Nr. bands: %1 " ).arg( nrBands ), 0 );

   pLayout->addWidget( pTitleLabel );
   pLayout->addWidget( pNameLabel );
   pLayout->addWidget( pDimensionsLabel );
   pLayout->addWidget( pNrBandsLabel );

   for (int i = 0; i < nrBands; i++)
   {
      double mmin, mmax;
      ArrayGrid<double>* pGrid = mpImage->GetBands()[i];
      GridStatistics<double>::GetMinMax( pGrid, mmin, mmax);
      double mean = GridStatistics<double>::GetGridMean( pGrid );
      double var  = GridStatistics<double>::GetGridVariance( pGrid, mean);

      QLabel* pMinMaxLabel = new QLabel( QString("\t Band nr.: %1 \t min = %2 \t max = %3 \t mean = %4 \t variance = %5" ).arg( i ).arg( mmin ).arg( mmax ).arg( mean ).arg( var ), 0 );
      pLayout->addWidget( pMinMaxLabel );
   }

   pDialog->show();
}

//------------------------------------------------------------------

void ProcessManager::SlotColorBalance()
{
   if ( mpImage->GetNumberOfBands() == 3)
   {
      Image* pImageOut = ColorBalancer::RunBalance( mpImage );
      
      Image* pImageOutScaled = stira::contrastenhance::HistogramTools::RobustLinearRescale( pImageOut, 0.03, 0.99 );
      delete pImageOut;
      ImageDataList::GetInstance()->AddImage( pImageOutScaled );
   }
   else
   {
      QMessageBox::information ( 0, tr ( "Error" ), tr ( "Need image with three bands for color balancing!!" ) );
   }
}

//------------------------------------------------------------------

void ProcessManager::SlotSelectLogGaborFilter()
{
   mpLogGaborFilterDialog = new LogGaborFilterDialog( mpImage );
   mpLogGaborFilterDialog->show();
}

//------------------------------------------------------------------

void ProcessManager::SlotSelectGNCDeconvolve()
{
   mpGNCDeconvolveDialog = new GNCDeconvolveDialog( mpImage );
   mpGNCDeconvolveDialog->show();
}

//------------------------------------------------------------------

void ProcessManager::SlotConvertToSepia()
{
   Image* pImageOut = ImageTools::ConvertToSepiaImage( mpImage );
   ImageDataList::GetInstance()->AddImage( pImageOut );
}

//------------------------------------------------------------------

void ProcessManager::SlotSplitChannels()
{
   mpSplitColorChannelsDialog = new SplitColorChannelsDialog( mpImage );
   mpSplitColorChannelsDialog->show();
}

//------------------------------------------------------------------

void ProcessManager::SlotAnalyseOrientations()
{
   ComputeSteerableFilteredImages csfi( mpImage->GetBands()[0] );
   csfi.Run();
   OrientationGrid* pGrid = csfi.GetOrientationGrid( );   // csfi is respon
   ImageDataList::GetInstance()->AddImage( pGrid->VisualizeOrientationImage( 5 ) );  // ownership of this image is transfered through GetImage() to ImageDataList
   ImageDataList::GetInstance()->AddImage( pGrid->VisualizeMagnitudeImage( ) );  // ownership of this image is transfered through GetImage() to ImageDataList
   delete pGrid;
}

//------------------------------------------------------------------

void ProcessManager::SlotHistogramOrientedGradients()
{
    int nrBins = 9;
    int cellWidth = 8;
    int cellHeight = 8;
    double viz_factor = 3;
    double scaleFactor = 1.0;

    std::vector<double> descriptorValues;

    RectangularROI<int> myRoi( 0, 0, mpImage->GetWidth() - 1, mpImage->GetHeight() - 1 );
    HOG myHOG( mpImage, myRoi, cellWidth, cellHeight, nrBins);

    myHOG.ComputeHogDescriptor( descriptorValues );

    Image* pVisual = myHOG.VisualizeHogDescriptor( descriptorValues,
                                                   mpImage->GetWidth(), mpImage->GetHeight(),
                                                   scaleFactor, viz_factor);

    ImageDataList::GetInstance()->AddImage( pVisual );  // ownership of this image is transfered through GetImage() to ImageDataList
}

//------------------------------------------------------------------

