SOURCES += testPyramidApplications.cpp

TEMPLATE = app

LIBS += ../../steerable/freemanadelson/libfreemanadelson.a \
        ../pyramidapplications/libpyramidapplications.a \
        ../../steerable/orientationestimation/liborientationestimation.a \
        ../../steerable/pyramid/libpyramid.a \
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

POST_TARGETDEPS += ../pyramidapplications/libpyramidapplications.a \
                   ../../steerable/orientationestimation/liborientationestimation.a \
                   ../../steerable/pyramid/libpyramid.a \
                   ../../steerable/freemanadelson/libfreemanadelson.a \
                   ../../filter/filter/libfilter.a \
                   ../../fouriertools/fouriertools/libfouriertools.a \
                   ../../imagetools/tools/libtools.a \
                   ../../imagetools/imagegenerator/libimagegenerator.a \
                   ../../imagedata/simpletools/libsimpletools.a \
                   ../../imagedata/datastructures/libdatastructures.a \
                   ../../imagedata/color/libcolor.a \
                   ../../common/common/libcommon.a

