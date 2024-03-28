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
    $$PWD/musicabstracttablewidget.h \
    $$PWD/musicabstractmovedialog.h \
    $$PWD/musicabstractmovewidget.h \
    $$PWD/musicabstractmoveresizewidget.h \
    $$PWD/musicitemdelegate.h \
    $$PWD/musicmarqueewidget.h \
    $$PWD/musicpreviewlabel.h \
    $$PWD/musicmessagebox.h \
    $$PWD/musicprogresswidget.h \
    $$PWD/musicclickedlabel.h \
    $$PWD/musicclickedslider.h \
    $$PWD/musicmovinglabelslider.h \
    $$PWD/musictoastlabel.h \
    $$PWD/musicroundanimationlabel.h \
    $$PWD/musiccodearea.h \
    $$PWD/musicgrabwidget.h \
    $$PWD/musicfloatabstractwidget.h \
    $$PWD/musictimersliderwidget.h \
    $$PWD/musiccutsliderwidget.h \
    $$PWD/musicanimationstackedwidget.h \
    $$PWD/musicuploadfilewidget.h \
    $$PWD/musictoolmenuwidget.h \
    $$PWD/musicgiflabelwidget.h
    
}

contains(CONFIG, MMM_BUILD_LIB){
SOURCES += \
    $$PWD/musicabstracttablewidget.cpp \
    $$PWD/musicabstractmovedialog.cpp \
    $$PWD/musicabstractmovewidget.cpp \
    $$PWD/musicabstractmoveresizewidget.cpp \
    $$PWD/musicitemdelegate.cpp \
    $$PWD/musicmarqueewidget.cpp \
    $$PWD/musicpreviewlabel.cpp \
    $$PWD/musicmessagebox.cpp \
    $$PWD/musicprogresswidget.cpp \
    $$PWD/musicclickedlabel.cpp \
    $$PWD/musicclickedslider.cpp \
    $$PWD/musicmovinglabelslider.cpp \
    $$PWD/musictoastlabel.cpp \
    $$PWD/musicroundanimationlabel.cpp \
    $$PWD/musiccodearea.cpp \
    $$PWD/musicgrabwidget.cpp \
    $$PWD/musicfloatabstractwidget.cpp \
    $$PWD/musictimersliderwidget.cpp \
    $$PWD/musiccutsliderwidget.cpp \
    $$PWD/musicanimationstackedwidget.cpp \
    $$PWD/musicuploadfilewidget.cpp \
    $$PWD/musictoolmenuwidget.cpp \
    $$PWD/musicgiflabelwidget.cpp

}
