SOURCES += testFilter.cpp

TEMPLATE = app

LIBS += ../filter/libfilter.a \
  ../../fouriertools/fouriertools/libfouriertools.a \
  ../../histogram/histogram/libhistogram.a \
  ../../image/geometrictransform/libgeometrictransform.a \
  ../../image/tools/libtools.a \
  ../../image/datastructures/libdatastructures.a \
  ../../image/color/libcolor.a \
  ../../common/common/libcommon.a \
  -lfftw3 \
  -lopencv_highgui \
  -lopencv_core

POST_TARGETDEPS += ../../common/common/libcommon.a \
  ../../image/tools/libtools.a \
  ../../image/datastructures/libdatastructures.a \
  ../../image/color/libcolor.a \
  ../../histogram/histogram/libhistogram.a \
  ../../image/geometrictransform/libgeometrictransform.a \
  ../../fouriertools/fouriertools/libfouriertools.a \
  ../filter/libfilter.a

