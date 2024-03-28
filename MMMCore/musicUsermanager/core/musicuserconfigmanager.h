#ifndef MUSICXMLCONFIGMANAGER_H
#define MUSICXMLCONFIGMANAGER_H

/* =================================================
 * This file is part of the MMM Music Player project
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "musicabstractxml.h"

typedef struct MUSIC_USER_EXPORT MusicUserRecord
{
    QString m_name;
    QString m_rp;
    QString m_al;
    QString m_pwd;
}MusicUserRecord;
MMM_DECLARE_LISTS(MusicUserRecord)

/*! @brief The class of the user config manager.
 */
class MUSIC_USER_EXPORT MusicUserConfigManager : public MusicAbstractXml
{
    Q_OBJECT
public:
    explicit MusicUserConfigManager(QObject *parent = 0);
    /*!
     * Object contsructor.
     */

    static QString getClassName();
    /*!
     * Get class object name.
     */
    inline bool readUserXMLConfig(){ return readConfig(USERPATH_FULL); }
    /*!
     * Read user datas from xml file by given name.
     */
    void writeUserXMLConfig(const MusicUserRecords &records);
    /*!
     * Write user datas into xml file.
     */
    void readUserConfig(MusicUserRecords &records);
    /*!
     * Read user datas into xml file.
     */

};

#endif // MUSICXMLCONFIGMANAGER_H
