#-------------------------------------------------
#
# Project created by QtCreator 2017-02-04T16:39:26
#
#-------------------------------------------------

QT       += core sensors

TARGET = mpu6050
TEMPLATE = lib
CONFIG += plugin
PLUGIN_TYPE = sensors

DESTDIR = plugins/sensors

SOURCES += mpu6050.cpp \
    plugin.cpp \
    timersensorbackend.cpp \
    backends.cpp

HEADERS += \
    mpu6050.h \
    plugin.h \
    timersensorbackend.h \
    backends.h

DISTFILES += mpu6050.json

unix {
    target.path = /opt/qt5pi/plugins/sensors
    INSTALLS += target
}
