#-------------------------------------------------
#
#
# =================================================
# * This file is part of the MMM Music Player project
# * All rights reserved!
# * Redistribution and use of the source code or any derivative
# * works are strictly forbiden.
# =================================================

QT       += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

MMMMusicPlayer = 2.4.0.0
unix:VERSION += $$MMMMusicPlayer

win32:TARGET = ../../bin/MMMMusicPlayer
unix:TARGET = ../lib/MMMMusicPlayer

TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

INCLUDEPATH += ../ \
    ../MMMCore/musicCore

SOURCES += \
    musicrunmain.cpp \
    musiclocalpeer.cpp \
    musicrunapplication.cpp \
    musicrunobject.cpp

HEADERS += \
    musicrunglobaldefine.h \
    musicrunobject.h \
    musiclocalpeer.h \
    musicrunapplication.h

RESOURCES += \
    ../MMMQrc/MusicApp.qrc

win32{
    RC_FILE = MMMApp.rc
}
