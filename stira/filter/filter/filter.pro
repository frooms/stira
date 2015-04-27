TEMPLATE = lib
CONFIG += staticlib
SOURCES += AdaptiveBilateralFilter.cpp \
    GaussConvolve.cpp \
    KuwaharaFilter.cpp \
    LaplacianOfGaussianFilter.cpp \
    LocalBinaryPattern.cpp \
    NonLocalMeansFilter.cpp \
    NonSeparableFilter.cpp \
    SeparableFilter.cpp \
    UnsharpMask.cpp \
    MedianFilter.cpp \
    LogGabor.cpp \
    AnisotropicGaussian.cpp \
    anigauss.c \
    DifferenceOfGaussians.cpp \
    ColorLookupTable.cpp
HEADERS += AdaptiveBilateralFilter.h \
    GaussConvolve.h \
    KuwaharaFilter.h \
    LaplacianOfGaussianFilter.h \
    LocalBinaryPattern.h \
    NonLocalMeansFilter.h \
    NonSeparableFilter.h \
    SeparableFilter.h \
    UnsharpMask.h \
    MedianFilter.h \
    LogGabor.h \
    AnisotropicGaussian.h \
    anigauss.h \
    DifferenceOfGaussians.h \
    ColorLookupTable.h
