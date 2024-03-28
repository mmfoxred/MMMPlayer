#ifndef MUSICVOICETTSTHREAD_H
#define MUSICVOICETTSTHREAD_H

/* =================================================
 * This file is part of the MMM Music Player project
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "musicglobaldefine.h"

const QString VOICETTS_URL = "http://tts.baidu.com/text2audio?lan=%1&ie=UTF-8&text=%2&spd=%3&pit=%4&vol=%5&per=%6";

class MusicSourceDownloadThread;

/*! @brief The class of translation voice by tts thread.
 */
class MUSIC_NETWORK_EXPORT MusicVoiceTtsThread : public QObject
{
    Q_OBJECT
public:
    enum TranslationType
    {
        Type_Uk,    ///English
        Type_En,    ///American English
        Type_Zh     ///Chinese
    };

    explicit MusicVoiceTtsThread(QObject *parent = 0);
    /*!
     * Object contsructor.
     */
    ~MusicVoiceTtsThread();

    static QString getClassName();
    /*!
     * Get class object name.
     */
    void setSpeed(int speed);
    /*!
     * Set speed.
     */
    int getSpeed() const;
    /*!
     * Get speed.
     */

    void setPitch(int pitch);
    /*!
     * Set pitch.
     */
    int getPitch() const;
    /*!
     * Get pitch.
     */

    void setVolume(int volume);
    /*!
     * Set volume.
     */
    int getVolume() const;
    /*!
     * Get volume.
     */

    void setPerson(int person);
    /*!
     * Set person.
     */
    int getPerson() const;
    /*!
     * Get person.
     */

    void startToTranslation(TranslationType type, const QString &data);
    /*!
     * Start to translation data.
     */

Q_SIGNALS:
    void downLoadDataChanged(const QByteArray &data);
    /*!
     * Send translated data from net.
     */

protected:
    QString mapTypeFromEnumToString(TranslationType type);
    /*!
     * Map type from enum to string.
     */

    int m_speed, m_pitch, m_volume, m_person;
    MusicSourceDownloadThread *m_parser;

};

#endif // MUSICVOICETTSTHREAD_H
