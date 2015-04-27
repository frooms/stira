TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += \
    testFileAccess.cpp

LIBS += ../common/libcommon.a \
    -lzip \
    -luuid

POST_TARGETDEPS += ../common/libcommon.a
