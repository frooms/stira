SOURCES += testRegistration.cpp

TEMPLATE = app

LIBS +=  ../registration/libregistration.a \
         ../../imagetools/geometrictransform/libgeometrictransform.a \
         ../../imagetools/tools/libtools.a \
         ../../imagetools/interpolation/libinterpolation.a \
         ../../imagedata/simpletools/libsimpletools.a \
         ../../imagedata/datastructures/libdatastructures.a \
         ../../imagedata/color/libcolor.a \
         ../../common/common/libcommon.a  \
         -lopencv_highgui \
         -lopencv_core

POST_TARGETDEPS += ../registration/libregistration.a \
                   ../../imagetools/tools/libtools.a \
                   ../../imagetools/interpolation/libinterpolation.a \
                   ../../imagetools/geometrictransform/libgeometrictransform.a \
                   ../../imagedata/simpletools/libsimpletools.a \
                   ../../imagedata/datastructures/libdatastructures.a \
                   ../../imagedata/color/libcolor.a \
                   ../../common/common/libcommon.a

