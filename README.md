# STIRA: Simple Toolkit for Image Restoration and Analysis

This is a project I wrote during my years at Ghent University and after that. The kit is written in C++, 
using Qt for the project files and QtCreator as IDE. The files are written to be run on Linux.

It consists of two parts, reflected by two subdirs in the repository:
- stira: the toolkit itself that consists of the data structures, algorithms and command line test programs. 
         This part uses Qt only for the the project organizationd and the build system
- gui:   a GUI that brings some of teh functionalities of stira in a GUI. Here Qt libraries and classes are 
         actually used 
  
Please read stira/README for more details on the toolkit itself

Dependencies
============
STIRA
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

 * also install libuuid-dev

GUI
 * on Qt of course
 * also on QWT: Qt Widgets for Technical Applications
    - http://qwt.sourceforge.net/
