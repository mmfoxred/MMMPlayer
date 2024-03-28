#-------------------------------------------------
#
#
# =================================================
# * This file is part of the MMM Music Player project
# * All rights reserved!
# * Redistribution and use of the source code or any derivative
# * works are strictly forbiden.
# =================================================

INCLUDEPATH += $$PWD \
               $$PWD/core

!contains(CONFIG, MMM_NO_MSVC_LINK_NEED){
HEADERS  += \
    $$PWD/core/musiclocalsongsearchrecordconfigmanager.h \
    $$PWD/musiclocalsongsearchedit.h \
    $$PWD/musiclocalsongsearchinlineedit.h \
    $$PWD/musiclocalsongsearchpopwidget.h \
    $$PWD/musiclocalsongsearchdialog.h

}

contains(CONFIG, MMM_BUILD_LIB){
SOURCES += \
    $$PWD/core/musiclocalsongsearchrecordconfigmanager.cpp \
    $$PWD/musiclocalsongsearchedit.cpp \
    $$PWD/musiclocalsongsearchinlineedit.cpp \
    $$PWD/musiclocalsongsearchpopwidget.cpp \
    $$PWD/musiclocalsongsearchdialog.cpp
}
