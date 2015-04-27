TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += \
    testTextFileUtils.cpp

LIBS += ../common/libcommon.a \
    -lopencv_core

POST_TARGETDEPS += ../common/libcommon.a
