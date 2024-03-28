#-------------------------------------------------
#
#
# =================================================
# * This file is part of the MMM Music Player project
# * All rights reserved!
# * Redistribution and use of the source code or any derivative
# * works are strictly forbiden.
# =================================================

INCLUDEPATH += $$PWD

!contains(CONFIG, MMM_NO_MSVC_LINK_NEED){
HEADERS  += \
    $$PWD/musiclogger.h \
    $$PWD/musicobject.h \
    $$PWD/musicuiobject.h \
    $$PWD/musicMMMuiobject.h \
    $$PWD/musicutils.h \
    $$PWD/musicnumberdefine.h \
    $$PWD/musicglobaldefine.h \
    $$PWD/musicglobalhotkey.h \
    $$PWD/musicversion.h \
    $$PWD/musictime.h \
    $$PWD/musicxmlconfigmanager.h \
    $$PWD/musicplayer.h \
    $$PWD/musicplaylist.h \
    $$PWD/musicabstractxml.h \
    $$PWD/musicsettingmanager.h \
    $$PWD/musicconnectionpool.h \
    $$PWD/musicregeditmanager.h \
    $$PWD/musicsingleton.h \
    $$PWD/musiccoremplayer.h \
    $$PWD/musicsong.h \
    $$PWD/musiccryptographichash.h \
    $$PWD/musicbackgroundmanager.h \
    $$PWD/musicsystemenvironment.h

}

contains(CONFIG, MMM_BUILD_LIB){
SOURCES += \
    $$PWD/musicutils.cpp \
    $$PWD/musicglobalhotkey.cpp \
    $$PWD/musictime.cpp \
    $$PWD/musicplayer.cpp \
    $$PWD/musicplaylist.cpp \
    $$PWD/musicabstractxml.cpp \
    $$PWD/musicxmlconfigmanager.cpp \
    $$PWD/musicconnectionpool.cpp \
    $$PWD/musicregeditmanager.cpp \
    $$PWD/musiccoremplayer.cpp \
    $$PWD/musicsong.cpp \
    $$PWD/musiccryptographichash.cpp \
    $$PWD/musicbackgroundmanager.cpp \
    $$PWD/musicsystemenvironment.cpp

}