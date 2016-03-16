SOURCES += testHistogram.cpp

TEMPLATE = app

POST_TARGETDEPS += ../../common/common/libcommon.a \
  ../../image/tools/libtools.a \
  ../../image/datastructures/libdatastructures.a \
  ../../image/color/libcolor.a \
  ../histogram/libhistogram.a

LIBS += ../histogram/libhistogram.a \
  ../../image/tools/libtools.a \
  ../../image/datastructures/libdatastructures.a \
  ../../image/color/libcolor.a \
  ../../common/common/libcommon.a \
  -lopencv_highgui \
  -lopencv_core

