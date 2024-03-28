#ifndef MUSICNETWORKTHREAD_H
#define MUSICNETWORKTHREAD_H

/* =================================================
 * This file is part of the MMM Music Player project
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "musicsingleton.h"

#include <QTimer>

#define M_NETWORK_PTR (MusicSingleton<MusicNetworkThread>::createInstance())

#define NETWORK_DETECT_INTERVAL 5000             // second
#define NETWORK_REQUEST_ADDRESS "www.baidu.com"  // ip

/*! @brief The class of thread to check current network.
 */
class MUSIC_NETWORK_EXPORT MusicNetworkThread : public QObject
{
    Q_OBJECT
public:
    static QString getClassName();
    /*!
     * Get class object name.
     */
    void start();
    /*!
     * Strat thread now.
     */
    void setBlockNetWork(int block);
    /*!
     * Set flag wheather to block current network.
     */
    inline bool isOnline() const {return m_networkState;}
    /*!
     * Check current network is on.
     */

Q_SIGNALS:
    void networkConnectionStateChanged(bool state);
    /*!
     * Network connection state changed.
     * default status is true, means connected network.
     */

public Q_SLOTS:
    void networkStateChanged();
    /*!
     * Network connection state changed.
     */

private:
    QTimer m_timer;
    bool m_networkState;

    MusicNetworkThread();
    /*!
     * Object contsructor.
     */
    ~MusicNetworkThread();

    DECLARE_SINGLETON_CLASS(MusicNetworkThread)
};

#endif // MUSICNETWORKTHREAD_H

