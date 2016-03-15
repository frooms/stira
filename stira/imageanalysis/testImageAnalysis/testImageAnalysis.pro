SOURCES += testImageAnalysis.cpp

TEMPLATE = app

POST_TARGETDEPS += ../imageanalysis/libimageanalysis.a \
  ../../filter/filter/libfilter.a \
  ../../fouriertools/fouriertools/libfouriertools.a \
  ../../histogram/histogram/libhistogram.a \
  ../../image/tools/libtools.a \
  ../../image/datastructures/libdatastructures.a \
  ../../image/color/libcolor.a \
  ../../common/common/libcommon.a

LIBS += ../imageanalysis/libimageanalysis.a \
  ../../filter/filter/libfilter.a \
  ../../fouriertools/fouriertools/libfouriertools.a \
  ../../histogram/histogram/libhistogram.a \
  ../../image/tools/libtools.a \
  ../../image/datastructures/libdatastructures.a \
  ../../image/color/libcolor.a \
  ../../common/common/libcommon.a \
  -lfftw3 \
  -lopencv_highgui \
  -lopencv_objdetect \
  -lopencv_imgproc \
  -lopencv_core \
  -luuid \
  -lzip

