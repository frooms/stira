TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

LIBS += ../common/libcommon.a

POST_TARGETDEPS += ../common/libcommon.a

