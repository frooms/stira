TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += \
    testFileAccess.cpp

LIBS += ../common/libcommon.a

POST_TARGETDEPS += ../common/libcommon.a
