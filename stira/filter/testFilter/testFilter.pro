SOURCES += testFilter.cpp

TEMPLATE = app

LIBS += ../filter/libfilter.a \
        ../../fouriertools/fouriertools/libfouriertools.a \
        ../../imagetools/geometrictransform/libgeometrictransform.a \
        ../../imagetools/interpolation/libinterpolation.a \
        ../../imagetools/imagegenerator/libimagegenerator.a \
        ../../imagetools/tools/libtools.a \
        ../../histogram/histogram/libhistogram.a \
        ../../imagedata/simpletools/libsimpletools.a \
        ../../imagedata/datastructures/libdatastructures.a \
        ../../imagedata/color/libcolor.a \
        ../../common/common/libcommon.a \
        -lfftw3 \
        -lopencv_highgui \
        -lopencv_core

POST_TARGETDEPS += ../filter/libfilter.a \
                   ../../fouriertools/fouriertools/libfouriertools.a \
                   ../../imagetools/geometrictransform/libgeometrictransform.a \
                   ../../imagetools/interpolation/libinterpolation.a \
                   ../../imagetools/imagegenerator//libimagegenerator.a \
                   ../../imagetools/tools/libtools.a \
                   ../../histogram/histogram/libhistogram.a \
                   ../../imagedata/simpletools/libsimpletools.a \
                   ../../imagedata/datastructures/libdatastructures.a \
                   ../../imagedata/color/libcolor.a \
                   ../../common/common/libcommon.a \
