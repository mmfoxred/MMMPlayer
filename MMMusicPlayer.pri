#-------------------------------------------------
#
#
# =================================================
# * This file is part of the MMM Music Player project
# * All rights reserved!
# * Redistribution and use of the source code or any derivative
# * works are strictly forbiden.
# =================================================

QT       += core gui xml sql

equals(QT_MAJOR_VERSION, 4){
QT       += network
CONFIG   += gcc
include(MMMExtra/Qt4/qmmp.pri)
}
equals(QT_MAJOR_VERSION, 5){
QT       += widgets multimediawidgets
include(MMMExtra/Qt5/qmmp.pri)
}

UI_DIR = ./.build/ui/
MOC_DIR = ./.build/moc/
OBJECTS_DIR = ./.build/obj
RCC_DIR = ./.build/rcc

#check Qt version
QT_VER_STRING = $$[QT_VERSION];
QT_VER_STRING = $$split(QT_VER_STRING, ".")
QT_VER_MAJOR = $$member(QT_VER_STRING, 0)
QT_VER_MINOR = $$member(QT_VER_STRING, 1)
QT_VER_PATCH = $$member(QT_VER_STRING, 2)

MMMMusicPlayer = 2.4.0.0

win32{
    LIBS += -lIphlpapi -luser32
    equals(QT_MAJOR_VERSION, 5){
        greaterThan(QT_VER_MINOR, 1):QT  += winextras
        msvc{
            LIBS += -L../bin/$$MMMMusicPlayer -lqmmp1 -lMusicUi -lMusicExtras -lzlib
            !contains(QMAKE_TARGET.arch, x86_64){
                 #support on windows XP
                 QMAKE_LFLAGS_WINDOWS = /SUBSYSTEM:WINDOWS,5.01
                 QMAKE_LFLAGS_CONSOLE = /SUBSYSTEM:CONSOLE,5.01
            }
        }

        gcc{
            LIBS += -L../bin/$$MMMMusicPlayer -lqmmp1 -lMusicUi -lMusicExtras -lzlib
            QMAKE_CXXFLAGS += -std=c++11
            QMAKE_CXXFLAGS += -Wunused-function
            QMAKE_CXXFLAGS += -Wswitch
        }
    }

    equals(QT_MAJOR_VERSION, 4){
        QT  += multimedia
        gcc{
            LIBS += -L../bin/$$MMMMusicPlayer -lqmmp0 -lMusicUi -lMusicExtras -lzlib
            QMAKE_CXXFLAGS += -std=c++11
            QMAKE_CXXFLAGS += -Wunused-function
            QMAKE_CXXFLAGS += -Wswitch
        }
    }
}

unix:!mac{
    equals(QT_MAJOR_VERSION, 4){
        QMAKE_CXXFLAGS += -I/usr/include/QtMultimediaKit \
                          -I/usr/include/QtMobility
        LIBS += -lQtMultimediaKit
    }

    QMAKE_CXXFLAGS += -std=c++11
    QMAKE_CXXFLAGS += -Wunused-function
    QMAKE_CXXFLAGS += -Wswitch
    LIBS += -L../lib/$$MMMMusicPlayer -lqmmp -lMusicUi -lMusicExtras -lzlib
}

DEFINES += MUSIC_LIBRARY
DEFINES += USE_MULTIPLE_QUERY


#########################################
HEADERS += $$PWD/musicglobal.h
INCLUDEPATH += $$PWD
#########################################
contains(CONFIG, MMM_BUILD_LIB){
  include(MMMCore/musicUi/MusicUi.pri)
}
#########################################
include(MMMThirdParty/MMMThirdParty.pri)
#########################################
include(MMMCore/musicCore/MusicCore.pri)
include(MMMCore/musicNetwork/MusicNetwork.pri)
include(MMMCore/musicWidget/MusicWidget.pri)
include(MMMCore/musicWidgetCore/MusicWidgetCore.pri)
include(MMMCore/musicLocalsearch/MusicLocalSearch.pri)
include(MMMCore/musicLrcmanager/MusicLrc.pri)
include(MMMCore/musicRemotewidget/MusicRemote.pri)
include(MMMCore/musicToolsetswidget/MusicToolsSets.pri)
include(MMMCore/musicToolswidget/MusicToolsWidget.pri)
include(MMMCore/musicUsermanager/MusicUser.pri)
include(MMMCore/musicVideokits/MusicVideo.pri)
