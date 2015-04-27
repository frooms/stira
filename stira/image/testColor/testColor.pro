SOURCES += testColor.cpp

TEMPLATE = app

POST_TARGETDEPS += ../tools/libtools.a \
  ../datastructures/libdatastructures.a \
  ../color/libcolor.a \
  ../../common/common/libcommon.a

LIBS += ../tools/libtools.a \
  ../datastructures/libdatastructures.a \
  ../color/libcolor.a \
  ../../common/common/libcommon.a \
  -lopencv_highgui \
  -lopencv_core \
  -luuid \
  -lzip

