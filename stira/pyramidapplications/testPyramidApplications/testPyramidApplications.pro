SOURCES += testPyramidApplications.cpp

TEMPLATE = app

LIBS += ../../steerable/freemanadelson/libfreemanadelson.a \
  ../pyramidapplications/libpyramidapplications.a \
  ../../wavelet/wavelet/libwavelet.a \
  ../../steerable/orientationestimation/liborientationestimation.a \
  ../../steerable/pyramid/libpyramid.a \
  ../../filter/filter/libfilter.a \
  ../../fouriertools/fouriertools/libfouriertools.a \
  ../../image/tools/libtools.a \
  ../../image/datastructures/libdatastructures.a \
  ../../image/color/libcolor.a \
  ../../common/common/libcommon.a \
  -lfftw3 \
  -lopencv_highgui \
  -lopencv_core

POST_TARGETDEPS += ../pyramidapplications/libpyramidapplications.a \
  ../../steerable/orientationestimation/liborientationestimation.a \
  ../../steerable/pyramid/libpyramid.a \
  ../../steerable/freemanadelson/libfreemanadelson.a \
  ../../wavelet/wavelet/libwavelet.a \
  ../../filter/filter/libfilter.a \
  ../../fouriertools/fouriertools/libfouriertools.a \
  ../../image/tools/libtools.a \
  ../../image/datastructures/libdatastructures.a \
  ../../image/color/libcolor.a \
  ../../common/common/libcommon.a

