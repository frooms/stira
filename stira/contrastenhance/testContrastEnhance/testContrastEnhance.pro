SOURCES += testContrastEnhance.cpp

TEMPLATE = app

LIBS += ../contrastenhance/libcontrastenhance.a \
        ../../filter/filter/libfilter.a \
        ../../fouriertools/fouriertools/libfouriertools.a \
        ../../imagetools/tools/libtools.a \
        ../../imagetools/imagegenerator/libimagegenerator.a \
        ../../imagetools/interpolation/libinterpolation.a \
        ../../histogram/histogram/libhistogram.a \
        ../../imagedata/simpletools/libsimpletools.a \
        ../../imagedata/datastructures/libdatastructures.a \
        ../../imagedata/color/libcolor.a \
        ../../common/common/libcommon.a \
        -lfftw3 \
        -lopencv_highgui \
        -lopencv_core

POST_TARGETDEPS += ../contrastenhance/libcontrastenhance.a \
                   ../../filter/filter/libfilter.a \
                   ../../fouriertools/fouriertools/libfouriertools.a \
                   ../../histogram/histogram/libhistogram.a \
                   ../../imagetools/tools/libtools.a \
                   ../../imagetools/imagegenerator/libimagegenerator.a \
                   ../../imagetools/interpolation/libinterpolation.a \
                   ../../imagedata/simpletools/libsimpletools.a \
                   ../../imagedata/datastructures/libdatastructures.a \
                   ../../imagedata/color/libcolor.a \
                   ../../common/common/libcommon.a

