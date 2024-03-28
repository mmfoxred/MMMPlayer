#ifndef MUSICRADIOSONGSTHREAD_H
#define MUSICRADIOSONGSTHREAD_H

/* =================================================
 * This file is part of the MMM Music Player project
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "musicradiothreadabstract.h"

typedef struct MUSIC_NETWORK_EXPORT SongRadioInfo
{
    QString m_songUrl;
    QString m_songName;
    QString m_artistName;
    QString m_songPicUrl;
    QString m_albumName;
    QString m_lrcUrl;
}SongRadioInfo;
MMM_DECLARE_LISTS(SongRadioInfo)

/*! @brief The class of music radio thread of song info.
 */
class MUSIC_NETWORK_EXPORT MusicRadioSongsThread : public MusicRadioThreadAbstract
{
    Q_OBJECT
public:
    explicit MusicRadioSongsThread(QObject *parent = 0, QNetworkCookieJar *cookie = 0);
    /*!
     * Object contsructor.
     */
    virtual ~MusicRadioSongsThread();

    static QString getClassName();
    /*!
     * Get class object name.
     */
    virtual void startToDownload(const QString &id) override;
    /*!
     * Start to download data.
     */
    SongRadioInfo getMusicSongInfo();
    /*!
     * Get music song information.
     */

public Q_SLOTS:
    virtual void downLoadFinished() override;
    /*!
     * Download data from net finished.
     */

protected:
    SongRadioInfo m_songInfo;

};

#endif // MUSICRADIOSONGSTHREAD_H
