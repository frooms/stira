TEMPLATE = lib

CONFIG += staticlib

SOURCES += CriticallySubsampledTransform.cpp \
NoiseEstimator.cpp \
NonSubsampledTransform.cpp \
SubsampledTransform.cpp \
Wavelet.cpp \
WaveletTapGenerator.cpp
HEADERS += CriticallySubsampledTransform.h \
NoiseEstimator.h \
NonSubsampledTransform.h \
SubsampledTransform.h \
Wavelet.h \
WaveletTapGenerator.h \
WaveletTaps.h
