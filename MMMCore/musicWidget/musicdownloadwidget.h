#ifndef MUSICDOWNLOADWIDGET_H
#define MUSICDOWNLOADWIDGET_H

/* =================================================
 * This file is part of the MMM Music Player project
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "musicabstractmovewidget.h"
#include "musicabstracttablewidget.h"
#include "musicdownloadquerythreadabstract.h"

#define ROW_HEIGHT  25

namespace Ui {
class MusicDownloadWidget;
}
class QLabel;

/*! @brief The class of the download table item.
 */
class MUSIC_WIDGET_EXPORT MusicDownloadTableItem : public QWidget
{
    Q_OBJECT
public:
    explicit MusicDownloadTableItem(QWidget *parent = 0);
    /*!
     * Object contsructor.
     */
    ~MusicDownloadTableItem();

    static QString getClassName();
    /*!
     * Get class object name.
     */
    void setIcon(const QString &name);
    /*!
     * Set current item icon.
     */
    void setInfomation(const QString &info);
    /*!
     * Set current item other infomation(size\type\time).
     */
    void setText(const QString &text);
    /*!
     * Set current item text name.
     */

protected:
    QLabel *m_text, *m_infomation, *m_icon;

};

#define BITRATE_ROLE Qt::UserRole + 1

/*! @brief The class of the download table widget.
 */
class MUSIC_WIDGET_EXPORT MusicDownloadTableWidget : public MusicAbstractTableWidget
{
    Q_OBJECT
public:
    explicit MusicDownloadTableWidget(QWidget *parent = 0);
    /*!
     * Object contsructor.
     */
    virtual ~MusicDownloadTableWidget();

    static QString getClassName();
    /*!
     * Get class object name.
     */
    void clearAllItems();
    /*!
     * Clear All Items.
     */
    void createItem(int bitrate, const QString &type, const QString &info,
                    const QString &icon);
    /*!
     * Create current itrm by given bitrate\type\icon\otherinfo.
     */
    int getCurrentBitrate();
    /*!
     * Get current bitrate from item.
     */

public Q_SLOTS:
    virtual void listCellClicked(int row, int column) override;
    /*!
     * Table widget list cell click.
     */

protected:
    QList<QObject*> m_items;

};

/*! @brief The class of the download widget.
 */
class MUSIC_WIDGET_EXPORT MusicDownloadWidget : public MusicAbstractMoveWidget
{
    Q_OBJECT
public:
    explicit MusicDownloadWidget(QWidget *parent = 0);
    /*!
     * Object contsructor.
     */
    virtual ~MusicDownloadWidget();

    static QString getClassName();
    /*!
     * Get class object name.
     */
    void setSongName(const QString &name, MusicDownLoadQueryThreadAbstract::QueryType type);
    /*!
     * Set current name to search and download musics.
     */

Q_SIGNALS:
    void dataDownloadChanged();
    /*!
     * Data download changed.
     */

public Q_SLOTS:
    void show();
    /*!
     * Override show function.
     */
    void queryAllFinished();
    /*!
     * Query all quality musics is finished.
     */
    void downloadDirSelected();
    /*!
     * Change data download save path.
     */
    void startToDownload();
    /*!
     * Start to download music data.
     */
    void dataDownloadFinished();
    /*!
     * Data download is finished.
     */

protected:
    void initWidget();
    /*!
     * Create all widget in layout.
     */
    void controlEnable(bool enable);
    /*!
     * Enable or disable control state.
     */
    void resizeWindow();
    /*!
     * Automatically adjust the height according to searched items.
     */
    void setFixedHeightWidget(QWidget *w, int height);
    /*!
     * Set widget fixed height.
     */
    void setMoveWidget(QWidget *w, int pos);
    /*!
     * Set widget moved into given pos.
     */

    void queryAllFinishedMusic();
    /*!
     * Query all quality that musics is finished.
     */
    void queryAllFinishedMovie();
    /*!
     * Query all quality that movies is finished.
     */
    void startToDownloadMusic();
    /*!
     * Strat to download music.
     */
    void startToDownloadMovie();
    /*!
     * Strat to download movie.
     */

    Ui::MusicDownloadWidget *ui;
    MusicDownLoadQueryThreadAbstract *m_downloadThread;
    MusicDownLoadQueryThreadAbstract::QueryType m_queryType;

};

#endif // MUSICDOWNLOADWIDGET_H
