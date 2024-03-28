#ifndef MUSICLOCALSONGSEARCHRECORDCONFIGMANAGER_H
#define MUSICLOCALSONGSEARCHRECORDCONFIGMANAGER_H

/* =================================================
 * This file is part of the MMM Music Player project
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "musicabstractxml.h"

typedef struct MUSIC_SEARCH_EXPORT MusicSearchRecord
{
    QString m_name;
    QString m_time;
}MusicSearchRecord;
MMM_DECLARE_LISTS(MusicSearchRecord)

/*! @brief The class of the search history Config.
 */
class MUSIC_SEARCH_EXPORT MusicLocalSongSearchRecordConfigManager : public MusicAbstractXml
{
    Q_OBJECT
public:
    explicit MusicLocalSongSearchRecordConfigManager(QObject *parent = 0);
    /*!
     * Object contsructor.
     */

    static QString getClassName();
    /*!
     * Get class object name.
     */
    inline bool readSearchXMLConfig(){ return readConfig(MUSICSEARCH_FULL); }
    /*!
     * Read history search datas from xml file by given name.
     */
    void writeSearchConfig(const MusicSearchRecords &records);
    /*!
     * Write history search datas into xml file.
     */
    void readSearchConfig(MusicSearchRecords &records);
    /*!
     * Read history search datas into xml file.
     */

};

#endif // MUSICLOCALSONGSEARCHRECORDCONFIGMANAGER_H
