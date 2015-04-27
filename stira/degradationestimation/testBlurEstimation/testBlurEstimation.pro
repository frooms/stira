SOURCES += testBlurEstimation.cpp

TEMPLATE = app

LIBS += ../degradationestimation/libdegradationestimation.a \
  ../../deconvolve/deconvolve/libdeconvolve.a \
  ../../pyramidapplications/pyramidapplications/libpyramidapplications.a \
  ../../steerable/pyramid/libpyramid.a \
  ../../wavelet/wavelet/libwavelet.a \
  ../../filter/filter/libfilter.a \
  ../../fouriertools/fouriertools/libfouriertools.a \
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

POST_TARGETDEPS += ../degradationestimation/libdegradationestimation.a \
  ../../deconvolve/deconvolve/libdeconvolve.a \
  ../../pyramidapplications/pyramidapplications/libpyramidapplications.a \
  ../../steerable/pyramid/libpyramid.a \
  ../../wavelet/wavelet/libwavelet.a \
  ../../filter/filter/libfilter.a \
  ../../fouriertools/fouriertools/libfouriertools.a \
  ../../histogram/histogram/libhistogram.a \
  ../../image/tools/libtools.a \
  ../../image/datastructures/libdatastructures.a \
  ../../image/color/libcolor.a \
  ../../common/common/libcommon.a

