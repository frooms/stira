SOURCES += testBlurEstimation.cpp

TEMPLATE = app

LIBS += ../degradationestimation/libdegradationestimation.a \
        ../../deconvolve/deconvolve/libdeconvolve.a \
        ../../pyramidapplications/pyramidapplications/libpyramidapplications.a \
        ../../steerable/pyramid/libpyramid.a \
        ../../wavelet/wavelet/libwavelet.a \
        ../../filter/filter/libfilter.a \
        ../../fouriertools/fouriertools/libfouriertools.a \
        ../../histogram/histogram/libhistogram.a \
        ../../imagetools/tools/libtools.a \
        ../../imagetools/imagegenerator/libimagegenerator.a \
        ../../imagedata/simpletools/libsimpletools.a \
        ../../imagedata/datastructures/libdatastructures.a \
        ../../imagedata/color/libcolor.a \
        ../../common/common/libcommon.a \
        -lfftw3 \
        -lopencv_highgui \
        -lopencv_core

POST_TARGETDEPS += ../degradationestimation/libdegradationestimation.a \
                   ../../deconvolve/deconvolve/libdeconvolve.a \
                   ../../pyramidapplications/pyramidapplications/libpyramidapplications.a \
                   ../../steerable/pyramid/libpyramid.a \
                   ../../wavelet/wavelet/libwavelet.a \
                   ../../filter/filter/libfilter.a \
                   ../../fouriertools/fouriertools/libfouriertools.a \
                   ../../histogram/histogram/libhistogram.a \
                   ../../imagetools/tools/libtools.a \
                   ../../imagetools/imagegenerator/libimagegenerator.a \
                   ../../imagedata/simpletools/libsimpletools.a \
                   ../../imagedata/datastructures/libdatastructures.a \
                   ../../imagedata/color/libcolor.a \
                   ../../common/common/libcommon.a

