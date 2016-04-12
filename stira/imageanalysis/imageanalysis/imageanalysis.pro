TEMPLATE = lib
CONFIG += staticlib
SOURCES += CannyEdgeDetector.cpp \
    StegerLineDetector.cpp \
    Thinning.cpp \
    WatershedMeyer.cpp \
    WatershedToboggan.cpp \
    FloodFill.cpp \
    ContourTracing.cpp \
    CompareCurvesInImage.cpp \
    FunctionsOpenCV.cpp \
    FindMaximalIncludedRectangles.cpp \
    SLIC.cpp \
    HOG.cpp \
    DistanceTransform.cpp
HEADERS += CannyEdgeDetector.h \
    StegerLineDetector.h \
    Thinning.h \
    Watershed.h \
    WatershedMeyer.h \
    WatershedToboggan.h \
    FloodFill.h \
    ContourTracing.h \
    CompareCurvesInImage.h \
    FunctionsOpenCV.h \
    FindMaximalIncludedRectangles.h \
    SLIC.h \
    HOG.h \
    DistanceTransform.h
