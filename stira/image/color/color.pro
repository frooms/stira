TEMPLATE = lib
CONFIG += staticlib
SOURCES += ChromaticAdaptation.cpp \
    ColorBalancer.cpp \
    ColorConstants.cpp \
    GretagMacbethColorChecker.cpp \
    ProfileCorrect.cpp \
    ProfileData.cpp \
    TransformColorSpace.cpp \
    ColorValue.cpp \
    DistinctColorGenerator.cpp
HEADERS += ChromaticAdaptation.h \
    ColorBalancer.h \
    ColorConstants.h \
    GretagMacbethColorChecker.h \
    ProfileCorrect.h \
    ProfileData.h \
    TransformColorSpace.h \
    ColorValue.h \
    DistinctColorGenerator.h
