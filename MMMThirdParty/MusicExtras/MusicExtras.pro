#-------------------------------------------------
#
#
# =================================================
# * This file is part of the MMM Music Player project
# * All rights reserved!
# * Redistribution and use of the source code or any derivative
# * works are strictly forbiden.
# =================================================

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

MMMMusicPlayer = 2.4.0.0
unix:VERSION += $$MMMMusicPlayer

win32{
    TARGET = ../../../bin/$$MMMMusicPlayer/MusicExtras
    msvc{
        LIBS += -luser32
    }
}
unix:TARGET = ../../lib/$$MMMMusicPlayer/MusicExtras
TEMPLATE = lib

QMAKE_CXXFLAGS += -std=c++11

INCLUDEPATH += ../../

win32{
    LIBS += -L../../bin/$$MMMMusicPlayer -lMusicUi
}
unix:!mac{
    LIBS += -L../../lib/$$MMMMusicPlayer -lMusicUi
}

HEADERS  += \
    musicextrasglobaldefine.h \
    ../../musicglobal.h \
    ../../musicprivate.h

include(hz2py/Hz2Py.pri)
include(kugou/KuGou.pri)
include(qiniu/QiNiu.pri)
include(qjson/QJson.pri)
include(qrencode/QRencode.pri)
include(shortcut/ShortCut.pri)
