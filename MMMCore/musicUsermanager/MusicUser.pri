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
    $$PWD/core/musicusermodel.h \
    $$PWD/core/musicuserconfigmanager.h \
    $$PWD/musicusermanager.h \
    $$PWD/musicuserdialog.h \
    $$PWD/musicuserlineedit.h \
    $$PWD/musicuserwindow.h \
    $$PWD/musicuserrecordwidget.h
    
}

contains(CONFIG, MMM_BUILD_LIB){
SOURCES += \
    $$PWD/core/musicusermodel.cpp \
    $$PWD/core/musicuserconfigmanager.cpp \
    $$PWD/musicusermanager.cpp \
    $$PWD/musicuserdialog.cpp \
    $$PWD/musicuserlineedit.cpp \
    $$PWD/musicuserwindow.cpp \
    $$PWD/musicuserrecordwidget.cpp

}
