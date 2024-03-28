#ifndef MUSICSONGSEARCHONLINEWIDGET_H
#define MUSICSONGSEARCHONLINEWIDGET_H

/* =================================================
 * This file is part of the MMM Music Player project
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "musicdownloadquerythreadabstract.h"
#include "musicquerytablewidget.h"

#define AUDITION_PLAY MStatic_cast(int, Qt::yellow)
#define AUDITION_STOP MStatic_cast(int, Qt::transparent)

class MusicCoreMPlayer;
class MusicDataDownloadThread;
class MusicTextDownLoadThread;

/*! @brief The class of the song search online table widget.
 */
class MUSIC_WIDGET_EXPORT MusicSongSearchOnlineTableWidget : public MusicQueryTableWidget
{
    Q_OBJECT
public:
    explicit MusicSongSearchOnlineTableWidget(QWidget *parent = 0);
    /*!
     * Object contsructor.
     */
    virtual ~MusicSongSearchOnlineTableWidget();

    static QString getClassName();
    /*!
     * Get class object name.
     */
    virtual void startSearchQuery(const QString &text) override;
    /*!
     * Start search query by text.
     */
    virtual void musicDownloadLocal(int row) override;
    /*!
     * Data download to local file.
     */

    void auditionToMusic(int row);
    /*!
     * Start play audition to music by row.
     */
    void auditionToMusicStop(int row);
    /*!
     * Stop play audition to music by row.
     */
    void setSearchQuality(const QString &quality);
    /*!
     * Set search data quality.
     */

Q_SIGNALS:
    void muiscSongToPlayListChanged(const QString &name, const QString &time,
                                    const QString &format, bool play);
    /*!
     * Add current network music to download to local.
     */
    void auditionIsPlaying(bool play);
    /*!
     * Check current audtion is playing or not.
     */

public Q_SLOTS:
    virtual void listCellClicked(int row, int column) override;
    /*!
     * Table widget list cell click.
     */
    virtual void clearAllItems() override;
    /*!
     * Clear All Items.
     */
    virtual void createSearchedItems(const QString &songname, const QString &artistname,
                                     const QString &time) override;
    /*!
     * Create searched items.
     */
    virtual void itemDoubleClicked(int row, int column) override;
    /*!
     * Item has double clicked.
     */
    virtual void actionGroupClick(QAction *action) override;
    /*!
     * Left context menu action group click by action.
     */
    void searchDataDwonloadFinished();
    /*!
     * Search data dwonload finished.
     */

protected:
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void contextMenuEvent(QContextMenuEvent *event) override;
    /*!
     * Override the widget event.
     */
    void addSearchMusicToPlayList(int row);
    /*!
     * Add search music to play list by index.
     */

    int m_previousAuditionRow;
    MusicCoreMPlayer *m_audition;
    DownloadData m_downloadData;

};


class QLabel;
class QPushButton;

/*! @brief The class of the song search online widget.
 */
class MUSIC_WIDGET_EXPORT MusicSongSearchOnlineWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MusicSongSearchOnlineWidget(QWidget *parent = 0);
    /*!
     * Object contsructor.
     */
    ~MusicSongSearchOnlineWidget();

    static QString getClassName();
    /*!
    * Get class object name.
    */
    void startSearchQuery(const QString &name);
    /*!
     * Start search query by text.
     */
    void researchQueryByQuality(const QString &name, const QString &quality);
    /*!
     * Research query by quality it changed.
     */

public Q_SLOTS:
    void buttonClicked(int index);
    /*!
     * Set diff button clicked by index.
     */
    void auditionIsPlaying(bool play);
    /*!
     * Check current audtion is playing or not.
     */

protected:
    virtual void resizeEvent(QResizeEvent *event) override;
    /*!
     * Override the widget event.
     */
    void createToolWidget(QWidget *widget);
    /*!
     * Create tool widget.
     */
    void setResizeLabelText(const QString &name);
    /*!
     * Set resize labelt ext.
     */

    QLabel *m_textLabel;
    QPushButton *m_playButton;
    MusicSongSearchOnlineTableWidget *m_searchTableWidget;

};

#endif // MUSICSONGSEARCHONLINEWIDGET_H
