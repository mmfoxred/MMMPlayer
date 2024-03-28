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
unix:VERSION += $$MMMMusicPlayer

win32:TARGET = ../../bin/$$MMMMusicPlayer/MusicUi
unix:TARGET = ../lib/$$MMMMusicPlayer/MusicUi

RESOURCES += \
    MusicPlayer.qrc \
    MusicThirdParty.qrc
