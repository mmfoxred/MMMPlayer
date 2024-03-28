#-------------------------------------------------
#
#
# =================================================
# * This file is part of the MMM Music Player project
# * All rights reserved!
# * Redistribution and use of the source code or any derivative
# * works are strictly forbiden.
# =================================================

TEMPLATE = lib
CONFIG += MMM_BUILD_LIB

include(../MMMMusicPlayer.pri)
unix:VERSION += $$MMMMusicPlayer

win32:TARGET = ../../bin/$$MMMMusicPlayer/MusicCore
unix:TARGET = ../lib/$$MMMMusicPlayer/MusicCore

INCLUDEPATH += $$PWD

SOURCES += \
    musicapplication.cpp \
    musicleftareawidget.cpp \
    musictopareawidget.cpp \
    musicrightareawidget.cpp \
    musicbottomareawidget.cpp \
    musicapplicationobject.cpp


HEADERS  += \
    musicapplication.h \
    musicleftareawidget.h \
    musictopareawidget.h \
    musicrightareawidget.h \
    musicbottomareawidget.h \
    musicapplicationobject.h
