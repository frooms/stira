TEMPLATE = lib
CONFIG += staticlib
SOURCES += DeconvolveMaster.cpp \
    GNCDeconvolve.cpp \
    IterativeDeconvolve.cpp \
    RichardsonLucyDeconvolve.cpp \
    VanCittertLandweberDeconvolve.cpp \
    WienerDeconvolve.cpp \
    TikhonovMillerDeconvolve.cpp \
    SimulateDegradation.cpp
HEADERS += DeconvolveMaster.h \
    GNCDeconvolve.h \
    IterativeDeconvolve.h \
    RichardsonLucyDeconvolve.h \
    VanCittertLandweberDeconvolve.h \
    WienerDeconvolve.h \
    TikhonovMillerDeconvolve.h \
    SimulateDegradation.h
