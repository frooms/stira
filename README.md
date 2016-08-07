
/***************************************************************************************
 *   Copyright (C) 2008-2016 by Filip Rooms                                            *
 *                                                                                     *
 *  Terms and conditions for using this software in any form are provided in the       *
 *  file COPYING, which can be found in the root directory of this project.            *
 *                                                                                     *
 *   Contact data: filip.rooms@gmail.com                                               *
 *                 http://www.filiprooms.be/                                           *
 *                                                                                     *
 ***************************************************************************************

1. What: STIRA: Simple Toolkit for Image Restoration and Analysis
=================================================================

This is a project I wrote during my years at Ghent University and after that. The kit is written in C++, 
using Qt for the project files and QtCreator as IDE. The code aND PROJECTS are written to be run on Linux.

It consists of two parts, reflected by two subdirs in the repository:
- stira: the toolkit itself that consists of the data structures, algorithms and command line test programs. 
         This part uses Qt only for the project organization and the build system
- gui:   a GUI that brings some of teh functionalities of stira in a GUI. Here Qt libraries and classes are 
         actually used

2. Project structure
====================

The projects are organized using the Qt qmake project files. These files have extension .pro.
Using the qmake command from Qt, the actual makefile are generated. Personally, I load the pro file called 
stiraMain.pro in the IDE from Qt, called Qt Creator. This will load all projects and subprojects and their 
dependencies in Qt Creator, ready for building.

Make sure you first install the necessary dependencies. All dependencies are available in the Ubuntu software 
repositories. Myself, I just installed them using synaptic (but of course using apt-get on the command line 
is equivalent).
  
Please read stira/README for more details on the toolkit itself

3. External dependencies
========================
 * OpenCV Open Source Computer Vision 2.0.0 (to check version: see /usr/include/opencv/cvver.h)
    - Availability: http://opencv.willowgarage.com/wiki/ or in a standard linux distro repository
    - Used by 
       - common/FitCurve for polynomial fitting
       - common/ClusteringLearning for PCA
       - image/ImageIO for reading and writing different image file formats

 * FFTW3 Fastest Fourier Transform in the West 
    - Availability: http://www.fftw.org or in a standard linux distro repository
    - Dependency can be removed, and code is then based on integrated KISS-FFT (see above)
    - Used by subprojects "fouriertools", "filter" and all other subprojects that depend on that

GUI
 * on Qt of course (uses version 4.X)
 * also on QWT: Qt Widgets for Technical Applications
    - http://qwt.sourceforge.net/

4. Acknowledgements
===================
All support and feedback from my former colleagues of Ghent University, dept. TELIN, research group IPI, especially 
prof. Wilfried Philips

For feedback on build attempt, my Bricsys colleague Tijs Vermeulen.
