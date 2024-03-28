#include "musicradiosongsthread.h"

#ifdef MUSIC_GREATER_NEW
#   include <QJsonParseError>
#   include <QJsonDocument>
#   include <QJsonObject>
#   include <QJsonArray>
#else
#   ///QJson import
#   include "qjson/parser.h"
#endif

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkCookieJar>

#define LRC_PREFIX "http://musicdata.baidu.com"

MusicRadioSongsThread::MusicRadioSongsThread(QObject *parent, QNetworkCookieJar *cookie)
    : MusicRadioThreadAbstract(parent, cookie)
{

}

MusicRadioSongsThread::~MusicRadioSongsThread()
{
    deleteAll();
}

QString MusicRadioSongsThread::getClassName()
{
    return staticMetaObject.className();
}

void MusicRadioSongsThread::startToDownload(const QString &id)
{
    m_manager = new QNetworkAccessManager(this);

    QNetworkRequest request;
    request.setUrl(QUrl(songsUrl + id));
#ifndef QT_NO_SSL
    connect(m_manager, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)),
                       SLOT(sslErrors(QNetworkReply*,QList<QSslError>)));
    M_LOGGER_INFO(QString("%1 Support ssl: %2").arg(getClassName()).arg(QSslSocket::supportsSsl()));

    QSslConfiguration sslConfig = request.sslConfiguration();
    sslConfig.setPeerVerifyMode(QSslSocket::VerifyNone);
    request.setSslConfiguration(sslConfig);
#endif
    if(m_cookJar)
    {
        m_manager->setCookieJar(m_cookJar);
        m_cookJar->setParent(nullptr);
    }
    m_reply = m_manager->get(request);
    connect(m_reply, SIGNAL(finished()), SLOT(downLoadFinished()));
    connect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)), SLOT(replyError(QNetworkReply::NetworkError)));

}

SongRadioInfo MusicRadioSongsThread::getMusicSongInfo()
{
    return m_songInfo;
}

void MusicRadioSongsThread::downLoadFinished()
{
    if(m_reply == nullptr)
    {
        deleteAll();
        return;
    }

    if(m_reply->error() == QNetworkReply::NoError)
    {
        QByteArray bytes = m_reply->readAll();
#ifdef MUSIC_GREATER_NEW
        QJsonParseError jsonError;
        QJsonDocument parseDoucment = QJsonDocument::fromJson(bytes, &jsonError);
        ///Put the data into Json
        if(jsonError.error != QJsonParseError::NoError ||
           !parseDoucment.isObject())
        {
            deleteAll();
            return ;
        }

        QJsonObject jsonObject = parseDoucment.object();
        if(jsonObject.contains("data"))
        {
            jsonObject = jsonObject.value("data").toObject();
            if(jsonObject.contains("songList"))
            {
                QJsonArray array = jsonObject.value("songList").toArray();
                foreach(const QJsonValue &value, array)
                {
                    if(!value.isObject())
                    {
                       continue;
                    }
                    QJsonObject object = value.toObject();

                    m_songInfo.m_songUrl = object.value("songLink").toString();
                    m_songInfo.m_songName = object.value("songName").toString();
                    m_songInfo.m_artistName = object.value("artistName").toString();
                    m_songInfo.m_songPicUrl = object.value("songPicRadio").toString();
                    m_songInfo.m_albumName = object.value("albumName").toString();
                    QString lrcLink = object.value("lrcLink").toString();
                    if(!lrcLink.contains( LRC_PREFIX ))
                    {
                        lrcLink = LRC_PREFIX + lrcLink;
                    }
                    m_songInfo.m_lrcUrl = lrcLink;
                }
            }
        }
#else
        QJson::Parser parser;
        bool ok;
        QVariant data = parser.parse(bytes, &ok);
        if(ok)
        {
            QVariantMap value = data.toMap();
            value = value["data"].toMap();
            QVariantList songLists = value["songList"].toList();
            foreach(const QVariant &var, songLists)
            {
                value = var.toMap();
                if(value.isEmpty() || value["songLink"].toString().isEmpty())
                {
                    continue;
                }

                m_songInfo.m_songUrl = value["songLink"].toString();
                m_songInfo.m_songName = value["songName"].toString();
                m_songInfo.m_artistName = value["artistName"].toString();
                m_songInfo.m_songPicUrl = value["songPicRadio"].toString();
                m_songInfo.m_albumName = value["albumName"].toString();
                m_songInfo.m_lrcUrl = "http://musicdata.baidu.com" + value["lrcLink"].toString();
            }
        }
#endif
    }
    emit downLoadDataChanged("query finished!");
    deleteAll();
}
