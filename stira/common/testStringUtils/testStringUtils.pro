TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += \
    testStringUtils.cpp

LIBS += ../common/libcommon.a

POST_TARGETDEPS += ../common/libcommon.a
