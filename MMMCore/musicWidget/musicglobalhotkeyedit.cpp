#include "musicglobalhotkeyedit.h"
#include "musicglobalhotkey.h"

#include <QKeyEvent>

MusicGlobalHotKeyEdit::MusicGlobalHotKeyEdit(QWidget *parent)
    : QLineEdit(parent)
{
    setReadOnly(true);
}

MusicGlobalHotKeyEdit::~MusicGlobalHotKeyEdit()
{

}

QString MusicGlobalHotKeyEdit::getClassName()
{
    return staticMetaObject.className();
}

void MusicGlobalHotKeyEdit::keyPressEvent(QKeyEvent *event)
{
    setText( M_HOTKEY_PTR->toString(event->key(), event->modifiers()) );
    QLineEdit::keyPressEvent(event);
}
