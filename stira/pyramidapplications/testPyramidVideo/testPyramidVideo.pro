SOURCES += testPyramidVideo.cpp

TEMPLATE = app

POST_TARGETDEPS += ../pyramidapplications/libpyramidapplications.a \
  ../../steerable/orientationestimation/liborientationestimation.a \
  ../../steerable/pyramid/libpyramid.a \
  ../../steerable/freemanadelson/libfreemanadelson.a \
  ../../contrastenhance/contrastenhance/libcontrastenhance.a \
  ../../wavelet/wavelet/libwavelet.a \
  ../../filter/filter/libfilter.a \
  ../../fouriertools/fouriertools/libfouriertools.a \
  ../../histogram/histogram/libhistogram.a \
  ../../avi/avi/libavi.a \
  ../../image/tools/libtools.a \
  ../../image/datastructures/libdatastructures.a \
  ../../image/color/libcolor.a \
  ../../common/common/libcommon.a

LIBS += ../../contrastenhance/contrastenhance/libcontrastenhance.a \
  ../../steerable/freemanadelson/libfreemanadelson.a \
  ../../steerable/orientationestimation/liborientationestimation.a \
  ../pyramidapplications/libpyramidapplications.a \
  ../../steerable/pyramid/libpyramid.a \
  ../../filter/filter/libfilter.a \
  ../../wavelet/wavelet/libwavelet.a \
  ../../fouriertools/fouriertools/libfouriertools.a \
  ../../avi/avi/libavi.a \
  ../../histogram/histogram/libhistogram.a \
  ../../image/tools/libtools.a \
  ../../image/datastructures/libdatastructures.a \
  ../../image/color/libcolor.a \
  ../../common/common/libcommon.a \
  -lfftw3 \
  -lopencv_highgui \
  -lopencv_core \
  -luuid \
  -lzip

