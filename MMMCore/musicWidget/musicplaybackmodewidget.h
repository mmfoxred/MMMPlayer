#ifndef MUSICPLAYBACKMODEWIDGET_H
#define MUSICPLAYBACKMODEWIDGET_H

/* =================================================
 * This file is part of the MMM Music Player project
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "musicobject.h"
#include "musictoolmenuwidget.h"

/*! @brief The class of the play back mode widget.
 */
class MUSIC_WIDGET_EXPORT MusicPlayBackModeWidget : public MusicToolMenuWidget
{
    Q_OBJECT
public:
    explicit MusicPlayBackModeWidget(QWidget *parent = 0);
    /*!
     * Object contsructor.
     */

    static QString getClassName();
    /*!
     * Get class object name.
     */

    void initWidget(QWidget *parent);
    /*!
     * Create all widget in layout.
     */

    void setPlaybackMode(MusicObject::SongPlayType mode);
    /*!
     * Set current play mode.
     */

};

#endif // MUSICPLAYBACKMODEWIDGET_H
