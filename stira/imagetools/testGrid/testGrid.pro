SOURCES += testGrid.cpp

TEMPLATE = app

LIBS += ../../histogram/histogram/libhistogram.a \
        ../tools/libtools.a \
        ../imagegenerator/libimagegenerator.a \
        ../interpolation/libinterpolation.a \
        ../../imagedata/simpletools/libsimpletools.a \
        ../../imagedata/datastructures/libdatastructures.a \
        ../../imagedata/color/libcolor.a \
        ../../common/common/libcommon.a \
        -lopencv_highgui \
        -lopencv_core

POST_TARGETDEPS += ../../histogram/histogram/libhistogram.a \
                   ../tools/libtools.a \
                   ../imagegenerator/libimagegenerator.a \
                   ../../imagedata/simpletools/libsimpletools.a \
                   ../../imagedata/datastructures/libdatastructures.a \
                   ../../imagedata/color/libcolor.a \
                   ../../common/common/libcommon.a

