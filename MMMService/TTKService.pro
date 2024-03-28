#-------------------------------------------------
#
#
# =================================================
# * This file is part of the MMM Music Player project
# * All rights reserved!
# * Redistribution and use of the source code or any derivative
# * works are strictly forbiden.
# =================================================

TEMPLATE = app

contains(CONFIG, MMM_BUILD_LIB){
    CONFIG -= MMM_BUILD_LIB
}

CONFIG += MMM_NO_MSVC_LINK_NEED
win32{
    msvc{
        CONFIG -= MMM_NO_MSVC_LINK_NEED
    }
}
include(../MMMMusicPlayer.pri)
unix:VERSION += $$MMMMusicPlayer

win32{
  TARGET = ../../bin/$$MMMMusicPlayer/MMMService
  LIBS += -L../bin/$$MMMMusicPlayer -lMusicCore
}
unix{
  TARGET = ../lib/$$MMMMusicPlayer/MMMService
  LIBS += -L./lib/$$MMMMusicPlayer -lMusicCore
}


INCLUDEPATH += ../MMMCore

!contains(CONFIG, MMM_NO_MSVC_LINK_NEED){
HEADERS  += \
    ../MMMCore/musicapplication.h \
    ../MMMCore/musicleftareawidget.h \
    ../MMMCore/musictopareawidget.h \
    ../MMMCore/musicrightareawidget.h \
    ../MMMCore/musicbottomareawidget.h \
    ../MMMCore/musicapplicationobject.h

}

SOURCES += \
    musicservicemain.cpp

win32{
    RC_FILE = MMMService.rc
}
