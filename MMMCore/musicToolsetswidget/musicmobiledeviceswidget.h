#ifndef MUSICMOBILEDEVICESWIDGET_H
#define MUSICMOBILEDEVICESWIDGET_H

/* =================================================
 * This file is part of the MMM Music Player project
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include <QLabel>
#include "musicobject.h"
#include "musicglobaldefine.h"

class QToolButton;

/*! @brief The class of the mobile devices widget.
 */
class MUSIC_TOOLSET_EXPORT MusicMobileDevicesWidget : public QLabel
{
    Q_OBJECT
public:
    explicit MusicMobileDevicesWidget(QWidget *parent = 0);
    /*!
     * Object contsructor.
     */
    ~MusicMobileDevicesWidget();

    static QString getClassName();
    /*!
     * Get class object name.
     */

public Q_SLOTS:
    void showMobileManager();
    /*!
     * Show mobile manager widget.
     */

protected:
    QToolButton *m_closeButton;
    QToolButton *m_openButton;

};

#endif // MUSICMOBILEDEVICESWIDGET_H
