#-------------------------------------------------
#
# Project created by QtCreator 2020-08-15T10:59:55
#
#-------------------------------------------------

QT       += core gui
QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HyperTry
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        hsi2l.cpp \
        main.cpp \
        mainwindow.cpp \
        mainwindowfunc.cpp \
        mlabel.cpp \
        weichang2l.cpp

HEADERS += \
        hsi2l.h \
        mainwindow.h \
        mlabel.h \
        weichang2l.h

FORMS += \
        mainwindow.ui
INCLUDEPATH += D:\OPENCV\opencv\build\include\
               D:\OPENCV\opencv\build\include\opencv2 \


LIBS += D:\OPENCV\opencv\build\x64\vc15\lib\opencv_world411.lib\
        D:\OPENCV\opencv\build\x64\vc15\lib\opencv_world411d.lib\

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
