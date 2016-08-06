SOURCES += main.cpp \
           ImageDataList.cpp \
           ImageWindow.cpp \
           MainWindow.cpp \
           ProcessManager.cpp \
           ClickableLabel.cpp \
           InteractiveImageWindow.cpp
HEADERS += ImageDataList.h \
           ImageWindow.h \
           MainWindow.h \
           ProcessManager.h \
           ClickableLabel.h \
           InteractiveImageWindow.h
TEMPLATE = app
CONFIG += warn_on \
          thread \
          qt \
          build_all
TARGET = ../bin/stiragui
RESOURCES = application.qrc

POST_TARGETDEPS += ../curveplotter/libcurveplotter.a \
  ../processes/libprocesses.a \
  ../dialogs/libdialogs.a \
  ../definitions/libdefinitions.a

LIBS += ../dialogs/libdialogs.a \
  ../curveplotter/libcurveplotter.a \
  ../processes/libprocesses.a \
  ../definitions/libdefinitions.a \
  -L../../stira/steerable/orientationestimation \
  -L../../stira/steerable/freemanadelson \
  -L../../stira/registration/registration \
  -L../../stira/contrastenhance/contrastenhance \
  -L../../stira/deconvolve/deconvolve \
  -L../../stira/pyramidapplications/pyramidapplications \
  -L../../stira/steerable/pyramid \
  -L../../stira/imageanalysis/imageanalysis \
  -L../../stira/wavelet/wavelet \
  -L../../stira/filter/filter \
  -L../../stira/fouriertools/fouriertools \
  -L../../stira/histogram/histogram \
  -L../../stira/diffusion/bregman \
  -L../../stira/diffusion/diffusion \
  -L../../stira/imagetools/geometrictransform \
  -L../../stira/imagetools/imagegenerator \
  -L../../stira/imagetools/tools \
  -L../../stira/imagetools/interpolation \
  -L../../stira/imagetools/colortools \
  -L../../stira/imagedata/simpletools \
  -L../../stira/imagedata/datastructures \
  -L../../stira/imagedata/color \
  -L../../stira/imagedata \
  -L../../stira/common/common \
  -L../../stira/ \
  -lregistration \
  -lcontrastenhance \
  -ldeconvolve \
  -lpyramidapplications \
  -lpyramid \
  -limageanalysis \
  -lwavelet \
  -lfreemanadelson \
  -lorientationestimation \
  -lfilter \
  -lfouriertools \
  -lhistogram \
  -lbregman \
  -ldiffusion \
  -lgeometrictransform \
  -limagegenerator \
  -linterpolation \
  -ltools \
  -lcolortools \
  -lsimpletools \
  -ldatastructures \
  -lcolor \
  -lcommon \
  -lqwt \
  -lopencv_highgui \
  -lopencv_imgproc \
  -lopencv_core \
  -lfftw3 \
  -lm \
  -luuid \
  -ldl \
  -lpthread
