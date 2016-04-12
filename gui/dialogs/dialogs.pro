TEMPLATE = lib

CONFIG += staticlib

SOURCES += AnisotropicDiffusionDialog.cpp \
CannyDialog.cpp \
ContrastEnhanceDialog.cpp \
GenerateImageDialog.cpp \
SteerableDenoisingDialog.cpp \
WatershedDialog.cpp \
WienerDeconvolveDialog.cpp \
 SimpleImageFilterDialog.cpp \
 SimulateNoiseDialog.cpp \
 DialogMaster.cpp \
 RichardsonLucyDeconvolveDialog.cpp \
 GNCDeconvolveDialog.cpp \
 LogGaborFilterDialog.cpp \
 SplitColorChannelsDialog.cpp \
 GeneratePerlinNoiseDialog.cpp \
 SplitBregmanDenoiseDialog.cpp

HEADERS += AnisotropicDiffusionDialog.h \
CannyDialog.h \
ContrastEnhanceDialog.h \
GenerateImageDialog.h \
SimpleImageFilterDialog.h \
SteerableDenoisingDialog.h \
WatershedDialog.h \
WienerDeconvolveDialog.h \
 SimulateNoiseDialog.h \
 DialogMaster.h \
 RichardsonLucyDeconvolveDialog.h \
 GNCDeconvolveDialog.h \
 LogGaborFilterDialog.h \
 SplitColorChannelsDialog.h \
 GeneratePerlinNoiseDialog.h \
 SplitBregmanDenoiseDialog.h
