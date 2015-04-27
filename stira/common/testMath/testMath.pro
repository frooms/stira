
TEMPLATE = app

SOURCES += testMath.cpp

LIBS += ../common/libcommon.a \
    -lopencv_core

POST_TARGETDEPS += ../common/libcommon.a

