#ifndef MUSICSONGSLISTITEMINFOWIDGET_H
#define MUSICSONGSLISTITEMINFOWIDGET_H

/* =================================================
 * This file is part of the MMM Music Player project
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include <QWidget>
#include "musicsong.h"
#include "musicglobaldefine.h"

namespace Ui {
class MusicSongsListItemInfoWidget;
}

/*! @brief The class of the song list item info widget.
 */
class MUSIC_WIDGET_EXPORT MusicSongsListItemInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MusicSongsListItemInfoWidget(QWidget *parent = 0);
    /*!
     * Object contsructor.
     */
    ~MusicSongsListItemInfoWidget();

    static QString getClassName();
    /*!
     * Get class object name.
     */
    void setMusicSongInformation(const MusicSong &info);
    /*!
     * Set music song information.
     */

protected:
    bool showArtPicture(const QString &name);
    /*!
     * Show artist small picture, if no exsit there is default pic.
     */

    Ui::MusicSongsListItemInfoWidget *ui;

};

#endif // MUSICSONGSLISTITEMINFOWIDGET_H
