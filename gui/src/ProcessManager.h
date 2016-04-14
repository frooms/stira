
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

#ifndef STIRAGUI_MAIN_PROCESSMANAGER_H
#define STIRAGUI_MAIN_PROCESSMANAGER_H

#include <map>
#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>

class SimulateNoiseDialog;
class SimpleImageFilterDialog;
class LogGaborFilterDialog;
class AnisotropicDiffusionDialog;
class WatershedDialog;
class WienerDeconvolveDialog;
class RichardsonLucyDeconvolveDialog;
class GNCDeconvolveDialog;
class CannyDialog;
class ContrastEnhanceDialog;
class SteerableDenoisingDialog;
class SplitBregmanDenoiseDialog;
class SplitColorChannelsDialog;

class ShowHistogramDialog;
class ShowRadiallyAveragedFourierSpectrumDialog;

#include "../../stira/image/datastructures/Image.h"
#include "../processes/Process.h"

/** \brief Manager to create and launch image processing processes
  * Separates the creation of processes from the ImageWindow class */
class ProcessManager : public QObject
{
    Q_OBJECT
public:

   /** \brief constructor
     * \param pImage image object on which to apply the process */
   ProcessManager( stira::image::Image* pImage );
   
   /** \brief destructor*/
   ~ProcessManager();
   
   std::vector<QMenu*> GetMenus();
   
   void SetImage( stira::image::Image* pImage );
   
private:
   
   stira::image::Image* mpImage;
   
   void CreateActions();
  
  // MENUS
  /////////
   void CreateMenus( );
   QMenu* mpSubMenuNoiseFilterProcess;
   QMenu* mpSubMenuColor;
   QMenu* mpSubMenuProperties;
   
   std::vector<QMenu*> mvSubMenus;
 
   // ENHANCE
   ///////////
      // Simulate noise
      private:
         QAction* mpSimulateNoiseAction;
         SimulateNoiseDialog* mpSimulateNoiseDialog;
      public slots:
         void SlotSelectSimulateNoise();
      
      // Log-Gabor
      private:
         QAction* mpLogGaborFilterAction;
         LogGaborFilterDialog* mpLogGaborFilterDialog;
      public slots:
         void SlotSelectLogGaborFilter();
         
      // Simple filter
      private:
         QAction* mpSimpleFilterAction;
         SimpleImageFilterDialog* mpSimpleImageFilterDialog;
      public slots:
         void SlotSelectSimpleFilter();
         
      // Anisotropic diffusion
      private:
         QAction* mpDiffusionAction;
         AnisotropicDiffusionDialog* mpAnisotropicDiffusionDialog;
      public slots:
         void SlotSelectAnisotropicDiffusion();
         
      // Split-Bregman TV Denoise
      private:
         QAction* mpSplitBregmanDenoiseAction;
         SplitBregmanDenoiseDialog* mpSplitBregmanDenoiseDialog;
      public slots:
         void SlotSelectSplitBregmanDenoise();

      // Wiener deconvolution
      private:
         QAction* mpWienerDeconvolveAction;
         WienerDeconvolveDialog* mpWienerDeconvolveDialog;
      public slots:
         void SlotSelectWienerDeconvolve();
      
      // Richardson-Lucy deconvolution
      private:
         QAction* mpRichardsonLucyDeconvolveAction;
         RichardsonLucyDeconvolveDialog* mpRichardsonLucyDeconvolveDialog;
      public slots:
         void SlotSelectRichardsonLucyDeconvolve();
         
      // GNC-based deconvolution
      private:
         QAction* mpGNCDeconvolveAction;
         GNCDeconvolveDialog* mpGNCDeconvolveDialog;
      public slots:
         void SlotSelectGNCDeconvolve();
         
      // steerable pyramid based bivariate denoise
      private:
         QAction* mpSteerableDenoiseAction;
         SteerableDenoisingDialog* mpSteerableDenoisingDialog;
      public slots:
         void SlotSelectSteerableDenoise();
   
      // Contrast enhancement techniques
      private:
         QAction* mpContrastEnhanceAction;
         ContrastEnhanceDialog* mpContrastEnhanceDialog;
      public slots:
         void SlotSelectContrastEnhance();
   
   // COLOR
   ///////////
         
      // Apply jet colormap
      private:
         QAction* mpApplyJetColorMapAction;
      public slots:
         void SlotApplyJetColorMap();
         
      // Split multiband image in separate color bands
      private:
         QAction* mpSplitChannelsAction;
         SplitColorChannelsDialog* mpSplitColorChannelsDialog;
      public slots:
         void SlotSplitChannels();
         
      // Convert multiband image to singleband gray image
      private:
         QAction* mpConvertToGrayAction;
      public slots:
         void SlotConvertToGray();
         
      // Convert image to sepia-tone image
      private:
         QAction* mpConvertToSepiaAction;
      public slots:
         void SlotConvertToSepia();
         
      // Balance colors in image
      private:
         QAction* mpColorBalanceAction;
      public slots:
         void SlotColorBalance();
   
   // PROPERTIES / ANALYSIS
   /////////////////////////

      // Create image histogram
      private:
         QAction* mpShowHistogramAction;
         ShowHistogramDialog* mpShowHistogramDialog;
      public slots:
         void SlotShowHistogram();
         
      // Create Fourier log-powerspectrum of image
      private:
         QAction* mpFourierSpectrumAction;
      public slots:
         void SlotSelectCreateFourierSpectrum();
         
      // Create graph with radially averaged Fourier log-powerspectrum of image
      private:
         QAction* mpRadiallyAveragedFourierSpectrumAction;
         ShowRadiallyAveragedFourierSpectrumDialog* mpShowRadiallyAveragedFourierSpectrumDialog;
      public slots:
         void SlotRadiallyAveragedFourierSpectrum();
         
      // Show image properties
      private:
         QAction* mpShowImagePropertiesAction;
      public slots:
         void SlotImageProperties();
      
      // Watershed segmentation
      private:
         QAction* mpWatershedAction;
      public:
         WatershedDialog* mpWatershedDialog;
      public slots:
         void SlotSelectWatershedMeyer();
   
      // Canny edge detection
      private:
         QAction* mpCannyAction;
      public:
         CannyDialog* mpCannyDialog;
      public slots:
         void SlotSelectCannyEdgeDetect();
         
      // Orientation Analysis
      private:
         QAction* mpOrientationAnalysisAction;
      public slots:
         void SlotAnalyseOrientations();

     // Histogram of Oriented Gradients
     private:
        QAction* mpHistogramOrientedGradientsAction;
     public slots:
        void SlotHistogramOrientedGradients();
};

#endif
