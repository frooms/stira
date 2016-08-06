SOURCES += testRichardsonLucy.cpp

TEMPLATE = app

LIBS += ../deconvolve/libdeconvolve.a \
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

POST_TARGETDEPS += ../deconvolve/libdeconvolve.a \
                   ../../filter/filter/libfilter.a \
                   ../../fouriertools/fouriertools/libfouriertools.a \
                   ../../imagetools/tools/libtools.a \
                   ../../imagetools/imagegenerator/libimagegenerator.a \
                   ../../imagedata/simpletools/libsimpletools.a \
                   ../../imagedata/datastructures/libdatastructures.a \
                   ../../imagedata/color/libcolor.a \
                   ../../common/common/libcommon.a

