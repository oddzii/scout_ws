QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    ../../../lib/jule/JOnvif/include/JOnvif.hpp \
    ../../../lib/jule/JOnvif/include/JOnvifDevice.hpp \
    ../../../lib/jule/JOnvif/include/JOnvifImaging.hpp \
    ../../../lib/jule/JOnvif/include/JOnvifMedia.hpp \
    ../../../lib/jule/JOnvif/include/JOnvifPtz.hpp \
    src/MainApplication.hpp

SOURCES += \
        ../../../lib/jule/JOnvif/src/JOnvif.cpp \
        ../../../lib/jule/JOnvif/src/JOnvifDevice.cpp \
        ../../../lib/jule/JOnvif/src/JOnvifImaging.cpp \
        ../../../lib/jule/JOnvif/src/JOnvifMedia.cpp \
        ../../../lib/jule/JOnvif/src/JOnvifPtz.cpp \
        src/MainApplication.cpp \
        src/main.cpp

DISTFILES += \
    CMakeLists.txt \
    package.xml


JLIB_DIR = $$(HOME)/lib/jule
INCLUDEPATH += \
    ../../devel/include \
    /opt/ros/noetic/include \
    $$JLIB_DIR/JTimer/include \
    $$JLIB_DIR/gSOAP/include \
    $$JLIB_DIR/JOnvif/include

CONFIG += link_pkgconfig
PKGCONFIG += opencv4

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
