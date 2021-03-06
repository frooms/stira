SOURCES += testGNCDeconvolve.cpp

TEMPLATE = app

POST_TARGETDEPS += ../../pyramidapplications/pyramidapplications/libpyramidapplications.a \
                   ../deconvolve/libdeconvolve.a \
                   ../../steerable/pyramid/libpyramid.a \
                   ../../wavelet/wavelet/libwavelet.a \
                   ../../filter/filter/libfilter.a \
                   ../../fouriertools/fouriertools/libfouriertools.a \
                   ../../imagetools/tools/libtools.a \
                   ../../imagedata/simpletools/libsimpletools.a \
                   ../../imagetools/imagegenerator/libimagegenerator.a \
                   ../../imagedata/datastructures/libdatastructures.a \
                   ../../imagedata/color/libcolor.a \
                   ../../common/common/libcommon.a

LIBS += ../deconvolve/libdeconvolve.a \
        ../../wavelet/wavelet/libwavelet.a \
        ../../pyramidapplications/pyramidapplications/libpyramidapplications.a \
        ../../steerable/pyramid/libpyramid.a \
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

