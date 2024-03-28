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
    $$PWD/core/musicmydownloadrecordconfigmanager.h \
    $$PWD/core/musicwebentainradiodatebase.h \
    $$PWD/core/musicfilesenderserver.h \
    $$PWD/core/musicfilereceiveserver.h \
    $$PWD/musicsongstoolboxwidget.h \
    $$PWD/musicsongssummarizied.h \
    $$PWD/musicsongssummariziedfloatwidget.h \
    $$PWD/musictoolsetswidget.h \
    $$PWD/musicmydownloadrecordwidget.h \
    $$PWD/musicconnectmobilewidget.h \
    $$PWD/musicconnecttransferwidget.h \
    $$PWD/musicconnecttransfertablewidget.h \
    $$PWD/musicwebradiotoolwidget.h \
    $$PWD/musicwebentainradiowidget.h \
    $$PWD/musicwebentainradiolistview.h \
    $$PWD/musicwebmusicradiolistview.h  \
    $$PWD/musicwebmusicradiowidget.h \
    $$PWD/musiccloudsharedsongwidget.h \
    $$PWD/musiccloudfilemanagerdialog.h

}

contains(CONFIG, MMM_BUILD_LIB){
SOURCES += \
    $$PWD/core/musicmydownloadrecordconfigmanager.cpp \
    $$PWD/core/musicwebentainradiodatebase.cpp \
    $$PWD/core/musicfilesenderserver.cpp \
    $$PWD/core/musicfilereceiveserver.cpp \
    $$PWD/musicsongstoolboxwidget.cpp \
    $$PWD/musicsongssummarizied.cpp \
    $$PWD/musicsongssummariziedfloatwidget.cpp \
    $$PWD/musictoolsetswidget.cpp \
    $$PWD/musicmydownloadrecordwidget.cpp \
    $$PWD/musicconnectmobilewidget.cpp \
    $$PWD/musicconnecttransferwidget.cpp \
    $$PWD/musicconnecttransfertablewidget.cpp \
    $$PWD/musicwebradiotoolwidget.cpp \
    $$PWD/musicwebentainradiowidget.cpp \
    $$PWD/musicwebentainradiolistview.cpp \
    $$PWD/musicwebmusicradiolistview.cpp \
    $$PWD/musicwebmusicradiowidget.cpp \
    $$PWD/musiccloudsharedsongwidget.cpp \
    $$PWD/musiccloudfilemanagerdialog.cpp

}
