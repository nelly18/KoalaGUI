#-------------------------------------------------
#
# Project created by QtCreator 2011-07-04T16:30:14
#
#-------------------------------------------------

QT       += core gui
CONFIG += qwt
TARGET = KoalaGUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    SerialGate.cpp \
    ProximitySensorPainter.cpp \
    Sensor.cpp \
    AnalogSensorGraph.cpp \
    colorpalettedialog.cpp \
    analoghistogram.cpp \
    speedcontrol.cpp \
    pidregulator.cpp \
    inputsoutputstab.cpp

HEADERS  += mainwindow.h \
    SerialGate.h \
    ProximitySensorPainter.h \
    Sensor.h \
    AnalogSensorGraph.h \
    colorpalettedialog.h \
    defines.h \
    analoghistogram.h \
    speedcontrol.h \
    pidregulator.h \
    inputsoutputstab.h

FORMS    += mainwindow.ui \
    colorpalettedialog.ui \
    form.ui

RESOURCES += \
    Icons.qrc

INCLUDEPATH += /usr/include/qwt6
LIBS    += -lqwt6
