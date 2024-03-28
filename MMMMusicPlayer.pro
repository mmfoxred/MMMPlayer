MMMMusicPlayer = 1.0.0.0

TEMPLATE = subdirs
SUBDIRS = MMMQrc MMMThirdParty MMMCore MMMApp MMMService MMMTest

##update translation
unix:exists($$[QT_INSTALL_BINS]/lrelease){
LRELEASE_EXECUTABLE = $$[QT_INSTALL_BINS]/lrelease
}

unix:exists($$[QT_INSTALL_BINS]/lrelease-qt5){
LRELEASE_EXECUTABLE = $$[QT_INSTALL_BINS]/lrelease-qt5
}

win32:exists($$[QT_INSTALL_BINS]/lrelease.exe){
LRELEASE_EXECUTABLE = $$[QT_INSTALL_BINS]/lrelease.exe
}

isEmpty(LRELEASE_EXECUTABLE){
  error(Could not find lrelease executable)
}
else{
  message(Found lrelease executable: $$LRELEASE_EXECUTABLE)
}

unix:{
    output = $$OUT_PWD/lib/$$MMMMusicPlayer/MLanguage
    !exists($$output):system(mkdir $$output)

    system(find . -name *.ts | xargs $$LRELEASE_EXECUTABLE)
    system(find . -name *.qm | xargs rename -vf 's/.qm/.ln/' *  )
    system(for F in MMMLanguage/*.ln ; do mv $F $$output ;done)
}
win32:{
    output = $$OUT_PWD/bin/$$MMMMusicPlayer/MLanguage
    output = $$replace(output, /, \\)
    !exists($$output):system(md $$output)

    system(for /r %i in (*.ts) do $$LRELEASE_EXECUTABLE %i)
    system(for /r %i in (*.qm) do ren %i *.ln)
    system(for /r %i in (*.ln) do move /y %i $$output)
}
