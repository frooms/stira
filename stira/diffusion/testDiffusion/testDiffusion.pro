SOURCES += testDiffusion.cpp

TEMPLATE = app

POST_TARGETDEPS += ../diffusion/libdiffusion.a \
  ../../image/tools/libtools.a \
  ../../image/datastructures/libdatastructures.a \
  ../../image/color/libcolor.a \
  ../../common/common/libcommon.a

LIBS += ../diffusion/libdiffusion.a \
  ../../image/tools/libtools.a \
  ../../image/datastructures/libdatastructures.a \
  ../../image/color/libcolor.a \
  ../../common/common/libcommon.a \
  -lopencv_highgui \
  -lopencv_core \
  -luuid \
  -lzip

