SOURCES += testPyramid.cpp

TEMPLATE = app

LIBS += ../orientationestimation/liborientationestimation.a \
        ../freemanadelson/libfreemanadelson.a \
        ../pyramid/libpyramid.a \
        ../../contrastenhance/contrastenhance/libcontrastenhance.a \
        ../../filter/filter/libfilter.a \
        ../../fouriertools/fouriertools/libfouriertools.a \
        ../../imagetools/tools/libtools.a \
        ../../imagetools/imagegenerator/libimagegenerator.a \
        ../../imagedata/simpletools/libsimpletools.a \
        ../../imagedata/datastructures/libdatastructures.a \
        ../../imagedata/color/libcolor.a \
        ../../common/common/libcommon.a \
        -lfftw3 \
        -lopencv_highgui \
        -lopencv_core

POST_TARGETDEPS += ../freemanadelson/libfreemanadelson.a \
                   ../pyramid/libpyramid.a \
                   ../orientationestimation/liborientationestimation.a \
                   ../../contrastenhance/contrastenhance/libcontrastenhance.a \
                   ../../filter/filter/libfilter.a \
                   ../../fouriertools/fouriertools/libfouriertools.a \
                   ../../imagetools/tools/libtools.a \
                   ../../imagetools/imagegenerator/libimagegenerator.a \
                   ../../imagedata/simpletools/libsimpletools.a \
                   ../../imagedata/datastructures/libdatastructures.a \
                   ../../imagedata/color/libcolor.a \
                   ../../common/common/libcommon.a

