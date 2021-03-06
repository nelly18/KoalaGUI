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
    serialgate.cpp \
    proximitysensorpainter.cpp \
    sensor.cpp \
    analogsensorgraph.cpp \
    colorpalettedialog.cpp \
    analoghistogram.cpp \
    speedcontrol.cpp \
    pidregulator.cpp \
    inputsoutputstab.cpp \
    console.cpp \
    batterycharge.cpp \
    statusbarwidget.cpp \
    script.cpp \
    scripttab.cpp \
    analogvaluesloader.cpp

HEADERS  += mainwindow.h \
    serialgate.h \
    proximitysensorpainter.h \
    sensor.h \
    analogsensorgraph.h \
    colorpalettedialog.h \
    defines.h \
    analoghistogram.h \
    speedcontrol.h \
    pidregulator.h \
    inputsoutputstab.h \
    console.h \
    batterycharge.h \
    statusbarwidget.h \
    script.h \
    scripttab.h \
    analogvaluesloader.h

FORMS    += mainwindow.ui \
    colorpalettedialog.ui \
    form.ui

RESOURCES += \
    Icons.qrc

win32: {
INCLUDEPATH += C:/qwt-6.0.0/src
LIBS    += C:/qwt-6.0.0/lib/libqwtd.a
#LIBS    += -L C:/qwt-6.0.0/lib/ -lqwt
}

unix: {
INCLUDEPATH += /usr/include/qwt6
LIBS    += -lqwt6
}

QT += script
