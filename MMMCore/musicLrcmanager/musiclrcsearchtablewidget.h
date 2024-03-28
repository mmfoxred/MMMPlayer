#ifndef MUSICLRCSEARCHTABLEWIDGET_H
#define MUSICLRCSEARCHTABLEWIDGET_H

/* =================================================
 * This file is part of the MMM Music Player project
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "musicquerytablewidget.h"

/*! @brief The class of the lrc search table widget.
 */
class MUSIC_LRC_EXPORT MusicLrcSearchTableWidget : public MusicQueryTableWidget
{
    Q_OBJECT
public:
    explicit MusicLrcSearchTableWidget(QWidget *parent = 0);
    /*!
     * Object contsructor.
     */
    virtual ~MusicLrcSearchTableWidget();

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

Q_SIGNALS:
    void resolvedSuccess();
    /*!
     * Lrc search state is finished.
     */
    void lrcDownloadStateChanged(const QString &name);
    /*!
     * Lrc download state is finished.
     */

public Q_SLOTS:
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

protected:
    virtual void contextMenuEvent(QContextMenuEvent *event) override;
    /*!
     * Override the widget event.
     */

};

#endif // MUSICLRCSEARCHTABLEWIDGET_H
