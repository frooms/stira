SOURCES += testRegistration.cpp

TEMPLATE = app

LIBS +=  ../registration/libregistration.a \
  ../../image/geometrictransform/libgeometrictransform.a \
  ../../image/tools/libtools.a \
  ../../image/datastructures/libdatastructures.a \
  ../../image/color/libcolor.a \
  ../../common/common/libcommon.a  \
  -lopencv_highgui \
  -lopencv_core

POST_TARGETDEPS += ../registration/libregistration.a \
  ../../image/tools/libtools.a \
  ../../image/geometrictransform/libgeometrictransform.a \
  ../../image/datastructures/libdatastructures.a \
  ../../image/color/libcolor.a \
  ../../common/common/libcommon.a

