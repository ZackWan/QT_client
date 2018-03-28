#-------------------------------------------------
#
# Project created by QtCreator 2018-03-21T11:14:17
#
#-------------------------------------------------

QT       += core gui multimediawidgets multimedia uitools
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = demo
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    login_dialog.cpp \
    frame_query.cpp \
    frame_sign.cpp \
    frame_stumanage.cpp \
    frame_manual_sign.cpp \
    choosecoursedialog.cpp \
    httpop.cpp \
    mytitlebar.cpp

HEADERS += \
        mainwindow.h \
    login_dialog.h \
    global.h \
    tabstyle.h \
    tabwidget.h \
    frame_query.h \
    frame_sign.h \
    frame_stumanage.h \
    frame_manual_sign.h \
    choosecoursedialog.h \
    httpop.h \
    mytitlebar.h

FORMS += \
        mainwindow.ui \
    login_dialog.ui \
    frame_query.ui \
    frame_sign.ui \
    frame_stumanage.ui \
    frame_manual_sign.ui \
    choosecoursedialog.ui

RESOURCES += \
    qt_resources.qrc

CONFIG += c++11

DISTFILES +=
