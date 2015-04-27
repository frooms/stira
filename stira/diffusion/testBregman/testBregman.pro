SOURCES += Example.cpp

HEADERS += Example.h

TEMPLATE = app

LIBS += ../bregman/libbregman.a \
  ../../image/tools/libtools.a \
  ../../image/datastructures/libdatastructures.a \
  ../../image/color/libcolor.a \
  ../../common/common/libcommon.a \
  -lopencv_highgui \
  -lopencv_core \
  -luuid \
  -lzip

POST_TARGETDEPS += ../bregman/libbregman.a \
  ../../image/tools/libtools.a \
  ../../image/datastructures/libdatastructures.a \
  ../../image/color/libcolor.a \
  ../../common/common/libcommon.a

