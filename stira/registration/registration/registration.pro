TEMPLATE = lib

CONFIG += staticlib

SOURCES += BsplnTrf.c \
BsplnWgt.c \
convolve.c \
errorMessage.c \
getPut.c \
main.c \
pyrFilt.c \
pyrGetSz.c \
quant.c \
reg0.c \
reg1.c \
reg2.c \
reg3.c \
regFlt3d.c \
RegistrationWrapper.cpp \
svdcmp.c \
    RegistrationDemon.cpp
HEADERS += BsplnTrf.h \
BsplnWgt.h \
convolve.h \
errorMessage.h \
getPut.h \
phil.h \
quant.h \
reg0.h \
reg1.h \
reg2.h \
reg3.h \
regFlt3d.h \
register.h \
RegistrationWrapper.h \
svdcmp.h \
    RegistrationDemon.h
