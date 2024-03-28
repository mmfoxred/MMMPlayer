#ifndef MUSICDOWNLOADQUERYTHREADABSTRACT_H
#define MUSICDOWNLOADQUERYTHREADABSTRACT_H

/* =================================================
 * This file is part of the MMM Music Player project
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "musicobject.h"
#include "musicnetworkabstract.h"

typedef struct MUSIC_NETWORK_EXPORT DownloadData
{
    QString m_songName;
    QString m_songArtist;
    QString m_songUrl;
    QString m_picUrl;
    QString m_time;
    QString m_format;

    void clear()
    {
        m_songName.clear();
        m_songArtist.clear();
        m_songUrl.clear();
        m_picUrl.clear();
        m_time.clear();
        m_format.clear();
    }

    bool isValid() const
    {
        return !(m_songName.isEmpty() && m_time.isEmpty() && m_format.isEmpty());
    }

}DownloadData;

/*! @brief The class to abstract query download data from net.
 */
class MUSIC_NETWORK_EXPORT MusicDownLoadQueryThreadAbstract : public MusicNetworkAbstract
{
    Q_OBJECT
public:
    enum QueryType
    {
        MusicQuery, ///*query music*/
        MovieQuery, ///*query movie*/
        LrcQuery    ///*query lrc*/
    };

    explicit MusicDownLoadQueryThreadAbstract(QObject *parent = 0);
    /*!
     * Object contsructor.
     */
    virtual ~MusicDownLoadQueryThreadAbstract();

    static QString getClassName();
    /*!
     * Get class object name.
     */
    virtual void deleteAll() override;
    /*!
     * Release the network object.
     */
    virtual void startSearchSong(QueryType type, const QString &text) = 0;
    /*!
     * Start to search data from name and type.
     * Subclass should implement this function.
     */
    inline void setSearchQuality(const QString &qual) { m_searchQuality = qual;}
    /*!
     * Set search data quality.
     */
    inline QString getSearchQuality() const { return m_searchQuality;}
    /*!
     * Get search data quality.
     */
    inline void setQueryAllRecords(bool state) { m_queryAllRecords = state;}
    /*!
     * Set wheather query all quality of records.
     */
    inline bool getQueryAllRecords() const { return m_queryAllRecords;}
    /*!
     * Get query all records flag.
     */
    inline QueryType getQueryType() const { return m_currentType;}
    /*!
     * Return the current song query type.
     */
    inline QString getSearchedText() const { return m_searchText;}
    /*!
     * Return the current song name.
     */
    inline int getSongIdIndex() const { return m_musicSongInfos.size() + 1;}
    /*!
     * Return the current song container size.
     */
    inline const MusicObject::MusicSongInfomations& getMusicSongInfos(){ return m_musicSongInfos;}
    /*!
     * Return the current song container.
     */

Q_SIGNALS:
    void clearAllItems();
    /*!
     * Clear all items before the new query start.
     */
    void createSearchedItems(const QString &songname,
                             const QString &artistname, const QString &time);
    /*!
     * Create the current items by song name\ artist name and time.
     */

protected:
    MusicObject::MusicSongInfomations m_musicSongInfos;
    QString m_searchText, m_searchQuality;
    QueryType m_currentType;
    bool m_queryAllRecords;

};

#endif // MUSICDOWNLOADQUERYTHREADABSTRACT_H
