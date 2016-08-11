TEMPLATE = lib

CONFIG += staticlib

SOURCES += AnisotropicDiffusionProcess.cpp \
 CannyProcess.cpp \
 GenerateImageProcess.cpp \
 WatershedProcess.cpp \
 WienerDeconvolveProcess.cpp \
 ContrastEnhanceProcess.cpp \
 SteerableDenoisingProcess.cpp \
 SimpleImageFilterProcess.cpp \
 SimulateNoiseProcess.cpp \
 RichardsonLucyDeconvolveProcess.cpp \
 Process.cpp \
 GNCDeconvolveProcess.cpp \
 LogGaborFilterProcess.cpp \
 RegisterImagesProcess.cpp \
 SplitColorChannelsProcess.cpp \
 GeneratePerlinNoiseProcess.cpp \
 SplitBregmanDenoiseProcess.cpp \
    HoughTransformProcess.cpp

HEADERS += AnisotropicDiffusionProcess.h \
 CannyProcess.h \
 GenerateImageProcess.h \
 WatershedProcess.h \
 WienerDeconvolveProcess.h \
 ContrastEnhanceProcess.h \
 SteerableDenoisingProcess.h \
 SimpleImageFilterProcess.h \
 SimulateNoiseProcess.h \
 RichardsonLucyDeconvolveProcess.h \
 Process.h \
 GNCDeconvolveProcess.h \
 LogGaborFilterProcess.h \
 RegisterImagesProcess.h \
 SplitColorChannelsProcess.h \
 GeneratePerlinNoiseProcess.h \
 SplitBregmanDenoiseProcess.h \
    HoughTransformProcess.h
