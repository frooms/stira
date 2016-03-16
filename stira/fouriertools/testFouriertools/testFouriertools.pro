SOURCES += testFouriertools.cpp

HEADERS += testFouriertools.h

TEMPLATE = app

POST_TARGETDEPS += ../fouriertools/libfouriertools.a \
  ../../image/tools/libtools.a \
  ../../image/datastructures/libdatastructures.a \
  ../../image/color/libcolor.a \
  ../../common/common/libcommon.a

LIBS += ../fouriertools/libfouriertools.a \
  ../../image/tools/libtools.a \
  ../../image/datastructures/libdatastructures.a \
  ../../image/color/libcolor.a \
  ../../common/common/libcommon.a \
  -lfftw3 \
  -lopencv_highgui \
  -lopencv_core

