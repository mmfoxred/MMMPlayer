#ifndef MUSICMOBILEDEVICESTHREAD_H
#define MUSICMOBILEDEVICESTHREAD_H

/* =================================================
 * This file is part of the MMM Music Player project
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include <QThread>
#include "musicglobaldefine.h"

#define UEVENT_BUFFER_SIZE 2048

/*! @brief The class of the mobile devices thread.
 */
class MUSIC_TOOLSET_EXPORT MusicMobileDevicesThread : public QThread
{
    Q_OBJECT
public:
    explicit MusicMobileDevicesThread(QObject *parent = 0);
    /*!
     * Object contsructor.
     */
    ~MusicMobileDevicesThread();

    static QString getClassName();
    /*!
     * Get class object name.
     */
    void stopAndQuitThread();
    /*!
     * Stop and quit current thread.
     */

Q_SIGNALS:
    void devicesChanged(bool state);
    /*!
     * Send current devices changed emit\ true add\ false remove.
     */

public Q_SLOTS:
    void start();
    /*!
     * Strat thread now.
     */
    void run();
    /*!
     * Thread run now.
     */

protected:
    int initHotPlugSock();
    /*!
     * Init hot plug sock.
     */

    bool m_run;

};

#endif // MUSICMOBILEDEVICESTHREAD_H
