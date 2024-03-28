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
    $$PWD/core/musicbarragerecordconfigmanager.h \
    $$PWD/core/musicbarragewidget.h \
    $$PWD/musicvideoqualitypopwidget.h \
    $$PWD/musicvideobarragestylepopwidget.h \
    $$PWD/musicvideocontrol.h \
    $$PWD/musicvideoview.h \
    $$PWD/musicvideotablewidget.h \
    $$PWD/musicvideoplaywidget.h \
    $$PWD/musicvideofloatwidget.h

}

contains(CONFIG, MMM_BUILD_LIB){
SOURCES += \
    $$PWD/core/musicbarragerecordconfigmanager.cpp \
    $$PWD/core/musicbarragewidget.cpp \
    $$PWD/musicvideoqualitypopwidget.cpp \
    $$PWD/musicvideobarragestylepopwidget.cpp \
    $$PWD/musicvideocontrol.cpp \
    $$PWD/musicvideoview.cpp \
    $$PWD/musicvideotablewidget.cpp \
    $$PWD/musicvideoplaywidget.cpp \
    $$PWD/musicvideofloatwidget.cpp

}
