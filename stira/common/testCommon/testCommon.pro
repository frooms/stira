SOURCES += \
    testExecutionTimer.cpp

TEMPLATE = app

LIBS += ../common/libcommon.a \
    -lopencv_core \
    -lzip

POST_TARGETDEPS += ../common/libcommon.a

