#ifndef MUSICFILERECEIVESERVER_H
#define MUSICFILERECEIVESERVER_H

/* =================================================
 * This file is part of the MMM Music Player project
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "musicfilesenderserver.h"

/*! @brief The class of the file receive server.
 */
class MUSIC_TOOL_EXPORT MusicFileReceiveServer : public QObject
{
    Q_OBJECT
public:
    explicit MusicFileReceiveServer(QObject *parent = 0);
    /*!
     * Object contsructor.
     */
    ~MusicFileReceiveServer();

    static QString getClassName();
    /*!
     * Get class object name.
     */
    void setSavePathDir(const QString &dir);
    /*!
     * Set save file dir.
     */

private Q_SLOTS:
    void readPendingDatagrams();
    /*!
     * Read pending datagrams.
     */

protected:
    QFile *m_file;
    QUdpSocket *m_receiveSocket;
    QString m_saveDir;

};

#endif // MUSICFILERECEIVESERVER_H
