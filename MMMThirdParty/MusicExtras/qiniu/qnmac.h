#ifndef QNMAC_H
#define QNMAC_H

/* =================================================
 * This file is part of the MMM Music Player project
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include <QNetworkRequest>
#include "musicprivate.h"
#include "musicextrasglobaldefine.h"

class QNMacPrivate;

class MUSIC_EXTRAS_EXPORT QNMac
{
public:
    QNMac(const QString &accessKey, const QByteArray &secretKey);

    QString sign(const QByteArray &data) const;
    QString signWithData(const QByteArray &data) const;
    QString signWithData2(const QByteArray &data) const;
    QString signRequest(const QUrl &reqestUrl, const QByteArray &bodyData = 0) const;
    QString signRequest(const QNetworkRequest &request, const QByteArray &bodyData = 0) const;

private:
    MMM_DECLARE_PRIVATE(QNMac)

};

#endif // QNMAC_H
