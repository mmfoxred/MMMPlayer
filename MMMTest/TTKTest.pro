#-------------------------------------------------
#
#
# =================================================
# * This file is part of the MMM Music Player project
# * All rights reserved!
# * Redistribution and use of the source code or any derivative
# * works are strictly forbiden.
# =================================================

QT       += core gui testlib
equals(QT_MAJOR_VERSION, 5){
QT       += widgets
}

QMAKE_CXXFLAGS += -std=c++11
INCLUDEPATH += $$PWD/../

TARGET = MMMTest

TEMPLATE = app

HEADERS  += \
    musicautotest.h \
    tst_codelines.h

SOURCES  += \
    musicapplicationmain.cpp \
    tst_codelines.cpp

