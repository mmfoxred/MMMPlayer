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
    $$PWD/musiclrcmanager.h \
    $$PWD/musiclrcmanagerfordesktop.h \
    $$PWD/musiclrcmanagerforinline.h \
    $$PWD/musiclrccontainer.h \
    $$PWD/musiclrccontainerfordesktop.h \
    $$PWD/musiclrccontainerforinline.h \
    $$PWD/musiclrcsearchwidget.h \
    $$PWD/musiclrcsearchtablewidget.h \
    $$PWD/musiclrcartphotoupload.h \
    $$PWD/musiclrcartphotolabel.h \
    $$PWD/musiclrcfloatwidget.h \
    $$PWD/musiclrcfloatsettingwidget.h \
    $$PWD/musiclrcfloatphotowidget.h \
    $$PWD/musiclrcmakerwidget.h \
    $$PWD/musiclrcanalysis.h \
    $$PWD/musiclrcerrorwidget.h \
    $$PWD/musiclrclocallinkwidget.h \
    $$PWD/musiclrcfromkrc.h

}

contains(CONFIG, MMM_BUILD_LIB){
SOURCES += \
    $$PWD/musiclrcmanager.cpp \
    $$PWD/musiclrcmanagerfordesktop.cpp \
    $$PWD/musiclrcmanagerforinline.cpp \
    $$PWD/musiclrccontainer.cpp \
    $$PWD/musiclrccontainerfordesktop.cpp \
    $$PWD/musiclrccontainerforinline.cpp \
    $$PWD/musiclrcsearchwidget.cpp \
    $$PWD/musiclrcsearchtablewidget.cpp \
    $$PWD/musiclrcartphotoupload.cpp \
    $$PWD/musiclrcartphotolabel.cpp \
    $$PWD/musiclrcfloatwidget.cpp \
    $$PWD/musiclrcfloatsettingwidget.cpp \
    $$PWD/musiclrcfloatphotowidget.cpp \
    $$PWD/musiclrcmakerwidget.cpp \
    $$PWD/musiclrcanalysis.cpp \
    $$PWD/musiclrcerrorwidget.cpp \
    $$PWD/musiclrclocallinkwidget.cpp \
    $$PWD/musiclrcfromkrc.cpp

}
