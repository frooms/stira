SOURCES += \
    testExecutionTimer.cpp

TEMPLATE = app

LIBS += ../common/libcommon.a \
    -lopencv_core

POST_TARGETDEPS += ../common/libcommon.a

