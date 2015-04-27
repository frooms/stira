TEMPLATE = lib
CONFIG += staticlib
SOURCES += CannyEdgeDetector.cpp \
    StegerLineDetector.cpp \
    Thinning.cpp \
    WatershedMeyer.cpp \
    WatershedToboggan.cpp \
    FloodFill.cpp \
    HardLink.cpp \
    ContourTracing.cpp \
    CompareCurvesInImage.cpp \
    FunctionsOpenCV.cpp \
    FindMaximalIncludedRectangles.cpp
HEADERS += CannyEdgeDetector.h \
    StegerLineDetector.h \
    Thinning.h \
    Watershed.h \
    WatershedMeyer.h \
    WatershedToboggan.h \
    FloodFill.h \
    HardLink.h \
    ContourTracing.h \
    CompareCurvesInImage.h \
    FunctionsOpenCV.h \
    FindMaximalIncludedRectangles.h
