SOURCES += testPyramid.cpp

TEMPLATE = app

LIBS += ../orientationestimation/liborientationestimation.a \
  ../freemanadelson/libfreemanadelson.a \
  ../pyramid/libpyramid.a \
  ../../contrastenhance/contrastenhance/libcontrastenhance.a \
  ../../filter/filter/libfilter.a \
  ../../fouriertools/fouriertools/libfouriertools.a \
  ../../image/tools/libtools.a \
  ../../image/datastructures/libdatastructures.a \
  ../../image/color/libcolor.a \
  ../../common/common/libcommon.a \
  -lfftw3 \
  -lopencv_highgui \
  -lopencv_core \
  -luuid \
  -lzip

POST_TARGETDEPS += ../freemanadelson/libfreemanadelson.a \
  ../pyramid/libpyramid.a \
  ../orientationestimation/liborientationestimation.a \
  ../../contrastenhance/contrastenhance/libcontrastenhance.a \
  ../../filter/filter/libfilter.a \
  ../../fouriertools/fouriertools/libfouriertools.a \
  ../../image/tools/libtools.a \
  ../../image/datastructures/libdatastructures.a \
  ../../image/color/libcolor.a \
  ../../common/common/libcommon.a

