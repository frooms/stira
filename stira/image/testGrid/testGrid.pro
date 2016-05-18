SOURCES += testGrid.cpp

TEMPLATE = app

LIBS += ../tools/libtools.a \
        ../datastructures/libdatastructures.a \
        ../color/libcolor.a \
        ../../histogram/histogram/libhistogram.a \
        ../../common/common/libcommon.a \
        -lopencv_highgui \
        -lopencv_core

POST_TARGETDEPS += ../tools/libtools.a \
                   ../datastructures/libdatastructures.a \
                   ../color/libcolor.a \
                   ../../histogram/histogram/libhistogram.a \
                   ../../common/common/libcommon.a

