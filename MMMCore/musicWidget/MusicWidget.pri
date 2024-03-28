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
    $$PWD/musicdownloadstatuslabel.h \
    $$PWD/musicquerytablewidget.h \
    $$PWD/musicsettingwidget.h \
    $$PWD/musicbackgroundskindialog.h \
    $$PWD/musicsystemtraymenu.h \
    $$PWD/musicequalizerdialog.h \
    $$PWD/musicwindowextras.h \
    $$PWD/musicsongslistwidget.h \
    $$PWD/musicsongslistiteminfowidget.h \
    $$PWD/musicsongsearchonlinewidget.h \
    $$PWD/musicsongstoolitemrenamedwidget.h \
    $$PWD/musicsongslistplaywidget.h \
    $$PWD/musicqualitychoicewidget.h \
    $$PWD/musicbackgroundremotewidget.h \
    $$PWD/musicbackgroundlistwidget.h \
    $$PWD/musicbackgroundpalettewidget.h \
    $$PWD/musicbackgroundpopwidget.h \
    $$PWD/musicenhancedwidget.h \
    $$PWD/musicdownloadwidget.h \
    $$PWD/musicdownloadmgmtwidget.h \
    $$PWD/musicsongsharingwidget.h \
    $$PWD/musicsourceupdatewidget.h \
    $$PWD/musicglobalhotkeyedit.h \
    $$PWD/musicsimilarfoundwidget.h \
    $$PWD/musicplaybackmodewidget.h \
    $$PWD/musicvolumepopwidget.h \
    $$PWD/musicmorefunctionspopwidget.h \
    $$PWD/musicplayedlistwidget.h

}

contains(CONFIG, MMM_BUILD_LIB){
SOURCES += \
    $$PWD/musicdownloadstatuslabel.cpp \
    $$PWD/musicquerytablewidget.cpp \
    $$PWD/musicsettingwidget.cpp \
    $$PWD/musicbackgroundskindialog.cpp \
    $$PWD/musicsystemtraymenu.cpp \
    $$PWD/musicequalizerdialog.cpp \
    $$PWD/musicwindowextras.cpp \
    $$PWD/musicsongslistwidget.cpp \
    $$PWD/musicsongslistiteminfowidget.cpp \
    $$PWD/musicsongsearchonlinewidget.cpp \
    $$PWD/musicsongstoolitemrenamedwidget.cpp \
    $$PWD/musicsongslistplaywidget.cpp \
    $$PWD/musicqualitychoicewidget.cpp \
    $$PWD/musicbackgroundremotewidget.cpp \
    $$PWD/musicbackgroundlistwidget.cpp \
    $$PWD/musicbackgroundpalettewidget.cpp \
    $$PWD/musicbackgroundpopwidget.cpp \
    $$PWD/musicenhancedwidget.cpp \
    $$PWD/musicdownloadwidget.cpp \
    $$PWD/musicdownloadmgmtwidget.cpp \
    $$PWD/musicsongsharingwidget.cpp \
    $$PWD/musicsourceupdatewidget.cpp \
    $$PWD/musicglobalhotkeyedit.cpp \
    $$PWD/musicsimilarfoundwidget.cpp \
    $$PWD/musicplaybackmodewidget.cpp \
    $$PWD/musicvolumepopwidget.cpp \
    $$PWD/musicmorefunctionspopwidget.cpp \
    $$PWD/musicplayedlistwidget.cpp

}
