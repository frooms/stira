TEMPLATE = lib

CONFIG += staticlib

SOURCES += AdaptiveEnhanceLuong.cpp \
           Retinex.cpp \
           HazeRemover.cpp \
           HistogramTools.cpp \
    AdaptiveHistogramEqualizer.cpp
HEADERS += AdaptiveEnhanceLuong.h \
           Retinex.h \
           HazeRemover.h \
           HistogramTools.h \
    AdaptiveHistogramEqualizer.h
