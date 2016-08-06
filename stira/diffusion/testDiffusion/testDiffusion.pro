SOURCES += testDiffusion.cpp

TEMPLATE = app

POST_TARGETDEPS += ../diffusion/libdiffusion.a \
                   ../../imagetools/tools/libtools.a \
                   ../../imagedata/simpletools/libsimpletools.a \
                   ../../imagedata/datastructures/libdatastructures.a \
                   ../../imagedata/color/libcolor.a \
                   ../../common/common/libcommon.a

LIBS += ../diffusion/libdiffusion.a \
        ../../imagetools/tools/libtools.a \
        ../../imagedata/simpletools/libsimpletools.a \
        ../../imagedata/datastructures/libdatastructures.a \
        ../../imagedata/color/libcolor.a \
        ../../common/common/libcommon.a \
        -lopencv_highgui \
        -lopencv_core

