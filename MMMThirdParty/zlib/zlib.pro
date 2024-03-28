#-------------------------------------------------
#
#
# =================================================
# * This file is part of the MMM Music Player project
# * All rights reserved!
# * Redistribution and use of the source code or any derivative
# * works are strictly forbiden.
# =================================================

TEMPLATE = lib

MMMMusicPlayer = 2.4.0.0
#unix:VERSION += $$MMMMusicPlayer

win32:TARGET = ../../../bin/$$MMMMusicPlayer/zlib
unix:TARGET = ../../lib/$$MMMMusicPlayer/zlib

CONFIG       += warn_off
unix:VERSION += 1.2.8

HEADERS  += \
    $$PWD/zconf.h \
    $$PWD/zlib.h \
    $$PWD/crc32.h \
    $$PWD/deflate.h \
    $$PWD/gzguts.h \
    $$PWD/inffixed.h \
    $$PWD/inffast.h \
    $$PWD/inflate.h \
    $$PWD/inftrees.h \
    $$PWD/trees.h \
    $$PWD/zutil.h

SOURCES += \
    $$PWD/adler32.c \
    $$PWD/compress.c \
    $$PWD/crc32.c \
    $$PWD/deflate.c \
    $$PWD/gzclose.c \
    $$PWD/gzlib.c \
    $$PWD/gzread.c \
    $$PWD/gzwrite.c \
    $$PWD/inflate.c \
    $$PWD/infback.c \
    $$PWD/inftrees.c \
    $$PWD/inffast.c \
    $$PWD/trees.c \
    $$PWD/uncompr.c \
    $$PWD/zutil.c
