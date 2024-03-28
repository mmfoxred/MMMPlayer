#ifndef MUSICVIDEOTABLEWIDGET_H
#define MUSICVIDEOTABLEWIDGET_H

/* =================================================
 * This file is part of the MMM Music Player project
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "musicdownloadquerythreadabstract.h"
#include "musicquerytablewidget.h"

/*! @brief The class of the video search table widget.
 */
class MUSIC_VIDEO_EXPORT MusicVideoTableWidget : public MusicQueryTableWidget
{
    Q_OBJECT
public:
    explicit MusicVideoTableWidget(QWidget *parent = 0);
    /*!
     * Object contsructor.
     */
    virtual ~MusicVideoTableWidget();

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
    void resizeWindow(int delta);
    /*!
     * Resize widget size by delta.
     */

Q_SIGNALS:
    void mvURLNameChanged(const QString &name, const QString &data);
    /*!
     * Set current media name and url to play.
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
    void getMusicMvInfo(MusicObject::MusicSongAttributes &data);
    /*!
     * Get music mv information data.
     */
    void downloadLocalFromControl();
    /*!
     * Download current mv by controller.
     */

protected:
    virtual void contextMenuEvent(QContextMenuEvent *event) override;
    /*!
     * Override the widget event.
     */
    QString randToGetStrength() const;
    /*!
     * Get current random video hotter(simulate).
     */
    void downloadLocalMovie(int row);
    /*!
     * Download movie to local file by index.
     */

    QString m_currentSongName;

};

#endif // MUSICVIDEOTABLEWIDGET_H
