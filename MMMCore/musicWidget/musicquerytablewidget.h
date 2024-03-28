#ifndef MUSICQUERYTABLEWIDGET_H
#define MUSICQUERYTABLEWIDGET_H

/* =================================================
 * This file is part of the MMM Music Player project
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "musicabstracttablewidget.h"
#include "musicnetworkthread.h"
#include "musicdownloadquerythreadabstract.h"

#include <QMenu>

class QActionGroup;
class MusicQueryTableDelegate;

/*! @brief The class of the query table widget.
 */
class MUSIC_WIDGET_EXPORT MusicQueryTableWidget : public MusicAbstractTableWidget
{
    Q_OBJECT
public:
    explicit MusicQueryTableWidget(QWidget *parent = 0);
    /*!
     * Object contsructor.
     */
    virtual ~MusicQueryTableWidget();

    static QString getClassName();
    /*!
     * Get class object name.
     */
    virtual void startSearchQuery(const QString &text) = 0;
    /*!
     * Start search query by text.
     * Subclass should implement this function.
     */
    virtual void musicDownloadLocal(int row) = 0;
    /*!
     * Data download to local file.
     * Subclass should implement this function.
     */
    MusicObject::MIntList getSelectedItems() const;
    /*!
     * Get selected items.
     */

Q_SIGNALS:
    void showDownLoadInfoFor(MusicObject::DownLoadType type);
    /*!
     * Show download state type.
     */
    void restartSearchQuery(const QString &name);
    /*!
     * Restart search query by name.
     */

public Q_SLOTS:
    virtual void listCellClicked(int row, int column) override;
    /*!
     * Table widget list cell click.
     */
    virtual void clearAllItems() = 0;
    /*!
     * Clear All Items.
     * Subclass should implement this function.
     */
    virtual void createSearchedItems(const QString &songname,
                                     const QString &artistname,
                                     const QString &time) = 0;
    /*!
     * Create searched items.
     * Subclass should implement this function.
     */
    virtual void itemDoubleClicked(int row, int column) = 0;
    /*!
     * Item has double clicked.
     * Subclass should implement this function.
     */
    virtual void actionGroupClick(QAction *action);
    /*!
     * Left context menu action group click by action.
     */
    void setSelectedAllItems(bool all);
    /*!
     * Set select all items.
     */

protected:
    virtual void contextMenuEvent(QContextMenuEvent *) override {}
    /*!
     * Override the widget event.
     */
    void createContextMenu(QMenu &menu);
    /*!
     * Create context menu.
     */

    QActionGroup *m_actionGroup;
    MusicDownLoadQueryThreadAbstract *m_downLoadManager;
    MusicQueryTableDelegate *m_checkBoxDelegate;

};

#endif // MUSICQUERYTABLEWIDGET_H
