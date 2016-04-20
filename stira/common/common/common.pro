TEMPLATE = lib
CONFIG += staticlib
HEADERS += Definitions.h \
    DrawFigures.h \
    ExecutionTimer.h \
    MathUtils.h \
    Point.h \
    Random.h \
    StiraMacros.h \
    StringUtils.h \
    TextFileUtils.h \
    RectangularROI.h \
    FitCurve.h \
    LineSegment.h \
    Curve.h \
    CurveSet.h \
    Statistics.h \
    FileAccess.h \
    FixedBuffer.h \
    QuantileNormalDistribution.h \
    ClusteringLearning.h \
    Polygon.h \
    SVD.h \
    MonotonicCubicSplineInterpolator.h
SOURCES += Definitions.cpp \
    DrawFigures.cpp \
    ExecutionTimer.cpp \
    MathUtils.cpp \
    Point.cpp \
    Random.cpp \
    StringUtils.cpp \
    TextFileUtils.cpp \
    RectangularROI.cpp \
    FitCurve.cpp \
    LineSegment.cpp \
    Curve.cpp \
    CurveSet.cpp \
    Statistics.cpp \
    FileAccess.cpp \
    FixedBuffer.cpp \
    QuantileNormalDistribution.cpp \
    ClusteringLearning.cpp \
    Polygon.cpp \
    SVD.cpp \
    MonotonicCubicSplineInterpolator.cpp
