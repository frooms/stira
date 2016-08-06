SOURCES += testColor.cpp

TEMPLATE = app

POST_TARGETDEPS += ../tools/libtools.a \
                   ../imagegenerator/libimagegenerator.a \
                   ../colortools/libcolortools.a \
                   ../../imagedata/simpletools/libsimpletools.a \
                   ../../imagedata/datastructures/libdatastructures.a \
                   ../../imagedata/color/libcolor.a \
                   ../../common/common/libcommon.a

LIBS += ../tools/libtools.a \
        ../imagegenerator/libimagegenerator.a \
        ../colortools/libcolortools.a \
        ../../imagedata/simpletools/libsimpletools.a \
        ../../imagedata/datastructures/libdatastructures.a \
        ../../imagedata/color/libcolor.a \
        ../../common/common/libcommon.a \
        -lopencv_highgui \
        -lopencv_core

