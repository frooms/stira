SOURCES += testHistogram.cpp

TEMPLATE = app

POST_TARGETDEPS += ../../common/common/libcommon.a \
                   ../../imagedata/datastructures/libdatastructures.a \
                   ../../imagedata/color/libcolor.a \
                   ../../imagedata/simpletools/libsimpletools.a \
                   ../../histogram/histogram/libhistogram.a \
                   ../tools/libtools.a \

LIBS += ../tools/libtools.a \
        ../../histogram/histogram/libhistogram.a \
        ../../imagedata/simpletools/libsimpletools.a \
        ../../imagedata/datastructures/libdatastructures.a \
        ../../imagedata/color/libcolor.a \
        ../../common/common/libcommon.a \
        -lopencv_highgui \
        -lopencv_core

