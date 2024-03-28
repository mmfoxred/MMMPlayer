#ifndef MUSICWEBENTAINRADIOLISTVIEW_H
#define MUSICWEBENTAINRADIOLISTVIEW_H

/* =================================================
 * This file is part of the MMM Music Player project
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include <QListWidget>
#include "musicobject.h"
#include "musicglobaldefine.h"

class MusicWebEntainRadioWidget;

/*! @brief The class of the web entain radio widget.
 */
class MUSIC_TOOL_EXPORT MusicWebEntainRadioListView : public QListWidget
{
    Q_OBJECT
public:
    explicit MusicWebEntainRadioListView(QWidget *parent = 0);
    /*!
     * Object contsructor.
     */
    ~MusicWebEntainRadioListView();

    static QString getClassName();
    /*!
     * Get class object name.
     */

public Q_SLOTS:
    void itemHasClicked(QListWidgetItem *item);
    /*!
     * Radio list item has clicked.
     */
    void addListWidgetItem();
    /*!
     * Add radio list into list widget.
     */

protected:
    void clearAllItems();
    /*!
     * Clear All Items.
     */

    MusicWebEntainRadioWidget *m_radioDialog;

};

#endif // MUSICWEBENTAINRADIOLISTVIEW_H
