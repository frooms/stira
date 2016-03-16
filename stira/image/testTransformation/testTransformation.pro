
TEMPLATE = app

POST_TARGETDEPS += ../tools/libtools.a \
  ../geometrictransform/libgeometrictransform.a \
  ../datastructures/libdatastructures.a \
  ../color/libcolor.a \
  ../../common/common/libcommon.a

LIBS += ../geometrictransform/libgeometrictransform.a \
  ../tools/libtools.a \
  ../datastructures/libdatastructures.a \
  ../color/libcolor.a \
  ../../common/common/libcommon.a \
  -lopencv_highgui \
  -lopencv_core

SOURCES += testTransformation.cpp

