SOURCES += testGrid.cpp

TEMPLATE = app

LIBS += ../tools/libtools.a \
  ../datastructures/libdatastructures.a \
  ../color/libcolor.a \
  ../../common/common/libcommon.a \
  -lopencv_highgui \
  -lopencv_core \
  -luuid \
  -lzip

POST_TARGETDEPS += ../tools/libtools.a \
  ../datastructures/libdatastructures.a \
  ../color/libcolor.a \
  ../../common/common/libcommon.a

