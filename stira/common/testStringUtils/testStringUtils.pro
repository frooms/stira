TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += \
    testStringUtils.cpp

LIBS += ../common/libcommon.a \
        -luuid

POST_TARGETDEPS += ../common/libcommon.a
