SOURCES += unsharpMaskTest.cpp

TEMPLATE = app

LIBS += ../filter/libfilter.a \
        ../../fouriertools/fouriertools/libfouriertools.a \
        ../../imagetools/tools/libtools.a \
        ../../imagetools/imagegenerator/libimagegenerator.a \
        ../../histogram/histogram/libhistogram.a \
        ../../imagedata/simpletools/libsimpletools.a \
        ../../imagedata/datastructures/libdatastructures.a \
        ../../imagedata/color/libcolor.a \
        ../../common/common/libcommon.a \
        -lfftw3 \
        -lopencv_highgui \
        -lopencv_core

POST_TARGETDEPS += ../../common/common/libcommon.a \
                   ../../imagetools/tools/libtools.a \
                   ../../imagetools/imagegenerator/libimagegenerator.a \
                   ../../imagedata/simpletools/libsimpletools.a \
                   ../../imagedata/datastructures/libdatastructures.a \
                   ../../imagedata/color/libcolor.a \
                   ../../histogram/histogram/libhistogram.a \
                   ../../fouriertools/fouriertools/libfouriertools.a \
                   ../filter/libfilter.a

