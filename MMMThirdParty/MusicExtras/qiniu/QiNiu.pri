#-------------------------------------------------
#
#
# =================================================
# * This file is part of the MMM Music Player project
# * All rights reserved!
# * Redistribution and use of the source code or any derivative
# * works are strictly forbiden.
# =================================================

QT       += network

INCLUDEPATH += $$PWD

HEADERS  += \
    $$PWD/qnconf.h \
    $$PWD/qniohelper.h \
    $$PWD/qnmac.h \
    $$PWD/qnputextra.h \
    $$PWD/qnputpolicy.h \
    $$PWD/qnputret.h \
    $$PWD/qnutils.h \
    $$PWD/qnsimplelistdata.h \
    $$PWD/qnsimpleuploaddata.h \
    $$PWD/qnsimpledeletedata.h

SOURCES += \
    $$PWD/qnconf.cpp \
    $$PWD/qniohelper.cpp \
    $$PWD/qnmac.cpp \
    $$PWD/qnputextra.cpp \
    $$PWD/qnputpolicy.cpp \
    $$PWD/qnputret.cpp \
    $$PWD/qnutils.cpp \
    $$PWD/qnsimplelistdata.cpp \
    $$PWD/qnsimpleuploaddata.cpp \
    $$PWD/qnsimpledeletedata.cpp
