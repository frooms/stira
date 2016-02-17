TEMPLATE = lib

CONFIG += staticlib

SOURCES += AffineTransform.cpp \
           GeometricTransform.cpp \
           RigidTransform.cpp \
           Translation.cpp \
           FisheyeCorrector.cpp

HEADERS += AffineTransform.h \
           GeometricTransform.h \
           RigidTransform.h \
           Translation.h \
           FisheyeCorrector.h
