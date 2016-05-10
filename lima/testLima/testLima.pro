SOURCES += \
    testVectorMatrix.cpp

TEMPLATE = app

LIBS += ../lima/liblima.a

POST_TARGETDEPS += ../lima/liblima.a

