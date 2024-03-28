#ifndef MUSICAUDIORECORDERCORE_H
#define MUSICAUDIORECORDERCORE_H

/* =================================================
 * This file is part of the MMM Music Player project
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include <QFile>
#include <QAudioInput>
#include <QAudioOutput>
#include <QAudioDeviceInfo>
#include "musicglobaldefine.h"

#define RECORD_FILE         "record.raw"
#define RECORD_IN_FILE      "record_input.wav"
#define RECORD_OUT_FILE     "record_output.wav"

/*! @brief The class of the audio recorder core.
 */
class MUSIC_TOOLSET_EXPORT MusicAudioRecorderCore : public QObject
{
    Q_OBJECT
public:
    struct HEADER
    {
        char RIFFNAME[4];
        unsigned long nRIFFLength;
        char WAVNAME[4];
        char FMTNAME[4];
        unsigned long nFMTLength;
        unsigned short nAudioFormat;
        unsigned short nChannleNumber;
        unsigned long nSampleRate;
        unsigned long nBytesPerSecond;
        unsigned short nBytesPerSample;
        unsigned short    nBitsPerSample;
        char    DATANAME[4];
        unsigned long   nDataLength;
    };

    explicit MusicAudioRecorderCore(QObject *parent = 0);
    /*!
     * Object contsructor.
     */
    ~MusicAudioRecorderCore();

    static QString getClassName();
    /*!
     * Get class object name.
     */
    int addWavHeader(const char *filename);
    /*!
     * Add the header of wav.
     */

    void setFileName(const QString &name);
    /*!
     * Set output file name.
     */
    QString getFileName() const;
    /*!
     * Get output file name.
     */

public Q_SLOTS:
    void onRecordStart();
    /*!
     * Recorder play start.
     */
    void onRecordStop();
    /*!
     * Recorder play stop.
     */
    void onRecordPlay();
    /*!
     * Recorder play play.
     */
    void onStateChange(QAudio::State state);
    /*!
     * Recorder play state changed.
     */

protected:
    QAudioFormat m_mFormatFile;
    QFile *m_mpOutputFile;
    QAudioInput *m_mpAudioInputFile;
    QAudioOutput *m_mpAudioOutputFile;

};

#endif // MUSICAUDIORECORDERCORE_H
