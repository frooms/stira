
TEMPLATE = app

POST_TARGETDEPS += ../tools/libtools.a \
                   ../geometrictransform/libgeometrictransform.a \
                   ../interpolation/libinterpolation.a \
                   ../../imagedata/simpletools/libsimpletools.a \
                   ../../imagedata/datastructures/libdatastructures.a \
                   ../../imagedata/color/libcolor.a \
                   ../../common/common/libcommon.a

LIBS += ../tools/libtools.a \
        ../geometrictransform/libgeometrictransform.a \
        ../interpolation/libinterpolation.a \
        ../../imagedata/simpletools/libsimpletools.a \
        ../../imagedata/datastructures/libdatastructures.a \
        ../../imagedata/color/libcolor.a \
        ../../common/common/libcommon.a \
        -lopencv_highgui \
        -lopencv_core

SOURCES += testTransformation.cpp

