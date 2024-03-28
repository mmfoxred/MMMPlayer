#ifndef MUSICBACKGROUNDREMOTEWIDGET_H
#define MUSICBACKGROUNDREMOTEWIDGET_H

/* =================================================
 * This file is part of the MMM Music Player project
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include <QWidget>
#include "musicglobaldefine.h"
#include "musicobject.h"

class QButtonGroup;
class QListWidgetItem;
class MusicBackgroundListWidget;
class MusicDownloadQueueCache;

/*! @brief The class of the remote background widget.
 */
class MUSIC_WIDGET_EXPORT MusicBackgroundRemoteWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MusicBackgroundRemoteWidget(QWidget *parent = 0);
    /*!
     * Object contsructor.
     */
    ~MusicBackgroundRemoteWidget();

    static QString getClassName();
    /*!
     * Get class object name.
     */
Q_SIGNALS:
    void showCustomSkin(const QString &path);
    /*!
     * Reset the current bg when user click remote bg emit.
     */

public Q_SLOTS:
    void buttonClicked(int index);
    /*!
     * Remote bg type selected by index.
     */
    void itemUserClicked(QListWidgetItem *item);
    /*!
     * User click the current remote item.
     */

protected:
    void initWidget();
    /*!
     * Create all widget in layout.
     */
    void createButton();
    /*!
     * Create remote button.
     */
    void createUrls();
    /*!
     * Create remote urls.
     */
    QStringList createPaths();
    /*!
     * Create download path.
     */

    int m_currentIndex;
    MusicObject::MStringLists m_urls;
    MusicBackgroundListWidget *m_listWidget;
    MusicDownloadQueueCache *m_downloadQueue;
    QButtonGroup *m_group;

};

#endif // MUSICBACKGROUNDREMOTEWIDGET_H
