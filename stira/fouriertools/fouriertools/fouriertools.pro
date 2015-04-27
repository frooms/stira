TEMPLATE = lib

CONFIG += staticlib

SOURCES += FFTBand.cpp \
FFTCalculator.cpp \
FFT.cpp \
FFTWCalculator.cpp \
kiss_fft.c \
KISSFFTCalculator.cpp \
kiss_fftnd.c \
TransferFunctionGenerator.cpp
HEADERS += FFTBand.h \
FFTCalculator.h \
FFT.h \
FFTWCalculator.h \
KISSFFTCalculator.h \
_kiss_fft_guts.h \
kiss_fft.h \
kiss_fftnd.h \
TransferFunctionGenerator.h
